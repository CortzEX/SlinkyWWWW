#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
#include <intrin.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static double g(const void *p){double v;memcpy(&v,p,8);return v;}
static float ff(uint64_t v){uint32_t b=(uint32_t)v;return f(&b);}
static uint32_t fb(float v){return d(&v);}
static void pd(void *p,uint32_t v){memcpy(p,&v,4);}
static void pg(void *p,double v){memcpy(p,&v,8);}
static double sub(double a,double b){return _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(a),_mm_set_sd(b)));}
static double mul(double a,double b){return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(a),_mm_set_sd(b)));}
static double divide(double a,double b){return _mm_cvtsd_f64(_mm_div_sd(_mm_set_sd(a),_mm_set_sd(b)));}
static float narrow(double a){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(a)));}
static float mf(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float sf(float a,float b){return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b)));}
void recovered_timer_range_43bf0(uint8_t *,uint8_t *,dependency);
double *recovered_vector_y_offset_9590(double *,const double *,uint8_t *);
void *recovered_geometry_construct_93b0(void *,double,double,double);
void *recovered_geometry_add_9400(double *,const double *,const double *);
double *recovered_vector_subtract_93d0(double *,const double *,const double *);
double *recovered_vector_scale_9430(double *,const double *,double);
double recovered_vector_distance_squared(const double *,const double *);
double *recovered_movement_prediction(double *,uint64_t,float,float,float,uint8_t *,dependency);
double *recovered_vector_reciprocal_9650(double *,const double *,const uint8_t *);
double *recovered_box_clamp_9880(double *,const double *,const double *);
uint32_t recovered_box_ray_98e0(const double *,const double *,const double *,const uint8_t *);

