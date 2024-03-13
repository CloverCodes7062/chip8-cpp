#include <iostream>
#include <string>
#include <fstream>
#include "chip8.h"

using namespace std;

int main(int argc, char* argv[]) {
    std::ifstream file(R"(C:\Users\Stacy\Desktop\cppProjects\chip8\data\TETRIS.bin)", std::ios::binary);

    std::vector<unsigned char> rom_data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

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

    return 0;
}


