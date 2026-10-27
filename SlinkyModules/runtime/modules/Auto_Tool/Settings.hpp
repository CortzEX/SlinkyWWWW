#ifndef SLINKY_SHARE_EAE01518541D4E21C825
#define SLINKY_SHARE_EAE01518541D4E21C825
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
namespace reconstruction::Auto_Tool {
namespace Storage {
inline constexpr std::uint32_t nativeData_13cf70 = 0x13cf70;
inline constexpr std::uint32_t nativeData_152420 = 0x152420;
inline constexpr std::uint32_t moduleDescriptor = 0x2ee158;
inline constexpr std::uint32_t nativeData_2ee368 = 0x2ee368;
inline constexpr std::uint32_t nativeData_2ee36c = 0x2ee36c;
inline constexpr std::uint32_t activation_timeRecord = 0x2ee370;
inline constexpr std::uint32_t activation_timeCurrent = 0x2ee3a0;
inline constexpr std::uint32_t allow_using_fistsRecord = 0x2ee3a8;
inline constexpr std::uint32_t allow_using_fistsCurrent = 0x2ee3c0;
inline constexpr std::uint32_t allow_using_swordRecord = 0x2ee3c8;
inline constexpr std::uint32_t allow_using_swordCurrent = 0x2ee3e0;
inline constexpr std::uint32_t allow_using_toolsRecord = 0x2ee3e8;
inline constexpr std::uint32_t allow_using_toolsCurrent = 0x2ee400;
inline constexpr std::uint32_t allow_using_otherRecord = 0x2ee408;
inline constexpr std::uint32_t allow_using_otherCurrent = 0x2ee420;
inline constexpr std::uint32_t require_sneakRecord = 0x2ee428;
inline constexpr std::uint32_t require_sneakCurrent = 0x2ee440;
inline constexpr std::uint32_t restrict_allowed_blocksRecord = 0x2ee448;
inline constexpr std::uint32_t restrict_allowed_blocksCurrent = 0x2ee460;
inline constexpr std::uint32_t switch_backRecord = 0x2ee468;
inline constexpr std::uint32_t switch_backCurrent = 0x2ee480;
inline constexpr std::uint32_t allowed_blocksRecord = 0x2ee488;
inline constexpr std::uint32_t nativeData_2fc520 = 0x2fc520;
inline constexpr std::uint32_t nativeData_2fc528 = 0x2fc528;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &activation_time() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::activation_timeRecord);
    }
    BooleanSetting &switch_back() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::switch_backRecord);
    }
    BooleanSetting &allow_using_sword() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::allow_using_swordRecord);
    }
    BooleanSetting &allow_using_tools() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::allow_using_toolsRecord);
    }
    BooleanSetting &allow_using_fists() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::allow_using_fistsRecord);
    }
    BooleanSetting &allow_using_other() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::allow_using_otherRecord);
    }
    BooleanSetting &require_sneak() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_sneakRecord);
    }
    BooleanSetting &restrict_allowed_blocks() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::restrict_allowed_blocksRecord);
    }
    ListSetting &allowed_blocks() const {
        return *reinterpret_cast<ListSetting *>(image + Storage::allowed_blocksRecord);
    }
};
} // namespace reconstruction::Auto_Tool
#endif // SLINKY_SHARE_EAE01518541D4E21C825
