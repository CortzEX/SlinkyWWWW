#include "Logarithm.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>

namespace {
__m128 scalar(const std::uint8_t *image, std::size_t rva) {
  float value;
  std::memcpy(&value, image + rva, sizeof value);
  return _mm_set_ss(value);
}
__m128 lanes(const std::uint8_t *image, std::size_t rva) {
  __m128 value;
  std::memcpy(&value, image + rva, sizeof value);
  return value;
}
}

// Native RVA B2050. The signed initial classification, packed polynomial, and
// separate SSE operations preserve the captured exceptional paths and order.
float recovered_logarithm_b2050(float input, const std::uint8_t *image) {
  auto bits = std::bit_cast<std::uint32_t>(input);
  auto value = _mm_set_ss(input);
  std::int32_t exponentOffset;
  if (std::bit_cast<std::int32_t>(bits) < 0x00800000) {
    const auto zero = _mm_setzero_ps();
    if (_mm_ucomieq_ss(value, zero) &&
        _mm_movemask_ps(_mm_cmpunord_ss(value, zero)) == 0) {
      value = _mm_mul_ss(value, value);
      return _mm_cvtss_f32(_mm_div_ss(scalar(image, 0x2bc4f4), value));
    }
    if (bits & 0x80000000u) {
      value = _mm_sub_ss(value, value);
      return _mm_cvtss_f32(_mm_div_ss(value, zero));
    }
    value = _mm_mul_ss(value, scalar(image, 0x2bc4f0));
    bits = std::bit_cast<std::uint32_t>(_mm_cvtss_f32(value));
    exponentOffset = -152;
  } else {
    if (bits > 0x7f7fffffu) return input;
    if (bits == 0x3f800000u) return 0.0f;
    exponentOffset = -127;
  }
  bits += 0x004afb0du;
  const auto exponent = std::int32_t(bits >> 23) + exponentOffset;
  bits = (bits & 0x007fffffu) + 0x3f3504f3u;
  const auto reduced = _mm_add_ss(_mm_set_ss(std::bit_cast<float>(bits)),
                                scalar(image, 0x2bc4f4));
  const auto denominator = _mm_add_ss(scalar(image, 0x2bc4f8), reduced);
  const auto ratio = _mm_div_ss(reduced, denominator);
  const auto square = _mm_mul_ss(ratio, ratio);
  const auto fourth = _mm_mul_ss(square, square);
  auto polynomial = _mm_shuffle_ps(fourth, fourth, 0);
  polynomial = _mm_mul_ps(polynomial, lanes(image, 0x2bc500));
  polynomial = _mm_add_ps(polynomial, lanes(image, 0x2bc510));
  auto terms = _mm_movelh_ps(fourth, square);
  terms = _mm_shuffle_ps(terms, square, 0xe2);
  terms = _mm_mul_ps(terms, polynomial);
  auto sum = _mm_shuffle_ps(terms, terms, 0x55);
  sum = _mm_add_ss(sum, terms);
  auto halfSquare = _mm_mul_ss(scalar(image, 0x2bc520), reduced);
  halfSquare = _mm_mul_ss(halfSquare, reduced);
  sum = _mm_add_ss(sum, halfSquare);
  sum = _mm_mul_ss(sum, ratio);
  const auto exponentFloat = _mm_cvtsi32_ss(_mm_setzero_ps(), exponent);
  auto correction = _mm_mul_ss(scalar(image, 0x2bc524), exponentFloat);
  correction = _mm_add_ss(correction, sum);
  correction = _mm_sub_ss(correction, halfSquare);
  correction = _mm_add_ss(correction, reduced);
  auto result = _mm_mul_ss(exponentFloat, scalar(image, 0x2bc528));
  return _mm_cvtss_f32(_mm_add_ss(result, correction));
}
