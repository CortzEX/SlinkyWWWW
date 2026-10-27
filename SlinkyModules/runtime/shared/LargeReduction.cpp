// 0xAD400 uses the classical 24-bit-chunk reduction algorithm. Its table
// shapes and constants agree with the Sun fdlibm family; that library identity
// is an inference, not a recovered build/version string. Native instructions
// in reports/native/large_reduction_ad400.asm determine this port's operations.
// Algorithm reference: https://netlib.org/fdlibm/k_rem_pio2.c
// No upstream table or host libm behavior substitutes for the caller's image.
#include "Trigonometry.hpp"
#include <algorithm>
#include <bit>
#include <cstring>
#include <emmintrin.h>

namespace {
template<class T> T constant(const std::uint8_t *image, unsigned rva) {
    T value; std::memcpy(&value,image+rva,sizeof(value)); return value;
}
double add(double a,double b) { return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(a),_mm_set_sd(b))); }
double sub(double a,double b) { return _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(a),_mm_set_sd(b))); }
double mul(double a,double b) { return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(a),_mm_set_sd(b))); }
std::int32_t truncate(double value) {return _mm_cvttsd_si32(_mm_set_sd(value));}
double convert(std::int32_t value) {return _mm_cvtsd_f64(_mm_cvtsi32_sd(_mm_setzero_pd(),value));}
double negate(double value,const std::uint8_t *image) {
    return std::bit_cast<double>(std::bit_cast<std::uint64_t>(value)^constant<std::uint64_t>(image,0x2bb060));
}
}

// 0xAE570. Integer exponent adjustment and native nearest-even subnormal
// rounding. This routine never calls the host scalbn or changes the FP mode.
double recovered_scale_binary64_ae570(double value,std::int32_t amount,const std::uint8_t *image) {
    auto bits=std::bit_cast<std::uint64_t>(value);
    const auto stored_exponent=static_cast<std::uint32_t>((bits>>52)&0x7ff);
    if (stored_exponent==0x7ff) return value;
    const auto sign=bits&0x8000000000000000ull;
    const auto doubled=bits*2;
    const std::int32_t high=doubled?63-std::countl_zero(doubled):127;
    const auto effective=stored_exponent?static_cast<std::int32_t>(stored_exponent):(doubled?high-52:-53);
    if (amount>=0) {
        if (amount>0x7fe-effective) return std::bit_cast<double>(
            (bits&constant<std::uint64_t>(image,0x2bb080))|constant<std::uint64_t>(image,0x2bb090));
        const auto adjusted=static_cast<std::int32_t>(std::uint32_t(effective)+std::uint32_t(amount));
        if (adjusted<=0) return std::bit_cast<double>((bits<<(std::uint32_t(amount)&63))|sign);
        if (effective>0) return std::bit_cast<double>(bits+(std::uint64_t(std::uint32_t(amount))<<52));
        const auto fraction=(bits<<(std::uint32_t(1-effective)&63))&0xfffffffffffffull;
        return std::bit_cast<double>(fraction|(std::uint64_t(std::uint32_t(adjusted))<<52)|sign);
    }
    const auto positive=0u-std::uint32_t(amount);
    if (amount>-effective) return std::bit_cast<double>(bits-(std::uint64_t(positive)<<52));
    if (amount<-52-effective) return std::bit_cast<double>(sign);
    const auto sum=static_cast<std::int32_t>(std::uint32_t(amount)+std::uint32_t(effective));
    const auto shift=(std::min<std::uint32_t>(positive,std::uint32_t(1-sum))-1)&63;
    const auto tie=std::countr_zero(bits)==shift;
    const auto significand=(bits&0xfffffffffffffull)|(effective>0?0x10000000000000ull:0);
    auto rounded=((significand>>shift)+1)>>1;
    rounded&=~std::uint64_t(tie);
    return std::bit_cast<double>((bits&constant<std::uint64_t>(image,0x2bb080))|
        (rounded&constant<std::uint64_t>(image,0x2bb070)));
}

// 0xB29B0. Bias additions are retained even on the small-magnitude path.
double recovered_floor_binary64_b29b0(double value,const std::uint8_t *image) {
    const auto bits=std::bit_cast<std::uint64_t>(value);
    const auto exponent=(bits>>52)&0x7ff;
    if (exponent>=0x433 || value==0.0) return value;
    const auto positive=constant<double>(image,0x2bc698);
    const auto negative=constant<double>(image,0x2bc6a0);
    const auto minus_one=constant<double>(image,0x2bc6a8);
    const bool is_negative=(bits>>63)!=0;
    const auto correction=is_negative?sub(add(positive,add(negative,value)),value):
        sub(add(add(positive,value),negative),value);
    if (exponent<=0x3fe) {
        volatile double raised=correction;
        return is_negative?minus_one:0.0;
    }
    const auto integer=add(value,correction);
    return correction>0.0?add(integer,minus_one):integer;
}

