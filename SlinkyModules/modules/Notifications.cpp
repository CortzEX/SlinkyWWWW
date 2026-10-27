// Notifications

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Notifications.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Notifications.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Notifications: lib_win settings 0x35c80.
// UI 0x35bb0.
static constexpr UiStep ui_steps_Surface_Notifications[] = {
    {UiControl::section, "Hide if", 0},
    {UiControl::checkbox, nullptr, 0x2ed610},
    {UiControl::checkbox, nullptr, 0x2ed550},
    {UiControl::checkbox, nullptr, 0x2ed530},
    {UiControl::section, "Visible mod categories", 0},
    {UiControl::checkbox, nullptr, 0x2ed570},
    {UiControl::checkbox, nullptr, 0x2ed590},
    {UiControl::checkbox, nullptr, 0x2ed5b0},
    {UiControl::checkbox, nullptr, 0x2ed5d0},
    {UiControl::checkbox, nullptr, 0x2ed5f0},
};
static constexpr SettingsStep settings_steps_Surface_Notifications[] = {
    {SettingsControl::boolean, "hide_ingame", 0x2ed610},
    {SettingsControl::boolean, "hide_hold_notifs", 0x2ed550},
    {SettingsControl::boolean, "hide_bind_only", 0x2ed530},
    {SettingsControl::boolean, "show_combat", 0x2ed570},
    {SettingsControl::boolean, "show_move", 0x2ed590},
    {SettingsControl::boolean, "show_block", 0x2ed5b0},
    {SettingsControl::boolean, "show_visual", 0x2ed5d0},
    {SettingsControl::boolean, "show_utility", 0x2ed5f0},
};
static constexpr ModuleSurface surface_Surface_Notifications{
    ui_steps_Surface_Notifications, std::size(ui_steps_Surface_Notifications),
    settings_steps_Surface_Notifications, std::size(settings_steps_Surface_Notifications)};

extern "C" __declspec(dllexport) void
recovered_notifications_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                           const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Notifications, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_notifications_settings(SettingsContext *context, std::uint8_t *image,
                                 const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Notifications, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Notifications.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Notifications
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Notifications.cpp
static constexpr UiStep surface_notifications_ui_steps[] = {
    {UiControl::section, "Hide if", 0},
    {UiControl::checkbox, nullptr, 0x2ed610},
    {UiControl::checkbox, nullptr, 0x2ed550},
    {UiControl::checkbox, nullptr, 0x2ed530},
    {UiControl::section, "Visible mod categories", 0},
    {UiControl::checkbox, nullptr, 0x2ed570},
    {UiControl::checkbox, nullptr, 0x2ed590},
    {UiControl::checkbox, nullptr, 0x2ed5b0},
    {UiControl::checkbox, nullptr, 0x2ed5d0},
    {UiControl::checkbox, nullptr, 0x2ed5f0},
};
static constexpr SettingsStep surface_notifications_settings_steps[] = {
    {SettingsControl::boolean, "hide_ingame", 0x2ed610},
    {SettingsControl::boolean, "hide_hold_notifs", 0x2ed550},
    {SettingsControl::boolean, "hide_bind_only", 0x2ed530},
    {SettingsControl::boolean, "show_combat", 0x2ed570},
    {SettingsControl::boolean, "show_move", 0x2ed590},
    {SettingsControl::boolean, "show_block", 0x2ed5b0},
    {SettingsControl::boolean, "show_visual", 0x2ed5d0},
    {SettingsControl::boolean, "show_utility", 0x2ed5f0},
};
static constexpr ModuleSurface surface_notifications_surface{
    surface_notifications_ui_steps, std::size(surface_notifications_ui_steps),
    surface_notifications_settings_steps, std::size(surface_notifications_settings_steps)};

extern "C" __declspec(dllexport) void
recovered_notifications_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                                 const BoundSurfaceUiDependencies *dependencies) {
    render_module_surface(surface_notifications_surface, ui, layout, image, *dependencies);
}
// END SOURCE shared/BoundSurfaces.cpp@Notifications

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Notifications/Handshake.cpp
#ifndef SLINKY_SHARE_EC6E6112877731F26D17
#define SLINKY_SHARE_EC6E6112877731F26D17
// BEGIN SOURCE modules/Notifications/Module.hpp
#include "../runtime/shared/RenderNativeBindings.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_notifications_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                                 const BoundSurfaceUiDependencies *);
extern "C" void recovered_notifications_settings(SettingsContext *, std::uint8_t *,
                                                 const SurfaceSettingsDependencies *);

