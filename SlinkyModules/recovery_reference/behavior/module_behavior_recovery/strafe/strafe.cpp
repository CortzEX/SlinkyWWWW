#include <stdint.h>
#include <string.h>
#include <emmintrin.h>

typedef uint64_t (*dependency)(uint32_t, uint64_t, uint64_t, uint64_t, uint64_t);
static uint64_t u64(const void *p) { uint64_t v;memcpy(&v,p,8);return v; }
static float f32(const void *p) { float v;memcpy(&v,p,4);return v; }
static double f64(const void *p) { double v;memcpy(&v,p,8);return v; }
static uint32_t fb(float f) { uint32_t v;memcpy(&v,&f,4);return v; }
static uint64_t db(double f) { uint64_t v;memcpy(&v,&f,8);return v; }
static double from_db(uint64_t v) { return f64(&v); }
static float from_fb(uint32_t v) { return f32(&v); }

/* RVA 0xa2d0, kept in the original scalar SSE operation order. */
__declspec(dllexport) double recovered_strafe_lerp(double current,double target,double amount) {
    __m128d a=_mm_set_sd(current),b=_mm_set_sd(target),c=_mm_set_sd(amount);
    return _mm_cvtsd_f64(_mm_add_sd(a,_mm_mul_sd(_mm_sub_sd(b,a),c)));
}

__declspec(dllexport) void recovered_strafe_sample(uint8_t *event,uint8_t *image,dependency call) {
    uint8_t *game=(uint8_t *)(uintptr_t)u64(event+8);
    image[0x3043cc]=(uint8_t)call(0x23690,u64(game),u64(game+0x28),0,0);
}

/* RVA 0x41fc0. Game access and the three math library entry points are injected. */
__declspec(dllexport) void recovered_strafe_motion(uint8_t *event,uint8_t *image,dependency call) {
    if (f32(event+0x14)==0.0f && f32(event+0x10)==0.0f) return;
    uint8_t *game=(uint8_t *)(uintptr_t)u64(event+8);
    if (image[0x2f27f0]==1 && !(uint8_t)call(0x380b0,u64(game),u64(game+0x28),0,0)) return;
    uint32_t raw=(uint32_t)call(0x239f0,u64(game),u64(game+0x28),0,0);
    int32_t signed_value;memcpy(&signed_value,&raw,4);
    if ((float)signed_value>f32(image+0x2f2728)) return;
    uint8_t grounded=(uint8_t)call(0x23780,u64(game),u64(game+0x28),0,0);
    uint8_t boost=0;
    float amount;
    if (!grounded) amount=f32(image+0x2f2760);
    else if (event[0x1c]==1) { boost=image[0x3043cc]^1;amount=f32(image+0x2f2798); }
    else amount=f32(image+0x2f27d0);
    if (amount==0.0f) return;
    double motion[3];
    call(0x23550,(uintptr_t)motion,u64(game),u64(game+0x28),0);
    double speed=from_db(call(0x13cfd0,db(motion[0]),db(motion[2]),0,0));
    if (boost) speed=speed+f64(image+0x1545f0);
    float yaw=from_fb((uint32_t)call(0x23170,u64(game),u64(game+0x28),0,0));
    float sideways=f32(event+0x10),forward=f32(event+0x14);
    double turn=sideways<0.0f?f64(image+0x1545f8):0.0;
    if (sideways>0.0f) turn=f64(image+0x154600);
    double heading=(double)yaw;
    if (forward>0.0f) turn=turn*f64(image+0x154620);
    else if (forward<0.0f) { heading=heading+f64(image+0x154610);turn=turn*f64(image+0x154618); }
    else turn=turn*f64(image+0x154608);
    float radians=(float)(((turn+heading)*f64(image+0x154628))/f64(image+0x154610));
    double old_x=motion[0];
    uint32_t sine=(uint32_t)call(0xb1cf0,fb(radians),0,0,0);
    uint32_t sign;memcpy(&sign,image+0x154630,4);
    double target=(double)from_fb(sine^sign)*speed;
    motion[0]=recovered_strafe_lerp(old_x,target,(double)amount);
    double old_z=motion[2];
    float cosine=from_fb((uint32_t)call(0xb3590,fb(radians),0,0,0));
    target=(double)cosine*speed;
    motion[2]=recovered_strafe_lerp(old_z,target,(double)amount);
    double copy[3];memcpy(copy,motion,sizeof(copy));
    call(0x235f0,u64(game),u64(game+0x28),(uintptr_t)copy,0);
}
