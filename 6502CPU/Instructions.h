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
};


