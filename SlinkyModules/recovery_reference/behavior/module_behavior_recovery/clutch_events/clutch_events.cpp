#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
#define API __declspec(dllexport)
typedef uint64_t (*Dispatch)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void*p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void*p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void*p){float v;memcpy(&v,p,4);return v;}
static uint64_t p(const void*v){return (uint64_t)(uintptr_t)v;}
API void recovered_clutch_488f0(uint8_t*event,uint8_t*image,Dispatch call){
 float time=f(image+0x304a18);
 if(time>0){
  time=_mm_cvtss_f32(_mm_add_ss(_mm_set_ss(time),_mm_set_ss(f(image+0x156070))));
  memcpy(image+0x304a18,&time,4);if(time>0)return;
 }
 float step=_mm_cvtss_f32(_mm_div_ss(_mm_set_ss(f(image+0x156074)),_mm_set_ss(f(image+0x2f57c0))));
 time=_mm_cvtss_f32(_mm_add_ss(_mm_set_ss(step),_mm_set_ss(time)));memcpy(image+0x304a18,&time,4);
 uint8_t*ctx=(uint8_t*)(uintptr_t)q(event+8);
 if(ctx[0x40]!=1||!image[0x304a1c])return;
 uint64_t target=call(0x22e10,q(ctx),q(ctx+0x18),0,0);if(!target)return;
 if((uint32_t)call(0x24b50,q(ctx),target,0,0)!=1)return;
 uint32_t block[3];call(0x24ce0,p(block),q(ctx),target,0);
 if(block[0]!=d(image+0x304a20)||block[1]!=d(image+0x304a24)||block[2]!=d(image+0x304a28))return;
 uint8_t side=(uint32_t)call(0x24b90,q(ctx),target,0,0)!=1;
 if(image[0x304a2c]==side)return;
 uint64_t settings=call(0x22cf0,q(ctx),q(ctx+0x18),0,0);
 uint64_t key=call(0x24f90,q(ctx),settings,0,0);call(0x25380,q(ctx),key,0,0);
 double hit[3];call(0x24d80,p(hit),q(ctx),target,0);
 uint32_t converted[3];for(unsigned i=0;i<3;i++)converted[i]=(uint32_t)_mm_cvttsd_si32(_mm_set_sd(hit[i]));
 memcpy(image+0x304a20,converted,12);
}
API void recovered_clutch_48a30(uint8_t*event,uint8_t*image,Dispatch call){
 (void)call;if(image[0x304a2d]==1){event[8]=1;event[9]=1;}
}
