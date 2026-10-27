// Inv Walk

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Inv_Walk.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Inv_Walk.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Inv Walk: lib_win settings 0x39f40.
static constexpr SettingsStep settings_steps_Surface_Inv_Walk[] = {
    {SettingsControl::choice, "mode", 0x2ef5f0},
    {SettingsControl::choice, "stop_on_click", 0x2ef648},
    {SettingsControl::number, "stop_duration", 0x2ef688},
    {SettingsControl::choice, "stop_non_inv", 0x2ef6c0},
};
static constexpr ModuleSurface surface_Surface_Inv_Walk{nullptr, 0, settings_steps_Surface_Inv_Walk,
                                                        std::size(settings_steps_Surface_Inv_Walk)};

extern "C" __declspec(dllexport) void
recovered_inv_walk_settings(SettingsContext *context, std::uint8_t *image,
                            const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Inv_Walk, context, image, *dependencies);
}

// Inv Walk: lib_win runtime UI 0x39ea0.
extern "C" __declspec(dllexport) void
recovered_inv_walk_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                      const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, image + 0x2ef5f0);
    if (read_surface_value<std::uint32_t>(image, 0x2ef620) == 0) {
        return;
    }
    dependencies->choice(layout, ui, image + 0x2ef648);
    if (read_surface_value<std::uint32_t>(image, 0x2ef678) != 2) {
        dependencies->number(layout, ui, image + 0x2ef688);
    }
    dependencies->section(ui, layout, "Other containers");
    dependencies->choice(layout, ui, image + 0x2ef6c0);
}
// END SOURCE native/verified/surfaces/Surface_Inv_Walk.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Inv_Walk/Inv_Walk.cpp
#ifndef SLINKY_SHARE_1883DBDCA3761360450F
#define SLINKY_SHARE_1883DBDCA3761360450F
// BEGIN SOURCE native/verified/Inv_Walk.hpp
#include "../runtime/native/verified/Timer.hpp"
#include "../runtime/native/verified/module_choice_ui.hpp"
#include "../runtime/native/verified/module_format.hpp"

struct InvWalkSettings {
    ChoiceSetting mode;
    std::uint8_t mode_flag;
    std::uint8_t mode_padding[7];
    const char *stop_options[3];
    ChoiceSetting stop_on_click;
    std::uint8_t stop_on_click_flag;
    std::uint8_t stop_on_click_padding[7];
    NumberSetting stop_duration;
    ChoiceSetting stop_non_inventory;
    std::uint8_t stop_non_inventory_flag;
    std::uint8_t padding[7];
};

struct InvWalkState {
    volatile std::uintptr_t packets[32];
    volatile std::uint64_t count;
    volatile std::uint8_t stopped;
    std::uint8_t padding[3];
    volatile std::uint32_t tick;
    volatile std::uint32_t phase;
    volatile std::uint32_t last_tick;
    volatile std::uint8_t busy;
    std::uint8_t padding2[7];
};

struct InvWalkPacketEvent {
    std::uintptr_t event_type;
    GameAccessBridge *bridge;
    std::uintptr_t destination;
    std::uintptr_t packet;
    std::uint8_t cancelled;
    std::uint8_t padding[7];
};

struct InvWalkDependencies {
    std::uintptr_t (*screen)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*options)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*forward_key)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*back_key)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*left_key)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*right_key)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*jump_key)(GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*physical_key)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*inventory_screen)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*inventory)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*interaction)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*destination)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*held_item)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*container)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*slots)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*slot)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    std::uintptr_t (*close_action)(GameAccessBridge *, std::uint32_t);
    std::uintptr_t (*action_type)(GameAccessBridge *);
    std::uintptr_t (*open_action)(GameAccessBridge *, std::uintptr_t);
    void (*send)(GameAccessBridge *, std::uintptr_t, std::uintptr_t);
    void (*set_key)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    void (*set_sprinting)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    std::uintptr_t (*sprint_key)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*action_packet)(GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*packet_action_type)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*click_packet)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*other_packet)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*drain_first)(GameAccessBridge *);
    std::uint8_t (*drain_second)(GameAccessBridge *);
};

