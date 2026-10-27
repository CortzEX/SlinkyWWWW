#include <stdint.h>
#include <string.h>
#include <intrin.h>

typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t u64(const void *p) { uint64_t v;memcpy(&v,p,8);return v; }
static uint32_t u32(const void *p) { uint32_t v;memcpy(&v,p,4);return v; }
static uint16_t u16(const void *p) { uint16_t v;memcpy(&v,p,2);return v; }
static void put32(void *p,uint32_t v) { memcpy(p,&v,4); }

/* RVA 0x46140. State production in callback 0x46270 remains separate. */
__declspec(dllexport) void recovered_knockback_delay_packet(uint8_t *event,
                                                          uint8_t *image,dependency call) {
    if (u32(event+0x24)) return;
    uint64_t packet=call(0x266b0,u64(event+8),u64(event+0x10),0,0);
    uint8_t matches=0;
    if (packet) {
        uint32_t id=(uint32_t)call(0x266f0,u64(event+8),packet,0,0);
        matches=(id==u32(image+0x3049a4));
    }
    uint8_t active;
    if (image[0x3049a0]&1) {
        active=u64(event+0x18)==0?(image[0x3049a1]&1):0;
        image[0x304998]=active;
    } else if (image[0x3049a1]&matches&1) {
        active=1;image[0x304998]=1;
    } else active=image[0x304998];
    if ((matches&active)==1) {
        uint32_t saved=u32(image+0x30499c),stamp=u32(event+0x20);
        if (saved && saved!=stamp) goto reset;
        if (!saved) put32(image+0x30499c,stamp);
    } else if (!active) return;
    uint64_t remaining_bits=u64(event+0x18);
    int64_t remaining;memcpy(&remaining,&remaining_bits,8);
    if (remaining>(int64_t)u16(image+0x3049a2)) goto reset;
    uint32_t result=1;
    if (call(0x26a30,u64(event+8),u64(event+0x10),0,0) ||
        call(0x26ad0,u64(event+8),u64(event+0x10),0,0) ||
        call(0x26a90,u64(event+8),u64(event+0x10),0,0)) result=3;
    put32(event+0x24,result);
    return;
reset:
    image[0x304998]=0;
    _InterlockedExchange8((volatile char *)(image+0x3049a1),0);
    put32(image+0x30499c,0);
}
