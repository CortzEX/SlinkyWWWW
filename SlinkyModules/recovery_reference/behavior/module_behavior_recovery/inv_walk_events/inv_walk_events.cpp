#include <stdint.h>
#include <string.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t u64(const void *p){return *(const volatile uint64_t *)p;}
static uint32_t u32(const void *p){return *(const volatile uint32_t *)p;}
static void put64(void *p,uint64_t v){*(volatile uint64_t *)p=v;}
static void put32(void *p,uint32_t v){*(volatile uint32_t *)p=v;}
static uint64_t method(uint64_t env,unsigned slot){return u64((void *)(uintptr_t)(u64((void *)(uintptr_t)env)+slot));}

__declspec(dllexport) uint8_t recovered_inv_walk_flush(uint64_t game,uint64_t world,uint8_t *image,dependency call){
    if(!u64(image+0x2fc780)) return 0;
    uint64_t env=u64((void *)(uintptr_t)(game+8));
    uint64_t object=call(0x22d10,game,world,0,0);
    uint64_t destination=call(0x25ed0,game,object,0,0);
    uint8_t valid=object!=0 && destination!=0;
    uint64_t count=u64(image+0x2fc780);
    if(count){
        uint64_t index=0;
        do{
            uint64_t packet=u64(image+0x2fc680+index*8);
            if(valid) call(0x25f80,game,destination,packet,0);
            call(0x800000b0,env,packet,method(env,0xb0),0);
            ++index;
        }while(index<u64(image+0x2fc780));
    }
    put64(image+0x2fc780,0);
    return valid;
}

__declspec(dllexport) void recovered_inv_walk_disable(uint8_t *event,uint8_t *image,dependency call){
    if(event[0x18]!=0 || u64(event+0x10)!=(uintptr_t)(image+0x2ef3d0)) return;
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    recovered_inv_walk_flush(u64(ctx),u64(ctx+0x18),image,call);
}

__declspec(dllexport) void recovered_inv_walk_packet(uint8_t *event,uint8_t *image,dependency call){
    if(u32(image+0x2ef620)!=1) return;
    uint64_t packet=call(0x26f00,u64(event+8),u64(event+0x18),0,0);
    uint64_t game=u64(event+8),count;
    if(packet){
        if((uint32_t)call(0x26fb0,game,packet,0,0)==2){
            event[0x20]=1;put32(image+0x2fc790,2);
        }
        return;
    }
    packet=call(0x26ec0,game,u64(event+0x18),0,0);
    if(packet){
        if(u32(image+0x2fc790)==2){
            uint64_t object=call(0x26f40,u64(event+8),0,0,0);
            uint64_t action=call(0x26f70,u64(event+8),object,0,0);
            call(0x25f80,u64(event+8),u64(event+0x10),action,0);
            put32(image+0x2fc790,3);image[0x2fc798]=1;
            count=u64(image+0x2fc780);
        }else{
            count=u64(image+0x2fc780);
            if(!(((count!=0)|image[0x2fc798])&1)){
                put32(image+0x2fc794,u32(image+0x2fc78c));return;
            }
        }
    }else{
        packet=call(0x26ff0,u64(event+8),u64(event+0x18),0,0);
        if(!packet) return;
        if(u32(image+0x2fc790)==2) goto cancel;
        count=u64(image+0x2fc780);
        if(!count) return;
    }
    if(count==32) goto cancel;
    game=u64(event+8);
    uint64_t env=u64((void *)(uintptr_t)(game+8));
    uint64_t retained=call(0x800000a8,env,u64(event+0x18),method(env,0xa8),0);
    if(retained){
        count=u64(image+0x2fc780);
        put64(image+0x2fc680+count*8,retained);
        put64(image+0x2fc780,count+1);
    }
cancel:
    event[0x20]=1;
}

__declspec(dllexport) void recovered_inv_walk_finish(uint8_t *event,uint8_t *image,dependency call){
    if(image[0x2fc798]) return;
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    if(!recovered_inv_walk_flush(u64(ctx),u64(ctx+0x18),image,call)) return;
    put32(image+0x2fc794,u32(image+0x2fc78c));
    if(ctx[0x40]!=1) return;
    while((uint8_t)call(0x25900,u64(ctx),0,0,0)){}
    while((uint8_t)call(0x257a0,u64(ctx),0,0,0)){}
}
