#include "CPU.h"
#include "UnitTests.h"
#include <iostream>
#include <fstream>
#include <exception>
int main() {
    cpu cpu{};
 
    std::ifstream file{"ass.prg", std::ios::binary | std::ios::ate};
    try {
        if (!file.is_open())
            throw std::exception("failed to open file");
    }
    catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    /*size_t fileSize = file.tellg();
    cpu.memory.resize(0xffff);
    file.seekg(0);
    file.read(cpu.memory.data(), fileSize);*/

    cpu.memory.resize(0xffff);
    cpu.memory[0] = 0x69;
    cpu.memory[1] = 255;
    cpu.AReg = 10;

    try {
        while (true)
            cpu.tick();
    }
    catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }
}