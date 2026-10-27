// Chams

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Chams.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Chams.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Chams: lib_win settings 0x3e8c0.
// UI 0x3e880.
static constexpr UiStep ui_steps_Surface_Chams[] = {
    {UiControl::section, "Main", 0},
    {UiControl::checkbox, nullptr, 0x2f11f0},
};
static constexpr SettingsStep settings_steps_Surface_Chams[] = {
    {SettingsControl::boolean, "hide_friendlies", 0x2f11f0},
};
static constexpr ModuleSurface surface_Surface_Chams{
    ui_steps_Surface_Chams, std::size(ui_steps_Surface_Chams), settings_steps_Surface_Chams,
    std::size(settings_steps_Surface_Chams)};

extern "C" __declspec(dllexport) void
recovered_chams_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                   const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Chams, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_chams_settings(SettingsContext *context, std::uint8_t *image,
                         const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Chams, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Chams.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Chams/Chams.cpp
#ifndef SLINKY_SHARE_7249FAEAF512705ABEB4
#define SLINKY_SHARE_7249FAEAF512705ABEB4
// BEGIN SOURCE native/verified/Chams.hpp
#include "../runtime/native/verified/module_game_access.hpp"
#include "../runtime/native/verified/module_ui_controls.hpp"

struct ChamsRenderRequest {
    GameAccessBridge *bridge;
    std::uintptr_t receiver, entity;
    double first, second, third;
    float fourth, fifth;
};
using ChamsCapabilityEndpoint = std::uint64_t (*)(std::uint32_t);
using ChamsOffsetEndpoint = std::uint64_t (*)(float, float);
struct ChamsGraphics {
    ChamsCapabilityEndpoint *begin;
    ChamsOffsetEndpoint *set_offset;
    ChamsCapabilityEndpoint *end;
};
struct ChamsOffsetConstants {
    float first, second;
};
static_assert(sizeof(ChamsRenderRequest) == 56);
static_assert(offsetof(ChamsRenderRequest, first) == 24);
static_assert(offsetof(ChamsRenderRequest, fourth) == 48);
static_assert(sizeof(ChamsGraphics) == 24);
static_assert(sizeof(ChamsOffsetConstants) == 8);

extern "C" {
__declspec(dllexport) std::uint32_t recovered_chams_flags(GameAccessBridge *, std::uintptr_t entity,
                                                          std::uint32_t mask);
__declspec(dllexport) std::uint64_t recovered_chams_forward(const ChamsRenderRequest *);
__declspec(dllexport) std::uint64_t recovered_chams_wrapper(const ChamsRenderRequest *,
                                                            std::uint8_t enabled,
                                                            const BooleanSetting *hide_friendlies,
                                                            const ChamsGraphics *,
                                                            const ChamsOffsetConstants *);
__declspec(dllexport) std::uint64_t
recovered_chams_hook(const std::uint8_t *const *metadata, std::uintptr_t *environment,
                     const ChamsRenderRequest *, std::uint8_t enabled,
                     const BooleanSetting *hide_friendlies, const ChamsGraphics *,
                     const ChamsOffsetConstants *);
__declspec(dllexport) std::uint64_t recovered_chams_typed_ui(std::uint64_t ui, std::uint64_t layout,
                                                             BooleanSetting *hide_friendlies,
                                                             UiDirtyState *,
                                                             const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_chams_typed_settings(SettingsContext *,
                                                          BooleanSetting *hide_friendlies,
                                                          const SettingsDependencies *);
}
// END SOURCE native/verified/Chams.hpp

#endif // SLINKY_SHARE_7249FAEAF512705ABEB4

#include <bit>
#include <cstring>
#include <emmintrin.h>

using Word = std::uintptr_t;
static Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word value;
    std::memcpy(&value, bridge->metadata + offset, sizeof(value));
    return value;
}
template <class Function> static Function slot(const GameAccessBridge *bridge, std::size_t offset) {
    const auto *table = reinterpret_cast<const Word *>(*bridge->environment);
    return reinterpret_cast<Function>(table[offset / sizeof(Word)]);
}
// 0x2ace0 calls float getter 0x240d0 and retains the high word of its raw bits.
extern "C" __declspec(dllexport) std::uint32_t
recovered_chams_flags(GameAccessBridge *bridge, Word entity, std::uint32_t mask) {
    using Getter = float (*)(Word *, Word, Word);
    const auto bits = std::bit_cast<std::uint32_t>(
        slot<Getter>(bridge, 0x330)(bridge->environment, entity, identifier(bridge, 0x5c0)));
    const auto high = bits & 0xffff0000u;
    const auto flags = high == 0xb3150000u ? bits & 0xffffu : 0u;
    return high | ((flags & mask) != 0);
}
// 0x274f0 forwards three doubles and promotes both float stack arguments.
extern "C" __declspec(dllexport) std::uint64_t
recovered_chams_forward(const ChamsRenderRequest *request) {
    const auto copy = *request;
    auto *bridge = copy.bridge;
    using Render =
        std::uint64_t (*)(Word *, Word, Word, Word, Word, double, double, double, double, double);
    const auto fourth = _mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(copy.fourth)));
    const auto fifth = _mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(copy.fifth)));
    return slot<Render>(bridge, 0x2d8)(
        bridge->environment, copy.receiver, identifier(bridge, 0x948), identifier(bridge, 0x990),
        copy.entity, copy.first, copy.second, copy.third, fourth, fifth);
}
// 0x3e730 snapshots arguments, but reloads graphics cells after dependency calls.
extern "C" __declspec(dllexport) std::uint64_t
recovered_chams_wrapper(const ChamsRenderRequest *request, std::uint8_t enabled,
                        const BooleanSetting *hide_friendlies, const ChamsGraphics *graphics,
                        const ChamsOffsetConstants *constants) {
    const auto copy = *request;
    if (enabled == 1 &&
        !(recovered_chams_flags(copy.bridge, copy.entity,
                                static_cast<std::uint32_t>(hide_friendlies->current) * 5u + 2u) &
          0xff)) {
        (*graphics->begin)(0x8037);
        (*graphics->set_offset)(constants->first, constants->second);
        recovered_chams_forward(&copy);
        return (*graphics->end)(0x8037);
    }
    return recovered_chams_forward(&copy);
}
// 0x8350 captures metadata and incoming JNI environment in a local two-word bridge.
extern "C" __declspec(dllexport) std::uint64_t
recovered_chams_hook(const std::uint8_t *const *metadata, Word *environment,
                     const ChamsRenderRequest *request, std::uint8_t enabled,
                     const BooleanSetting *hide_friendlies, const ChamsGraphics *graphics,
                     const ChamsOffsetConstants *constants) {
    GameAccessBridge bridge{*metadata, environment};
    auto copy = *request;
    copy.bridge = &bridge;
    return recovered_chams_wrapper(&copy, enabled, hide_friendlies, graphics, constants);
}
// 0x3e880 / 0x3e8c0 share the checkbox and Boolean persistence helpers.
extern "C" __declspec(dllexport) std::uint64_t
recovered_chams_typed_ui(std::uint64_t ui, std::uint64_t layout, BooleanSetting *hide_friendlies,
                         UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Main");
    return recovered_checkbox_control(layout, ui, hide_friendlies, dirty, &endpoints->controls);
}
extern "C" __declspec(dllexport) void
recovered_chams_typed_settings(SettingsContext *context, BooleanSetting *hide_friendlies,
                               const SettingsDependencies *dependencies) {
    recovered_boolean_settings(context, "hide_friendlies", hide_friendlies, dependencies);
}
// END SOURCE modules/Chams/Chams.cpp

