#include <stdint.h>
#include <string.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t u64(const void *p){return *(const volatile uint64_t *)p;}
static uint32_t u32(const void *p){return *(const volatile uint32_t *)p;}
static int32_t s32(uint32_t b){int32_t v;memcpy(&v,&b,4);return v;}
static float f32(uint32_t b){float v;memcpy(&v,&b,4);return v;}
static uint32_t fb(float v){uint32_t b;memcpy(&b,&v,4);return b;}
static void put32(void *p,uint32_t v){*(volatile uint32_t *)p=v;}

__declspec(dllexport) void recovered_bridge_update(uint8_t *event,uint8_t *image,dependency call){
    image[0x2f7dd0]=0;image[0x2f7dd1]=0;
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    if(ctx[0x40]!=1) return;
    uint64_t settings=call(0x22cf0,u64(ctx),u64(ctx+0x18),0,0);
    uint32_t cooldown=u32(image+0x2f7dcc);
    if(s32(cooldown)>0) put32(image+0x2f7dcc,cooldown-1);
    uint64_t key=call(0x25030,u64(ctx),settings,0,0);
    uint32_t pressed=(uint32_t)call(0x25490,u64(ctx),key,0,0);
    if(image[0x2e9ce8]!=(uint8_t)pressed) goto reject;
    uint64_t game=u64(ctx),player=u64(ctx+0x28);
    if(image[0x2e9d08]==1){
        uint64_t angle=call(0x23170,game,player,0,0);
        if(f32(u32(image+0x1507c0))>f32((uint32_t)(angle>>32))) goto reject;
    }
    if(image[0x2e9d28]==1){
        float vertical=f32((uint32_t)call(0x23ac0,game,player,0,0));
        if(vertical>0.) goto reject;
    }
    image[0x2f7dd1]=u32(image+0x2e9d78)!=0;
    if(image[0x2e9da0]==1){
        uint64_t block=call(0x28a50,game,player,0,0);
        uint8_t held=(uint8_t)call(0x28b00,game,block,0,0);
        uint32_t ticks=2;
        if(!held){
            ticks=u32(image+0x2f7dd8);
            if(s32(ticks)<=0) goto reject;
            --ticks;
        }
        put32(image+0x2f7dd8,ticks);
    }
    image[0x2f7dc8]=1;
    uint8_t down=(uint8_t)call(0x25430,u64(ctx),key,0,0);
    game=u64(ctx);uint64_t world=u64(ctx+0x20);player=u64(ctx+0x28);
    if(!down){
        if(!(uint8_t)call(0x23780,game,player,0,0)){
            if(image[0x2e9dc0]!=1) return;
            double velocity[3];call(0x23550,(uintptr_t)velocity,game,player,0);
            if(0.>velocity[1]) return;
        }
        if(!(uint8_t)call(0x2e7b0,game,settings,world,player)) return;
        call(0x25460,u64(ctx),key,1,0);
        goto finish_flag;
    }
    if(image[0x2e9ce8]==1){
        float vertical=f32((uint32_t)call(0x23ac0,game,player,0,0));
        if(vertical>=0.) goto finish_flag;
        if(s32(u32(image+0x2f7dcc))<=0) goto finish_flag;
    }else if(!(uint8_t)call(0x23780,game,player,0,0)){
        if(image[0x2e9dc0]!=1) goto countdown;
        double velocity[3];call(0x23550,(uintptr_t)velocity,game,player,0);
        if(0.>velocity[1]) goto countdown;
    }
    if((uint8_t)call(0x2e7b0,game,settings,world,player)) goto finish_flag;
countdown:
    {
        float timer=f32(u32(image+0x2f7dd4))+f32(u32(image+0x1507c4));
        put32(image+0x2f7dd4,fb(timer));
        if(timer>0.) goto finish_flag;
    }
    call(0x25460,u64(ctx),key,0,0);
    float next=f32(u32(image+0x2e9e70));
    if(image[0x2e9e18]==1){
        uint64_t random=call(0xa050,u32(image+0x1507c8),u32(image+0x1507cc),0,0);
        next+=f32((uint32_t)call(0xa510,(uintptr_t)(image+0x2f7df0),random,u64(image+0x1507d0),0));
        random=call(0xa050,u32(image+0x1507d8),u32(image+0x1507dc),0,0);
        if((uint8_t)call(0xaa30,(uintptr_t)(image+0x2f7e00),random,u64(image+0x1507e0),0)){
            random=call(0xa050,0,u32(image+0x1507e8),0,0);
            next+=f32((uint32_t)call(0xa3e0,random,0,0,0));
        }
    }
    next+=f32(u32(image+0x2f7dd4));
    put32(image+0x2f7dd4,fb(next));return;
finish_flag:
    image[0x2f7dd0]=image[0x2e9e38];return;
reject:
    if(image[0x2f7dc8]==1) call(0x25460,u64(ctx),key,pressed,0);
    image[0x2f7dc8]=0;
}
