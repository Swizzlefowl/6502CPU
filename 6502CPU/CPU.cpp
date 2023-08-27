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

void cpu::printCPUState(const std::string_view& opName, std::uint8_t opcode) {
    fmt::println("{}:{:0x} PC:{:0x} SP:{:0x} AReg:{:0x} XReg:{:0x} YReg:{:0x} ", opName, opcode, pc, sp, AReg, XReg, YReg);
}

void cpu::tick() {
    auto opcode = this->readByte(pc);
    execute(opcode);
}

void cpu::execute(std::uint8_t opcode) {
    switch (opcode) {
        case 0x69:
            printCPUState("ADC", 0x69);
            instr.opADC(Instructions::Immediate);
            pc += 2; // instruction length
            printCPUState("ADC", 0x69);
            break;
        case 0x65:
            printCPUState("ADC", 0x65);
            instr.opADC(Instructions::ZeroPage);
            pc += 2; // instruction length
            printCPUState("ADC", 0x65);
            break;
        case 0x75:
            printCPUState("ADC", 0x75);
            instr.opADC(Instructions::ZeroPageX);
            pc += 2; // instruction length
            printCPUState("ADC", 0x75);
            break;
        case 0x6D:
            printCPUState("ADC", 0x6D);
            instr.opADC(Instructions::Absolute);
            pc += 3; // instruction length
            printCPUState("ADC", 0x6D);
            break;
        case 0x7D:
            printCPUState("ADC", 0x7D);
            instr.opADC(Instructions::AbsoluteX);
            pc += 3; // instruction length
            printCPUState("ADC", 0x7D);
            break;
        case 0x79:
            printCPUState("ADC", 0x79);
            instr.opADC(Instructions::AbsoluteY);
            pc += 3; // instruction length
            printCPUState("ADC", 0x79);
            break;
        case 0x61:
            printCPUState("ADC", 0x61);
            instr.opADC(Instructions::IndirectX);
            pc += 2; // instruction length
            printCPUState("ADC", 0x61);
            break;
        case 0x71:
            printCPUState("ADC", 0x71);
            instr.opADC(Instructions::IndirectY);
            pc += 2; // instruction length
            printCPUState("ADC", 0x71);
            break;
        case 0x29:
            printCPUState("AND", 0x29);
            instr.opAND(Instructions::Immediate);
            pc += 2; // instruction length
            printCPUState("AND", 0x29);
            break;
        case 0x25:
            printCPUState("AND", 0x25);
            instr.opAND(Instructions::ZeroPage);
            pc += 2; // instruction length
            printCPUState("AND", 0x25);
            break;
        case 0x35:
            printCPUState("AND", 0x35);
            instr.opAND(Instructions::ZeroPageX);
            pc += 2; // instruction length
            printCPUState("AND", 0x35);
            break;
        case 0x2D:
            printCPUState("AND", 0x2D);
            instr.opAND(Instructions::Absolute);
            pc += 3; // instruction length
            printCPUState("AND", 0x2D);
            break;
        case 0x3D:
            printCPUState("AND", 0x3D);
            instr.opAND(Instructions::AbsoluteX);
            pc += 3; // instruction length
            printCPUState("AND", 0x3D);
            break;
        case 0x39:
            printCPUState("AND", 0x39);
            instr.opAND(Instructions::AbsoluteY);
            printCPUState("AND", 0x39);
            pc += 3; // instruction length
            break;
        case 0x21:
            printCPUState("AND", 0x21);
            instr.opAND(Instructions::IndirectX);
            printCPUState("AND", 0x21);
            pc += 2; // instruction length
            break;
        case 0x31:
            printCPUState("AND", 0x31);
            instr.opAND(Instructions::IndirectY);
            printCPUState("AND", 0x31);
            pc += 2; // instruction length
            break;
        case 0x0A:
            printCPUState("ASL", 0x0A);
            instr.opASL(Instructions::Accumulator);
            printCPUState("ASL", 0x0A);
            pc += 1; // instruction length
            break;
        case 0x06:
            printCPUState("ASL", 0x06);
            instr.opASL(Instructions::ZeroPage);
            printCPUState("ASL", 0x06);
            pc += 2; // instruction length
            break;
        case 0x16:
            printCPUState("ASL", 0x16);
            instr.opASL(Instructions::ZeroPageX);
            printCPUState("ASL", 0x16);
            pc += 2; // instruction length
            break;
        case 0x0E:
            printCPUState("ASL", 0x0E);
            instr.opASL(Instructions::Absolute);
            printCPUState("ASL", 0x0E);
            pc += 3; // instruction length
            break;
        case 0x1E:
            printCPUState("ASL", 0x1E);
            instr.opASL(Instructions::AbsoluteX);
            printCPUState("ASL", 0x1E);
            pc += 3; // instruction length
            break;
        case 0x90:
            printCPUState("BCC", 0x90);
            instr.opBCC(Instructions::Relative);
            printCPUState("BCC", 0x90);
            if (Statusreg.isSet(StatusRegister::Carry))
                pc += 2;
            break;
        case 0xB0:
            printCPUState("BCS", 0xB0);
            instr.opBCS(Instructions::Relative);
            printCPUState("BCS", 0xB0);
            if (!Statusreg.isSet(StatusRegister::Carry))
                pc += 2;
            break;
        case 0xF0:
            printCPUState("BEQ", 0xF0);
            instr.opBEQ(Instructions::Relative);
            printCPUState("BEQ", 0xF0);
            if (!Statusreg.isSet(StatusRegister::Zero))
                pc += 2;
            break;
        case 0x30:
            printCPUState("BMI", 0x30);
            instr.opBMI(Instructions::Relative);
            printCPUState("BMI", 0x30);
            if (!Statusreg.isSet(StatusRegister::Negative))
                pc += 2;
        case 0x24:
            printCPUState("BIT", 0x24);
            instr.opBIT(Instructions::ZeroPage);
            printCPUState("BIT", 0x24);
            pc += 2;
            break;
        case 0x2C:
            printCPUState("BIT", 0x2C);
            instr.opBIT(Instructions::Absolute);
            printCPUState("BIT", 0x2C);
            pc += 3;
            break;
        default:
            throw std::exception("Unimplemented opcode!");
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

