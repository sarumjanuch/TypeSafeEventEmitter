//
// Created by Eugene Voityuk on 19.12.2022.
//
#include <forward_list>
#include <functional>
#ifndef TYPESAFEEVENTEMITTER_HANDLERSTORAGE_H
#define TYPESAFEEVENTEMITTER_HANDLERSTORAGE_H

struct HandlerStorageBase {
    virtual void Handle(void* args) = 0;
protected:
    virtual ~HandlerStorageBase() = default;
};

template <typename EVENTS>
struct HandlerStorage : public HandlerStorageBase {
    template <EVENTS T>
    struct EventHandlerInfo {
        // This base case will cause a compile error for any BWE_EVENT types that
        // haven't been specialized and therefore don't have an Args signature.
    };
    using EventArgsType = typename EventHandlerInfo<T>::event;
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
#endif//TYPESAFEEVENTEMITTER_HANDLERSTORAGE_H
