#ifndef SLINKY_SHARE_2C4B4B40A650806623BF
#define SLINKY_SHARE_2C4B4B40A650806623BF
#include <cstdint>

namespace reconstruction::window_service {
using Word = std::uint64_t;
inline constexpr std::uint32_t encodedCellRva_103762f = 0xf947c2;
inline constexpr Word pointerAdd_103762f = 0x13a545f1;
struct Context {
    const std::uint8_t *image;
    const std::uint8_t *encodedCell = nullptr;
};
Word decodedTarget_103762f(const std::uint8_t *cell);
Word query_103762f(const Context &);
}
#endif // SLINKY_SHARE_2C4B4B40A650806623BF
