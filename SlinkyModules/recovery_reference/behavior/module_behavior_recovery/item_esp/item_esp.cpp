#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
typedef uint64_t (*endpoint4)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static double real(const void *p){double v;memcpy(&v,p,8);return v;}
static uint32_t fb(float v){return d(&v);}
static uint64_t target(uint64_t holder){return q((void *)(uintptr_t)holder);}
static uint64_t method(uint8_t *image,uint32_t slot){return target(q(image+slot));}
static float narrow(double v){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(v)));}
static float value(uint64_t v){uint32_t b=(uint32_t)v;float r;memcpy(&r,&b,4);return r;}
static __declspec(thread) endpoint geometry_endpoint;
static uint64_t geometry_call(uint64_t r,uint64_t a,uint64_t b,uint64_t c,uint64_t d){return geometry_endpoint(r,a,b,c,d,0,0,0);}
uint64_t recovered_render_293c0(uint8_t *,endpoint4);
uint64_t recovered_render_29400(uint8_t *,endpoint4);
uint64_t recovered_render_295a0(uint8_t *,endpoint4);
double *recovered_vector_lerp_9460(double *,const double *,const double *,double);
double *recovered_vector_subtract_93d0(double *,const double *,const double *);
static void relative_position(double *out,uint8_t *row,uint8_t *event,double fraction){
    double previous[3],current[3],position[3],camera[3];memcpy(previous,row,24);memcpy(current,row+24,24);
    recovered_vector_lerp_9460(position,previous,current,fraction);memcpy(camera,event+8,24);recovered_vector_subtract_93d0(out,position,camera);
}
__declspec(dllexport) void recovered_item_esp_416c0(uint8_t *event,uint8_t *image,endpoint call){
    (void)event;memset(image+0x3043a0,0,16);call(0x13cf70,q(image+0x3043b0),0,0,0,0,0,0);memset(image+0x3043b0,0,8);
}
static void render(uint8_t *event,uint8_t *image,endpoint call){
    if(!q(image+0x302130))return;
    call(method(image,0x13e458),0xbe2,0,0,0,0,0,0);float partial=f(event+0x28);
    recovered_render_293c0(image,geometry_call);
    if(q(image+0x302130)){
        double fraction=(double)partial,offset=real(image+0x154320);float size=f(image+0x154328),alpha=f(image+0x15432c);
        uint64_t color=q(image+0x13e448),pop=q(image+0x150cb8),index=0;uint8_t *row=image+0x302140;
        do{
            double p[3];relative_position(p,row,event,fraction);
            call(method(image,0x150cc0),0,0,0,0,0,0,0);
            call(method(image,0x150cd8),fb(narrow(p[0])),fb(narrow(p[1]+offset)),fb(narrow(p[2])),0,0,0,0);
            call(method(image,0x150cd0),fb(size),fb(size),fb(size),0,0,0,0);
            call(target(color),d(row+0x30),d(row+0x34),d(row+0x38),fb(alpha),0,0,0);
            recovered_render_29400(image,geometry_call);call(target(pop),0,0,0,0,0,0,0);
            ++index;row+=88;
        }while(index<q(image+0x302130));
    }
    recovered_render_295a0(image,geometry_call);
    if(image[0x2f1ca8]!=1)return;
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+0x20);
    uint64_t camera=call(0x22d40,q(ctx),q(ctx+0x18),0,0,0,0,0);
    uint64_t font=call(0x272a0,q(ctx),camera,0,0,0,0,0);
    float pitch=value(call(0x27200,q(ctx),camera,0,0,0,0,0));
    uint32_t yaw=(uint32_t)call(0x27250,q(ctx),camera,0,0,0,0,0);
    partial=f(event+0x28);
    if(event[0x2c]==1){
        call(0x277f0,q(ctx),0,0,0,0,0,0);
        uint32_t color=d(image+0x154330);call(0x278f0,q(ctx),color,color,color,0x3f800000,0,0);
    }else{
        call(method(image,0x13e458),0xde1,0,0,0,0,0,0);
        uint32_t color=d(image+0x154330);call(method(image,0x150ca0),color,color,color,0,0,0,0);
    }
    uint64_t count=q(image+0x302130);
    if(count){
        double fraction=(double)partial,offset=real(image+0x154320),half=real(image+0x154358);
        yaw^=d(image+0x154340);uint64_t rotate=q(image+0x150cc8),index=0;
        uint32_t one=d(image+0x154330),size=d(image+0x154350);uint8_t *row=image+0x302140;
        do{
            if(q(row+0x40)){
                double p[3];relative_position(p,row,event,fraction);
                call(method(image,0x150cc0),0,0,0,0,0,0,0);
                call(method(image,0x150cd8),fb(narrow(p[0])),fb(narrow(p[1]+offset)),fb(narrow(p[2])),0,0,0,0);
                call(target(rotate),yaw,0,one,0,0,0,0);call(target(rotate),fb(pitch),one,0,0,0,0,0);
                call(method(image,0x150cd0),size,size,size,0,0,0,0);
                int32_t negative=(int32_t)(0u-d(row+0x48));float x=narrow((double)negative*half);
                call(0x27590,q(ctx),font,q(row+0x40),fb(x),0xc0800000,0xffffffff,1);
                call(method(image,0x150cb8),0,0,0,0,0,0,0);
                count=q(image+0x302130);
            }
            ++index;row+=88;
        }while(index<count);
    }
    if(event[0x2c])call(0x27820,q(ctx),0,0,0,0,0,0);
    else call(method(image,0x13e450),0xde1,0,0,0,0,0,0);
}
__declspec(dllexport) void recovered_item_esp_40de0(uint8_t *event,uint8_t *image,endpoint call){
    endpoint previous=geometry_endpoint;geometry_endpoint=call;render(event,image,call);geometry_endpoint=previous;
}
