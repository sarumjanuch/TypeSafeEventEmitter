#include "src/include/EventEmitter.hpp"
#include "src/include/HandlerStore.hpp"
#include <forward_list>
#include <functional>
#ifndef TYPESAFEEVENTEMITTER_MYCLASS_H
#define TYPESAFEEVENTEMITTER_MYCLASS_H

enum struct BWE_EVENTS {
    INCREASE,
    DECREASE,
    NUM_EVENT_TYPES,  // This must be last, it's a trick for counting the number
                    // of enum elements.
};

template<> template<>
struct HandlerStorage<BWE_EVENTS>::EventHandlerInfo<BWE_EVENTS::INCREASE> {
    struct event {
        int a;
        int b;
    };
};

class MyClass {
public:
    MyClass() = default;
    ~MyClass() = default;

    EventEmitter<BWE_EVENTS> events;
};

#endif//TYPESAFEEVENTEMITTER_MYCLASS_H
