#include "CPU.h"
std::uint8_t cpu::readByte() {
    return memory[pc];
}
std::uint16_t cpu::readWord() {
    std::uint16_t loByte{};
    std::uint16_t HiByte{};
    loByte = readByte();
    fmt::println("{}", loByte);
    pc++;
    HiByte = (readByte() << 8);
    fmt::println("{}", HiByte);
    return HiByte | loByte;
}
cpu::cpu()
    : instr{*this} {
   
}

cpu::~cpu() {

}

void StatusRegister::set(const FlagBits& Mask) {
    this->flags = this->flags | Mask;
}

void StatusRegister::clear(const FlagBits& Mask) {
    this->flags = this->flags ^ Mask;
}

bool StatusRegister::isSet(const FlagBits& Mask) {
    return (this->flags & Mask) != 0;
}

