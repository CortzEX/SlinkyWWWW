#include "fake_lag.h"

#include <stddef.h>
#include <emmintrin.h>
#include <intrin.h>

static_assert(offsetof(fake_lag_event0, payload) == 8, "event 0 payload offset");
static_assert(offsetof(fake_lag_event0_payload, required_object) == 0x20, "event 0 gate offset");
static_assert(offsetof(fake_lag_event0_payload, target) == 0x28, "event 0 target offset");
static_assert(offsetof(fake_lag_event0_payload, in_game) == 0x40, "event 0 in-game offset");
static_assert(offsetof(fake_lag_packet_event, object_a) == 8, "packet object A offset");
static_assert(offsetof(fake_lag_packet_event, object_b) == 0x10, "packet object B offset");
static_assert(offsetof(fake_lag_packet_event, remaining) == 0x18, "packet delay offset");
static_assert(offsetof(fake_lag_packet_event, result) == 0x24, "packet result offset");

static int32_t cvttss_i32(float value)
{
    return _mm_cvttss_si32(_mm_set_ss(value));
}

static int32_t add_i32_and_float_truncate(int32_t value, float increment)
{
    __m128 converted = _mm_cvtsi32_ss(_mm_setzero_ps(), value);
    __m128 sum = _mm_add_ss(converted, _mm_set_ss(increment));
    return _mm_cvttss_si32(sum);
}

/* Callback body RVA 0x32b30 (registry event 0). */
__declspec(dllexport) uint32_t recovered_fake_lag_update(
    fake_lag_state *state, fake_lag_config *config,
    fake_lag_event0 *event, const fake_lag_dependencies *dependencies, void *user)
{
    uint32_t result;
    int32_t current;
    int32_t sampled_state;
    uint8_t send;

    current = (int32_t)state->pulse_timer;
    if (current > 0) state->pulse_timer = (uint32_t)(current - 1);

    /* MOVZX loads the config byte, then XCHG replaces only the shared byte. */
    (void)_InterlockedExchange8((volatile char *)&state->shared_byte,
                                (char)config->inbound_token);

    if (config->advance_mode == 1) {
        current = (int32_t)state->inbound_value;
        if (current < 1) {
            state->inbound_value = (uint32_t)add_i32_and_float_truncate(
                current, config->inbound_delta);
        } else {
            state->inbound_value = (uint32_t)current - 0x32u;
        }
        (void)_InterlockedExchange8((volatile char *)&state->inbound_block,
                                    (char)(current >= 1 && (uint32_t)current < 0x33u));

        current = (int32_t)state->outbound_value;
        if (current < 1) {
            state->outbound_value = (uint32_t)add_i32_and_float_truncate(
                current, config->outbound_delta);
        } else {
            state->outbound_value = (uint32_t)current - 0x32u;
        }
        (void)_InterlockedExchange8((volatile char *)&state->outbound_block,
                                    (char)(current >= 1 && (uint32_t)current < 0x33u));
    }

    /* The native code captures the payload pointer after the counter phases. */
    volatile fake_lag_event0_payload *payload = event->payload;
    if (payload->required_object == 0 ||
        (config->require_ingame == 1 && payload->in_game == 0)) {
        state->pulse_timer = 0;
    } else {
        sampled_state = dependencies->sample_state(
            payload->object, payload->target, user);
        if (config->require_weapon == 1 &&
            dependencies->weapon_allowed(payload->object, payload->target, user) == 0) {
            state->pulse_timer = 0;
            send = 0;
        } else {
            /* These globals are loaded after the helper boundary in the original. */
            send = (uint8_t)((config->require_attack ^ 1u) |
                             (state->pulse_timer != 0));
        }
        if ((uint32_t)sampled_state != state->last_state) state->pulse_timer = 0x14;
        state->last_state = (uint32_t)sampled_state;

        if (send != 0) {
            int32_t converted_inbound = cvttss_i32(config->inbound_delta);
            uint16_t previous_outbound;
            (void)_InterlockedExchange16((volatile short *)&state->inbound_amount,
                                         (short)converted_inbound);
            {
                int32_t converted_outbound = cvttss_i32(config->outbound_delta);
                previous_outbound = (uint16_t)_InterlockedExchange16(
                    (volatile short *)&state->outbound_amount, (short)converted_outbound);
                result = ((uint32_t)converted_outbound & 0xffff0000u) | previous_outbound;
            }
            return result;
        }
    }

    (void)_InterlockedExchange16((volatile short *)&state->outbound_amount, 0);
    result = (uint16_t)_InterlockedExchange16((volatile short *)&state->inbound_amount, 0);
    return result;
}

/* Shared callback body RVA 0x32cb0 (registry events 2 and 3). */
__declspec(dllexport) void recovered_fake_lag_packet(
    fake_lag_state *state, volatile fake_lag_packet_event *event,
    const fake_lag_dependencies *dependencies, void *user)
{
    uint32_t event_type = event->type;
    uint16_t amount;
    uint8_t blocked;

    if (event_type == 2) {
        if ((state->shared_byte & 1u) != 0) {
            uint64_t a = dependencies->packet_predicate_a(
                event->object_a, event->object_b, user);
            if (a != 0) {
                event->result = 3;
                return;
            }
            a = dependencies->packet_predicate_b(
                event->object_a, event->object_b, user);
            if (a != 0) {
                event->result = 3;
                return;
            }
            a = dependencies->packet_predicate_c(
                event->object_a, event->object_b, user);
            if (a != 0) {
                event->result = 3;
                return;
            }
        }
        blocked = state->inbound_block;
    } else {
        blocked = state->outbound_block;
    }

    if ((blocked & 1u) != 0) return;
    amount = event_type == 2 ? state->inbound_amount : state->outbound_amount;

    {
        uint64_t remaining = (uint64_t)event->remaining - (uint64_t)amount;
        event->remaining = (int64_t)remaining;
        /* Native JNS tests the result sign bit directly, including subtraction overflow. */
        if ((remaining & (UINT64_C(1) << 63)) == 0) return;
    }
    event->remaining = 0;
    event->result = 1;
}
