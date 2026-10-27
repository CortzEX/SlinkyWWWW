#include "No_Use_Delay_typed.hpp"
#include "module_access_helpers.hpp"
#include "Sprint_Reset_runtime.hpp"
#include <cstring>

namespace {
std::uintptr_t options(GameAccessBridge *bridge, std::uintptr_t client) {
    return recovered_access_helper(bridge, 0x22cf0, client, 0, 0);
}
std::uintptr_t use_key(GameAccessBridge *bridge, std::uintptr_t options) {
    return recovered_access_helper(bridge, 0x24f90, options, 0, 0);
}
std::uint8_t use_pressed(GameAccessBridge *bridge, std::uintptr_t key) {
    return static_cast<std::uint8_t>(recovered_access_helper(bridge, 0x25430, key, 0, 0));
}
void set_key(GameAccessBridge *bridge, std::uintptr_t key, std::uint32_t value) {
    recovered_access_helper(bridge, 0x25460, key, value, 0);
}
std::int32_t item_use_count(GameAccessBridge *bridge, std::uintptr_t player) {
    return static_cast<std::int32_t>(recovered_access_helper(bridge, 0x23fc0, player, 0, 0));
}
}

extern "C" __declspec(dllexport) void recovered_bind_no_use_delay_access(NoUseDelayDependencies *access) {
    *access = {options, use_key, use_pressed, recovered_game_inventory, recovered_game_inventory_index,
               recovered_sprint_reset_physical_word, set_key, item_use_count};
}

// 0x3e8e0 retains the selected key, its active byte and the bridge across physical-query/setter calls.
extern "C" __declspec(dllexport) void recovered_no_use_delay_typed_update(NoUseDelayEvent *event,
    const NoUseDelaySettings *settings, NoUseDelayState *state, const NoUseDelayDependencies *access) {
    auto *game = event->game;
    if (!game->ready) {
        state->countdown = 0;
        return;
    }
    const auto options = access->options(game->bridge, game->client);
    const auto key = access->use_key(game->bridge, options);
    const auto active = access->use_pressed(game->bridge, key);
    const auto inventory = access->inventory(game->bridge, game->player);
    const auto selected_slot = access->selected_slot(game->bridge, inventory);
    if (selected_slot != state->last_slot) {
        state->countdown = 0;
        state->last_slot = selected_slot;
        auto *bridge = game->bridge;
        const auto physical = access->physical_key(bridge, key);
        access->set_key(bridge, key, physical);
    }
    if (!active) return;
    const auto use_count = access->item_use_count(game->bridge, game->player);
    auto count = state->countdown;
    if (count > 0) {
        state->countdown = --count;
        if (count == 0 || (static_cast<std::uint8_t>(use_count == 0) & settings->allow_desync.current) == 1)
            access->set_key(game->bridge, key, 0);
    } else {
        state->countdown = use_count;
    }
}

extern "C" __declspec(dllexport) std::uint64_t recovered_no_use_delay_typed_ui(std::uint64_t ui,
    std::uint64_t layout, NoUseDelaySettings *settings, UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Main");
    return recovered_checkbox_control(layout, ui, &settings->allow_desync, dirty, &endpoints->controls);
}

extern "C" __declspec(dllexport) void recovered_no_use_delay_typed_settings(SettingsContext *context,
    NoUseDelaySettings *settings, const SettingsDependencies *endpoints) {
    recovered_boolean_settings(context, "allow_desync", &settings->allow_desync, endpoints);
}

extern "C" __declspec(dllexport) void recovered_no_use_delay_initialize_settings(NoUseDelaySettings *settings) {
    *settings = {};
    const char *label = "Allow desync abuse";
    std::memcpy(settings->allow_desync.metadata + 16, &label, sizeof(label));
}
