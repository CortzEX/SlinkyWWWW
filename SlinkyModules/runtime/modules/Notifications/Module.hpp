#ifndef SLINKY_SHARE_EC6E6112877731F26D17
#define SLINKY_SHARE_EC6E6112877731F26D17
#include "../../shared/RenderNativeBindings.hpp"
#include "../../native/verified/module_surface.hpp"
#include "../../shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_notifications_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                           const BoundSurfaceUiDependencies *);
extern "C" void recovered_notifications_settings(SettingsContext *, std::uint8_t *,
                                                 const SurfaceSettingsDependencies *);

namespace reconstruction::notifications {
// The image view retains native storage offsets. It does not invent initialization.
using Endpoint6 = reconstruction::native_binding::RenderEndpoint<5, std::uint64_t>;
using Endpoint7 = reconstruction::native_binding::RenderEndpoint<6, std::uint64_t>;
__declspec(dllexport) void onModuleStateChanged(uint8_t *event, uint8_t *image, Endpoint6 call);
__declspec(dllexport) void advanceMessages(uint8_t *event, uint8_t *image, Endpoint6 call);
__declspec(dllexport) void onConfigAction(uint8_t *event, uint8_t *image, Endpoint6 call);
__declspec(dllexport) void onMessage(uint8_t *event, uint8_t *image, Endpoint6 call);
__declspec(dllexport) void onFriendChanged(uint8_t *event, uint8_t *image, Endpoint6 call);
__declspec(dllexport) void renderMessages(uint8_t *event, uint8_t *image, Endpoint7 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_notifications_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_notifications_settings(context, stateImage, &deps);
}
} // namespace reconstruction::notifications

namespace reconstruction::notifications {
std::uint8_t clearHandshake(std::uint8_t *);
struct MessageRecord {
    std::uint32_t kind;
    char text[101];
    std::uint8_t padding[3];
    float age;
};
static_assert(sizeof(MessageRecord) == 112);
static_assert(offsetof(MessageRecord, age) == 0x6c);
} // namespace reconstruction::notifications

namespace reconstruction::notifications::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t hide_ingame = 0x2ed610 + offsetof(BooleanSetting, current);
inline constexpr std::size_t hide_hold_notifs = 0x2ed550 + offsetof(BooleanSetting, current);
inline constexpr std::size_t hide_bind_only = 0x2ed530 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_combat = 0x2ed570 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_move = 0x2ed590 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_block = 0x2ed5b0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_visual = 0x2ed5d0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_utility = 0x2ed5f0 + offsetof(BooleanSetting, current);
} // namespace reconstruction::notifications::setting_offset
#endif // SLINKY_SHARE_EC6E6112877731F26D17
