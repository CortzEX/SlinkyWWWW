#include <stdint.h>
#include <string.h>
#include <intrin.h>
#include <emmintrin.h>

typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t u64(const void *p) { uint64_t v;memcpy(&v,p,8);return v; }
static uint32_t u32(const void *p) { uint32_t v;memcpy(&v,p,4);return v; }
static int32_t signed32(uint32_t v) { int32_t s;memcpy(&s,&v,4);return s; }
static float f32(const void *p) { float v;memcpy(&v,p,4);return v; }
static double f64(const void *p) { double v;memcpy(&v,p,8);return v; }
static uint32_t fb(float v) { uint32_t b;memcpy(&b,&v,4);return b; }
static double from_db(uint64_t v) { return f64(&v); }
static float from_fb(uint32_t v) { return f32(&v); }

/* RVA 0x46270. The packet-side consumer is in ../knockback_delay_packet/. */
__declspec(dllexport) void recovered_knockback_delay_update(uint8_t *event,
                                                          uint8_t *image,dependency call) {
    uint8_t *game=(uint8_t *)(uintptr_t)u64(event+8);
    uint64_t target=u64(game+0x28);
    if (!target) return;
    uint32_t id=(uint32_t)call(0x23720,u64(game),target,0,0);
    _InterlockedExchange((volatile long *)(image+0x3049a4),(long)id);
    uint8_t ground=0;
    if (image[0x2f4358]==1) ground=(uint8_t)call(0x23780,u64(game),u64(game+0x28),0,0);
    _InterlockedExchange8((volatile char *)(image+0x3049a0),(char)ground);
    uint8_t allowed=0;
    uint8_t *hit=(uint8_t *)(uintptr_t)u64(game+0x38);
    if (!u64(hit+8)) goto finish;
    float range=f32(image+0x2f4390);
    if (f64(hit+0x10)>(double)(range*range)) goto finish;
    if (image[0x2f43b0]==1 && !(uint8_t)call(0x380b0,u64(game),u64(game+0x28),0,0)) goto finish;
    if (image[0x2f43d0]==1 && !(uint8_t)call(0x29080,(uintptr_t)game,0,0,0)) goto finish;
    if (image[0x2f43f0]==1) {
        double player[3];
        call(0x23030,(uintptr_t)player,u64(game),u64(game+0x28),0);
        float yaw=from_fb((uint32_t)call(0x23170,u64(game),u64(game+0x28),0,0));
        uint64_t list=call(0x24600,u64(game),u64(game+0x20),0,0);
        int32_t count=signed32((uint32_t)call(0x24e50,u64(game),list,0,0));
        if (count<=0) goto finish;
        double distance_limit=f64(image+0x154fa0);
        uint32_t abs_mask=u32(image+0x154fb0);
        float angle_limit=f32(image+0x154fc0);
        uint32_t index=0;
        for (;;) {
            uint64_t entity=call(0x24e80,u64(game),list,index,0);
            uint8_t *bridge=(uint8_t *)(uintptr_t)u64(game);
            uint64_t interface_pointer=u64(bridge+8);
            if (!(uint8_t)call(0x800000c0,interface_pointer,u64(game+0x28),entity,0)) {
                double first[3],enemy[3],a[3],b[3];
                memcpy(first,player,24);
                call(0x23030,(uintptr_t)enemy,u64(game),entity,0);
                memcpy(a,first,24);memcpy(b,enemy,24);
                double distance=from_db(call(0x94b0,(uintptr_t)a,(uintptr_t)b,0,0));
                if (!(distance>distance_limit)) {
                    memcpy(a,first,24);memcpy(b,enemy,24);
                    float angle=from_fb((uint32_t)call(0x9f80,(uintptr_t)a,(uintptr_t)b,0,0));
                    float delta=angle-yaw;
                    uint32_t wrapped=(uint32_t)call(0xa210,fb(delta),0,0,0);
                    if (!(from_fb(wrapped&abs_mask)>angle_limit)) break;
                }
            }
            ++index;
            count=signed32((uint32_t)call(0x24e50,u64(game),list,0,0));
            if (signed32(index)>=count) goto finish;
        }
    }
    {
        double chance=(double)f32(image+0x2f4428);
        allowed=1;
        if (!(chance>f64(image+0x154fc8))) {
            float low=(float)(f64(image+0x154fd0)+chance);
            float high=(float)(chance+f64(image+0x154fd8));
            uint64_t draw=call(0xa050,fb(low),fb(high),0,0);
            allowed=(uint8_t)call(0xaa30,(uintptr_t)(image+0x3049a8),draw,u64(image+0x154fe0),0);
        }
    }
finish:
    _InterlockedExchange8((volatile char *)(image+0x3049a1),(char)allowed);
    int32_t delay=_mm_cvttss_si32(_mm_set_ss(f32(image+0x2f4338)));
    _InterlockedExchange16((volatile short *)(image+0x3049a2),(short)delay);
}
