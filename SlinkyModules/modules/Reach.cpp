// Reach

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Reach.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Reach.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Reach: lib_win settings 0x300e0.
// UI 0x30060.
static constexpr UiStep ui_steps_Surface_Reach[] = {
    {UiControl::section, "Main", 0},       {UiControl::number, nullptr, 0x2ea760},
    {UiControl::section, "Advanced", 0},   {UiControl::number, nullptr, 0x2ea798},
    {UiControl::section, "Conditions", 0}, {UiControl::checkbox, nullptr, 0x2ea7d0},
};
static constexpr SettingsStep settings_steps_Surface_Reach[] = {
    {SettingsControl::number, "distance", 0x2ea760},
    {SettingsControl::number, "activate_time", 0x2ea798},
    {SettingsControl::boolean, "require_sprint", 0x2ea7d0},
};
static constexpr ModuleSurface surface_Surface_Reach{
    ui_steps_Surface_Reach, std::size(ui_steps_Surface_Reach), settings_steps_Surface_Reach,
    std::size(settings_steps_Surface_Reach)};

extern "C" __declspec(dllexport) void
recovered_reach_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                   const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Reach, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_reach_settings(SettingsContext *context, std::uint8_t *image,
                         const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Reach, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Reach.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Reach/Reach.cpp
#include "../runtime/native/verified/event_callbacks.hpp"
#include <cmath>
#include <cstring>

// lib_win RVA 0x2ffb0: event 8 callback. State mirrors the module's persistent fields.
extern "C" __declspec(dllexport) void recovered_reach(std::uint8_t *event, ReachState *state,
                                                      const Dependencies *deps) {
    std::uintptr_t frame;
    std::memcpy(&frame, event + 8, sizeof(frame));
    auto *fields = reinterpret_cast<const std::uint8_t *>(frame);
    std::uintptr_t game, target;
    std::memcpy(&game, fields, sizeof(game));
    std::memcpy(&target, fields + 0x28, sizeof(target));

    if (state->timer > 0)
        --state->timer;
    if (state->require_sprint == 1 && !deps->dep_180023690(game, target))
        return;

    std::memcpy(&game, fields, sizeof(game));
    std::memcpy(&target, fields + 0x28, sizeof(target));
    if (state->timer == 0) {
        const auto identifier = deps->dep_1800239d0(game, target);
        if (identifier != state->previous_target) {
            state->timer = 9;
            state->previous_target = identifier;
        }
    }

    const float count = static_cast<float>(state->timer);
    const float threshold = state->activation_threshold;
    if (std::isnan(threshold) || threshold <= count)
        return;

    event[0x10] = 1;
    const double value = static_cast<double>(state->reach_value);
    std::memcpy(event + 0x18, &value, sizeof(value));
}
// END SOURCE modules/Reach/Reach.cpp

// BEGIN SOURCE modules/Reach/Reach_typed.cpp
#ifndef SLINKY_SHARE_AE9A28D04532673A8633
#define SLINKY_SHARE_AE9A28D04532673A8633
// BEGIN SOURCE native/verified/Reach_typed.hpp
#include "../runtime/native/verified/Timer.hpp"
#include "../runtime/native/verified/module_ui_controls.hpp"
#include "../runtime/native/verified/module_format.hpp"

struct ReachSettings {
    NumberSetting distance;
    NumberSetting activation_ticks;
    BooleanSetting require_sprint;
};
struct ReachRuntimeState {
    volatile std::int32_t previous_attacker_time;
    volatile std::int32_t countdown;
};
struct ReachEvent {
    std::uintptr_t type;
    TimerGame *game;
    std::uint8_t enabled;
    std::uint8_t padding[7];
    double distance;
};
struct ReachDependencies {
    std::uint8_t (*sprinting)(GameAccessBridge *, std::uintptr_t player);
    std::int32_t (*last_attacker_time)(GameAccessBridge *, std::uintptr_t player);
};
static_assert(sizeof(ReachSettings) == 144);
static_assert(offsetof(ReachSettings, activation_ticks) == 56);
static_assert(offsetof(ReachSettings, require_sprint) == 112);
static_assert(sizeof(ReachRuntimeState) == 8);
static_assert(sizeof(ReachEvent) == 32);
static_assert(offsetof(ReachEvent, distance) == 24);
static_assert(sizeof(ReachDependencies) == 16);

extern "C" {
__declspec(dllexport) void recovered_bind_reach_access(ReachDependencies *);
__declspec(dllexport) void recovered_reach_initialize_settings(ReachSettings *);
__declspec(dllexport) void recovered_reach_typed_update(ReachEvent *, const ReachSettings *,
                                                        ReachRuntimeState *,
                                                        const ReachDependencies *);
__declspec(dllexport) std::uint64_t recovered_reach_typed_ui(std::uint64_t ui, std::uint64_t layout,
                                                             ReachSettings *, UiDirtyState *,
                                                             const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_reach_typed_settings(SettingsContext *, ReachSettings *,
                                                          const ValueSettingsDependencies *,
                                                          const SettingsDependencies *);
__declspec(dllexport) std::uint64_t recovered_reach_typed_label(char *, const ReachSettings *,
                                                                FormatState *);
}

class ReachModule {
  public:
    static constexpr const char *name = "Reach";
    static constexpr const char *description = "Increases your melee range.";
    static constexpr std::uint32_t event_type = 8;
    static constexpr std::int32_t event_priority = 0;
    ReachSettings settings{};
    ReachRuntimeState state{};
    ReachDependencies access{};
    // Restore the captured baseline; the original startup constructor is unresolved.
    ReachModule() {
        recovered_reach_initialize_settings(&settings);
        recovered_bind_reach_access(&access);
    }
    void update(ReachEvent &event) {
        recovered_reach_typed_update(&event, &settings, &state, &access);
    }
    std::uint64_t render(std::uint64_t ui, std::uint64_t layout, UiDirtyState &dirty,
                         const SettingsUiEndpoints &endpoints) {
        return recovered_reach_typed_ui(ui, layout, &settings, &dirty, &endpoints);
    }
    void configure(SettingsContext &context, const ValueSettingsDependencies &values,
                   const SettingsDependencies &booleans) {
        recovered_reach_typed_settings(&context, &settings, &values, &booleans);
    }
    std::uint64_t label(char *destination, FormatState &format) const {
        return recovered_reach_typed_label(destination, &settings, &format);
    }
};
// END SOURCE native/verified/Reach_typed.hpp

#endif // SLINKY_SHARE_AE9A28D04532673A8633

#include <cstring>

extern "C" __declspec(dllexport) void recovered_bind_reach_access(ReachDependencies *access) {
    *access = {recovered_game_sprinting, recovered_game_last_attacker_time};
}

// 0x2ffb0 retains the local countdown, refreshing it only at the original query boundaries.
extern "C" __declspec(dllexport) void
recovered_reach_typed_update(ReachEvent *event, const ReachSettings *settings,
                             ReachRuntimeState *state, const ReachDependencies *access) {
    auto count = state->countdown;
    if (count > 0)
        state->countdown = --count;
    auto *game = event->game;
    if (settings->require_sprint.current == 1) {
        if (!access->sprinting(game->bridge, game->player))
            return;
        count = state->countdown;
    }
    if (count == 0) {
        const auto attacker_time = access->last_attacker_time(game->bridge, game->player);
        if (attacker_time == state->previous_attacker_time) {
            count = state->countdown;
        } else {
            state->previous_attacker_time = attacker_time;
            state->countdown = 9;
            count = 9;
        }
    }
    if (!(settings->activation_ticks.current > static_cast<float>(count)))
        return;
    event->enabled = 1;
    event->distance = static_cast<double>(settings->distance.current);
}

// 0x30060 includes the final checkbox wrapper's full return and dirty-state update.
extern "C" __declspec(dllexport) std::uint64_t
recovered_reach_typed_ui(std::uint64_t ui, std::uint64_t layout, ReachSettings *settings,
                         UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Main");
    recovered_number_control(layout, ui, &settings->distance, dirty, &endpoints->controls);
    endpoints->section(ui, layout, "Advanced");
    recovered_number_control(layout, ui, &settings->activation_ticks, dirty, &endpoints->controls);
    endpoints->section(ui, layout, "Conditions");
    return recovered_checkbox_control(layout, ui, &settings->require_sprint, dirty,
                                      &endpoints->controls);
}

extern "C" __declspec(dllexport) void
recovered_reach_typed_settings(SettingsContext *context, ReachSettings *settings,
                               const ValueSettingsDependencies *values,
                               const SettingsDependencies *booleans) {
    recovered_number_settings(context, "distance", &settings->distance, values);
    recovered_number_settings(context, "activate_time", &settings->activation_ticks, values);
    recovered_boolean_settings(context, "require_sprint", &settings->require_sprint, booleans);
}

// 0x30140 leaves the caller's destination intact and promotes the current binary32 distance.
extern "C" __declspec(dllexport) std::uint64_t
recovered_reach_typed_label(char *destination, const ReachSettings *settings, FormatState *format) {
    return recovered_format(format, destination, 32, "%.2f",
                            static_cast<double>(settings->distance.current));
}

extern "C" __declspec(dllexport) void recovered_reach_initialize_settings(ReachSettings *settings) {
    *settings = {};
    auto initialize = [](NumberSetting &setting, const char *label, const char *format, float step,
                         float minimum, float maximum, float current) {
        std::memcpy(setting.metadata + 16, &label, sizeof(label));
        std::memcpy(setting.metadata + 24, &format, sizeof(format));
        std::memcpy(setting.metadata + 32, &step, sizeof(step));
        setting.minimum = minimum;
        setting.maximum = maximum;
        setting.current = current;
    };
    initialize(settings->distance, "Distance", "%0.2f blocks", 0.01f, 3.0f, 6.0f, 3.05f);
    initialize(settings->activation_ticks, "Activate for", "%.0f tick(s)", 1.0f, 1.0f, 10.0f, 3.0f);
    const char *label = "Sprinting";
    std::memcpy(settings->require_sprint.metadata + 16, &label, sizeof(label));
}
// END SOURCE modules/Reach/Reach_typed.cpp

#ifndef SLINKY_SHARE_AF63A816DB88B2CA46BB
#define SLINKY_SHARE_AF63A816DB88B2CA46BB
// BEGIN SOURCE modules/Reach/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Reach/Api.hpp

#endif // SLINKY_SHARE_AF63A816DB88B2CA46BB

// Convenient borrowed-state interface

namespace shareable {
using Reach = ::ReachModule;
}
