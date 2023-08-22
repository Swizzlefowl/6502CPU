#ifndef CPU
#define CPU
#include <cstdint>
#include <fmt/core.h>

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

class cpu {
    
  public:
    StatusRegister Statusreg{};
    std::uint8_t accuReg{};
    std::uint8_t xReg{};
    std::uint8_t yReg{};
    std::uint16_t pc{};
    std::uint8_t sp{};
    cpu();
    ~cpu();
};

#endif // !CPU
