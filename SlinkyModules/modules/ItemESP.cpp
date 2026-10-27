// Item ESP

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Item_ESP.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Item_ESP.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Item ESP: lib_win settings 0x417b0.
static constexpr SettingsStep settings_steps_Surface_Item_ESP[] = {
    {SettingsControl::number, "range", 0x2f1cb0},
    {SettingsControl::boolean, "show_count", 0x2f1c90},
    {SettingsControl::list, "allowed_items", 0x2f1d28},
    {SettingsControl::boolean, "highlight_all", 0x2f1d08},
    {SettingsControl::color, "default_color", 0x2f1ce8},
};
static constexpr ModuleSurface surface_Surface_Item_ESP{nullptr, 0, settings_steps_Surface_Item_ESP,
                                                        std::size(settings_steps_Surface_Item_ESP)};

extern "C" __declspec(dllexport) void
recovered_item_esp_settings(SettingsContext *context, std::uint8_t *image,
                            const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Item_ESP, context, image, *dependencies);
}

// Item ESP: lib_win runtime UI 0x41700.
extern "C" __declspec(dllexport) void
recovered_item_esp_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                      const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f1cb0);
    dependencies->section(ui, layout, "Customization");
    dependencies->checkbox(layout, ui, image + 0x2f1c90);
    dependencies->list(layout, ui, image + 0x2f1d28);
    dependencies->checkbox(layout, ui, image + 0x2f1d08);
    if (image[0x2f1d20] == 1) {
        dependencies->color(layout, ui, image + 0x2f1ce8);
    }
}
// END SOURCE native/verified/surfaces/Surface_Item_ESP.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Item_ESP
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Item_ESP.cpp
extern "C" __declspec(dllexport) void
recovered_item_esp_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                            const BoundSurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f1cb0);
    dependencies->section(ui, layout, "Customization");
    dependencies->checkbox(layout, ui, image + 0x2f1c90);
    dependencies->list(layout, ui, image + 0x2f1d28);
    dependencies->checkbox(layout, ui, image + 0x2f1d08);
    if (image[0x2f1d20] == 1) {
        dependencies->color(layout, ui, image + 0x2f1ce8);
    }
}
// END SOURCE shared/BoundSurfaces.cpp@Item_ESP

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Item_ESP/Buffer.cpp
#ifndef SLINKY_SHARE_CBE3E7D241B08AACE211
#define SLINKY_SHARE_CBE3E7D241B08AACE211
// BEGIN SOURCE modules/Item_ESP/Module.hpp
#include "../runtime/shared/RenderNativeBindings.hpp"
#include "../runtime/native/verified/module_esp_lists.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_item_esp_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                            const BoundSurfaceUiDependencies *);
extern "C" void recovered_item_esp_settings(SettingsContext *, std::uint8_t *,
                                            const SurfaceSettingsDependencies *);

namespace reconstruction::item_esp {
// The image view retains native storage offsets. It does not invent initialization.
using Endpoint8 = reconstruction::native_binding::RenderEndpoint<7, std::uint64_t>;
using Endpoint5 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
__declspec(dllexport) void onLifecycleEvent(uint8_t *event, uint8_t *image, Endpoint8 call);
__declspec(dllexport) void renderItems(uint8_t *event, uint8_t *image, Endpoint8 call);
__declspec(dllexport) int32_t compareItemIdentifier(const int32_t *left, const uint8_t *right);
__declspec(dllexport) void updateItems(uint8_t *event, uint8_t *image, Endpoint8 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_item_esp_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_item_esp_settings(context, stateImage, &deps);
}
} // namespace reconstruction::item_esp

namespace reconstruction::item_esp {
void releaseBuffer(std::uint8_t *, Endpoint5);
void appendCatalogCharacter(char *, std::uint8_t, Endpoint5);
} // namespace reconstruction::item_esp

namespace reconstruction::item_esp::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t range = 0x2f1cb0 + offsetof(NumberSetting, current);
inline constexpr std::size_t show_count = 0x2f1c90 + offsetof(BooleanSetting, current);
inline constexpr std::size_t highlight_all = 0x2f1d08 + offsetof(BooleanSetting, current);
inline constexpr std::size_t default_color = 0x2f1ce8 + offsetof(ColorSetting, current);
} // namespace reconstruction::item_esp::setting_offset
// END SOURCE modules/Item_ESP/Module.hpp

