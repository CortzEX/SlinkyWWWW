#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
typedef uint64_t (*endpoint4)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static double g(const void *p){double v;memcpy(&v,p,8);return v;}
static uint32_t fb(float v){return d(&v);}
static float ff(uint64_t v){uint32_t b=(uint32_t)v;return f(&b);}
static void wq(void *p,uint64_t v){memcpy(p,&v,8);}
static void wd(void *p,uint32_t v){memcpy(p,&v,4);}
static float narrow(double v){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(v)));}
static float sf(float a,float b){return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static uint64_t target(uint64_t holder){return q((void *)(uintptr_t)holder);}
static uint64_t method(uint8_t *image,uint32_t slot){return target(q(image+slot));}
static uint64_t virtual_method(uint64_t env,uint32_t offset){return q((void *)(uintptr_t)(q((void *)(uintptr_t)env)+offset));}
static __declspec(thread) endpoint current_endpoint;
static uint64_t geometry_call(uint64_t r,uint64_t a,uint64_t b,uint64_t c,uint64_t d){return current_endpoint(r,a,b,c,d,0,0,0);}
static uint64_t wrap_call(uint32_t r,uint64_t a,uint64_t b,uint64_t c,uint64_t d){return geometry_call(r,a,b,c,d);}
float recovered_angle_wrap_a210(float,uint8_t *,dependency);
float recovered_scalar_lerp_a2b0(float,float,float);
uint64_t recovered_angle_scale_9e60(uint64_t,float);
double recovered_vector_distance_squared(const double *,const double *);
uint64_t recovered_render_29500(uint8_t *,endpoint4);
uint64_t recovered_render_29540(uint8_t *,endpoint4);
uint64_t recovered_render_29570(uint8_t *,endpoint4);
uint64_t recovered_render_295a0(uint8_t *,endpoint4);

static void release(uint8_t *ctx,uint8_t *image,endpoint call){
    uint64_t count=q(image+0x301ea0);
    if(count){
        uint64_t env=q((void *)(uintptr_t)(q(ctx)+8)),index=0;uint8_t *row=image+0x301eb0;
        do{
            uint64_t ref=q(row+0x28);
            if(ref){call(virtual_method(env,0xb0),env,ref,0,0,0,0,0);count=q(image+0x301ea0);}
            ++index;row+=56;
        }while(index<count);
    }
    wq(image+0x301ea0,0);
}
__declspec(dllexport) void recovered_indicators_3ea40(uint8_t *event,uint8_t *image,endpoint call){
    if(event[0x18]||q(event+0x10)!=(uintptr_t)(image+0x2f1440))return;
    release((uint8_t *)(uintptr_t)q(event+8),image,call);
}
__declspec(dllexport) void recovered_indicators_3ef20(uint8_t *event,uint8_t *image,endpoint call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);release(ctx,image,call);if(!q(ctx+0x20))return;
    uint64_t camera=call(0x22d40,q(ctx),q(ctx+0x18),0,0,0,0,0);
    uint64_t font=call(0x272a0,q(ctx),camera,0,0,0,0,0);if(!font)return;
    double self[3];call(0x23030,(uintptr_t)self,q(ctx),q(ctx+0x28),0,0,0,0);
    uint64_t list=call(0x24620,q(ctx),q(ctx+0x20),0,0,0,0,0);
    if((int32_t)call(0x24e50,q(ctx),list,0,0,0,0,0)<=0)return;
    double yellow_threshold=g(image+0x154028),white_threshold=g(image+0x154030);uint32_t index=0;
    do{
        uint64_t entity=call(0x24e80,q(ctx),list,index,0,0,0,0);uint32_t type=(uint32_t)call(0x23860,q(ctx),entity,0,0,0,0,0);
        if(type==14){if(!image[0x2f1718])goto next;}
        else if(type==12){if(!image[0x2f16f8])goto next;}
        else if(type==10){if(!image[0x2f16d8]||(uint8_t)call(0x27fa0,q(ctx),entity,0,0,0,0,0))goto next;}
        else goto next;
        double position[3],previous[3];call(0x23030,(uintptr_t)position,q(ctx),entity,0,0,0,0);call(0x230d0,(uintptr_t)previous,q(ctx),entity,0,0,0,0);
        double distance=recovered_vector_distance_squared(position,self);
        if(image[0x2f1738]==1&&distance>recovered_vector_distance_squared(previous,self))goto next;
        if(!(distance>=0)){uint64_t result=call(0xaf2f0,q(&distance),0,0,0,0,0,0);distance=g(&result);}
        else distance=_mm_cvtsd_f64(_mm_sqrt_sd(_mm_setzero_pd(),_mm_set_sd(distance)));
        uint64_t old=q(image+0x301ea0);wq(image+0x301ea0,old+1);uint8_t *row=image+0x301eb0+56*old;
        memcpy(row,position,8);memcpy(row+8,position+2,8);memcpy(row+16,previous,8);memcpy(row+24,previous+2,8);wd(row+0x20,type);
        uint64_t env=q((void *)(uintptr_t)(q(ctx)+8));
        call(0xab710,(uintptr_t)(image+0x3020e0),10,(uintptr_t)(image+0x1540a8),q(&distance),0,0,0);
        uint64_t local=call(virtual_method(env,0x538),env,(uintptr_t)(image+0x3020e0),0,0,0,0,0);
        if(!local)wq(row+0x28,0);
        else{
            uint64_t global=call(virtual_method(env,0xa8),env,local,0,0,0,0,0);wq(row+0x28,global);
            if(global){uint32_t width=(uint32_t)call(0x27560,q(ctx),font,global,0,0,0,0);uint32_t color=distance>yellow_threshold?0xffffff00:0xffff0000;wd(row+0x30,width);if(distance>white_threshold)color=0xffffffff;wd(row+0x34,color);}
        }
        if(q(image+0x301ea0)==10)return;
next:  ++index;
    }while((int32_t)index<(int32_t)call(0x24e50,q(ctx),list,0,0,0,0,0));
}

