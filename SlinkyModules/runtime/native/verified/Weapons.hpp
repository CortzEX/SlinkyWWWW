#ifndef SLINKY_SHARE_C9FB24679C19A644C3EA
#define SLINKY_SHARE_C9FB24679C19A644C3EA
#include "module_game_access.hpp"
#include "module_item_policy_lookup.hpp"
#include "module_list_ui.hpp"

struct WeaponSettings {
    BooleanSetting fist;
    BooleanSetting slots[9];
    BooleanSetting sharpness, knockback, fire_aspect, axes, swords;
    ListUiSetting extra_items;
};
struct WeaponUiEndpoints {
    SettingsUiEndpoints standard;
    ListUiEndpoint list;
};
struct WeaponCache {
    std::uint32_t key;
    std::uint8_t allowed, padding[3];
    std::uint32_t groups, reserved;
};
struct WeaponDependencies {
    std::uint32_t (*counter)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*inventory)(GameAccessBridge *, std::uintptr_t);
    std::int32_t (*selected_slot)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*item_at)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    std::uintptr_t (*candidate)(GameAccessBridge *, std::uintptr_t);
    std::int32_t (*identifier)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*enchantments)(GameAccessBridge *, std::uintptr_t);
    std::int32_t (*count)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*element)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    std::uint16_t (*kind)(GameAccessBridge *, std::uintptr_t, std::uintptr_t);
    std::uintptr_t (*string_key)(std::uintptr_t *, const char *);
};
static_assert(offsetof(WeaponSettings, slots) == 32);
static_assert(offsetof(WeaponSettings, sharpness) == 320);
static_assert(offsetof(WeaponSettings, axes) == 416);
static_assert(offsetof(WeaponSettings, swords) == 448);
static_assert(offsetof(WeaponSettings, extra_items) == 480);
static_assert(sizeof(WeaponSettings) == 584);
static_assert(sizeof(WeaponCache) == 16);
static_assert(offsetof(WeaponCache, allowed) == 4);
static_assert(offsetof(WeaponCache, groups) == 8);
static_assert(sizeof(WeaponDependencies) == 88);

extern "C" {
__declspec(dllexport) void recovered_bind_weapon_access(WeaponDependencies *);
__declspec(dllexport) std::uint32_t recovered_weapon_groups(GameAccessBridge *, std::uintptr_t item, const WeaponDependencies *);
__declspec(dllexport) std::uintptr_t recovered_weapon_allowed(GameAccessBridge *, std::uintptr_t candidate,
    const WeaponSettings *, const ItemPolicyTable *, const WeaponDependencies *);
__declspec(dllexport) std::uint8_t recovered_weapon_cache(GameAccessBridge *, std::uintptr_t entity,
    std::uint32_t *groups_out, WeaponCache *, const WeaponSettings *, const ItemPolicyTable *, const WeaponDependencies *);
__declspec(dllexport) std::uint8_t recovered_weapon_cached_query(GameAccessBridge *, std::uintptr_t entity,
    WeaponCache *, const WeaponSettings *, const ItemPolicyTable *, const WeaponDependencies *);
__declspec(dllexport) std::uint32_t recovered_weapon_select(GameAccessBridge *const *bridge, std::uintptr_t inventory,
    const WeaponSettings *, const ItemPolicyTable *, const WeaponDependencies *);
__declspec(dllexport) void recovered_weapons_cleanup(ItemPolicyTable *, void (*release)(void *));
__declspec(dllexport) std::uint64_t recovered_weapons_typed_ui(std::uint64_t ui, std::uint64_t layout,
    WeaponSettings *, UiDirtyState *, const WeaponUiEndpoints *);
__declspec(dllexport) void recovered_weapons_typed_settings(SettingsContext *, WeaponSettings *,
    const SettingsDependencies *, const ListSettingsDependencies *);
}
#endif // SLINKY_SHARE_C9FB24679C19A644C3EA
