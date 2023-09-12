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

    //JMP - Jump
    void opJMP(AddrMode mode);

    // JSR - Jump to Subroutine
    void opJSR(AddrMode mode);

    // LDA - Load Accumulator
    void opLDA(AddrMode mode);

    // LDX - Load X Register
    void opLDX(AddrMode mode);

    // LDY - Load Y Register
    void opLDY(AddrMode mode);

    // LSR - Logical Shift Right
    void opLSR(AddrMode mode);

    // NOP - No Operation
    void opNOP(AddrMode mode);

    // ORA - Logical Inclusive OR
    void opORA(AddrMode mode);

    // PHA - Push Accumulator
    void opPHA(AddrMode mode);

    // PHP - Push Processor Status
    void opPHP(AddrMode mode);

    // PLA - Pull Accumulator
    void opPLA(AddrMode mode);

    // PLP - Pull Processor Status
    void opPLP(AddrMode mode);

    // ROL - Rotate Left
    void opROL(AddrMode mode);

    // ROR - Rotate Right
    void opROR(AddrMode mode);

    // RTI - Return from Interrupt
    void opRTI(AddrMode mode);

    //RTS - Return from Subroutine
    void opRTS(AddrMode mode);

    // SBC - Subtract with Carry
    void opSBC(AddrMode mode);

    // SEC - Set Carry Flag
    void opSEC(AddrMode mode);

    // SED - Set Decimal Flag
    void opSED(AddrMode mode);

    // SEI - Set Interrupt Disable
    void opSEI(AddrMode mode);

    // STA - Store Accumulator
    void opSTA(AddrMode mode);

    // STX - Store X Register
    void opSTX(AddrMode mode);

    // STY - Store Y Register
    void opSTY(AddrMode mode);

    // TAX - Transfer Accumulator to X
    void opTAX(AddrMode mode);

    // TAY - Transfer Accumulator to Y
    void opTAY(AddrMode mode);

    // TSX - Transfer Stack Pointer to X
    void opTSX(AddrMode mode);

    // TXA - Transfer X to Accumulator
    void opTXA(AddrMode mode);

    // TXS - Transfer X to Stack Pointer
    void opTXS(AddrMode mode);

    // TYA - Transfer Y to Accumulator
    void opTYA(AddrMode mode);
};


