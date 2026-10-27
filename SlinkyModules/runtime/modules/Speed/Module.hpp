#ifndef SLINKY_SHARE_EF7C851CF0AEC8782522
#define SLINKY_SHARE_EF7C851CF0AEC8782522
#include "../../native/verified/module_surface.hpp"
#include "../../shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_speed_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                   const BoundSurfaceUiDependencies *);
extern "C" void recovered_speed_settings(SettingsContext *, std::uint8_t *,
                                         const SurfaceSettingsDependencies *);

namespace reconstruction::speed {
// The image view retains native storage offsets. It does not invent initialization.

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_speed_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_speed_settings(context, stateImage, &deps);
}
} // namespace reconstruction::speed

namespace reconstruction::speed::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t speed = 0x2f6338 + offsetof(NumberSetting, current);
inline constexpr std::size_t require_ground = 0x2f6318 + offsetof(BooleanSetting, current);
} // namespace reconstruction::speed::setting_offset
#endif // SLINKY_SHARE_EF7C851CF0AEC8782522
