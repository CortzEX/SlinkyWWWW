#include <stdint.h>
#include <string.h>
#define API __declspec(dllexport)
typedef uint64_t (*Dispatch)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void*p){uint64_t v;memcpy(&v,p,8);return v;}
static uint8_t*ptr(uint64_t v){return (uint8_t*)(uintptr_t)v;}
static void w(void*p,uint64_t v){memcpy(p,&v,8);}
static void clear_collection(uint8_t*image,Dispatch call){
 if(q(image+0x3020f0))for(uint64_t n=0,off=0;;off+=0x50){
  uint8_t*entry=ptr(q(image+0x302100))+off;
  memset(entry+8,0,16);call(0x13cf70,q(entry+0x18),0,0,0);
  memset(entry+0x18,0,16);memset(entry+0x28,0,8);
  call(0x13cf70,q(entry+0x30),0,0,0);
  memset(entry+0x30,0,16);memset(entry+0x40,0,8);
  call(0x13cf70,q(entry+0x48),0,0,0);memset(entry+0x48,0,8);
  if(++n>=q(image+0x3020f0))break;
 }
 memset(image+0x3020f0,0,16);call(0x13cf70,q(image+0x302100),0,0,0);memset(image+0x302100,0,8);
}
API void recovered_block_esp_3f4c0(uint8_t*event,uint8_t*image,Dispatch call){
 uint8_t*ctx=ptr(q(event+8));
 if(ctx[0x40]==1&&image[0x2f19b0]){
  if(q(image+0x3020f0))for(uint64_t n=0,off=0;;off+=0x50){
   call(0x3fcc0,q(image+0x302100)+off,0,0,0);
   if(++n>=q(image+0x3020f0))break;
  }
  image[0x2f19b0]=0;
 }
 uint64_t world=q(ctx+0x20);
 if(world){
  call(0x26060,q(ctx),world,0,0);if(image[0x302108]!=1)return;
  clear_collection(image,call);call(0x3fed0,(uint64_t)(uintptr_t)ctx,0,0,0);image[0x302108]=0;
 }else clear_collection(image,call);
}
API void recovered_block_esp_3f6a0(uint8_t*event,uint8_t*image,Dispatch call){
 if(q(event+0x10)!=(uint64_t)(uintptr_t)(image+0x2f1740))return;
 if(event[0x18]){
  uint8_t*ctx=ptr(q(event+8));uint32_t kind;memcpy(&kind,ptr(q(ptr(q(ctx)))),4);
  w(image+0x302128,(uint64_t)(uintptr_t)(image+(kind?0x40af0:0x40980)));
  if(q(ctx+0x20))call(0x3fed0,(uint64_t)(uintptr_t)ctx,0,0,0);
 }else clear_collection(image,call);
}
API void recovered_block_esp_3fa40(uint8_t*event,uint8_t*image,Dispatch call){
 (void)image;call(0x40420,(uint64_t)(uintptr_t)(event+8),0,0,0);
}
API void recovered_block_esp_3fa50(uint8_t*event,uint8_t*image,Dispatch call){
 (void)event;memset(image+0x302110,0,16);call(0x13cf70,q(image+0x302120),0,0,0);memset(image+0x302120,0,8);
 clear_collection(image,call);
}
