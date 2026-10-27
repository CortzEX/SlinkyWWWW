#ifndef SLINKY_SHARE_B2CC0D86B1B4634E023A
#define SLINKY_SHARE_B2CC0D86B1B4634E023A
#include "../../shared/RenderNativeBindings.hpp"
#include "../../native/verified/module_surface.hpp"
#include "../../shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_player_esp_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                        const BoundSurfaceUiDependencies *);
extern "C" void recovered_player_esp_settings(SettingsContext *, std::uint8_t *,
                                              const SurfaceSettingsDependencies *);

namespace reconstruction::player_esp {
// The image view retains native storage offsets. It does not invent initialization.
using Endpoint5 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
__declspec(dllexport) void renderScreen(uint8_t *event, uint8_t *image, Endpoint5 call);
__declspec(dllexport) uint64_t drawHealthBar(uint8_t *row, float x, float lower, float upper, uint8_t *image,
                                             Endpoint5 call);
__declspec(dllexport) void renderWorld(uint8_t *event, uint8_t *image, Endpoint5 call);
__declspec(dllexport) uint32_t compareDistance(const uint8_t *a, const uint8_t *b);
__declspec(dllexport) void updatePlayers(uint8_t *event, uint8_t *image, Endpoint5 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_player_esp_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_player_esp_settings(context, stateImage, &deps);
}
} // namespace reconstruction::player_esp

namespace reconstruction::player_esp {
void writeStatus(char *, std::uint8_t *, Endpoint5);
struct PlayerRecord {
    double previous[3], position[3];
    float red, green, blue, distanceSquared;
    std::int32_t hurtTime;
    float healthFraction, absorptionFraction;
    std::uint8_t highlighted, padding[3];
};
static_assert(sizeof(PlayerRecord) == 80);
static_assert(offsetof(PlayerRecord, hurtTime) == 0x40);
} // namespace reconstruction::player_esp

namespace reconstruction::player_esp::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t mode = 0x2ea0e0 + offsetof(ChoiceSetting, current);
inline constexpr std::size_t range = 0x2ea1a0 + offsetof(NumberSetting, current);
inline constexpr std::size_t hide_friendlies = 0x2ea238 + offsetof(BooleanSetting, current);
inline constexpr std::size_t color_mode = 0x2ea290 + offsetof(ChoiceSetting, current);
inline constexpr std::size_t color_enemies = 0x2ea218 + offsetof(ColorSetting, current);
inline constexpr std::size_t color_friendlies = 0x2ea1f8 + offsetof(ColorSetting, current);
inline constexpr std::size_t override_target_color = 0x2ea258 + offsetof(BooleanSetting, current);
inline constexpr std::size_t color_target = 0x2ea1d8 + offsetof(ColorSetting, current);
inline constexpr std::size_t line_width = 0x2ea090 + offsetof(NumberSetting, current);
inline constexpr std::size_t hurt_effect = 0x2ea140 + offsetof(BooleanSetting, current);
inline constexpr std::size_t filled = 0x2ea160 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_2d_box = 0x2ea120 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_health_bar = 0x2ea180 + offsetof(BooleanSetting, current);
} // namespace reconstruction::player_esp::setting_offset
#endif // SLINKY_SHARE_B2CC0D86B1B4634E023A
