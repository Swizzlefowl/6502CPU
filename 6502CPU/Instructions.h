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
    std::uint8_t fetchArgument(AddrMode adress);

    //ADC - Add with Carry
    void opADC(AddrMode addr);

    // AND - Logical AND
    void opAND(AddrMode addr);

    // ASL - Arithmetic Shift Left
    void opASL(AddrMode addr);
};


