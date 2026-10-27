// Keep Sprint

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Keep_Sprint.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Keep_Sprint.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Keep Sprint: lib_win settings 0x3a310.
// UI 0x3a290.
static constexpr UiStep ui_steps_Surface_Keep_Sprint[] = {
    {UiControl::section, "Main", 0},        {UiControl::number, nullptr, 0x2ef910},
    {UiControl::number, nullptr, 0x2ef948}, {UiControl::checkbox, nullptr, 0x2ef9a0},
    {UiControl::section, "Conditions", 0},  {UiControl::checkbox, nullptr, 0x2ef980},
};
static constexpr SettingsStep settings_steps_Surface_Keep_Sprint[] = {
    {SettingsControl::number, "chance", 0x2ef910},
    {SettingsControl::number, "motion_mult", 0x2ef948},
    {SettingsControl::boolean, "allow_reduce", 0x2ef9a0},
    {SettingsControl::boolean, "require_on_ground", 0x2ef980},
};
static constexpr ModuleSurface surface_Surface_Keep_Sprint{
    ui_steps_Surface_Keep_Sprint, std::size(ui_steps_Surface_Keep_Sprint),
    settings_steps_Surface_Keep_Sprint, std::size(settings_steps_Surface_Keep_Sprint)};

extern "C" __declspec(dllexport) void
recovered_keep_sprint_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                         const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Keep_Sprint, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_keep_sprint_settings(SettingsContext *context, std::uint8_t *image,
                               const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Keep_Sprint, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Keep_Sprint.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Keep_Sprint/Keep_Sprint.cpp
#ifndef SLINKY_SHARE_D3B353E8DB2E5E4DA332
#define SLINKY_SHARE_D3B353E8DB2E5E4DA332
// BEGIN SOURCE native/verified/Keep_Sprint.hpp
#include "../runtime/native/verified/Timer.hpp"
#include "../runtime/native/verified/module_random.hpp"

struct KeepSprintStatus {
    std::uint8_t reserved[24];
    std::uint8_t reducing;
};

struct KeepSprintGame {
    GameAccessBridge *bridge;
    std::uintptr_t reserved[4];
    std::uintptr_t player;
    std::uintptr_t reserved2;
    const KeepSprintStatus *status;
    std::uint8_t ready;
    std::uint8_t padding[7];
};

struct KeepSprintEvent {
    std::uintptr_t event_type;
    KeepSprintGame *game;
    std::uint8_t active;
    std::uint8_t padding[7];
};

struct KeepSprintSettings {
    NumberSetting chance;
    NumberSetting motion_multiplier;
    BooleanSetting require_on_ground;
    BooleanSetting allow_reduce;
};

struct KeepSprintState {
    TimerVelocity movement;
    std::uint8_t armed, pending;
    std::uint8_t padding[6];
};

struct KeepSprintDependencies {
    std::uint8_t (*sprinting)(GameAccessBridge *, std::uintptr_t);
    void (*velocity)(TimerVelocity *, GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*on_ground)(GameAccessBridge *, std::uintptr_t);
    std::int32_t (*counter)(GameAccessBridge *, std::uintptr_t);
    std::int32_t (*last_attacker_time)(GameAccessBridge *, std::uintptr_t);
    void (*set_velocity)(GameAccessBridge *, std::uintptr_t, const TimerVelocity *);
    void (*set_sprinting)(GameAccessBridge *, std::uintptr_t, std::uint8_t);
};

static_assert(sizeof(KeepSprintGame) == 72);
static_assert(offsetof(KeepSprintGame, player) == 40);
static_assert(offsetof(KeepSprintGame, status) == 56);
static_assert(offsetof(KeepSprintGame, ready) == 64);
static_assert(offsetof(KeepSprintStatus, reducing) == 24);
static_assert(sizeof(KeepSprintEvent) == 24);
static_assert(offsetof(KeepSprintEvent, active) == 16);
static_assert(sizeof(KeepSprintSettings) == 176);
static_assert(offsetof(KeepSprintSettings, motion_multiplier) == 56);
static_assert(offsetof(KeepSprintSettings, require_on_ground) == 112);
static_assert(offsetof(KeepSprintSettings, allow_reduce) == 144);
static_assert(sizeof(KeepSprintState) == 32);
static_assert(offsetof(KeepSprintState, armed) == 24);
static_assert(offsetof(KeepSprintState, pending) == 25);
static_assert(sizeof(KeepSprintDependencies) == 56);

extern "C" {
__declspec(dllexport) void recovered_keep_sprint_sample(KeepSprintEvent *,
                                                        const KeepSprintSettings *,
                                                        KeepSprintState *, RandomState *,
                                                        const RandomConstants *,
                                                        const KeepSprintDependencies *);
__declspec(dllexport) void recovered_keep_sprint_apply(KeepSprintEvent *,
                                                       const KeepSprintSettings *,
                                                       KeepSprintState *,
                                                       const KeepSprintDependencies *);
__declspec(dllexport) void recovered_keep_sprint_finish(KeepSprintEvent *, KeepSprintState *,
                                                        const KeepSprintDependencies *);
__declspec(dllexport) void recovered_bind_keep_sprint_access(KeepSprintDependencies *);
__declspec(dllexport) std::int32_t recovered_keep_sprint_counter(GameAccessBridge *,
                                                                 std::uintptr_t);
__declspec(dllexport) void recovered_keep_sprint_set_velocity(GameAccessBridge *, std::uintptr_t,
                                                              const TimerVelocity *);
__declspec(dllexport) void recovered_keep_sprint_typed_ui(std::uint64_t ui, std::uint64_t layout,
                                                          KeepSprintSettings *,
                                                          const SurfaceUiDependencies *);
__declspec(dllexport) void recovered_keep_sprint_typed_settings(SettingsContext *,
                                                                KeepSprintSettings *,
                                                                const SettingsDependencies *,
                                                                const ValueSettingsDependencies *);
}
// END SOURCE native/verified/Keep_Sprint.hpp

#endif // SLINKY_SHARE_D3B353E8DB2E5E4DA332

#include "../runtime/native/verified/Sprint.hpp"
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

// 0x23760 compares only the low 32 bits of the JNI result.
extern "C" __declspec(dllexport) std::int32_t
recovered_keep_sprint_counter(GameAccessBridge *bridge, Word player) {
    using Getter = std::int32_t (*)(Word *, Word, Word);
    return slot<Getter>(bridge, 0x320)(bridge->environment, player, identifier(bridge, 0x2d8));
}

// 0x235f0 reloads the bridge and each input lane after every setter call.
extern "C" __declspec(dllexport) void
recovered_keep_sprint_set_velocity(GameAccessBridge *bridge, Word player,
                                   const TimerVelocity *velocity) {
    using Setter = void (*)(Word *, Word, Word, double);
    slot<Setter>(bridge, 0x380)(bridge->environment, player, identifier(bridge, 0x2b8),
                                velocity->x);
    slot<Setter>(bridge, 0x380)(bridge->environment, player, identifier(bridge, 0x2c0),
                                velocity->y);
    slot<Setter>(bridge, 0x380)(bridge->environment, player, identifier(bridge, 0x2c8),
                                velocity->z);
}

extern "C" __declspec(dllexport) void
recovered_bind_keep_sprint_access(KeepSprintDependencies *dependencies) {
    TimerDependencies timer;
    recovered_bind_timer_access(&timer);
    *dependencies = {recovered_game_sprinting,
                     timer.velocity,
                     timer.on_ground,
                     recovered_keep_sprint_counter,
                     recovered_game_last_attacker_time,
                     recovered_keep_sprint_set_velocity,
                     recovered_sprint_set_player};
}

// 0x3a0f0. An inactive event retains both state flags.
extern "C" __declspec(dllexport) void
recovered_keep_sprint_sample(KeepSprintEvent *event, const KeepSprintSettings *settings,
                             KeepSprintState *state, RandomState *random,
                             const RandomConstants *constants,
                             const KeepSprintDependencies *dependencies) {
    if (event->active != 1)
        return;
    auto *game = event->game;
    if (game->ready == 1 && dependencies->sprinting(game->bridge, game->player) &&
        static_cast<std::uint8_t>(
            recovered_random_chance(random, constants, settings->chance.current))) {
        TimerVelocity movement;
        dependencies->velocity(&movement, game->bridge, game->player);
        state->movement = movement;
        state->armed = 1;
    } else {
        state->armed = 0;
    }
}

// 0x3a170. The X and Z multiplies have opposite operand order.
extern "C" __declspec(dllexport) void
recovered_keep_sprint_apply(KeepSprintEvent *event, const KeepSprintSettings *settings,
                            KeepSprintState *state, const KeepSprintDependencies *dependencies) {
    if (state->armed != 1 || event->active != 1)
        return;
    auto *game = event->game;
    if (!game->player)
        return;
    if (settings->require_on_ground.current == 1 &&
        !dependencies->on_ground(game->bridge, game->player))
        return;
    const auto counter = dependencies->counter(game->bridge, game->player);
    if (counter != dependencies->last_attacker_time(game->bridge, game->player))
        return;
    if (settings->allow_reduce.current == 1 && game->status->reducing)
        return;
    const auto factor = _mm_set_sd(static_cast<double>(settings->motion_multiplier.current));
    state->movement.x = _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(state->movement.x), factor));
    state->movement.z = _mm_cvtsd_f64(_mm_mul_sd(factor, _mm_set_sd(state->movement.z)));
    const auto movement = state->movement;
    dependencies->set_velocity(game->bridge, game->player, &movement);
    state->pending = 1;
}

