#include "Inv_Walk.hpp"
#include <emmintrin.h>

namespace {
using Word = std::uintptr_t;

std::uint32_t delay_ticks(const InvWalkSettings *settings) {
    return static_cast<std::uint32_t>(_mm_cvttss_si64(_mm_set_ss(settings->stop_duration.current)));
}

Word retain_packet(GameAccessBridge *bridge, Word packet) {
    auto *environment = bridge->environment;
    const auto retain = reinterpret_cast<Word (*)(Word *, Word)>(reinterpret_cast<Word *>(*environment)[0xa8 / sizeof(Word)]);
    return retain(environment, packet);
}

void release_packet(Word *environment, Word packet) {
    const auto release = reinterpret_cast<void (*)(Word *, Word)>(reinterpret_cast<Word *>(*environment)[0xb0 / sizeof(Word)]);
    release(environment, packet);
}
}

// 0x39ff0. The environment is captured before interaction access, while its table
// and the queue count are reread for each release.
extern "C" __declspec(dllexport) std::uint8_t recovered_inv_walk_typed_flush(
    GameAccessBridge *bridge, Word client, InvWalkState *state, const InvWalkDependencies *dependencies) {
    if (!state->count) return 0;
    auto *environment = bridge->environment;
    const auto object = dependencies->interaction(bridge, client);
    const auto destination = dependencies->destination(bridge, object);
    const std::uint8_t valid = object != 0 && destination != 0;
    if (state->count) {
        std::uint64_t index = 0;
        do {
            const auto packet = state->packets[index];
            if (valid) dependencies->send(bridge, destination, packet);
            release_packet(environment, packet);
        } while (++index < state->count);
    }
    state->count = 0;
    return valid;
}

// 0x39790.
extern "C" __declspec(dllexport) void recovered_inv_walk_typed_disable(
    TimerEvent *event, Word module_identity, InvWalkState *state, const InvWalkDependencies *dependencies) {
    if (event->enabled != 0 || event->module != module_identity) return;
    auto *game = event->game;
    recovered_inv_walk_typed_flush(game->bridge, game->client, state, dependencies);
}

// 0x39ce0.
extern "C" __declspec(dllexport) void recovered_inv_walk_typed_packet(
    InvWalkPacketEvent *event, const InvWalkSettings *settings, InvWalkState *state,
    const InvWalkDependencies *dependencies) {
    if (settings->mode.current != 1) return;
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
        if (!packet) return;
        if (state->phase == 2) {
            event->cancelled = 1;
            return;
        }
        count = state->count;
        if (!count) return;
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
extern "C" __declspec(dllexport) void recovered_inv_walk_typed_finish(
    TimerEvent *event, InvWalkState *state, const InvWalkDependencies *dependencies) {
    if (state->busy) return;
    auto *game = event->game;
    if (!recovered_inv_walk_typed_flush(game->bridge, game->client, state, dependencies)) return;
    state->last_tick = state->tick;
    if (game->ready != 1) return;
    while (dependencies->drain_first(game->bridge)) {}
    while (dependencies->drain_second(game->bridge)) {}
}

// 0x397c0.
extern "C" __declspec(dllexport) void recovered_inv_walk_typed_update(
    TimerEvent *event, const InvWalkSettings *settings, InvWalkState *state,
    const InvWalkDependencies *dependencies) {
    auto *game = event->game;
    const auto screen = dependencies->screen(game->bridge, game->client);
    const auto options = dependencies->options(game->bridge, game->client);
    const Word keys[] = {
        dependencies->forward_key(game->bridge, options),
        dependencies->back_key(game->bridge, options),
        dependencies->left_key(game->bridge, options),
        dependencies->right_key(game->bridge, options),
        dependencies->jump_key(game->bridge, options)
    };
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
            for (unsigned i = 0; i != 5; ++i) dependencies->set_key(game->bridge, keys[i], pressed[i]);
        }
        state->phase = 0;
        if (!game->ready) return;
        active = 0;
        goto apply;
    }
    {
        const auto moving = static_cast<std::uint8_t>(pressed[0] | pressed[1] | pressed[2] | pressed[3] | pressed[4]);
        if (!dependencies->inventory_screen(game->bridge, screen)) {
            state->phase = 1;
            if (settings->mode.current == 1) {
                block |= moving ^ 1;
                mode = settings->stop_on_click.current;
                std::uint32_t recent = 0;
                if (mode != 2) recent = state->tick - state->last_tick < delay_ticks(settings);
                const std::uint8_t blocked = block | static_cast<std::uint8_t>(recent);
                const auto other = settings->stop_non_inventory.current;
                block = (other != 2) | blocked;
                if (((mode == 0) & blocked) || ((other == 0) & block)) goto zero_keys;
            } else if (stop) goto zero_keys;
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
                if (state->phase == 1) deny = block;
                else {
                    const auto container = dependencies->container(game->bridge, game->player);
                    const auto slots = dependencies->slots(game->bridge, container);
                    unsigned i = 0;
                    for (; i != 4; ++i) if (dependencies->slot(game->bridge, slots, i)) break;
                    if (i == 4) deny = block;
                }
            }
            const std::uint8_t allowed = moving & (deny ^ 1);
            auto phase = state->phase;
            if ((phase != 2) | allowed) {
                if (((state->count == 0) & (phase == 3) & allowed) == 1) {
                    if (settings->stop_on_click.current != 2 && state->tick - state->last_tick < delay_ticks(settings)) goto state_ready;
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
        if (stop) goto zero_keys;
        goto set_keys;
    }
    goto finish;
set_keys:
    for (unsigned i = 0; i != 5; ++i) dependencies->set_key(game->bridge, keys[i], pressed[i]);
    stop = 0;
    goto finish;
zero_keys:
    for (unsigned i = 0; i != 5; ++i) dependencies->set_key(game->bridge, keys[i], 0);
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
