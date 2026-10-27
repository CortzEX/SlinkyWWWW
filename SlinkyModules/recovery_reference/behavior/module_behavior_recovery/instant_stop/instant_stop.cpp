#include <stdint.h>
#include <string.h>

/* The dependency boundary preserves the original call-site register/stack
   arguments.  Return values are raw RAX bits; callback-specific float returns
   are returned in the low 32 bits. */
typedef uint64_t (*instant_stop_helper)(uint32_t rva, uint64_t rcx,
    uint64_t rdx, uint64_t r8, uint64_t r9, uint32_t xmm2,
    uint32_t xmm3, uint32_t fifth_f32, uint32_t *helper_r8);
static uint32_t *active_helper_r8;

static uint64_t call(instant_stop_helper h, uint32_t id,
    uint64_t a, uint64_t b, uint64_t c, uint64_t d,
    uint32_t x2, uint32_t x3, uint32_t fifth)
{ return h(id,a,b,c,d,x2,x3,fifth,active_helper_r8); }

static uint8_t low_al(uint64_t x) { return (uint8_t)x; }
static float f32(uint32_t u) { float f; memcpy(&f,&u,4); return f; }
static uint32_t fbits(float f) { uint32_t u; memcpy(&u,&f,4); return u; }
static double f64(uint64_t u) { double d; memcpy(&d,&u,8); return d; }

static int unordered(double a, double b) { return a != a || b != b; }
static int ucomi_gt(double a, double b) { return !unordered(a,b) && a>b; }
static int ucomi_le(double a, double b) { return unordered(a,b) || a<=b; }

/* This matches MINSD's operand rule: if either operand is NaN or they compare
   equal, the source (right-hand) operand wins. */
static double minsd(double dest, double src)
{ return unordered(dest,src) || dest==src ? src : (dest<src ? dest : src); }

/* RVA 0x42650. image is a copy of the supplied image with writable data pages;
   helpers remain injected and are not claimed as recovered here. */
