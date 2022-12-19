#include "EventEmitter.h"

#ifndef TYPESAFEEVENTEMITTER_MYCLASS_H
#define TYPESAFEEVENTEMITTER_MYCLASS_H



class MyClass {
public:
    enum class BWE_EVENTS {
        INCREASE,
        DECREASE,
        NUM_EVENT_TYPES,  // This must be last, it's a trick for counting the number
                        // of enum elements.
    };
    EventEmitter<BWE_EVENTS> events;

    template <>
    struct EventHandlerInfo<BWE_EVENTS::DECREASE> {
        struct event {
            float a;
            float b;
        };
    };
};

#endif//TYPESAFEEVENTEMITTER_MYCLASS_H
