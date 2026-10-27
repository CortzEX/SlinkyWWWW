#include "Exponential.hpp"
#include <algorithm>
#include <bit>
#include <cstring>
#include <emmintrin.h>
namespace {
float read(const std::uint8_t*p,std::uint32_t rva){float v;std::memcpy(&v,p+rva,4);return v;}
float add(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float sub(float a,float b){return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float mul(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float div(float a,float b){return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a),_mm_set_ss(b)));}
void compareException(float x){volatile auto comparison=_mm_ucomieq_ss(_mm_set_ss(x),_mm_set_ss(x));(void)comparison;}
}
float recovered_scale_float_b2cb0(float value,std::int32_t power,const std::uint8_t *image){
    compareException(value);
    const auto bits=std::bit_cast<std::uint32_t>(value),magnitude=bits&0x7fffffff;
    if(magnitude>=0x7f800000)return value;
    const auto sign=bits&0x80000000,doubled=bits<<1;
    auto exponent=std::int32_t(doubled>>24);
    if(doubled<0x1000000){
        const auto highest=doubled?31-std::countl_zero(doubled):63;
        exponent=std::bit_cast<std::int32_t>((std::uint32_t(highest)^0xffffffe0u)+9u);
    }
    if(power>=0){
        if(power>254-exponent)return std::bit_cast<float>(sign|std::bit_cast<std::uint32_t>(read(image,0x2bc8a0)));
    }else if(power<=-exponent){
        if(power<-23-exponent)return std::bit_cast<float>(sign);
        const auto shift=(std::min(-power,1-(power+exponent))-1)&31;
        const auto trailing=std::countr_zero(bits);
        const auto tie=std::uint32_t(trailing==shift);
        const auto significand=(bits&0x7fffff)|(exponent>0?0x800000:0);
        const auto rounded=((significand>>shift)+1)>>1;
        return std::bit_cast<float>(sign|(rounded&~tie&0x7fffff));
    }
    const auto nextExponent=power+exponent;
    if(nextExponent<=0)return std::bit_cast<float>((bits<<(std::uint32_t(power)&31))|sign);
    if(exponent>0)return std::bit_cast<float>(bits+(std::uint32_t(power)<<23));
    const auto fraction=(bits<<((1-exponent)&31))&0x7fffff;
    return std::bit_cast<float>((std::uint32_t(nextExponent)<<23)|fraction|sign);
}
float recovered_exponential_b2b40(float input,const std::uint8_t *image){
    compareException(input);
    const auto bits=std::bit_cast<std::uint32_t>(input),magnitude=bits&0x7fffffff,negative=bits>>31;
    if(magnitude>0x7f800000)return input;
    if(magnitude>0x42aeac4f){
        if(!negative && magnitude>=0x42b17218)return mul(input,read(image,0x2bc850));
        if(negative){volatile auto evaluated=div(read(image,0x2bc858),input);(void)evaluated;if(magnitude>0x42cff1b4)return 0;}
    }
    std::int32_t power=0;float high=input,low=0,reduced=input;
    if(magnitude>0x3eb17218){
        if(magnitude<=0x3f851592)power=negative?-1:1;
        else power=_mm_cvttss_si32(_mm_set_ss(add(mul(read(image,0x2bc85c),input),read(image,0x2be040+negative*4))));
        const auto converted=_mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),power));
        high=add(input,mul(read(image,0x2bc860),converted));
        low=mul(converted,read(image,0x2bc864));reduced=sub(high,low);
    }else if(magnitude<=0x39000000){
        volatile auto evaluated=add(read(image,0x2bc850),input);(void)evaluated;
        return add(input,read(image,0x2bc854));
    }
    const auto square=mul(reduced,reduced);
    auto correction=mul(read(image,0x2bc868),square);correction=add(correction,read(image,0x2bc86c));correction=mul(correction,square);
    const auto denominatorCorrection=sub(reduced,correction);
    auto result=mul(reduced,denominatorCorrection);
    result=div(result,sub(read(image,0x2bc870),denominatorCorrection));result=sub(result,low);result=add(result,high);result=add(result,read(image,0x2bc854));
    return power?recovered_scale_float_b2cb0(result,power,image):result;
}
