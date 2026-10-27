#include <stdint.h>
#include <stddef.h>
#include <string.h>

typedef uintptr_t up;
typedef struct {
    void (*f34ce0)(up);
    void (*f34e90)(up);
    void (*f_ab710)(up,uint32_t,up,up);
    up (*f_ab840)(up);
    up character_provider;
    uint8_t (*f_character)(up,int32_t);
    void (*f_79610)(up);
    void (*f_10340)(up,uint32_t);
    void (*f_79690)(up,uint32_t);
    void (*f_7ae90)(up,uint64_t,uint64_t,up,uint64_t,up);
    void (*f_qsort)(up,uint64_t,uint64_t,up);
    void (*f_74150)(up,uint32_t,uint32_t,uint32_t,uint32_t);
    void (*f_74130)(up,uint32_t,uint32_t,uint32_t,up);
    void (*f_74a60)(up,uint32_t);
    void (*f_74ef0)(up,up);
    void (*f_75bc0)(up);
    void (*f_76a10)(up,uint32_t,uint32_t,uint32_t,uint32_t,uint64_t,uint32_t,uint32_t,uint32_t);
    void (*f_77210)(up);
    uint32_t (*f_00a280)(void);
    uint32_t (*f_79770)(up,uint32_t,uint32_t,up,uint32_t);
    void (*f_dynamic)(up,up);
} deps;

static uint64_t rd64(const void *p, unsigned n) { uint64_t v; memcpy(&v,(const uint8_t*)p+n,8); return v; }
static uint32_t rd32(const void *p, unsigned n) { uint32_t v; memcpy(&v,(const uint8_t*)p+n,4); return v; }
static float rdf(const void *p, unsigned n) { float v; memcpy(&v,(const uint8_t*)p+n,4); return v; }
static void wr64(void *p, unsigned n, uint64_t v) { memcpy((uint8_t*)p+n,&v,8); }
static void wr32(void *p, unsigned n, uint32_t v) { memcpy((uint8_t*)p+n,&v,4); }
static void wrf(void *p, unsigned n, float v) { memcpy((uint8_t*)p+n,&v,4); }
static uint8_t *G(uint8_t *im, uint32_t rva) { return im+rva; }

/* Three registry hooks below reproduce only the observed body. The helper at
   34ce0 remains an explicit dependency. Globals are addressed from image RVA. */
__declspec(dllexport) void mod_overlay_dirty(uint8_t *ev,uint8_t *im,const deps *d) {
    (void)d;
    if (rd32(ev,0x10)==0) G(im,0x2faff4)[0]=1;
}
__declspec(dllexport) void mod_overlay_refresh(uint8_t *ev,uint8_t *im,const deps *d) {
    if (G(im,0x2ed1b8)[0]==1) { d->f34ce0(rd64(ev,8)); G(im,0x2faff5)[0]=1; }
}
__declspec(dllexport) void mod_overlay_event(uint8_t *ev,uint8_t *im,const deps *d) {
    uint32_t old=rd32(ev,0x10); wr32(ev,0x10,old|1u);
    if (G(im,0x2faff5)[0]!=0 || (rdf(im,0x2fbfa0)>0.0f)) wr32(ev,0x10,old|3u);
}

