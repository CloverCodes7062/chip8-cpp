//
// Created by Stacy on 3/12/2024.
//

#ifndef CHIP8_CHIP8_H
#define CHIP8_CHIP8_H

#include <vector>
#include "ram.h"
#include "bus.h"
#include "cpu.h"

class Chip8 {
private:
    Bus bus;
    Cpu cpu;

public:
    Chip8();
    void load_rom(const std::vector<uint8_t>& data);
    void run_instruction();
    void print_ram() const;

    const uint8_t * get_display_buffer();
};

#endif //CHIP8_CHIP8_H
