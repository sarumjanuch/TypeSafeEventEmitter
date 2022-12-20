#include "src/include/EventEmitter.h"
#include <forward_list>
#include <functional>

#ifndef TYPESAFEEVENTEMITTER_MYCLASS_H
#define TYPESAFEEVENTEMITTER_MYCLASS_H


struct BWE_EVENTS {
    enum EVENTS {
        INCREASE,
        DECREASE,
        NUM_EVENT_TYPES,// This must be last, it's a trick for counting the number
                        // of enum elements.
    };

    template<EVENTS T>
    struct Event {
        // Leave empty, this causes a compile error for unspecialized EVENT types.
    };

    // For each event type you need to define a struct with a substruct Args.
    // With some tweaks this could also be made into struct Args<INCREASE>.
    template<>
    struct Event<INCREASE> {
        struct Args {
            int a;
            int b;
        };
    };

    template<>
    struct Event<DECREASE> {
        struct Args {
            float a;
            float b;
        };
    };
};

class MyClass {
public:
    MyClass() = default;
    ~MyClass() = default;

    EventEmitter<BWE_EVENTS> events;
};

#endif//TYPESAFEEVENTEMITTER_MYCLASS_H
