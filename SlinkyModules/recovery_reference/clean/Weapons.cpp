#include "Weapons.hpp"
#include <cstring>

using Word = std::uintptr_t;
static Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word value;
    std::memcpy(&value, bridge->metadata + offset, sizeof(value));
    return value;
}
template <class Function>
static Function slot(Word *environment, std::size_t offset) {
    const auto *table = reinterpret_cast<const Word *>(*environment);
    return reinterpret_cast<Function>(table[offset / sizeof(Word)]);
}
using ObjectMethod = Word (*)(Word *, Word, Word, ...);
static Word object_method(GameAccessBridge *bridge, Word object, std::size_t offset) {
    return slot<ObjectMethod>(bridge->environment, 0x110)(bridge->environment, object, identifier(bridge, offset));
}
static Word indexed_method(GameAccessBridge *bridge, Word object, std::size_t offset, std::uint32_t index) {
    return slot<ObjectMethod>(bridge->environment, 0x110)(bridge->environment, object, identifier(bridge, offset), index);
}
// 0x23760, 0x26140 and 0x25d10.
static std::uint32_t counter(GameAccessBridge *bridge, Word entity) {
    using Getter = std::uint32_t (*)(Word *, Word, Word);
    return slot<Getter>(bridge->environment, 0x320)(bridge->environment, entity, identifier(bridge, 0x2d8));
}
static Word item_at(GameAccessBridge *bridge, Word inventory, std::uint32_t index) {
    return indexed_method(bridge, inventory, 0x6e0, index);
}
static Word candidate(GameAccessBridge *bridge, Word item) { return object_method(bridge, item, 0x5f8); }
// 0x25de0, 0x27f10, 0x27f40 and 0x27f70.
static Word enchantments(GameAccessBridge *bridge, Word item) { return object_method(bridge, item, 0x608); }
static std::int32_t count(GameAccessBridge *bridge, Word list) {
    using Getter = std::int32_t (*)(Word *, Word, Word, ...);
    return slot<Getter>(bridge->environment, 0x188)(bridge->environment, list, identifier(bridge, 0xbf8));
}
static Word element(GameAccessBridge *bridge, Word list, std::uint32_t index) {
    return indexed_method(bridge, list, 0xc00, index);
}
static std::uint16_t kind(GameAccessBridge *bridge, Word tag, Word key) {
    using Getter = std::uint16_t (*)(Word *, Word, Word, ...);
    return slot<Getter>(bridge->environment, 0x170)(bridge->environment, tag, identifier(bridge, 0xc10), key);
}
static Word string_key(Word *environment, const char *key) {
    using Create = Word (*)(Word *, const char *);
    return slot<Create>(environment, 0x538)(environment, key);
}
extern "C" __declspec(dllexport) void recovered_bind_weapon_access(WeaponDependencies *dependencies) {
    *dependencies = {counter, recovered_game_inventory, recovered_game_inventory_index, item_at, candidate,
        recovered_game_item_numeric_id, enchantments, count, element, kind, string_key};
}