static_assert(sizeof(InvWalkSettings) == 272);
static_assert(offsetof(InvWalkSettings, mode_flag) == 56);
static_assert(offsetof(InvWalkSettings, stop_options) == 64);
static_assert(offsetof(InvWalkSettings, stop_on_click_flag) == 144);
static_assert(offsetof(InvWalkSettings, stop_non_inventory_flag) == 264);
static_assert(offsetof(InvWalkSettings, stop_on_click) == 88);
static_assert(offsetof(InvWalkSettings, stop_duration) == 152);
static_assert(offsetof(InvWalkSettings, stop_non_inventory) == 208);
static_assert(sizeof(InvWalkState) == 288);
static_assert(offsetof(InvWalkState, count) == 256);
static_assert(offsetof(InvWalkState, stopped) == 264);
static_assert(offsetof(InvWalkState, tick) == 268);
static_assert(offsetof(InvWalkState, phase) == 272);
static_assert(offsetof(InvWalkState, last_tick) == 276);
static_assert(offsetof(InvWalkState, busy) == 280);
static_assert(sizeof(InvWalkPacketEvent) == 40);
static_assert(offsetof(InvWalkPacketEvent, cancelled) == 32);
static_assert(sizeof(InvWalkDependencies) == 232);

extern "C" {
__declspec(dllexport) void recovered_bind_inv_walk_access(InvWalkDependencies *);
__declspec(dllexport) std::uint64_t recovered_inv_walk_typed_ui(std::uint64_t ui,
                                                                std::uint64_t layout,
                                                                InvWalkSettings *, UiDirtyState *,
                                                                const ChoiceUiEndpoints *);
__declspec(dllexport) void recovered_inv_walk_typed_settings(SettingsContext *, InvWalkSettings *,
                                                             const ValueSettingsDependencies *);
__declspec(dllexport) std::uint64_t
recovered_inv_walk_label(char *, const ChoiceSetting *, const char *const *labels, FormatState *);
__declspec(dllexport) void recovered_inv_walk_typed_update(TimerEvent *, const InvWalkSettings *,
                                                           InvWalkState *,
                                                           const InvWalkDependencies *);
__declspec(dllexport) void recovered_inv_walk_typed_disable(TimerEvent *,
                                                            std::uintptr_t module_identity,
                                                            InvWalkState *,
                                                            const InvWalkDependencies *);
__declspec(dllexport) void recovered_inv_walk_typed_packet(InvWalkPacketEvent *,
                                                           const InvWalkSettings *, InvWalkState *,
                                                           const InvWalkDependencies *);
__declspec(dllexport) void recovered_inv_walk_typed_finish(TimerEvent *, InvWalkState *,
                                                           const InvWalkDependencies *);
__declspec(dllexport) std::uint8_t recovered_inv_walk_typed_flush(GameAccessBridge *,
                                                                  std::uintptr_t client,
                                                                  InvWalkState *,
                                                                  const InvWalkDependencies *);
}
// END SOURCE native/verified/Inv_Walk.hpp

#endif // SLINKY_SHARE_1883DBDCA3761360450F

#include <emmintrin.h>

namespace {
using Word = std::uintptr_t;

std::uint32_t delay_ticks(const InvWalkSettings *settings) {
    return static_cast<std::uint32_t>(_mm_cvttss_si64(_mm_set_ss(settings->stop_duration.current)));
}

Word retain_packet(GameAccessBridge *bridge, Word packet) {
    auto *environment = bridge->environment;
    const auto retain = reinterpret_cast<Word (*)(Word *, Word)>(
        reinterpret_cast<Word *>(*environment)[0xa8 / sizeof(Word)]);
    return retain(environment, packet);
}

void release_packet(Word *environment, Word packet) {
    const auto release = reinterpret_cast<void (*)(Word *, Word)>(
        reinterpret_cast<Word *>(*environment)[0xb0 / sizeof(Word)]);
    release(environment, packet);
}
} // namespace

