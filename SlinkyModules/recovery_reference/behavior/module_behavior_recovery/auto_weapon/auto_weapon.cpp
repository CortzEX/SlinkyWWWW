#include <stdint.h>
#include <string.h>
typedef uint64_t (*helper)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t r64(const void*p,unsigned n){uint64_t v;memcpy(&v,(const char*)p+n,8);return v;}
static int32_t i32(const void*p,unsigned n){int32_t v;memcpy(&v,(const char*)p+n,4);return v;}
static float f32(const void*p,unsigned n){float v;memcpy(&v,(const char*)p+n,4);return v;}
static void w32(void*p,unsigned n,uint32_t v){memcpy((char*)p+n,&v,4);}

/* RVA 4a340. Dependencies retain address names; the image parameter supplies data only. */
__declspec(dllexport) void auto_weapon(uint8_t *event,uint8_t *image,helper call) {
    uint8_t *game=(uint8_t*)(uintptr_t)r64(event,8);
    uint64_t hit,target,inventory; int32_t current,selected;
    if(game[64]!=1) goto reset;
    if((uint8_t)call(0x23f90,r64(game,0),r64(game,40),0,0)) goto reset;
    if(image[0x2f5d58]==1 && !(uint8_t)call(0x29080,(uintptr_t)game,0,0,0)) goto reset;
    hit=call(0x22e10,r64(game,0),r64(game,24),0,0);
    if(!hit || (int32_t)call(0x24b50,r64(game,0),hit,0,0)!=2) goto reset;
    target=call(0x24e30,r64(game,0),hit,0,0);
    target=call(0x23f00,r64(game,0),target,0,0);
    if(!target || (uint8_t)call(0x2ace0,r64(game,0),target,7,0)) goto reset;
    if((uint8_t)call(0x380b0,r64(game,0),r64(game,40),0,0)) goto reset;
    inventory=call(0x23f40,r64(game,0),r64(game,40),0,0);
    current=(int32_t)call(0x25a60,r64(game,0),inventory,0,0);
    selected=(int32_t)call(0x380c0,(uintptr_t)game,inventory,0,0);
    if(selected==-1 || selected==current) goto reset;
    int32_t count=i32(image,0x304ae8);
    if(f32(image,0x2f5d38)>(float)count) {
        w32(image,0x304ae8,(uint32_t)count+1);return;
    }
    if(!(uint8_t)call(0x2aa80,UINT64_C(0x1802f5af8),0,0,0)) return;
    call(0x25a80,r64(game,0),inventory,(uint32_t)selected,0);
    call(0x2aab0,UINT64_C(0x1802f5af8),0,0,0);
    return;
reset:
    w32(image,0x304ae8,0);
}
