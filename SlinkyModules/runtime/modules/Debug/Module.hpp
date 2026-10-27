#ifndef SLINKY_SHARE_24A89DD564A8E5FA98AD
#define SLINKY_SHARE_24A89DD564A8E5FA98AD
#include "../../shared/RenderNativeBindings.hpp"
#include "../../native/verified/module_surface.hpp"
#include "../../shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_debug_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                   const BoundSurfaceUiDependencies *);
extern "C" void recovered_debug_settings(SettingsContext *, std::uint8_t *,
                                         const SurfaceSettingsDependencies *);

namespace reconstruction::debug {
// The image view retains native storage offsets. It does not invent initialization.
using Dependency8 = reconstruction::native_binding::RenderEndpoint<7, std::uint32_t>;
__declspec(dllexport) void onMovement(uint8_t *event, uint8_t *image, Dependency8 call);
__declspec(dllexport) void onRender(uint8_t *event, uint8_t *image, Dependency8 call);
__declspec(dllexport) void onPosition(uint8_t *event, uint8_t *image, Dependency8 call);
__declspec(dllexport) void onPacket(uint8_t *event, uint8_t *image, Dependency8 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_debug_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_debug_settings(context, stateImage, &deps);
}
} // namespace reconstruction::debug

namespace reconstruction::debug::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t clicks = 0x2f4680 + offsetof(BooleanSetting, current);
inline constexpr std::size_t hurt_time = 0x2f4640 + offsetof(BooleanSetting, current);
inline constexpr std::size_t item_use_state = 0x2f4660 + offsetof(BooleanSetting, current);
} // namespace reconstruction::debug::setting_offset
#endif // SLINKY_SHARE_24A89DD564A8E5FA98AD
