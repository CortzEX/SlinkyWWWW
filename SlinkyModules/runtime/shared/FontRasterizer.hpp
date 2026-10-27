#ifndef SLINKY_SHARE_A0EA71278A57004D5A0B
#define SLINKY_SHARE_A0EA71278A57004D5A0B
#include "WordInvoker.hpp"
#include "FontTables.hpp"
#include <cstddef>
#include <cstdint>

namespace reconstruction::font {
using Vertex=fonttables::Vertex;
struct Point { float x,y; };
struct Edge { float x0,y0,x1,y1; std::int32_t direction; };
static_assert(sizeof(Point)==8 && sizeof(Edge)==20);
struct Bitmap {
    std::int32_t width,height,stride;
    std::uint32_t padding;
    std::uint8_t *pixels;
};
static_assert(sizeof(Bitmap)==24 && offsetof(Bitmap,pixels)==16);
struct RasterDependencies {
    void *context;
    const std::uint8_t *image;
    RecoveredFrameInvoker calls;
    std::int32_t (*getGlyphShape_62bb0)(void*,std::uint8_t*,std::int32_t,Vertex**);
    std::int32_t (*getGlyphBox_63cf0)(void*,std::uint8_t*,std::int32_t,
        std::int32_t*,std::int32_t*,std::int32_t*,std::int32_t*);
    // This is incoming frame storage, not an inferred source initializer.
    Vertex *incomingShapePointer;
};
void flattenQuadratic_7d1d0(Point*,std::int32_t*,float x0,float y0,
    float x1,float y1,float x2,float y2,float flatnessSquared,
    std::int32_t depth,const std::uint8_t *image);
void flattenCubic_7d3b0(Point*,std::int32_t*,float x0,float y0,
    float x1,float y1,float x2,float y2,float x3,float y3,
    float flatnessSquared,std::int32_t depth,const std::uint8_t *image);
// Native7D720 is the quick-sort pass; the small insertion pass is in64E50.
void sortEdges_7d720(Edge*,std::int32_t count);
void rasterize_64e50(Bitmap*,float flatness,Vertex*,std::int32_t vertexCount,
    float scaleX,float scaleY,float shiftX,float shiftY,std::int32_t offsetX,
    std::int32_t offsetY,std::int32_t invert,std::uint8_t *scratchOwner,
    const RasterDependencies&);
void makeGlyphBitmap_66f00(std::uint8_t *font,std::uint8_t *output,
    std::int32_t width,std::int32_t height,std::int32_t stride,
    float scaleX,float scaleY,float shiftX,float shiftY,std::int32_t glyph,
    const RasterDependencies&);
}
#endif // SLINKY_SHARE_A0EA71278A57004D5A0B