// 0x39ff0. The environment is captured before interaction access, while its table
// and the queue count are reread for each release.
extern "C" __declspec(dllexport) std::uint8_t
recovered_inv_walk_typed_flush(GameAccessBridge *bridge, Word client, InvWalkState *state,
                               const InvWalkDependencies *dependencies) {
    if (!state->count)
        return 0;
    auto *environment = bridge->environment;
    const auto object = dependencies->interaction(bridge, client);
    const auto destination = dependencies->destination(bridge, object);
    const std::uint8_t valid = object != 0 && destination != 0;
    if (state->count) {
        std::uint64_t index = 0;
        do {
            const auto packet = state->packets[index];
            if (valid)
                dependencies->send(bridge, destination, packet);
            release_packet(environment, packet);
        } while (++index < state->count);
    }
    state->count = 0;
    return valid;
}

// 0x39790.
extern "C" __declspec(dllexport) void
recovered_inv_walk_typed_disable(TimerEvent *event, Word module_identity, InvWalkState *state,
                                 const InvWalkDependencies *dependencies) {
    if (event->enabled != 0 || event->module != module_identity)
        return;
    auto *game = event->game;
    recovered_inv_walk_typed_flush(game->bridge, game->client, state, dependencies);
}

// 0x39ce0.
extern "C" __declspec(dllexport) void
recovered_inv_walk_typed_packet(InvWalkPacketEvent *event, const InvWalkSettings *settings,
                                InvWalkState *state, const InvWalkDependencies *dependencies) {
    if (settings->mode.current != 1)
        return;
    auto packet = dependencies->action_packet(event->bridge, event->packet);
    auto *bridge = event->bridge;
    if (packet) {
        if (dependencies->packet_action_type(bridge, packet) == 2) {
            event->cancelled = 1;
            state->phase = 2;
        }
        return;
    }
    packet = dependencies->click_packet(bridge, event->packet);
    std::uint64_t count;
    if (packet) {
        if (state->phase == 2) {
            const auto type = dependencies->action_type(event->bridge);
            const auto action = dependencies->open_action(event->bridge, type);
            dependencies->send(event->bridge, event->destination, action);
            state->phase = 3;
            state->busy = 1;
            count = state->count;
        } else {
            count = state->count;
            if (!((static_cast<std::uint8_t>(count != 0) | state->busy) & 1)) {
                state->last_tick = state->tick;
                return;
            }
        }
    } else {
        packet = dependencies->other_packet(event->bridge, event->packet);
        if (!packet)
            return;
        if (state->phase == 2) {
            event->cancelled = 1;
            return;
        }
        count = state->count;
        if (!count)
            return;
    }
    if (count != 32) {
        const auto retained = retain_packet(event->bridge, event->packet);
        if (retained) {
            count = state->count;
            state->packets[count] = retained;
            state->count = count + 1;
        }
    }
    event->cancelled = 1;
}

// 0x39e30.
extern "C" __declspec(dllexport) void
recovered_inv_walk_typed_finish(TimerEvent *event, InvWalkState *state,
                                const InvWalkDependencies *dependencies) {
    if (state->busy)
        return;
    auto *game = event->game;
    if (!recovered_inv_walk_typed_flush(game->bridge, game->client, state, dependencies))
        return;
    state->last_tick = state->tick;
    if (game->ready != 1)
        return;
    while (dependencies->drain_first(game->bridge)) {
    }
    while (dependencies->drain_second(game->bridge)) {
    }
}

