// Name Tags

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Name_Tags.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Name_Tags.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Name Tags: lib_win settings 0x3d6e0.
static constexpr SettingsStep settings_steps_Surface_Name_Tags[] = {
    {SettingsControl::number, "range", 0x2f05b8},
    {SettingsControl::number, "scale", 0x2f04e0},
    {SettingsControl::boolean, "show_own_name_tag", 0x2f05f0},
    {SettingsControl::boolean, "use_display_name", 0x2f0610},
    {SettingsControl::boolean, "distance_scaling", 0x2f0518},
    {SettingsControl::boolean, "background", 0x2f0538},
    {SettingsControl::boolean, "text_shadow", 0x2f0558},
    {SettingsControl::boolean, "show_health", 0x2f0630},
    {SettingsControl::choice, "health_fmt", 0x2f0680},
    {SettingsControl::boolean, "show_distance", 0x2f0650},
    {SettingsControl::boolean, "show_equipment", 0x2f0578},
    {SettingsControl::boolean, "show_enchants", 0x2f0598},
};
static constexpr ModuleSurface surface_Surface_Name_Tags{
    nullptr, 0, settings_steps_Surface_Name_Tags, std::size(settings_steps_Surface_Name_Tags)};

extern "C" __declspec(dllexport) void
recovered_name_tags_settings(SettingsContext *context, std::uint8_t *image,
                             const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Name_Tags, context, image, *dependencies);
}

// Name Tags: lib_win runtime UI 0x3d5b0.
extern "C" __declspec(dllexport) void
recovered_name_tags_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                       const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f05b8);
    dependencies->number(layout, ui, image + 0x2f04e0);
    dependencies->checkbox(layout, ui, image + 0x2f05f0);
    dependencies->checkbox(layout, ui, image + 0x2f0610);
    dependencies->checkbox(layout, ui, image + 0x2f0518);
    dependencies->checkbox(layout, ui, image + 0x2f0538);
    dependencies->checkbox(layout, ui, image + 0x2f0558);
    dependencies->section(ui, layout, "Extra info");
    dependencies->checkbox(layout, ui, image + 0x2f0630);
    if (image[0x2f0648] == 1) {
        dependencies->choice(layout, ui, image + 0x2f0680);
    }
    dependencies->checkbox(layout, ui, image + 0x2f0650);
    dependencies->checkbox(layout, ui, image + 0x2f0578);
    if (image[0x2f0590] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2f0598);
    }
}
// END SOURCE native/verified/surfaces/Surface_Name_Tags.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Name_Tags
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Name_Tags.cpp
extern "C" __declspec(dllexport) void
recovered_name_tags_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                             const BoundSurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f05b8);
    dependencies->number(layout, ui, image + 0x2f04e0);
    dependencies->checkbox(layout, ui, image + 0x2f05f0);
    dependencies->checkbox(layout, ui, image + 0x2f0610);
    dependencies->checkbox(layout, ui, image + 0x2f0518);
    dependencies->checkbox(layout, ui, image + 0x2f0538);
    dependencies->checkbox(layout, ui, image + 0x2f0558);
    dependencies->section(ui, layout, "Extra info");
    dependencies->checkbox(layout, ui, image + 0x2f0630);
    if (image[0x2f0648] == 1) {
        dependencies->choice(layout, ui, image + 0x2f0680);
    }
    dependencies->checkbox(layout, ui, image + 0x2f0650);
    dependencies->checkbox(layout, ui, image + 0x2f0578);
    if (image[0x2f0590] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2f0598);
    }
}
// END SOURCE shared/BoundSurfaces.cpp@Name_Tags

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Name_Tags/name_tags.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses evidence/recovered_cpp/behavior/module_behavior_recovery/name_tags/name_tags.cpp
// SHA-256 0ea8ab2ba5628609a793cae8e4d03075be0dfe7f99e49e0c9a38e526a75c5547
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.
#ifndef SLINKY_SHARE_B99D0BD096E6751B2C1D
#define SLINKY_SHARE_B99D0BD096E6751B2C1D
// BEGIN SOURCE modules/Name_Tags/Module.hpp
#include "../runtime/shared/RenderNativeBindings.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/shared/Geometry.hpp"
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
__declspec(dllexport) int32_t compareEnchantment(const uint8_t *a, const uint8_t *b,
                                                 uint8_t *image);
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
// END SOURCE modules/Name_Tags/Module.hpp

#endif // SLINKY_SHARE_B99D0BD096E6751B2C1D

