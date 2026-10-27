// Trajectories

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Trajectories.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Trajectories.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Trajectories: lib_win settings 0x45e90.
static constexpr SettingsStep settings_steps_Surface_Trajectories[] = {
    {SettingsControl::number, "line_width", 0x2f4000},
    {SettingsControl::color, "color_hit", 0x2f4038},
    {SettingsControl::color, "color_miss", 0x2f4058},
    {SettingsControl::boolean, "render_throwables", 0x2f40d8},
    {SettingsControl::boolean, "render_pearls", 0x2f40b8},
    {SettingsControl::boolean, "render_bow", 0x2f4078},
    {SettingsControl::boolean, "render_uncharged_bow", 0x2f4098},
};
static constexpr ModuleSurface surface_Surface_Trajectories{
    nullptr, 0, settings_steps_Surface_Trajectories,
    std::size(settings_steps_Surface_Trajectories)};

extern "C" __declspec(dllexport) void
recovered_trajectories_settings(SettingsContext *context, std::uint8_t *image,
                                const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Trajectories, context, image, *dependencies);
}

// Trajectories: lib_win runtime UI 0x45dc0.
extern "C" __declspec(dllexport) void
recovered_trajectories_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                          const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f4000);
    dependencies->color(layout, ui, image + 0x2f4038);
    dependencies->color(layout, ui, image + 0x2f4058);
    dependencies->section(ui, layout, "Render when holding");
    dependencies->checkbox(layout, ui, image + 0x2f40d8);
    dependencies->checkbox(layout, ui, image + 0x2f40b8);
    dependencies->checkbox(layout, ui, image + 0x2f4078);
    if (image[0x2f4090] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2f4098);
    }
}
// END SOURCE native/verified/surfaces/Surface_Trajectories.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Trajectories
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Trajectories.cpp
extern "C" __declspec(dllexport) void
recovered_trajectories_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                                const BoundSurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f4000);
    dependencies->color(layout, ui, image + 0x2f4038);
    dependencies->color(layout, ui, image + 0x2f4058);
    dependencies->section(ui, layout, "Render when holding");
    dependencies->checkbox(layout, ui, image + 0x2f40d8);
    dependencies->checkbox(layout, ui, image + 0x2f40b8);
    dependencies->checkbox(layout, ui, image + 0x2f4078);
    if (image[0x2f4090] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2f4098);
    }
}
// END SOURCE shared/BoundSurfaces.cpp@Trajectories

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Trajectories/trajectories.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses evidence/recovered_cpp/behavior/module_behavior_recovery/trajectories/trajectories.cpp
// SHA-256 b83da9cc073af70a690881791595a6f6ade3a2045314c02b3a499e9ce251fc72
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.
#ifndef SLINKY_SHARE_4AD7110C6FF4A92F0A61
#define SLINKY_SHARE_4AD7110C6FF4A92F0A61
// BEGIN SOURCE modules/Trajectories/Module.hpp
#include "../runtime/shared/RenderNativeBindings.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_trajectories_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                                const BoundSurfaceUiDependencies *);
extern "C" void recovered_trajectories_settings(SettingsContext *, std::uint8_t *,
                                                const SurfaceSettingsDependencies *);

namespace reconstruction::trajectories {
// The image view retains native storage offsets. It does not invent initialization.
using Endpoint5 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
using Endpoint8 = reconstruction::native_binding::RenderEndpoint<7, std::uint64_t>;
__declspec(dllexport) void computeLaunch(uint8_t *ctx, double *input, uint64_t angle,
                                         float fraction, double *position, double *velocity,
                                         uint8_t *image, Endpoint5 call);
__declspec(dllexport) void onLifecycleEvent(uint8_t *event, uint8_t *image, Endpoint5 call);
__declspec(dllexport) void renderTrajectory(uint8_t *event, uint8_t *image, Endpoint5 call);
__declspec(dllexport) void updateTrajectory(uint8_t *event, uint8_t *image, Endpoint8 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_trajectories_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_trajectories_settings(context, stateImage, &deps);
}
} // namespace reconstruction::trajectories

