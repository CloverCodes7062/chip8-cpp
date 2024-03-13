//
// Created by Stacy on 3/13/2024.
//

#ifndef CHIP8_KEYBOARD_H
#define CHIP8_KEYBOARD_H


#include <cstdint>
#include <optional>

class Keyboard {
private:
    std::optional<uint8_t> key_pressed;

public:
    Keyboard();
    bool is_key_pressed(uint8_t key_code) const;
    void set_key_pressed(std::optional<uint8_t> key);
    std::optional<uint8_t> get_key_pressed() const;
};

#endif //CHIP8_KEYBOARD_H
