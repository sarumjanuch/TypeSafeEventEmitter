cmake_minimum_required(VERSION 3.23)
project(TypeSafeEventEmitter)

set(CMAKE_CXX_STANDARD 20)

add_executable(main.cpp MyClass.h src/include/EventEmitter.hpp src/include/HandlerStore.hpp)
