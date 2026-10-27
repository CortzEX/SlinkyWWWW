// Mod Overlay

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Mod_Overlay.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Mod_Overlay.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Mod Overlay: lib_win settings 0x34b90.
static constexpr SettingsStep settings_steps_Surface_Mod_Overlay[] = {
    {SettingsControl::boolean, "show_combat", 0x2ed100},
    {SettingsControl::boolean, "show_move", 0x2ed120},
    {SettingsControl::boolean, "show_block", 0x2ed140},
    {SettingsControl::boolean, "show_visual", 0x2ed160},
    {SettingsControl::boolean, "show_utility", 0x2ed180},
    {SettingsControl::number, "text_size", 0x2ed200},
    {SettingsControl::number, "padding_x", 0x2ed2b0},
    {SettingsControl::number, "padding_y", 0x2ed2e8},
    {SettingsControl::number, "bg_rounding", 0x2ed278},
    {SettingsControl::color, "name_color", 0x2ed238},
    {SettingsControl::color, "details_color", 0x2ed258},
    {SettingsControl::boolean, "lowercase", 0x2ed1c0},
    {SettingsControl::boolean, "show_details", 0x2ed1e0},
    {SettingsControl::boolean, "require_bound", 0x2ed1a0},
};
static constexpr ModuleSurface surface_Surface_Mod_Overlay{
    nullptr, 0, settings_steps_Surface_Mod_Overlay, std::size(settings_steps_Surface_Mod_Overlay)};

extern "C" __declspec(dllexport) void
recovered_mod_overlay_settings(SettingsContext *context, std::uint8_t *image,
                               const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Mod_Overlay, context, image, *dependencies);
}

// Mod Overlay: lib_win runtime UI 0x34a40.
extern "C" __declspec(dllexport) void
recovered_mod_overlay_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                         const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Visible categories");
    dependencies->checkbox(layout, ui, image + 0x2ed100);
    dependencies->checkbox(layout, ui, image + 0x2ed120);
    dependencies->checkbox(layout, ui, image + 0x2ed140);
    dependencies->checkbox(layout, ui, image + 0x2ed160);
    dependencies->checkbox(layout, ui, image + 0x2ed180);
    dependencies->section(ui, layout, "Customization");
    dependencies->number(layout, ui, image + 0x2ed200);
    dependencies->number(layout, ui, image + 0x2ed2b0);
    dependencies->number(layout, ui, image + 0x2ed2e8);
    dependencies->number(layout, ui, image + 0x2ed278);
    dependencies->color(layout, ui, image + 0x2ed238);
    dependencies->color(layout, ui, image + 0x2ed258);
    dependencies->checkbox(layout, ui, image + 0x2ed1c0);
    dependencies->checkbox(layout, ui, image + 0x2ed1e0);
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2ed1a0);
}
// END SOURCE native/verified/surfaces/Surface_Mod_Overlay.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Mod_Overlay
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Mod_Overlay.cpp
extern "C" __declspec(dllexport) void
recovered_mod_overlay_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                               const BoundSurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Visible categories");
    dependencies->checkbox(layout, ui, image + 0x2ed100);
    dependencies->checkbox(layout, ui, image + 0x2ed120);
    dependencies->checkbox(layout, ui, image + 0x2ed140);
    dependencies->checkbox(layout, ui, image + 0x2ed160);
    dependencies->checkbox(layout, ui, image + 0x2ed180);
    dependencies->section(ui, layout, "Customization");
    dependencies->number(layout, ui, image + 0x2ed200);
    dependencies->number(layout, ui, image + 0x2ed2b0);
    dependencies->number(layout, ui, image + 0x2ed2e8);
    dependencies->number(layout, ui, image + 0x2ed278);
    dependencies->color(layout, ui, image + 0x2ed238);
    dependencies->color(layout, ui, image + 0x2ed258);
    dependencies->checkbox(layout, ui, image + 0x2ed1c0);
    dependencies->checkbox(layout, ui, image + 0x2ed1e0);
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2ed1a0);
}
// END SOURCE shared/BoundSurfaces.cpp@Mod_Overlay

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Mod_Overlay/mod_overlay_extended.cpp
#ifndef SLINKY_SHARE_4C553FE55778379850D1
#define SLINKY_SHARE_4C553FE55778379850D1
// BEGIN SOURCE modules/Mod_Overlay/Module.hpp
#include "../runtime/shared/RenderNativeBindings.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/shared/Geometry.hpp"
#include "../runtime/shared/ModOverlayCharacterBindings.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_mod_overlay_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                               const BoundSurfaceUiDependencies *);
extern "C" void recovered_mod_overlay_settings(SettingsContext *, std::uint8_t *,
                                               const SurfaceSettingsDependencies *);

