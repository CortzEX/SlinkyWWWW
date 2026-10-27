#include "Anti_Debuff_typed.hpp"
#include "module_access_helpers.hpp"
#include <cstring>

namespace {
std::uintptr_t effect_by_id(GameAccessBridge *bridge, std::uint32_t id) {
    return recovered_access_helper(bridge, 0x27960, id, 0, 0);
}
std::uintptr_t player_effect(GameAccessBridge *bridge, std::uintptr_t player, std::uintptr_t effect) {
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
}

extern "C" __declspec(dllexport) void recovered_bind_anti_debuff_access(AntiDebuffDependencies *access) {
    *access = {effect_by_id, player_effect, set_effect_value, set_nausea_value<0x23e60>, set_nausea_value<0x23e90>};
}

// 0x44940 captures the game, refreshing bridge/player and the second setting between calls.
extern "C" __declspec(dllexport) void recovered_anti_debuff_typed_update(AntiDebuffEvent *event,
    const AntiDebuffSettings *settings, const AntiDebuffDependencies *access) {
    auto *game = event->game;
    if (settings->blindness.current == 1) {
        const auto blindness = access->effect_by_id(game->bridge, 15);
        const auto effect = access->player_effect(game->bridge, game->player, blindness);
        if (effect) access->set_effect_value(game->bridge, effect, 0);
    }
    if (settings->nausea.current == 1) {
        access->set_nausea_strength(game->bridge, game->player, 0.0f);
        access->set_previous_nausea_strength(game->bridge, game->player, 0.0f);
    }
}

extern "C" __declspec(dllexport) std::uint64_t recovered_anti_debuff_typed_ui(std::uint64_t ui,
    std::uint64_t layout, AntiDebuffSettings *settings, UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Effects");
    recovered_checkbox_control(layout, ui, &settings->blindness, dirty, &endpoints->controls);
    return recovered_checkbox_control(layout, ui, &settings->nausea, dirty, &endpoints->controls);
}

extern "C" __declspec(dllexport) void recovered_anti_debuff_typed_settings(SettingsContext *context,
    AntiDebuffSettings *settings, const SettingsDependencies *endpoints) {
    recovered_boolean_settings(context, "blindness", &settings->blindness, endpoints);
    recovered_boolean_settings(context, "nausea", &settings->nausea, endpoints);
}

extern "C" __declspec(dllexport) void recovered_anti_debuff_initialize_settings(AntiDebuffSettings *settings) {
    *settings = {};
    const char *blindness = "Blindness", *nausea = "Nausea";
    std::memcpy(settings->blindness.metadata + 16, &blindness, sizeof(blindness));
    std::memcpy(settings->nausea.metadata + 16, &nausea, sizeof(nausea));
    settings->blindness.current = 1;
    settings->nausea.current = 1;
}
