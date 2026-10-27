#include <stdint.h>
#include <string.h>
#include <intrin.h>
#include <emmintrin.h>

typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t u64(const void *p){return *(const volatile uint64_t *)p;}
static uint32_t u32(const void *p){return *(const volatile uint32_t *)p;}
static uint16_t u16(const void *p){return *(const volatile uint16_t *)p;}
static int32_t s32(uint32_t b){int32_t v;memcpy(&v,&b,4);return v;}
static int64_t s64(uint64_t b){int64_t v;memcpy(&v,&b,8);return v;}
static float f32(const void *p){uint32_t b=u32(p);float v;memcpy(&v,&b,4);return v;}
static double f64(const void *p){uint64_t b=u64(p);double v;memcpy(&v,&b,8);return v;}
static uint32_t fb(float v){uint32_t b;memcpy(&b,&v,4);return b;}
static uint64_t db(double v){uint64_t b;memcpy(&b,&v,8);return b;}
static float from_fb(uint64_t v){uint32_t b=(uint32_t)v;return f32(&b);}
static double from_db(uint64_t v){return f64(&v);}
static void put32(void *p,uint32_t v){*(volatile uint32_t *)p=v;}
static void putd(void *p,double v){*(volatile uint64_t *)p=db(v);}

__declspec(dllexport) void recovered_criticals_update(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    uint8_t eligible=0;
    if(ctx[0x40]!=1) goto select_mode;
    uint32_t counter=u32(image+0x2fa328);
    if(counter){
        uint8_t cached=image[0x2fa32c];
        put32(image+0x2fa328,counter-1u);
        if(cached!=1) goto select_mode;
    } else {
        put32(image+0x2fa328,10);
        uint8_t chance=(uint8_t)call(0xa460,u32(image+0x2ec288),0,0,0);
        image[0x2fa32c]=chance;
        put32(image+0x2fa328,u32(image+0x2fa328)-1u);
        if(!chance) goto select_mode;
    }
    if(image[0x2ec2a8]==1 && !(uint8_t)call(0x29080,(uintptr_t)ctx,0,0,0)) goto select_mode;
    if(image[0x2ec2c8]==1 && !(uint8_t)call(0x380b0,u64(ctx),u64(ctx+0x28),0,0)) goto select_mode;
    {
        uint32_t previous=(uint32_t)call(0x239d0,u64(ctx),u64(ctx+0x28),0,0);
        uint32_t current=(uint32_t)call(0x23760,u64(ctx),u64(ctx+0x28),0,0);
        eligible=s32(current-previous)<11;
    }
select_mode:
    ;uint32_t mode=u32(image+0x2ec310);
    if(mode==0){
        _InterlockedExchange8((volatile char *)(image+0x2fa320),(char)eligible);
        int32_t limit=_mm_cvttss_si32(_mm_set_ss(f32(image+0x2ec250)));
        _InterlockedExchange16((volatile short *)(image+0x2fa322),(short)limit);
        image[0x2fa324]=0;
    } else if(mode==1){
        _InterlockedExchange8((volatile char *)(image+0x2fa320),0);
        uint8_t active=0;
        if(eligible && !(uint8_t)call(0x23780,u64(ctx),u64(ctx+0x28),0,0)){
            double velocity[3];
            call(0x23550,(uintptr_t)velocity,u64(ctx),u64(ctx+0x28),0);
            if(!(velocity[1]>=0.0)){
                if((uint32_t)call(0x239f0,u64(ctx),u64(ctx+0x28),0,0)!=10){
                    uint64_t target=call(0x22e10,u64(ctx),u64(ctx+0x18),0,0);
                    if(target) active=(uint32_t)call(0x24b50,u64(ctx),target,0,0)==2;
                }
            }
        }
        image[0x2fa324]=active;
    }
}

__declspec(dllexport) void recovered_criticals_timer(uint8_t *event,uint8_t *image,dependency call){
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    uint64_t timer=call(0x22c70,u64(ctx),u64(ctx+0x18),0,0);
    if(image[0x2fa324]==1){
        call(0x259c0,u64(ctx),timer,u32(image+0x2ec350),0);
        image[0x2fa32d]=1;
        double elapsed=f64(event+0x18)*f64(image+0x151818);
        float difference=f32(image+0x151810)-f32(image+0x2ec350);
        double accumulated=(double)difference*elapsed;
        accumulated=accumulated+f64(image+0x2fa330);
        putd(image+0x2fa330,accumulated);
        double cap=(double)f32(image+0x2ec388);
        if(accumulated>cap) putd(image+0x2fa330,cap);
    } else {
        double accumulated=f64(image+0x2fa330);
        if(accumulated>f64(image+0x151808)){
            float previous=from_fb(call(0x259f0,u64(ctx),timer,0,0));
            int32_t whole=_mm_cvttsd_si32(_mm_set_sd(accumulated));
            float adjusted=(float)whole+previous;
            call(0x25a10,u64(ctx),timer,fb(adjusted),0);
            putd(image+0x2fa330,f64(image+0x2fa330)-(double)whole);
        }
        if(image[0x2fa32d]==1){
            call(0x259c0,u64(ctx),timer,u32(image+0x151810),0);
            image[0x2fa32d]=0;
        }
    }
}

__declspec(dllexport) void recovered_criticals_packet(uint8_t *event,uint8_t *image,dependency call){
    uint64_t packet=call(0x26350,u64(event+8),u64(event+0x10),0,0);
    if(packet && (uint8_t)call(0x26390,u64(event+8),packet,0,0) &&
       s32(u32(event+0x20))>s32(u32(image+0x2fa348))){
        double position=from_db(call(0x26410,u64(event+8),packet,0,0));
        uint8_t flag=(uint8_t)call(0x263c0,u64(event+8),packet,0,0);
        if(flag || f64(image+0x2fa340)>position) image[0x2fa34c]=flag^1u;
        if((image[0x2fa320]&1) && (image[0x2fa34c]&1)){
            uint32_t step=((uint32_t)u16(image+0x2fa322)*0xcccdu)>>18;
            uint32_t total=u32(image+0x2fa338)+step;
            put32(image+0x2fa338,total);
            if(s32(total)>(int32_t)u16(image+0x2fa322)) put32(image+0x2fa338,u16(image+0x2fa322));
        } else put32(image+0x2fa338,0);
        putd(image+0x2fa340,position);
        put32(image+0x2fa348,u32(event+0x20));
    }
    if(s64(u64(event+0x18))<(int64_t)s32(u32(image+0x2fa338))) put32(event+0x24,1);
}

__declspec(dllexport) void recovered_criticals_disable(uint8_t *event,uint8_t *image,dependency call){
    if(u64(event+0x10)!=(uintptr_t)(image+0x2ec010) || event[0x18]!=0 || !(image[0x2fa32d]&1)) return;
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    uint64_t timer=call(0x22c70,u64(ctx),u64(ctx+0x18),0,0);
    call(0x259c0,u64(ctx),timer,u32(image+0x151820),0);
    image[0x2fa32d]=0;
}
