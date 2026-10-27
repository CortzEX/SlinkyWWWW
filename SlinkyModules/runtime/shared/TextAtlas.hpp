#ifndef SLINKY_SHARE_41CFEE0A2AE4CA467629
#define SLINKY_SHARE_41CFEE0A2AE4CA467629
#include "WordInvoker.hpp"
namespace reconstruction::drawing {
struct TextAtlasDependencies {
    const std::uint8_t *image;
    RecoveredFrameInvoker calls;
    // Native callback output slots may retain incoming stack bytes when a
    // provider does not write them. They are caller-owned frame observations.
    std::uint32_t incomingQueryWidth;
    std::uint32_t incomingQueryHeight;
    std::uint32_t incomingResetX;
    std::uint32_t incomingResetY;
};
std::uint32_t allocateTextAtlas_79eb0(std::uint8_t *canvas,const TextAtlasDependencies &);
std::uint32_t resetTextAtlas_6f380(std::uint8_t *font,std::uint32_t width,
    std::uint32_t height,const TextAtlasDependencies &);
}
#endif // SLINKY_SHARE_41CFEE0A2AE4CA467629
