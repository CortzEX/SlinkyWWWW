#include <stdint.h>
#include <string.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static void pd(void *p,uint32_t v){memcpy(p,&v,4);}
extern "C" __declspec(dllexport) void recovered_gui_start_11800(uint8_t *state,uint64_t time_bits){pd(state+0x4b8,0);memcpy(state+0x498,&time_bits,8);}
extern "C" __declspec(dllexport) void recovered_gui_reset_12a80(uint8_t *state,dependency call){call(0x165f0,(uintptr_t)state,0,0,0);}
extern "C" __declspec(dllexport) void recovered_gui_clear_12a90(uint8_t *state){pd(state+0x370,0);state[0x4c8]=0;}
extern "C" __declspec(dllexport) uint32_t *recovered_color_74130(uint32_t *out,uint32_t red,uint32_t green,uint32_t blue){
    pd(out,red);pd(out+1,green);pd(out+2,blue);pd(out+3,0x3f800000);return out;
}
extern "C" __declspec(dllexport) void recovered_gui_325c0(uint8_t *event,uint8_t *image,dependency call){
    (void)image;uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);
    if((uint8_t)call(0x25840,q(ctx),0,0,0))call(0x25880,q(ctx),0,0,0);
}
extern "C" __declspec(dllexport) void recovered_gui_32600(uint8_t *event,uint8_t *image,dependency call){
    if(q(event+0x10)!=(uintptr_t)(image+0x2eb740))return;
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);uint64_t game=q(ctx);
    if(event[0x18]==1){
        if((uint8_t)call(0x25840,game,0,0,0)){
            int32_t width=(int32_t)call(0x27a60,q(ctx),0,0,0);
            int32_t height=(int32_t)call(0x27a90,q(ctx),0,0,0);
            call(0x25940,q(ctx),(uint32_t)(width/2),(uint32_t)(height/2),0);
            call(0x25880,q(ctx),0,0,0);
        }
        uint64_t clock_bits=call(0x4c270,0,0,0,0);recovered_gui_start_11800(image+0x2f9e30,clock_bits);return;
    }
    if((uint8_t)call(0x22e60,game,q(ctx+0x18),0,0))call(0x25880,q(ctx),1,0,0);
    recovered_gui_reset_12a80(image+0x2f9e30,call);recovered_gui_clear_12a90(image+0x2f9e30);
    if(image[0x2fa300]!=0)return;
    uint32_t id=(uint32_t)call(0xbbd0,q(ctx+8),q(ctx+0x10),0,0);if(!id)return;
    uint8_t message[72]={0};pd(message,12);pd(message+8,id);
    uint8_t *current=(uint8_t *)(uintptr_t)q(event+8);call(0x28480,q(current+8),(uintptr_t)message,0,0);
}
extern "C" __declspec(dllexport) void recovered_gui_32730(uint8_t *event,uint8_t *image,dependency call){(void)image;(void)call;event[0x10]|=3;}
extern "C" __declspec(dllexport) void recovered_gui_32740(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);uint32_t color[4];
    recovered_color_74130(color,d(image+0x2eb728),d(image+0x2eb72c),d(image+0x2eb730));memcpy(image+0x2fa190,color,16);
    image[0x2fa2fc]=image[0x2eb9e8];image[0x2fa2fd]=image[0x2eba08];
    call(0x11820,(uintptr_t)(image+0x2f9e30),q(event+0x10),q(ctx+8),q(ctx+0x10));
}
extern "C" __declspec(dllexport) void recovered_gui_327c0(uint8_t *event,uint8_t *image,dependency call){(void)event;(void)call;image[0x2fa300]=1;}
