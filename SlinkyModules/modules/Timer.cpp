// Timer

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Timer.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Timer.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Timer: lib_win settings 0x32a80.
// UI 0x32a00.
static constexpr UiStep ui_steps_Surface_Timer[] = {
    {UiControl::section, "Main", 0},          {UiControl::number, nullptr, 0x2ebc20},
    {UiControl::section, "Conditions", 0},    {UiControl::checkbox, nullptr, 0x2ebc58},
    {UiControl::checkbox, nullptr, 0x2ebc98}, {UiControl::checkbox, nullptr, 0x2ebc78},
};
static constexpr SettingsStep settings_steps_Surface_Timer[] = {
    {SettingsControl::number, "speed", 0x2ebc20},
    {SettingsControl::boolean, "require_mouse", 0x2ebc58},
    {SettingsControl::boolean, "require_damage", 0x2ebc98},
    {SettingsControl::boolean, "require_falling", 0x2ebc78},
};
static constexpr ModuleSurface surface_Surface_Timer{
    ui_steps_Surface_Timer, std::size(ui_steps_Surface_Timer), settings_steps_Surface_Timer,
    std::size(settings_steps_Surface_Timer)};

extern "C" __declspec(dllexport) void
recovered_timer_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                   const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Timer, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_timer_settings(SettingsContext *context, std::uint8_t *image,
                         const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Timer, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Timer.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Timer/Timer.cpp
#ifndef SLINKY_SHARE_24067D8DCA488C7C5604
#define SLINKY_SHARE_24067D8DCA488C7C5604
// BEGIN SOURCE native/verified/Timer.hpp
#include "../runtime/native/verified/module_game_access.hpp"
#include "../runtime/native/verified/module_surface.hpp"

struct TimerGame {
    GameAccessBridge *bridge;
    std::uintptr_t reserved[2];
    std::uintptr_t client;
    std::uintptr_t world;
    std::uintptr_t player;
    const std::uint8_t *input;
    std::uintptr_t reserved2;
    std::uint8_t ready;
    std::uint8_t padding[7];
};

struct TimerEvent {
    std::uintptr_t event_type;
    TimerGame *game;
    std::uintptr_t module;
    std::uint8_t enabled;
    std::uint8_t padding[7];
};

struct TimerSettings {
    NumberSetting speed;
    BooleanSetting require_mouse;
    BooleanSetting require_falling;
    BooleanSetting require_damage;
};

struct TimerVelocity {
    double x, y, z;
};

struct TimerDependencies {
    std::uintptr_t (*timer)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*mouse)(TimerGame *);
    std::uint8_t (*on_ground)(GameAccessBridge *, std::uintptr_t);
    void (*velocity)(TimerVelocity *, GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*damage)(GameAccessBridge *, std::uintptr_t);
    void (*set_speed)(GameAccessBridge *, std::uintptr_t, float);
};

static_assert(sizeof(TimerGame) == 72);
static_assert(offsetof(TimerGame, input) == 48);
static_assert(offsetof(TimerGame, ready) == 64);
static_assert(sizeof(TimerEvent) == 32);
static_assert(offsetof(TimerEvent, module) == 16);
static_assert(offsetof(TimerEvent, enabled) == 24);
static_assert(sizeof(TimerSettings) == 152);
static_assert(offsetof(TimerSettings, speed) == 0);
static_assert(offsetof(TimerSettings, require_mouse) == 56);
static_assert(offsetof(TimerSettings, require_falling) == 88);
static_assert(offsetof(TimerSettings, require_damage) == 120);
static_assert(sizeof(TimerVelocity) == 24);
static_assert(sizeof(TimerDependencies) == 48);

extern "C" {
__declspec(dllexport) void recovered_timer_update(TimerEvent *, const TimerSettings *,
                                                  const TimerDependencies *);
__declspec(dllexport) void recovered_timer_lifecycle(TimerEvent *, std::uintptr_t module_identity,
                                                     const TimerDependencies *);
__declspec(dllexport) void recovered_bind_timer_access(TimerDependencies *);
__declspec(dllexport) void recovered_timer_typed_ui(std::uint64_t ui, std::uint64_t layout,
                                                    TimerSettings *, const SurfaceUiDependencies *);
__declspec(dllexport) void recovered_timer_typed_settings(SettingsContext *, TimerSettings *,
                                                          const SettingsDependencies *,
                                                          const ValueSettingsDependencies *);
}
// END SOURCE native/verified/Timer.hpp

