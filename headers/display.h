//
// Created by Stacy on 3/12/2024.
//

#ifndef CHIP8_DISPLAY_H
#define CHIP8_DISPLAY_H

#include <cstdint>

class Display {
public:
    Display();
    bool debug_draw_byte(uint8_t byte, uint8_t x, uint8_t y);
    void clear();
    const uint8_t* get_display_buffer() const;

    static size_t get_index_from_coords(size_t x, size_t y);

private:
    static constexpr size_t WIDTH = 64;
    static constexpr size_t HEIGHT = 32;
    uint8_t screen[WIDTH * HEIGHT];

};

#endif //CHIP8_DISPLAY_H
