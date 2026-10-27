#ifndef RECOVERED_SPRINT_RESET_H
#define RECOVERED_SPRINT_RESET_H

#include <stdint.h>

typedef struct {
    volatile uint64_t object;
    uint8_t reserved0[0x10];
    volatile uint64_t action_arg; /* payload +0x18, passed to 0x22cf0 */
    uint8_t reserved1[8];
    volatile uint64_t target;     /* payload +0x28 */
    uint8_t reserved2[0x10];
    volatile uint8_t sprinting;   /* payload +0x40; enabled only when exactly 1 */
} sprint_reset_context;

typedef struct { uint64_t reserved; sprint_reset_context *context; } sprint_reset_event;

typedef struct {
    volatile uint32_t mode;             /* RVA 0x2eff58 */
    volatile uint32_t phase;            /* RVA 0x2fc870; callback state machine */
    volatile float timer;               /* RVA 0x2fc874 */
    volatile double last_sample_time;   /* RVA 0x2fc878 */
    volatile uint8_t have_state;        /* RVA 0x2fc880 */
    volatile uint32_t sample_count;     /* RVA 0x2fc884 */
    volatile float duration;            /* RVA 0x2eff98 */
    volatile uint8_t randomize;         /* RVA 0x2effb8 */
    volatile uint8_t wait_for_damage;   /* RVA 0x2effd8 */
    volatile uint8_t require_weapon;    /* RVA 0x2efff8 */
    volatile float delay;               /* RVA 0x2f0030 */
} sprint_reset_globals;

typedef struct {
    uint64_t rcx, rdx, r8, r9;
    uint64_t xmm0, xmm1, xmm2;
} sprint_call_args;
typedef struct { uint64_t rax, rdx, r8, r9, xmm0; } sprint_call_result;
typedef void (*sprint_dispatch_fn)(uint32_t rva, const sprint_call_args *args,
                                   sprint_call_result *result, void *user);
typedef struct { sprint_dispatch_fn dispatch; } sprint_reset_dependencies;

#ifdef __cplusplus
extern "C" {
#endif
__declspec(dllexport) void recovered_sprint_reset(
    sprint_reset_globals *globals, sprint_reset_event *event,
    const sprint_reset_dependencies *dependencies, void *user);

/* Local helper body at RVA 0x3b150; action dispatch endpoint 0x25460 is injected. */
void recovered_sprint_action(
    const sprint_reset_globals *globals, volatile sprint_reset_context *context, uint32_t active_arg,
    const sprint_reset_dependencies *dependencies, void *user);
#ifdef __cplusplus
}
#endif

#endif
