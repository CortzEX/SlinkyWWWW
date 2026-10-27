#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <math.h>

typedef uint64_t (*dispatch_fn)(uintptr_t,uint32_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
typedef struct { uintptr_t game; uint8_t gap08[0x10]; uintptr_t key; uintptr_t state_arg; uintptr_t target;
                 uint8_t gap30[0x10]; uint8_t enabled; } ToolContext;
typedef struct { uintptr_t unused; volatile ToolContext *context; } ToolEvent;
enum { SELECTED=0x2ee368, LAST_INDEX=0x2ee36c, GROUP_A=0x2ee3c0, GROUP_B=0x2ee3e0,
       GROUP_C=0x2ee400, GROUP_DEFAULT=0x2ee420, ACTION_GATE=0x2ee440,
       MATCH_GATE=0x2ee460, SWITCH_BACK=0x2ee480, RESET_DELAY=0x2ee3a0,
       COOLDOWN=0x2fc520, SLOT_FILTER=0x2fc528, MIN_SCORE=0x152420 };
enum { H_23F40=0x23f40,H_25A60=0x25a60,H_28A50=0x28a50,H_25C50=0x25c50,
       H_22CF0=0x22cf0,H_23F90=0x23f90,H_25270=0x25270,H_25490=0x25490,
       H_25030=0x25030,H_25430=0x25430,H_22E10=0x22e10,H_24B50=0x24b50,
       H_24C10=0x24c10,H_24690=0x24690,H_24280=0x24280,H_2AC60=0x2ac60,
       H_26140=0x26140,H_25D40=0x25d40,H_2AA80=0x2aa80,H_25A80=0x25a80,
       H_2AAB0=0x2aab0,H_13CF70=0x13cf70 };

static uint32_t read32(const volatile uint8_t *p,uint32_t rva){uint32_t v;memcpy(&v,(const void *)(p+rva),4);return v;}
static uint64_t read64(const volatile uint8_t *p,uint32_t rva){uint64_t v;memcpy(&v,(const void *)(p+rva),8);return v;}
static void write32(volatile uint8_t *p,uint32_t rva,uint32_t v){memcpy((void *)(p+rva),&v,4);}
static int32_t signed32(uint32_t v){int32_t s;memcpy(&s,&v,4);return s;}
static float float32(uint32_t v){float f;memcpy(&f,&v,4);return f;}
static int32_t cvttsd2si(double v){if(isnan(v)||v>=2147483648.0||v< -2147483648.0)return INT32_MIN;return (int32_t)v;}
static int32_t cvttss2si(float v){if(isnan(v)||v>=2147483648.0f||v< -2147483648.0f)return INT32_MIN;return (int32_t)v;}
static uint64_t call(dispatch_fn f,uintptr_t state,uint32_t id,uint64_t a,uint64_t b,uint64_t c,uint64_t d,uint64_t e){return f(state,id,a,b,c,d,e);}
static int type_group(uint32_t item_type,uint8_t g_a,uint8_t g_b,uint8_t g_c,uint8_t g_default){
    uint32_t index=item_type-0x100u;
    if(index>0x67u)return g_default;
    switch(index){
    case 0x00:case 0x01:case 0x02:case 0x0d:case 0x0e:case 0x0f:
    case 0x11:case 0x12:case 0x13:case 0x15:case 0x16:case 0x17:
    case 0x1c:case 0x1d:case 0x1e:case 0x67:return g_c;
    case 0x0b:case 0x0c:case 0x10:case 0x14:case 0x1b:return g_b;
    default:return g_default;
    }
}

__declspec(dllexport) void recovered_auto_tool(uintptr_t event_address,volatile uint8_t *image,
    uintptr_t state,dispatch_fn invoke){
    volatile ToolEvent *event=(volatile ToolEvent *)event_address;
    volatile ToolContext *ctx=event->context;
    if(ctx->enabled!=1)return;
    uint64_t item=call(invoke,state,H_23F40,ctx->game,ctx->target,0,0,0);
    int32_t current=signed32((uint32_t)call(invoke,state,H_25A60,ctx->game,item,0,0,0));
    int32_t selected=signed32(read32(image,SELECTED));
    if(selected!=-1&&signed32(read32(image,LAST_INDEX))!=current){write32(image,SELECTED,UINT32_MAX);goto restore;}
    if(selected==-1){
        uint64_t held=call(invoke,state,H_28A50,ctx->game,ctx->target,0,0,0);
        uint8_t choice=image[GROUP_A];
        if(held){uint32_t item_type=(uint32_t)call(invoke,state,H_25C50,ctx->game,held,0,0,0);
            choice=(uint8_t)type_group(item_type,image[GROUP_A],image[GROUP_B],image[GROUP_C],image[GROUP_DEFAULT]);}
        if(choice!=1)goto failed;
    }

    uint64_t bridge=call(invoke,state,H_22CF0,ctx->game,ctx->key,0,0,0);
    if((uint8_t)call(invoke,state,H_23F90,ctx->game,ctx->target,0,0,0)!=0)goto failed;
    uint64_t active=call(invoke,state,H_25270,ctx->game,bridge,0,0,0);
    if((uint8_t)call(invoke,state,H_25490,ctx->game,active,0,0,0)==0)goto failed;
    if(image[ACTION_GATE]==1){
        uint64_t action=call(invoke,state,H_25030,ctx->game,bridge,0,0,0);
        if((uint8_t)call(invoke,state,H_25430,ctx->game,action,0,0,0)==0)goto failed;
    }
    uint64_t entity=call(invoke,state,H_22E10,ctx->game,ctx->key,0,0,0);
    if(!entity||(int32_t)call(invoke,state,H_24B50,ctx->game,entity,0,0,0)!=1)goto failed;
    double coordinates[3];
    call(invoke,state,H_24C10,(uintptr_t)coordinates,ctx->game,entity,0,0);
    int32_t x=cvttsd2si(coordinates[0]),y=cvttsd2si(coordinates[1]),z=cvttsd2si(coordinates[2]);
    uint64_t slot=call(invoke,state,H_24690,ctx->game,ctx->state_arg,(uint32_t)x,(uint32_t)y,(uint32_t)z);
    if(!slot)goto failed;
    if(image[MATCH_GATE]==1){
        uint32_t type=(uint32_t)call(invoke,state,H_24280,ctx->game,slot,0,0,0);
        if((uint8_t)call(invoke,state,H_2AC60,(uintptr_t)(image+SLOT_FILTER),type,0,0,0)==0)goto failed;
    }
    if(signed32(read32(image,COOLDOWN))>=1){write32(image,COOLDOWN,read32(image,COOLDOWN)-1);goto restore;}

    uintptr_t scan_game=ctx->game;
    float best=float32(read32(image,MIN_SCORE));
    int32_t best_index=current;
    for(int32_t offset=0;offset<9;offset++){
        int32_t sum=signed32((uint32_t)current+(uint32_t)offset);
        int32_t index=(int32_t)((int64_t)sum-(int64_t)(sum/9)*9);
        uint64_t candidate=call(invoke,state,H_26140,scan_game,item,(uint32_t)index,0,0);
        if(candidate){
            float score=float32((uint32_t)call(invoke,state,H_25D40,scan_game,candidate,slot,0,0));
            if(!isnan(score)&&!isnan(best)&&score>best){best=score;best_index=index;}
        }
    }
    if(best_index==current)return;
    uint8_t locked=(uint8_t)call(invoke,state,H_2AA80,(uintptr_t)(image+0x2ee158),0,0,0,0);
    if(locked){
        call(invoke,state,H_25A80,ctx->game,item,(uint32_t)best_index,0,0);
        write32(image,LAST_INDEX,(uint32_t)best_index);
        if(signed32(read32(image,SELECTED))==-1&&image[SWITCH_BACK]!=0)write32(image,SELECTED,(uint32_t)current);
    }
    if(best_index!=-1)return;
    goto restore;

failed:
    write32(image,COOLDOWN,(uint32_t)cvttss2si(float32(read32(image,RESET_DELAY))));
restore:
    call(invoke,state,H_2AAB0,(uintptr_t)(image+0x2ee158),0,0,0,0);
    if(signed32(read32(image,SELECTED))!=-1){
        uint32_t saved_index=read32(image,SELECTED);
        call(invoke,state,H_25A80,ctx->game,item,saved_index,0,0);
        write32(image,SELECTED,UINT32_MAX);
    }
}

__declspec(dllexport) void recovered_auto_tool_reset(volatile uint8_t *image,uintptr_t state,dispatch_fn invoke){
    uint64_t saved=read64(image,SLOT_FILTER);
    call(invoke,state,H_13CF70,saved,0,0,0,0);
    memset((void *)(image+SLOT_FILTER),0,16);
}