// 0x3a260 clears pending before inspecting the current game/player.
extern "C" __declspec(dllexport) void
recovered_keep_sprint_finish(KeepSprintEvent *event, KeepSprintState *state,
                             const KeepSprintDependencies *dependencies) {
    if (state->pending != 1)
        return;
    state->pending = 0;
    auto *game = event->game;
    if (game->player)
        dependencies->set_sprinting(game->bridge, game->player, 1);
}

// 0x3a290.
extern "C" __declspec(dllexport) void
recovered_keep_sprint_typed_ui(std::uint64_t ui, std::uint64_t layout, KeepSprintSettings *settings,
                               const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, &settings->chance);
    dependencies->number(layout, ui, &settings->motion_multiplier);
    dependencies->checkbox(layout, ui, &settings->allow_reduce);
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, &settings->require_on_ground);
}

// 0x3a310.
extern "C" __declspec(dllexport) void
recovered_keep_sprint_typed_settings(SettingsContext *context, KeepSprintSettings *settings,
                                     const SettingsDependencies *booleans,
                                     const ValueSettingsDependencies *numbers) {
    recovered_number_settings(context, "chance", &settings->chance, numbers);
    recovered_number_settings(context, "motion_mult", &settings->motion_multiplier, numbers);
    recovered_boolean_settings(context, "allow_reduce", &settings->allow_reduce, booleans);
    recovered_boolean_settings(context, "require_on_ground", &settings->require_on_ground,
                               booleans);
}
// END SOURCE modules/Keep_Sprint/Keep_Sprint.cpp

