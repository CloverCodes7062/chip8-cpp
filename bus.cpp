//
// Created by Stacy on 3/12/2024.
//

#include <iostream>
#include "bus.h"

Bus::Bus() : ram(), display(), delay_timer(0), delay_timer_set_time(std::chrono::steady_clock::now()) {}

uint8_t Bus::ram_read_byte(uint16_t address) const {
    return ram.read_byte(address);
}

void Bus::ram_write_byte(uint16_t address, uint8_t value) {
    ram.write_byte(address, value);
}

void Bus::print_ram() const {
    ram.print_ram();
}

void Bus::clear_screen() {

}

bool Bus::debug_draw_byte(uint8_t byte, uint8_t x, uint8_t y) {
    return display.debug_draw_byte(byte, x, y);
}