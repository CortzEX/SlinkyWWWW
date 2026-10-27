// Indicators

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Indicators.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Indicators.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Indicators: lib_win settings 0x3f360.
// UI 0x3f2a0.
static constexpr UiStep ui_steps_Surface_Indicators[] = {
    {UiControl::section, "Main", 0},          {UiControl::number, nullptr, 0x2f1650},
    {UiControl::number, nullptr, 0x2f1688},   {UiControl::section, "Warn for", 0},
    {UiControl::checkbox, nullptr, 0x2f16c0}, {UiControl::checkbox, nullptr, 0x2f16e0},
    {UiControl::checkbox, nullptr, 0x2f1700}, {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2f1720},
};
static constexpr SettingsStep settings_steps_Surface_Indicators[] = {
    {SettingsControl::number, "scale", 0x2f1650},
    {SettingsControl::number, "radius", 0x2f1688},
    {SettingsControl::boolean, "show_arrow", 0x2f16c0},
    {SettingsControl::boolean, "show_fireball", 0x2f16e0},
    {SettingsControl::boolean, "show_pearl", 0x2f1700},
    {SettingsControl::boolean, "require_coming_closer", 0x2f1720},
};
static constexpr ModuleSurface surface_Surface_Indicators{
    ui_steps_Surface_Indicators, std::size(ui_steps_Surface_Indicators),
    settings_steps_Surface_Indicators, std::size(settings_steps_Surface_Indicators)};

extern "C" __declspec(dllexport) void
recovered_indicators_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                        const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Indicators, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_indicators_settings(SettingsContext *context, std::uint8_t *image,
                              const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Indicators, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Indicators.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Indicators
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Indicators.cpp
static constexpr UiStep surface_indicators_ui_steps[] = {
    {UiControl::section, "Main", 0},          {UiControl::number, nullptr, 0x2f1650},
    {UiControl::number, nullptr, 0x2f1688},   {UiControl::section, "Warn for", 0},
    {UiControl::checkbox, nullptr, 0x2f16c0}, {UiControl::checkbox, nullptr, 0x2f16e0},
    {UiControl::checkbox, nullptr, 0x2f1700}, {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2f1720},
};
static constexpr SettingsStep surface_indicators_settings_steps[] = {
    {SettingsControl::number, "scale", 0x2f1650},
    {SettingsControl::number, "radius", 0x2f1688},
    {SettingsControl::boolean, "show_arrow", 0x2f16c0},
    {SettingsControl::boolean, "show_fireball", 0x2f16e0},
    {SettingsControl::boolean, "show_pearl", 0x2f1700},
    {SettingsControl::boolean, "require_coming_closer", 0x2f1720},
};
static constexpr ModuleSurface surface_indicators_surface{
    surface_indicators_ui_steps, std::size(surface_indicators_ui_steps),
    surface_indicators_settings_steps, std::size(surface_indicators_settings_steps)};

extern "C" __declspec(dllexport) void
recovered_indicators_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                              const BoundSurfaceUiDependencies *dependencies) {
    render_module_surface(surface_indicators_surface, ui, layout, image, *dependencies);
}
// END SOURCE shared/BoundSurfaces.cpp@Indicators

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Indicators/indicators.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses evidence/recovered_cpp/behavior/module_behavior_recovery/indicators/indicators.cpp
// SHA-256 575aa17eec1d60a689480b8b1552d745696033e9b537839b4110add01afeef97
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.
#ifndef SLINKY_SHARE_CFCC88DE759038EAF664
#define SLINKY_SHARE_CFCC88DE759038EAF664
// BEGIN SOURCE modules/Indicators/Module.hpp
#include "../runtime/shared/RenderNativeBindings.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_indicators_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                              const BoundSurfaceUiDependencies *);
extern "C" void recovered_indicators_settings(SettingsContext *, std::uint8_t *,
                                              const SurfaceSettingsDependencies *);

