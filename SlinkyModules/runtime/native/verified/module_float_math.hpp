#ifndef SLINKY_SHARE_BF2FB20AD01675D50933
#define SLINKY_SHARE_BF2FB20AD01675D50933
#include <cstdint>

struct AngleWrapConstants {
    float period;
    float upper;
    float upper_adjustment;
    float lower;
};

extern "C" {
__declspec(dllexport) std::uint64_t recovered_remainder_b2170(std::uint64_t dividend_bits, std::uint64_t divisor_bits);
__declspec(dllexport) std::uint32_t recovered_remainder_b2300(std::uint32_t dividend_bits, std::uint32_t divisor_bits);
__declspec(dllexport) float recovered_wrap_angle(float angle, const AngleWrapConstants *);
}
#endif // SLINKY_SHARE_BF2FB20AD01675D50933
