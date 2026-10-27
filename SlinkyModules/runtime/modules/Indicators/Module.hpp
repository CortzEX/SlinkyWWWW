#ifndef SLINKY_SHARE_CFCC88DE759038EAF664
#define SLINKY_SHARE_CFCC88DE759038EAF664
#include "../../shared/RenderNativeBindings.hpp"
#include "../../native/verified/module_surface.hpp"
#include "../../shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_indicators_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                        const BoundSurfaceUiDependencies *);
extern "C" void recovered_indicators_settings(SettingsContext *, std::uint8_t *,
                                              const SurfaceSettingsDependencies *);

namespace reconstruction::indicators {
// The image view retains native storage offsets. It does not invent initialization.
using Endpoint8 = reconstruction::native_binding::RenderEndpoint<7, std::uint64_t>;
using Endpoint5 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
using Dependency5 = reconstruction::native_binding::RenderEndpoint<4, std::uint32_t>;
__declspec(dllexport) void onLifecycleEvent(uint8_t *event, uint8_t *image, Endpoint8 call);
__declspec(dllexport) void renderIndicators(uint8_t *event, uint8_t *image, Endpoint8 call);
__declspec(dllexport) void updateIndicators(uint8_t *event, uint8_t *image, Endpoint8 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_indicators_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_indicators_settings(context, stateImage, &deps);
}
} // namespace reconstruction::indicators

namespace reconstruction::indicators::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t scale = 0x2f1650 + offsetof(NumberSetting, current);
inline constexpr std::size_t radius = 0x2f1688 + offsetof(NumberSetting, current);
inline constexpr std::size_t show_arrow = 0x2f16c0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_fireball = 0x2f16e0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_pearl = 0x2f1700 + offsetof(BooleanSetting, current);
inline constexpr std::size_t require_coming_closer = 0x2f1720 + offsetof(BooleanSetting, current);
} // namespace reconstruction::indicators::setting_offset
#endif // SLINKY_SHARE_CFCC88DE759038EAF664
