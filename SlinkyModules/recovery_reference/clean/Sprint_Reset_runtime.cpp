#include "Sprint_Reset_runtime.hpp"
#include "Sprint.hpp"
#include "Null_Move.hpp"
#include "module_access_helpers.hpp"
#include "module_clock.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>

using Word = std::uintptr_t;
static Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word value; std::memcpy(&value, bridge->metadata + offset, sizeof(value)); return value;
}
template <class Function>
static Function slot(const GameAccessBridge *bridge, std::size_t offset) {
    const auto *table = reinterpret_cast<const Word *>(*bridge->environment);
    return reinterpret_cast<Function>(table[offset / sizeof(Word)]);
}
// 0x239d0 retains the low DWORD from the integer getter.
extern "C" __declspec(dllexport) std::uint32_t recovered_sprint_reset_other_counter(GameAccessBridge *bridge, Word player) {
    using Getter = std::int32_t (*)(Word *, Word, Word);
    return static_cast<std::uint32_t>(slot<Getter>(bridge, 0x320)(bridge->environment, player, identifier(bridge, 0x560)));
}
// 0x25760/0x258c0 replace only AL. 0x25490 forwards that complete EAX to its caller.
static std::uint32_t physical_word(GameAccessBridge *bridge, std::uint32_t code, bool mouse) {
    using Query = Word (*)(Word *, Word, Word, std::uint32_t);
    const auto raw = slot<Query>(bridge, 0x3a8)(bridge->environment,
        identifier(bridge, mouse ? 0x88 : 0x60), identifier(bridge, mouse ? 0xa0 : 0x68), code);
    return (static_cast<std::uint32_t>(raw) & 0xffffff00u) | static_cast<std::uint32_t>(static_cast<std::uint8_t>(raw) != 0);
}
extern "C" __declspec(dllexport) std::uint32_t recovered_sprint_reset_physical_word(GameAccessBridge *bridge, Word key) {
    using Getter = std::int32_t (*)(Word *, Word, Word);
    const auto code = static_cast<std::uint32_t>(slot<Getter>(bridge, 0x320)(bridge->environment, key, identifier(bridge, 0x488)));
    if (code & 0x80000000u) return physical_word(bridge, code + 100u, true);
    return code <= 256u ? physical_word(bridge, code, false) : 0;
}
static Word options(GameAccessBridge *bridge, Word client) { return recovered_access_helper(bridge, 0x22cf0, client, 0, 0); }
static Word forward_key(GameAccessBridge *bridge, Word options) { return recovered_null_move_key(bridge, options, 2); }
static Word sneak_key(GameAccessBridge *bridge, Word options) { return recovered_null_move_key(bridge, options, 7); }
static void set_key(GameAccessBridge *bridge, Word key, std::uint32_t value) { recovered_access_helper(bridge, 0x25460, key, value, 0); }
extern "C" __declspec(dllexport) void recovered_bind_sprint_reset_access(SprintResetDependencies *dependencies) {
    WeaponDependencies weapons; recovered_bind_weapon_access(&weapons);
    TimerDependencies timer; recovered_bind_timer_access(&timer);
    dependencies->counter = weapons.counter;
    dependencies->other_counter = recovered_sprint_reset_other_counter;
    dependencies->damage = timer.damage;
    dependencies->options = options;
    dependencies->forward_key = forward_key;
    dependencies->sneak_key = sneak_key;
    dependencies->sprint_key = recovered_sprint_key;
    dependencies->set_sprinting = recovered_sprint_set_player;
    dependencies->physical_key = recovered_sprint_reset_physical_word;
    dependencies->set_key = set_key;
}
// 0x3b150 reloads mode after selecting the key and bridge after the sprint setter.
extern "C" __declspec(dllexport) void recovered_sprint_reset_action(TimerGame *context,
    const SprintResetSettings *settings, std::uint32_t active_word, const SprintResetDependencies *dependencies) {
    volatile auto *game = context;
    const auto options = dependencies->options(game->bridge, game->client);
    const auto mode = settings->mode.current;
    const auto key = mode == 2 ? dependencies->sprint_key(game->bridge, options)
        : mode == 1 ? dependencies->sneak_key(game->bridge, options) : dependencies->forward_key(game->bridge, options);
    if (settings->mode.current == 2) dependencies->set_sprinting(game->bridge, game->player, static_cast<std::uint8_t>(active_word ^ 1u));
    auto *bridge = game->bridge;
    const auto value = static_cast<std::uint8_t>(active_word)
        ? (*dependencies->post_call_r8 & 0xffffff00u) | static_cast<std::uint32_t>(settings->mode.current == 1)
        : dependencies->physical_key(bridge, key);
    dependencies->set_key(bridge, key, value);
}
static float add(float first, float second) { return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(first), _mm_set_ss(second))); }
// 0x3ad10 captures the context, keeps the phase transitions and consumes random draws in order.
extern "C" __declspec(dllexport) void recovered_sprint_reset_update(SprintResetEvent *event,
    const SprintResetSettings *settings, SprintResetState *state, const SprintResetConstants *constants,
    const SprintResetDependencies *dependencies) {
    auto *context = event->game;
    volatile auto *game = context;
    if (game->ready != 1) {
        if (state->phase == 2) recovered_sprint_reset_action(context, settings, 0, dependencies);
        state->phase = 0; state->have_state = 0; state->timer = 0.0f; return;
    }
    const auto now = recovered_clock_value(dependencies->frequency_bits, dependencies->frequency_target, dependencies->counter_target);
    const auto elapsed = _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(now), _mm_set_sd(state->last_sample_time)));
    if (elapsed >= constants->minimum_elapsed) {
        const auto first = dependencies->counter(game->bridge, game->player);
        const auto second = dependencies->other_counter(game->bridge, game->player);
        if (first == second) { state->last_sample_time = now; state->have_state = 1; }
    }
    state->sample_count = state->sample_count + 1u;
    if (dependencies->damage(game->bridge, game->player) == 10) state->sample_count = 0;
    auto timer = state->timer;
    if (timer > 0.0f) {
        timer = add(timer, constants->decrement); state->timer = timer;
        if (timer > 0.0f) {
            if (state->phase == 2) recovered_sprint_reset_action(context, settings, 1, dependencies);
            return;
        }
    }
    const auto phase = state->phase;
    if (phase == 2) {
        recovered_sprint_reset_action(context, settings, 0, dependencies); state->phase = 0; return;
    }
    if (phase == 1) {
        recovered_sprint_reset_action(context, settings, 1, dependencies);
        state->phase = 2; state->have_state = 0;
        auto duration = settings->duration.current;
        if (settings->randomize.current == 1) {
            const auto bounds = recovered_random_bounds(0.0f, constants->one);
            const auto window = constants->suppression_window;
            const auto sample = std::bit_cast<float>(recovered_policy_smooth_bits(&state->duration_random, bounds,
                window, dependencies->random, dependencies->policy_clock, dependencies->policy_constants));
            const auto difference = _mm_sub_ss(_mm_set_ss(duration), _mm_set_ss(sample));
            duration = _mm_cvtss_f32(_mm_max_ss(_mm_setzero_ps(), difference));
            if (recovered_policy_gate(&state->gate_random, recovered_random_bounds(constants->gate_low, constants->gate_high),
                window, dependencies->random, dependencies->policy_clock, dependencies->policy_constants))
                duration = add(duration, recovered_random_interval(dependencies->random, dependencies->random_constants,
                    recovered_random_bounds(constants->one, constants->two)));
        }
        state->timer = add(duration, state->timer); return;
    }
    auto delay = settings->delay.current;
    if (settings->randomize.current == 1) {
        const auto sample = std::bit_cast<float>(recovered_policy_smooth_bits(&state->delay_random,
            recovered_random_bounds(0.0f, constants->two), constants->delay_window,
            dependencies->random, dependencies->policy_clock, dependencies->policy_constants));
        delay = add(delay, sample);
    }
    if (state->have_state != 1 || (settings->wait_for_damage.current == 1 && state->sample_count != 0)) return;
    if (settings->require_weapon.current == 1 && !recovered_weapon_cached_query(game->bridge, game->player,
        dependencies->weapon_cache, dependencies->weapon_settings, dependencies->weapon_policy, dependencies->weapons)) return;
    state->timer = add(delay, state->timer); state->phase = 1;
}
