#ifndef SLINKY_SHARE_670B4CCAE109C3968423
#define SLINKY_SHARE_670B4CCAE109C3968423
#include "FontTables.hpp"
#include <cstddef>
#include <cstdint>

namespace reconstruction::fontcff {
// Borrowed native CFF byte span. Reads consume available bytes; exhausted reads
// return zero without advancing the cursor.
struct Buffer { std::uint8_t *data; std::int32_t cursor, size; };
static_assert(sizeof(Buffer) == 16 && offsetof(Buffer, cursor) == 8);
struct CffContext {
    std::int32_t bounds, started;
    float firstX, firstY, currentX, currentY;
    std::int32_t minX, maxX, minY, maxY;
    fonttables::Vertex *vertices;
    std::int32_t count, padding;
};
static_assert(sizeof(CffContext) == 56 && offsetof(CffContext, vertices) == 40);

std::int32_t runCharString_7b3b0(std::uint8_t *font,
    std::int32_t glyph, CffContext *context);
Buffer *indexElement_7c5d0(Buffer *output, Buffer *index, std::int32_t element);
void relativeMove_7c800(CffContext *, float dx, float dy);
void relativeCurve_7c8e0(CffContext *, float dx1, float dy1,
    float dx2, float dy2, float dx3, float dy3);
void closeShape_7ca90(CffContext *);
std::uint32_t readInteger_7cb60(Buffer *);
Buffer *privateSubroutines_7ccb0(Buffer *output, Buffer *cff, Buffer *dictionary);
void dictionaryIntegers_7cd90(Buffer *, std::int32_t key,
    std::int32_t count, std::uint32_t *output);
Buffer *readIndex_7cf40(Buffer *output, Buffer *input);
}
#endif // SLINKY_SHARE_670B4CCAE109C3968423
