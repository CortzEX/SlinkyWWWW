// Source-equivalent reconstruction from the supplied native recovery evidence.
// Assigned semantic names do not recover original source spelling. Native
// operation order and thresholds come from the captured instruction listings
// reports/native/double_reduction_aec00.asm and double_sine_b1990.asm.
#include "DoubleTrigonometry.hpp"
#include "Trigonometry.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>

namespace {
template<class T> T read(const std::uint8_t* image, unsigned rva) {
    T value; std::memcpy(&value, image+rva, sizeof value); return value;
}
double add(double a, double b) { return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(a), _mm_set_sd(b))); }
double sub(double a, double b) { return _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(a), _mm_set_sd(b))); }
double mul(double a, double b) { return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(a), _mm_set_sd(b))); }
unsigned exponent(double value) { return unsigned((std::bit_cast<std::uint64_t>(value)>>52)&0x7ff); }
std::int32_t truncate(double value) { return _mm_cvttsd_si32(_mm_set_sd(value)); }
double negate(double value, const std::uint8_t* image, unsigned rva) {
    return std::bit_cast<double>(std::bit_cast<std::uint64_t>(value)^read<std::uint64_t>(image,rva));
}
__m128d scalar(double value) { return _mm_set_sd(value); }
__m128d pair(const std::uint8_t* image, unsigned rva) {
    __m128d value; std::memcpy(&value,image+rva,sizeof value); return value;
}
double low(__m128d value) { return _mm_cvtsd_f64(value); }
double directReduction(double value, double* output, const std::uint8_t* image,
    unsigned head, unsigned tail) {
    const double first=add(value,read<double>(image,head));
    const double correction=read<double>(image,tail);
    output[0]=add(first,correction);
    output[1]=add(sub(first,output[0]),correction);
    return output[0];
}
}

