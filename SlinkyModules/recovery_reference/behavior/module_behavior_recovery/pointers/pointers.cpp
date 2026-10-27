#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static double g(const void *p){double v;memcpy(&v,p,8);return v;}
static uint32_t fb(float v){return d(&v);}
static float ff(uint64_t v){uint32_t b=(uint32_t)v;return f(&b);}
static void wq(void *p,uint64_t v){memcpy(p,&v,8);}
static void wf(void *p,float v){memcpy(p,&v,4);}
static float narrow(double v){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(v)));}
static float af(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float sf(float a,float b){return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float mf(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float df(float a,float b){return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static uint64_t target(uint64_t holder){return q((void *)(uintptr_t)holder);}
static uint64_t method(uint8_t *image,uint32_t slot){return target(q(image+slot));}
static __declspec(thread) endpoint current_endpoint;
static uint64_t wrap_call(uint32_t r,uint64_t a,uint64_t b,uint64_t c,uint64_t d){return current_endpoint(r,a,b,c,d);}
float recovered_angle_wrap_a210(float,uint8_t *,dependency);
float recovered_scalar_lerp_a2b0(float,float,float);
float recovered_float_clamp_a1f0(float,float,float);
uint64_t recovered_angle_scale_9e60(uint64_t,float);
double recovered_vector_distance_squared(const double *,const double *);
double recovered_vector_distance_94f0(const double *,const double *);
uint64_t recovered_render_29500(uint8_t *,endpoint);
uint64_t recovered_render_29540(uint8_t *,endpoint);
uint64_t recovered_render_29570(uint8_t *,endpoint);
uint64_t recovered_render_295a0(uint8_t *,endpoint);

__declspec(dllexport) uint32_t recovered_pointers_compare_3e570(const uint8_t *a,const uint8_t *b){return (uint32_t)_mm_cvttss_si32(_mm_sub_ss(_mm_load_ss((const float *)(b+0x30)),_mm_load_ss((const float *)(a+0x30))));}
__declspec(dllexport) uint64_t pointers_compare_adapter(uint8_t *event,uint8_t *image,endpoint call){(void)image;(void)call;return recovered_pointers_compare_3e570((void *)(uintptr_t)q(event),(void *)(uintptr_t)q(event+8));}

static void update(uint8_t *event,uint8_t *image,endpoint call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);if(!q(ctx+0x20))return;
    wq(image+0x3008a0,0);double self[3],self_previous[3];
    call(0x23030,(uintptr_t)self,q(ctx),q(ctx+0x28),0);call(0x230d0,(uintptr_t)self_previous,q(ctx),q(ctx+0x28),0);
    uint64_t camera=call(0x22d40,q(ctx),q(ctx+0x18),0,0);float yaw=ff(call(0x27250,q(ctx),camera,0,0));
    uint64_t list=call(0x24600,q(ctx),q(ctx+0x20),0,0);uint8_t filter=image[0x2f0b60];
    if((int32_t)call(0x24e50,q(ctx),list,0,0)>0){
        uint32_t mask=filter*5+2,index=0;double degrees=g(image+0x153cc0),pi=g(image+0x153cc8),adjustment=g(image+0x153cd0);uint32_t absolute=d(image+0x153ce0);
        do{
            uint64_t entity=call(0x24e80,q(ctx),list,index,0);
            uint8_t *game=(uint8_t *)(uintptr_t)q(ctx);uint64_t env=q(game+8);
            if((uint8_t)call(q((void *)(uintptr_t)(q((void *)(uintptr_t)env)+0xc0)),env,q(ctx+0x28),entity,0))goto next;
            if((uint8_t)call(0x237b0,q(ctx),entity,0,0))goto next;
            uint32_t flags=(uint32_t)call(0x2acb0,q(ctx),entity,0,0);if(flags&mask)goto next;
            double position[3],previous[3];call(0x23030,(uintptr_t)position,q(ctx),entity,0);
            double distance=recovered_vector_distance_squared(position,self);float range=f(image+0x2f0ac8);range=mf(range,range);if(distance>(double)range)goto next;
            double dx=position[0]-self[0],dz=position[2]-self[2];uint64_t angle_bits=call(0x13cfb0,q(&dz),q(&dx),0,0);
            double angle=(g(&angle_bits)*degrees)/pi+adjustment;float wrapped=recovered_angle_wrap_a210(sf(narrow(angle),yaw),image,wrap_call);
            if(f(image+0x2f0b00)>ff(fb(wrapped)&absolute))goto next;
            call(0x230d0,(uintptr_t)previous,q(ctx),entity,0);
            uint64_t old=q(image+0x3008a0);wq(image+0x3008a0,old+1);uint8_t *row=image+0x3008b0+56*old;
            memcpy(row,position,8);memcpy(row+8,position+2,8);memcpy(row+16,previous,8);memcpy(row+24,previous+2,8);
            float current_distance=narrow(distance);
            if(!(current_distance>=0))current_distance=ff(call(0xaf4a0,fb(current_distance),0,0,0));
            else current_distance=_mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(current_distance)));
            wf(row+0x30,current_distance);wf(row+0x2c,narrow(recovered_vector_distance_94f0(self_previous,previous)));
            uint32_t mode=d(image+0x2f0a88);
            if(mode==1){uint32_t color=(uint32_t)call(0x28e10,q(ctx),entity,0,0);float rgb[3];call(0x290d0,(uintptr_t)rgb,color,0,0);memcpy(row+0x28,rgb+2,4);memcpy(row+0x20,rgb,8);}
            else if(mode==2){uint32_t color=flags&5?0x2f0b10:0x2f0b30;memcpy(row+0x28,image+color+8,4);memcpy(row+0x20,image+color,8);}
            if(q(image+0x3008a0)==100)break;
next:      ++index;
        }while((int32_t)index<(int32_t)call(0x24e50,q(ctx),list,0,0));
    }
    call(0x13d0f0,(uintptr_t)(image+0x3008b0),q(image+0x3008a0),56,UINT64_C(0x18003e570));
}
__declspec(dllexport) void recovered_pointers_3df10(uint8_t *event,uint8_t *image,endpoint call){endpoint old=current_endpoint;current_endpoint=call;update(event,image,call);current_endpoint=old;}

static void render(uint8_t *event,uint8_t *image,endpoint call){
    if(!q(image+0x3008a0))return;
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+0x20);float partial=f(event+0x40);
    uint64_t camera=call(0x22d40,q(ctx),q(ctx+0x18),0,0);
    float pitch=ff(call(0x27200,q(ctx),camera,0,0)),yaw=ff(call(0x27250,q(ctx),camera,0,0));
    recovered_render_29500(image,call);
    uint64_t center=recovered_angle_scale_9e60(q(event+0x28),f(image+0x153c70));
    call(method(image,0x150cc0),0,0,0,0);
    if(d(image+0x2f0a10)){
        float floor=_mm_cvtss_f32(_mm_max_ss(_mm_set_ss(f(image+0x153c74)),_mm_set_ss(pitch)));
        call(method(image,0x150cd8),(uint32_t)center,(uint32_t)(center>>32),0,0);
        call(method(image,0x150cc8),fb(sf(f(image+0x153c78),floor)),d(image+0x153c7c),0,0);
    }else call(method(image,0x150cd8),(uint32_t)center,(uint32_t)(center>>32),0,0);
    float one=f(image+0x153c7c);call(method(image,0x150cb0),fb(one),0,0,0);
    call(method(image,0x13e458),0xb20,0,0,0);
    if(q(image+0x3008a0)){
        float span=sf(f(image+0x2f0914),f(image+0x2f0910));if(span==0)span=f(image+0x153c80);
        double degrees=g(image+0x153c88),pi=g(image+0x153c90),adjustment=g(image+0x153c98);float size=f(image+0x153ca0);
        uint64_t scale=q(image+0x150cd0),translate=q(image+0x150cd8),color=q(image+0x150ca0),pop=q(image+0x150cb8);uint32_t sign=d(image+0x153cb0);
        uint64_t index=0;uint8_t *row=image+0x3008b0;
        do{
            double px=(double)recovered_scalar_lerp_a2b0(narrow(g(row+0x10)),narrow(g(row)),partial);
            double pz=(double)recovered_scalar_lerp_a2b0(narrow(g(row+0x18)),narrow(g(row+8)),partial);
            px-=g(event+8);pz-=g(event+0x18);uint64_t angle_bits=call(0x13cfb0,q(&pz),q(&px),0,0);
            float angle=recovered_angle_wrap_a210(sf(narrow((g(&angle_bits)*degrees)/pi+adjustment),yaw),image,wrap_call);
            call(method(image,0x150cc0),0,0,0,0);call(method(image,0x150cc8),fb(angle),0,0,fb(one));
            float glyph_size=mf(f(image+0x2f0950),size);call(target(scale),fb(glyph_size),fb(glyph_size),fb(glyph_size),0);
            float distance=recovered_scalar_lerp_a2b0(f(row+0x2c),f(row+0x30),partial);
            float factor=recovered_float_clamp_a1f0(0,one,df(sf(distance,f(image+0x2f0910)),span));
            float radius=f(image+0x2f0988);if(image[0x2f0a38])radius=mf(radius,af(factor,one));
            call(target(translate),0,fb(radius)^sign,0,0);
            float red,green,blue;
            if(d(image+0x2f0a88)==0){red=recovered_scalar_lerp_a2b0(f(image+0x2f0998),f(image+0x2f09b8),factor);green=recovered_scalar_lerp_a2b0(f(image+0x2f099c),f(image+0x2f09bc),factor);blue=recovered_scalar_lerp_a2b0(f(image+0x2f09a0),f(image+0x2f09c0),factor);}
            else{red=f(row+0x20);green=f(row+0x24);blue=f(row+0x28);}
            call(target(color),fb(red),fb(green),fb(blue),0);recovered_render_29540(image,call);call(target(color),0,0,0,0);recovered_render_29570(image,call);call(target(pop),0,0,0,0);
            ++index;row+=56;
        }while(index<q(image+0x3008a0));
    }
    call(method(image,0x150cb8),0,0,0,0);recovered_render_295a0(image,call);
}
__declspec(dllexport) void recovered_pointers_3da80(uint8_t *event,uint8_t *image,endpoint call){endpoint old=current_endpoint;current_endpoint=call;render(event,image,call);current_endpoint=old;}
