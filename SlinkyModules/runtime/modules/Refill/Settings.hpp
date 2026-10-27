#ifndef SLINKY_SHARE_40316CCE03B36E53764C
#define SLINKY_SHARE_40316CCE03B36E53764C
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
namespace reconstruction::Refill {
namespace Storage {
inline constexpr std::uint32_t nativeData_152a30 = 0x152a30;
inline constexpr std::uint32_t nativeData_152a34 = 0x152a34;
inline constexpr std::uint32_t nativeData_152a38 = 0x152a38;
inline constexpr std::uint32_t nativeData_152a40 = 0x152a40;
inline constexpr std::uint32_t nativeData_152a44 = 0x152a44;
inline constexpr std::uint32_t nativeData_152a48 = 0x152a48;
inline constexpr std::uint32_t nativeData_152a50 = 0x152a50;
inline constexpr std::uint32_t nativeData_152a58 = 0x152a58;
inline constexpr std::uint32_t nativeData_152a60 = 0x152a60;
inline constexpr std::uint32_t nativeData_152a64 = 0x152a64;
inline constexpr std::uint32_t nativeData_152a68 = 0x152a68;
inline constexpr std::uint32_t nativeData_152a6c = 0x152a6c;
inline constexpr std::uint32_t nativeData_152a70 = 0x152a70;
inline constexpr std::uint32_t nativeData_152a74 = 0x152a74;
inline constexpr std::uint32_t nativeData_152a78 = 0x152a78;
inline constexpr std::uint32_t nativeData_152a7c = 0x152a7c;
inline constexpr std::uint32_t moduleDescriptor = 0x2eed90;
inline constexpr std::uint32_t delay_before_closeRecord = 0x2eefa0;
inline constexpr std::uint32_t delay_before_closeCurrent = 0x2eefd0;
inline constexpr std::uint32_t delay_after_openRecord = 0x2eefd8;
inline constexpr std::uint32_t delay_after_openCurrent = 0x2ef008;
inline constexpr std::uint32_t speedRecord = 0x2ef010;
inline constexpr std::uint32_t speedCurrent = 0x2ef040;
inline constexpr std::uint32_t refill_soupRecord = 0x2ef048;
inline constexpr std::uint32_t refill_soupCurrent = 0x2ef060;
inline constexpr std::uint32_t refill_potionRecord = 0x2ef068;
inline constexpr std::uint32_t refill_potionCurrent = 0x2ef080;
inline constexpr std::uint32_t refill_potion_non_healthRecord = 0x2ef088;
inline constexpr std::uint32_t refill_potion_non_healthCurrent = 0x2ef0a0;
inline constexpr std::uint32_t smart_speedRecord = 0x2ef0a8;
inline constexpr std::uint32_t smart_speedCurrent = 0x2ef0c0;
inline constexpr std::uint32_t simulate_buttonRecord = 0x2ef0e8;
inline constexpr std::uint32_t simulate_buttonCurrent = 0x2ef118;
inline constexpr std::uint32_t refillPhase = 0x2fc580;
inline constexpr std::uint32_t nativeData_2fc588 = 0x2fc588;
inline constexpr std::uint32_t nativeData_2fc598 = 0x2fc598;
inline constexpr std::uint32_t nativeData_2fc5a8 = 0x2fc5a8;
inline constexpr std::uint32_t nativeData_2fc5b8 = 0x2fc5b8;
inline constexpr std::uint32_t nativeData_2fc5c8 = 0x2fc5c8;
inline constexpr std::uint32_t remainingDelay = 0x2fc5d0;
inline constexpr std::uint32_t candidateSlotMask = 0x2fc5e0;
inline constexpr std::uint32_t previousSelection = 0x2fc5fc;
inline constexpr std::uint32_t selectionAngle = 0x2fc600;
inline constexpr std::uint32_t selectedSlot = 0x2fc604;
inline constexpr std::uint32_t alternateAction = 0x2fc608;
inline constexpr std::uint32_t nativeData_2fc610 = 0x2fc610;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    BooleanSetting &refill_potion() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::refill_potionRecord);
    }
    BooleanSetting &refill_potion_non_health() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::refill_potion_non_healthRecord);
    }
    BooleanSetting &refill_soup() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::refill_soupRecord);
    }
    ChoiceSetting &simulate_button() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::simulate_buttonRecord);
    }
    NumberSetting &delay_after_open() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::delay_after_openRecord);
    }
    NumberSetting &delay_before_close() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::delay_before_closeRecord);
    }
    NumberSetting &speed() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::speedRecord);
    }
    BooleanSetting &smart_speed() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::smart_speedRecord);
    }
};
// Runtime-observed native labels for config key "simulate_button". Numeric values preserved.
enum class Simulate_buttonMode : std::uint32_t {
    Left = 0,
    Right = 1,
    Left___right = 2,
};
} // namespace reconstruction::Refill
#endif // SLINKY_SHARE_40316CCE03B36E53764C
