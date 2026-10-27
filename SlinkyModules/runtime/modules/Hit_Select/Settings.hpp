#ifndef SLINKY_SHARE_50C5F13F6BA9E103F21D
#define SLINKY_SHARE_50C5F13F6BA9E103F21D
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
namespace reconstruction::Hit_Select {
namespace Storage {
inline constexpr std::uint32_t moduleDescriptor = 0x2ee4f0;
inline constexpr std::uint32_t cancel_rate_airRecord = 0x2ee700;
inline constexpr std::uint32_t cancel_rate_airCurrent = 0x2ee730;
inline constexpr std::uint32_t pause_durRecord = 0x2ee738;
inline constexpr std::uint32_t pause_durCurrent = 0x2ee768;
inline constexpr std::uint32_t wait_for_damage_durRecord = 0x2ee770;
inline constexpr std::uint32_t wait_for_damage_durCurrent = 0x2ee7a0;
inline constexpr std::uint32_t trades_delayRecord = 0x2ee7a8;
inline constexpr std::uint32_t trades_delayCurrent = 0x2ee7d8;
inline constexpr std::uint32_t cancel_rateRecord = 0x2ee7e0;
inline constexpr std::uint32_t cancel_rateCurrent = 0x2ee810;
inline constexpr std::uint32_t require_sprintRecord = 0x2ee818;
inline constexpr std::uint32_t require_sprintCurrent = 0x2ee830;
inline constexpr std::uint32_t require_weaponRecord = 0x2ee838;
inline constexpr std::uint32_t require_weaponCurrent = 0x2ee850;
inline constexpr std::uint32_t modeRecord = 0x2ee870;
inline constexpr std::uint32_t modeCurrent = 0x2ee8a0;
inline constexpr std::uint32_t use_server_timeRecord = 0x2ee8b0;
inline constexpr std::uint32_t use_server_timeCurrent = 0x2ee8c8;
inline constexpr std::uint32_t crits_allow_reduceRecord = 0x2ee8d0;
inline constexpr std::uint32_t crits_allow_reduceCurrent = 0x2ee8e8;
inline constexpr std::uint32_t require_damageRecord = 0x2ee8f0;
inline constexpr std::uint32_t require_damageCurrent = 0x2ee908;
inline constexpr std::uint32_t fake_swingRecord = 0x2ee910;
inline constexpr std::uint32_t fake_swingCurrent = 0x2ee928;
inline constexpr std::uint32_t attackDecisionReady = 0x2fc538;
inline constexpr std::uint32_t unhurtTicks = 0x2fc53c;
inline constexpr std::uint32_t cancelAttackDecision = 0x2fc540;
inline constexpr std::uint32_t targetHistoryTicks = 0x2fc544;
inline constexpr std::uint32_t consecutiveTargetChecks = 0x2fc548;
inline constexpr std::uint32_t newHurtWindow = 0x2fc54c;
inline constexpr std::uint32_t previousTargetIdentifier = 0x2fc550;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    ChoiceSetting &mode() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::modeRecord);
    }
    NumberSetting &cancel_rate() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::cancel_rateRecord);
    }
    NumberSetting &cancel_rate_air() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::cancel_rate_airRecord);
    }
    NumberSetting &pause_dur() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::pause_durRecord);
    }
    NumberSetting &wait_for_damage_dur() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::wait_for_damage_durRecord);
    }
    NumberSetting &trades_delay() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::trades_delayRecord);
    }
    BooleanSetting &use_server_time() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::use_server_timeRecord);
    }
    BooleanSetting &fake_swing() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::fake_swingRecord);
    }
    BooleanSetting &crits_allow_reduce() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::crits_allow_reduceRecord);
    }
    BooleanSetting &require_damage() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_damageRecord);
    }
    BooleanSetting &require_sprint() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_sprintRecord);
    }
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_weaponRecord);
    }
};
// Runtime-observed native labels for config key "mode". Numeric values preserved.
enum class ModeMode : std::uint32_t {
    Burst = 0,
    Criticals = 1,
};
} // namespace reconstruction::Hit_Select
#endif // SLINKY_SHARE_50C5F13F6BA9E103F21D
