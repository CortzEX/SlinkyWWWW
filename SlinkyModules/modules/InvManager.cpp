// Inv Manager

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Inv_Manager.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Inv_Manager.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Inv Manager: lib_win settings 0x476e0.
static constexpr SettingsStep settings_steps_Surface_Inv_Manager[] = {
    {SettingsControl::number, "delay_after_open", 0x2f4e50},
    {SettingsControl::number, "speed", 0x2f5230},
    {SettingsControl::boolean, "smart_speed", 0x2f5268},
    {SettingsControl::boolean, "randomize", 0x2f5210},
    {SettingsControl::boolean, "equip_armor", 0x2f4e88},
    {SettingsControl::boolean, "sort_hotbar", 0x2f4ea8},
    {SettingsControl::boolean, "sort_hotbar_fallback", 0x2f51f0},
    {SettingsControl::choice, "1", 0x2f4fb0},
    {SettingsControl::choice, "2", 0x2f4ff0},
    {SettingsControl::choice, "3", 0x2f5030},
    {SettingsControl::choice, "4", 0x2f5070},
    {SettingsControl::choice, "5", 0x2f50b0},
    {SettingsControl::choice, "6", 0x2f50f0},
    {SettingsControl::choice, "7", 0x2f5130},
    {SettingsControl::choice, "8", 0x2f5170},
    {SettingsControl::choice, "9", 0x2f51b0},
};
static constexpr ModuleSurface surface_Surface_Inv_Manager{
    nullptr, 0, settings_steps_Surface_Inv_Manager, std::size(settings_steps_Surface_Inv_Manager)};

extern "C" __declspec(dllexport) void
recovered_inv_manager_settings(SettingsContext *context, std::uint8_t *image,
                               const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Inv_Manager, context, image, *dependencies);
}