typedef uintptr_t up;
struct ModOverlayDependencies {
    reconstruction::native_binding::RenderEndpoint<4> native;
    up character_provider;
    void *user;
    // Retained character callback fields are compatibility data. The canonical
    // append/collect bodies use their four proved decoded-cell contracts.
    uint8_t (*character)(void *, up provider, int32_t character);
    void (*dynamic)(void *, up callback, up destination);
    // Partial views borrow the shared cell used by all four character contracts.
    const std::uint8_t *nameEncodedCell_32ecfb = nullptr;
};

namespace reconstruction::mod_overlay {
// The image view retains native storage offsets. It does not invent initialization.
using Endpoint10 = reconstruction::native_binding::RenderEndpoint<9, std::uint64_t>;
__declspec(dllexport) void onSettingChanged(uint8_t *ev, uint8_t *im,
                                            const ModOverlayDependencies *d);
__declspec(dllexport) void onModuleStateChanged(uint8_t *ev, uint8_t *im,
                                                const ModOverlayDependencies *d);
__declspec(dllexport) void onStatusEvent(uint8_t *ev, uint8_t *im, const ModOverlayDependencies *d);
__declspec(dllexport) void onControlEvent(uint8_t *ev, uint8_t *im,
                                          const ModOverlayDependencies *d);
__declspec(dllexport) void collectModules(uint8_t *ev, uint8_t *im,
                                          const ModOverlayDependencies *d);
__declspec(dllexport) uint64_t compareWidth(const uint8_t *a, const uint8_t *b, Endpoint10 call);
__declspec(dllexport) void renderOverlay(uint8_t *event, uint8_t *image, Endpoint10 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &ModOverlayDependencies) {
    recovered_mod_overlay_bound_ui(ui, layout, stateImage, &ModOverlayDependencies);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &ModOverlayDependencies) {
    recovered_mod_overlay_settings(context, stateImage, &ModOverlayDependencies);
}
} // namespace reconstruction::mod_overlay

namespace reconstruction::mod_overlay {
void appendModule(std::uintptr_t, std::uint8_t *, const ModOverlayDependencies *);
void refreshVisibleModules(const std::uint8_t *, std::uint8_t *, const ModOverlayDependencies *);
struct OverlayRecord {
    std::uintptr_t descriptor;
    char name[20], status[32];
    float width, height, progress;
    std::uint8_t enabled, padding[7];
};
static_assert(sizeof(OverlayRecord) == 80);
static_assert(offsetof(OverlayRecord, progress) == 0x44);
} // namespace reconstruction::mod_overlay

namespace reconstruction::mod_overlay::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t show_combat = 0x2ed100 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_move = 0x2ed120 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_block = 0x2ed140 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_visual = 0x2ed160 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_utility = 0x2ed180 + offsetof(BooleanSetting, current);
inline constexpr std::size_t text_size = 0x2ed200 + offsetof(NumberSetting, current);
inline constexpr std::size_t padding_x = 0x2ed2b0 + offsetof(NumberSetting, current);
inline constexpr std::size_t padding_y = 0x2ed2e8 + offsetof(NumberSetting, current);
inline constexpr std::size_t bg_rounding = 0x2ed278 + offsetof(NumberSetting, current);
inline constexpr std::size_t name_color = 0x2ed238 + offsetof(ColorSetting, current);
inline constexpr std::size_t details_color = 0x2ed258 + offsetof(ColorSetting, current);
inline constexpr std::size_t lowercase = 0x2ed1c0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_details = 0x2ed1e0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t require_bound = 0x2ed1a0 + offsetof(BooleanSetting, current);
} // namespace reconstruction::mod_overlay::setting_offset
// END SOURCE modules/Mod_Overlay/Module.hpp

#endif // SLINKY_SHARE_4C553FE55778379850D1

#include <stddef.h>
#include <stdint.h>
#include <string.h>

static uint64_t rd64(const void *p, unsigned n) {
    uint64_t v;
    memcpy(&v, (const uint8_t *)p + n, 8);
    return v;
}
static uint32_t rd32(const void *p, unsigned n) {
    uint32_t v;
    memcpy(&v, (const uint8_t *)p + n, 4);
    return v;
}
static float rdf(const void *p, unsigned n) {
    float v;
    memcpy(&v, (const uint8_t *)p + n, 4);
    return v;
}
static void wr64(void *p, unsigned n, uint64_t v) {
    memcpy((uint8_t *)p + n, &v, 8);
}
static void wr32(void *p, unsigned n, uint32_t v) {
    memcpy((uint8_t *)p + n, &v, 4);
}
static void wrf(void *p, unsigned n, float v) {
    memcpy((uint8_t *)p + n, &v, 4);
}
static uint8_t *G(uint8_t *im, uint32_t rva) {
    return im + rva;
}

