#pragma once
#include <cstdint>
struct cpu;
struct Instructions {

    enum AddrMode {
        Implied,
        Accumulator,
        Immediate,
        Relative,
        IndirectX,
        IndirectY,
        Absolute,
        ZeroPage,
        ZeroPageX,
        ZeroPageY,
        Indirect,
        AbsoluteX,
        AbsoluteY,
    };

    Instructions(cpu& cpu);
    ~Instructions();
    cpu& m_cpu;

    std::uint16_t fetchArgumentadress(AddrMode addrMode);
    std::uint8_t fetchArgument(AddrMode mode);

    // ADC - Add with Carry
    void opADC(AddrMode mode);

    // AND - Logical AND
    void opAND(AddrMode mode);

    // ASL - Arithmetic Shift Left
    void opASL(AddrMode mode);

    // BCC - Branch if Carry Clear
    void opBCC(AddrMode mode);

    //BCS - Branch if Carry Set
    void opBCS(AddrMode mode);

    // BEQ - Branch if Equal
    void opBEQ(AddrMode mode);

    // BMI - Branch if Minus
    void opBMI(AddrMode mode);

     // BNE - Branch if Not Equal
    void opBNE(AddrMode mode);

    // BPL - Branch if Positive
    void opBPL(AddrMode mode);

    // BVC - Branch if Overflow Clear
    void opBVC(AddrMode mode);

    // BVS - Branch if Overflow Set
    void opBVS(AddrMode mode);

    // BIT - Bit Test
    void opBIT(AddrMode mode);

    // BRK - Force Interrupt
    void opBRK(AddrMode mode);

    // CLC - Clear Carry Flag
    void opCLC(AddrMode mode);

    // CLD - Clear Decimal Mode
    void opCLD(AddrMode mode);

    // CLI - Clear Interrupt Disable
    void opCLI(AddrMode mode);

    // CLV - Clear Overflow Flag
    void opCLV(AddrMode mode);

    // CMP - Compare
    void opCMP(AddrMode mode);

    // CPX - Compare X Register
    void opCPX(AddrMode mode);

    // CPY - Compare Y Register
    void opCPY(AddrMode mode);

    // DEC - Decrement Memory
    void opDEC(AddrMode mode);

    // DEX - Decrement X Register
    void opDEX(AddrMode mode);

    // DEY - Decrement Y Register
    void opDEY(AddrMode mode);

    // EOR - Exclusive OR
    void opEOR(AddrMode mode);

    // INC - Increment Memory
    void opINC(AddrMode mode);

    // INX - Increment X Register
    void opINX(AddrMode mode);

    // INY - Increment Y Register
    void opINY(AddrMode mode);
};


