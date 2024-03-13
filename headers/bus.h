//
// Created by Stacy on 3/12/2024.
//

#ifndef CHIP8_BUS_H
#define CHIP8_BUS_H

#include <chrono>
#include "ram.h"
#include "display.h"
#include "keyboard.h"

class Bus {
private:
    Ram ram;
    Display display;
    Keyboard keyboard;
    uint8_t delay_timer;
    std::chrono::steady_clock::time_point delay_timer_set_time;

public:
    Bus();

    uint8_t ram_read_byte(uint16_t address) const;

    void ram_write_byte(uint16_t address, uint8_t value);

    bool debug_draw_byte(uint8_t byte, uint8_t x, uint8_t y);

    void clear_screen();

    void set_key_pressed(std::optional<uint8_t> key);

    bool is_key_pressed(uint8_t key_code) const;

    std::optional<uint8_t> get_key_pressed() const;

    void set_delay_timer(uint8_t value);

    uint8_t get_delay_timer() const;

    const uint8_t * get_display_buffer() const;

    void print_ram() const;
};

#endif //CHIP8_BUS_H
