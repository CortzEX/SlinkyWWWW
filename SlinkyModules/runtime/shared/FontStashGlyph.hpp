#ifndef SLINKY_SHARE_C2085441E03E018F0A33
#define SLINKY_SHARE_C2085441E03E018F0A33
#include <cstdint>
namespace reconstruction::fontstash {
struct GlyphDependencies {
    void *context;
    const std::uint8_t *image;
    std::int32_t (*mapGlyph_62850)(void*,std::uint8_t *font,std::uint32_t codepoint);
    std::int32_t (*glyphBox_63cf0)(void*,std::uint8_t*,std::int32_t,
        std::int32_t*,std::int32_t*,std::int32_t*,std::int32_t*);
    void *(*resize_13cf90)(void*,void*,std::uint64_t);
    void (*atlasError)(void*,std::uint64_t target,std::uint64_t user,
        std::int32_t error,std::int32_t value);
    void (*bitmap_66f00)(void*,std::uint8_t *font,std::uint8_t *output,
        std::int32_t width,std::int32_t height,std::int32_t stride,
        float scaleX,float scaleY,float shiftX,float shiftY,std::int32_t glyph);
};
std::int32_t addRectangle_7dd90(std::uint8_t *atlas,std::int32_t width,
    std::int32_t height,std::int32_t *x,std::int32_t *y,const GlyphDependencies&);
std::uint8_t *lookupGlyph_6d1d0(std::uint8_t *stash,std::uint8_t *font,
    std::uint32_t codepoint,std::uint32_t sizeBits,std::int16_t blur,
    std::int32_t bitmapRequired,const GlyphDependencies&);
}
#endif // SLINKY_SHARE_C2085441E03E018F0A33
