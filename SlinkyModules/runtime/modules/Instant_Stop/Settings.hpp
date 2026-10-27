#ifndef SLINKY_SHARE_E5249ED60B972E65F69D
#define SLINKY_SHARE_E5249ED60B972E65F69D
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
namespace reconstruction::Instant_Stop {
namespace Storage {
inline constexpr std::uint32_t nativeData_1547a8 = 0x1547a8;
inline constexpr std::uint32_t nativeData_1547b0 = 0x1547b0;
inline constexpr std::uint32_t nativeData_1547b4 = 0x1547b4;
inline constexpr std::uint32_t moduleDescriptor = 0x2f2a80;
inline constexpr std::uint32_t stoppingPhase = 0x3043d0;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
};
} // namespace reconstruction::Instant_Stop
#endif // SLINKY_SHARE_E5249ED60B972E65F69D
