cmake_minimum_required(VERSION 3.31)
project(rc_simulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(rc_simulator main.cpp
        components/resistor.cpp
        components/resistor.h
        capacitor.cpp
        capacitor.h
        components/component.cpp
        components/component.h
        components/node.h
        components/node.cpp
        circuit.cpp
        circuit.h
        parser/netlist_parser.h
        components/current_source.cpp
        components/current_source.h
        matrix.cpp
        matrix.h
        components/voltage_source.cpp
        components/voltage_source.h)

find_package(SDL3 CONFIG REQUIRED)
target_link_libraries(rc_simulator PRIVATE SDL3::SDL3)