#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
using endpoint = reconstruction::native_binding::RenderEndpoint<8, std::uint64_t>;
static uint64_t readWord_name_tags(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t readDword_name_tags(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static float readFloat_name_tags(const void *p) {
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
    return readDword_name_tags(&v);
}
static float floatFromWord_name_tags(uint64_t v) {
    uint32_t b = (uint32_t)v;
    return readFloat_name_tags(&b);
}
static void writeWord_name_tags(void *p, uint64_t v) {
    memcpy(p, &v, 8);
}
static float narrow_name_tags(double v) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(v)));
}
static float addFloat(float a, float b) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float multiplyFloat_name_tags(float a, float b) {
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float divideFloat(float a, float b) {
    return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float maxf(float a, float b) {
    return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static uint64_t target(uint64_t holder) {
    return readWord_name_tags((uint8_t *)(uintptr_t)holder);
}
static uint64_t method_name_tags(uint8_t *stateImage, uint32_t slot) {
    return target(readWord_name_tags(stateImage + slot));
}
static uint64_t virtual_method(uint64_t env, uint32_t slot) {
    return readWord_name_tags(
        (uint8_t *)(uintptr_t)(readWord_name_tags((uint8_t *)(uintptr_t)env) + slot));
}
uint32_t recovered_screen_project_295f0(uint8_t *, const double *, float *, float *, uint8_t *);

__declspec(dllexport) void reconstruction::name_tags::releaseTags(uint8_t *game,
                                                                  uint8_t *stateImage,
                                                                  endpoint invokeEndpoint) {
    if (readWord_name_tags(stateImage + 0x2fc910)) {
        uint64_t env = readWord_name_tags(game + 8), entryIndex = 0;
        do {
            uint8_t *record = stateImage + 0x2fc920 + 160 * entryIndex;
            uint64_t label = readWord_name_tags(record + 0x38);
            if (label)
                invokeEndpoint(virtual_method(env, 0xb0), env, label, 0, 0, 0, 0, 0, 0);
            uint64_t entity = readWord_name_tags(record + 0x30);
            if (entity)
                invokeEndpoint(virtual_method(env, 0xb0), env, entity, 0, 0, 0, 0, 0, 0);
            for (unsigned slot = 0; slot < 5; ++slot) {
                uint8_t *equipment = record + 0x50 + 16 * slot;
                uint64_t array = readWord_name_tags(equipment + 8);
                if (array) {
                    if ((int32_t)readDword_name_tags(equipment + 4) > 0) {
                        uint64_t i = 0;
                        do {
                            uint64_t entry = readWord_name_tags(
                                (uint8_t *)(uintptr_t)(readWord_name_tags(equipment + 8) + 8 * i));
                            invokeEndpoint(virtual_method(env, 0xb0), env, entry, 0, 0, 0, 0, 0, 0);
                            ++i;
                        } while ((int64_t)i < (int64_t)(int32_t)readDword_name_tags(equipment + 4));
                        array = readWord_name_tags(equipment + 8);
                    }
                    invokeEndpoint(0x13cf70, array, 0, 0, 0, 0, 0, 0, 0);
                    writeWord_name_tags(equipment + 8, 0);
                }
            }
            ++entryIndex;
        } while (entryIndex < readWord_name_tags(stateImage + 0x2fc910));
    }
    writeWord_name_tags(stateImage + 0x2fc910, 0);
}
__declspec(dllexport) void reconstruction::name_tags::onLifecycleEvent(uint8_t *event,
                                                                       uint8_t *stateImage,
                                                                       endpoint invokeEndpoint) {
    if (event[0x18] || readWord_name_tags(event + 0x10) != (uintptr_t)(stateImage + 0x2f02d0))
        return;
    reconstruction::name_tags::releaseTags((uint8_t *)(uintptr_t)readWord_name_tags(
                                               (uint8_t *)(uintptr_t)readWord_name_tags(event + 8)),
                                           stateImage, invokeEndpoint);
    uint64_t object = readWord_name_tags(stateImage + 0x3007a0);
    if (object) {
        uint64_t game = readWord_name_tags((uint8_t *)(uintptr_t)readWord_name_tags(event + 8)),
                 env = readWord_name_tags((uint8_t *)(uintptr_t)(game + 8));
        invokeEndpoint(virtual_method(env, 0xb0), env, object, 0, 0, 0, 0, 0, 0);
        writeWord_name_tags(stateImage + 0x3007a0, 0);
    }
}
__declspec(dllexport) void name_tags_release_adapter(uint8_t *event, uint8_t *stateImage,
                                                     endpoint invokeEndpoint) {
    reconstruction::name_tags::releaseTags((uint8_t *)(uintptr_t)readWord_name_tags(event),
                                           stateImage, invokeEndpoint);
}

__declspec(dllexport) void reconstruction::name_tags::renderTags(uint8_t *event,
                                                                 uint8_t *stateImage,
                                                                 endpoint invokeEndpoint) {
    if (!readWord_name_tags(stateImage + 0x2fc910) || !readWord_name_tags(stateImage + 0x3007a0))
        return;
    uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord_name_tags(event + 0x20);
    uint64_t camera = invokeEndpoint(0x22d40, readWord_name_tags(gameContext),
                                     readWord_name_tags(gameContext + 0x18), 0, 0, 0, 0, 0, 0),
             font =
                 invokeEndpoint(0x272a0, readWord_name_tags(gameContext), camera, 0, 0, 0, 0, 0, 0);
    uint64_t texture = invokeEndpoint(0x22dd0, readWord_name_tags(gameContext),
                                      readWord_name_tags(gameContext + 0x18), 0, 0, 0, 0, 0, 0);
    float saved_depth = floatFromWord_name_tags(
        invokeEndpoint(0x27b50, readWord_name_tags(gameContext),
                       readWord_name_tags(stateImage + 0x3007a0), 0, 0, 0, 0, 0, 0));
    invokeEndpoint(0x27b70, readWord_name_tags(gameContext),
                   readWord_name_tags(stateImage + 0x3007a0),
                   readDword_name_tags(stateImage + 0x1536d0), 0, 0, 0, 0, 0);
    uint64_t renderer = invokeEndpoint(0x22d90, readWord_name_tags(gameContext),
                                       readWord_name_tags(gameContext + 0x18), 0, 0, 0, 0, 0, 0);
    float fov =
        floatFromWord_name_tags(invokeEndpoint(0x273e0, readWord_name_tags(gameContext), renderer,
                                               readDword_name_tags(event + 0x40), 0, 0, 0, 0, 0));
    if (readWord_name_tags(stateImage + 0x2fc910)) {
        float fov_scale = divideFloat(readFloat_name_tags(stateImage + 0x1536d4), fov),
              depth_scale = readFloat_name_tags(stateImage + 0x1536e0),
              one = readFloat_name_tags(stateImage + 0x1536e8),
              height = readFloat_name_tags(stateImage + 0x153710),
              half = readFloat_name_tags(stateImage + 0x153700),
              pad = readFloat_name_tags(stateImage + 0x153714);
        double lift = readDouble(stateImage + 0x1536d8),
               center_scale = readDouble(stateImage + 0x1536f0),
               left_padding = readDouble(stateImage + 0x1536f8);
        uint64_t entryIndex = 0;
        do {
            {

                uint8_t *record = stateImage + 0x2fc920 + 160 * entryIndex;
                double previous[3], current[3], position[3], camera_position[3], relative[3];
                float screen[2], inverse;
                memcpy(previous, record, 24);
                memcpy(current, record + 0x18, 24);
                recovered_vector_lerp_9460(position, previous, current,
                                           (double)readFloat_name_tags(event + 0x40));
                position[1] += lift;
                memcpy(camera_position, event + 8, 24);
                recovered_vector_subtract_93d0(relative, position, camera_position);
                if (!(uint8_t)recovered_screen_project_295f0(event + 8, relative, screen, &inverse,
                                                             stateImage))
                    goto next;
                invokeEndpoint(method_name_tags(stateImage, 0x150cc0), 0, 0, 0, 0, 0, 0, 0, 0);
                invokeEndpoint(method_name_tags(stateImage, 0x150cd8), floatBits(screen[0]),
                               floatBits(screen[1]),
                               floatBits(multiplyFloat_name_tags(inverse, depth_scale)), 0, 0, 0, 0,
                               0);
                float factor =
                    multiplyFloat_name_tags(inverse, readFloat_name_tags(stateImage + 0x1536e4));
                if (stateImage[reconstruction::name_tags::setting_offset::distance_scaling])
                    factor = maxf(factor, one);
                float size = multiplyFloat_name_tags(
                    multiplyFloat_name_tags(
                        readFloat_name_tags(stateImage +
                                            reconstruction::name_tags::setting_offset::scale),
                        fov_scale),
                    factor);
                invokeEndpoint(method_name_tags(stateImage, 0x150cd0), floatBits(size),
                               floatBits(size), floatBits(size), 0, 0, 0, 0, 0);
                int32_t negative_width = _mm_cvtsi128_si32(
                    _mm_sub_epi32(_mm_setzero_si128(),
                                  _mm_cvtsi32_si128((int32_t)readDword_name_tags(record + 0x40))));
                double left =
                    _mm_cvtsd_f64(_mm_cvtsi32_sd(_mm_setzero_pd(), negative_width)) * center_scale +
                    left_padding;
                if (event[0x44] == 1)
                    invokeEndpoint(0x27760, readWord_name_tags(gameContext), 0, 0, 0, 0, 0, 0, 0);
                else
                    invokeEndpoint(method_name_tags(stateImage, 0x13e450), 0xb71, 0, 0, 0, 0, 0, 0,
                                   0);
                float left_x = narrow_name_tags(left);
                if (stateImage[reconstruction::name_tags::setting_offset::background] == 1) {
                    if (event[0x44] == 1) {
                        invokeEndpoint(0x27820, readWord_name_tags(gameContext), 0, 0, 0, 0, 0, 0,
                                       0);
                        invokeEndpoint(0x278f0, readWord_name_tags(gameContext), 0, 0, 0,
                                       0x3f000000, 0, 0, 0);
                    } else {
                        invokeEndpoint(method_name_tags(stateImage, 0x13e450), 0xde1, 0, 0, 0, 0, 0,
                                       0, 0);
                        invokeEndpoint(method_name_tags(stateImage, 0x13e448), 0, 0, 0,
                                       floatBits(half), 0, 0, 0, 0);
                    }
                    float right_x = narrow_name_tags(
                        (double)(int32_t)readDword_name_tags(record + 0x40) * center_scale +
                        readDouble(stateImage + 0x153708));
                    invokeEndpoint(method_name_tags(stateImage, 0x150c98), 5, 0, 0, 0, 0, 0, 0, 0);
                    uint64_t vertex_holder = readWord_name_tags(stateImage + 0x150ce0);
                    invokeEndpoint(target(vertex_holder), floatBits(left_x), 0, 0, 0, 0, 0, 0, 0);
                    invokeEndpoint(target(vertex_holder), floatBits(right_x), 0, 0, 0, 0, 0, 0, 0);
                    invokeEndpoint(target(vertex_holder), floatBits(left_x), floatBits(height), 0,
                                   0, 0, 0, 0, 0);
                    invokeEndpoint(target(vertex_holder), floatBits(right_x), floatBits(height), 0,
                                   0, 0, 0, 0, 0);
                    invokeEndpoint(method_name_tags(stateImage, 0x150ca8), 0, 0, 0, 0, 0, 0, 0, 0);
                    depth_scale = readFloat_name_tags(stateImage + 0x1536e0);
                }
                if (event[0x44] == 1) {
                    invokeEndpoint(0x277f0, readWord_name_tags(gameContext), 0, 0, 0, 0, 0, 0, 0);
                    invokeEndpoint(0x278f0, readWord_name_tags(gameContext), floatBits(one),
                                   floatBits(one), floatBits(one), 0x3f800000, 0, 0, 0);
                } else {
                    invokeEndpoint(method_name_tags(stateImage, 0x13e458), 0xde1, 0, 0, 0, 0, 0, 0,
                                   0);
                    invokeEndpoint(method_name_tags(stateImage, 0x150ca0), floatBits(one),
                                   floatBits(one), floatBits(one), 0, 0, 0, 0, 0);
                }
                left_x = addFloat(left_x, pad);
                invokeEndpoint(
                    0x27590, readWord_name_tags(gameContext), font,
                    readWord_name_tags(record + 0x38), floatBits(left_x), 0xc1200000, 0xffffffff,
                    stateImage[reconstruction::name_tags::setting_offset::text_shadow], 0);
                if (stateImage[reconstruction::name_tags::setting_offset::show_equipment] == 1) {
                    if (event[0x44] == 1)
                        invokeEndpoint(0x27730, readWord_name_tags(gameContext), 0, 0, 0, 0, 0, 0,
                                       0);
                    else
                        invokeEndpoint(method_name_tags(stateImage, 0x13e458), 0xb71, 0, 0, 0, 0, 0,
                                       0, 0);
                    invokeEndpoint(0x27c90, readWord_name_tags(gameContext), 0, 0, 0, 0, 0, 0, 0);
                    invokeEndpoint(method_name_tags(stateImage, 0x150cd0), floatBits(one),
                                   floatBits(one), readDword_name_tags(stateImage + 0x153718), 0, 0,
                                   0, 0, 0);
                    uint32_t x = 0u - (readDword_name_tags(record + 0x4c) << 3);
                    for (unsigned slot = 0; slot < 5; ++slot) {
                        if (record[0x50 + 16 * slot] != 1)
                            continue;
                        uint64_t item =
                            invokeEndpoint(0x24050, readWord_name_tags(gameContext),
                                           readWord_name_tags(record + 0x30), slot, 0, 0, 0, 0, 0);
                        if (!item)
                            continue;
                        invokeEndpoint(0x27ba0, readWord_name_tags(gameContext),
                                       readWord_name_tags(stateImage + 0x3007a0), font, texture,
                                       item, x, 0xffffffe0, 0);
                        invokeEndpoint(0x27c10, readWord_name_tags(gameContext),
                                       readWord_name_tags(stateImage + 0x3007a0), font, texture,
                                       item, x, 0xffffffe0, 0);
                        x += 16;
                    }
                    invokeEndpoint(0x27cc0, readWord_name_tags(gameContext), 0, 0, 0, 0, 0, 0, 0);
                    if (event[0x44]) {
                        invokeEndpoint(0x27790, readWord_name_tags(gameContext), 0, 0, 0, 0, 0, 0,
                                       0);
                        invokeEndpoint(0x27880, readWord_name_tags(gameContext), 0, 0, 0, 0, 0, 0,
                                       0);
                        invokeEndpoint(0x278b0, readWord_name_tags(gameContext), 0x302, 0x303, 0, 0,
                                       0, 0, 0);
                    } else {
                        invokeEndpoint(method_name_tags(stateImage, 0x13e458), 0xbe2, 0, 0, 0, 0, 0,
                                       0, 0);
                        invokeEndpoint(method_name_tags(stateImage, 0x13e450), 0xbc0, 0, 0, 0, 0, 0,
                                       0, 0);
                        invokeEndpoint(method_name_tags(stateImage, 0x13e438), 0x302, 0x303, 0, 0,
                                       0, 0, 0, 0);
                    }
                    invokeEndpoint(method_name_tags(stateImage, 0x150ca0), floatBits(one),
                                   floatBits(one), floatBits(one), 0, 0, 0, 0, 0);
                    invokeEndpoint(method_name_tags(stateImage, 0x150cd0), floatBits(half),
                                   floatBits(half), floatBits(half), 0, 0, 0, 0, 0);
                    if (stateImage[reconstruction::name_tags::setting_offset::show_enchants] == 1) {
                        uint32_t x = 0u - (readDword_name_tags(record + 0x4c) << 3);
                        for (unsigned slot = 0; slot < 5; ++slot) {
                            uint8_t *equipment = record + 0x50 + 16 * slot;
                            if (*equipment != 1)
                                continue;
                            if (readWord_name_tags(equipment + 8) &&
                                (int32_t)readDword_name_tags(equipment + 4) > 0) {
                                float label_x = (float)(int32_t)(x + x);
                                uint32_t y = 0xffffffc0;
                                uint64_t i = 0;
                                do {
                                    uint64_t label = readWord_name_tags(
                                        (uint8_t *)(uintptr_t)(readWord_name_tags(equipment + 8) +
                                                               8 * i));
                                    invokeEndpoint(0x27590, readWord_name_tags(gameContext), font,
                                                   label, floatBits(label_x),
                                                   floatBits((float)(int32_t)y), 0xffffffff, 1, 0);
                                    ++i;
                                    y += 8;
                                } while ((int64_t)i <
                                         (int64_t)(int32_t)readDword_name_tags(equipment + 4));
                            }
                            x += 16;
                        }
                    }
                }
                invokeEndpoint(method_name_tags(stateImage, 0x150cb8), 0, 0, 0, 0, 0, 0, 0, 0);
            }
        next:
            ++entryIndex;
        } while (entryIndex < readWord_name_tags(stateImage + 0x2fc910));
    }
    if (event[0x44]) {
        invokeEndpoint(0x27820, readWord_name_tags(gameContext), 0, 0, 0, 0, 0, 0, 0);
        invokeEndpoint(0x27760, readWord_name_tags(gameContext), 0, 0, 0, 0, 0, 0, 0);
    } else {
        uint64_t holder = readWord_name_tags(stateImage + 0x13e450);
        invokeEndpoint(target(holder), 0xde1, 0, 0, 0, 0, 0, 0, 0);
        invokeEndpoint(target(holder), 0xb71, 0, 0, 0, 0, 0, 0, 0);
    }
    invokeEndpoint(0x27b70, readWord_name_tags(gameContext),
                   readWord_name_tags(stateImage + 0x3007a0), floatBits(saved_depth), 0, 0, 0, 0,
                   0);
}
// END SOURCE modules/Name_Tags/name_tags.cpp

// BEGIN SOURCE modules/Name_Tags/name_tags_update.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses
// evidence/recovered_cpp/behavior/module_behavior_recovery/name_tags_update/name_tags_update.cpp
// SHA-256 85a10e22bb2986eaca972bbfc061271c1117adc0ce9846d2cb89d20bf7ffd4d1
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.

#include "../runtime/shared/Text.hpp"
#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
using endpoint = reconstruction::native_binding::RenderEndpoint<8, std::uint64_t>;
using endpoint4 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
static uint64_t readWord_name_tags_update(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t readDword_name_tags_update(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static uint16_t h(const void *p) {
    uint16_t v;
    memcpy(&v, p, 2);
    return v;
}
static float readFloat_name_tags_update(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static void writeWord_name_tags_update(void *p, uint64_t v) {
    memcpy(p, &v, 8);
}
static void writeDword(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
static void wh(void *p, uint16_t v) {
    memcpy(p, &v, 2);
}
static void writeFloat(void *p, float v) {
    memcpy(p, &v, 4);
}
static float floatFromWord_name_tags_update(uint64_t v) {
    uint32_t b = (uint32_t)v;
    return readFloat_name_tags_update(&b);
}
static double gf(uint64_t v) {
    double a;
    memcpy(&a, &v, 8);
    return a;
}
static uint64_t gb(double v) {
    return readWord_name_tags_update(&v);
}
static float narrow_name_tags_update(double v) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(v)));
}
static float multiplyFloat_name_tags_update(float a, float b) {
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static uint64_t method_name_tags_update(uint64_t env, uint32_t slot) {
    return readWord_name_tags_update(
        (uint8_t *)(uintptr_t)(readWord_name_tags_update((uint8_t *)(uintptr_t)env) + slot));
}
static uint64_t env_of(uint8_t *gameContext) {
    return readWord_name_tags_update(
        (uint8_t *)(uintptr_t)(readWord_name_tags_update(gameContext) + 8));
}
static uint64_t c3(endpoint invokeEndpoint, uint64_t r, uint64_t a, uint64_t b, uint64_t c) {
    return invokeEndpoint(r, a, b, c, 0, 0, 0, 0, 0);
}
void reconstruction::name_tags::releaseTags(uint8_t *, uint8_t *, endpoint);
__declspec(dllexport) int32_t reconstruction::name_tags::compareDistance(const uint8_t *a,
                                                                         const uint8_t *b) {
    return _mm_cvttss_si32(
        _mm_sub_ss(_mm_load_ss((const float *)(b + 0x48)), _mm_load_ss((const float *)(a + 0x48))));
}
__declspec(dllexport) int32_t reconstruction::name_tags::compareEnchantment(const uint8_t *a,
                                                                            const uint8_t *b,
                                                                            uint8_t *stateImage) {
    uint32_t v = readDword_name_tags_update(stateImage + 0x153ac0 + 4 * (int64_t)(int16_t)h(a)) -
                 readDword_name_tags_update(stateImage + 0x153ac0 + 4 * (int64_t)(int16_t)h(b));
    int32_t result;
    memcpy(&result, &v, 4);
    return result;
}
static void update(uint8_t *event, uint8_t *stateImage, endpoint invokeEndpoint) {
    {

        uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord_name_tags_update(event + 8);
        reconstruction::name_tags::releaseTags(
            (uint8_t *)(uintptr_t)readWord_name_tags_update(gameContext), stateImage,
            invokeEndpoint);
        if (!readWord_name_tags_update(gameContext + 0x20))
            return;
        if (!readWord_name_tags_update(stateImage + 0x3007a0)) {
            uint64_t game = readWord_name_tags_update(gameContext),
                     env = readWord_name_tags_update((uint8_t *)(uintptr_t)(game + 8)), renderer;
            if (readDword_name_tags_update(
                    (uint8_t *)(uintptr_t)readWord_name_tags_update((uint8_t *)(uintptr_t)game))) {
                renderer = c3(invokeEndpoint, 0x22db0, game,
                              readWord_name_tags_update(gameContext + 0x18), 0);
            } else {
                renderer = c3(invokeEndpoint, 0x27b20, game, 0, 0);
                if (!renderer)
                    goto renderer_done;
            }
            writeWord_name_tags_update(
                stateImage + 0x3007a0,
                c3(invokeEndpoint, method_name_tags_update(env, 0xa8), env, renderer, 0));
        }
    renderer_done:;
        double self[3], self_previous[3];
        c3(invokeEndpoint, 0x23030, (uintptr_t)self, readWord_name_tags_update(gameContext),
           readWord_name_tags_update(gameContext + 0x28));
        c3(invokeEndpoint, 0x230d0, (uintptr_t)self_previous,
           readWord_name_tags_update(gameContext), readWord_name_tags_update(gameContext + 0x28));
        uint64_t list = c3(invokeEndpoint, 0x24600, readWord_name_tags_update(gameContext),
                           readWord_name_tags_update(gameContext + 0x20), 0),
                 saved_env = env_of(gameContext);
        uint64_t font = c3(invokeEndpoint, 0x22d40, readWord_name_tags_update(gameContext),
                           readWord_name_tags_update(gameContext + 0x18), 0);
        font = c3(invokeEndpoint, 0x272a0, readWord_name_tags_update(gameContext), font, 0);
        if (!font)
            return;
        uint64_t id_key = c3(invokeEndpoint, method_name_tags_update(saved_env, 0x538), saved_env,
                             (uintptr_t)(stateImage + 0x1537bb), 0),
                 level_key = c3(invokeEndpoint, method_name_tags_update(saved_env, 0x538),
                                saved_env, (uintptr_t)(stateImage + 0x1537be), 0);
        if (!id_key || !level_key)
            return;
        int32_t length =
            (int32_t)c3(invokeEndpoint, 0x24e50, readWord_name_tags_update(gameContext), list, 0);
        if (length <= 0)
            goto sorted;
        float max_health = readFloat_name_tags_update(stateImage + 0x15371c),
              max_absorb = readFloat_name_tags_update(stateImage + 0x153720),
              health_yellow = readFloat_name_tags_update(stateImage + 0x153724),
              health_red = readFloat_name_tags_update(stateImage + 0x153728),
              health_scale = readFloat_name_tags_update(stateImage + 0x15372c),
              distance_red = readFloat_name_tags_update(stateImage + 0x153734);
        for (uint32_t entryIndex = 0;; ++entryIndex) {
            {

                uint64_t entity = c3(invokeEndpoint, 0x24e80,
                                     readWord_name_tags_update(gameContext), list, entryIndex),
                         env = env_of(gameContext);
                uint8_t is_self =
                    (uint8_t)c3(invokeEndpoint, method_name_tags_update(env, 0xc0), env, entity,
                                readWord_name_tags_update(gameContext + 0x28));
                if (is_self) {
                    if (stateImage[reconstruction::name_tags::setting_offset::show_own_name_tag] !=
                        1)
                        goto next;
                    uint64_t settings =
                        c3(invokeEndpoint, 0x22cf0, readWord_name_tags_update(gameContext),
                           readWord_name_tags_update(gameContext + 0x18), 0);
                    if (!(uint32_t)c3(invokeEndpoint, 0x25310,
                                      readWord_name_tags_update(gameContext), settings, 0))
                        goto next;
                }
                uint32_t flags = (uint32_t)c3(invokeEndpoint, 0x2acb0,
                                              readWord_name_tags_update(gameContext), entity, 0);
                if (flags & 2)
                    goto next;
                if ((uint8_t)c3(invokeEndpoint, 0x237b0, readWord_name_tags_update(gameContext),
                                entity, 0))
                    goto next;
                double position[3], previous[3], copy_a[3], copy_b[3];
                c3(invokeEndpoint, 0x23030, (uintptr_t)position,
                   readWord_name_tags_update(gameContext), entity);
                memcpy(copy_a, position, 24);
                memcpy(copy_b, self, 24);
                double distance = recovered_vector_distance_squared(copy_a, copy_b);
                float range = readFloat_name_tags_update(
                    stateImage + reconstruction::name_tags::setting_offset::range);
                if (distance > (double)multiplyFloat_name_tags_update(range, range))
                    goto next;
                env = env_of(gameContext);
                uint64_t name;
                if (stateImage[reconstruction::name_tags::setting_offset::use_display_name] == 1) {
                    name = c3(invokeEndpoint, 0x23800, readWord_name_tags_update(gameContext),
                              entity, 0);
                    name = c3(invokeEndpoint, 0x26090, readWord_name_tags_update(gameContext), name,
                              0);
                    if (!stateImage[reconstruction::name_tags::setting_offset::show_health] &&
                        !stateImage[reconstruction::name_tags::setting_offset::show_distance])
                        goto label_ready;
                } else
                    name = c3(invokeEndpoint, 0x23830, readWord_name_tags_update(gameContext),
                              entity, 0);
                {
                    int32_t raw_length = (int32_t)c3(
                                invokeEndpoint, method_name_tags_update(env, 0x540), env, name, 0),
                            limit = raw_length < 64 ? raw_length : 64;
                    uint8_t *chars = (uint8_t *)(uintptr_t)c3(
                        invokeEndpoint, method_name_tags_update(env, 0x548), env, name, 0);
                    uint8_t builder[24];
                    recovered_text_initialize_dc20(builder, stateImage + 0x3007b0, 128);
                    if (stateImage[reconstruction::name_tags::setting_offset::show_health] == 1) {
                        float health = recovered_float_clamp_a1f0(
                                  0, max_health,
                                  floatFromWord_name_tags_update(
                                      c3(invokeEndpoint, 0x23a40,
                                         readWord_name_tags_update(gameContext), entity, 0))),
                              absorb = recovered_float_clamp_a1f0(
                                  0, max_absorb,
                                  floatFromWord_name_tags_update(
                                      c3(invokeEndpoint, 0x23fe0,
                                         readWord_name_tags_update(gameContext), entity, 0)));
                        uint32_t color = health_yellow > health ? 'e' : 'a';
                        if (health_red > health)
                            color = 'c';
                        uint32_t precision =
                            readDword_name_tags_update(
                                stateImage +
                                reconstruction::name_tags::setting_offset::health_fmt) == 1;
                        if (precision) {
                            health = multiplyFloat_name_tags_update(health, health_scale);
                            absorb = multiplyFloat_name_tags_update(absorb, health_scale);
                        }
                        uint64_t args[3] = {color, precision, gb((double)health)};
                        if (!recovered_text_format_dca0(builder, (char *)(stateImage + 0x1537e7),
                                                        args, invokeEndpoint))
                            goto label_ready;
                        if (absorb > 0) {
                            uint64_t more[2] = {precision, gb((double)absorb)};
                            if (!recovered_text_format_dca0(
                                    builder, (char *)(stateImage + 0x1537f0), more, invokeEndpoint))
                                goto label_ready;
                        }
                        if (!recovered_text_append_dc40(builder, (char *)(stateImage + 0x1537f9),
                                                        invokeEndpoint))
                            goto label_ready;
                    }
                    if (stateImage[reconstruction::name_tags::setting_offset::use_display_name] ==
                        1) {
                        if (!recovered_text_append_dc40(builder, (char *)chars, invokeEndpoint))
                            goto label_ready;
                    } else {
                        if (!recovered_text_append_dc40(builder, (char *)(stateImage + 0x153801),
                                                        invokeEndpoint))
                            goto label_ready;
                        if (!recovered_text_byte_dd10(builder, (flags & 5) ? 'a' : 'c'))
                            goto label_ready;
                        if (raw_length > 0)
                            for (int32_t i = 0; i < limit; ++i) {
                                if (chars[i] == 0xc2) {
                                    i += 2;
                                    continue;
                                }
                                if (!recovered_text_byte_dd10(builder, chars[i]))
                                    goto label_ready;
                            }
                    }
                    if (stateImage[reconstruction::name_tags::setting_offset::show_distance] == 1) {
                        uint64_t current_env = env_of(gameContext);
                        if (!(uint8_t)c3(invokeEndpoint, method_name_tags_update(current_env, 0xc0),
                                         current_env, readWord_name_tags_update(gameContext + 0x28),
                                         entity)) {
                            double root = distance >= 0
                                              ? _mm_cvtsd_f64(_mm_sqrt_sd(_mm_setzero_pd(),
                                                                          _mm_set_sd(distance)))
                                              : gf(c3(invokeEndpoint, 0xaf2f0, gb(distance), 0, 0));
                            float short_distance = narrow_name_tags_update(root);
                            uint32_t color =
                                readFloat_name_tags_update(stateImage + 0x153730) > short_distance
                                    ? 'e'
                                    : 'a';
                            if (distance_red > short_distance)
                                color = 'c';
                            uint64_t args[2] = {color, gb(root)};
                            if (!recovered_text_format_dca0(
                                    builder, (char *)(stateImage + 0x153804), args, invokeEndpoint))
                                goto label_ready;
                        }
                    }
                    c3(invokeEndpoint, method_name_tags_update(env, 0x550), env, name,
                       (uintptr_t)chars);
                    if (recovered_text_finish_dd40(builder))
                        name = c3(invokeEndpoint, method_name_tags_update(env, 0x538), env,
                                  (uintptr_t)(stateImage + 0x3007b0), 0);
                }
            label_ready:
                if (!name)
                    goto sorted;
                uint64_t label =
                    c3(invokeEndpoint, method_name_tags_update(env, 0xa8), env, name, 0);
                if (!label)
                    goto sorted;
                uint64_t global_entity = c3(
                    invokeEndpoint, method_name_tags_update(saved_env, 0xa8), saved_env, entity, 0);
                if (!global_entity) {
                    c3(invokeEndpoint, method_name_tags_update(saved_env, 0xb0), saved_env, label,
                       0);
                    goto sorted;
                }
                c3(invokeEndpoint, 0x230d0, (uintptr_t)previous,
                   readWord_name_tags_update(gameContext), entity);
                uint8_t version = (uint8_t)c3(invokeEndpoint, 0x23020,
                                              readWord_name_tags_update(gameContext), 0, 0);
                if (is_self && version) {
                    memcpy(copy_a, position, 24);
                    recovered_vector_adjust_95c0(copy_b, copy_a, stateImage);
                    memcpy(position, copy_b, 24);
                    memcpy(copy_a, previous, 24);
                    recovered_vector_adjust_95c0(copy_b, copy_a, stateImage);
                    memcpy(previous, copy_b, 24);
                }
                uint64_t count = readWord_name_tags_update(stateImage + 0x2fc910);
                writeWord_name_tags_update(stateImage + 0x2fc910, count + 1);
                uint8_t *record = stateImage + 0x2fc920 + 160 * count;
                memcpy(record + 0x28, position + 2, 8);
                memcpy(record + 0x18, position, 16);
                memcpy(record + 0x10, previous + 2, 8);
                memcpy(record, previous, 16);
                writeWord_name_tags_update(record + 0x30, global_entity);
                float dist = narrow_name_tags_update(distance);
                dist = dist >= 0
                           ? _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(dist)))
                           : floatFromWord_name_tags_update(c3(
                                 invokeEndpoint, 0xaf4a0, readDword_name_tags_update(&dist), 0, 0));
                writeFloat(record + 0x48, dist);
                memcpy(copy_a, self_previous, 24);
                memcpy(copy_b, record, 24);
                writeFloat(record + 0x44,
                           narrow_name_tags_update(recovered_vector_distance_94f0(copy_a, copy_b)));
                writeWord_name_tags_update(record + 0x38, label);
                writeDword(record + 0x40,
                           (uint32_t)c3(invokeEndpoint, 0x27560,
                                        readWord_name_tags_update(gameContext), font, label));
                writeDword(record + 0x4c, 0);
                for (uint32_t slot = 0; slot < 5; ++slot) {
                    uint8_t present = c3(invokeEndpoint, 0x24050,
                                         readWord_name_tags_update(gameContext), entity, slot) != 0;
                    if (present)
                        writeDword(record + 0x4c, readDword_name_tags_update(record + 0x4c) + 1);
                    record[0x50 + 16 * slot] = present;
                }
                if (stateImage[reconstruction::name_tags::setting_offset::show_enchants] == 1) {
                    uint64_t enchant_env = env_of(gameContext);
                    for (uint32_t slot = 0; slot < 5; ++slot) {
                        uint8_t *equipment = record + 0x50 + 16 * slot;
                        writeWord_name_tags_update(equipment + 8, 0);
                        writeDword(equipment + 4, 0);
                        uint64_t item = c3(invokeEndpoint, 0x24050,
                                           readWord_name_tags_update(gameContext), entity, slot);
                        if (!item)
                            continue;
                        uint64_t tags = c3(invokeEndpoint, 0x25de0,
                                           readWord_name_tags_update(gameContext), item, 0);
                        if (!tags)
                            continue;
                        int32_t raw_count =
                                    (int32_t)c3(invokeEndpoint, 0x27f10,
                                                readWord_name_tags_update(gameContext), tags, 0),
                                limit = raw_count < 25 ? raw_count : 25;
                        for (int32_t i = 0; i < limit; ++i) {
                            uint64_t tag =
                                c3(invokeEndpoint, 0x27f40, readWord_name_tags_update(gameContext),
                                   tags, (uint32_t)i);
                            uint16_t id =
                                (uint16_t)c3(invokeEndpoint, 0x27f70,
                                             readWord_name_tags_update(gameContext), tag, id_key);
                            if (id > 62 || ((UINT64_C(0x1ff0fff0ffc0fe00) >> id) & 1))
                                continue;
                            int16_t level =
                                (int16_t)c3(invokeEndpoint, 0x27f70,
                                            readWord_name_tags_update(gameContext), tag, level_key);
                            if (level <= 0)
                                level = 0;
                            if (level >= 99)
                                level = 99;
                            wh(stateImage + 0x300830 + 4 * i, id);
                            wh(stateImage + 0x300832 + 4 * i, (uint16_t)level);
                        }
                        invokeEndpoint(0x13d0f0, (uintptr_t)(stateImage + 0x300830),
                                       (uint64_t)(int64_t)limit, 4, UINT64_C(0x18003da60), 0, 0, 0,
                                       0);
                        int32_t shown = raw_count < 4 ? raw_count : 4;
                        uint64_t array =
                            c3(invokeEndpoint, 0x13cf60, (uint64_t)(int64_t)shown, 8, 0);
                        writeWord_name_tags_update(equipment + 8, array);
                        if (!array)
                            goto record_done;
                        for (int32_t i = 0; i < shown; ++i) {
                            uint16_t id = h(stateImage + 0x300830 + 4 * i);
                            uint64_t abbr =
                                id <= 62 ? readWord_name_tags_update(stateImage + 0x153870 + 8 * id)
                                         : 0;
                            if (abbr)
                                abbr = (uintptr_t)stateImage + (abbr - UINT64_C(0x180000000));
                            invokeEndpoint(
                                0xab710, (uintptr_t)(stateImage + 0x300894), 6,
                                (uintptr_t)(stateImage + 0x153864), abbr,
                                (uint32_t)(int32_t)(int16_t)h(stateImage + 0x300832 + 4 * i), 0, 0,
                                0);
                            uint64_t text =
                                c3(invokeEndpoint, method_name_tags_update(enchant_env, 0x538),
                                   enchant_env, (uintptr_t)(stateImage + 0x300894), 0);
                            if (!text)
                                goto record_done;
                            text = c3(invokeEndpoint, method_name_tags_update(enchant_env, 0xa8),
                                      enchant_env, text, 0);
                            if (!text)
                                goto record_done;
                            writeWord_name_tags_update(
                                (uint8_t *)(uintptr_t)(readWord_name_tags_update(equipment + 8) +
                                                       8 * i),
                                text);
                            writeDword(equipment + 4,
                                       readDword_name_tags_update(equipment + 4) + 1);
                        }
                    }
                }
            record_done:
                if (readWord_name_tags_update(stateImage + 0x2fc910) == 100)
                    break;
            }
        next:
            length = (int32_t)c3(invokeEndpoint, 0x24e50, readWord_name_tags_update(gameContext),
                                 list, 0);
            if ((int32_t)(entryIndex + 1) >= length)
                break;
        }
    }
sorted:
    invokeEndpoint(0x13d0f0, (uintptr_t)(stateImage + 0x2fc920),
                   readWord_name_tags_update(stateImage + 0x2fc910), 160, UINT64_C(0x18003da40), 0,
                   0, 0, 0);
}
__declspec(dllexport) void reconstruction::name_tags::updateTags(uint8_t *event,
                                                                 uint8_t *stateImage,
                                                                 endpoint invokeEndpoint) {
    update(event, stateImage, invokeEndpoint);
}
// END SOURCE modules/Name_Tags/name_tags_update.cpp

// BEGIN SOURCE modules/Name_Tags/Query.cpp
// Native RVA 0x3c1a0. Descriptor ownership is Name Tags (0x2f02d0),
// despite placement at the end of the supplied Friends candidate interval.
// The tail helper 0x274c0 is expanded here from the runtime instructions;
// the decompiler's uninitialized RBP argument is not passed by native code.
#ifndef SLINKY_SHARE_EEF8D7E7D514BABCDCC5
#define SLINKY_SHARE_EEF8D7E7D514BABCDCC5
// BEGIN SOURCE modules/Name_Tags/Query.hpp
#include "../runtime/shared/RenderNativeBindings.hpp"
#include "../runtime/native/verified/module_game_access.hpp"
namespace reconstruction::name_tags {
using VisibilityEndpoint = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
std::uint64_t queryNameTagValue(GameAccessBridge *, std::uintptr_t object, std::uintptr_t entity,
                                const std::uint8_t *stateImage, VisibilityEndpoint);
} // namespace reconstruction::name_tags
// END SOURCE modules/Name_Tags/Query.hpp

#endif // SLINKY_SHARE_EEF8D7E7D514BABCDCC5

#include <cstring>
namespace reconstruction::name_tags {
namespace {
std::uintptr_t readWord(const void *p) {
    std::uintptr_t value;
    std::memcpy(&value, p, sizeof value);
    return value;
}
} // namespace
std::uint64_t queryNameTagValue(GameAccessBridge *bridge, std::uintptr_t object,
                                std::uintptr_t entity, const std::uint8_t *stateImage,
                                VisibilityEndpoint invoke) {
    const auto address = reinterpret_cast<std::uintptr_t>(bridge);
    if (stateImage[0x2f02e4] == 1 && invoke(0x23f00, address, entity, 0, 0) != 0 &&
        static_cast<std::uint8_t>(invoke(0x2ace0, address, entity, 2, 0)) == 0)
        return 0;
    const auto *metadata = bridge->metadata;
    const auto environment = reinterpret_cast<std::uintptr_t>(bridge->environment);
    const auto table = readWord(reinterpret_cast<const void *>(environment));
    const auto field = readWord(metadata + 0x978);
    const auto target = readWord(reinterpret_cast<const std::uint8_t *>(table) + 0x128);
    return invoke(target, environment, object, field, entity);
}
} // namespace reconstruction::name_tags
// END SOURCE modules/Name_Tags/Query.cpp

// Convenient borrowed-state interface

namespace shareable {
class NameTags {
  public:
    static constexpr const char *kName = "Name Tags";
    static constexpr const char *kDescription = "Makes player name tags easier to see.";
    explicit NameTags(std::uint8_t *image) : image_(image) {}
    // Range. Config key: range.
    NumberSetting &range() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f05b8);
    }
    // Scale. Config key: scale.
    NumberSetting &scale() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f04e0);
    }
    // Show own name tag. Config key: show_own_name_tag.
    BooleanSetting &show_own_name_tag() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f05f0);
    }
    // Use display name format. Config key: use_display_name.
    BooleanSetting &use_display_name() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f0610);
    }
    // Distance scaling. Config key: distance_scaling.
    BooleanSetting &distance_scaling() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f0518);
    }
    // Text background. Config key: background.
    BooleanSetting &background() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f0538);
    }
    // Text shadow. Config key: text_shadow.
    BooleanSetting &text_shadow() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f0558);
    }
    // Health. Config key: show_health.
    BooleanSetting &show_health() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f0630);
    }
    // Health format. Config key: health_fmt.
    ChoiceSetting &health_fmt() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f0680);
    }
    // Option labels observed in the captured metadata.
    enum class HealthFmtMode : std::uint32_t { Hp020 = 0, Hearts00100 = 1 };
    // Distance. Config key: show_distance.
    BooleanSetting &show_distance() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f0650);
    }
    // Equipment. Config key: show_equipment.
    BooleanSetting &show_equipment() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f0578);
    }
    // Enchantments. Config key: show_enchants.
    BooleanSetting &show_enchants() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f0598);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_name_tags_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_name_tags_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_name_tags_settings(&context, image_, &dependencies);
    }
    void releaseTags(uint8_t *game, endpoint invokeEndpoint) {
        ::reconstruction::name_tags::releaseTags(game, image_, invokeEndpoint);
    }
    void onLifecycleEvent(uint8_t *event, endpoint invokeEndpoint) {
        ::reconstruction::name_tags::onLifecycleEvent(event, image_, invokeEndpoint);
    }
    void renderTags(uint8_t *event, endpoint invokeEndpoint) {
        ::reconstruction::name_tags::renderTags(event, image_, invokeEndpoint);
    }
    static int32_t compareDistance(const uint8_t *a, const uint8_t *b) {
        return ::reconstruction::name_tags::compareDistance(a, b);
    }
    int32_t compareEnchantment(const uint8_t *a, const uint8_t *b) {
        return ::reconstruction::name_tags::compareEnchantment(a, b, image_);
    }
    void updateTags(uint8_t *event, endpoint invokeEndpoint) {
        ::reconstruction::name_tags::updateTags(event, image_, invokeEndpoint);
    }
    static std::uint64_t queryNameTagValue(GameAccessBridge *bridge, std::uintptr_t object,
                                           std::uintptr_t entity, const std::uint8_t *stateImage,
                                           ::reconstruction::name_tags::VisibilityEndpoint invoke) {
        return ::reconstruction::name_tags::queryNameTagValue(bridge, object, entity, stateImage,
                                                              invoke);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
