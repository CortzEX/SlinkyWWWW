#include "auto_soup.h"
#include <string.h>

#define ENABLED 0x2f7d68
#define STATE 0x2f7d6c
#define FLAG 0x2f7d70
#define ITEM_ID 0x2f7d74
#define ITEM_KIND 0x2f7d78
#define HAS_TARGET 0x2f7d7c
#define SELECTED 0x2f7d7d
#define TIMER 0x2f7d80
#define ITEM_FILTER 0x2f7db8
#define DESC 0x2e96b0
#define F32(x) fbits((float)(x))

static uint8_t get8(const uint8_t *p,uint32_t o){return p[o];}
static uint32_t get32(const uint8_t *p,uint32_t o){uint32_t v;memcpy(&v,p+o,4);return v;}
static uint64_t get64(const uint8_t *p,uint32_t o){uint64_t v;memcpy(&v,p+o,8);return v;}
static void put8(uint8_t *p,uint32_t o,uint8_t v){p[o]=v;}
static void put32(uint8_t *p,uint32_t o,uint32_t v){memcpy(p+o,&v,4);}
static float getf(const uint8_t *p,uint32_t o){float v;memcpy(&v,p+o,4);return v;}
static void putf(uint8_t *p,uint32_t o,float v){memcpy(p+o,&v,4);}
static uint64_t fbits(float v){uint32_t b;memcpy(&b,&v,4);return b;}
static void invoke(soup_dispatch call,void *user,uint32_t rva,
    uint64_t rcx,uint64_t rdx,uint64_t r8,uint64_t r9,
    uint64_t xmm0,uint64_t xmm1,uint64_t xmm2,soup_result *out)
{
    soup_args a={rcx,rdx,r8,r9,xmm0,xmm1,xmm2,0};out->rax=0;out->xmm0=0;
    call(rva,&a,out,user);
}
static void invoke_vtable(soup_dispatch call,void *user,uint64_t target,
    uint64_t rcx,uint64_t rdx,uint64_t r8,soup_result *out)
{
    soup_args a={rcx,rdx,r8,0,0,0,0,target};
    out->rax=0;out->xmm0=0;call(0x70000000,&a,out,user);
}
static uint64_t image_address(uint8_t *image,uint32_t offset){return (uint64_t)(uintptr_t)(image+offset);}
static float random_add(uint8_t *image,soup_dispatch call,void *user,float scale)
{
    soup_result r;invoke(call,user,0x2dd50,0,0,0,0,F32(scale),0,0,&r);
    float value;uint32_t bits=(uint32_t)r.xmm0;memcpy(&value,&bits,4);return getf(image,TIMER)+value;
}
static void post_action(uint8_t *image,soup_dispatch call,void *user)
{
    soup_result r;put32(image,STATE,5);
    if(get32(image,ITEM_ID)!=get32(image,ITEM_KIND)){
        putf(image,TIMER,random_add(image,call,user,getf(image,0x2e9998)));
        if(getf(image,TIMER)<=0.0f)putf(image,TIMER,getf(image,TIMER)+*(float *)(image+0x1505a8));
    }
}
static uint64_t query_player(const uint8_t *ctx){return get64(ctx,0);}
static uint64_t query_second(const uint8_t *ctx,uint32_t off){return get64(ctx,off);}

