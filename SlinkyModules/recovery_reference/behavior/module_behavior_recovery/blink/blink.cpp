#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
#include <intrin.h>

static uint64_t r64(const void *p, unsigned n) { uint64_t v; memcpy(&v,(const char*)p+n,8); return v; }
static uint32_t r32(const void *p, unsigned n) { uint32_t v; memcpy(&v,(const char*)p+n,4); return v; }
static void w32(void *p, unsigned n, uint32_t v) { memcpy((char*)p+n,&v,4); }
typedef struct {
    int32_t (*f239d0)(uint64_t,uint64_t);
    void (*f284f0)(uint64_t,uint64_t,uint8_t);
    uint64_t (*f26a30)(uint64_t,uint64_t);
    uint64_t (*f26ad0)(uint64_t,uint64_t);
    uint64_t (*f26a90)(uint64_t,uint64_t);
    uint64_t (*f27160)(uint64_t,uint64_t);
    uint64_t (*f22e10)(uint64_t,uint64_t);
    int32_t (*f24b50)(uint64_t,uint64_t);
} dependencies;

/* Settings base 2ec800; state base 2fa300. Exports have the registry's void return contract. */
__declspec(dllexport) void blink_0(uint8_t *event,uint8_t *settings,uint8_t *state,const dependencies *d) {
    uint8_t *game=(uint8_t*)(uintptr_t)r64(event,8);
    if (game[64]==1) {
        int32_t current=d->f239d0(r64(game,0),r64(game,40));
        int32_t previous; uint32_t old=r32(state,0x54); memcpy(&previous,&old,4);
        uint8_t rising=(current>previous)&settings[0x28];
        w32(state,0x54,(uint32_t)current);
        uint32_t remaining=r32(state,0x58)-1;
        w32(state,0x58,remaining);
        if (!remaining || rising) d->f284f0(r64(game,8),UINT64_C(0x1802ec600),0);
    }
}
__declspec(dllexport) void blink_2(uint8_t *event,uint8_t *state,const dependencies *d) {
    if (state[0x5c]==1) return;
    uint32_t result=3;
    if (!d->f26a30(r64(event,8),r64(event,16)) &&
        !d->f26ad0(r64(event,8),r64(event,16)) &&
        !d->f26a90(r64(event,8),r64(event,16)))
        result=d->f27160(r64(event,8),r64(event,16))?3:1;
    w32(event,36,result);
}
__declspec(dllexport) void blink_3(uint8_t *event,uint8_t *state) {
    if (state[0x5c]) w32(event,36,1);
}
__declspec(dllexport) void blink_5(uint8_t *event,uint8_t *settings,uint8_t *state) {
    if (r64(event,16)==UINT64_C(0x1802ec600) && event[24]==1) {
        float duration; memcpy(&duration,settings+0x60,4);
        w32(state,0x58,(uint32_t)_mm_cvttss_si64(_mm_set_ss(duration)));
        w32(state,0x54,0x7fffffff);
        _InterlockedExchange8((volatile char*)state+0x5c,(char)settings[0xb8]);
    }
}
__declspec(dllexport) void blink_14(uint8_t *event,uint8_t *settings,const dependencies *d) {
    uint8_t *game=(uint8_t*)(uintptr_t)r64(event,8);
    if ((event[16]==1?settings[0xe0]:settings[0x100])==1) {
        uint64_t hit=d->f22e10(r64(game,0),r64(game,24));
        if (hit && d->f24b50(r64(game,0),hit)==1)
            d->f284f0(r64(game,8),UINT64_C(0x1802ec600),0);
    }
}
