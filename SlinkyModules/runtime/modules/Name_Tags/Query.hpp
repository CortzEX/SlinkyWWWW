#ifndef SLINKY_SHARE_EEF8D7E7D514BABCDCC5
#define SLINKY_SHARE_EEF8D7E7D514BABCDCC5
#include "../../shared/RenderNativeBindings.hpp"
#include "../../native/verified/module_game_access.hpp"
namespace reconstruction::name_tags {
using VisibilityEndpoint = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
std::uint64_t queryNameTagValue(GameAccessBridge *, std::uintptr_t object, std::uintptr_t entity,
                                const std::uint8_t *stateImage, VisibilityEndpoint);
} // namespace reconstruction::name_tags
#endif // SLINKY_SHARE_EEF8D7E7D514BABCDCC5