static int eligible(uint8_t *item,uint8_t *im,int require_active) {
    if ((require_active && item[0x14]!=1) || (item[0x18]&4)!=0) return 0;
    if (G(im,0x2ed1b8)[0]==1 && rd32(item,0x1c)==0) return 0;
    switch(rd32(item,0x10)) {
    case 0: return G(im,0x2ed118)[0]!=0;
    case 1: return G(im,0x2ed138)[0]!=0;
    case 2: return G(im,0x2ed178)[0]!=0;
    case 3: return G(im,0x2ed158)[0]!=0;
    case 4: return G(im,0x2ed198)[0]==1;
    default: return 1;
    }
}
static void append_candidate(uint8_t *im,up item,const deps *d) { d->f34e90(item); }
__declspec(dllexport) void mod_overlay_control(uint8_t *ev,uint8_t *im,const deps *d) {
    up item=rd64(ev,0x10); uint8_t *row; uint64_t n,i; uint8_t *game; uint8_t *list;
    wr32(im,0x2fbfa0,0x3e4ccccd);
    if (item==(up)(uintptr_t)(im+0x2ecef0)) {
        game=(uint8_t*)(uintptr_t)rd64(ev,8); list=(uint8_t*)(uintptr_t)rd64(game,8);
        wr64(im,0x2faff8,0);
        if (ev[0x18]!=1) return;
        n=rd64(list,8);
        for (i=0;i<n;i++) {
            up candidate=rd64((void*)(uintptr_t)rd64(list,0),(unsigned)(i*8));
            if (eligible((uint8_t*)(uintptr_t)candidate,im,1)) {
                append_candidate(im,candidate,d);
                n=rd64(list,8);
            }
        }
        G(im,0x2faff5)[0]=1;
        return;
    }
    n=rd64(im,0x2faff8);
    for (i=0;i<n;i++) {
        row=G(im,0x2fb000)+(size_t)i*0x50;
        if (rd64(row,0)!=item) continue;
        if (ev[0x18]==0) { row[0x48]=0; return; }
        if (!eligible((uint8_t*)(uintptr_t)item,im,0)) return;
        row[0x48]=1; return;
    }
    if (ev[0x18]!=1 || !eligible((uint8_t*)(uintptr_t)item,im,1)) return;
    append_candidate(im,item,d); G(im,0x2faff5)[0]=1;
}

/* The protected provider is supplied by the harness; string length and
   character mapping remain explicit runtime dependencies. */
__declspec(dllexport) void mod_overlay_collect(uint8_t *ev,uint8_t *im,const deps *d) {
    uint8_t *ctx=(uint8_t*)(uintptr_t)rd64(ev,8);
    uint32_t mask=(uint32_t)G(im,0x2ed118)[0]+2u*G(im,0x2ed138)[0]+4u*G(im,0x2ed158)[0]+8u*G(im,0x2ed178)[0];
    mask|=(uint32_t)G(im,0x2ed198)[0]<<4; mask|=(uint32_t)G(im,0x2ed1b8)[0]<<5;
    uint8_t old_dirty=G(im,0x2faff4)[0], bl; uint64_t i;
    if (rd32(im,0x2faff0)!=mask || (old_dirty&1)) {
        d->f34ce0(rd64(ctx,8)); wr32(im,0x2faff0,mask); G(im,0x2faff5)[0]=1; G(im,0x2faff4)[0]=0;
    }
    if (!(old_dirty&1) && ctx[0x40]!=0) return;
    bl=G(im,0x2ed1d8)[0];
    for (i=0;i<rd64(im,0x2faff8);i++) {
        uint8_t *row=G(im,0x2fb000)+(size_t)i*0x50; up item=rd64(row,0); uint8_t *item_object=(uint8_t*)(uintptr_t)item; int formatted=0;
        if (bl&1) {
            up length=d->f_ab840(rd64(item_object,0)),terminator=length;
            for (up j=0;j<length;j++) {
                up name=rd64(item_object,0);
                int32_t source=(int8_t)*((uint8_t*)(uintptr_t)name+j);
                row[8+j]=d->f_character(d->character_provider,source);
            }
            row[8+terminator]=0;
            bl=1;
        } else {
            d->f_ab710((up)(uintptr_t)(row+8),0x14,(up)(uintptr_t)(im+0x151cfc),rd64(item_object,0));
            bl=G(im,0x2ed1d8)[0];
            formatted=1;
        }
        if (formatted) {
            item=rd64(row,0); item_object=(uint8_t*)(uintptr_t)item;
        }
        up callback=rd64(item_object,0x208);
        if (!callback || !G(im,0x2ed1f8)[0]) row[0x1c]=0;
        else {
            /* Dynamic callback is an explicit, address-preserving boundary. */
            d->f_dynamic(callback,(up)(uintptr_t)(row+0x1c));
            if (G(im,0x2ed1d8)[0]==1) {
                bl=1;
            } else {
                bl=0;
            }
            if (bl && row[0x1c]) {
                up j=0,length;
                do {
                    uint8_t *text=G(im,0x2fb01c)+(size_t)i*0x50;
                    text[j]=d->f_character(d->character_provider,(int8_t)text[j]);
                    j++; length=d->f_ab840((up)(uintptr_t)(row+0x1c));
                } while (j<length);
            }
        }
    }
    G(im,0x2faff5)[0]=1;
}
