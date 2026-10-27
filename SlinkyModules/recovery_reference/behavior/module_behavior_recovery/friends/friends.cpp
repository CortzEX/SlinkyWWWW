#include <stdint.h>
#include <string.h>

typedef uint64_t (*friends_helper)(uint32_t id, uint64_t rcx, uint64_t rdx,
    uint64_t r8, uint64_t r9, uint64_t stack5);

static uint64_t invoke(friends_helper h,uint32_t id,uint64_t a,uint64_t b,
                       uint64_t c,uint64_t d,uint64_t e)
{ return h(id,a,b,c,d,e); }
static uint8_t al(uint64_t x){return (uint8_t)x;}

/* Registered event callback at RVA 0x3b3c0. */
__declspec(dllexport) void recovered_friends_scan(void *event,uint8_t *image,
    uint64_t virtual_base,friends_helper h)
{
    uint8_t *ctx=(uint8_t *)(uintptr_t)*(uint64_t *)((uint8_t *)event+8);
    if(!*(uint64_t *)(ctx+0x28))return;
    uint64_t temporary=invoke(h,0x13d0d0,0,0,0,0,0);
    uint64_t game=*(uint64_t *)ctx;
    uint64_t iterator=invoke(h,0x24600,game,*(uint64_t *)(ctx+0x20),0,0,0);
    game=*(uint64_t *)ctx;
    int32_t count=(int32_t)invoke(h,0x24e50,game,iterator,0,0,0);
    for(uint32_t i=0;(int32_t)i<count;i++){
        game=*(uint64_t *)ctx;
        uint64_t entity=invoke(h,0x24e80,game,iterator,i,0,0);
        game=*(uint64_t *)ctx;
        uint64_t target=*(uint64_t *)(ctx+0x28);
        uint64_t api_interface=*(uint64_t *)(uintptr_t)(game+8);
        uint64_t api_vtable=*(uint64_t *)(uintptr_t)api_interface;
        uint64_t predicate_target=*(uint64_t *)(uintptr_t)(api_vtable+0xc0);
        uint64_t allowed=invoke(h,0x10000c0,predicate_target,api_interface,target,entity,0);
        if(!al(allowed)){
            game=*(uint64_t *)ctx;
            uint64_t uuid=invoke(h,0x23740,game,entity,0,0,0);
            game=*(uint64_t *)ctx;
            uint64_t high=invoke(h,0x27dc0,game,uuid,0,0,0);
            game=*(uint64_t *)ctx;
            uint64_t low=invoke(h,0x27d90,game,uuid,0,0,0);
            uint64_t key[4]={high,low,0,0};
            uint64_t found=invoke(h,0xdf00,*(uint64_t *)(image+0x2fc8c0),0x20,
                virtual_base+0x2fc8c8,(uint64_t)(uintptr_t)key,
                virtual_base+0x3b380);
            game=*(uint64_t *)ctx;
            if(!found)invoke(h,0x2ad80,game,entity,4,0,0);
            else{
                invoke(h,0x2ad20,game,entity,4,0,0);
                *(uint64_t *)(uintptr_t)(found+0x10)=temporary;
            }
        }
        game=*(uint64_t *)ctx;
        count=(int32_t)invoke(h,0x24e50,game,iterator,0,0,0);
        if((int32_t)(i+1)>=count)break;
    }
}