namespace reconstruction::trajectories::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t line_width = 0x2f4000 + offsetof(NumberSetting, current);
inline constexpr std::size_t color_hit = 0x2f4038 + offsetof(ColorSetting, current);
inline constexpr std::size_t color_miss = 0x2f4058 + offsetof(ColorSetting, current);
inline constexpr std::size_t render_throwables = 0x2f40d8 + offsetof(BooleanSetting, current);
inline constexpr std::size_t render_pearls = 0x2f40b8 + offsetof(BooleanSetting, current);
inline constexpr std::size_t render_bow = 0x2f4078 + offsetof(BooleanSetting, current);
inline constexpr std::size_t render_uncharged_bow = 0x2f4098 + offsetof(BooleanSetting, current);
} // namespace reconstruction::trajectories::setting_offset
// END SOURCE modules/Trajectories/Module.hpp

#endif // SLINKY_SHARE_4AD7110C6FF4A92F0A61

#include <emmintrin.h>
#include <stdint.h>
#include <string.h>

using endpoint_trajectories = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
static uint64_t readWord_trajectories(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t readDword_trajectories(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static float readFloat_trajectories(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static double readDouble_trajectories(const void *p) {
    double v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t floatBits(float v) {
    return readDword_trajectories(&v);
}
static float floatFromWord(uint64_t v) {
    uint32_t b = (uint32_t)v;
    return readFloat_trajectories(&b);
}
static void writeFloat_trajectories(void *p, float v) {
    memcpy(p, &v, 4);
}
static float narrow_trajectories(double v) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(v)));
}
static float multiplyFloat_trajectories(float a, float b) {
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static uint64_t method(uint8_t *stateImage, uint32_t slot) {
    return readWord_trajectories((uint8_t *)(uintptr_t)readWord_trajectories(stateImage + slot));
}

__declspec(dllexport) void reconstruction::trajectories::computeLaunch(
    uint8_t *gameContext, double *input, uint64_t angle, float fraction, double *position,
    double *velocity, uint8_t *stateImage, endpoint_trajectories invokeEndpoint) {
    double radians = readDouble_trajectories(stateImage + 0x154e50);
    float yaw = narrow_trajectories((double)floatFromWord(angle) * radians),
          pitch = narrow_trajectories((double)floatFromWord(angle >> 32) * radians);
    float cy = floatFromWord(invokeEndpoint(0xb3590, floatBits(yaw), 0, 0, 0));
    float cp = floatFromWord(invokeEndpoint(0xb3590, floatBits(pitch), 0, 0, 0));
    float sy = floatFromWord(invokeEndpoint(0xb1cf0, floatBits(yaw), 0, 0, 0));
    float sp = floatFromWord(invokeEndpoint(0xb1cf0, floatBits(pitch), 0, 0, 0));
    uint32_t sign = readDword_trajectories(stateImage + 0x154e60);
    double direction[3] = {(double)multiplyFloat_trajectories(floatFromWord(floatBits(sy) ^ sign),
                                                              cp),
                           (double)floatFromWord(floatBits(sp) ^ sign),
                           (double)multiplyFloat_trajectories(cp, cy)},
           scaled[3];
    float speed =
        recovered_scalar_lerp_a2b0(readFloat_trajectories(stateImage + 0x30498c),
                                   readFloat_trajectories(stateImage + 0x304990), fraction);
    recovered_vector_scale_9430(scaled, direction, (double)speed);
    if (!(uint8_t)invokeEndpoint(0x23020, readWord_trajectories(gameContext), 0, 0, 0)) {
        double copy[3];
        memcpy(copy, input, 24);
        recovered_vector_y_offset_9590(input, copy, stateImage);
        if ((uint8_t)invokeEndpoint(0x236f0, readWord_trajectories(gameContext),
                                    readWord_trajectories(gameContext + 0x28), 0, 0))
            input[1] += readDouble_trajectories(stateImage + 0x154e70);
    }
    double offset = readDouble_trajectories(stateImage + 0x154e78);
    input[0] -= (double)cy * offset;
    input[1] += readDouble_trajectories(stateImage + 0x154e80);
    input[2] -= (double)sy * offset;
    memcpy(position, input, 24);
    memcpy(velocity, scaled, 24);
}

__declspec(dllexport) void trajectory_launch_adapter(uint8_t *event, uint8_t *stateImage,
                                                     endpoint_trajectories invokeEndpoint) {
    reconstruction::trajectories::computeLaunch(
        (uint8_t *)(uintptr_t)readWord_trajectories(event + 8),
        (double *)(uintptr_t)readWord_trajectories(event + 0x10),
        readWord_trajectories(event + 0x18), readFloat_trajectories(event + 0x20),
        (double *)(uintptr_t)readWord_trajectories(event + 0x28),
        (double *)(uintptr_t)readWord_trajectories(event + 0x30), stateImage, invokeEndpoint);
}

__declspec(dllexport) void
reconstruction::trajectories::onLifecycleEvent(uint8_t *event, uint8_t *stateImage,
                                               endpoint_trajectories invokeEndpoint) {
    if (event[0x18] || readWord_trajectories(event + 0x10) != (uintptr_t)(stateImage + 0x2f3df0))
        return;
    invokeEndpoint(0x13cf70, readWord_trajectories(stateImage + 0x304478), 0, 0, 0);
    memset(stateImage + 0x304478, 0, 16);
    invokeEndpoint(0x13cf70, readWord_trajectories(stateImage + 0x304488), 0, 0, 0);
    memset(stateImage + 0x304488, 0, 16);
}

__declspec(dllexport) void
reconstruction::trajectories::renderTrajectory(uint8_t *event, uint8_t *stateImage,
                                               endpoint_trajectories invokeEndpoint) {
    if (!readDword_trajectories(stateImage + 0x304498))
        return;
    uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord_trajectories(event + 0x20);
    uint64_t angle = invokeEndpoint(0x23170, readWord_trajectories(gameContext),
                                    readWord_trajectories(gameContext + 0x28), 0, 0);
    double current[3], previous[3], input[3], position[3], velocity[3];
    invokeEndpoint(0x23030, (uintptr_t)current, readWord_trajectories(gameContext),
                   readWord_trajectories(gameContext + 0x28), 0);
    invokeEndpoint(0x230d0, (uintptr_t)previous, readWord_trajectories(gameContext),
                   readWord_trajectories(gameContext + 0x28), 0);
    recovered_vector_lerp_9460(input, previous, current,
                               (double)readFloat_trajectories(event + 0x28));
    float fraction = readFloat_trajectories(event + 0x28);
    double camera[3];
    memcpy(camera, event + 8, 24);
    reconstruction::trajectories::computeLaunch(gameContext, input, angle, fraction, position,
                                                velocity, stateImage, invokeEndpoint);
    if (readDword_trajectories(stateImage + 0x304498)) {
        double drag = readDouble_trajectories(stateImage + 0x154df0);
        uint64_t entryIndex = 0;
        do {
            double a[3], b[3];
            memcpy(a, position, 24);
            memcpy(b, velocity, 24);
            recovered_geometry_add_9400(position, a, b);
            for (unsigned lane = 0; lane < 3; ++lane)
                writeFloat_trajectories(stateImage + 0x3044a0 + 12 * entryIndex + 4 * lane,
                                        narrow_trajectories(position[lane] - camera[lane]));
            memcpy(a, velocity, 24);
            recovered_vector_scale_9430(velocity, a, drag);
            velocity[1] -= (double)readFloat_trajectories(stateImage + 0x304988);
            ++entryIndex;
        } while (entryIndex < readDword_trajectories(stateImage + 0x304498));
    }
    invokeEndpoint(method(stateImage, 0x13e458), 0xbe2, 0, 0, 0);
    invokeEndpoint(method(stateImage, 0x150cb0),
                   readDword_trajectories(stateImage +
                                          reconstruction::trajectories::setting_offset::line_width),
                   0, 0, 0);
    uint8_t *color = stateImage + (stateImage[0x30449c]
                                       ? reconstruction::trajectories::setting_offset::color_hit
                                       : reconstruction::trajectories::setting_offset::color_miss);
    invokeEndpoint(method(stateImage, 0x150ca0), readDword_trajectories(color),
                   readDword_trajectories(color + 4), readDword_trajectories(color + 8), 0);
    invokeEndpoint(method(stateImage, 0x14fd08), 0x8074, 0, 0, 0);
    invokeEndpoint(method(stateImage, 0x14fd10), 3, 0x1406, 0, (uintptr_t)(stateImage + 0x3044a0));
    invokeEndpoint(method(stateImage, 0x154f98), 3, 0,
                   readDword_trajectories(stateImage + 0x304498), 0);
    if (stateImage[0x304950] == 1) {
        double low[3], high[3], center[3], half[3], motion[3], offset[3], relative[3],
            translation[3];
        memcpy(low, stateImage + 0x304958, 24);
        memcpy(high, stateImage + 0x304970, 24);
        recovered_vector_lerp_9460(center, low, high,
                                   readDouble_trajectories(stateImage + 0x154df8));
        memcpy(high, stateImage + 0x304970, 24);
        recovered_vector_subtract_93d0(half, high, center);
        double remaining = readDouble_trajectories(stateImage + 0x154e00) -
                           (double)readFloat_trajectories(event + 0x28);
        memcpy(motion, stateImage + 0x304460, 24);
        recovered_vector_scale_9430(offset, motion, remaining);
        memcpy(camera, event + 8, 24);
        recovered_vector_subtract_93d0(relative, center, camera);
        recovered_vector_subtract_93d0(translation, relative, offset);
        invokeEndpoint(method(stateImage, 0x150cc0), 0, 0, 0, 0);
        invokeEndpoint(method(stateImage, 0x150cd8), floatBits(narrow_trajectories(translation[0])),
                       floatBits(narrow_trajectories(translation[1])),
                       floatBits(narrow_trajectories(translation[2])), 0);
        invokeEndpoint(method(stateImage, 0x150cd0), floatBits(narrow_trajectories(half[0])),
                       floatBits(narrow_trajectories(half[1])),
                       floatBits(narrow_trajectories(half[2])), 0);
        recovered_render_293c0(stateImage, invokeEndpoint);
        recovered_render_29430(stateImage, invokeEndpoint);
        invokeEndpoint(method(stateImage, 0x150cb8), 0, 0, 0, 0);
    }
    recovered_render_295a0(stateImage, invokeEndpoint);
}
// END SOURCE modules/Trajectories/trajectories.cpp

// BEGIN SOURCE modules/Trajectories/trajectories_update.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses
// evidence/recovered_cpp/behavior/module_behavior_recovery/trajectories_update/trajectories_update.cpp
// SHA-256 b4a8a752d8aa1225f0cf9520e0ea3c44e5d03371fb42b074fa29b466b355f24a
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.

#include <emmintrin.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
using endpoint_trajectories_update =
    reconstruction::native_binding::RenderEndpoint<7, std::uint64_t>;
using short_endpoint = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
static uint64_t readWord_trajectories_update(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t readDword_trajectories_update(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static float readFloat_trajectories_update(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static double readDouble_trajectories_update(const void *p) {
    double v;
    memcpy(&v, p, 8);
    return v;
}
static void writeWord(void *p, uint64_t v) {
    memcpy(p, &v, 8);
}
static void writeDword(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
static void writeFloat_trajectories_update(void *p, float v) {
    memcpy(p, &v, 4);
}
static float narrow_trajectories_update(double v) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(v)));
}
static float addFloat(float a, float b) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float multiplyFloat_trajectories_update(float a, float b) {
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float divideFloat(float a, float b) {
    return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float minf(float a, float b) {
    return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
void reconstruction::trajectories::computeLaunch(uint8_t *, double *, uint64_t, float, double *,
                                                 double *, uint8_t *, short_endpoint);

__declspec(dllexport) double *recovered_box_sorted_96e0(double *out, const double *a,
                                                        const double *b) {
    __m128d az = _mm_load_sd(a + 2), bz = _mm_load_sd(b + 2), mask = _mm_cmpunord_sd(az, az);
    __m128d lo = _mm_or_pd(_mm_and_pd(mask, bz), _mm_andnot_pd(mask, _mm_min_sd(bz, az)));
    __m128d hi = _mm_or_pd(_mm_and_pd(mask, bz), _mm_andnot_pd(mask, _mm_max_sd(bz, az)));
    _mm_store_sd(out + 2, lo);
    __m128d av = _mm_loadu_pd(a), bv = _mm_loadu_pd(b);
    mask = _mm_cmpunord_pd(av, av);
    lo = _mm_or_pd(_mm_and_pd(mask, bv), _mm_andnot_pd(mask, _mm_min_pd(bv, av)));
    __m128d high = _mm_or_pd(_mm_and_pd(mask, bv), _mm_andnot_pd(mask, _mm_max_pd(bv, av)));
    _mm_storeu_pd(out, lo);
    _mm_storeu_pd(out + 3, high);
    _mm_store_sd(out + 5, hi);
    return out;
}
__declspec(dllexport) uint8_t *recovered_vector_index_ddc0(uint8_t *data, uint32_t stride,
                                                           const void *state, uint32_t entryIndex) {
    (void)state;
    return data + (uint32_t)(stride * entryIndex);
}
__declspec(dllexport) uint64_t
recovered_vector_append_ddd0(uint8_t *pointer, uint32_t stride, uint8_t *state, const void *value,
                             endpoint_trajectories_update invokeEndpoint) {
    uint32_t capacity = readDword_trajectories_update(state),
             count = readDword_trajectories_update(state + 4);
    uint64_t data = readWord_trajectories_update(pointer);
    if (count >= capacity) {
        uint32_t next = capacity ? capacity + capacity : 8;
        writeDword(state, next);
        data = invokeEndpoint(0x13cf90, data, (uint32_t)(next * stride), 0, 0, 0, 0, 0);
        if (!data) {
            invokeEndpoint(0x13d040, 0, 0, 0, 0, 0, 0, 0);
            abort();
        }
        writeWord(pointer, data);
        count = readDword_trajectories_update(state + 4);
    }
    writeDword(state + 4, count + 1);
    return invokeEndpoint(0xabbf0, data + (uint32_t)(count * stride), (uintptr_t)value, stride, 0,
                          0, 0, 0);
}
static float charge(uint32_t ticks, uint8_t *stateImage) {
    float t = divideFloat(_mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(), (int32_t)ticks)),
                          readFloat_trajectories_update(stateImage + 0x154e08));
    return divideFloat(addFloat(multiplyFloat_trajectories_update(t, t), addFloat(t, t)),
                       readFloat_trajectories_update(stateImage + 0x154e0c));
}
static float speed(float strength, uint8_t *stateImage) {
    double v = (double)minf(readFloat_trajectories_update(stateImage + 0x154e18), strength) *
               readDouble_trajectories_update(stateImage + 0x154e20);
    return narrow_trajectories_update(v + v);
}
static void update(uint8_t *event, uint8_t *stateImage,
                   endpoint_trajectories_update invokeEndpoint) {
    {

        uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord_trajectories_update(event + 8);
        if (gameContext[0x40] != 1 || (uint8_t)invokeEndpoint(0x29f80, 0, 0, 0, 0, 0, 0, 0))
            goto inactive;
        uint64_t settings =
            invokeEndpoint(0x22cf0, readWord_trajectories_update(gameContext),
                           readWord_trajectories_update(gameContext + 0x18), 0, 0, 0, 0, 0);
        if ((uint32_t)invokeEndpoint(0x25310, readWord_trajectories_update(gameContext), settings,
                                     0, 0, 0, 0, 0))
            goto inactive;
        uint64_t item =
            invokeEndpoint(0x28a50, readWord_trajectories_update(gameContext),
                           readWord_trajectories_update(gameContext + 0x28), 0, 0, 0, 0, 0);
        if (!item)
            goto inactive;
        uint32_t id = (uint32_t)invokeEndpoint(0x25c50, readWord_trajectories_update(gameContext),
                                               item, 0, 0, 0, 0, 0);
        uint8_t block_flag = 0, entity_flag = 1;
        if (id == 368) {
            if (stateImage[reconstruction::trajectories::setting_offset::render_pearls] != 1)
                goto inactive;
            block_flag = 1;
            entity_flag = 0;
        } else if (id == 332 || id == 344) {
            if (stateImage[reconstruction::trajectories::setting_offset::render_throwables] != 1)
                goto inactive;
        } else if (id != 261)
            goto inactive;
        if (id != 261) {
            writeFloat_trajectories_update(stateImage + 0x30498c, 1.5f);
            writeFloat_trajectories_update(stateImage + 0x304990, 1.5f);
            writeDword(stateImage + 0x304988, 0x3cf5c28f);
        } else {
            if (stateImage[reconstruction::trajectories::setting_offset::render_bow] != 1)
                goto inactive;
            writeDword(stateImage + 0x304988, 0x3d4ccccd);
            if ((uint8_t)invokeEndpoint(0x23f90, readWord_trajectories_update(gameContext),
                                        readWord_trajectories_update(gameContext + 0x28), 0, 0, 0,
                                        0, 0)) {
                uint32_t ticks = (uint32_t)invokeEndpoint(
                    0x23fc0, readWord_trajectories_update(gameContext),
                    readWord_trajectories_update(gameContext + 0x28), 0, 0, 0, 0, 0);
                float now = charge(72000u - ticks, stateImage);
                double threshold = readDouble_trajectories_update(stateImage + 0x154e10);
                if (threshold > (double)now) {
                    writeFloat_trajectories_update(stateImage + 0x304990, 0);
                    goto inactive;
                }
                float current = speed(now, stateImage);
                writeFloat_trajectories_update(stateImage + 0x304990, current);
                if (current == 0)
                    goto inactive;
                float before = charge(71999u - ticks, stateImage);
                writeFloat_trajectories_update(
                    stateImage + 0x30498c,
                    threshold > (double)before ? 0.f : speed(before, stateImage));
            } else {
                if (stateImage
                        [reconstruction::trajectories::setting_offset::render_uncharged_bow] != 1)
                    goto inactive;
                writeFloat_trajectories_update(stateImage + 0x30498c, 3.f);
                writeFloat_trajectories_update(stateImage + 0x304990, 3.f);
            }
        }
        uint64_t angle =
            invokeEndpoint(0x23170, readWord_trajectories_update(gameContext),
                           readWord_trajectories_update(gameContext + 0x28), 0, 0, 0, 0, 0);
        double input[3], position[3], velocity[3];
        invokeEndpoint(0x23030, (uintptr_t)input, readWord_trajectories_update(gameContext),
                       readWord_trajectories_update(gameContext + 0x28), 0, 0, 0, 0);
        reconstruction::trajectories::computeLaunch(gameContext, input, angle, 0.f, position,
                                                    velocity, stateImage,
                                                    short_endpoint(invokeEndpoint));
        writeDword(stateImage + 0x304484, 0);
        writeDword(stateImage + 0x304494, 0);
        uint64_t list =
            invokeEndpoint(0x24620, readWord_trajectories_update(gameContext),
                           readWord_trajectories_update(gameContext + 0x20), 0, 0, 0, 0, 0);
        double horizontal = readDouble_trajectories_update(stateImage + 0x154e28),
               low[3] = {position[0], -100., position[2]},
               high[3] = {velocity[0] * horizontal + position[0],
                          position[1] + readDouble_trajectories_update(stateImage + 0x154e30),
                          horizontal * velocity[2] + position[2]},
               broad[6];
        recovered_box_sorted_96e0(broad, low, high);
        if ((int32_t)invokeEndpoint(0x24e50, readWord_trajectories_update(gameContext), list, 0, 0,
                                    0, 0, 0) > 0) {
            double margin = readDouble_trajectories_update(stateImage + 0x154e38);
            uint32_t entryIndex = 0;
            do {
                {

                    uint64_t entity =
                                 invokeEndpoint(0x24e80, readWord_trajectories_update(gameContext),
                                                list, entryIndex, 0, 0, 0, 0),
                             env = readWord_trajectories_update(
                                 (uint8_t *)(uintptr_t)(readWord_trajectories_update(gameContext) +
                                                        8));
                    uint64_t equal = readWord_trajectories_update(
                        (uint8_t *)(uintptr_t)(readWord_trajectories_update(
                                                   (uint8_t *)(uintptr_t)env) +
                                               0xc0));
                    if ((uint8_t)invokeEndpoint(equal, env, entity,
                                                readWord_trajectories_update(gameContext + 0x28), 0,
                                                0, 0, 0))
                        goto next;
                    if (!(uint8_t)invokeEndpoint(0x23900, readWord_trajectories_update(gameContext),
                                                 entity, 0, 0, 0, 0, 0))
                        goto next;
                    uint64_t box_object = invokeEndpoint(
                        0x23670, readWord_trajectories_update(gameContext), entity, 0, 0, 0, 0, 0);
                    double box[6], expanded[6];
                    invokeEndpoint(0x25640, (uintptr_t)box,
                                   readWord_trajectories_update(gameContext), box_object, 0, 0, 0,
                                   0);
                    recovered_box_expand_9770(expanded, box, margin);
                    if (recovered_geometry_intersects_97d0(expanded, broad)) {
                        recovered_vector_append_ddd0(stateImage + 0x304478, 8,
                                                     stateImage + 0x304480, &entity,
                                                     invokeEndpoint);
                        recovered_vector_append_ddd0(stateImage + 0x304488, 48,
                                                     stateImage + 0x304490, expanded,
                                                     invokeEndpoint);
                    }
                }
            next:
                ++entryIndex;
            } while ((int32_t)entryIndex <
                     (int32_t)invokeEndpoint(0x24e50, readWord_trajectories_update(gameContext),
                                             list, 0, 0, 0, 0, 0));
        }
        double drag = readDouble_trajectories_update(stateImage + 0x154e48),
               block_size = readDouble_trajectories_update(stateImage + 0x154e40);
        for (uint32_t step = 0; step != 100; ++step) {
            double old[3], v[3], temporary[3], inverse[3];
            memcpy(old, position, 24);
            memcpy(v, velocity, 24);
            recovered_geometry_add_9400(position, old, v);
            memcpy(temporary, old, 24);
            uint64_t from = invokeEndpoint(0x254f0, readWord_trajectories_update(gameContext),
                                           (uintptr_t)temporary, 0, 0, 0, 0, 0);
            memcpy(temporary, position, 24);
            uint64_t to = invokeEndpoint(0x254f0, readWord_trajectories_update(gameContext),
                                         (uintptr_t)temporary, 0, 0, 0, 0, 0);
            uint64_t hit =
                invokeEndpoint(0x24860, readWord_trajectories_update(gameContext),
                               readWord_trajectories_update(gameContext + 0x20), from, to, 0, 1, 0);
            if (hit) {
                writeDword(stateImage + 0x304498, step + 1);
                stateImage[0x304950] = 1;
                stateImage[0x30449c] = block_flag;
                uint64_t point = invokeEndpoint(0x24bf0, readWord_trajectories_update(gameContext),
                                                hit, 0, 0, 0, 0, 0);
                invokeEndpoint(0x25540, (uintptr_t)position,
                               readWord_trajectories_update(gameContext), point, 0, 0, 0, 0);
                recovered_vector_subtract_93d0(velocity, position, old);
                double corner[3], size[3] = {block_size, block_size, block_size}, end[3], box[6];
                invokeEndpoint(0x24c10, (uintptr_t)corner,
                               readWord_trajectories_update(gameContext), hit, 0, 0, 0, 0);
                recovered_geometry_add_9400(end, corner, size);
                recovered_geometry_pair_96b0(box, corner, end);
                memcpy(stateImage + 0x304958, box, 48);
                memset(stateImage + 0x304460, 0, 24);
            }
            memcpy(v, velocity, 24);
            recovered_vector_reciprocal_9650(inverse, v, stateImage);
            for (uint64_t entryIndex = 0;
                 entryIndex < readDword_trajectories_update(stateImage + 0x304494); ++entryIndex) {
                double box[6];
                memcpy(
                    box,
                    recovered_vector_index_ddc0(
                        (uint8_t *)(uintptr_t)readWord_trajectories_update(stateImage + 0x304488),
                        48, stateImage + 0x304490, (uint32_t)entryIndex),
                    48);
                if ((uint8_t)recovered_box_ray_98e0(box, old, inverse, stateImage)) {
                    writeDword(stateImage + 0x304498, step + 1);
                    stateImage[0x304950] = 1;
                    stateImage[0x30449c] = entity_flag;
                    memcpy(stateImage + 0x304958, box, 48);
                    uint64_t entity = readWord_trajectories_update(recovered_vector_index_ddc0(
                        (uint8_t *)(uintptr_t)readWord_trajectories_update(stateImage + 0x304478),
                        8, stateImage + 0x304480, (uint32_t)entryIndex));
                    double current[3], previous[3], movement[3];
                    invokeEndpoint(0x23030, (uintptr_t)current,
                                   readWord_trajectories_update(gameContext), entity, 0, 0, 0, 0);
                    invokeEndpoint(0x230d0, (uintptr_t)previous,
                                   readWord_trajectories_update(gameContext), entity, 0, 0, 0, 0);
                    recovered_vector_subtract_93d0(movement, current, previous);
                    memcpy(stateImage + 0x304460, movement, 24);
                    return;
                }
            }
            if (hit)
                return;
            memcpy(v, velocity, 24);
            recovered_vector_scale_9430(velocity, v, drag);
            velocity[1] -= (double)readFloat_trajectories_update(stateImage + 0x304988);
        }
        writeDword(stateImage + 0x304498, 100);
        stateImage[0x304950] = 0;
        stateImage[0x30449c] = 0;
        return;
    }
inactive:
    writeDword(stateImage + 0x304498, 0);
}
__declspec(dllexport) void
reconstruction::trajectories::updateTrajectory(uint8_t *event, uint8_t *stateImage,
                                               endpoint_trajectories_update invokeEndpoint) {
    update(event, stateImage, invokeEndpoint);
}
__declspec(dllexport) void trajectory_sorted_adapter(uint8_t *event, uint8_t *stateImage,
                                                     endpoint_trajectories_update invokeEndpoint) {
    (void)stateImage;
    (void)invokeEndpoint;
    recovered_box_sorted_96e0((double *)(uintptr_t)readWord_trajectories_update(event),
                              (double *)(uintptr_t)readWord_trajectories_update(event + 8),
                              (double *)(uintptr_t)readWord_trajectories_update(event + 16));
}
__declspec(dllexport) void trajectory_expand_adapter(uint8_t *event, uint8_t *stateImage,
                                                     endpoint_trajectories_update invokeEndpoint) {
    (void)stateImage;
    (void)invokeEndpoint;
    recovered_box_expand_9770((double *)(uintptr_t)readWord_trajectories_update(event),
                              (double *)(uintptr_t)readWord_trajectories_update(event + 8),
                              readDouble_trajectories_update(event + 16));
}
// END SOURCE modules/Trajectories/trajectories_update.cpp

// Convenient borrowed-state interface

namespace shareable {
class Trajectories {
  public:
    static constexpr const char *kName = "Trajectories";
    static constexpr const char *kDescription = "Predicts the trajectory of the item in your hand.";
    explicit Trajectories(std::uint8_t *image) : image_(image) {}
    // Line width. Config key: line_width.
    NumberSetting &line_width() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f4000);
    }
    // color_hit. Config key: color_hit.
    ColorSetting &color_hit() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2f4038);
    }
    // color_miss. Config key: color_miss.
    ColorSetting &color_miss() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2f4058);
    }
    // Snowballs/eggs. Config key: render_throwables.
    BooleanSetting &render_throwables() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f40d8);
    }
    // Enderpearls. Config key: render_pearls.
    BooleanSetting &render_pearls() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f40b8);
    }
    // Bow. Config key: render_bow.
    BooleanSetting &render_bow() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4078);
    }
    // Bow (uncharged). Config key: render_uncharged_bow.
    BooleanSetting &render_uncharged_bow() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4098);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_trajectories_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_trajectories_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_trajectories_settings(&context, image_, &dependencies);
    }
    void computeLaunch(uint8_t *gameContext, double *input, uint64_t angle, float fraction,
                       double *position, double *velocity, endpoint_trajectories invokeEndpoint) {
        ::reconstruction::trajectories::computeLaunch(gameContext, input, angle, fraction, position,
                                                      velocity, image_, invokeEndpoint);
    }
    void onLifecycleEvent(uint8_t *event, endpoint_trajectories invokeEndpoint) {
        ::reconstruction::trajectories::onLifecycleEvent(event, image_, invokeEndpoint);
    }
    void renderTrajectory(uint8_t *event, endpoint_trajectories invokeEndpoint) {
        ::reconstruction::trajectories::renderTrajectory(event, image_, invokeEndpoint);
    }
    static uint64_t vectorAppendDdd0(uint8_t *pointer, uint32_t stride, uint8_t *state,
                                     const void *value,
                                     endpoint_trajectories_update invokeEndpoint) {
        return ::recovered_vector_append_ddd0(pointer, stride, state, value, invokeEndpoint);
    }
    void updateTrajectory(uint8_t *event, endpoint_trajectories_update invokeEndpoint) {
        ::reconstruction::trajectories::updateTrajectory(event, image_, invokeEndpoint);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
