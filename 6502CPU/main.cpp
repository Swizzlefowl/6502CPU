#include "CPU.h"
int main() {
    cpu cpu{};

    cpu.memory[21] = 10;
    cpu.pc = 20;
    cpu.pc = cpu.instr.fetchArgumentadress(Instructions::Relative);
    fmt::println("{}", cpu.pc);
   
}