#ifndef SLINKY_SHARE_4AD7110C6FF4A92F0A61
#define SLINKY_SHARE_4AD7110C6FF4A92F0A61
#include "../../shared/RenderNativeBindings.hpp"
#include "../../native/verified/module_surface.hpp"
#include "../../shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_trajectories_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                          const BoundSurfaceUiDependencies *);
extern "C" void recovered_trajectories_settings(SettingsContext *, std::uint8_t *,
                                                const SurfaceSettingsDependencies *);

namespace reconstruction::trajectories {
// The image view retains native storage offsets. It does not invent initialization.
using Endpoint5 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
using Endpoint8 = reconstruction::native_binding::RenderEndpoint<7, std::uint64_t>;
__declspec(dllexport) void computeLaunch(uint8_t *ctx, double *input, uint64_t angle, float fraction,
                                         double *position, double *velocity, uint8_t *image, Endpoint5 call);
__declspec(dllexport) void onLifecycleEvent(uint8_t *event, uint8_t *image, Endpoint5 call);
__declspec(dllexport) void renderTrajectory(uint8_t *event, uint8_t *image, Endpoint5 call);
__declspec(dllexport) void updateTrajectory(uint8_t *event, uint8_t *image, Endpoint8 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_trajectories_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_trajectories_settings(context, stateImage, &deps);
}
} // namespace reconstruction::trajectories

namespace reconstruction::trajectories::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t line_width = 0x2f4000 + offsetof(NumberSetting, current);
inline constexpr std::size_t color_hit = 0x2f4038 + offsetof(ColorSetting, current);
inline constexpr std::size_t color_miss = 0x2f4058 + offsetof(ColorSetting, current);
inline constexpr std::size_t render_throwables = 0x2f40d8 + offsetof(BooleanSetting, current);
inline constexpr std::size_t render_pearls = 0x2f40b8 + offsetof(BooleanSetting, current);
inline constexpr std::size_t render_bow = 0x2f4078 + offsetof(BooleanSetting, current);
inline constexpr std::size_t render_uncharged_bow = 0x2f4098 + offsetof(BooleanSetting, current);
} // namespace reconstruction::trajectories::setting_offset
#endif // SLINKY_SHARE_4AD7110C6FF4A92F0A61
