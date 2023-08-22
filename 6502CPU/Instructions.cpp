#include "Instructions.h"
#include "CPU.h"

Instructions::Instructions(cpu& cpu)
    : m_cpu{cpu} {


}

Instructions::~Instructions() {
}

std::uint16_t Instructions::fetchArgumentadress() {
    return std::uint16_t();
}

std::uint8_t Instructions::fetchArgument() {
    return std::uint8_t();
}

void Instructions::opAdc(AddrMode addr, std::uint16_t op) {

}
