#include <stdint.h>
#include <string.h>
#include <math.h>

typedef uint64_t (*invoke_fn)(uintptr_t, uint32_t, uint64_t, uint64_t, uint64_t, uint64_t,
                              uint64_t, uint64_t, uint64_t, uint64_t);
typedef struct { uintptr_t game; uint8_t pad08[0x10]; uintptr_t key; uint8_t pad20[8];
                 uintptr_t target; uint8_t pad30[0x10]; uint8_t enabled; } PlaceContext;
typedef struct { uintptr_t unused; volatile PlaceContext *context; } PlaceEvent;

enum { TIMER=0x2f9d60, TOGGLE=0x2f9d64, COUNT=0x2f9d68, RATE_TAG=0x2f9d70,
       RATE_DENOM=0x2ea510, MAX_DELAY=0x2ea548, STEP=0x150ce8, RATE=0x150cf0,
       RATE_ARGS=0x150cf8, SPEED_MIN=0x150d00, SPEED_MAX=0x150d04 };
enum { H_22CF0=0x22cf0, H_24F90=0x24f90, H_25490=0x25490, H_25360=0x25360,
       H_25380=0x25380, H_28A50=0x28a50, H_28B00=0x28b00, H_22E10=0x22e10,
       H_24B50=0x24b50, H_25C50=0x25c50, H_24D80=0x24d80, H_093B0=0x93b0,
       H_09400=0x9400, H_096B0=0x96b0, H_23670=0x23670, H_25640=0x25640,
       H_097D0=0x97d0, H_0A050=0xa050, H_0AA30=0xaa30 };

static uint32_t get_u32(const volatile uint8_t *image, uint32_t rva) {
    uint32_t v; memcpy(&v, (const void *)(image+rva), 4); return v;
}
static void put_u32(volatile uint8_t *image, uint32_t rva, uint32_t v) {
    memcpy((void *)(image+rva), &v, 4);
}
static float f32_at(const volatile uint8_t *image, uint32_t rva) {
    uint32_t b=get_u32(image,rva); float f; memcpy(&f,&b,4); return f;
}
static uint64_t get_u64(const volatile uint8_t *image, uint32_t rva) {
    uint64_t v; memcpy(&v, (const void *)(image+rva), 8); return v;
}
static uint32_t f32_bits(float value) { uint32_t bits; memcpy(&bits,&value,4); return bits; }
static int ucomiss_le(float a,float b) { return isnan(a)||isnan(b)||a<=b; }
static int ucomiss_gt(float a,float b) { return !isnan(a)&&!isnan(b)&&a>b; }
static int32_t cvttss2si(float f) {
    if (isnan(f)||f>=2147483648.0f||f< -2147483648.0f) return INT32_MIN;
    return (int32_t)f;
}
static uint64_t call4(invoke_fn fn, uintptr_t state, uint32_t id,
                      uint64_t a,uint64_t b,uint64_t c,uint64_t d,
                      uint64_t x0,uint64_t x1,uint64_t x2,uint64_t x3) {
    return fn(state,id,a,b,c,d,x0,x1,x2,x3);
}

