// Sprint Reset

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Sprint_Reset.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Sprint_Reset.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Sprint Reset: lib_win settings 0x3b070.
// UI 0x3afc0.
static constexpr UiStep ui_steps_Surface_Sprint_Reset[] = {
    {UiControl::section, "Main", 0},          {UiControl::choice, nullptr, 0x2eff28},
    {UiControl::number, nullptr, 0x2eff68},   {UiControl::number, nullptr, 0x2f0000},
    {UiControl::checkbox, nullptr, 0x2effa0}, {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2effc0}, {UiControl::checkbox, nullptr, 0x2effe0},
};
static constexpr SettingsStep settings_steps_Surface_Sprint_Reset[] = {
    {SettingsControl::choice, "mode", 0x2eff28},
    {SettingsControl::number, "delay", 0x2eff68},
    {SettingsControl::number, "duration", 0x2f0000},
    {SettingsControl::boolean, "randomize", 0x2effa0},
    {SettingsControl::boolean, "wait_for_damage", 0x2effc0},
    {SettingsControl::boolean, "require_weapon", 0x2effe0},
};
static constexpr ModuleSurface surface_Surface_Sprint_Reset{
    ui_steps_Surface_Sprint_Reset, std::size(ui_steps_Surface_Sprint_Reset),
    settings_steps_Surface_Sprint_Reset, std::size(settings_steps_Surface_Sprint_Reset)};