__declspec(dllexport) void recovered_instant_stop(void *event, uint8_t *image,
    instant_stop_helper helper, uint32_t *helper_r8)
{
    active_helper_r8=helper_r8;
    uint8_t *evt=(uint8_t *)event;
    uint64_t *ctx=(uint64_t *)(uintptr_t)*(uint64_t *)(evt+8);
    uint64_t game=ctx[0], meta=ctx[3];
    uint64_t bridge;
    uint64_t mode1,state2,state3,state4;
    uint32_t mode=0;
    if (!low_al(call(helper,0x22e60,game,meta,0,0,0,0,0))) goto store;
    game=ctx[0]; meta=ctx[3];
    bridge=call(helper,0x22cf0,game,meta,0,0,0,0,0);
    game=ctx[0];
    mode1=call(helper,0x250d0,game,bridge,0,0,0,0,0);
    game=ctx[0];
    state2=call(helper,0x25120,game,bridge,0,0,0,0,0);
    game=ctx[0];
    state3=call(helper,0x25170,game,bridge,0,0,0,0,0);
    game=ctx[0];
    state4=call(helper,0x251c0,game,bridge,0,0,0,0,0);
    memcpy(&mode,image+0x3043d0,4);
    uint32_t active_mode=mode;
    mode=0; /* R12D is the eventual value stored, initialized at entry. */
    game=ctx[0];
    if (active_mode==2) {
        uint64_t captured_game=game;
        uint32_t value=(uint32_t)call(helper,0x25490,captured_game,state2,0,0,0,0,0);
        *helper_r8=value;
        call(helper,0x25460,captured_game,state2,value,0,0,0,0);
        game=ctx[0];
        value=(uint32_t)call(helper,0x25490,game,state3,0,0,0,0,0);
        *helper_r8=value;
        call(helper,0x25460,game,state3,value,0,0,0,0);
        game=ctx[0];
        value=(uint32_t)call(helper,0x25490,game,state4,0,0,0,0,0);
        *helper_r8=value;
        call(helper,0x25460,game,state4,value,0,0,0,0);
        /* R12D starts at zero and the state-2 path never changes it. */
        mode=0;
        goto store;
    }
    if (active_mode!=1) {
        if (!low_al(call(helper,0x25430,game,mode1,0,0,0,0,0))) return;
        mode=1;
        goto store;
    }
    if (low_al(call(helper,0x25430,game,mode1,0,0,0,0,0))) return;
    game=ctx[0];
    uint64_t player=ctx[5];
    if (!low_al(call(helper,0x23780,game,player,0,0,0,0,0))) return;
    double start[3];
    game=ctx[0]; player=ctx[5];
    call(helper,0x23550,(uint64_t)(uintptr_t)start,game,player,0,0,0,0);
    game=ctx[0]; player=ctx[5];
    uint64_t yaw=call(helper,0x23170,game,player,0,0,0,0,0);
    game=ctx[0]; player=ctx[5];
    float rate=f32((uint32_t)call(helper,0x23b40,game,player,0,0,0,0,0));
    game=ctx[0]; player=ctx[5];
    if (low_al(call(helper,0x23690,game,player,0,0,0,0,0))) {
        double divisor=f64(*(uint64_t *)(image+0x1547a8));
        rate=(float)((double)rate/divisor);
    }
    uint32_t global=(uint32_t)*(uint64_t *)(image+0x1547b0);
    uint32_t third=(uint32_t)*(uint64_t *)(image+0x1547b4);
    double current_min=0.0;
    double third_distance=0.0;
    double origin_distance=start[0]*start[0]+start[2]*start[2];
    uint32_t index=999;
    for (unsigned candidate=0;candidate<3;candidate++) {
        uint32_t x3=candidate==0?global:(candidate==1?0:third);
        double generated[3];
        call(helper,0x29290,(uint64_t)(uintptr_t)generated,yaw,0,0,
             global,x3,fbits(rate));
        double left_copy[3],right_copy[3],sum[3];
        memcpy(left_copy,start,sizeof(left_copy));
        memcpy(right_copy,generated,sizeof(right_copy));
        call(helper,0x9400,(uint64_t)(uintptr_t)sum,
             (uint64_t)(uintptr_t)left_copy,(uint64_t)(uintptr_t)right_copy,0,0,0,0);
        /* The callback compares horizontal X/Z lanes; Y is carried through
           vector addition but does not contribute to this squared distance. */
        double distance=sum[0]*sum[0]+sum[2]*sum[2];
        if (candidate==2) third_distance=distance;
        if (candidate==0) {
            current_min=minsd(distance,origin_distance);
            index=ucomi_gt(origin_distance,distance)?UINT32_MAX:999;
        } else if (candidate==1) {
            double old=current_min;
            current_min=minsd(distance,old);
            if (ucomi_gt(old,distance)) index=0;
        } else {
            uint32_t prior=index;
            index=ucomi_le(current_min,distance)?prior:1;
        }
    }
    if (index==999) goto store;
    /* The machine code writes only R8B here. The dependency contract supplies
       the controlled helper-produced upper bits through helper_r8. */
    uint32_t first_value=(*helper_r8&0xffffff00u)|1u;
    *helper_r8=first_value;
    game=ctx[0]; call(helper,0x25460,game,state2,first_value,0,0,0,0);
    /* SETA from UCOMISD(current_min, third candidate distance). */
    game=ctx[0]; *helper_r8=(uint32_t)ucomi_gt(current_min,third_distance);
    call(helper,0x25460,game,state3,*helper_r8,0,0,0,0);
    uint32_t last_value=(*helper_r8&0xffffff00u)|(uint32_t)(index==UINT32_MAX);
    *helper_r8=last_value;
    game=ctx[0]; call(helper,0x25460,game,state4,last_value,0,0,0,0);
    mode=2;
store:
    memcpy(image+0x3043d0,&mode,4);
}
