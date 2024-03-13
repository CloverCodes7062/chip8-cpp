#include <iostream>
#include <string>
#include <fstream>
#include "../headers/chip8.h"
#include "engine.h"


using namespace std;
const int HEIGHT = 640;
const int WIDTH = 320;
const int SCALE = 10;

int main(int argc, char* argv[]) {
    string rom_path = R"(C:\Users\Stacy\Desktop\cppProjects\chip8\data\MERLIN.bin)";

    Engine engine(rom_path);
    engine.run();

    return 0;
}


