#ifndef SLINKY_SHARE_E052C0F182C0905C1C1A
#define SLINKY_SHARE_E052C0F182C0905C1C1A
#include <cstdint>
#include "../../shared/RenderNativeBindings.hpp"
namespace reconstruction::gui {
struct QueryDependencies {
    void (*protectedStateOperation)(std::uint8_t *);             // 0x129b0, protected provider
    native_binding::RenderEndpoint<4> native; // concrete shared input/registry bindings
};
void invokeProtectedStateOperation(std::uint8_t *stateImage, const QueryDependencies &);
std::uint8_t queryInteractionFlag(const std::uint8_t *stateImage);
float queryScale(const std::uint8_t *stateImage);
float *copyAccentColor(float *output, const std::uint8_t *stateImage);
std::uint64_t dispatchInput(std::uint8_t *input, std::uint8_t modifier, std::uintptr_t registry,
                            std::uint8_t *stateImage, const QueryDependencies &);
std::uint64_t openFromEvent(const std::uint8_t *event, std::uint8_t *stateImage, const QueryDependencies &);
} // namespace reconstruction::gui
#endif // SLINKY_SHARE_E052C0F182C0905C1C1A
