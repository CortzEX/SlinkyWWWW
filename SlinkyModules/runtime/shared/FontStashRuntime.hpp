#ifndef SLINKY_SHARE_C376AEA07AA442E4B22F
#define SLINKY_SHARE_C376AEA07AA442E4B22F
#include <cstdint>
#include <cstddef>

namespace reconstruction::fontstash {
struct GlyphQuad {float x0,y0,s0,t0,x1,y1,s1,t1;};
struct TextIterator {
    float x,y,nextX,nextY,scale,spacing;
    std::uint32_t codepoint;
    std::int16_t size,blur;
    std::uint8_t *font;
    std::int32_t previousGlyph;
    std::uint32_t reserved2c;
    const char *start,*next,*end;
    std::uint32_t utf8State;
    std::int32_t bitmapRequired;
};
static_assert(sizeof(TextIterator)==80 && offsetof(TextIterator,font)==0x20 && offsetof(TextIterator,next)==0x38);
struct Dependencies {
    void *context;
    const std::uint8_t *image;
    std::uint8_t *(*glyph_6d1d0)(void*,std::uint8_t *stash,std::uint8_t *font,
        std::uint32_t codepoint,std::uint32_t sizeBits,std::int16_t blur,
        std::int32_t bitmapRequired);
    std::int32_t (*kerning_64170)(void*,std::uint8_t *font,std::int32_t previous,std::int32_t current);
};
float textBounds_6cde0(std::uint8_t *stash,float x,float y,const char *text,
    const char *end,float *bounds,const Dependencies&);
void lineBounds_6ebc0(std::uint8_t *stash,float y,float *minimum,float *maximum,const Dependencies&);
std::int32_t iteratorInit_6dff0(std::uint8_t *stash,TextIterator*,float x,float y,
    const char *text,const char *end,std::int32_t bitmapRequired,const Dependencies&);
std::int32_t iteratorNext_6e2d0(std::uint8_t *stash,TextIterator*,GlyphQuad*,const Dependencies&);
void glyphQuad_6de40(std::uint8_t *stash,std::uint8_t *font,std::int32_t previous,
    const std::uint8_t *glyph,float scale,float spacing,float *x,float *y,
    GlyphQuad*,const Dependencies&);
}
#endif // SLINKY_SHARE_C376AEA07AA442E4B22F
