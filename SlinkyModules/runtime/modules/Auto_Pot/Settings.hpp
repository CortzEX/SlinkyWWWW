#ifndef SLINKY_SHARE_F1C492C66827E0B71BB1
#define SLINKY_SHARE_F1C492C66827E0B71BB1
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
namespace reconstruction::Auto_Pot {
namespace Storage {
inline constexpr std::uint32_t nativeData_152c38 = 0x152c38;
inline constexpr std::uint32_t nativeData_152c3c = 0x152c3c;
inline constexpr std::uint32_t nativeData_152c58 = 0x152c58;
inline constexpr std::uint32_t nativeData_152c60 = 0x152c60;
inline constexpr std::uint32_t nativeData_152c68 = 0x152c68;
inline constexpr std::uint32_t nativeData_152c70 = 0x152c70;
inline constexpr std::uint32_t nativeData_152c78 = 0x152c78;
inline constexpr std::uint32_t nativeData_152c7c = 0x152c7c;
inline constexpr std::uint32_t nativeData_152c80 = 0x152c80;
inline constexpr std::uint32_t nativeData_152c88 = 0x152c88;
inline constexpr std::uint32_t moduleDescriptor = 0x2ef128;
inline constexpr std::uint32_t use_non_healthRecord = 0x2ef338;
inline constexpr std::uint32_t use_non_healthCurrent = 0x2ef350;
inline constexpr std::uint32_t delayRecord = 0x2ef358;
inline constexpr std::uint32_t delayCurrent = 0x2ef388;
inline constexpr std::uint32_t prevent_wasteRecord = 0x2ef390;
inline constexpr std::uint32_t prevent_wasteCurrent = 0x2ef3a8;
inline constexpr std::uint32_t double_splashRecord = 0x2ef3b0;
inline constexpr std::uint32_t double_splashCurrent = 0x2ef3c8;
inline constexpr std::uint32_t potionPhase = 0x2fc640;
inline constexpr std::uint32_t potionSlot = 0x2fc644;
inline constexpr std::uint32_t previousSlot = 0x2fc648;
inline constexpr std::uint32_t continueSelection = 0x2fc64c;
inline constexpr std::uint32_t remainingDelay = 0x2fc650;
inline constexpr std::uint32_t remainingUses = 0x2fc654;
inline constexpr std::uint32_t nativeData_2fc658 = 0x2fc658;
inline constexpr std::uint32_t nativeData_2fc668 = 0x2fc668;
inline constexpr std::uint32_t pendingActionRequests = 0x2fc678;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &delay() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::delayRecord);
    }
    BooleanSetting &prevent_waste() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::prevent_wasteRecord);
    }
    BooleanSetting &double_splash() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::double_splashRecord);
    }
    BooleanSetting &use_non_health() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::use_non_healthRecord);
    }
};
} // namespace reconstruction::Auto_Pot
#endif // SLINKY_SHARE_F1C492C66827E0B71BB1
