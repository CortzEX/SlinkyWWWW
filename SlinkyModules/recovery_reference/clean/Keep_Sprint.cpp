#include "Keep_Sprint.hpp"
#include "Sprint.hpp"
#include <cstring>
#include <emmintrin.h>

using Word = std::uintptr_t;

static Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word value;
    std::memcpy(&value, bridge->metadata + offset, sizeof(value));
    return value;
}

template <class Function>
static Function slot(const GameAccessBridge *bridge, std::size_t offset) {
    const auto *table = reinterpret_cast<const Word *>(*bridge->environment);
    return reinterpret_cast<Function>(table[offset / sizeof(Word)]);
}

// 0x23760 compares only the low 32 bits of the JNI result.
extern "C" __declspec(dllexport) std::int32_t recovered_keep_sprint_counter(
    GameAccessBridge *bridge, Word player) {
    using Getter = std::int32_t (*)(Word *, Word, Word);
    return slot<Getter>(bridge, 0x320)(bridge->environment, player, identifier(bridge, 0x2d8));
}

// 0x235f0 reloads the bridge and each input lane after every setter call.
extern "C" __declspec(dllexport) void recovered_keep_sprint_set_velocity(
    GameAccessBridge *bridge, Word player, const TimerVelocity *velocity) {
    using Setter = void (*)(Word *, Word, Word, double);
    slot<Setter>(bridge, 0x380)(bridge->environment, player, identifier(bridge, 0x2b8), velocity->x);
    slot<Setter>(bridge, 0x380)(bridge->environment, player, identifier(bridge, 0x2c0), velocity->y);
    slot<Setter>(bridge, 0x380)(bridge->environment, player, identifier(bridge, 0x2c8), velocity->z);
}

extern "C" __declspec(dllexport) void recovered_bind_keep_sprint_access(KeepSprintDependencies *dependencies) {
    TimerDependencies timer;
    recovered_bind_timer_access(&timer);
    *dependencies = {recovered_game_sprinting, timer.velocity, timer.on_ground,
                     recovered_keep_sprint_counter, recovered_game_last_attacker_time,
                     recovered_keep_sprint_set_velocity, recovered_sprint_set_player};
}

// 0x3a0f0. An inactive event retains both state flags.
extern "C" __declspec(dllexport) void recovered_keep_sprint_sample(
    KeepSprintEvent *event, const KeepSprintSettings *settings, KeepSprintState *state,
    RandomState *random, const RandomConstants *constants, const KeepSprintDependencies *dependencies) {
    if (event->active != 1) return;
    auto *game = event->game;
    if (game->ready == 1 && dependencies->sprinting(game->bridge, game->player) &&
        static_cast<std::uint8_t>(recovered_random_chance(random, constants, settings->chance.current))) {
        TimerVelocity movement;
        dependencies->velocity(&movement, game->bridge, game->player);
        state->movement = movement;
        state->armed = 1;
    } else {
        state->armed = 0;
    }
}

// 0x3a170. The X and Z multiplies have opposite operand order.
extern "C" __declspec(dllexport) void recovered_keep_sprint_apply(
    KeepSprintEvent *event, const KeepSprintSettings *settings, KeepSprintState *state,
    const KeepSprintDependencies *dependencies) {
    if (state->armed != 1 || event->active != 1) return;
    auto *game = event->game;
    if (!game->player) return;
    if (settings->require_on_ground.current == 1 && !dependencies->on_ground(game->bridge, game->player)) return;
    const auto counter = dependencies->counter(game->bridge, game->player);
    if (counter != dependencies->last_attacker_time(game->bridge, game->player)) return;
    if (settings->allow_reduce.current == 1 && game->status->reducing) return;
    const auto factor = _mm_set_sd(static_cast<double>(settings->motion_multiplier.current));
    state->movement.x = _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(state->movement.x), factor));
    state->movement.z = _mm_cvtsd_f64(_mm_mul_sd(factor, _mm_set_sd(state->movement.z)));
    const auto movement = state->movement;
    dependencies->set_velocity(game->bridge, game->player, &movement);
    state->pending = 1;
}

// 0x3a260 clears pending before inspecting the current game/player.
extern "C" __declspec(dllexport) void recovered_keep_sprint_finish(
    KeepSprintEvent *event, KeepSprintState *state, const KeepSprintDependencies *dependencies) {
    if (state->pending != 1) return;
    state->pending = 0;
    auto *game = event->game;
    if (game->player) dependencies->set_sprinting(game->bridge, game->player, 1);
}

// 0x3a290.
extern "C" __declspec(dllexport) void recovered_keep_sprint_typed_ui(
    std::uint64_t ui, std::uint64_t layout, KeepSprintSettings *settings,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, &settings->chance);
    dependencies->number(layout, ui, &settings->motion_multiplier);
    dependencies->checkbox(layout, ui, &settings->allow_reduce);
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, &settings->require_on_ground);
}

// 0x3a310.
extern "C" __declspec(dllexport) void recovered_keep_sprint_typed_settings(
    SettingsContext *context, KeepSprintSettings *settings, const SettingsDependencies *booleans,
    const ValueSettingsDependencies *numbers) {
    recovered_number_settings(context, "chance", &settings->chance, numbers);
    recovered_number_settings(context, "motion_mult", &settings->motion_multiplier, numbers);
    recovered_boolean_settings(context, "allow_reduce", &settings->allow_reduce, booleans);
    recovered_boolean_settings(context, "require_on_ground", &settings->require_on_ground, booleans);
}