namespace reconstruction::indicators {
// The image view retains native storage offsets. It does not invent initialization.
using Endpoint8 = reconstruction::native_binding::RenderEndpoint<7, std::uint64_t>;
using Endpoint5 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
using Dependency5 = reconstruction::native_binding::RenderEndpoint<4, std::uint32_t>;
__declspec(dllexport) void onLifecycleEvent(uint8_t *event, uint8_t *image, Endpoint8 call);
__declspec(dllexport) void renderIndicators(uint8_t *event, uint8_t *image, Endpoint8 call);
__declspec(dllexport) void updateIndicators(uint8_t *event, uint8_t *image, Endpoint8 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_indicators_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_indicators_settings(context, stateImage, &deps);
}
} // namespace reconstruction::indicators

namespace reconstruction::indicators::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t scale = 0x2f1650 + offsetof(NumberSetting, current);
inline constexpr std::size_t radius = 0x2f1688 + offsetof(NumberSetting, current);
inline constexpr std::size_t show_arrow = 0x2f16c0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_fireball = 0x2f16e0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_pearl = 0x2f1700 + offsetof(BooleanSetting, current);
inline constexpr std::size_t require_coming_closer = 0x2f1720 + offsetof(BooleanSetting, current);
} // namespace reconstruction::indicators::setting_offset
// END SOURCE modules/Indicators/Module.hpp

#endif // SLINKY_SHARE_CFCC88DE759038EAF664

