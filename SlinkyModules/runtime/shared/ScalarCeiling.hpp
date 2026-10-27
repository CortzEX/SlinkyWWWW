#ifndef SLINKY_SHARE_D83E801E97A171D3ED63
#define SLINKY_SHARE_D83E801E97A171D3ED63
#include <bit>
#include <cstdint>
#include <cstring>
#include <emmintrin.h>

inline float recovered_ceiling_float_b2920(float value,const std::uint8_t *image) {
    const auto bits=std::bit_cast<std::uint32_t>(value),exponent=(bits>>23)&255;
    if(exponent>=150)return value;
    auto constant=[&](std::uint32_t at){float f;std::memcpy(&f,image+at,4);return f;};
    if(exponent>=127) {
        const auto mask=0xffffffffu<<((0x16-exponent)&31),fraction=~mask;
        if((bits&fraction)==0)return value;
        volatile float evaluated=_mm_cvtss_f32(_mm_add_ss(_mm_set_ss(value),_mm_set_ss(constant(0x2bc640))));
        (void)evaluated;
        return std::bit_cast<float>((bits+((bits&0x80000000u)?0u:fraction))&mask);
    }
    volatile float evaluated=_mm_cvtss_f32(_mm_add_ss(_mm_set_ss(constant(0x2bc640)),_mm_set_ss(value)));
    (void)evaluated;
    if(bits&0x80000000u)return constant(0x2bc644);
    return bits==0?value:constant(0x2bc648);
}
#endif // SLINKY_SHARE_D83E801E97A171D3ED63
