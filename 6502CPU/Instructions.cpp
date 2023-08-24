#include "Instructions.h"
#include "CPU.h"

Instructions::Instructions(cpu& cpu)
    : m_cpu{cpu} {


}

Instructions::~Instructions() {
}

std::uint16_t Instructions::fetchArgumentadress(AddrMode addr) {
    auto instrAfterOp = m_cpu.pc + 1;
    switch (addr) {
        case Instructions::Implied:
            return 0;
            break;
        case Instructions::Accumulator:
            return 0;
            break;
        case Instructions::Immediate:
            return instrAfterOp;
            break;
        case Instructions::Relative:{
            auto rel = m_cpu.readByte(instrAfterOp);
            if (rel & 0x80)
                 return rel |= 0xff00;
        }
            break;
        case Instructions::IndirectX:{
            auto ptr = m_cpu.readWord(instrAfterOp) + m_cpu.xReg;
            return ptr;
            }
            break;
        case Instructions::IndirectY:{
            auto ptr = m_cpu.readWord(instrAfterOp) + m_cpu.yReg;
            return ptr;
        }
            break;
        case Instructions::Absolute:
            return m_cpu.readWord(instrAfterOp);
            break;
        case Instructions::ZeroPage:
            return instrAfterOp;
            break;
        case Instructions::ZeroPageX:
            return (instrAfterOp + m_cpu.xReg);
            break;
        case Instructions::ZeroPageY:
            return (instrAfterOp + m_cpu.yReg);
            break;
        case Instructions::Indirect:{ 
            std::uint16_t ptr = m_cpu.readWord(instrAfterOp);
            std::uint16_t LoByte = m_cpu.readByte(ptr);
            // Accomodate for a hardware bug, the 6502 reference states the following:
            // "An original 6502 has does not correctly fetch the target address if the indirect vector
            // falls on a page boundary (e.g. $xxFF where xx is any value from $00 to $FF). In this case
            // it fetches the LSB from $xxFF as expected but takes the MSB from $xx00"
            std::uint16_t HiByte{};
            if ((ptr & 0x00FF) == 0xFF) {
                HiByte = m_cpu.readByte(ptr & 0xFF00);
            } else {
                HiByte = m_cpu.readByte(ptr + 1);
            }
            return (HiByte << 8) | LoByte;
            }
            break;
        case Instructions::AbsoluteX:
            return m_cpu.readWord(m_cpu.pc + 1) + m_cpu.xReg;
            break;
        case Instructions::AbsoluteY:
            return m_cpu.readWord(m_cpu.pc + 1) + m_cpu.yReg;
            break;
        default:
            return 0;
            break;
    }
}

void Instructions::opAdc(AddrMode addr) {

}
