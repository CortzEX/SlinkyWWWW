#ifndef SLINKY_SHARE_4C553FE55778379850D1
#define SLINKY_SHARE_4C553FE55778379850D1
#include "../../shared/RenderNativeBindings.hpp"
#include "../../native/verified/module_surface.hpp"
#include "../../shared/Geometry.hpp"
#include "../../shared/ModOverlayCharacterBindings.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_mod_overlay_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                         const BoundSurfaceUiDependencies *);
extern "C" void recovered_mod_overlay_settings(SettingsContext *, std::uint8_t *,
                                               const SurfaceSettingsDependencies *);

typedef uintptr_t up;
struct ModOverlayDependencies {
    reconstruction::native_binding::RenderEndpoint<4> native;
    up character_provider;
    void *user;
    // Retained character callback fields are compatibility data. The canonical
    // append/collect bodies use their four proved decoded-cell contracts.
    uint8_t (*character)(void *, up provider, int32_t character);
    void (*dynamic)(void *, up callback, up destination);
    // Partial views borrow the shared cell used by all four character contracts.
    const std::uint8_t *nameEncodedCell_32ecfb = nullptr;
};

namespace reconstruction::mod_overlay {
// The image view retains native storage offsets. It does not invent initialization.
using Endpoint10 = reconstruction::native_binding::RenderEndpoint<9, std::uint64_t>;
__declspec(dllexport) void onSettingChanged(uint8_t *ev, uint8_t *im, const ModOverlayDependencies *d);
__declspec(dllexport) void onModuleStateChanged(uint8_t *ev, uint8_t *im, const ModOverlayDependencies *d);
__declspec(dllexport) void onStatusEvent(uint8_t *ev, uint8_t *im, const ModOverlayDependencies *d);
__declspec(dllexport) void onControlEvent(uint8_t *ev, uint8_t *im, const ModOverlayDependencies *d);
__declspec(dllexport) void collectModules(uint8_t *ev, uint8_t *im, const ModOverlayDependencies *d);
__declspec(dllexport) uint64_t compareWidth(const uint8_t *a, const uint8_t *b, Endpoint10 call);
__declspec(dllexport) void renderOverlay(uint8_t *event, uint8_t *image, Endpoint10 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &ModOverlayDependencies) {
    recovered_mod_overlay_bound_ui(ui, layout, stateImage, &ModOverlayDependencies);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &ModOverlayDependencies) {
    recovered_mod_overlay_settings(context, stateImage, &ModOverlayDependencies);
}
} // namespace reconstruction::mod_overlay

namespace reconstruction::mod_overlay {
void appendModule(std::uintptr_t, std::uint8_t *, const ModOverlayDependencies *);
void refreshVisibleModules(const std::uint8_t *, std::uint8_t *, const ModOverlayDependencies *);
struct OverlayRecord {
    std::uintptr_t descriptor;
    char name[20], status[32];
    float width, height, progress;
    std::uint8_t enabled, padding[7];
};
static_assert(sizeof(OverlayRecord) == 80);
static_assert(offsetof(OverlayRecord, progress) == 0x44);
} // namespace reconstruction::mod_overlay

namespace reconstruction::mod_overlay::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t show_combat = 0x2ed100 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_move = 0x2ed120 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_block = 0x2ed140 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_visual = 0x2ed160 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_utility = 0x2ed180 + offsetof(BooleanSetting, current);
inline constexpr std::size_t text_size = 0x2ed200 + offsetof(NumberSetting, current);
inline constexpr std::size_t padding_x = 0x2ed2b0 + offsetof(NumberSetting, current);
inline constexpr std::size_t padding_y = 0x2ed2e8 + offsetof(NumberSetting, current);
inline constexpr std::size_t bg_rounding = 0x2ed278 + offsetof(NumberSetting, current);
inline constexpr std::size_t name_color = 0x2ed238 + offsetof(ColorSetting, current);
inline constexpr std::size_t details_color = 0x2ed258 + offsetof(ColorSetting, current);
inline constexpr std::size_t lowercase = 0x2ed1c0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_details = 0x2ed1e0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t require_bound = 0x2ed1a0 + offsetof(BooleanSetting, current);
} // namespace reconstruction::mod_overlay::setting_offset
#endif // SLINKY_SHARE_4C553FE55778379850D1
