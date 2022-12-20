#include <array>
#include <forward_list>
#include <functional>
#include <iostream>
#include "HandlerStore.hpp"
#ifndef TYPESAFEEVENTEMITTER_EVENTEMITTER_HPP
#define TYPESAFEEVENTEMITTER_EVENTEMITTER_HPP

// This base class exists so that the EventEmitter has object instances to
// store.

template <typename EVENTS, typename std::enable_if<std::is_enum<EVENTS>::value>::type* = nullptr>
class EventEmitter : public HandlerStorage<EVENTS> {
public:
    EventEmitter() = default;
    ~EventEmitter() = default;

    template <EVENTS T>
    void Subscribe(typename HandlerStorage<T>::HandlerType handler) {
        handlers_[static_cast<std::size_t>(T)] =
                std::make_unique<HandlerStorage<EVENTS>>(handler);
    }

    template <EVENTS T>
    void Emit(typename HandlerStorage<T>::EventArgsType* args) {
        handlers_[static_cast<std::size_t>(T)]->Handle(args);
    }

    std::array<std::unique_ptr<HandlerStorageBase>,
               (size_t)EVENTS::NUM_EVENT_TYPES>
            handlers_;
};


#endif//TYPESAFEEVENTEMITTER_EVENTEMITTER_HPP
