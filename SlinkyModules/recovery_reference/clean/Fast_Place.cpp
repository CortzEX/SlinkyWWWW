#include "Fast_Place.hpp"
#include <cmath>
#include <emmintrin.h>

namespace {
// Preserve the temporary record identities at helper boundaries. Every field
// used below is filled by an operation before it is read.
struct PlacementWorkspace {
    PlacementPosition maximum, extent;
    PlacementBox placed, player, computed, fetched;
    std::uint8_t padding[8];
    PlacementPosition adjacent;
};
static_assert(offsetof(PlacementWorkspace, adjacent) == 248);

bool unordered_or_nonpositive(float value) {
    return std::isnan(value) || value <= 0.0f;
}
}

// 0x2fbc0. Check the timer before touching the event, retain the use-key handle,
// and reload the bridge/player/client fields after each external operation.
extern "C" __declspec(dllexport) void recovered_fast_place_typed_update(
    TimerEvent *event, const FastPlaceSettings *settings, FastPlaceState *state,
    const FastPlaceConstants *constants, const FastPlaceDependencies *access) {
    if (!unordered_or_nonpositive(state->timer)) {
        state->timer = state->timer + constants->tick_step;
        if (!std::isnan(state->timer) && state->timer > 0.0f) return;
    }
    auto *game = event->game;
    if (game->ready != 1) return;
    const auto options = access->options(game->bridge, game->client);
    const auto key = access->use_key(game->bridge, options);
    const auto pressed = access->physical_key(game->bridge, key);
    const auto previous = state->previously_pressed;
    state->previously_pressed = pressed;
    if (!pressed) {
        state->activation_countdown = _mm_cvttss_si32(_mm_set_ss(settings->activation_delay.current));
        return;
    }
    if (state->activation_countdown >= 1) {
        state->activation_countdown = state->activation_countdown - 1;
        return;
    }
    if (access->queued_presses(game->bridge, key) > 0) return;
    if (std::isnan(state->timer) || state->timer > 0.0f) return;

    const double rate = constants->rate_scale;
    const double extent = constants->block_extent;
    const float lower = constants->gate_lower, upper = constants->gate_upper;
    auto phase = static_cast<std::uint8_t>(previous ^ 1);
    do {
        state->timer = static_cast<float>(static_cast<double>(state->timer) +
            rate / static_cast<double>(settings->maximum_cps.current));
        if (!(phase & 1)) {
            auto *bridge = game->bridge;
            auto item = access->held_item(bridge, game->player);
            if (access->block_item(bridge, item)) {
                const auto hit = access->mouse_over(game->bridge, game->client);
                bool use_gate = !hit;
                if (!use_gate) use_gate = access->hit_type(game->bridge, hit) != 1;
                bool skip_geometry = false;
                if (!use_gate) {
                    item = access->held_item(game->bridge, game->player);
                    if (item) skip_geometry = access->item_type(game->bridge, item) == 0x41;
                }
                if (!use_gate && !skip_geometry) {
                    PlacementWorkspace work;
                    access->adjacent_position(&work.adjacent, game->bridge, hit, access->context);
                    access->position(&work.extent, extent, extent, extent);
                    work.computed.minimum = work.adjacent;
                    access->add(&work.maximum, &work.computed.minimum, &work.extent);
                    work.fetched.minimum = work.adjacent;
                    access->box(&work.computed, &work.fetched.minimum, &work.maximum);
                    bridge = game->bridge;
                    const auto player = game->player;
                    const auto player_box = access->player_box(bridge, player);
                    access->read_box(&work.fetched, bridge, player_box);
                    work.placed = work.computed;
                    work.player = work.fetched;
                    if (access->intersects(&work.placed, &work.player)) use_gate = true;
                }
                if (use_gate) {
                    const auto bounds = access->random_bounds(lower, upper);
                    if (!access->placement_allowed(&state->placement_gate, bounds, rate, access->context)) goto advance;
                }
                access->increment_presses(game->bridge, key);
            }
        }
advance:
        phase = 0;
    } while (!std::isnan(state->timer) && state->timer <= 0.0f);
}
