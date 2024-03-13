//
// Created by Stacy on 3/13/2024.
//

#include <fstream>
#include <iostream>
#include <SFML/Window.hpp>
#include "engine.h"
std::optional<uint8_t> get_chip8_keycode_for(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Key::Num1: return 0x1;
        case sf::Keyboard::Key::Num2: return 0x2;
        case sf::Keyboard::Key::Num3: return 0x3;
        case sf::Keyboard::Key::Num4: return 0xC;

        case sf::Keyboard::Key::Q: return 0x4;
        case sf::Keyboard::Key::W: return 0x5;
        case sf::Keyboard::Key::E: return 0x6;
        case sf::Keyboard::Key::R: return 0xD;

        case sf::Keyboard::Key::A: return 0x7;
        case sf::Keyboard::Key::S: return 0x8;
        case sf::Keyboard::Key::D: return 0x9;
        case sf::Keyboard::Key::F: return 0xE;

        case sf::Keyboard::Key::Z: return 0xA;
        case sf::Keyboard::Key::X: return 0x0;
        case sf::Keyboard::Key::C: return 0xB;
        case sf::Keyboard::Key::V: return 0xF;

        default: return std::nullopt;
    }
}

Engine::Engine(const std::string& rom_path)
        : window(sf::VideoMode(WIDTH, HEIGHT), "Chip8 Emulator"), buffer(WIDTH * HEIGHT, 0), chip8() {
    std::ifstream file(rom_path, std::ios::binary);

    if (file.is_open()) {
        std::vector<unsigned char> rom_data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        chip8.load_rom(rom_data);
        file.close();
        chip8.print_ram();

        last_instruction_run_time = std::chrono::steady_clock::now();
        last_key_update_time = std::chrono::steady_clock::now();

    } else {
        std::cerr << "Failed to open ROM file." << std::endl;
    }
}

void Engine::run() {
    while (window.isOpen()) {
        process_input();
        update();
        render();
    }
}

void Engine::process_input() {
    auto current_time = std::chrono::steady_clock::now();
    auto diff_update_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_key_update_time).count();
    if (diff_update_time < 300) {
        return;
    }

    sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        else if (event.type == sf::Event::KeyPressed) {
            auto chip8_key = get_chip8_keycode_for(event.key.code);

            if (chip8_key.has_value()) {

                chip8.set_key_pressed(chip8_key);

                last_key_update_time = std::chrono::steady_clock::now();
            }
        }
    }
}

void Engine::update() {

    auto current_time = std::chrono::steady_clock::now();

    auto diff_update_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - last_instruction_run_time).count();

    if (diff_update_time > 8) {
        chip8.run_instruction();
        last_instruction_run_time = current_time;
    }

    auto chip8_buffer = chip8.get_display_buffer();

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            int index = Display::get_index_from_coords(x / 10, y / 10);
            int pixel = chip8_buffer[index];
            int color_pixel = pixel == 0 ? 0x000000FF : 0xFFFFFFFF;
            buffer[y * WIDTH + x] = color_pixel;
        }
    }
}

void Engine::render() {
    window.clear();
    sf::Texture texture;
    texture.create(WIDTH, HEIGHT);
    texture.update(reinterpret_cast<sf::Uint8*>(buffer.data()));

    sf::Sprite sprite(texture);
    window.draw(sprite);

    window.display();
}