#endif // SLINKY_SHARE_CBE3E7D241B08AACE211

#include <cstring>
void reconstruction::item_esp::releaseBuffer(std::uint8_t *buffer, Endpoint5 invoke) {
    std::uint64_t zero = 0;
    std::memcpy(buffer, &zero, 8);
    std::memcpy(buffer + 8, &zero, 8);
    std::uint64_t allocation;
    std::memcpy(&allocation, buffer + 16, 8);
    invoke(0x13cf70, allocation, 0, 0, 0);
    std::memcpy(buffer + 16, &zero, 8);
}
// END SOURCE modules/Item_ESP/Buffer.cpp

// BEGIN SOURCE modules/Item_ESP/CatalogInput.cpp
void reconstruction::item_esp::appendCatalogCharacter(char *text, std::uint8_t character,
                                                      Endpoint5 invoke) {
    const auto length = invoke(0xab840, reinterpret_cast<std::uintptr_t>(text), 0, 0, 0);
    const auto alphabetic = static_cast<std::uint8_t>((character & 0xdf) + 0xbf) < 0x1a;
    const auto numeric = static_cast<std::uint8_t>(character - 0x30) < 10;
    if (length < 100 && (alphabetic || character == 0x20 || numeric))
        text[length] = static_cast<char>(character);
}
// END SOURCE modules/Item_ESP/CatalogInput.cpp

// BEGIN SOURCE modules/Item_ESP/item_esp.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses evidence/recovered_cpp/behavior/module_behavior_recovery/item_esp/item_esp.cpp
// SHA-256 ecddfb5edfe4a030d02b43b85429f85a84dc8f9e8b2ffb3e4049847e33a2997b
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.

