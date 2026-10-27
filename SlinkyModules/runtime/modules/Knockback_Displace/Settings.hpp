#ifndef SLINKY_SHARE_F4A5AF7A30361D5F575B
#define SLINKY_SHARE_F4A5AF7A30361D5F575B
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
namespace reconstruction::Knockback_Displace {
namespace Storage {
inline constexpr std::uint32_t nativeData_156680 = 0x156680;
inline constexpr std::uint32_t nativeData_156684 = 0x156684;
inline constexpr std::uint32_t nativeData_156688 = 0x156688;
inline constexpr std::uint32_t nativeData_156690 = 0x156690;
inline constexpr std::uint32_t nativeData_1566a0 = 0x1566a0;
inline constexpr std::uint32_t nativeData_1566b0 = 0x1566b0;
inline constexpr std::uint32_t nativeData_1566b4 = 0x1566b4;
inline constexpr std::uint32_t nativeData_2f3174 = 0x2f3174;
inline constexpr std::uint32_t moduleDescriptor = 0x2f5d60;
inline constexpr std::uint32_t cooldownRecord = 0x2f5f70;
inline constexpr std::uint32_t cooldownCurrent = 0x2f5fa0;
inline constexpr std::uint32_t angleRecord = 0x2f5fa8;
inline constexpr std::uint32_t angleCurrent = 0x2f5fd8;
inline constexpr std::uint32_t require_no_kbRecord = 0x2f5fe0;
inline constexpr std::uint32_t require_no_kbCurrent = 0x2f5ff8;
inline constexpr std::uint32_t require_weaponRecord = 0x2f6000;
inline constexpr std::uint32_t require_weaponCurrent = 0x2f6018;
inline constexpr std::uint32_t require_kb_enchantRecord = 0x2f6020;
inline constexpr std::uint32_t require_kb_enchantCurrent = 0x2f6038;
inline constexpr std::uint32_t require_facing_awayRecord = 0x2f6040;
inline constexpr std::uint32_t require_facing_awayCurrent = 0x2f6058;
inline constexpr std::uint32_t directionRecord = 0x2f6088;
inline constexpr std::uint32_t directionCurrent = 0x2f60b8;
inline constexpr std::uint32_t hide_rotationRecord = 0x2f60c8;
inline constexpr std::uint32_t hide_rotationCurrent = 0x2f60e0;
inline constexpr std::uint32_t use_last_strafeRecord = 0x2f60e8;
inline constexpr std::uint32_t use_last_strafeCurrent = 0x2f6100;
inline constexpr std::uint32_t nativeData_3043d8 = 0x3043d8;
inline constexpr std::uint32_t nativeData_3043dc = 0x3043dc;
inline constexpr std::uint32_t packetDispatchPending = 0x304af0;
inline constexpr std::uint32_t displacementActive = 0x304af1;
inline constexpr std::uint32_t displacementWasActive = 0x304af2;
inline constexpr std::uint32_t targetInputSeen = 0x304af3;
inline constexpr std::uint32_t targetInputTicks = 0x304af4;
inline constexpr std::uint32_t activationTicks = 0x304af8;
inline constexpr std::uint32_t retainedRotation = 0x304b00;
inline constexpr std::uint32_t movementDirection = 0x304b08;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    ChoiceSetting &direction() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::directionRecord);
    }
    BooleanSetting &use_last_strafe() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::use_last_strafeRecord);
    }
    NumberSetting &angle() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::angleRecord);
    }
    NumberSetting &cooldown() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::cooldownRecord);
    }
    BooleanSetting &hide_rotation() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::hide_rotationRecord);
    }
    BooleanSetting &require_no_kb() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_no_kbRecord);
    }
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_weaponRecord);
    }
    BooleanSetting &require_kb_enchant() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_kb_enchantRecord);
    }
    BooleanSetting &require_facing_away() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_facing_awayRecord);
    }
};
// Runtime-observed native labels for config key "direction". Numeric values preserved.
enum class DirectionMode : std::uint32_t {
    Left = 0,
    Right = 1,
    Random = 2,
    Strafe = 3,
    Strafe__inverted = 4,
};
} // namespace reconstruction::Knockback_Displace
#endif // SLINKY_SHARE_F4A5AF7A30361D5F575B
