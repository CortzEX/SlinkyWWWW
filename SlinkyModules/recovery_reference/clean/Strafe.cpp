#include "Strafe.hpp"
#include "Free_Look.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>

static std::uint8_t weapon(GameAccessBridge *bridge, std::uintptr_t entity, const StrafeWeaponBinding *state) {
    return recovered_weapon_cached_query(bridge, entity, state->cache, state->settings, state->policy, state->access);
}
extern "C" __declspec(dllexport) void recovered_bind_strafe_access(StrafeDependencies *dependencies) {
    TimerDependencies timer;
    recovered_bind_timer_access(&timer);
    FreeLookDependencies rotation;
    recovered_bind_free_look_access(&rotation);
    dependencies->sprinting = recovered_game_sprinting;
    dependencies->weapon = weapon;
    dependencies->damage = timer.damage;
    dependencies->on_ground = timer.on_ground;
    dependencies->velocity = timer.velocity;
    dependencies->rotation = rotation.player_angles;
    dependencies->set_velocity = recovered_keep_sprint_set_velocity;
}
extern "C" __declspec(dllexport) double recovered_strafe_interpolate(double current, double target, double amount) {
    const auto a = _mm_set_sd(current);
    return _mm_cvtsd_f64(_mm_add_sd(a, _mm_mul_sd(_mm_sub_sd(_mm_set_sd(target), a), _mm_set_sd(amount))));
}
extern "C" __declspec(dllexport) void recovered_strafe_typed_sample(
    StrafeEvent *event, std::uint8_t *sampled, const StrafeDependencies *dependencies) {
    auto *game = event->game;
    *sampled = dependencies->sprinting(game->bridge, game->player);
}
extern "C" __declspec(dllexport) void recovered_strafe_typed_motion(StrafeEvent *event,
    const StrafeSettings *settings, const std::uint8_t *sampled, const StrafeConstants *constants,
    const StrafeDependencies *dependencies) {
    if (event->forward == 0.0f && event->sideways == 0.0f) return;
    auto *game = event->game;
    if (settings->require_weapon.current == 1 && !dependencies->weapon(game->bridge, game->player, dependencies->weapon_state)) return;
    const auto damage = std::bit_cast<std::int32_t>(dependencies->damage(game->bridge, game->player));
    if (static_cast<float>(damage) > settings->max_hurt_time.current) return;
    std::uint8_t boost = 0;
    float amount;
    if (!dependencies->on_ground(game->bridge, game->player)) amount = settings->air.current;
    else if (event->jump == 1) { boost = *sampled ^ 1; amount = settings->jump.current; }
    else amount = settings->ground.current;
    if (amount == 0.0f) return;
    TimerVelocity motion;
    dependencies->velocity(&motion, game->bridge, game->player);
    auto speed = dependencies->speed(motion.x, motion.z);
    if (boost) speed += constants->boost;
    const auto yaw_bits = static_cast<std::uint32_t>(dependencies->rotation(game->bridge, game->player));
    const auto sideways = event->sideways, forward = event->forward;
    auto turn = sideways < 0.0f ? constants->negative_side : 0.0;
    if (sideways > 0.0f) turn = constants->positive_side;
    auto heading = static_cast<double>(std::bit_cast<float>(yaw_bits));
    if (forward > 0.0f) turn *= constants->forward_factor;
    else if (forward < 0.0f) { heading += constants->half_turn; turn *= constants->backward_factor; }
    else turn *= constants->zero_factor;
    const auto radians = static_cast<float>(((turn + heading) * constants->angle_scale) / constants->half_turn);
    const auto old_x = motion.x;
    const auto sine = std::bit_cast<float>(std::bit_cast<std::uint32_t>(dependencies->sine(radians)) ^ constants->sign_mask);
    motion.x = recovered_strafe_interpolate(old_x, static_cast<double>(sine) * speed, static_cast<double>(amount));
    const auto old_z = motion.z;
    const auto cosine = dependencies->cosine(radians);
    motion.z = recovered_strafe_interpolate(old_z, static_cast<double>(cosine) * speed, static_cast<double>(amount));
    const auto copy = motion;
    dependencies->set_velocity(game->bridge, game->player, &copy);
}

extern "C" __declspec(dllexport) std::uint64_t recovered_strafe_typed_ui(std::uint64_t ui,
    std::uint64_t layout, StrafeSettings *settings, UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Strength");
    recovered_number_control(layout, ui, &settings->jump, dirty, &endpoints->controls);
    recovered_number_control(layout, ui, &settings->ground, dirty, &endpoints->controls);
    recovered_number_control(layout, ui, &settings->air, dirty, &endpoints->controls);
    endpoints->section(ui, layout, "Conditions");
    recovered_number_control(layout, ui, &settings->max_hurt_time, dirty, &endpoints->controls);
    return recovered_checkbox_control(layout, ui, &settings->require_weapon, dirty, &endpoints->controls);
}
extern "C" __declspec(dllexport) void recovered_strafe_typed_settings(SettingsContext *context,
    StrafeSettings *settings, const SettingsDependencies *booleans, const ValueSettingsDependencies *numbers) {
    recovered_number_settings(context, "strength_jump", &settings->jump, numbers);
    recovered_number_settings(context, "strength_ground", &settings->ground, numbers);
    recovered_number_settings(context, "strength_air", &settings->air, numbers);
    recovered_number_settings(context, "max_hurt_time", &settings->max_hurt_time, numbers);
    recovered_boolean_settings(context, "require_weapon", &settings->require_weapon, booleans);
}
