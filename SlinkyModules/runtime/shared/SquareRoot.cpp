// Runtime instruction evidence: reports/native/render_math_af2f0.asm and
// render_math_af4a0.asm. Unsigned arithmetic retains native wrapping widths.
#include "SquareRoot.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>
#include <intrin.h>

namespace {
template<class T> T read(const std::uint8_t *image, std::size_t rva) {
    T value; std::memcpy(&value, image + rva, sizeof value); return value;
}
std::uint64_t upperProduct(std::uint64_t a, std::uint64_t b) { return __umulh(a, b); }
}

// Native RVA AF2F0: fixed-point reciprocal refinement followed by exact square
// residual comparison and a floating addition that applies current rounding.
double recovered_square_root_af2f0(double input, const std::uint8_t *image) {
    std::uint64_t bits = std::bit_cast<std::uint64_t>(input);
    std::uint64_t exponent = bits >> 52;
    if (exponent - 0x7ffu < std::uint64_t(0) - 0x7feu) {
        if (input == 0.0 || bits == 0x7ff0000000000000ull) return input;
        if (bits > 0x7ff0000000000000ull) {
            const auto zero = _mm_setzero_pd();
            auto value = _mm_set_sd(input);
            value = _mm_sub_sd(value, value);
            return _mm_cvtsd_f64(_mm_div_sd(value, zero));
        }
        input = _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(input), _mm_set_sd(read<double>(image, 0x2bb738))));
        bits = std::bit_cast<std::uint64_t>(input);
        exponent = (bits >> 52) - 52u;
    }
    std::uint64_t significand = (bits << 11) | 0x8000000000000000ull;
    if (exponent & 1) significand = (bits << 10) & 0x7ffffffffffffc00ull;
    std::uint64_t reciprocal = std::uint64_t(read<std::uint16_t>(image, 0x2bdf40 + 2 * ((bits >> 46) & 0x7f))) << 16;
    std::uint64_t root = ((significand >> 32) * reciprocal) >> 32;
    const std::uint64_t square = (root * reciprocal) >> 32;
    std::uint32_t correction = 0xc0000000u - std::uint32_t(square);
    reciprocal = std::uint32_t((reciprocal * correction) >> 31) & 0xfffffffeu;
    root = std::uint32_t((root * correction) >> 31) & 0xfffffffeu;
    correction = 0xc0000000u - std::uint32_t((root * reciprocal) >> 32);
    const std::uint64_t inverse = (2 * (std::uint64_t(correction) * reciprocal)) & 0xfffffffe00000000ull;
    root = upperProduct(inverse, significand);
    root = upperProduct(root, 0xc000000000000000ull - upperProduct(root, inverse));
    root = (root - 2) >> 9;
    significand <<= 42;
    const std::uint64_t residual = root * root - significand + root;
    const std::uint64_t rounded = root + (residual >> 63);
    std::uint64_t test = root + residual;
    const std::uint64_t result = ((0x1ff8000000000000ull + (exponent << 51)) & 0xfff0000000000000ull) |
        (rounded & 0x000fffffffffffffull);
    auto value = _mm_set_sd(std::bit_cast<double>(result));
    ++test;
    if (test != 0) {
        const std::uint64_t adjustment = 0x0010000000000000ull | ((test ^ residual) & 0x8000000000000000ull);
        value = _mm_add_sd(value, _mm_set_sd(std::bit_cast<double>(adjustment)));
    }
    return _mm_cvtsd_f64(value);
}

// Native RVA AF4A0: binary32 counterpart, including its always-executed final
// ADDSS (the exact-square path adds signed zero).
float recovered_square_root_af4a0(float input, const std::uint8_t *image) {
    std::uint32_t bits = std::bit_cast<std::uint32_t>(input);
    if (bits - 0x7f800000u < 0x81000000u) {
        if (input == 0.0f || bits == 0x7f800000u) return input;
        if (bits >= 0x7f800001u) {
            auto value = _mm_set_ss(input);
            value = _mm_sub_ss(value, value);
            return _mm_cvtss_f32(_mm_div_ss(value, _mm_setzero_ps()));
        }
        input = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(input), _mm_set_ss(read<float>(image, 0x2bb740))));
        bits = std::bit_cast<std::uint32_t>(input) + 0xf4800000u;
    }
    std::uint32_t significand = (bits << 8) | 0x80000000u;
    if (bits & 0x00800000u) significand = (bits << 7) & 0x7fffff80u;
    const std::uint32_t exponent = ((bits >> 1) + 0x1fc00000u) & 0x7f800000u;
    std::uint64_t reciprocal = std::uint64_t(read<std::uint16_t>(image, 0x2bdf40 + ((bits >> 16) & 0xfe))) << 16;
    std::uint64_t root = (std::uint64_t(significand) * reciprocal) >> 32;
    const std::uint64_t square = (root * reciprocal) >> 32;
    std::uint32_t correction = 0xc0000000u - std::uint32_t(square);
    reciprocal = std::uint32_t((reciprocal * correction) >> 31) & 0xfffffffeu;
    root = std::uint32_t((root * correction) >> 31) & 0xfffffffeu;
    correction = 0xc0000000u - std::uint32_t((reciprocal * root) >> 32);
    std::uint32_t integer = (std::uint32_t((std::uint64_t(correction) * root) >> 32) - 1u) >> 6;
    significand <<= 16;
    const std::uint32_t residual = integer * integer - significand + integer;
    const std::uint32_t rounded = integer + (residual >> 31);
    std::uint32_t test = integer + residual;
    auto value = _mm_set_ss(std::bit_cast<float>(exponent | (rounded & 0x007fffffu)));
    ++test;
    const std::uint32_t adjustment = (test == 0 ? 0u : 0x01000000u) |
        ((test ^ residual) & 0x80000000u);
    return _mm_cvtss_f32(_mm_add_ss(value, _mm_set_ss(std::bit_cast<float>(adjustment))));
}
