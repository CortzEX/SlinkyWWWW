// Pointers

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Pointers.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Pointers.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Pointers: lib_win settings 0x3e400.
static constexpr SettingsStep settings_steps_Surface_Pointers[] = {
    {SettingsControl::number, "range", 0x2f0a98},
    {SettingsControl::number, "ignore_fov", 0x2f0ad0},
    {SettingsControl::boolean, "hide_friendlies", 0x2f0b48},
    {SettingsControl::choice, "style", 0x2f09e0},
    {SettingsControl::choice, "color_mode", 0x2f0a58},
    {SettingsControl::range, "near_far_range", 0x2f08d0},
    {SettingsControl::color, "color_near", 0x2f0990},
    {SettingsControl::color, "color_far", 0x2f09b0},
    {SettingsControl::color, "color_enemies", 0x2f0b28},
    {SettingsControl::color, "color_friendlies", 0x2f0b08},
    {SettingsControl::number, "scale", 0x2f0920},
    {SettingsControl::number, "radius", 0x2f0958},
    {SettingsControl::boolean, "scale_radius", 0x2f0a20},
};
static constexpr ModuleSurface surface_Surface_Pointers{nullptr, 0, settings_steps_Surface_Pointers,
                                                        std::size(settings_steps_Surface_Pointers)};

extern "C" __declspec(dllexport) void
recovered_pointers_settings(SettingsContext *context, std::uint8_t *image,
                            const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Pointers, context, image, *dependencies);
}

// Pointers: lib_win runtime UI 0x3e2d0.
extern "C" __declspec(dllexport) void
recovered_pointers_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                      const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f0a98);
    dependencies->number(layout, ui, image + 0x2f0ad0);
    dependencies->checkbox(layout, ui, image + 0x2f0b48);
    dependencies->section(ui, layout, "Customization");
    dependencies->choice(layout, ui, image + 0x2f09e0);
    dependencies->choice(layout, ui, image + 0x2f0a58);
    dependencies->range(layout, ui, image + 0x2f08d0);
    const auto color_mode = read_surface_value<std::uint32_t>(image, 0x2f0a88);
    if (color_mode == 2) {
        dependencies->color(layout, ui, image + 0x2f0b28);
        if (image[0x2f0b60] == 0) {
            dependencies->color(layout, ui, image + 0x2f0b08);
        }
    } else if (color_mode == 0) {
        dependencies->color(layout, ui, image + 0x2f0990);
        dependencies->color(layout, ui, image + 0x2f09b0);
    }
    dependencies->number(layout, ui, image + 0x2f0920);
    dependencies->number(layout, ui, image + 0x2f0958);
    dependencies->checkbox(layout, ui, image + 0x2f0a20);
}
// END SOURCE native/verified/surfaces/Surface_Pointers.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Pointers
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Pointers.cpp
extern "C" __declspec(dllexport) void
recovered_pointers_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                            const BoundSurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f0a98);
    dependencies->number(layout, ui, image + 0x2f0ad0);
    dependencies->checkbox(layout, ui, image + 0x2f0b48);
    dependencies->section(ui, layout, "Customization");
    dependencies->choice(layout, ui, image + 0x2f09e0);
    dependencies->choice(layout, ui, image + 0x2f0a58);
    dependencies->range(layout, ui, image + 0x2f08d0);
    const auto color_mode = read_surface_value<std::uint32_t>(image, 0x2f0a88);
    if (color_mode == 2) {
        dependencies->color(layout, ui, image + 0x2f0b28);
        if (image[0x2f0b60] == 0) {
            dependencies->color(layout, ui, image + 0x2f0b08);
        }
    } else if (color_mode == 0) {
        dependencies->color(layout, ui, image + 0x2f0990);
        dependencies->color(layout, ui, image + 0x2f09b0);
    }
    dependencies->number(layout, ui, image + 0x2f0920);
    dependencies->number(layout, ui, image + 0x2f0958);
    dependencies->checkbox(layout, ui, image + 0x2f0a20);
}
// END SOURCE shared/BoundSurfaces.cpp@Pointers

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Pointers/pointers.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses evidence/recovered_cpp/behavior/module_behavior_recovery/pointers/pointers.cpp
// SHA-256 16ceca88bfce898bcc7b3578816f180cae6ed0e4d886ab33f5757b997b811c04
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.
#ifndef SLINKY_SHARE_17A8079A15A2E1AF7F61
#define SLINKY_SHARE_17A8079A15A2E1AF7F61
// BEGIN SOURCE modules/Pointers/Module.hpp
#include "../runtime/shared/RenderNativeBindings.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/shared/Geometry.hpp"
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
// END SOURCE modules/Pointers/Module.hpp

