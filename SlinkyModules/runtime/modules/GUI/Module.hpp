#ifndef SLINKY_SHARE_568FBC576981B76E91CD
#define SLINKY_SHARE_568FBC576981B76E91CD
#include "../../shared/RenderNativeBindings.hpp"
#include "../../native/verified/module_surface.hpp"
#include "../../shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_gui_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *, const BoundSurfaceUiDependencies *);
extern "C" void recovered_gui_settings(SettingsContext *, std::uint8_t *,
                                       const SurfaceSettingsDependencies *);

namespace reconstruction::gui {
// The image view retains native storage offsets. It does not invent initialization.
using Dependency5 = reconstruction::native_binding::RenderEndpoint<4, std::uint32_t>;
__declspec(dllexport) void onRenderFrame(uint8_t *event, uint8_t *image, Dependency5 call);
__declspec(dllexport) void onInput(uint8_t *event, uint8_t *image, Dependency5 call);
__declspec(dllexport) void resetState(uint8_t *event, uint8_t *image, Dependency5 call);
__declspec(dllexport) void onModuleStateChanged(uint8_t *event, uint8_t *image, Dependency5 call);
__declspec(dllexport) void clearState(uint8_t *event, uint8_t *image, Dependency5 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_gui_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_gui_settings(context, stateImage, &deps);
}
} // namespace reconstruction::gui

namespace reconstruction::gui::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t scale = 0x2eb970 + offsetof(ChoiceSetting, current);
inline constexpr std::size_t accent_color = 0x2eb720 + offsetof(ColorSetting, current);
inline constexpr std::size_t allow_input = 0x2eb9b0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t compact = 0x2eb9d0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t wide = 0x2eb9f0 + offsetof(BooleanSetting, current);
} // namespace reconstruction::gui::setting_offset
#endif // SLINKY_SHARE_568FBC576981B76E91CD
