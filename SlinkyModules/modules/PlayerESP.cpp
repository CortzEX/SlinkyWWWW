// Player ESP

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Player_ESP.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Player_ESP.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Player ESP: lib_win settings 0x2f8c0.
static constexpr SettingsStep settings_steps_Surface_Player_ESP[] = {
    {SettingsControl::choice, "mode", 0x2ea0e0},
    {SettingsControl::number, "range", 0x2ea1a0},
    {SettingsControl::boolean, "hide_friendlies", 0x2ea238},
    {SettingsControl::choice, "color_mode", 0x2ea290},
    {SettingsControl::color, "color_enemies", 0x2ea218},
    {SettingsControl::color, "color_friendlies", 0x2ea1f8},
    {SettingsControl::boolean, "override_target_color", 0x2ea258},
    {SettingsControl::color, "color_target", 0x2ea1d8},
    {SettingsControl::number, "line_width", 0x2ea090},
    {SettingsControl::boolean, "hurt_effect", 0x2ea140},
    {SettingsControl::boolean, "filled", 0x2ea160},
    {SettingsControl::boolean, "show_2d_box", 0x2ea120},
    {SettingsControl::boolean, "show_health_bar", 0x2ea180},
};
static constexpr ModuleSurface surface_Surface_Player_ESP{
    nullptr, 0, settings_steps_Surface_Player_ESP, std::size(settings_steps_Surface_Player_ESP)};

extern "C" __declspec(dllexport) void
recovered_player_esp_settings(SettingsContext *context, std::uint8_t *image,
                              const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Player_ESP, context, image, *dependencies);
}

// Player ESP: lib_win runtime UI 0x2f770.
extern "C" __declspec(dllexport) void
recovered_player_esp_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                        const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2ea1a0);
    dependencies->checkbox(layout, ui, image + 0x2ea238);
    dependencies->section(ui, layout, "Customization");
    dependencies->choice(layout, ui, image + 0x2ea0e0);
    dependencies->choice(layout, ui, image + 0x2ea290);
    if (read_surface_value<std::uint32_t>(image, 0x2ea2c0) == 1) {
        dependencies->color(layout, ui, image + 0x2ea218);
        if (image[0x2ea250] == 0) {
            dependencies->color(layout, ui, image + 0x2ea1f8);
        }
    }
    dependencies->checkbox(layout, ui, image + 0x2ea258);
    if (image[0x2ea270] == 1) {
        dependencies->color(layout, ui, image + 0x2ea1d8);
    }
    dependencies->number(layout, ui, image + 0x2ea090);
    dependencies->checkbox(layout, ui, image + 0x2ea120);
    if (image[0x2ea138] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2ea160);
        dependencies->checkbox(layout, ui, image + 0x2ea140);
    }
    dependencies->checkbox(layout, ui, image + 0x2ea180);
}
// END SOURCE native/verified/surfaces/Surface_Player_ESP.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Player_ESP
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Player_ESP.cpp
extern "C" __declspec(dllexport) void
recovered_player_esp_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                              const BoundSurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2ea1a0);
    dependencies->checkbox(layout, ui, image + 0x2ea238);
    dependencies->section(ui, layout, "Customization");
    dependencies->choice(layout, ui, image + 0x2ea0e0);
    dependencies->choice(layout, ui, image + 0x2ea290);
    if (read_surface_value<std::uint32_t>(image, 0x2ea2c0) == 1) {
        dependencies->color(layout, ui, image + 0x2ea218);
        if (image[0x2ea250] == 0) {
            dependencies->color(layout, ui, image + 0x2ea1f8);
        }
    }
    dependencies->checkbox(layout, ui, image + 0x2ea258);
    if (image[0x2ea270] == 1) {
        dependencies->color(layout, ui, image + 0x2ea1d8);
    }
    dependencies->number(layout, ui, image + 0x2ea090);
    dependencies->checkbox(layout, ui, image + 0x2ea120);
    if (image[0x2ea138] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2ea160);
        dependencies->checkbox(layout, ui, image + 0x2ea140);
    }
    dependencies->checkbox(layout, ui, image + 0x2ea180);
}
// END SOURCE shared/BoundSurfaces.cpp@Player_ESP

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Player_ESP/player_esp_render_2d.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses
// evidence/recovered_cpp/behavior/module_behavior_recovery/player_esp_render_2d/player_esp_render_2d.cpp
// SHA-256 1e18ad61b3f7734c0ca783c292d1d3ae47cdf18be2cab9b09e3ecc5e06e8e1be
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.
#ifndef SLINKY_SHARE_B2CC0D86B1B4634E023A
#define SLINKY_SHARE_B2CC0D86B1B4634E023A
// BEGIN SOURCE modules/Player_ESP/Module.hpp
#include "../runtime/shared/RenderNativeBindings.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/shared/Geometry.hpp"
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
__declspec(dllexport) uint64_t drawHealthBar(uint8_t *row, float x, float lower, float upper,
                                             uint8_t *image, Endpoint5 call);
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
// END SOURCE modules/Player_ESP/Module.hpp

