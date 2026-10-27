#include "Fast_Accel.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>

extern "C" __declspec(dllexport) void recovered_bind_fast_accel_access(FastAccelDependencies *dependencies) {
    TimerDependencies timer;
    recovered_bind_timer_access(&timer);
    dependencies->damage = timer.damage;
    dependencies->velocity = timer.velocity;
    dependencies->on_ground = timer.on_ground;
    dependencies->sprinting = recovered_game_sprinting;
    dependencies->set_velocity = recovered_keep_sprint_set_velocity;
}
// 0x13cfd0 reads an unaligned encoded cell immediately before the external numeric call.
static double numeric_pair(const std::uint8_t *cell, double first, double second) {
    std::uintptr_t encoded;
    std::memcpy(&encoded, cell, sizeof(encoded));
    using Function = double (*)(double, double);
    return reinterpret_cast<Function>(encoded + std::uintptr_t{0x2d2898a5})(first, second);
}
// 0x42320 snapshots the game pointer and reloads its bridge/player at each helper boundary.
extern "C" __declspec(dllexport) void recovered_fast_accel_update(FastAccelEvent *event,
    const FastAccelSettings *settings, const FastAccelConstants *constants, const FastAccelDependencies *dependencies) {
    if (event->forward == 0.0f && event->sideways == 0.0f) return;
    auto *game = event->game;
    if (settings->require_weapon.current == 1 && !recovered_weapon_cached_query(game->bridge, game->player,
        dependencies->weapon_cache, dependencies->weapon_settings, dependencies->weapon_policy, dependencies->weapon_access)) return;
    if (settings->require_not_damaged.current == 1 &&
        std::bit_cast<std::int32_t>(dependencies->damage(game->bridge, game->player)) > 0) return;
    TimerVelocity motion;
    dependencies->velocity(&motion, game->bridge, game->player);
    const auto speed = numeric_pair(dependencies->encoded_numeric_target, motion.x, motion.z);
    if (speed == 0.0 || !dependencies->on_ground(game->bridge, game->player)) return;
    const auto side = event->sideways, forward = event->forward, factor = event->factor;
    const auto distance = [&](float first, float second) {
        return std::bit_cast<float>(recovered_float_distance(std::bit_cast<std::uint32_t>(first),
            std::bit_cast<std::uint32_t>(second), dependencies->distance_constants));
    };
    const auto length = distance(side, forward);
    const auto denominator = _mm_max_ss(_mm_set_ss(constants->minimum), _mm_set_ss(length));
    const auto scale = _mm_div_ss(_mm_set_ss(factor), denominator);
    const auto x = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(side), scale));
    const auto z = _mm_cvtss_f32(_mm_mul_ss(scale, _mm_set_ss(forward)));
    const auto step = _mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(distance(x, z)));
    auto limit = _mm_add_sd(_mm_setzero_pd(), step);
    const auto decay = _mm_set_sd(constants->decay);
    for (int index = 0; index < 19; ++index) limit = _mm_add_sd(_mm_mul_sd(limit, decay), step);
    if (event->jump == 1 && dependencies->sprinting(game->bridge, game->player))
        limit = _mm_add_sd(limit, _mm_set_sd(constants->jump_increment));
    if (speed > _mm_cvtsd_f64(limit)) return;
    const auto original = _mm_set_sd(speed);
    const auto amount = _mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(settings->acceleration.current));
    const auto accelerated = _mm_add_sd(original, _mm_mul_sd(_mm_sub_sd(limit, original), amount));
    motion.x = _mm_cvtsd_f64(_mm_mul_sd(_mm_div_sd(_mm_set_sd(motion.x), original), accelerated));
    motion.z = _mm_cvtsd_f64(_mm_mul_sd(_mm_div_sd(_mm_set_sd(motion.z), original), accelerated));
    const TimerVelocity copy = motion;
    dependencies->set_velocity(game->bridge, game->player, &copy);
}

// 0x42580 / 0x425f0 retain the original order and shared helper behavior.
extern "C" __declspec(dllexport) std::uint64_t recovered_fast_accel_typed_ui(std::uint64_t ui,
    std::uint64_t layout, FastAccelSettings *settings, UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Main");
    recovered_number_control(layout, ui, &settings->acceleration, dirty, &endpoints->controls);
    endpoints->section(ui, layout, "Conditions");
    recovered_checkbox_control(layout, ui, &settings->require_not_damaged, dirty, &endpoints->controls);
    return recovered_checkbox_control(layout, ui, &settings->require_weapon, dirty, &endpoints->controls);
}
extern "C" __declspec(dllexport) void recovered_fast_accel_typed_settings(SettingsContext *context,
    FastAccelSettings *settings, const SettingsDependencies *booleans, const ValueSettingsDependencies *numbers) {
    recovered_number_settings(context, "acceleration", &settings->acceleration, numbers);
    recovered_boolean_settings(context, "require_not_damaged", &settings->require_not_damaged, booleans);
    recovered_boolean_settings(context, "require_weapon", &settings->require_weapon, booleans);
}
