// GUI

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/GUI.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_GUI.cpp
#include "../runtime/native/verified/module_surface.hpp"

// GUI: lib_win settings 0x32870.
static constexpr SettingsStep settings_steps_Surface_GUI[] = {
    {SettingsControl::choice, "scale", 0x2eb970},
    {SettingsControl::color, "accent_color", 0x2eb720},
    {SettingsControl::boolean, "allow_input", 0x2eb9b0},
    {SettingsControl::boolean, "compact", 0x2eb9d0},
    {SettingsControl::boolean, "wide", 0x2eb9f0},
};
static constexpr ModuleSurface surface_Surface_GUI{nullptr, 0, settings_steps_Surface_GUI,
                                                   std::size(settings_steps_Surface_GUI)};

extern "C" __declspec(dllexport) void
recovered_gui_settings(SettingsContext *context, std::uint8_t *image,
                       const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_GUI, context, image, *dependencies);
}

// GUI: lib_win runtime UI 0x327d0.
extern "C" __declspec(dllexport) void recovered_gui_ui(std::uint64_t ui, std::uint64_t layout,
                                                       std::uint8_t *image,
                                                       const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, image + 0x2eb970);
    dependencies->color(layout, ui, image + 0x2eb720);
    dependencies->checkbox(layout, ui, image + 0x2eb9b0);
    dependencies->section(ui, layout, "Layout");
    dependencies->checkbox(layout, ui, image + 0x2eb9d0);
    dependencies->checkbox(layout, ui, image + 0x2eb9f0);
}
// END SOURCE native/verified/surfaces/Surface_GUI.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@GUI
// Same native ordering as reconstruction/native/verified/surfaces/Surface_GUI.cpp
extern "C" __declspec(dllexport) void
recovered_gui_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                       const BoundSurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, image + 0x2eb970);
    dependencies->color(layout, ui, image + 0x2eb720);
    dependencies->checkbox(layout, ui, image + 0x2eb9b0);
    dependencies->section(ui, layout, "Layout");
    dependencies->checkbox(layout, ui, image + 0x2eb9d0);
    dependencies->checkbox(layout, ui, image + 0x2eb9f0);
}
// END SOURCE shared/BoundSurfaces.cpp@GUI

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/GUI/gui.cpp
#include "../runtime/shared/RenderNativeBindings.hpp"
// Source-equivalent reconstruction from the supplied native evidence.
// Semantic identifiers were assigned during reverse engineering. Original names,
// namespaces and inline boundaries generally cannot be recovered.
// Reuses evidence/recovered_cpp/behavior/module_behavior_recovery/gui/gui.cpp
// SHA-256 6e1c848caef39dfd81084a9bd1aeda160c003c34d1662afc52a7fded7fc83cd8
// Changes rename recovered algorithms and make C pointer/scope rules explicit in C++.
// External endpoint arguments retain native widths, ordering and identities.
#ifndef SLINKY_SHARE_568FBC576981B76E91CD
#define SLINKY_SHARE_568FBC576981B76E91CD
// BEGIN SOURCE modules/GUI/Module.hpp
#include "../runtime/shared/RenderNativeBindings.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_gui_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                       const BoundSurfaceUiDependencies *);
extern "C" void recovered_gui_settings(SettingsContext *, std::uint8_t *,
                                       const SurfaceSettingsDependencies *);

namespace reconstruction::gui {
// The image view retains native storage offsets. It does not invent initialization.
using Dependency5 = reconstruction::native_binding::RenderEndpoint<4, std::uint32_t>;
__declspec(dllexport) void onRenderFrame(uint8_t *event, uint8_t *image, Dependency5 call);
__declspec(dllexport) void onInput(uint8_t *event, uint8_t *image, Dependency5 call);
__declspec(dllexport) void resetState(uint8_t *event, uint8_t *image, Dependency5 call);
__declspec(dllexport) void onModuleStateChanged(uint8_t *event, uint8_t *image, Dependency5 call);
__declspec(dllexport) void clearState(uint8_t *event, uint8_t *image, Dependency5 call);

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_gui_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_gui_settings(context, stateImage, &deps);
}
} // namespace reconstruction::gui

