#ifndef RECOVERED_FAKE_LAG_H
#define RECOVERED_FAKE_LAG_H

#include <stdint.h>

typedef struct {
    volatile uint32_t last_state;       /* Native RVA 0x2fa304 */
    volatile uint32_t pulse_timer;      /* Native RVA 0x2fa308 */
    volatile uint32_t inbound_value;    /* Native RVA 0x2fa30c */
    volatile uint32_t outbound_value;   /* Native RVA 0x2fa310 */
    volatile uint8_t shared_byte;       /* Native RVA 0x2fa314 */
    volatile uint8_t inbound_block;     /* Native RVA 0x2fa315 */
    volatile uint8_t outbound_block;    /* Native RVA 0x2fa316 */
    uint8_t reserved;
    volatile uint16_t inbound_amount;   /* Native RVA 0x2fa318 */
    volatile uint16_t outbound_amount;  /* Native RVA 0x2fa31a */
} fake_lag_state;

typedef struct {
    volatile float inbound_delta;       /* Native RVA 0x2ebf00 */
    volatile float outbound_delta;      /* Native RVA 0x2ebf38 */
    volatile uint8_t inbound_token;     /* Native RVA 0x2ebf58 */
    volatile uint32_t advance_mode;     /* Native RVA 0x2ebfa0 */
    volatile uint8_t require_ingame;    /* Native RVA 0x2ebfc8 */
    volatile uint8_t require_weapon;    /* Native RVA 0x2ebfe8 */
    volatile uint8_t require_attack;    /* Native RVA 0x2ec008 */
} fake_lag_config;

typedef struct {
    uint64_t object;
    uint8_t reserved0[0x18];
    uint64_t required_object;
    uint64_t target;
    uint8_t reserved1[0x10];
    uint8_t in_game;
} fake_lag_event0_payload;

typedef struct {
    uint64_t reserved;
    fake_lag_event0_payload *payload;    /* Native callback reads this at +8 */
} fake_lag_event0;

typedef struct {
    uint32_t type;
    uint32_t reserved0;
    uint64_t object_a;
    uint64_t object_b;
    int64_t remaining;
    uint32_t reserved1;
    uint32_t result;                    /* Native callback writes this at +0x24 */
} fake_lag_packet_event;

typedef struct {
    int32_t (*sample_state)(uint64_t object, uint64_t target, void *user);
    uint8_t (*weapon_allowed)(uint64_t object, uint64_t target, void *user);
    uint64_t (*packet_predicate_a)(uint64_t object_a, uint64_t object_b, void *user);
    uint64_t (*packet_predicate_b)(uint64_t object_a, uint64_t object_b, void *user);
    uint64_t (*packet_predicate_c)(uint64_t object_a, uint64_t object_b, void *user);
} fake_lag_dependencies;

/* Event 0 callback at RVA 0x32b30. Query implementations are injected. */
#ifdef __cplusplus
extern "C" {
#endif
__declspec(dllexport) uint32_t recovered_fake_lag_update(
    fake_lag_state *state, fake_lag_config *config,
    fake_lag_event0 *event, const fake_lag_dependencies *dependencies, void *user);

/* Event 2/3 callback at RVA 0x32cb0. Both registry entries share this body. */
__declspec(dllexport) void recovered_fake_lag_packet(
    fake_lag_state *state, volatile fake_lag_packet_event *event,
    const fake_lag_dependencies *dependencies, void *user);
#ifdef __cplusplus
}
#endif

#endif
