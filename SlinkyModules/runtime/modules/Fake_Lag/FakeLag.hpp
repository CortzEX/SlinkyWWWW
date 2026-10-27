#ifndef SLINKY_SHARE_E4F25B90EAA79F2554FF
#define SLINKY_SHARE_E4F25B90EAA79F2554FF
#ifndef SEMANTIC_FAKE_LAG_H
#define SEMANTIC_FAKE_LAG_H

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

struct fake_lag_config {
    volatile float &inbound_delta, &outbound_delta;
    volatile uint8_t &inbound_token;
    volatile uint32_t &advance_mode;
    volatile uint8_t &require_ingame, &require_weapon, &require_attack;
    explicit fake_lag_config(uint8_t *image) :
        inbound_delta(*reinterpret_cast<volatile float *>(image+0x2ebf00)),
        outbound_delta(*reinterpret_cast<volatile float *>(image+0x2ebf38)),
        inbound_token(image[0x2ebf58]),
        advance_mode(*reinterpret_cast<volatile uint32_t *>(image+0x2ebfa0)),
        require_ingame(image[0x2ebfc8]), require_weapon(image[0x2ebfe8]), require_attack(image[0x2ec008]) {}
};
enum class FakeLagMode : uint32_t { Static = 0, Pulse = 1 };


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

void bind_fake_lag_known(fake_lag_dependencies *);

/* Event 0 callback at RVA 0x32b30. Query implementations are injected. */
#ifdef __cplusplus
extern "C" {
#endif
__declspec(dllexport) uint32_t semantic_fake_lag_update(
    fake_lag_state *state, fake_lag_config *config,
    fake_lag_event0 *event, const fake_lag_dependencies *dependencies, void *user);

/* Event 2/3 callback at RVA 0x32cb0. Both registry entries share this body. */
__declspec(dllexport) void semantic_fake_lag_packet(
    fake_lag_state *state, volatile fake_lag_packet_event *event,
    const fake_lag_dependencies *dependencies, void *user);
#ifdef __cplusplus
}
#endif

#endif
#endif // SLINKY_SHARE_E4F25B90EAA79F2554FF
