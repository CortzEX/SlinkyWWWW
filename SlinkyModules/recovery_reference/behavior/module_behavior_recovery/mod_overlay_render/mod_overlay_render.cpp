#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static double g(const void *p){double v;memcpy(&v,p,8);return v;}
static void wq(void *p,uint64_t v){memcpy(p,&v,8);}
static void wf(void *p,float v){memcpy(p,&v,4);}
static uint32_t bits(float v){return d(&v);}
static float ff(uint64_t v){uint32_t b=(uint32_t)v;return f(&b);}
static float add(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float sub(float a,float b){return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float mul(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float minimum(float a,float b){return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float narrow(double v){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(v)));}
static uint64_t call4(endpoint call,uint64_t r,uint64_t a,uint64_t b,uint64_t c,uint64_t d){return call(r,a,b,c,d,0,0,0,0,0);}
float recovered_smooth_a280(float,uint8_t *);
float *recovered_color_74150(float *,float,float,float,float);
uint32_t *recovered_color_74130(uint32_t *,uint32_t,uint32_t,uint32_t);
__declspec(dllexport) uint64_t recovered_mod_overlay_compare_34fb0(const uint8_t *a,const uint8_t *b,endpoint call){
    float left=f(a+0x3c),right=f(b+0x3c);
    if(right>left)return 1;
    if(left>right)return UINT32_MAX;
    return call4(call,0x13d0a0,(uintptr_t)(a+8),(uintptr_t)(b+8),0,0);
}
__declspec(dllexport) uint64_t mod_overlay_compare_adapter(uint8_t *event,uint8_t *image,endpoint call){(void)image;return recovered_mod_overlay_compare_34fb0((void *)(uintptr_t)q(event),(void *)(uintptr_t)q(event+8),call);}
__declspec(dllexport) void recovered_mod_overlay_34510(uint8_t *event,uint8_t *image,endpoint call){
    uint8_t *draw=(void *)(uintptr_t)q(event+0x10);uint64_t canvas=q(draw);
    call4(call,0x79610,canvas,d(image+0x2ed230),0,0);call4(call,0x10340,(uintptr_t)draw,0,0,0);
    float timer=f(image+0x2fbfa0);if(timer>0.f)wf(image+0x2fbfa0,sub(timer,f(event+0x18)));
    uint64_t count=q(image+0x2faff8);
    if(count){
        double dt=(double)f(event+0x18),rate=g(image+0x151c60);uint64_t neg=q(&dt)^q(image+0x151c50);
        double increase=dt*rate,decrease=g(&neg)*rate;float cap=f(image+0x151c68);
        for(uint64_t i=0;i<count;++i){
            uint8_t *row=image+0x2fb000+i*0x50;float value=f(row+0x44);
            if(row[0x48]==1){if(value!=cap)wf(row+0x44,minimum(cap,narrow((double)value+increase)));}
            else {
                value=narrow((double)value+decrease);wf(row+0x44,value);
                if(!(value>0.f)){
                    uint64_t smaller=count-1;wq(image+0x2faff8,smaller);
                    call4(call,0xab910,(uintptr_t)row,(uintptr_t)(row+0x50),(count-i-1)*0x50,0);count=smaller;
                }
            }
        }
    }
    if(image[0x2faff5]==1){
        call4(call,0x79690,canvas,9,0,0);count=q(image+0x2faff8);
        if(count){
            float gap=f(image+0x151c6c);float measure[4];uint64_t i=0;
            do{
                uint8_t *row=image+0x2fb000+i*0x50;
                call(0x7ae90,canvas,0,0,(uintptr_t)(row+8),0,(uintptr_t)measure,0,0,0);memcpy(row+0x3c,measure+2,8);
                if(row[0x1c]){
                    call(0x7ae90,canvas,0,0,(uintptr_t)(row+0x1c),0,(uintptr_t)measure,0,0,0);
                    wf(row+0x3c,add(add(measure[2],gap),f(row+0x3c)));
                }
                ++i;count=q(image+0x2faff8);
            }while(i<count);
        }
        call4(call,0x13d0f0,(uintptr_t)(image+0x2fb000),count,0x50,UINT64_C(0x180034fb0));image[0x2faff5]=0;
    }
    call4(call,0x79690,canvas,9,0,0);
    float background[4],temporary[4];uint32_t primary[4],secondary[4];
    recovered_color_74150(background,0.f,0.f,0.f,ff(0x3f333333));
    recovered_color_74130(primary,d(image+0x2ed240),d(image+0x2ed244),d(image+0x2ed248));
    recovered_color_74130(secondary,d(image+0x2ed260),d(image+0x2ed264),d(image+0x2ed268));
    if(q(image+0x2faff8)){
        float screen=f(draw+0x18),cap=f(image+0x151c68),gap=f(image+0x151c6c),y=0.f;uint64_t index=0;
        do{
            uint8_t *row=image+0x2fb000+index*0x50;float progress=f(row+0x44),alpha=cap;
            if(progress!=cap)alpha=recovered_smooth_a280(progress,image);
            call4(call,0x74a60,canvas,bits(alpha),0,0);
            float corner=f(image+0x2ed2a8);++index;
            if(index<q(image+0x2faff8))corner=minimum(sub(f(row+0x3c),f(row+0x8c)),corner);
            memcpy(temporary,background,16);call4(call,0x74ef0,canvas,(uintptr_t)temporary,0,0);call4(call,0x75bc0,canvas,0,0,0);
            float px=f(image+0x2ed2e0),twice_x=add(px,px),width=f(row+0x3c);
            float bar_x=sub(sub(screen,twice_x),mul(width,alpha)),bar_width=add(twice_x,width),py=f(image+0x2ed318);
            float bar_height=add(add(py,py),f(row+0x40));
            call(0x76a10,canvas,bits(bar_x),bits(y),bits(bar_width),bits(bar_height),0,0,0,bits(corner));call4(call,0x77210,canvas,0,0,0);
            memcpy(temporary,primary,16);call4(call,0x74ef0,canvas,(uintptr_t)temporary,0,0);
            float text_y=add(f(image+0x2ed318),y),text_x=sub(sub(screen,f(image+0x2ed2e0)),mul(f(row+0x3c),alpha));
            float end=ff(call(0x79770,canvas,bits(text_x),bits(text_y),(uintptr_t)(row+8),0,0,0,0,0));
            if(row[0x1c]){
                memcpy(temporary,secondary,16);call4(call,0x74ef0,canvas,(uintptr_t)temporary,0,0);
                call(0x79770,canvas,bits(add(end,gap)),bits(text_y),(uintptr_t)(row+0x1c),0,0,0,0,0);
            }
            py=f(image+0x2ed318);y=add(y,mul(alpha,add(add(py,py),f(row+0x40))));
        }while(index<q(image+0x2faff8));
    }
    call4(call,0x74a60,canvas,d(image+0x151c68),0,0);
}
