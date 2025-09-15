cmake_minimum_required(VERSION 4.0)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled main.cpp
        include/lorenz.hpp
        include/rk4.hpp
        include/euler.hpp
        src/lorenz.cpp
        src/euler.cpp
        src/rk4.cpp)