/* Three registry hooks below reproduce only the observed body. The shared collection helper at
   34ce0 has a separate source body. Globals are addressed from stateImage RVA. */
__declspec(dllexport) void
reconstruction::mod_overlay::onSettingChanged(uint8_t *ev, uint8_t *im,
                                              const ModOverlayDependencies *d) {
    (void)d;
    if (rd32(ev, 0x10) == 0)
        G(im, 0x2faff4)[0] = 1;
}
__declspec(dllexport) void
reconstruction::mod_overlay::onModuleStateChanged(uint8_t *ev, uint8_t *im,
                                                  const ModOverlayDependencies *d) {
    if (G(im, reconstruction::mod_overlay::setting_offset::require_bound)[0] == 1) {
        reconstruction::mod_overlay::refreshVisibleModules(
            reinterpret_cast<const uint8_t *>(rd64(ev, 8)), im, d);
        G(im, 0x2faff5)[0] = 1;
    }
}
__declspec(dllexport) void
reconstruction::mod_overlay::onStatusEvent(uint8_t *ev, uint8_t *im,
                                           const ModOverlayDependencies *d) {
    uint32_t old = rd32(ev, 0x10);
    wr32(ev, 0x10, old | 1u);
    if (G(im, 0x2faff5)[0] != 0 || (rdf(im, 0x2fbfa0) > 0.0f))
        wr32(ev, 0x10, old | 3u);
}

static int eligible(uint8_t *item, uint8_t *im, int require_active) {
    if ((require_active && item[0x14] != 1) || (item[0x18] & 4) != 0)
        return 0;
    if (G(im, reconstruction::mod_overlay::setting_offset::require_bound)[0] == 1 &&
        rd32(item, 0x1c) == 0)
        return 0;
    switch (rd32(item, 0x10)) {
    case 0:
        return G(im, reconstruction::mod_overlay::setting_offset::show_combat)[0] != 0;
    case 1:
        return G(im, reconstruction::mod_overlay::setting_offset::show_move)[0] != 0;
    case 2:
        return G(im, reconstruction::mod_overlay::setting_offset::show_visual)[0] != 0;
    case 3:
        return G(im, reconstruction::mod_overlay::setting_offset::show_block)[0] != 0;
    case 4:
        return G(im, reconstruction::mod_overlay::setting_offset::show_utility)[0] == 1;
    default:
        return 1;
    }
}
static void append_candidate(uint8_t *im, up item, const ModOverlayDependencies *d) {
    reconstruction::mod_overlay::appendModule(item, im, d);
}
__declspec(dllexport) void
reconstruction::mod_overlay::onControlEvent(uint8_t *ev, uint8_t *im,
                                            const ModOverlayDependencies *d) {
    up item = rd64(ev, 0x10);
    uint8_t *record;
    uint64_t n, i;
    uint8_t *game;
    uint8_t *list;
    wr32(im, 0x2fbfa0, 0x3e4ccccd);
    if (item == (up)(uintptr_t)(im + 0x2ecef0)) {
        game = (uint8_t *)(uintptr_t)rd64(ev, 8);
        list = (uint8_t *)(uintptr_t)rd64(game, 8);
        wr64(im, 0x2faff8, 0);
        if (ev[0x18] != 1)
            return;
        n = rd64(list, 8);
        for (i = 0; i < n; i++) {
            up candidate = rd64((void *)(uintptr_t)rd64(list, 0), (unsigned)(i * 8));
            if (eligible((uint8_t *)(uintptr_t)candidate, im, 1)) {
                append_candidate(im, candidate, d);
                n = rd64(list, 8);
            }
        }
        G(im, 0x2faff5)[0] = 1;
        return;
    }
    n = rd64(im, 0x2faff8);
    for (i = 0; i < n; i++) {
        record = G(im, 0x2fb000) + (size_t)i * 0x50;
        if (rd64(record, 0) != item)
            continue;
        if (ev[0x18] == 0) {
            record[0x48] = 0;
            return;
        }
        if (!eligible((uint8_t *)(uintptr_t)item, im, 0))
            return;
        record[0x48] = 1;
        return;
    }
    if (ev[0x18] != 1 || !eligible((uint8_t *)(uintptr_t)item, im, 1))
        return;
    append_candidate(im, item, d);
    G(im, 0x2faff5)[0] = 1;
}

/* Byte scanning and formatting use concrete shared algorithms. The name
   E6314D resolver loads once before the length branch; status E28595 reloads
   its borrowed cell per byte. Descriptor callbacks retain caller context. */