#endif // SLINKY_SHARE_17A8079A15A2E1AF7F61

#include "../runtime/shared/AngleCompatibility.hpp"
#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
using endpoint = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
using dependency = reconstruction::native_binding::RenderEndpoint<4, std::uint32_t>;
static uint64_t readWord(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t readDword(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static float readFloat(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static double readDouble(const void *p) {
    double v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t floatBits(float v) {
    return readDword(&v);
}
static float floatFromWord(uint64_t v) {
    uint32_t b = (uint32_t)v;
    return readFloat(&b);
}
static void writeWord(void *p, uint64_t v) {
    memcpy(p, &v, 8);
}
static void writeFloat(void *p, float v) {
    memcpy(p, &v, 4);
}
static float narrow(double v) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(v)));
}
static float addFloat(float a, float b) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float subtractFloat(float a, float b) {
    return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float multiplyFloat(float a, float b) {
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float divideFloat(float a, float b) {
    return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static uint64_t target(uint64_t holder) {
    return readWord((uint8_t *)(uintptr_t)holder);
}
static uint64_t method(uint8_t *stateImage, uint32_t slot) {
    return target(readWord(stateImage + slot));
}

__declspec(dllexport) uint32_t reconstruction::pointers::compareDistance(const uint8_t *a,
                                                                         const uint8_t *b) {
    return (uint32_t)_mm_cvttss_si32(
        _mm_sub_ss(_mm_load_ss((const float *)(b + 0x30)), _mm_load_ss((const float *)(a + 0x30))));
}
__declspec(dllexport) uint64_t pointers_compare_adapter(uint8_t *event, uint8_t *stateImage,
                                                        endpoint invokeEndpoint) {
    (void)stateImage;
    (void)invokeEndpoint;
    return reconstruction::pointers::compareDistance((uint8_t *)(uintptr_t)readWord(event),
                                                     (uint8_t *)(uintptr_t)readWord(event + 8));
}

static void update(uint8_t *event, uint8_t *stateImage, endpoint invokeEndpoint) {
    uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord(event + 8);
    if (!readWord(gameContext + 0x20))
        return;
    writeWord(stateImage + 0x3008a0, 0);
    double self[3], self_previous[3];
    invokeEndpoint(0x23030, (uintptr_t)self, readWord(gameContext), readWord(gameContext + 0x28),
                   0);
    invokeEndpoint(0x230d0, (uintptr_t)self_previous, readWord(gameContext),
                   readWord(gameContext + 0x28), 0);
    uint64_t camera =
        invokeEndpoint(0x22d40, readWord(gameContext), readWord(gameContext + 0x18), 0, 0);
    float yaw = floatFromWord(invokeEndpoint(0x27250, readWord(gameContext), camera, 0, 0));
    uint64_t list =
        invokeEndpoint(0x24600, readWord(gameContext), readWord(gameContext + 0x20), 0, 0);
    uint8_t filter = stateImage[reconstruction::pointers::setting_offset::hide_friendlies];
    if ((int32_t)invokeEndpoint(0x24e50, readWord(gameContext), list, 0, 0) > 0) {
        uint32_t mask = filter * 5 + 2, entryIndex = 0;
        double degrees = readDouble(stateImage + 0x153cc0), pi = readDouble(stateImage + 0x153cc8),
               adjustment = readDouble(stateImage + 0x153cd0);
        uint32_t absolute = readDword(stateImage + 0x153ce0);
        do {
            {

                uint64_t entity =
                    invokeEndpoint(0x24e80, readWord(gameContext), list, entryIndex, 0);
                uint8_t *game = (uint8_t *)(uintptr_t)readWord(gameContext);
                uint64_t env = readWord(game + 8);
                if ((uint8_t)invokeEndpoint(
                        readWord(
                            (uint8_t *)(uintptr_t)(readWord((uint8_t *)(uintptr_t)env) + 0xc0)),
                        env, readWord(gameContext + 0x28), entity, 0))
                    goto next;
                if ((uint8_t)invokeEndpoint(0x237b0, readWord(gameContext), entity, 0, 0))
                    goto next;
                uint32_t flags =
                    (uint32_t)invokeEndpoint(0x2acb0, readWord(gameContext), entity, 0, 0);
                if (flags & mask)
                    goto next;
                double position[3], previous[3];
                invokeEndpoint(0x23030, (uintptr_t)position, readWord(gameContext), entity, 0);
                double distance = recovered_vector_distance_squared(position, self);
                float range =
                    readFloat(stateImage + reconstruction::pointers::setting_offset::range);
                range = multiplyFloat(range, range);
                if (distance > (double)range)
                    goto next;
                double dx = position[0] - self[0], dz = position[2] - self[2];
                uint64_t angle_bits = invokeEndpoint(0x13cfb0, readWord(&dz), readWord(&dx), 0, 0);
                double angle = (readDouble(&angle_bits) * degrees) / pi + adjustment;
                float wrapped = recovered_angle_wrap_a210(subtractFloat(narrow(angle), yaw),
                                                          stateImage, nullptr);
                if (readFloat(stateImage + reconstruction::pointers::setting_offset::ignore_fov) >
                    floatFromWord(floatBits(wrapped) & absolute))
                    goto next;
                invokeEndpoint(0x230d0, (uintptr_t)previous, readWord(gameContext), entity, 0);
                uint64_t old = readWord(stateImage + 0x3008a0);
                writeWord(stateImage + 0x3008a0, old + 1);
                uint8_t *record = stateImage + 0x3008b0 + 56 * old;
                memcpy(record, position, 8);
                memcpy(record + 8, position + 2, 8);
                memcpy(record + 16, previous, 8);
                memcpy(record + 24, previous + 2, 8);
                float current_distance = narrow(distance);
                if (!(current_distance >= 0))
                    current_distance = floatFromWord(
                        invokeEndpoint(0xaf4a0, floatBits(current_distance), 0, 0, 0));
                else
                    current_distance = _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(current_distance)));
                writeFloat(record + 0x30, current_distance);
                writeFloat(record + 0x2c,
                           narrow(recovered_vector_distance_94f0(self_previous, previous)));
                uint32_t mode =
                    readDword(stateImage + reconstruction::pointers::setting_offset::color_mode);
                if (mode == 1) {
                    uint32_t color =
                        (uint32_t)invokeEndpoint(0x28e10, readWord(gameContext), entity, 0, 0);
                    float rgb[3];
                    invokeEndpoint(0x290d0, (uintptr_t)rgb, color, 0, 0);
                    memcpy(record + 0x28, rgb + 2, 4);
                    memcpy(record + 0x20, rgb, 8);
                } else if (mode == 2) {
                    uint32_t color =
                        flags & 5 ? reconstruction::pointers::setting_offset::color_friendlies
                                  : reconstruction::pointers::setting_offset::color_enemies;
                    memcpy(record + 0x28, stateImage + color + 8, 4);
                    memcpy(record + 0x20, stateImage + color, 8);
                }
                if (readWord(stateImage + 0x3008a0) == 100)
                    break;
            }
        next:
            ++entryIndex;
        } while ((int32_t)entryIndex <
                 (int32_t)invokeEndpoint(0x24e50, readWord(gameContext), list, 0, 0));
    }
    invokeEndpoint(0x13d0f0, (uintptr_t)(stateImage + 0x3008b0), readWord(stateImage + 0x3008a0),
                   56, UINT64_C(0x18003e570));
}
__declspec(dllexport) void reconstruction::pointers::updatePointers(uint8_t *event,
                                                                    uint8_t *stateImage,
                                                                    endpoint invokeEndpoint) {
    update(event, stateImage, invokeEndpoint);
}

static void render(uint8_t *event, uint8_t *stateImage, endpoint invokeEndpoint) {
    if (!readWord(stateImage + 0x3008a0))
        return;
    uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord(event + 0x20);
    float partial = readFloat(event + 0x40);
    uint64_t camera =
        invokeEndpoint(0x22d40, readWord(gameContext), readWord(gameContext + 0x18), 0, 0);
    float pitch = floatFromWord(invokeEndpoint(0x27200, readWord(gameContext), camera, 0, 0)),
          yaw = floatFromWord(invokeEndpoint(0x27250, readWord(gameContext), camera, 0, 0));
    recovered_render_29500(stateImage, invokeEndpoint);
    uint64_t center =
        recovered_angle_scale_9e60(readWord(event + 0x28), readFloat(stateImage + 0x153c70));
    invokeEndpoint(method(stateImage, 0x150cc0), 0, 0, 0, 0);
    if (readDword(stateImage + reconstruction::pointers::setting_offset::style)) {
        float floor = _mm_cvtss_f32(
            _mm_max_ss(_mm_set_ss(readFloat(stateImage + 0x153c74)), _mm_set_ss(pitch)));
        invokeEndpoint(method(stateImage, 0x150cd8), (uint32_t)center, (uint32_t)(center >> 32), 0,
                       0);
        invokeEndpoint(method(stateImage, 0x150cc8),
                       floatBits(subtractFloat(readFloat(stateImage + 0x153c78), floor)),
                       readDword(stateImage + 0x153c7c), 0, 0);
    } else
        invokeEndpoint(method(stateImage, 0x150cd8), (uint32_t)center, (uint32_t)(center >> 32), 0,
                       0);
    float one = readFloat(stateImage + 0x153c7c);
    invokeEndpoint(method(stateImage, 0x150cb0), floatBits(one), 0, 0, 0);
    invokeEndpoint(method(stateImage, 0x13e458), 0xb20, 0, 0, 0);
    if (readWord(stateImage + 0x3008a0)) {
        float span =
            subtractFloat(readFloat(stateImage + 0x2f0914), readFloat(stateImage + 0x2f0910));
        if (span == 0)
            span = readFloat(stateImage + 0x153c80);
        double degrees = readDouble(stateImage + 0x153c88), pi = readDouble(stateImage + 0x153c90),
               adjustment = readDouble(stateImage + 0x153c98);
        float size = readFloat(stateImage + 0x153ca0);
        uint64_t scale = readWord(stateImage + 0x150cd0),
                 translate = readWord(stateImage + 0x150cd8),
                 color = readWord(stateImage + 0x150ca0), pop = readWord(stateImage + 0x150cb8);
        uint32_t sign = readDword(stateImage + 0x153cb0);
        uint64_t entryIndex = 0;
        uint8_t *record = stateImage + 0x3008b0;
        do {
            double px = (double)recovered_scalar_lerp_a2b0(narrow(readDouble(record + 0x10)),
                                                           narrow(readDouble(record)), partial);
            double pz = (double)recovered_scalar_lerp_a2b0(narrow(readDouble(record + 0x18)),
                                                           narrow(readDouble(record + 8)), partial);
            px -= readDouble(event + 8);
            pz -= readDouble(event + 0x18);
            uint64_t angle_bits = invokeEndpoint(0x13cfb0, readWord(&pz), readWord(&px), 0, 0);
            float angle = recovered_angle_wrap_a210(
                subtractFloat(narrow((readDouble(&angle_bits) * degrees) / pi + adjustment), yaw),
                stateImage, nullptr);
            invokeEndpoint(method(stateImage, 0x150cc0), 0, 0, 0, 0);
            invokeEndpoint(method(stateImage, 0x150cc8), floatBits(angle), 0, 0, floatBits(one));
            float glyph_size = multiplyFloat(
                readFloat(stateImage + reconstruction::pointers::setting_offset::scale), size);
            invokeEndpoint(target(scale), floatBits(glyph_size), floatBits(glyph_size),
                           floatBits(glyph_size), 0);
            float distance = recovered_scalar_lerp_a2b0(readFloat(record + 0x2c),
                                                        readFloat(record + 0x30), partial);
            float factor = recovered_float_clamp_a1f0(
                0, one,
                divideFloat(subtractFloat(distance, readFloat(stateImage + 0x2f0910)), span));
            float radius = readFloat(stateImage + reconstruction::pointers::setting_offset::radius);
            if (stateImage[reconstruction::pointers::setting_offset::scale_radius])
                radius = multiplyFloat(radius, addFloat(factor, one));
            invokeEndpoint(target(translate), 0, floatBits(radius) ^ sign, 0, 0);
            float red, green, blue;
            if (readDword(stateImage + reconstruction::pointers::setting_offset::color_mode) == 0) {
                red = recovered_scalar_lerp_a2b0(
                    readFloat(stateImage + reconstruction::pointers::setting_offset::color_near),
                    readFloat(stateImage + reconstruction::pointers::setting_offset::color_far),
                    factor);
                green = recovered_scalar_lerp_a2b0(readFloat(stateImage + 0x2f099c),
                                                   readFloat(stateImage + 0x2f09bc), factor);
                blue = recovered_scalar_lerp_a2b0(readFloat(stateImage + 0x2f09a0),
                                                  readFloat(stateImage + 0x2f09c0), factor);
            } else {
                red = readFloat(record + 0x20);
                green = readFloat(record + 0x24);
                blue = readFloat(record + 0x28);
            }
            invokeEndpoint(target(color), floatBits(red), floatBits(green), floatBits(blue), 0);
            recovered_render_29540(stateImage, invokeEndpoint);
            invokeEndpoint(target(color), 0, 0, 0, 0);
            recovered_render_29570(stateImage, invokeEndpoint);
            invokeEndpoint(target(pop), 0, 0, 0, 0);
            ++entryIndex;
            record += 56;
        } while (entryIndex < readWord(stateImage + 0x3008a0));
    }
    invokeEndpoint(method(stateImage, 0x150cb8), 0, 0, 0, 0);
    recovered_render_295a0(stateImage, invokeEndpoint);
}
__declspec(dllexport) void reconstruction::pointers::renderPointers(uint8_t *event,
                                                                    uint8_t *stateImage,
                                                                    endpoint invokeEndpoint) {
    render(event, stateImage, invokeEndpoint);
}
// END SOURCE modules/Pointers/pointers.cpp

// BEGIN SOURCE modules/Pointers/Status.cpp
#include <cstring>
void reconstruction::pointers::writeStatus(char *destination, std::uint8_t *stateImage,
                                           Endpoint5 invoke) {
    std::uint32_t mode;
    std::memcpy(&mode, stateImage + reconstruction::pointers::setting_offset::style, 4);
    std::uint64_t label;
    std::memcpy(&label, stateImage + 0x2f09d0 + std::uint64_t(mode) * 8, 8);
    invoke(0xab710, reinterpret_cast<std::uintptr_t>(destination), 0x20,
           reinterpret_cast<std::uintptr_t>(stateImage + 0x153ea4), label);
}
// END SOURCE modules/Pointers/Status.cpp

// Convenient borrowed-state interface

namespace shareable {
class Pointers {
  public:
    static constexpr const char *kName = "Pointers";
    static constexpr const char *kDescription = "Points to other players.";
    explicit Pointers(std::uint8_t *image) : image_(image) {}
    // Range. Config key: range.
    NumberSetting &range() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f0a98);
    }
    // Ignore within FOV. Config key: ignore_fov.
    NumberSetting &ignore_fov() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f0ad0);
    }
    // Hide friendlies. Config key: hide_friendlies.
    BooleanSetting &hide_friendlies() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f0b48);
    }
    // Style. Config key: style.
    ChoiceSetting &style() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f09e0);
    }
    // Option labels observed in the captured metadata.
    enum class StyleMode : std::uint32_t { Option2D = 0, Option3D = 1 };
    // Colors. Config key: color_mode.
    ChoiceSetting &color_mode() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f0a58);
    }
    // Option labels observed in the captured metadata.
    enum class ColorModeMode : std::uint32_t { Distance = 0, NameTag = 1, Manual = 2 };
    // near_far_range. Config key: near_far_range.
    RangeSetting &near_far_range() const {
        return *reinterpret_cast<RangeSetting *>(image_ + 0x2f08d0);
    }
    // color_near. Config key: color_near.
    ColorSetting &color_near() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2f0990);
    }
    // color_far. Config key: color_far.
    ColorSetting &color_far() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2f09b0);
    }
    // color_enemies. Config key: color_enemies.
    ColorSetting &color_enemies() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2f0b28);
    }
    // color_friendlies. Config key: color_friendlies.
    ColorSetting &color_friendlies() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2f0b08);
    }
    // Scale. Config key: scale.
    NumberSetting &scale() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f0920);
    }
    // Radius. Config key: radius.
    NumberSetting &radius() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f0958);
    }
    // Distance-based radius. Config key: scale_radius.
    BooleanSetting &scale_radius() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f0a20);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_pointers_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_pointers_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_pointers_settings(&context, image_, &dependencies);
    }
    static uint32_t compareDistance(const uint8_t *a, const uint8_t *b) {
        return ::reconstruction::pointers::compareDistance(a, b);
    }
    void updatePointers(uint8_t *event, endpoint invokeEndpoint) {
        ::reconstruction::pointers::updatePointers(event, image_, invokeEndpoint);
    }
    void renderPointers(uint8_t *event, endpoint invokeEndpoint) {
        ::reconstruction::pointers::renderPointers(event, image_, invokeEndpoint);
    }
    void writeStatus(char *destination, ::reconstruction::pointers::Endpoint5 invoke) {
        ::reconstruction::pointers::writeStatus(destination, image_, invoke);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