#endif // SLINKY_SHARE_B2CC0D86B1B4634E023A

#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
using endpoint = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
static uint64_t readWord_player_esp_render_2d(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t readDword_player_esp_render_2d(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static float readFloat_player_esp_render_2d(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static uint32_t floatBits_player_esp_render_2d(float v) {
    return readDword_player_esp_render_2d(&v);
}
static uint64_t method_player_esp_render_2d(uint8_t *stateImage, uint32_t slot) {
    return readWord_player_esp_render_2d(
        (uint8_t *)(uintptr_t)readWord_player_esp_render_2d(stateImage + slot));
}
static float add_player_esp_render_2d(float a, float b) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float sub(float a, float b) {
    return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
uint32_t recovered_screen_project_295c0(uint8_t *, const double *, float *, uint8_t *);
uint64_t reconstruction::player_esp::drawHealthBar(uint8_t *, float, float, float, uint8_t *,
                                                   endpoint);

__declspec(dllexport) void reconstruction::player_esp::renderScreen(uint8_t *event,
                                                                    uint8_t *stateImage,
                                                                    endpoint invokeEndpoint) {
    if (!readWord_player_esp_render_2d(stateImage + 0x2f7e10) ||
        readDword_player_esp_render_2d(stateImage +
                                       reconstruction::player_esp::setting_offset::mode) != 0)
        return;
    invokeEndpoint(method_player_esp_render_2d(stateImage, 0x13e458), 0xbe2, 0, 0, 0);
    invokeEndpoint(method_player_esp_render_2d(stateImage, 0x150cb0),
                   readDword_player_esp_render_2d(
                       stateImage + reconstruction::player_esp::setting_offset::line_width),
                   0, 0, 0);
    if (!readWord_player_esp_render_2d(stateImage + 0x2f7e10))
        return;
    float partial = readFloat_player_esp_render_2d(event + 0x40);
    double fraction = (double)partial, first_corner[3];
    memcpy(first_corner, stateImage + 0x150aa0, 16);
    first_corner[2] = -.4;
    uint64_t entryIndex = 0;
    do {
        {

            uint8_t *record = stateImage + 0x2f7e20 + 80 * entryIndex;
            double previous[3], current[3], position[3], camera[3], relative[3], point[3];
            float screen[2];
            memcpy(previous, record, 24);
            memcpy(current, record + 0x18, 24);
            recovered_vector_lerp_9460(position, previous, current, fraction);
            memcpy(camera, event + 8, 24);
            recovered_vector_subtract_93d0(relative, position, camera);
            recovered_geometry_add_9400(point, relative, first_corner);
            if (!recovered_screen_project_295c0(event + 8, point, screen, stateImage))
                goto next;
            float minx = screen[0], maxx = screen[0], miny = screen[1], maxy = screen[1];
            for (unsigned offset = 24; offset != 192; offset += 24) {
                double corner[3];
                memcpy(corner, stateImage + 0x150aa0 + offset, 24);
                recovered_geometry_add_9400(point, relative, corner);
                if (!recovered_screen_project_295c0(event + 8, point, screen, stateImage))
                    goto next;
                if (minx > screen[0])
                    minx = screen[0];
                else if (screen[0] > maxx)
                    maxx = screen[0];
                if (miny > screen[1])
                    miny = screen[1];
                else if (screen[1] > maxy)
                    maxy = screen[1];
            }
            float width = readFloat_player_esp_render_2d(event + 0x28),
                  height = readFloat_player_esp_render_2d(event + 0x2c);
            if ((0 > minx || 0 > miny || minx > width || miny > height) &&
                (0 > maxx || maxx > width || 0 > maxy || maxy > height))
                goto next;
            int32_t hurt = (int32_t)readDword_player_esp_render_2d(record + 0x40);
            float red = readFloat_player_esp_render_2d(record + 0x30),
                  green = readFloat_player_esp_render_2d(record + 0x34),
                  blue = readFloat_player_esp_render_2d(record + 0x38);
            if (hurt > 0 && stateImage[reconstruction::player_esp::setting_offset::hurt_effect]) {
                __m128 elapsed =
                    _mm_sub_ss(_mm_cvtsi32_ss(_mm_setzero_ps(), hurt), _mm_set_ss(partial));
                float t = _mm_cvtss_f32(_mm_mul_ss(
                    _mm_min_ss(_mm_set_ss(readFloat_player_esp_render_2d(stateImage + 0x150a08)),
                               elapsed),
                    _mm_set_ss(readFloat_player_esp_render_2d(stateImage + 0x150a0c))));
                red = recovered_scalar_lerp_a2b0(
                    red, readFloat_player_esp_render_2d(stateImage + 0x150a10), t);
                green = recovered_scalar_lerp_a2b0(green, 0, t);
                blue = recovered_scalar_lerp_a2b0(blue, 0, t);
            }
            if (stateImage[reconstruction::player_esp::setting_offset::show_2d_box] ||
                record[0x4c] == 1) {
                recovered_render_29460(stateImage, invokeEndpoint);
                invokeEndpoint(method_player_esp_render_2d(stateImage, 0x150cc0), 0, 0, 0, 0);
                invokeEndpoint(method_player_esp_render_2d(stateImage, 0x150cd8),
                               floatBits_player_esp_render_2d(minx),
                               floatBits_player_esp_render_2d(miny), 0, 0);
                invokeEndpoint(method_player_esp_render_2d(stateImage, 0x150cd0),
                               floatBits_player_esp_render_2d(sub(maxx, minx)),
                               floatBits_player_esp_render_2d(sub(maxy, miny)),
                               readDword_player_esp_render_2d(stateImage + 0x150a10), 0);
                if (stateImage[reconstruction::player_esp::setting_offset::filled] == 1) {
                    invokeEndpoint(method_player_esp_render_2d(stateImage, 0x13e448),
                                   floatBits_player_esp_render_2d(red),
                                   floatBits_player_esp_render_2d(green),
                                   floatBits_player_esp_render_2d(blue),
                                   readDword_player_esp_render_2d(stateImage + 0x150a14));
                    recovered_render_294a0(stateImage, invokeEndpoint);
                }
                invokeEndpoint(method_player_esp_render_2d(stateImage, 0x150ca0),
                               floatBits_player_esp_render_2d(red),
                               floatBits_player_esp_render_2d(green),
                               floatBits_player_esp_render_2d(blue), 0);
                recovered_render_294d0(stateImage, invokeEndpoint);
                invokeEndpoint(method_player_esp_render_2d(stateImage, 0x150cb8), 0, 0, 0, 0);
                recovered_render_295a0(stateImage, invokeEndpoint);
            }
            if (stateImage[reconstruction::player_esp::setting_offset::show_health_bar] == 1) {
                float x = add_player_esp_render_2d(
                    add_player_esp_render_2d(
                        sub(minx, readFloat_player_esp_render_2d(
                                      stateImage +
                                      reconstruction::player_esp::setting_offset::line_width)),
                        readFloat_player_esp_render_2d(stateImage + 0x150a18)),
                    readFloat_player_esp_render_2d(stateImage + 0x150a1c));
                reconstruction::player_esp::drawHealthBar(record, x, miny, maxy, stateImage,
                                                          invokeEndpoint);
            }
        }
    next:
        ++entryIndex;
    } while (entryIndex < readWord_player_esp_render_2d(stateImage + 0x2f7e10));
}
// END SOURCE modules/Player_ESP/player_esp_render_2d.cpp

// BEGIN SOURCE modules/Player_ESP/player_esp_render_3d.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses
// evidence/recovered_cpp/behavior/module_behavior_recovery/player_esp_render_3d/player_esp_render_3d.cpp
// SHA-256 d1e1f74a56403acb01423d2e5f6562d7ea9b31c32f7bf232c3c8486fa370849b
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.

#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
using endpoint = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
static uint64_t readWord_player_esp_render_3d(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t readDword_player_esp_render_3d(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static float readFloat_player_esp_render_3d(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static double readDouble(const void *p) {
    double v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t floatBits_player_esp_render_3d(float v) {
    return readDword_player_esp_render_3d(&v);
}
static uint64_t target(uint64_t holder) {
    return readWord_player_esp_render_3d((uint8_t *)(uintptr_t)holder);
}
static uint64_t method_player_esp_render_3d(uint8_t *stateImage, uint32_t slot) {
    return target(readWord_player_esp_render_3d(stateImage + slot));
}
static float narrow_player_esp_render_3d(double v) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(v)));
}

__declspec(dllexport) uint64_t reconstruction::player_esp::drawHealthBar(uint8_t *record, float x,
                                                                         float lower, float upper,
                                                                         uint8_t *stateImage,
                                                                         endpoint invokeEndpoint) {
    float middle =
        recovered_scalar_lerp_a2b0(upper, lower, readFloat_player_esp_render_3d(record + 0x44));
    uint64_t color = readWord_player_esp_render_3d(stateImage + 0x150ca0);
    invokeEndpoint(target(color), 0, 0, 0, 0);
    uint64_t begin = readWord_player_esp_render_3d(stateImage + 0x150c98);
    invokeEndpoint(target(begin), 1, 0, 0, 0);
    uint64_t vertex = readWord_player_esp_render_3d(stateImage + 0x150ce0);
    invokeEndpoint(target(vertex), floatBits_player_esp_render_3d(x),
                   floatBits_player_esp_render_3d(lower), 0, 0);
    invokeEndpoint(target(vertex), floatBits_player_esp_render_3d(x),
                   floatBits_player_esp_render_3d(middle), 0, 0);
    uint64_t end = readWord_player_esp_render_3d(stateImage + 0x150ca8);
    invokeEndpoint(target(end), 0, 0, 0, 0);
    float extra = readFloat_player_esp_render_3d(record + 0x48);
    if (extra > 0) {
        float split = recovered_scalar_lerp_a2b0(middle, upper, extra);
        invokeEndpoint(target(color), readDword_player_esp_render_3d(stateImage + 0x150a24),
                       readDword_player_esp_render_3d(stateImage + 0x150a28), 0, 0);
        invokeEndpoint(target(begin), 1, 0, 0, 0);
        invokeEndpoint(target(vertex), floatBits_player_esp_render_3d(x),
                       floatBits_player_esp_render_3d(middle), 0, 0);
        invokeEndpoint(target(vertex), floatBits_player_esp_render_3d(x),
                       floatBits_player_esp_render_3d(split), 0, 0);
        invokeEndpoint(target(end), 0, 0, 0, 0);
        middle = split;
    }
    uint64_t color_target = target(color);
    float peak = readFloat_player_esp_render_3d(stateImage + 0x150a24);
    float red = recovered_scalar_lerp_a2b0(peak, 0, readFloat_player_esp_render_3d(record + 0x44));
    float green =
        recovered_scalar_lerp_a2b0(0, peak, readFloat_player_esp_render_3d(record + 0x44));
    invokeEndpoint(color_target, floatBits_player_esp_render_3d(red),
                   floatBits_player_esp_render_3d(green), 0, 0);
    invokeEndpoint(target(begin), 1, 0, 0, 0);
    invokeEndpoint(target(vertex), floatBits_player_esp_render_3d(x),
                   floatBits_player_esp_render_3d(middle), 0, 0);
    invokeEndpoint(target(vertex), floatBits_player_esp_render_3d(x),
                   floatBits_player_esp_render_3d(upper), 0, 0);
    return invokeEndpoint(target(end), 0, 0, 0, 0);
}
__declspec(dllexport) void reconstruction::player_esp::renderWorld(uint8_t *event,
                                                                   uint8_t *stateImage,
                                                                   endpoint invokeEndpoint) {
    if (!readWord_player_esp_render_3d(stateImage + 0x2f7e10) ||
        readDword_player_esp_render_3d(stateImage +
                                       reconstruction::player_esp::setting_offset::mode) != 1)
        return;
    invokeEndpoint(method_player_esp_render_3d(stateImage, 0x13e458), 0xbe2, 0, 0, 0);
    invokeEndpoint(method_player_esp_render_3d(stateImage, 0x150cb0),
                   readDword_player_esp_render_3d(
                       stateImage + reconstruction::player_esp::setting_offset::line_width),
                   0, 0, 0);
    float partial = readFloat_player_esp_render_3d(event + 0x28);
    uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord_player_esp_render_3d(event + 0x20);
    uint64_t camera = invokeEndpoint(0x22d40, readWord_player_esp_render_3d(gameContext),
                                     readWord_player_esp_render_3d(gameContext + 0x18), 0, 0);
    uint32_t yaw =
        (uint32_t)invokeEndpoint(0x27250, readWord_player_esp_render_3d(gameContext), camera, 0, 0);
    if (!readWord_player_esp_render_3d(stateImage + 0x2f7e10))
        return;
    yaw ^= readDword_player_esp_render_3d(stateImage + 0x1509d0);
    double fraction = (double)partial, offset = readDouble(stateImage + 0x1509e0);
    uint64_t scale = readWord_player_esp_render_3d(stateImage + 0x150cd0),
             pop = readWord_player_esp_render_3d(stateImage + 0x150cb8), entryIndex = 0;
    float sy = readFloat_player_esp_render_3d(stateImage + 0x1509e8),
          sx = readFloat_player_esp_render_3d(stateImage + 0x1509ec);
    uint8_t *record = stateImage + 0x2f7e20;
    do {
        double previous[3], current[3], position[3], camera_position[3], relative[3];
        memcpy(previous, record, 24);
        memcpy(current, record + 0x18, 24);
        recovered_vector_lerp_9460(position, previous, current, fraction);
        memcpy(camera_position, event + 8, 24);
        recovered_vector_subtract_93d0(relative, position, camera_position);
        invokeEndpoint(method_player_esp_render_3d(stateImage, 0x150cc0), 0, 0, 0, 0);
        invokeEndpoint(
            method_player_esp_render_3d(stateImage, 0x150cd8),
            floatBits_player_esp_render_3d(narrow_player_esp_render_3d(relative[0])),
            floatBits_player_esp_render_3d(narrow_player_esp_render_3d(relative[1] + offset)),
            floatBits_player_esp_render_3d(narrow_player_esp_render_3d(relative[2])), 0);
        invokeEndpoint(target(scale), floatBits_player_esp_render_3d(sx),
                       floatBits_player_esp_render_3d(sy), floatBits_player_esp_render_3d(sx), 0);
        if (stateImage[reconstruction::player_esp::setting_offset::show_2d_box] ||
            record[0x4c] == 1) {
            recovered_render_293c0(stateImage, invokeEndpoint);
            int32_t hurt = (int32_t)readDword_player_esp_render_3d(record + 0x40);
            float red = readFloat_player_esp_render_3d(record + 0x30),
                  green = readFloat_player_esp_render_3d(record + 0x34),
                  blue = readFloat_player_esp_render_3d(record + 0x38);
            if (hurt > 0 && stateImage[reconstruction::player_esp::setting_offset::hurt_effect]) {
                __m128 elapsed =
                    _mm_sub_ss(_mm_cvtsi32_ss(_mm_setzero_ps(), hurt), _mm_set_ss(partial));
                float t = _mm_cvtss_f32(_mm_mul_ss(
                    _mm_min_ss(_mm_set_ss(readFloat_player_esp_render_3d(stateImage + 0x1509f0)),
                               elapsed),
                    _mm_set_ss(readFloat_player_esp_render_3d(stateImage + 0x1509f4))));
                red = recovered_scalar_lerp_a2b0(red, sy, t);
                green = recovered_scalar_lerp_a2b0(green, 0, t);
                blue = recovered_scalar_lerp_a2b0(blue, 0, t);
            }
            if (stateImage[reconstruction::player_esp::setting_offset::filled] == 1) {
                invokeEndpoint(method_player_esp_render_3d(stateImage, 0x13e448),
                               floatBits_player_esp_render_3d(red),
                               floatBits_player_esp_render_3d(green),
                               floatBits_player_esp_render_3d(blue),
                               readDword_player_esp_render_3d(stateImage + 0x1509f8));
                recovered_render_29400(stateImage, invokeEndpoint);
            }
            invokeEndpoint(method_player_esp_render_3d(stateImage, 0x150ca0),
                           floatBits_player_esp_render_3d(red),
                           floatBits_player_esp_render_3d(green),
                           floatBits_player_esp_render_3d(blue), 0);
            recovered_render_29430(stateImage, invokeEndpoint);
            recovered_render_295a0(stateImage, invokeEndpoint);
        }
        if (stateImage[reconstruction::player_esp::setting_offset::show_health_bar] == 1) {
            invokeEndpoint(method_player_esp_render_3d(stateImage, 0x150cc8), yaw, 0,
                           floatBits_player_esp_render_3d(sy), 0);
            invokeEndpoint(method_player_esp_render_3d(stateImage, 0x13e448), 0,
                           floatBits_player_esp_render_3d(sy), 0,
                           readDword_player_esp_render_3d(stateImage + 0x1509fc));
            reconstruction::player_esp::drawHealthBar(
                record, readFloat_player_esp_render_3d(stateImage + 0x150a00), sy,
                readFloat_player_esp_render_3d(stateImage + 0x150a04), stateImage, invokeEndpoint);
        }
        invokeEndpoint(target(pop), 0, 0, 0, 0);
        ++entryIndex;
        record += 80;
    } while (entryIndex < readWord_player_esp_render_3d(stateImage + 0x2f7e10));
}
// END SOURCE modules/Player_ESP/player_esp_render_3d.cpp

// BEGIN SOURCE modules/Player_ESP/player_esp_update.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses
// evidence/recovered_cpp/behavior/module_behavior_recovery/player_esp_update/player_esp_update.cpp
// SHA-256 67861a349d6fd39fa4e5a490ee0042bd91bd0922e243f619465384a6e0958824
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.

#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
using endpoint = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
static uint64_t readWord_player_esp_update(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t readDword_player_esp_update(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static float readFloat_player_esp_update(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static float floatFromWord(uint64_t v) {
    uint32_t b = (uint32_t)v;
    return readFloat_player_esp_update(&b);
}
static uint32_t floatBits_player_esp_update(float v) {
    return readDword_player_esp_update(&v);
}
static void writeWord(void *p, uint64_t v) {
    memcpy(p, &v, 8);
}
static void writeDword(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
static float add_player_esp_update(float a, float b) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float divf(float a, float b) {
    return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float narrow_player_esp_update(double v) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(v)));
}

__declspec(dllexport) uint32_t reconstruction::player_esp::compareDistance(const uint8_t *a,
                                                                           const uint8_t *b) {
    __m128 difference =
        _mm_sub_ss(_mm_load_ss((const float *)(b + 0x3c)), _mm_load_ss((const float *)(a + 0x3c)));
    return (uint32_t)_mm_cvttss_si32(difference);
}
__declspec(dllexport) void reconstruction::player_esp::updatePlayers(uint8_t *event,
                                                                     uint8_t *stateImage,
                                                                     endpoint invokeEndpoint) {
    uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord_player_esp_update(event + 8);
    if (!readWord_player_esp_update(gameContext + 0x20))
        return;
    writeWord(stateImage + 0x2f7e10, 0);
    double self[3];
    invokeEndpoint(0x23030, (uintptr_t)self, readWord_player_esp_update(gameContext),
                   readWord_player_esp_update(gameContext + 0x28), 0);
    uint64_t list = invokeEndpoint(0x24600, readWord_player_esp_update(gameContext),
                                   readWord_player_esp_update(gameContext + 0x20), 0, 0);
    uint32_t filter = stateImage[reconstruction::player_esp::setting_offset::hide_friendlies];
    if ((int32_t)invokeEndpoint(0x24e50, readWord_player_esp_update(gameContext), list, 0, 0) > 0) {
        filter = filter * 5 + 2;
        uint32_t entryIndex = 0;
        float maximum = readFloat_player_esp_update(stateImage + 0x150a20);
        do {
            {

                uint64_t entry = invokeEndpoint(0x24e80, readWord_player_esp_update(gameContext),
                                                list, entryIndex, 0);
                uint64_t game = readWord_player_esp_update(gameContext),
                         env = readWord_player_esp_update((uint8_t *)(uintptr_t)(game + 8));
                uint64_t target = readWord_player_esp_update(
                    (uint8_t *)(uintptr_t)(readWord_player_esp_update((uint8_t *)(uintptr_t)env) +
                                           0xc0));
                if ((uint8_t)invokeEndpoint(
                        target, env, readWord_player_esp_update(gameContext + 0x28), entry, 0))
                    goto next;
                uint32_t flags = (uint32_t)invokeEndpoint(
                    0x2acb0, readWord_player_esp_update(gameContext), entry, 0, 0);
                if (flags & filter)
                    goto next;
                if ((uint8_t)invokeEndpoint(0x237b0, readWord_player_esp_update(gameContext), entry,
                                            0, 0))
                    goto next;
                double position[3], a[3], b[3];
                invokeEndpoint(0x23030, (uintptr_t)position,
                               readWord_player_esp_update(gameContext), entry, 0);
                memcpy(a, position, 24);
                memcpy(b, self, 24);
                double distance = recovered_vector_distance_squared(a, b);
                float range = readFloat_player_esp_update(
                    stateImage + reconstruction::player_esp::setting_offset::range);
                range = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(range), _mm_set_ss(range)));
                if (distance > (double)range)
                    goto next;
                uint8_t color[12], highlight = 0;
                if (stateImage[reconstruction::player_esp::setting_offset::override_target_color] ==
                    1) {
                    env = readWord_player_esp_update(
                        (uint8_t *)(uintptr_t)(readWord_player_esp_update(gameContext) + 8));
                    target = readWord_player_esp_update(
                        (uint8_t *)(uintptr_t)(readWord_player_esp_update(
                                                   (uint8_t *)(uintptr_t)env) +
                                               0xc0));
                    uint64_t selected = invokeEndpoint(0x2b1c0, 0, 0, 0, 0);
                    if ((uint8_t)invokeEndpoint(target, env, entry, selected, 0)) {
                        memcpy(color + 8, stateImage + 0x2ea1e8, 4);
                        memcpy(color,
                               stateImage +
                                   reconstruction::player_esp::setting_offset::color_target,
                               8);
                        highlight = 1;
                    }
                }
                if (!highlight) {
                    if (!readDword_player_esp_update(
                            stateImage + reconstruction::player_esp::setting_offset::color_mode)) {
                        uint32_t packed = (uint32_t)invokeEndpoint(
                            0x28e10, readWord_player_esp_update(gameContext), entry, 0, 0);
                        invokeEndpoint(0x290d0, (uintptr_t)color, packed, 0, 0);
                    } else {
                        uint32_t off =
                            (flags & 5)
                                ? reconstruction::player_esp::setting_offset::color_friendlies
                                : reconstruction::player_esp::setting_offset::color_enemies;
                        memcpy(color + 8, stateImage + off + 8, 4);
                        memcpy(color, stateImage + off, 8);
                    }
                }
                uint64_t count = readWord_player_esp_update(stateImage + 0x2f7e10);
                writeWord(stateImage + 0x2f7e10, count + 1);
                uint8_t *record = stateImage + 0x2f7e20 + count * 80;
                memcpy(record + 0x28, position + 2, 8);
                memcpy(record + 0x18, position, 16);
                double previous[3];
                invokeEndpoint(0x230d0, (uintptr_t)previous,
                               readWord_player_esp_update(gameContext), entry, 0);
                memcpy(record + 0x10, previous + 2, 8);
                memcpy(record, previous, 16);
                memcpy(record + 0x38, color + 8, 4);
                memcpy(record + 0x30, color, 8);
                writeDword(record + 0x3c,
                           floatBits_player_esp_update(narrow_player_esp_update(distance)));
                writeDword(record + 0x40,
                           (uint32_t)invokeEndpoint(
                               0x239f0, readWord_player_esp_update(gameContext), entry, 0, 0));
                record[0x4c] = highlight;
                game = readWord_player_esp_update(gameContext);
                float health = floatFromWord(invokeEndpoint(0x23a40, game, entry, 0, 0)),
                      extra = floatFromWord(invokeEndpoint(0x23fe0, game, entry, 0, 0));
                extra = _mm_cvtss_f32(_mm_max_ss(_mm_setzero_ps(), _mm_set_ss(extra)));
                float total = add_player_esp_update(
                          floatFromWord(invokeEndpoint(0x23a80, game, entry, 0, 0)), extra),
                      fraction = 0.f;
                if (total != 0.f)
                    fraction = recovered_float_clamp_a1f0(
                        0.f, maximum, divf(add_player_esp_update(health, extra), total));
                writeDword(record + 0x44, floatBits_player_esp_update(fraction));
                fraction = 0.f;
                if (health != 0.f)
                    fraction = recovered_float_clamp_a1f0(0.f, maximum, divf(extra, health));
                writeDword(record + 0x48, floatBits_player_esp_update(fraction));
                if (readWord_player_esp_update(stateImage + 0x2f7e10) == 100)
                    break;
            }
        next:
            entryIndex++;
        } while (
            (int32_t)entryIndex <
            (int32_t)invokeEndpoint(0x24e50, readWord_player_esp_update(gameContext), list, 0, 0));
    }
    invokeEndpoint(0x13d0f0, (uintptr_t)(stateImage + 0x2f7e20),
                   readWord_player_esp_update(stateImage + 0x2f7e10), 80, UINT64_C(0x18002fba0));
}
__declspec(dllexport) uint64_t player_esp_compare_adapter(uint8_t *event, uint8_t *stateImage,
                                                          endpoint invokeEndpoint) {
    (void)stateImage;
    (void)invokeEndpoint;
    return reconstruction::player_esp::compareDistance(
        (uint8_t *)(uintptr_t)readWord_player_esp_update(event),
        (uint8_t *)(uintptr_t)readWord_player_esp_update(event + 8));
}
// END SOURCE modules/Player_ESP/player_esp_update.cpp

// BEGIN SOURCE modules/Player_ESP/Status.cpp
#include <cstring>
void reconstruction::player_esp::writeStatus(char *destination, std::uint8_t *stateImage,
                                             Endpoint5 invoke) {
    std::uint32_t mode;
    std::memcpy(&mode, stateImage + reconstruction::player_esp::setting_offset::mode, 4);
    std::uint64_t label;
    std::memcpy(&label, stateImage + 0x2ea0d0 + std::uint64_t(mode) * 8, 8);
    invoke(0xab710, reinterpret_cast<std::uintptr_t>(destination), 0x20,
           reinterpret_cast<std::uintptr_t>(stateImage + 0x150c8e), label);
}
// END SOURCE modules/Player_ESP/Status.cpp

// Convenient borrowed-state interface

namespace shareable {
class PlayerESP {
  public:
    static constexpr const char *kName = "Player ESP";
    static constexpr const char *kDescription = "Highlights other players.";
    explicit PlayerESP(std::uint8_t *image) : image_(image) {}
    // Style. Config key: mode.
    ChoiceSetting &mode() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2ea0e0);
    }
    // Option labels observed in the captured metadata.
    enum class ModeMode : std::uint32_t { Option2D = 0, Option3D = 1 };
    // Range. Config key: range.
    NumberSetting &range() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ea1a0);
    }
    // Hide friendlies. Config key: hide_friendlies.
    BooleanSetting &hide_friendlies() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ea238);
    }
    // Colors. Config key: color_mode.
    ChoiceSetting &color_mode() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2ea290);
    }
    // Option labels observed in the captured metadata.
    enum class ColorModeMode : std::uint32_t { Automatic = 0, Manual = 1 };
    // color_enemies. Config key: color_enemies.
    ColorSetting &color_enemies() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2ea218);
    }
    // color_friendlies. Config key: color_friendlies.
    ColorSetting &color_friendlies() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2ea1f8);
    }
    // Override target color. Config key: override_target_color.
    BooleanSetting &override_target_color() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ea258);
    }
    // color_target. Config key: color_target.
    ColorSetting &color_target() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2ea1d8);
    }
    // Line width. Config key: line_width.
    NumberSetting &line_width() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ea090);
    }
    // Hurt effect. Config key: hurt_effect.
    BooleanSetting &hurt_effect() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ea140);
    }
    // Filled. Config key: filled.
    BooleanSetting &filled() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ea160);
    }
    // Show box. Config key: show_2d_box.
    BooleanSetting &show_2d_box() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ea120);
    }
    // Show health bar. Config key: show_health_bar.
    BooleanSetting &show_health_bar() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ea180);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_player_esp_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_player_esp_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_player_esp_settings(&context, image_, &dependencies);
    }
    void renderScreen(uint8_t *event, endpoint invokeEndpoint) {
        ::reconstruction::player_esp::renderScreen(event, image_, invokeEndpoint);
    }
    uint64_t drawHealthBar(uint8_t *record, float x, float lower, float upper,
                           endpoint invokeEndpoint) {
        return ::reconstruction::player_esp::drawHealthBar(record, x, lower, upper, image_,
                                                           invokeEndpoint);
    }
    void renderWorld(uint8_t *event, endpoint invokeEndpoint) {
        ::reconstruction::player_esp::renderWorld(event, image_, invokeEndpoint);
    }
    static uint32_t compareDistance(const uint8_t *a, const uint8_t *b) {
        return ::reconstruction::player_esp::compareDistance(a, b);
    }
    void updatePlayers(uint8_t *event, endpoint invokeEndpoint) {
        ::reconstruction::player_esp::updatePlayers(event, image_, invokeEndpoint);
    }
    void writeStatus(char *destination, ::reconstruction::player_esp::Endpoint5 invoke) {
        ::reconstruction::player_esp::writeStatus(destination, image_, invoke);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
