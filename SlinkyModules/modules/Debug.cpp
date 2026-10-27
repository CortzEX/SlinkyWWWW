// Debug

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Debug.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Debug.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Debug: lib_win settings 0x46a60.
// UI 0x46a00.
static constexpr UiStep ui_steps_Surface_Debug[] = {
    {UiControl::section, "Main", 0},
    {UiControl::checkbox, nullptr, 0x2f4680},
    {UiControl::checkbox, nullptr, 0x2f4640},
    {UiControl::checkbox, nullptr, 0x2f4660},
};
static constexpr SettingsStep settings_steps_Surface_Debug[] = {
    {SettingsControl::boolean, "clicks", 0x2f4680},
    {SettingsControl::boolean, "hurt_time", 0x2f4640},
    {SettingsControl::boolean, "item_use_state", 0x2f4660},
};
static constexpr ModuleSurface surface_Surface_Debug{
    ui_steps_Surface_Debug, std::size(ui_steps_Surface_Debug), settings_steps_Surface_Debug,
    std::size(settings_steps_Surface_Debug)};

extern "C" __declspec(dllexport) void
recovered_debug_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                   const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Debug, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_debug_settings(SettingsContext *context, std::uint8_t *image,
                         const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Debug, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Debug.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Debug
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Debug.cpp
static constexpr UiStep surface_debug_ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::checkbox, nullptr, 0x2f4680},
    {UiControl::checkbox, nullptr, 0x2f4640},
    {UiControl::checkbox, nullptr, 0x2f4660},
};
static constexpr SettingsStep surface_debug_settings_steps[] = {
    {SettingsControl::boolean, "clicks", 0x2f4680},
    {SettingsControl::boolean, "hurt_time", 0x2f4640},
    {SettingsControl::boolean, "item_use_state", 0x2f4660},
};
static constexpr ModuleSurface surface_debug_surface{
    surface_debug_ui_steps, std::size(surface_debug_ui_steps), surface_debug_settings_steps,
    std::size(surface_debug_settings_steps)};

extern "C" __declspec(dllexport) void
recovered_debug_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                         const BoundSurfaceUiDependencies *dependencies) {
    render_module_surface(surface_debug_surface, ui, layout, image, *dependencies);
}
// END SOURCE shared/BoundSurfaces.cpp@Debug

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Debug/debug.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses evidence/recovered_cpp/behavior/module_behavior_recovery/debug/debug.cpp
// SHA-256 3b33548d4191ef0f8008861c530b778b58dde795cd7232e6b5506e82bd342630
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.
#ifndef SLINKY_SHARE_24A89DD564A8E5FA98AD
#define SLINKY_SHARE_24A89DD564A8E5FA98AD
// BEGIN SOURCE modules/Debug/Module.hpp
#include "../runtime/shared/RenderNativeBindings.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_debug_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                         const BoundSurfaceUiDependencies *);
extern "C" void recovered_debug_settings(SettingsContext *, std::uint8_t *,
                                         const SurfaceSettingsDependencies *);

namespace reconstruction::debug {
// The image view retains native storage offsets. It does not invent initialization.
using Dependency8 = reconstruction::native_binding::RenderEndpoint<7, std::uint32_t>;
__declspec(dllexport) void onMovement(uint8_t *event, uint8_t *image, Dependency8 call);
__declspec(dllexport) void onRender(uint8_t *event, uint8_t *image, Dependency8 call);
__declspec(dllexport) void onPosition(uint8_t *event, uint8_t *image, Dependency8 call);
__declspec(dllexport) void onPacket(uint8_t *event, uint8_t *image, Dependency8 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_debug_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_debug_settings(context, stateImage, &deps);
}
} // namespace reconstruction::debug

namespace reconstruction::debug::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t clicks = 0x2f4680 + offsetof(BooleanSetting, current);
inline constexpr std::size_t hurt_time = 0x2f4640 + offsetof(BooleanSetting, current);
inline constexpr std::size_t item_use_state = 0x2f4660 + offsetof(BooleanSetting, current);
} // namespace reconstruction::debug::setting_offset
// END SOURCE modules/Debug/Module.hpp

#endif // SLINKY_SHARE_24A89DD564A8E5FA98AD

