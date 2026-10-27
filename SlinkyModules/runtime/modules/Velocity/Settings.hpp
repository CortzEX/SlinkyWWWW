#ifndef SLINKY_SHARE_A5EC6F1D4D6341E6AA53
#define SLINKY_SHARE_A5EC6F1D4D6341E6AA53
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
namespace reconstruction::Velocity {
namespace Storage {
inline constexpr std::uint32_t nativeData_13cfa0 = 0x13cfa0;
inline constexpr std::uint32_t nativeData_13cfd0 = 0x13cfd0;
inline constexpr std::uint32_t nativeData_150e20 = 0x150e20;
inline constexpr std::uint32_t nativeData_150e48 = 0x150e48;
inline constexpr std::uint32_t nativeData_150e50 = 0x150e50;
inline constexpr std::uint32_t nativeData_150e58 = 0x150e58;
inline constexpr std::uint32_t nativeData_150e80 = 0x150e80;
inline constexpr std::uint32_t nativeData_150e88 = 0x150e88;
inline constexpr std::uint32_t moduleDescriptor = 0x2ea7f0;
inline constexpr std::uint32_t modeRecord = 0x2eaa20;
inline constexpr std::uint32_t modeCurrent = 0x2eaa50;
inline constexpr std::uint32_t ignore_chanceRecord = 0x2eaa60;
inline constexpr std::uint32_t ignore_chanceCurrent = 0x2eaa90;
inline constexpr std::uint32_t require_forwardRecord = 0x2eaa98;
inline constexpr std::uint32_t require_forwardCurrent = 0x2eaab0;
inline constexpr std::uint32_t require_mouseRecord = 0x2eaab8;
inline constexpr std::uint32_t require_mouseCurrent = 0x2eaad0;
inline constexpr std::uint32_t require_weaponRecord = 0x2eaad8;
inline constexpr std::uint32_t require_weaponCurrent = 0x2eaaf0;
inline constexpr std::uint32_t require_targetRecord = 0x2eaaf8;
inline constexpr std::uint32_t require_targetCurrent = 0x2eab10;
inline constexpr std::uint32_t ignore_verticalRecord = 0x2eab38;
inline constexpr std::uint32_t ignore_verticalCurrent = 0x2eab68;
inline constexpr std::uint32_t reduce_multiple_per_tickRecord = 0x2eab78;
inline constexpr std::uint32_t reduce_multiple_per_tickCurrent = 0x2eab90;
inline constexpr std::uint32_t reduce_chanceRecord = 0x2eab98;
inline constexpr std::uint32_t reduce_chanceCurrent = 0x2eabc8;
inline constexpr std::uint32_t reduce_delayRecord = 0x2eabd0;
inline constexpr std::uint32_t reduce_delayCurrent = 0x2eac00;
inline constexpr std::uint32_t reduce_amountRecord = 0x2eac08;
inline constexpr std::uint32_t reduce_amountCurrent = 0x2eac38;
inline constexpr std::uint32_t fovRecord = 0x2eac40;
inline constexpr std::uint32_t fovCurrent = 0x2eac70;
inline constexpr std::uint32_t jump_chanceRecord = 0x2eac78;
inline constexpr std::uint32_t jump_chanceCurrent = 0x2eaca8;
inline constexpr std::uint32_t require_sprinting_jumpRecord = 0x2eacb0;
inline constexpr std::uint32_t require_sprinting_jumpCurrent = 0x2eacc8;
inline constexpr std::uint32_t packetResetPending = 0x2f9d88;
inline constexpr std::uint32_t storedVelocityPending = 0x2f9d89;
inline constexpr std::uint32_t storedVelocityX = 0x2f9d90;
inline constexpr std::uint32_t storedVelocityY = 0x2f9d98;
inline constexpr std::uint32_t storedVelocityZ = 0x2f9da0;
inline constexpr std::uint32_t nativeData_2f9da8 = 0x2f9da8;
inline constexpr std::uint32_t localEntityIdentifier = 0x2f9db8;
inline constexpr std::uint32_t knockbackPacketPending = 0x2f9dbc;
inline constexpr std::uint32_t inputVelocityX = 0x2f9dc0;
inline constexpr std::uint32_t inputVelocityZ = 0x2f9dd0;
inline constexpr std::uint32_t attackVelocityApplied = 0x2f9dd8;
inline constexpr std::uint32_t horizontalDelayTicks = 0x2f9ddc;
inline constexpr std::uint32_t jumpKeyOwned = 0x2f9de0;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    ChoiceSetting &mode() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::modeRecord);
    }
    NumberSetting &reduce_chance() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::reduce_chanceRecord);
    }
    NumberSetting &fov() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::fovRecord);
    }
    NumberSetting &reduce_amount() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::reduce_amountRecord);
    }
    NumberSetting &reduce_delay() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::reduce_delayRecord);
    }
    NumberSetting &jump_chance() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::jump_chanceRecord);
    }
    BooleanSetting &reduce_multiple_per_tick() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::reduce_multiple_per_tickRecord);
    }
    ChoiceSetting &ignore_vertical() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::ignore_verticalRecord);
    }
    NumberSetting &ignore_chance() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::ignore_chanceRecord);
    }
    BooleanSetting &require_target() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_targetRecord);
    }
    BooleanSetting &require_mouse() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_mouseRecord);
    }
    BooleanSetting &require_forward() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_forwardRecord);
    }
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_weaponRecord);
    }
    BooleanSetting &require_sprinting_jump() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_sprinting_jumpRecord);
    }
};
// Runtime-observed native labels for config key "mode". Numeric values preserved.
enum class ModeMode : std::uint32_t {
    Regular = 0,
    Jump = 1,
    Reduce = 2,
    Ignore = 3,
};
// Runtime-observed native labels for config key "ignore_vertical". Numeric values preserved.
enum class Ignore_verticalMode : std::uint32_t {
    Never = 0,
    Only_in_air = 1,
    Always = 2,
};
} // namespace reconstruction::Velocity
#endif // SLINKY_SHARE_A5EC6F1D4D6341E6AA53
