#include <stdint.h>
#include <string.h>
#include <intrin.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t u64(const void *p){return *(const volatile uint64_t *)p;}
static uint32_t u32(const void *p){return *(const volatile uint32_t *)p;}
static int32_t s32(uint32_t b){int32_t v;memcpy(&v,&b,4);return v;}
static int64_t s64(uint64_t b){int64_t v;memcpy(&v,&b,8);return v;}
static void put32(void *p,uint32_t v){*(volatile uint32_t *)p=v;}

__declspec(dllexport) void recovered_backtrack_packet(uint8_t *event,uint8_t *image,dependency call){
    volatile uint8_t *state=image;
    while(_InterlockedExchange8((volatile char *)(image+0x2fc458),1)) _mm_pause();
    if(state[0x2fc470]!=1) goto unlock;
    uint64_t packet=call(0x26a30,u64(event+8),u64(event+0x10),0,0);
    uint64_t game=u64(event+8);
    if(packet){
        uint32_t id=(uint32_t)call(0x26a70,game,packet,0,0);
        if(id==u32(image+0x2fc468)) goto cancel;
    }else{
        if(call(0x26ad0,game,u64(event+0x10),0,0)) goto cancel;
        if(call(0x26a90,u64(event+8),u64(event+0x10),0,0)) goto cancel;
    }
    packet=call(0x266b0,u64(event+8),u64(event+0x10),0,0);
    if(packet){
        if(state[0x2fc471]){
            uint32_t id=(uint32_t)call(0x266f0,u64(event+8),packet,0,0);
            if(id==u32(image+0x2fc46c)) goto deactivate;
        }
    }else if(call(0x26b10,u64(event+8),u64(event+0x10),0,0)) goto deactivate;
    if(s64(u64(event+0x18))<=s64(u64(image+0x2fc460))){
        put32(event+0x24,1);
        uint32_t stamp=u32(event+0x20);
        if(s32(stamp)>s32(u32(image+0x2fc450))){
            put32(image+0x2fc450,stamp);
            call(0x369d0,(uintptr_t)(event+8),0,0,0);
        }
    }else if(!u32(event+0x24) && s32(u32(event+0x20))>s32(u32(image+0x2fc454))){
        call(0x369d0,(uintptr_t)(event+8),1,0,0);
        put32(image+0x2fc454,u32(event+0x20));
    }
    goto unlock;
cancel:
    put32(event+0x24,3);
    goto unlock;
deactivate:
    state[0x2fc470]=0;
unlock:
    state[0x2fc458]=0;
}
