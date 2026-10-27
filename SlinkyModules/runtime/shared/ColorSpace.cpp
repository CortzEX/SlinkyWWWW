// Reconstruction of captured ordinary instructions from the identified build.
// Semantic identifiers are assigned; original names and helper boundaries are
// not established. Constant-image bytes are evidence, not startup defaults.
#include "ColorSpace.hpp"
#include "../native/verified/module_float_math.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>

namespace {
float constant(const std::uint8_t *image,std::size_t rva) { float v;std::memcpy(&v,image+rva,4);return v; }
float add(float a,float b) { return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b))); }
float subtract(float a,float b) { return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b))); }
float multiply(float a,float b) { return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b))); }
float clamp(float v,float one) {
    const auto value=_mm_set_ss(v);
    const auto bounded=_mm_min_ss(_mm_set_ss(one),value);
    const auto below=_mm_cmplt_ss(value,_mm_setzero_ps());
    return _mm_cvtss_f32(_mm_andnot_ps(below,bounded));
}
float wrapOnce(float value,float one,float negativeOne) {
    const auto v=_mm_set_ss(value),o=_mm_set_ss(one);
    const auto below=_mm_cmplt_ss(v,_mm_setzero_ps());
    const auto positive=_mm_or_ps(_mm_and_ps(below,_mm_add_ss(v,o)),_mm_andnot_ps(below,v));
    const auto above=_mm_cmplt_ss(o,positive);
    return _mm_cvtss_f32(_mm_or_ps(_mm_and_ps(above,_mm_add_ss(positive,_mm_set_ss(negativeOne))),_mm_andnot_ps(above,positive)));
}
float channel(float hue,float high,float low,float half,const std::uint8_t *image) {
    const auto sixth=constant(image,0x2b51a8),twoThirds=constant(image,0x2b51ac),six=constant(image,0x2b51b0);
    // JBE skips the first and third branches on unordered input; JA skips the
    // middle branch on unordered input. The native fallthrough returns low.
    if(sixth>hue) return add(multiply(multiply(subtract(high,low),hue),six),low);
    if(half>hue) return high;
    if(twoThirds>hue) return add(multiply(multiply(subtract(twoThirds,hue),subtract(high,low)),six),low);
    return low;
}
}
float *recovered_hsl_74220(float *out,float hue,float saturation,float lightness,const std::uint8_t *image) {
    return recovered_hsla_74250(out,hue,saturation,lightness,0xff,image);
}
float *recovered_hsla_74250(float *out,float hue,float saturation,float lightness,
    std::uint8_t alpha,const std::uint8_t *image) {
    const auto one=constant(image,0x2b5198);
    hue=std::bit_cast<float>(recovered_remainder_b2300(std::bit_cast<std::uint32_t>(hue),std::bit_cast<std::uint32_t>(one)));
    // This first wrap has only the negative-hue correction.
    const auto h=_mm_set_ss(hue),negative=_mm_cmplt_ss(h,_mm_setzero_ps());
    hue=_mm_cvtss_f32(_mm_or_ps(_mm_and_ps(negative,_mm_add_ss(h,_mm_set_ss(one))),_mm_andnot_ps(negative,h)));
    saturation=clamp(saturation,one);lightness=clamp(lightness,one);
    const auto half=constant(image,0x2b519c);
    float high;
    if(half>=lightness) high=multiply(add(saturation,constant(image,0x2b5198)),lightness);
    else {
        const auto product=multiply(lightness,saturation);
        high=subtract(add(saturation,lightness),product);
    }
    const auto low=subtract(add(lightness,lightness),high);
    const auto negativeOne=constant(image,0x2b51a4);
    const auto redHue=wrapOnce(add(constant(image,0x2b51a0),hue),one,negativeOne);
    out[0]=clamp(channel(redHue,high,low,half,image),one);
    const auto greenHue=wrapOnce(hue,one,negativeOne);
    out[1]=clamp(channel(greenHue,high,low,half,image),one);
    const auto blueHue=wrapOnce(add(hue,constant(image,0x2b51b4)),one,negativeOne);
    out[2]=clamp(channel(blueHue,high,low,half,image),one);
    out[3]=_mm_cvtss_f32(_mm_div_ss(_mm_cvtsi32_ss(_mm_setzero_ps(),alpha),_mm_set_ss(constant(image,0x2b51b8))));
    return out;
}
float recovered_floor_b2a70(float value,const std::uint8_t *image) {
    const auto bits=std::bit_cast<std::uint32_t>(value);
    const auto exponent=(bits>>23)&0xffu;
    if(exponent>=150) return value;
    if(exponent>=127) {
        const auto shift=(22u-exponent)&31u;
        const auto keep=0xffffffffu<<shift,discard=~keep;
        if(!(bits&discard)) return value;
        volatile float raised=add(value,constant(image,0x2bc6b0));(void)raised;
        return std::bit_cast<float>((bits+((0u-(bits>>31))&discard))&keep);
    }
    volatile float raised=add(constant(image,0x2bc6b0),value);(void)raised;
    if(!(bits>>31)) return 0.0f;
    const auto input=_mm_set_ss(value),zero=_mm_setzero_ps(),equal=_mm_cmpeq_ss(zero,input);
    return _mm_cvtss_f32(_mm_or_ps(_mm_and_ps(input,equal),_mm_andnot_ps(equal,_mm_set_ss(constant(image,0x2bc6b4)))));
}
