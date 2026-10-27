#include <stdint.h>
#include <string.h>
#include <intrin.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static void pd(void *p,uint32_t v){memcpy(p,&v,4);}
static uint64_t invoke(dependency call,uint32_t r,uint64_t a,uint64_t b){return call(r,a,b,0,0,0,0,0);}
extern "C" __declspec(dllexport) void recovered_debug_466e0(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);if(ctx[0x40]!=1)return;
    if(image[0x2f4658]==1){
        int32_t hurt=(int32_t)invoke(call,0x239f0,q(ctx),q(ctx+0x28));
        if(hurt>=7){
            uint64_t game=q(ctx);uint32_t tick=(uint32_t)invoke(call,0x23760,game,q(ctx+0x28));
            uint32_t color=0x66,index=(uint32_t)hurt-7;if(index<=3)color=d(image+0x155200+index*4);
            uint32_t sprint=(uint8_t)invoke(call,0x23690,q(ctx),q(ctx+0x28))?0x38:0x63;
            uint32_t block=(uint8_t)invoke(call,0x23f90,q(ctx),q(ctx+0x28))?0x63:0x38;
            call(0x291f0,game,(uintptr_t)(image+0x155136),tick%1000,color,(uint32_t)hurt,sprint,block);
        }
    }
    if(image[0x2f4678]!=1)return;
    uint8_t use=image[0x3049b9];if((use&1)==image[0x3049b8])return;
    image[0x3049b8]=use&1;uint64_t game=q(ctx);
    uint32_t tick=(uint32_t)invoke(call,0x23760,game,q(ctx+0x28));
    call(0x291f0,game,(uintptr_t)(image+0x15517d),tick%1000,(uintptr_t)(image+((use&1)?0x15519d:0x1551a4)),0,0,0);
}
extern "C" __declspec(dllexport) void recovered_debug_46850(uint8_t *event,uint8_t *image,dependency call){
    uint32_t kind=d(event+0x24);if(kind!=0 && kind!=3)return;
    if(invoke(call,0x26580,q(event+8),q(event+0x10))){_InterlockedExchange8((volatile char *)(image+0x3049b9),1);return;}
    uint64_t packet=invoke(call,0x264f0,q(event+8),q(event+0x10));if(!packet)return;
    if((uint32_t)invoke(call,0x26530,q(event+8),packet)==5)_InterlockedExchange8((volatile char *)(image+0x3049b9),0);
}
extern "C" __declspec(dllexport) void recovered_debug_468c0(uint8_t *event,uint8_t *image,dependency call){
    (void)call;if(image[0x2f4698]!=1)return;
    uint32_t at=event[0x10]?0x3049bc:0x3049c0;pd(image+at,d(image+at)+1);pd(image+0x3049c4,0);
}
extern "C" __declspec(dllexport) void recovered_debug_46900(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);if(ctx[0x40]!=1)return;
    uint32_t age=d(image+0x3049c4);
    if(image[0x2f4698]==1){
        if(age<=9){
            uint32_t left=d(image+0x3049bc),right=d(image+0x3049c0);
            uint32_t lc=left==0?0x38:left==1?0x61:0x32,rc=right==0?0x38:right==1?0x62:0x33;
            uint64_t game=q(ctx);uint32_t tick=(uint32_t)invoke(call,0x23760,game,q(ctx+0x28));
            call(0x291f0,game,(uintptr_t)(image+0x1551b1),tick%1000,lc,d(image+0x3049bc),rc,d(image+0x3049c0));
            age=d(image+0x3049c4);
        }
        pd(image+0x3049bc,0);pd(image+0x3049c0,0);
    }
    pd(image+0x3049c4,age+1);
}
