#ifndef SLINKY_SHARE_B99D0BD096E6751B2C1D
#define SLINKY_SHARE_B99D0BD096E6751B2C1D
#include "../../shared/RenderNativeBindings.hpp"
#include "../../native/verified/module_surface.hpp"
#include "../../shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_name_tags_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                       const BoundSurfaceUiDependencies *);
extern "C" void recovered_name_tags_settings(SettingsContext *, std::uint8_t *,
                                             const SurfaceSettingsDependencies *);

namespace reconstruction::name_tags {
// The image view retains native storage offsets. It does not invent initialization.
using Endpoint9 = reconstruction::native_binding::RenderEndpoint<8, std::uint64_t>;
using Endpoint5 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
__declspec(dllexport) void releaseTags(uint8_t *game, uint8_t *image, Endpoint9 call);
__declspec(dllexport) void onLifecycleEvent(uint8_t *event, uint8_t *image, Endpoint9 call);
__declspec(dllexport) void renderTags(uint8_t *event, uint8_t *image, Endpoint9 call);
__declspec(dllexport) int32_t compareDistance(const uint8_t *a, const uint8_t *b);
__declspec(dllexport) int32_t compareEnchantment(const uint8_t *a, const uint8_t *b, uint8_t *image);
__declspec(dllexport) void updateTags(uint8_t *event, uint8_t *image, Endpoint9 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_name_tags_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_name_tags_settings(context, stateImage, &deps);
}
} // namespace reconstruction::name_tags

namespace reconstruction::name_tags {
struct EquipmentRecord {
    std::uint8_t present, padding[3];
    std::uint32_t count;
    std::uintptr_t labels;
};
struct TagRecord {
    double previous[3], position[3];
    std::uintptr_t entity, label;
    std::uint32_t width;
    float previousDistance, distance;
    std::uint32_t equipmentCount;
    EquipmentRecord equipment[5];
};
static_assert(sizeof(TagRecord) == 160);
static_assert(offsetof(TagRecord, equipment) == 0x50);
} // namespace reconstruction::name_tags

namespace reconstruction::name_tags::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t range = 0x2f05b8 + offsetof(NumberSetting, current);
inline constexpr std::size_t scale = 0x2f04e0 + offsetof(NumberSetting, current);
inline constexpr std::size_t show_own_name_tag = 0x2f05f0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t use_display_name = 0x2f0610 + offsetof(BooleanSetting, current);
inline constexpr std::size_t distance_scaling = 0x2f0518 + offsetof(BooleanSetting, current);
inline constexpr std::size_t background = 0x2f0538 + offsetof(BooleanSetting, current);
inline constexpr std::size_t text_shadow = 0x2f0558 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_health = 0x2f0630 + offsetof(BooleanSetting, current);
inline constexpr std::size_t health_fmt = 0x2f0680 + offsetof(ChoiceSetting, current);
inline constexpr std::size_t show_distance = 0x2f0650 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_equipment = 0x2f0578 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_enchants = 0x2f0598 + offsetof(BooleanSetting, current);
} // namespace reconstruction::name_tags::setting_offset
#endif // SLINKY_SHARE_B99D0BD096E6751B2C1D
