#include <stdint.h>
#include <string.h>
#include <intrin.h>
#include <emmintrin.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t u64(const void *p){return *(const volatile uint64_t *)p;}
static uint32_t u32(const void *p){return *(const volatile uint32_t *)p;}
static int32_t s32(uint32_t b){int32_t v;memcpy(&v,&b,4);return v;}
static float f32(const void *p){uint32_t b=u32(p);float v;memcpy(&v,&b,4);return v;}
static double f64(const void *p){uint64_t b=u64(p);double v;memcpy(&v,&b,8);return v;}
static void put32(void *p,uint32_t v){*(volatile uint32_t *)p=v;}
static void lock(uint8_t *image){while(_InterlockedExchange8((volatile char *)(image+0x2fc7c8),1)) _mm_pause();}

__declspec(dllexport) void recovered_lag_range_update(uint8_t *event,uint8_t *image,dependency call){
    volatile uint8_t *state=image;
    uint8_t input=state[0x2fc858];state[0x2fc858]=0;
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    if(ctx[0x40]!=1) goto reset;
    if(state[0x2efc98]==1 && !(uint8_t)call(0x380b0,u64(ctx),u64(ctx+0x28),0,0)) goto reset;
    if(state[0x2efcb8]==1){
        uint64_t inventory=call(0x23f40,u64(ctx),u64(ctx+0x28),0,0);
        uint32_t slot=(uint32_t)call(0x25a60,u64(ctx),inventory,0,0);
        uint64_t stack=call(0x26140,u64(ctx),inventory,slot,0);
        if(stack){
            uint64_t item=call(0x28a50,u64(ctx),u64(ctx+0x28),0,0);
            if(item && (uint32_t)call(0x25c50,u64(ctx),item,0,0)==0x175 &&
               ((uint32_t)call(0x25dc0,u64(ctx),stack,0,0)&0x4000)){
                put32(image+0x2fc85c,15);goto reset;
            }
        }
        uint32_t cooldown=u32(image+0x2fc85c);
        if(s32(cooldown)>0){put32(image+0x2fc85c,cooldown-1);goto reset;}
    }
    uint8_t sprint=(uint8_t)call(0x23690,u64(ctx),u64(ctx+0x28),0,0);
    uint32_t sprint_delay=(state[0x2fc859]&1)?u32(image+0x2efcd8):0;
    if(sprint) sprint_delay=0;
    state[0x2fc859]=sprint;
    double position[3];
    call(0x23030,(uintptr_t)position,u64(ctx),u64(ctx+0x28),0);
    if((uint8_t)call(0x23020,u64(ctx),0,0,0)){
        double copy[3],adjusted[3];memcpy(copy,position,24);
        call(0x95c0,(uintptr_t)adjusted,(uintptr_t)copy,0,0);
        memcpy(position,adjusted,24);
    }
    uint8_t *target=(uint8_t *)(uintptr_t)u64(ctx+0x38);
    if(!u64(target+8)) goto reset;
    double distance=f64(target+0x10);
    uint64_t random=call(0xa050,u32(image+0x152ef0),u32(image+0x152ef4),0,0);
    uint32_t radius_bits=(uint32_t)call(0xa510,(uintptr_t)(image+0x2fc860),random,u64(image+0x152ef8),0);
    double radius=(double)f32(&radius_bits);
    if(distance>radius*radius) goto reset;
    uint8_t fresh=s32((uint32_t)call(0x239f0,u64(ctx),u64(target+8),0,0))<5;
    uint8_t render=0;
    if(state[0x2efcf8]==1){
        uint64_t view=call(0x22cf0,u64(ctx),u64(ctx+0x18),0,0);
        render=(uint32_t)call(0x25310,u64(ctx),view,0,0)!=0;
    }
    input&=fresh;
    double target_position[3];
    call(0x24160,(uintptr_t)target_position,u64(ctx),u64(target+8),0);
    lock(image);
    *(volatile uint64_t *)(image+0x2fc7d0)=(uint64_t)_mm_cvttss_si64(_mm_set_ss(f32(image+0x2efc78)));
    state[0x2fc7d9]=input;state[0x2fc7da]=(uint8_t)sprint_delay;state[0x2fc7f8]=1;
    memcpy(image+0x2fc7e0,target_position,24);
    memcpy(image+0x2fc828,image+(state[0x2fc820]==1?0x2fc840:0x2fc808),24);
    memcpy(image+0x2fc840,image+0x2fc808,24);
    state[0x2fc820]=render?(uint8_t)u32(image+0x2fc7d8):0;
    state[0x2fc7c8]=0;
    return;
reset:
    lock(image);
    state[0x2fc7db]=0;*(volatile uint16_t *)(image+0x2fc7d9)=0;state[0x2fc7f8]=0;
    state[0x2fc7c8]=0;state[0x2fc820]=0;
}
