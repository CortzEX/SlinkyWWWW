#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static double g(const void *p){double v;memcpy(&v,p,8);return v;}
static float ff(uint64_t v){uint32_t b=(uint32_t)v;return f(&b);}
static uint32_t fb(float v){return d(&v);}
static float narrow(double v){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(v)));}
__declspec(dllexport) uint64_t recovered_angle_add_9de0(uint64_t a,uint64_t b){
    float low=_mm_cvtss_f32(_mm_add_ss(_mm_set_ss(ff(b)),_mm_set_ss(ff(a))));
    float high=_mm_cvtss_f32(_mm_add_ss(_mm_set_ss(ff(b>>32)),_mm_set_ss(ff(a>>32))));
    return fb(low)|((uint64_t)fb(high)<<32);
}
__declspec(dllexport) uint64_t recovered_angle_subtract_9e20(uint64_t a,uint64_t b){
    float low=_mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(ff(a)),_mm_set_ss(ff(b))));
    float high=_mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(ff(a>>32)),_mm_set_ss(ff(b>>32))));
    return fb(low)|((uint64_t)fb(high)<<32);
}
__declspec(dllexport) float recovered_angle_length_9f60(uint64_t angle,dependency call){return ff(call(0xab7c0,(uint32_t)angle,(uint32_t)(angle>>32),0,0));}
float recovered_angle_wrap_a210(float,uint8_t *,dependency);
double *recovered_vector_subtract_93d0(double *,const double *,const double *);
double *recovered_vector_scale_9430(double *,const double *,double);
void *recovered_geometry_add_9400(double *,const double *,const double *);
double *recovered_vector_y_offset_9590(double *,const double *,uint8_t *);
double *recovered_vector_lerp_9460(double *,const double *,const double *,double);
static uint64_t wrapped(uint64_t angle,uint8_t *image,dependency call){
    return (angle&UINT64_C(0xffffffff00000000))|fb(recovered_angle_wrap_a210(ff(angle),image,call));
}
static void apply(uint64_t angle,uint8_t *event,dependency call){call(0x2bf40,angle,fb(narrow(g(event+0x18))),0,0);}
__declspec(dllexport) void recovered_aim_assist_2b200(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);if(ctx[0x40]!=1)return;
    if(image[0x2f7bd8]==0){
        if(image[0x2f7c20]!=1)return;
        if(!(uint8_t)call(0x29f80,0,0,0,0) || !(uint8_t)call(0x29800,100,0,0,0)){image[0x2f7c20]=0;return;}
        uint64_t angle=call(0x23170,q(ctx),q(ctx+0x28),0,0),offset=call(0x29850,0,0,0,0);
        uint64_t combined=recovered_angle_add_9de0(angle,offset),silent=call(0x29ff0,0,0,0,0);
        uint64_t delta=wrapped(recovered_angle_subtract_9e20(silent,combined),image,call);
        float length=recovered_angle_length_9f60(delta,call);
        if(f(image+0x14fef0)>length)image[0x2f7c20]=0;
        apply(delta,event,call);return;
    }
    if(!(uint8_t)call(0x29800,100,0,0,0))return;
    uint8_t pending=image[0x2f7c20];
    if(!pending && d(image+0x2e9020)==3){image[0x2f7c20]=1;pending=1;}
    if(pending && !(uint8_t)call(0x29f80,0,0,0,0))return;
    float partial=f(event+0x10);
    double previous[3],current[3],a[3],b[3],difference[3],scaled[3],self[3],target[3];
    call(0x230d0,(uintptr_t)previous,q(ctx),q(ctx+0x28),0);
    call(0x23030,(uintptr_t)current,q(ctx),q(ctx+0x28),0);
    memcpy(a,current,24);memcpy(b,previous,24);recovered_vector_subtract_93d0(difference,a,b);
    memcpy(a,difference,24);recovered_vector_scale_9430(scaled,a,(double)partial);
    memcpy(a,previous,24);recovered_geometry_add_9400(self,a,scaled);
    if(!(uint8_t)call(0x23020,q(ctx),0,0,0)){memcpy(a,self,24);recovered_vector_y_offset_9590(previous,a,image);memcpy(self,previous,24);}
    double fraction=(double)f(event+0x10);memcpy(a,image+0x2f7be8,24);memcpy(b,image+0x2f7c00,24);
    recovered_vector_lerp_9460(target,a,b,fraction);memcpy(a,self,24);memcpy(b,target,24);
    uint64_t desired=call(0x9f80,(uintptr_t)a,(uintptr_t)b,0,0);
    uint64_t angle=call(0x23170,q(ctx),q(ctx+0x28),0,0),offset=call(0x29850,0,0,0,0);
    uint64_t combined=recovered_angle_add_9de0(angle,offset);
    uint64_t delta=wrapped(recovered_angle_subtract_9e20(desired,combined),image,call);
    if(d(image+0x2e9020)==3 && image[0x2e9048]==0){
        uint64_t silent=call(0x29ff0,0,0,0,0);
        uint64_t old_delta=wrapped(recovered_angle_subtract_9e20(silent,combined),image,call);
        silent=call(0x29ff0,0,0,0,0);
        uint64_t desired_delta=wrapped(recovered_angle_subtract_9e20(desired,silent),image,call);
        float old_length=recovered_angle_length_9f60(old_delta,call);
        if(f(image+0x14fef0)>old_length){
            float desired_length=recovered_angle_length_9f60(desired_delta,call);
            if(recovered_angle_length_9f60(delta,call)>desired_length){call(0x29820,old_delta,0,0,0);return;}
        }
    }
    apply(delta,event,call);
}
