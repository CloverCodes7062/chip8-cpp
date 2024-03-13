//
// Created by Stacy on 3/12/2024.
//

#include "../headers/chip8.h"
#include <vector>

Chip8::Chip8() : bus() {}

void Chip8::load_rom(const std::vector<uint8_t> &data) {
    for (size_t i = 0; i < data.size(); ++i) {
        bus.ram_write_byte(0x200 + i, data[i]);
    }
}

void Chip8::print_ram() const {
    bus.print_ram();
}

void Chip8::run_instruction() {
    cpu.run_instruction(bus);
}

const uint8_t * Chip8::get_display_buffer() {
    return bus.get_display_buffer();
}

void Chip8::set_key_pressed(std::optional<uint8_t> key) {
    bus.set_key_pressed(key);
}
