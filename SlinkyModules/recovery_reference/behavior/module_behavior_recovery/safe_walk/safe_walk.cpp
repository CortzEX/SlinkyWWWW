#include <stdint.h>
#include <string.h>
typedef uint64_t (*helper)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t r64(const void*p,unsigned n){uint64_t v;memcpy(&v,(const char*)p+n,8);return v;}
static float f32(const void*p,unsigned n){float v;memcpy(&v,(const char*)p+n,4);return v;}

/* RVA 41d30. Shared helper calls are explicit unresolved dependencies. */
__declspec(dllexport) void safe_walk(uint8_t *event,uint8_t *image,helper call) {
    uint8_t *game=(uint8_t*)(uintptr_t)r64(event,8);
    if(game[64]!=1) return;
    if(image[0x2f2290]==1) {
        uint32_t bits=(uint32_t)(call(0x23170,r64(game,0),r64(game,40),0,0)>>32);
        float pitch;memcpy(&pitch,&bits,4);
        if(f32(image,0x1544d8)>pitch) goto reject;
    }
    if(image[0x2f22b0]==1) {
        uint32_t bits=(uint32_t)call(0x23ac0,r64(game,0),r64(game,40),0,0);
        float value;memcpy(&value,&bits,4);
        if(value>0.0f) goto reject;
    }
    if(image[0x2f22d0]==1) {
        uint64_t item=call(0x28a50,r64(game,0),r64(game,40),0,0);
        if(!(uint8_t)call(0x28b00,r64(game,0),item,0,0)) goto reject;
    }
    image[0x3043c8]=1;
    if((uint8_t)call(0x23780,r64(game,0),r64(game,40),0,0)) {
        if(f32(image,0x2f2270)!=f32(image,0x1544dc)) {
            double v[3];
            call(0x23550,(uintptr_t)v,r64(game,0),r64(game,40),0);
            double factor=(double)f32(image,0x2f2270);
            v[0]=v[0]*factor;v[2]=factor*v[2];
            call(0x235f0,r64(game,0),r64(game,40),(uintptr_t)v,0);
        }
    }
    return;
reject:
    image[0x3043c8]=0;
}
