#include <stdint.h>
#include <stddef.h>
#include <string.h>

typedef uint64_t (*weapons_dependency)(void *context, uint32_t helper_rva,
    uint64_t a, uint64_t b, uint64_t c, uint64_t d);
typedef struct { weapons_dependency invoke; void *context; } weapons_dependencies;

typedef struct {
    uint8_t default_allowed;
    uint8_t identifier_allow_a;
    uint8_t identifier_allow_b;
    uint8_t table_enabled[9];
    uint8_t return_slot_for_group_a;
    uint8_t return_slot_for_group_b;
    uint8_t return_slot_for_high_group;
} weapons_policy;

static uint64_t call(const weapons_dependencies *d, uint32_t rva,
    uint64_t a, uint64_t b, uint64_t c, uint64_t e)
{
    return d->invoke(d->context, rva, a, b, c, e);
}

/* RVA 0x38190, registered for Weapons event 26 at priority 0. */
__declspec(dllexport) void recovered_weapons_cleanup_38190(uint8_t cache[16],
    const weapons_dependencies *d)
{
    uint64_t old_pointer;
    memcpy(&old_pointer, cache, sizeof(old_pointer));
    call(d, 0x13CF70, old_pointer, 0, 0, 0);
    memset(cache, 0, 16);
}

/* RVA 0x38040. Helper 0x2ac60 remains an explicit external policy dependency. */
__declspec(dllexport) uint8_t recovered_weapon_allowed_38040(uint64_t object,
    uint64_t candidate, const weapons_policy *policy, const weapons_dependencies *d)
{
    if (!candidate) return policy->default_allowed;
    uint32_t identifier = (uint32_t)call(d, 0x25C50, object, candidate, 0, 0);
    uint32_t bit = identifier - 0x102u;
    if (bit < 0x1d) {
        if (((0x02044600u >> bit) & 1u) != 0) return policy->identifier_allow_a;
        if (((0x10222001u >> bit) & 1u) != 0) return policy->identifier_allow_b;
    }
    if (identifier != 0)
        return (uint8_t)call(d, 0x2AC60, 0x1802FC568ull, identifier, 0, 0);
    return policy->default_allowed;
}

/* RVA 0x37f60. The virtual field lookups and enchantment adapters remain
   dependencies; the slot count, low-16-bit classification and group mask are recovered. */
__declspec(dllexport) uint32_t recovered_weapon_groups_37f60(uint64_t object, uint64_t item,
    const weapons_dependencies *d)
{
    uint64_t environment = call(d, 0x25DE0, object, item, 0, 0);
    if (!environment) return 0;
    uint64_t interface_object;
    memcpy(&interface_object, (const void *)(uintptr_t)(object + 8), sizeof(interface_object));
    uint64_t key_a = call(d, 0x80000538u, interface_object, 0x18015292eull, 0, 0);
    if (!key_a) return 0;
    uint64_t key_b = call(d, 0x80000538u, interface_object, 0x180152931ull, 0, 0);
    if (!key_b) return 0;
    int32_t count = (int32_t)call(d, 0x27F10, object, environment, 0, 0);
    if (count <= 0) return 0;
    uint32_t groups = 0;
    for (int32_t index = 0; index < count; ++index) {
        uint64_t enchantment = call(d, 0x27F40, object, environment, (uint32_t)index, 0);
        uint16_t kind = (uint16_t)call(d, 0x27F70, object, enchantment, key_a, 0);
        if (kind == 0x14) groups |= 4;
        else if (kind == 0x13) groups |= 2;
        else if (kind == 0x10) groups |= 1;
    }
    return groups;
}

/* RVA 0x380c0. Iterates the nine weapon slots, then checks configured groups
   and the current-item eligibility policy before returning a slot. */
__declspec(dllexport) uint32_t recovered_find_weapon_slot_380c0(uint64_t game_ref,
    uint64_t inventory, const weapons_policy *policy, const weapons_dependencies *d)
{
    uint64_t object;
    for (uint32_t slot = 0; slot != 9; ++slot) {
        if (policy->table_enabled[slot]) return slot;
        memcpy(&object, (const void *)(uintptr_t)game_ref, sizeof(object));
        uint64_t item = call(d, 0x26140, object, inventory, slot, 0);
        if (!item) continue;
        memcpy(&object, (const void *)(uintptr_t)game_ref, sizeof(object));
        uint32_t groups = recovered_weapon_groups_37f60(object, item, d);
        if (((groups & 1u) && policy->return_slot_for_group_a) ||
            ((groups & 2u) && policy->return_slot_for_group_b) ||
            ((groups > 3u) && policy->return_slot_for_high_group)) return slot;
        uint64_t candidate = call(d, 0x25D10, object, item, 0, 0);
        if (recovered_weapon_allowed_38040(object, candidate, policy, d)) return slot;
    }
    return UINT32_MAX;
}

/* RVA 0x380b0 is only a tail-call adapter: xor r8d,r8d; jmp 0x37e50. The
   cache-producing target remains external and is not represented as recovered. */
__declspec(dllexport) uint8_t recovered_weapon_cached_query_380b0(uint64_t object,
    uint64_t item, const weapons_dependencies *d)
{
    return (uint8_t)call(d, 0x37E50, object, item, 0, 0);
}
