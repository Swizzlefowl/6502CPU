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
    int opCount{0x10};
    size_t fileSize = file.tellg();
    cpu.memory.resize(0xffff);
    file.seekg(0x10);
    file.read((cpu.memory.data()), fileSize);
  
    try {
        while (cpu.pc < (0xffff + 1)) {
            cpu.tick();
            opCount++;
        }
    }
    catch (std::exception& err) {
        fmt::println("{}", opCount);
        std::cout << err.what() << std::endl;
    }
    
}