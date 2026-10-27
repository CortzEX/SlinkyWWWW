#include "Criticals.hpp"
#include "module_access_helpers.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>
#include <intrin.h>

using Word = std::uintptr_t;
static Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word value;
    std::memcpy(&value, bridge->metadata + offset, sizeof(value));
    return value;
}
template <class Function>
static Function slot(const GameAccessBridge *bridge, std::size_t offset) {
    return reinterpret_cast<Function>(reinterpret_cast<const Word *>(*bridge->environment)[offset / sizeof(Word)]);
}
// 0x259f0 / 0x25a10 use the float getter and fourth setter argument.
static float timer_value(GameAccessBridge *bridge, Word object) {
    using Get = float (*)(Word *, Word, Word);
    return slot<Get>(bridge, 0x330)(bridge->environment, object, identifier(bridge, 0x398));
}
static void set_timer_value(GameAccessBridge *bridge, Word object, float value) {
    using Set = void (*)(Word *, Word, Word, float);
    slot<Set>(bridge, 0x378)(bridge->environment, object, identifier(bridge, 0x398), value);
}
// 0x26350 / 0x26390 / 0x263c0 consume only the low predicate byte.
static std::uint8_t predicate(GameAccessBridge *bridge, Word object, std::size_t field, std::size_t entry) {
    using Get = std::uint8_t (*)(Word *, Word, Word);
    return slot<Get>(bridge, entry)(bridge->environment, object, identifier(bridge, field));
}
// 0x26410 returns the raw double Y coordinate.
static double packet_y(GameAccessBridge *bridge, Word object) {
    using Get = double (*)(Word *, Word, Word);
    return slot<Get>(bridge, 0x338)(bridge->environment, object, identifier(bridge, 0x728));
}
extern "C" __declspec(dllexport) void recovered_bind_criticals_access(CriticalsDependencies *dependencies) {
    recovered_bind_timer_access(&dependencies->timer);
}

// 0x32f10 keeps chance countdown, signed wrapping tick subtraction and atomic publication.
extern "C" __declspec(dllexport) void recovered_criticals_typed_update(TimerEvent *event,
    const CriticalsSettings *settings, volatile CriticalsState *state, const CriticalsDependencies *dependencies) {
    auto *game = event->game;
    std::uint8_t eligible = 0;
    if (game->ready == 1) {
        const auto counter = state->chance_counter;
        std::uint8_t chance;
        if (counter) {
            chance = state->cached_chance == 1;
            state->chance_counter = counter - 1u;
        } else {
            state->chance_counter = 10;
            chance = static_cast<std::uint8_t>(recovered_random_chance(dependencies->random_state,
                dependencies->random_constants, settings->chance.current));
            state->cached_chance = chance;
            state->chance_counter = state->chance_counter - 1u;
        }
        if (chance && (settings->require_mouse.current != 1 || dependencies->timer.mouse(game)) &&
            (settings->require_weapon.current != 1 || recovered_weapon_cached_query(game->bridge, game->player,
                dependencies->weapon_cache, dependencies->weapon_settings, dependencies->weapon_policy, dependencies->weapon_access))) {
            const auto previous = static_cast<std::uint32_t>(recovered_game_last_attacker_time(game->bridge, game->player));
            const auto current = dependencies->weapon_access->counter(game->bridge, game->player);
            eligible = std::bit_cast<std::int32_t>(current - previous) < 11;
        }
    }
    const auto mode = settings->mode.current;
    if (mode == 0) {
        _InterlockedExchange8(reinterpret_cast<volatile char *>(&state->eligible), static_cast<char>(eligible));
        const auto limit = _mm_cvttss_si32(_mm_set_ss(settings->max_delay.current));
        _InterlockedExchange16(reinterpret_cast<volatile short *>(&state->limit), static_cast<short>(limit));
        state->active = 0;
    } else if (mode == 1) {
        _InterlockedExchange8(reinterpret_cast<volatile char *>(&state->eligible), 0);
        std::uint8_t active = 0;
        if (eligible && !dependencies->timer.on_ground(game->bridge, game->player)) {
            TimerVelocity velocity;
            dependencies->timer.velocity(&velocity, game->bridge, game->player);
            if (!(velocity.y >= 0.0) && dependencies->timer.damage(game->bridge, game->player) != 10) {
                const auto target = recovered_access_helper(game->bridge, 0x22e10, game->client, 0, 0);
                if (target) active = static_cast<std::uint32_t>(recovered_access_helper(game->bridge, 0x24b50, target, 0, 0)) == 2;
            }
        }
        state->active = active;
    }
}

