// Anti Debuff

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Anti_Debuff.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Anti_Debuff.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Anti Debuff: lib_win settings 0x44a10.
// UI 0x449c0.
static constexpr UiStep ui_steps_Surface_Anti_Debuff[] = {
    {UiControl::section, "Effects", 0},
    {UiControl::checkbox, nullptr, 0x2f3a70},
    {UiControl::checkbox, nullptr, 0x2f3a90},
};
static constexpr SettingsStep settings_steps_Surface_Anti_Debuff[] = {
    {SettingsControl::boolean, "blindness", 0x2f3a70},
    {SettingsControl::boolean, "nausea", 0x2f3a90},
};
static constexpr ModuleSurface surface_Surface_Anti_Debuff{
    ui_steps_Surface_Anti_Debuff, std::size(ui_steps_Surface_Anti_Debuff),
    settings_steps_Surface_Anti_Debuff, std::size(settings_steps_Surface_Anti_Debuff)};

extern "C" __declspec(dllexport) void
recovered_anti_debuff_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                         const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Anti_Debuff, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_anti_debuff_settings(SettingsContext *context, std::uint8_t *image,
                               const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Anti_Debuff, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Anti_Debuff.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Anti_Debuff/Anti_Debuff.cpp
#include "../runtime/native/verified/access_events.hpp"

// lib_win RVA 0x44940: event 18 callback.
extern "C" __declspec(dllexport) void
recovered_anti_debuff_44940(void *event, AccessGlobals *globals, const AccessDependencies *deps) {
    auto *payload = reinterpret_cast<std::uint64_t *>(access_word(event, 8));
    if (globals->enabled_44940 == 1) {
        const auto value = access_call(deps, 0x27960, payload[0], 0xf);
        const auto found = access_call(deps, 0x23c10, payload[0], payload[5], value);
        if (found != 0)
            access_call(deps, 0x279c0, payload[0], found);
    }
    if (globals->enabled_44940_second == 1) {
        deps->invoke_23e60(payload[0], payload[5], 0.0f);
        deps->invoke_23e90(payload[0], payload[5], 0.0f);
    }
}
// END SOURCE modules/Anti_Debuff/Anti_Debuff.cpp

// BEGIN SOURCE modules/Anti_Debuff/Anti_Debuff_typed.cpp
#ifndef SLINKY_SHARE_23FB334FC7B9138FC0D3
#define SLINKY_SHARE_23FB334FC7B9138FC0D3
// BEGIN SOURCE native/verified/Anti_Debuff_typed.hpp
#include "../runtime/native/verified/Timer.hpp"
#include "../runtime/native/verified/module_ui_controls.hpp"

struct AntiDebuffSettings {
    BooleanSetting blindness;
    BooleanSetting nausea;
};
struct AntiDebuffEvent {
    std::uintptr_t type;
    TimerGame *game;
};
struct AntiDebuffDependencies {
    std::uintptr_t (*effect_by_id)(GameAccessBridge *, std::uint32_t id);
    std::uintptr_t (*player_effect)(GameAccessBridge *, std::uintptr_t player,
                                    std::uintptr_t effect);
    void (*set_effect_value)(GameAccessBridge *, std::uintptr_t effect, std::uint32_t value);
    void (*set_nausea_strength)(GameAccessBridge *, std::uintptr_t player, float value);
    void (*set_previous_nausea_strength)(GameAccessBridge *, std::uintptr_t player, float value);
};
static_assert(sizeof(AntiDebuffSettings) == 64);
static_assert(offsetof(AntiDebuffSettings, nausea) == 32);
static_assert(sizeof(AntiDebuffEvent) == 16);
static_assert(sizeof(AntiDebuffDependencies) == 40);
extern "C" {
__declspec(dllexport) void recovered_bind_anti_debuff_access(AntiDebuffDependencies *);
__declspec(dllexport) void recovered_anti_debuff_initialize_settings(AntiDebuffSettings *);
__declspec(dllexport) void recovered_anti_debuff_typed_update(AntiDebuffEvent *,
                                                              const AntiDebuffSettings *,
                                                              const AntiDebuffDependencies *);
__declspec(dllexport) std::uint64_t
recovered_anti_debuff_typed_ui(std::uint64_t ui, std::uint64_t layout, AntiDebuffSettings *,
                               UiDirtyState *, const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_anti_debuff_typed_settings(SettingsContext *,
                                                                AntiDebuffSettings *,
                                                                const SettingsDependencies *);
}
class AntiDebuffModule {
  public:
    static constexpr const char *name = "Anti Debuff";
    static constexpr const char *description = "Removes negative visual effects.";
    static constexpr std::uint32_t event_type = 18;
    static constexpr std::int32_t event_priority = 0;
    AntiDebuffSettings settings{};
    AntiDebuffDependencies access{};
    // Captured baseline, not a recovered original startup constructor.
    AntiDebuffModule() {
        recovered_anti_debuff_initialize_settings(&settings);
        recovered_bind_anti_debuff_access(&access);
    }
    void update(AntiDebuffEvent &event) {
        recovered_anti_debuff_typed_update(&event, &settings, &access);
    }
    std::uint64_t render(std::uint64_t ui, std::uint64_t layout, UiDirtyState &dirty,
                         const SettingsUiEndpoints &endpoints) {
        return recovered_anti_debuff_typed_ui(ui, layout, &settings, &dirty, &endpoints);
    }
    void configure(SettingsContext &context, const SettingsDependencies &endpoints) {
        recovered_anti_debuff_typed_settings(&context, &settings, &endpoints);
    }
};
// END SOURCE native/verified/Anti_Debuff_typed.hpp

#endif // SLINKY_SHARE_23FB334FC7B9138FC0D3

#include "../runtime/native/verified/module_access_helpers.hpp"
#include <cstring>

namespace {
std::uintptr_t effect_by_id(GameAccessBridge *bridge, std::uint32_t id) {
    return recovered_access_helper(bridge, 0x27960, id, 0, 0);
}
std::uintptr_t player_effect(GameAccessBridge *bridge, std::uintptr_t player,
                             std::uintptr_t effect) {
    return recovered_access_helper(bridge, 0x23c10, player, effect, 0);
}
void set_effect_value(GameAccessBridge *bridge, std::uintptr_t effect, std::uint32_t value) {
    recovered_access_helper(bridge, 0x279c0, effect, value, 0);
}
template <std::uint32_t Helper>
void set_nausea_value(GameAccessBridge *bridge, std::uintptr_t player, float value) {
    std::uint32_t bits;
    std::memcpy(&bits, &value, sizeof(bits));
    recovered_access_helper(bridge, Helper, player, bits, 0);
}
} // namespace

extern "C" __declspec(dllexport) void
recovered_bind_anti_debuff_access(AntiDebuffDependencies *access) {
    *access = {effect_by_id, player_effect, set_effect_value, set_nausea_value<0x23e60>,
               set_nausea_value<0x23e90>};
}

// 0x44940 captures the game, refreshing bridge/player and the second setting between calls.
extern "C" __declspec(dllexport) void
recovered_anti_debuff_typed_update(AntiDebuffEvent *event, const AntiDebuffSettings *settings,
                                   const AntiDebuffDependencies *access) {
    auto *game = event->game;
    if (settings->blindness.current == 1) {
        const auto blindness = access->effect_by_id(game->bridge, 15);
        const auto effect = access->player_effect(game->bridge, game->player, blindness);
        if (effect)
            access->set_effect_value(game->bridge, effect, 0);
    }
    if (settings->nausea.current == 1) {
        access->set_nausea_strength(game->bridge, game->player, 0.0f);
        access->set_previous_nausea_strength(game->bridge, game->player, 0.0f);
    }
}

extern "C" __declspec(dllexport) std::uint64_t
recovered_anti_debuff_typed_ui(std::uint64_t ui, std::uint64_t layout, AntiDebuffSettings *settings,
                               UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Effects");
    recovered_checkbox_control(layout, ui, &settings->blindness, dirty, &endpoints->controls);
    return recovered_checkbox_control(layout, ui, &settings->nausea, dirty, &endpoints->controls);
}

extern "C" __declspec(dllexport) void
recovered_anti_debuff_typed_settings(SettingsContext *context, AntiDebuffSettings *settings,
                                     const SettingsDependencies *endpoints) {
    recovered_boolean_settings(context, "blindness", &settings->blindness, endpoints);
    recovered_boolean_settings(context, "nausea", &settings->nausea, endpoints);
}

extern "C" __declspec(dllexport) void
recovered_anti_debuff_initialize_settings(AntiDebuffSettings *settings) {
    *settings = {};
    const char *blindness = "Blindness", *nausea = "Nausea";
    std::memcpy(settings->blindness.metadata + 16, &blindness, sizeof(blindness));
    std::memcpy(settings->nausea.metadata + 16, &nausea, sizeof(nausea));
    settings->blindness.current = 1;
    settings->nausea.current = 1;
}
// END SOURCE modules/Anti_Debuff/Anti_Debuff_typed.cpp

#ifndef SLINKY_SHARE_44714F7185B559F08057
#define SLINKY_SHARE_44714F7185B559F08057
// BEGIN SOURCE modules/Anti_Debuff/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Anti_Debuff/Api.hpp

#endif // SLINKY_SHARE_44714F7185B559F08057

// Convenient borrowed-state interface

namespace shareable {
using AntiDebuff = ::AntiDebuffModule;
}
