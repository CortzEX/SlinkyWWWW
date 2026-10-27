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

double *recovered_vector_subtract_93d0(double *,const double *,const double *);
double *recovered_vector_lerp_9460(double *,const double *,const double *,double);
__declspec(dllexport) float recovered_scalar_lerp_a2b0(float a,float b,float fraction){
    __m128 av=_mm_set_ss(a),difference=_mm_sub_ss(_mm_set_ss(b),av);
    return _mm_cvtss_f32(_mm_add_ss(av,_mm_mul_ss(difference,_mm_set_ss(fraction))));
}
__declspec(dllexport) void recovered_backtrack_render(uint8_t *event,uint8_t *image,endpoint invoke){
    if(image[0x2fc4a0]!=1) return;
    double fraction=(double)f32(event+0x28);
    double previous[3],current[3],position[3],camera[3],relative[3];
    memcpy(previous,image+0x2fc4a8,24);memcpy(current,image+0x2fc4c0,24);
    recovered_vector_lerp_9460(position,previous,current,fraction);
    memcpy(camera,event+8,24);
    recovered_vector_subtract_93d0(relative,position,camera);
    invoke(0x1800293c0,0,0,0,0);
    invoke(method(image,0x150cb0),u32(image+0x2edd10),0,0,0);
    invoke(method(image,0x150cc0),0,0,0,0);
    invoke(method(image,0x150cd8),fb((float)relative[0]),fb((float)(relative[1]+f64(image+0x152178))),fb((float)relative[2]),0);
    invoke(method(image,0x150cd0),u32(image+0x152184),u32(image+0x152180),u32(image+0x152184),0);
    if(image[0x2edd50]==1){
        float angle=recovered_scalar_lerp_a2b0(f32(image+0x2fc4d8),f32(image+0x2fc4dc),f32(event+0x28));
        invoke(method(image,0x150cc8),fb(f32(image+0x152188)-angle),0,u32(image+0x152180),0);
    }
    if(image[0x2edd70]==1){
        invoke(method(image,0x13e448),u32(image+0x2edd20),u32(image+0x2edd24),u32(image+0x2edd28),u32(image+0x15218c));
        invoke(0x180029400,0,0,0,0);
    }
    invoke(method(image,0x150ca0),u32(image+0x2edd20),u32(image+0x2edd24),u32(image+0x2edd28),0);
    invoke(0x180029430,0,0,0,0);
    invoke(method(image,0x150cb8),0,0,0,0);
    invoke(0x1800295a0,0,0,0,0);
}