namespace reconstruction::notifications {
// The image view retains native storage offsets. It does not invent initialization.
using Endpoint6 = reconstruction::native_binding::RenderEndpoint<5, std::uint64_t>;
using Endpoint7 = reconstruction::native_binding::RenderEndpoint<6, std::uint64_t>;
__declspec(dllexport) void onModuleStateChanged(uint8_t *event, uint8_t *image, Endpoint6 call);
__declspec(dllexport) void advanceMessages(uint8_t *event, uint8_t *image, Endpoint6 call);
__declspec(dllexport) void onConfigAction(uint8_t *event, uint8_t *image, Endpoint6 call);
__declspec(dllexport) void onMessage(uint8_t *event, uint8_t *image, Endpoint6 call);
__declspec(dllexport) void onFriendChanged(uint8_t *event, uint8_t *image, Endpoint6 call);
__declspec(dllexport) void renderMessages(uint8_t *event, uint8_t *image, Endpoint7 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_notifications_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_notifications_settings(context, stateImage, &deps);
}
} // namespace reconstruction::notifications

namespace reconstruction::notifications {
std::uint8_t clearHandshake(std::uint8_t *);
struct MessageRecord {
    std::uint32_t kind;
    char text[101];
    std::uint8_t padding[3];
    float age;
};
static_assert(sizeof(MessageRecord) == 112);
static_assert(offsetof(MessageRecord, age) == 0x6c);
} // namespace reconstruction::notifications

namespace reconstruction::notifications::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t hide_ingame = 0x2ed610 + offsetof(BooleanSetting, current);
inline constexpr std::size_t hide_hold_notifs = 0x2ed550 + offsetof(BooleanSetting, current);
inline constexpr std::size_t hide_bind_only = 0x2ed530 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_combat = 0x2ed570 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_move = 0x2ed590 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_block = 0x2ed5b0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_visual = 0x2ed5d0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t show_utility = 0x2ed5f0 + offsetof(BooleanSetting, current);
} // namespace reconstruction::notifications::setting_offset
// END SOURCE modules/Notifications/Module.hpp

#endif // SLINKY_SHARE_EC6E6112877731F26D17

#include <intrin.h>
std::uint8_t reconstruction::notifications::clearHandshake(std::uint8_t *stateImage) {
    return static_cast<std::uint8_t>(
        _InterlockedExchange8(reinterpret_cast<volatile char *>(stateImage + 0x2fbfb0), 0));
}
// END SOURCE modules/Notifications/Handshake.cpp

// BEGIN SOURCE modules/Notifications/notifications.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses evidence/recovered_cpp/behavior/module_behavior_recovery/notifications/notifications.cpp
// SHA-256 f61136392536de73628db95b8c30624f8f00392d5a8b2d0e1dd2e3e3ac0fbe3b
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.