#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
using endpoint = reconstruction::native_binding::RenderEndpoint<7, std::uint64_t>;
using endpoint4 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
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
static uint64_t target(uint64_t holder) {
    return readWord((uint8_t *)(uintptr_t)holder);
}
static uint64_t method(uint8_t *stateImage, uint32_t slot) {
    return target(readWord(stateImage + slot));
}
static float narrow(double v) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(v)));
}
static float value(uint64_t v) {
    uint32_t b = (uint32_t)v;
    float r;
    memcpy(&r, &b, 4);
    return r;
}
static void relative_position(double *out, uint8_t *record, uint8_t *event, double fraction) {
    double previous[3], current[3], position[3], camera[3];
    memcpy(previous, record, 24);
    memcpy(current, record + 24, 24);
    recovered_vector_lerp_9460(position, previous, current, fraction);
    memcpy(camera, event + 8, 24);
    recovered_vector_subtract_93d0(out, position, camera);
}
__declspec(dllexport) void reconstruction::item_esp::onLifecycleEvent(uint8_t *event,
                                                                      uint8_t *stateImage,
                                                                      endpoint invokeEndpoint) {
    (void)event;
    memset(stateImage + 0x3043a0, 0, 16);
    invokeEndpoint(0x13cf70, readWord(stateImage + 0x3043b0), 0, 0, 0, 0, 0, 0);
    memset(stateImage + 0x3043b0, 0, 8);
}
static void render(uint8_t *event, uint8_t *stateImage, endpoint invokeEndpoint) {
    if (!readWord(stateImage + 0x302130))
        return;
    invokeEndpoint(method(stateImage, 0x13e458), 0xbe2, 0, 0, 0, 0, 0, 0);
    float partial = readFloat(event + 0x28);
    recovered_render_293c0(stateImage, invokeEndpoint);
    if (readWord(stateImage + 0x302130)) {
        double fraction = (double)partial, offset = readDouble(stateImage + 0x154320);
        float size = readFloat(stateImage + 0x154328), alpha = readFloat(stateImage + 0x15432c);
        uint64_t color = readWord(stateImage + 0x13e448), pop = readWord(stateImage + 0x150cb8),
                 entryIndex = 0;
        uint8_t *record = stateImage + 0x302140;
        do {
            double p[3];
            relative_position(p, record, event, fraction);
            invokeEndpoint(method(stateImage, 0x150cc0), 0, 0, 0, 0, 0, 0, 0);
            invokeEndpoint(method(stateImage, 0x150cd8), floatBits(narrow(p[0])),
                           floatBits(narrow(p[1] + offset)), floatBits(narrow(p[2])), 0, 0, 0, 0);
            invokeEndpoint(method(stateImage, 0x150cd0), floatBits(size), floatBits(size),
                           floatBits(size), 0, 0, 0, 0);
            invokeEndpoint(target(color), readDword(record + 0x30), readDword(record + 0x34),
                           readDword(record + 0x38), floatBits(alpha), 0, 0, 0);
            recovered_render_29400(stateImage, invokeEndpoint);
            invokeEndpoint(target(pop), 0, 0, 0, 0, 0, 0, 0);
            ++entryIndex;
            record += 88;
        } while (entryIndex < readWord(stateImage + 0x302130));
    }
    recovered_render_295a0(stateImage, invokeEndpoint);
    if (stateImage[reconstruction::item_esp::setting_offset::show_count] != 1)
        return;
    uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord(event + 0x20);
    uint64_t camera =
        invokeEndpoint(0x22d40, readWord(gameContext), readWord(gameContext + 0x18), 0, 0, 0, 0, 0);
    uint64_t font = invokeEndpoint(0x272a0, readWord(gameContext), camera, 0, 0, 0, 0, 0);
    float pitch = value(invokeEndpoint(0x27200, readWord(gameContext), camera, 0, 0, 0, 0, 0));
    uint32_t yaw = (uint32_t)invokeEndpoint(0x27250, readWord(gameContext), camera, 0, 0, 0, 0, 0);
    partial = readFloat(event + 0x28);
    if (event[0x2c] == 1) {
        invokeEndpoint(0x277f0, readWord(gameContext), 0, 0, 0, 0, 0, 0);
        uint32_t color = readDword(stateImage + 0x154330);
        invokeEndpoint(0x278f0, readWord(gameContext), color, color, color, 0x3f800000, 0, 0);
    } else {
        invokeEndpoint(method(stateImage, 0x13e458), 0xde1, 0, 0, 0, 0, 0, 0);
        uint32_t color = readDword(stateImage + 0x154330);
        invokeEndpoint(method(stateImage, 0x150ca0), color, color, color, 0, 0, 0, 0);
    }
    uint64_t count = readWord(stateImage + 0x302130);
    if (count) {
        double fraction = (double)partial, offset = readDouble(stateImage + 0x154320),
               half = readDouble(stateImage + 0x154358);
        yaw ^= readDword(stateImage + 0x154340);
        uint64_t rotate = readWord(stateImage + 0x150cc8), entryIndex = 0;
        uint32_t one = readDword(stateImage + 0x154330), size = readDword(stateImage + 0x154350);
        uint8_t *record = stateImage + 0x302140;
        do {
            if (readWord(record + 0x40)) {
                double p[3];
                relative_position(p, record, event, fraction);
                invokeEndpoint(method(stateImage, 0x150cc0), 0, 0, 0, 0, 0, 0, 0);
                invokeEndpoint(method(stateImage, 0x150cd8), floatBits(narrow(p[0])),
                               floatBits(narrow(p[1] + offset)), floatBits(narrow(p[2])), 0, 0, 0,
                               0);
                invokeEndpoint(target(rotate), yaw, 0, one, 0, 0, 0, 0);
                invokeEndpoint(target(rotate), floatBits(pitch), one, 0, 0, 0, 0, 0);
                invokeEndpoint(method(stateImage, 0x150cd0), size, size, size, 0, 0, 0, 0);
                int32_t negative = (int32_t)(0u - readDword(record + 0x48));
                float x = narrow((double)negative * half);
                invokeEndpoint(0x27590, readWord(gameContext), font, readWord(record + 0x40),
                               floatBits(x), 0xc0800000, 0xffffffff, 1);
                invokeEndpoint(method(stateImage, 0x150cb8), 0, 0, 0, 0, 0, 0, 0);
                count = readWord(stateImage + 0x302130);
            }
            ++entryIndex;
            record += 88;
        } while (entryIndex < count);
    }
    if (event[0x2c])
        invokeEndpoint(0x27820, readWord(gameContext), 0, 0, 0, 0, 0, 0);
    else
        invokeEndpoint(method(stateImage, 0x13e450), 0xde1, 0, 0, 0, 0, 0, 0);
}
__declspec(dllexport) void reconstruction::item_esp::renderItems(uint8_t *event,
                                                                 uint8_t *stateImage,
                                                                 endpoint invokeEndpoint) {
    render(event, stateImage, invokeEndpoint);
}
// END SOURCE modules/Item_ESP/item_esp.cpp

