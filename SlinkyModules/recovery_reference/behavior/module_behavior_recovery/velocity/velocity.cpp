#include <stdint.h>
#include <string.h>
#include <intrin.h>
#include <emmintrin.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static int32_t s(uint32_t v){int32_t n;memcpy(&n,&v,4);return n;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static double g(const void *p){double v;memcpy(&v,p,8);return v;}
static void pd(void *p,uint32_t v){memcpy(p,&v,4);}
static void pg(void *p,double v){memcpy(p,&v,8);}
static uint32_t fb(float v){return d(&v);}
static uint64_t gb(double v){return q(&v);}
static float ff(uint64_t v){uint32_t n=(uint32_t)v;return f(&n);}
static double gg(uint64_t v){return g(&v);}
static double add(double a,double b){return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(a),_mm_set_sd(b)));}
static double mul(double a,double b){return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(a),_mm_set_sd(b)));}
static double divd(double a,double b){return _mm_cvtsd_f64(_mm_div_sd(_mm_set_sd(a),_mm_set_sd(b)));}
static float roundf32(double a){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(a)));}
static uint8_t chance(float value,uint32_t constants,uint8_t *image,dependency call){
    if(value>f(image+constants))return 1;
    double fraction=(double)roundf32(mul((double)value,g(image+constants+8)));
    float lower=roundf32(add(g(image+constants+16),fraction));
    float upper=roundf32(add(fraction,g(image+constants+24)));
    uint64_t random=call(0xa050,fb(lower),fb(upper),0,0);
    return (uint8_t)call(0xaa30,(uintptr_t)(image+0x2f9da8),random,q(image+constants+32),0);
}
static void velocity_get(double *v,uint8_t *ctx,dependency call){call(0x23550,(uintptr_t)v,q(ctx),q(ctx+0x28),0);}
static void velocity_set(const double *v,uint8_t *ctx,dependency call){double copy[3];memcpy(copy,v,24);call(0x235f0,q(ctx),q(ctx+0x28),(uintptr_t)copy,0);}

