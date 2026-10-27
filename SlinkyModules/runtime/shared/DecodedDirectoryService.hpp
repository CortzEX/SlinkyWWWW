#ifndef SLINKY_SHARE_48CFA598C58FAA65DC7F
#define SLINKY_SHARE_48CFA598C58FAA65DC7F
// Source-equivalent DCDBE0 service-cell contract from selected captured bytes.
// Semantic names were assigned during recovery. Original source identifiers
// and helper boundaries are not preserved. See DirectoryServiceStaticFrameReview.
#include <cstdint>

namespace reconstruction::directory_service {
using Word = std::uint64_t;
inline constexpr std::uint32_t encodedCellRva_dcdbe0 = 0xacc76a;
inline constexpr Word pointerSubtract_dcdbe0 = 0x1c611ead;
struct Context {
    const std::uint8_t *image;
    const std::uint8_t *encodedCell = nullptr;
};
Word decodedTarget_dcdbe0(const std::uint8_t *cell);
Word execute_dcdbe0(const Context &,Word owner,const std::uint16_t *operation,
    const std::uint16_t *path,Word parameters,Word directory,std::uint32_t show);
}
#endif // SLINKY_SHARE_48CFA598C58FAA65DC7F