static void render(uint8_t *event,uint8_t *image,endpoint call){
    if(!q(image+0x301ea0))return;
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+0x20);float partial=f(event+0x40);
    uint64_t camera=call(0x22d40,q(ctx),q(ctx+0x18),0,0,0,0,0),font=call(0x272a0,q(ctx),camera,0,0,0,0,0);
    float yaw=ff(call(0x27250,q(ctx),camera,0,0,0,0,0));recovered_render_29500(image,geometry_call);
    uint64_t center=recovered_angle_scale_9e60(q(event+0x28),f(image+0x153fe0));call(method(image,0x150cc0),0,0,0,0,0,0,0);
    uint64_t translate=q(image+0x150cd8);call(target(translate),(uint32_t)center,(uint32_t)(center>>32),0,0,0,0,0);
    call(method(image,0x150cb0),d(image+0x153fe4),0,0,0,0,0,0);call(method(image,0x13e458),0xb20,0,0,0,0,0,0);
    uint64_t clock=call(0x4c270,0,0,0,0,0,0,0);double phase=g(&clock)*g(image+0x153fe8);uint64_t wave=call(0xb1990,q(&phase),0,0,0,0,0,0);
    if(q(image+0x301ea0)){
        double half=g(image+0x153ff0);float alpha=narrow(g(&wave)*half+half);double angle_offset=g(image+0x154008);
        float one=f(image+0x153fe4),marker_offset=f(image+0x154020),marker_scale=f(image+0x154024);uint32_t sign=d(image+0x154010);
        uint64_t scale=q(image+0x150cd0),color=q(image+0x13e448),index=0;uint8_t *row=image+0x301eb0;
        do{
            double px=(double)recovered_scalar_lerp_a2b0(narrow(g(row+16)),narrow(g(row)),partial),pz=(double)recovered_scalar_lerp_a2b0(narrow(g(row+24)),narrow(g(row+8)),partial);
            px-=g(event+8);pz-=g(event+0x18);uint64_t angle_bits=call(0x13cfb0,q(&pz),q(&px),0,0,0,0,0);
            float angle=recovered_angle_wrap_a210(sf(narrow((g(&angle_bits)*g(image+0x153ff8))/g(image+0x154000)+angle_offset),yaw),image,wrap_call);
            call(method(image,0x150cc0),0,0,0,0,0,0,0);call(method(image,0x150cc8),fb(angle),0,0,fb(one),0,0,0);
            float size=f(image+0x2f1680);call(target(translate),0,d(image+0x2f16b8)^sign,0,0,0,0,0);call(target(scale),fb(size),fb(size),fb(size),0,0,0,0);
            if(q(row+0x28)){
                call(method(image,0x150cc0),0,0,0,0,0,0,0);call(method(image,0x150cc8),fb(angle)^sign,0,0,fb(one),0,0,0);
                if(event[0x44]==1){call(0x277f0,q(ctx),0,0,0,0,0,0);call(0x278f0,q(ctx),fb(one),fb(one),fb(one),0x3f800000,0,0);}
                else call(method(image,0x13e458),0xde1,0,0,0,0,0,0);
                int32_t negative=(int32_t)(0u-d(row+0x30));float x=narrow((double)negative*g(image+0x153ff0));
                call(0x27590,q(ctx),font,q(row+0x28),fb(x),0xc0a00000,d(row+0x34),1);
                if(event[0x44]==1)call(0x27820,q(ctx),0,0,0,0,0,0);else call(method(image,0x13e450),0xde1,0,0,0,0,0,0);
                call(method(image,0x150cb8),0,0,0,0,0,0,0);
            }
            call(target(translate),0,fb(marker_offset),0,0,0,0,0);call(target(scale),fb(marker_scale),fb(marker_scale),fb(marker_scale),0,0,0,0);
            uint32_t type=d(row+0x20)-10;
            call(target(color),d(image+0x154110+4*(uint64_t)type),d(image+0x154124+4*(uint64_t)type),d(image+0x154138+4*(uint64_t)type),fb(alpha),0,0,0);
            recovered_render_29540(image,geometry_call);call(target(color),0,0,0,fb(alpha),0,0,0);recovered_render_29570(image,geometry_call);call(method(image,0x150cb8),0,0,0,0,0,0,0);
            ++index;row+=56;
        }while(index<q(image+0x301ea0));
    }
    call(method(image,0x150cb8),0,0,0,0,0,0,0);recovered_render_295a0(image,geometry_call);
}
__declspec(dllexport) void recovered_indicators_3ead0(uint8_t *event,uint8_t *image,endpoint call){endpoint old=current_endpoint;current_endpoint=call;render(event,image,call);current_endpoint=old;}
