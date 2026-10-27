#ifndef SLINKY_SHARE_4ED77CFCEC2AE7FF24D7
#define SLINKY_SHARE_4ED77CFCEC2AE7FF24D7
#include "FontRuntime.hpp"
#include <cstdint>

namespace reconstruction::ui {
struct UiDependencies {
    void *context;
    std::uint64_t (*length)(void *, const char *);
    void (*release)(void *, void *);
    // Target is a callback pointer read from caller-owned state, not an RVA
    // resolver. The three payloads preserve each callback's register arguments.
    std::uint64_t (*invoke)(void *, std::uint64_t target,
        std::uint64_t first, std::uint64_t second, std::uint64_t third);
};
void selectFont_10340(std::uint8_t *ui, std::uint32_t style);
float *nextColumnRect_10860(float *out, std::uint8_t *ui, float height,
    const std::uint8_t *image);
void fillRoundedRect_10a60(std::uint8_t *ui, const float *rect, float radius,
    const std::uint8_t *image, const drawing::FontDependencies &);
void strokeRoundedRect_10b00(std::uint8_t *ui, const float *rect, float radius,
    const std::uint8_t *image, const drawing::FontDependencies &);
float drawAlignedText_10cb0(std::uint8_t *ui, const float *rect,
    std::uint32_t alignment, std::uint32_t style, const char *text,
    const std::uint8_t *image, const drawing::FontDependencies &);
std::uint8_t processInput_10f30(std::uint8_t *state, const std::uint8_t *event,
    std::uint8_t *image, const UiDependencies &);
std::uint64_t processInputWord_10f30(std::uint8_t *state,
    const std::uint8_t *event, std::uint8_t *image,
    std::uint64_t incomingRsi, const UiDependencies &);
void finishModal_169c0(std::uint8_t *state, std::uint8_t apply,
    std::uint8_t *image, const UiDependencies &);
void resetModal_165f0(std::uint8_t *state, std::uint8_t *image,
    const UiDependencies &);
}
#endif // SLINKY_SHARE_4ED77CFCEC2AE7FF24D7
