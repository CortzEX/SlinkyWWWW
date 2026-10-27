#ifndef SLINKY_SHARE_E72D32150455274ADF81
#define SLINKY_SHARE_E72D32150455274ADF81
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
namespace reconstruction::Auto_Rod {
namespace Storage {
inline constexpr std::uint32_t moduleDescriptor = 0x2f3520;
inline constexpr std::uint32_t nativeData_2f3540 = 0x2f3540;
inline constexpr std::uint32_t nativeData_2f3730 = 0x2f3730;
inline constexpr std::uint32_t require_not_mouse_overRecord = 0x2f3738;
inline constexpr std::uint32_t require_not_mouse_overCurrent = 0x2f3750;
inline constexpr std::uint32_t allow_throwablesRecord = 0x2f3758;
inline constexpr std::uint32_t allow_throwablesCurrent = 0x2f3770;
inline constexpr std::uint32_t always_switch_to_weaponRecord = 0x2f3778;
inline constexpr std::uint32_t always_switch_to_weaponCurrent = 0x2f3790;
inline constexpr std::uint32_t delayRecord = 0x2f3798;
inline constexpr std::uint32_t delayCurrent = 0x2f37c8;
inline constexpr std::uint32_t randomize_delaysRecord = 0x2f37d0;
inline constexpr std::uint32_t randomize_delaysCurrent = 0x2f37e8;
inline constexpr std::uint32_t retract_speedRecord = 0x2f37f0;
inline constexpr std::uint32_t retract_speedCurrent = 0x2f3820;
inline constexpr std::uint32_t throw_speedRecord = 0x2f3828;
inline constexpr std::uint32_t throw_speedCurrent = 0x2f3858;
inline constexpr std::uint32_t nativeData_304400 = 0x304400;
inline constexpr std::uint32_t nativeData_304404 = 0x304404;
inline constexpr std::uint32_t nativeData_304408 = 0x304408;
inline constexpr std::uint32_t nativeData_30440c = 0x30440c;
inline constexpr std::uint32_t nativeData_304410 = 0x304410;
inline constexpr std::uint32_t nativeData_304414 = 0x304414;
inline constexpr std::uint32_t nativeData_304415 = 0x304415;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &retract_speed() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::retract_speedRecord);
    }
    NumberSetting &delay() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::delayRecord);
    }
    BooleanSetting &randomize_delays() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::randomize_delaysRecord);
    }
    BooleanSetting &always_switch_to_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::always_switch_to_weaponRecord);
    }
    BooleanSetting &allow_throwables() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::allow_throwablesRecord);
    }
    NumberSetting &throw_speed() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::throw_speedRecord);
    }
    BooleanSetting &require_not_mouse_over() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_not_mouse_overRecord);
    }
};
} // namespace reconstruction::Auto_Rod
#endif // SLINKY_SHARE_E72D32150455274ADF81
