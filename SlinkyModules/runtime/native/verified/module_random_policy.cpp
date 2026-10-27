#include "module_random_policy.hpp"
#include <bit>
#include <emmintrin.h>

static float add(float first, float second) { return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(first), _mm_set_ss(second))); }
static float subtract(float first, float second) { return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(first), _mm_set_ss(second))); }
static float multiply(float first, float second) { return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(first), _mm_set_ss(second))); }
// sum >> 8 is a nonnegative 24-bit integer, exact in float. Identity arithmetic
// reuses the existing RNG transition without altering any returned bit.
static float random_integer(RandomState *state) {
    constexpr RandomConstants identity{1.0f, 0.0f, 0.0f};
    return recovered_random_interval(state, &identity, recovered_random_bounds(0.0f, 1.0f));
}
static float draw(RandomState *state, float upper, float scale) {
    const auto bounds = recovered_random_bounds(0.0f, upper);
    const auto low = std::bit_cast<float>(static_cast<std::uint32_t>(bounds));
    const auto high = std::bit_cast<float>(static_cast<std::uint32_t>(bounds >> 32));
    return add(multiply(multiply(random_integer(state), scale), subtract(high, low)), low);
}
static double difference(float first, float second, std::uint32_t mask) {
    return static_cast<double>(std::bit_cast<float>(std::bit_cast<std::uint32_t>(subtract(first, second)) & mask));
}
// 0xa6d0 regenerates both values on every retry when first is nonzero.
extern "C" __declspec(dllexport) void recovered_policy_initialize(SmoothRandomState *sampler,
    std::uint8_t first, RandomState *random, const RandomPolicyConstants *constants) {
    const auto threshold = constants->initialize.minimum_difference;
    const auto mask = constants->initialize.difference_mask;
    const auto upper = constants->initialize.upper, scale = constants->initialize.scale;
    do {
        if (first) sampler->left = draw(random, upper, scale);
        sampler->right = draw(random, upper, scale);
    } while (threshold > difference(sampler->left, sampler->right, mask));
}
// 0xa510 refreshes expired endpoints, then interpolates in binary64.
extern "C" __declspec(dllexport) std::uint32_t recovered_policy_smooth_bits(SmoothRandomState *sampler,
    std::uint64_t bounds, double duration, RandomState *random, const double *clock,
    const RandomPolicyConstants *constants) {
    const auto end = _mm_add_sd(_mm_set_sd(sampler->timestamp), _mm_set_sd(duration));
    const auto now = *clock;
    if (now > _mm_cvtsd_f64(end)) {
        sampler->timestamp = now;
        const auto left = sampler->left, right = sampler->right;
        if (left != 0.0f || right != 0.0f) {
            sampler->left = right;
            const auto mask = constants->refresh.difference_mask;
            const auto threshold = constants->refresh.minimum_difference;
            const auto upper = constants->refresh.upper, scale = constants->refresh.scale;
            do { sampler->right = draw(random, upper, scale); }
            while (threshold > difference(sampler->left, sampler->right, mask));
        } else recovered_policy_initialize(sampler, 1, random, constants);
    }
    const auto phase = _mm_div_sd(_mm_sub_sd(_mm_set_sd(*clock), _mm_set_sd(sampler->timestamp)), _mm_set_sd(duration));
    const auto curve = _mm_add_sd(_mm_mul_sd(_mm_set_sd(static_cast<double>(subtract(sampler->right, sampler->left))), phase),
        _mm_set_sd(static_cast<double>(sampler->left)));
    const auto low = std::bit_cast<float>(static_cast<std::uint32_t>(bounds));
    const auto high = std::bit_cast<float>(static_cast<std::uint32_t>(bounds >> 32));
    const auto result = _mm_add_sd(_mm_mul_sd(_mm_set_sd(static_cast<double>(subtract(high, low))), curve),
        _mm_set_sd(static_cast<double>(low)));
    return std::bit_cast<std::uint32_t>(_mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), result)));
}
// 0xaa30 consumes its independent comparison draw before advancing the smooth sampler.
extern "C" __declspec(dllexport) std::uint8_t recovered_policy_gate(SmoothRandomState *sampler,
    std::uint64_t bounds, double duration, RandomState *random, const double *clock,
    const RandomPolicyConstants *constants) {
    const auto comparison = draw(random, constants->gate_upper, constants->gate_scale);
    const auto value = std::bit_cast<float>(recovered_policy_smooth_bits(sampler, bounds, duration, random, clock, constants));
    return value > comparison;
}
// 0xab00 consumes raw cache validity, rejects pairs, then caches the second result.
extern "C" __declspec(dllexport) std::uint32_t recovered_policy_gaussian_bits(GaussianRandomState *cache,
    RandomState *random, const RandomPolicyConstants *constants, const GaussianRandomEndpoints *endpoints) {
    if (cache->valid) { cache->valid = 0; return std::bit_cast<std::uint32_t>(cache->cached); }
    const auto scale = constants->gaussian_scale, offset = constants->gaussian_offset, upper = constants->gaussian_upper;
    float x, y, gate;
    do {
        auto value = multiply(random_integer(random), scale); x = add(add(value, value), offset);
        value = multiply(random_integer(random), scale); y = add(add(value, value), offset);
        gate = endpoints->pair(endpoints->user, x, y);
    } while (gate >= upper || gate == 0.0f);
    const auto radial = endpoints->radial(endpoints->user, gate);
    const auto quotient = _mm_div_ss(_mm_set_ss(multiply(radial, constants->radial_factor)), _mm_set_ss(gate));
    const auto ratio = _mm_cvtss_f32(quotient);
    const auto factor = ratio < 0.0f || ratio != ratio ? endpoints->negative_sqrt(endpoints->user, ratio)
        : _mm_cvtss_f32(_mm_sqrt_ss(quotient));
    cache->cached = multiply(y, factor);
    cache->valid = 1;
    return std::bit_cast<std::uint32_t>(multiply(x, factor));
}
