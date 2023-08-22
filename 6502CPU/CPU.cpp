#include "CPU.h"
cpu::cpu() {

}

cpu::~cpu() {

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

