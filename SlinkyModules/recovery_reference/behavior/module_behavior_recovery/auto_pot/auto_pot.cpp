#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <emmintrin.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t u64(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t u32(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static int32_t signed32(uint32_t v){int32_t s;memcpy(&s,&v,4);return s;}
static float f32(const void *p){float v;memcpy(&v,p,4);return v;}
static void put32(void *p,uint32_t v){memcpy(p,&v,4);}
static void putf(void *p,float v){memcpy(p,&v,4);}
static float add(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float call_float(dependency call,uint32_t rva,uint64_t a,uint64_t b){uint32_t v=(uint32_t)call(rva,a,b,0,0);return f32(&v);}
static void schedule(uint8_t *ctx,uint8_t *image,dependency call){call(0x284f0,u64(ctx+8),(uintptr_t)(image+0x2ef128),0,0);}
static uint32_t float_bits(float v){return u32(&v);}
__declspec(dllexport) float recovered_auto_pot_delay(uint8_t *image,dependency call){
    float base=f32(image+0x2ef388);
    uint64_t random=call(0xa050,0,u32(image+0x152c68),0,0);
    uint32_t offset=(uint32_t)call(0xa510,(uintptr_t)(image+0x2fc658),random,u64(image+0x152c70),0);
    __m128 adjusted=_mm_sub_ss(_mm_set_ss(base),_mm_set_ss(f32(&offset)));
    float delay=_mm_cvtss_f32(_mm_max_ss(_mm_setzero_ps(),adjusted));
    random=call(0xa050,u32(image+0x152c78),u32(image+0x152c7c),0,0);
    uint8_t extra=(uint8_t)call(0xaa30,(uintptr_t)(image+0x2fc668),random,u64(image+0x152c80),0);
    if(extra){random=call(0xa050,u32(image+0x152c68),u32(image+0x152c88),0,0);uint32_t amount=(uint32_t)call(0xa3e0,random,0,0,0);delay=add(delay,f32(&amount));}
    return delay;
}
__declspec(dllexport) uint64_t recovered_auto_pot_delay_test(uint8_t *event,uint8_t *image,dependency call){(void)event;return float_bits(recovered_auto_pot_delay(image,call));}

__declspec(dllexport) void recovered_auto_pot_update(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    float after_use=f32(image+0x152c38);
    for(unsigned pass=0;pass<4;pass++){
        float timer=f32(image+0x2fc650);
        if(timer>0.0f){putf(image+0x2fc650,add(timer,f32(image+0x152c3c)));break;}
        if(ctx[0x40]==0){image[0x2fc64c]=0;put32(image+0x2fc640,4);schedule(ctx,image,call);return;}
        switch(u32(image+0x2fc640)){
        case 0:{
            uint64_t inventory=call(0x23f40,u64(ctx),u64(ctx+0x28),0,0);
            uint32_t selected;
            for(selected=0;selected<9;selected++){
                uint64_t stack=call(0x26140,u64(ctx),inventory,selected,0);if(!stack)continue;
                uint64_t item=call(0x25d10,u64(ctx),stack,0,0);if(!item)continue;
                uint32_t kind=(uint32_t)call(0x25c50,u64(ctx),item,0,0);if(kind!=0x175)continue;
                uint32_t damage=(uint32_t)call(0x25dc0,u64(ctx),stack,0,0);
                if(!(damage&0x4000))continue;
                if((damage&15)!=5 && image[0x2ef350]==0)continue;
                break;
            }
            if(selected==9){put32(image+0x2fc654,0);uint32_t state=4-image[0x2fc64c];put32(image+0x2fc640,state);image[0x2fc64c]=0;if(state==4)schedule(ctx,image,call);return;}
            put32(image+0x2fc644,selected);
            uint32_t previous;
            if(image[0x2fc64c]==1)previous=u32(image+0x2fc648);
            else {previous=(uint32_t)call(0x25a60,u64(ctx),inventory,0,0);put32(image+0x2fc648,previous);selected=u32(image+0x2fc644);}
            image[0x2fc64c]=0;put32(image+0x2fc640,1+(selected==previous));
            break;
        }
        case 1:{
            uint8_t claimed=(uint8_t)call(0x2aa80,(uintptr_t)(image+0x2ef128),0,0,0);
            if(!claimed){put32(image+0x2fc640,4);schedule(ctx,image,call);return;}
            uint64_t inventory=call(0x23f40,u64(ctx),u64(ctx+0x28),0,0);
            call(0x25a80,u64(ctx),inventory,u32(image+0x2fc644),0);
            put32(image+0x2fc640,2);
            float delay=recovered_auto_pot_delay(image,call);putf(image+0x2fc650,add(delay,f32(image+0x2fc650)));
            break;
        }
        case 2:{
            if((uint8_t)call(0x23f90,u64(ctx),u64(ctx+0x28),0,0))goto finish;
            uint64_t settings=call(0x22cf0,u64(ctx),u64(ctx+0x18),0,0);
            uint64_t use=call(0x24f90,u64(ctx),settings,0,0);
            call(0x25380,u64(ctx),use,0,0);
            put32(image+0x2fc654,u32(image+0x2fc654)-1);put32(image+0x2fc640,3);
            if(u32(image+0x2fc644)!=u32(image+0x2fc648)){
                float delay=recovered_auto_pot_delay(image,call);delay=add(delay,after_use);putf(image+0x2fc650,add(delay,f32(image+0x2fc650)));
            }
            break;
        }
        case 3:
            if(signed32(u32(image+0x2fc654))>0){image[0x2fc64c]=1;put32(image+0x2fc640,0);}
            else {
                uint64_t inventory=call(0x23f40,u64(ctx),u64(ctx+0x28),0,0);
                call(0x25a80,u64(ctx),inventory,u32(image+0x2fc648),0);put32(image+0x2fc640,4);
            }
            break;
        case 4:call(0x2aab0,(uintptr_t)(image+0x2ef128),0,0,0);goto finish;
        default:abort(); /* Original jump table is defined only for states 0 through 4. */
        }
    }
finish:
    if(u32(image+0x2fc640)==4)schedule(ctx,image,call);
}

__declspec(dllexport) void recovered_auto_pot_input(uint8_t *event,uint8_t *image,dependency call){
    (void)call;
    uint32_t remaining=u32(image+0x2fc678);
    if(u64(event+8)!=(uintptr_t)(image+0x2ef128)||u32(image+0x2fc640)==4||signed32(remaining)<=0)return;
    event[0x10]=1;put32(image+0x2fc654,u32(image+0x2fc654)+1);put32(image+0x2fc678,remaining-1);
}

__declspec(dllexport) void recovered_auto_pot_enable(uint8_t *event,uint8_t *image,dependency call){
    if(u64(event+0x10)!=(uintptr_t)(image+0x2ef128))return;
    if(event[0x18]!=1){put32(image+0x2fc640,0);put32(image+0x2fc654,0);return;}
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);if(ctx[0x40]!=1)return;
    float health=call_float(call,0x23a40,u64(ctx),u64(ctx+0x28));
    float maximum=call_float(call,0x23a80,u64(ctx),u64(ctx+0x28));
    __m128 difference=_mm_sub_ss(_mm_set_ss(maximum),_mm_set_ss(health));
    __m128d scaled=_mm_cvtss_sd(_mm_setzero_pd(),difference);
    scaled=_mm_add_sd(scaled,_mm_load_sd((double *)(image+0x152c58)));
    scaled=_mm_mul_sd(scaled,_mm_load_sd((double *)(image+0x152c60)));
    uint32_t count=(uint32_t)_mm_cvttsd_si32(scaled);
    if(count==0){count=1;if(image[0x2ef3a8]==1){put32(image+0x2fc640,4);return;}}
    if(image[0x2ef3c8]==1){put32(image+0x2fc654,count);put32(image+0x2fc678,0);}
    else {put32(image+0x2fc654,1);put32(image+0x2fc678,image[0x2ef3a8]!=0?count-1:5);}
}
