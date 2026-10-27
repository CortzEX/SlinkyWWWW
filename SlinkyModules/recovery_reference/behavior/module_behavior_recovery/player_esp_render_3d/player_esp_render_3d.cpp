#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static double real(const void *p){double v;memcpy(&v,p,8);return v;}
static uint32_t fb(float v){return d(&v);}
static uint64_t target(uint64_t holder){return q((void *)(uintptr_t)holder);}
static uint64_t method(uint8_t *image,uint32_t slot){return target(q(image+slot));}
static float narrow(double v){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(v)));}
float recovered_scalar_lerp_a2b0(float,float,float);
double *recovered_vector_lerp_9460(double *,const double *,const double *,double);
double *recovered_vector_subtract_93d0(double *,const double *,const double *);
uint64_t recovered_render_293c0(uint8_t *,endpoint);
uint64_t recovered_render_29400(uint8_t *,endpoint);
uint64_t recovered_render_29430(uint8_t *,endpoint);
uint64_t recovered_render_295a0(uint8_t *,endpoint);

__declspec(dllexport) uint64_t recovered_player_esp_health_2fa30(uint8_t *row,float x,float lower,float upper,uint8_t *image,endpoint call){
    float middle=recovered_scalar_lerp_a2b0(upper,lower,f(row+0x44));
    uint64_t color=q(image+0x150ca0);call(target(color),0,0,0,0);
    uint64_t begin=q(image+0x150c98);call(target(begin),1,0,0,0);
    uint64_t vertex=q(image+0x150ce0);call(target(vertex),fb(x),fb(lower),0,0);call(target(vertex),fb(x),fb(middle),0,0);
    uint64_t end=q(image+0x150ca8);call(target(end),0,0,0,0);
    float extra=f(row+0x48);
    if(extra>0){
        float split=recovered_scalar_lerp_a2b0(middle,upper,extra);
        call(target(color),d(image+0x150a24),d(image+0x150a28),0,0);
        call(target(begin),1,0,0,0);call(target(vertex),fb(x),fb(middle),0,0);call(target(vertex),fb(x),fb(split),0,0);call(target(end),0,0,0,0);
        middle=split;
    }
    uint64_t color_target=target(color);float peak=f(image+0x150a24);
    float red=recovered_scalar_lerp_a2b0(peak,0,f(row+0x44));
    float green=recovered_scalar_lerp_a2b0(0,peak,f(row+0x44));
    call(color_target,fb(red),fb(green),0,0);
    call(target(begin),1,0,0,0);call(target(vertex),fb(x),fb(middle),0,0);call(target(vertex),fb(x),fb(upper),0,0);
    return call(target(end),0,0,0,0);
}
__declspec(dllexport) void recovered_player_esp_2eb20(uint8_t *event,uint8_t *image,endpoint call){
    if(!q(image+0x2f7e10)||d(image+0x2ea110)!=1)return;
    call(method(image,0x13e458),0xbe2,0,0,0);
    call(method(image,0x150cb0),d(image+0x2ea0c0),0,0,0);
    float partial=f(event+0x28);uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+0x20);
    uint64_t camera=call(0x22d40,q(ctx),q(ctx+0x18),0,0);
    uint32_t yaw=(uint32_t)call(0x27250,q(ctx),camera,0,0);
    if(!q(image+0x2f7e10))return;
    yaw^=d(image+0x1509d0);double fraction=(double)partial,offset=real(image+0x1509e0);
    uint64_t scale=q(image+0x150cd0),pop=q(image+0x150cb8),index=0;
    float sy=f(image+0x1509e8),sx=f(image+0x1509ec);uint8_t *row=image+0x2f7e20;
    do{
        double previous[3],current[3],position[3],camera_position[3],relative[3];
        memcpy(previous,row,24);memcpy(current,row+0x18,24);recovered_vector_lerp_9460(position,previous,current,fraction);
        memcpy(camera_position,event+8,24);recovered_vector_subtract_93d0(relative,position,camera_position);
        call(method(image,0x150cc0),0,0,0,0);
        call(method(image,0x150cd8),fb(narrow(relative[0])),fb(narrow(relative[1]+offset)),fb(narrow(relative[2])),0);
        call(target(scale),fb(sx),fb(sy),fb(sx),0);
        if(image[0x2ea138]||row[0x4c]==1){
            recovered_render_293c0(image,call);
            int32_t hurt=(int32_t)d(row+0x40);float red=f(row+0x30),green=f(row+0x34),blue=f(row+0x38);
            if(hurt>0&&image[0x2ea158]){
                __m128 elapsed=_mm_sub_ss(_mm_cvtsi32_ss(_mm_setzero_ps(),hurt),_mm_set_ss(partial));
                float t=_mm_cvtss_f32(_mm_mul_ss(_mm_min_ss(_mm_set_ss(f(image+0x1509f0)),elapsed),_mm_set_ss(f(image+0x1509f4))));
                red=recovered_scalar_lerp_a2b0(red,sy,t);green=recovered_scalar_lerp_a2b0(green,0,t);blue=recovered_scalar_lerp_a2b0(blue,0,t);
            }
            if(image[0x2ea178]==1){call(method(image,0x13e448),fb(red),fb(green),fb(blue),d(image+0x1509f8));recovered_render_29400(image,call);}
            call(method(image,0x150ca0),fb(red),fb(green),fb(blue),0);recovered_render_29430(image,call);recovered_render_295a0(image,call);
        }
        if(image[0x2ea198]==1){
            call(method(image,0x150cc8),yaw,0,fb(sy),0);
            call(method(image,0x13e448),0,fb(sy),0,d(image+0x1509fc));
            recovered_player_esp_health_2fa30(row,f(image+0x150a00),sy,f(image+0x150a04),image,call);
        }
        call(target(pop),0,0,0,0);++index;row+=80;
    }while(index<q(image+0x2f7e10));
}
