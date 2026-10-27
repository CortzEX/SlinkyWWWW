#include "DisplayGeometry.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>
#include <intrin.h>
// Captured A070 and74150 perform ascending scalar stores.
float *recovered_rect_a070(float *out,float x,float y,float width,float height) {
    out[0]=x; _ReadWriteBarrier(); out[1]=y; _ReadWriteBarrier();
    out[2]=width; _ReadWriteBarrier(); out[3]=height; return out;
}
// A280 squares first, then evaluates (image_constant-(value+value))*square.
float recovered_smooth_a280(float value,const std::uint8_t *image) {
    float constant; std::memcpy(&constant,image+0x13e8d4,4);
    const auto x=_mm_set_ss(value);
    const auto square=_mm_mul_ss(x,x);
    return _mm_cvtss_f32(_mm_mul_ss(_mm_sub_ss(_mm_set_ss(constant),_mm_add_ss(x,x)),square));
}
std::uint32_t *recovered_color_74130(std::uint32_t *out,std::uint32_t red,std::uint32_t green,std::uint32_t blue) {
    out[0]=red; _ReadWriteBarrier(); out[1]=green; _ReadWriteBarrier();
    out[2]=blue; _ReadWriteBarrier(); out[3]=0x3f800000; return out;
}
float *recovered_color_74150(float *out,float red,float green,float blue,float alpha) {
    return recovered_rect_a070(out,red,green,blue,alpha);
}
//741B0 updates the source alpha BEFORE loading its complete128-bit record.
float *recovered_color_741b0(float *out,float *source,float alpha) {
    source[3]=alpha; _ReadWriteBarrier();
    _mm_storeu_ps(out,_mm_loadu_ps(source)); return out;
}
std::uint64_t recovered_angle_pack_9dc0(float first,float second) {
    return std::bit_cast<std::uint32_t>(first)|(std::uint64_t(std::bit_cast<std::uint32_t>(second))<<32);
}
std::uint32_t recovered_chunk_coordinate_a2f0(std::uint32_t value) {
    return (value>>4)|((0u-(value>>31))&0xf0000000u);
}
std::uint32_t recovered_block_coordinate_a300(std::uint32_t value) { return value<<4; }

float *recovered_rectangle_inset_a130(float *out,const float *rectangle,float inset) {
    const auto first=_mm_castsi128_ps(_mm_loadl_epi64(reinterpret_cast<const __m128i *>(rectangle)));
    const auto amount=_mm_set_ss(inset);const auto pair=_mm_unpacklo_ps(amount,amount);
    _mm_storel_pi(reinterpret_cast<__m64 *>(out),_mm_add_ps(pair,first));
    _ReadWriteBarrier();
    const auto size=_mm_castsi128_ps(_mm_loadl_epi64(reinterpret_cast<const __m128i *>(rectangle+2)));
    const auto doubled=_mm_add_ss(amount,amount);
    _mm_storel_pi(reinterpret_cast<__m64 *>(out+2),_mm_sub_ps(size,_mm_unpacklo_ps(doubled,doubled)));return out;
}
float recovered_limited_lerp_a260(float first,float second,float fraction,const std::uint8_t *image){
    float upper;std::memcpy(&upper,image+0x13e8d0,4);
    const auto amount=_mm_min_ss(_mm_set_ss(upper),_mm_set_ss(fraction));
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(first),_mm_mul_ss(amount,_mm_sub_ss(_mm_set_ss(second),_mm_set_ss(first)))));
}
float *recovered_color_blend_741d0(float *out,const float *first,const float *second,float fraction,const std::uint8_t *image){
    float one;std::memcpy(&one,image+0x2b5194,4);
    const auto input=_mm_set_ss(fraction);
    const auto amount=_mm_andnot_ps(_mm_cmplt_ss(input,_mm_setzero_ps()),_mm_min_ss(_mm_set_ss(one),input));
    const auto complement=_mm_sub_ss(_mm_set_ss(one),amount);
    const auto left=_mm_loadu_ps(first),right=_mm_loadu_ps(second);
    const auto rightTerm=_mm_mul_ps(_mm_shuffle_ps(amount,amount,0),right);
    const auto leftTerm=_mm_mul_ps(_mm_shuffle_ps(complement,complement,0),left);
    _mm_storeu_ps(out,_mm_add_ps(leftTerm,rightTerm));return out;
}
std::uint8_t recovered_rectangle_contains_a0a0(const float *rectangle,std::uint64_t point){
    const auto x=std::bit_cast<float>(std::uint32_t(point));
    if(!(x>=rectangle[0]))return 0;
    const auto y=std::bit_cast<float>(std::uint32_t(point>>32));
    if(!(y>=rectangle[1]))return 0;
    const auto upperX=_mm_cvtss_f32(_mm_add_ss(_mm_set_ss(rectangle[0]),_mm_set_ss(rectangle[2])));
    if(!(upperX>x))return 0;
    const auto upperY=_mm_cvtss_f32(_mm_add_ss(_mm_set_ss(rectangle[1]),_mm_set_ss(rectangle[3])));
    return upperY>y;
}
