#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <emmintrin.h>

typedef uint64_t (*refill_dispatch)(uint32_t rva,uint64_t rcx,uint64_t rdx,
    uint64_t r8,uint64_t r9,uint64_t xmm0,uint64_t xmm1,uint64_t xmm2,
    uint64_t fifth_stack_argument);
static uint64_t u64(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t u32(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static int32_t s32(uint32_t v){int32_t s;memcpy(&s,&v,4);return s;}
static float f32(const void *p){float v;memcpy(&v,p,4);return v;}
static double f64(const void *p){double v;memcpy(&v,p,8);return v;}
static uint32_t fb(float v){uint32_t b;memcpy(&b,&v,4);return b;}
static uint64_t db(double v){uint64_t b;memcpy(&b,&v,8);return b;}
static float from_fb(uint64_t b){uint32_t low=(uint32_t)b;return f32(&low);}
static void put32(void *p,uint32_t v){memcpy(p,&v,4);}
static void putf(void *p,float v){memcpy(p,&v,4);}
static double max_zero(double v){return _mm_cvtsd_f64(_mm_max_sd(_mm_set_sd(v),_mm_setzero_pd()));}
static uint64_t draw(refill_dispatch call,float lo,float hi){return call(0xa050,0,0,0,0,fb(lo),fb(hi),0,0);}
static float sample(refill_dispatch call,uint8_t *storage,uint64_t random,double scale){
    return from_fb(call(0xa510,(uintptr_t)storage,random,0,0,0,0,db(scale),0));
}
static float random_float(refill_dispatch call,float lo,float hi){
    return from_fb(call(0xa3e0,draw(call,lo,hi),0,0,0,0,0,0,0));
}

__declspec(dllexport) void recovered_refill_reset_384c0(uint8_t *event,uint8_t *image){
    if(u64(event+0x10)==(uintptr_t)(image+0x2eed90) && event[0x18]==1)
        put32(image+0x2fc580,0);
}

/* Only original table states 0..4 have translated handlers. The original
   performs an unchecked indirect jump for other values; this adapter traps. */
__declspec(dllexport) void recovered_refill_384f0(uint8_t *event,uint8_t *image,
                                               uint32_t incoming_r13,refill_dispatch call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    uint64_t current=call(0x22c90,u64(ctx),u64(ctx+0x18),0,0,0,0,0,0);
    if(u32(image+0x2fc580)!=0){
        if(!current) goto cleanup;
        if(!(uint8_t)call(0x25b80,u64(ctx),current,0,0,0,0,0,0)) goto cleanup;
        event[0x10]=1;
    }
    float delay=f32(image+0x2fc5d0);
    if(delay>0.0f){putf(image+0x2fc5d0,delay+f32(image+0x152a7c));return;}
    if(!(delay<=0.0f)) return;

    uint32_t state=u32(image+0x2fc580);
    float index_limit=f32(image+0x152a74),angle_limit=f32(image+0x152a78);
    float sample_limit=f32(image+0x152a70);
    double sample_scale=f64(image+0x152a48),factor_base=f64(image+0x152a58);
    float chance_low=f32(image+0x152a60),chance_high=f32(image+0x152a64);
    for(;;){
        if(state==4) goto cleanup;
        uint64_t target=u64(ctx+0x28);
        if(!target) goto schedule_close;
        uint64_t inventory=call(0x23f40,u64(ctx),target,0,0,0,0,0,0);
        uint32_t index;
        for(index=0;index<9;++index){
            uint64_t stack=call(0x26140,u64(ctx),inventory,index,0,0,0,0,0);
            if(!stack) break;
            uint64_t item=call(0x25d10,u64(ctx),stack,0,0,0,0,0,0);
            if(!item) break;
            if(!(uint32_t)call(0x25c50,u64(ctx),item,0,0,0,0,0,0)) break;
        }
        if(index==9) goto schedule_close;
        state=u32(image+0x2fc580);
        switch(state){
        case 0: {
            put32(image+0x2fc580,1);
            if(current) return;
            call(0x38dc0,(uintptr_t)ctx,0,0,0,0,0,0,0);
            float output;
            uint32_t selected=(uint32_t)call(0x38ed0,u32(image+0x2fc5fc),0,(uintptr_t)&output,0,
                                             0,fb(f32(image+0x2fc600)),0,0);
            if(selected==UINT32_MAX){call(0x38d60,(uintptr_t)ctx,0,0,0,0,0,0,0);return;}
            uint64_t settings=call(0x22cf0,u64(ctx),u64(ctx+0x18),0,0,0,0,0,0);
            uint64_t key=call(0x252c0,u64(ctx),settings,0,0,0,0,0,0);
            call(0x25380,u64(ctx),key,0,0,0,0,0,0);
            return;
        }
        case 1: {
            float random_index=random_float(call,0.0f,index_limit);
            put32(image+0x2fc5fc,(uint32_t)_mm_cvttss_si32(_mm_set_ss(random_index)));
            putf(image+0x2fc600,random_float(call,0.0f,angle_limit));
            put32(image+0x2fc580,2);
            double setting=(double)f32(image+0x2ef008);
            uint64_t random=draw(call,0.0f,sample_limit);
            double sampled=(double)sample(call,image+0x2fc588,random,sample_scale);
            double extra=max_zero(setting-sampled);
            delay=(float)((double)f32(image+0x2fc5d0)+extra);
            putf(image+0x2fc5d0,delay);
            state=u32(image+0x2fc580);
            break;
        }
        case 2: {
            float output;
            uint32_t selected=(uint32_t)call(0x38ed0,u32(image+0x2fc5fc),0,(uintptr_t)&output,0,
                                             0,fb(f32(image+0x2fc600)),0,0);
            put32(image+0x2fc604,selected);
            if(selected==UINT32_MAX){
                double setting=(double)f32(image+0x2eefd0);
                uint64_t random=draw(call,0.0f,f32(image+0x152a70));
                double sampled=(double)sample(call,image+0x2fc598,random,f64(image+0x152a48));
                delay=(float)((double)f32(image+0x2fc5d0)+max_zero(setting-sampled));
                putf(image+0x2fc5d0,delay);put32(image+0x2fc580,4);
                return;
            }
            float speed=f32(image+0x2ef040);
            uint64_t random=draw(call,f32(image+0x152a40),f32(image+0x152a44));
            float multiplier=sample(call,image+0x2fc5a8,random,sample_scale)*speed;
            double wave=(double)from_fb(call(0xab00,(uintptr_t)(image+0x2fc5c8),0,0,0,0,0,0,0));
            wave=wave*f64(image+0x152a50);
            wave=wave+factor_base;
            multiplier=(float)((double)multiplier*wave);
            random=draw(call,chance_low,chance_high);
            uint8_t gate=(uint8_t)call(0xaa30,(uintptr_t)(image+0x2fc5b8),random,0,0,0,0,db(sample_scale),0);
            if(gate) multiplier=multiplier/random_float(call,f32(image+0x152a68),f32(image+0x152a6c));
            float distance=image[0x2ef0c0]!=0?output:f32(image+0x152a34);
            delay=distance/multiplier;
            delay=delay+f32(image+0x2fc5d0);
            putf(image+0x2fc5d0,delay);
            put32(image+0x2fc5fc,u32(image+0x2fc604));put32(image+0x2fc580,3);
            state=3;
            break;
        }
        case 3: {
            uint32_t action=u32(image+0x2ef118);
            if(action>=2){
                if(action==2){
                    action=u32(image+0x2fc608);
                    uint64_t random=draw(call,f32(image+0x152a30),f32(image+0x152a34));
                    uint8_t gate=(uint8_t)call(0xaa30,(uintptr_t)(image+0x2fc610),random,0,0,0,0,u64(image+0x152a38),0);
                    if(gate) put32(image+0x2fc608,u32(image+0x2fc608)==0);
                } else action=incoming_r13;
            }
            call(0x25be0,u64(ctx),current,u32(image+0x2fc604)+9u,action,0,0,0,1);
            int32_t selected=s32(u32(image+0x2fc604));
            *(image+0x2fc5e0+(intptr_t)selected)=0;
            put32(image+0x2fc580,2);state=2;
            delay=f32(image+0x2fc5d0);incoming_r13=action;
            break;
        }
        case 4: goto cleanup;
        default: abort();
        }
        if(!(delay<=0.0f)) return;
    }
schedule_close: {
        double setting=(double)f32(image+0x2eefd0);
        uint64_t random=draw(call,0.0f,f32(image+0x152a70));
        double sampled=(double)sample(call,image+0x2fc598,random,f64(image+0x152a48));
        delay=(float)((double)f32(image+0x2fc5d0)+max_zero(setting-sampled));
        putf(image+0x2fc5d0,delay);put32(image+0x2fc580,4);
        if(!(delay<=0.0f)) return;
    }
cleanup:
    call(0x284f0,u64(ctx+8),(uintptr_t)(image+0x2eed90),0,0,0,0,0,0);
    current=call(0x22c90,u64(ctx),u64(ctx+0x18),0,0,0,0,0,0);
    if(current) call(0x25af0,u64(ctx),current,0,1,0,0,0,0);
}
