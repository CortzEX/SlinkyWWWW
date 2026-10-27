#include "Fast_Mine.hpp"
#include "module_access_helpers.hpp"
#include <bit>
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
static Word controller(GameAccessBridge *bridge, Word client) {
    return recovered_access_helper(bridge, 0x22df0, client, 0, 0);
}
// 0x27df0 / 0x27e10 use the float getter return and the fourth setter argument.
static float progress(GameAccessBridge *bridge, Word object) {
    using Call = float (*)(Word *, Word, Word);
    return slot<Call>(bridge, 0x330)(bridge->environment, object, identifier(bridge, 0xbc8));
}
static void set_progress(GameAccessBridge *bridge, Word object, float value) {
    using Call = void (*)(Word *, Word, Word, float);
    slot<Call>(bridge, 0x378)(bridge->environment, object, identifier(bridge, 0xbc8), value);
}
// 0x27e40 / 0x27e60 read signed current state and write the raw low DWORD.
static std::int32_t current(GameAccessBridge *bridge, Word object) {
    using Call = std::int32_t (*)(Word *, Word, Word);
    return slot<Call>(bridge, 0x320)(bridge->environment, object, identifier(bridge, 0xbd0));
}
static void set_current(GameAccessBridge *bridge, Word object, std::uint32_t value) {
    using Call = void (*)(Word *, Word, Word, std::uint32_t);
    slot<Call>(bridge, 0x368)(bridge->environment, object, identifier(bridge, 0xbd0), value);
}
extern "C" __declspec(dllexport) void recovered_bind_fast_mine_access(FastMineDependencies *dependencies) {
    *dependencies = {controller, progress, set_progress, current, set_current};
}

// 0x41a90 stores the original counter even after clamping or decrementing it.
extern "C" __declspec(dllexport) void recovered_fast_mine_update(FastMineEvent *event,
    const FastMineSettings *settings, FastMineState *state, const FastMineDependencies *dependencies) {
    auto *game = event->game;
    const auto object = dependencies->controller(game->bridge, game->client);
    std::int32_t value = 0;
    if (object) {
        state->saved_progress = dependencies->progress(game->bridge, object);
        value = dependencies->current(game->bridge, object);
        const auto limit = settings->break_delay.current;
        const auto converted = _mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(), value));
        if (converted > limit) {
            dependencies->set_current(game->bridge, object,
                static_cast<std::uint32_t>(_mm_cvttss_si32(_mm_set_ss(limit))));
        } else if (value > 0 && settings->decrement_block_hit_delay.current && value == state->last_current) {
            dependencies->set_current(game->bridge, object, static_cast<std::uint32_t>(value) - 1u);
        }
    }
    state->last_current = value;
}

// 0x41b30 keeps scalar SSE conversions and modulo-32-bit step arithmetic.
extern "C" __declspec(dllexport) void recovered_fast_mine_progress(FastMineEvent *event,
    const FastMineSettings *settings, const FastMineState *state, const FastMineConstants *constants,
    const FloatCeilingConstants *ceiling, const FastMineDependencies *dependencies) {
    auto *game = event->game;
    const auto object = dependencies->controller(game->bridge, game->client);
    if (!object) return;
    const auto value = dependencies->progress(game->bridge, object);
    if (value == 0.0f || state->saved_progress != 0.0f) return;
    const auto promoted = _mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(value));
    const auto first_argument = _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(constants->progress_unit), _mm_set_ss(value)));
    const auto first = _mm_cvttss_si64(_mm_set_ss(std::bit_cast<float>(
        recovered_float_ceiling_bits(std::bit_cast<std::uint32_t>(first_argument), ceiling))));
    const auto speed = _mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(settings->speed.current));
    const auto quotient = _mm_div_sd(_mm_div_sd(_mm_set_sd(constants->speed_unit), speed), promoted);
    const auto second_argument = _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), quotient));
    const auto second = _mm_cvttss_si64(_mm_set_ss(std::bit_cast<float>(
        recovered_float_ceiling_bits(std::bit_cast<std::uint32_t>(second_argument), ceiling))));
    const auto steps = static_cast<std::uint32_t>(first) - static_cast<std::uint32_t>(second) + 1u;
    const auto factor = _mm_cvtsi64_ss(_mm_setzero_ps(), static_cast<std::int64_t>(steps));
    const auto result = _mm_cvtss_f32(_mm_mul_ss(factor, _mm_set_ss(value)));
    dependencies->set_progress(game->bridge, object, result);
}

// 0x41c20 / 0x41c80 share the recovered control and persistence helpers.
extern "C" __declspec(dllexport) std::uint64_t recovered_fast_mine_typed_ui(std::uint64_t ui,
    std::uint64_t layout, FastMineSettings *settings, UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Main");
    recovered_number_control(layout, ui, &settings->speed, dirty, &endpoints->controls);
    recovered_number_control(layout, ui, &settings->break_delay, dirty, &endpoints->controls);
    return recovered_checkbox_control(layout, ui, &settings->decrement_block_hit_delay, dirty, &endpoints->controls);
}
extern "C" __declspec(dllexport) void recovered_fast_mine_typed_settings(SettingsContext *context,
    FastMineSettings *settings, const SettingsDependencies *booleans, const ValueSettingsDependencies *numbers) {
    recovered_number_settings(context, "speed", &settings->speed, numbers);
    recovered_number_settings(context, "break_delay", &settings->break_delay, numbers);
    recovered_boolean_settings(context, "decr_block_hit_delay", &settings->decrement_block_hit_delay, booleans);
}
// 0x41ce0 promotes the configured speed before passing it to the formatter.
extern "C" __declspec(dllexport) std::uint64_t recovered_fast_mine_label(char *destination,
    const FastMineSettings *settings, FormatState *format) {
    return recovered_format(format, destination, 32, "%.2fx", static_cast<double>(settings->speed.current));
}
