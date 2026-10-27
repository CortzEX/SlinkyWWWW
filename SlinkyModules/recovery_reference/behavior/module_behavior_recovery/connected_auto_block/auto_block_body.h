#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include <windows.h>
#include <xmmintrin.h>


typedef struct { uint8_t *image; ab_dispatch dispatch; void *opaque; } ab_context;
static __declspec(thread) ab_context *active_context;

static uint8_t *img(void) { return active_context->image; }
static uint8_t r8(size_t o) { return img()[o]; }
static uint32_t r32(size_t o) { uint32_t v; memcpy(&v,img()+o,4); return v; }
static uint64_t r64p(const void *p,size_t o) { uint64_t v; memcpy(&v,(const uint8_t *)p+o,8); return v; }
static float rf32(size_t o) { uint32_t b=r32(o); float v; memcpy(&v,&b,4); return v; }
static double rd64p(const void *p,size_t o) { double v; memcpy(&v,(const uint8_t *)p+o,8); return v; }
static void w8(size_t o,uint8_t v) { img()[o]=v; }
static void w32(size_t o,uint32_t v) { memcpy(img()+o,&v,4); }
static uint32_t xchg32(size_t o,uint32_t v)
{ return (uint32_t)InterlockedExchange((volatile LONG *)(void *)(img()+o),(LONG)v); }
static uint32_t dec32(size_t o)
{ return (uint32_t)InterlockedDecrement((volatile LONG *)(void *)(img()+o)); }
static int32_t cvttss_i32(float v) { return _mm_cvttss_si32(_mm_set_ss(v)); }
static float subss(float a,float b) { return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b))); }
static uint64_t call(uint32_t rva,uint64_t a,uint64_t b,uint32_t c,uint64_t d,uint32_t xmm0)
{ return active_context->dispatch(active_context->opaque,rva,a,b,c,d,xmm0,0); }
static uint64_t call0(uint32_t rva) { return call(rva,0,0,0,0,0); }
static uint32_t random_raw(uint32_t bits) { return (uint8_t)call(0xa460,0,0,0,0,bits); }
static uint32_t random_byte(float x)
{ uint32_t bits; memcpy(&bits,&x,4); return random_raw(bits); }
static uint64_t game_of(uint8_t *bridge) { return r64p(bridge,0); }
static uint64_t target_of(uint8_t *bridge) { return r64p(bridge,0x38); }
static uint64_t rearm(uint8_t *bridge,uint64_t entity,uint32_t mode)
{ uint64_t game=game_of(bridge); return call(0x25460,game,entity,mode,0,0); }
static uint64_t entity_from(uint8_t *bridge)
{ uint64_t game=game_of(bridge); uint64_t raw=call(0x22cf0,game,r64p(bridge,0x18),0,0,0); game=game_of(bridge); return call(0x24f90,game,raw,0,0,0); }
static uint64_t current_block(uint8_t *bridge)
{
    uint64_t game=game_of(bridge), item=r64p(bridge,0x28);
    uint64_t obj=call(0x28a50,game,item,0,0,0);
    /* The native body captures RCX before 28a50 and reuses that game pointer. */
    return call(0x28ac0,game,obj,0,0,0);
}
static uint32_t random_integer(float value)
{
    int32_t whole=cvttss_i32(value);
    float frac=subss(value,(float)whole);
    return (uint32_t)whole+random_byte(frac);
}

