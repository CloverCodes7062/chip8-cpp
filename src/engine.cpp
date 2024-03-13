//
// Created by Stacy on 3/13/2024.
//

#include <fstream>
#include <iostream>
#include "engine.h"
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
