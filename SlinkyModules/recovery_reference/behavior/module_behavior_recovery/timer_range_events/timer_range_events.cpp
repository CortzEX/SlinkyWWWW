#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
#include <intrin.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static double g(const void *p){double v;memcpy(&v,p,8);return v;}
static void pd(void *p,uint32_t v){memcpy(p,&v,4);}
static void pf(void *p,float v){memcpy(p,&v,4);}
static float af(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
extern "C" __declspec(dllexport) double *recovered_vector_y_offset_9590(double *out,const double *in,uint8_t *image){
    uint64_t x=q(in);memcpy(out,&x,8);
    double value=_mm_cvtsd_f64(_mm_add_sd(_mm_load_sd(in+1),_mm_load_sd((const double *)(image+0x13e850))));
    memcpy(out+1,&value,8);uint64_t z=q(in+2);memcpy(out+2,&z,8);return out;
}
extern "C" __declspec(dllexport) void recovered_timer_range_43ca0(uint64_t game,uint64_t settings,uint8_t *image,dependency call){
    uint64_t forward=call(0x250d0,game,settings,0,0),backward=call(0x25120,game,settings,0,0);
    uint64_t left=call(0x25170,game,settings,0,0),right=call(0x251c0,game,settings,0,0);
    uint8_t pressed=(uint8_t)call(0x25430,game,forward,0,0);float one=f(image+0x15493c),longitudinal=pressed?one:0.f;
    pressed=(uint8_t)call(0x25430,game,backward,0,0);float negative=f(image+0x154940);
    if(pressed)longitudinal=af(longitudinal,negative);
    pressed=(uint8_t)call(0x25430,game,left,0,0);float lateral=pressed?one:0.f;
    if((uint8_t)call(0x25430,game,right,0,0))lateral=af(lateral,negative);
    pf(image+0x3043e0,longitudinal);pf(image+0x3043e4,lateral);
}
extern "C" __declspec(dllexport) void recovered_timer_range_43bf0(uint8_t *ctx,uint8_t *image,dependency call){
    uint64_t timer=call(0x22c70,q(ctx),q(ctx+0x18),0,0);call(0x259c0,q(ctx),timer,0,0);
    image[0x3043dc]=1;
    if(d(image+0x2f3410)==1){_InterlockedExchange8((volatile char *)(image+0x3043e8),1);return;}
    if(image[0x2f3438]==1){
        uint64_t game=q(ctx),item=call(0x28a50,game,q(ctx+0x28),0,0);
        if(!(uint8_t)call(0x28ac0,game,item,0,0))return;
        uint64_t settings=call(0x22cf0,q(ctx),q(ctx+0x18),0,0),key=call(0x24f90,q(ctx),settings,0,0);
        call(0x25460,q(ctx),key,1,0);call(0x25380,q(ctx),key,0,0);
    }
}
extern "C" __declspec(dllexport) void recovered_timer_range_42c60(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);
    if((int32_t)d(image+0x3043d8)>0){
        uint64_t settings=call(0x22cf0,q(ctx),q(ctx+0x18),0,0);
        uint32_t remaining=d(image+0x3043d8)-1;pd(image+0x3043d8,remaining);
        if((remaining|d(image+0x2f3410))==0)recovered_timer_range_43bf0(ctx,image,call);
        if(ctx[0x40]!=1)return;
        uint8_t *target=(uint8_t *)(uintptr_t)q(ctx+0x38);if(!q(target+8))return;
        uint64_t hit=call(0x22e10,q(ctx),q(ctx+0x18),0,0);if(!hit)return;
        if((uint32_t)call(0x24b50,q(ctx),hit,0,0)!=2)return;
        call(0x22eb0,q(ctx),q(ctx+0x18),0,0);
        uint64_t key=call(0x25270,q(ctx),settings,0,0);call(0x25380,q(ctx),key,0,0);return;
    }
    image[0x3043dd]=0;if(ctx[0x40]!=1)return;
    uint8_t *target=(uint8_t *)(uintptr_t)q(ctx+0x38);
    if(!q(target+8) || g(image+0x1548c0)>g(target+0x10))return;
    if(!(uint8_t)call(0x23780,q(ctx),q(ctx+0x28),0,0))return;
    if((int32_t)call(0x239f0,q(ctx),q(target+8),0,0)>1)return;
    if(image[0x2f3388]==1 && !(uint8_t)call(0x29080,(uintptr_t)ctx,0,0,0))return;
    if(image[0x2f33a8]==1 && !(uint8_t)call(0x380b0,q(ctx),q(ctx+0x28),0,0))return;
    if(image[0x2f33c8]==1 && (uint8_t)call(0x23f90,q(ctx),q(ctx+0x28),0,0))return;
    double velocity[3];call(0x23550,(uintptr_t)velocity,q(ctx),q(ctx+0x28),0);if(velocity[1]>0.0)return;
    uint64_t settings=call(0x22cf0,q(ctx),q(ctx+0x18),0,0),jump=call(0x25080,q(ctx),settings,0,0);
    if((uint8_t)call(0x25430,q(ctx),jump,0,0))return;
    double self[3],candidate[3],copy[3];
    call(0x23030,(uintptr_t)self,q(ctx),q(ctx+0x28),0);
    if(!(uint8_t)call(0x23020,q(ctx),0,0,0)){memcpy(copy,self,24);recovered_vector_y_offset_9590(self,copy,image);}
    call(0x24160,(uintptr_t)candidate,q(ctx),q(target+8),0);
    if(!(uint8_t)call(0x23020,q(ctx),0,0,0)){memcpy(copy,candidate,24);recovered_vector_y_offset_9590(candidate,copy,image);}
    double self_copy[3],candidate_copy[3];memcpy(self_copy,self,24);memcpy(candidate_copy,candidate,24);
    if(!(uint8_t)call(0x29000,q(ctx),q(ctx+0x20),(uintptr_t)self_copy,(uintptr_t)candidate_copy))return;
    recovered_timer_range_43ca0(q(ctx),settings,image,call);image[0x3043dd]=(f(image+0x3043e0)>0.f);
}
extern "C" __declspec(dllexport) void recovered_timer_range_43950(uint8_t *event,uint8_t *image,dependency call){
    (void)call;if(image[0x3043e8]&1)pd(event+0x24,1);
}
extern "C" __declspec(dllexport) void recovered_timer_range_43970(uint8_t *event,uint8_t *image,dependency call){
    if(q(event+0x10)!=(uintptr_t)(image+0x2f3160) || event[0x18]!=0)return;
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);uint64_t timer=call(0x22c70,q(ctx),q(ctx+0x18),0,0);
    call(0x259c0,q(ctx),timer,d(image+0x154938),0);image[0x3043dc]=0;pd(image+0x3043d8,0);_InterlockedExchange8((volatile char *)(image+0x3043e8),0);
}
extern "C" __declspec(dllexport) void timer_range_43bf0_adapter(uint8_t *event,uint8_t *image,dependency call){recovered_timer_range_43bf0((uint8_t *)(uintptr_t)q(event+8),image,call);}
extern "C" __declspec(dllexport) void timer_range_43ca0_adapter(uint8_t *event,uint8_t *image,dependency call){uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);recovered_timer_range_43ca0(q(ctx),q(event+0x10),image,call);}
extern "C" __declspec(dllexport) uint64_t timer_range_9590_adapter(uint8_t *event,uint8_t *image,dependency call){(void)call;return (uintptr_t)recovered_vector_y_offset_9590((double *)(uintptr_t)q(event+8),(const double *)(uintptr_t)q(event+0x10),image);}
