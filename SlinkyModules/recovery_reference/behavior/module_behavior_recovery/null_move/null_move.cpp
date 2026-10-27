#include <stdint.h>
#include <string.h>
typedef uint64_t (*helper)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t r64(const void*p,unsigned n){uint64_t v;memcpy(&v,(const char*)p+n,8);return v;}
static uint32_t r32(const void*p,unsigned n){uint32_t v;memcpy(&v,(const char*)p+n,4);return v;}
static void w32(void*p,unsigned n,uint32_t v){memcpy((char*)p+n,&v,4);}

/* RVA 46ac0. Key names are deliberately numeric; original pair order is preserved. */
__declspec(dllexport) void null_move(uint8_t *event,uint8_t *image,helper call) {
    uint8_t *game=(uint8_t*)(uintptr_t)r64(event,8);
    if(!(uint8_t)call(0x22e60,r64(game,0),r64(game,24),0,0)) return;
    uint32_t stamp=(uint32_t)call(0x23760,r64(game,0),r64(game,40),0,0);
    uint64_t options=call(0x22cf0,r64(game,0),r64(game,24),0,0);
    uint64_t key[4];
    key[0]=call(0x250d0,r64(game,0),options,0,0);
    key[1]=call(0x25170,r64(game,0),options,0,0);
    key[2]=call(0x25120,r64(game,0),options,0,0);
    key[3]=call(0x251c0,r64(game,0),options,0,0);
    static const unsigned opposite[4]={2,3,0,1};
    for(unsigned i=0;i<4;++i) {
        uint32_t previous=r32(image,0x3049d0+i*4);
        unsigned other=opposite[i];
        uint8_t pressed=(uint8_t)call(0x25430,r64(game,0),key[i],0,0);
        uint8_t other_pressed=(uint8_t)call(0x25430,r64(game,0),key[other],0,0);
        uint32_t next=0;
        if(pressed) {
            next=stamp;
            if(!previous && (other_pressed&1)) call(0x25460,r64(game,0),key[other],0,0);
        } else if(previous && (uint8_t)call(0x25490,r64(game,0),key[other],0,0)) {
            call(0x25460,r64(game,0),key[other],1,0);
        }
        w32(image,0x3049d0+i*4,next);
    }
}
