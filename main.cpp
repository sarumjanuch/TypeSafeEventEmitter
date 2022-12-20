
#include <array>
#include <forward_list>
#include <functional>
#include <iostream>
#include "MyClass.h"

int main() {

    // This defines the actual events that can be emitted.

    auto myClass = new MyClass();

    myClass->events.Subscribe<BWE_EVENTS::INCREASE>([](auto &event) {

                  });

/*    myClass.events.Subscribe<BWE_EVENTS::DECREASE>([](auto args) {
        std::cout << "a=" << args->a << " b=" << args->b << std::endl;
    });*/


/*    std::cout << "This should invoke the increase handler." << std::endl;
    myClass.events.Emit<MyClass::BWE_EVENTS::INCREASE>({
            .a = 6.5,
            .b = 7.8,
    });

    std::cout << "This should invoke the decrease handler." << std::endl;
    myClass.events.Emit<MyClass::BWE_EVENTS::DECREASE>(auto {
            .a = 6.5,
            .b = 7.8,
    });*/
}