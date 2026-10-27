#include "module_float_math.hpp"
#include <bit>
#include <emmintrin.h>

// Invalid inputs retain the original SSE multiply-then-divide operand order.
static std::uint64_t invalid_double(std::uint64_t x, std::uint64_t y) {
    const auto a = _mm_castsi128_pd(_mm_cvtsi64_si128(std::bit_cast<std::int64_t>(x)));
    const auto b = _mm_castsi128_pd(_mm_cvtsi64_si128(std::bit_cast<std::int64_t>(y)));
    const auto product = _mm_mul_sd(a, b);
    return static_cast<std::uint64_t>(_mm_cvtsi128_si64(_mm_castpd_si128(_mm_div_sd(product, product))));
}

static std::uint32_t invalid_float(std::uint32_t x, std::uint32_t y) {
    const auto a = _mm_castsi128_ps(_mm_cvtsi32_si128(std::bit_cast<std::int32_t>(x)));
    const auto b = _mm_castsi128_ps(_mm_cvtsi32_si128(std::bit_cast<std::int32_t>(y)));
    const auto product = _mm_mul_ss(a, b);
    return static_cast<std::uint32_t>(_mm_cvtsi128_si32(_mm_castps_si128(_mm_div_ss(product, product))));
}

// 0xb2170. Divide normalized significands by subtracting and shifting.
extern "C" __declspec(dllexport) std::uint64_t recovered_remainder_b2170(std::uint64_t x, std::uint64_t y) {
    constexpr std::uint64_t implicit = 0x10000000000000ull;
    const auto sign = x & 0x8000000000000000ull;
    auto dividend = x & 0x7fffffffffffffffull;
    auto divisor = y & 0x7fffffffffffffffull;
    auto dividend_exponent = static_cast<int>(dividend >> 52);
    auto divisor_exponent = static_cast<int>(divisor >> 52);
    if (divisor == 0 || divisor > 0x7ff0000000000000ull || dividend_exponent == 0x7ff)
        return invalid_double(x, y);
    if (dividend <= divisor) return dividend == divisor ? sign : x;
    if (dividend_exponent) dividend = (dividend & (implicit - 1)) | implicit;
    else {
        dividend_exponent = 1;
        while (dividend < implicit) { dividend <<= 1; --dividend_exponent; }
    }
    if (divisor_exponent) divisor = (divisor & (implicit - 1)) | implicit;
    else {
        divisor_exponent = 1;
        while (divisor < implicit) { divisor <<= 1; --divisor_exponent; }
    }
    while (dividend_exponent > divisor_exponent) {
        if (dividend >= divisor) {
            dividend -= divisor;
            if (!dividend) return sign;
        }
        dividend <<= 1;
        --dividend_exponent;
    }
    if (dividend >= divisor) {
        dividend -= divisor;
        if (!dividend) return sign;
    }
    while (dividend < implicit) { dividend <<= 1; --dividend_exponent; }
    if (dividend_exponent > 0)
        dividend = (dividend - implicit) | (static_cast<std::uint64_t>(dividend_exponent) << 52);
    else dividend >>= 1 - dividend_exponent;
    return dividend | sign;
}

// 0xb2300 uses the same division on binary32's 24-bit significand.
extern "C" __declspec(dllexport) std::uint32_t recovered_remainder_b2300(std::uint32_t x, std::uint32_t y) {
    constexpr std::uint32_t implicit = 0x800000u;
    const auto sign = x & 0x80000000u;
    auto dividend = x & 0x7fffffffu;
    auto divisor = y & 0x7fffffffu;
    auto dividend_exponent = static_cast<int>(dividend >> 23);
    auto divisor_exponent = static_cast<int>(divisor >> 23);
    if (divisor == 0 || divisor > 0x7f800000u || dividend_exponent == 0xff)
        return invalid_float(x, y);
    if (dividend <= divisor) return dividend == divisor ? sign : x;
    if (dividend_exponent) dividend = (dividend & (implicit - 1)) | implicit;
    else {
        dividend_exponent = 1;
        while (dividend < implicit) { dividend <<= 1; --dividend_exponent; }
    }
    if (divisor_exponent) divisor = (divisor & (implicit - 1)) | implicit;
    else {
        divisor_exponent = 1;
        while (divisor < implicit) { divisor <<= 1; --divisor_exponent; }
    }
    while (dividend_exponent > divisor_exponent) {
        if (dividend >= divisor) {
            dividend -= divisor;
            if (!dividend) return sign;
        }
        dividend <<= 1;
        --dividend_exponent;
    }
    if (dividend >= divisor) {
        dividend -= divisor;
        if (!dividend) return sign;
    }
    while (dividend < implicit) { dividend <<= 1; --dividend_exponent; }
    if (dividend_exponent > 0)
        dividend = (dividend - implicit) | (static_cast<std::uint32_t>(dividend_exponent) << 23);
    else dividend >>= 1 - dividend_exponent;
    return dividend | sign;
}

// 0xa210. Constants remain caller-owned data, including their original comparison order.
extern "C" __declspec(dllexport) float recovered_wrap_angle(float angle, const AngleWrapConstants *constants) {
    auto value = std::bit_cast<float>(recovered_remainder_b2300(
        std::bit_cast<std::uint32_t>(angle), std::bit_cast<std::uint32_t>(constants->period)));
    if (value >= constants->upper)
        value = _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(value), _mm_set_ss(constants->upper_adjustment)));
    else if (value < constants->lower)
        value = _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(value), _mm_set_ss(constants->period)));
    return value;
}
