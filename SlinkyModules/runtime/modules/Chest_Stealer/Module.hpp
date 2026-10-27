#ifndef SLINKY_SHARE_9C1223725D6759AC62FE
#define SLINKY_SHARE_9C1223725D6759AC62FE
#include "../../shared/RenderNativeBindings.hpp"
#include "../../native/verified/module_random.hpp"
#include "../../native/verified/module_surface.hpp"
#include "../../shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_chest_stealer_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                           const BoundSurfaceUiDependencies *);
extern "C" void recovered_chest_stealer_settings(SettingsContext *, std::uint8_t *,
                                                 const SurfaceSettingsDependencies *);

namespace reconstruction::chest_stealer {
// The image view retains native storage offsets. It does not invent initialization.

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_chest_stealer_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_chest_stealer_settings(context, stateImage, &deps);
}
} // namespace reconstruction::chest_stealer

namespace reconstruction::chest_stealer {
using Endpoint5 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
std::uint32_t compareTitle(std::uint8_t *, std::uint64_t, const char *, Endpoint5);
std::uint64_t updateOpenDelay(std::uint8_t *, std::uint8_t *, RandomState *, const RandomConstants *,
                              Endpoint5);
} // namespace reconstruction::chest_stealer

namespace reconstruction::chest_stealer::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t delay_after_open = 0x2f5498 + offsetof(NumberSetting, current);
inline constexpr std::size_t delay_before_close = 0x2f54f0 + offsetof(NumberSetting, current);
inline constexpr std::size_t speed = 0x2f5528 + offsetof(NumberSetting, current);
inline constexpr std::size_t smart_speed = 0x2f5560 + offsetof(BooleanSetting, current);
inline constexpr std::size_t require_vanilla_title = 0x2f54d0 + offsetof(BooleanSetting, current);
} // namespace reconstruction::chest_stealer::setting_offset
#endif // SLINKY_SHARE_9C1223725D6759AC62FE