/* Registered event callback at RVA 0x3b510. */
__declspec(dllexport) void recovered_friends_prune(void *event,
    uint64_t virtual_base,friends_helper h)
{
    uint8_t *ev=(uint8_t *)event;
    if(*(uint64_t *)(ev+0x10)!=virtual_base+0x2f0038 || ev[0x18]!=0)return;
    uint8_t *ctx=(uint8_t *)(uintptr_t)*(uint64_t *)(ev+8);
    uint64_t list=*(uint64_t *)(ctx+0x20);
    if(!list)return;
    uint64_t game=*(uint64_t *)ctx;
    uint64_t iterator=invoke(h,0x24600,game,list,0,0,0);
    game=*(uint64_t *)ctx;
    int32_t count=(int32_t)invoke(h,0x24e50,game,iterator,0,0,0);
    for(uint32_t i=0;(int32_t)i<count;i++){
        game=*(uint64_t *)ctx;
        uint64_t entity=invoke(h,0x24e80,game,iterator,i,0,0);
        game=*(uint64_t *)ctx;
        uint64_t target=*(uint64_t *)(ctx+0x28);
        uint64_t api_interface=*(uint64_t *)(uintptr_t)(game+8);
        uint64_t api_vtable=*(uint64_t *)(uintptr_t)api_interface;
        uint64_t predicate_target=*(uint64_t *)(uintptr_t)(api_vtable+0xc0);
        if(!al(invoke(h,0x10000c0,predicate_target,api_interface,target,entity,0)))
            invoke(h,0x2ad80,*(uint64_t *)ctx,entity,4,0,0);
        game=*(uint64_t *)ctx;
        count=(int32_t)invoke(h,0x24e50,game,iterator,0,0,0);
        if((int32_t)(i+1)>=count)break;
    }
}

/* Registered unload callback at RVA 0x3b5d0. */
__declspec(dllexport) void recovered_friends_clear(uint8_t *image,
    friends_helper h)
{
    invoke(h,0x13cf70,*(uint64_t *)(image+0x2fc8c0),0,0,0,0);
    memset(image+0x2fc8c0,0,16);
}

/* Direct consumer at RVA 0x8bd0. The native image retains pointer slots at
   their original RVAs; helper-dependent JNI and module actions stay injected. */
__declspec(dllexport) uint32_t recovered_friends_query(uint32_t *request,
    uint8_t *image,uint64_t virtual_base,friends_helper h)
{
    uint8_t result_flag=1;
    if(request[0]==2){
        uint8_t *bits=(uint8_t *)(uintptr_t)*(uint64_t *)(image+0x2f7218);
        uint8_t old=bits[request[1]];
        uint8_t bit=old&1,requested=*(uint8_t *)((uint8_t *)request+12);
        if(*((uint8_t *)request+13)==1){
            if(bit==requested)goto bit_done;
            requested=(uint8_t)((requested|(old&2))^2);
        }
        bits[request[1]]=requested;
        result_flag=(uint8_t)(bit==*(uint8_t *)((uint8_t *)request+12));
    }
bit_done:
    {
        uint64_t env_object=*(uint64_t *)(image+0x2f6ee0);
        uint64_t env_vtable=*(uint64_t *)(uintptr_t)env_object;
        uint64_t jni_target=*(uint64_t *)(uintptr_t)(env_vtable+0x30);
        uint64_t env=0;
        uint32_t status=(uint32_t)invoke(h,0x10000030,jni_target,env_object,
            (uint64_t)(uintptr_t)&env,0x10008,0);
        if(status!=0)return 0;
        uint64_t global_env=*(uint64_t *)(image+0x2f6ef0);
        uint64_t pair[2]={global_env,env};
        uint32_t result=(uint32_t)invoke(h,0x324d0,
            (uint64_t)(uintptr_t)request,result_flag,
            virtual_base+0x2f6f08,0,0);
        if((uint8_t)result!=0)return result;
        if(request[0]!=2 || result_flag!=0 || request[1]==0)return result;
        uint64_t current=invoke(h,0x22c00,(uint64_t)(uintptr_t)pair,0,0,0,0);
        if(!al(invoke(h,0x22e60,(uint64_t)(uintptr_t)pair,current,0,0,0)))return result;
        uint64_t *ghost=(uint64_t *)(image+0x13e498);
        uint64_t *friends=(uint64_t *)(image+0x13e490);
        if(*(uint8_t *)(uintptr_t)(*ghost+0x14)!=0)return result;
        if(*(uint8_t *)(uintptr_t)(*friends+0x14)==1 && request[0]==2 &&
           *((uint8_t *)request+12)==1 && request[1]==3)
            invoke(h,0x3b200,(uint64_t)(uintptr_t)pair,
                   virtual_base+0x2f6f08,0,0,0);
        if(!al(invoke(h,0xe870,*(uint64_t *)(image+0x2f7230),request[1],
                      *((uint8_t *)request+12),0,0)))
            invoke(h,0xe870,*(uint64_t *)(image+0x2f7238),request[1],
                   *((uint8_t *)request+12),0,0);
        return result;
    }
}
