#include "UnitTests.h"
#include "fmt/core.h"
#include <cassert>

void testOpAdc() {
    cpu m_cpu{};
    std::uint8_t operand = UINT8_MAX;
    m_cpu.AReg = 1;
    m_cpu.AReg += operand;
    bool overflow = m_cpu.AReg < operand ? true : false;
    if (overflow) {
        m_cpu.Statusreg.set(StatusRegister::Overflow);
        m_cpu.Statusreg.set(StatusRegister::Carry);

        assert(m_cpu.Statusreg.isSet(StatusRegister::Overflow) && "Overflow is not set!");
        assert(m_cpu.Statusreg.isSet(StatusRegister::Carry) && "Carry is not set!");
    }
    if (m_cpu.AReg == 0) {
        m_cpu.Statusreg.set(StatusRegister::Zero);
        assert(m_cpu.Statusreg.isSet(StatusRegister::Zero) && "Zero is not set!");
    }
    m_cpu.AReg = 0xff;
    if (m_cpu.AReg & StatusRegister::Negative) {
        m_cpu.Statusreg.set(StatusRegister::Negative);
        assert(m_cpu.Statusreg.isSet(StatusRegister::Negative) && "Negative is not set!");
    }

    fmt::println("{}", m_cpu.AReg);
    fmt::println("{:0b}", m_cpu.Statusreg.flags);
}

void testOpAnd() {
    cpu m_cpu{};
    m_cpu.AReg &= 0x0;

    if (m_cpu.AReg == 0) {
        m_cpu.Statusreg.set(StatusRegister::Zero);
        assert(m_cpu.Statusreg.isSet(StatusRegister::Zero) && "Zero is not set!");
    }

    m_cpu.AReg &= 0xff;
    if (m_cpu.AReg & StatusRegister::Negative) {
        m_cpu.Statusreg.set(StatusRegister::Negative);
        assert(m_cpu.Statusreg.isSet(StatusRegister::Negative) && "Negative is not set!");
    }
    fmt::println("{}", m_cpu.AReg);
    fmt::println("{:0b}", m_cpu.Statusreg.flags);
}
