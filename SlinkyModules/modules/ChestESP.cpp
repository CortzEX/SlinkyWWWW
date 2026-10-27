// Chest ESP

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Chest_ESP.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Chest_ESP.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Chest ESP: lib_win settings 0x33eb0.
static constexpr SettingsStep settings_steps_Surface_Chest_ESP[] = {
    {SettingsControl::number, "range", 0x2ecb18},
    {SettingsControl::boolean, "render_chest", 0x2ecb50},
    {SettingsControl::boolean, "render_ender_chest", 0x2ecb70},
    {SettingsControl::boolean, "render_trapped_chest", 0x2ecb90},
    {SettingsControl::boolean, "render_beacon", 0x2ecbb0},
    {SettingsControl::number, "line_width", 0x2ecbd0},
    {SettingsControl::color, "color_chest", 0x2ecc68},
    {SettingsControl::color, "color_ender_chest", 0x2ecc08},
    {SettingsControl::color, "color_trapped_chest", 0x2ecc28},
    {SettingsControl::color, "color_beacon", 0x2ecc48},
    {SettingsControl::boolean, "filled", 0x2ecc88},
};
static constexpr ModuleSurface surface_Surface_Chest_ESP{
    nullptr, 0, settings_steps_Surface_Chest_ESP, std::size(settings_steps_Surface_Chest_ESP)};

extern "C" __declspec(dllexport) void
recovered_chest_esp_settings(SettingsContext *context, std::uint8_t *image,
                             const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Chest_ESP, context, image, *dependencies);
}

// Chest ESP: lib_win runtime UI 0x33d60.
extern "C" __declspec(dllexport) void
recovered_chest_esp_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                       const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2ecb18);
    dependencies->section(ui, layout, "Target");
    dependencies->checkbox(layout, ui, image + 0x2ecb50);
    dependencies->checkbox(layout, ui, image + 0x2ecb70);
    dependencies->checkbox(layout, ui, image + 0x2ecb90);
    dependencies->checkbox(layout, ui, image + 0x2ecbb0);
    dependencies->section(ui, layout, "Customization");
    dependencies->number(layout, ui, image + 0x2ecbd0);
    if (image[0x2ecb68] == 1) {
        dependencies->color(layout, ui, image + 0x2ecc68);
    }
    if (image[0x2ecb88] == 1) {
        dependencies->color(layout, ui, image + 0x2ecc08);
    }
    if (image[0x2ecba8] == 1) {
        dependencies->color(layout, ui, image + 0x2ecc28);
    }
    if (image[0x2ecbc8] == 1) {
        dependencies->color(layout, ui, image + 0x2ecc48);
    }
    dependencies->checkbox(layout, ui, image + 0x2ecc88);
}
// END SOURCE native/verified/surfaces/Surface_Chest_ESP.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Chest_ESP
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Chest_ESP.cpp
extern "C" __declspec(dllexport) void
recovered_chest_esp_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                             const BoundSurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2ecb18);
    dependencies->section(ui, layout, "Target");
    dependencies->checkbox(layout, ui, image + 0x2ecb50);
    dependencies->checkbox(layout, ui, image + 0x2ecb70);
    dependencies->checkbox(layout, ui, image + 0x2ecb90);
    dependencies->checkbox(layout, ui, image + 0x2ecbb0);
    dependencies->section(ui, layout, "Customization");
    dependencies->number(layout, ui, image + 0x2ecbd0);
    if (image[0x2ecb68] == 1) {
        dependencies->color(layout, ui, image + 0x2ecc68);
    }
    if (image[0x2ecb88] == 1) {
        dependencies->color(layout, ui, image + 0x2ecc08);
    }
    if (image[0x2ecba8] == 1) {
        dependencies->color(layout, ui, image + 0x2ecc28);
    }
    if (image[0x2ecbc8] == 1) {
        dependencies->color(layout, ui, image + 0x2ecc48);
    }
    dependencies->checkbox(layout, ui, image + 0x2ecc88);
}
// END SOURCE shared/BoundSurfaces.cpp@Chest_ESP

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Chest_ESP/chest_esp.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses evidence/recovered_cpp/behavior/module_behavior_recovery/chest_esp/chest_esp.cpp
// SHA-256 96448ede63d71779c650bba508bb417e1ce00aec043d7552bbc3068a191a09d0
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.
#ifndef SLINKY_SHARE_C4F9682BDF5AA0E100B0
#define SLINKY_SHARE_C4F9682BDF5AA0E100B0
// BEGIN SOURCE modules/Chest_ESP/Module.hpp
#include "../runtime/shared/RenderNativeBindings.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_chest_esp_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                             const BoundSurfaceUiDependencies *);
extern "C" void recovered_chest_esp_settings(SettingsContext *, std::uint8_t *,
                                             const SurfaceSettingsDependencies *);

