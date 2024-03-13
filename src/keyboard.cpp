//
// Created by Stacy on 3/13/2024.
//

#include "keyboard.h"
#include "bus.h"

Keyboard::Keyboard() : key_pressed(std::nullopt) {}

bool Keyboard::is_key_pressed(uint8_t key_code) const {
    return key_pressed.has_value() && key_pressed.value() == key_code;
}

void Keyboard::set_key_pressed(std::optional <uint8_t> key) {
    key_pressed = key;
}

std::optional<uint8_t> Keyboard::get_key_pressed() const {
    return key_pressed;
}