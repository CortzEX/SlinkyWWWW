#include <stdint.h>
#include <stdlib.h>
#include "../random_primitives/random_primitives.h"
typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
typedef uint64_t (*ab_dispatch)(void *,uint32_t,uint64_t,uint64_t,uint64_t,uint64_t,uint32_t,uint64_t);
typedef uint32_t (*post_r8)(void);
typedef struct {uint8_t *image;endpoint call;post_r8 r8;} frame;
extern uint64_t recovered_access_239f0(uint8_t *,uint64_t,uint32_t,endpoint);
extern uint64_t recovered_access_23720(uint8_t *,uint64_t,uint32_t,endpoint);
extern uint64_t recovered_access_23760(uint8_t *,uint64_t,uint32_t,endpoint);
extern uint64_t recovered_access_239d0(uint8_t *,uint64_t,uint32_t,endpoint);
extern uint64_t recovered_access_22cf0(uint8_t *,uint64_t,uint32_t,endpoint);
extern uint64_t recovered_access_23f90(uint8_t *,uint64_t,endpoint);
extern uint64_t recovered_action_24020(uint8_t *,uint64_t,uint32_t,endpoint);
extern uint64_t recovered_access_24f90(uint8_t *,uint64_t,endpoint);
extern uint64_t recovered_access_25380(uint8_t *,uint64_t,endpoint);
extern uint64_t recovered_access_25460(uint8_t *,uint64_t,uint32_t,endpoint);
extern uint64_t recovered_access_25490(uint8_t *,uint64_t,uint32_t,endpoint);
extern uint64_t recovered_access_25760(uint8_t *,uint32_t,endpoint);
extern uint64_t recovered_access_258c0(uint8_t *,uint32_t,endpoint);
extern uint64_t recovered_held_item_28a50(uint8_t *,uint64_t,endpoint);
extern uint32_t recovered_item_classification_28ac0(uint8_t *,uint64_t,endpoint);
extern uint8_t recovered_timer_range_query(uint8_t *);
static __declspec(thread) frame *active;
static uint32_t connected_external_r8(void){return active->r8();}
static uint64_t external(uint64_t target,uint64_t a,uint64_t b,uint64_t c,uint64_t d){
 if(target==UINT64_C(0x180025760))return recovered_access_25760((void *)(uintptr_t)a,(uint32_t)b,external);
 if(target==UINT64_C(0x1800258c0))return recovered_access_258c0((void *)(uintptr_t)a,(uint32_t)b,external);
 return active->call(target,a,b,c,d);
}
static uint64_t dispatch(void *opaque,uint32_t r,uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint32_t x0,uint64_t x1){
 (void)d;(void)x1;frame *s=opaque;uint8_t *g=(void *)(uintptr_t)a;
 switch(r){
 case 0xa460:return recovered_a460(s->image,x0);
 case 0x42c30:return recovered_timer_range_query(s->image);
 case 0x239f0:return recovered_access_239f0(g,b,0,external);
 case 0x23720:return recovered_access_23720(g,b,0,external);
 case 0x23760:return recovered_access_23760(g,b,0,external);
 case 0x239d0:return recovered_access_239d0(g,b,0,external);
 case 0x22cf0:return recovered_access_22cf0(g,b,0,external);
 case 0x23f90:return recovered_access_23f90(g,b,external);
 case 0x24020:return recovered_action_24020(g,b,(uint32_t)c,external);
 case 0x24f90:return recovered_access_24f90(g,b,external);
 case 0x25380:return recovered_access_25380(g,b,external);
 case 0x25460:return recovered_access_25460(g,b,(uint32_t)c,external);
 case 0x25490:return recovered_access_25490(g,b,0,external);
 case 0x28a50:return recovered_held_item_28a50(g,b,external);
 case 0x28ac0:return recovered_item_classification_28ac0(g,b,external);
 default:abort();
 }
}
#define RETURN_ENTRY(rva) \
 extern uint64_t linked_auto_block_##rva(uint8_t *,uint8_t *,ab_dispatch,void *); \
 __declspec(dllexport) uint64_t connected_auto_block_##rva(uint8_t *event,uint8_t *image,endpoint call,post_r8 residue){ \
 frame local={image,call,residue},*previous=active;active=&local; \
 uint64_t result=linked_auto_block_##rva(event,image,dispatch,&local);active=previous;return result; }
#define VOID_ENTRY(rva) \
 extern void linked_auto_block_##rva(uint8_t *,uint8_t *,ab_dispatch,void *); \
 __declspec(dllexport) void connected_auto_block_##rva(uint8_t *event,uint8_t *image,endpoint call,post_r8 residue){ \
 frame local={image,call,residue},*previous=active;active=&local; \
 linked_auto_block_##rva(event,image,dispatch,&local);active=previous; }
RETURN_ENTRY(31570)
RETURN_ENTRY(31a70)
VOID_ENTRY(31b00)
VOID_ENTRY(31b60)
extern void linked_auto_block_31a50(uint8_t *,uint8_t *);
__declspec(dllexport) void connected_auto_block_31a50(uint8_t *event,uint8_t *image,endpoint unused,post_r8 residue){(void)unused;(void)residue;linked_auto_block_31a50(event,image);}

#include "auto_block_body.h"