extern "C" __declspec(dllexport) void
recovered_sprint_reset_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                          const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Sprint_Reset, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_sprint_reset_settings(SettingsContext *context, std::uint8_t *image,
                                const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Sprint_Reset, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Sprint_Reset.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Sprint_Reset/Sprint_Reset.cpp
#ifndef SLINKY_SHARE_313109E60B317702A855
#define SLINKY_SHARE_313109E60B317702A855
// BEGIN SOURCE native/verified/Sprint_Reset.hpp
#include "../runtime/native/verified/module_choice_ui.hpp"
#include "../runtime/native/verified/module_format.hpp"
#include <cstddef>

struct SprintResetSettings {
    ChoiceSetting mode;
    std::uint8_t choice_flag, padding[7];
    NumberSetting delay;
    BooleanSetting randomize, wait_for_damage, require_weapon;
    NumberSetting duration;
};
static_assert(sizeof(SprintResetSettings) == 272);
static_assert(offsetof(SprintResetSettings, delay) == 64);
static_assert(offsetof(SprintResetSettings, randomize) == 120);
static_assert(offsetof(SprintResetSettings, wait_for_damage) == 152);
static_assert(offsetof(SprintResetSettings, require_weapon) == 184);
static_assert(offsetof(SprintResetSettings, duration) == 216);

extern "C" {
__declspec(dllexport) std::uint64_t
recovered_sprint_reset_typed_ui(std::uint64_t ui, std::uint64_t layout, SprintResetSettings *,
                                UiDirtyState *, const ChoiceUiEndpoints *);
__declspec(dllexport) void recovered_sprint_reset_typed_settings(SettingsContext *,
                                                                 SprintResetSettings *,
                                                                 const SettingsDependencies *,
                                                                 const ValueSettingsDependencies *);
__declspec(dllexport) std::uint64_t recovered_sprint_reset_label(char *destination,
                                                                 const ChoiceSetting *,
                                                                 const char *const *labels,
                                                                 FormatState *);
}
// END SOURCE native/verified/Sprint_Reset.hpp

#endif // SLINKY_SHARE_313109E60B317702A855

// 0x3afc0 uses the shared choice, number and checkbox controls in this order.
extern "C" __declspec(dllexport) std::uint64_t
recovered_sprint_reset_typed_ui(std::uint64_t ui, std::uint64_t layout,
                                SprintResetSettings *settings, UiDirtyState *dirty,
                                const ChoiceUiEndpoints *endpoints) {
    const auto &standard = endpoints->standard;
    standard.section(ui, layout, "Main");
    recovered_choice_control(layout, ui, &settings->mode, settings->choice_flag, dirty,
                             endpoints->choice);
    recovered_number_control(layout, ui, &settings->delay, dirty, &standard.controls);
    recovered_number_control(layout, ui, &settings->duration, dirty, &standard.controls);
    recovered_checkbox_control(layout, ui, &settings->randomize, dirty, &standard.controls);
    standard.section(ui, layout, "Conditions");
    recovered_checkbox_control(layout, ui, &settings->wait_for_damage, dirty, &standard.controls);
    return recovered_checkbox_control(layout, ui, &settings->require_weapon, dirty,
                                      &standard.controls);
}
// 0x3b070 persists each setting independently of the selected mode.
extern "C" __declspec(dllexport) void
recovered_sprint_reset_typed_settings(SettingsContext *context, SprintResetSettings *settings,
                                      const SettingsDependencies *booleans,
                                      const ValueSettingsDependencies *values) {
    recovered_choice_settings(context, "mode", &settings->mode, values);
    recovered_number_settings(context, "delay", &settings->delay, values);
    recovered_number_settings(context, "duration", &settings->duration, values);
    recovered_boolean_settings(context, "randomize", &settings->randomize, booleans);
    recovered_boolean_settings(context, "wait_for_damage", &settings->wait_for_damage, booleans);
    recovered_boolean_settings(context, "require_weapon", &settings->require_weapon, booleans);
}
// 0x3b110 indexes an independent label table, not the choice control's options.
extern "C" __declspec(dllexport) std::uint64_t
recovered_sprint_reset_label(char *destination, const ChoiceSetting *mode,
                             const char *const *labels, FormatState *format) {
    return recovered_format(format, destination, 32, "%s", labels[mode->current]);
}
// END SOURCE modules/Sprint_Reset/Sprint_Reset.cpp

// BEGIN SOURCE modules/Sprint_Reset/Sprint_Reset_runtime.cpp
#ifndef SLINKY_SHARE_0656B1C9495EA064A9F0
#define SLINKY_SHARE_0656B1C9495EA064A9F0
// BEGIN SOURCE native/verified/Sprint_Reset_runtime.hpp
#include "../runtime/native/verified/Timer.hpp"
#include "../runtime/native/verified/Weapons.hpp"
#include "../runtime/native/verified/module_random_policy.hpp"

struct SprintResetEvent {
    std::uintptr_t event_type;
    TimerGame *game;
};
struct SprintResetState {
    volatile std::uint32_t phase;
    volatile float timer;
    volatile double last_sample_time;
    volatile std::uint8_t have_state;
    std::uint8_t padding[3];
    volatile std::uint32_t sample_count;
    SmoothRandomState delay_random, duration_random, gate_random;
};
struct SprintResetConstants {
    double minimum_elapsed;
    float decrement, one;
    double suppression_window;
    float gate_low, gate_high, two;
    std::uint32_t padding;
    double delay_window;
};
struct SprintResetDependencies {
    std::uint32_t (*counter)(GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*other_counter)(GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*damage)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*options)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*forward_key)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*sneak_key)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*sprint_key)(GameAccessBridge *, std::uintptr_t);
    void (*set_sprinting)(GameAccessBridge *, std::uintptr_t, std::uint8_t);
    std::uint32_t (*physical_key)(GameAccessBridge *, std::uintptr_t);
    void (*set_key)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    // The boundary provider records R8 after each JNI call. 0x3b150 retains its upper DWORD bytes.
    const volatile std::uint32_t *post_call_r8;
    std::uint64_t *frequency_bits;
    const std::uint8_t *frequency_target, *counter_target;
    WeaponCache *weapon_cache;
    const WeaponSettings *weapon_settings;
    const ItemPolicyTable *weapon_policy;
    const WeaponDependencies *weapons;
    RandomState *random;
    const RandomConstants *random_constants;
    const RandomPolicyConstants *policy_constants;
    const double *policy_clock;
};
static_assert(sizeof(SprintResetEvent) == 16);
static_assert(sizeof(SprintResetState) == 72);
static_assert(offsetof(SprintResetState, delay_random) == 24);
static_assert(offsetof(SprintResetState, duration_random) == 40);
static_assert(offsetof(SprintResetState, gate_random) == 56);
static_assert(sizeof(SprintResetConstants) == 48);
static_assert(offsetof(SprintResetConstants, delay_window) == 40);
static_assert(sizeof(SprintResetDependencies) == 176);

