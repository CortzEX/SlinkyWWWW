#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static double g(const void *p){double v;memcpy(&v,p,8);return v;}
static uint32_t fb(float v){return d(&v);}
static float ff(uint64_t v){uint32_t b=(uint32_t)v;return f(&b);}
static void wq(void *p,uint64_t v){memcpy(p,&v,8);}
static float narrow(double v){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(v)));}
static float af(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float mf(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float df(float a,float b){return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float maxf(float a,float b){return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static uint64_t target(uint64_t holder){return q((void *)(uintptr_t)holder);}
static uint64_t method(uint8_t *image,uint32_t slot){return target(q(image+slot));}
static uint64_t virtual_method(uint64_t env,uint32_t slot){return q((void *)(uintptr_t)(q((void *)(uintptr_t)env)+slot));}
double *recovered_vector_lerp_9460(double *,const double *,const double *,double);
double *recovered_vector_subtract_93d0(double *,const double *,const double *);
uint32_t recovered_screen_project_295f0(uint8_t *,const double *,float *,float *,uint8_t *);

__declspec(dllexport) void recovered_name_tags_release_3d800(uint8_t *game,uint8_t *image,endpoint call){
    if(q(image+0x2fc910)){
        uint64_t env=q(game+8),index=0;
        do{
            uint8_t *row=image+0x2fc920+160*index;
            uint64_t label=q(row+0x38);if(label)call(virtual_method(env,0xb0),env,label,0,0,0,0,0,0);
            uint64_t entity=q(row+0x30);if(entity)call(virtual_method(env,0xb0),env,entity,0,0,0,0,0,0);
            for(unsigned slot=0;slot<5;++slot){
                uint8_t *equipment=row+0x50+16*slot;uint64_t array=q(equipment+8);
                if(array){
                    if((int32_t)d(equipment+4)>0){
                        uint64_t i=0;do{uint64_t entry=q((void *)(uintptr_t)(q(equipment+8)+8*i));call(virtual_method(env,0xb0),env,entry,0,0,0,0,0,0);++i;}while((int64_t)i<(int64_t)(int32_t)d(equipment+4));
                        array=q(equipment+8);
                    }
                    call(0x13cf70,array,0,0,0,0,0,0,0);wq(equipment+8,0);
                }
            }
            ++index;
        }while(index<q(image+0x2fc910));
    }
    wq(image+0x2fc910,0);
}
__declspec(dllexport) void recovered_name_tags_3c210(uint8_t *event,uint8_t *image,endpoint call){
    if(event[0x18] || q(event+0x10)!=(uintptr_t)(image+0x2f02d0))return;
    recovered_name_tags_release_3d800((void *)(uintptr_t)q((void *)(uintptr_t)q(event+8)),image,call);
    uint64_t object=q(image+0x3007a0);if(object){uint64_t game=q((void *)(uintptr_t)q(event+8)),env=q((void *)(uintptr_t)(game+8));call(virtual_method(env,0xb0),env,object,0,0,0,0,0,0);wq(image+0x3007a0,0);}
}
__declspec(dllexport) void name_tags_release_adapter(uint8_t *event,uint8_t *image,endpoint call){recovered_name_tags_release_3d800((void *)(uintptr_t)q(event),image,call);}

__declspec(dllexport) void recovered_name_tags_3c280(uint8_t *event,uint8_t *image,endpoint call){
    if(!q(image+0x2fc910) || !q(image+0x3007a0))return;
    uint8_t *ctx=(void *)(uintptr_t)q(event+0x20);
    uint64_t camera=call(0x22d40,q(ctx),q(ctx+0x18),0,0,0,0,0,0),font=call(0x272a0,q(ctx),camera,0,0,0,0,0,0);
    uint64_t texture=call(0x22dd0,q(ctx),q(ctx+0x18),0,0,0,0,0,0);
    float saved_depth=ff(call(0x27b50,q(ctx),q(image+0x3007a0),0,0,0,0,0,0));call(0x27b70,q(ctx),q(image+0x3007a0),d(image+0x1536d0),0,0,0,0,0);
    uint64_t renderer=call(0x22d90,q(ctx),q(ctx+0x18),0,0,0,0,0,0);float fov=ff(call(0x273e0,q(ctx),renderer,d(event+0x40),0,0,0,0,0));
    if(q(image+0x2fc910)){
        float fov_scale=df(f(image+0x1536d4),fov),depth_scale=f(image+0x1536e0),one=f(image+0x1536e8),height=f(image+0x153710),half=f(image+0x153700),pad=f(image+0x153714);
        double lift=g(image+0x1536d8),center_scale=g(image+0x1536f0),left_padding=g(image+0x1536f8);uint64_t index=0;
        do{
            uint8_t *row=image+0x2fc920+160*index;double previous[3],current[3],position[3],camera_position[3],relative[3];float screen[2],inverse;
            memcpy(previous,row,24);memcpy(current,row+0x18,24);recovered_vector_lerp_9460(position,previous,current,(double)f(event+0x40));position[1]+=lift;
            memcpy(camera_position,event+8,24);recovered_vector_subtract_93d0(relative,position,camera_position);
            if(!(uint8_t)recovered_screen_project_295f0(event+8,relative,screen,&inverse,image))goto next;
            call(method(image,0x150cc0),0,0,0,0,0,0,0,0);call(method(image,0x150cd8),fb(screen[0]),fb(screen[1]),fb(mf(inverse,depth_scale)),0,0,0,0,0);
            float factor=mf(inverse,f(image+0x1536e4));if(image[0x2f0530])factor=maxf(factor,one);
            float size=mf(mf(f(image+0x2f0510),fov_scale),factor);call(method(image,0x150cd0),fb(size),fb(size),fb(size),0,0,0,0,0);
            int32_t negative_width=_mm_cvtsi128_si32(_mm_sub_epi32(_mm_setzero_si128(),_mm_cvtsi32_si128((int32_t)d(row+0x40))));
            double left=_mm_cvtsd_f64(_mm_cvtsi32_sd(_mm_setzero_pd(),negative_width))*center_scale+left_padding;
            if(event[0x44]==1)call(0x27760,q(ctx),0,0,0,0,0,0,0);else call(method(image,0x13e450),0xb71,0,0,0,0,0,0,0);
            float left_x=narrow(left);
            if(image[0x2f0550]==1){
                if(event[0x44]==1){call(0x27820,q(ctx),0,0,0,0,0,0,0);call(0x278f0,q(ctx),0,0,0,0x3f000000,0,0,0);}
                else{call(method(image,0x13e450),0xde1,0,0,0,0,0,0,0);call(method(image,0x13e448),0,0,0,fb(half),0,0,0,0);}
                float right_x=narrow((double)(int32_t)d(row+0x40)*center_scale+g(image+0x153708));
                call(method(image,0x150c98),5,0,0,0,0,0,0,0);uint64_t vertex_holder=q(image+0x150ce0);
                call(target(vertex_holder),fb(left_x),0,0,0,0,0,0,0);call(target(vertex_holder),fb(right_x),0,0,0,0,0,0,0);
                call(target(vertex_holder),fb(left_x),fb(height),0,0,0,0,0,0);call(target(vertex_holder),fb(right_x),fb(height),0,0,0,0,0,0);
                call(method(image,0x150ca8),0,0,0,0,0,0,0,0);depth_scale=f(image+0x1536e0);
            }
            if(event[0x44]==1){call(0x277f0,q(ctx),0,0,0,0,0,0,0);call(0x278f0,q(ctx),fb(one),fb(one),fb(one),0x3f800000,0,0,0);}
            else{call(method(image,0x13e458),0xde1,0,0,0,0,0,0,0);call(method(image,0x150ca0),fb(one),fb(one),fb(one),0,0,0,0,0);}
            left_x=af(left_x,pad);call(0x27590,q(ctx),font,q(row+0x38),fb(left_x),0xc1200000,0xffffffff,image[0x2f0570],0);
            if(image[0x2f0590]==1){
                if(event[0x44]==1)call(0x27730,q(ctx),0,0,0,0,0,0,0);else call(method(image,0x13e458),0xb71,0,0,0,0,0,0,0);
                call(0x27c90,q(ctx),0,0,0,0,0,0,0);call(method(image,0x150cd0),fb(one),fb(one),d(image+0x153718),0,0,0,0,0);
                uint32_t x=0u-(d(row+0x4c)<<3);
                for(unsigned slot=0;slot<5;++slot){
                    if(row[0x50+16*slot]!=1)continue;uint64_t item=call(0x24050,q(ctx),q(row+0x30),slot,0,0,0,0,0);if(!item)continue;
                    call(0x27ba0,q(ctx),q(image+0x3007a0),font,texture,item,x,0xffffffe0,0);
                    call(0x27c10,q(ctx),q(image+0x3007a0),font,texture,item,x,0xffffffe0,0);x+=16;
                }
                call(0x27cc0,q(ctx),0,0,0,0,0,0,0);
                if(event[0x44]){call(0x27790,q(ctx),0,0,0,0,0,0,0);call(0x27880,q(ctx),0,0,0,0,0,0,0);call(0x278b0,q(ctx),0x302,0x303,0,0,0,0,0);}
                else{call(method(image,0x13e458),0xbe2,0,0,0,0,0,0,0);call(method(image,0x13e450),0xbc0,0,0,0,0,0,0,0);call(method(image,0x13e438),0x302,0x303,0,0,0,0,0,0);}
                call(method(image,0x150ca0),fb(one),fb(one),fb(one),0,0,0,0,0);call(method(image,0x150cd0),fb(half),fb(half),fb(half),0,0,0,0,0);
                if(image[0x2f05b0]==1){
                    uint32_t x=0u-(d(row+0x4c)<<3);
                    for(unsigned slot=0;slot<5;++slot){
                        uint8_t *equipment=row+0x50+16*slot;if(*equipment!=1)continue;
                        if(q(equipment+8) && (int32_t)d(equipment+4)>0){
                            float label_x=(float)(int32_t)(x+x);uint32_t y=0xffffffc0;uint64_t i=0;
                            do{uint64_t label=q((void *)(uintptr_t)(q(equipment+8)+8*i));call(0x27590,q(ctx),font,label,fb(label_x),fb((float)(int32_t)y),0xffffffff,1,0);++i;y+=8;}while((int64_t)i<(int64_t)(int32_t)d(equipment+4));
                        }
                        x+=16;
                    }
                }
            }
            call(method(image,0x150cb8),0,0,0,0,0,0,0,0);
next:       ++index;
        }while(index<q(image+0x2fc910));
    }
    if(event[0x44]){call(0x27820,q(ctx),0,0,0,0,0,0,0);call(0x27760,q(ctx),0,0,0,0,0,0,0);}
    else{uint64_t holder=q(image+0x13e450);call(target(holder),0xde1,0,0,0,0,0,0,0);call(target(holder),0xb71,0,0,0,0,0,0,0);}
    call(0x27b70,q(ctx),q(image+0x3007a0),fb(saved_depth),0,0,0,0,0);
}
