#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <emmintrin.h>

typedef uint64_t (*keep_dependency)(void *context, uint32_t helper_rva,
    uint64_t a, uint64_t b, uint64_t c, uint64_t d);
typedef uint8_t (*keep_float_dependency)(void *context, uint32_t helper_rva, uint32_t xmm0_bits);

typedef struct {
    keep_dependency invoke;
    keep_float_dependency invoke_float;
    void *context;
} keep_dependencies;

typedef struct {
    double movement[3];
    uint8_t armed;
    uint8_t pending;
} keep_state;

typedef struct {
    float chance;
    uint8_t require_on_ground;
    float motion_multiplier;
    uint8_t allow_reduce;
} keep_config;

static uint64_t call(const keep_dependencies *d, uint32_t rva,
    uint64_t a, uint64_t b, uint64_t c, uint64_t e)
{
    return d->invoke(d->context, rva, a, b, c, e);
}

static uint8_t chance(const keep_dependencies *d, uint32_t value_bits)
{
    return d->invoke_float(d->context, 0x0A460, value_bits);
}

static uint32_t bits_of_float(float value)
{
    uint32_t bits;
    memcpy(&bits, &value, sizeof(bits));
    return bits;
}

static uint64_t read64(const void *p, size_t off)
{
    uint64_t value;
    memcpy(&value, (const uint8_t *)p + off, sizeof(value));
    return value;
}

/* Keep Sprint callback at RVA 0x3a0f0: event 14, priority 0. */
extern "C" __declspec(dllexport) void recovered_keep_sprint_3a0f0(void *event,
    keep_state *state, const keep_config *config, const keep_dependencies *d)
{
    if (*((uint8_t *)event + 0x10) != 1) return;
    uint8_t *payload = (uint8_t *)(uintptr_t)read64(event, 8);
    if (payload[0x40] == 1 &&
        (uint8_t)call(d, 0x23690, read64(payload, 0), read64(payload, 0x28), 0, 0) != 0 &&
        chance(d, bits_of_float(config->chance)) != 0) {
        uint8_t sampled[24];
        call(d, 0x23550, (uintptr_t)sampled, read64(payload, 0), read64(payload, 0x28), 0);
        memcpy(state->movement, sampled, sizeof(sampled));
        state->armed = 1;
    } else {
        state->armed = 0;
    }
}

/* Keep Sprint callback at RVA 0x3a170: event 15, priority 0. */
extern "C" __declspec(dllexport) void recovered_keep_sprint_3a170(void *event,
    keep_state *state, const keep_config *config, const keep_dependencies *d)
{
    if (state->armed != 1 || *((uint8_t *)event + 0x10) != 1) return;
    uint8_t *payload = (uint8_t *)(uintptr_t)read64(event, 8);
    uint64_t target = read64(payload, 0x28);
    if (!target) return;
    if (config->require_on_ground == 1 &&
        (uint8_t)call(d, 0x23780, read64(payload, 0), target, 0, 0) == 0) return;
    target = read64(payload, 0x28);
    int32_t a = (int32_t)call(d, 0x23760, read64(payload, 0), target, 0, 0);
    int32_t b = (int32_t)call(d, 0x239D0, read64(payload, 0), read64(payload, 0x28), 0, 0);
    if (a != b) return;
    uint64_t status = read64(payload, 0x38);
    if (config->allow_reduce == 1 && *((uint8_t *)(uintptr_t)status + 0x18) != 0) return;

    double multiplier = (double)config->motion_multiplier;
    double old_z = state->movement[2];
    __m128d factor = _mm_set_sd(multiplier);
    state->movement[0] = _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(state->movement[0]), factor));
    state->movement[2] = _mm_cvtsd_f64(_mm_mul_sd(factor, _mm_set_sd(old_z)));
    uint64_t bridge = read64(payload, 0);
    target = read64(payload, 0x28);
    double movement_copy[3];
    memcpy(movement_copy, state->movement, sizeof(movement_copy));
    call(d, 0x235F0, bridge, target, (uintptr_t)movement_copy, 0);
    state->pending = 1;
}

/* Keep Sprint callback at RVA 0x3a260: event 17, priority 0. */
extern "C" __declspec(dllexport) void recovered_keep_sprint_3a260(void *event,
    keep_state *state, const keep_dependencies *d)
{
    if (state->pending != 1) return;
    state->pending = 0;
    uint8_t *payload = (uint8_t *)(uintptr_t)read64(event, 8);
    uint64_t target = read64(payload, 0x28);
    if (target) call(d, 0x236C0, read64(payload, 0), target, 1, 0);
}
