#include <stdint.h>
#include <string.h>

static uint64_t u64(const void *p, unsigned n) { uint64_t v; memcpy(&v,(const char*)p+n,8); return v; }
static uint32_t u32(const void *p, unsigned n) { uint32_t v; memcpy(&v,(const char*)p+n,4); return v; }
static void w64(void *p, unsigned n, uint64_t v) { memcpy((char*)p+n,&v,8); }
static void w32(void *p, unsigned n, uint32_t v) { memcpy((char*)p+n,&v,4); }

/* All dependency names are addresses. They are explicit boundaries, not recovered wrappers.
   Scalar float arguments cross this verification interface as their exact uint32 bits. */
typedef struct {
    uint64_t (*f22c70)(uint64_t,uint64_t);
    uint8_t (*f29080)(void*);
    uint8_t (*f23780)(uint64_t,uint64_t);
    void (*f23550)(void*,uint64_t,uint64_t);
    uint32_t (*f239f0)(uint64_t,uint64_t);
    void (*f259c0)(uint64_t,uint64_t,uint32_t);
    uint8_t (*f29f80)(void);
    uint64_t (*f29f90)(void);
    uint64_t (*f23170)(uint64_t,uint64_t);
    uint64_t (*f22cf0)(uint64_t,uint64_t);
    uint32_t (*f25310)(uint64_t,uint64_t);
    void (*f25330)(uint64_t,uint64_t,uint32_t);
    void (*f29fa0)(uint64_t);
} dependencies;

/* Settings addresses relative to 2ebc00. Game remains the initially loaded pointer.
   RVA 3295a uses JAE after UCOMISD, accepting unordered values along with negatives. */
extern "C" __declspec(dllexport) void timer_update(uint8_t *event, uint8_t *settings, const dependencies *d) {
    uint8_t *game=(uint8_t*)(uintptr_t)u64(event,8);
    uint64_t timer=d->f22c70(u64(game,0),u64(game,24));
    uint32_t speed=0x3f800000;
    if (settings[0x70]==1 && !d->f29080(game)) goto apply;
    if (settings[0x90]==1) {
        uint8_t vector[24]; double y;
        if (d->f23780(u64(game,0),u64(game,40))) goto apply;
        d->f23550(vector,u64(game,0),u64(game,40));
        memcpy(&y,vector+8,8);
        if (y>=0.0) goto apply;
    }
    if (settings[0xb0]==1 && (game[64]!=1 || !d->f239f0(u64(game,0),u64(game,40)))) goto apply;
    speed=u32(settings,0x50);
apply:
    d->f259c0(u64(game,0),timer,speed);
}

extern "C" __declspec(dllexport) void timer_lifecycle(uint8_t *event, const dependencies *d) {
    if (u64(event,16)==UINT64_C(0x1802eba10) && event[24]==0) {
        uint8_t *game=(uint8_t*)(uintptr_t)u64(event,8);
        uint64_t timer=d->f22c70(u64(game,0),u64(game,24));
        d->f259c0(u64(game,0),timer,0x3f800000);
    }
}

/* State offsets are relative to 2fc500; perspective setting relative to 2ee100. */
extern "C" __declspec(dllexport) void free_look_lifecycle(uint8_t *event, uint8_t *settings, uint8_t *state, const dependencies *d) {
    uint8_t *game;
    if (u64(event,16)!=UINT64_C(0x1802edef0)) return;
    game=(uint8_t*)(uintptr_t)u64(event,8);
    if (!u64(game,32)) return;
    if (event[24]==1) {
        uint64_t rotation;
        state[8]=1;
        if (d->f29f80()) rotation=d->f29f90();
        else rotation=d->f23170(u64(game,0),u64(game,40));
        w64(state,16,rotation);
    }
    uint64_t options=d->f22cf0(u64(game,0),u64(game,24));
    if (event[24]) {
        uint32_t perspective=d->f25310(u64(game,0),options);
        w32(state,24,perspective);
        d->f25330(u64(game,0),options,u32(settings,0x48));
    } else {
        d->f25330(u64(game,0),options,u32(state,24));
        if (state[8]==1) {
            d->f29fa0(u64(state,16));
            state[8]=0;
        }
    }
}

extern "C" __declspec(dllexport) void free_look_rotation(uint8_t *event, const uint8_t *state) {
    event[8]=1;
    w64(event,12,u64(state,16));
}
