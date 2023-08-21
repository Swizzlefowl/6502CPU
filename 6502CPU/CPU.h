#ifndef CPU
#define CPU

#include <cstdint>
class cpu {

  public:
    std::uint8_t accuReg{};
    std::uint8_t xReg{};
    std::uint8_t yReg{};
    std::uint16_t pc{};
    std::uint8_t sp{};
    cpu();
    ~cpu();
};

#endif // !CPU
