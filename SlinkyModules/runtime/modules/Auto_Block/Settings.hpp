#ifndef SLINKY_SHARE_8A56E7354D15C4624391
#define SLINKY_SHARE_8A56E7354D15C4624391
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
namespace reconstruction::Auto_Block {
namespace Storage {
inline constexpr std::uint32_t moduleDescriptor = 0x2eaff8;
inline constexpr std::uint32_t max_hold_timeRecord = 0x2eb208;
inline constexpr std::uint32_t max_hold_timeCurrent = 0x2eb238;
inline constexpr std::uint32_t lag_chanceRecord = 0x2eb240;
inline constexpr std::uint32_t lag_chanceCurrent = 0x2eb270;
inline constexpr std::uint32_t lag_durationRecord = 0x2eb278;
inline constexpr std::uint32_t lag_durationCurrent = 0x2eb2a8;
inline constexpr std::uint32_t max_hurt_timeRecord = 0x2eb2b0;
inline constexpr std::uint32_t max_hurt_timeCurrent = 0x2eb2e0;
inline constexpr std::uint32_t require_left_mouse_pressedRecord = 0x2eb2e8;
inline constexpr std::uint32_t require_left_mouse_pressedCurrent = 0x2eb300;
inline constexpr std::uint32_t require_right_mouse_pressedRecord = 0x2eb308;
inline constexpr std::uint32_t require_right_mouse_pressedCurrent = 0x2eb320;
inline constexpr std::uint32_t require_damageRecord = 0x2eb328;
inline constexpr std::uint32_t require_damageCurrent = 0x2eb340;
inline constexpr std::uint32_t fake_block_animationRecord = 0x2eb348;
inline constexpr std::uint32_t fake_block_animationCurrent = 0x2eb360;
inline constexpr std::uint32_t fake_block_animation_require_targetRecord = 0x2eb368;
inline constexpr std::uint32_t fake_block_animation_require_targetCurrent = 0x2eb380;
inline constexpr std::uint32_t rangeRecord = 0x2eb388;
inline constexpr std::uint32_t rangeCurrent = 0x2eb3b8;
inline constexpr std::uint32_t lag_flush_attackRecord = 0x2eb3c0;
inline constexpr std::uint32_t lag_flush_attackCurrent = 0x2eb3d8;
inline constexpr std::uint32_t lag_reblockRecord = 0x2eb3e0;
inline constexpr std::uint32_t lag_reblockCurrent = 0x2eb3f8;
inline constexpr std::uint32_t nativeData_2f9e00 = 0x2f9e00;
inline constexpr std::uint32_t nativeData_2f9e04 = 0x2f9e04;
inline constexpr std::uint32_t nativeData_2f9e08 = 0x2f9e08;
inline constexpr std::uint32_t nativeData_2f9e0c = 0x2f9e0c;
inline constexpr std::uint32_t nativeData_2f9e10 = 0x2f9e10;
inline constexpr std::uint32_t nativeData_2f9e11 = 0x2f9e11;
inline constexpr std::uint32_t nativeData_2f9e12 = 0x2f9e12;
inline constexpr std::uint32_t nativeData_2f9e14 = 0x2f9e14;
inline constexpr std::uint32_t nativeData_2f9e18 = 0x2f9e18;
inline constexpr std::uint32_t nativeData_2f9e19 = 0x2f9e19;
inline constexpr std::uint32_t nativeData_2f9e1c = 0x2f9e1c;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &range() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::rangeRecord);
    }
    NumberSetting &max_hurt_time() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::max_hurt_timeRecord);
    }
    NumberSetting &max_hold_time() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::max_hold_timeRecord);
    }
    BooleanSetting &fake_block_animation() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::fake_block_animationRecord);
    }
    BooleanSetting &fake_block_animation_require_target() const {
        return *reinterpret_cast<BooleanSetting *>(
            image + Storage::fake_block_animation_require_targetRecord);
    }
    NumberSetting &lag_chance() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::lag_chanceRecord);
    }
    NumberSetting &lag_duration() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::lag_durationRecord);
    }
    BooleanSetting &lag_flush_attack() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::lag_flush_attackRecord);
    }
    BooleanSetting &lag_reblock() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::lag_reblockRecord);
    }
    BooleanSetting &require_left_mouse_pressed() const {
        return *reinterpret_cast<BooleanSetting *>(image +
                                                   Storage::require_left_mouse_pressedRecord);
    }
    BooleanSetting &require_right_mouse_pressed() const {
        return *reinterpret_cast<BooleanSetting *>(image +
                                                   Storage::require_right_mouse_pressedRecord);
    }
    BooleanSetting &require_damage() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_damageRecord);
    }
};
} // namespace reconstruction::Auto_Block
#endif // SLINKY_SHARE_8A56E7354D15C4624391
