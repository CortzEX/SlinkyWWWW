#include <stdint.h>
#include <string.h>
#include <emmintrin.h>

typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static double g(const void *p){double v;memcpy(&v,p,8);return v;}
static uint32_t fb(float v){return d(&v);}
static float ff(uint64_t v){uint32_t b=(uint32_t)v;return f(&b);}
static void wf(void *p,float v){memcpy(p,&v,4);}
static float narrow(double v){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(v)));}
static float mf(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static uint64_t method(uint8_t *image,uint32_t slot){return q((void *)(uintptr_t)q(image+slot));}
double *recovered_vector_scale_9430(double *,const double *,double);
double *recovered_vector_subtract_93d0(double *,const double *,const double *);
double *recovered_vector_lerp_9460(double *,const double *,const double *,double);
double *recovered_vector_y_offset_9590(double *,const double *,uint8_t *);
void *recovered_geometry_add_9400(double *,const double *,const double *);
float recovered_scalar_lerp_a2b0(float,float,float);
uint64_t recovered_render_293c0(uint8_t *,endpoint);
uint64_t recovered_render_29430(uint8_t *,endpoint);
uint64_t recovered_render_295a0(uint8_t *,endpoint);

__declspec(dllexport) void recovered_trajectory_launch_45f40(uint8_t *ctx,double *input,uint64_t angle,float fraction,double *position,double *velocity,uint8_t *image,endpoint call){
    double radians=g(image+0x154e50);float yaw=narrow((double)ff(angle)*radians),pitch=narrow((double)ff(angle>>32)*radians);
    float cy=ff(call(0xb3590,fb(yaw),0,0,0));
    float cp=ff(call(0xb3590,fb(pitch),0,0,0));
    float sy=ff(call(0xb1cf0,fb(yaw),0,0,0));
    float sp=ff(call(0xb1cf0,fb(pitch),0,0,0));
    uint32_t sign=d(image+0x154e60);
    double direction[3]={(double)mf(ff(fb(sy)^sign),cp),(double)ff(fb(sp)^sign),(double)mf(cp,cy)},scaled[3];
    float speed=recovered_scalar_lerp_a2b0(f(image+0x30498c),f(image+0x304990),fraction);
    recovered_vector_scale_9430(scaled,direction,(double)speed);
    if(!(uint8_t)call(0x23020,q(ctx),0,0,0)){
        double copy[3];memcpy(copy,input,24);recovered_vector_y_offset_9590(input,copy,image);
        if((uint8_t)call(0x236f0,q(ctx),q(ctx+0x28),0,0))input[1]+=g(image+0x154e70);
    }
    double offset=g(image+0x154e78);input[0]-=(double)cy*offset;input[1]+=g(image+0x154e80);input[2]-=(double)sy*offset;
    memcpy(position,input,24);memcpy(velocity,scaled,24);
}

__declspec(dllexport) void trajectory_launch_adapter(uint8_t *event,uint8_t *image,endpoint call){
    recovered_trajectory_launch_45f40((void *)(uintptr_t)q(event+8),(void *)(uintptr_t)q(event+0x10),q(event+0x18),f(event+0x20),(void *)(uintptr_t)q(event+0x28),(void *)(uintptr_t)q(event+0x30),image,call);
}

__declspec(dllexport) void recovered_trajectories_44e40(uint8_t *event,uint8_t *image,endpoint call){
    if(event[0x18] || q(event+0x10)!=(uintptr_t)(image+0x2f3df0))return;
    call(0x13cf70,q(image+0x304478),0,0,0);memset(image+0x304478,0,16);
    call(0x13cf70,q(image+0x304488),0,0,0);memset(image+0x304488,0,16);
}

__declspec(dllexport) void recovered_trajectories_44ea0(uint8_t *event,uint8_t *image,endpoint call){
    if(!d(image+0x304498))return;
    uint8_t *ctx=(void *)(uintptr_t)q(event+0x20);uint64_t angle=call(0x23170,q(ctx),q(ctx+0x28),0,0);
    double current[3],previous[3],input[3],position[3],velocity[3];
    call(0x23030,(uintptr_t)current,q(ctx),q(ctx+0x28),0);call(0x230d0,(uintptr_t)previous,q(ctx),q(ctx+0x28),0);
    recovered_vector_lerp_9460(input,previous,current,(double)f(event+0x28));float fraction=f(event+0x28);
    double camera[3];memcpy(camera,event+8,24);
    recovered_trajectory_launch_45f40(ctx,input,angle,fraction,position,velocity,image,call);
    if(d(image+0x304498)){
        double drag=g(image+0x154df0);uint64_t index=0;
        do{
            double a[3],b[3];memcpy(a,position,24);memcpy(b,velocity,24);recovered_geometry_add_9400(position,a,b);
            for(unsigned lane=0;lane<3;++lane)wf(image+0x3044a0+12*index+4*lane,narrow(position[lane]-camera[lane]));
            memcpy(a,velocity,24);recovered_vector_scale_9430(velocity,a,drag);velocity[1]-=(double)f(image+0x304988);++index;
        }while(index<d(image+0x304498));
    }
    call(method(image,0x13e458),0xbe2,0,0,0);call(method(image,0x150cb0),d(image+0x2f4030),0,0,0);
    uint8_t *color=image+(image[0x30449c]?0x2f4040:0x2f4060);call(method(image,0x150ca0),d(color),d(color+4),d(color+8),0);
    call(method(image,0x14fd08),0x8074,0,0,0);call(method(image,0x14fd10),3,0x1406,0,(uintptr_t)(image+0x3044a0));
    call(method(image,0x154f98),3,0,d(image+0x304498),0);
    if(image[0x304950]==1){
        double low[3],high[3],center[3],half[3],motion[3],offset[3],relative[3],translation[3];
        memcpy(low,image+0x304958,24);memcpy(high,image+0x304970,24);recovered_vector_lerp_9460(center,low,high,g(image+0x154df8));
        memcpy(high,image+0x304970,24);recovered_vector_subtract_93d0(half,high,center);
        double remaining=g(image+0x154e00)-(double)f(event+0x28);memcpy(motion,image+0x304460,24);recovered_vector_scale_9430(offset,motion,remaining);
        memcpy(camera,event+8,24);recovered_vector_subtract_93d0(relative,center,camera);recovered_vector_subtract_93d0(translation,relative,offset);
        call(method(image,0x150cc0),0,0,0,0);call(method(image,0x150cd8),fb(narrow(translation[0])),fb(narrow(translation[1])),fb(narrow(translation[2])),0);
        call(method(image,0x150cd0),fb(narrow(half[0])),fb(narrow(half[1])),fb(narrow(half[2])),0);
        recovered_render_293c0(image,call);recovered_render_29430(image,call);call(method(image,0x150cb8),0,0,0,0);
    }
    recovered_render_295a0(image,call);
}
