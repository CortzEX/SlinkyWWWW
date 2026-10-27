#include <stdint.h>
#include <string.h>
#include <intrin.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
double recovered_vector_distance_squared(const double *,const double *);
static uint64_t u64(const void *p){return *(const volatile uint64_t *)p;}
static uint32_t u32(const void *p){return *(const volatile uint32_t *)p;}
static int32_t s32(uint32_t b){int32_t v;memcpy(&v,&b,4);return v;}
static int64_t s64(uint64_t b){int64_t v;memcpy(&v,&b,8);return v;}
static void put32(void *p,uint32_t v){*(volatile uint32_t *)p=v;}

__declspec(dllexport) void recovered_lag_range_packet(uint8_t *event,uint8_t *image,dependency call){
    volatile uint8_t *state=image;
    while(_InterlockedExchange8((volatile char *)(image+0x2fc7c8),1)) _mm_pause();
    uint8_t active=state[0x2fc7f8];
    if(s32(u32(event+0x20))>s32(u32(image+0x2fc7c0))){
        if(active){
            uint64_t packet=call(0x26350,u64(event+8),u64(event+0x10),0,0);
            if(packet && (uint8_t)call(0x26390,u64(event+8),packet,0,0)){
                double position[3],target[3],previous[3];
                call(0x26450,(uintptr_t)position,u64(event+8),packet,0);
                memcpy(target,image+0x2fc7e0,24);memcpy(previous,image+0x2fc808,24);
                double before=recovered_vector_distance_squared(target,previous);
                memcpy(target,image+0x2fc7e0,24);
                double after=recovered_vector_distance_squared(target,position);
                state[0x2fc7d8]=before>after;
            }
        }
        put32(image+0x2fc7c0,u32(event+0x20));
        active=state[0x2fc7f8];
    }
    if(active && state[0x2fc7d8] && !state[0x2fc7d9] && !state[0x2fc7db] && !state[0x2fc7da] &&
        s64(u64(event+0x18))<s64(u64(image+0x2fc7d0))){
        put32(event+0x24,1);
        goto unlock;
    }
    if(u32(event+0x24)) goto unlock;
    {
        uint64_t packet=call(0x26350,u64(event+8),u64(event+0x10),0,0);
        if(packet){
            state[0x2fc7db]=0;
            if((uint8_t)call(0x26390,u64(event+8),packet,0,0)){
                double position[3];
                call(0x26450,(uintptr_t)position,u64(event+8),packet,0);
                memcpy(image+0x2fc808,position,24);
            }
            goto unlock;
        }
        packet=call(0x265e0,u64(event+8),u64(event+0x10),0,0);
        if(packet){
            if(state[0x2fc7d9]){state[0x2fc7d9]=0;state[0x2fc7db]=1;}
            goto unlock;
        }
        packet=call(0x26620,u64(event+8),u64(event+0x10),0,0);
        if(packet && state[0x2fc7da] && (uint32_t)call(0x26660,u64(event+8),packet,0,0)==4)
            *(volatile uint16_t *)(image+0x2fc7da)=0x100;
    }
unlock:
    state[0x2fc7c8]=0;
}

__declspec(dllexport) void recovered_lag_range_input(uint8_t *event,uint8_t *image,dependency call){
    if(event[0x10]!=1) return;
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    uint32_t current=(uint32_t)call(0x23760,u64(ctx),u64(ctx+0x28),0,0);
    uint32_t previous=(uint32_t)call(0x239d0,u64(ctx),u64(ctx+0x28),0,0);
    image[0x2fc858]=current==previous;
}