__declspec(dllexport) void recovered_fast_place(uintptr_t event_address,
    volatile uint8_t *image, uintptr_t state, invoke_fn invoke) {
    volatile PlaceEvent *event=(volatile PlaceEvent *)event_address;
    float timer=f32_at(image,TIMER), zero=0.0f;
    if (!ucomiss_le(timer,zero)) {
        timer=timer+f32_at(image,STEP);
        put_u32(image,TIMER,f32_bits(timer));
        if (ucomiss_gt(timer,zero)) return;
    }
    volatile PlaceContext *ctx=event->context;
    if (ctx->enabled != 1) return;

    uint64_t value=call4(invoke,state,H_22CF0,ctx->game,ctx->key,0,0,0,0,0,0);
    value=call4(invoke,state,H_24F90,ctx->game,value,0,0,0,0,0,0);
    uint8_t active=(uint8_t)call4(invoke,state,H_25490,ctx->game,value,0,0,0,0,0,0);
    uint8_t previous=(uint8_t)image[TOGGLE]; image[TOGGLE]=active;
    if (!active) {
        float delay=f32_at(image,MAX_DELAY);
        put_u32(image,COUNT,(uint32_t)cvttss2si(delay));
        return;
    }

    int32_t count=(int32_t)get_u32(image,COUNT);
    if (count >= 1) { put_u32(image,COUNT,(uint32_t)(count-1)); return; }
    int32_t condition=(int32_t)call4(invoke,state,H_25360,ctx->game,value,0,0,0,0,0,0);
    if (condition > 0) return;
    timer=f32_at(image,TIMER);
    if (isnan(timer)||timer>zero) return;

    uint8_t phase=(uint8_t)(previous^1);
    double rate; uint64_t rate_bits=get_u64(image,RATE); memcpy(&rate,&rate_bits,8);
    float speed_min=f32_at(image,SPEED_MIN), speed_max=f32_at(image,SPEED_MAX);
    uintptr_t tag=(uintptr_t)(image+RATE_TAG);
    uint64_t rate_arg_bits=get_u64(image,RATE_ARGS);

    do {
        float denominator=f32_at(image,RATE_DENOM);
        double step=(double)denominator;
        timer=f32_at(image,TIMER);
        timer=(float)((double)timer+rate/step);
        put_u32(image,TIMER,f32_bits(timer));
        if ((phase&1)==0) {
            uintptr_t game=ctx->game;
            uintptr_t target=ctx->target;
            uint64_t found=call4(invoke,state,H_28A50,game,target,0,0,0,0,0,0);
            uint8_t should_process=(uint8_t)call4(invoke,state,H_28B00,game,found,0,0,0,0,0,0);
            if (should_process) {
                uint64_t entity=call4(invoke,state,H_22E10,ctx->game,ctx->key,0,0,0,0,0,0);
                int delay_fallback=(entity==0);
                if (!delay_fallback) delay_fallback=(int32_t)call4(invoke,state,H_24B50,ctx->game,entity,0,0,0,0,0,0)!=1;
                int direct_cleanup=0;
                if (!delay_fallback) {
                    found=call4(invoke,state,H_28A50,ctx->game,ctx->target,0,0,0,0,0,0);
                    if (found) direct_cleanup=(uint32_t)call4(invoke,state,H_25C50,ctx->game,found,0,0,0,0,0,0)==0x41;
                }
                if (!delay_fallback && !direct_cleanup) {
                    uint8_t local[0x168];
                    uint8_t *w=local;
                    call4(invoke,state,H_24D80,(uintptr_t)(w+0xf8),ctx->game,entity,0,0,0,0,0);
                    call4(invoke,state,H_093B0,(uintptr_t)(w+0x18),0,0,0,
                          0,rate_arg_bits,rate_arg_bits,rate_arg_bits);
                    memcpy(w+0xa0,w+0x108,8); memcpy(w+0x90,w+0xf8,16);
                    call4(invoke,state,H_09400,(uintptr_t)w,(uintptr_t)(w+0x90),(uintptr_t)(w+0x18),0,0,0,0,0);
                    memcpy(w+0xd0,w+0x108,8); memcpy(w+0xc0,w+0xf8,16);
                    call4(invoke,state,H_096B0,(uintptr_t)(w+0x90),(uintptr_t)(w+0xc0),(uintptr_t)w,0,0,0,0,0);
                    uintptr_t captured_game=ctx->game, captured_target=ctx->target;
                    uint64_t info=call4(invoke,state,H_23670,captured_game,captured_target,0,0,0,0,0,0);
                    call4(invoke,state,H_25640,(uintptr_t)(w+0xc0),captured_game,info,0,0,0,0,0);
                    memcpy(w+0x30,w+0x90,16); memcpy(w+0x40,w+0xa0,16); memcpy(w+0x50,w+0xb0,16);
                    memcpy(w+0x60,w+0xc0,16); memcpy(w+0x70,w+0xd0,16); memcpy(w+0x80,w+0xe0,16);
                    if ((uint8_t)call4(invoke,state,H_097D0,(uintptr_t)(w+0x30),(uintptr_t)(w+0x60),0,0,0,0,0,0))
                        delay_fallback=1;
                }
                if (delay_fallback) {
                    uint64_t rate_result=call4(invoke,state,H_0A050,0,0,0,0,
                        f32_bits(speed_min),f32_bits(speed_max),0,0);
                    uint8_t allowed=(uint8_t)call4(invoke,state,H_0AA30,tag,rate_result,0,0,
                        0,0,rate_bits,0);
                    if (!allowed) goto advance_timer;
                }
                call4(invoke,state,H_25380,ctx->game,value,0,0,0,0,0,0);
            }
        }
advance_timer:
        phase=0;
        timer=f32_at(image,TIMER);
    } while (!isnan(timer)&&timer<=zero);
}