// 0x397c0.
extern "C" __declspec(dllexport) void
recovered_inv_walk_typed_update(TimerEvent *event, const InvWalkSettings *settings,
                                InvWalkState *state, const InvWalkDependencies *dependencies) {
    auto *game = event->game;
    const auto screen = dependencies->screen(game->bridge, game->client);
    const auto options = dependencies->options(game->bridge, game->client);
    const Word keys[] = {dependencies->forward_key(game->bridge, options),
                         dependencies->back_key(game->bridge, options),
                         dependencies->left_key(game->bridge, options),
                         dependencies->right_key(game->bridge, options),
                         dependencies->jump_key(game->bridge, options)};
    std::uint32_t pressed[5];
    for (unsigned i = 0; i != 5; ++i) {
        const auto value = dependencies->physical_key(game->bridge, keys[i]);
        pressed[i] = i < 2 ? value : static_cast<std::uint8_t>(value);
    }
    auto mode = settings->stop_on_click.current;
    std::uint8_t block = settings->mode.current == 1 && mode != 2 && state->count != 0;
    std::uint8_t stop = (mode == 0) & block;
    std::uint8_t active;
    state->tick = state->tick + 1;
    if (!screen) {
        if (state->phase) {
            for (unsigned i = 0; i != 5; ++i)
                dependencies->set_key(game->bridge, keys[i], pressed[i]);
        }
        state->phase = 0;
        if (!game->ready)
            return;
        active = 0;
        goto apply;
    }
    {
        const auto moving = static_cast<std::uint8_t>(pressed[0] | pressed[1] | pressed[2] |
                                                      pressed[3] | pressed[4]);
        if (!dependencies->inventory_screen(game->bridge, screen)) {
            state->phase = 1;
            if (settings->mode.current == 1) {
                block |= moving ^ 1;
                mode = settings->stop_on_click.current;
                std::uint32_t recent = 0;
                if (mode != 2)
                    recent = state->tick - state->last_tick < delay_ticks(settings);
                const std::uint8_t blocked = block | static_cast<std::uint8_t>(recent);
                const auto other = settings->stop_non_inventory.current;
                block = (other != 2) | blocked;
                if (((mode == 0) & blocked) || ((other == 0) & block))
                    goto zero_keys;
            } else if (stop)
                goto zero_keys;
            goto set_keys;
        }
        std::uint8_t deny;
        if (settings->mode.current != 1) {
            state->phase = 3;
            active = 1;
            deny = 0;
        } else {
            const auto inventory = dependencies->inventory(game->bridge, game->player);
            const auto interaction = dependencies->interaction(game->bridge, game->client);
            const auto destination = dependencies->destination(game->bridge, interaction);
            const auto held = dependencies->held_item(game->bridge, inventory);
            deny = 1;
            if (!held) {
                if (state->phase == 1)
                    deny = block;
                else {
                    const auto container = dependencies->container(game->bridge, game->player);
                    const auto slots = dependencies->slots(game->bridge, container);
                    unsigned i = 0;
                    for (; i != 4; ++i)
                        if (dependencies->slot(game->bridge, slots, i))
                            break;
                    if (i == 4)
                        deny = block;
                }
            }
            const std::uint8_t allowed = moving & (deny ^ 1);
            auto phase = state->phase;
            if ((phase != 2) | allowed) {
                if (((state->count == 0) & (phase == 3) & allowed) == 1) {
                    if (settings->stop_on_click.current != 2 &&
                        state->tick - state->last_tick < delay_ticks(settings))
                        goto state_ready;
                    const auto action = dependencies->close_action(game->bridge, 0);
                    dependencies->send(game->bridge, destination, action);
                    phase = 2;
                    state->phase = phase;
                }
            } else {
                const auto type = dependencies->action_type(game->bridge);
                const auto action = dependencies->open_action(game->bridge, type);
                dependencies->send(game->bridge, destination, action);
                phase = 3;
                state->phase = phase;
            }
        state_ready:
            deny |= phase == 3;
            active = phase != 0;
        }
        mode = settings->stop_on_click.current;
        block |= (mode != 2) & deny;
        stop = (mode == 0) & block;
    }
apply:
    if ((active | state->stopped | stop) & 1) {
        if (stop)
            goto zero_keys;
        goto set_keys;
    }
    goto finish;
set_keys:
    for (unsigned i = 0; i != 5; ++i)
        dependencies->set_key(game->bridge, keys[i], pressed[i]);
    stop = 0;
    goto finish;
zero_keys:
    for (unsigned i = 0; i != 5; ++i)
        dependencies->set_key(game->bridge, keys[i], 0);
    stop = 1;
finish:
    if (block) {
        dependencies->set_sprinting(game->bridge, game->player, 0);
        auto *bridge = game->bridge;
        const auto key = dependencies->sprint_key(bridge, options);
        dependencies->set_key(bridge, key, 0);
    }
    state->stopped = stop;
    state->busy = 0;
}
// END SOURCE modules/Inv_Walk/Inv_Walk.cpp

// BEGIN SOURCE modules/Inv_Walk/Inv_Walk_access.cpp
#include "../runtime/native/verified/Null_Move.hpp"
#include "../runtime/native/verified/Sprint_Reset_runtime.hpp"
#include "../runtime/native/verified/module_access_helpers.hpp"
#include <cstring>

