#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*dependency)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static void pq(void *p,uint64_t v){memcpy(p,&v,8);}
static void pd(void *p,uint32_t v){memcpy(p,&v,4);}
static void pf(void *p,float v){memcpy(p,&v,4);}
static float ff(uint64_t v){uint32_t n=(uint32_t)v;return f(&n);}
static uint32_t fb(float v){return d(&v);}
static float add(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float mul(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float divide(float a,float b){return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float maximum(float a,float b){return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float random_factor(uint8_t *image,dependency call,uint32_t upper){
    uint64_t sample=call(0xa050,d(image+0x15559c),d(image+upper),0,0,0);
    return ff(call(0xa3e0,sample,0,0,0,0));
}
static void delay(uint8_t *image,dependency call,uint64_t angle){
    uint64_t previous=q(image+0x304a08);
    float amount=divide(f(image+0x2f525c),f(image+0x2f5260));
    float distance=ff(call(0x9ee0,angle,previous,0,0,0));
    if(image[0x2f5280]==1)amount=mul(amount,maximum(mul(distance,f(image+0x155598)),f(image+0x15559c)));
    if(image[0x2f5228]==1){float factor=random_factor(image,call,0x1555a0);amount=mul(amount,factor);}
    pf(image+0x304a00,add(amount,f(image+0x304a00)));
    pq(image+0x304a08,angle);
}
static void advance(uint8_t *image,uint32_t state){
    pd(image+0x3049e0,state);memset(image+0x3049e4,0,16);memset(image+0x3049f0,0,16);
}
__declspec(dllexport) void recovered_inv_manager_47090(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);
    uint64_t screen=call(0x22c90,q(ctx),q(ctx+0x18),0,0,0);
    if(!screen || !(uint8_t)call(0x25b80,q(ctx),screen,0,0,0)){
        memset(image+0x3049f0,0,16);memset(image+0x3049e0,0,16);
        pf(image+0x304a00,f(image+0x2f4e80));
        if(image[0x2f5228]==1){float factor=random_factor(image,call,0x1555a4);pf(image+0x304a00,mul(factor,f(image+0x304a00)));}
        uint64_t angle=call(0x2aad0,13,0,0,0,0);pq(image+0x304a08,angle);return;
    }
    uint32_t state=d(image+0x3049e0);if(state==2)return;
    float timer=f(image+0x304a00);
    if(timer>0.0f){timer=add(timer,f(image+0x155590));pf(image+0x304a00,timer);if(timer>0.0f)return;}
    event[0x10]=1;
    for(;;){
        switch(state){
        case 0:case 1:{
            uint8_t *enabled=(uint8_t *)(uintptr_t)q(image+0x155b40+state*8);
            if(*enabled!=0){
                uint8_t limit=image[0x155b50+state];
                if(image[0x3049fc]<limit){
                    uint64_t target=q(image+0x155b60+state*8);
                    do{
                        if((uint8_t)call(target,(uintptr_t)ctx,(uintptr_t)(image+0x3049e0),0,0,0)){
                            uint64_t angle=call(0x2aad0,image[0x3049fd],0,0,0,0);
                            delay(image,call,angle);pd(image+0x3049e0,3);pd(image+0x3049f8,state);image[0x3049fe]=(state!=1);return;
                        }
                        image[0x3049fc]=(uint8_t)(image[0x3049fc]+1);
                    }while(image[0x3049fc]<limit);
                }
            }
            state++;advance(image,state);break;
        }
        case 2:return;
        case 3:{
            uint32_t action=d(image+0x3049f0);uint8_t destination=image[0x3049f4];
            uint32_t button,mode;
            switch(action){case 0:button=0;mode=1;break;case 1:button=destination;mode=2;break;case 2:button=0;mode=0;break;default:abort();}
            call(0x25be0,q(ctx),screen,image[0x3049fd],button,mode);
            uint8_t index=image[0x3049fc];uint32_t bit=UINT32_C(1)<<(index&31);
            uint64_t mask=(bit&0x80000000)?(UINT64_C(0xffffffff00000000)|bit):bit;
            pq(image+0x3049e8,q(image+0x3049e8)|mask);
            if(image[0x3049fe]==1)image[0x3049fc]=(uint8_t)(index+1);
            if(action==2){uint64_t angle=call(0x2aad0,destination,0,0,0,0);delay(image,call,angle);pd(image+0x3049e0,4);image[0x3049fd]=destination;return;}
            state=d(image+0x3049f8);pd(image+0x3049e0,state);break;
        }
        case 4:{
            call(0x25be0,q(ctx),screen,image[0x3049fd],0,0);
            float low=add(f(image+0x304a08),f(image+0x155594));uint32_t high=d(image+0x304a0c);
            uint64_t angle=((uint64_t)high<<32)|fb(low);delay(image,call,angle);pd(image+0x3049e0,5);return;
        }
        case 5:
            call(0x25be0,q(ctx),screen,0xfffffc19,0,0);
            state=d(image+0x3049f8);pd(image+0x3049e0,state);break;
        default:return;
        }
    }
}
