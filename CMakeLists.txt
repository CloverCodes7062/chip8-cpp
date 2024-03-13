cmake_minimum_required(VERSION 3.27)
project(chip8)

set(CMAKE_CXX_STANDARD 14)

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
