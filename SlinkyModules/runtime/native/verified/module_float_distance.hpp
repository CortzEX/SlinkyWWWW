#ifndef SLINKY_SHARE_E8BF78B1FEC59F29EA9A
#define SLINKY_SHARE_E8BF78B1FEC59F29EA9A
#include <cstdint>

struct FloatDistanceConstants {
    std::uint32_t infinity = 0x7f800000u, nan = 0x7fc00000u;
};
extern "C" {
__declspec(dllexport) std::uint32_t recovered_float_distance(std::uint32_t first,
    std::uint32_t second, const FloatDistanceConstants *);
__declspec(dllexport) std::uint32_t recovered_packed_float_distance(std::uint64_t first,
    std::uint64_t second, const FloatDistanceConstants *);
}
#endif // SLINKY_SHARE_E8BF78B1FEC59F29EA9A
