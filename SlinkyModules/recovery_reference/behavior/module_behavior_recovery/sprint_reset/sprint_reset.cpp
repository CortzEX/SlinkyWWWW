#include "sprint_reset.h"

#include <math.h>
#include <stddef.h>
#include <string.h>

static_assert(offsetof(sprint_reset_event, context) == 8, "callback context offset");
static_assert(offsetof(sprint_reset_context, action_arg) == 0x18, "action helper argument offset");
static_assert(offsetof(sprint_reset_context, target) == 0x28, "target offset");
static_assert(offsetof(sprint_reset_context, sprinting) == 0x40, "sprinting byte offset");

static uint32_t f32_bits(float x) { uint32_t b; memcpy(&b, &x, sizeof(b)); return b; }
static float bits_f32(uint64_t x) { uint32_t b=(uint32_t)x; float f; memcpy(&f,&b,sizeof(f)); return f; }
static double bits_f64(uint64_t x) { double d; memcpy(&d,&x,sizeof(d)); return d; }
static uint64_t f64_bits(double x) { uint64_t b; memcpy(&b,&x,sizeof(b)); return b; }

static sprint_call_result invoke(const sprint_reset_dependencies *deps, void *user,
                                 uint32_t rva, uint64_t rcx, uint64_t rdx,
                                 uint64_t r8, uint64_t r9,
                                 uint64_t xmm0, uint64_t xmm1, uint64_t xmm2)
{
    sprint_call_args args={rcx,rdx,r8,r9,xmm0,xmm1,xmm2};
    sprint_call_result empty={0,0,0,0,0};
    deps->dispatch(rva,&args,&empty,user);
    return empty;
}

/* Local action helper at 0x3b150. Its native indirect target remains injected. */
void recovered_sprint_action(const sprint_reset_globals *g, volatile sprint_reset_context *ctx,
                             uint32_t active_arg, const sprint_reset_dependencies *deps, void *user)
{
    sprint_call_result r=invoke(deps,user,0x22cf0,ctx->object,ctx->action_arg,0,0,0,0,0);
    uint32_t select_mode=g->mode;
    uint64_t selected;
    if (select_mode==2)
        r=invoke(deps,user,0x25210,ctx->object,r.rax,0,0,0,0,0);
    else if (select_mode==1)
        r=invoke(deps,user,0x25030,ctx->object,r.rax,0,0,0,0,0);
    else
        r=invoke(deps,user,0x250d0,ctx->object,r.rax,0,0,0,0,0);
    selected=r.rax;
    if (g->mode==2) {
        r=invoke(deps,user,0x236c0,ctx->object,ctx->target,(uint32_t)(active_arg^1u),r.r9,0,0,0);
    }
    uint64_t action_object=ctx->object;
    uint64_t final_r8;
    if ((uint8_t)active_arg != 0) {
        final_r8=(r.r8 & ~UINT64_C(0xff)) | (uint64_t)(g->mode==1);
    } else {
        r=invoke(deps,user,0x25490,action_object,selected,0,0,0,0,0);
        final_r8=(uint32_t)r.rax;
    }
    (void)invoke(deps,user,0x25460,action_object,selected,final_r8,0,0,0,0);
}

static float randomized_sample(const sprint_reset_dependencies *deps, void *user,
                               uint64_t storage, float x0, float x1, double scale)
{
    sprint_call_result random=invoke(deps,user,0xa050,0,0,0,0,f32_bits(x0),f32_bits(x1),0);
    sprint_call_result sample=invoke(deps,user,0xa510,UINT64_C(0x180000000)+storage,random.rax,0,0,0,0,f64_bits(scale));
    return bits_f32(sample.xmm0);
}

static float maxss_zero_second(float x)
{
    /* MAXSS returns its second operand for unordered inputs and equal zeros. */
    if (isnan(x) || x >= 0.0f) return x;
    return 0.0f;
}

__declspec(dllexport) void recovered_sprint_reset(
    sprint_reset_globals *g, sprint_reset_event *event,
    const sprint_reset_dependencies *deps, void *user)
{
    volatile sprint_reset_context *ctx=event->context;
    sprint_call_result r;
    double now, elapsed;
    float timer, duration;
    uint32_t mode;

    if (ctx->sprinting != 1) {
        if (g->phase==2) recovered_sprint_action(g,ctx,0,deps,user);
        g->phase=0; g->have_state=0; g->timer=0.0f;
        return;
    }

    r=invoke(deps,user,0x4c270,0,0,0,0,0,0,0);
    now=bits_f64(r.xmm0);
    elapsed=now-g->last_sample_time;
    if (elapsed >= 0.5) {
        uint64_t first=invoke(deps,user,0x23760,ctx->object,ctx->target,0,0,0,0,0).rax;
        uint64_t second=invoke(deps,user,0x239d0,ctx->object,ctx->target,0,0,0,0,0).rax;
        if ((uint32_t)first==(uint32_t)second) {
            g->last_sample_time=now;
            g->have_state=1;
        }
    }
    ++g->sample_count;
    r=invoke(deps,user,0x239f0,ctx->object,ctx->target,0,0,0,0,0);
    if ((uint32_t)r.rax==10)
        g->sample_count=0;

    timer=g->timer;
    if (timer > 0.0f) {
        timer=timer-1.0f;
        g->timer=timer;
        if (timer > 0.0f) {
            if (g->phase==2) recovered_sprint_action(g,ctx,((uint32_t)r.rdx&0xffffff00u)|1u,deps,user);
            return;
        }
    }

    mode=g->phase;
    if (mode==2) {
        recovered_sprint_action(g,ctx,0,deps,user);
        g->phase=0;
        return;
    }
    if (mode==1) {
        recovered_sprint_action(g,ctx,((uint32_t)r.rdx&0xffffff00u)|1u,deps,user);
        g->phase=2;
        g->have_state=0;
        duration=g->delay;
        if (g->randomize==1) {
            float sampled=randomized_sample(deps,user,0x2fc898,0.0f,1.0f,30.0);
            duration=maxss_zero_second(duration-sampled);
            r=invoke(deps,user,0xa050,0,0,0,0,f32_bits(0.05f),f32_bits(0.1f),0);
            r=invoke(deps,user,0xaa30,UINT64_C(0x1802fc8a8),r.rax,0,0,0,0,f64_bits(30.0));
            if ((uint8_t)r.rax!=0) {
                r=invoke(deps,user,0xa050,0,0,0,0,f32_bits(1.0f),f32_bits(2.0f),0);
                r=invoke(deps,user,0xa3e0,r.rax,0,0,0,0,0,0);
                duration=duration+bits_f32(r.xmm0);
            }
        }
        g->timer=duration+g->timer;
        return;
    }

    duration=g->duration;
    if (g->randomize==1)
        duration=duration+randomized_sample(deps,user,0x2fc888,0.0f,2.0f,5.0);
    if (g->have_state==1 && (g->wait_for_damage!=1 || g->sample_count==0) &&
        (g->require_weapon!=1 || (uint8_t)invoke(deps,user,0x380b0,ctx->object,ctx->target,0,0,0,0,0).rax!=0)) {
        g->timer=duration+g->timer;
        g->phase=1;
    }
}
