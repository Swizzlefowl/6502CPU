#include "CPU.h"
#include "UnitTests.h"
#include <iostream>
#include <fstream>
#include <exception>
int main() {
    cpu cpu{};
 
    std::ifstream file{"nestest.nes", std::ios::binary | std::ios::ate};
    try {
        if (!file.is_open())
            throw std::exception("failed to open file");
    }
    catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }

    size_t fileSize = file.tellg();
    cpu.memory.resize(0xffff);
    file.seekg(0);
    file.read(cpu.memory.data(), fileSize);
    
    try {
        while (true)
            cpu.tick();
    }
    catch (std::exception& err) {
        std::cout << err.what() << std::endl;
    }
}