void recovered_auto_soup_2d510(uint8_t *event,uint8_t *image,soup_dispatch call,void *user)
{
    uint8_t *ctx=(uint8_t *)(uintptr_t)get64(event,8);
    uint32_t state=get32(image,STATE);
    if(get8(image,ENABLED)==1&&(state==6||state==0)){
        soup_result r;invoke(call,user,0x284f0,get64(ctx,8),image_address(image,DESC),0,0,0,0,0,&r);return;
    }
    if(get8(ctx,0x40)!=1){put8(image,FLAG,0);put32(image,STATE,0);return;}
    for(uint32_t pass=0;pass<3;pass++){
        float timer=getf(image,TIMER);
        if(timer>0.0f){timer+=*(float *)(image+0x1505c0);putf(image,TIMER,timer);return;}
        state=get32(image,STATE);
        soup_result r;
        switch(state){
        case 0:{
            invoke(call,user,0x23a40,query_player(ctx),query_second(ctx,0x28),0,0,0,0,0,&r);
            float value=*(float *)&r.xmm0;
            if(value>getf(image,0x2e98f0))return;
            putf(image,TIMER,random_add(image,call,user,getf(image,0x2e9928)));
            put8(image,HAS_TARGET,(uint8_t)(value<=getf(image,0x2e9960)));
            put32(image,STATE,1);break;
        }
        case 4:{
            invoke(call,user,0x22cf0,query_player(ctx),query_second(ctx,0x18),0,0,0,0,0,&r);
            uint64_t v=r.rax;invoke(call,user,0x24fe0,query_player(ctx),v,0,0,0,0,0,&r);v=r.rax;
            invoke(call,user,0x25380,query_player(ctx),v,0,0,0,0,0,&r);
            post_action(image,call,user);
            break;
        }
        case 2:{
            invoke(call,user,0x2aa80,image_address(image,DESC),0,0,0,0,0,0,&r);
            if((uint8_t)r.rax==0){put32(image,STATE,0);return;}
            invoke(call,user,0x23f40,query_player(ctx),query_second(ctx,0x28),0,0,0,0,0,&r);uint64_t inv=r.rax;
            invoke(call,user,0x25a80,query_player(ctx),inv,get32(image,ITEM_ID),0,0,0,0,&r);
            put32(image,STATE,3);
            putf(image,TIMER,random_add(image,call,user,getf(image,0x2e9998)));
            invoke(call,user,0x23f90,query_player(ctx),query_second(ctx,0x28),0,0,0,0,0,&r);
            if((uint8_t)r.rax!=0&&getf(image,TIMER)<=0.0f)
                putf(image,TIMER,getf(image,TIMER)+*(float *)(image+0x1505a8));
            break;
        }
        case 3:{
            invoke(call,user,0x22cf0,query_player(ctx),query_second(ctx,0x18),0,0,0,0,0,&r);uint64_t v=r.rax;
            invoke(call,user,0x24f90,query_player(ctx),v,0,0,0,0,0,&r);v=r.rax;
            invoke(call,user,0x25380,query_player(ctx),v,0,0,0,0,0,&r);
            if(get8(image,0x2e9a48)==1&&get8(image,SELECTED)!=0){
                put32(image,STATE,4);
                float t=random_add(image,call,user,getf(image,0x2e9998));
                if(t<=0.0f)t+=*(float *)(image+0x1505a8);
                putf(image,TIMER,t);
            }else post_action(image,call,user);
            break;
        }
        case 1:{
            invoke(call,user,0x23f40,query_player(ctx),query_second(ctx,0x28),0,0,0,0,0,&r);uint64_t inv=r.rax;
            uint8_t skip_current=get8(image,FLAG);
            invoke(call,user,0x25a60,query_player(ctx),inv,0,0,0,0,0,&r);int32_t start=(int32_t)(uint32_t)r.rax;
            invoke(call,user,0x25ab0,query_player(ctx),inv,0,0,0,0,0,&r);uint64_t stack=r.rax;
            int32_t selected=-1;int32_t candidate=-1;uint32_t kind=0;
            for(int32_t i=0;i<9;i++){
                uint32_t wrapped=(uint32_t)start+(uint32_t)i;int32_t signed_wrapped=(int32_t)wrapped;
                int32_t rem=signed_wrapped%9;
                candidate=rem;
                if(candidate==start&&(skip_current&1))continue;
                uint64_t item=0;
                uint64_t game=query_player(ctx),endpoint_object=get64((const uint8_t *)(uintptr_t)game,8);
                uint64_t endpoint_vtable=get64((const uint8_t *)(uintptr_t)endpoint_object,0);
                uint64_t target=get64((const uint8_t *)(uintptr_t)endpoint_vtable,0x568);
                invoke_vtable(call,user,target,endpoint_object,stack,(uint32_t)candidate,&r);item=r.rax;
                if(item){invoke(call,user,0x25d10,game,item,0,0,0,0,0,&r);
                    invoke(call,user,0x25c50,game,r.rax,0,0,0,0,0,&r);kind=(uint32_t)r.rax;
                }else kind=0;
                uint8_t filtered=get8(image,0x2e9a28)==1;
                if(filtered){invoke(call,user,0x2ac60,image_address(image,ITEM_FILTER),kind,0,0,0,0,0,&r);
                    if((uint8_t)r.rax==0)continue;
                }else if(kind!=0x19d&&kind!=0x11a)continue;
                {
                    put8(image,SELECTED,(uint8_t)(kind==0x19d||kind==0x11a));
                    invoke(call,user,0xa050,0,0,0,0,F32(getf(image,0x1505ac)),
                        F32(getf(image,0x1505b0)),0,&r);
                    invoke(call,user,0xaa30,image_address(image,0x2f7da8),r.rax,0,0,0,
                        0,get64(image,0x1505b8),&r);
                    selected=candidate;if((uint8_t)r.rax==0)break;
                }
            }
            if(selected==-1){uint8_t flag=get8(image,FLAG);put32(image,STATE,6-flag);put8(image,FLAG,0);return;}
            put32(image,ITEM_ID,(uint32_t)selected);
            uint32_t current;
            if(get8(image,FLAG)==1)current=get32(image,ITEM_KIND);
            else {invoke(call,user,0x25a60,query_player(ctx),inv,0,0,0,0,0,&r);current=(uint32_t)r.rax;put32(image,ITEM_KIND,current);}
            uint32_t selected_after_reload=get32(image,ITEM_ID);
            put8(image,FLAG,0);put32(image,STATE,(selected_after_reload==current)+2);break;
        }
        case 5:{
            invoke(call,user,0x2aab0,image_address(image,DESC),0,0,0,0,0,0,&r);
            if(get8(image,HAS_TARGET)==1){put8(image,HAS_TARGET,0);put8(image,FLAG,1);put32(image,STATE,1);}
            else {
                invoke(call,user,0x23f40,query_player(ctx),query_second(ctx,0x28),0,0,0,0,0,&r);uint64_t inv=r.rax;
                invoke(call,user,0x25a80,query_player(ctx),inv,get32(image,ITEM_KIND),0,0,0,0,&r);put32(image,STATE,6);
            }
            break;
        }
        case 6:{
            put8(image,FLAG,0);putf(image,TIMER,random_add(image,call,user,getf(image,0x2e99d0)));put32(image,STATE,0);break;
        }
        default:return;
        }
    }
}

void recovered_auto_soup_2dae0(uint8_t *event,uint8_t *image)
{
    if(get64(event,8)!=(uint64_t)(uintptr_t)(image+DESC))return;
    uint32_t state=get32(image,STATE);if(state==0||state==6)return;
    put8(event,0x10,1);put8(image,ENABLED,1);
}
void recovered_auto_soup_2db10(uint8_t *event,uint8_t *image)
{
    if(get64(event,0x10)!=(uint64_t)(uintptr_t)(image+DESC)||get8(event,0x18)!=1)return;
    put32(image,STATE,0);put8(image,FLAG,0);putf(image,TIMER,0.0f);put8(image,ENABLED,0);
}
