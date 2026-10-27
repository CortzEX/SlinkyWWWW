#pragma once
#include <cstdint>

struct FloatCeilingConstants {
    std::uint32_t addition_bias, negative_zero, one;
};
static_assert(sizeof(FloatCeilingConstants) == 12);

extern "C" __declspec(dllexport) std::uint32_t recovered_float_ceiling_bits(
    std::uint32_t bits, const FloatCeilingConstants *);