namespace reconstruction::chest_esp {
// The image view retains native storage offsets. It does not invent initialization.
using Endpoint5 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
__declspec(dllexport) void updateChests(uint8_t *event, uint8_t *image, Endpoint5 call);
__declspec(dllexport) void renderChests(uint8_t *event, uint8_t *image, Endpoint5 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_chest_esp_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_chest_esp_settings(context, stateImage, &deps);
}
} // namespace reconstruction::chest_esp

namespace reconstruction::chest_esp {
struct ChestRecord {
    double position[3];
    std::uint32_t blockId, padding;
};
static_assert(sizeof(ChestRecord) == 32);
} // namespace reconstruction::chest_esp

namespace reconstruction::chest_esp::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t range = 0x2ecb18 + offsetof(NumberSetting, current);
inline constexpr std::size_t render_chest = 0x2ecb50 + offsetof(BooleanSetting, current);
inline constexpr std::size_t render_ender_chest = 0x2ecb70 + offsetof(BooleanSetting, current);
inline constexpr std::size_t render_trapped_chest = 0x2ecb90 + offsetof(BooleanSetting, current);
inline constexpr std::size_t render_beacon = 0x2ecbb0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t line_width = 0x2ecbd0 + offsetof(NumberSetting, current);
inline constexpr std::size_t color_chest = 0x2ecc68 + offsetof(ColorSetting, current);
inline constexpr std::size_t color_ender_chest = 0x2ecc08 + offsetof(ColorSetting, current);
inline constexpr std::size_t color_trapped_chest = 0x2ecc28 + offsetof(ColorSetting, current);
inline constexpr std::size_t color_beacon = 0x2ecc48 + offsetof(ColorSetting, current);
inline constexpr std::size_t filled = 0x2ecc88 + offsetof(BooleanSetting, current);
} // namespace reconstruction::chest_esp::setting_offset
// END SOURCE modules/Chest_ESP/Module.hpp

#endif // SLINKY_SHARE_C4F9682BDF5AA0E100B0

#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
using endpoint = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
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
static uint32_t floatBits(float v) {
    return readDword(&v);
}
static void writeWord(void *p, uint64_t v) {
    memcpy(p, &v, 8);
}
static void writeDword(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
static uint64_t method(uint8_t *stateImage, uint32_t slot) {
    return readWord((uint8_t *)(uintptr_t)readWord(stateImage + slot));
}
static float narrow(double v) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(v)));
}