__declspec(dllexport) void recovered_timer_range_42f00(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);
    uint64_t timer=call(0x22c70,q(ctx),q(ctx+0x18),0,0);
    if(image[0x3043dc]==1){
        double remaining=sub(g(image+0x3043f8),g(event+0x18));pg(image+0x3043f8,remaining);
        if(remaining>0.){call(0x259c0,q(ctx),timer,0,0);return;}
        uint64_t fresh=call(0x22c70,q(ctx),q(ctx+0x18),0,0);
        call(0x259c0,q(ctx),fresh,d(image+0x1548d0),0);
        image[0x3043dc]=0;_InterlockedExchange8((volatile char *)(image+0x3043e8),0);
        uint32_t mode=d(image+0x2f3410);
        if(((mode!=1)&image[0x2f3438])==1){
            uint64_t game=q(ctx),item=call(0x28a50,game,q(ctx+0x28),0,0);
            if((uint8_t)call(0x28ac0,game,item,0,0)){
                uint64_t settings=call(0x22cf0,q(ctx),q(ctx+0x18),0,0);
                uint64_t key=call(0x24f90,q(ctx),settings,0,0);call(0x25460,q(ctx),key,0,0);
            }
            mode=d(image+0x2f3410);
        }
        if(mode==1)call(0x25a10,q(ctx),timer,fb((float)(int32_t)d(image+0x3043d8)),0);
    }
    double cooldown=g(image+0x3043f0);
    if(cooldown>0.){pg(image+0x3043f0,sub(cooldown,g(event+0x18)));return;}
    if(image[0x3043dd]!=1 || ctx[0x40]!=1)return;
    uint8_t *target=(uint8_t *)(uintptr_t)q(ctx+0x38);if(!q(target+8))return;
    double velocity[3],self[3],position[3],desired[3],a[3],b[3],out[3];
    call(0x23550,(uintptr_t)velocity,q(ctx),q(ctx+0x28),0);
    call(0x23030,(uintptr_t)self,q(ctx),q(ctx+0x28),0);
    if(!(uint8_t)call(0x23020,q(ctx),0,0,0)){memcpy(a,self,24);recovered_vector_y_offset_9590(out,a,image);memcpy(self,out,24);}
    call(0x23030,(uintptr_t)position,q(ctx),q(target+8),0);
    call(0x24160,(uintptr_t)desired,q(ctx),q(target+8),0);
    int32_t target_ticks=(int32_t)call(0x24200,q(ctx),q(target+8),0,0);
    uint64_t angles=call(0x23170,q(ctx),q(ctx+0x28),0,0);
    double radians=g(image+0x1548d8);
    float yaw=narrow(sub(g(image+0x1548e0),mul((double)ff(angles),radians)));
    float pitch=ff((uint32_t)(angles>>32)+0x80000000u);
    float cosine=ff(call(0xb3590,fb(yaw),0,0,0)),sine=ff(call(0xb1cf0,fb(yaw),0,0,0));
    pitch=narrow(mul((double)pitch,radians));
    float pitch_cos=ff(call(0xb3590,fb(pitch),0,0,0)),pitch_sin=ff(call(0xb1cf0,fb(pitch),0,0,0));
    uint32_t setting=d(image+0x2f3410)==0?0x2f3478:0x2f34b0;
    int32_t steps=_mm_cvttss_si32(_mm_load_ss((const float *)(image+setting+0x30)));if(steps<=0)return;
    pitch_cos=ff(fb(pitch_cos)^d(image+0x1548f0));
    double direction[3]={(double)mf(sine,pitch_cos),(double)pitch_sin,(double)mf(cosine,pitch_cos)};
    double bottom=g(image+0x154900),half=g(image+0x154908),top=g(image+0x154910),reach=g(image+0x154918);
    double damping=g(image+0x154928),target_factor=g(image+0x154930);
    for(uint32_t step=1;step<=(uint32_t)steps;++step){
        double snapshot[3],target_snapshot[3],box[6],ray[3],inverse[3];
        memcpy(snapshot,self,24);memcpy(target_snapshot,position,24);
        recovered_geometry_construct_93b0(a,half,bottom,half);memcpy(b,target_snapshot,24);recovered_vector_subtract_93d0(box,b,a);
        recovered_geometry_construct_93b0(a,half,top,half);memcpy(b,target_snapshot,24);recovered_geometry_add_9400(box+3,b,a);
        memcpy(a,direction,24);recovered_vector_scale_9430(ray,a,reach);
        memcpy(a,ray,24);recovered_vector_reciprocal_9650(inverse,a,image);
        if((uint8_t)recovered_box_ray_98e0(box,snapshot,inverse,image)){
            recovered_box_clamp_9880(out,box,snapshot);memcpy(a,snapshot,24);memcpy(b,out,24);
            double distance=recovered_vector_distance_squared(a,b);
            if(distance>0.){
                float radius=f(image+0x2f3518);if((double)mf(radius,radius)>distance || step==UINT32_MAX)return;
                float step_float=(float)(int32_t)step;
                if(d(image+0x2f3410)==1)recovered_timer_range_43bf0(ctx,image,call);
                else call(0x25a10,q(ctx),timer,fb(step_float),0);
                pd(image+0x3043d8,step);pg(image+0x3043f8,mul((double)sf(step_float,f(event+0x10)),g(image+0x154920)));
                pg(image+0x3043f0,(double)f(image+0x2f3470));return;
            }
        }
        float longitudinal=f(image+0x3043e0),lateral=f(image+0x3043e4);
        float speed=ff(call(0x23b40,q(ctx),q(ctx+0x28),0,0));
        double motion[3];recovered_movement_prediction(motion,angles,longitudinal,lateral,speed,image,call);
        memcpy(a,velocity,24);recovered_geometry_add_9400(out,a,motion);memcpy(velocity,out,24);
        memcpy(a,self,24);memcpy(b,velocity,24);recovered_geometry_add_9400(out,a,b);memcpy(self,out,24);
        memcpy(a,velocity,24);recovered_vector_scale_9430(out,a,damping);memcpy(velocity,out,24);
        if(d(image+0x2f3410)==1){
            uint64_t result=call(0x13cfd0,q(velocity),q(velocity+2),0,0);double length=g(&result);
            memcpy(a,self,24);memcpy(b,desired,24);recovered_vector_subtract_93d0(out,a,b);
            result=call(0x13cfd0,q(out),q(out+2),0,0);double scale=divide(length,g(&result));
            memcpy(a,out,24);recovered_vector_scale_9430(b,a,scale);b[1]=0.;
            memcpy(a,desired,24);recovered_geometry_add_9400(out,a,b);memcpy(desired,out,24);
        }
        if(target_ticks>0){
            memcpy(a,desired,24);memcpy(b,position,24);recovered_vector_subtract_93d0(out,a,b);
            memcpy(a,out,24);recovered_vector_scale_9430(b,a,divide(target_factor,(double)target_ticks));
            memcpy(a,position,24);recovered_geometry_add_9400(out,a,b);memcpy(position,out,24);--target_ticks;
        }
    }
}
