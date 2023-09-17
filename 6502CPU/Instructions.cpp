#include "Instructions.h"
#include "CPU.h"

Instructions::Instructions(cpu& cpu)
    : m_cpu{cpu} {


}

Instructions::~Instructions() {
}

// the function and most of the project is inspired from https://github.com/IvarWithoutBones
// implementaion of the NES CPU
std::uint16_t Instructions::fetchArgumentadress(AddrMode addrMode) {
    auto instrAfterOp = ((m_cpu.pc + 1) - 0x8000) % 0x4000;
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
                /*std::int16_t offset = m_cpu.readByte(instrAfterOp);
                if (offset & StatusRegister::Negative) {
                    offset |= 0xff00; 
                    return (m_cpu.pc + offset);
                    }
                return m_cpu.pc + offset + 1;*/
            std::int8_t offset = static_cast<std::int8_t>(m_cpu.readByte(instrAfterOp));
            return m_cpu.pc + offset + 1;
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

std::uint8_t Instructions::fetchArgument(AddrMode mode) {
    auto address = fetchArgumentadress(mode);
    return m_cpu.readByte(address);
}

void Instructions::opADC(AddrMode mode) {
    auto operand = fetchArgument(mode);
    m_cpu.AReg += operand;

    bool overflow = m_cpu.AReg < operand ? true : false;
    if (overflow) {
        m_cpu.Statusreg.set(StatusRegister::Overflow);
        m_cpu.Statusreg.set(StatusRegister::Carry);
    } else {
        m_cpu.Statusreg.clear(StatusRegister::Overflow);
        m_cpu.Statusreg.clear(StatusRegister::Carry);
    }

    if (m_cpu.AReg == 0) {
        m_cpu.Statusreg.set(StatusRegister::Zero);
    } else {
         m_cpu.Statusreg.clear(StatusRegister::Zero);
    }

    if (m_cpu.AReg & StatusRegister::Negative) {
        m_cpu.Statusreg.set(StatusRegister::Negative);
    } else {
        m_cpu.Statusreg.clear(StatusRegister::Negative);
    }
}

void Instructions::opAND(AddrMode mode) {
    m_cpu.AReg &= fetchArgument(mode);

     if (m_cpu.AReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
     else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

     if (m_cpu.AReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
     else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opASL(AddrMode mode) {
     if (mode == Instructions::Accumulator) {
        // I am using the negative flag to just test if the 7th bit of
        // Areg is set or not
        if (m_cpu.AReg & StatusRegister::Negative)
            m_cpu.Statusreg.set(StatusRegister::Carry);
        else
            m_cpu.Statusreg.clear(StatusRegister::Carry);

        m_cpu.AReg <<= 1;

        if (m_cpu.AReg == 0)
            m_cpu.Statusreg.set(StatusRegister::Zero);
        else
            m_cpu.Statusreg.clear(StatusRegister::Zero);

        if (m_cpu.AReg & StatusRegister::Negative)
            m_cpu.Statusreg.set(StatusRegister::Negative);
        else
            m_cpu.Statusreg.clear(StatusRegister::Negative);

    } else {
        auto adress = fetchArgumentadress(mode);
        auto value = m_cpu.readByte(adress);

        // I am using the negative flag to just test if the 7th bit of
        // value is set or not
        if (value & StatusRegister::Negative)
            m_cpu.Statusreg.set(StatusRegister::Carry);
        else
            m_cpu.Statusreg.clear(StatusRegister::Carry);

        value <<= 1;
        if (value == 0)
            m_cpu.Statusreg.set(StatusRegister::Zero);
        else
            m_cpu.Statusreg.clear(StatusRegister::Zero);

        if (value & StatusRegister::Negative)
            m_cpu.Statusreg.set(StatusRegister::Negative);
        else
            m_cpu.Statusreg.clear(StatusRegister::Negative);

        m_cpu.writeByte(adress, value);
    }
}

void Instructions::opBCC(AddrMode mode) {
    if (!m_cpu.Statusreg.isSet(StatusRegister::Carry)) {
        auto adress = fetchArgumentadress(mode);
        m_cpu.pc = adress;
    }
}

void Instructions::opBCS(AddrMode mode) {
    if (m_cpu.Statusreg.isSet(StatusRegister::Carry)) {
        auto adress = fetchArgumentadress(mode);
        m_cpu.pc = adress;
    }
}

void Instructions::opBEQ(AddrMode mode) {
    if (m_cpu.Statusreg.isSet(StatusRegister::Zero)) {
        auto adress = fetchArgumentadress(mode);
        m_cpu.pc = adress;
    }
}

void Instructions::opBMI(AddrMode mode) {
    if (m_cpu.Statusreg.isSet(StatusRegister::Negative)) {
        auto adress = fetchArgumentadress(mode);
        m_cpu.pc = adress;
    }
}

void Instructions::opBNE(AddrMode mode) {
    if (!m_cpu.Statusreg.isSet(StatusRegister::Zero)) {
        auto adress = fetchArgumentadress(mode);
        m_cpu.pc = adress;
    }
}

void Instructions::opBPL(AddrMode mode) {
    if (!m_cpu.Statusreg.isSet(StatusRegister::Negative)) {
        auto adress = fetchArgumentadress(mode);
        m_cpu.pc = adress;
    }
}

void Instructions::opBVC(AddrMode mode) {
    if (!m_cpu.Statusreg.isSet(StatusRegister::Overflow)) {
        auto adress = fetchArgumentadress(mode);
        m_cpu.pc = adress;
    }
}

void Instructions::opBVS(AddrMode mode) {
    if (m_cpu.Statusreg.isSet(StatusRegister::Overflow)) {
        auto adress = fetchArgumentadress(mode);
        m_cpu.pc = adress;
    }
}

void Instructions::opBIT(AddrMode mode) {
    auto value = fetchArgument(mode);
    
    if ((value & m_cpu.AReg) == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (value & StatusRegister::Overflow)
        m_cpu.Statusreg.set(StatusRegister::Overflow);
    else
        m_cpu.Statusreg.clear(StatusRegister::Overflow);

    if (value & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opBRK(AddrMode mode) {
    // TODO
    return;
}

void Instructions::opCLC(AddrMode mode) {
    m_cpu.Statusreg.clear(StatusRegister::Carry);
}

void Instructions::opCLD(AddrMode mode) {
    m_cpu.Statusreg.clear(StatusRegister::Decimal);
}

void Instructions::opCLI(AddrMode mode) {
    m_cpu.Statusreg.clear(StatusRegister::InterruptDisable);
}

void Instructions::opCLV(AddrMode mode) {
    m_cpu.Statusreg.clear(StatusRegister::Overflow);
}

void Instructions::opCMP(AddrMode mode) {
    auto value = fetchArgument(mode);

    if (m_cpu.AReg >= value)
        m_cpu.Statusreg.set(StatusRegister::Carry);
    else
        m_cpu.Statusreg.clear(StatusRegister::Carry);

    std::uint8_t result = m_cpu.AReg - value;

    if (result == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (result & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opCPX(AddrMode mode) {
    auto value = fetchArgument(mode);

    if (m_cpu.XReg >= value)
        m_cpu.Statusreg.set(StatusRegister::Carry);
    else
        m_cpu.Statusreg.clear(StatusRegister::Carry);

    std::uint8_t result = m_cpu.XReg - value;

    if (result == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (result & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opCPY(AddrMode mode) {
    auto value = fetchArgument(mode);

    if (m_cpu.YReg >= value)
        m_cpu.Statusreg.set(StatusRegister::Carry);
    else
        m_cpu.Statusreg.clear(StatusRegister::Carry);

    std::uint8_t result = m_cpu.YReg - value;

    if (result == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (result & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opDEC(AddrMode mode) {
    auto adress = fetchArgumentadress(mode);
    auto value = fetchArgument(mode);
    value -= 1;

    if (value == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (value & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);

    m_cpu.writeByte(adress, value);
}

void Instructions::opDEX(AddrMode mode) {
    m_cpu.XReg -= 1;

    if (m_cpu.XReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (m_cpu.XReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opDEY(AddrMode mode) {
    m_cpu.YReg -= 1;

    if (m_cpu.YReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (m_cpu.YReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opEOR(AddrMode mode) {
    auto value = fetchArgument(mode);
    m_cpu.AReg ^= value;

    if (m_cpu.AReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (m_cpu.AReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opINC(AddrMode mode) {
    auto adress = fetchArgumentadress(mode);
    auto value = fetchArgument(mode);
    value += 1;

    if (value == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (value & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);

    m_cpu.writeByte(adress, value);
}

void Instructions::opINX(AddrMode mode) {
    m_cpu.XReg += 1;

    if (m_cpu.XReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (m_cpu.XReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opINY(AddrMode mode) {
    m_cpu.YReg += 1;

    if (m_cpu.YReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (m_cpu.YReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opJMP(AddrMode mode) {
    auto adress = fetchArgumentadress(mode);
    m_cpu.pc = adress;
}

void Instructions::opJSR(AddrMode mode) {
    auto adress = fetchArgumentadress(mode);

    m_cpu.pushWord(m_cpu.pc + 2);
    m_cpu.pc = adress;
}

void Instructions::opLDA(AddrMode mode) {
    m_cpu.AReg = fetchArgument(mode);

    if (m_cpu.AReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (m_cpu.AReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opLDX(AddrMode mode) {
    m_cpu.XReg = fetchArgument(mode);

    if (m_cpu.XReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (m_cpu.XReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opLDY(AddrMode mode) {
    m_cpu.YReg = fetchArgument(mode);

    if (m_cpu.YReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (m_cpu.YReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opLSR(AddrMode mode) {
    if (mode == Instructions::Accumulator) {
        // I am using the Carry flag to just test if the 0th bit of
        // Areg is set or not
        if (m_cpu.AReg & StatusRegister::Carry)
            m_cpu.Statusreg.set(StatusRegister::Carry);
        else
            m_cpu.Statusreg.clear(StatusRegister::Carry);

        m_cpu.AReg >>= 1;

        if (m_cpu.AReg == 0)
            m_cpu.Statusreg.set(StatusRegister::Zero);
        else
            m_cpu.Statusreg.clear(StatusRegister::Zero);

        if (m_cpu.AReg & StatusRegister::Negative)
            m_cpu.Statusreg.set(StatusRegister::Negative);
        else
            m_cpu.Statusreg.clear(StatusRegister::Negative);

    } else {
        auto adress = fetchArgumentadress(mode);
        auto value = m_cpu.readByte(adress);

        // I am using the Carry flag to just test if the 0th bit of
        // value is set or not
        if (value & StatusRegister::Carry)
            m_cpu.Statusreg.set(StatusRegister::Carry);
        else
            m_cpu.Statusreg.clear(StatusRegister::Carry);

        value >>= 1;

        if (value == 0)
            m_cpu.Statusreg.set(StatusRegister::Zero);
        else
            m_cpu.Statusreg.clear(StatusRegister::Zero);

        if (value & StatusRegister::Negative)
            m_cpu.Statusreg.set(StatusRegister::Negative);
        else
            m_cpu.Statusreg.clear(StatusRegister::Negative);

        m_cpu.writeByte(adress, value);
    }
}

void Instructions::opNOP(AddrMode mode) {
    // TODO throw ken here, lazy ass fuck
    // needs to return to his job
    return;
}

void Instructions::opORA(AddrMode mode) {
    auto value = fetchArgument(mode);
    m_cpu.AReg |= value;

    if (m_cpu.AReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (m_cpu.AReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opPHA(AddrMode mode) {
    m_cpu.pushByte(m_cpu.AReg);
}

void Instructions::opPHP(AddrMode mode) {
    m_cpu.pushByte(m_cpu.Statusreg.flags);
}

void Instructions::opPLA(AddrMode mode) {
    m_cpu.AReg = m_cpu.popByte();

    if (m_cpu.AReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (m_cpu.AReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opPLP(AddrMode mode) {
    m_cpu.Statusreg.flags = m_cpu.popByte();
}

void Instructions::opROL(AddrMode mode) {
    if (mode == Instructions::Accumulator) {
        bool oldBitSeven = m_cpu.AReg & StatusRegister::Negative;

        m_cpu.AReg <<= 1;
        if (m_cpu.AReg == 0)
            m_cpu.Statusreg.set(StatusRegister::Zero);
        else
            m_cpu.Statusreg.clear(StatusRegister::Zero);

        if (m_cpu.Statusreg.isSet(StatusRegister::Carry))
            m_cpu.AReg |= StatusRegister::Carry;

        if (oldBitSeven)
            m_cpu.Statusreg.set(StatusRegister::Carry);
        else {
             m_cpu.Statusreg.clear(StatusRegister::Carry);
        }

        if (m_cpu.AReg & StatusRegister::Negative)
            m_cpu.Statusreg.set(StatusRegister::Negative);
        else
            m_cpu.Statusreg.clear(StatusRegister::Negative);

    } else {
        auto adress = fetchArgumentadress(mode);
        auto value = m_cpu.readByte(adress);
        bool oldBitSeven = value & StatusRegister::Negative;

        value <<= 1;

        if (value == 0)
            m_cpu.Statusreg.set(StatusRegister::Zero);
        else
            m_cpu.Statusreg.clear(StatusRegister::Zero);

        if (m_cpu.Statusreg.isSet(StatusRegister::Carry))
            value |= StatusRegister::Carry;

        if (oldBitSeven)
            m_cpu.Statusreg.set(StatusRegister::Carry);
        else
            m_cpu.Statusreg.clear(StatusRegister::Carry);

        if (value & StatusRegister::Negative)
            m_cpu.Statusreg.set(StatusRegister::Negative);
        else
            m_cpu.Statusreg.clear(StatusRegister::Negative);

        m_cpu.writeByte(adress, value);
    }

}

void Instructions::opROR(AddrMode mode) {
    if (mode == Instructions::Accumulator) {
        bool oldBitZero = m_cpu.AReg & StatusRegister::Carry;

        m_cpu.AReg >>= 1;

        if (m_cpu.AReg == 0)
            m_cpu.Statusreg.set(StatusRegister::Zero);
        else
            m_cpu.Statusreg.clear(StatusRegister::Zero);

        if (m_cpu.Statusreg.isSet(StatusRegister::Carry))
            m_cpu.AReg |= StatusRegister::Negative;

        if (oldBitZero)
            m_cpu.Statusreg.set(StatusRegister::Carry);
        else
            m_cpu.Statusreg.clear(StatusRegister::Carry);

        if (m_cpu.AReg & StatusRegister::Negative)
            m_cpu.Statusreg.set(StatusRegister::Negative);
        else
            m_cpu.Statusreg.clear(StatusRegister::Negative);

    } else {
        auto adress = fetchArgumentadress(mode);
        auto value = m_cpu.readByte(adress);
        bool oldBitZero = value & StatusRegister::Carry;

        value <<= 1;
        if (value == 0)
            m_cpu.Statusreg.set(StatusRegister::Zero);
        else
            m_cpu.Statusreg.clear(StatusRegister::Zero);

        if (m_cpu.Statusreg.isSet(StatusRegister::Carry))
            value |= StatusRegister::Negative;

        if (oldBitZero)
            m_cpu.Statusreg.set(StatusRegister::Carry);
        else
            m_cpu.Statusreg.clear(StatusRegister::Carry);

        if (value & StatusRegister::Negative)
            m_cpu.Statusreg.set(StatusRegister::Negative);
        else
            m_cpu.Statusreg.clear(StatusRegister::Negative);

        m_cpu.writeByte(adress, value);
    }

}

void Instructions::opRTI(AddrMode mode) {
    return;
}

void Instructions::opRTS(AddrMode mode) {
    auto adress = m_cpu.popWord();
    m_cpu.pc = adress;
}

void Instructions::opSBC(AddrMode mode) {
    auto operand = fetchArgument(mode);
    auto carry = static_cast<std::uint8_t>((!m_cpu.Statusreg.isSet(StatusRegister::Carry)));

    m_cpu.AReg = m_cpu.AReg - operand - carry;

    bool overflow = m_cpu.AReg > operand ? true : false;
    if (overflow) {
        m_cpu.Statusreg.set(StatusRegister::Overflow);
        m_cpu.Statusreg.clear(StatusRegister::Carry);
    }
    if (m_cpu.AReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (m_cpu.AReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opSEC(AddrMode mode) {
    m_cpu.Statusreg.set(StatusRegister::Carry);
}

void Instructions::opSED(AddrMode mode) {
    m_cpu.Statusreg.set(StatusRegister::Decimal);
}

void Instructions::opSEI(AddrMode mode) {
    m_cpu.Statusreg.set(StatusRegister::InterruptDisable);
}

void Instructions::opSTA(AddrMode mode) {
    auto adress = m_cpu.instr.fetchArgumentadress(mode);
    m_cpu.writeByte(adress, m_cpu.AReg);
}

void Instructions::opSTX(AddrMode mode) {
    auto adress = m_cpu.instr.fetchArgumentadress(mode);
    m_cpu.writeByte(adress, m_cpu.XReg);
}

void Instructions::opSTY(AddrMode mode) {
    auto adress = m_cpu.instr.fetchArgumentadress(mode);
    m_cpu.writeByte(adress, m_cpu.YReg);
}

void Instructions::opTAX(AddrMode mode) {
    m_cpu.XReg = m_cpu.AReg;

    if (m_cpu.XReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (m_cpu.XReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opTAY(AddrMode mode) {
    m_cpu.YReg = m_cpu.AReg;

    if (m_cpu.YReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (m_cpu.YReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opTSX(AddrMode mode) {
    m_cpu.XReg = m_cpu.sp;

    if (m_cpu.XReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (m_cpu.XReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opTXA(AddrMode mode) {
    m_cpu.AReg = m_cpu.XReg;

    if (m_cpu.AReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (m_cpu.AReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}

void Instructions::opTXS(AddrMode mode) {
    m_cpu.sp = m_cpu.XReg;
}

void Instructions::opTYA(AddrMode mode) {
    m_cpu.AReg = m_cpu.YReg;

    if (m_cpu.AReg == 0)
        m_cpu.Statusreg.set(StatusRegister::Zero);
    else
        m_cpu.Statusreg.clear(StatusRegister::Zero);

    if (m_cpu.AReg & StatusRegister::Negative)
        m_cpu.Statusreg.set(StatusRegister::Negative);
    else
        m_cpu.Statusreg.clear(StatusRegister::Negative);
}



