#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t u64(const void *p){return *(const volatile uint64_t *)p;}
static uint32_t u32(const void *p){return *(const volatile uint32_t *)p;}
static float f32(const void *p){uint32_t b=u32(p);float v;memcpy(&v,&b,4);return v;}
static double f64(const void *p){uint64_t b=u64(p);double v;memcpy(&v,&b,8);return v;}
static uint32_t fb(float v){uint32_t b;memcpy(&b,&v,4);return b;}
static uint64_t method(uint8_t *image,uint32_t slot){return u64((void *)(uintptr_t)u64(image+slot));}

__declspec(dllexport) double *recovered_vector_subtract_93d0(double *out,const double *a,const double *b){
    _mm_storeu_pd(out,_mm_sub_pd(_mm_loadu_pd(a),_mm_loadu_pd(b)));
    _mm_store_sd(out+2,_mm_sub_sd(_mm_load_sd(a+2),_mm_load_sd(b+2)));
    return out;
}
__declspec(dllexport) double *recovered_vector_lerp_9460(double *out,const double *a,const double *b,double fraction){
    __m128d first=_mm_loadu_pd(a),difference=_mm_sub_pd(_mm_loadu_pd(b),first);
    _mm_storeu_pd(out,_mm_add_pd(_mm_mul_pd(_mm_set1_pd(fraction),difference),first));
    __m128d az=_mm_load_sd(a+2),dz=_mm_sub_sd(_mm_load_sd(b+2),az);
    _mm_store_sd(out+2,_mm_add_sd(_mm_mul_sd(dz,_mm_set_sd(fraction)),az));
    return out;
}
__declspec(dllexport) void recovered_lag_range_render(uint8_t *event,uint8_t *image,endpoint invoke){
    if(image[0x2fc820]!=1) return;
    double fraction=(double)f32(event+0x28);
    double previous[3],current[3],position[3],camera[3],relative[3];
    memcpy(previous,image+0x2fc828,24);memcpy(current,image+0x2fc840,24);
    recovered_vector_lerp_9460(position,previous,current,fraction);
    memcpy(camera,event+8,24);
    recovered_vector_subtract_93d0(relative,position,camera);
    invoke(0x1800293c0,0,0,0,0);
    invoke(method(image,0x150cb0),u32(image+0x2efc00),0,0,0);
    invoke(method(image,0x150cc0),0,0,0,0);
    invoke(method(image,0x150cd8),fb((float)relative[0]),fb((float)(relative[1]+f64(image+0x152ed8))),fb((float)relative[2]),0);
    invoke(method(image,0x150cd0),u32(image+0x152ee4),u32(image+0x152ee0),u32(image+0x152ee4),0);
    if(image[0x2efc40]==1){
        invoke(method(image,0x13e448),u32(image+0x2efc10),u32(image+0x2efc14),u32(image+0x2efc18),u32(image+0x152ee8));
        invoke(0x180029400,0,0,0,0);
    }
    invoke(method(image,0x150ca0),u32(image+0x2efc10),u32(image+0x2efc14),u32(image+0x2efc18),0);
    invoke(0x180029430,0,0,0,0);
    invoke(method(image,0x150cb8),0,0,0,0);
    invoke(0x1800295a0,0,0,0,0);
}
