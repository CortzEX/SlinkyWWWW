#include "Blink.hpp"
#include <cstring>
#include <emmintrin.h>
#include <intrin.h>
#include "module_settings.hpp"

static std::uint64_t read_u64(const void *base, unsigned offset) {
    std::uint64_t value;
    std::memcpy(&value, static_cast<const std::uint8_t *>(base) + offset, sizeof(value));
    return value;
}

static std::uint32_t read_u32(const void *base, unsigned offset) {
    std::uint32_t value;
    std::memcpy(&value, static_cast<const std::uint8_t *>(base) + offset, sizeof(value));
    return value;
}

static void write_u32(void *base, unsigned offset, std::uint32_t value) {
    std::memcpy(static_cast<std::uint8_t *>(base) + offset, &value, sizeof(value));
}

constexpr std::uint64_t blink_descriptor = 0x1802ec600;

// lib_win RVA 0x33660: update countdown and request disable when it expires.
extern "C" __declspec(dllexport) void blink_0(
    std::uint8_t *event, std::uint8_t *settings, std::uint8_t *state,
    const BlinkDependencies *deps) {
    auto *game = reinterpret_cast<std::uint8_t *>(read_u64(event, 8));
    if (game[0x40] != 1) return;

    const auto current = deps->current_239d0(read_u64(game, 0), read_u64(game, 0x28));
    const auto old = read_u32(state, 0x54);
    std::int32_t previous;
    std::memcpy(&previous, &old, sizeof(previous));
    const std::uint8_t rising = (current > previous) & settings[0x28];
    write_u32(state, 0x54, static_cast<std::uint32_t>(current));
    const auto remaining = read_u32(state, 0x58) - 1;
    write_u32(state, 0x58, remaining);
    if (!remaining || rising) deps->queue_state_284f0(read_u64(game, 8), blink_descriptor, 0);
}

// lib_win RVA 0x336d0: classify an intercepted packet.
extern "C" __declspec(dllexport) void blink_2(
    std::uint8_t *event, std::uint8_t *state, const BlinkDependencies *deps) {
    if (state[0x5c] == 1) return;
    std::uint32_t action = 3;
    if (!deps->packet_26a30(read_u64(event, 8), read_u64(event, 0x10)) &&
        !deps->packet_26ad0(read_u64(event, 8), read_u64(event, 0x10)) &&
        !deps->packet_26a90(read_u64(event, 8), read_u64(event, 0x10))) {
        action = deps->packet_27160(read_u64(event, 8), read_u64(event, 0x10)) ? 3 : 1;
    }
    write_u32(event, 0x24, action);
}

// lib_win RVA 0x33750: force action 1 for any nonzero direction byte.
extern "C" __declspec(dllexport) void blink_3(std::uint8_t *event, std::uint8_t *state) {
    if (state[0x5c]) write_u32(event, 0x24, 1);
}

// lib_win RVA 0x33770: module notification initializes the countdown and direction.
extern "C" __declspec(dllexport) void blink_5(
    std::uint8_t *event, std::uint8_t *settings, std::uint8_t *state) {
    if (read_u64(event, 0x10) != blink_descriptor || event[0x18] != 1) return;
    float duration;
    std::memcpy(&duration, settings + 0x60, sizeof(duration));
    write_u32(state, 0x58, static_cast<std::uint32_t>(_mm_cvttss_si64(_mm_set_ss(duration))));
    write_u32(state, 0x54, 0x7fffffff);
    _InterlockedExchange8(reinterpret_cast<volatile char *>(state + 0x5c),
                          static_cast<char>(settings[0xb8]));
}

// lib_win RVA 0x337c0: selected block interactions can disable Blink.
extern "C" __declspec(dllexport) void blink_14(
    std::uint8_t *event, std::uint8_t *settings, const BlinkDependencies *deps) {
    auto *game = reinterpret_cast<std::uint8_t *>(read_u64(event, 8));
    if ((event[0x10] == 1 ? settings[0xe0] : settings[0x100]) != 1) return;
    const auto hit = deps->hit_22e10(read_u64(game, 0), read_u64(game, 0x18));
    if (hit && deps->hit_type_24b50(read_u64(game, 0), hit) == 1)
        deps->queue_state_284f0(read_u64(game, 8), blink_descriptor, 0);
}

struct BlinkSettings {
    void *direction;
    void *max_duration;
    BooleanSetting *disable_on_attack;
    BooleanSetting *disable_on_block_interact;
    BooleanSetting *disable_on_block_dig;
};

struct BlinkUiDependencies {
    void (*section)(std::uint64_t ui, std::uint64_t layout, const char *label);
    void (*choice)(std::uint64_t layout, std::uint64_t ui, void *setting);
    void (*number)(std::uint64_t layout, std::uint64_t ui, void *setting);
    void (*checkbox)(std::uint64_t layout, std::uint64_t ui, BooleanSetting *setting);
};

// lib_win RVA 0x33830.
extern "C" __declspec(dllexport) void recovered_blink_ui(
    std::uint64_t ui, std::uint64_t layout, const BlinkSettings *settings,
    const BlinkUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, settings->direction);
    dependencies->number(layout, ui, settings->max_duration);
    dependencies->section(ui, layout, "Disable on");
    dependencies->checkbox(layout, ui, settings->disable_on_attack);
    dependencies->checkbox(layout, ui, settings->disable_on_block_interact);
    dependencies->checkbox(layout, ui, settings->disable_on_block_dig);
}

struct BlinkSettingsDependencies {
    void (*choice)(SettingsContext *context, const char *key, void *setting);
    void (*number)(SettingsContext *context, const char *key, void *setting);
    SettingsDependencies boolean;
};

// lib_win RVA 0x338d0.
extern "C" __declspec(dllexport) void recovered_blink_settings(
    SettingsContext *context, const BlinkSettings *settings,
    const BlinkSettingsDependencies *dependencies) {
    dependencies->choice(context, "direction", settings->direction);
    dependencies->number(context, "max_duration", settings->max_duration);
    recovered_boolean_settings(context, "disable_on_attack",
                               settings->disable_on_attack, &dependencies->boolean);
    recovered_boolean_settings(context, "disable_on_block_interact",
                               settings->disable_on_block_interact, &dependencies->boolean);
    recovered_boolean_settings(context, "disable_on_block_dig",
                               settings->disable_on_block_dig, &dependencies->boolean);
}

struct BlinkFormatDependencies {
    void (*format)(std::uint64_t target, std::uint32_t capacity,
                   const char *pattern, const char *value);
};

// lib_win RVA 0x33950. The valid direction values are In, Out, and Both.
extern "C" __declspec(dllexport) void recovered_blink_direction_label(
    std::uint64_t target, std::uint32_t direction,
    const BlinkFormatDependencies *dependencies) {
    // ponytail: only the three registered enum states are modeled; extend if another valid state is found.
    static constexpr const char *names[] = {"In", "Out", "Both"};
    dependencies->format(target, 0x20, "%s", names[direction]);
}
