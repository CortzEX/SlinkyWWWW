#include "module_clock.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>

static __m128d scalar(std::uint64_t bits) {
    return _mm_castsi128_pd(_mm_cvtsi64_si128(std::bit_cast<std::int64_t>(bits)));
}
static void sample(const std::uint8_t *cell, std::uintptr_t addend, std::int64_t *output) {
    std::uintptr_t encoded;
    std::memcpy(&encoded, cell, sizeof(encoded));
    using Function = std::uintptr_t (*)(std::int64_t *);
    reinterpret_cast<Function>(encoded + addend)(output);
}
// 0x4c270 ignores endpoint status and reuses one output address for both samples.
extern "C" __declspec(dllexport) std::uint64_t recovered_clock_bits(std::uint64_t *frequency_bits,
    const std::uint8_t *frequency_target, const std::uint8_t *counter_target) {
    std::int64_t value;
    if (_mm_cvtsd_f64(scalar(*frequency_bits)) == 0.0) {
        sample(frequency_target, 0x610ebebc, &value);
        *frequency_bits = static_cast<std::uint64_t>(_mm_cvtsi128_si64(_mm_castpd_si128(
            _mm_cvtsi64_sd(_mm_setzero_pd(), value))));
    }
    sample(counter_target, 0x62379417, &value);
    const auto result = _mm_div_sd(_mm_cvtsi64_sd(_mm_setzero_pd(), value), scalar(*frequency_bits));
    return static_cast<std::uint64_t>(_mm_cvtsi128_si64(_mm_castpd_si128(result)));
}
extern "C" __declspec(dllexport) double recovered_clock_value(std::uint64_t *frequency_bits,
    const std::uint8_t *frequency_target, const std::uint8_t *counter_target) {
    return std::bit_cast<double>(recovered_clock_bits(frequency_bits, frequency_target, counter_target));
}
