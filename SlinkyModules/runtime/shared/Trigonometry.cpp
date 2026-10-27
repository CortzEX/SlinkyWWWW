#include "Trigonometry.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>
#include <intrin.h>
namespace {
template<class T> T read(const std::uint8_t *image,std::uint32_t rva) {
    T value;std::memcpy(&value,image+rva,sizeof value);return value;
}
__m128d d(const std::uint8_t *image,std::uint32_t rva) { return _mm_load_sd(reinterpret_cast<const double *>(image+rva)); }
__m128 f(const std::uint8_t *image,std::uint32_t rva) { return _mm_load_ss(reinterpret_cast<const float *>(image+rva)); }
float narrow(__m128d value) {return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),value));}
__m128d widen(float value) {return _mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(value));}
float change_sign(float value,const std::uint8_t *image,std::uint32_t rva) {
    return _mm_cvtss_f32(_mm_xor_ps(_mm_set_ss(value),_mm_loadu_ps(reinterpret_cast<const float *>(image+rva))));
}
// Native paired polynomial lanes are retained. Low/high lanes correspond to
// the two independently evaluated sine terms and are added in native order.
float sine_kernel(__m128d x,const std::uint8_t *image,std::uint32_t coefficients,
    std::uint32_t sign,bool negative) {
    const auto z=_mm_mul_sd(x,x);
    const auto squared=_mm_mul_sd(z,z);
    const auto signedX=negative?_mm_xor_pd(_mm_loadu_pd(reinterpret_cast<const double *>(image+sign)),x):x;
    const auto cube=negative?_mm_mul_sd(signedX,z):_mm_mul_sd(z,x);
    auto pair=_mm_mul_pd(_mm_unpacklo_pd(z,z),_mm_loadu_pd(reinterpret_cast<const double *>(image+coefficients)));
    pair=_mm_add_pd(pair,_mm_loadu_pd(reinterpret_cast<const double *>(image+coefficients+16)));
    auto terms=_mm_unpacklo_pd(_mm_mul_sd(squared,cube),cube);
    terms=_mm_mul_pd(terms,pair);
    auto high=_mm_unpackhi_pd(terms,terms);
    high=negative?_mm_sub_sd(high,x):_mm_add_sd(high,x);
    return narrow(_mm_add_sd(high,terms));
}
float cosine_kernel(__m128d x,const std::uint8_t *image,std::uint32_t coefficients,
    std::uint32_t sign,bool negative) {
    const auto z=_mm_mul_sd(x,x);
    const auto fourth=_mm_mul_sd(z,z);
    auto first=_mm_mul_sd(d(image,coefficients),z);
    first=_mm_add_sd(first,d(image,coefficients+8));
    auto second=_mm_mul_sd(d(image,coefficients+16),z);
    second=_mm_add_sd(second,d(image,coefficients+24));
    const auto sixth=_mm_mul_sd(z,fourth);
    auto fourthTerm=_mm_mul_sd(fourth,d(image,coefficients+32));
    fourthTerm=_mm_add_sd(fourthTerm,second);
    const auto sixthTerm=_mm_mul_sd(sixth,first);
    const float value=narrow(_mm_add_sd(sixthTerm,fourthTerm));
    return negative?change_sign(value,image,sign):value;
}
}
// 0xAF1B0: ordinary float pi/2 reduction, including the rounding-to-integer
// additions and optional one-quadrant correction before the large reducer.
std::int32_t recovered_reduce_float_af1b0(float input,double *output,const std::uint8_t *image) {
    const auto bits=std::bit_cast<std::uint32_t>(input),absolute=bits&0x7fffffffu;
    if(absolute<=0x4dc90fdau) {
        auto x=widen(input);
        auto multiple=_mm_mul_sd(d(image,0x2bb6c0),x);
        multiple=_mm_add_sd(multiple,d(image,0x2bb6c8));
        multiple=_mm_add_sd(multiple,d(image,0x2bb6d0));
        auto quadrant=_mm_cvttsd_si32(multiple);
        auto first=_mm_mul_sd(d(image,0x2bb6d8),multiple);
        first=_mm_add_sd(first,x);
        auto remainder=_mm_mul_sd(d(image,0x2bb6e0),multiple);
        remainder=_mm_add_sd(remainder,first);
        _mm_store_sd(output,remainder);
        _ReadWriteBarrier();
        if(_mm_cvtsd_f64(d(image,0x2bb6e8))>_mm_cvtsd_f64(remainder)) {
            multiple=_mm_add_sd(multiple,d(image,0x2bb700));
            quadrant=std::bit_cast<std::int32_t>(std::bit_cast<std::uint32_t>(quadrant)-1);
        } else if(!(_mm_cvtsd_f64(remainder)>_mm_cvtsd_f64(d(image,0x2bb6f0)))) return quadrant;
        else {
            multiple=_mm_add_sd(multiple,d(image,0x2bb6f8));
            quadrant=std::bit_cast<std::int32_t>(std::bit_cast<std::uint32_t>(quadrant)+1);
        }
        auto correction=_mm_mul_sd(d(image,0x2bb6d8),multiple);
        x=_mm_add_sd(x,correction);
        multiple=_mm_mul_sd(multiple,d(image,0x2bb6e0));
        _mm_store_sd(output,_mm_add_sd(multiple,x));
        return quadrant;
    }
    if(absolute>0x7f7fffffu) {
        const auto nan=_mm_sub_ss(_mm_set_ss(input),_mm_set_ss(input));
        _mm_store_sd(output,_mm_cvtss_sd(_mm_setzero_pd(),nan));
        return 0;
    }
    const auto exponent=static_cast<std::int32_t>(absolute>>23)-0x96;
    const auto scaledBits=absolute-(static_cast<std::uint32_t>(exponent)<<23);
    const double scaled=static_cast<double>(std::bit_cast<float>(scaledBits));
    double reduced;
    auto quadrant=recovered_reduce_large_ad400(&scaled,&reduced,exponent,1,0,image);
    if(bits&0x80000000u) {
        const auto signedRemainder=_mm_xor_ps(_mm_castpd_ps(_mm_set_sd(reduced)),_mm_loadu_ps(reinterpret_cast<const float *>(image+0x2bb6b0)));
        _mm_storel_pi(reinterpret_cast<__m64 *>(output),signedRemainder);
        quadrant=std::bit_cast<std::int32_t>(0u-std::bit_cast<std::uint32_t>(quadrant));
    } else _mm_store_sd(output,_mm_set_sd(reduced));
    return quadrant;
}
// 0xB1CF0: piecewise float sine. The native thresholds and polynomial choices
// are based on raw absolute bits, including its tiny-input evaluation stores.
float recovered_sine_b1cf0(float input,const std::uint8_t *image) {
    const auto bits=std::bit_cast<std::uint32_t>(input),absolute=bits&0x7fffffffu;
    const bool negative=(bits&0x80000000u)!=0;
    auto x=widen(input);
    if(absolute<=0x3f490fdau) {
        if(absolute<0x39800000u) {
            volatile float evaluated=absolute<0x00800000u?
                _mm_cvtss_f32(_mm_mul_ss(f(image,0x2bc014),_mm_set_ss(input))):
                _mm_cvtss_f32(_mm_add_ss(f(image,0x2bc010),_mm_set_ss(input)));
            (void)evaluated;return input;
        }
        return sine_kernel(x,image,0x2bbfb0,0x2bbfa0,false);
    }
    if(absolute<0x407b53d2u) {
        if(absolute>=0x4016cbe4u) {
            x=_mm_add_sd(x,d(image,negative?0x2bbff0:0x2bbff8));
            return sine_kernel(x,image,0x2bbfb0,0x2bbfa0,true);
        }
        x=_mm_add_sd(x,d(image,negative?0x2bc000:0x2bc008));
        return cosine_kernel(x,image,0x2bbf60,0x2bbf90,negative);
    }
    if(absolute<0x40e231d6u) {
        if(absolute>=0x40afede0u) {
            x=_mm_add_sd(x,d(image,negative?0x2bbfd0:0x2bbfd8));
            return sine_kernel(x,image,0x2bbfb0,0x2bbfa0,false);
        }
        x=_mm_add_sd(x,d(image,negative?0x2bbfe0:0x2bbfe8));
        return cosine_kernel(x,image,0x2bbf60,0x2bbf90,!negative);
    }
    if(absolute>0x7f7fffffu)return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(input),_mm_set_ss(input)));
    double remainder;const auto quadrant=recovered_reduce_float_af1b0(input,&remainder,image)&3;
    x=_mm_set_sd(remainder);
    if(quadrant==0)return sine_kernel(x,image,0x2bbfb0,0x2bbfa0,false);
    if(quadrant==1)return cosine_kernel(x,image,0x2bbf60,0x2bbf90,false);
    if(quadrant==2)return sine_kernel(x,image,0x2bbfb0,0x2bbfa0,true);
    return cosine_kernel(x,image,0x2bbf60,0x2bbf90,true);
}
// 0xB3590: float cosine has its own threshold inclusions and sine-path
// subtraction order rather than reusing sine(x+pi/2).
float recovered_cosine_b3590(float input,const std::uint8_t *image) {
    const auto bits=std::bit_cast<std::uint32_t>(input),absolute=bits&0x7fffffffu;
    const bool negative=(bits&0x80000000u)!=0;
    auto x=widen(input);
    if(absolute<=0x3f490fdau) {
        if(absolute<0x39800000u) {
            volatile float evaluated=_mm_cvtss_f32(_mm_add_ss(_mm_set_ss(input),f(image,0x2bcb40)));
            (void)evaluated;return read<float>(image,0x2bcb44);
        }
        return cosine_kernel(x,image,0x2bcac0,0x2bcaf0,false);
    }
    if(absolute<0x407b53d2u) {
        if(absolute>0x4016cbe3u) {
            x=_mm_add_sd(x,d(image,negative?0x2bcb30:0x2bcb38));
            return cosine_kernel(x,image,0x2bcac0,0x2bcaf0,true);
        }
        x=negative?_mm_add_sd(x,d(image,0x2bcb28)):_mm_sub_sd(d(image,0x2bcb28),x);
        return sine_kernel(x,image,0x2bcaa0,0x2bcb00,false);
    }
    if(absolute<0x40e231d6u) {
        if(absolute>0x40afeddfu) {
            x=_mm_add_sd(x,d(image,negative?0x2bcb18:0x2bcb20));
            return cosine_kernel(x,image,0x2bcac0,0x2bcaf0,false);
        }
        x=negative?_mm_sub_sd(d(image,0x2bcb10),x):_mm_add_sd(x,d(image,0x2bcb10));
        return sine_kernel(x,image,0x2bcaa0,0x2bcb00,false);
    }
    if(absolute>0x7f7fffffu)return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(input),_mm_set_ss(input)));
    double remainder;const auto quadrant=recovered_reduce_float_af1b0(input,&remainder,image)&3;
    x=_mm_set_sd(remainder);
    if(quadrant==0)return cosine_kernel(x,image,0x2bcac0,0x2bcaf0,false);
    if(quadrant==1)return sine_kernel(x,image,0x2bcaa0,0x2bcb00,true);
    if(quadrant==2)return cosine_kernel(x,image,0x2bcac0,0x2bcaf0,true);
    return sine_kernel(x,image,0x2bcaa0,0x2bcb00,false);
}
