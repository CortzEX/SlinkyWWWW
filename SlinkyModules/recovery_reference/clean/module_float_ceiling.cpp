#include "module_float_ceiling.hpp"
#include <bit>
#include <emmintrin.h>

static __m128 scalar(std::uint32_t bits) {
    return _mm_castsi128_ps(_mm_cvtsi32_si128(std::bit_cast<std::int32_t>(bits)));
}

// 0xb2920 retains the addition, including its floating-point side effects.
extern "C" __declspec(dllexport) std::uint32_t recovered_float_ceiling_bits(
    std::uint32_t bits, const FloatCeilingConstants *constants) {
    const auto exponent = (bits >> 23) & 255u;
    if (exponent >= 150) return bits;
    if (exponent >= 127) {
        const auto mask = 0xffffffffu << ((22u - (bits >> 23)) & 31u);
        const auto fraction = ~mask;
        if (!(bits & fraction)) return bits;
        volatile float raised = _mm_cvtss_f32(_mm_add_ss(scalar(bits), scalar(constants->addition_bias)));
        return (bits + ((bits & 0x80000000u) ? 0u : fraction)) & mask;
    }
    volatile float raised = _mm_cvtss_f32(_mm_add_ss(scalar(constants->addition_bias), scalar(bits)));
    if (bits & 0x80000000u) return constants->negative_zero;
    return bits ? constants->one : bits;
}