// Inv Manager: lib_win runtime UI 0x47560.
extern "C" __declspec(dllexport) void
recovered_inv_manager_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                         const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f4e50);
    dependencies->number(layout, ui, image + 0x2f5230);
    dependencies->checkbox(layout, ui, image + 0x2f5268);
    dependencies->checkbox(layout, ui, image + 0x2f5210);
    dependencies->section(ui, layout, "Equip armor");
    dependencies->checkbox(layout, ui, image + 0x2f4e88);
    dependencies->section(ui, layout, "Sort hotbar");
    dependencies->checkbox(layout, ui, image + 0x2f4ea8);
    if (image[0x2f4ec0] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2f51f0);
        dependencies->choice(layout, ui, image + 0x2f4fb0);
        dependencies->choice(layout, ui, image + 0x2f4ff0);
        dependencies->choice(layout, ui, image + 0x2f5030);
        dependencies->choice(layout, ui, image + 0x2f5070);
        dependencies->choice(layout, ui, image + 0x2f50b0);
        dependencies->choice(layout, ui, image + 0x2f50f0);
        dependencies->choice(layout, ui, image + 0x2f5130);
        dependencies->choice(layout, ui, image + 0x2f5170);
        dependencies->choice(layout, ui, image + 0x2f51b0);
    }
}
// END SOURCE native/verified/surfaces/Surface_Inv_Manager.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Inv_Manager/inv_manager.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_567F7497ED1B3A94657C
#define SLINKY_SHARE_567F7497ED1B3A94657C
// BEGIN SOURCE modules/Inv_Manager/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
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
    ChoiceSetting &hotbarSlot1() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot1Record);
    }
    ChoiceSetting &hotbarSlot2() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot2Record);
    }
    ChoiceSetting &hotbarSlot3() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot3Record);
    }
    ChoiceSetting &hotbarSlot4() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot4Record);
    }
    ChoiceSetting &hotbarSlot5() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot5Record);
    }
    ChoiceSetting &hotbarSlot6() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot6Record);
    }
    ChoiceSetting &hotbarSlot7() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot7Record);
    }
    ChoiceSetting &hotbarSlot8() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot8Record);
    }
    ChoiceSetting &hotbarSlot9() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::hotbarSlot9Record);
    }
};
// Runtime-observed native labels for config key "1". Numeric values preserved.
enum class hotbarSlot1Mode : std::uint32_t {
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
enum class hotbarSlot2Mode : std::uint32_t {
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
enum class hotbarSlot3Mode : std::uint32_t {
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
enum class hotbarSlot4Mode : std::uint32_t {
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
enum class hotbarSlot5Mode : std::uint32_t {
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
enum class hotbarSlot6Mode : std::uint32_t {
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
enum class hotbarSlot7Mode : std::uint32_t {
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
enum class hotbarSlot8Mode : std::uint32_t {
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
enum class hotbarSlot9Mode : std::uint32_t {
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
// END SOURCE modules/Inv_Manager/Settings.hpp

#endif // SLINKY_SHARE_567F7497ED1B3A94657C

#include <emmintrin.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
namespace reconstruction::Inv_Manager {
using dependency = native_binding::WordEndpoints;
// Native entry 0x9ee0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t rotationDistance(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                                 uint64_t a4) {
    return api(0x9ee0, a0, a1, a2, a3, a4);
}
// Native entry 0xa050; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t randomRangeBits(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                                uint64_t a4) {
    return api(0xa050, a0, a1, a2, a3, a4);
}
// Native entry 0xa3e0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t randomRangeSample(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                  uint64_t a3, uint64_t a4) {
    return api(0xa3e0, a0, a1, a2, a3, a4);
}
// Native entry 0x22c90; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t currentScreen(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                              uint64_t a4) {
    return api(0x22c90, a0, a1, a2, a3, a4);
}
// Native entry 0x25b80; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t inventoryScreenPredicate(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                         uint64_t a3, uint64_t a4) {
    return api(0x25b80, a0, a1, a2, a3, a4);
}
// Native entry 0x25be0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t inventoryClick(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                               uint64_t a4) {
    return api(0x25be0, a0, a1, a2, a3, a4);
}
// Native entry 0x2aad0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_2aad0(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4) {
    return api(0x2aad0, a0, a1, a2, a3, a4);
}

static uint64_t loadWord64(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t loadWord32(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static float loadFloat(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static void storeWord64(void *p, uint64_t v) {
    memcpy(p, &v, 8);
}
static void storeWord32(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
static void storeFloat(void *p, float v) {
    memcpy(p, &v, 4);
}
static float floatFromWord(uint64_t v) {
    uint32_t n = (uint32_t)v;
    return loadFloat(&n);
}
static uint32_t floatBits(float v) {
    return loadWord32(&v);
}
static float add(float a, float b) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float mul(float a, float b) {
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float divide(float a, float b) {
    return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float maximum(float a, float b) {
    return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float random_factor(uint8_t *image, dependency call, uint32_t upper) {
    uint64_t sample = randomRangeBits(call, loadWord32(image + Storage::nativeData_15559c),
                                      loadWord32(image + upper), 0, 0, 0);
    return floatFromWord(randomRangeSample(call, sample, 0, 0, 0, 0));
}
static void delay(uint8_t *image, dependency call, uint64_t angle) {
    uint64_t previous = loadWord64(image + Storage::previousActionPosition);
    float amount = divide(loadFloat(image + Storage::nativeData_2f525c),
                          loadFloat(image + Storage::speedCurrent));
    float distance = floatFromWord(rotationDistance(call, angle, previous, 0, 0, 0));
    if (image[Storage::smart_speedCurrent] == 1)
        amount = mul(amount, maximum(mul(distance, loadFloat(image + Storage::nativeData_155598)),
                                     loadFloat(image + Storage::nativeData_15559c)));
    if (image[Storage::randomizeCurrent] == 1) {
        float factor = random_factor(image, call, Storage::nativeData_1555a0);
        amount = mul(amount, factor);
    }
    storeFloat(image + Storage::remainingDelay,
               add(amount, loadFloat(image + Storage::remainingDelay)));
    storeWord64(image + Storage::previousActionPosition, angle);
}
static void advance(uint8_t *image, uint32_t state) {
    storeWord32(image + Storage::inventoryPhase, state);
    memset(image + Storage::nativeData_3049e4, 0, 16);
    memset(image + Storage::pendingActionKind, 0, 16);
}
#ifndef SLINKY_SHARE_A774453B3D84C8726DFE
#define SLINKY_SHARE_A774453B3D84C8726DFE
// BEGIN SOURCE modules/Inv_Manager/InventorySelection.inc.hpp
// Owned interval candidates 0x47870..0x485df, recovered from Inv_Manager.cpp
// and audited against the separately labelled runtime_observed_locals.asm.
// Scalar return registers are narrowed only where original callers consume
// AL/AX.
static int32_t signedWord(uint32_t value) {
    int32_t result;
    memcpy(&result, &value, 4);
    return result;
}
static double imageDouble(uint8_t *image, uint32_t rva) {
    uint64_t bits = loadWord64(image + rva);
    double value;
    memcpy(&value, &bits, 8);
    return value;
}
static double dadd(double a, double b) {
    return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double dsub(double a, double b) {
    return _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double dmul(double a, double b) {
    return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double ddiv(double a, double b) {
    return _mm_cvtsd_f64(_mm_div_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static float narrow(double a) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(a)));
}
static uint64_t environmentOf(uint8_t *ctx) {
    return loadWord64(reinterpret_cast<void *>(loadWord64(ctx) + 8));
}
// JNI environment vtable +0x538 NewStringUTF; +0x568 GetObjectArrayElement.
static uint64_t nameTag(uint64_t environment, uint8_t *image, uint32_t rva, dependency call) {
    return call(0x80000538, environment, uintptr_t(image + rva), 0, 0, 0);
}
static uint64_t arrayElement(uint64_t environment, uint64_t array, uint32_t index,
                             dependency call) {
    return call(0x80000568, environment, array, index, 0, 0);
}
static uint64_t stackIdentity(uint8_t *ctx, uint64_t stack, dependency call) {
    uint64_t item = call(0x25d10, loadWord64(ctx), stack, 0, 0, 0);
    if (!item)
        return 0;
    uint32_t type = uint32_t(call(0x25c50, loadWord64(ctx), item, 0, 0, 0));
    int32_t damage = signedWord(uint32_t(call(0x25dc0, loadWord64(ctx), stack, 0, 0, 0)));
    return (uint64_t(type) << 32) | uint64_t(int64_t(damage));
}
// RVA 0x48360: low word category, high word material tier.
static uint64_t classifyToolMaterial(uint32_t item) {
    uint32_t category = 1, tier = 1;
    switch (item) {
    case 0x100:
        category = 16;
        tier = 3;
        break;
    case 0x101:
        category = 14;
        tier = 3;
        break;
    case 0x102:
        tier = 3;
        break;
    case 0x10b:
        category = 22;
        tier = 3;
        break;
    case 0x10c:
        category = 22;
        break;
    case 0x10d:
        category = 16;
        break;
    case 0x10e:
        category = 14;
        break;
    case 0x10f:
        break;
    case 0x110:
        category = 22;
        tier = 2;
        break;
    case 0x111:
        category = 16;
        tier = 2;
        break;
    case 0x112:
        category = 14;
        tier = 2;
        break;
    case 0x113:
        tier = 2;
        break;
    case 0x114:
        category = 22;
        tier = 5;
        break;
    case 0x115:
        category = 16;
        tier = 5;
        break;
    case 0x116:
        category = 14;
        tier = 5;
        break;
    case 0x117:
        tier = 5;
        break;
    case 0x11b:
        category = 22;
        tier = 4;
        break;
    case 0x11c:
        category = 16;
        tier = 4;
        break;
    case 0x11d:
        category = 14;
        tier = 4;
        break;
    case 0x11e:
        tier = 4;
        break;
    case 0x167:
        category = 15;
        break;
    default:
        category = 0;
        tier = 0;
    }
    return uint64_t(category) | (uint64_t(tier) << 32);
}
// RVA 0x484d0. Coefficient table indexes tag id; accumulation wraps at 32 bits.
static uint32_t weightedTagScore(uint8_t *ctx, uint64_t tags, uint8_t *coefficients, uint8_t *image,
                                 dependency call) {
    if (!tags)
        return 0;
    uint64_t environment = environmentOf(ctx);
    uint64_t idName = nameTag(environment, image, 0x155b94, call);
    if (!idName)
        return 0;
    uint64_t levelName = nameTag(environment, image, 0x155b97, call);
    if (!levelName)
        return 0;
    int32_t count = signedWord(uint32_t(call(0x27f10, loadWord64(ctx), tags, 0, 0, 0)));
    if (count <= 0)
        return 0;
    uint32_t total = 0;
    for (uint32_t index = 0; index != uint32_t(count); ++index) {
        uint64_t tag = call(0x27f40, loadWord64(ctx), tags, index, 0, 0);
        uint16_t id = uint16_t(call(0x27f70, loadWord64(ctx), tag, idName, 0, 0));
        uint8_t coefficient = id < 63 ? coefficients[id] : 0;
        if (coefficient) {
            uint32_t level = uint32_t(call(0x27f70, loadWord64(ctx), tag, levelName, 0, 0));
            uint32_t score = uint32_t(coefficient) * level;
            if (int16_t(uint16_t(level)) < 0)
                score = 0;
            total += score;
        }
    }
    return total;
}
// RVA 0x48080. Category numbering is native configuration numbering.
static uint16_t scoreItemCategory(uint8_t *ctx, uint32_t category, uint32_t item, uint32_t damage,
                                  uint64_t tags, uint8_t itemFlag, uint8_t *image,
                                  dependency call) {
    if (category - 1u > 25u)
        return 0;
    switch (category) {
    case 2:
        if (item - 1u > 0xa1u)
            return 0;
        switch (item) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 0x11:
        case 0x12:
        case 0x14:
        case 0x18:
        case 0x23:
        case 0x2d:
        case 0x31:
        case 0x4e:
        case 0x57:
        case 0x5f:
        case 0x62:
        case 0x79:
        case 0x7d:
        case 0x85:
        case 0x9b:
        case 0x9f:
        case 0xa2:
            return 1;
        default:
            return 0;
        }
    case 3:
        return item == 0x105
                   ? uint16_t(weightedTagScore(ctx, tags, image + 0x155d30, image, call) + 1)
                   : 0;
    case 4:
        return item == 0x36;
    case 5:
        return item == 0x170 ? uint16_t(2u - itemFlag) : 0;
    case 6:
        return item == 0x181;
    case 7:
        return item == 0x15a;
    case 8:
        return item == 0x103;
    case 9:
        return item == 0x142 ? uint16_t((damage == 1) + 1) : 0;
    case 10:
    case 11:
    case 19:
    case 21: {
        if (item != 0x175)
            return 0;
        uint16_t base;
        switch (damage & 15) {
        case 1:
            if (category != 10)
                return 0;
            base = 1;
            break;
        case 5:
            if (category != 10)
                return 0;
            base = 2;
            break;
        case 2:
            if (category != 19)
                return 0;
            base = 1;
            break;
        case 9:
            if (category != 21)
                return 0;
            base = 1;
            break;
        case 11:
            if (category != 11)
                return 0;
            base = 1;
            break;
        default:
            return 0;
        }
        return uint16_t(((damage >> 6) & 1) + base + ((damage >> 5) & 1));
    }
    case 12:
        return item == 0x41;
    case 13:
        return item == 0x147;
    case 17:
        return item == 0x14c || item == 0x158;
    case 18:
        return item == 0x19d || item == 0x11a;
    case 20:
        return item == 0x118;
    case 23:
        return item == 0x2e;
    case 24:
        return item == 0x146;
    case 26:
        return item == 0x23;
    case 22: {
        uint64_t classified = classifyToolMaterial(item);
        if (uint32_t(classified) != 22)
            return 0;
        uint32_t tier = image[0x155d1e + (classified >> 32)];
        return uint16_t(weightedTagScore(ctx, tags, image + 0x155ce0, image, call) + tier * 40u +
                        160u);
    }
    case 25: {
        uint64_t classified = classifyToolMaterial(item);
        uint16_t preference;
        switch (uint32_t(classified)) {
        case 1:
            preference = 3;
            break;
        case 14:
            preference = 2;
            break;
        case 16:
            preference = 1;
            break;
        case 22:
            preference = 4;
            break;
        default:
            preference = 0;
        }
        uint32_t amount = (uint32_t(preference) + image[0x155d1e + (classified >> 32)]) * 40;
        return uint16_t(weightedTagScore(ctx, tags, image + 0x155ce0, image, call) + amount);
    }
    default: {
        uint64_t classified = classifyToolMaterial(item);
        if (category != uint32_t(classified))
            return 0;
        uint32_t amount = uint32_t(classified >> 32) * 100u;
        return uint16_t(weightedTagScore(ctx, tags, image + 0x155d70, image, call) + amount);
    }
    }
}
// RVA 0x47f90. Strict category wins in high 16 bits when the hotbar fallback
// setting is set.
static uint32_t scoreStackPolicy(uint8_t *ctx, uint64_t stack, uint32_t category, uint8_t *image,
                                 dependency call) {
    uint64_t item = call(0x25d10, loadWord64(ctx), stack, 0, 0, 0);
    if (!item)
        return 0;
    uint32_t type = uint32_t(call(0x25c50, loadWord64(ctx), item, 0, 0, 0));
    uint32_t damage = uint32_t(call(0x25dc0, loadWord64(ctx), stack, 0, 0, 0));
    uint64_t tags = call(0x25de0, loadWord64(ctx), stack, 0, 0, 0);
    uint8_t flag = uint8_t(call(0x25e80, loadWord64(ctx), stack, 0, 0, 0));
    uint16_t score = scoreItemCategory(ctx, category, type, damage, tags, flag, image, call);
    if (image[0x2f5208] == 1) {
        if (score)
            return uint32_t(score) << 16;
        uint32_t fallback;
        if (category == 22)
            fallback = 25;
        else if (category == 17)
            fallback = 7;
        else if (category == 7)
            fallback = 17;
        else
            return 0;
        return scoreItemCategory(ctx, fallback, type, damage, tags, flag, image, call);
    }
    return score;
}
// RVA 0x47cf0. Score combines armor material and protection enchantments.
static uint32_t armorScore(uint8_t *ctx, uint64_t stack, uint32_t armorSlot, uint8_t *image,
                           dependency call) {
    if (!stack)
        return 0;
    uint64_t item = call(0x25d10, loadWord64(ctx), stack, 0, 0, 0);
    if (!item)
        return 0;
    uint32_t type = uint32_t(call(0x25c50, loadWord64(ctx), item, 0, 0, 0));
    uint32_t index = type - 0x12a;
    if (index >= 20 || type + loadWord32(image + 0x155e70 + index * 4) != armorSlot)
        return 0;
    uint64_t material = loadWord64(image + 0x155ec0 + index * 8);
    uint64_t tags = call(0x25de0, loadWord64(ctx), stack, 0, 0, 0);
    uint8_t base = image[0x155b80 + material * 4 + armorSlot];
    double enchantments = 0;
    if (tags) {
        uint64_t environment = environmentOf(ctx),
                 idName = nameTag(environment, image, 0x155b94, call);
        if (idName) {
            uint64_t levelName = nameTag(environment, image, 0x155b97, call);
            if (levelName) {
                int32_t count = signedWord(uint32_t(call(0x27f10, loadWord64(ctx), tags, 0, 0, 0)));
                double weight = imageDouble(image, 0x1555c0), scale = imageDouble(image, 0x1555c8),
                       divisor = imageDouble(image, 0x1555d0);
                float fraction = loadFloat(image + 0x1555d8);
                float other = 0, protection = 0;
                for (uint32_t n = 0; signedWord(n) < count; ++n) {
                    uint64_t tag = call(0x27f40, loadWord64(ctx), tags, n, 0, 0);
                    uint16_t id = uint16_t(call(0x27f70, loadWord64(ctx), tag, idName, 0, 0));
                    int16_t level =
                        int16_t(uint16_t(call(0x27f70, loadWord64(ctx), tag, levelName, 0, 0)));
                    if (level < 0)
                        continue;
                    if (uint32_t(id) - 1u < 4)
                        other = narrow(dadd(dmul(double(level), weight), double(other)));
                    else if (id == 0) {
                        uint32_t power = uint32_t(level) * uint32_t(level) + 6u;
                        double value = ddiv(dmul(double(signedWord(power)), scale), divisor);
                        uint32_t quantized = uint32_t(_mm_cvttsd_si64(_mm_set_sd(value)));
                        if (quantized >= 25)
                            quantized = 25;
                        uint32_t combined = (quantized >> 1) + ((quantized + 1) & 0x3e);
                        protection = mul(float(signedWord(combined)), fraction);
                    }
                }
                if (count > 0)
                    enchantments = double(add(other, protection));
            }
        }
    }
    double factor = imageDouble(image, 0x1555e0), one = imageDouble(image, 0x1555e8);
    double materialRemainder = dsub(one, dmul(double(base), factor));
    double enchantRemainder = dsub(one, dmul(enchantments, factor));
    float combined = narrow(dsub(one, dmul(enchantRemainder, materialRemainder)));
    float scaled = mul(combined, loadFloat(image + 0x1555f0));
    return uint32_t(_mm_cvttss_si64(_mm_set_ss(scaled)));
}
// RVA 0x47870: plan one armor upgrade, retaining first strictly better score.
static bool planArmorUpgrade(uint8_t *ctx, uint8_t *action, uint8_t *image, dependency call) {
    uint8_t armor = action[0x1c];
    uint64_t inventory = call(0x23f40, loadWord64(ctx), loadWord64(ctx + 0x28), 0, 0, 0);
    uint64_t equipped = call(0x26140, loadWord64(ctx), inventory, 39u - armor, 0, 0);
    uint64_t array = call(0x25ab0, loadWord64(ctx), inventory, 0, 0, 0),
             environment = environmentOf(ctx);
    uint32_t bestScore = armorScore(ctx, equipped, armor, image, call), best = UINT32_MAX;
    for (uint32_t slot = 0; slot != 36; ++slot) {
        uint64_t stack = arrayElement(environment, array, slot, call);
        uint32_t score = armorScore(ctx, stack, armor, image, call);
        if (bestScore < score) {
            bestScore = score;
            best = slot;
        }
    }
    if (best == UINT32_MAX)
        return false;
    if (!equipped) {
        storeWord64(action + 0x10, 0);
        action[0x1d] = uint8_t(best < 9 ? best + 36 : best);
    } else {
        storeWord32(action + 0x10, best < 9 ? 1 : 2);
        action[0x14] = uint8_t(best < 9 ? best : armor + 5);
        memset(action + 0x15, 0, 3);
        action[0x1d] = uint8_t(best < 9 ? action[0x1c] + 5 : best);
    }
    return true;
}
// RVA 0x479c0: compare total stack scores and compatible merge scores.
static bool planHotbarUpgrade(uint8_t *ctx, uint8_t *action, uint8_t *image, dependency call) {
    uint8_t destination = action[0x1c];
    uint32_t category = loadWord32(image + 0x2f4fe0 + uint32_t(destination) * 64);
    if (!category)
        return false;
    uint64_t inventory = call(0x23f40, loadWord64(ctx), loadWord64(ctx + 0x28), 0, 0, 0),
             array = call(0x25ab0, loadWord64(ctx), inventory, 0, 0, 0),
             environment = environmentOf(ctx);
    uint64_t original = arrayElement(environment, array, destination, call);
    uint32_t originalCount = 0, maximumCount = 0, originalScore = 0;
    uint64_t identity = 0;
    if (original) {
        originalCount = uint32_t(call(0x25d70, loadWord64(ctx), original, 0, 0, 0));
        maximumCount = uint32_t(call(0x25e10, loadWord64(ctx), original, 0, 0, 0));
        identity = stackIdentity(ctx, original, call);
        originalScore = scoreStackPolicy(ctx, original, category, image, call);
    }
    bool hasEmpty = false;
    for (uint32_t slot = 9; slot != 36; ++slot) {
        if (!arrayElement(environment, array, slot, call)) {
            hasEmpty = true;
            break;
        }
    }
    if (signedWord(originalCount) <= 0)
        originalCount = 0;
    uint32_t bestScore = originalCount * originalScore, best = destination,
             mergeFlag = hasEmpty ? 0 : 36;
    for (uint32_t slot = 0; slot != 36; ++slot) {
        if (slot == destination || ((loadWord64(action + 8) >> (slot & 63)) & 1))
            continue;
        uint64_t stack = arrayElement(environment, array, slot, call);
        if (!stack)
            continue;
        uint32_t count = uint32_t(call(0x25d70, loadWord64(ctx), stack, 0, 0, 0));
        uint64_t candidateIdentity = stackIdentity(ctx, stack, call);
        uint32_t mergedScore = 0;
        if (signedWord(originalCount) < signedWord(maximumCount) &&
            signedWord(count) < signedWord(maximumCount) && candidateIdentity == identity &&
            uint8_t(call(0x25e40, loadWord64(ctx), original, stack, 0, 0))) {
            uint32_t combined = count + originalCount;
            if (signedWord(combined) >= signedWord(maximumCount))
                combined = maximumCount;
            mergedScore = combined * originalScore;
        }
        uint32_t score = scoreStackPolicy(ctx, stack, category, image, call) * count,
                 previous = score - 1u;
        bool merge = previous < mergedScore;
        if (merge)
            score = mergedScore;
        if (bestScore < score) {
            bool admissible = slot >= 9 || hasEmpty || !merge;
            if (admissible) {
                best = slot;
                bestScore = score;
                mergeFlag = merge ? 1 : 0;
            } else
                mergeFlag &= 0xff;
        }
    }
    bool changed = best != destination;
    if (!changed && bestScore == 0)
        return false;
    if (changed) {
        memset(action + 0x15, 0, 3);
        storeWord32(action + 0x10, uint8_t(~uint8_t(mergeFlag)) & 1);
        action[0x14] = (mergeFlag & 1) ? 0 : destination;
        action[0x1d] = uint8_t(best < 9 ? best + 36 : best);
    }
    uint32_t word = 1u << (destination & 31);
    int64_t mask = int64_t(signedWord(word));
    storeWord64(action + 8, loadWord64(action + 8) | uint64_t(mask));
    return changed;
}
// END SOURCE modules/Inv_Manager/InventorySelection.inc.hpp

#endif // SLINKY_SHARE_A774453B3D84C8726DFE

void advanceInventoryActions(uint8_t *event, uint8_t *image, dependency call) {
    uint8_t *ctx = (uint8_t *)(uintptr_t)loadWord64(event + 8);
    uint64_t screen = currentScreen(call, loadWord64(ctx), loadWord64(ctx + 0x18), 0, 0, 0);
    if (!screen || !(uint8_t)inventoryScreenPredicate(call, loadWord64(ctx), screen, 0, 0, 0)) {
        memset(image + Storage::pendingActionKind, 0, 16);
        memset(image + Storage::inventoryPhase, 0, 16);
        storeFloat(image + Storage::remainingDelay,
                   loadFloat(image + Storage::delay_after_openCurrent));
        if (image[Storage::randomizeCurrent] == 1) {
            float factor = random_factor(image, call, Storage::nativeData_1555a4);
            storeFloat(image + Storage::remainingDelay,
                       mul(factor, loadFloat(image + Storage::remainingDelay)));
        }
        uint64_t angle = nativeBoundary_2aad0(call, 13, 0, 0, 0, 0);
        storeWord64(image + Storage::previousActionPosition, angle);
        return;
    }
    uint32_t state = loadWord32(image + Storage::inventoryPhase);
    if (state == 2)
        return;
    float timer = loadFloat(image + Storage::remainingDelay);
    if (timer > 0.0f) {
        timer = add(timer, loadFloat(image + Storage::nativeData_155590));
        storeFloat(image + Storage::remainingDelay, timer);
        if (timer > 0.0f)
            return;
    }
    event[0x10] = 1;
    for (;;) {
        switch (state) {
        case 0:
        case 1: {
            uint8_t *enabled =
                (uint8_t *)(uintptr_t)loadWord64(image + Storage::nativeData_155b40 + state * 8);
            if (*enabled != 0) {
                uint8_t limit = image[Storage::nativeData_155b50 + state];
                if (image[Storage::scanIndex] < limit) {
                    uint64_t target = loadWord64(image + Storage::nativeData_155b60 + state * 8);
                    do {
                        // Runtime table 0x155b60 contains 0x47870 and 0x479c0.
                        // Preserve the indirect boundary if a backing table is modified.
                        bool planned;
                        if (target == 0x47870 || target == 0x180047870ULL ||
                            target == 0x7ffbfb3f7870ULL)
                            planned =
                                planArmorUpgrade(ctx, image + Storage::inventoryPhase, image, call);
                        else if (target == 0x479c0 || target == 0x1800479c0ULL ||
                                 target == 0x7ffbfb3f79c0ULL)
                            planned = planHotbarUpgrade(ctx, image + Storage::inventoryPhase, image,
                                                        call);
                        else
                            planned = uint8_t(call(target, uintptr_t(ctx),
                                                   uintptr_t(image + Storage::inventoryPhase), 0, 0,
                                                   0)) != 0;
                        if (planned) {
                            uint64_t angle = nativeBoundary_2aad0(
                                call, image[Storage::actionSourceSlot], 0, 0, 0, 0);
                            delay(image, call, angle);
                            storeWord32(image + Storage::inventoryPhase, 3);
                            storeWord32(image + Storage::resumePhase, state);
                            image[Storage::advanceScanAfterAction] = (state != 1);
                            return;
                        }
                        image[Storage::scanIndex] = (uint8_t)(image[Storage::scanIndex] + 1);
                    } while (image[Storage::scanIndex] < limit);
                }
            }
            state++;
            advance(image, state);
            break;
        }
        case 2:
            return;
        case 3: {
            uint32_t action = loadWord32(image + Storage::pendingActionKind);
            uint8_t destination = image[Storage::actionDestination];
            uint32_t button, mode;
            switch (action) {
            case 0:
                button = 0;
                mode = 1;
                break;
            case 1:
                button = destination;
                mode = 2;
                break;
            case 2:
                button = 0;
                mode = 0;
                break;
            default:
                abort();
            }
            inventoryClick(call, loadWord64(ctx), screen, image[Storage::actionSourceSlot], button,
                           mode);
            uint8_t index = image[Storage::scanIndex];
            uint32_t bit = UINT32_C(1) << (index & 31);
            uint64_t mask = (bit & 0x80000000) ? (UINT64_C(0xffffffff00000000) | bit) : bit;
            storeWord64(image + Storage::processedSlotMask,
                        loadWord64(image + Storage::processedSlotMask) | mask);
            if (image[Storage::advanceScanAfterAction] == 1)
                image[Storage::scanIndex] = (uint8_t)(index + 1);
            if (action == 2) {
                uint64_t angle = nativeBoundary_2aad0(call, destination, 0, 0, 0, 0);
                delay(image, call, angle);
                storeWord32(image + Storage::inventoryPhase, 4);
                image[Storage::actionSourceSlot] = destination;
                return;
            }
            state = loadWord32(image + Storage::resumePhase);
            storeWord32(image + Storage::inventoryPhase, state);
            break;
        }
        case 4: {
            inventoryClick(call, loadWord64(ctx), screen, image[Storage::actionSourceSlot], 0, 0);
            float low = add(loadFloat(image + Storage::previousActionPosition),
                            loadFloat(image + Storage::nativeData_155594));
            uint32_t high = loadWord32(image + Storage::nativeData_304a0c);
            uint64_t angle = ((uint64_t)high << 32) | floatBits(low);
            delay(image, call, angle);
            storeWord32(image + Storage::inventoryPhase, 5);
            return;
        }
        case 5:
            inventoryClick(call, loadWord64(ctx), screen, 0xfffffc19, 0, 0);
            state = loadWord32(image + Storage::resumePhase);
            storeWord32(image + Storage::inventoryPhase, state);
            break;
        default:
            return;
        }
    }
}

} // namespace reconstruction::Inv_Manager
// END SOURCE modules/Inv_Manager/inv_manager.cpp

// Convenient borrowed-state interface

namespace shareable {
class InvManager {
  public:
    static constexpr const char *kName = "Inv Manager";
    static constexpr const char *kDescription = "Organises your inventory for you.";
    explicit InvManager(std::uint8_t *image) : image_(image) {}
    // Delay after open. Config key: delay_after_open.
    NumberSetting &delay_after_open() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f4e50);
    }
    // Speed. Config key: speed.
    NumberSetting &speed() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f5230);
    }
    // Smart speed. Config key: smart_speed.
    BooleanSetting &smart_speed() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f5268);
    }
    // Randomize. Config key: randomize.
    BooleanSetting &randomize() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f5210);
    }
    // Enabled. Config key: equip_armor.
    BooleanSetting &equip_armor() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4e88);
    }
    // Enabled. Config key: sort_hotbar.
    BooleanSetting &sort_hotbar() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4ea8);
    }
    // Smart fallbacks. Config key: sort_hotbar_fallback.
    BooleanSetting &sort_hotbar_fallback() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f51f0);
    }
    // Slot 1. Config key: 1.
    ChoiceSetting &setting_1() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f4fb0);
    }
    // Option labels observed in the captured metadata.
    enum class Setting1Mode : std::uint32_t {
        None = 0,
        Axe = 1,
        Blocks = 2,
        Bow = 3,
        Chest = 4,
        EnderPearl = 5,
        Fireball = 6,
        FishingRod = 7,
        FlintAndSteel = 8,
        GoldenApple = 9,
        HealingPotion = 10,
        JumpPotion = 11,
        Ladders = 12,
        LavaBucket = 13,
        Pickaxe = 14,
        Shears = 15,
        Shovel = 16,
        SnowballsEggs = 17,
        Soup = 18,
        SpeedPotion = 19,
        Stick = 20,
        StrengthPotion = 21,
        Sword = 22,
        Tnt = 23,
        WaterBucket = 24,
        Weapon = 25,
        Wool = 26
    };
    // Slot 2. Config key: 2.
    ChoiceSetting &setting_2() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f4ff0);
    }
    // Option labels observed in the captured metadata.
    enum class Setting2Mode : std::uint32_t {
        None = 0,
        Axe = 1,
        Blocks = 2,
        Bow = 3,
        Chest = 4,
        EnderPearl = 5,
        Fireball = 6,
        FishingRod = 7,
        FlintAndSteel = 8,
        GoldenApple = 9,
        HealingPotion = 10,
        JumpPotion = 11,
        Ladders = 12,
        LavaBucket = 13,
        Pickaxe = 14,
        Shears = 15,
        Shovel = 16,
        SnowballsEggs = 17,
        Soup = 18,
        SpeedPotion = 19,
        Stick = 20,
        StrengthPotion = 21,
        Sword = 22,
        Tnt = 23,
        WaterBucket = 24,
        Weapon = 25,
        Wool = 26
    };
    // Slot 3. Config key: 3.
    ChoiceSetting &setting_3() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f5030);
    }
    // Option labels observed in the captured metadata.
    enum class Setting3Mode : std::uint32_t {
        None = 0,
        Axe = 1,
        Blocks = 2,
        Bow = 3,
        Chest = 4,
        EnderPearl = 5,
        Fireball = 6,
        FishingRod = 7,
        FlintAndSteel = 8,
        GoldenApple = 9,
        HealingPotion = 10,
        JumpPotion = 11,
        Ladders = 12,
        LavaBucket = 13,
        Pickaxe = 14,
        Shears = 15,
        Shovel = 16,
        SnowballsEggs = 17,
        Soup = 18,
        SpeedPotion = 19,
        Stick = 20,
        StrengthPotion = 21,
        Sword = 22,
        Tnt = 23,
        WaterBucket = 24,
        Weapon = 25,
        Wool = 26
    };
    // Slot 4. Config key: 4.
    ChoiceSetting &setting_4() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f5070);
    }
    // Option labels observed in the captured metadata.
    enum class Setting4Mode : std::uint32_t {
        None = 0,
        Axe = 1,
        Blocks = 2,
        Bow = 3,
        Chest = 4,
        EnderPearl = 5,
        Fireball = 6,
        FishingRod = 7,
        FlintAndSteel = 8,
        GoldenApple = 9,
        HealingPotion = 10,
        JumpPotion = 11,
        Ladders = 12,
        LavaBucket = 13,
        Pickaxe = 14,
        Shears = 15,
        Shovel = 16,
        SnowballsEggs = 17,
        Soup = 18,
        SpeedPotion = 19,
        Stick = 20,
        StrengthPotion = 21,
        Sword = 22,
        Tnt = 23,
        WaterBucket = 24,
        Weapon = 25,
        Wool = 26
    };
    // Slot 5. Config key: 5.
    ChoiceSetting &setting_5() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f50b0);
    }
    // Option labels observed in the captured metadata.
    enum class Setting5Mode : std::uint32_t {
        None = 0,
        Axe = 1,
        Blocks = 2,
        Bow = 3,
        Chest = 4,
        EnderPearl = 5,
        Fireball = 6,
        FishingRod = 7,
        FlintAndSteel = 8,
        GoldenApple = 9,
        HealingPotion = 10,
        JumpPotion = 11,
        Ladders = 12,
        LavaBucket = 13,
        Pickaxe = 14,
        Shears = 15,
        Shovel = 16,
        SnowballsEggs = 17,
        Soup = 18,
        SpeedPotion = 19,
        Stick = 20,
        StrengthPotion = 21,
        Sword = 22,
        Tnt = 23,
        WaterBucket = 24,
        Weapon = 25,
        Wool = 26
    };
    // Slot 6. Config key: 6.
    ChoiceSetting &setting_6() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f50f0);
    }
    // Option labels observed in the captured metadata.
    enum class Setting6Mode : std::uint32_t {
        None = 0,
        Axe = 1,
        Blocks = 2,
        Bow = 3,
        Chest = 4,
        EnderPearl = 5,
        Fireball = 6,
        FishingRod = 7,
        FlintAndSteel = 8,
        GoldenApple = 9,
        HealingPotion = 10,
        JumpPotion = 11,
        Ladders = 12,
        LavaBucket = 13,
        Pickaxe = 14,
        Shears = 15,
        Shovel = 16,
        SnowballsEggs = 17,
        Soup = 18,
        SpeedPotion = 19,
        Stick = 20,
        StrengthPotion = 21,
        Sword = 22,
        Tnt = 23,
        WaterBucket = 24,
        Weapon = 25,
        Wool = 26
    };
    // Slot 7. Config key: 7.
    ChoiceSetting &setting_7() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f5130);
    }
    // Option labels observed in the captured metadata.
    enum class Setting7Mode : std::uint32_t {
        None = 0,
        Axe = 1,
        Blocks = 2,
        Bow = 3,
        Chest = 4,
        EnderPearl = 5,
        Fireball = 6,
        FishingRod = 7,
        FlintAndSteel = 8,
        GoldenApple = 9,
        HealingPotion = 10,
        JumpPotion = 11,
        Ladders = 12,
        LavaBucket = 13,
        Pickaxe = 14,
        Shears = 15,
        Shovel = 16,
        SnowballsEggs = 17,
        Soup = 18,
        SpeedPotion = 19,
        Stick = 20,
        StrengthPotion = 21,
        Sword = 22,
        Tnt = 23,
        WaterBucket = 24,
        Weapon = 25,
        Wool = 26
    };
    // Slot 8. Config key: 8.
    ChoiceSetting &setting_8() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f5170);
    }
    // Option labels observed in the captured metadata.
    enum class Setting8Mode : std::uint32_t {
        None = 0,
        Axe = 1,
        Blocks = 2,
        Bow = 3,
        Chest = 4,
        EnderPearl = 5,
        Fireball = 6,
        FishingRod = 7,
        FlintAndSteel = 8,
        GoldenApple = 9,
        HealingPotion = 10,
        JumpPotion = 11,
        Ladders = 12,
        LavaBucket = 13,
        Pickaxe = 14,
        Shears = 15,
        Shovel = 16,
        SnowballsEggs = 17,
        Soup = 18,
        SpeedPotion = 19,
        Stick = 20,
        StrengthPotion = 21,
        Sword = 22,
        Tnt = 23,
        WaterBucket = 24,
        Weapon = 25,
        Wool = 26
    };
    // Slot 9. Config key: 9.
    ChoiceSetting &setting_9() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f51b0);
    }
    // Option labels observed in the captured metadata.
    enum class Setting9Mode : std::uint32_t {
        None = 0,
        Axe = 1,
        Blocks = 2,
        Bow = 3,
        Chest = 4,
        EnderPearl = 5,
        Fireball = 6,
        FishingRod = 7,
        FlintAndSteel = 8,
        GoldenApple = 9,
        HealingPotion = 10,
        JumpPotion = 11,
        Ladders = 12,
        LavaBucket = 13,
        Pickaxe = 14,
        Shears = 15,
        Shovel = 16,
        SnowballsEggs = 17,
        Soup = 18,
        SpeedPotion = 19,
        Stick = 20,
        StrengthPotion = 21,
        Sword = 22,
        Tnt = 23,
        WaterBucket = 24,
        Weapon = 25,
        Wool = 26
    };
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_inv_manager_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_inv_manager_settings(&context, image_, &dependencies);
    }
    void advanceInventoryActions(uint8_t *event, ::reconstruction::Inv_Manager::dependency call) {
        ::reconstruction::Inv_Manager::advanceInventoryActions(event, image_, call);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
