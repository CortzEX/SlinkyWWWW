#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static double g(const void *p){double v;memcpy(&v,p,8);return v;}
static void pd(void *p,uint32_t v){memcpy(p,&v,4);}
static void pg(void *p,double v){memcpy(p,&v,8);}
static float ff(uint64_t n){uint32_t v=(uint32_t)n;return f(&v);}
static uint32_t fb(float v){return d(&v);}
static double add(double a,double b){return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(a),_mm_set_sd(b)));}
static double mul(double a,double b){return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(a),_mm_set_sd(b)));}
static double divide(double a,double b){return _mm_cvtsd_f64(_mm_div_sd(_mm_set_sd(a),_mm_set_sd(b)));}
static float roundf(double a){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(a)));}
static float af(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float mf(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float df(float a,float b){return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static uint64_t random_range(dependency call,float lo,float hi){return call(0xa050,fb(lo),fb(hi),0,0);}
static float smooth(dependency call,uint8_t *image,uint32_t state,uint64_t sample,uint64_t period){return ff(call(0xa510,(uintptr_t)(image+state),sample,period,0));}
static void emit(dependency call,uint8_t button,uint8_t pressed){call(0x4c390,button,pressed,0,0);}

extern "C" __declspec(dllexport) void recovered_auto_clicker_2ca10(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);
    uint64_t settings=call(0x22cf0,q(ctx),q(ctx+0x18),0,0);
    uint64_t key=call(0x25270,q(ctx),settings,0,0);
    uint32_t code=(uint32_t)call(0x25410,q(ctx),key,0,0);image[0x2f7c90]=(code==0xffffff9d);
    if(ctx[0x40]!=1)return;
    uint64_t angle=call(0x23170,q(ctx),q(ctx+0x28),0,0);memcpy(image+0x2f7c88,&angle,8);
    uint8_t *other=(uint8_t *)(uintptr_t)q(image+0x1505a0);
    if(other[0x14]==0)call(0x22eb0,q(ctx),q(ctx+0x18),0,0);
}
extern "C" __declspec(dllexport) void recovered_auto_clicker_2d140(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);if(ctx[0x40]!=1)return;
    uint64_t hit=call(0x22e10,q(ctx),q(ctx+0x18),0,0);
    uint32_t kind=hit?(uint32_t)call(0x24b50,q(ctx),hit,0,0):0;pd(image+0x2f7cd0,kind);
}
static void cleanup(uint8_t *image,double delay){pg(image+0x2f7c98,delay);pd(image+0x2e9540,0xffffffff);}
static void menu(uint8_t *ctx,uint8_t *image,dependency call,uint8_t physical,uint8_t synthetic,double idle){
    uint64_t game,screen,inventory,slot;
    uint32_t slot_id;
    if(synthetic&1)emit(call,image[0x2f7c90]^1,(uint8_t)(~physical)&1);
    if(!call(0x22c90,q(ctx),q(ctx+0x18),0,0)){cleanup(image,idle);return;}
    uint8_t *keys=(uint8_t *)(uintptr_t)q(ctx+0x30);uint8_t primary=keys[1];
    if(primary!=1 || image[0x2f7cb8]!=1){image[0x2f7cb8]=(primary==1);goto idle_delay;}
    if(image[0x2e9560]!=1 || !((keys[0x62]|keys[0x63])&1))goto idle_delay;
    game=q(ctx);
    screen=call(0x22c90,game,q(ctx+0x18),0,0);
    inventory=call(0x23f40,game,q(ctx+0x28),0,0);
    slot=call(0x25b60,game,screen,0,0);if(!slot)goto idle_delay;
    if(call(0x25ad0,game,inventory,0,0))goto idle_delay;
    slot_id=(uint32_t)call(0x26190,game,slot,0,0);if(slot_id==d(image+0x2e9540))goto idle_delay;
    pd(image+0x2e9540,slot_id);
    if(!call(0x261b0,game,slot,0,0)){
        uint64_t sample=random_range(call,f(image+0x150338),f(image+0x15033c));
        if((uint8_t)call(0xaa30,(uintptr_t)(image+0x2f7cc0),sample,q(image+0x150340),0))goto idle_delay;
    }
    emit(call,1,1);
    if(image[0x2e9580]==1){
        uint64_t sample=random_range(call,f(image+0x150350),f(image+0x150354));
        uint8_t longer=(uint8_t)call(0xaa30,(uintptr_t)(image+0x2f7ca8),sample,q(image+0x150340),0);
        uint32_t range=longer?0x150360:0x150358;
        sample=random_range(call,f(image+range),f(image+range+4));
        float delay=ff(call(0xa3e0,sample,0,0,0));pg(image+0x2f7c98,add((double)delay,g(image+0x2f7c98)));return;
    }
    pg(image+0x2f7c98,add(g(image+0x150348),g(image+0x2f7c98)));return;
idle_delay:
    pg(image+0x2f7c98,add(g(image+(image[0x2e9580]!=0?0x150368:0x150348)),g(image+0x2f7c98)));
}
extern "C" __declspec(dllexport) void recovered_auto_clicker_2ca90(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);
    uint64_t timer_obj=call(0x22c70,q(ctx),q(ctx+0x18),0,0);
    double elapsed=g(event+0x18);
    float speed=ff(call(0x259a0,q(ctx),timer_obj,0,0));
    double consumed=mul((double)speed,elapsed);
    double remaining=_mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(g(image+0x2f7c98)),_mm_set_sd(consumed)));
    remaining=_mm_cvtsd_f64(_mm_max_sd(_mm_load_sd((double *)(image+0x150328)),_mm_set_sd(remaining)));
    pg(image+0x2f7c98,remaining);if(!(0.0>=remaining))return;
    uint8_t *keys=(uint8_t *)(uintptr_t)q(ctx+0x30);uint8_t physical=keys[image[0x2f7c90]+1],synthetic=(physical&2)>>1;
    double idle=g(image+0x150330);uint64_t period=q(image+0x150378);
    float random_high=f(image+0x150384),one=f(image+0x1503a0),divisor=f(image+0x1503a8);
    for(;;){
        if(ctx[0x40]==0){menu(ctx,image,call,physical,synthetic,idle);return;}
        if(!((physical|synthetic)&1)){cleanup(image,idle);return;}
        if(d(image+0x2f7cd0)==1 && image[0x2e95a0]!=0)goto reject;
        if(image[0x2e95c0]==1 && !(uint8_t)call(0x380b0,q(ctx),q(ctx+0x28),0,0))goto reject;
        if(image[0x2e95e0]==1){
            if((uint8_t)call(0x23f90,q(ctx),q(ctx+0x28),0,0))goto reject;
            if((physical&synthetic)&1)goto reject;
        } else if((physical&synthetic)&1){physical=1;goto release_cleanup;}
        if(physical&1){
            emit(call,image[0x2f7c90]^1,0);remaining=add(g(image+0x2f7ca0),g(image+0x2f7c98));pg(image+0x2f7c98,remaining);
        } else {
            emit(call,image[0x2f7c90]^1,1);
            float rate=f(image+0x2e9618);
            if(image[0x2e9638]==1){
                uint64_t sample=random_range(call,f(image+0x150370),f(image+0x150374));float amplitude=smooth(call,image,0x2f7ce8,sample,period);
                float low=f(image+0x150380);
                sample=random_range(call,low,random_high);float slow=smooth(call,image,0x2f7d08,sample,q(image+0x150388));
                sample=random_range(call,low,random_high);float medium=smooth(call,image,0x2f7d18,sample,period);
                sample=random_range(call,f(image+0x150390),f(image+0x150394));float fast=smooth(call,image,0x2f7d28,sample,q(image+0x150398));
                rate=mf(rate,af(af(af(slow,one),medium),fast));
                float wave=ff(call(0xab00,(uintptr_t)(image+0x2f7cf8),0,0,0));rate=mf(rate,af(mf(wave,amplitude),one));
            }
            float interval;uint32_t mode=d(image+0x2e9680);
            if(mode==1 && image[0x2f7d00]==1){uint32_t quick=0x3c656042;interval=f(&quick);image[0x2f7d00]=0;}
            else {
                interval=mode==1?roundf(add(divide(g(image+0x1503c0),(double)rate),g(image+0x1503c8))):df(f(image+0x1503a4),rate);
                uint64_t angle=call(0x23170,q(ctx),q(ctx+0x28),0,0);
                float turn=ff(call(0x9ee0,angle,q(image+0x2f7c88),0,0));float adjustment=af(df(turn,divisor),0.0f);
                uint8_t *target=(uint8_t *)(uintptr_t)q(ctx+0x38);
                if(!q(target+8) || g(target+0x10)>g(image+0x1503b0))adjustment=roundf(add((double)adjustment,g(image+0x1503b8)));
                uint8_t adjusted=(uint8_t)call(0x2d3b0,(uintptr_t)&interval,fb(adjustment),0,0);
                if(mode==1 && !adjusted){
                    uint64_t sample=random_range(call,f(image+0x1503d0),f(image+0x1503d4));
                    uint8_t gate=(uint8_t)call(0xaa30,(uintptr_t)(image+0x2f7cd8),sample,period,0);
                    image[0x2f7d00]=(uint8_t)call(0xa460,fb((float)gate),0,0,0);
                }
            }
            remaining=add(g(image+0x2f7c98),(double)interval);pg(image+0x2f7c98,remaining);pg(image+0x2f7ca0,(double)interval);
        }
        physical^=1;synthetic^=1;if(!(0.0>=remaining))return;
        continue;
reject:
        idle=0.;if(!(synthetic&1)){cleanup(image,idle);return;}
release_cleanup:
        physical=(uint8_t)(~physical)&1;emit(call,image[0x2f7c90]^1,physical);cleanup(image,0.);return;
    }
}