extern "C" {
__declspec(dllexport) void recovered_bind_sprint_reset_access(SprintResetDependencies *);
__declspec(dllexport) std::uint32_t recovered_sprint_reset_other_counter(GameAccessBridge *,
                                                                         std::uintptr_t);
__declspec(dllexport) std::uint32_t recovered_sprint_reset_physical_word(GameAccessBridge *,
                                                                         std::uintptr_t);
__declspec(dllexport) void recovered_sprint_reset_action(TimerGame *, const SprintResetSettings *,
                                                         std::uint32_t active_word,
                                                         const SprintResetDependencies *);
__declspec(dllexport) void
recovered_sprint_reset_update(SprintResetEvent *, const SprintResetSettings *, SprintResetState *,
                              const SprintResetConstants *, const SprintResetDependencies *);
}
// END SOURCE native/verified/Sprint_Reset_runtime.hpp

#endif // SLINKY_SHARE_0656B1C9495EA064A9F0

#include "../runtime/native/verified/Sprint.hpp"
#include "../runtime/native/verified/Null_Move.hpp"
#include "../runtime/native/verified/module_access_helpers.hpp"
#include "../runtime/native/verified/module_clock.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>

using Word = std::uintptr_t;
static Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word value;
    std::memcpy(&value, bridge->metadata + offset, sizeof(value));
    return value;
}
template <class Function> static Function slot(const GameAccessBridge *bridge, std::size_t offset) {
    const auto *table = reinterpret_cast<const Word *>(*bridge->environment);
    return reinterpret_cast<Function>(table[offset / sizeof(Word)]);
}
// 0x239d0 retains the low DWORD from the integer getter.
extern "C" __declspec(dllexport) std::uint32_t
recovered_sprint_reset_other_counter(GameAccessBridge *bridge, Word player) {
    using Getter = std::int32_t (*)(Word *, Word, Word);
    return static_cast<std::uint32_t>(
        slot<Getter>(bridge, 0x320)(bridge->environment, player, identifier(bridge, 0x560)));
}
// 0x25760/0x258c0 replace only AL. 0x25490 forwards that complete EAX to its caller.
static std::uint32_t physical_word(GameAccessBridge *bridge, std::uint32_t code, bool mouse) {
    using Query = Word (*)(Word *, Word, Word, std::uint32_t);
    const auto raw =
        slot<Query>(bridge, 0x3a8)(bridge->environment, identifier(bridge, mouse ? 0x88 : 0x60),
                                   identifier(bridge, mouse ? 0xa0 : 0x68), code);
    return (static_cast<std::uint32_t>(raw) & 0xffffff00u) |
           static_cast<std::uint32_t>(static_cast<std::uint8_t>(raw) != 0);
}
extern "C" __declspec(dllexport) std::uint32_t
recovered_sprint_reset_physical_word(GameAccessBridge *bridge, Word key) {
    using Getter = std::int32_t (*)(Word *, Word, Word);
    const auto code = static_cast<std::uint32_t>(
        slot<Getter>(bridge, 0x320)(bridge->environment, key, identifier(bridge, 0x488)));
    if (code & 0x80000000u)
        return physical_word(bridge, code + 100u, true);
    return code <= 256u ? physical_word(bridge, code, false) : 0;
}
static Word options(GameAccessBridge *bridge, Word client) {
    return recovered_access_helper(bridge, 0x22cf0, client, 0, 0);
}
static Word forward_key(GameAccessBridge *bridge, Word options) {
    return recovered_null_move_key(bridge, options, 2);
}
static Word sneak_key(GameAccessBridge *bridge, Word options) {
    return recovered_null_move_key(bridge, options, 7);
}
static void set_key(GameAccessBridge *bridge, Word key, std::uint32_t value) {
    recovered_access_helper(bridge, 0x25460, key, value, 0);
}
extern "C" __declspec(dllexport) void
recovered_bind_sprint_reset_access(SprintResetDependencies *dependencies) {
    WeaponDependencies weapons;
    recovered_bind_weapon_access(&weapons);
    TimerDependencies timer;
    recovered_bind_timer_access(&timer);
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
extern "C" __declspec(dllexport) void
recovered_sprint_reset_action(TimerGame *context, const SprintResetSettings *settings,
                              std::uint32_t active_word,
                              const SprintResetDependencies *dependencies) {
    volatile auto *game = context;
    const auto options = dependencies->options(game->bridge, game->client);
    const auto mode = settings->mode.current;
    const auto key = mode == 2   ? dependencies->sprint_key(game->bridge, options)
                     : mode == 1 ? dependencies->sneak_key(game->bridge, options)
                                 : dependencies->forward_key(game->bridge, options);
    if (settings->mode.current == 2)
        dependencies->set_sprinting(game->bridge, game->player,
                                    static_cast<std::uint8_t>(active_word ^ 1u));
    auto *bridge = game->bridge;
    const auto value = static_cast<std::uint8_t>(active_word)
                           ? (*dependencies->post_call_r8 & 0xffffff00u) |
                                 static_cast<std::uint32_t>(settings->mode.current == 1)
                           : dependencies->physical_key(bridge, key);
    dependencies->set_key(bridge, key, value);
}
static float add(float first, float second) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(first), _mm_set_ss(second)));
}
// 0x3ad10 captures the context, keeps the phase transitions and consumes random draws in order.
extern "C" __declspec(dllexport) void
recovered_sprint_reset_update(SprintResetEvent *event, const SprintResetSettings *settings,
                              SprintResetState *state, const SprintResetConstants *constants,
                              const SprintResetDependencies *dependencies) {
    auto *context = event->game;
    volatile auto *game = context;
    if (game->ready != 1) {
        if (state->phase == 2)
            recovered_sprint_reset_action(context, settings, 0, dependencies);
        state->phase = 0;
        state->have_state = 0;
        state->timer = 0.0f;
        return;
    }
    const auto now = recovered_clock_value(
        dependencies->frequency_bits, dependencies->frequency_target, dependencies->counter_target);
    const auto elapsed =
        _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(now), _mm_set_sd(state->last_sample_time)));
    if (elapsed >= constants->minimum_elapsed) {
        const auto first = dependencies->counter(game->bridge, game->player);
        const auto second = dependencies->other_counter(game->bridge, game->player);
        if (first == second) {
            state->last_sample_time = now;
            state->have_state = 1;
        }
    }
    state->sample_count = state->sample_count + 1u;
    if (dependencies->damage(game->bridge, game->player) == 10)
        state->sample_count = 0;
    auto timer = state->timer;
    if (timer > 0.0f) {
        timer = add(timer, constants->decrement);
        state->timer = timer;
        if (timer > 0.0f) {
            if (state->phase == 2)
                recovered_sprint_reset_action(context, settings, 1, dependencies);
            return;
        }
    }
    const auto phase = state->phase;
    if (phase == 2) {
        recovered_sprint_reset_action(context, settings, 0, dependencies);
        state->phase = 0;
        return;
    }
    if (phase == 1) {
        recovered_sprint_reset_action(context, settings, 1, dependencies);
        state->phase = 2;
        state->have_state = 0;
        auto duration = settings->duration.current;
        if (settings->randomize.current == 1) {
            const auto bounds = recovered_random_bounds(0.0f, constants->one);
            const auto window = constants->suppression_window;
            const auto sample = std::bit_cast<float>(recovered_policy_smooth_bits(
                &state->duration_random, bounds, window, dependencies->random,
                dependencies->policy_clock, dependencies->policy_constants));
            const auto difference = _mm_sub_ss(_mm_set_ss(duration), _mm_set_ss(sample));
            duration = _mm_cvtss_f32(_mm_max_ss(_mm_setzero_ps(), difference));
            if (recovered_policy_gate(
                    &state->gate_random,
                    recovered_random_bounds(constants->gate_low, constants->gate_high), window,
                    dependencies->random, dependencies->policy_clock,
                    dependencies->policy_constants))
                duration =
                    add(duration, recovered_random_interval(
                                      dependencies->random, dependencies->random_constants,
                                      recovered_random_bounds(constants->one, constants->two)));
        }
        state->timer = add(duration, state->timer);
        return;
    }
    auto delay = settings->delay.current;
    if (settings->randomize.current == 1) {
        const auto sample = std::bit_cast<float>(recovered_policy_smooth_bits(
            &state->delay_random, recovered_random_bounds(0.0f, constants->two),
            constants->delay_window, dependencies->random, dependencies->policy_clock,
            dependencies->policy_constants));
        delay = add(delay, sample);
    }
    if (state->have_state != 1 ||
        (settings->wait_for_damage.current == 1 && state->sample_count != 0))
        return;
    if (settings->require_weapon.current == 1 &&
        !recovered_weapon_cached_query(game->bridge, game->player, dependencies->weapon_cache,
                                       dependencies->weapon_settings, dependencies->weapon_policy,
                                       dependencies->weapons))
        return;
    state->timer = add(delay, state->timer);
    state->phase = 1;
}
// END SOURCE modules/Sprint_Reset/Sprint_Reset_runtime.cpp

