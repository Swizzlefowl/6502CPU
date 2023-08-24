#include "CPU.h"

// reads an uint8 byte from cpu memory
std::uint8_t cpu::readByte(std::uint16_t adress) {
    return memory[adress];
}

// reads an uint16 word from cpu memory
std::uint16_t cpu::readWord(std::uint16_t adress) {
    std::uint16_t loByte{};
    std::uint16_t HiByte{};

    loByte = readByte(adress);
    HiByte = (readByte(adress + 1) << 8);

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

