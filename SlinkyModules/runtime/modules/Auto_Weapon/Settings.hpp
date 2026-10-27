#ifndef SLINKY_SHARE_7B7034FCA0DDFF3E51E7
#define SLINKY_SHARE_7B7034FCA0DDFF3E51E7
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
namespace reconstruction::Auto_Weapon {
namespace Storage {
inline constexpr std::uint32_t moduleDescriptor = 0x2f5af8;
inline constexpr std::uint32_t activation_timeRecord = 0x2f5d08;
inline constexpr std::uint32_t activation_timeCurrent = 0x2f5d38;
inline constexpr std::uint32_t require_mouse_pressedRecord = 0x2f5d40;
inline constexpr std::uint32_t require_mouse_pressedCurrent = 0x2f5d58;
inline constexpr std::uint32_t selectionDelayTicks = 0x304ae8;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &activation_time() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::activation_timeRecord);
    }
    BooleanSetting &require_mouse_pressed() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_mouse_pressedRecord);
    }
};
} // namespace reconstruction::Auto_Weapon
#endif // SLINKY_SHARE_7B7034FCA0DDFF3E51E7
