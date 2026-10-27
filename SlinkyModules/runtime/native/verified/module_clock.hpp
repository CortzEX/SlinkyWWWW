#ifndef SLINKY_SHARE_60EF1C285734ACC80CDF
#define SLINKY_SHARE_60EF1C285734ACC80CDF
#include <cstdint>

extern "C" {
__declspec(dllexport) std::uint64_t recovered_clock_bits(std::uint64_t *frequency_bits,
    const std::uint8_t *encoded_frequency_target, const std::uint8_t *encoded_counter_target);
__declspec(dllexport) double recovered_clock_value(std::uint64_t *frequency_bits,
    const std::uint8_t *encoded_frequency_target, const std::uint8_t *encoded_counter_target);
}
#endif // SLINKY_SHARE_60EF1C285734ACC80CDF