static uint64_t tick_impl(uint8_t *event)
{
    uint8_t *bridge=(uint8_t *)(uintptr_t)r64p(event,8); /* captured in R14 */
    uint32_t esi=0,eax=0,edi=0,ebx=0;
    uint8_t r12=0,r15=0,b6=0,b8=0;
    int write_state=0;
    uint64_t uvar14=0;
    w8(0x2f9e10,0);
    if (r8(0x2f9e11)==1) {
        uint64_t item=r64p(bridge,0x28);
        if (item) {
            uint64_t game=game_of(bridge);
            if ((call(0x23f90,game,item,0,0,0)&0xff)==0) {
                call(0x24020,game,item,0,0,0);
            }
        }
        w8(0x2f9e11,0);
    }
    eax=r32(0x2f9e00);
    if (eax) w32(0x2f9e00,eax-1);

    if (*(uint8_t *)(bridge+0x40)==0) {
        if (r8(0x2f9e19)==1) {
            uint64_t entity=entity_from(bridge);
            uint32_t mode=(uint32_t)call(0x25490,game_of(bridge),entity,0,0,0);
            rearm(bridge,entity,mode);
            w8(0x2f9e19,0);
        }
        w8(0x2f9e12,0);
        goto post_main;
    }

    esi=(uint32_t)call(0x239f0,game_of(bridge),r64p(bridge,0x28),0,0,0);
    {
        uint64_t game=game_of(bridge);
        uint64_t item=r64p(bridge,0x28);
        uint64_t obj=call(0x28a50,game,item,0,0,0);
        uint8_t can=(uint8_t)call(0x28ac0,game,obj,0,0,0);
        w8(0x2f9e12,0);
        if (!can) {
            r12=0; b6=0; r15=0;
            if (r8(0x2f9e19)==1) goto fallback;
            goto after_block_test;
        }
        if (r8(0x2eb300)==1) {
            uint64_t tag=r64p(bridge,0x30);
            if (*(uint8_t *)(uintptr_t)(tag+1)==0) goto fallback;
        }
        if ((call0(0x42c30)&0xff)!=0) goto fallback;
        ebx=r8(0x2eb320);
        w8(0x2f9e12,(uint8_t)ebx);
        {
            uint64_t tag=r64p(bridge,0x30);
            if ((uint8_t)ebx!=*(uint8_t *)(uintptr_t)(tag+2)) goto fallback;
        }
        r12=1;
        if (esi==0 && r8(0x2eb340)!=0) goto fallback;
        {
            float chance=rf32(0x2eb2e0);
            int32_t chance_whole=cvttss_i32(chance);
            edi=(uint32_t)chance_whole;
            float frac=subss(chance,(float)chance_whole);
            uint32_t n=(uint32_t)edi+random_byte(frac);
            if ((int32_t)esi>(int32_t)n) goto fallback;
        }
        ebx=r8(0x2f9e18);
        {
            uint64_t entity=entity_from(bridge);
            rearm(bridge,entity,ebx);
            r15=1;
            if ((uint8_t)ebx==1) {
                uint64_t game=game_of(bridge);
                call(0x25380,game,entity,0,0,0);
                r12=1;
            }
        }
        b6=1;
        write_state=1;
        goto after_block_test;
    }

fallback:
    {
        uint64_t entity=entity_from(bridge);
        /* Native captures RBX=game at 3177a before the optional 25490 call. */
        uint64_t captured_game=game_of(bridge);
        uint32_t mode=0;
        if (r8(0x2f9e12)==0) mode=(uint32_t)call(0x25490,captured_game,entity,0,0,0);
        call(0x25460,captured_game,entity,mode,0,0);
    }
    b6=0;
    r15=0;
    write_state=1;
    goto after_block_test;

after_block_test:
    /* Native R15B is assigned from the enabled/configuration branch above. */
    if (write_state) w8(0x2f9e19,r15);
    r12=(uint8_t)(r12 && r8(0x2eb360)!=0);
    if (r12 && r8(0x2eb380)==1) {
        uint64_t distance=target_of(bridge);
        if (r64p((const void *)(uintptr_t)distance,8)==0) r12=0;
        else {
            float radius=rf32(0x2eb3b8); double squared=(double)(radius*radius);
            double actual=rd64p((const void *)(uintptr_t)distance,0x10);
            r12=(uint8_t)(squared>actual);
        }
    }
    w8(0x2f9e10,r12);

    if (esi==10) w32(0x2f9e00,0);
    w32(0x2f9e08,r32(0x2f9e08)+1u);
    eax=r32(0x2f9e08);
    /* Native clears ESI before either counter branch at 31814. */
    esi=0; edi=0;
    if (eax>9) {
        edi=(uint32_t)call(0x23760,game_of(bridge),r64p(bridge,0x28),0,0,0);
        eax=(uint32_t)call(0x239d0,game_of(bridge),r64p(bridge,0x28),0,0,0);
        if (edi==eax+1u) { w32(0x2f9e08,0); b8=1; }
    }
    {
        uint64_t dist=target_of(bridge);
        if (r64p((const void *)(uintptr_t)dist,8)!=0)
            esi=(uint32_t)call(0x23720,game_of(bridge),r64p((const void *)(uintptr_t)dist,8),0,0,0);
        /* On a null target the native branch preserves ESI from 239f0. */
    }
    if (esi!=r32(0x2f9e0c)) {
        w32(0x2f9e08,0); b8=1; w32(0x2f9e0c,esi);
    }
    eax=r32(0x2f9e14); uvar14=eax;
    if (eax) {
        if (((uint32_t)b8 & r8(0x2eb3d8))==1) xchg32(0x2f9e14,0);
        else dec32(0x2f9e14);
        if (r8(0x2eb3f8)==1 && r32(0x2f9e14)==0) w32(0x2f9e00,0);
        uvar14=eax;
    }
    if (r8(0x2f9e18)!=0) {
        uint32_t i15=r32(0x2f9e04)+1u;
        float delay=rf32(0x2eb238);
        int32_t whole=cvttss_i32(delay);
        float frac=subss(delay,(float)whole);
        w32(0x2f9e04,i15);
        uint32_t limit=(uint32_t)whole+random_byte(frac);
        if ((r15 & ((int32_t)i15<(int32_t)limit))!=0) {
            return (uint64_t)(((uint32_t)limit & 0xffffff00u)|((int32_t)i15<(int32_t)limit));
        }
        {
            uint64_t entity=entity_from(bridge); rearm(bridge,entity,0); w8(0x2f9e19,1);
            uint64_t chance_return=call(0xa460,0,0,0,0,r32(0x2eb270));
            if ((chance_return&0xff)!=0) {
                float v=rf32(0x2eb2a8); int32_t n=cvttss_i32(v);
                uint32_t newvalue=(uint32_t)n+random_byte(subss(v,(float)n));
                uvar14=r32(0x2f9e14);
                xchg32(0x2f9e14,newvalue);
            } else { w8(0x2f9e18,0); return chance_return; }
        }
        w8(0x2f9e18,0);
        return uvar14;
    }
    if (!((r15 && r32(0x2f9e00)==0)==1))
        return (uvar14 & ~UINT64_C(0xff)) | (uint8_t)(r32(0x2f9e00)==0);
    {
        uint64_t distance=target_of(bridge);
        if (r64p((const void *)(uintptr_t)distance,8)==0) return distance;
        float radius=rf32(0x2eb3b8); double squared=(double)(radius*radius);
        double actual=rd64p((const void *)(uintptr_t)distance,0x10);
        if (!(squared>actual)) return distance;
        {
            uint64_t entity=entity_from(bridge); rearm(bridge,entity,(connected_external_r8()&0xffffff00u)|1u);
            uint64_t game=game_of(bridge); call(0x25380,game,entity,0,0,0);
            w8(0x2f9e19,1); w8(0x2f9e18,1); w32(0x2f9e00,10); w32(0x2f9e04,0);
        }
    }
post_main:
    eax=xchg32(0x2f9e14,0); return eax;
}

