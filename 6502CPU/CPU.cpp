#include "CPU.h"

// reads an uint8 byte from cpu memory
std::uint8_t cpu::readByte(std::uint16_t adress) {
    return memory[adress];
}

// reads an uint16 word from cpu memory
std::uint16_t cpu::readWord(std::uint16_t adress) {
    std::uint16_t LoByte{};
    std::uint16_t HiByte{};

    LoByte = readByte(adress);
    HiByte = (readByte(adress + 1) << 8);

    return HiByte | LoByte;
}

void cpu::writeByte(std::uint16_t adress, std::uint8_t val) {
    this->memory[adress] = val;
}

void cpu::writeWord(std::uint16_t adress, std::uint16_t val) {
    std::uint8_t LoByte = static_cast<uint8_t>(val >> 8);
    std::uint8_t HiByte = static_cast<uint8_t> (val & 0x00ff);

    writeByte(adress, LoByte);
    writeByte(adress + 1, HiByte);
}

void cpu::pushByte(std::uint8_t value) {
    this->memory[sp] = value;
    --sp;

    return;
}

std::uint8_t cpu::popByte() {
    sp++;
    std::uint8_t value = static_cast<std::uint8_t>(this->memory[sp]);

    return value;
}

void cpu::pushWord(std::uint16_t value) {
    std::uint8_t LoByte = static_cast<uint8_t>(value >> 8);
    std::uint8_t HiByte = static_cast<uint8_t>(value & 0x00ff);

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
    pc = 0x10;
    sp = 0xFD;
    Statusreg.flags = 0x32;
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
            pc += 2; // instruction length
            printCPUState("ADC");
            break;
        case 0x65:
            printCPUState("ADC");
            instr.opAdc(Instructions::ZeroPage);
            pc += 2; // instruction length
            printCPUState("ADC");
            break;
        case 0x75:
            printCPUState("ADC");
            instr.opAdc(Instructions::ZeroPageX);
            pc += 2; // instruction length
            printCPUState("ADC");
            break;
        case 0x6D:
            printCPUState("ADC");
            instr.opAdc(Instructions::Absolute);
            pc += 3; // instruction length
            printCPUState("ADC");
            break;
        case 0x7D:
            printCPUState("ADC");
            instr.opAdc(Instructions::AbsoluteX);
            pc += 3; // instruction length
            printCPUState("ADC");
        case 0x79:
            printCPUState("ADC");
            instr.opAdc(Instructions::AbsoluteY);
            pc += 3; // instruction length
            printCPUState("ADC");
            break;
        case 0x61:
            printCPUState("ADC");
            instr.opAdc(Instructions::IndirectX);
            pc += 2; // instruction length
            printCPUState("ADC");
            break;
        case 0x71:
            printCPUState("ADC");
            instr.opAdc(Instructions::IndirectY);
            pc += 2; // instruction length
            printCPUState("ADC");
            break;
        case 0x29:
            printCPUState("AND");
            instr.opAnd(Instructions::Immediate);
            pc += 2; // instruction length
            printCPUState("AND");
            break;
        case 0x25:
            printCPUState("And");
            instr.opAnd(Instructions::ZeroPage);
            pc += 2; // instruction length
            printCPUState("AND");
            break;
        case 0x35:
            printCPUState("And");
            instr.opAnd(Instructions::ZeroPageX);
            pc += 2; // instruction length
            printCPUState("AND");
            break;
        case 0x2D:
            printCPUState("And");
            instr.opAnd(Instructions::Absolute);
            pc += 2; // instruction length
            printCPUState("AND");
            break;
        case 0x3D:
            printCPUState("And");
            instr.opAnd(Instructions::AbsoluteX);
            pc += 2; // instruction length
            printCPUState("AND");
            break;
        case 0x39:
            printCPUState("And");
            instr.opAnd(Instructions::AbsoluteY);
            pc += 2; // instruction length
            printCPUState("AND");
            break;
        default:
            //throw std::exception("Unimplemented opcode!");
            //fmt::println("Unimplemented opcode!:{:0x}", opcode);
            pc++;
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

