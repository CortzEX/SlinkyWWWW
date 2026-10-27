#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*Endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
double *recovered_vector_subtract_93d0(double*,const double*,const double*);
static uint64_t q(const void*p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void*p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void*p){float v;memcpy(&v,p,4);return v;}
static double dbl(const void*p){double v;memcpy(&v,p,8);return v;}
static uint64_t db(double v){uint64_t u;memcpy(&u,&v,8);return u;}
static uint32_t fb(float v){uint32_t u;memcpy(&u,&v,4);return u;}
static uint8_t*ptr(uint64_t v){return (uint8_t*)(uintptr_t)v;}
static uint64_t target(uint8_t*im,uint32_t slot){return q(ptr(q(im+slot)));}
__declspec(dllexport) void recovered_block_esp_3f7b0(uint8_t*event,uint8_t*image,Endpoint call){
 if(!q(image+0x3020f0))return;
 uint8_t*enable=ptr(q(image+0x14fd08));call(q(enable),0x8074,0,0,0);call(q(enable),0x8076,0,0,0);
 call(target(image,0x150cb0),d(image+0x2f19e8),0,0,0);
 float amount=_mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(f(image+0x2f1a20)),_mm_set_ss(f(image+0x154158))));
 int64_t first=_mm_cvttss_si64(_mm_set_ss(amount));
 float shifted=_mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(amount),_mm_set_ss(f(image+0x15415c))));
 int64_t second=_mm_cvttss_si64(_mm_set_ss(shifted));
 uint64_t limit=image[0x2f1a78]?((uint64_t)first|((uint64_t)second&(first<0?UINT64_MAX:0))):0x1000;
 uint64_t count=q(image+0x3020f0);
 if(count){
  double scale=dbl(image+0x154150),cx=dbl(event+8)*scale,cz=scale*dbl(event+0x18);
  uint8_t*entries=ptr(q(image+0x302100));float radius=f(image+0x2f1a58);
  double midpoint=dbl(image+0x154160);uint8_t*pop=ptr(q(image+0x150cb8));
  for(uint64_t index=0,off=0;index<count;index++,off+=0x50){
   double x=cx-((double)(int32_t)d(entries+off)+midpoint);
   double z=cz-((double)(int32_t)d(entries+off+4)+midpoint);
   uint64_t result=call(0x13cfd0,db(x),db(z),0,0);double distance;memcpy(&distance,&result,8);
   if(distance>(double)radius)continue;
   call(target(image,0x150cc0),0,0,0,0);
   double position[3]={(double)(int32_t)(d(entries+off)<<4),0.,(double)(int32_t)(d(entries+off+4)<<4)};
   double camera[3],relative[3];memcpy(camera,event+8,24);recovered_vector_subtract_93d0(relative,position,camera);
   call(target(image,0x150cd8),fb((float)relative[0]),fb((float)relative[1]),fb((float)relative[2]),0);
   call(target(image,0x14fd10),3,0x1406,0x10,q(entries+off+0x30));
   call(target(image,0x154310),3,0x1401,0x10,q(entries+off+0x30)+12);
   uint64_t vertices=q(entries+off+0x38);call(target(image,0x14fd00),1,vertices>limit?limit:vertices,0x1403,q(entries+off+0x48));
   call(q(pop),0,0,0,0);
   entries=ptr(q(image+0x302100));radius=f(image+0x2f1a58);count=q(image+0x3020f0);
  }
 }
 uint8_t*disable=ptr(q(image+0x14fcf8));call(q(disable),0x8074,0,0,0);call(q(disable),0x8076,0,0,0);
}
