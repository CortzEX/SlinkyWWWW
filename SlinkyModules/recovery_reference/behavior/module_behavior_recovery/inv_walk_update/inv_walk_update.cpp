#include <stdint.h>
#include <intrin.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t u64(const void *p){return *(const volatile uint64_t *)p;}
static uint32_t u32(const void *p){return *(const volatile uint32_t *)p;}
static void put32(void *p,uint32_t v){*(volatile uint32_t *)p=v;}
static uint32_t delay(uint8_t *image){return (uint32_t)_mm_cvttss_si64(_mm_load_ss((const float *)(image+0x2ef6b8)));}

__declspec(dllexport) void recovered_inv_walk_update(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    uint64_t screen=call(0x22c90,u64(ctx),u64(ctx+0x18),0,0);
    uint64_t settings=call(0x22cf0,u64(ctx),u64(ctx+0x18),0,0);
    uint64_t keys[5];uint32_t pressed[5];
    keys[0]=call(0x25120,u64(ctx),settings,0,0);
    keys[1]=call(0x25170,u64(ctx),settings,0,0);
    keys[2]=call(0x251c0,u64(ctx),settings,0,0);
    keys[3]=call(0x250d0,u64(ctx),settings,0,0);
    keys[4]=call(0x25080,u64(ctx),settings,0,0);
    for(unsigned i=0;i<5;++i){
        uint32_t result=(uint32_t)call(0x25490,u64(ctx),keys[i],0,0);
        pressed[i]=i<2?result:(uint8_t)result;
    }
    uint32_t mode=u32(image+0x2ef678);
    uint8_t block=u32(image+0x2ef620)==1 && mode!=2 && u64(image+0x2fc780)!=0;
    uint8_t stop=(mode==0)&block,active;
    put32(image+0x2fc78c,u32(image+0x2fc78c)+1);
    if(!screen){
        if(u32(image+0x2fc790)){
            for(unsigned i=0;i<5;++i) call(0x25460,u64(ctx),keys[i],pressed[i],0);
        }
        put32(image+0x2fc790,0);
        if(ctx[0x40]==0) return;
        active=0;goto apply;
    }
    uint8_t moving=(uint8_t)(pressed[0]|pressed[1]|pressed[2]|pressed[3]|pressed[4]);
    uint8_t inventory_screen=(uint8_t)call(0x25b80,u64(ctx),screen,0,0);
    if(!inventory_screen){
        put32(image+0x2fc790,1);
        if(u32(image+0x2ef620)==1){
            block|=moving^1;
            mode=u32(image+0x2ef678);
            uint32_t recent=0;
            if(mode!=2) recent=(u32(image+0x2fc78c)-u32(image+0x2fc794))<delay(image);
            uint8_t blocked=block|(uint8_t)recent;
            uint32_t other=u32(image+0x2ef6f0);
            block=(other!=2)|blocked;
            if(((mode==0)&blocked) || ((other==0)&block)) goto zero_keys;
        }else if(stop) goto zero_keys;
        goto set_keys;
    }
    uint8_t deny;
    if(u32(image+0x2ef620)!=1){
        put32(image+0x2fc790,3);active=1;deny=0;goto options;
    }
    uint64_t inventory=call(0x23f40,u64(ctx),u64(ctx+0x28),0,0);
    uint64_t object=call(0x22d10,u64(ctx),u64(ctx+0x18),0,0);
    uint64_t destination=call(0x25ed0,u64(ctx),object,0,0);
    uint64_t held=call(0x25ad0,u64(ctx),inventory,0,0);
    deny=1;
    if(!held){
        if(u32(image+0x2fc790)==1) deny=block;
        else{
            uint64_t container=call(0x24080,u64(ctx),u64(ctx+0x28),0,0);
            uint64_t slots=call(0x26170,u64(ctx),container,0,0);
            unsigned i;
            for(i=0;i<4;++i) if(call(0x26140,u64(ctx),slots,i,0)) break;
            if(i==4) deny=block;
        }
    }
    uint8_t allowed=moving&(deny^1);
    uint32_t state=u32(image+0x2fc790);
    uint64_t action;
    if((state!=2)|allowed){
        if(((u64(image+0x2fc780)==0)&(state==3)&allowed)==1){
            if(u32(image+0x2ef678)!=2 && (u32(image+0x2fc78c)-u32(image+0x2fc794))<delay(image)) goto state_ready;
            action=call(0x27030,u64(ctx),0,0,0);state=2;goto send;
        }
    }else{
        object=call(0x26f40,u64(ctx),0,0,0);
        action=call(0x26f70,u64(ctx),object,0,0);state=3;
send:
        call(0x25f80,u64(ctx),destination,action,0);
        put32(image+0x2fc790,state);
    }
state_ready:
    deny|=state==3;active=state!=0;
options:
    mode=u32(image+0x2ef678);
    block|=(mode!=2)&deny;
    stop=(mode==0)&block;
apply:
    if((active|image[0x2fc788]|stop)&1){
        if(stop) goto zero_keys;
        goto set_keys;
    }
    goto finish;
set_keys:
    for(unsigned i=0;i<5;++i) call(0x25460,u64(ctx),keys[i],pressed[i],0);
    stop=0;goto finish;
zero_keys:
    for(unsigned i=0;i<5;++i) call(0x25460,u64(ctx),keys[i],0,0);
    stop=1;
finish:
    if(block){
        call(0x236c0,u64(ctx),u64(ctx+0x28),0,0);
        uint64_t game=u64(ctx);
        uint64_t key=call(0x25210,game,settings,0,0);
        call(0x25460,game,key,0,0);
    }
    image[0x2fc788]=stop;image[0x2fc798]=0;
}