#include <intrin.h>
#include <stdint.h>
#include <string.h>
using dependency = reconstruction::native_binding::RenderEndpoint<7, std::uint32_t>;
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
static void pd(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
static uint64_t invoke(dependency invokeEndpoint, uint32_t r, uint64_t a, uint64_t b) {
    return invokeEndpoint(r, a, b, 0, 0, 0, 0, 0);
}
__declspec(dllexport) void reconstruction::debug::onMovement(uint8_t *event, uint8_t *stateImage,
                                                             dependency invokeEndpoint) {
    uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord(event + 8);
    if (gameContext[0x40] != 1)
        return;
    if (stateImage[reconstruction::debug::setting_offset::hurt_time] == 1) {
        int32_t hurt = (int32_t)invoke(invokeEndpoint, 0x239f0, readWord(gameContext),
                                       readWord(gameContext + 0x28));
        if (hurt >= 7) {
            uint64_t game = readWord(gameContext);
            uint32_t tick =
                (uint32_t)invoke(invokeEndpoint, 0x23760, game, readWord(gameContext + 0x28));
            uint32_t color = 0x66, entryIndex = (uint32_t)hurt - 7;
            if (entryIndex <= 3)
                color = readDword(stateImage + 0x155200 + entryIndex * 4);
            uint32_t sprint = (uint8_t)invoke(invokeEndpoint, 0x23690, readWord(gameContext),
                                              readWord(gameContext + 0x28))
                                  ? 0x38
                                  : 0x63;
            uint32_t block = (uint8_t)invoke(invokeEndpoint, 0x23f90, readWord(gameContext),
                                             readWord(gameContext + 0x28))
                                 ? 0x63
                                 : 0x38;
            invokeEndpoint(0x291f0, game, (uintptr_t)(stateImage + 0x155136), tick % 1000, color,
                           (uint32_t)hurt, sprint, block);
        }
    }
    if (stateImage[reconstruction::debug::setting_offset::item_use_state] != 1)
        return;
    uint8_t use = stateImage[0x3049b9];
    if ((use & 1) == stateImage[0x3049b8])
        return;
    stateImage[0x3049b8] = use & 1;
    uint64_t game = readWord(gameContext);
    uint32_t tick = (uint32_t)invoke(invokeEndpoint, 0x23760, game, readWord(gameContext + 0x28));
    invokeEndpoint(0x291f0, game, (uintptr_t)(stateImage + 0x15517d), tick % 1000,
                   (uintptr_t)(stateImage + ((use & 1) ? 0x15519d : 0x1551a4)), 0, 0, 0);
}
__declspec(dllexport) void reconstruction::debug::onRender(uint8_t *event, uint8_t *stateImage,
                                                           dependency invokeEndpoint) {
    uint32_t kind = readDword(event + 0x24);
    if (kind != 0 && kind != 3)
        return;
    if (invoke(invokeEndpoint, 0x26580, readWord(event + 8), readWord(event + 0x10))) {
        _InterlockedExchange8((volatile char *)(stateImage + 0x3049b9), 1);
        return;
    }
    uint64_t packet = invoke(invokeEndpoint, 0x264f0, readWord(event + 8), readWord(event + 0x10));
    if (!packet)
        return;
    if ((uint32_t)invoke(invokeEndpoint, 0x26530, readWord(event + 8), packet) == 5)
        _InterlockedExchange8((volatile char *)(stateImage + 0x3049b9), 0);
}
__declspec(dllexport) void reconstruction::debug::onPosition(uint8_t *event, uint8_t *stateImage,
                                                             dependency invokeEndpoint) {
    (void)invokeEndpoint;
    if (stateImage[reconstruction::debug::setting_offset::clicks] != 1)
        return;
    uint32_t at = event[0x10] ? 0x3049bc : 0x3049c0;
    pd(stateImage + at, readDword(stateImage + at) + 1);
    pd(stateImage + 0x3049c4, 0);
}
__declspec(dllexport) void reconstruction::debug::onPacket(uint8_t *event, uint8_t *stateImage,
                                                           dependency invokeEndpoint) {
    uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord(event + 8);
    if (gameContext[0x40] != 1)
        return;
    uint32_t age = readDword(stateImage + 0x3049c4);
    if (stateImage[reconstruction::debug::setting_offset::clicks] == 1) {
        if (age <= 9) {
            uint32_t left = readDword(stateImage + 0x3049bc),
                     right = readDword(stateImage + 0x3049c0);
            uint32_t lc = left == 0   ? 0x38
                          : left == 1 ? 0x61
                                      : 0x32,
                     rc = right == 0   ? 0x38
                          : right == 1 ? 0x62
                                       : 0x33;
            uint64_t game = readWord(gameContext);
            uint32_t tick =
                (uint32_t)invoke(invokeEndpoint, 0x23760, game, readWord(gameContext + 0x28));
            invokeEndpoint(0x291f0, game, (uintptr_t)(stateImage + 0x1551b1), tick % 1000, lc,
                           readDword(stateImage + 0x3049bc), rc, readDword(stateImage + 0x3049c0));
            age = readDword(stateImage + 0x3049c4);
        }
        pd(stateImage + 0x3049bc, 0);
        pd(stateImage + 0x3049c0, 0);
    }
    pd(stateImage + 0x3049c4, age + 1);
}
// END SOURCE modules/Debug/debug.cpp

// Convenient borrowed-state interface

namespace shareable {
class Debug {
  public:
    static constexpr const char *kName = "Debug";
    static constexpr const char *kDescription = "Prints debug information in chat.";
    explicit Debug(std::uint8_t *image) : image_(image) {}
    // Clicks. Config key: clicks.
    BooleanSetting &clicks() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4680);
    }
    // Hurt time. Config key: hurt_time.
    BooleanSetting &hurt_time() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4640);
    }
    // Server item use state. Config key: item_use_state.
    BooleanSetting &item_use_state() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4660);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_debug_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_debug_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_debug_settings(&context, image_, &dependencies);
    }
    void onMovement(uint8_t *event, dependency invokeEndpoint) {
        ::reconstruction::debug::onMovement(event, image_, invokeEndpoint);
    }
    void onRender(uint8_t *event, dependency invokeEndpoint) {
        ::reconstruction::debug::onRender(event, image_, invokeEndpoint);
    }
    void onPosition(uint8_t *event, dependency invokeEndpoint) {
        ::reconstruction::debug::onPosition(event, image_, invokeEndpoint);
    }
    void onPacket(uint8_t *event, dependency invokeEndpoint) {
        ::reconstruction::debug::onPacket(event, image_, invokeEndpoint);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
