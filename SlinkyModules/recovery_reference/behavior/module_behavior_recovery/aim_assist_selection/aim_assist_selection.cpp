#include <stdint.h>
#include <string.h>

typedef uint64_t (*dependency)(uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
/* 4 register arguments followed by the 8 stack arguments visible at 2b8a3. */
typedef uint64_t (*aim_test_12)(uint64_t, uint64_t, uint64_t, uint64_t,
    uint8_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
static uint64_t q(const void *p) { uint64_t v; memcpy(&v, p, 8); return v; }
static uint32_t d(const void *p) { uint32_t v; memcpy(&v, p, 4); return v; }
static float f(const void *p) { float v; memcpy(&v, p, 4); return v; }
static void w64(void *p, uint64_t v) { memcpy(p, &v, 8); }
static void w32(void *p, uint32_t v) { memcpy(p, &v, 4); }

static uint64_t invoke_test(aim_test_12 test, uint8_t *ctx, uint64_t candidate,
    double *input, uint64_t current, uint64_t mode, double *metric,
    uint32_t *first, uint32_t *second, uint32_t *third, uint32_t *threshold,
    double *position, void *selected) {
    return test((uintptr_t)ctx, candidate, (uintptr_t)input, current, mode,
        (uintptr_t)metric, (uintptr_t)first, (uintptr_t)second, (uintptr_t)third,
        (uintptr_t)threshold, (uintptr_t)position, (uintptr_t)selected);
}

static uint64_t virtual_call(uint8_t *ctx, uint32_t slot, uint64_t arg1,
    uint64_t arg2, dependency call) {
    uint64_t game = q(ctx), iface = q((const void *)(uintptr_t)(game + 8));
    uint64_t table = q((const void *)(uintptr_t)iface);
    uint64_t target = q((const void *)(uintptr_t)(table + slot));
    return call(target, iface, arg1, arg2, 0);
}
static uint64_t method_call_on_iface(uint64_t iface, uint32_t slot,
    uint64_t arg1, uint64_t arg2, dependency call) {
    uint64_t table = q((const void *)(uintptr_t)iface);
    uint64_t target = q((const void *)(uintptr_t)(table + slot));
    return call(target, iface, arg1, arg2, 0);
}

static void release_target(uint8_t *ctx, uint8_t *image, dependency call) {
    uint64_t current = q(image + 0x2f7be0);
    if (current) virtual_call(ctx, 0xb0, current, 0, call);
    w64(image + 0x2f7be0, 0);
    image[0x2f7bd8] = 0;
}

__declspec(dllexport) void recovered_aim_assist_select_2b630(
    uint8_t *event, uint8_t *image, dependency call, aim_test_12 test) {
    uint8_t *ctx = (uint8_t *)(uintptr_t)q(event + 8);
    w64(image + 0x2f7c18, 0);
    if (ctx[0x40] != 1) goto cleanup;
    if (image[0x2e90d8] == 1 && d(image + 0x2e9020) != 3 &&
        !(uint8_t)call(0x23690, q(ctx), q(ctx + 0x28), 0, 0)) goto clear_active;

    uint8_t predicate = (uint8_t)call(0x29080, (uintptr_t)ctx, 0, 0, 0);
    if (image[0x2e90f8] == 1) {
        if (!predicate) {
            extern uint32_t recovered_a460(uint8_t *, uint32_t);
            w32(image + 0x2f7c78, (recovered_a460(image, d(image + 0x14fef4)) & 0xff) + 1);
            goto cleanup;
        }
        if (d(image + 0x2f7c78) != 0 && d(image + 0x2e9020) < 2) {
            w32(image + 0x2f7c78, d(image + 0x2f7c78) - 1);
            goto cleanup;
        }
    }
    if ((predicate & image[0x2e9118]) == 1) {
        uint64_t target = call(0x22e10, q(ctx), q(ctx + 0x18), 0, 0);
        if (target && (uint32_t)call(0x24b50, q(ctx), target, 0, 0) == 1) goto clear_active;
    }
    if (image[0x2e9138] == 1 &&
        !(uint8_t)call(0x380b0, q(ctx), q(ctx + 0x28), 0, 0)) goto cleanup;

    double from[3], input[3], position[3];
    call(0x23030, (uintptr_t)from, q(ctx), q(ctx + 0x28), 0);
    if (!(uint8_t)call(0x23020, q(ctx), 0, 0, 0)) {
        memcpy(input, from, sizeof input);
        extern double *recovered_vector_y_offset_9590(double *, const double *, uint8_t *);
        recovered_vector_y_offset_9590(from, input, image);
    }
    uint64_t current = (uint8_t)call(0x29f80, 0, 0, 0, 0)
        ? call(0x29ff0, 0, 0, 0, 0)
        : call(0x23170, q(ctx), q(ctx + 0x28), 0, 0);

    double metric, selected_metric;
    uint32_t arg_a, arg_b, arg_c, arg_d;
    metric = (double)f(image + 0x2e90b4);
    arg_a = 0x7f7fffff; arg_b = 0x7fffffff; arg_c = 0;
    arg_d = d(image + 0x2e8f14);
    uint64_t list;
    if (d(image + 0x2e9180) == 0) {
        double fallback_metric = (double)f(image + 0x2e90b4);
        uint32_t fallback_a = 0x7f7fffff, fallback_b = 0x7fffffff;
        uint32_t fallback_c = 0, fallback_d = d(image + 0x2e8f14);
        uint64_t old_target = q(image + 0x2f7be0);
        if (old_target) {
            memcpy(input, from, sizeof input);
            if (invoke_test(test, ctx, old_target, input, current, 1, &fallback_metric,
                &fallback_a, &fallback_b, &fallback_c, &fallback_d, position, image + 0x2f7bd8) & 0xff) {
                w64(image + 0x2f7be8, q(image + 0x2f7c00));
                w64(image + 0x2f7bf0, q(image + 0x2f7c08));
                w64(image + 0x2f7bf8, q(image + 0x2f7c10));
                memcpy(image + 0x2f7c00, position, sizeof position);
                return;
            }
            uint64_t current_after_test = q(image + 0x2f7be0);
            if (current_after_test) virtual_call(ctx, 0xb0, current_after_test, 0, call);
            w64(image + 0x2f7be0, 0);
            image[0x2f7bd8] = 0;
        }
    }
    list = call(0x24600, q(ctx), q(ctx + 0x20), 0, 0);
    int32_t count = (int32_t)call(0x24e50, q(ctx), list, 0, 0);
    if (count > 0) {
        uint64_t best = 0;
        for (uint32_t i = 0;; ++i) {
            uint64_t candidate = call(0x24e80, q(ctx), list, i, 0);
            uint64_t accepted = virtual_call(ctx, 0xc0, q(ctx + 0x28), candidate, call);
            if (!(uint8_t)accepted) {
                memcpy(input, from, sizeof input);
                uint64_t result = invoke_test(test, ctx, candidate, input, current, 0,
                    &metric, &arg_a, &arg_b, &arg_c, &arg_d, position, &selected_metric);
                if (result & 0xff) best = candidate;
            }
            int32_t reloaded_count = (int32_t)call(0x24e50, q(ctx), list, 0, 0);
            if ((int32_t)(i + 1u) >= reloaded_count) break;
        }
        if (best) {
            if (!(uint8_t)virtual_call(ctx, 0xc0, q(image + 0x2f7be0), best, call)) {
                w64(image + 0x2f7be8, q(position));
                w64(image + 0x2f7bf0, q(position + 1));
                w64(image + 0x2f7bf8, q(position + 2));
            } else {
                w64(image + 0x2f7be8, q(image + 0x2f7c00));
                w64(image + 0x2f7bf0, q(image + 0x2f7c08));
                w64(image + 0x2f7bf8, q(image + 0x2f7c10));
            }
            memcpy(image + 0x2f7c00, position, sizeof position);
            image[0x2f7bd8] = *(const uint8_t *)&selected_metric;
            uint64_t old = q(image + 0x2f7be0);
            uint64_t game_now = q(ctx), retained_iface = q((const void *)(uintptr_t)(game_now + 8));
            if (old) method_call_on_iface(retained_iface, 0xb0, old, 0, call);
            uint64_t retained = method_call_on_iface(retained_iface, 0xa8, best, 0, call);
            if (retained) w64(image + 0x2f7be0, retained);
            return;
        }
    }
cleanup:
    release_target(ctx, image, call);
    return;
clear_active:
    image[0x2f7bd8] = 0;
    return;
}
