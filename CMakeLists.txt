cmake_minimum_required(VERSION 3.31)
project(rc_simulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(rc_simulator main.cpp
        resistor.cpp
        resistor.h
        capacitor.cpp
        capacitor.h
        component.cpp
        component.h
connectivity/pin.h
connectivity/pin.cpp)

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(rc_simulator PRIVATE SDL3::SDL3)
