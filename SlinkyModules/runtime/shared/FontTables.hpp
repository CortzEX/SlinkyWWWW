#ifndef SLINKY_SHARE_4AA82DAAE1BB940CDCFC
#define SLINKY_SHARE_4AA82DAAE1BB940CDCFC
#include <cstdint>
#include <cstddef>

namespace reconstruction::fonttables {
// The embedded native font-info record is borrowed; +8 is its byte-data pointer,
// +0x38 its selected cmap offset, and +0x40 begins the CFF buffer record.
struct Vertex {
    std::int16_t x, y, controlX, controlY, controlX1, controlY1;
    std::uint8_t type, padding;
};
static_assert(sizeof(Vertex) == 14 && offsetof(Vertex, type) == 12);

struct ShapeDependencies {
    void *context;
    // This build uses the caller-owned stash scratch arena (+0x5080/+0x5088),
    // not a heap allocator. Its installed error callback receives (user, 2).
    void (*scratchError)(void *context, std::uint64_t target,
        std::uint64_t nativeUser, std::int32_t error);
    const std::uint8_t *image;
};

std::int32_t mapGlyph_62850(std::uint8_t *font, std::uint32_t codepoint);
std::int32_t glyphBox_63cf0(std::uint8_t *font, std::int32_t glyph,
    std::int32_t *x0, std::int32_t *y0, std::int32_t *x1, std::int32_t *y1);
std::int32_t kerning_64170(std::uint8_t *font,
    std::int32_t previous, std::int32_t current);
std::int32_t glyphClass_7d0e0(const std::uint8_t *table, std::int32_t glyph);
std::int32_t getGlyphShape_62bb0(std::uint8_t *font, std::int32_t glyph,
    Vertex **output, const ShapeDependencies &);
}
#endif // SLINKY_SHARE_4AA82DAAE1BB940CDCFC
