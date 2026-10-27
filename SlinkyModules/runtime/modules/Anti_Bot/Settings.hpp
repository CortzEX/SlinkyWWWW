#ifndef SLINKY_SHARE_914EE2AD87EA5C9E3E50
#define SLINKY_SHARE_914EE2AD87EA5C9E3E50
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
namespace reconstruction::Anti_Bot {
namespace Storage {
inline constexpr std::uint32_t nativeData_13cf70 = 0x13cf70;
inline constexpr std::uint32_t nativeData_1510c8 = 0x1510c8;
inline constexpr std::uint32_t moduleDescriptor = 0x2eacd0;
inline constexpr std::uint32_t min_ageRecord = 0x2eaee0;
inline constexpr std::uint32_t min_ageCurrent = 0x2eaf10;
inline constexpr std::uint32_t always_stationaryRecord = 0x2eaf18;
inline constexpr std::uint32_t always_stationaryCurrent = 0x2eaf30;
inline constexpr std::uint32_t invalid_uuidRecord = 0x2eaf58;
inline constexpr std::uint32_t invalid_uuidCurrent = 0x2eaf88;
inline constexpr std::uint32_t sleepingRecord = 0x2eaf98;
inline constexpr std::uint32_t sleepingCurrent = 0x2eafb0;
inline constexpr std::uint32_t always_invisRecord = 0x2eafb8;
inline constexpr std::uint32_t always_invisCurrent = 0x2eafd0;
inline constexpr std::uint32_t invalid_usernameRecord = 0x2eafd8;
inline constexpr std::uint32_t invalid_usernameCurrent = 0x2eaff0;
inline constexpr std::uint32_t cachedWorldIdentifier = 0x2f9de8;
inline constexpr std::uint32_t playerHistoryTable = 0x2f9df0;
inline constexpr std::uint32_t playerHistoryCount = 0x2f9df8;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    ChoiceSetting &invalid_uuid() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::invalid_uuidRecord);
    }
    BooleanSetting &invalid_username() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::invalid_usernameRecord);
    }
    BooleanSetting &always_invis() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::always_invisRecord);
    }
    BooleanSetting &always_stationary() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::always_stationaryRecord);
    }
    BooleanSetting &sleeping() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::sleepingRecord);
    }
    NumberSetting &min_age() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::min_ageRecord);
    }
};
// Runtime-observed native labels for config key "invalid_uuid". Numeric values preserved.
enum class Invalid_uuidMode : std::uint32_t {
    Off = 0,
    Stationary_only = 1,
    Always = 2,
};
} // namespace reconstruction::Anti_Bot
#endif // SLINKY_SHARE_914EE2AD87EA5C9E3E50