__declspec(dllexport) void
reconstruction::mod_overlay::collectModules(uint8_t *ev, uint8_t *im,
                                            const ModOverlayDependencies *d) {
    uint8_t *gameContext = (uint8_t *)(uintptr_t)rd64(ev, 8);
    uint32_t mask = (uint32_t)G(im, reconstruction::mod_overlay::setting_offset::show_combat)[0] +
                    2u * G(im, reconstruction::mod_overlay::setting_offset::show_move)[0] +
                    4u * G(im, reconstruction::mod_overlay::setting_offset::show_block)[0] +
                    8u * G(im, reconstruction::mod_overlay::setting_offset::show_visual)[0];
    mask |= (uint32_t)G(im, reconstruction::mod_overlay::setting_offset::show_utility)[0] << 4;
    mask |= (uint32_t)G(im, reconstruction::mod_overlay::setting_offset::require_bound)[0] << 5;
    uint8_t old_dirty = G(im, 0x2faff4)[0], bl;
    uint64_t i;
    if (rd32(im, 0x2faff0) != mask || (old_dirty & 1)) {
        reconstruction::mod_overlay::refreshVisibleModules(
            reinterpret_cast<const uint8_t *>(rd64(gameContext, 8)), im, d);
        wr32(im, 0x2faff0, mask);
        G(im, 0x2faff5)[0] = 1;
        G(im, 0x2faff4)[0] = 0;
    }
    if (!(old_dirty & 1) && gameContext[0x40] != 0)
        return;
    bl = G(im, reconstruction::mod_overlay::setting_offset::lowercase)[0];
    for (i = 0; i < rd64(im, 0x2faff8); i++) {
        uint8_t *record = G(im, 0x2fb000) + (size_t)i * 0x50;
        up item = rd64(record, 0);
        uint8_t *item_object = (uint8_t *)(uintptr_t)item;
        int formatted = 0;
        if (bl & 1) {
            up length = d->native(0xab840, rd64(item_object, 0), 0, 0, 0), terminator = length;
            const auto character =
                reconstruction::overlay_character::resolve_e6314d({im, d->nameEncodedCell_32ecfb});
            for (up j = 0; j < length; j++) {
                up name = rd64(item_object, 0);
                int32_t source = (int8_t)*((uint8_t *)(uintptr_t)name + j);
                record[8 + j] = static_cast<std::uint8_t>(character(source));
            }
            record[8 + terminator] = 0;
            bl = 1;
        } else {
            d->native(0xab710, (up)(uintptr_t)(record + 8), 0x14, (up)(uintptr_t)(im + 0x151cfc),
                      rd64(item_object, 0));
            bl = G(im, reconstruction::mod_overlay::setting_offset::lowercase)[0];
            formatted = 1;
        }
        if (formatted) {
            item = rd64(record, 0);
            item_object = (uint8_t *)(uintptr_t)item;
        }
        up callback = rd64(item_object, 0x208);
        if (!callback || !G(im, reconstruction::mod_overlay::setting_offset::show_details)[0])
            record[0x1c] = 0;
        else {
            /* Dynamic callback is an explicit, address-preserving boundary. */
            d->dynamic(d->user, callback, (up)(uintptr_t)(record + 0x1c));
            if (G(im, reconstruction::mod_overlay::setting_offset::lowercase)[0] == 1) {
                bl = 1;
            } else {
                bl = 0;
            }
            if (bl && record[0x1c]) {
                up j = 0, length;
                do {
                    uint8_t *text = G(im, 0x2fb01c) + (size_t)i * 0x50;
                    text[j] = static_cast<std::uint8_t>(
                        reconstruction::overlay_character::character_e28595(
                            {im, d->nameEncodedCell_32ecfb}, (int8_t)text[j]));
                    j++;
                    length = d->native(0xab840, (up)(uintptr_t)(record + 0x1c), 0, 0, 0);
                } while (j < length);
            }
        }
    }
    G(im, 0x2faff5)[0] = 1;
}
// END SOURCE modules/Mod_Overlay/mod_overlay_extended.cpp

// BEGIN SOURCE modules/Mod_Overlay/mod_overlay_render.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses
// evidence/recovered_cpp/behavior/module_behavior_recovery/mod_overlay_render/mod_overlay_render.cpp
// SHA-256 51fde7512b0ab23020613e05bf4d00b7ba893e65b0cdb9c8ce94977f724ea645
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.

