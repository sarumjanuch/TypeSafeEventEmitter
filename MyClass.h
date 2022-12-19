#include "EventEmitter.h"

#ifndef TYPESAFEEVENTEMITTER_MYCLASS_H
#define TYPESAFEEVENTEMITTER_MYCLASS_H

enum class BWE_EVENTS {
    INCREASE,
    DECREASE,
    NUM_EVENT_TYPES,  // This must be last, it's a trick for counting the number
                    // of enum elements.
};

class MyClass {
public:
    MyClass() = default;
    ~MyClass() = default;

    EventEmitter<BWE_EVENTS> events;

    template <>
    struct EventHandlerInfo<BWE_EVENTS::INCREASE> {
        struct event {
            int a;
            int b;
        };
    };
};

#endif//TYPESAFEEVENTEMITTER_MYCLASS_H
