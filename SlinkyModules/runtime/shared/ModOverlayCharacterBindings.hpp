#ifndef SLINKY_SHARE_AFC04180D865DF59B0BD
#define SLINKY_SHARE_AFC04180D865DF59B0BD
// Four captured Mod Overlay character contracts use one encoded cell.
// ProtectedOverlay*StaticReview reports prove each actual caller frame and
// the distinct resolver/per-byte reload policies. Retained copies unchanged.
#include <cstdint>

namespace reconstruction::overlay_character {
using Endpoint = std::int32_t (*)(std::int32_t);
struct Context {
    const std::uint8_t *image;
    const std::uint8_t *encodedCellOverride = nullptr;
};
inline constexpr std::uint64_t inlineCellRva_32ecfb = 0xe8d88f;
inline constexpr std::uint64_t pointerAdd_32ecfb = 0x7539b2bb;
std::uint64_t decodedTarget_32ecfb(const std::uint8_t *encodedCell);
Endpoint resolve_32ecfb(const Context &);
Endpoint resolve_bb8f39(const Context &);
Endpoint resolve_e6314d(const Context &);
std::int32_t character_e28595(const Context &, std::int32_t character);
}
#endif // SLINKY_SHARE_AFC04180D865DF59B0BD
