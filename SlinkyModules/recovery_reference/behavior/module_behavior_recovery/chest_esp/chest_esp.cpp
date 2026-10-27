#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static uint32_t fb(float v){return d(&v);}
static void wq(void *p,uint64_t v){memcpy(p,&v,8);}
static void wd(void *p,uint32_t v){memcpy(p,&v,4);}
static uint64_t method(uint8_t *image,uint32_t slot){return q((void *)(uintptr_t)q(image+slot));}
static float narrow(double v){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(v)));}
double recovered_vector_distance_squared(const double *,const double *);
double *recovered_vector_subtract_93d0(double *,const double *,const double *);
void *recovered_geometry_add_9400(double *,const double *,const double *);

__declspec(dllexport) void recovered_chest_esp_33990(uint8_t *event,uint8_t *image,endpoint call){
    wq(image+0x2fa360,0);
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);if(!q(ctx+0x20))return;
    double self[3];call(0x23030,(uintptr_t)self,q(ctx),q(ctx+0x28),0);
    uint64_t list=call(0x24640,q(ctx),q(ctx+0x20),0,0);
    if((int32_t)call(0x24e50,q(ctx),list,0,0)<=0)return;
    uint32_t index=0;
    do{
        uint64_t entry=call(0x24e80,q(ctx),list,index,0);
        uint64_t block=call(0x244f0,q(ctx),entry,0,0);
        if(block){
            uint32_t type=(uint32_t)call(0x24280,q(ctx),block,0,0);int enabled=0;
            switch(type){
            case 54:enabled=image[0x2ecb68]!=0;break;
            case 130:enabled=image[0x2ecb88]!=0;break;
            case 146:enabled=image[0x2ecba8]!=0;break;
            case 138:enabled=image[0x2ecbc8]==1;break;
            }
            if(enabled){
                double position[3],a[3],b[3];call(0x24510,(uintptr_t)position,q(ctx),entry,0);
                memcpy(a,position,24);memcpy(b,self,24);double distance=recovered_vector_distance_squared(a,b);
                float range=f(image+0x2ecb48);range=_mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(range),_mm_set_ss(range)));
                if(!(distance>(double)range)){
                    uint64_t old=q(image+0x2fa360),count=old+1;wq(image+0x2fa360,count);
                    uint8_t *slot=image+0x2fa370+(old<<5);memcpy(slot,position,24);wd(slot+24,type);
                    if(count==100)return;
                }
            }
        }
        index++;
    }while((int32_t)index<(int32_t)call(0x24e50,q(ctx),list,0,0));
}
__declspec(dllexport) void recovered_chest_esp_33b60(uint8_t *event,uint8_t *image,endpoint call){
    call(0x293c0,0,0,0,0);
    uint64_t width_method=method(image,0x150cb0);call(width_method,d(image+0x2ecc00),0,0,0);
    if(q(image+0x2fa360)){
        double adjustment[3];memcpy(adjustment,image+0x151ad0,16);adjustment[2]=.5;
        uint32_t scale=d(image+0x151a60),alpha=d(image+0x151a64);
        uint64_t index=0;uint8_t *entry=image+0x2fa370;
        do{
            uint32_t type=d(entry+24),color=type==130?0x2ecc10:type==138?0x2ecc50:type==146?0x2ecc30:0x2ecc70;
            double position[3],camera[3],relative[3],center[3];memcpy(position,entry,24);memcpy(camera,event+8,24);
            recovered_vector_subtract_93d0(relative,position,camera);recovered_geometry_add_9400(center,relative,adjustment);
            call(method(image,0x150cc0),0,0,0,0);
            call(method(image,0x150cd8),fb(narrow(center[0])),fb(narrow(center[1])),fb(narrow(center[2])),0);
            call(method(image,0x150cd0),scale,scale,scale,0);
            if(image[0x2ecca0]==1){
                call(method(image,0x13e448),d(image+color),d(image+color+4),d(image+color+8),alpha);
                call(0x29400,0,0,0,0);
            }
            call(method(image,0x150ca0),d(image+color),d(image+color+4),d(image+color+8),0);
            call(0x29430,0,0,0,0);call(method(image,0x150cb8),0,0,0,0);
            index++;entry+=32;
        }while(index<q(image+0x2fa360));
    }
    call(0x295a0,0,0,0,0);
}
