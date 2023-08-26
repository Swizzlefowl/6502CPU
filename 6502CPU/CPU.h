#ifndef CPU
#define CPU
#include <cstdint>
#include <fmt/core.h>
#include "Instructions.h"
#include <vector>
#include <string_view>
struct StatusRegister {
    using Flags = std::uint8_t;
    Flags flags{}
    ;

    /*7  bit  0
        ---- ----
        NVss DIZC
        |||| ||||
        |||| |||+- Carry
        |||| ||+-- Zero
        |||| |+--- Interrupt Disable
        |||| +---- Decimal
        ||++------ No CPU effect, see: the B flag
        |+-------- Overflow
        +--------- Negative*/
    enum FlagBits: uint8_t {
        Carry = 0b1, 
        Zero = (0b1<<1),
        InterruptDisable = (0b1 << 2),
        Decimal = (0b1 << 3),
        Break1 = (0b1 << 4),
        Break2 = (0b1 << 5),
        Overflow = (0b1 << 6),
        Negative = (0b1 << 7),
    };

    void set(const FlagBits& Mask);
    void clear(const FlagBits& Mask);
    bool isSet(const FlagBits& Mask);
};

struct cpu {
    
  public:
    Instructions instr;
    StatusRegister Statusreg{};
    std::uint8_t AReg{};
    std::uint8_t XReg{};
    std::uint8_t YReg{};
    std::uint16_t pc{};
    std::uint8_t sp{};
    std::vector<char> memory{};

    std::uint8_t readByte(std::uint16_t adress);
    std::uint16_t readWord(std::uint16_t adress);

    void writeByte(std::uint16_t adress, std::uint8_t val);
    void writeWord(std::uint16_t adress, std::uint16_t val);

    // fn to push a byte into the stack
    void pushByte(std::uint8_t value);

    // fn to pop a byte into the stack
    std::uint8_t popByte();

    // fn to push a word into the stack
    void pushWord(std::uint16_t value);

    // fn to pop a word into the stack
    std::uint16_t popWord();

    cpu();
    ~cpu();

    void printCPUState(const std::string_view& opName);
    void tick();
    void execute(std::uint8_t opcode);
};

#endif // !CPU
