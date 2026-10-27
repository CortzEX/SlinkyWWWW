#pragma once
#include "module_random.hpp"

struct SmoothRandomState { double timestamp; float left, right; };
struct GaussianRandomState { float cached; std::uint8_t valid, padding[3]; };
struct PolicyDrawConstants {
    float upper, scale;
    std::uint32_t difference_mask, padding;
    double minimum_difference;
};
struct RandomPolicyConstants {
    PolicyDrawConstants refresh, initialize;
    float gate_upper, gate_scale, gaussian_scale, gaussian_offset, gaussian_upper, radial_factor;
};
struct GaussianRandomEndpoints {
    void *user;
    float (*pair)(void *, float, float);
    float (*radial)(void *, float);
    float (*negative_sqrt)(void *, float);
};
static_assert(sizeof(SmoothRandomState) == 16);
static_assert(sizeof(GaussianRandomState) == 8);
static_assert(sizeof(PolicyDrawConstants) == 24);
static_assert(sizeof(RandomPolicyConstants) == 72);
static_assert(sizeof(GaussianRandomEndpoints) == 32);

extern "C" {
__declspec(dllexport) void recovered_policy_initialize(SmoothRandomState *, std::uint8_t first,
    RandomState *, const RandomPolicyConstants *);
__declspec(dllexport) std::uint32_t recovered_policy_smooth_bits(SmoothRandomState *, std::uint64_t bounds,
    double duration, RandomState *, const double *clock, const RandomPolicyConstants *);
__declspec(dllexport) std::uint8_t recovered_policy_gate(SmoothRandomState *, std::uint64_t bounds,
    double duration, RandomState *, const double *clock, const RandomPolicyConstants *);
__declspec(dllexport) std::uint32_t recovered_policy_gaussian_bits(GaussianRandomState *, RandomState *,
    const RandomPolicyConstants *, const GaussianRandomEndpoints *);
}
