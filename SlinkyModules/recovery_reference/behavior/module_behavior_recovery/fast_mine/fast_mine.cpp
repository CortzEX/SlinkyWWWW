#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*helper)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t r64(const void*p,unsigned n){uint64_t v;memcpy(&v,(const char*)p+n,8);return v;}
static int32_t i32(const void*p,unsigned n){int32_t v;memcpy(&v,(const char*)p+n,4);return v;}
static float f32(const void*p,unsigned n){float v;memcpy(&v,(const char*)p+n,4);return v;}
static double f64(const void*p,unsigned n){double v;memcpy(&v,(const char*)p+n,8);return v;}
static float as_float(uint32_t bits){float v;memcpy(&v,&bits,4);return v;}
static uint32_t bits(float v){uint32_t b;memcpy(&b,&v,4);return b;}
static void w32(void*p,unsigned n,uint32_t v){memcpy((char*)p+n,&v,4);}

__declspec(dllexport) void fast_mine_0(uint8_t *event,uint8_t *image,helper call) {
    uint8_t *game=(uint8_t*)(uintptr_t)r64(event,8);
    uint64_t controller=call(0x22df0,r64(game,0),r64(game,24),0,0);
    int32_t current=0;
    if(controller) {
        w32(image,0x3043c4,(uint32_t)call(0x27df0,r64(game,0),controller,0,0));
        current=(int32_t)call(0x27e40,r64(game,0),controller,0,0);
        float limit=f32(image,0x2f1fd0);
        if((float)current>limit) {
            int32_t capped=_mm_cvttss_si32(_mm_set_ss(limit));
            call(0x27e60,r64(game,0),controller,(uint32_t)capped,0);
        } else if(current>0 && image[0x2f1ff0] && current==i32(image,0x3043c0)) {
            call(0x27e60,r64(game,0),controller,(uint32_t)current-1,0);
        }
    }
    w32(image,0x3043c0,(uint32_t)current);
}

__declspec(dllexport) void fast_mine_18(uint8_t *event,uint8_t *image,helper call) {
    uint8_t *game=(uint8_t*)(uintptr_t)r64(event,8);
    uint64_t controller=call(0x22df0,r64(game,0),r64(game,24),0,0);
    if(!controller) return;
    float progress=as_float((uint32_t)call(0x27df0,r64(game,0),controller,0,0));
    if(progress==0.0f || f32(image,0x3043c4)!=0.0f) return;
    float a=f32(image,0x154438)/progress;
    a=as_float((uint32_t)call(0xb2920,bits(a),0,0,0));
    uint64_t first=(uint64_t)_mm_cvttss_si64(_mm_set_ss(a));
    float b=(float)((f64(image,0x154440)/(double)f32(image,0x2f2028))/(double)progress);
    b=as_float((uint32_t)call(0xb2920,bits(b),0,0,0));
    uint64_t second=(uint64_t)_mm_cvttss_si64(_mm_set_ss(b));
    uint32_t steps=(uint32_t)first-(uint32_t)second+1;
    float result=(float)(uint64_t)steps*progress;
    call(0x27e10,r64(game,0),controller,bits(result),0);
}