namespace reconstruction::gui::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t scale = 0x2eb970 + offsetof(ChoiceSetting, current);
inline constexpr std::size_t accent_color = 0x2eb720 + offsetof(ColorSetting, current);
inline constexpr std::size_t allow_input = 0x2eb9b0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t compact = 0x2eb9d0 + offsetof(BooleanSetting, current);
inline constexpr std::size_t wide = 0x2eb9f0 + offsetof(BooleanSetting, current);
} // namespace reconstruction::gui::setting_offset
// END SOURCE modules/GUI/Module.hpp

#endif // SLINKY_SHARE_568FBC576981B76E91CD

#include <stdint.h>
#include <string.h>
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
static void pd(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
__declspec(dllexport) void recovered_gui_start_11800(uint8_t *state, uint64_t time_bits) {
    pd(state + 0x4b8, 0);
    memcpy(state + 0x498, &time_bits, 8);
}
__declspec(dllexport) void recovered_gui_reset_12a80(uint8_t *state, dependency invokeEndpoint) {
    invokeEndpoint(0x165f0, (uintptr_t)state, 0, 0, 0);
}
__declspec(dllexport) void recovered_gui_clear_12a90(uint8_t *state) {
    pd(state + 0x370, 0);
    state[0x4c8] = 0;
}
__declspec(dllexport) void reconstruction::gui::onRenderFrame(uint8_t *event, uint8_t *stateImage,
                                                              dependency invokeEndpoint) {
    (void)stateImage;
    uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord(event + 8);
    if ((uint8_t)invokeEndpoint(0x25840, readWord(gameContext), 0, 0, 0))
        invokeEndpoint(0x25880, readWord(gameContext), 0, 0, 0);
}
__declspec(dllexport) void reconstruction::gui::onInput(uint8_t *event, uint8_t *stateImage,
                                                        dependency invokeEndpoint) {
    if (readWord(event + 0x10) != (uintptr_t)(stateImage + 0x2eb740))
        return;
    uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord(event + 8);
    uint64_t game = readWord(gameContext);
    if (event[0x18] == 1) {
        if ((uint8_t)invokeEndpoint(0x25840, game, 0, 0, 0)) {
            int32_t width = (int32_t)invokeEndpoint(0x27a60, readWord(gameContext), 0, 0, 0);
            int32_t height = (int32_t)invokeEndpoint(0x27a90, readWord(gameContext), 0, 0, 0);
            invokeEndpoint(0x25940, readWord(gameContext), (uint32_t)(width / 2),
                           (uint32_t)(height / 2), 0);
            invokeEndpoint(0x25880, readWord(gameContext), 0, 0, 0);
        }
        uint64_t clock_bits = invokeEndpoint(0x4c270, 0, 0, 0, 0);
        recovered_gui_start_11800(stateImage + 0x2f9e30, clock_bits);
        return;
    }
    if ((uint8_t)invokeEndpoint(0x22e60, game, readWord(gameContext + 0x18), 0, 0))
        invokeEndpoint(0x25880, readWord(gameContext), 1, 0, 0);
    recovered_gui_reset_12a80(stateImage + 0x2f9e30, invokeEndpoint);
    recovered_gui_clear_12a90(stateImage + 0x2f9e30);
    if (stateImage[0x2fa300] != 0)
        return;
    uint32_t id = (uint32_t)invokeEndpoint(0xbbd0, readWord(gameContext + 8),
                                           readWord(gameContext + 0x10), 0, 0);
    if (!id)
        return;
    uint8_t message[72] = {0};
    pd(message, 12);
    pd(message + 8, id);
    uint8_t *current = (uint8_t *)(uintptr_t)readWord(event + 8);
    invokeEndpoint(0x28480, readWord(current + 8), (uintptr_t)message, 0, 0);
}
__declspec(dllexport) void reconstruction::gui::resetState(uint8_t *event, uint8_t *stateImage,
                                                           dependency invokeEndpoint) {
    (void)stateImage;
    (void)invokeEndpoint;
    event[0x10] |= 3;
}
__declspec(dllexport) void reconstruction::gui::onModuleStateChanged(uint8_t *event,
                                                                     uint8_t *stateImage,
                                                                     dependency invokeEndpoint) {
    uint8_t *gameContext = (uint8_t *)(uintptr_t)readWord(event + 8);
    uint32_t color[4];
    recovered_color_74130(color,
                          readDword(stateImage + reconstruction::gui::setting_offset::accent_color),
                          readDword(stateImage + 0x2eb72c), readDword(stateImage + 0x2eb730));
    memcpy(stateImage + 0x2fa190, color, 16);
    stateImage[0x2fa2fc] = stateImage[reconstruction::gui::setting_offset::compact];
    stateImage[0x2fa2fd] = stateImage[reconstruction::gui::setting_offset::wide];
    invokeEndpoint(0x11820, (uintptr_t)(stateImage + 0x2f9e30), readWord(event + 0x10),
                   readWord(gameContext + 8), readWord(gameContext + 0x10));
}
__declspec(dllexport) void reconstruction::gui::clearState(uint8_t *event, uint8_t *stateImage,
                                                           dependency invokeEndpoint) {
    (void)event;
    (void)invokeEndpoint;
    stateImage[0x2fa300] = 1;
}
// END SOURCE modules/GUI/gui.cpp

// BEGIN SOURCE modules/GUI/Queries.cpp
// Native wrappers/queries 0x32450,0x32470,0x32490,0x324b0,0x324d0,0x32590.
// Descriptor 0x2eb740 and UI state 0x2f9e30 establish GUI ownership rather than Teams.
// The protected operation at 0x129b0 remains a dependency; its meaning is not guessed.
#ifndef SLINKY_SHARE_E052C0F182C0905C1C1A
#define SLINKY_SHARE_E052C0F182C0905C1C1A
// BEGIN SOURCE modules/GUI/Queries.hpp
#include <cstdint>
#include "../runtime/shared/RenderNativeBindings.hpp"
namespace reconstruction::gui {
struct QueryDependencies {
    void (*protectedStateOperation)(std::uint8_t *); // 0x129b0, protected provider
    native_binding::RenderEndpoint<4> native;        // concrete shared input/registry bindings
};
void invokeProtectedStateOperation(std::uint8_t *stateImage, const QueryDependencies &);
std::uint8_t queryInteractionFlag(const std::uint8_t *stateImage);
float queryScale(const std::uint8_t *stateImage);
float *copyAccentColor(float *output, const std::uint8_t *stateImage);
std::uint64_t dispatchInput(std::uint8_t *input, std::uint8_t modifier, std::uintptr_t registry,
                            std::uint8_t *stateImage, const QueryDependencies &);
std::uint64_t openFromEvent(const std::uint8_t *event, std::uint8_t *stateImage,
                            const QueryDependencies &);
} // namespace reconstruction::gui
// END SOURCE modules/GUI/Queries.hpp

#endif // SLINKY_SHARE_E052C0F182C0905C1C1A

#include <cstring>
namespace reconstruction::gui {
namespace {
template <class T> T load(const void *p) {
    T v;
    std::memcpy(&v, p, sizeof v);
    return v;
}
template <class T> void store(void *p, T v) {
    std::memcpy(p, &v, sizeof v);
}
constexpr std::size_t descriptor = 0x2eb740;
constexpr std::size_t moduleEnabled = descriptor + 0x14;
constexpr std::size_t moduleBinding = descriptor + 0x1c;
constexpr std::size_t state = 0x2f9e30;
std::uint64_t accepted(std::uint64_t value) {
    return (value & ~std::uint64_t{0xff}) | 1;
}
} // namespace
void invokeProtectedStateOperation(std::uint8_t *image, const QueryDependencies &deps) {
    deps.protectedStateOperation(image + state);
}
std::uint8_t queryInteractionFlag(const std::uint8_t *image) {
    return image[state + 0x4cb]; // Expands the ordinary 0x12ab0 byte getter.
}
float queryScale(const std::uint8_t *image) {
    const auto index = load<std::uint32_t>(image + setting_offset::scale);
    return load<float>(image + 0x1514f0 + std::uint64_t(index) * 4);
}
float *copyAccentColor(float *output, const std::uint8_t *image) {
    // The third component is stored before loading the first pair, preserving alias order.
    store(reinterpret_cast<std::uint8_t *>(output) + 8,
          load<std::uint32_t>(image + setting_offset::accent_color + 8));
    store(output, load<std::uint64_t>(image + setting_offset::accent_color));
    return output;
}
std::uint64_t dispatchInput(std::uint8_t *input, std::uint8_t modifier, std::uintptr_t registry,
                            std::uint8_t *image, const QueryDependencies &deps) {
    if (image[moduleEnabled] == 1) {
        const auto result =
            deps.native(0x10f30, std::uintptr_t(image + state), std::uintptr_t(input), 0, 0);
        if (static_cast<std::uint8_t>(result) != 0)
            return accepted(result);
    }
    const auto kind = load<std::uint32_t>(input);
    if (kind == 2 && input[12] == 1) {
        const auto key = load<std::uint32_t>(input + 4);
        if (key != 0) {
            const auto enabled = image[moduleEnabled];
            std::uint8_t requested;
            if (modifier == 0 && key == load<std::uint32_t>(image + moduleBinding))
                requested = enabled ^ 1;
            else if (key == 0x57 && enabled == 1)
                requested = 0;
            else
                goto fallback;
            return accepted(
                deps.native(0x284f0, registry, std::uintptr_t(image + descriptor), requested, 0));
        }
    }
fallback:
    if (image[moduleEnabled] != 1 || (kind == 2 && image[setting_offset::allow_input] != 0 &&
                                      load<std::uint32_t>(input + 4) > 5))
        return 0;
    // Native MOV AL,1 retains the high bytes of the captured input DWORD.
    return accepted(kind);
}
std::uint64_t openFromEvent(const std::uint8_t *event, std::uint8_t *image,
                            const QueryDependencies &deps) {
    return accepted(deps.native(0x284f0, load<std::uintptr_t>(event + 8),
                                std::uintptr_t(image + descriptor), 1, 0));
}
} // namespace reconstruction::gui
// END SOURCE modules/GUI/Queries.cpp

// Convenient borrowed-state interface

namespace shareable {
class GUI {
  public:
    static constexpr const char *kName = "GUI";
    static constexpr const char *kDescription = "Graphical interface for the cheat.";
    explicit GUI(std::uint8_t *image) : image_(image) {}
    // Scale. Config key: scale.
    ChoiceSetting &scale() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2eb970);
    }
    // Option labels observed in the captured metadata.
    enum class ScaleMode : std::uint32_t {
        Small75 = 0,
        Medium100 = 1,
        Large150 = 2,
        ExtraLarge200 = 3
    };
    // accent_color. Config key: accent_color.
    ColorSetting &accent_color() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2eb720);
    }
    // Allow input while open. Config key: allow_input.
    BooleanSetting &allow_input() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eb9b0);
    }
    // Compact. Config key: compact.
    BooleanSetting &compact() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eb9d0);
    }
    // Wide. Config key: wide.
    BooleanSetting &wide() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eb9f0);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_gui_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_gui_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_gui_settings(&context, image_, &dependencies);
    }
    static void start11800(uint8_t *state, uint64_t time_bits) {
        ::recovered_gui_start_11800(state, time_bits);
    }
    static void reset12A80(uint8_t *state, dependency invokeEndpoint) {
        ::recovered_gui_reset_12a80(state, invokeEndpoint);
    }
    static void clear12A90(uint8_t *state) {
        ::recovered_gui_clear_12a90(state);
    }
    void onRenderFrame(uint8_t *event, dependency invokeEndpoint) {
        ::reconstruction::gui::onRenderFrame(event, image_, invokeEndpoint);
    }
    void onInput(uint8_t *event, dependency invokeEndpoint) {
        ::reconstruction::gui::onInput(event, image_, invokeEndpoint);
    }
    void resetState(uint8_t *event, dependency invokeEndpoint) {
        ::reconstruction::gui::resetState(event, image_, invokeEndpoint);
    }
    void onModuleStateChanged(uint8_t *event, dependency invokeEndpoint) {
        ::reconstruction::gui::onModuleStateChanged(event, image_, invokeEndpoint);
    }
    void clearState(uint8_t *event, dependency invokeEndpoint) {
        ::reconstruction::gui::clearState(event, image_, invokeEndpoint);
    }
    void invokeProtectedStateOperation(const ::reconstruction::gui::QueryDependencies &deps) {
        ::reconstruction::gui::invokeProtectedStateOperation(image_, deps);
    }
    static std::uint8_t queryInteractionFlag(const std::uint8_t *image) {
        return ::reconstruction::gui::queryInteractionFlag(image);
    }
    static float queryScale(const std::uint8_t *image) {
        return ::reconstruction::gui::queryScale(image);
    }
    std::uint64_t dispatchInput(std::uint8_t *input, std::uint8_t modifier, std::uintptr_t registry,
                                const ::reconstruction::gui::QueryDependencies &deps) {
        return ::reconstruction::gui::dispatchInput(input, modifier, registry, image_, deps);
    }
    std::uint64_t openFromEvent(const std::uint8_t *event,
                                const ::reconstruction::gui::QueryDependencies &deps) {
        return ::reconstruction::gui::openFromEvent(event, image_, deps);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
