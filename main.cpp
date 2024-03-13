#include <iostream>
#include <string>
#include <fstream>
#include "chip8.h"
#include <SFML/Graphics.hpp>

using namespace std;
const int HEIGHT = 640;
const int WIDTH = 320;
const int SCALE = 10;

int main(int argc, char* argv[]) {
    std::ifstream file(R"(C:\Users\Stacy\Desktop\cppProjects\chip8\data\TETRIS.bin)", std::ios::binary);

    std::vector<unsigned char> rom_data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    std::vector<uint32_t> buffer(WIDTH * HEIGHT, 0);

    Chip8 chip8;
    chip8.load_rom(rom_data);
    chip8.print_ram();

    while (true) {
       try {
           chip8.run_instruction();
       } catch (const std::runtime_error& e) {
           break;
       }
    }

    auto chip8_buffer = chip8.get_display_buffer();


    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            int index = Display::get_index_from_coords(x / 10, y / 10);
            int pixel = chip8_buffer[index];
            int color_pixel = pixel == 0 ? 0x0 : 0xffffff;
            buffer[y * WIDTH + x] = color_pixel;
        }
    }

    return 0;
}


