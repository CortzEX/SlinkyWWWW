#include "module_random.hpp"
#include <bit>
#include <emmintrin.h>

struct RandomStep { std::uint32_t sum, rotated; };

// The transition is inlined in both 0xa3e0 and 0xa460.
static RandomStep next(RandomState *state) {
    const auto a = state->words[0], b = state->words[1];
    const auto c = state->words[2], d = state->words[3];
    const auto rotated = std::rotl(b ^ d, 11);
    state->words[1] = c ^ a ^ b;
    state->words[0] = a ^ b ^ d;
    state->words[2] = c ^ a ^ (b << 9);
    state->words[3] = rotated;
    return {d + a, rotated};
}

static float sample(std::uint32_t sum, float scale, float width, float low) {
    auto value = _mm_cvtsi32_ss(_mm_setzero_ps(), static_cast<std::int32_t>(sum >> 8));
    value = _mm_mul_ss(value, _mm_set_ss(scale));
    value = _mm_mul_ss(value, _mm_set_ss(width));
    return _mm_cvtss_f32(_mm_add_ss(value, _mm_set_ss(low)));
}

// 0xa050 packs the raw low XMM0/XMM1 float bits.
extern "C" __declspec(dllexport) std::uint64_t recovered_random_bounds(float low, float high) {
    return std::bit_cast<std::uint32_t>(low) |
           (std::uint64_t{std::bit_cast<std::uint32_t>(high)} << 32);
}

// 0xa3e0 uses scalar single-precision arithmetic at every step.
extern "C" __declspec(dllexport) float recovered_random_interval(
    RandomState *state, const RandomConstants *constants, std::uint64_t bounds) {
    const auto low = std::bit_cast<float>(static_cast<std::uint32_t>(bounds));
    const auto high = std::bit_cast<float>(static_cast<std::uint32_t>(bounds >> 32));
    const auto width = _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(high), _mm_set_ss(low)));
    return sample(next(state).sum, constants->interval_scale, width, low);
}

// 0xa460 writes only AL after the state transition; retain the rest of EAX.
extern "C" __declspec(dllexport) std::uint32_t recovered_random_chance(
    RandomState *state, const RandomConstants *constants, float threshold) {
    const auto bounds = recovered_random_bounds(0.0f, constants->chance_upper);
    const auto low = std::bit_cast<float>(static_cast<std::uint32_t>(bounds));
    const auto high = std::bit_cast<float>(static_cast<std::uint32_t>(bounds >> 32));
    const auto width = _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(high), _mm_set_ss(low)));
    const auto step = next(state);
    const auto generated = sample(step.sum, constants->chance_scale, width, low);
    return (step.rotated & 0xffffff00u) | static_cast<std::uint32_t>(threshold > generated);
}
