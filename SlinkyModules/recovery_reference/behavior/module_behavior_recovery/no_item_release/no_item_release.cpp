#include <stdint.h>
#include <string.h>

typedef uint64_t (*dependency)(uint32_t, uint64_t, uint64_t, uint64_t, uint64_t);
static uint64_t load64(const void *p) { uint64_t v; memcpy(&v,p,8); return v; }
static uint32_t load32(const void *p) { uint32_t v; memcpy(&v,p,4); return v; }

/* RVA 0x334c0. Packet decoding and item queries remain external dependencies. */
__declspec(dllexport) void recovered_no_item_release(uint8_t *event, uint8_t *image,
                                                   dependency call) {
    uint64_t decoded = call(0x26580,load64(event+8),load64(event+16),0,0);
    uint64_t game = load64(event+8);
    uint8_t *active = image+0x2fa350;
    if (!decoded) {
        decoded = call(0x264f0,game,load64(event+16),0,0);
        if (!decoded || !*active) return;
        if ((uint32_t)call(0x26530,load64(event+8),decoded,0,0)==5) {
            uint32_t result=2; memcpy(event+0x24,&result,4);
        }
        *active=0;
        return;
    }
    uint64_t stack = call(0x265c0,game,decoded,0,0);
    if (!stack) { *active=0; return; }
    uint64_t item = call(0x25d10,game,stack,0,0);
    if (!item) { *active=0; return; }
    uint32_t id=(uint32_t)call(0x25c50,game,item,0,0);
    uint32_t bit=id-0x105u;
    if (bit<23 && ((0x4088c0u>>bit)&1)) {
        if (load32(image+0x2ec5e8)==1) { *active=0; return; }
    } else {
        if (id==0x105 || id==0x15a || load32(image+0x2ec5e8)==0) {
            *active=0; return;
        }
    }
    id=(uint32_t)call(0x25c50,game,item,0,0);
    *active=(uint8_t)(id!=0x105 && id!=0x15a);
}
