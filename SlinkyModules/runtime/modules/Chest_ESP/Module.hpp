#ifndef SLINKY_SHARE_C4F9682BDF5AA0E100B0
#define SLINKY_SHARE_C4F9682BDF5AA0E100B0
#include "../../shared/RenderNativeBindings.hpp"
#include "../../native/verified/module_surface.hpp"
#include "../../shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_chest_esp_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                       const BoundSurfaceUiDependencies *);
extern "C" void recovered_chest_esp_settings(SettingsContext *, std::uint8_t *,
                                             const SurfaceSettingsDependencies *);

namespace reconstruction::chest_esp {
// The image view retains native storage offsets. It does not invent initialization.
using Endpoint5 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
__declspec(dllexport) void updateChests(uint8_t *event, uint8_t *image, Endpoint5 call);
__declspec(dllexport) void renderChests(uint8_t *event, uint8_t *image, Endpoint5 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_chest_esp_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_chest_esp_settings(context, stateImage, &deps);
}
} // namespace reconstruction::chest_esp

namespace reconstruction::chest_esp {
struct ChestRecord {
    double position[3];
    std::uint32_t blockId, padding;
};
static_assert(sizeof(ChestRecord) == 32);
} // namespace reconstruction::chest_esp

namespace reconstruction::chest_esp::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t range = 0x2ecb18 + offsetof(NumberSetting, current);
inline constexpr std::size_t render_chest = 0x2ecb50 + offsetof(BooleanSetting, current);
inline constexpr std::size_t render_ender_chest = 0x2ecb70 + offsetof(BooleanSetting, current);
inline constexpr std::size_t render_trapped_chest = 0x2ecb90 + offsetof(BooleanSetting, current);
inline constexpr std::size_t render_beacon = 0x2ecbb0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t line_width = 0x2ecbd0 + offsetof(NumberSetting, current);
inline constexpr std::size_t color_chest = 0x2ecc68 + offsetof(ColorSetting, current);
inline constexpr std::size_t color_ender_chest = 0x2ecc08 + offsetof(ColorSetting, current);
inline constexpr std::size_t color_trapped_chest = 0x2ecc28 + offsetof(ColorSetting, current);
inline constexpr std::size_t color_beacon = 0x2ecc48 + offsetof(ColorSetting, current);
inline constexpr std::size_t filled = 0x2ecc88 + offsetof(BooleanSetting, current);
} // namespace reconstruction::chest_esp::setting_offset
#endif // SLINKY_SHARE_C4F9682BDF5AA0E100B0
