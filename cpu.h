//
// Created by Stacy on 3/12/2024.
//

#ifndef CHIP8_CPU_H
#define CHIP8_CPU_H

#include <cstdint>
#include <vector>
#include <stack>
#include "bus.h"

class Bus;

class Cpu {
private:
    std::vector<uint8_t> vx;
    uint16_t pc;
    uint16_t i;
    std::stack<uint16_t> ret_stack;

public:
    Cpu();

    void run_instruction(Bus& bus);
    void debug_draw_sprite(Bus& bus, uint8_t x, uint8_t y, uint8_t height);
    void write_reg_vx(uint8_t index, uint8_t value);
    uint8_t read_reg_vx(uint8_t index);
    void panic();
};

#endif //CHIP8_CPU_H