uint64_t linked_auto_block_31570(uint8_t *event,uint8_t *image,ab_dispatch dispatch,void *opaque)
{
    ab_context next={image,dispatch,opaque},*old=active_context; active_context=&next;
    uint64_t r=tick_impl(event); active_context=old; return r;
}

void linked_auto_block_31a50(uint8_t *event,uint8_t *image)
{ uint32_t count; memcpy(&count,image+0x2f9e14,4); if (count!=0) { uint32_t one=1; memcpy(event+0x24,&one,4); } }

uint64_t linked_auto_block_31a70(uint8_t *event,uint8_t *image,ab_dispatch dispatch,void *opaque)
{
    ab_context next={image,dispatch,opaque},*old=active_context; active_context=&next;
    uint64_t result=UINT64_C(0x1802eaff8);
    if (r64p(event,0x10)==(uint64_t)(uintptr_t)(image+0x2eaff8) && event[0x18]==0 && (r8(0x2f9e18)&1)) {
        if (r8(0x2f9e19)==1) {
            uint8_t *bridge=(uint8_t *)(uintptr_t)r64p(event,8);
            uint64_t entity=entity_from(bridge);
            uint32_t mode=(uint32_t)call(0x25490,game_of(bridge),entity,0,0,0);
            rearm(bridge,entity,mode); w8(0x2f9e19,0);
        }
        w8(0x2f9e18,0); uint32_t oldcount=xchg32(0x2f9e14,0); result=oldcount;
    }
    active_context=old; return result;
}

void linked_auto_block_31b00(uint8_t *event,uint8_t *image,ab_dispatch dispatch,void *opaque)
{
    ab_context next={image,dispatch,opaque},*old=active_context; active_context=&next;
    if (event[0x10]==0) {
        uint8_t *bridge=(uint8_t *)(uintptr_t)r64p(event,8);
        uint64_t game=game_of(bridge),item=r64p(bridge,0x28);
        uint64_t obj=call(0x28a50,game,item,0,0,0);
        uint8_t can=(uint8_t)call(0x28ac0,game,obj,0,0,0);
        if (!can) w32(0x2f9e14,0);
        if (r8(0x2f9e12)==1 && (r8(0x2f9e18)&1)==0) event[0x11]=1;
    }
    active_context=old;
}

void linked_auto_block_31b60(uint8_t *event,uint8_t *image,ab_dispatch dispatch,void *opaque)
{
    ab_context next={image,dispatch,opaque},*old=active_context; active_context=&next;
    if (r8(0x2f9e10)==0) w32(0x2f9e1c,0x11940);
    else {
        uint8_t *bridge=(uint8_t *)(uintptr_t)r64p(event,8); uint64_t item=r64p(bridge,0x28);
        if (item) {
            w8(0x2f9e11,1); uint32_t v=r32(0x2f9e1c)-1u; w32(0x2f9e1c,v);
            uint64_t game=game_of(bridge); call(0x24020,game,item,v,0,0);
        }
    }
    active_context=old;
}
