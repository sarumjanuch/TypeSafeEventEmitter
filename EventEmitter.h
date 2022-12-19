#include <array>
#include <forward_list>
#include <functional>
#include <iostream>

#ifndef TYPESAFEEVENTEMITTER_EVENTEMITTER_HPP
#define TYPESAFEEVENTEMITTER_EVENTEMITTER_HPP

// This base class exists so that the EventEmitter has object instances to
// store.
class HandlerStorageBase {
    virtual ~HandlerStorageBase() = default;
    virtual void Handle(void* args) = 0;
};

template <typename EVENTS, typename std::enable_if<std::is_enum<EVENTS>::value>::type* = nullptr>
struct EventHandlerInfo {
    // This base case will cause a compile error for any BWE_EVENT types that
    // haven't been specialized and therefore don't have an Args signature.
};

template <typename EVENTS, typename std::enable_if<std::is_enum<EVENTS>::value>::type* = nullptr>
class EventEmitter {
public:
    ~EventEmitter() = default;

    struct HandlerStorage : public HandlerStorageBase {
        using EventArgsType = typename EventHandlerInfo<EVENTS>::event;
        using HandlerType = std::function<void(EventArgsType*)>;

        HandlerStorage(HandlerType handler) : handler_(handler) {}

        ~HandlerStorage() override = default;

        // The function arg here can be char* instead. The idea is to have it a single
        // generic pointer, which we can convert to the real type in a type safe way,
        // since this templated structure knows the real type.
        void Handle(void* args) override {
            handler_(reinterpret_cast<EventArgsType*>(args));
        }
    private:
        HandlerType handler_;
    };

    template <EVENTS T>
    void Subscribe(typename HandlerStorage<T>::HandlerType handler) {
        handlers_[static_cast<std::size_t>(T)] =
                std::make_unique<HandlerStorage<T>>(handler);
    }

    template <EVENTS T>
    void Emit(typename HandlerStorage<T>::EventArgsType* args) {
        handlers_[static_cast<std::size_t>(T)]->Handle(args);
    }

    std::array<std::unique_ptr<HandlerStorageBase>,
               (size_t)EVENTS::NUM_EVENT_TYPES>
            handlers_;
    EventEmitter() = default;
};

#endif//TYPESAFEEVENTEMITTER_EVENTEMITTER_HPP
