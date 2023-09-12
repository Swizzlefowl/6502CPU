#include "CPU.h"

// reads an uint8 byte from cpu memory
std::uint8_t cpu::readByte(std::uint16_t adress) {
    return memory[adress % 0x800];
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
    this->memory[adress % 0x800] = val;
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
    pc = 0xC000;
    sp = 0xFD;
    Statusreg.flags = 0x32;
}

cpu::~cpu() {

}

void cpu::printCPUState(const std::string_view& opName, std::uint8_t opcode) {
    fmt::println("{}:{:0x} PC:{:0x} SP:{:0x} AReg:{:0x} XReg:{:0x} YReg:{:0x} ", opName, opcode, pc, sp, AReg, XReg, YReg);
}

void cpu::tick() {
    auto opcode = this->readByte((pc - 0x8000) % 0x4000);
    execute(opcode);
}

void cpu::execute(std::uint8_t opcode) {
    switch (opcode) {
        case 0x69:
            printCPUState("ADC", opcode);
            instr.opADC(Instructions::Immediate);
            pc += 2; // instruction length
            printCPUState("ADC", opcode);
            break;
        case 0x65:
            printCPUState("ADC", opcode);
            instr.opADC(Instructions::ZeroPage);
            pc += 2; // instruction length
            printCPUState("ADC", opcode);
            break;
        case 0x75:
            printCPUState("ADC", opcode);
            instr.opADC(Instructions::ZeroPageX);
            pc += 2; // instruction length
            printCPUState("ADC", opcode);
            break;
        case 0x6D:
            printCPUState("ADC", opcode);
            instr.opADC(Instructions::Absolute);
            pc += 3; // instruction length
            printCPUState("ADC", opcode);
            break;
        case 0x7D:
            printCPUState("ADC", opcode);
            instr.opADC(Instructions::AbsoluteX);
            pc += 3; // instruction length
            printCPUState("ADC", opcode);
            break;
        case 0x79:
            printCPUState("ADC", opcode);
            instr.opADC(Instructions::AbsoluteY);
            pc += 3; // instruction length
            printCPUState("ADC", opcode);
            break;
        case 0x61:
            printCPUState("ADC", opcode);
            instr.opADC(Instructions::IndirectX);
            pc += 2; // instruction length
            printCPUState("ADC", opcode);
            break;
        case 0x71:
            printCPUState("ADC", opcode);
            instr.opADC(Instructions::IndirectY);
            pc += 2; // instruction length
            printCPUState("ADC", opcode);
            break;
        case 0x29:
            printCPUState("AND", opcode);
            instr.opAND(Instructions::Immediate);
            pc += 2; // instruction length
            printCPUState("AND", opcode);
            break;
        case 0x25:
            printCPUState("AND", opcode);
            instr.opAND(Instructions::ZeroPage);
            pc += 2; // instruction length
            printCPUState("AND", opcode);
            break;
        case 0x35:
            printCPUState("AND", opcode);
            instr.opAND(Instructions::ZeroPageX);
            pc += 2; // instruction length
            printCPUState("AND", opcode);
            break;
        case 0x2D:
            printCPUState("AND", opcode);
            instr.opAND(Instructions::Absolute);
            pc += 3; // instruction length
            printCPUState("AND", opcode);
            break;
        case 0x3D:
            printCPUState("AND", opcode);
            instr.opAND(Instructions::AbsoluteX);
            pc += 3; // instruction length
            printCPUState("AND", opcode);
            break;
        case 0x39:
            printCPUState("AND", opcode);
            instr.opAND(Instructions::AbsoluteY);
            printCPUState("AND", opcode);
            pc += 3; // instruction length
            break;
        case 0x21:
            printCPUState("AND", opcode);
            instr.opAND(Instructions::IndirectX);
            printCPUState("AND", opcode);
            pc += 2; // instruction length
            break;
        case 0x31:
            printCPUState("AND", opcode);
            instr.opAND(Instructions::IndirectY);
            printCPUState("AND", opcode);
            pc += 2; // instruction length
            break;
        case 0x0A:
            printCPUState("ASL", opcode);
            instr.opASL(Instructions::Accumulator);
            printCPUState("ASL", opcode);
            pc += 1; // instruction length
            break;
        case 0x06:
            printCPUState("ASL", opcode);
            instr.opASL(Instructions::ZeroPage);
            printCPUState("ASL", opcode);
            pc += 2; // instruction length
            break;
        case 0x16:
            printCPUState("ASL", opcode);
            instr.opASL(Instructions::ZeroPageX);
            printCPUState("ASL", opcode);
            pc += 2; // instruction length
            break;
        case 0x0E:
            printCPUState("ASL", opcode);
            instr.opASL(Instructions::Absolute);
            printCPUState("ASL", opcode);
            pc += 3; // instruction length
            break;
        case 0x1E:
            printCPUState("ASL", opcode);
            instr.opASL(Instructions::AbsoluteX);
            printCPUState("ASL", opcode);
            pc += 3; // instruction length
            break;
        case 0x90:
            printCPUState("BCC", opcode);
            instr.opBCC(Instructions::Relative);
            printCPUState("BCC", opcode);
            if (Statusreg.isSet(StatusRegister::Carry))
                pc += 2;
            break;
        case 0xB0:
            printCPUState("BCS", opcode);
            instr.opBCS(Instructions::Relative);
            printCPUState("BCS", opcode);
            if (!Statusreg.isSet(StatusRegister::Carry))
                pc += 2;
            break;
        case 0xF0:
            printCPUState("BEQ", opcode);
            instr.opBEQ(Instructions::Relative);
            printCPUState("BEQ", opcode);
            if (!Statusreg.isSet(StatusRegister::Zero))
                pc += 2;
            break;
        case 0x30:
            printCPUState("BMI", opcode);
            instr.opBMI(Instructions::Relative);
            printCPUState("BMI", opcode);
            if (!Statusreg.isSet(StatusRegister::Negative))
                pc += 2;
            break;
        case 0xD0:
            printCPUState("BNE", opcode);
            instr.opBNE(Instructions::Relative);
            printCPUState("BNE", opcode);
            if (Statusreg.isSet(StatusRegister::Zero))
                pc += 2;
            break;
        case 0x10:
            printCPUState("BPL", opcode);
            instr.opBPL(Instructions::Relative);
            printCPUState("BPL", opcode);
            if (Statusreg.isSet(StatusRegister::Negative))
                pc += 2;
            break;
        case 0x50:
            printCPUState("BVC", opcode);
            instr.opBVC(Instructions::Relative);
            printCPUState("BVC", opcode);
            if (Statusreg.isSet(StatusRegister::Overflow))
                pc += 2;
            break;
        case 0x70:
            printCPUState("BVS", opcode);
            instr.opBVS(Instructions::Relative);
            printCPUState("BVS", opcode);
            if (!Statusreg.isSet(StatusRegister::Overflow))
                pc += 2;
            break;
        case 0x24:
            printCPUState("BIT", opcode);
            instr.opBIT(Instructions::ZeroPage);
            printCPUState("BIT", opcode);
            pc += 2;
            break;
        case 0x2C:
            printCPUState("BIT", opcode);
            instr.opBIT(Instructions::Absolute);
            printCPUState("BIT", opcode);
            pc += 3;
            break;
        case 0x00:
            printCPUState("BRK", opcode);
            instr.opBRK(Instructions::Implied);
            printCPUState("BRK", opcode);
            pc += 1;
            break;
        case 0x18:
            printCPUState("CLC", opcode);
            instr.opCLC(Instructions::Implied);
            printCPUState("CLC", opcode);
            pc += 1;
            break;
        case 0xD8:
            printCPUState("CLD", opcode);
            instr.opCLD(Instructions::Implied);
            printCPUState("CLD", opcode);
            pc += 1;
            break;
        case 0x58:
            printCPUState("CLI", opcode);
            instr.opCLI(Instructions::Implied);
            printCPUState("CLI", opcode);
            pc += 1;
            break;
        case 0xB8:
            printCPUState("CLV", opcode);
            instr.opCLV(Instructions::Implied);
            printCPUState("CLV", opcode);
            pc += 1;
            break;
        case 0xC9:
            printCPUState("CMP", opcode);
            instr.opCMP(Instructions::Immediate);
            printCPUState("CMP", opcode);
            pc += 2;
            break;
        case 0xC5:
            printCPUState("CMP", opcode);
            instr.opCMP(Instructions::ZeroPage);
            printCPUState("CMP", opcode);
            pc += 2;
            break;
        case 0xD5:
            printCPUState("CMP", opcode);
            instr.opCMP(Instructions::ZeroPageX);
            printCPUState("CMP", opcode);
            pc += 2;
            break;
        case 0xCD:
            printCPUState("CMP", opcode);
            instr.opCMP(Instructions::Absolute);
            printCPUState("CMP", opcode);
            pc += 3;
            break;
        case 0xDD:
            printCPUState("CMP", opcode);
            instr.opCMP(Instructions::AbsoluteX);
            printCPUState("CMP", opcode);
            pc += 3;
            break;
        case 0xD9:
            printCPUState("CMP", opcode);
            instr.opCMP(Instructions::AbsoluteY);
            printCPUState("CMP", opcode);
            pc += 3;
            break;
        case 0xC1:
            printCPUState("CMP", opcode);
            instr.opCMP(Instructions::IndirectX);
            printCPUState("CMP", opcode);
            pc += 2;
            break;
        case 0xD1:
            printCPUState("CMP", opcode);
            instr.opCMP(Instructions::IndirectY);
            printCPUState("CMP", opcode);
            pc += 2;
            break;
        case 0xE0:
            printCPUState("CPX", opcode);
            instr.opCPX(Instructions::Immediate);
            printCPUState("CPX", opcode);
            pc += 2;
            break;
        case 0xE4:
            printCPUState("CPX", opcode);
            instr.opCPX(Instructions::ZeroPage);
            printCPUState("CPX", opcode);
            pc += 2;
            break;
        case 0xEC:
            printCPUState("CPX", opcode);
            instr.opCPX(Instructions::Absolute);
            printCPUState("CPX", opcode);
            pc += 3;
            break;
        case 0xC0:
            printCPUState("CPY", opcode);
            instr.opCPY(Instructions::Immediate);
            printCPUState("CPY", opcode);
            pc += 2;
            break;
        case 0xC4:
            printCPUState("CPY", opcode);
            instr.opCPY(Instructions::ZeroPage);
            printCPUState("CPY", opcode);
            pc += 2;
            break;
        case 0xCC:
            printCPUState("CPY", opcode);
            instr.opCPY(Instructions::Absolute);
            printCPUState("CPY", opcode);
            pc += 3;
            break;
        case 0xC6:
            printCPUState("DEC", opcode);
            instr.opDEC(Instructions::ZeroPage);
            printCPUState("DEC", opcode);
            pc += 2;
            break;
        case 0xD6:
            printCPUState("DEC", opcode);
            instr.opDEC(Instructions::ZeroPageX);
            printCPUState("DEC", opcode);
            pc += 2;
            break;
        case 0xCE:
            printCPUState("DEC", opcode);
            instr.opDEC(Instructions::Absolute);
            printCPUState("DEC", opcode);
            pc += 3;
            break;
        case 0xDE:
            printCPUState("DEC", opcode);
            instr.opDEC(Instructions::AbsoluteX);
            printCPUState("DEC", opcode);
            pc += 3;
            break;
        case 0xCA:
            printCPUState("DEX", opcode);
            instr.opDEX(Instructions::Implied);
            printCPUState("DEX", opcode);
            pc += 1;
            break;
        case 0x88:
            printCPUState("DEY", opcode);
            instr.opDEY(Instructions::Implied);
            printCPUState("DEY", opcode);
            pc += 1;
            break;
        case 0x49:
            printCPUState("EOR", opcode);
            instr.opEOR(Instructions::Immediate);
            printCPUState("EOR", opcode);
            pc += 2;
            break;
        case 0x45:
            printCPUState("EOR", opcode);
            instr.opEOR(Instructions::ZeroPage);
            printCPUState("EOR", opcode);
            pc += 2;
            break;
        case 0x55:
            printCPUState("EOR", opcode);
            instr.opEOR(Instructions::ZeroPageX);
            printCPUState("EOR", opcode);
            pc += 2;
            break;
        case 0x4D:
            printCPUState("EOR", opcode);
            instr.opEOR(Instructions::Absolute);
            printCPUState("EOR", opcode);
            pc += 3;
            break;
        case 0x5D:
            printCPUState("EOR", opcode);
            instr.opEOR(Instructions::AbsoluteX);
            printCPUState("EOR", opcode);
            pc += 3;
            break;
        case 0x59:
            printCPUState("EOR", opcode);
            instr.opEOR(Instructions::AbsoluteY);
            printCPUState("EOR", opcode);
            pc += 3;
            break;
        case 0x41:
            printCPUState("EOR", opcode);
            instr.opEOR(Instructions::IndirectX);
            printCPUState("EOR", opcode);
            pc += 2;
            break;
        case 0x51:
            printCPUState("EOR", opcode);
            instr.opEOR(Instructions::IndirectY);
            printCPUState("EOR", opcode);
            pc += 2;
            break;
        case 0xE6:
            printCPUState("INC", opcode);
            instr.opINC(Instructions::ZeroPage);
            printCPUState("INC", opcode);
            pc += 2;
            break;
        case 0xF6:
            printCPUState("INC", opcode);
            instr.opINC(Instructions::ZeroPageX);
            printCPUState("INC", opcode);
            pc += 2;
            break;
        case 0xEE:
            printCPUState("INC", opcode);
            instr.opINC(Instructions::Absolute);
            printCPUState("INC", opcode);
            pc += 3;
            break;
        case 0xFE:
            printCPUState("INC", opcode);
            instr.opINC(Instructions::AbsoluteX);
            printCPUState("INC", opcode);
            pc += 3;
            break;
        case 0xE8:
            printCPUState("INX", opcode);
            instr.opINX(Instructions::Implied);
            printCPUState("INX", opcode);
            pc += 1;
            break;
        case 0xC8:
            printCPUState("INY", opcode);
            instr.opINY(Instructions::Implied);
            printCPUState("INY", opcode);
            pc += 1;
            break;
        case 0x4C:
            printCPUState("JMP", opcode);
            instr.opJMP(Instructions::Absolute);
            printCPUState("JMP", opcode);
            break;
        case 0x6C:
            printCPUState("JMP", opcode);
            instr.opJMP(Instructions::Indirect);
            printCPUState("JMP", opcode);
            break;
        case 0x20:
            printCPUState("JSR", opcode);
            instr.opJSR(Instructions::Absolute);
            printCPUState("JSR", opcode);
            break;
        case 0xA9:
            printCPUState("LDA", opcode);
            instr.opLDA(Instructions::Immediate);
            printCPUState("LDA", opcode);
            pc += 2;
            break;
        case 0xA5:
            printCPUState("LDA", opcode);
            instr.opLDA(Instructions::ZeroPage);
            printCPUState("LDA", opcode);
            pc += 2;
            break;
        case 0xB5:
            printCPUState("LDA", opcode);
            instr.opLDA(Instructions::ZeroPageX);
            printCPUState("LDA", opcode);
            pc += 2;
            break;
        case 0xAD:
            printCPUState("LDA", opcode);
            instr.opLDA(Instructions::Absolute);
            printCPUState("LDA", opcode);
            pc += 3;
            break;
        case 0xBD:
            printCPUState("LDA", opcode);
            instr.opLDA(Instructions::AbsoluteX);
            printCPUState("LDA", opcode);
            pc += 3;
            break;
        case 0xB9:
            printCPUState("LDA", opcode);
            instr.opLDA(Instructions::AbsoluteY);
            printCPUState("LDA", opcode);
            pc += 3;
            break;
        case 0xA1:
            printCPUState("LDA", opcode);
            instr.opLDA(Instructions::IndirectX);
            printCPUState("LDA", opcode);
            pc += 2;
            break;
        case 0xB1:
            printCPUState("LDA", opcode);
            instr.opLDA(Instructions::IndirectY);
            printCPUState("LDA", opcode);
            pc += 2;
            break;
        case 0xA2:
            printCPUState("LDX", opcode);
            instr.opLDX(Instructions::Immediate);
            printCPUState("LDX", opcode);
            pc += 2;
            break;
        case 0xA6:
            printCPUState("LDX", opcode);
            instr.opLDX(Instructions::ZeroPage);
            printCPUState("LDX", opcode);
            pc += 2;
            break;
        case 0xB6:
            printCPUState("LDX", opcode);
            instr.opLDX(Instructions::ZeroPageY);
            printCPUState("LDX", opcode);
            pc += 2;
            break;
        case 0xAE:
            printCPUState("LDX", opcode);
            instr.opLDX(Instructions::Absolute);
            printCPUState("LDX", opcode);
            pc += 3;
            break;
        case 0xBE:
            printCPUState("LDX", opcode);
            instr.opLDX(Instructions::AbsoluteY);
            printCPUState("LDX", opcode);
            pc += 3;
            break;
        case 0xA0:
            printCPUState("LDY", opcode);
            instr.opLDY(Instructions::Immediate);
            printCPUState("LDY", opcode);
            pc += 2;
            break;
        case 0xA4:
            printCPUState("LDY", opcode);
            instr.opLDY(Instructions::ZeroPage);
            printCPUState("LDY", opcode);
            pc += 2;
            break;
        case 0xB4:
            printCPUState("LDY", opcode);
            instr.opLDY(Instructions::ZeroPageX);
            printCPUState("LDY", opcode);
            pc += 2;
            break;
        case 0xAC:
            printCPUState("LDY", opcode);
            instr.opLDY(Instructions::Absolute);
            printCPUState("LDY", opcode);
            pc += 3;
            break;
        case 0xBC:
            printCPUState("LDY", opcode);
            instr.opLDY(Instructions::AbsoluteX);
            printCPUState("LDY", opcode);
            pc += 3;
            break;
        case 0x4A:
            printCPUState("LSR", opcode);
            instr.opLSR(Instructions::Accumulator);
            printCPUState("LSR", opcode);
            pc += 1;
            break;
        case 0x46:
            printCPUState("LSR", opcode);
            instr.opLSR(Instructions::ZeroPage);
            printCPUState("LSR", opcode);
            pc += 2;
            break;
        case 0x56:
            printCPUState("LSR", opcode);
            instr.opLSR(Instructions::ZeroPageX);
            printCPUState("LSR", opcode);
            pc += 2;
            break;
        case 0x4E:
            printCPUState("LSR", opcode);
            instr.opLSR(Instructions::Absolute);
            printCPUState("LSR", opcode);
            pc += 3;
            break;
        case 0x5E:
            printCPUState("LSR", opcode);
            instr.opLSR(Instructions::AbsoluteX);
            printCPUState("LSR", opcode);
            pc += 3;
            break;
        case 0xEA:
            printCPUState("NOP", opcode);
            instr.opNOP(Instructions::Implied);
            printCPUState("NOP", opcode);
            pc += 1;
            break;
        case 0x09:
            printCPUState("ORA", opcode);
            instr.opORA(Instructions::Immediate);
            printCPUState("ORA", opcode);
            pc += 2;
            break;
        case 0x05:
            printCPUState("ORA", opcode);
            instr.opORA(Instructions::ZeroPage);
            printCPUState("ORA", opcode);
            pc += 2;
            break;
        case 0x15:
            printCPUState("ORA", opcode);
            instr.opORA(Instructions::ZeroPageX);
            printCPUState("ORA", opcode);
            pc += 2;
            break;
        case 0x0D:
            printCPUState("ORA", opcode);
            instr.opORA(Instructions::Absolute);
            printCPUState("ORA", opcode);
            pc += 3;
            break;
        case 0x1D:
            printCPUState("ORA", opcode);
            instr.opORA(Instructions::AbsoluteX);
            printCPUState("ORA", opcode);
            pc += 3;
            break;
        case 0x19:
            printCPUState("ORA", opcode);
            instr.opORA(Instructions::AbsoluteY);
            printCPUState("ORA", opcode);
            pc += 3;
            break;
        case 0x01:
            printCPUState("ORA", opcode);
            instr.opORA(Instructions::IndirectX);
            printCPUState("ORA", opcode);
            pc += 2;
            break;
        case 0x11:
            printCPUState("ORA", opcode);
            instr.opORA(Instructions::IndirectY);
            printCPUState("ORA", opcode);
            pc += 2;
            break;
        case 0x48:
            printCPUState("PHA", opcode);
            instr.opPHA(Instructions::Implied);
            printCPUState("PHA", opcode);
            pc += 1;
            break;
        case 0x08:
            printCPUState("PHP", opcode);
            instr.opPHP(Instructions::Implied);
            printCPUState("PHP", opcode);
            pc += 1;
            break;
        case 0x68:
            printCPUState("PLA", opcode);
            instr.opPLA(Instructions::Implied);
            printCPUState("PLA", opcode);
            pc += 1;
            break;
        case 0x28:
            printCPUState("PLP", opcode);
            instr.opPLP(Instructions::Implied);
            printCPUState("PLP", opcode);
            pc += 1;
            break;
        case 0x2A:
            printCPUState("ROL", opcode);
            instr.opROL(Instructions::Accumulator);
            printCPUState("ROL", opcode);
            pc += 1;
            break;
        case 0x26:
            printCPUState("ROL", opcode);
            instr.opROL(Instructions::ZeroPage);
            printCPUState("ROL", opcode);
            pc += 2;
            break;
        case 0x36:
            printCPUState("ROL", opcode);
            instr.opROL(Instructions::ZeroPageX);
            printCPUState("ROL", opcode);
            pc += 2;
            break;
        case 0x2E:
            printCPUState("ROL", opcode);
            instr.opROL(Instructions::Absolute);
            printCPUState("ROL", opcode);
            pc += 3;
            break;
        case 0x3E:
            printCPUState("ROL", opcode);
            instr.opROL(Instructions::AbsoluteX);
            printCPUState("ROL", opcode);
            pc += 3;
            break;
        case 0x6A:
            printCPUState("ROR", opcode);
            instr.opROR(Instructions::Accumulator);
            printCPUState("ROR", opcode);
            pc += 1;
            break;
        case 0x66:
            printCPUState("ROR", opcode);
            instr.opROR(Instructions::ZeroPage);
            printCPUState("ROR", opcode);
            pc += 2;
            break;
        case 0x76:
            printCPUState("ROR", opcode);
            instr.opROR(Instructions::ZeroPageX);
            printCPUState("ROR", opcode);
            pc += 2;
            break;
        case 0x6E:
            printCPUState("ROR", opcode);
            instr.opROR(Instructions::Absolute);
            printCPUState("ROR", opcode);
            pc += 3;
            break;
        case 0x7E:
            printCPUState("ROR", opcode);
            instr.opROR(Instructions::AbsoluteX);
            printCPUState("ROR", opcode);
            pc += 3;
            break;
        case 0x40:
            printCPUState("RTI", opcode);
            instr.opRTI(Instructions::Implied);
            printCPUState("RTI", opcode);
            pc += 1;
            break;
        case 0x60:
            printCPUState("RTS", opcode);
            instr.opRTS(Instructions::Implied);
            printCPUState("RTS", opcode);
            pc += 1;
            break;
        case 0xE9:
            printCPUState("SBC", opcode);
            instr.opSBC(Instructions::Immediate);
            printCPUState("SBC", opcode);
            pc += 2;
            break;
        case 0xE5:
            printCPUState("SBC", opcode);
            instr.opSBC(Instructions::ZeroPage);
            printCPUState("SBC", opcode);
            pc += 2;
            break;
        case 0xF5:
            printCPUState("SBC", opcode);
            instr.opSBC(Instructions::ZeroPageX);
            printCPUState("SBC", opcode);
            pc += 2;
            break;
        case 0xED:
            printCPUState("SBC", opcode);
            instr.opSBC(Instructions::Absolute);
            printCPUState("SBC", opcode);
            pc += 3;
            break;
        case 0xFD:
            printCPUState("SBC", opcode);
            instr.opSBC(Instructions::AbsoluteX);
            printCPUState("SBC", opcode);
            pc += 3;
            break;
        case 0xF9:
            printCPUState("SBC", opcode);
            instr.opSBC(Instructions::AbsoluteY);
            printCPUState("SBC", opcode);
            pc += 3;
            break;
        case 0xE1:
            printCPUState("SBC", opcode);
            instr.opSBC(Instructions::IndirectX);
            printCPUState("SBC", opcode);
            pc += 2;
            break;
        case 0xF1:
            printCPUState("SBC", opcode);
            instr.opSBC(Instructions::IndirectY);
            printCPUState("SBC", opcode);
            pc += 2;
            break;
        case 0x38:
            printCPUState("SEC", opcode);
            instr.opSEC(Instructions::Implied);
            printCPUState("SEC", opcode);
            pc += 1;
            break;
        case 0xF8:
            printCPUState("SED", opcode);
            instr.opSED(Instructions::Implied);
            printCPUState("SED", opcode);
            pc += 1;
            break;
        case 0x78:
            printCPUState("SEI", opcode);
            instr.opSEI(Instructions::Implied);
            printCPUState("SEI", opcode);
            pc += 1;
            break;
        case 0x85:
            printCPUState("STA", opcode);
            instr.opSTA(Instructions::ZeroPage);
            printCPUState("STA", opcode);
            pc += 2;
            break;
        case 0x95:
            printCPUState("STA", opcode);
            instr.opSTA(Instructions::ZeroPageX);
            printCPUState("STA", opcode);
            pc += 2;
            break;
        case 0x8D:
            printCPUState("STA", opcode);
            instr.opSTA(Instructions::Absolute);
            printCPUState("STA", opcode);
            pc += 3;
            break;
        case 0x9D:
            printCPUState("STA", opcode);
            instr.opSTA(Instructions::AbsoluteX);
            printCPUState("STA", opcode);
            pc += 3;
            break;
        case 0x99:
            printCPUState("STA", opcode);
            instr.opSTA(Instructions::AbsoluteY);
            printCPUState("STA", opcode);
            pc += 3;
            break;
        case 0x81:
            printCPUState("STA", opcode);
            instr.opSTA(Instructions::IndirectX);
            printCPUState("STA", opcode);
            pc += 2;
            break;
        case 0x91:
            printCPUState("STA", opcode);
            instr.opSTA(Instructions::IndirectY);
            printCPUState("STA", opcode);
            pc += 2;
            break;
        case 0x86:
            printCPUState("STX", opcode);
            instr.opSTX(Instructions::ZeroPage);
            printCPUState("STX", opcode);
            pc += 2;
            break;
        case 0x96:
            printCPUState("STX", opcode);
            instr.opSTX(Instructions::ZeroPageY);
            printCPUState("STX", opcode);
            pc += 2;
            break;
        case 0x8E:
            printCPUState("STX", opcode);
            instr.opSTX(Instructions::Absolute);
            printCPUState("STX", opcode);
            pc += 3;
            break;
        case 0x84:
            printCPUState("STY", opcode);
            instr.opSTY(Instructions::ZeroPage);
            printCPUState("STY", opcode);
            pc += 2;
            break;
        case 0x94:
            printCPUState("STY", opcode);
            instr.opSTY(Instructions::ZeroPageX);
            printCPUState("STY", opcode);
            pc += 2;
            break;
        case 0x8C:
            printCPUState("STY", opcode);
            instr.opSTY(Instructions::Absolute);
            printCPUState("STY", opcode);
            pc += 3;
            break;
        case 0xAA:
            printCPUState("TAX", opcode);
            instr.opTAX(Instructions::Implied);
            printCPUState("TAX", opcode);
            pc += 1;
            break;
        case 0xA8:
            printCPUState("TAY", opcode);
            instr.opTAY(Instructions::Implied);
            printCPUState("TAY", opcode);
            pc += 1;
            break;
        case 0xBA:
            printCPUState("TSX", opcode);
            instr.opTSX(Instructions::Implied);
            printCPUState("TSX", opcode);
            pc += 1;
            break;
        case 0x8A:
            printCPUState("TXA", opcode);
            instr.opTXA(Instructions::Implied);
            printCPUState("TXA", opcode);
            pc += 1;
            break;
        case 0x9A:
            printCPUState("TXS", opcode);
            instr.opTXS(Instructions::Implied);
            printCPUState("TXS", opcode);
            pc += 1;
            break;
        case 0x98:
            printCPUState("TYA", opcode);
            instr.opTYA(Instructions::Implied);
            printCPUState("TYA", opcode);
            pc += 1;
            break;
        default:
            fmt::println("Unimplemented opcode!:{:0x}", opcode);
            throw std::exception("more barbie then(than) ken it would seem");
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