namespace {
using Word = std::uintptr_t;
using ObjectGetter = Word (*)(Word *, Word, Word);
using Predicate = std::uint8_t (*)(Word *, Word, Word);
using ObjectMethod = Word (*)(Word *, Word, Word, ...);

Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word value;
    std::memcpy(&value, bridge->metadata + offset, sizeof(value));
    return value;
}
template <class Function> Function slot(const GameAccessBridge *bridge, std::size_t offset) {
    return reinterpret_cast<Function>(
        reinterpret_cast<const Word *>(*bridge->environment)[offset / sizeof(Word)]);
}
template <std::size_t Offset> Word object_field(GameAccessBridge *bridge, Word object) {
    return slot<ObjectGetter>(bridge, 0x2f8)(bridge->environment, object,
                                             identifier(bridge, Offset));
}
template <std::uint32_t Index> Word key(GameAccessBridge *bridge, Word options) {
    return recovered_null_move_key(bridge, options, Index);
}
Word options(GameAccessBridge *bridge, Word client) {
    return recovered_access_helper(bridge, 0x22cf0, client, 0, 0);
}
void set_key(GameAccessBridge *bridge, Word key, std::uint32_t value) {
    recovered_access_helper(bridge, 0x25460, key, value, 0);
}
void set_sprinting(GameAccessBridge *bridge, Word player, std::uint32_t value) {
    recovered_sprint_set_player(bridge, player, static_cast<std::uint8_t>(value));
}
// 0x22d10: unlike a field getter, interaction uses CallObjectMethod.
Word interaction(GameAccessBridge *bridge, Word client) {
    return slot<ObjectMethod>(bridge, 0x110)(bridge->environment, client,
                                             identifier(bridge, 0x158));
}
std::uint8_t inventory_screen(GameAccessBridge *bridge, Word screen) {
    return slot<Predicate>(bridge, 0x100)(bridge->environment, screen, identifier(bridge, 0x8a0)) !=
           0;
}
// 0x26ec0 / 0x26f00 / 0x26ff0 retain the caller's packet when AL is nonzero.
template <std::size_t Class> Word packet(GameAccessBridge *bridge, Word object) {
    return slot<Predicate>(bridge, 0x100)(bridge->environment, object, identifier(bridge, Class))
               ? object
               : 0;
}
// 0x26fb0 reloads the bridge for the enum ordinal after fetching the enum object.
std::uint32_t packet_action_type(GameAccessBridge *bridge, Word packet) {
    const auto type = object_field<0xc68>(bridge, packet);
    return static_cast<std::uint32_t>(recovered_access_helper(bridge, 0x271a0, type, 0, 0));
}
// 0x26f40.
Word action_type(GameAccessBridge *bridge) {
    return slot<ObjectGetter>(bridge, 0x488)(bridge->environment, identifier(bridge, 0xc78),
                                             identifier(bridge, 0xc80));
}
// 0x26f70 / 0x27030. The latter forwards only the low DWORD.
Word open_action(GameAccessBridge *bridge, Word type) {
    return slot<ObjectMethod>(bridge, 0xe0)(bridge->environment, identifier(bridge, 0xc60),
                                            identifier(bridge, 0xc70), type);
}
Word close_action(GameAccessBridge *bridge, std::uint32_t value) {
    return slot<ObjectMethod>(bridge, 0xe0)(bridge->environment, identifier(bridge, 0xc88),
                                            identifier(bridge, 0xc90), value);
}
// 0x25f80 selects the overload before the array call, then rereads metadata,
// environment and the JNI target. The overload selection survives those changes.
void send(GameAccessBridge *bridge, Word destination, Word packet) {
    using Method = void (*)(Word *, Word, Word, ...);
    if (identifier(bridge, 0x6f8)) {
        using Array = Word (*)(Word *, std::uint32_t, Word, Word);
        const auto array =
            slot<Array>(bridge, 0x560)(bridge->environment, 0, identifier(bridge, 0xc58), 0);
        slot<Method>(bridge, 0x1e8)(bridge->environment, destination, identifier(bridge, 0x6f8),
                                    packet, array);
    } else {
        slot<Method>(bridge, 0x1e8)(bridge->environment, destination, identifier(bridge, 0x700),
                                    packet);
    }
}
// 0x25900 / 0x257a0 have three JNI arguments; physical-key queries have four.
template <std::size_t Class, std::size_t Method> std::uint8_t drain(GameAccessBridge *bridge) {
    return slot<Predicate>(bridge, 0x3a8)(bridge->environment, identifier(bridge, Class),
                                          identifier(bridge, Method)) != 0;
}
} // namespace

