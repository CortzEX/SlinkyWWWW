#include "Sprint.hpp"
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

// 0x22c90 reloads both bridge pointers after fetching the screen object.
extern "C" __declspec(dllexport) Word recovered_sprint_screen(GameAccessBridge *bridge, Word client) {
    using ObjectField = Word (*)(Word *, Word, Word);
    using Predicate = std::uint8_t (*)(Word *, Word, Word);
    const auto screen = slot<ObjectField>(bridge, 0x2f8)(bridge->environment, client, identifier(bridge, 0x1c8));
    return slot<Predicate>(bridge, 0x100)(bridge->environment, screen, identifier(bridge, 0x4d8)) ? screen : 0;
}

// 0x25210 reads the version after the array getter returns. Zero selects 17; nonzero selects 8.
extern "C" __declspec(dllexport) Word recovered_sprint_key(GameAccessBridge *bridge, Word options) {
    using ObjectField = Word (*)(Word *, Word, Word);
    using ArrayElement = Word (*)(Word *, Word, std::int32_t);
    const auto array = slot<ObjectField>(bridge, 0x2f8)(bridge->environment, options, identifier(bridge, 0x3b8));
    std::uint32_t version;
    std::memcpy(&version, bridge->metadata, sizeof(version));
    return slot<ArrayElement>(bridge, 0x568)(bridge->environment, array, version == 0 ? 17 : 8);
}

// 0x236c0 promotes the Boolean argument to int for the variadic JNI method.
extern "C" __declspec(dllexport) void recovered_sprint_set_player(
    GameAccessBridge *bridge, Word player, std::uint8_t value) {
    using VoidMethod = void (*)(Word *, Word, Word, ...);
    slot<VoidMethod>(bridge, 0x1e8)(bridge->environment, player, identifier(bridge, 0x230), static_cast<int>(value));
}

static Word options(GameAccessBridge *bridge, Word client) {
    return recovered_access_helper(bridge, 0x22cf0, client, 0, 0);
}

static void set_key(GameAccessBridge *bridge, Word key, std::uint8_t value) {
    recovered_access_helper(bridge, 0x25460, key, value, 0);
}

extern "C" __declspec(dllexport) void recovered_bind_sprint_access(SprintDependencies *dependencies) {
    dependencies->screen = recovered_sprint_screen;
    dependencies->options = options;
    dependencies->sprint_key = recovered_sprint_key;
    dependencies->set_key = set_key;
    dependencies->ready = recovered_game_sprinting;
    dependencies->using_item = recovered_game_using_item;
    dependencies->set_sprinting = recovered_sprint_set_player;
}

// 0x35d80. When a player exists but active is zero, last_state is retained.
extern "C" __declspec(dllexport) void recovered_sprint_update(
    SprintEvent *event, const SprintSettings *settings, std::uint8_t *last_state,
    const SprintDependencies *dependencies) {
    auto *game = event->game;
    const auto screen = dependencies->screen(game->bridge, game->client);
    const auto active = static_cast<std::uint8_t>(((screen == 0) | settings->while_in_gui.current) & 1);
    const auto configuration = dependencies->options(game->bridge, game->client);
    const auto key = dependencies->sprint_key(game->bridge, configuration);
    dependencies->set_key(game->bridge, key, active);
    if (game->player) {
        if (!active) {
            if (*last_state == 1) dependencies->set_sprinting(game->bridge, game->player, 0);
            return;
        }
        if (dependencies->ready(game->bridge, game->player))
            dependencies->set_sprinting(game->bridge, game->player, 1);
    }
    *last_state = active;
}

// 0x35e30 converts the scale to double for multiplication, then rounds back to float.
extern "C" __declspec(dllexport) void recovered_sprint_movement(
    SprintEvent *event, const SprintSettings *settings, const SprintDependencies *dependencies) {
    auto *game = event->game;
    if (event->forward == 0.0f && event->sideways == 0.0f) return;
    const auto using_item = dependencies->using_item(game->bridge, game->player);
    if (using_item && !settings->while_using_item.current) return;
    const auto forward = event->forward;
    if (forward < 0.0f) {
        if (!settings->while_backwards.current) return;
    } else if (forward == 0.0f && event->sideways != 0.0f) {
        if (!settings->while_sideways.current) return;
    } else if (!using_item) return;
    event->scale = static_cast<float>(static_cast<double>(event->scale) * 1.3);
    dependencies->set_sprinting(game->bridge, game->player, 1);
}

// 0x35ef0. Control order follows the original, with GUI last.
extern "C" __declspec(dllexport) void recovered_sprint_typed_ui(
    std::uint64_t ui, std::uint64_t layout, SprintSettings *settings,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Allow while");
    dependencies->checkbox(layout, ui, &settings->while_using_item);
    dependencies->checkbox(layout, ui, &settings->while_backwards);
    dependencies->checkbox(layout, ui, &settings->while_sideways);
    dependencies->checkbox(layout, ui, &settings->while_in_gui);
}

// 0x35f60 uses the same record order and shared Boolean settings helper.
extern "C" __declspec(dllexport) void recovered_sprint_typed_settings(
    SettingsContext *context, SprintSettings *settings, const SettingsDependencies *dependencies) {
    recovered_boolean_settings(context, "while_using_item", &settings->while_using_item, dependencies);
    recovered_boolean_settings(context, "while_backwards", &settings->while_backwards, dependencies);
    recovered_boolean_settings(context, "while_sideways", &settings->while_sideways, dependencies);
    recovered_boolean_settings(context, "while_in_gui", &settings->while_in_gui, dependencies);
}
