#ifndef SLINKY_SHARE_1A5B0F139D71941AA7EF
#define SLINKY_SHARE_1A5B0F139D71941AA7EF
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
namespace reconstruction::Auto_Soup {
namespace Storage {
inline constexpr std::uint32_t nativeData_1505a8 = 0x1505a8;
inline constexpr std::uint32_t nativeData_1505ac = 0x1505ac;
inline constexpr std::uint32_t nativeData_1505b0 = 0x1505b0;
inline constexpr std::uint32_t nativeData_1505b8 = 0x1505b8;
inline constexpr std::uint32_t nativeData_1505c0 = 0x1505c0;
inline constexpr std::uint32_t moduleDescriptor = 0x2e96b0;
inline constexpr std::uint32_t single_soup_max_hpRecord = 0x2e98c0;
inline constexpr std::uint32_t single_soup_max_hpCurrent = 0x2e98f0;
inline constexpr std::uint32_t delay_beforeRecord = 0x2e98f8;
inline constexpr std::uint32_t delay_beforeCurrent = 0x2e9928;
inline constexpr std::uint32_t double_soup_max_hpRecord = 0x2e9930;
inline constexpr std::uint32_t double_soup_max_hpCurrent = 0x2e9960;
inline constexpr std::uint32_t delay_betweenRecord = 0x2e9968;
inline constexpr std::uint32_t delay_betweenCurrent = 0x2e9998;
inline constexpr std::uint32_t delay_afterRecord = 0x2e99a0;
inline constexpr std::uint32_t delay_afterCurrent = 0x2e99d0;
inline constexpr std::uint32_t randomizationRecord = 0x2e99d8;
inline constexpr std::uint32_t randomizationCurrent = 0x2e9a08;
inline constexpr std::uint32_t override_itemRecord = 0x2e9a10;
inline constexpr std::uint32_t override_itemCurrent = 0x2e9a28;
inline constexpr std::uint32_t drop_bowlsRecord = 0x2e9a30;
inline constexpr std::uint32_t drop_bowlsCurrent = 0x2e9a48;
inline constexpr std::uint32_t allowed_itemsRecord = 0x2e9a50;
inline constexpr std::uint32_t cancelRequested = 0x2f7d68;
inline constexpr std::uint32_t soupPhase = 0x2f7d6c;
inline constexpr std::uint32_t reusePreviousSlot = 0x2f7d70;
inline constexpr std::uint32_t selectedSoupSlot = 0x2f7d74;
inline constexpr std::uint32_t previousSlot = 0x2f7d78;
inline constexpr std::uint32_t repeatUsePending = 0x2f7d7c;
inline constexpr std::uint32_t selectedItemIsSoup = 0x2f7d7d;
inline constexpr std::uint32_t remainingDelay = 0x2f7d80;
inline constexpr std::uint32_t nativeData_2f7da8 = 0x2f7da8;
inline constexpr std::uint32_t nativeData_2f7db8 = 0x2f7db8;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &single_soup_max_hp() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::single_soup_max_hpRecord);
    }
    NumberSetting &double_soup_max_hp() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::double_soup_max_hpRecord);
    }
    NumberSetting &randomization() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::randomizationRecord);
    }
    NumberSetting &delay_before() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::delay_beforeRecord);
    }
    NumberSetting &delay_between() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::delay_betweenRecord);
    }
    NumberSetting &delay_after() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::delay_afterRecord);
    }
    BooleanSetting &drop_bowls() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::drop_bowlsRecord);
    }
    BooleanSetting &override_item() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::override_itemRecord);
    }
    ListSetting &allowed_items() const {
        return *reinterpret_cast<ListSetting *>(image + Storage::allowed_itemsRecord);
    }
};
} // namespace reconstruction::Auto_Soup
#endif // SLINKY_SHARE_1A5B0F139D71941AA7EF