extern "C" __declspec(dllexport) void recovered_velocity_30180(uint8_t *event,uint8_t *image,dependency call){
    if(d(image+0x2eaa50)!=3)return;
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);if(ctx[0x40]!=1)return;
    if(image[0x2f9d88]&1){_InterlockedExchange8((volatile char *)(image+0x2f9d88),0);return;}
    if(image[0x2f9d89]!=1)return;
    if(!(uint8_t)call(0x30c50,(uintptr_t)ctx,0,0,0))return;
    if(!chance(f(image+0x2eaa90),0x150e20,image,call))return;
    double v[3];velocity_get(v,ctx,call);v[0]=g(image+0x2f9d90);
    uint32_t mode=d(image+0x2eab68);
    if(mode==2 || (mode==1 && !(uint8_t)call(0x23780,q(ctx),q(ctx+0x28),0,0)))v[1]=g(image+0x2f9d98);
    v[2]=g(image+0x2f9da0);velocity_set(v,ctx,call);image[0x2f9d89]=0;
}
extern "C" __declspec(dllexport) void recovered_velocity_302d0(uint8_t *event,uint8_t *image,dependency call){
    if(d(event+0x24)!=0)return;
    uint64_t packet=call(0x266b0,q(event+8),q(event+0x10),0,0);
    if(packet){uint32_t id=(uint32_t)call(0x266f0,q(event+8),packet,0,0);if(id==d(image+0x2f9db8))_InterlockedExchange8((volatile char *)(image+0x2f9dbc),1);return;}
    packet=call(0x26b50,q(event+8),q(event+0x10),0,0);
    if(packet){
        float x=ff(call(0x26b90,q(event+8),packet,0,0));float z=ff(call(0x26c30,q(event+8),packet,0,0));
        __m128 xx=_mm_mul_ss(_mm_set_ss(x),_mm_set_ss(x));__m128 zz=_mm_mul_ss(_mm_set_ss(z),_mm_set_ss(z));
        float squared=_mm_cvtss_f32(_mm_add_ss(xx,zz));
        _InterlockedExchange8((volatile char *)(image+0x2f9dbc),(char)((double)squared>g(image+0x150e48)));return;
    }
    if(call(0x26b10,q(event+8),q(event+0x10),0,0))_InterlockedExchange8((volatile char *)(image+0x2f9d88),1);
}
extern "C" __declspec(dllexport) void recovered_velocity_303a0(uint8_t *event,uint8_t *image,dependency call){
    (void)call;if(q(event+0x10)==(uintptr_t)(image+0x2ea7f0))image[0x2f9d89]=0;
}
extern "C" __declspec(dllexport) void recovered_velocity_303c0(uint8_t *event,uint8_t *image,dependency call){
    if(event[0x10]!=1)return;uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);if(!q(ctx+0x28))return;
    double v[3];velocity_get(v,ctx,call);memcpy(image+0x2f9dd0,v+2,8);memcpy(image+0x2f9dc0,v,16);
}
extern "C" __declspec(dllexport) void recovered_velocity_30410(uint8_t *event,uint8_t *image,dependency call){
    if(d(image+0x2eaa50)!=2)return;
    if(image[0x2f9dd8]==1 && image[0x2eab90]==0)return;
    if(event[0x10]!=1)return;uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);uint64_t player=q(ctx+0x28);if(!player)return;
    uint8_t *target=(uint8_t *)(uintptr_t)q(ctx+0x38);if(target[0x18]!=1)return;
    if(image[0x2eaab0]==1){float vertical=ff(call(0x23ac0,q(ctx),player,0,0));if(0.0f>=vertical)return;player=q(ctx+0x28);}
    if(image[0x2eaaf0]==1){if(!(uint8_t)call(0x380b0,q(ctx),player,0,0))return;player=q(ctx+0x28);}
    uint32_t tick=(uint32_t)call(0x23760,q(ctx),player,0,0);uint32_t prior=(uint32_t)call(0x239d0,q(ctx),q(ctx+0x28),0,0);if(tick!=prior)return;
    double scale=g(image+0x150e50);pg(image+0x2f9dc0,mul(g(image+0x2f9dc0),scale));pg(image+0x2f9dd0,mul(scale,g(image+0x2f9dd0)));
    double v[3];memcpy(v,image+0x2f9dc0,24);velocity_set(v,ctx,call);image[0x2f9dd8]=1;
}
extern "C" __declspec(dllexport) void recovered_velocity_308e0(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);if(!q(ctx+0x28))return;
    double v[3];velocity_get(v,ctx,call);memcpy(image+0x2f9da0,v+2,8);memcpy(image+0x2f9d90,v,16);image[0x2f9d89]=1;
}
static void scale_current(uint8_t *ctx,uint8_t *image,dependency call){
    double v[3];velocity_get(v,ctx,call);double factor=(double)f(image+0x2eac38);v[0]=mul(v[0],factor);v[2]=mul(factor,v[2]);velocity_set(v,ctx,call);
}
extern "C" __declspec(dllexport) void recovered_velocity_30520(uint8_t *event,uint8_t *image,dependency call){
    image[0x2f9dd8]=0;if(d(image+0x2eaa50)==2)return;
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);if(ctx[0x40]!=1)return;
    uint32_t id=(uint32_t)call(0x23720,q(ctx),q(ctx+0x28),0,0);_InterlockedExchange((volatile long *)(image+0x2f9db8),(long)id);
    uint32_t mode=d(image+0x2eaa50);
    if(mode==1){
        if(image[0x2f9de0]==1){
            uint64_t settings=call(0x22cf0,q(ctx),q(ctx+0x18),0,0);uint64_t key=call(0x25080,q(ctx),settings,0,0);
            uint64_t game=q(ctx);uint8_t pressed=(uint8_t)call(0x25490,game,key,0,0);call(0x25460,game,key,pressed,0);image[0x2f9de0]=0;return;
        }
        if(!(uint8_t)call(0x30c50,(uintptr_t)ctx,0,0,0))return;
        if(!chance(f(image+0x2eaca8),0x150e58,image,call))return;
        if(image[0x2eacc8]==1 && !(uint8_t)call(0x23690,q(ctx),q(ctx+0x28),0,0))return;
        if(!(uint8_t)call(0x23780,q(ctx),q(ctx+0x28),0,0))return;
        double v[3];velocity_get(v,ctx,call);if(0.0>=v[1])return;
        uint64_t effect=call(0x27960,q(ctx),8,0,0);
        if(call(0x23c10,q(ctx),q(ctx+0x28),effect,0))return;
        uint64_t settings=call(0x22cf0,q(ctx),q(ctx+0x18),0,0);uint64_t key=call(0x25080,q(ctx),settings,0,0);
        if((uint8_t)call(0x25430,q(ctx),key,0,0))return;
        call(0x25460,q(ctx),key,1,0);image[0x2f9de0]=1;return;
    }
    if(mode!=0)return;
    uint32_t countdown=d(image+0x2f9ddc);
    if(s(countdown)>0){countdown--;pd(image+0x2f9ddc,countdown);if(countdown!=0)return;scale_current(ctx,image,call);return;}
    if(_InterlockedCompareExchange8((volatile char *)(image+0x2f9dbc),0,1)!=1)return;
    if(!(uint8_t)call(0x30c50,(uintptr_t)ctx,0,0,0))return;
    if(!chance(f(image+0x2eabc8),0x150e58,image,call))return;
    double v[3];velocity_get(v,ctx,call);
    double length=gg(call(0x13cfd0,gb(v[0]),gb(v[2]),0,0));if(length==0.0)return;
    uint32_t yaw=(uint32_t)call(0x23170,q(ctx),q(ctx+0x28),0,0);
    double pi=g(image+0x150e80);float angle=roundf32(add(divd(mul((double)f(&yaw),pi),g(image+0x150e88)),pi));
    float sine=ff(call(0xb1cf0,fb(angle),0,0,0));float cosine=ff(call(0xb3590,fb(angle),0,0,0));
    double projection=divd(add(mul((double)sine,v[0]),mul((double)cosine,v[2])),length);
    double angle_measure=gg(call(0x13cfa0,gb(projection),0,0,0));
    if(!((double)f(image+0x2eac70)>=angle_measure))return;
    countdown=(uint32_t)_mm_cvttss_si32(_mm_load_ss((float *)(image+0x2eac00)));pd(image+0x2f9ddc,countdown);
    if(s(countdown)>0){countdown--;pd(image+0x2f9ddc,countdown);if(countdown!=0)return;}
    scale_current(ctx,image,call);
}