__declspec(dllexport) void reconstruction::chest_esp::updateChests(uint8_t *event,
                                                                   uint8_t *stateImage,
                                                                   endpoint invokeEndpoint) {
    writeWord(stateImage + 0x2fa360, 0);
    uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord(event + 8);
    if (!readWord(gameContext + 0x20))
        return;
    double self[3];
    invokeEndpoint(0x23030, (uintptr_t)self, readWord(gameContext), readWord(gameContext + 0x28),
                   0);
    uint64_t list =
        invokeEndpoint(0x24640, readWord(gameContext), readWord(gameContext + 0x20), 0, 0);
    if ((int32_t)invokeEndpoint(0x24e50, readWord(gameContext), list, 0, 0) <= 0)
        return;
    uint32_t entryIndex = 0;
    do {
        uint64_t entry = invokeEndpoint(0x24e80, readWord(gameContext), list, entryIndex, 0);
        uint64_t block = invokeEndpoint(0x244f0, readWord(gameContext), entry, 0, 0);
        if (block) {
            uint32_t type = (uint32_t)invokeEndpoint(0x24280, readWord(gameContext), block, 0, 0);
            int enabled = 0;
            switch (type) {
            case 54:
                enabled = stateImage[reconstruction::chest_esp::setting_offset::render_chest] != 0;
                break;
            case 130:
                enabled =
                    stateImage[reconstruction::chest_esp::setting_offset::render_ender_chest] != 0;
                break;
            case 146:
                enabled =
                    stateImage[reconstruction::chest_esp::setting_offset::render_trapped_chest] !=
                    0;
                break;
            case 138:
                enabled = stateImage[reconstruction::chest_esp::setting_offset::render_beacon] == 1;
                break;
            }
            if (enabled) {
                double position[3], a[3], b[3];
                invokeEndpoint(0x24510, (uintptr_t)position, readWord(gameContext), entry, 0);
                memcpy(a, position, 24);
                memcpy(b, self, 24);
                double distance = recovered_vector_distance_squared(a, b);
                float range =
                    readFloat(stateImage + reconstruction::chest_esp::setting_offset::range);
                range = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(range), _mm_set_ss(range)));
                if (!(distance > (double)range)) {
                    uint64_t old = readWord(stateImage + 0x2fa360), count = old + 1;
                    writeWord(stateImage + 0x2fa360, count);
                    uint8_t *slot = stateImage + 0x2fa370 + (old << 5);
                    memcpy(slot, position, 24);
                    writeDword(slot + 24, type);
                    if (count == 100)
                        return;
                }
            }
        }
        entryIndex++;
    } while ((int32_t)entryIndex <
             (int32_t)invokeEndpoint(0x24e50, readWord(gameContext), list, 0, 0));
}
__declspec(dllexport) void reconstruction::chest_esp::renderChests(uint8_t *event,
                                                                   uint8_t *stateImage,
                                                                   endpoint invokeEndpoint) {
    invokeEndpoint(0x293c0, 0, 0, 0, 0);
    uint64_t width_method = method(stateImage, 0x150cb0);
    invokeEndpoint(width_method,
                   readDword(stateImage + reconstruction::chest_esp::setting_offset::line_width), 0,
                   0, 0);
    if (readWord(stateImage + 0x2fa360)) {
        double adjustment[3];
        memcpy(adjustment, stateImage + 0x151ad0, 16);
        adjustment[2] = .5;
        uint32_t scale = readDword(stateImage + 0x151a60), alpha = readDword(stateImage + 0x151a64);
        uint64_t entryIndex = 0;
        uint8_t *entry = stateImage + 0x2fa370;
        do {
            uint32_t type = readDword(entry + 24),
                     color = type == 130
                                 ? reconstruction::chest_esp::setting_offset::color_ender_chest
                             : type == 138 ? reconstruction::chest_esp::setting_offset::color_beacon
                             : type == 146
                                 ? reconstruction::chest_esp::setting_offset::color_trapped_chest
                                 : reconstruction::chest_esp::setting_offset::color_chest;
            double position[3], camera[3], relative[3], center[3];
            memcpy(position, entry, 24);
            memcpy(camera, event + 8, 24);
            recovered_vector_subtract_93d0(relative, position, camera);
            recovered_geometry_add_9400(center, relative, adjustment);
            invokeEndpoint(method(stateImage, 0x150cc0), 0, 0, 0, 0);
            invokeEndpoint(method(stateImage, 0x150cd8), floatBits(narrow(center[0])),
                           floatBits(narrow(center[1])), floatBits(narrow(center[2])), 0);
            invokeEndpoint(method(stateImage, 0x150cd0), scale, scale, scale, 0);
            if (stateImage[reconstruction::chest_esp::setting_offset::filled] == 1) {
                invokeEndpoint(method(stateImage, 0x13e448), readDword(stateImage + color),
                               readDword(stateImage + color + 4), readDword(stateImage + color + 8),
                               alpha);
                invokeEndpoint(0x29400, 0, 0, 0, 0);
            }
            invokeEndpoint(method(stateImage, 0x150ca0), readDword(stateImage + color),
                           readDword(stateImage + color + 4), readDword(stateImage + color + 8), 0);
            invokeEndpoint(0x29430, 0, 0, 0, 0);
            invokeEndpoint(method(stateImage, 0x150cb8), 0, 0, 0, 0);
            entryIndex++;
            entry += 32;
        } while (entryIndex < readWord(stateImage + 0x2fa360));
    }
    invokeEndpoint(0x295a0, 0, 0, 0, 0);
}
// END SOURCE modules/Chest_ESP/chest_esp.cpp

// Convenient borrowed-state interface

namespace shareable {
class ChestESP {
  public:
    static constexpr const char *kName = "Chest ESP";
    static constexpr const char *kDescription = "Highlights chests.";
    explicit ChestESP(std::uint8_t *image) : image_(image) {}
    // Range. Config key: range.
    NumberSetting &range() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ecb18);
    }
    // Regular chests. Config key: render_chest.
    BooleanSetting &render_chest() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ecb50);
    }
    // Ender chests. Config key: render_ender_chest.
    BooleanSetting &render_ender_chest() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ecb70);
    }
    // Trapped chests. Config key: render_trapped_chest.
    BooleanSetting &render_trapped_chest() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ecb90);
    }
    // Beacons. Config key: render_beacon.
    BooleanSetting &render_beacon() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ecbb0);
    }
    // Line width. Config key: line_width.
    NumberSetting &line_width() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ecbd0);
    }
    // color_chest. Config key: color_chest.
    ColorSetting &color_chest() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2ecc68);
    }
    // color_ender_chest. Config key: color_ender_chest.
    ColorSetting &color_ender_chest() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2ecc08);
    }
    // color_trapped_chest. Config key: color_trapped_chest.
    ColorSetting &color_trapped_chest() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2ecc28);
    }
    // color_beacon. Config key: color_beacon.
    ColorSetting &color_beacon() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2ecc48);
    }
    // Filled. Config key: filled.
    BooleanSetting &filled() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ecc88);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_chest_esp_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_chest_esp_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_chest_esp_settings(&context, image_, &dependencies);
    }
    void updateChests(uint8_t *event, endpoint invokeEndpoint) {
        ::reconstruction::chest_esp::updateChests(event, image_, invokeEndpoint);
    }
    void renderChests(uint8_t *event, endpoint invokeEndpoint) {
        ::reconstruction::chest_esp::renderChests(event, image_, invokeEndpoint);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