extern "C" __declspec(dllexport) void
recovered_bind_inv_walk_access(InvWalkDependencies *dependencies) {
    WeaponDependencies weapons;
    recovered_bind_weapon_access(&weapons);
    *dependencies = {recovered_sprint_screen,
                     options,
                     key<4>,
                     key<3>,
                     key<5>,
                     key<2>,
                     key<6>,
                     recovered_sprint_reset_physical_word,
                     inventory_screen,
                     recovered_game_inventory,
                     interaction,
                     object_field<0x698>,
                     object_field<0x5e0>,
                     object_field<0x5b0>,
                     object_field<0xca0>,
                     weapons.item_at,
                     close_action,
                     action_type,
                     open_action,
                     send,
                     set_key,
                     set_sprinting,
                     recovered_sprint_key,
                     packet<0xc60>,
                     packet_action_type,
                     packet<0xbe8>,
                     packet<0xc88>,
                     drain<0x88, 0xa8>,
                     drain<0x60, 0x70>};
}
// END SOURCE modules/Inv_Walk/Inv_Walk_access.cpp

// BEGIN SOURCE modules/Inv_Walk/Inv_Walk_local.cpp
// 0x39ea0 reloads both choices after rendering before choosing the next control.
extern "C" __declspec(dllexport) std::uint64_t
recovered_inv_walk_typed_ui(std::uint64_t ui, std::uint64_t layout, InvWalkSettings *settings,
                            UiDirtyState *dirty, const ChoiceUiEndpoints *endpoints) {
    endpoints->standard.section(ui, layout, "Main");
    const auto first = recovered_choice_control(layout, ui, &settings->mode, settings->mode_flag,
                                                dirty, endpoints->choice);
    if (!settings->mode.current)
        return first;
    recovered_choice_control(layout, ui, &settings->stop_on_click, settings->stop_on_click_flag,
                             dirty, endpoints->choice);
    if (settings->stop_on_click.current != 2)
        recovered_number_control(layout, ui, &settings->stop_duration, dirty,
                                 &endpoints->standard.controls);
    endpoints->standard.section(ui, layout, "Other containers");
    return recovered_choice_control(layout, ui, &settings->stop_non_inventory,
                                    settings->stop_non_inventory_flag, dirty, endpoints->choice);
}

// 0x39f40 persists all choices regardless of which controls are visible.
extern "C" __declspec(dllexport) void
recovered_inv_walk_typed_settings(SettingsContext *context, InvWalkSettings *settings,
                                  const ValueSettingsDependencies *dependencies) {
    recovered_choice_settings(context, "mode", &settings->mode, dependencies);
    recovered_choice_settings(context, "stop_on_click", &settings->stop_on_click, dependencies);
    recovered_number_settings(context, "stop_duration", &settings->stop_duration, dependencies);
    recovered_choice_settings(context, "stop_non_inv", &settings->stop_non_inventory, dependencies);
}

// 0x39fb0 indexes a separate Vanilla/Spoof label table.
extern "C" __declspec(dllexport) std::uint64_t recovered_inv_walk_label(char *destination,
                                                                        const ChoiceSetting *mode,
                                                                        const char *const *labels,
                                                                        FormatState *format) {
    return recovered_format(format, destination, 32, "%s", labels[mode->current]);
}
// END SOURCE modules/Inv_Walk/Inv_Walk_local.cpp

// BEGIN SOURCE modules/Inv_Walk/Inv_Walk_module.cpp
#ifndef SLINKY_SHARE_5D5B46C020ED6872E910
#define SLINKY_SHARE_5D5B46C020ED6872E910
// BEGIN SOURCE native/verified/Inv_Walk_module.hpp
// Restores the captured settings baseline into host-owned storage. This does not
// establish the original constructor's behavior before the capture.
extern "C" __declspec(dllexport) void recovered_inv_walk_initialize_settings(InvWalkSettings *);

