#include "Reach_typed.hpp"
#include <cstring>

extern "C" __declspec(dllexport) void recovered_bind_reach_access(ReachDependencies *access) {
    *access = {recovered_game_sprinting, recovered_game_last_attacker_time};
}

// 0x2ffb0 retains the local countdown, refreshing it only at the original query boundaries.
extern "C" __declspec(dllexport) void recovered_reach_typed_update(ReachEvent *event,
    const ReachSettings *settings, ReachRuntimeState *state, const ReachDependencies *access) {
    auto count = state->countdown;
    if (count > 0) state->countdown = --count;
    auto *game = event->game;
    if (settings->require_sprint.current == 1) {
        if (!access->sprinting(game->bridge, game->player)) return;
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
    if (!(settings->activation_ticks.current > static_cast<float>(count))) return;
    event->enabled = 1;
    event->distance = static_cast<double>(settings->distance.current);
}

// 0x30060 includes the final checkbox wrapper's full return and dirty-state update.
extern "C" __declspec(dllexport) std::uint64_t recovered_reach_typed_ui(std::uint64_t ui,
    std::uint64_t layout, ReachSettings *settings, UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Main");
    recovered_number_control(layout, ui, &settings->distance, dirty, &endpoints->controls);
    endpoints->section(ui, layout, "Advanced");
    recovered_number_control(layout, ui, &settings->activation_ticks, dirty, &endpoints->controls);
    endpoints->section(ui, layout, "Conditions");
    return recovered_checkbox_control(layout, ui, &settings->require_sprint, dirty, &endpoints->controls);
}

extern "C" __declspec(dllexport) void recovered_reach_typed_settings(SettingsContext *context,
    ReachSettings *settings, const ValueSettingsDependencies *values, const SettingsDependencies *booleans) {
    recovered_number_settings(context, "distance", &settings->distance, values);
    recovered_number_settings(context, "activate_time", &settings->activation_ticks, values);
    recovered_boolean_settings(context, "require_sprint", &settings->require_sprint, booleans);
}

// 0x30140 leaves the caller's destination intact and promotes the current binary32 distance.
extern "C" __declspec(dllexport) std::uint64_t recovered_reach_typed_label(char *destination,
    const ReachSettings *settings, FormatState *format) {
    return recovered_format(format, destination, 32, "%.2f", static_cast<double>(settings->distance.current));
}

extern "C" __declspec(dllexport) void recovered_reach_initialize_settings(ReachSettings *settings) {
    *settings = {};
    auto initialize = [](NumberSetting &setting, const char *label, const char *format,
                         float step, float minimum, float maximum, float current) {
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
