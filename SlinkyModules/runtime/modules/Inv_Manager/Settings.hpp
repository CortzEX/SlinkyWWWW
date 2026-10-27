#ifndef SLINKY_SHARE_567F7497ED1B3A94657C
#define SLINKY_SHARE_567F7497ED1B3A94657C
// Source-equivalent reconstruction from supplied native recovery evidence.
// Semantic names were assigned during reverse engineering. Original locals,
// class spelling, namespaces, templates and inline boundaries are not recovered.
// Algorithms below are expressed directly from the supplied C behavior bodies.
// External calls preserve explicit native ABI boundaries and exact RVAs.
// Historical finite verification is not a newly rerun equivalence claim.
// Named setting labels/options come from the separately identified runtime
// observation; captured current/saved values are never treated as defaults.

#include "../../native/verified/module_list_settings.hpp"
#include "../../native/verified/module_range_settings.hpp"
#include "../../native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Inv_Manager {
namespace Storage {
inline constexpr std::uint32_t nativeData_155590 = 0x155590;
inline constexpr std::uint32_t nativeData_155594 = 0x155594;
inline constexpr std::uint32_t nativeData_155598 = 0x155598;
inline constexpr std::uint32_t nativeData_15559c = 0x15559c;
inline constexpr std::uint32_t nativeData_1555a0 = 0x1555a0;
inline constexpr std::uint32_t nativeData_1555a4 = 0x1555a4;
inline constexpr std::uint32_t nativeData_155b40 = 0x155b40;
inline constexpr std::uint32_t nativeData_155b50 = 0x155b50;
inline constexpr std::uint32_t nativeData_155b60 = 0x155b60;
inline constexpr std::uint32_t moduleDescriptor = 0x2f4c40;
inline constexpr std::uint32_t delay_after_openRecord = 0x2f4e50;
inline constexpr std::uint32_t delay_after_openCurrent = 0x2f4e80;
inline constexpr std::uint32_t equip_armorRecord = 0x2f4e88;
inline constexpr std::uint32_t equip_armorCurrent = 0x2f4ea0;
inline constexpr std::uint32_t sort_hotbarRecord = 0x2f4ea8;
inline constexpr std::uint32_t sort_hotbarCurrent = 0x2f4ec0;
inline constexpr std::uint32_t hotbarSlot1Record = 0x2f4fb0;
inline constexpr std::uint32_t hotbarSlot1Current = 0x2f4fe0;
inline constexpr std::uint32_t hotbarSlot2Record = 0x2f4ff0;
inline constexpr std::uint32_t hotbarSlot2Current = 0x2f5020;
inline constexpr std::uint32_t hotbarSlot3Record = 0x2f5030;
inline constexpr std::uint32_t hotbarSlot3Current = 0x2f5060;
inline constexpr std::uint32_t hotbarSlot4Record = 0x2f5070;
inline constexpr std::uint32_t hotbarSlot4Current = 0x2f50a0;
inline constexpr std::uint32_t hotbarSlot5Record = 0x2f50b0;
inline constexpr std::uint32_t hotbarSlot5Current = 0x2f50e0;
inline constexpr std::uint32_t hotbarSlot6Record = 0x2f50f0;
inline constexpr std::uint32_t hotbarSlot6Current = 0x2f5120;
inline constexpr std::uint32_t hotbarSlot7Record = 0x2f5130;
inline constexpr std::uint32_t hotbarSlot7Current = 0x2f5160;
inline constexpr std::uint32_t hotbarSlot8Record = 0x2f5170;
inline constexpr std::uint32_t hotbarSlot8Current = 0x2f51a0;
inline constexpr std::uint32_t hotbarSlot9Record = 0x2f51b0;
inline constexpr std::uint32_t hotbarSlot9Current = 0x2f51e0;
inline constexpr std::uint32_t sort_hotbar_fallbackRecord = 0x2f51f0;
inline constexpr std::uint32_t sort_hotbar_fallbackCurrent = 0x2f5208;
inline constexpr std::uint32_t randomizeRecord = 0x2f5210;
inline constexpr std::uint32_t randomizeCurrent = 0x2f5228;
inline constexpr std::uint32_t speedRecord = 0x2f5230;
inline constexpr std::uint32_t nativeData_2f525c = 0x2f525c;
inline constexpr std::uint32_t speedCurrent = 0x2f5260;
inline constexpr std::uint32_t smart_speedRecord = 0x2f5268;
inline constexpr std::uint32_t smart_speedCurrent = 0x2f5280;
inline constexpr std::uint32_t inventoryPhase = 0x3049e0;
inline constexpr std::uint32_t nativeData_3049e4 = 0x3049e4;
inline constexpr std::uint32_t processedSlotMask = 0x3049e8;
inline constexpr std::uint32_t pendingActionKind = 0x3049f0;
inline constexpr std::uint32_t actionDestination = 0x3049f4;
inline constexpr std::uint32_t resumePhase = 0x3049f8;
inline constexpr std::uint32_t scanIndex = 0x3049fc;
inline constexpr std::uint32_t actionSourceSlot = 0x3049fd;
inline constexpr std::uint32_t advanceScanAfterAction = 0x3049fe;
inline constexpr std::uint32_t remainingDelay = 0x304a00;
inline constexpr std::uint32_t previousActionPosition = 0x304a08;
inline constexpr std::uint32_t nativeData_304a0c = 0x304a0c;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &delay_after_open() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::delay_after_openRecord);
    }
    NumberSetting &speed() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::speedRecord);
    }
    BooleanSetting &smart_speed() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::smart_speedRecord);
    }
    BooleanSetting &randomize() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::randomizeRecord);
    }
    BooleanSetting &equip_armor() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::equip_armorRecord);
    }
    BooleanSetting &sort_hotbar() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::sort_hotbarRecord);
    }
    BooleanSetting &sort_hotbar_fallback() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::sort_hotbar_fallbackRecord);
    }
    ChoiceSetting & hotbarSlot1() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot1Record);
    }
    ChoiceSetting & hotbarSlot2() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot2Record);
    }
    ChoiceSetting & hotbarSlot3() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot3Record);
    }
    ChoiceSetting & hotbarSlot4() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot4Record);
    }
    ChoiceSetting & hotbarSlot5() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot5Record);
    }
    ChoiceSetting & hotbarSlot6() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot6Record);
    }
    ChoiceSetting & hotbarSlot7() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot7Record);
    }
    ChoiceSetting & hotbarSlot8() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot8Record);
    }
    ChoiceSetting & hotbarSlot9() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot9Record);
    }
};
// Runtime-observed native labels for config key "1". Numeric values preserved.
enum class hotbarSlot1Mode : std::uint32_t{
    None = 0,
    Axe = 1,
    Blocks = 2,
    Bow = 3,
    Chest = 4,
    Ender_pearl = 5,
    Fireball = 6,
    Fishing_rod = 7,
    Flint_and_steel = 8,
    Golden_apple = 9,
    Healing_potion = 10,
    Jump_potion = 11,
    Ladders = 12,
    Lava_bucket = 13,
    Pickaxe = 14,
    Shears = 15,
    Shovel = 16,
    Snowballs_eggs = 17,
    Soup = 18,
    Speed_potion = 19,
    Stick = 20,
    Strength_potion = 21,
    Sword = 22,
    TNT = 23,
    Water_bucket = 24,
    Weapon = 25,
    Wool = 26,
};
// Runtime-observed native labels for config key "2". Numeric values preserved.
enum class hotbarSlot2Mode : std::uint32_t{
    None = 0,
    Axe = 1,
    Blocks = 2,
    Bow = 3,
    Chest = 4,
    Ender_pearl = 5,
    Fireball = 6,
    Fishing_rod = 7,
    Flint_and_steel = 8,
    Golden_apple = 9,
    Healing_potion = 10,
    Jump_potion = 11,
    Ladders = 12,
    Lava_bucket = 13,
    Pickaxe = 14,
    Shears = 15,
    Shovel = 16,
    Snowballs_eggs = 17,
    Soup = 18,
    Speed_potion = 19,
    Stick = 20,
    Strength_potion = 21,
    Sword = 22,
    TNT = 23,
    Water_bucket = 24,
    Weapon = 25,
    Wool = 26,
};
// Runtime-observed native labels for config key "3". Numeric values preserved.
enum class hotbarSlot3Mode : std::uint32_t{
    None = 0,
    Axe = 1,
    Blocks = 2,
    Bow = 3,
    Chest = 4,
    Ender_pearl = 5,
    Fireball = 6,
    Fishing_rod = 7,
    Flint_and_steel = 8,
    Golden_apple = 9,
    Healing_potion = 10,
    Jump_potion = 11,
    Ladders = 12,
    Lava_bucket = 13,
    Pickaxe = 14,
    Shears = 15,
    Shovel = 16,
    Snowballs_eggs = 17,
    Soup = 18,
    Speed_potion = 19,
    Stick = 20,
    Strength_potion = 21,
    Sword = 22,
    TNT = 23,
    Water_bucket = 24,
    Weapon = 25,
    Wool = 26,
};
// Runtime-observed native labels for config key "4". Numeric values preserved.
enum class hotbarSlot4Mode : std::uint32_t{
    None = 0,
    Axe = 1,
    Blocks = 2,
    Bow = 3,
    Chest = 4,
    Ender_pearl = 5,
    Fireball = 6,
    Fishing_rod = 7,
    Flint_and_steel = 8,
    Golden_apple = 9,
    Healing_potion = 10,
    Jump_potion = 11,
    Ladders = 12,
    Lava_bucket = 13,
    Pickaxe = 14,
    Shears = 15,
    Shovel = 16,
    Snowballs_eggs = 17,
    Soup = 18,
    Speed_potion = 19,
    Stick = 20,
    Strength_potion = 21,
    Sword = 22,
    TNT = 23,
    Water_bucket = 24,
    Weapon = 25,
    Wool = 26,
};
// Runtime-observed native labels for config key "5". Numeric values preserved.
enum class hotbarSlot5Mode : std::uint32_t{
    None = 0,
    Axe = 1,
    Blocks = 2,
    Bow = 3,
    Chest = 4,
    Ender_pearl = 5,
    Fireball = 6,
    Fishing_rod = 7,
    Flint_and_steel = 8,
    Golden_apple = 9,
    Healing_potion = 10,
    Jump_potion = 11,
    Ladders = 12,
    Lava_bucket = 13,
    Pickaxe = 14,
    Shears = 15,
    Shovel = 16,
    Snowballs_eggs = 17,
    Soup = 18,
    Speed_potion = 19,
    Stick = 20,
    Strength_potion = 21,
    Sword = 22,
    TNT = 23,
    Water_bucket = 24,
    Weapon = 25,
    Wool = 26,
};
// Runtime-observed native labels for config key "6". Numeric values preserved.
enum class hotbarSlot6Mode : std::uint32_t{
    None = 0,
    Axe = 1,
    Blocks = 2,
    Bow = 3,
    Chest = 4,
    Ender_pearl = 5,
    Fireball = 6,
    Fishing_rod = 7,
    Flint_and_steel = 8,
    Golden_apple = 9,
    Healing_potion = 10,
    Jump_potion = 11,
    Ladders = 12,
    Lava_bucket = 13,
    Pickaxe = 14,
    Shears = 15,
    Shovel = 16,
    Snowballs_eggs = 17,
    Soup = 18,
    Speed_potion = 19,
    Stick = 20,
    Strength_potion = 21,
    Sword = 22,
    TNT = 23,
    Water_bucket = 24,
    Weapon = 25,
    Wool = 26,
};
// Runtime-observed native labels for config key "7". Numeric values preserved.
enum class hotbarSlot7Mode : std::uint32_t{
    None = 0,
    Axe = 1,
    Blocks = 2,
    Bow = 3,
    Chest = 4,
    Ender_pearl = 5,
    Fireball = 6,
    Fishing_rod = 7,
    Flint_and_steel = 8,
    Golden_apple = 9,
    Healing_potion = 10,
    Jump_potion = 11,
    Ladders = 12,
    Lava_bucket = 13,
    Pickaxe = 14,
    Shears = 15,
    Shovel = 16,
    Snowballs_eggs = 17,
    Soup = 18,
    Speed_potion = 19,
    Stick = 20,
    Strength_potion = 21,
    Sword = 22,
    TNT = 23,
    Water_bucket = 24,
    Weapon = 25,
    Wool = 26,
};
// Runtime-observed native labels for config key "8". Numeric values preserved.
enum class hotbarSlot8Mode : std::uint32_t{
    None = 0,
    Axe = 1,
    Blocks = 2,
    Bow = 3,
    Chest = 4,
    Ender_pearl = 5,
    Fireball = 6,
    Fishing_rod = 7,
    Flint_and_steel = 8,
    Golden_apple = 9,
    Healing_potion = 10,
    Jump_potion = 11,
    Ladders = 12,
    Lava_bucket = 13,
    Pickaxe = 14,
    Shears = 15,
    Shovel = 16,
    Snowballs_eggs = 17,
    Soup = 18,
    Speed_potion = 19,
    Stick = 20,
    Strength_potion = 21,
    Sword = 22,
    TNT = 23,
    Water_bucket = 24,
    Weapon = 25,
    Wool = 26,
};
// Runtime-observed native labels for config key "9". Numeric values preserved.
enum class hotbarSlot9Mode : std::uint32_t{
    None = 0,
    Axe = 1,
    Blocks = 2,
    Bow = 3,
    Chest = 4,
    Ender_pearl = 5,
    Fireball = 6,
    Fishing_rod = 7,
    Flint_and_steel = 8,
    Golden_apple = 9,
    Healing_potion = 10,
    Jump_potion = 11,
    Ladders = 12,
    Lava_bucket = 13,
    Pickaxe = 14,
    Shears = 15,
    Shovel = 16,
    Snowballs_eggs = 17,
    Soup = 18,
    Speed_potion = 19,
    Stick = 20,
    Strength_potion = 21,
    Sword = 22,
    TNT = 23,
    Water_bucket = 24,
    Weapon = 25,
    Wool = 26,
};
} // namespace reconstruction::Inv_Manager
#endif // SLINKY_SHARE_567F7497ED1B3A94657C
