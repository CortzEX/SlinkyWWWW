#ifndef SLINKY_SHARE_12CB6F2AB19DAA190A04
#define SLINKY_SHARE_12CB6F2AB19DAA190A04
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
namespace reconstruction::Auto_Clicker {
namespace Storage {
inline constexpr std::uint32_t nativeData_150328 = 0x150328;
inline constexpr std::uint32_t nativeData_150330 = 0x150330;
inline constexpr std::uint32_t nativeData_150338 = 0x150338;
inline constexpr std::uint32_t nativeData_15033c = 0x15033c;
inline constexpr std::uint32_t nativeData_150340 = 0x150340;
inline constexpr std::uint32_t nativeData_150348 = 0x150348;
inline constexpr std::uint32_t nativeData_150350 = 0x150350;
inline constexpr std::uint32_t nativeData_150354 = 0x150354;
inline constexpr std::uint32_t nativeData_150358 = 0x150358;
inline constexpr std::uint32_t nativeData_150360 = 0x150360;
inline constexpr std::uint32_t nativeData_150368 = 0x150368;
inline constexpr std::uint32_t nativeData_150370 = 0x150370;
inline constexpr std::uint32_t nativeData_150374 = 0x150374;
inline constexpr std::uint32_t nativeData_150378 = 0x150378;
inline constexpr std::uint32_t nativeData_150380 = 0x150380;
inline constexpr std::uint32_t nativeData_150384 = 0x150384;
inline constexpr std::uint32_t nativeData_150388 = 0x150388;
inline constexpr std::uint32_t nativeData_150390 = 0x150390;
inline constexpr std::uint32_t nativeData_150394 = 0x150394;
inline constexpr std::uint32_t nativeData_150398 = 0x150398;
inline constexpr std::uint32_t nativeData_1503a0 = 0x1503a0;
inline constexpr std::uint32_t nativeData_1503a4 = 0x1503a4;
inline constexpr std::uint32_t nativeData_1503a8 = 0x1503a8;
inline constexpr std::uint32_t nativeData_1503b0 = 0x1503b0;
inline constexpr std::uint32_t nativeData_1503b8 = 0x1503b8;
inline constexpr std::uint32_t nativeData_1503c0 = 0x1503c0;
inline constexpr std::uint32_t nativeData_1503c8 = 0x1503c8;
inline constexpr std::uint32_t nativeData_1503d0 = 0x1503d0;
inline constexpr std::uint32_t nativeData_1503d4 = 0x1503d4;
inline constexpr std::uint32_t nativeData_1505a0 = 0x1505a0;
inline constexpr std::uint32_t moduleDescriptor = 0x2e9330;
inline constexpr std::uint32_t nativeData_2e9540 = 0x2e9540;
inline constexpr std::uint32_t allow_inventoryRecord = 0x2e9548;
inline constexpr std::uint32_t allow_inventoryCurrent = 0x2e9560;
inline constexpr std::uint32_t inventory_randomizeRecord = 0x2e9568;
inline constexpr std::uint32_t inventory_randomizeCurrent = 0x2e9580;
inline constexpr std::uint32_t allow_block_breakRecord = 0x2e9588;
inline constexpr std::uint32_t allow_block_breakCurrent = 0x2e95a0;
inline constexpr std::uint32_t require_weaponRecord = 0x2e95a8;
inline constexpr std::uint32_t require_weaponCurrent = 0x2e95c0;
inline constexpr std::uint32_t require_not_using_itemRecord = 0x2e95c8;
inline constexpr std::uint32_t require_not_using_itemCurrent = 0x2e95e0;
inline constexpr std::uint32_t target_cpsRecord = 0x2e95e8;
inline constexpr std::uint32_t target_cpsCurrent = 0x2e9618;
inline constexpr std::uint32_t randomize_cpsRecord = 0x2e9620;
inline constexpr std::uint32_t randomize_cpsCurrent = 0x2e9638;
inline constexpr std::uint32_t patternRecord = 0x2e9650;
inline constexpr std::uint32_t patternCurrent = 0x2e9680;
inline constexpr std::uint32_t exhaustRecord = 0x2e9690;
inline constexpr std::uint32_t exhaustCurrent = 0x2e96a8;
inline constexpr std::uint32_t previousRotation = 0x2f7c88;
inline constexpr std::uint32_t primaryButtonSelector = 0x2f7c90;
inline constexpr std::uint32_t remainingClickTime = 0x2f7c98;
inline constexpr std::uint32_t previousClickInterval = 0x2f7ca0;
inline constexpr std::uint32_t nativeData_2f7ca8 = 0x2f7ca8;
inline constexpr std::uint32_t inventoryPrimaryWasPressed = 0x2f7cb8;
inline constexpr std::uint32_t nativeData_2f7cc0 = 0x2f7cc0;
inline constexpr std::uint32_t currentHitKind = 0x2f7cd0;
inline constexpr std::uint32_t nativeData_2f7cd8 = 0x2f7cd8;
inline constexpr std::uint32_t nativeData_2f7ce8 = 0x2f7ce8;
inline constexpr std::uint32_t nativeData_2f7cf8 = 0x2f7cf8;
inline constexpr std::uint32_t quickClickPending = 0x2f7d00;
inline constexpr std::uint32_t nativeData_2f7d08 = 0x2f7d08;
inline constexpr std::uint32_t nativeData_2f7d18 = 0x2f7d18;
inline constexpr std::uint32_t nativeData_2f7d28 = 0x2f7d28;
inline constexpr std::uint32_t intervalAdjustmentCountdown = 0x2f7d60;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    ChoiceSetting &pattern() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::patternRecord);
    }
    NumberSetting &target_cps() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::target_cpsRecord);
    }
    BooleanSetting &randomize_cps() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::randomize_cpsRecord);
    }
    BooleanSetting &exhaust() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::exhaustRecord);
    }
    BooleanSetting &allow_block_break() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::allow_block_breakRecord);
    }
    BooleanSetting &allow_inventory() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::allow_inventoryRecord);
    }
    BooleanSetting &inventory_randomize() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::inventory_randomizeRecord);
    }
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_weaponRecord);
    }
    BooleanSetting &require_not_using_item() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_not_using_itemRecord);
    }
};
// Runtime-observed native labels for config key "pattern". Numeric values preserved.
enum class PatternMode : std::uint32_t {
    Jitter = 0,
    Butterfly = 1,
};
} // namespace reconstruction::Auto_Clicker
#endif // SLINKY_SHARE_12CB6F2AB19DAA190A04