#include "../runtime/shared/AngleCompatibility.hpp"
#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
using endpoint = reconstruction::native_binding::RenderEndpoint<7, std::uint64_t>;
using endpoint4 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
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
static void writeDword(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
static float narrow(double v) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(v)));
}
static float subtractFloat(float a, float b) {
    return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static uint64_t target(uint64_t holder) {
    return readWord((uint8_t *)(uintptr_t)holder);
}
static uint64_t method(uint8_t *stateImage, uint32_t slot) {
    return target(readWord(stateImage + slot));
}
static uint64_t virtual_method(uint64_t env, uint32_t offset) {
    return readWord((uint8_t *)(uintptr_t)(readWord((uint8_t *)(uintptr_t)env) + offset));
}

static void release(uint8_t *gameContext, uint8_t *stateImage, endpoint invokeEndpoint) {
    uint64_t count = readWord(stateImage + 0x301ea0);
    if (count) {
        uint64_t env = readWord((uint8_t *)(uintptr_t)(readWord(gameContext) + 8)), entryIndex = 0;
        uint8_t *record = stateImage + 0x301eb0;
        do {
            uint64_t ref = readWord(record + 0x28);
            if (ref) {
                invokeEndpoint(virtual_method(env, 0xb0), env, ref, 0, 0, 0, 0, 0);
                count = readWord(stateImage + 0x301ea0);
            }
            ++entryIndex;
            record += 56;
        } while (entryIndex < count);
    }
    writeWord(stateImage + 0x301ea0, 0);
}
__declspec(dllexport) void reconstruction::indicators::onLifecycleEvent(uint8_t *event,
                                                                        uint8_t *stateImage,
                                                                        endpoint invokeEndpoint) {
    if (event[0x18] || readWord(event + 0x10) != (uintptr_t)(stateImage + 0x2f1440))
        return;
    release((uint8_t *)(uintptr_t)readWord(event + 8), stateImage, invokeEndpoint);
}
__declspec(dllexport) void reconstruction::indicators::renderIndicators(uint8_t *event,
                                                                        uint8_t *stateImage,
                                                                        endpoint invokeEndpoint) {
    uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord(event + 8);
    release(gameContext, stateImage, invokeEndpoint);
    if (!readWord(gameContext + 0x20))
        return;
    uint64_t camera =
        invokeEndpoint(0x22d40, readWord(gameContext), readWord(gameContext + 0x18), 0, 0, 0, 0, 0);
    uint64_t font = invokeEndpoint(0x272a0, readWord(gameContext), camera, 0, 0, 0, 0, 0);
    if (!font)
        return;
    double self[3];
    invokeEndpoint(0x23030, (uintptr_t)self, readWord(gameContext), readWord(gameContext + 0x28), 0,
                   0, 0, 0);
    uint64_t list =
        invokeEndpoint(0x24620, readWord(gameContext), readWord(gameContext + 0x20), 0, 0, 0, 0, 0);
    if ((int32_t)invokeEndpoint(0x24e50, readWord(gameContext), list, 0, 0, 0, 0, 0) <= 0)
        return;
    double yellow_threshold = readDouble(stateImage + 0x154028),
           white_threshold = readDouble(stateImage + 0x154030);
    uint32_t entryIndex = 0;
    do {
        {

            uint64_t entity =
                invokeEndpoint(0x24e80, readWord(gameContext), list, entryIndex, 0, 0, 0, 0);
            uint32_t type =
                (uint32_t)invokeEndpoint(0x23860, readWord(gameContext), entity, 0, 0, 0, 0, 0);
            if (type == 14) {
                if (!stateImage[reconstruction::indicators::setting_offset::show_pearl])
                    goto next;
            } else if (type == 12) {
                if (!stateImage[reconstruction::indicators::setting_offset::show_fireball])
                    goto next;
            } else if (type == 10) {
                if (!stateImage[reconstruction::indicators::setting_offset::show_arrow] ||
                    (uint8_t)invokeEndpoint(0x27fa0, readWord(gameContext), entity, 0, 0, 0, 0, 0))
                    goto next;
            } else
                goto next;
            double position[3], previous[3];
            invokeEndpoint(0x23030, (uintptr_t)position, readWord(gameContext), entity, 0, 0, 0, 0);
            invokeEndpoint(0x230d0, (uintptr_t)previous, readWord(gameContext), entity, 0, 0, 0, 0);
            double distance = recovered_vector_distance_squared(position, self);
            if (stateImage[reconstruction::indicators::setting_offset::require_coming_closer] ==
                    1 &&
                distance > recovered_vector_distance_squared(previous, self))
                goto next;
            if (!(distance >= 0)) {
                uint64_t result = invokeEndpoint(0xaf2f0, readWord(&distance), 0, 0, 0, 0, 0, 0);
                distance = readDouble(&result);
            } else
                distance = _mm_cvtsd_f64(_mm_sqrt_sd(_mm_setzero_pd(), _mm_set_sd(distance)));
            uint64_t old = readWord(stateImage + 0x301ea0);
            writeWord(stateImage + 0x301ea0, old + 1);
            uint8_t *record = stateImage + 0x301eb0 + 56 * old;
            memcpy(record, position, 8);
            memcpy(record + 8, position + 2, 8);
            memcpy(record + 16, previous, 8);
            memcpy(record + 24, previous + 2, 8);
            writeDword(record + 0x20, type);
            uint64_t env = readWord((uint8_t *)(uintptr_t)(readWord(gameContext) + 8));
            invokeEndpoint(0xab710, (uintptr_t)(stateImage + 0x3020e0), 10,
                           (uintptr_t)(stateImage + 0x1540a8), readWord(&distance), 0, 0, 0);
            uint64_t local = invokeEndpoint(virtual_method(env, 0x538), env,
                                            (uintptr_t)(stateImage + 0x3020e0), 0, 0, 0, 0, 0);
            if (!local)
                writeWord(record + 0x28, 0);
            else {
                uint64_t global =
                    invokeEndpoint(virtual_method(env, 0xa8), env, local, 0, 0, 0, 0, 0);
                writeWord(record + 0x28, global);
                if (global) {
                    uint32_t width = (uint32_t)invokeEndpoint(0x27560, readWord(gameContext), font,
                                                              global, 0, 0, 0, 0);
                    uint32_t color = distance > yellow_threshold ? 0xffffff00 : 0xffff0000;
                    writeDword(record + 0x30, width);
                    if (distance > white_threshold)
                        color = 0xffffffff;
                    writeDword(record + 0x34, color);
                }
            }
            if (readWord(stateImage + 0x301ea0) == 10)
                return;
        }
    next:
        ++entryIndex;
    } while ((int32_t)entryIndex <
             (int32_t)invokeEndpoint(0x24e50, readWord(gameContext), list, 0, 0, 0, 0, 0));
}

static void render(uint8_t *event, uint8_t *stateImage, endpoint invokeEndpoint) {
    if (!readWord(stateImage + 0x301ea0))
        return;
    uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord(event + 0x20);
    float partial = readFloat(event + 0x40);
    uint64_t camera = invokeEndpoint(0x22d40, readWord(gameContext), readWord(gameContext + 0x18),
                                     0, 0, 0, 0, 0),
             font = invokeEndpoint(0x272a0, readWord(gameContext), camera, 0, 0, 0, 0, 0);
    float yaw =
        floatFromWord(invokeEndpoint(0x27250, readWord(gameContext), camera, 0, 0, 0, 0, 0));
    recovered_render_29500(stateImage, invokeEndpoint);
    uint64_t center =
        recovered_angle_scale_9e60(readWord(event + 0x28), readFloat(stateImage + 0x153fe0));
    invokeEndpoint(method(stateImage, 0x150cc0), 0, 0, 0, 0, 0, 0, 0);
    uint64_t translate = readWord(stateImage + 0x150cd8);
    invokeEndpoint(target(translate), (uint32_t)center, (uint32_t)(center >> 32), 0, 0, 0, 0, 0);
    invokeEndpoint(method(stateImage, 0x150cb0), readDword(stateImage + 0x153fe4), 0, 0, 0, 0, 0,
                   0);
    invokeEndpoint(method(stateImage, 0x13e458), 0xb20, 0, 0, 0, 0, 0, 0);
    uint64_t clock = invokeEndpoint(0x4c270, 0, 0, 0, 0, 0, 0, 0);
    double phase = readDouble(&clock) * readDouble(stateImage + 0x153fe8);
    uint64_t wave = invokeEndpoint(0xb1990, readWord(&phase), 0, 0, 0, 0, 0, 0);
    if (readWord(stateImage + 0x301ea0)) {
        double half = readDouble(stateImage + 0x153ff0);
        float alpha = narrow(readDouble(&wave) * half + half);
        double angle_offset = readDouble(stateImage + 0x154008);
        float one = readFloat(stateImage + 0x153fe4),
              marker_offset = readFloat(stateImage + 0x154020),
              marker_scale = readFloat(stateImage + 0x154024);
        uint32_t sign = readDword(stateImage + 0x154010);
        uint64_t scale = readWord(stateImage + 0x150cd0), color = readWord(stateImage + 0x13e448),
                 entryIndex = 0;
        uint8_t *record = stateImage + 0x301eb0;
        do {
            double px = (double)recovered_scalar_lerp_a2b0(narrow(readDouble(record + 16)),
                                                           narrow(readDouble(record)), partial),
                   pz = (double)recovered_scalar_lerp_a2b0(narrow(readDouble(record + 24)),
                                                           narrow(readDouble(record + 8)), partial);
            px -= readDouble(event + 8);
            pz -= readDouble(event + 0x18);
            uint64_t angle_bits =
                invokeEndpoint(0x13cfb0, readWord(&pz), readWord(&px), 0, 0, 0, 0, 0);
            float angle = recovered_angle_wrap_a210(
                subtractFloat(narrow((readDouble(&angle_bits) * readDouble(stateImage + 0x153ff8)) /
                                         readDouble(stateImage + 0x154000) +
                                     angle_offset),
                              yaw),
                stateImage, nullptr);
            invokeEndpoint(method(stateImage, 0x150cc0), 0, 0, 0, 0, 0, 0, 0);
            invokeEndpoint(method(stateImage, 0x150cc8), floatBits(angle), 0, 0, floatBits(one), 0,
                           0, 0);
            float size = readFloat(stateImage + reconstruction::indicators::setting_offset::scale);
            invokeEndpoint(
                target(translate), 0,
                readDword(stateImage + reconstruction::indicators::setting_offset::radius) ^ sign,
                0, 0, 0, 0, 0);
            invokeEndpoint(target(scale), floatBits(size), floatBits(size), floatBits(size), 0, 0,
                           0, 0);
            if (readWord(record + 0x28)) {
                invokeEndpoint(method(stateImage, 0x150cc0), 0, 0, 0, 0, 0, 0, 0);
                invokeEndpoint(method(stateImage, 0x150cc8), floatBits(angle) ^ sign, 0, 0,
                               floatBits(one), 0, 0, 0);
                if (event[0x44] == 1) {
                    invokeEndpoint(0x277f0, readWord(gameContext), 0, 0, 0, 0, 0, 0);
                    invokeEndpoint(0x278f0, readWord(gameContext), floatBits(one), floatBits(one),
                                   floatBits(one), 0x3f800000, 0, 0);
                } else
                    invokeEndpoint(method(stateImage, 0x13e458), 0xde1, 0, 0, 0, 0, 0, 0);
                int32_t negative = (int32_t)(0u - readDword(record + 0x30));
                float x = narrow((double)negative * readDouble(stateImage + 0x153ff0));
                invokeEndpoint(0x27590, readWord(gameContext), font, readWord(record + 0x28),
                               floatBits(x), 0xc0a00000, readDword(record + 0x34), 1);
                if (event[0x44] == 1)
                    invokeEndpoint(0x27820, readWord(gameContext), 0, 0, 0, 0, 0, 0);
                else
                    invokeEndpoint(method(stateImage, 0x13e450), 0xde1, 0, 0, 0, 0, 0, 0);
                invokeEndpoint(method(stateImage, 0x150cb8), 0, 0, 0, 0, 0, 0, 0);
            }
            invokeEndpoint(target(translate), 0, floatBits(marker_offset), 0, 0, 0, 0, 0);
            invokeEndpoint(target(scale), floatBits(marker_scale), floatBits(marker_scale),
                           floatBits(marker_scale), 0, 0, 0, 0);
            uint32_t type = readDword(record + 0x20) - 10;
            invokeEndpoint(target(color), readDword(stateImage + 0x154110 + 4 * (uint64_t)type),
                           readDword(stateImage + 0x154124 + 4 * (uint64_t)type),
                           readDword(stateImage + 0x154138 + 4 * (uint64_t)type), floatBits(alpha),
                           0, 0, 0);
            recovered_render_29540(stateImage, invokeEndpoint);
            invokeEndpoint(target(color), 0, 0, 0, floatBits(alpha), 0, 0, 0);
            recovered_render_29570(stateImage, invokeEndpoint);
            invokeEndpoint(method(stateImage, 0x150cb8), 0, 0, 0, 0, 0, 0, 0);
            ++entryIndex;
            record += 56;
        } while (entryIndex < readWord(stateImage + 0x301ea0));
    }
    invokeEndpoint(method(stateImage, 0x150cb8), 0, 0, 0, 0, 0, 0, 0);
    recovered_render_295a0(stateImage, invokeEndpoint);
}
__declspec(dllexport) void reconstruction::indicators::updateIndicators(uint8_t *event,
                                                                        uint8_t *stateImage,
                                                                        endpoint invokeEndpoint) {
    render(event, stateImage, invokeEndpoint);
}
// END SOURCE modules/Indicators/indicators.cpp

// Convenient borrowed-state interface

namespace shareable {
class Indicators {
  public:
    static constexpr const char *kName = "Indicators";
    static constexpr const char *kDescription = "Points to incoming projectiles.";
    explicit Indicators(std::uint8_t *image) : image_(image) {}
    // Scale. Config key: scale.
    NumberSetting &scale() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f1650);
    }
    // Radius. Config key: radius.
    NumberSetting &radius() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f1688);
    }
    // Arrows. Config key: show_arrow.
    BooleanSetting &show_arrow() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f16c0);
    }
    // Fireballs. Config key: show_fireball.
    BooleanSetting &show_fireball() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f16e0);
    }
    // Ender pearls. Config key: show_pearl.
    BooleanSetting &show_pearl() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f1700);
    }
    // Coming closer. Config key: require_coming_closer.
    BooleanSetting &require_coming_closer() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f1720);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_indicators_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_indicators_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_indicators_settings(&context, image_, &dependencies);
    }
    void onLifecycleEvent(uint8_t *event, endpoint invokeEndpoint) {
        ::reconstruction::indicators::onLifecycleEvent(event, image_, invokeEndpoint);
    }
    void renderIndicators(uint8_t *event, endpoint invokeEndpoint) {
        ::reconstruction::indicators::renderIndicators(event, image_, invokeEndpoint);
    }
    void updateIndicators(uint8_t *event, endpoint invokeEndpoint) {
        ::reconstruction::indicators::updateIndicators(event, image_, invokeEndpoint);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