// 0x33080 reloads settings and accumulated state after each timer endpoint.
extern "C" __declspec(dllexport) void recovered_criticals_typed_timer(CriticalsTimerEvent *event,
    const CriticalsSettings *settings, volatile CriticalsState *state, const CriticalsConstants *constants,
    const CriticalsDependencies *dependencies) {
    auto *game = event->game;
    const auto timer = dependencies->timer.timer(game->bridge, game->client);
    if (state->active == 1) {
        dependencies->timer.set_speed(game->bridge, timer, settings->timer_speed.current);
        state->restore_timer = 1;
        const auto elapsed = _mm_mul_sd(_mm_set_sd(event->elapsed), _mm_set_sd(constants->time_scale));
        const auto difference = _mm_sub_ss(_mm_set_ss(constants->normal_speed), _mm_set_ss(settings->timer_speed.current));
        const auto amount = _mm_mul_sd(_mm_cvtss_sd(_mm_setzero_pd(), difference), elapsed);
        const auto accumulated = _mm_add_sd(amount, _mm_set_sd(state->accumulated));
        state->accumulated = _mm_cvtsd_f64(accumulated);
        const auto cap = static_cast<double>(settings->boost.current);
        if (_mm_cvtsd_f64(accumulated) > cap) state->accumulated = cap;
    } else {
        const auto accumulated = state->accumulated;
        if (accumulated > constants->threshold) {
            const auto previous = timer_value(game->bridge, timer);
            const auto whole = _mm_cvttsd_si32(_mm_set_sd(accumulated));
            const auto adjusted = _mm_add_ss(_mm_cvtsi32_ss(_mm_setzero_ps(), whole), _mm_set_ss(previous));
            set_timer_value(game->bridge, timer, _mm_cvtss_f32(adjusted));
            state->accumulated = _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(state->accumulated),
                _mm_cvtsi32_sd(_mm_setzero_pd(), whole)));
        }
        if (state->restore_timer == 1) {
            dependencies->timer.set_speed(game->bridge, timer, constants->normal_speed);
            state->restore_timer = 0;
        }
    }
}

// 0x331a0 preserves signed IDs/timestamps, low-bit state gates and wrapping counters.
extern "C" __declspec(dllexport) void recovered_criticals_typed_packet(CriticalsPacketEvent *event,
    volatile CriticalsState *state) {
    const auto object = event->object;
    const auto packet = predicate(event->bridge, object, 0x708, 0x100) ? object : 0;
    if (packet && predicate(event->bridge, packet, 0x710, 0x300) &&
        std::bit_cast<std::int32_t>(event->id) > std::bit_cast<std::int32_t>(static_cast<std::uint32_t>(state->last_packet_id))) {
        const auto position = packet_y(event->bridge, packet);
        const auto ground = static_cast<std::uint8_t>(predicate(event->bridge, packet, 0x718, 0x300) != 0);
        if (ground || state->previous_y > position) state->falling = ground ^ 1u;
        if ((state->eligible & 1) && (state->falling & 1)) {
            const auto step = (static_cast<std::uint32_t>(state->limit) * 0xcccdu) >> 18;
            const auto total = state->packet_count + step;
            state->packet_count = total;
            if (std::bit_cast<std::int32_t>(total) > static_cast<std::int32_t>(state->limit)) state->packet_count = state->limit;
        } else state->packet_count = 0;
        state->previous_y = position;
        state->last_packet_id = event->id;
    }
    if (std::bit_cast<std::int64_t>(event->timestamp) < static_cast<std::int64_t>(std::bit_cast<std::int32_t>(static_cast<std::uint32_t>(state->packet_count))))
        event->action = 1;
}

// 0x332b0 matches caller-owned module identity and tests the restore flag's low bit.
extern "C" __declspec(dllexport) void recovered_criticals_typed_disable(TimerEvent *event, Word module_identity,
    volatile CriticalsState *state, const CriticalsConstants *constants, const CriticalsDependencies *dependencies) {
    if (event->module != module_identity || event->enabled != 0 || !(state->restore_timer & 1)) return;
    auto *game = event->game;
    const auto timer = dependencies->timer.timer(game->bridge, game->client);
    dependencies->timer.set_speed(game->bridge, timer, constants->disable_speed);
    state->restore_timer = 0;
}

// 0x33310 reads mode after rendering chance, so renderer changes affect the branch.
extern "C" __declspec(dllexport) std::uint64_t recovered_criticals_typed_ui(std::uint64_t ui,
    std::uint64_t layout, CriticalsSettings *settings, UiDirtyState *dirty, const ChoiceUiEndpoints *endpoints) {
    const auto &standard = endpoints->standard;
    standard.section(ui, layout, "Main");
    recovered_choice_control(layout, ui, &settings->mode, settings->choice_flag, dirty, endpoints->choice);
    recovered_number_control(layout, ui, &settings->chance, dirty, &standard.controls);
    if (settings->mode.current) {
        recovered_number_control(layout, ui, &settings->timer_speed, dirty, &standard.controls);
        recovered_number_control(layout, ui, &settings->boost, dirty, &standard.controls);
    } else recovered_number_control(layout, ui, &settings->max_delay, dirty, &standard.controls);
    standard.section(ui, layout, "Conditions");
    recovered_checkbox_control(layout, ui, &settings->require_weapon, dirty, &standard.controls);
    return recovered_checkbox_control(layout, ui, &settings->require_mouse, dirty, &standard.controls);
}
// 0x333d0 processes all records, independently of the UI branch.
extern "C" __declspec(dllexport) void recovered_criticals_typed_settings(SettingsContext *context,
    CriticalsSettings *settings, const SettingsDependencies *booleans, const ValueSettingsDependencies *values) {
    recovered_choice_settings(context, "mode", &settings->mode, values);
    recovered_number_settings(context, "chance", &settings->chance, values);
    recovered_number_settings(context, "max_delay", &settings->max_delay, values);
    recovered_number_settings(context, "timer_speed", &settings->timer_speed, values);
    recovered_number_settings(context, "boost", &settings->boost, values);
    recovered_boolean_settings(context, "require_weapon", &settings->require_weapon, booleans);
    recovered_boolean_settings(context, "require_mouse_pressed", &settings->require_mouse, booleans);
}
// 0x33480 indexes the independent label table using the configured DWORD mode.
extern "C" __declspec(dllexport) std::uint64_t recovered_criticals_label(char *destination,
    const ChoiceSetting *mode, const char *const *labels, FormatState *format) {
    return recovered_format(format, destination, 32, "%s", labels[mode->current]);
}
