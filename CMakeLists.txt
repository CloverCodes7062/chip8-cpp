cmake_minimum_required(VERSION 3.27)
project(chip8)

set(CMAKE_CXX_STANDARD 14)

set(SFML_ROOT "C:/Users/Stacy/Desktop/cppProjects/chip8/SFML-2.6.1")

find_package(SFML 2.6.1 COMPONENTS graphics window system REQUIRED)

add_executable(chip8
        main.cpp
        chip8.cpp
        chip8.h
        ram.cpp
        ram.h
        cpu.cpp
        cpu.h
        bus.cpp
        bus.h
        display.cpp
        display.h
)

target_link_libraries(chip8 sfml-graphics sfml-window sfml-system)
