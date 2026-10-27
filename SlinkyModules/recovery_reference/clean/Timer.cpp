#include "Timer.hpp"
#include "module_access_helpers.hpp"
#include <cstring>

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

static Word object_field(GameAccessBridge *bridge, Word object, std::size_t offset) {
    using Getter = Word (*)(Word *, Word, Word);
    return slot<Getter>(bridge, 0x2f8)(bridge->environment, object, identifier(bridge, offset));
}

static std::uint32_t integer_field(GameAccessBridge *bridge, Word object, std::size_t offset) {
    using Getter = std::uint32_t (*)(Word *, Word, Word);
    return slot<Getter>(bridge, 0x320)(bridge->environment, object, identifier(bridge, offset));
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
    using Getter = std::uint8_t (*)(Word *, Word, Word);
    return slot<Getter>(bridge, 0x300)(bridge->environment, player, identifier(bridge, 0x2f0)) != 0;
}

// 0x23550 reloads bridge pointers after each getter, retaining the player argument.
static void velocity(TimerVelocity *output, GameAccessBridge *bridge, Word player) {
    using Getter = double (*)(Word *, Word, Word);
    const auto x = slot<Getter>(bridge, 0x338)(bridge->environment, player, identifier(bridge, 0x2b8));
    const auto y = slot<Getter>(bridge, 0x338)(bridge->environment, player, identifier(bridge, 0x2c0));
    const auto z = slot<Getter>(bridge, 0x338)(bridge->environment, player, identifier(bridge, 0x2c8));
    *output = {x, y, z}; // 0x93b0
}

// 0x239f0.
static std::uint32_t damage(GameAccessBridge *bridge, Word player) {
    return integer_field(bridge, player, 0x558);
}

// 0x259c0 moves the callback's XMM2 value to the JNI setter's XMM3 argument.
static void set_speed(GameAccessBridge *bridge, Word timer_object, float speed) {
    using Setter = void (*)(Word *, Word, Word, float);
    slot<Setter>(bridge, 0x378)(bridge->environment, timer_object, identifier(bridge, 0x390), speed);
}

extern "C" __declspec(dllexport) void recovered_bind_timer_access(TimerDependencies *dependencies) {
    *dependencies = {timer, mouse, on_ground, velocity, damage, set_speed};
}

// 0x328f0 accepts unordered vertical velocity alongside negative values.
extern "C" __declspec(dllexport) void recovered_timer_update(
    TimerEvent *event, const TimerSettings *settings, const TimerDependencies *dependencies) {
    auto *game = event->game;
    const auto timer_object = dependencies->timer(game->bridge, game->client);
    auto speed = 1.0f;
    if (settings->require_mouse.current == 1 && !dependencies->mouse(game)) goto apply;
    if (settings->require_falling.current == 1) {
        if (dependencies->on_ground(game->bridge, game->player)) goto apply;
        TimerVelocity motion;
        dependencies->velocity(&motion, game->bridge, game->player);
        if (motion.y >= 0.0) goto apply;
    }
    if (settings->require_damage.current == 1 &&
        (game->ready != 1 || !dependencies->damage(game->bridge, game->player))) goto apply;
    speed = settings->speed.current;
apply:
    dependencies->set_speed(game->bridge, timer_object, speed);
}

// 0x329b0. The caller supplies its registered Timer descriptor's identity.
extern "C" __declspec(dllexport) void recovered_timer_lifecycle(
    TimerEvent *event, Word module_identity, const TimerDependencies *dependencies) {
    if (event->module != module_identity || event->enabled != 0) return;
    auto *game = event->game;
    const auto timer_object = dependencies->timer(game->bridge, game->client);
    dependencies->set_speed(game->bridge, timer_object, 1.0f);
}

// 0x32a00 puts the falling control after damage.
extern "C" __declspec(dllexport) void recovered_timer_typed_ui(
    std::uint64_t ui, std::uint64_t layout, TimerSettings *settings,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, &settings->speed);
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, &settings->require_mouse);
    dependencies->checkbox(layout, ui, &settings->require_damage);
    dependencies->checkbox(layout, ui, &settings->require_falling);
}

// 0x32a80 uses the same number/mouse/damage/falling record order.
extern "C" __declspec(dllexport) void recovered_timer_typed_settings(
    SettingsContext *context, TimerSettings *settings, const SettingsDependencies *booleans,
    const ValueSettingsDependencies *numbers) {
    recovered_number_settings(context, "speed", &settings->speed, numbers);
    recovered_boolean_settings(context, "require_mouse", &settings->require_mouse, booleans);
    recovered_boolean_settings(context, "require_damage", &settings->require_damage, booleans);
    recovered_boolean_settings(context, "require_falling", &settings->require_falling, booleans);
}
