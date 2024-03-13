//
// Created by Stacy on 3/13/2024.
//

#ifndef CHIP8_ENGINE_H
#define CHIP8_ENGINE_H

#include <SFML/Graphics.hpp>
#include "chip8.h"

class Engine {
public:
    Engine(const std::string& rom_path);
    void run();
    bool key_pressed;

private:
    static const int WIDTH = 640;
    static const int HEIGHT = 320;

    sf::RenderWindow window;
    Chip8 chip8;
    std::vector<uint32_t> buffer;

    std::chrono::steady_clock::time_point last_instruction_run_time;
    std::chrono::steady_clock::time_point last_key_update_time;

    void process_input();
    void update();
    void render();
};

#endif //CHIP8_ENGINE_H
