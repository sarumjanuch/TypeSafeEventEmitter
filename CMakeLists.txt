cmake_minimum_required(VERSION 3.23)
project(TypeSafeEventEmitter)

set(CMAKE_CXX_STANDARD 17)

add_executable(TypeSafeEventEmitter EventEmitter.h MyClass.h main.cpp)
