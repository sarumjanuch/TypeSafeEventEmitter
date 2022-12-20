#include "MyClass.h"
#include <functional>
#include <iostream>

int main() {

    // This defines the actual events that can be emitted.

    auto myClass = new MyClass();

    myClass->events.Subscribe<BWE_EVENTS::INCREASE>([](const auto &args) {
        std::cout << "a=" << args.a << " b=" << args.b << std::endl;
    });

    myClass->events.Subscribe<BWE_EVENTS::DECREASE>([](const auto &args) {
        std::cout << "a=" << args.a << " b=" << args.b << std::endl;
    });

    myClass->events.Emit<BWE_EVENTS::INCREASE>({.a = 1, .b = 2});

    myClass->events.Emit<BWE_EVENTS::DECREASE>({.a = 6.5, .b = 7.5});
}