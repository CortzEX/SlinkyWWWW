#include <stdint.h>
#include <string.h>
#include <emmintrin.h>

typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t u64(const void *p){return *(const volatile uint64_t *)p;}
static uint32_t u32(const void *p){return *(const volatile uint32_t *)p;}
static float f32(const void *p){uint32_t b=u32(p);float v;memcpy(&v,&b,4);return v;}
static uint32_t fb(float v){uint32_t b;memcpy(&b,&v,4);return b;}
static uint64_t db(double v){uint64_t b;memcpy(&b,&v,8);return b;}
static double fd(uint64_t b){double v;memcpy(&v,&b,8);return v;}
static void put32(void *p,uint32_t v){*(volatile uint32_t *)p=v;}
static uint32_t rounded_count(uint8_t *image,uint32_t setting,dependency call){
    float value=f32(image+setting);
    int64_t whole=_mm_cvttss_si64(_mm_set_ss(value));
    float fraction=value-(float)(uint64_t)(uint32_t)whole;
    return (uint32_t)whole+(uint8_t)call(0xa460,fb(fraction),0,0,0,0);
}

__declspec(dllexport) void recovered_hit_select_update(uint8_t *event,uint8_t *image,dependency call){
    image[0x2fc538]=0;
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    uint32_t count=0;
    if(ctx[0x40]==1 && (uint32_t)call(0x239f0,u64(ctx),u64(ctx+0x28),0,0,0)==0)
        count=u32(image+0x2fc53c)+1u;
    put32(image+0x2fc53c,count);
}

__declspec(dllexport) void recovered_hit_select_input(uint8_t *event,uint8_t *image,dependency call){
    if(event[0x10]!=1) return;
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    if(image[0x2fc538]==1){
        if(!image[0x2fc540]) return;
        goto cancel;
    }
    if(image[0x2ee830]==1 && !(uint8_t)call(0x23690,u64(ctx),u64(ctx+0x28),0,0,0)) goto allow;
    if(image[0x2ee850]==1 && !(uint8_t)call(0x380b0,u64(ctx),u64(ctx+0x28),0,0,0)) goto allow;
    uint64_t target=call(0x22e10,u64(ctx),u64(ctx+0x18),0,0,0);
    uint8_t missing_target=1;
    if(target){
        uint32_t kind=(uint32_t)call(0x24b50,u64(ctx),target,0,0,0);
        if(kind==1) goto allow;
        if(kind==0 && (uint8_t)call(0xa460,u32(image+0x2ee730),0,0,0,0)) goto always_cancel;
        if(kind==2) missing_target=call(0x24e30,u64(ctx),target,0,0,0)==0;
    }
    uint32_t threshold=rounded_count(image,0x2ee768,call);
    uint8_t ground=(uint8_t)call(0x23780,u64(ctx),u64(ctx+0x28),0,0,0);
    uint8_t rising=1;
    if(ground){
        double velocity[3];
        call(0x23550,(uintptr_t)velocity,u64(ctx),u64(ctx+0x28),0,0);
        rising=velocity[1]>0.0;
    }
    uint8_t *state=(uint8_t *)(uintptr_t)u64(ctx+0x38);
    rising&=state[0x18];
    uint32_t mode=u32(image+0x2ee8a0);
    if(mode==0){
        if(rising) goto allow;
        if(u32(image+0x2fc544)<15) put32(image+0x2fc548,0);
        else if(!missing_target){
            uint32_t count=u32(image+0x2fc548)+1u;
            put32(image+0x2fc548,count);
            if(count<=rounded_count(image,0x2ee7a0,call)) goto always_cancel;
        }
        if(u32(image+0x2fc53c)<=9) threshold+=rounded_count(image,0x2ee7d8,call);
        if(image[0x2fc54c]==1){image[0x2fc54c]=0;goto allow;}
    } else if(mode==1){
        uint8_t window=(uint8_t)((u32(image+0x2fc544)-9u)<0xfffffff9u);
        window|=image[0x2ee8c8];
        uint8_t descending=0;
        if(!ground){
            uint32_t b=(uint32_t)call(0x237e0,u64(ctx),u64(ctx+0x28),0,0,0);
            descending=f32(&b)>0.0f;
            if(descending&window) goto allow;
        }
        if(rising && (!(window&rising) || image[0x2ee8e8]!=0)) goto allow;
        double position[3];
        call(0x23030,(uintptr_t)position,u64(ctx),u64(ctx+0x28),0,0);
        if((uint8_t)call(0x23020,u64(ctx),0,0,0,0)){
            double copy[3],output[3]; memcpy(copy,position,24);
            call(0x95c0,(uintptr_t)output,(uintptr_t)copy,0,0,0);
            memcpy(position,output,24);
        }
        uint32_t coords[3];
        for(unsigned i=0;i<3;i++) coords[i]=(uint32_t)_mm_cvttsd_si32(_mm_set_sd(fd(call(0xb29b0,db(position[i]),0,0,0,0))));
        uint64_t block=call(0x24690,u64(ctx),u64(ctx+0x20),coords[0],coords[1],coords[2]);
        if((uint32_t)call(0x24280,u64(ctx),block,0,0,0)!=0) goto allow;
        if(!(ground|descending)){
            if(image[0x2ee908]!=1 || (uint32_t)call(0x239f0,u64(ctx),u64(ctx+0x28),0,0,0)!=0) goto always_cancel;
        }
    } else goto allow;
    if(threshold<=u32(image+0x2fc544)+1u) goto allow;
    image[0x2fc540]=(uint8_t)call(0xa460,u32(image+0x2ee810),0,0,0,0);
    image[0x2fc538]=1;
    if(!image[0x2fc540]) return;
    goto cancel;
always_cancel:
    image[0x2fc540]=1;
    image[0x2fc538]=1;
cancel:
    event[0x11]=1;
    if(image[0x2ee928]==1){
        uint64_t entity=u64(ctx+0x28);
        if(entity && !(uint8_t)call(0x23f90,u64(ctx),entity,0,0,0))
            call(0x23bb0,u64(ctx),u64(ctx+0x28),0,0,0);
    }
    return;
allow:
    image[0x2fc540]=0;
    image[0x2fc538]=1;
}

__declspec(dllexport) void recovered_hit_select_target(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    uint8_t *state=(uint8_t *)(uintptr_t)u64(ctx+0x38);
    uint64_t target=u64(state+8);
    if(image[0x2ee8c8]==1){
        if(target && (uint32_t)call(0x239f0,u64(ctx),target,0,0,0)==10){
            put32(image+0x2fc544,0); image[0x2fc54c]=1;
        } else put32(image+0x2fc544,u32(image+0x2fc544)+1u);
        return;
    }
    uint32_t id=target?(uint32_t)call(0x23720,u64(ctx),target,0,0,0):0;
    if(id==u32(image+0x2fc550)){
        uint32_t count=u32(image+0x2fc544)+1u;
        put32(image+0x2fc544,count);
        if(count<10) return;
    } else {put32(image+0x2fc550,id);put32(image+0x2fc544,1001);}
    uint32_t current=(uint32_t)call(0x23760,u64(ctx),u64(ctx+0x28),0,0,0);
    uint32_t previous=(uint32_t)call(0x239d0,u64(ctx),u64(ctx+0x28),0,0,0);
    if(current==previous) put32(image+0x2fc544,0);
}
