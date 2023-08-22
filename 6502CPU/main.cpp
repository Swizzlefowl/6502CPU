#include "CPU.h"
int main() {

    cpu cpu{};

    for (int index{10}; index > 0; index--) {
        cpu.memory.push_back(static_cast<std::uint16_t>(index));
    }

   auto num = cpu.readWord();
    fmt::println("{}", num);

}