// 0xAD400. Input comprises positive 24-bit limbs in binary64. Caller contract
// supplies enough valid limbs/table entries and precision 0..3, as native does.
// Float sine/cosine callers use one limb, precision zero, exponent at most 104.
std::int32_t recovered_reduce_large_ad400(const double *input,double *output,
    std::int32_t exponent,std::int32_t count,std::int32_t precision,const std::uint8_t *image) {
    const auto initial=constant<std::int32_t>(image,0x2bd428+4*precision);
    const auto last_input=count-1;
    const auto short_exponent=static_cast<std::int16_t>(std::uint16_t(exponent-3));
    const auto table_start=std::max(0,static_cast<int>(short_exponent)/24);
    auto chunk_exponent=exponent-24*(table_start+1);
    double table[20],products[20],weighted[20];
    std::int32_t chunks[20];
    const auto tiny=constant<double>(image,0x2bb020);
    const auto radix=constant<double>(image,0x2bb028);
    const auto negative_radix=constant<double>(image,0x2bb030);
    const auto one=constant<double>(image,0x2bb050);
    const auto half=constant<double>(image,0x2bb048);
    auto digit=[&](int index){return constant<std::int32_t>(image,0x2bd438+4*index);};
    for (int i=0;i<=last_input+initial;++i) {
        const auto index=table_start-last_input+i;
        table[i]=index<0?0.0:convert(digit(index));
    }
    auto convolution=[&](int index) {
        double sum=0.0;
        for(int j=0;j<=last_input;++j) sum=add(mul(input[j],table[last_input+index-j]),sum);
        return sum;
    };
    for(int i=0;i<=initial;++i) products[i]=convolution(i);
    int last=initial,quadrant=0,complement=0;
    double residual;
    for (;;) {
        residual=products[last];
        for(int i=0,j=last;j>0;++i,--j) {
            const auto carry=convert(truncate(mul(residual,tiny)));
            chunks[i]=truncate(add(mul(carry,negative_radix),residual));
            residual=add(products[j-1],carry);
        }
        residual=recovered_scale_binary64_ae570(residual,chunk_exponent,image);
        const auto cycles=recovered_floor_binary64_b29b0(mul(residual,constant<double>(image,0x2bb038)),image);
        residual=add(mul(cycles,constant<double>(image,0x2bb040)),residual);
        quadrant=truncate(residual);
        residual=sub(residual,convert(quadrant));
        complement=0;
        if(chunk_exponent>0) {
            const auto high=chunks[last-1]>>(24-chunk_exponent);
            quadrant+=high;
            chunks[last-1]-=high<<(24-chunk_exponent);
            complement=chunks[last-1]>>(23-chunk_exponent);
        } else if(chunk_exponent==0) complement=chunks[last-1]>>23;
        else if(!(residual<half)) complement=2;
        if(complement>0) {
            ++quadrant;
            bool carry=false;
            for(int i=0;i<last;++i) {
                const auto chunk=chunks[i];
                if(carry) chunks[i]=0xffffff-chunk;
                else if(chunk) {carry=true;chunks[i]=0x1000000-chunk;}
            }
            if(chunk_exponent==1) chunks[last-1]&=0x7fffff;
            else if(chunk_exponent==2) chunks[last-1]&=0x3fffff;
            if(complement==2) {
                residual=sub(one,residual);
                if(carry) residual=sub(residual,recovered_scale_binary64_ae570(one,chunk_exponent,image));
            }
        }
        if(residual!=0.0) break;
        int nonzero=0;
        for(int i=last-1;i>=initial;--i) nonzero|=chunks[i];
        if(nonzero) break;
        int additional=1;
        while(chunks[initial-additional]==0) ++additional;
        for(int i=last+1;i<=last+additional;++i) {
            table[last_input+i]=convert(digit(table_start+i));
            products[i]=convolution(i);
        }
        last+=additional;
    }
    if(residual==0.0) {
        --last;chunk_exponent-=24;
        while(chunks[last]==0) {--last;chunk_exponent-=24;}
    } else {
        residual=recovered_scale_binary64_ae570(residual,-chunk_exponent,image);
        if(!(residual<radix)) {
            const auto carry=convert(truncate(mul(residual,tiny)));
            chunks[last]=truncate(add(mul(carry,negative_radix),residual));
            ++last;chunk_exponent+=24;chunks[last]=truncate(carry);
        } else chunks[last]=truncate(residual);
    }
    double factor=recovered_scale_binary64_ae570(one,chunk_exponent,image);
    for(int i=last;i>=0;--i) {products[i]=mul(factor,convert(chunks[i]));factor=mul(factor,tiny);}
    for(int i=last;i>=0;--i) {
        double sum=0.0;
        for(int k=0;k<=initial && k<=last-i;++k) {
            const auto coefficient=constant<double>(image,0x2bdf00+8*k);
            sum=add(mul(coefficient,products[i+k]),sum);
        }
        weighted[last-i]=sum;
    }
    auto signed_value=[&](double value){return complement?negate(value,image):value;};
    if(precision<3) {
        double sum=0.0;
        for(int i=last;i>=0;--i) sum=add(sum,weighted[i]);
        output[0]=signed_value(sum);
        if(precision==1 || precision==2) {
            double tail=sub(weighted[0],sum);
            for(int i=1;i<=last;++i) tail=add(tail,weighted[i]);
            output[1]=signed_value(tail);
        }
    } else if(precision==3) {
        for(int pass=0;pass<2;++pass) for(int i=last;i>pass;--i) {
            const auto sum=add(weighted[i-1],weighted[i]);
            weighted[i]=add(weighted[i],sub(weighted[i-1],sum));weighted[i-1]=sum;
        }
        double tail=0.0;
        for(int i=last;i>=2;--i) tail=add(tail,weighted[i]);
        output[0]=signed_value(weighted[0]);output[1]=signed_value(weighted[1]);output[2]=signed_value(tail);
    }
    return quadrant&7;
}
