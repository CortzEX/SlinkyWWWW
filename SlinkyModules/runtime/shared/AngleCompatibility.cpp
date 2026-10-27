#include "AngleCompatibility.hpp"
#include "../native/verified/module_float_math.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>

namespace {
float readFloat(const std::uint8_t *source) {
    float value;
    std::memcpy(&value, source, sizeof value);
    return value;
}
float add(float first, float second) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(first), _mm_set_ss(second)));
}
}

// RVA A210. Use the unchanged, instruction-audited B2300 remainder body. Loads
// after that call stay on their original branches; no constants are guessed.
float recovered_angle_wrap_a210(float angle, std::uint8_t *constantImage,
    RecoveredAngleEndpoint endpoint) {
    (void)endpoint;
    const float period = readFloat(constantImage + 0x13E8C0);
    float value = std::bit_cast<float>(recovered_remainder_b2300(
        std::bit_cast<std::uint32_t>(angle), std::bit_cast<std::uint32_t>(period)));
    if (value >= readFloat(constantImage + 0x13E8C4)) {
        value = add(value, readFloat(constantImage + 0x13E8C8));
    } else if (readFloat(constantImage + 0x13E8CC) > value) {
        value = add(value, readFloat(constantImage + 0x13E8C0));
    }
    return value;
}
