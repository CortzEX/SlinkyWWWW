#include <stdint.h>
#include <string.h>
#include <math.h>

typedef uint8_t (*dep_bool2)(uintptr_t, uintptr_t);
typedef uintptr_t (*dep_ptr2)(uintptr_t, uintptr_t);
typedef int32_t (*dep_i32_2)(uintptr_t, uintptr_t);
typedef struct {
    dep_bool2 dep_180023f90;
    dep_ptr2 dep_180028a50;
    dep_i32_2 dep_180025c50;
    dep_bool2 dep_180023690;
    dep_i32_2 dep_1800239d0;
    dep_ptr2 dep_180026c80;
    dep_ptr2 dep_180026cc0;
} Dependencies;
typedef struct {
    int32_t timer;
    int32_t previous_target;
    int32_t require_sprint;
    int32_t event_type;
    float activation_threshold;
    float reach_value;
} ReachState;

__declspec(dllexport) void recovered_ghost_hand(uint8_t *event) {
    event[0x10] = 1;
}
__declspec(dllexport) void recovered_hitboxes(uint8_t *event, float expand) {
    double value = (double)expand;
    event[0x10] = 1;
    memcpy(event + 0x20, &value, sizeof(value));
}
__declspec(dllexport) void recovered_piercing(uint8_t *event) {
    event[0x10] = 1;
}
__declspec(dllexport) void recovered_no_slow(uint8_t *event, const float multipliers[3], double divisor, const Dependencies *deps) {
    uintptr_t frame, game, target, item;
    uint8_t ready;
    int32_t type;
    uint32_t bucket;
    float factor;
    double ratio;
    float x, y;
    memcpy(&frame, event + 8, 8);
    memcpy(&game, (const uint8_t *)frame, 8);
    memcpy(&target, (const uint8_t *)frame + 0x28, 8);
    ready = deps->dep_180023f90(game, target);
    if (!ready) return;
    memcpy(&game, (const uint8_t *)frame, 8);
    memcpy(&target, (const uint8_t *)frame + 0x28, 8);
    item = deps->dep_180028a50(game, target);
    if (!item) return;
    memcpy(&game, (const uint8_t *)frame, 8);
    type = deps->dep_180025c50(game, item);
    bucket = (uint32_t)type - 0x105u;
    if (bucket < 0x17u && ((0x4088c0u >> (bucket & 31u)) & 1u)) factor = multipliers[0];
    else if (bucket == 0) factor = multipliers[1];
    else factor = multipliers[2];
    ratio = (double)factor / divisor;
    memcpy(&x, event + 0x10, 4);
    memcpy(&y, event + 0x14, 4);
    x = (float)(ratio * (double)x);
    y = (float)(ratio * (double)y);
    memcpy(event + 0x10, &x, 4);
    memcpy(event + 0x14, &y, 4);
}
__declspec(dllexport) void recovered_ping_fix_3e6d0(uint8_t *event, const Dependencies *deps) {
    uintptr_t a, b, result;
    memcpy(&a, event + 8, 8); memcpy(&b, event + 0x10, 8);
    result = deps->dep_180026c80(a, b);
    if (result) { uint32_t value = 3; memcpy(event + 0x24, &value, 4); }
}
__declspec(dllexport) void recovered_ping_fix_3e700(uint8_t *event, const Dependencies *deps) {
    uintptr_t a, b, result;
    memcpy(&a, event + 8, 8); memcpy(&b, event + 0x10, 8);
    result = deps->dep_180026cc0(a, b);
    if (result) { uint32_t value = 3; memcpy(event + 0x24, &value, 4); }
}
__declspec(dllexport) void recovered_reach(uint8_t *event, ReachState *s, const Dependencies *deps) {
    uintptr_t frame, game, target;
    int32_t identifier;
    float count, threshold;
    double value;
    uint8_t gate = 1;
    memcpy(&frame, event + 8, 8); memcpy(&game, (const uint8_t *)frame, 8); memcpy(&target, (const uint8_t *)frame + 0x28, 8);
    if (s->timer > 0) --s->timer;
    if (s->require_sprint == 1) gate = deps->dep_180023690(game, target);
    if (!gate) return;
    memcpy(&game, (const uint8_t *)frame, 8); memcpy(&target, (const uint8_t *)frame + 0x28, 8);
    if (s->timer == 0) {
        identifier = deps->dep_1800239d0(game, target);
        if (identifier != s->previous_target) {
            s->timer = 9;
            s->previous_target = identifier;
        }
    }
    count = (float)s->timer;
    threshold = s->activation_threshold;
    if (isnan(threshold) || threshold <= count) return;
    value = (double)s->reach_value;
    event[0x10] = 1;
    memcpy(event + 0x18, &value, 8);
}
