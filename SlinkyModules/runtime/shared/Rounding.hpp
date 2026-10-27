#ifndef SLINKY_SHARE_4777893988F416AFECB2
#define SLINKY_SHARE_4777893988F416AFECB2
#include <bit>
#include <cstdint>
#include <cstring>
#include <emmintrin.h>
// Runtime observation: native 0xb1fb0..0xb2048. Image constants are borrowed.
// The input and result are single precision. SSE operations retain their order.
inline float recovered_round_float_b1fb0(float input,
                                         const std::uint8_t *image) {
  auto load = [&](std::size_t rva) {
    float v;
    std::memcpy(&v, image + rva, 4);
    return _mm_set_ss(v);
  };
  const auto bits = std::bit_cast<std::uint32_t>(input);
  const auto exponent = (bits >> 23) & 255u;
  __m128 original = _mm_set_ss(input);
  if (exponent >= 150u)
    return input;
  __m128 magnitude = _mm_and_ps(
      original, _mm_castsi128_ps(_mm_loadu_si128(
                    reinterpret_cast<const __m128i *>(image + 0x2bc180))));
  __m128 delta = _mm_add_ss(load(0x2bc190), magnitude);
  if (exponent <= 125u) {
    volatile float evaluated = _mm_cvtss_f32(delta);
    (void)evaluated;
    return _mm_cvtss_f32(_mm_mul_ss(original, _mm_setzero_ps()));
  }
  delta = _mm_add_ss(delta, load(0x2bc194));
  delta = _mm_sub_ss(delta, magnitude);
  if (_mm_cvtss_f32(delta) > _mm_cvtss_f32(load(0x2bc198))) {
    magnitude = _mm_add_ss(magnitude, delta);
    magnitude = _mm_add_ss(magnitude, load(0x2bc1a4));
  } else {
    const auto threshold = load(0x2bc19c);
    magnitude = _mm_add_ss(magnitude, delta);
    if (_mm_cvtss_f32(threshold) >= _mm_cvtss_f32(delta))
      magnitude = _mm_add_ss(magnitude, load(0x2bc1a0));
  }
  if (bits & 0x80000000u)
    magnitude = _mm_xor_ps(
        magnitude, _mm_castsi128_ps(_mm_loadu_si128(
                       reinterpret_cast<const __m128i *>(image + 0x2bc1b0))));
  return _mm_cvtss_f32(magnitude);
}

// Runtime 0xabeb0..0xabf00: truncate by masking, retaining the ADDSS exception.
inline float recovered_truncate_float_abeb0(float input,
                                            const std::uint8_t *image) {
  const auto bits = std::bit_cast<std::uint32_t>(input);
  const auto exponent = (bits >> 23) & 255u;
  if (exponent >= 150u)
    return input;
  const auto shift = exponent >= 127u ? std::uint8_t(exponent - 118u) : 1u;
  const auto mask = 0xffffffffu >> (shift & 31u);
  if (!(bits & mask))
    return input;
  float bias;
  std::memcpy(&bias, image + 0x2bada8, 4);
  volatile float evaluated =
      _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(input), _mm_set_ss(bias)));
  (void)evaluated;
  return std::bit_cast<float>(bits & ~mask);
}
#endif // SLINKY_SHARE_4777893988F416AFECB2
