#ifndef SLINKY_SHARE_FFFAE54EBF0A4204E69C
#define SLINKY_SHARE_FFFAE54EBF0A4204E69C
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
namespace reconstruction::Block_In {
namespace Storage {
inline constexpr std::uint32_t nativeData_156870 = 0x156870;
inline constexpr std::uint32_t nativeData_156880 = 0x156880;
inline constexpr std::uint32_t nativeData_156890 = 0x156890;
inline constexpr std::uint32_t nativeData_1568a0 = 0x1568a0;
inline constexpr std::uint32_t nativeData_1568a8 = 0x1568a8;
inline constexpr std::uint32_t nativeData_1568b0 = 0x1568b0;
inline constexpr std::uint32_t nativeData_1568b4 = 0x1568b4;
inline constexpr std::uint32_t nativeData_1568b8 = 0x1568b8;
inline constexpr std::uint32_t nativeData_1568c0 = 0x1568c0;
inline constexpr std::uint32_t nativeData_1568c8 = 0x1568c8;
inline constexpr std::uint32_t nativeData_1568d0 = 0x1568d0;
inline constexpr std::uint32_t nativeData_1568d8 = 0x1568d8;
inline constexpr std::uint32_t nativeData_1568dc = 0x1568dc;
inline constexpr std::uint32_t nativeData_1568e4 = 0x1568e4;
inline constexpr std::uint32_t nativeData_1568e8 = 0x1568e8;
inline constexpr std::uint32_t nativeData_1568ec = 0x1568ec;
inline constexpr std::uint32_t nativeData_1568f0 = 0x1568f0;
inline constexpr std::uint32_t nativeData_1568f4 = 0x1568f4;
inline constexpr std::uint32_t nativeData_1568f8 = 0x1568f8;
inline constexpr std::uint32_t nativeData_156900 = 0x156900;
inline constexpr std::uint32_t nativeData_156910 = 0x156910;
inline constexpr std::uint32_t nativeData_156920 = 0x156920;
inline constexpr std::uint32_t nativeData_156930 = 0x156930;
inline constexpr std::uint32_t nativeData_156940 = 0x156940;
inline constexpr std::uint32_t nativeData_156b80 = 0x156b80;
inline constexpr std::uint32_t nativeData_156b9e = 0x156b9e;
inline constexpr std::uint32_t nativeData_156b9f = 0x156b9f;
inline constexpr std::uint32_t nativeData_156ba8 = 0x156ba8;
inline constexpr std::uint32_t nativeData_156bb0 = 0x156bb0;
inline constexpr std::uint32_t moduleDescriptor = 0x2f6108;
inline constexpr std::uint32_t require_groundRecord = 0x2f6318;
inline constexpr std::uint32_t require_groundCurrent = 0x2f6330;
inline constexpr std::uint32_t speedRecord = 0x2f6338;
inline constexpr std::uint32_t speedCurrent = 0x2f6368;
inline constexpr std::uint32_t nativeData_304b10 = 0x304b10;
inline constexpr std::uint32_t nativeData_304b18 = 0x304b18;
inline constexpr std::uint32_t nativeData_304b1c = 0x304b1c;
inline constexpr std::uint32_t nativeData_304b20 = 0x304b20;
inline constexpr std::uint32_t nativeData_304b28 = 0x304b28;
inline constexpr std::uint32_t nativeData_304b30 = 0x304b30;
inline constexpr std::uint32_t nativeData_304b38 = 0x304b38;
inline constexpr std::uint32_t nativeData_304b48 = 0x304b48;
inline constexpr std::uint32_t nativeData_304b58 = 0x304b58;
inline constexpr std::uint32_t nativeData_304b68 = 0x304b68;
inline constexpr std::uint32_t nativeData_304b78 = 0x304b78;
inline constexpr std::uint32_t nativeData_304b88 = 0x304b88;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &speed() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::speedRecord);
    }
    BooleanSetting &require_ground() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_groundRecord);
    }
};
} // namespace reconstruction::Block_In
#endif // SLINKY_SHARE_FFFAE54EBF0A4204E69C
