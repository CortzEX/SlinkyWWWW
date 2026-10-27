#ifndef SLINKY_SHARE_17A8079A15A2E1AF7F61
#define SLINKY_SHARE_17A8079A15A2E1AF7F61
#include "../../shared/RenderNativeBindings.hpp"
#include "../../native/verified/module_surface.hpp"
#include "../../shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_pointers_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                      const BoundSurfaceUiDependencies *);
extern "C" void recovered_pointers_settings(SettingsContext *, std::uint8_t *,
                                            const SurfaceSettingsDependencies *);

namespace reconstruction::pointers {
// The image view retains native storage offsets. It does not invent initialization.
using Endpoint5 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
using Dependency5 = reconstruction::native_binding::RenderEndpoint<4, std::uint32_t>;
__declspec(dllexport) uint32_t compareDistance(const uint8_t *a, const uint8_t *b);
__declspec(dllexport) void updatePointers(uint8_t *event, uint8_t *image, Endpoint5 call);
__declspec(dllexport) void renderPointers(uint8_t *event, uint8_t *image, Endpoint5 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_pointers_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_pointers_settings(context, stateImage, &deps);
}
} // namespace reconstruction::pointers

namespace reconstruction::pointers {
void writeStatus(char *, std::uint8_t *, Endpoint5);
struct PointerRecord {
    double x, z, previousX, previousZ;
    float red, green, blue, previousDistance, distance;
    std::uint32_t padding;
};
static_assert(sizeof(PointerRecord) == 56);
} // namespace reconstruction::pointers

namespace reconstruction::pointers::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t range = 0x2f0a98 + offsetof(NumberSetting, current);
inline constexpr std::size_t ignore_fov = 0x2f0ad0 + offsetof(NumberSetting, current);
inline constexpr std::size_t hide_friendlies = 0x2f0b48 + offsetof(BooleanSetting, current);
inline constexpr std::size_t style = 0x2f09e0 + offsetof(ChoiceSetting, current);
inline constexpr std::size_t color_mode = 0x2f0a58 + offsetof(ChoiceSetting, current);
inline constexpr std::size_t color_near = 0x2f0990 + offsetof(ColorSetting, current);
inline constexpr std::size_t color_far = 0x2f09b0 + offsetof(ColorSetting, current);
inline constexpr std::size_t color_enemies = 0x2f0b28 + offsetof(ColorSetting, current);
inline constexpr std::size_t color_friendlies = 0x2f0b08 + offsetof(ColorSetting, current);
inline constexpr std::size_t scale = 0x2f0920 + offsetof(NumberSetting, current);
inline constexpr std::size_t radius = 0x2f0958 + offsetof(NumberSetting, current);
inline constexpr std::size_t scale_radius = 0x2f0a20 + offsetof(BooleanSetting, current);
} // namespace reconstruction::pointers::setting_offset
#endif // SLINKY_SHARE_17A8079A15A2E1AF7F61
