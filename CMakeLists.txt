cmake_minimum_required(VERSION 3.27)
project(chip8)

set(CMAKE_CXX_STANDARD 14)

add_executable(chip8
        src/main.cpp
        src/chip8.cpp
        headers/chip8.h
        src/ram.cpp
        headers/ram.h
        src/cpu.cpp
        headers/cpu.h
        src/bus.cpp
        headers/bus.h
        src/display.cpp
        headers/display.h
        headers/engine.h
        src/engine.cpp
)

include_directories(headers c:/SFML/include)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics)

if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(chip8 ${SFML_LIBRARIES})
endif()

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
if (WIN32)
    file(GLOB BINARY_DEP_DLLS "${SFML_INCLUDE_DIR}/../bin/*.dll")
    file(COPY ${BINARY_DEP_DLLS} DESTINATION ${CMAKE_BINARY_DIR})
endif()