#endif // SLINKY_SHARE_24067D8DCA488C7C5604

#include "../runtime/native/verified/module_access_helpers.hpp"
#include <cstring>

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

static Word object_field(GameAccessBridge *bridge, Word object, std::size_t offset) {
    using Getter_Timer = Word (*)(Word *, Word, Word);
    return slot<Getter_Timer>(bridge, 0x2f8)(bridge->environment, object,
                                             identifier(bridge, offset));
}

static std::uint32_t integer_field(GameAccessBridge *bridge, Word object, std::size_t offset) {
    using Getter_Timer = std::uint32_t (*)(Word *, Word, Word);
    return slot<Getter_Timer>(bridge, 0x320)(bridge->environment, object,
                                             identifier(bridge, offset));
}

// 0x22c70.
static Word timer(GameAccessBridge *bridge, Word client) {
    return object_field(bridge, client, 0x198);
}

// 0x29080 reloads the game bridge between helpers, and input after the key-code query.
static std::uint8_t mouse(TimerGame *game) {
    const auto options = recovered_access_helper(game->bridge, 0x22cf0, game->client, 0, 0);
    auto *bridge = game->bridge;
    const auto array = object_field(bridge, options, 0x3b8); // 0x25270
    using ArrayElement = Word (*)(Word *, Word, std::int32_t);
    const auto key = slot<ArrayElement>(bridge, 0x568)(bridge->environment, array, 0);
    const auto code = integer_field(game->bridge, key, 0x488); // 0x25410
    return game->input[1 + (code == 0xffffff9du)] != 0;
}

// 0x23780 normalizes only the returned low byte.
static std::uint8_t on_ground(GameAccessBridge *bridge, Word player) {
    using Getter_Timer = std::uint8_t (*)(Word *, Word, Word);
    return slot<Getter_Timer>(bridge, 0x300)(bridge->environment, player,
                                             identifier(bridge, 0x2f0)) != 0;
}

// 0x23550 reloads bridge pointers after each getter, retaining the player argument.
static void velocity(TimerVelocity *output, GameAccessBridge *bridge, Word player) {
    using Getter_Timer = double (*)(Word *, Word, Word);
    const auto x =
        slot<Getter_Timer>(bridge, 0x338)(bridge->environment, player, identifier(bridge, 0x2b8));
    const auto y =
        slot<Getter_Timer>(bridge, 0x338)(bridge->environment, player, identifier(bridge, 0x2c0));
    const auto z =
        slot<Getter_Timer>(bridge, 0x338)(bridge->environment, player, identifier(bridge, 0x2c8));
    *output = {x, y, z}; // 0x93b0
}

// 0x239f0.
static std::uint32_t damage(GameAccessBridge *bridge, Word player) {
    return integer_field(bridge, player, 0x558);
}

// 0x259c0 moves the callback's XMM2 value to the JNI setter's XMM3 argument.
static void set_speed(GameAccessBridge *bridge, Word timer_object, float speed) {
    using Setter = void (*)(Word *, Word, Word, float);
    slot<Setter>(bridge, 0x378)(bridge->environment, timer_object, identifier(bridge, 0x390),
                                speed);
}

extern "C" __declspec(dllexport) void recovered_bind_timer_access(TimerDependencies *dependencies) {
    *dependencies = {timer, mouse, on_ground, velocity, damage, set_speed};
}