#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
using endpoint = reconstruction::native_binding::RenderEndpoint<9, std::uint64_t>;
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
static void writeWord(void *p, uint64_t v) {
    memcpy(p, &v, 8);
}
static void writeFloat(void *p, float v) {
    memcpy(p, &v, 4);
}
static uint32_t bits(float v) {
    return readDword(&v);
}
static float floatFromWord(uint64_t v) {
    uint32_t b = (uint32_t)v;
    return readFloat(&b);
}
static float add(float a, float b) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float sub(float a, float b) {
    return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float mul(float a, float b) {
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float minimum(float a, float b) {
    return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float narrow(double v) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(v)));
}
static uint64_t call4(endpoint invokeEndpoint, uint64_t r, uint64_t a, uint64_t b, uint64_t c,
                      uint64_t d) {
    return invokeEndpoint(r, a, b, c, d, 0, 0, 0, 0, 0);
}
float *recovered_color_74150(float *, float, float, float, float);
uint32_t *recovered_color_74130(uint32_t *, uint32_t, uint32_t, uint32_t);
__declspec(dllexport) uint64_t reconstruction::mod_overlay::compareWidth(const uint8_t *a,
                                                                         const uint8_t *b,
                                                                         endpoint invokeEndpoint) {
    float left = readFloat(a + 0x3c), right = readFloat(b + 0x3c);
    if (right > left)
        return 1;
    if (left > right)
        return UINT32_MAX;
    return call4(invokeEndpoint, 0x13d0a0, (uintptr_t)(a + 8), (uintptr_t)(b + 8), 0, 0);
}
__declspec(dllexport) uint64_t mod_overlay_compare_adapter(uint8_t *event, uint8_t *stateImage,
                                                           endpoint invokeEndpoint) {
    (void)stateImage;
    return reconstruction::mod_overlay::compareWidth((uint8_t *)(uintptr_t)readWord(event),
                                                     (uint8_t *)(uintptr_t)readWord(event + 8),
                                                     invokeEndpoint);
}
__declspec(dllexport) void reconstruction::mod_overlay::renderOverlay(uint8_t *event,
                                                                      uint8_t *stateImage,
                                                                      endpoint invokeEndpoint) {
    uint8_t *draw = (uint8_t *)(uintptr_t)readWord(event + 0x10);
    uint64_t canvas = readWord(draw);
    call4(invokeEndpoint, 0x79610, canvas,
          readDword(stateImage + reconstruction::mod_overlay::setting_offset::text_size), 0, 0);
    call4(invokeEndpoint, 0x10340, (uintptr_t)draw, 0, 0, 0);
    float timer = readFloat(stateImage + 0x2fbfa0);
    if (timer > 0.f)
        writeFloat(stateImage + 0x2fbfa0, sub(timer, readFloat(event + 0x18)));
    uint64_t count = readWord(stateImage + 0x2faff8);
    if (count) {
        double dt = (double)readFloat(event + 0x18), rate = readDouble(stateImage + 0x151c60);
        uint64_t neg = readWord(&dt) ^ readWord(stateImage + 0x151c50);
        double increase = dt * rate, decrease = readDouble(&neg) * rate;
        float cap = readFloat(stateImage + 0x151c68);
        for (uint64_t i = 0; i < count; ++i) {
            uint8_t *record = stateImage + 0x2fb000 + i * 0x50;
            float value = readFloat(record + 0x44);
            if (record[0x48] == 1) {
                if (value != cap)
                    writeFloat(record + 0x44, minimum(cap, narrow((double)value + increase)));
            } else {
                value = narrow((double)value + decrease);
                writeFloat(record + 0x44, value);
                if (!(value > 0.f)) {
                    uint64_t smaller = count - 1;
                    writeWord(stateImage + 0x2faff8, smaller);
                    call4(invokeEndpoint, 0xab910, (uintptr_t)record, (uintptr_t)(record + 0x50),
                          (count - i - 1) * 0x50, 0);
                    count = smaller;
                }
            }
        }
    }
    if (stateImage[0x2faff5] == 1) {
        call4(invokeEndpoint, 0x79690, canvas, 9, 0, 0);
        count = readWord(stateImage + 0x2faff8);
        if (count) {
            float gap = readFloat(stateImage + 0x151c6c);
            float measure[4];
            uint64_t i = 0;
            do {
                uint8_t *record = stateImage + 0x2fb000 + i * 0x50;
                invokeEndpoint(0x7ae90, canvas, 0, 0, (uintptr_t)(record + 8), 0,
                               (uintptr_t)measure, 0, 0, 0);
                memcpy(record + 0x3c, measure + 2, 8);
                if (record[0x1c]) {
                    invokeEndpoint(0x7ae90, canvas, 0, 0, (uintptr_t)(record + 0x1c), 0,
                                   (uintptr_t)measure, 0, 0, 0);
                    writeFloat(record + 0x3c, add(add(measure[2], gap), readFloat(record + 0x3c)));
                }
                ++i;
                count = readWord(stateImage + 0x2faff8);
            } while (i < count);
        }
        call4(invokeEndpoint, 0x13d0f0, (uintptr_t)(stateImage + 0x2fb000), count, 0x50,
              UINT64_C(0x180034fb0));
        stateImage[0x2faff5] = 0;
    }
    call4(invokeEndpoint, 0x79690, canvas, 9, 0, 0);
    float background[4], temporary[4];
    uint32_t primary[4], secondary[4];
    recovered_color_74150(background, 0.f, 0.f, 0.f, floatFromWord(0x3f333333));
    recovered_color_74130(
        primary, readDword(stateImage + reconstruction::mod_overlay::setting_offset::name_color),
        readDword(stateImage + 0x2ed244), readDword(stateImage + 0x2ed248));
    recovered_color_74130(
        secondary,
        readDword(stateImage + reconstruction::mod_overlay::setting_offset::details_color),
        readDword(stateImage + 0x2ed264), readDword(stateImage + 0x2ed268));
    if (readWord(stateImage + 0x2faff8)) {
        float screen = readFloat(draw + 0x18), cap = readFloat(stateImage + 0x151c68),
              gap = readFloat(stateImage + 0x151c6c), y = 0.f;
        uint64_t entryIndex = 0;
        do {
            uint8_t *record = stateImage + 0x2fb000 + entryIndex * 0x50;
            float progress = readFloat(record + 0x44), alpha = cap;
            if (progress != cap)
                alpha = recovered_smooth_a280(progress, stateImage);
            call4(invokeEndpoint, 0x74a60, canvas, bits(alpha), 0, 0);
            float corner =
                readFloat(stateImage + reconstruction::mod_overlay::setting_offset::bg_rounding);
            ++entryIndex;
            if (entryIndex < readWord(stateImage + 0x2faff8))
                corner = minimum(sub(readFloat(record + 0x3c), readFloat(record + 0x8c)), corner);
            memcpy(temporary, background, 16);
            call4(invokeEndpoint, 0x74ef0, canvas, (uintptr_t)temporary, 0, 0);
            call4(invokeEndpoint, 0x75bc0, canvas, 0, 0, 0);
            float px = readFloat(stateImage +
                                 reconstruction::mod_overlay::setting_offset::padding_x),
                  twice_x = add(px, px), width = readFloat(record + 0x3c);
            float bar_x = sub(sub(screen, twice_x), mul(width, alpha)),
                  bar_width = add(twice_x, width),
                  py = readFloat(stateImage +
                                 reconstruction::mod_overlay::setting_offset::padding_y);
            float bar_height = add(add(py, py), readFloat(record + 0x40));
            invokeEndpoint(0x76a10, canvas, bits(bar_x), bits(y), bits(bar_width), bits(bar_height),
                           0, 0, 0, bits(corner));
            call4(invokeEndpoint, 0x77210, canvas, 0, 0, 0);
            memcpy(temporary, primary, 16);
            call4(invokeEndpoint, 0x74ef0, canvas, (uintptr_t)temporary, 0, 0);
            float text_y = add(readFloat(stateImage +
                                         reconstruction::mod_overlay::setting_offset::padding_y),
                               y),
                  text_x =
                      sub(sub(screen,
                              readFloat(stateImage +
                                        reconstruction::mod_overlay::setting_offset::padding_x)),
                          mul(readFloat(record + 0x3c), alpha));
            float end = floatFromWord(invokeEndpoint(0x79770, canvas, bits(text_x), bits(text_y),
                                                     (uintptr_t)(record + 8), 0, 0, 0, 0, 0));
            if (record[0x1c]) {
                memcpy(temporary, secondary, 16);
                call4(invokeEndpoint, 0x74ef0, canvas, (uintptr_t)temporary, 0, 0);
                invokeEndpoint(0x79770, canvas, bits(add(end, gap)), bits(text_y),
                               (uintptr_t)(record + 0x1c), 0, 0, 0, 0, 0);
            }
            py = readFloat(stateImage + reconstruction::mod_overlay::setting_offset::padding_y);
            y = add(y, mul(alpha, add(add(py, py), readFloat(record + 0x40))));
        } while (entryIndex < readWord(stateImage + 0x2faff8));
    }
    call4(invokeEndpoint, 0x74a60, canvas, readDword(stateImage + 0x151c68), 0, 0);
}
// END SOURCE modules/Mod_Overlay/mod_overlay_render.cpp

