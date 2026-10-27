#ifndef SLINKY_SHARE_E821A7064FCF3A6B3EB8
#define SLINKY_SHARE_E821A7064FCF3A6B3EB8
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
namespace reconstruction::Bridge_Assist {
namespace Storage {
inline constexpr std::uint32_t nativeData_150760 = 0x150760;
inline constexpr std::uint32_t nativeData_150770 = 0x150770;
inline constexpr std::uint32_t nativeData_150780 = 0x150780;
inline constexpr std::uint32_t nativeData_150784 = 0x150784;
inline constexpr std::uint32_t nativeData_150790 = 0x150790;
inline constexpr std::uint32_t nativeData_1507a0 = 0x1507a0;
inline constexpr std::uint32_t nativeData_1507a8 = 0x1507a8;
inline constexpr std::uint32_t nativeData_1507b0 = 0x1507b0;
inline constexpr std::uint32_t nativeData_1507b8 = 0x1507b8;
inline constexpr std::uint32_t nativeData_1507c0 = 0x1507c0;
inline constexpr std::uint32_t nativeData_1507c4 = 0x1507c4;
inline constexpr std::uint32_t nativeData_1507c8 = 0x1507c8;
inline constexpr std::uint32_t nativeData_1507cc = 0x1507cc;
inline constexpr std::uint32_t nativeData_1507d0 = 0x1507d0;
inline constexpr std::uint32_t nativeData_1507d8 = 0x1507d8;
inline constexpr std::uint32_t nativeData_1507dc = 0x1507dc;
inline constexpr std::uint32_t nativeData_1507e0 = 0x1507e0;
inline constexpr std::uint32_t nativeData_1507e8 = 0x1507e8;
inline constexpr std::uint32_t moduleDescriptor = 0x2e9ac0;
inline constexpr std::uint32_t require_sneakRecord = 0x2e9cd0;
inline constexpr std::uint32_t require_sneakCurrent = 0x2e9ce8;
inline constexpr std::uint32_t require_looking_downRecord = 0x2e9cf0;
inline constexpr std::uint32_t require_looking_downCurrent = 0x2e9d08;
inline constexpr std::uint32_t require_not_forwardRecord = 0x2e9d10;
inline constexpr std::uint32_t require_not_forwardCurrent = 0x2e9d28;
inline constexpr std::uint32_t select_blocksRecord = 0x2e9d48;
inline constexpr std::uint32_t select_blocksCurrent = 0x2e9d78;
inline constexpr std::uint32_t require_holding_blocksRecord = 0x2e9d88;
inline constexpr std::uint32_t require_holding_blocksCurrent = 0x2e9da0;
inline constexpr std::uint32_t sneak_on_jumpRecord = 0x2e9da8;
inline constexpr std::uint32_t sneak_on_jumpCurrent = 0x2e9dc0;
inline constexpr std::uint32_t edge_offsetRecord = 0x2e9dc8;
inline constexpr std::uint32_t edge_offsetCurrent = 0x2e9df8;
inline constexpr std::uint32_t randomizeRecord = 0x2e9e00;
inline constexpr std::uint32_t randomizeCurrent = 0x2e9e18;
inline constexpr std::uint32_t avoid_double_sneakRecord = 0x2e9e20;
inline constexpr std::uint32_t avoid_double_sneakCurrent = 0x2e9e38;
inline constexpr std::uint32_t unsneak_delayRecord = 0x2e9e40;
inline constexpr std::uint32_t unsneak_delayCurrent = 0x2e9e70;
inline constexpr std::uint32_t sneakStateOwned = 0x2f7dc8;
inline constexpr std::uint32_t placementCooldown = 0x2f7dcc;
inline constexpr std::uint32_t placementInputGate = 0x2f7dd0;
inline constexpr std::uint32_t placementActionGate = 0x2f7dd1;
inline constexpr std::uint32_t unsneakCountdown = 0x2f7dd4;
inline constexpr std::uint32_t heldBlockGraceTicks = 0x2f7dd8;
inline constexpr std::uint32_t nativeData_2f7df0 = 0x2f7df0;
inline constexpr std::uint32_t nativeData_2f7e00 = 0x2f7e00;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &edge_offset() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::edge_offsetRecord);
    }
    NumberSetting &unsneak_delay() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::unsneak_delayRecord);
    }
    ChoiceSetting &select_blocks() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::select_blocksRecord);
    }
    BooleanSetting &randomize() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::randomizeRecord);
    }
    BooleanSetting &sneak_on_jump() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::sneak_on_jumpRecord);
    }
    BooleanSetting &avoid_double_sneak() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::avoid_double_sneakRecord);
    }
    BooleanSetting &require_sneak() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_sneakRecord);
    }
    BooleanSetting &require_holding_blocks() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_holding_blocksRecord);
    }
    BooleanSetting &require_looking_down() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_looking_downRecord);
    }
    BooleanSetting &require_not_forward() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_not_forwardRecord);
    }
};
// Runtime-observed native labels for config key "select_blocks". Numeric values preserved.
enum class Select_blocksMode : std::uint32_t {
    No = 0,
    On_depletion = 1,
    Always = 2,
};
} // namespace reconstruction::Bridge_Assist
#endif // SLINKY_SHARE_E821A7064FCF3A6B3EB8