#ifndef SLINKY_SHARE_A6C340EF680234D1B986
#define SLINKY_SHARE_A6C340EF680234D1B986
// BEGIN SOURCE modules/Keep_Sprint/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Keep_Sprint/Api.hpp

#endif // SLINKY_SHARE_A6C340EF680234D1B986

// Convenient borrowed-state interface

namespace shareable {
class KeepSprint {
  public:
    static constexpr const char *kName = "Keep Sprint";
    static constexpr const char *kDescription = "Keeps your sprint speed when attacking players.";
    explicit KeepSprint(std::uint8_t *image) : image_(image) {}
    // Chance. Config key: chance.
    NumberSetting &chance() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ef910);
    }
    // Retained speed. Config key: motion_mult.
    NumberSetting &motion_mult() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ef948);
    }
    // Allow reducing. Config key: allow_reduce.
    BooleanSetting &allow_reduce() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ef9a0);
    }
    // On ground. Config key: require_on_ground.
    BooleanSetting &require_on_ground() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ef980);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_keep_sprint_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_keep_sprint_settings(&context, image_, &dependencies);
    }
    static std::int32_t counter(GameAccessBridge *bridge, Word player) {
        return ::recovered_keep_sprint_counter(bridge, player);
    }
    static void setVelocity(GameAccessBridge *bridge, Word player, const TimerVelocity *velocity) {
        ::recovered_keep_sprint_set_velocity(bridge, player, velocity);
    }
    static void bindAccess(KeepSprintDependencies *dependencies) {
        ::recovered_bind_keep_sprint_access(dependencies);
    }
    static void sample(KeepSprintEvent *event, const KeepSprintSettings *settings,
                       KeepSprintState *state, RandomState *random,
                       const RandomConstants *constants,
                       const KeepSprintDependencies *dependencies) {
        ::recovered_keep_sprint_sample(event, settings, state, random, constants, dependencies);
    }
    static void apply(KeepSprintEvent *event, const KeepSprintSettings *settings,
                      KeepSprintState *state, const KeepSprintDependencies *dependencies) {
        ::recovered_keep_sprint_apply(event, settings, state, dependencies);
    }
    static void finish(KeepSprintEvent *event, KeepSprintState *state,
                       const KeepSprintDependencies *dependencies) {
        ::recovered_keep_sprint_finish(event, state, dependencies);
    }
    static void typedUi(std::uint64_t ui, std::uint64_t layout, KeepSprintSettings *settings,
                        const SurfaceUiDependencies *dependencies) {
        ::recovered_keep_sprint_typed_ui(ui, layout, settings, dependencies);
    }
    static void typedSettings(SettingsContext *context, KeepSprintSettings *settings,
                              const SettingsDependencies *booleans,
                              const ValueSettingsDependencies *numbers) {
        ::recovered_keep_sprint_typed_settings(context, settings, booleans, numbers);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