class InvWalkModule {
  public:
    enum class Mode : std::uint32_t { Vanilla, Spoof };
    enum class StopMode : std::uint32_t { Full, Partial, No };
    static constexpr const char *name = "Inv Walk";
    static constexpr const char *description = "Allows moving in inventory.";

    InvWalkSettings settings{};
    InvWalkState state{};
    InvWalkDependencies access;

    // Identity is the host's module token used by the disable event.
    InvWalkModule(std::uintptr_t identity, const InvWalkDependencies &dependencies)
        : access(dependencies), identity_(identity) {
        recovered_inv_walk_initialize_settings(&settings);
    }
    InvWalkModule(const InvWalkModule &) = delete;
    InvWalkModule &operator=(const InvWalkModule &) = delete;

    void update(TimerEvent &event) {
        recovered_inv_walk_typed_update(&event, &settings, &state, &access);
    }
    void disable(TimerEvent &event) {
        recovered_inv_walk_typed_disable(&event, identity_, &state, &access);
    }
    void packet(InvWalkPacketEvent &event) {
        recovered_inv_walk_typed_packet(&event, &settings, &state, &access);
    }
    void finish(TimerEvent &event) {
        recovered_inv_walk_typed_finish(&event, &state, &access);
    }
    std::uint8_t flush(GameAccessBridge &bridge, std::uintptr_t client) {
        return recovered_inv_walk_typed_flush(&bridge, client, &state, &access);
    }
    std::uint64_t render(std::uint64_t ui, std::uint64_t layout, UiDirtyState &dirty,
                         const ChoiceUiEndpoints &endpoints) {
        return recovered_inv_walk_typed_ui(ui, layout, &settings, &dirty, &endpoints);
    }
    void configure(SettingsContext &context, const ValueSettingsDependencies &endpoints) {
        recovered_inv_walk_typed_settings(&context, &settings, &endpoints);
    }
    std::uint64_t status(char (&destination)[32], FormatState &format) const {
        static constexpr const char *labels[] = {"Vanilla", "Spoof"};
        return recovered_inv_walk_label(destination, &settings.mode, labels, &format);
    }

  private:
    std::uintptr_t identity_;
};
// END SOURCE native/verified/Inv_Walk_module.hpp

#endif // SLINKY_SHARE_5D5B46C020ED6872E910

#include <cstring>

namespace {
constexpr const char *modes[] = {"Vanilla", "Spoof"};

template <class Value> void metadata(std::uint8_t *bytes, std::size_t offset, Value value) {
    std::memcpy(bytes + offset, &value, sizeof(value));
}

void choice(ChoiceSetting &setting, const char *label, std::uint32_t count,
            const char *const *options) {
    metadata(setting.metadata, 24, label);
    setting.count = count;
    setting.options = options;
}
} // namespace

// The checkpoint records contain these values. Text and option pointers refer
// to this source's static storage; no captured addresses are used.
extern "C" __declspec(dllexport) void
recovered_inv_walk_initialize_settings(InvWalkSettings *settings) {
    *settings = {};
    settings->stop_options[0] = "Full";
    settings->stop_options[1] = "Partial";
    settings->stop_options[2] = "No";
    choice(settings->mode, "Mode", 2, modes);
    choice(settings->stop_on_click, "Stop on interact", 3, settings->stop_options);
    choice(settings->stop_non_inventory, "Always stop", 3, settings->stop_options);
    auto &duration = settings->stop_duration;
    metadata(duration.metadata, 16, "Stop duration");
    metadata(duration.metadata, 24, "%.0f ms");
    metadata(duration.metadata, 32, 1.0f);
    metadata(duration.metadata, 36, 50.0f);
    duration.minimum = 1.0f;
    duration.maximum = 20.0f;
    duration.current = 2.0f;
}
// END SOURCE modules/Inv_Walk/Inv_Walk_module.cpp

#ifndef SLINKY_SHARE_5B694CC885DE37A18038
#define SLINKY_SHARE_5B694CC885DE37A18038
// BEGIN SOURCE modules/Inv_Walk/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Inv_Walk/Api.hpp

#endif // SLINKY_SHARE_5B694CC885DE37A18038

// Convenient borrowed-state interface

namespace shareable {
using InvWalk = ::InvWalkModule;
}
