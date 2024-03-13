//
// Created by Stacy on 3/12/2024.
//

#include "../headers/display.h"
Display::Display() {
    clear();
}

bool Display::debug_draw_byte(uint8_t byte, uint8_t x, uint8_t y) {
    bool erased = false;
    size_t coord_x = x;
    size_t coord_y = y;
    uint8_t b = byte;

    for (int i = 0; i < 8; ++i) {
        size_t index = get_index_from_coords(coord_x, coord_y);

        if (index >= WIDTH * HEIGHT) {
            continue;
        }

        uint8_t bit = (b & 0b10000000) >> 7;
        uint8_t prev_value = screen[index];
        screen[index] ^= bit;

        if (prev_value == 1 && screen[index] == 0) {
            erased = true;
        }

        coord_x += 1;
        b = b << 1;
    }

    return erased;
}

void Display::clear() {
    for (size_t i = 0; i < WIDTH * HEIGHT; ++i) {
        screen[i] = 0;
    }
}

const uint8_t* Display::get_display_buffer() const {
    return screen;
}

size_t Display::get_index_from_coords(size_t x, size_t y) {
    return y * WIDTH + x;
}