#include <stdint.h>
#include <stddef.h>

/* Dependency identifiers are native helper RVAs. Their semantics stay
   address-based where the supplied artifacts do not establish a safe name. */
typedef uint64_t (*access_dependency)(void *context, uint32_t helper_rva,
    uint64_t a, uint64_t b, uint64_t c, uint64_t d);
typedef uint64_t (*access_float_dependency)(uint64_t a, uint64_t b, float xmm2);

typedef struct {
    access_dependency invoke;
    void *context;
    access_float_dependency invoke_23e60;
    access_float_dependency invoke_23e90;
} access_dependencies;

typedef struct {
    uint8_t enabled_44940;
    uint8_t enabled_44940_second;
    uint8_t state_42b80;
    int32_t state_3e590;
    int32_t countdown_3e8e0;
    int32_t last_value_3e8e0;
    uint8_t gate_3e8e0;
} access_globals;

static uint64_t word(const void *p, size_t offset)
{
    return *(const uint64_t *)((const uint8_t *)p + offset);
}

static uint64_t call(const access_dependencies *d, uint32_t rva,
    uint64_t a, uint64_t b, uint64_t c, uint64_t e)
{
    return d->invoke(d->context, rva, a, b, c, e);
}

static uint64_t call_xmm2(const access_dependencies *d, uint32_t rva,
    uint64_t a, uint64_t b)
{
    access_float_dependency fn = rva == 0x23E60 ? d->invoke_23e60 : d->invoke_23e90;
    return fn(a, b, 0.0f);
}

/* Anti Debuff, registered at event 18, priority 0. */
__declspec(dllexport) void recovered_anti_debuff_44940(void *event,
    access_globals *g, const access_dependencies *d)
{
    uint64_t *payload = (uint64_t *)word(event, 8);
    if (g->enabled_44940 == 1) {
        uint64_t value = call(d, 0x27960, payload[0], 0xF, 0, 0);
        uint64_t found = call(d, 0x23C10, payload[0], payload[5], value, 0);
        if (found != 0) call(d, 0x279C0, payload[0], found, 0, 0);
    }
    if (g->enabled_44940_second == 1) {
        call_xmm2(d, 0x23E60, payload[0], payload[5]);
        /* The tail call at 0x449af resolves to helper 0x23e90. */
        call_xmm2(d, 0x23E90, payload[0], payload[5]);
    }
}

/* No Jump Delay, registered at event 17, priority 100. */
__declspec(dllexport) void recovered_no_jump_delay_35d50(void *event,
    const access_dependencies *d)
{
    uint64_t *payload = (uint64_t *)word(event, 8);
    if (*((uint8_t *)payload + 0x40) == 1)
        call(d, 0x23B80, payload[0], payload[5], 0, 0);
}

/* Item Use Fix, registered at events 14 and 15, each priority 0. */
__declspec(dllexport) void recovered_item_use_fix_42b80(void *event,
    access_globals *g, const access_dependencies *d)
{
    if (*((uint8_t *)event + 0x10) != 0) return;
    uint64_t *payload = (uint64_t *)word(event, 8);
    uint64_t value = call(d, 0x22DF0, payload[0], payload[3], 0, 0);
    g->state_42b80 = (uint8_t)((uint8_t)call(d, 0x27E90, payload[0], value, 0, 0) != 0);
    if (g->state_42b80)
        call(d, 0x27EB0, payload[0], value, 0, 0);
}

__declspec(dllexport) void recovered_item_use_fix_42be0(void *event,
    access_globals *g, const access_dependencies *d)
{
    if (g->state_42b80 != 1 || *((uint8_t *)event + 0x10) != 0) return;
    uint64_t *payload = (uint64_t *)word(event, 8);
    uint64_t value = call(d, 0x22DF0, payload[0], payload[3], 0, 0);
    call(d, 0x27EB0, payload[0], value, g->state_42b80, 0);
}

/* No Hit Delay, registered at event 14, priority 0. */
__declspec(dllexport) void recovered_no_hit_delay_3e590(void *event,
    access_globals *g, const access_dependencies *d)
{
    if (*((uint8_t *)event + 0x10) != 1) return;
    uint64_t *payload = (uint64_t *)word(event, 8);
    if (*(int32_t *)(uintptr_t)word((void *)(uintptr_t)payload[0], 0) == 0) return;
    int32_t count = (int32_t)call(d, 0x22E90, payload[0], payload[3], 0, 0);
    if (count <= 0) return;
    if (g->state_3e590 == 1) {
        uint64_t token = call(d, 0x22E10, payload[0], payload[3], 0, 0);
        if (token != 0 && (int32_t)call(d, 0x24B50, payload[0], token, 0, 0) != 0) {
            call(d, 0x22EB0, payload[0], payload[3], 0, 0);
            return;
        }
    } else {
        call(d, 0x22EB0, payload[0], payload[3], 0, 0);
        return;
    }
    if ((uint8_t)call(d, 0x23F90, payload[0], payload[5], 0, 0) == 0)
        call(d, 0x23BB0, payload[0], payload[5], 0, 0);
}

/* No Use Delay, registered at event 18, priority 0. */
__declspec(dllexport) void recovered_no_use_delay_3e8e0(void *event,
    access_globals *g, const access_dependencies *d)
{
    uint64_t *payload = (uint64_t *)word(event, 8);
    if (*((uint8_t *)payload + 0x40) == 0) {
        g->countdown_3e8e0 = 0;
        return;
    }
    uint64_t selected = call(d, 0x22CF0, payload[0], payload[3], 0, 0);
    selected = call(d, 0x24F90, payload[0], selected, 0, 0);
    uint8_t active = (uint8_t)call(d, 0x25430, payload[0], selected, 0, 0);
    uint64_t item = call(d, 0x23F40, payload[0], payload[5], 0, 0);
    int32_t item_id = (int32_t)call(d, 0x25A60, payload[0], item, 0, 0);
    if (item_id != g->last_value_3e8e0) {
        g->countdown_3e8e0 = 0;
        g->last_value_3e8e0 = item_id;
        uint64_t object = payload[0]; /* 0x3e954 captures this pair across the next call. */
        uint32_t arg = (uint32_t)call(d, 0x25490, object, selected, 0, 0);
        call(d, 0x25460, object, selected, arg, 0);
    }
    if (!active) return;
    int32_t use_result = (int32_t)call(d, 0x23FC0, payload[0], payload[5], 0, 0);
    if (g->countdown_3e8e0 > 0) {
        --g->countdown_3e8e0;
        if (g->countdown_3e8e0 == 0 || (use_result == 0 && (g->gate_3e8e0 & 1) != 0)) {
            call(d, 0x25460, payload[0], selected, 0, 0);
            return;
        }
        return;
    }
    g->countdown_3e8e0 = use_result;
}
