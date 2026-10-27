#ifndef SLINKY_SHARE_ED5F8680BCDFFCC28C6E
#define SLINKY_SHARE_ED5F8680BCDFFCC28C6E
#include <cstdint>

namespace reconstruction::drawing {
// The callbacks are the native allocator, path tessellator, FontStash and
// graphics-driver services. Their context belongs to the caller. No native
// address is executed by this implementation.
struct FontDependencies {
    void *context;
    void *(*resize)(void *, void *, std::uint64_t);
    void (*copy)(void *, void *, const void *, std::uint64_t);
    std::uint64_t (*length)(void *, const char *);
    void (*flattenPaths)(void *, std::uint8_t *);
    void (*expandFill)(void *, std::uint8_t *, float);
    void (*renderFill)(void *, std::uint64_t target, std::uint64_t user,
        const void *paint, const void *composite, const void *scissor,
        float fringe, const void *bounds, const void *paths, std::int32_t count);
    float (*fontBounds)(void *, std::uint8_t *font, float, float,
        const char *, const char *, float *);
    void (*fontLineBounds)(void *, std::uint8_t *font, float, float *, float *);
    void (*fontIteratorInit)(void *, std::uint8_t *font, void *iterator,
        float, float, const char *, const char *, std::int32_t bitmapRequired);
    std::int32_t (*fontIteratorNext)(void *, std::uint8_t *, void *, void *quad);
    std::int32_t (*allocateTextAtlas)(void *, std::uint8_t *canvas);
    void (*updateTexture)(void *, std::uint64_t target, std::uint64_t user,
        std::int32_t texture, std::int32_t x, std::int32_t y,
        std::int32_t width, std::int32_t height, const void *pixels);
    void (*renderText)(void *, std::uint64_t target, std::uint64_t user,
        const void *paint, const void *composite, const void *scissor,
        const void *vertices, std::int32_t count, float fringe);
    void (*expandStroke)(void *, std::uint8_t *, float halfWidth, float fringe,
        std::uint32_t cap, std::uint32_t join, float miterLimit);
    void (*renderStroke)(void *, std::uint64_t target, std::uint64_t user,
        const void *paint, const void *composite, const void *scissor,
        float fringe, float width, const void *paths, std::int32_t count);
};
// The native canvas selects a 0x110-byte drawing state through its signed index
// at 0x2288. These APIs use caller-owned canvas storage and captured constants.
void setStrokeWidth_74a60(std::uint8_t *canvas, float width);
void setGlobalAlpha_74a60(std::uint8_t *canvas, float alpha);
void setFillColor_74ef0(std::uint8_t *canvas, const void *rgba,
    const std::uint8_t *constantImage);
void beginPath_75bc0(std::uint8_t *canvas);
void setFontSize_79610(std::uint8_t *canvas, float size);
void setFontBlur_79630(std::uint8_t *canvas, float blur);
void setLetterSpacing_79650(std::uint8_t *canvas, float spacing);
void setLineHeight_79670(std::uint8_t *canvas, float height);
void setTextAlignment_79690(std::uint8_t *canvas, std::uint32_t alignment);
void setFontIndex_796b0(std::uint8_t *canvas, std::uint32_t index);
void appendCommands_75c30(std::uint8_t *canvas, float *commands,
    std::uint32_t count, const FontDependencies &);
void roundedRectVarying_76a10(std::uint8_t *, float x, float y,
    float width, float height, float topLeft, float topRight,
    float bottomRight, float bottomLeft, const std::uint8_t *constantImage,
    const FontDependencies &);
void fill_77210(std::uint8_t *, const FontDependencies &);
void stroke_77f80(std::uint8_t *,const std::uint8_t *constantImage,
    const FontDependencies &);
void ellipse_76de0(std::uint8_t *,float,float,float,float,
    const std::uint8_t *constantImage,const FontDependencies &);
void circle_76f40(std::uint8_t *,float,float,float,
    const std::uint8_t *constantImage,const FontDependencies &);
void *linearGradient_75340(void *out,float startX,float startY,
    float endX,float endY,const void *innerColor,const void *outerColor,
    const std::uint8_t *constantImage);
float text_79770(std::uint8_t *, float x, float y, const char *text,
    const char *end, const std::uint8_t *constantImage, const FontDependencies &);
float textBounds_7ae90(std::uint8_t *, float x, float y, const char *text,
    const char *end, float *bounds, const std::uint8_t *constantImage,
    const FontDependencies &);
}
#endif // SLINKY_SHARE_ED5F8680BCDFFCC28C6E