#ifndef SLINKY_SHARE_26D559A9A533DC10B2F1
#define SLINKY_SHARE_26D559A9A533DC10B2F1
// BEGIN SOURCE modules/Chams/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Chams/Api.hpp

#endif // SLINKY_SHARE_26D559A9A533DC10B2F1

// Convenient borrowed-state interface

namespace shareable {
class Chams {
  public:
    static constexpr const char *kName = "Chams";
    static constexpr const char *kDescription = "Renders players behind blocks.";
    explicit Chams(std::uint8_t *image) : image_(image) {}
    // Hide friendlies. Config key: hide_friendlies.
    BooleanSetting &hide_friendlies() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f11f0);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_chams_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_chams_settings(&context, image_, &dependencies);
    }
    static std::uint32_t flags(GameAccessBridge *bridge, Word entity, std::uint32_t mask) {
        return ::recovered_chams_flags(bridge, entity, mask);
    }
    static std::uint64_t forward(const ChamsRenderRequest *request) {
        return ::recovered_chams_forward(request);
    }
    static std::uint64_t wrapper(const ChamsRenderRequest *request, std::uint8_t enabled,
                                 const BooleanSetting *hide_friendlies,
                                 const ChamsGraphics *graphics,
                                 const ChamsOffsetConstants *constants) {
        return ::recovered_chams_wrapper(request, enabled, hide_friendlies, graphics, constants);
    }
    static std::uint64_t hook(const std::uint8_t *const *metadata, Word *environment,
                              const ChamsRenderRequest *request, std::uint8_t enabled,
                              const BooleanSetting *hide_friendlies, const ChamsGraphics *graphics,
                              const ChamsOffsetConstants *constants) {
        return ::recovered_chams_hook(metadata, environment, request, enabled, hide_friendlies,
                                      graphics, constants);
    }
    static std::uint64_t typedUi(std::uint64_t ui, std::uint64_t layout,
                                 BooleanSetting *hide_friendlies, UiDirtyState *dirty,
                                 const SettingsUiEndpoints *endpoints) {
        return ::recovered_chams_typed_ui(ui, layout, hide_friendlies, dirty, endpoints);
    }
    static void typedSettings(SettingsContext *context, BooleanSetting *hide_friendlies,
                              const SettingsDependencies *dependencies) {
        ::recovered_chams_typed_settings(context, hide_friendlies, dependencies);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