// 0x328f0 accepts unordered vertical velocity alongside negative values.
extern "C" __declspec(dllexport) void
recovered_timer_update(TimerEvent *event, const TimerSettings *settings,
                       const TimerDependencies *dependencies) {
    auto *game = event->game;
    const auto timer_object = dependencies->timer(game->bridge, game->client);
    auto speed = 1.0f;
    if (settings->require_mouse.current == 1 && !dependencies->mouse(game))
        goto apply;
    if (settings->require_falling.current == 1) {
        if (dependencies->on_ground(game->bridge, game->player))
            goto apply;
        TimerVelocity motion;
        dependencies->velocity(&motion, game->bridge, game->player);
        if (motion.y >= 0.0)
            goto apply;
    }
    if (settings->require_damage.current == 1 &&
        (game->ready != 1 || !dependencies->damage(game->bridge, game->player)))
        goto apply;
    speed = settings->speed.current;
apply:
    dependencies->set_speed(game->bridge, timer_object, speed);
}

// 0x329b0. The caller supplies its registered Timer descriptor's identity.
extern "C" __declspec(dllexport) void
recovered_timer_lifecycle(TimerEvent *event, Word module_identity,
                          const TimerDependencies *dependencies) {
    if (event->module != module_identity || event->enabled != 0)
        return;
    auto *game = event->game;
    const auto timer_object = dependencies->timer(game->bridge, game->client);
    dependencies->set_speed(game->bridge, timer_object, 1.0f);
}

// 0x32a00 puts the falling control after damage.
extern "C" __declspec(dllexport) void
recovered_timer_typed_ui(std::uint64_t ui, std::uint64_t layout, TimerSettings *settings,
                         const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, &settings->speed);
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, &settings->require_mouse);
    dependencies->checkbox(layout, ui, &settings->require_damage);
    dependencies->checkbox(layout, ui, &settings->require_falling);
}

// 0x32a80 uses the same number/mouse/damage/falling record order.
extern "C" __declspec(dllexport) void
recovered_timer_typed_settings(SettingsContext *context, TimerSettings *settings,
                               const SettingsDependencies *booleans,
                               const ValueSettingsDependencies *numbers) {
    recovered_number_settings(context, "speed", &settings->speed, numbers);
    recovered_boolean_settings(context, "require_mouse", &settings->require_mouse, booleans);
    recovered_boolean_settings(context, "require_damage", &settings->require_damage, booleans);
    recovered_boolean_settings(context, "require_falling", &settings->require_falling, booleans);
}
// END SOURCE modules/Timer/Timer.cpp

#ifndef SLINKY_SHARE_3922437E3833475DA236
#define SLINKY_SHARE_3922437E3833475DA236
// BEGIN SOURCE modules/Timer/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Timer/Api.hpp

#endif // SLINKY_SHARE_3922437E3833475DA236

// Convenient borrowed-state interface

namespace shareable {
class Timer {
  public:
    static constexpr const char *kName = "Timer";
    static constexpr const char *kDescription = "Modifies the speed the game runs at.";
    explicit Timer(std::uint8_t *image) : image_(image) {}
    // Speed. Config key: speed.
    NumberSetting &speed() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ebc20);
    }
    // Mouse pressed. Config key: require_mouse.
    BooleanSetting &require_mouse() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ebc58);
    }
    // Damage. Config key: require_damage.
    BooleanSetting &require_damage() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ebc98);
    }
    // Falling. Config key: require_falling.
    BooleanSetting &require_falling() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ebc78);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_timer_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_timer_settings(&context, image_, &dependencies);
    }
    static void bindAccess(TimerDependencies *dependencies) {
        ::recovered_bind_timer_access(dependencies);
    }
    static void update(TimerEvent *event, const TimerSettings *settings,
                       const TimerDependencies *dependencies) {
        ::recovered_timer_update(event, settings, dependencies);
    }
    static void lifecycle(TimerEvent *event, Word module_identity,
                          const TimerDependencies *dependencies) {
        ::recovered_timer_lifecycle(event, module_identity, dependencies);
    }
    static void typedUi(std::uint64_t ui, std::uint64_t layout, TimerSettings *settings,
                        const SurfaceUiDependencies *dependencies) {
        ::recovered_timer_typed_ui(ui, layout, settings, dependencies);
    }
    static void typedSettings(SettingsContext *context, TimerSettings *settings,
                              const SettingsDependencies *booleans,
                              const ValueSettingsDependencies *numbers) {
        ::recovered_timer_typed_settings(context, settings, booleans, numbers);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
