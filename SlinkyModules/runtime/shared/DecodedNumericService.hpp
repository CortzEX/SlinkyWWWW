#ifndef SLINKY_SHARE_C0EB4BDB7EA461397A74
#define SLINKY_SHARE_C0EB4BDB7EA461397A74
// Six native numeric dispatch contracts reconstructed from supplied capture
// by static stack/constant analysis. Captured exports: hypot, atan2, acos,
// atan2f, acosf and powf. The Protected*StaticReview reports preserve each proof.
#include <cstdint>
namespace reconstruction::numeric_service {
inline constexpr std::uint64_t inlineCellRva_13cfd0 = 0xfef6c6;
inline constexpr std::uint64_t pointerAddend_13cfd0 = 0x2d2898a5;
inline constexpr std::uint64_t inlineCellRva_13cfb0 = 0xf48782;
inline constexpr std::uint64_t pointerSubtract_13cfb0 = 0x327eb16a;
inline constexpr std::uint64_t inlineCellRva_13cfa0 = 0xae5156;
inline constexpr std::uint64_t pointerSubtract_13cfa0 = 0x2bd9c5ac;
inline constexpr std::uint64_t inlineCellRva_13cfc0 = 0xac1e69;
inline constexpr std::uint64_t pointerAddend_13cfc0 = 0x7936cc91;
inline constexpr std::uint64_t inlineCellRva_13d190 = 0xe3bdff;
inline constexpr std::uint64_t pointerSubtract_13d190 = 0x7a471c96;
inline constexpr std::uint64_t inlineCellRva_13cfe0 = 0xb49c28;
inline constexpr std::uint64_t pointerSubtract_13cfe0 = 0x73f18291;
// Borrowed storage only. A partial ordinary-section image must supply the
// explicit cell; a complete image may use its proven image-relative cell.
struct Context {
    const std::uint8_t *image;
    const std::uint8_t *encodedCellOverride = nullptr;
};
std::uint64_t decodedTarget_13cfd0(const std::uint8_t *encodedCell);
double pairCell_13cfd0(const std::uint8_t *encodedCell, double first, double second);
double pair_13cfd0(const Context &, double first, double second);
std::uint64_t decodedTarget_13cfb0(const std::uint8_t *encodedCell);
double directionCell_13cfb0(const std::uint8_t *encodedCell, double first, double second);
double direction_13cfb0(const Context &, double first, double second);
std::uint64_t decodedTarget_13cfa0(const std::uint8_t *encodedCell);
double projectionCell_13cfa0(const std::uint8_t *encodedCell, double value);
double projection_13cfa0(const Context &, double value);
std::uint64_t decodedTarget_13cfc0(const std::uint8_t *encodedCell);
float floatDirectionCell_13cfc0(const std::uint8_t *encodedCell, float first, float second);
float floatDirection_13cfc0(const Context &, float first, float second);
std::uint64_t decodedTarget_13d190(const std::uint8_t *encodedCell);
float floatUnaryCell_13d190(const std::uint8_t *encodedCell, float value);
float floatUnary_13d190(const Context &, float value);
std::uint64_t decodedTarget_13cfe0(const std::uint8_t *encodedCell);
float binaryScalarCell_13cfe0(const std::uint8_t *encodedCell, float first, float second);
float binaryScalar_13cfe0(const Context &, float first, float second);
}
#endif // SLINKY_SHARE_C0EB4BDB7EA461397A74
