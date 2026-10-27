#ifndef SLINKY_SHARE_CBE3E7D241B08AACE211
#define SLINKY_SHARE_CBE3E7D241B08AACE211
#include "../../shared/RenderNativeBindings.hpp"
#include "../../native/verified/module_esp_lists.hpp"
#include "../../native/verified/module_surface.hpp"
#include "../../shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_item_esp_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                      const BoundSurfaceUiDependencies *);
extern "C" void recovered_item_esp_settings(SettingsContext *, std::uint8_t *,
                                            const SurfaceSettingsDependencies *);

namespace reconstruction::item_esp {
// The image view retains native storage offsets. It does not invent initialization.
using Endpoint8 = reconstruction::native_binding::RenderEndpoint<7, std::uint64_t>;
using Endpoint5 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
__declspec(dllexport) void onLifecycleEvent(uint8_t *event, uint8_t *image, Endpoint8 call);
__declspec(dllexport) void renderItems(uint8_t *event, uint8_t *image, Endpoint8 call);
__declspec(dllexport) int32_t compareItemIdentifier(const int32_t *left, const uint8_t *right);
__declspec(dllexport) void updateItems(uint8_t *event, uint8_t *image, Endpoint8 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_item_esp_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_item_esp_settings(context, stateImage, &deps);
}
} // namespace reconstruction::item_esp

namespace reconstruction::item_esp {
void releaseBuffer(std::uint8_t *, Endpoint5);
void appendCatalogCharacter(char *, std::uint8_t, Endpoint5);
} // namespace reconstruction::item_esp

namespace reconstruction::item_esp::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t range = 0x2f1cb0 + offsetof(NumberSetting, current);
inline constexpr std::size_t show_count = 0x2f1c90 + offsetof(BooleanSetting, current);
inline constexpr std::size_t highlight_all = 0x2f1d08 + offsetof(BooleanSetting, current);
inline constexpr std::size_t default_color = 0x2f1ce8 + offsetof(ColorSetting, current);
} // namespace reconstruction::item_esp::setting_offset
#endif // SLINKY_SHARE_CBE3E7D241B08AACE211
