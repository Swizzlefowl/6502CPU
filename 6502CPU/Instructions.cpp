#include "Instructions.h"
#include "CPU.h"

Instructions::Instructions(cpu& cpu)
    : m_cpu{cpu} {


}

Instructions::~Instructions() {
}

std::uint16_t Instructions::fetchArgumentadress(AddrMode addrMode) {
    auto instrAfterOp = m_cpu.pc + 1;
    switch (addrMode) {
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
            std::int8_t offset = static_cast<std::int8_t>(m_cpu.readByte(instrAfterOp));
            return (m_cpu.pc + offset) + 1 ;
                }
            break;
        case Instructions::IndirectX:{ 
            std::uint8_t ptr = m_cpu.readByte(instrAfterOp) + m_cpu.XReg;
            std::uint16_t LoByte = m_cpu.readByte(ptr);
            std::uint16_t HiByte = m_cpu.readByte(ptr + 1);
            std::uint16_t adress = (HiByte << 8) | LoByte;
            
            return adress;
            }
            break;
        case Instructions::IndirectY:{ 
            std::uint8_t ptr = m_cpu.readByte(instrAfterOp);
            std::uint16_t LoByte = m_cpu.readByte(ptr);
            std::uint16_t HiByte = m_cpu.readByte(ptr + 1);
            std::uint16_t adressBase = (HiByte << 8) | LoByte;

            return adressBase + m_cpu.YReg;
            }
            break;
        case Instructions::Absolute:
            return m_cpu.readWord(instrAfterOp);
            break;
        case Instructions::ZeroPage:
            return m_cpu.readByte(instrAfterOp);
            break;
        case Instructions::ZeroPageX:
            return m_cpu.readByte(instrAfterOp + m_cpu.XReg);
            break;
        case Instructions::ZeroPageY:
            return m_cpu.readByte(instrAfterOp + m_cpu.YReg);
            break;
        case Instructions::Indirect:{ 
            std::uint16_t ptr = m_cpu.readWord(instrAfterOp);
            std::uint16_t LoByte = m_cpu.readByte(ptr);
            // Accomodate for a hardware bug, the 6502 reference states the following:
            // "An original 6502 does not correctly fetch the target address if the indirect vector
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
        case Instructions::AbsoluteX: {
            auto adressBase = m_cpu.readWord(instrAfterOp);
            auto adress = m_cpu.readWord(adressBase + m_cpu.XReg);

            return adress;
        }
            break;
        case Instructions::AbsoluteY: {
            auto adressBase = m_cpu.readWord(instrAfterOp);
            auto adress = m_cpu.readWord(adressBase + m_cpu.YReg);

            return adress;
        }
            break;
        default:
            return 0;
            break;
    }
}

std::uint8_t Instructions::fetchArgument(AddrMode addrMode) {
    auto address = fetchArgumentadress(addrMode);
    return m_cpu.readByte(address);
}

void Instructions::opAdc(AddrMode addr) {
    auto operand = fetchArgument(addr);
    m_cpu.AReg += operand;

    bool overflow = m_cpu.AReg < operand ? true : false;
    if (overflow) {
        m_cpu.Statusreg.set(StatusRegister::Overflow);
        m_cpu.Statusreg.set(StatusRegister::Carry);
    }
    if (m_cpu.AReg == 0) {
        m_cpu.Statusreg.set(StatusRegister::Zero);
    }
    if (m_cpu.AReg & StatusRegister::Negative) {
        m_cpu.Statusreg.set(StatusRegister::Negative);
    }
}

void Instructions::opAnd(AddrMode addr) {
    m_cpu.AReg &= fetchArgument(addr);

     if (m_cpu.AReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
     if (m_cpu.AReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
}

