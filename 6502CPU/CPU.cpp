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

void cpu::pushByte(std::uint8_t value) {
    this->memory[sp] = value;
    --sp;

    return;
}

std::uint8_t cpu::popByte() {
    sp++;
    auto value = this->memory[sp];

    return value;
}

void cpu::pushWord(std::uint16_t value) {
    std::uint8_t LoByte = value >> 8;
    std::uint8_t HiByte = (value & 0x00ff);

    pushByte(HiByte);
    pushByte(LoByte);
}

std::uint16_t cpu::popWord() {
    std::uint16_t LoByte = popByte();
    std::uint16_t HiByte = popByte();

    return (HiByte << 8) | LoByte;
}

cpu::cpu()
    : instr{*this} {
   
}

cpu::~cpu() {

}

void cpu::printCPUState(const std::string_view& opName) {
    fmt::println("{} PC:{:0x} SP:{:0x} AReg:{:0x} XReg:{:0x} YReg:{:0x} ", opName, pc, sp, AReg, XReg, YReg);
}

void cpu::tick() {
    auto opcode = this->readByte(pc);
    execute(opcode);
}

void cpu::execute(std::uint8_t opcode) {
    switch (opcode) {
        case 0x69:
            printCPUState("ADC");
            instr.opAdc(Instructions::Immediate);
            pc += 2;
            printCPUState("ADC");
            break;
        case 0x65:
            printCPUState("ADC");
            instr.opAdc(Instructions::ZeroPage);
            pc += 2;
            printCPUState("ADC");
            break;
        case 0x75:
            printCPUState("ADC");
            instr.opAdc(Instructions::ZeroPageX);
            pc += 2;
            printCPUState("ADC");
        default:
            break;
    }
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

