#include <stdint.h>
#include <string.h>
#include <emmintrin.h>

typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t u64(const void *p) { uint64_t v;memcpy(&v,p,8);return v; }
static float f32(const void *p) { float v;memcpy(&v,p,4);return v; }
static double f64(const void *p) { double v;memcpy(&v,p,8);return v; }
static uint32_t fb(float f) { uint32_t v;memcpy(&v,&f,4);return v; }
static uint64_t db(double f) { uint64_t v;memcpy(&v,&f,8);return v; }
static float from_fb(uint32_t b) { return f32(&b); }
static double from_db(uint64_t b) { return f64(&b); }

/* RVA 0x42320, including the observed twenty-term recurrence and 0xa2d0. */
__declspec(dllexport) void recovered_fast_accel(uint8_t *event,uint8_t *image,dependency call) {
    if (f32(event+0x14)==0.0f && f32(event+0x10)==0.0f) return;
    uint8_t *game=(uint8_t *)(uintptr_t)u64(event+8);
    if (image[0x2f2a58]==1 && !(uint8_t)call(0x380b0,u64(game),u64(game+0x28),0,0)) return;
    if (image[0x2f2a78]==1) {
        uint32_t raw=(uint32_t)call(0x239f0,u64(game),u64(game+0x28),0,0);
        int32_t counter;memcpy(&counter,&raw,4);
        if (counter>0) return;
    }
    double motion[3];
    call(0x23550,(uintptr_t)motion,u64(game),u64(game+0x28),0);
    double speed=from_db(call(0x13cfd0,db(motion[0]),db(motion[2]),0,0));
    if (speed==0.0 || !(uint8_t)call(0x23780,u64(game),u64(game+0x28),0,0)) return;
    float sideways=f32(event+0x10),forward=f32(event+0x14),factor=f32(event+0x18);
    float length=from_fb((uint32_t)call(0xab7c0,fb(sideways),fb(forward),0,0));
    __m128 denominator=_mm_max_ss(_mm_set_ss(f32(image+0x154700)),_mm_set_ss(length));
    __m128 scale=_mm_div_ss(_mm_set_ss(factor),denominator);
    float x=_mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(sideways),scale));
    float z=_mm_cvtss_f32(_mm_mul_ss(scale,_mm_set_ss(forward)));
    double step=(double)from_fb((uint32_t)call(0xab7c0,fb(x),fb(z),0,0));
    double limit=0.0+step;
    double decay=f64(image+0x154708);
    for (int i=0;i<19;++i) limit=limit*decay+step;
    if (event[0x1c]==1 && (uint8_t)call(0x23690,u64(game),u64(game+0x28),0,0))
        limit=limit+f64(image+0x154710);
    if (speed>limit) return;
    double amount=(double)f32(image+0x2f2a38);
    __m128d original=_mm_set_sd(speed);
    double accelerated=_mm_cvtsd_f64(_mm_add_sd(original,
        _mm_mul_sd(_mm_sub_sd(_mm_set_sd(limit),original),_mm_set_sd(amount))));
    motion[0]=(motion[0]/speed)*accelerated;
    motion[2]=(motion[2]/speed)*accelerated;
    double copy[3];memcpy(copy,motion,sizeof(copy));
    call(0x235f0,u64(game),u64(game+0x28),(uintptr_t)copy,0);
}
