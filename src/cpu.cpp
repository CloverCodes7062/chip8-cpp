//
// Created by Stacy on 3/12/2024.
//

#include <iostream>
#include <random>
#include "../headers/cpu.h"
const uint16_t PROGRAM_START = 0x200;

Cpu::Cpu() : vx(16, 0), pc(PROGRAM_START), i(0), ret_stack() {}

void Cpu::run_instruction(Bus &bus) {
    uint16_t hi = bus.ram_read_byte(pc);
    uint16_t lo = bus.ram_read_byte(pc + 1);
    uint16_t instruction = (hi << 8) | lo;

    std::cout << "Instruction Read instruction " << std::hex << std::showbase << instruction << ": pc "
              << std::hex << std::showbase << static_cast<int>(pc) << ", hi: " << std::hex << std::showbase << static_cast<int>(hi) << ", lo: "
              << std::hex << std::showbase << static_cast<int>(lo) << std::endl;

    uint16_t nnn = instruction & 0x0FFF;
    uint8_t nn = instruction & 0x00FF;
    uint8_t n = instruction & 0x000F;
    uint8_t x = (instruction & 0x0F00) >> 8;
    uint8_t y = (instruction & 0x00F0) >> 4;

    std::cout << "nnn=" << std::hex << std::showbase << static_cast<int>(nnn) << ", nn=" << std::hex << std::showbase << static_cast<int>(nn)
              << ", n=" << std::hex << std::showbase << static_cast<int>(n) << ", x=" << static_cast<int>(x) << ", y="
              << static_cast<int>(y) << std::endl;

    switch ((instruction & 0xF000) >> 12) {
        case 0x0: {
            switch (nn) {
                case 0xE0: {
                    bus.clear_screen();
                    pc += 2;
                    break;
                }
                case 0xEE: {
                    pc = ret_stack.top();
                    ret_stack.pop();
                    break;
                }
                default: {
                    std::cerr << "Unknown 0x00** instruction: " << std::hex << pc << ": " << instruction << std::endl;
                    Cpu::panic();
                    break;
                }
            }
            break;
        }
        case 0x1: {
            pc = nnn;
            break;
        }
        case 0x2: {
            ret_stack.push(pc + 2);
            pc = nnn;
            break;
        }
        case 0x3: {
            uint8_t local_vx = read_reg_vx(x);
            if (local_vx == nn) {
                pc += 4;
            } else {
                pc += 2;
            }
            break;
        }
        case 0x4: {
            uint8_t local_vx = read_reg_vx(x);
            if (local_vx != nn) {
                pc += 4;
            } else {
                pc += 2;
            }
            break;
        }
        case 0x5: {
            uint8_t local_vx = read_reg_vx(x);
            uint8_t local_vy = read_reg_vx(y);

            if (local_vx == local_vy) {
                pc += 4;
            } else {
                pc += 2;
            }
            break;
        }
        case 0x6: {
            write_reg_vx(x, nn);
            pc += 2;
            break;
        }
        case 0x7: {
            uint8_t local_vx = read_reg_vx(x);
            local_vx += nn;
            write_reg_vx(x, local_vx);
            pc += 2;
            break;
        }
        case 0x8: {
            uint8_t vx = read_reg_vx(x);
            uint8_t vy = read_reg_vx(y);

            switch (n) {
                case 0: {
                    write_reg_vx(x, vy);
                    break;
                }
                case 2: {
                    write_reg_vx(x, vx & vy);
                    break;
                }
                case 3: {
                    write_reg_vx(x, vx ^ vy);
                    break;
                }
                case 4: {
                    uint16_t sum = static_cast<uint16_t>(vx) + static_cast<uint16_t>(vy);
                    write_reg_vx(x, static_cast<uint8_t>(sum));
                    if (sum > 0xFF) {
                        write_reg_vx(0xF, 1);
                    } else {
                        write_reg_vx(0xF, 0);
                    }
                    break;
                }
                case 5: {
                    int8_t diff = static_cast<int8_t>(vx) - static_cast<int8_t>(vy);
                    write_reg_vx(x, static_cast<uint8_t>(diff));
                    if (diff < 0) {
                        write_reg_vx(0xF, 0);
                    } else {
                        write_reg_vx(0xF, 1);
                    }
                    break;
                }
                case 6: {
                    write_reg_vx(0xF, vy & 0x1);
                    write_reg_vx(y, vy >> 1);
                    write_reg_vx(x, vy >> 1);
                    break;
                }
                default: {
                    throw std::runtime_error("Unknown 0x8** instruction");
                }
            }
            pc += 2;
            break;
        }
        case 0x9: {
            uint8_t local_vx = read_reg_vx(x);
            uint8_t local_vy = read_reg_vx(y);

            if (local_vx != local_vy) {
                pc += 4;
            } else {
                pc += 2;
            }
            break;
        }
        case 0xA: {
            i = nnn;
            pc += 2;
            break;
        }
        case 0xC: {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<uint8_t> dist(0, 255);
            uint8_t random_number = dist(gen);
            uint8_t result = random_number & nn;
            write_reg_vx(x, result);

            pc += 2;
            break;
        }
        case 0xD: {
            uint8_t local_vx = read_reg_vx(x);
            uint8_t local_vy = read_reg_vx(y);

            debug_draw_sprite(bus, local_vx, local_vy, n);
            pc += 2;
            break;
        }
        case 0xE: {
            switch (nn) {
                case 0xA1: {
                    uint8_t key = read_reg_vx(x);
                    if (!bus.is_key_pressed(key)) {
                        pc += 4;
                    } else {
                        pc += 2;
                    }
                    break;
                }
                case 0x9E: {
                    uint8_t key = read_reg_vx(x);
                    if (bus.is_key_pressed(key)) {
                        pc += 4;
                    } else {
                        pc += 2;
                    }
                    break;
                }
                default:
                    std::cerr << "Unknown 0xEX** instruction: " << std::hex << pc << ": " << instruction << std::endl;
                    panic();
                    break;
            }
            break;
        }
        case 0xF: {
            switch (nn) {
                case 0x7: {
                    write_reg_vx(x, bus.get_delay_timer());
                    pc += 2;
                    break;
                }
                case 0x15: {
                    bus.set_delay_timer(read_reg_vx(x));
                    pc += 2;
                    break;
                }
                case 0x29: {
                    uint8_t local_vx = read_reg_vx(x);
                    i = local_vx * 5;
                    pc += 2;
                }
                case 0x33: {
                    uint8_t local_vx = read_reg_vx(x);
                    uint8_t hundreds = local_vx / 100;
                    uint8_t tens = (local_vx % 100) / 10;
                    uint8_t ones = local_vx % 10;
                    bus.ram_write_byte(i, hundreds);
                    bus.ram_write_byte(i + 1, tens);
                    bus.ram_write_byte(i + 2, ones);
                    pc += 2;
                    break;
                }
                case 0x55: {
                    for (int index = 0; index <= x; ++index) {
                        uint8_t value = read_reg_vx(index);
                        bus.ram_write_byte(i + index, value);
                    }
                    i += x + 1;
                    pc += 2;
                    break;
                }
                case 0x65: {
                    for (int index = 0; index <= x; ++index) {
                        uint8_t value = bus.ram_read_byte(i + index);
                        write_reg_vx(index, value);
                    }
                    pc += 2;
                    break;
                }
                case 0x0A: {
                    std::optional<uint8_t> key = bus.get_key_pressed();
                    if (key.has_value()) {
                        write_reg_vx(x, key.value());
                        pc += 2;
                    }
                    break;
                }
                case 0x1E: {
                    uint8_t local_vx = read_reg_vx(x);
                    i += local_vx;
                    pc += 2;
                    break;
                }
                default: {
                    std::cerr << "Unknown 0xF0** instruction: " << std::hex << pc << ": " << instruction << std::endl;
                    Cpu::panic();
                    break;
                }
            }
            break;
        }
        default: {
            std::cerr << "Unknown instruction: " << std::hex << pc << ": " << instruction << std::endl;
            Cpu::panic();
            break;
        }
    }
}

void Cpu::write_reg_vx(uint8_t index, uint8_t value) {
    vx[index] = value;
}

void Cpu::panic() {
    throw std::runtime_error("Panic! Unknown instruction.");
}

uint8_t Cpu::read_reg_vx(uint8_t index) {
    return vx[index];
}

void Cpu::debug_draw_sprite(Bus &bus, uint8_t x, uint8_t y, uint8_t height) {
    std::cout << "DRAWING PIXEL AT (" << static_cast<int>(x) << ", " << static_cast<int>(y) << ")" << std::endl;

    bool should_set_vf = false;

    for (uint8_t sprite_y = 0; sprite_y < height; ++sprite_y) {
        uint8_t byte = bus.ram_read_byte(i + sprite_y);
        if (bus.debug_draw_byte(byte, x, y + sprite_y)) {
            should_set_vf = true;
        }
    }

    if (should_set_vf) {
        write_reg_vx(0xF, 1);
    } else {
        write_reg_vx(0xF, 0);
    }
}
