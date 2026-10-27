#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static float ff(uint64_t v){uint32_t b=(uint32_t)v;return f(&b);}
static uint32_t fb(float v){return d(&v);}
static void wq(void *p,uint64_t v){memcpy(p,&v,8);}
static void wd(void *p,uint32_t v){memcpy(p,&v,4);}
static float add(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float divf(float a,float b){return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float narrow(double v){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(v)));}
double recovered_vector_distance_squared(const double *,const double *);
float recovered_float_clamp_a1f0(float,float,float);

__declspec(dllexport) uint32_t recovered_player_esp_compare_2fba0(const uint8_t *a,const uint8_t *b){
    __m128 difference=_mm_sub_ss(_mm_load_ss((const float *)(b+0x3c)),_mm_load_ss((const float *)(a+0x3c)));
    return (uint32_t)_mm_cvttss_si32(difference);
}
__declspec(dllexport) void recovered_player_esp_2f3f0(uint8_t *event,uint8_t *image,endpoint call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);if(!q(ctx+0x20))return;
    wq(image+0x2f7e10,0);double self[3];call(0x23030,(uintptr_t)self,q(ctx),q(ctx+0x28),0);
    uint64_t list=call(0x24600,q(ctx),q(ctx+0x20),0,0);uint32_t filter=image[0x2ea250];
    if((int32_t)call(0x24e50,q(ctx),list,0,0)>0){
        filter=filter*5+2;uint32_t index=0;float maximum=f(image+0x150a20);
        do{
            uint64_t entry=call(0x24e80,q(ctx),list,index,0);
            uint64_t game=q(ctx),env=q((void *)(uintptr_t)(game+8));
            uint64_t target=q((void *)(uintptr_t)(q((void *)(uintptr_t)env)+0xc0));
            if((uint8_t)call(target,env,q(ctx+0x28),entry,0))goto next;
            uint32_t flags=(uint32_t)call(0x2acb0,q(ctx),entry,0,0);if(flags&filter)goto next;
            if((uint8_t)call(0x237b0,q(ctx),entry,0,0))goto next;
            double position[3],a[3],b[3];call(0x23030,(uintptr_t)position,q(ctx),entry,0);
            memcpy(a,position,24);memcpy(b,self,24);double distance=recovered_vector_distance_squared(a,b);
            float range=f(image+0x2ea1d0);range=_mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(range),_mm_set_ss(range)));
            if(distance>(double)range)goto next;
            uint8_t color[12],highlight=0;
            if(image[0x2ea270]==1){
                env=q((void *)(uintptr_t)(q(ctx)+8));target=q((void *)(uintptr_t)(q((void *)(uintptr_t)env)+0xc0));
                uint64_t selected=call(0x2b1c0,0,0,0,0);
                if((uint8_t)call(target,env,entry,selected,0)){memcpy(color+8,image+0x2ea1e8,4);memcpy(color,image+0x2ea1e0,8);highlight=1;}
            }
            if(!highlight){
                if(!d(image+0x2ea2c0)){
                    uint32_t packed=(uint32_t)call(0x28e10,q(ctx),entry,0,0);call(0x290d0,(uintptr_t)color,packed,0,0);
                }else{
                    uint32_t off=(flags&5)?0x2ea200:0x2ea220;memcpy(color+8,image+off+8,4);memcpy(color,image+off,8);
                }
            }
            uint64_t count=q(image+0x2f7e10);wq(image+0x2f7e10,count+1);uint8_t *row=image+0x2f7e20+count*80;
            memcpy(row+0x28,position+2,8);memcpy(row+0x18,position,16);
            double previous[3];call(0x230d0,(uintptr_t)previous,q(ctx),entry,0);
            memcpy(row+0x10,previous+2,8);memcpy(row,previous,16);memcpy(row+0x38,color+8,4);memcpy(row+0x30,color,8);
            wd(row+0x3c,fb(narrow(distance)));wd(row+0x40,(uint32_t)call(0x239f0,q(ctx),entry,0,0));row[0x4c]=highlight;
            game=q(ctx);float health=ff(call(0x23a40,game,entry,0,0)),extra=ff(call(0x23fe0,game,entry,0,0));
            extra=_mm_cvtss_f32(_mm_max_ss(_mm_setzero_ps(),_mm_set_ss(extra)));
            float total=add(ff(call(0x23a80,game,entry,0,0)),extra),fraction=0.f;
            if(total!=0.f)fraction=recovered_float_clamp_a1f0(0.f,maximum,divf(add(health,extra),total));
            wd(row+0x44,fb(fraction));fraction=0.f;
            if(health!=0.f)fraction=recovered_float_clamp_a1f0(0.f,maximum,divf(extra,health));
            wd(row+0x48,fb(fraction));
            if(q(image+0x2f7e10)==100)break;
next:
            index++;
        }while((int32_t)index<(int32_t)call(0x24e50,q(ctx),list,0,0));
    }
    call(0x13d0f0,(uintptr_t)(image+0x2f7e20),q(image+0x2f7e10),80,UINT64_C(0x18002fba0));
}
__declspec(dllexport) uint64_t player_esp_compare_adapter(uint8_t *event,uint8_t *image,endpoint call){
    (void)image;(void)call;return recovered_player_esp_compare_2fba0((uint8_t *)(uintptr_t)q(event),(uint8_t *)(uintptr_t)q(event+8));
}