#include <emmintrin.h>
#include <intrin.h>
#include <stdint.h>
#include <string.h>
using endpoint_notifications = reconstruction::native_binding::RenderEndpoint<5, std::uint64_t>;
static uint64_t readWord_notifications(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t readDword_notifications(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static float readFloat_notifications(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static double readDouble_notifications(const void *p) {
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
static void writeFloat(void *p, float v) {
    memcpy(p, &v, 4);
}
static float addFloat_notifications(float a, float b) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static uint8_t *append(uint8_t *stateImage, uint32_t kind) {
    uint64_t start = readWord_notifications(stateImage + 0x2fc440),
             count = readWord_notifications(stateImage + 0x2fbfd8);
    uint8_t *record = stateImage + 0x2fbfe0 + 112 * ((start + count) % 10);
    writeDword(record, kind);
    writeDword(record + 0x6c, 0);
    if (count == 10)
        writeWord(stateImage + 0x2fc440, start + 1);
    else
        writeWord(stateImage + 0x2fbfd8, count + 1);
    return record + 4;
}
static uint64_t image_address(uint8_t *stateImage, uint64_t original) {
    return (uintptr_t)stateImage + (original - UINT64_C(0x180000000));
}
__declspec(dllexport) void
reconstruction::notifications::onModuleStateChanged(uint8_t *event, uint8_t *stateImage,
                                                    endpoint_notifications invokeEndpoint) {
    uint8_t *descriptor = (uint8_t *)(uintptr_t)readWord_notifications(event + 0x10);
    if (descriptor == stateImage + 0x2ed320) {
        if (!event[0x18]) {
            writeWord(stateImage + 0x2fbfd8, 0);
            return;
        }
        if (_InterlockedCompareExchange8((volatile char *)(stateImage + 0x2fbfb0), 1, 0) != 0)
            return;
        uint8_t *text = append(stateImage, 1);
        uint64_t app = readWord_notifications(stateImage + 0x13e498);
        uint64_t key = invokeEndpoint(
            0x9380, readDword_notifications((uint8_t *)(uintptr_t)(app + 0x1c)), 0, 0, 0, 0);
        invokeEndpoint(0xab710, (uintptr_t)text, 101, (uintptr_t)(stateImage + 0x151f02), key, 0);
        return;
    }
    uint32_t flags = readDword_notifications(descriptor + 0x18);
    if (flags & 16)
        return;
    if ((flags & 2) && stateImage[reconstruction::notifications::setting_offset::hide_bind_only])
        return;
    if (descriptor[0x20] == 1 &&
        stateImage[reconstruction::notifications::setting_offset::hide_hold_notifs])
        return;
    switch (readDword_notifications(descriptor + 0x10)) {
    case 0:
        if (!stateImage[reconstruction::notifications::setting_offset::show_combat])
            return;
        break;
    case 1:
        if (!stateImage[reconstruction::notifications::setting_offset::show_move])
            return;
        break;
    case 2:
        if (!stateImage[reconstruction::notifications::setting_offset::show_visual])
            return;
        break;
    case 3:
        if (!stateImage[reconstruction::notifications::setting_offset::show_block])
            return;
        break;
    case 4:
        if (stateImage[reconstruction::notifications::setting_offset::show_utility] != 1)
            return;
        break;
    }
    uint8_t *pending = stateImage + (event[0x18] ? 0x2fbfb8 : 0x2fbfc8);
    writeWord(pending, readWord_notifications(descriptor));
    writeDword(pending + 8, readDword_notifications(pending + 8) + 1);
}
__declspec(dllexport) void
reconstruction::notifications::advanceMessages(uint8_t *event, uint8_t *stateImage,
                                               endpoint_notifications invokeEndpoint) {
    if (stateImage[reconstruction::notifications::setting_offset::hide_ingame] == 1 &&
        !*(uint8_t *)(uintptr_t)(readWord_notifications(stateImage + 0x13e498) + 0x14)) {
        writeWord(stateImage + 0x2fbfd8, 0);
        writeDword(stateImage + 0x2fbfc0, 0);
        writeDword(stateImage + 0x2fbfd0, 0);
        return;
    }
    uint64_t count = readWord_notifications(stateImage + 0x2fbfd8),
             start = readWord_notifications(stateImage + 0x2fc440);
    float expiry = readFloat_notifications(stateImage + 0x151e48);
    while (count) {
        if (!(readFloat_notifications(stateImage + 0x2fbfe0 + 112 * (start % 10) + 0x6c) > expiry))
            break;
        ++start;
        writeWord(stateImage + 0x2fc440, start);
        --count;
        writeWord(stateImage + 0x2fbfd8, count);
    }
    for (unsigned disabled = 0; disabled < 2; ++disabled) {
        uint8_t *pending = stateImage + (disabled ? 0x2fbfc8 : 0x2fbfb8);
        uint32_t total = readDword_notifications(pending + 8);
        if (!total)
            continue;
        uint8_t *text = append(stateImage, 1);
        uint64_t label = (uintptr_t)(stateImage + (disabled ? 0x151f74 : 0x151f6c));
        invokeEndpoint(0xab710, (uintptr_t)text, 101,
                       (uintptr_t)(stateImage + (total == 1 ? 0x151f66 : 0x151f7d)), label,
                       total == 1 ? readWord_notifications(pending) : total);
        writeDword(pending + 8, 0);
    }
    count = readWord_notifications(stateImage + 0x2fbfd8);
    if (!count)
        return;
    uint32_t old_flags = readDword_notifications(event + 0x10);
    writeDword(event + 0x10, old_flags | 1);
    start = readWord_notifications(stateImage + 0x2fc440);
    float elapsed = readFloat_notifications(event + 0x14);
    double late = readDouble_notifications(stateImage + 0x151e50),
           early = readDouble_notifications(stateImage + 0x151e58);
    uint8_t transitioning = 0;
    for (uint64_t i = 0; i < count; ++i) {
        uint8_t *age = stateImage + 0x2fbfe0 + 112 * ((start + i) % 10) + 0x6c;
        float next = addFloat_notifications(readFloat_notifications(age), elapsed);
        writeFloat(age, next);
        if ((double)next > late || (double)next < early)
            transitioning = 1;
    }
    if (transitioning)
        writeDword(event + 0x10, old_flags | 3);
}
__declspec(dllexport) void
reconstruction::notifications::onConfigAction(uint8_t *event, uint8_t *stateImage,
                                              endpoint_notifications invokeEndpoint) {
    uint32_t kind = readDword_notifications(event + 0x10);
    if (kind == 2)
        return;
    uint64_t action = image_address(
                 stateImage, readWord_notifications(stateImage + 0x151f90 + 8 * (uint64_t)kind)),
             label = readWord_notifications(event + 8);
    if (!label)
        label = (uintptr_t)(stateImage + 0x151fb0);
    uint8_t *text = append(stateImage, 0);
    invokeEndpoint(0xab710, (uintptr_t)text, 101, (uintptr_t)(stateImage + 0x151f66), action,
                   label);
}
__declspec(dllexport) void
reconstruction::notifications::onMessage(uint8_t *event, uint8_t *stateImage,
                                         endpoint_notifications invokeEndpoint) {
    uint8_t *text = append(stateImage, 2);
    uint64_t message = readWord_notifications(event + 0x10);
    invokeEndpoint(0xab710, (uintptr_t)text, 101,
                   (uintptr_t)(stateImage + (message ? 0x151fe5 : 0x151fe8)),
                   message ? message : readDword_notifications(event + 8), 0);
}
__declspec(dllexport) void
reconstruction::notifications::onFriendChanged(uint8_t *event, uint8_t *stateImage,
                                               endpoint_notifications invokeEndpoint) {
    (void)invokeEndpoint;
    uint8_t *text = append(stateImage, 1);
    if (event[8] == 1) {
        writeWord(text + 5, UINT64_C(0x64656464612064));
        writeWord(text, UINT64_C(0x6120646e65697246));
    } else {
        writeWord(text + 7, UINT64_C(0x6465766f6d6572));
        writeWord(text, UINT64_C(0x7220646e65697246));
    }
}
// END SOURCE modules/Notifications/notifications.cpp

// BEGIN SOURCE modules/Notifications/notifications_render.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses
// evidence/recovered_cpp/behavior/module_behavior_recovery/notifications_render/notifications_render.cpp
// SHA-256 8abc6d25e316a3727b99bc9018ba10efc0b9616f1440d2669cc47d6d01d2c244
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.

#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
using endpoint_notifications_render =
    reconstruction::native_binding::RenderEndpoint<6, std::uint64_t>;
static uint64_t readWord_notifications_render(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t readDword_notifications_render(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static float readFloat_notifications_render(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static double readDouble_notifications_render(const void *p) {
    double v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t bits(float v) {
    uint32_t b;
    memcpy(&b, &v, 4);
    return b;
}
static float addFloat_notifications_render(float a, float b) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float subtractFloat(float a, float b) {
    return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float multiplyFloat(float a, float b) {
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
uint32_t *recovered_color_74130(uint32_t *, uint32_t, uint32_t, uint32_t);
__declspec(dllexport) void *recovered_theme_324b0(void *out, uint8_t *stateImage) {
    memcpy((uint8_t *)out + 8, stateImage + 0x2eb730, 4);
    memcpy(out, stateImage + 0x2eb728, 8);
    return out;
}
__declspec(dllexport) void
reconstruction::notifications::renderMessages(uint8_t *event, uint8_t *stateImage,
                                              endpoint_notifications_render invokeEndpoint) {
    if (!readWord_notifications_render(stateImage + 0x2fbfd8))
        return;
    if (stateImage[reconstruction::notifications::setting_offset::hide_ingame] == 1 &&
        !*(uint8_t *)(uintptr_t)(readWord_notifications_render(stateImage + 0x13e498) + 0x14))
        return;
    uint8_t *draw = (uint8_t *)(uintptr_t)readWord_notifications_render(event + 0x10);
    uint64_t saved_canvas = readWord_notifications_render(draw);
    invokeEndpoint(0x79610, saved_canvas, readDword_notifications_render(stateImage + 0x151e60), 0,
                   0, 0, 0);
    if (readWord_notifications_render(stateImage + 0x2fbfd8)) {
        float y = readFloat_notifications_render(stateImage + 0x151e64), initial_x = y,
              one = readFloat_notifications_render(stateImage + 0x151e70),
              white = readFloat_notifications_render(stateImage + 0x151e8c),
              dark = readFloat_notifications_render(stateImage + 0x151ea4),
              padding = readFloat_notifications_render(stateImage + 0x151eac),
              shrink = readFloat_notifications_render(stateImage + 0x151eb0);
        double duration = readDouble_notifications_render(stateImage + 0x151e68);
        for (uint64_t i = 0;; ++i) {
            uint8_t *record =
                stateImage + 0x2fbfe0 +
                112 * ((readWord_notifications_render(stateImage + 0x2fc440) + i) % 10);
            double age = (double)readFloat_notifications_render(record + 0x6c);
            float amount = one;
            if (duration > age)
                amount = recovered_smooth_a280((float)(age / duration), stateImage);
            else if (age > readDouble_notifications_render(stateImage + 0x151e78))
                amount = recovered_smooth_a280(
                    (float)((readDouble_notifications_render(stateImage + 0x151e80) - age) /
                            duration),
                    stateImage);
            amount = _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(one), _mm_set_ss(amount)));
            invokeEndpoint(0x74a60, saved_canvas, bits(amount), 0, 0, 0, 0);
            float x = addFloat_notifications_render(
                multiplyFloat(subtractFloat(one, amount),
                              readFloat_notifications_render(stateImage + 0x151e88)),
                initial_x);
            uint64_t canvas = readWord_notifications_render(draw);
            float color[4], main_rect[4], stripe[4], temporary[4], copy[4], text_rect[4];
            switch (readDword_notifications_render(record)) {
            case 0:
                recovered_color_74150(color, readFloat_notifications_render(stateImage + 0x151e94),
                                      readFloat_notifications_render(stateImage + 0x151e98),
                                      readFloat_notifications_render(stateImage + 0x151e9c), 1.f);
                break;
            case 1:
                recovered_theme_324b0(main_rect, stateImage);
                recovered_color_74130((uint32_t *)color, bits(main_rect[0]), bits(main_rect[1]),
                                      bits(main_rect[2]));
                break;
            case 2:
                recovered_color_74150(color, white,
                                      readFloat_notifications_render(stateImage + 0x151e90),
                                      readFloat_notifications_render(stateImage + 0x151e90), 1.f);
                break;
            default:
                recovered_color_74150(color, white, white, white, 1.f);
                break;
            }
            uint8_t *text = record + 4;
            uint32_t width_bits =
                (uint32_t)invokeEndpoint(0x7ae90, canvas, 0, 0, (uintptr_t)text, 0, 0);
            float width;
            memcpy(&width, &width_bits, 4);
            recovered_rect_a070(main_rect, x, y,
                                addFloat_notifications_render(
                                    width, readFloat_notifications_render(stateImage + 0x151ea0)),
                                42.f);
            recovered_color_74150(temporary, dark, dark, dark, 1.f);
            invokeEndpoint(0x74ef0, canvas, (uintptr_t)temporary, 0, 0, 0, 0);
            memcpy(copy, main_rect, 16);
            invokeEndpoint(0x10a60, (uintptr_t)draw, (uintptr_t)copy,
                           readDword_notifications_render(stateImage + 0x151ea8), 0, 0, 0);
            recovered_rect_a070(stripe, addFloat_notifications_render(main_rect[0], padding),
                                addFloat_notifications_render(main_rect[1], padding),
                                readFloat_notifications_render(stateImage + 0x151eb4),
                                addFloat_notifications_render(main_rect[3], shrink));
            memcpy(copy, color, 16);
            recovered_color_741b0(temporary, copy,
                                  readFloat_notifications_render(stateImage + 0x151eb8));
            invokeEndpoint(0x74ef0, canvas, (uintptr_t)temporary, 0, 0, 0, 0);
            memcpy(copy, stripe, 16);
            invokeEndpoint(0x10a60, (uintptr_t)draw, (uintptr_t)copy,
                           readDword_notifications_render(stateImage + 0x151ebc), 0, 0, 0);
            memcpy(copy, color, 16);
            invokeEndpoint(0x74ef0, canvas, (uintptr_t)copy, 0, 0, 0, 0);
            memcpy(copy, stripe, 16);
            invokeEndpoint(0x10cb0, (uintptr_t)draw, (uintptr_t)copy, 1, 0,
                           (uintptr_t)(stateImage + 0x151f88), 0);
            recovered_rect_a070(
                text_rect,
                addFloat_notifications_render(addFloat_notifications_render(stripe[0], stripe[2]),
                                              padding),
                main_rect[1],
                addFloat_notifications_render(subtractFloat(main_rect[2], stripe[2]), shrink),
                main_rect[3]);
            recovered_color_74150(temporary, white, white, white, 1.f);
            invokeEndpoint(0x74ef0, canvas, (uintptr_t)temporary, 0, 0, 0, 0);
            memcpy(copy, text_rect, 16);
            invokeEndpoint(0x10cb0, (uintptr_t)draw, (uintptr_t)copy, 0, 0, (uintptr_t)text, 0);
            y = addFloat_notifications_render(
                y, multiplyFloat(amount, readFloat_notifications_render(stateImage + 0x151ec0)));
            if (i + 1 >= readWord_notifications_render(stateImage + 0x2fbfd8))
                break;
        }
    }
    invokeEndpoint(0x74a60, saved_canvas, readDword_notifications_render(stateImage + 0x151e70), 0,
                   0, 0, 0);
}
// END SOURCE modules/Notifications/notifications_render.cpp

// Convenient borrowed-state interface

namespace shareable {
class Notifications {
  public:
    static constexpr const char *kName = "Notifications";
    static constexpr const char *kDescription = "Informs you when certain actions are performed.";
    explicit Notifications(std::uint8_t *image) : image_(image) {}
    // In-game. Config key: hide_ingame.
    BooleanSetting &hide_ingame() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ed610);
    }
    // Hold bind is used. Config key: hide_hold_notifs.
    BooleanSetting &hide_hold_notifs() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ed550);
    }
    // Module is bind-only. Config key: hide_bind_only.
    BooleanSetting &hide_bind_only() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ed530);
    }
    // Combat. Config key: show_combat.
    BooleanSetting &show_combat() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ed570);
    }
    // Move. Config key: show_move.
    BooleanSetting &show_move() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ed590);
    }
    // Block. Config key: show_block.
    BooleanSetting &show_block() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ed5b0);
    }
    // Visual. Config key: show_visual.
    BooleanSetting &show_visual() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ed5d0);
    }
    // Utility. Config key: show_utility.
    BooleanSetting &show_utility() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ed5f0);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_notifications_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_notifications_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_notifications_settings(&context, image_, &dependencies);
    }
    std::uint8_t clearHandshake() {
        return ::reconstruction::notifications::clearHandshake(image_);
    }
    void onModuleStateChanged(uint8_t *event, endpoint_notifications invokeEndpoint) {
        ::reconstruction::notifications::onModuleStateChanged(event, image_, invokeEndpoint);
    }
    void advanceMessages(uint8_t *event, endpoint_notifications invokeEndpoint) {
        ::reconstruction::notifications::advanceMessages(event, image_, invokeEndpoint);
    }
    void onConfigAction(uint8_t *event, endpoint_notifications invokeEndpoint) {
        ::reconstruction::notifications::onConfigAction(event, image_, invokeEndpoint);
    }
    void onMessage(uint8_t *event, endpoint_notifications invokeEndpoint) {
        ::reconstruction::notifications::onMessage(event, image_, invokeEndpoint);
    }
    void onFriendChanged(uint8_t *event, endpoint_notifications invokeEndpoint) {
        ::reconstruction::notifications::onFriendChanged(event, image_, invokeEndpoint);
    }
    void renderMessages(uint8_t *event, endpoint_notifications_render invokeEndpoint) {
        ::reconstruction::notifications::renderMessages(event, image_, invokeEndpoint);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