// BEGIN SOURCE modules/Mod_Overlay/ModuleCollection.cpp
#include <cstring>

namespace reconstruction::mod_overlay {
namespace {
template <class T> T load(const void *p) {
    T value;
    std::memcpy(&value, p, sizeof value);
    return value;
}
template <class T> void store(void *p, T value) {
    std::memcpy(p, &value, sizeof value);
}
std::uint8_t currentCategoryFlag(std::uint32_t category, const std::uint8_t *image) {
    switch (category) {
    case 0:
        return image[reconstruction::mod_overlay::setting_offset::show_combat];
    case 1:
        return image[reconstruction::mod_overlay::setting_offset::show_move];
    case 2:
        return image[reconstruction::mod_overlay::setting_offset::show_visual];
    case 3:
        return image[reconstruction::mod_overlay::setting_offset::show_block];
    case 4:
        return image[reconstruction::mod_overlay::setting_offset::show_utility];
    default:
        return 1;
    }
}
} // namespace

void appendModule(std::uintptr_t descriptor, std::uint8_t *stateImage,
                  const ModOverlayDependencies *deps) {
    auto *record = stateImage + 0x2fb000 + load<std::uint64_t>(stateImage + 0x2faff8) * 0x50;
    store(record, static_cast<std::uint64_t>(descriptor));
    store(record + 0x44, std::uint32_t(0));
    record[0x48] = 1;
    auto *module = reinterpret_cast<std::uint8_t *>(descriptor);
    if (stateImage[reconstruction::mod_overlay::setting_offset::lowercase] == 0) {
        deps->native(0xab710, reinterpret_cast<std::uintptr_t>(record + 8), 0x14,
                     reinterpret_cast<std::uintptr_t>(stateImage + 0x151cfc),
                     load<std::uint64_t>(module));
        module = reinterpret_cast<std::uint8_t *>(load<std::uintptr_t>(record));
    } else {
        const auto length = deps->native(0xab840, load<std::uint64_t>(module), 0, 0, 0);
        if (length != 0) {
            const auto character =
                overlay_character::resolve_32ecfb({stateImage, deps->nameEncodedCell_32ecfb});
            for (std::uintptr_t i = 0; i < length; ++i) {
                const auto *name =
                    reinterpret_cast<const std::int8_t *>(load<std::uintptr_t>(module));
                record[8 + i] = static_cast<std::uint8_t>(character(name[i]));
            }
        }
        record[8 + length] = 0;
    }
    const auto callback = load<std::uintptr_t>(module + 0x208);
    auto *status = record + 0x1c;
    if (callback && stateImage[reconstruction::mod_overlay::setting_offset::show_details] != 0) {
        deps->dynamic(deps->user, callback, reinterpret_cast<std::uintptr_t>(status));
        if (stateImage[reconstruction::mod_overlay::setting_offset::lowercase] == 1 && *status) {
            const auto character =
                overlay_character::resolve_bb8f39({stateImage, deps->nameEncodedCell_32ecfb});
            std::uintptr_t i = 0;
            do {
                status[i] =
                    static_cast<std::uint8_t>(character(static_cast<std::int8_t>(status[i])));
                ++i;
            } while (i < deps->native(0xab840, reinterpret_cast<std::uintptr_t>(status), 0, 0, 0));
        }
    } else
        *status = 0;
    store(stateImage + 0x2faff8, load<std::uint64_t>(stateImage + 0x2faff8) + 1);
}

void refreshVisibleModules(const std::uint8_t *registryList, std::uint8_t *stateImage,
                           const ModOverlayDependencies *deps) {
    auto count = load<std::uint64_t>(stateImage + 0x2faff8);
    if (count) {
        const std::uint8_t categoryFlags[5] = {
            stateImage[reconstruction::mod_overlay::setting_offset::show_combat],
            stateImage[reconstruction::mod_overlay::setting_offset::show_move],
            stateImage[reconstruction::mod_overlay::setting_offset::show_visual],
            stateImage[reconstruction::mod_overlay::setting_offset::show_block],
            stateImage[reconstruction::mod_overlay::setting_offset::show_utility]};
        const auto requireBinding =
            stateImage[reconstruction::mod_overlay::setting_offset::require_bound];
        auto *record = stateImage + 0x2fb000;
        do {
            const auto *module =
                reinterpret_cast<const std::uint8_t *>(load<std::uintptr_t>(record));
            bool disable = (module[0x18] & 4) != 0 ||
                           (requireBinding != 0 && load<std::uint32_t>(module + 0x1c) == 0);
            if (!disable) {
                const auto category = load<std::uint32_t>(module + 0x10);
                if (category <= 4)
                    disable = categoryFlags[category] == 0;
            }
            if (disable)
                record[0x48] = 0;
            record += 0x50;
        } while (--count);
    }
    auto registryCount = load<std::uint64_t>(registryList + 8);
    for (std::uint64_t i = 0; i < registryCount; ++i) {
        const auto *pointers =
            reinterpret_cast<const std::uint8_t *>(load<std::uintptr_t>(registryList));
        const auto descriptor = load<std::uintptr_t>(pointers + i * 8);
        const auto *module = reinterpret_cast<const std::uint8_t *>(descriptor);
        if (module[0x14] != 1 || (module[0x18] & 4) != 0)
            continue;
        if (stateImage[reconstruction::mod_overlay::setting_offset::require_bound] == 1 &&
            load<std::uint32_t>(module + 0x1c) == 0)
            continue;
        const auto category = load<std::uint32_t>(module + 0x10);
        const auto flag = currentCategoryFlag(category, stateImage);
        if (category == 4 ? flag != 1 : flag == 0)
            continue;
        auto remaining = load<std::uint64_t>(stateImage + 0x2faff8);
        auto *record = stateImage + 0x2fb000;
        bool found = false;
        while (remaining) {
            if (load<std::uintptr_t>(record) == descriptor) {
                record[0x48] = 1;
                found = true;
                break;
            }
            record += 0x50;
            --remaining;
        }
        if (!found) {
            appendModule(descriptor, stateImage, deps);
            registryCount = load<std::uint64_t>(registryList + 8);
        }
    }
}
} // namespace reconstruction::mod_overlay
// END SOURCE modules/Mod_Overlay/ModuleCollection.cpp