// 0xAEC00. Two-term pi/2 reduction. Native callers normally bypass this entry
// for |x| <= pi/4, but its direct-call behavior is retained for those inputs.
std::int32_t recovered_reduce_double_aec00(double value, double* output,
    const std::uint8_t* image) {
    const auto bits=std::bit_cast<std::uint64_t>(value);
    const unsigned high=unsigned(bits>>32)&0x7fffffffu;
    const bool negative=(bits>>63)!=0;
    bool nearbyCancellation=false;
    if (high<=0x400f6a7au) {
        if ((unsigned(bits>>32)&0xfffffu)!=0x921fbu) {
            if (high<=0x4002d97cu) {
                directReduction(value,output,image,negative?0x2bb6a0:0x2bb5e8,
                    negative?0x2bb5f0:0x2bb698);
                return negative?-1:1;
            }
            directReduction(value,output,image,negative?0x2bb688:0x2bb678,
                negative?0x2bb690:0x2bb680);
            return negative?-2:2;
        }
    } else if (high<0x401c463cu) {
        if (high<0x4015fdbdu) {
            if (high!=0x4012d97cu) {
                directReduction(value,output,image,negative?0x2bb668:0x2bb658,
                    negative?0x2bb670:0x2bb660);
                return negative?-3:3;
            }
        } else if (high!=0x401921fbu) {
            directReduction(value,output,image,negative?0x2bb648:0x2bb638,
                negative?0x2bb650:0x2bb640);
            return negative?-4:4;
        }
        nearbyCancellation=true;
    } else if (high>=0x413921fbu) {
        if (high>=0x7ff00000u) {
            const double invalid=sub(value,value);
            output[0]=invalid; output[1]=invalid;
            return 0;
        }
        const double normalized=std::bit_cast<double>((bits&0xfffffffffffffull)|0x4160000000000000ull);
        double chunks[3];
        chunks[0]=double(truncate(normalized));
        const double fraction=mul(sub(normalized,chunks[0]),read<double>(image,0x2bb5b0));
        chunks[1]=double(truncate(fraction));
        chunks[2]=mul(sub(fraction,chunks[1]),read<double>(image,0x2bb5b0));
        std::int32_t count=3;
        while (chunks[count-1]==0.0) --count;
        double residual[2];
        std::int32_t quadrant=recovered_reduce_large_ad400(chunks,residual,
            std::int32_t(high>>20)-1046,count,1,image);
        if (negative) {
            // Native XORPD applies independently to the two residual lanes.
            output[0]=negate(residual[0],image,0x2bb5c0);
            output[1]=negate(residual[1],image,0x2bb5c8);
            return std::bit_cast<std::int32_t>(0u-std::uint32_t(quadrant));
        }
        output[0]=residual[0]; output[1]=residual[1];
        return quadrant;
    }
    double multiple=mul(read<double>(image,0x2bb5d0),value);
    multiple=add(multiple,read<double>(image,0x2bb5d8));
    multiple=add(multiple,read<double>(image,0x2bb5e0));
    std::int32_t quadrant=truncate(multiple);
    double remainder=add(mul(read<double>(image,0x2bb5e8),multiple),value);
    double tail=mul(read<double>(image,0x2bb5f0),multiple);
    const double first=sub(remainder,tail);
    bool adjust=false;
    if (read<double>(image,0x2bb5f8)>first) {
        quadrant=std::bit_cast<std::int32_t>(std::uint32_t(quadrant)-1u);
        multiple=add(multiple,read<double>(image,0x2bb610));
        adjust=true;
    } else if (first>read<double>(image,0x2bb600)) {
        quadrant=std::bit_cast<std::int32_t>(std::uint32_t(quadrant)+1u);
        multiple=add(multiple,read<double>(image,0x2bb608));
        adjust=true;
    }
    if (adjust) {
        remainder=add(value,mul(read<double>(image,0x2bb5e8),multiple));
        tail=mul(read<double>(image,0x2bb5f0),multiple);
    }
    output[0]=sub(remainder,tail);
    const unsigned inputExponent=high>>20;
    const bool secondStage=nearbyCancellation ? exponent(output[0])<0x3f1u
        : std::int32_t(inputExponent)-std::int32_t(exponent(output[0]))>16;
    if (secondStage) {
        const double second=mul(read<double>(image,0x2bb618),multiple);
        const double reduced=sub(remainder,second);
        tail=sub(mul(read<double>(image,0x2bb620),multiple),sub(sub(remainder,reduced),second));
        output[0]=sub(reduced,tail);
        const bool thirdStage=nearbyCancellation ? ((std::bit_cast<std::uint64_t>(output[0])>>56)&0x7f)<=0x3cu
            : std::int32_t(inputExponent)-std::int32_t(exponent(output[0]))>=50;
        remainder=reduced;
        if (thirdStage) {
            const double third=mul(read<double>(image,0x2bb628),multiple);
            const double reducedThird=sub(remainder,third);
            tail=sub(mul(multiple,read<double>(image,0x2bb630)),sub(sub(remainder,reducedThird),third));
            remainder=reducedThird;
            output[0]=sub(remainder,tail);
        }
    }
    output[1]=sub(sub(remainder,output[0]),tail);
    return quadrant;
}

