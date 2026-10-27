#include <stdint.h>
#include <string.h>
#include <intrin.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t u64(const void *p){return *(const volatile uint64_t *)p;}
static uint32_t u32(const void *p){return *(const volatile uint32_t *)p;}
static int32_t s32(uint32_t b){int32_t v;memcpy(&v,&b,4);return v;}
static double d64(uint64_t b){double v;memcpy(&v,&b,8);return v;}
static float f32(const void *p){uint32_t b=u32(p);float v;memcpy(&v,&b,4);return v;}
static void put32(void *p,uint32_t v){*(volatile uint32_t *)p=v;}
static void put64(void *p,uint64_t v){*(volatile uint64_t *)p=v;}
static void lock(uint8_t *image){while(_InterlockedExchange8((volatile char *)(image+0x2fc458),1)) _mm_pause();}
void *recovered_geometry_construct_93b0(void *,double,double,double);
void *recovered_geometry_add_9400(double *,const double *,const double *);

__declspec(dllexport) double *recovered_vector_adjust_95c0(double *out,const double *input,uint8_t *image){
    _mm_store_sd(out,_mm_load_sd(input));
    _mm_store_sd(out+1,_mm_add_sd(_mm_load_sd(input+1),_mm_load_sd((const double *)(image+0x13e858))));
    _mm_store_sd(out+2,_mm_load_sd(input+2));
    return out;
}

__declspec(dllexport) void recovered_backtrack_update(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    volatile uint8_t *state=image;
    uint32_t cooldown=u32(image+0x2fc4e0);
    if(s32(cooldown)>0){
        put32(image+0x2fc4e0,cooldown-1);
        if(cooldown!=1) return;
    }
    if(ctx[0x40]!=1) goto reject;
    if(state[0x2ede88]==1 && !(uint8_t)call(0x29080,(uintptr_t)ctx,0,0,0)) goto reject;
    if(state[0x2edea8]==1 && !(uint8_t)call(0x380b0,u64(ctx),u64(ctx+0x28),0,0)) goto reject;
    uint32_t previous=(uint32_t)call(0x239d0,u64(ctx),u64(ctx+0x28),0,0);
    uint32_t current=(uint32_t)call(0x23760,u64(ctx),u64(ctx+0x28),0,0);
    if(s32(current-previous)>20) goto reject;
    uint8_t *target=(uint8_t *)(uintptr_t)u64(ctx+0x38);
    uint64_t entity=u64(target+8);
    if(!entity) goto reject;
    uint32_t hurt=(uint32_t)call(0x239f0,u64(ctx),entity,0,0);
    if((float)s32(hurt)>f32(image+0x2edda8)) goto reject;
    float minimum=f32(image+0x2eddf0);minimum=minimum*minimum;
    double distance=d64(u64(target+0x10));
    if((double)minimum>distance) goto reject;
    float maximum=f32(image+0x2eddf4);maximum=maximum*maximum;
    if(distance>(double)maximum) goto reject;
    double self[3],position[3],candidate[3],copy[3];
    call(0x23030,(uintptr_t)self,u64(ctx),u64(ctx+0x28),0);
    if((uint8_t)call(0x23020,u64(ctx),0,0,0)){
        double adjusted[3];memcpy(copy,self,24);
        recovered_vector_adjust_95c0(adjusted,copy,image);
        memcpy(self,adjusted,24);
    }
    call(0x24160,(uintptr_t)position,u64(ctx),u64(target+8),0);
    uint64_t angles=call(0x23170,u64(ctx),u64(target+8),0,0);
    uint32_t target_id=(uint32_t)call(0x23720,u64(ctx),u64(target+8),0,0);
    uint32_t self_id=(uint32_t)call(0x23720,u64(ctx),u64(ctx+0x28),0,0);
    lock(image);
    int64_t limit=_mm_cvttss_si64(_mm_set_ss(f32(image+0x2ede30)));
    uint32_t old_id=u32(image+0x2fc468);
    put64(image+0x2fc460,(uint64_t)limit);
    put32(image+0x2fc468,target_id);put32(image+0x2fc46c,self_id);
    state[0x2fc471]=state[0x2edec8];
    if(state[0x2fc470]!=1){
        memcpy(copy,self,24);
        if(!(uint8_t)call(0x36f60,(uintptr_t)ctx,u64(target+8),(uintptr_t)copy,0)){
            state[0x2fc4a0]=0;goto unlock;
        }
        state[0x2fc470]=1;
        recovered_geometry_construct_93b0(copy,0.,0.,0.);
        memcpy(image+0x2fc478,copy,24);state[0x2fc490]=0;state[0x2fc498]=0;
        call(0x23030,(uintptr_t)copy,u64(ctx),u64(target+8),0);
        memcpy(image+0x2fc4a8,copy,24);memcpy(image+0x2fc4c0,copy,24);memcpy(image+0x2fc4e8,copy,24);
        put32(image+0x2fc4d8,(uint32_t)angles);put32(image+0x2fc4dc,(uint32_t)angles);put32(image+0x2fc500,(uint32_t)angles);
        state[0x2fc4a0]=state[0x2edee8];goto unlock;
    }
    if(state[0x2fc490]==1) memcpy(candidate,image+0x2fc478,24);
    else{
        double position_copy[3];memcpy(copy,image+0x2fc478,24);memcpy(position_copy,position,24);
        recovered_geometry_add_9400(candidate,copy,position_copy);
    }
    double self_copy[3],position_copy[3],candidate_copy[3];
    memcpy(self_copy,self,24);memcpy(position_copy,position,24);memcpy(candidate_copy,candidate,24);
    double metric=d64(call(0x36cf0,(uintptr_t)self_copy,(uintptr_t)position_copy,(uintptr_t)candidate_copy,0));
    if(d64(u64(image+0x152190))>metric || old_id!=target_id){
        recovered_geometry_construct_93b0(copy,0.,0.,0.);
        memcpy(image+0x2fc478,copy,24);state[0x2fc490]=0;state[0x2fc498]=0;
        uint32_t next=(uint32_t)_mm_cvttss_si32(_mm_set_ss(f32(image+0x2ede68)));
        state[0x2fc4a0]=0;state[0x2fc470]=0;put32(image+0x2fc4e0,next);
    }else{
        uint32_t angle=state[0x2fc498]?u32(image+0x2fc494):(uint32_t)angles;
        memcpy(copy,candidate,24);
        call(0x36d80,(uintptr_t)copy,angle,0,0);
    }
unlock:
    state[0x2fc458]=0;return;
reject:
    lock(image);
    if(state[0x2fc470]==1){
        put32(image+0x2fc4e0,(uint32_t)_mm_cvttss_si32(_mm_set_ss(f32(image+0x2ede68))));
        state[0x2fc470]=0;
    }
    state[0x2fc458]=0;state[0x2fc4a0]=0;
}
