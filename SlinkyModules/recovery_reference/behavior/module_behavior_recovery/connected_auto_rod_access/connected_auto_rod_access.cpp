#include "auto_rod_corrected.c"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
typedef uint64_t (*rod_dispatch)(void *,uint32_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
typedef struct {uint8_t *image;endpoint call;} frame;
static __declspec(thread) frame *active;
extern void recovered_auto_rod_43d80(uint8_t *,uint8_t *,rod_dispatch,void *);
extern void recovered_auto_rod_44340(uint8_t *,uint8_t *);
extern void recovered_auto_rod_44390(uint8_t *,uint8_t *);
extern void recovered_auto_rod_443c0(uint8_t *,uint8_t *,rod_dispatch,void *);
extern uint64_t recovered_access_22e10(uint8_t *,uint64_t,endpoint);
extern uint64_t recovered_access_24b50(uint8_t *,uint64_t,endpoint);
extern uint64_t recovered_access_23f40(uint8_t *,uint64_t,uint32_t,endpoint);
extern uint64_t recovered_access_25a60(uint8_t *,uint64_t,uint32_t,endpoint);
extern uint64_t recovered_access_25a80(uint8_t *,uint64_t,uint32_t,endpoint);
extern uint64_t recovered_access_26140(uint8_t *,uint64_t,uint32_t,endpoint);
extern uint64_t recovered_access_25d10(uint8_t *,uint64_t,endpoint);
extern uint64_t recovered_access_25c50(uint8_t *,uint64_t,endpoint);
extern uint64_t recovered_access_22cf0(uint8_t *,uint64_t,uint32_t,endpoint);
extern uint64_t recovered_access_24f90(uint8_t *,uint64_t,endpoint);
extern uint64_t recovered_input_253e0(uint8_t *,uint64_t,uint32_t,endpoint);
extern uint64_t recovered_held_item_28a50(uint8_t *,uint64_t,endpoint);
extern uint8_t recovered_action_claim_2aa80(uint64_t,uint8_t *);
extern void recovered_action_release_2aab0(uint64_t,uint8_t *);
extern uint32_t recovered_registry_request_284f0(uint8_t *,uint8_t *,uint8_t,uint64_t,endpoint);
extern uint32_t connected_weapon_selection_380c0(uint8_t *,uint64_t,uint8_t *,endpoint);
extern float recovered_rod_delay_445a0(uint8_t *);
extern uint32_t recovered_rod_travel_44660(uint8_t *,uint8_t *,endpoint);
extern float recovered_rod_interval_44860(uint8_t *);
static uint32_t bits(float v){uint32_t b;memcpy(&b,&v,4);return b;}
static uint64_t registry_endpoint(uint64_t target,uint64_t a,uint64_t b,uint64_t c,uint64_t d){
 if(target==UINT64_C(0x180044340)){recovered_auto_rod_44340((void *)(uintptr_t)a,active->image);return 0;}
 return active->call(target,a,b,c,d);
}
static uint64_t dispatch(void *opaque,uint32_t rva,uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t e){
 (void)d;(void)e;frame *s=opaque;uint8_t *game=(void *)(uintptr_t)a;
 switch(rva){
 case 0x22e10:return recovered_access_22e10(game,b,s->call);
 case 0x24b50:return recovered_access_24b50(game,b,s->call);
 case 0x23f40:return recovered_access_23f40(game,b,0,s->call);
 case 0x25a60:return recovered_access_25a60(game,b,0,s->call);
 case 0x25a80:return recovered_access_25a80(game,b,(uint32_t)c,s->call);
 case 0x26140:return recovered_access_26140(game,b,(uint32_t)c,s->call);
 case 0x25d10:return recovered_access_25d10(game,b,s->call);
 case 0x25c50:return recovered_access_25c50(game,b,s->call);
 case 0x22cf0:return recovered_access_22cf0(game,b,0,s->call);
 case 0x24f90:return recovered_access_24f90(game,b,s->call);
 case 0x253e0:return recovered_input_253e0(game,b,(uint32_t)c,s->call);
 case 0x28a50:return recovered_held_item_28a50(game,b,s->call);
 case 0x2aa80:return recovered_action_claim_2aa80(a,s->image);
 case 0x2aab0:recovered_action_release_2aab0(a,s->image);return 0;
 case 0x284f0:return recovered_registry_request_284f0(game,(void *)(uintptr_t)b,(uint8_t)c,0,registry_endpoint);
 case 0x380c0:return connected_weapon_selection_380c0(game,b,s->image,s->call);
 case 0x445a0:return bits(recovered_rod_delay_445a0(s->image));
 case 0x44660:return recovered_rod_travel_44660(game,s->image,s->call);
 case 0x44860:return bits(recovered_rod_interval_44860(s->image));
 default:abort();
 }
}
__declspec(dllexport) void connected_auto_rod_access(uint8_t *event,uint8_t *image,uint32_t rva,endpoint call){
 frame local={image,call},*previous=active;active=&local;
 switch(rva){
 case 0x43d80:recovered_auto_rod_43d80(event,image,dispatch,&local);break;
 case 0x44340:recovered_auto_rod_44340(event,image);break;
 case 0x44390:recovered_auto_rod_44390(event,image);break;
 case 0x443c0:recovered_auto_rod_443c0(event,image,dispatch,&local);break;
 default:abort();
 }
 active=previous;
}
