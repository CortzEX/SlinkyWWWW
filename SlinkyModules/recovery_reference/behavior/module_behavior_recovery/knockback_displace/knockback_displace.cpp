#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <intrin.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t u64(const void *p){return *(const volatile uint64_t *)p;}
static uint32_t u32(const void *p){return *(const volatile uint32_t *)p;}
static int32_t s32(uint32_t b){int32_t v;memcpy(&v,&b,4);return v;}
static float f32(const void *p){uint32_t b=u32(p);float v;memcpy(&v,&b,4);return v;}
static double f64(const void *p){uint64_t b=u64(p);double v;memcpy(&v,&b,8);return v;}
static uint32_t fb(float v){uint32_t b;memcpy(&b,&v,4);return b;}
static void put32(void *p,uint32_t v){*(volatile uint32_t *)p=v;}

__declspec(dllexport) uint8_t recovered_timer_range_query(uint8_t *image){
    if(image[0x2f3174]!=1) return 0;
    return ((s32(u32(image+0x3043d8))>0)|image[0x3043dc])&1;
}
__declspec(dllexport) uint8_t recovered_displace_angle(uint8_t *ctx,uint64_t angle,uint64_t target,uint8_t *image,dependency call){
    uint64_t bits=call(0x24220,u64(ctx),target,0,0,0);
    float difference=(float)f64(&bits)-f32(&angle);
    uint32_t normalized=(uint32_t)call(0xa210,fb(difference),0,0,0,0);
    normalized&=u32(image+0x1566a0);
    return f32(image+0x1566b0)>f32(&normalized);
}
__declspec(dllexport) uint32_t recovered_displace_direction(uint8_t *image,dependency call){
    switch(u32(image+0x2f60b8)){
    case 0:return 0xffffffffu;
    case 1:return 1;
    case 2:return ((uint32_t)(uint8_t)call(0xa460,u32(image+0x1566b4),0,0,0,0)-1u)|1u;
    case 3:return u32(image+0x304b08);
    case 4:return 0u-u32(image+0x304b08);
    default:abort();
    }
}
__declspec(dllexport) void recovered_displace_packet(uint8_t *event,uint8_t *image,dependency unused){
    (void)unused;
    if(image[0x304af0]&1) put32(event+0x24,1);
}
__declspec(dllexport) void recovered_displace_movement(uint8_t *event,uint8_t *image,dependency unused){
    (void)unused;
    if(image[0x304af1] || image[0x304af2]) event[9]=0;
}
__declspec(dllexport) void recovered_displace_reset(uint8_t *event,uint8_t *image,dependency unused){
    (void)unused;
    if(event[0x10]==1 && u32(image+0x304af4)>=10 && (image[0x304af3]&1)) put32(image+0x304af4,0);
}
__declspec(dllexport) void recovered_displace_input(uint8_t *event,uint8_t *image,dependency call){
    volatile uint8_t *state=image;
    if(state[0x304af1]==1){event[0x11]=1;return;}
    if(event[0x10]!=1) return;
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    uint64_t target=call(0x22e10,u64(ctx),u64(ctx+0x18),0,0,0);
    if(!target || (uint32_t)call(0x24b50,u64(ctx),target,0,0,0)!=2) return;
    uint64_t entity=call(0x24e30,u64(ctx),target,0,0,0);
    entity=call(0x24120,u64(ctx),entity,0,0,0);
    if(!entity || (uint8_t)call(0x2ace0,u64(ctx),entity,7,0,0)) return;
    state[0x304af3]=1;
    if(state[0x304af2] || u32(image+0x304af4)<9) return;
    if(f32(image+0x2f5fa0)>(float)(uint64_t)u32(image+0x304af8)) return;
    if(recovered_timer_range_query(image)) return;
    if(state[0x2f5ff8]==1){
        uint8_t *target_state=(uint8_t *)(uintptr_t)u64(ctx+0x38);
        if(target_state[0x18]) return;
    }
    uint32_t weapon_flags;
    uint8_t weapon=(uint8_t)call(0x37e50,u64(ctx),u64(ctx+0x28),(uintptr_t)&weapon_flags,0,0);
    if(state[0x2f6018]==1 && !weapon) return;
    if(!(weapon_flags&2)){
        if(state[0x2f6038] || !(uint8_t)call(0x23690,u64(ctx),u64(ctx+0x28),0,0,0)) return;
    }
    uint64_t angle=call(0x23170,u64(ctx),u64(ctx+0x28),0,0,0);
    *(volatile uint64_t *)(image+0x304b00)=angle;
    if(state[0x2f6058]==1 && !recovered_displace_angle(ctx,angle,entity,image,call)) return;
    uint32_t direction=recovered_displace_direction(image,call);
    if(!direction || !(uint8_t)call(0x29800,200,0,0,0,0)) return;
    call(0x29d90,(uintptr_t)ctx,1,0,0,u64(image+0x304b00));
    state[0x304af1]=1;
    uint8_t sign=(uint8_t)call(0xa460,u32(image+0x156680),0,0,0,0);
    float direction_float=(float)s32(direction);
    float strength=f32(image+0x2f5fd8);
    uint32_t ten=u32(image+0x156684);
    uint64_t random=call(0xa050,0,ten,0,0,0);
    uint32_t jitter=(uint32_t)call(0xa3e0,random,0,0,0,0);
    strength=(strength-f32(&jitter))*direction_float;
    random=call(0xa050,ten,u32(image+0x156688),0,0,0);
    uint32_t vertical=(uint32_t)call(0xa3e0,random,0,0,0,0);
    if(!sign) vertical^=u32(image+0x156690);
    uint64_t displacement=(uint64_t)fb(strength)|((uint64_t)vertical<<32);
    call(0x29820,displacement,0,0,0,0);
    call(0x29950,u64(ctx),u64(ctx+0x28),0,0,0);
    if(state[0x2f60e0]==1) _InterlockedExchange8((volatile char *)(image+0x304af0),1);
    event[0x11]=1;put32(image+0x304af8,0);
}
__declspec(dllexport) void recovered_displace_update(uint8_t *event,uint8_t *image,dependency call){
    volatile uint8_t *state=image;
    put32(image+0x304af4,u32(image+0x304af4)+1u);put32(image+0x304af8,u32(image+0x304af8)+1u);
    state[0x304af2]=state[0x304af1];state[0x304af3]=0;
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    if(ctx[0x40]!=1) goto clear;
    uint32_t movement_bits=(uint32_t)call(0x23ae0,u64(ctx),u64(ctx+0x28),0,0,0);
    float movement=f32(&movement_bits);
    uint32_t sign=(uint32_t)((movement>0.0f)-(movement<0.0f));
    if(state[0x2f6100]!=1 || sign) put32(image+0x304b08,sign);
    if(state[0x304af1]!=1) goto finish;
    if(!(uint8_t)call(0x29800,200,0,0,0,0)) goto clear;
    uint64_t angle=call(0x23170,u64(ctx),u64(ctx+0x28),0,0,0);
    uint64_t displacement=call(0x29850,0,0,0,0,0);
    displacement=call(0x9de0,angle,displacement,0,0,0);
    displacement=call(0x9e20,u64(image+0x304b00),displacement,0,0,0);
    call(0x29820,displacement,0,0,0,0);
    call(0x29950,u64(ctx),u64(ctx+0x28),0,0,0);
    uint64_t inventory=call(0x22cf0,u64(ctx),u64(ctx+0x18),0,0,0);
    call(0x22eb0,u64(ctx),u64(ctx+0x18),0,0,0);
    uint64_t slot=call(0x25270,u64(ctx),inventory,0,0,0);
    call(0x25380,u64(ctx),slot,0,0,0);
clear:
    state[0x304af1]=0;
finish:
    uint32_t packet_flag=state[0x304af2]?u32(image+0x2f60e0):0;
    _InterlockedExchange8((volatile char *)(image+0x304af0),(char)packet_flag);
}