#ifndef SLINKY_SHARE_90E099DCF55B5814F8A6
#define SLINKY_SHARE_90E099DCF55B5814F8A6
// BEGIN SOURCE modules/Sprint_Reset/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Sprint_Reset/Api.hpp

#endif // SLINKY_SHARE_90E099DCF55B5814F8A6

// Convenient borrowed-state interface

namespace shareable {
class SprintReset {
  public:
    static constexpr const char *kName = "Sprint Reset";
    static constexpr const char *kDescription = "Resets your sprint state to deal more knockback.";
    explicit SprintReset(std::uint8_t *image) : image_(image) {}
    // Mode. Config key: mode.
    ChoiceSetting &mode() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2eff28);
    }
    // Option labels observed in the captured metadata.
    enum class ModeMode : std::uint32_t { Wtap = 0, Sneak = 1, Nostop = 2 };
    // Delay. Config key: delay.
    NumberSetting &delay() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2eff68);
    }
    // Stop duration. Config key: duration.
    NumberSetting &duration() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f0000);
    }
    // Randomize. Config key: randomize.
    BooleanSetting &randomize() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2effa0);
    }
    // Damaged. Config key: wait_for_damage.
    BooleanSetting &wait_for_damage() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2effc0);
    }
    // Holding weapon. Config key: require_weapon.
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2effe0);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_sprint_reset_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_sprint_reset_settings(&context, image_, &dependencies);
    }
    static std::uint64_t typedUi(std::uint64_t ui, std::uint64_t layout,
                                 SprintResetSettings *settings, UiDirtyState *dirty,
                                 const ChoiceUiEndpoints *endpoints) {
        return ::recovered_sprint_reset_typed_ui(ui, layout, settings, dirty, endpoints);
    }
    static void typedSettings(SettingsContext *context, SprintResetSettings *settings,
                              const SettingsDependencies *booleans,
                              const ValueSettingsDependencies *values) {
        ::recovered_sprint_reset_typed_settings(context, settings, booleans, values);
    }
    static std::uint64_t label(char *destination, const ChoiceSetting *mode,
                               const char *const *labels, FormatState *format) {
        return ::recovered_sprint_reset_label(destination, mode, labels, format);
    }
    static std::uint32_t otherCounter(GameAccessBridge *bridge, Word player) {
        return ::recovered_sprint_reset_other_counter(bridge, player);
    }
    static std::uint32_t physicalWord(GameAccessBridge *bridge, Word key) {
        return ::recovered_sprint_reset_physical_word(bridge, key);
    }
    static void bindAccess(SprintResetDependencies *dependencies) {
        ::recovered_bind_sprint_reset_access(dependencies);
    }
    static void action(TimerGame *context, const SprintResetSettings *settings,
                       std::uint32_t active_word, const SprintResetDependencies *dependencies) {
        ::recovered_sprint_reset_action(context, settings, active_word, dependencies);
    }
    static void update(SprintResetEvent *event, const SprintResetSettings *settings,
                       SprintResetState *state, const SprintResetConstants *constants,
                       const SprintResetDependencies *dependencies) {
        ::recovered_sprint_reset_update(event, settings, state, constants, dependencies);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
