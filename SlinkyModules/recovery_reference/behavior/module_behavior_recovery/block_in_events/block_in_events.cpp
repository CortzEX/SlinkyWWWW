#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
#define API extern "C" __declspec(dllexport)
typedef uint64_t (*Dispatch)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void*p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void*p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void*p){float v;memcpy(&v,p,4);return v;}
static uint8_t*ptr(uint64_t v){return (uint8_t*)(uintptr_t)v;}
static void collect(uint8_t*ctx,uint64_t keys[4],Dispatch call){
 uint64_t settings=call(0x22cf0,q(ctx),q(ctx+0x18),0,0);
 keys[0]=call(0x250d0,q(ctx),settings,0,0);
 keys[1]=call(0x25120,q(ctx),settings,0,0);
 keys[2]=call(0x25170,q(ctx),settings,0,0);
 keys[3]=call(0x251c0,q(ctx),settings,0,0);
}
API void recovered_block_in_4abf0(uint8_t*event,uint8_t*image,Dispatch call){(void)event;(void)image;(void)call;}
API void recovered_block_in_4ac00(uint8_t*event,uint8_t*image,Dispatch call){
 if(q(event+0x10)!=(uint64_t)(uintptr_t)(image+0x2f6108))return;
 uint8_t*ctx=ptr(q(event+8));
 if(event[0x18]==1){
  memset(image+0x304b10,0,8);
  uint32_t angle=(uint32_t)call(0x23170,q(ctx),q(ctx+0x28),0,0);
  float value;memcpy(&value,&angle,4);
  value=_mm_cvtss_f32(_mm_div_ss(_mm_set_ss(value),_mm_set_ss(f(image+0x156870))));
  uint32_t bits;memcpy(&bits,&value,4);bits=(uint32_t)call(0xb1fb0,bits,0,0,0);memcpy(&value,&bits,4);
  uint32_t n=(uint32_t)_mm_cvttss_si32(_mm_set_ss(value));
  uint32_t aligned=((n&0x80000000u)?n+3:n)&~3u;
  n-=aligned;memcpy(image+0x304b18,&n,4);return;
 }
 uint64_t keys[4];collect(ctx,keys,call);
 for(unsigned i=0;i<4;i++){
  uint64_t game=q(ctx);uint32_t pressed=(uint32_t)call(0x25490,game,keys[i],0,0);
  call(0x25460,game,keys[i],pressed,0);
 }
}
API void recovered_block_in_4ad50(uint8_t*event,uint8_t*image,Dispatch call){
 (void)call;if(image[0x304b1c]!=1)return;
 event[8]=1;event[9]=1;
 if(d(image+0x304b20)==1)memcpy(event+0xc,image+0x304b28,8);
}
API void recovered_block_in_4ad80(uint8_t*event,uint8_t*image,Dispatch call){
 if(!d(image+0x304b20))return;
 uint8_t*ctx=ptr(q(event+8));uint64_t keys[4];collect(ctx,keys,call);
 call(0x25460,q(ctx),keys[0],d(image+0x304b20)==1,0);
 for(unsigned i=1;i<4;i++)call(0x25460,q(ctx),keys[i],0,0);
}
