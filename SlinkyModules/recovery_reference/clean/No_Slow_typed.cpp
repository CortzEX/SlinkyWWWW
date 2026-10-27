#include "No_Slow_typed.hpp"
#include <cstring>
#include <emmintrin.h>

extern "C" __declspec(dllexport) void recovered_bind_no_slow_access(NoSlowDependencies *access) {
    *access = {recovered_game_using_item, recovered_game_item_object, recovered_game_item_numeric_id};
}

// 0x42a20 captures the game, reloading its bridge/player between item queries.
extern "C" __declspec(dllexport) void recovered_no_slow_typed_update(NoSlowEvent *event,
    const NoSlowSettings *settings, const double *slowdown_divisor, const NoSlowDependencies *access) {
    auto *game = event->game;
    if (!access->using_item(game->bridge, game->player)) return;
    const auto item = access->held_item(game->bridge, game->player);
    if (!item) return;
    const auto bucket = static_cast<std::uint32_t>(access->item_type(game->bridge, item)) - 0x105u;
    const auto &setting = bucket < 23 && ((0x4088c0u >> (bucket & 31u)) & 1u)
        ? settings->sword : bucket == 0 ? settings->bow : settings->consumables;
    const auto ratio = _mm_div_sd(_mm_set_sd(static_cast<double>(setting.current)), _mm_set_sd(*slowdown_divisor));
    std::uint64_t input;
    std::memcpy(&input, &event->sideways, sizeof(input));
    const auto movement = _mm_cvtps_pd(_mm_castsi128_ps(_mm_cvtsi64_si128(static_cast<std::int64_t>(input))));
    const auto scaled = _mm_cvtpd_ps(_mm_mul_pd(_mm_unpacklo_pd(ratio, ratio), movement));
    const auto output = static_cast<std::uint64_t>(_mm_cvtsi128_si64(_mm_castps_si128(scaled)));
    std::memcpy(&event->sideways, &output, sizeof(output));
}

// 0x42ac0 retains the sword/bow/consumables order and final full wrapper return.
extern "C" __declspec(dllexport) std::uint64_t recovered_no_slow_typed_ui(std::uint64_t ui,
    std::uint64_t layout, NoSlowSettings *settings, UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Retained speed");
    recovered_number_control(layout, ui, &settings->sword, dirty, &endpoints->controls);
    recovered_number_control(layout, ui, &settings->bow, dirty, &endpoints->controls);
    return recovered_number_control(layout, ui, &settings->consumables, dirty, &endpoints->controls);
}

// 0x42b20 uses the same order for all three persistence keys.
extern "C" __declspec(dllexport) void recovered_no_slow_typed_settings(SettingsContext *context,
    NoSlowSettings *settings, const ValueSettingsDependencies *endpoints) {
    recovered_number_settings(context, "mult_sword", &settings->sword, endpoints);
    recovered_number_settings(context, "mult_bow", &settings->bow, endpoints);
    recovered_number_settings(context, "mult_consumables", &settings->consumables, endpoints);
}

extern "C" __declspec(dllexport) void recovered_no_slow_initialize_settings(NoSlowSettings *settings) {
    *settings = {};
    auto initialize = [](NumberSetting &setting, const char *label) {
        const char *format = "%.0f%%";
        const float percentage = 100.0f;
        std::memcpy(setting.metadata + 16, &label, sizeof(label));
        std::memcpy(setting.metadata + 24, &format, sizeof(format));
        std::memcpy(setting.metadata + 36, &percentage, sizeof(percentage));
        setting.minimum = 0.2f;
        setting.maximum = 1.0f;
        setting.current = 1.0f;
    };
    initialize(settings->bow, "Bow");
    initialize(settings->sword, "Sword");
    initialize(settings->consumables, "Consumables");
}