// 0x37f60 captures the environment for both strings, rereading its table at each call.
extern "C" __declspec(dllexport) std::uint32_t recovered_weapon_groups(GameAccessBridge *bridge,
    Word item, const WeaponDependencies *dependencies) {
    const auto list = dependencies->enchantments(bridge, item);
    if (!list) return 0;
    auto *environment = bridge->environment;
    const auto id = dependencies->string_key(environment, "id");
    if (!id) return 0;
    if (!dependencies->string_key(environment, "lvl")) return 0;
    const auto length = dependencies->count(bridge, list);
    std::uint32_t groups = 0;
    for (std::int32_t index = 0; index < length; ++index) {
        const auto tag = dependencies->element(bridge, list, static_cast<std::uint32_t>(index));
        switch (dependencies->kind(bridge, tag, id)) {
        case 16: groups |= 1; break;
        case 19: groups |= 2; break;
        case 20: groups |= 4; break;
        }
    }
    return groups;
}
// 0x38040 returns raw setting bytes or the policy lookup's pointer-derived result.
extern "C" __declspec(dllexport) Word recovered_weapon_allowed(GameAccessBridge *bridge,
    Word object, const WeaponSettings *settings, const ItemPolicyTable *table, const WeaponDependencies *dependencies) {
    if (!object) return settings->fist.current;
    const auto id = static_cast<std::uint32_t>(dependencies->identifier(bridge, object));
    const auto bit = id - 0x102u;
    if (bit < 29) {
        if ((0x02044600u >> bit) & 1u) return settings->swords.current;
        if ((0x10222001u >> bit) & 1u) return settings->axes.current;
    }
    return id ? recovered_item_policy_lookup(table, id) : settings->fist.current;
}
static bool group_allowed(std::uint32_t groups, const WeaponSettings *settings) {
    return ((groups & 1) && settings->sharpness.current) ||
        ((groups & 2) && settings->knockback.current) || (groups >= 4 && settings->fire_aspect.current);
}
// 0x37e50 reads a signed slot at a 32-byte stride; slot -1 selects the preceding fist record.
extern "C" __declspec(dllexport) std::uint8_t recovered_weapon_cache(GameAccessBridge *bridge,
    Word entity, std::uint32_t *groups_out, WeaponCache *cache, const WeaponSettings *settings,
    const ItemPolicyTable *table, const WeaponDependencies *dependencies) {
    const auto key = dependencies->counter(bridge, entity);
    if (key != cache->key) {
        cache->key = key;
        cache->groups = 0;
        const auto inventory = dependencies->inventory(bridge, entity);
        const auto selected = dependencies->selected_slot(bridge, inventory);
        const auto item = dependencies->item_at(bridge, inventory, static_cast<std::uint32_t>(selected));
        std::uint8_t allowed;
        if (!item) allowed = settings->fist.current;
        else {
            const auto groups = recovered_weapon_groups(bridge, item, dependencies);
            cache->groups = groups;
            const auto *bytes = reinterpret_cast<const std::uint8_t *>(settings);
            const auto offset = std::int64_t{32} + std::int64_t{selected} * 32 + 24;
            if (bytes[offset] || group_allowed(groups, settings)) allowed = 1;
            else {
                const auto object = dependencies->candidate(bridge, item);
                allowed = static_cast<std::uint8_t>(recovered_weapon_allowed(bridge, object, settings, table, dependencies));
            }
        }
        cache->allowed = allowed;
    }
    if (groups_out) std::memcpy(groups_out, &cache->groups, sizeof(cache->groups));
    return cache->allowed;
}
// 0x380b0 supplies a null output pointer to the same cache.
extern "C" __declspec(dllexport) std::uint8_t recovered_weapon_cached_query(GameAccessBridge *bridge,
    Word entity, WeaponCache *cache, const WeaponSettings *settings, const ItemPolicyTable *table,
    const WeaponDependencies *dependencies) {
    return recovered_weapon_cache(bridge, entity, nullptr, cache, settings, table, dependencies);
}
// 0x380c0 reloads the bridge after item lookup, then retains that bridge during classification and policy calls.
extern "C" __declspec(dllexport) std::uint32_t recovered_weapon_select(GameAccessBridge *const *bridge,
    Word inventory, const WeaponSettings *settings, const ItemPolicyTable *table, const WeaponDependencies *dependencies) {
    for (std::uint32_t index = 0; index < 9; ++index) {
        if (settings->slots[index].current) return index;
        const auto item = dependencies->item_at(*bridge, inventory, index);
        if (!item) continue;
        auto *current = *bridge;
        const auto groups = recovered_weapon_groups(current, item, dependencies);
        if (group_allowed(groups, settings)) return index;
        const auto object = dependencies->candidate(current, item);
        if (recovered_weapon_allowed(current, object, settings, table, dependencies) & 0xff) return index;
    }
    return 0xffffffffu;
}
// Registered cleanup 0x38190 clears the complete table after the release endpoint returns.
extern "C" __declspec(dllexport) void recovered_weapons_cleanup(ItemPolicyTable *table, void (*release)(void *)) {
    release(table->entries);
    *table = {};
}

// 0x381c0 retains the full return of the last slot checkbox.
extern "C" __declspec(dllexport) std::uint64_t recovered_weapons_typed_ui(std::uint64_t ui,
    std::uint64_t layout, WeaponSettings *settings, UiDirtyState *dirty, const WeaponUiEndpoints *endpoints) {
    const auto checkbox = [&](BooleanSetting &setting) {
        return recovered_checkbox_control(layout, ui, &setting, dirty, &endpoints->standard.controls);
    };
    endpoints->standard.section(ui, layout, "Item types");
    checkbox(settings->fist);
    checkbox(settings->swords);
    checkbox(settings->axes);
    recovered_list_control(layout, ui, &settings->extra_items, dirty, &endpoints->list);
    endpoints->standard.section(ui, layout, "Any item with");
    checkbox(settings->sharpness);
    checkbox(settings->knockback);
    checkbox(settings->fire_aspect);
    endpoints->standard.section(ui, layout, "Any item in");
    std::uint64_t result = 0;
    for (auto &setting : settings->slots) result = checkbox(setting);
    return result;
}
// 0x38330 uses one reusable two-byte buffer for the nine slot keys.
extern "C" __declspec(dllexport) void recovered_weapons_typed_settings(SettingsContext *context,
    WeaponSettings *settings, const SettingsDependencies *booleans, const ListSettingsDependencies *lists) {
    recovered_boolean_settings(context, "fist", &settings->fist, booleans);
    recovered_boolean_settings(context, "swords", &settings->swords, booleans);
    recovered_boolean_settings(context, "axes", &settings->axes, booleans);
    recovered_list_settings(context, "extra_items", &settings->extra_items.value, lists);
    recovered_boolean_settings(context, "enchant_sharpness", &settings->sharpness, booleans);
    recovered_boolean_settings(context, "enchant_knockback", &settings->knockback, booleans);
    recovered_boolean_settings(context, "enchant_fire_aspect", &settings->fire_aspect, booleans);
    char key[2] = {'\0', '\0'};
    for (std::uint32_t index = 0; index < 9; ++index) {
        key[0] = static_cast<char>('1' + index);
        recovered_boolean_settings(context, key, &settings->slots[index], booleans);
    }
}