// Convenient borrowed-state interface

namespace shareable {
class ModOverlay {
  public:
    static constexpr const char *kName = "Mod Overlay";
    static constexpr const char *kDescription = "Displays a list of all active mods.";
    explicit ModOverlay(std::uint8_t *image) : image_(image) {}
    // Combat. Config key: show_combat.
    BooleanSetting &show_combat() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ed100);
    }
    // Move. Config key: show_move.
    BooleanSetting &show_move() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ed120);
    }
    // Block. Config key: show_block.
    BooleanSetting &show_block() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ed140);
    }
    // Visual. Config key: show_visual.
    BooleanSetting &show_visual() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ed160);
    }
    // Utility. Config key: show_utility.
    BooleanSetting &show_utility() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ed180);
    }
    // Text size. Config key: text_size.
    NumberSetting &text_size() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ed200);
    }
    // Padding X. Config key: padding_x.
    NumberSetting &padding_x() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ed2b0);
    }
    // Padding Y. Config key: padding_y.
    NumberSetting &padding_y() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ed2e8);
    }
    // Rounding. Config key: bg_rounding.
    NumberSetting &bg_rounding() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ed278);
    }
    // name_color. Config key: name_color.
    ColorSetting &name_color() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2ed238);
    }
    // details_color. Config key: details_color.
    ColorSetting &details_color() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2ed258);
    }
    // Lowercase. Config key: lowercase.
    BooleanSetting &lowercase() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ed1c0);
    }
    // Show details. Config key: show_details.
    BooleanSetting &show_details() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ed1e0);
    }
    // Only bound modules. Config key: require_bound.
    BooleanSetting &require_bound() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ed1a0);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_mod_overlay_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_mod_overlay_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_mod_overlay_settings(&context, image_, &dependencies);
    }
    static void onSettingChanged(uint8_t *ev, uint8_t *im, const ModOverlayDependencies *d) {
        ::reconstruction::mod_overlay::onSettingChanged(ev, im, d);
    }
    static void onModuleStateChanged(uint8_t *ev, uint8_t *im, const ModOverlayDependencies *d) {
        ::reconstruction::mod_overlay::onModuleStateChanged(ev, im, d);
    }
    static void onStatusEvent(uint8_t *ev, uint8_t *im, const ModOverlayDependencies *d) {
        ::reconstruction::mod_overlay::onStatusEvent(ev, im, d);
    }
    static void onControlEvent(uint8_t *ev, uint8_t *im, const ModOverlayDependencies *d) {
        ::reconstruction::mod_overlay::onControlEvent(ev, im, d);
    }
    static void collectModules(uint8_t *ev, uint8_t *im, const ModOverlayDependencies *d) {
        ::reconstruction::mod_overlay::collectModules(ev, im, d);
    }
    static uint64_t compareWidth(const uint8_t *a, const uint8_t *b, endpoint invokeEndpoint) {
        return ::reconstruction::mod_overlay::compareWidth(a, b, invokeEndpoint);
    }
    void renderOverlay(uint8_t *event, endpoint invokeEndpoint) {
        ::reconstruction::mod_overlay::renderOverlay(event, image_, invokeEndpoint);
    }
    void appendModule(std::uintptr_t descriptor, const ModOverlayDependencies *deps) {
        ::reconstruction::mod_overlay::appendModule(descriptor, image_, deps);
    }
    void refreshVisibleModules(const std::uint8_t *registryList,
                               const ModOverlayDependencies *deps) {
        ::reconstruction::mod_overlay::refreshVisibleModules(registryList, image_, deps);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