// BEGIN SOURCE modules/Item_ESP/item_esp_update.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses
// evidence/recovered_cpp/behavior/module_behavior_recovery/item_esp_update/item_esp_update.cpp
// SHA-256 aca9dd71e36ce3864d5be462f19cfe1a47df01d0d95692a658deb16c7a634afd
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.

#include <emmintrin.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

using item_endpoint = reconstruction::native_binding::RenderEndpoint<7, std::uint64_t>;

static uint64_t read64(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t read32(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static double readf64(const void *p) {
    double v;
    memcpy(&v, p, 8);
    return v;
}
static float readf32(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static void write64(void *p, uint64_t v) {
    memcpy(p, &v, 8);
}
static void write32(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
static void write8(void *p, uint8_t v) {
    memcpy(p, &v, 1);
}
static uint64_t method_target(uint64_t object, uint32_t offset) {
    uint64_t table = read64((const void *)(uintptr_t)object);
    return read64((const void *)(uintptr_t)(table + offset));
}
static uint64_t invoke(item_endpoint invokeEndpoint, uint64_t target, uint64_t a, uint64_t b,
                       uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g) {
    return invokeEndpoint(target, a, b, c, d, e, f, g);
}
static uint64_t game_at(uint64_t bridge) {
    return read64((const void *)(uintptr_t)bridge);
}
static uint64_t game_call(item_endpoint invokeEndpoint, uint64_t bridge, uint32_t rva, uint64_t a,
                          uint64_t b, uint64_t c, uint64_t d, uint64_t e, uint64_t f, uint64_t g) {
    return invoke(invokeEndpoint, rva, a, b, c, d, e, f, g);
}

/* Original callback target passed to the UTF-16 label lookup at 0x13d0e0. */
__declspec(dllexport) int32_t
reconstruction::item_esp::compareItemIdentifier(const int32_t *left, const uint8_t *right) {
    uint32_t a, b, result;
    int32_t signed_result;
    memcpy(&a, left, 4);
    b = read32(right + 0x14);
    result = a - b;
    memcpy(&signed_result, &result, 4);
    return signed_result;
}

__declspec(dllexport) void reconstruction::item_esp::updateItems(uint8_t *event,
                                                                 uint8_t *stateImage,
                                                                 item_endpoint invokeEndpoint) {
    const uint64_t bridge = read64(event + 8);
    uint64_t count = read64(stateImage + 0x302130);

    /* Drop cached label objects before rebuilding the 88-byte record table. */
    if (count) {
        uint64_t client = read64((const void *)(uintptr_t)(game_at(bridge) + 8));
        for (uint64_t i = 0; i < count; i++) {
            uint8_t *record = stateImage + 0x302180 + i * 0x58;
            if (read64(record)) {
                invoke(invokeEndpoint, method_target(client, 0xb0), client, read64(record), 0, 0, 0,
                       0, 0);
                write64(record, 0);
                count = read64(stateImage + 0x302130);
            }
        }
    }
    write64(stateImage + 0x302130, 0);
    if (!read64((const void *)(uintptr_t)(bridge + 0x20)))
        return;

    uint8_t query[0x30], origin[0x30], current[0x30];
    memset(query, 0, 0x30);
    memset(origin, 0, 0x30);
    game_call(invokeEndpoint, bridge, 0x23030, (uint64_t)(uintptr_t)query, game_at(bridge),
              read64((const void *)(uintptr_t)(bridge + 0x28)), 0, 0, 0, 0);
    uint64_t list = game_call(invokeEndpoint, bridge, 0x24620, game_at(bridge),
                              read64((const void *)(uintptr_t)(bridge + 0x20)), 0, 0, 0, 0, 0);
    int32_t reported =
        (int32_t)game_call(invokeEndpoint, bridge, 0x24e50, game_at(bridge), list, 0, 0, 0, 0, 0);
    for (int32_t entryIndex = 0; entryIndex < reported; entryIndex++) {
        do {
            uint64_t item = game_call(invokeEndpoint, bridge, 0x24e80, game_at(bridge), list,
                                      (uint32_t)entryIndex, 0, 0, 0, 0);
            uint64_t entity =
                game_call(invokeEndpoint, bridge, 0x27cf0, game_at(bridge), item, 0, 0, 0, 0, 0);
            if (!entity)
                break;
            if ((uint8_t)game_call(invokeEndpoint, bridge, 0x237b0, game_at(bridge), entity, 0, 0,
                                   0, 0, 0))
                break;

            memset(origin, 0, 0x30);
            game_call(invokeEndpoint, bridge, 0x23030, (uint64_t)(uintptr_t)origin, game_at(bridge),
                      entity, 0, 0, 0, 0);
            double distance =
                recovered_vector_distance_squared((const double *)origin, (const double *)query);
            float radius = readf32(stateImage + reconstruction::item_esp::setting_offset::range);
            __m128 r = _mm_set_ss(radius);
            r = _mm_mul_ss(r, r);
            double radius2 = (double)_mm_cvtss_f32(r);
            /* UCOMISD followed by JA rejects only ordered values above radius;
               unordered NaN distances fall through into record creation. */
            if (distance > radius2)
                break;

            /* Destination record is captured before any item/game helper can mutate count. */
            uint64_t captured_count = read64(stateImage + 0x302130);
            uint8_t *record = stateImage + 0x302140 + captured_count * 0x58;
            uint64_t base_game = game_at(bridge);
            uint64_t stack =
                game_call(invokeEndpoint, bridge, 0x27d30, base_game, entity, 0, 0, 0, 0, 0);
            if (!stack)
                break;
            int32_t quantity = (int32_t)game_call(invokeEndpoint, bridge, 0x25d70, base_game, stack,
                                                  0, 0, 0, 0, 0);
            if (quantity <= 0)
                break;
            uint64_t item_object =
                game_call(invokeEndpoint, bridge, 0x25d10, base_game, stack, 0, 0, 0, 0, 0);
            if (!item_object)
                break;
            uint32_t item_id = (uint32_t)game_call(invokeEndpoint, bridge, 0x25c50, base_game,
                                                   item_object, 0, 0, 0, 0, 0);

            uint64_t string_data = 0;
            if (read64(stateImage + 0x3043b0)) {
                string_data = invoke(invokeEndpoint, 0x13d0e0, (uint64_t)(uintptr_t)&item_id,
                                     read64(stateImage + 0x3043b0), read64(stateImage + 0x3043a0),
                                     0x18, 0x180041830, 0, 0);
            }
            if (!string_data) {
                if (!stateImage[reconstruction::item_esp::setting_offset::highlight_all])
                    break;
                string_data = (uint64_t)(uintptr_t)(stateImage + 0x2f1ce8);
            }

            /* Record fields through +0x50 follow the original individual stores. */
            write64(record + 0x30, read64((const void *)(uintptr_t)(string_data + 8)));
            write32(record + 0x38, read32((const void *)(uintptr_t)(string_data + 0x10)));
            write32(record + 0x4c, item_id);
            write8(record + 0x50, (uint8_t)quantity);
            write64(record + 0x28, read64((const void *)(uintptr_t)(origin + 0x10)));
            memcpy(record + 0x18, origin, 16);

            memset(current, 0, 0x30);
            game_call(invokeEndpoint, bridge, 0x230d0, (uint64_t)(uintptr_t)current,
                      game_at(bridge), entity, 0, 0, 0, 0);
            write64(record + 0x10, read64(current + 0x10));
            memcpy(record, current, 16);
            uint64_t now = read64(stateImage + 0x302130) + 1;
            write64(stateImage + 0x302130, now);
            if (now == 100)
                goto collection_done;
        } while (0);
        reported = (int32_t)game_call(invokeEndpoint, bridge, 0x24e50, game_at(bridge), list, 0, 0,
                                      0, 0, 0);
    }

collection_done:
    if (stateImage[reconstruction::item_esp::setting_offset::show_count] != 1 ||
        !read64(stateImage + 0x302130))
        return;
    uint64_t world = game_call(invokeEndpoint, bridge, 0x22d40, game_at(bridge),
                               read64((const void *)(uintptr_t)(bridge + 0x18)), 0, 0, 0, 0, 0);
    uint64_t camera =
        game_call(invokeEndpoint, bridge, 0x272a0, game_at(bridge), world, 0, 0, 0, 0, 0);
    if (!camera || !read64(stateImage + 0x302130))
        return;
    double merge_radius = readf64(stateImage + 0x154360);
    for (uint64_t i = 0; i < read64(stateImage + 0x302130); i++) {
        uint8_t *record = stateImage + 0x302140 + i * 0x58;
        uint64_t quantity = record[0x50];
        if (!quantity)
            continue;
        uint64_t total = quantity;
        for (uint64_t j = 0; j < read64(stateImage + 0x302130); j++) {
            if (i == j)
                continue;
            uint8_t *other = stateImage + 0x302140 + j * 0x58;
            if (read32(record + 0x4c) != read32(other + 0x4c))
                continue;
            double d2 = recovered_vector_distance_squared((const double *)(record + 0x18),
                                                          (const double *)(other + 0x18));
            if (d2 < merge_radius) {
                total += (uint64_t)other[0x50];
                write8(other + 0x50, 0);
            }
        }
        uint8_t clamped = (uint8_t)(total < 99 ? total : 99);
        write8(record + 0x50, clamped);
        if (total > 1) {
            uint64_t row_game = game_at(bridge);
            invoke(invokeEndpoint, 0xab710, (uint64_t)(uintptr_t)(stateImage + 0x3043b8), 5,
                   (uint64_t)(uintptr_t)(stateImage + 0x1543cb), clamped, 0, 0, 0);
            uint64_t client = read64((const void *)(uintptr_t)(row_game + 8));
            uint64_t label = invoke(invokeEndpoint, method_target(client, 0x538), client,
                                    (uint64_t)(uintptr_t)(stateImage + 0x3043b8), 0, 0, 0, 0, 0);
            if (label) {
                label = invoke(invokeEndpoint, method_target(client, 0xa8), client, label, 0, 0, 0,
                               0, 0);
                write64(record + 0x40, label);
                if (label) {
                    uint32_t color = (uint32_t)game_call(invokeEndpoint, bridge, 0x27560, row_game,
                                                         camera, label, 0, 0, 0, 0);
                    write32(record + 0x48, color);
                }
            } else
                write64(record + 0x40, 0);
        } else
            write64(record + 0x40, 0);
    }
}
// END SOURCE modules/Item_ESP/item_esp_update.cpp

// Convenient borrowed-state interface

namespace shareable {
class ItemESP {
  public:
    static constexpr const char *kName = "Item ESP";
    static constexpr const char *kDescription = "Highlights dropped items.";
    explicit ItemESP(std::uint8_t *image) : image_(image) {}
    // Range. Config key: range.
    NumberSetting &range() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f1cb0);
    }
    // Show count. Config key: show_count.
    BooleanSetting &show_count() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f1c90);
    }
    // allowed_items. Config key: allowed_items.
    ListSetting &allowed_items() const {
        return *reinterpret_cast<ListSetting *>(image_ + 0x2f1d28);
    }
    // Highlight all items. Config key: highlight_all.
    BooleanSetting &highlight_all() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f1d08);
    }
    // default_color. Config key: default_color.
    ColorSetting &default_color() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2f1ce8);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_item_esp_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_item_esp_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_item_esp_settings(&context, image_, &dependencies);
    }
    static void releaseBuffer(std::uint8_t *buffer, ::reconstruction::item_esp::Endpoint5 invoke) {
        ::reconstruction::item_esp::releaseBuffer(buffer, invoke);
    }
    static void appendCatalogCharacter(char *text, std::uint8_t character,
                                       ::reconstruction::item_esp::Endpoint5 invoke) {
        ::reconstruction::item_esp::appendCatalogCharacter(text, character, invoke);
    }
    void onLifecycleEvent(uint8_t *event, endpoint invokeEndpoint) {
        ::reconstruction::item_esp::onLifecycleEvent(event, image_, invokeEndpoint);
    }
    void renderItems(uint8_t *event, endpoint invokeEndpoint) {
        ::reconstruction::item_esp::renderItems(event, image_, invokeEndpoint);
    }
    static int32_t compareItemIdentifier(const int32_t *left, const uint8_t *right) {
        return ::reconstruction::item_esp::compareItemIdentifier(left, right);
    }
    void updateItems(uint8_t *event, item_endpoint invokeEndpoint) {
        ::reconstruction::item_esp::updateItems(event, image_, invokeEndpoint);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