namespace {
double sineKernel(double value, double tail, const std::uint8_t* image) {
    const auto x=scalar(value), y=scalar(tail);
    const auto z=_mm_mul_sd(x,x);
    auto cube=_mm_mul_sd(z,z);
    auto polynomial=_mm_mul_sd(scalar(read<double>(image,0x2bbed0)),z);
    polynomial=_mm_add_sd(polynomial,scalar(read<double>(image,0x2bbed8)));
    const auto zz=_mm_unpacklo_pd(z,z);
    auto coefficients=_mm_unpacklo_pd(pair(image,0x2bbee0),polynomial);
    coefficients=_mm_mul_pd(coefficients,zz);
    coefficients=_mm_add_pd(coefficients,pair(image,0x2bbef0));
    cube=_mm_mul_sd(cube,z);
    cube=_mm_mul_sd(cube,coefficients);
    auto sum=_mm_unpackhi_pd(coefficients,coefficients);
    sum=_mm_add_sd(sum,cube);
    auto xz=_mm_mul_sd(x,z);
    auto correction=_mm_mul_sd(scalar(read<double>(image,0x2bbeb0)),y);
    sum=_mm_mul_sd(sum,xz);
    correction=_mm_sub_sd(correction,sum);
    correction=_mm_mul_sd(correction,z);
    correction=_mm_sub_sd(correction,y);
    xz=_mm_mul_sd(xz,scalar(read<double>(image,0x2bbf00)));
    xz=_mm_add_sd(xz,correction);
    return low(_mm_sub_sd(x,xz));
}
double cosineKernel(double value, double tail, const std::uint8_t* image) {
    auto x=scalar(value), z=_mm_mul_sd(x,x);
    auto fourth=_mm_mul_sd(z,z);
    const auto zz=_mm_unpacklo_pd(z,z);
    auto p=_mm_mul_pd(pair(image,0x2bbe70),zz);
    auto lower=_mm_add_pd(scalar(read<double>(image,0x2bbe80)),p);
    auto upper=_mm_sub_pd(pair(image,0x2bbe90),p);
    upper=_mm_move_sd(upper,lower);
    upper=_mm_mul_pd(upper,zz);
    upper=_mm_add_pd(upper,pair(image,0x2bbea0));
    fourth=_mm_mul_sd(fourth,fourth);
    auto products=_mm_mul_pd(_mm_unpacklo_pd(z,fourth),upper);
    auto polynomial=_mm_add_sd(_mm_unpackhi_pd(products,products),products);
    const auto halfZ=_mm_mul_sd(scalar(read<double>(image,0x2bbeb0)),z);
    const auto one=scalar(read<double>(image,0x2bbeb8));
    auto head=_mm_sub_sd(one,halfZ);
    auto correction=_mm_sub_sd(_mm_sub_sd(one,head),halfZ);
    polynomial=_mm_mul_sd(polynomial,z);
    x=_mm_mul_sd(x,scalar(tail));
    polynomial=_mm_sub_sd(polynomial,x);
    polynomial=_mm_add_sd(polynomial,correction);
    return low(_mm_add_sd(polynomial,head));
}
}

// 0xB1990. Distinct unreduced/reduced kernels preserve packed operand order.
double recovered_sine_b1990(double value,const std::uint8_t* image) {
    const unsigned high=unsigned(std::bit_cast<std::uint64_t>(value)>>32)&0x7fffffffu;
    if (high<=0x3fe921fbu) {
        if (high<0x3e500000u) {
            // Volatile stores keep native underflow/inexact-producing operations.
            if (high<0x100000u) { volatile double force=mul(read<double>(image,0x2bbf48),value); (void)force; }
            else { volatile double force=add(read<double>(image,0x2bbf40),value); (void)force; }
            return value;
        }
        const auto x=scalar(value), z=_mm_mul_sd(x,x);
        auto cube=_mm_mul_sd(_mm_mul_sd(z,z),z);
        auto polynomial=_mm_mul_pd(_mm_unpacklo_pd(z,z),pair(image,0x2bbf10));
        polynomial=_mm_add_pd(polynomial,pair(image,0x2bbf20));
        auto terms=_mm_mul_pd(_mm_unpacklo_pd(cube,z),polynomial);
        auto sum=_mm_add_sd(_mm_unpackhi_pd(terms,terms),scalar(read<double>(image,0x2bbf30)));
        sum=_mm_add_sd(sum,terms);
        const auto xz=_mm_mul_sd(x,z);
        sum=_mm_mul_sd(sum,z);
        sum=_mm_add_sd(sum,scalar(read<double>(image,0x2bbf38)));
        sum=_mm_mul_sd(sum,xz);
        return low(_mm_add_sd(x,sum));
    }
    if (high>0x7fefffffu) return sub(value,value);
    double residual[2];
    const unsigned quadrant=std::uint32_t(recovered_reduce_double_aec00(value,residual,image))&3u;
    // Captured jump table maps 0/2 to signed sine and 1/3 to signed cosine.
    if ((quadrant&1u)==0) {
        double result=sineKernel(residual[0],residual[1],image);
        return quadrant==2?negate(result,image,0x2bbec0):result;
    }
    double result=cosineKernel(residual[0],residual[1],image);
    return quadrant==3?negate(result,image,0x2bbec0):result;
}
