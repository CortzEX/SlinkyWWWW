#include "module_float_distance.hpp"
#include <bit>
#include <emmintrin.h>

static __m128 scalar(std::uint32_t bits) {
    return _mm_castsi128_ps(_mm_cvtsi32_si128(std::bit_cast<std::int32_t>(bits)));
}
static std::uint32_t word(__m128 value) {
    return static_cast<std::uint32_t>(_mm_cvtsi128_si32(_mm_castps_si128(value)));
}
// 0xab7c0. Every finite binary32 square is exact and normal in binary64.
extern "C" __declspec(dllexport) std::uint32_t recovered_float_distance(std::uint32_t first,
    std::uint32_t second, const FloatDistanceConstants *constants) {
    const auto a = first & 0x7fffffffu, b = second & 0x7fffffffu;
    if (a == 0x7f800000u || b == 0x7f800000u) return constants->infinity;
    if (a > 0x7f800000u || b > 0x7f800000u) return constants->nan;
    const auto x = _mm_cvtss_sd(_mm_setzero_pd(), scalar(first));
    const auto y = _mm_cvtss_sd(_mm_setzero_pd(), scalar(second));
    const auto sum = _mm_add_sd(_mm_mul_sd(x, x), _mm_mul_sd(y, y));
    return word(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_sqrt_sd(sum, sum)));
}
// 0x9ee0 subtracts both packed float lanes before classification.
extern "C" __declspec(dllexport) std::uint32_t recovered_packed_float_distance(std::uint64_t first,
    std::uint64_t second, const FloatDistanceConstants *constants) {
    const auto x = word(_mm_sub_ss(scalar(static_cast<std::uint32_t>(first)), scalar(static_cast<std::uint32_t>(second))));
    const auto y = word(_mm_sub_ss(scalar(static_cast<std::uint32_t>(first >> 32)), scalar(static_cast<std::uint32_t>(second >> 32))));
    return recovered_float_distance(x, y, constants);
}
