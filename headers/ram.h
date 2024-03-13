//
// Created by Stacy on 3/12/2024.
//

#ifndef CHIP8_RAM_H
#define CHIP8_RAM_H

#include <array>
#include <cstdint>

class Ram {
private:
    std::array<uint8_t, 4096> mem;

public:
    Ram();
    void write_byte(uint16_t address, uint8_t value);
    uint8_t read_byte(uint16_t address) const;
    void print_ram() const;
};
#endif //CHIP8_RAM_H
