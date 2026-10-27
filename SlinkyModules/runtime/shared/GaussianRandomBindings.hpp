#ifndef SLINKY_SHARE_1AC9D9D2BCC6FC72C3A1
#define SLINKY_SHARE_1AC9D9D2BCC6FC72C3A1
#include "../native/verified/module_float_distance.hpp"
#include "../native/verified/module_random_policy.hpp"
#include "Logarithm.hpp"
#include "SquareRoot.hpp"
#include <bit>

namespace reconstruction::gaussian_binding {
// Borrowed for one synchronous AB00 call. No module state is stored here.
struct Context {
  const std::uint8_t *image;
  const FloatDistanceConstants &distanceConstants;
};
inline float pair_ab7c0(void *user, float first, float second) {
  const auto &context = *static_cast<Context *>(user);
  return std::bit_cast<float>(recovered_float_distance(
      std::bit_cast<std::uint32_t>(first), std::bit_cast<std::uint32_t>(second),
      &context.distanceConstants));
}
inline float radial_b2050(void *user, float value) {
  return recovered_logarithm_b2050(value, static_cast<Context *>(user)->image);
}
inline float negativeSqrt_af4a0(void *user, float value) {
  return recovered_square_root_af4a0(value, static_cast<Context *>(user)->image);
}
inline GaussianRandomEndpoints endpoints(Context &context) {
  return {&context, pair_ab7c0, radial_b2050, negativeSqrt_af4a0};
}
}
#endif // SLINKY_SHARE_1AC9D9D2BCC6FC72C3A1
