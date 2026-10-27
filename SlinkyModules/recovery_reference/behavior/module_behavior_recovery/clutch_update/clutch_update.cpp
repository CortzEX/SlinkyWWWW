#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <emmintrin.h>

typedef struct clutch_args {
    uint64_t gpr[4];              /* RCX, RDX, R8, R9 */
    uint64_t xmm[4];              /* XMM0..XMM3 low 64-bit lanes */
    uint64_t stack[4];            /* first four stack arguments */
} clutch_args;
typedef struct clutch_result { uint64_t rax, xmm0; } clutch_result;
typedef void (*clutch_dispatch)(uint32_t, const clutch_args *, clutch_result *, void *);

static uint64_t q(const void *p) { uint64_t v; memcpy(&v,p,8); return v; }
static uint32_t u32(const void *p) { uint32_t v; memcpy(&v,p,4); return v; }
static int32_t i32(const void *p) { int32_t v; memcpy(&v,p,4); return v; }
static uint32_t wrapped_abs_difference(uint32_t a,uint32_t b) {
    uint32_t ab=a-b,ba=b-a;
    return (int32_t)b<(int32_t)a ? ab : ba;
}
static int candidate_score_rejected(float score,float best_score,int64_t max_distance,int64_t distance) {
    /* UCOMISS/JBE accepts unordered scores as well as score <= best. */
    return score>best_score && max_distance<=distance;
}
/* Exposes the exact arithmetic primitive only to the bounded verifier. */
__declspec(dllexport) uint32_t clutch_absdiff_test_adapter(uint32_t a,uint32_t b) {
    return wrapped_abs_difference(a,b);
}
__declspec(dllexport) int clutch_score_gate_test_adapter(uint32_t score_bits,uint32_t best_bits,int64_t max_distance,int64_t distance) {
    float score,best;memcpy(&score,&score_bits,4);memcpy(&best,&best_bits,4);
    return candidate_score_rejected(score,best,max_distance,distance);
}
__declspec(dllexport) int clutch_threshold_test_adapter(uint32_t score_bits,uint32_t threshold_bits) {
    float score,threshold;memcpy(&score,&score_bits,4);memcpy(&threshold,&threshold_bits,4);
    return score>threshold;
}
static float f32(const void *p) { float v; memcpy(&v,p,4); return v; }
static double f64(const void *p) { double v; memcpy(&v,p,8); return v; }
static void w32(void *p,uint32_t v) { memcpy(p,&v,4); }
static void w64(void *p,uint64_t v) { memcpy(p,&v,8); }
static uint32_t fb(float v) { uint32_t b; memcpy(&b,&v,4); return b; }
static uint64_t db(double v) { uint64_t b; memcpy(&b,&v,8); return b; }
static int32_t cvtt(float x) { return _mm_cvttss_si32(_mm_set_ss(x)); }
static int32_t cvttd(double x) { return _mm_cvttsd_si32(_mm_set_sd(x)); }
static uint64_t ptr(const void *p) { return (uint64_t)(uintptr_t)p; }

static clutch_result invoke(clutch_dispatch d,void *user,uint32_t r,
    uint64_t rcx,uint64_t rdx,uint64_t r8,uint64_t r9,
    uint64_t x0,uint64_t x1,uint64_t x2,uint64_t x3,uint64_t s0,uint64_t s1)
{
    clutch_args a={{rcx,rdx,r8,r9},{x0,x1,x2,x3},{s0,s1,0,0}};
    clutch_result out={0,0};
    d(r,&a,&out,user);
    return out;
}
static clutch_result gcall(clutch_dispatch d,void *u,uint32_t r,uint64_t a,uint64_t b,uint64_t c,uint64_t e)
{ return invoke(d,u,r,a,b,c,e,0,0,0,0,0,0); }
static clutch_result xcall(clutch_dispatch d,void *u,uint32_t r,uint64_t x0,uint64_t x1,uint64_t x2)
{ return invoke(d,u,r,0,0,0,0,x0,x1,x2,0,0,0); }
static clutch_result gxcall(clutch_dispatch d,void *u,uint32_t r,uint64_t rcx,uint64_t rdx,uint64_t x0,uint64_t x1,uint64_t x2)
{ return invoke(d,u,r,rcx,rdx,0,0,x0,x1,x2,0,0,0); }
static clutch_result gx4call(clutch_dispatch d,void *u,uint32_t r,uint64_t rcx,uint64_t rdx,uint64_t x0,uint64_t x1,uint64_t x2,uint64_t x3)
{ return invoke(d,u,r,rcx,rdx,0,0,x0,x1,x2,x3,0,0); }
static clutch_result x4call(clutch_dispatch d,void *u,uint32_t r,uint64_t x0,uint64_t x1,uint64_t x2,uint64_t x3)
{ return invoke(d,u,r,0,0,0,0,x0,x1,x2,x3,0,0); }
static clutch_result gstack(clutch_dispatch d,void *u,uint32_t r,uint64_t a,uint64_t b,uint64_t c,uint64_t e,uint64_t s0,uint64_t s1)
{ return invoke(d,u,r,a,b,c,e,0,0,0,0,s0,s1); }
static uint64_t rv(clutch_result r) { return r.rax; }
static float rf(clutch_result r) { uint32_t b=(uint32_t)r.xmm0; float f; memcpy(&f,&b,4); return f; }
static double rd(clutch_result r) { double d; memcpy(&d,&r.xmm0,8); return d; }
static uint64_t packed2(float lo,float hi) { return (uint64_t)fb(lo)|((uint64_t)fb(hi)<<32); }

/* RVA 0x48a50. Every non-local game/runtime call stays an explicit endpoint. */
__declspec(dllexport) void recovered_clutch_48a50(
    uint8_t *event,uint8_t *image,clutch_dispatch dispatch,void *user)
{
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);
    uint64_t object=q(ctx), state=q(ctx+0x28);
    uint8_t *st=image+0x304a00;
    uint8_t *cfg=image+0x2f5000;
    image[0x304a1c]=0; image[0x304a2d]=0;
    if(ctx[0x40]!=1) return;

    uint8_t fall=(uint8_t)gcall(dispatch,user,0x23780,object,state,0,0).rax;
    uint32_t timer_result=(uint32_t)gcall(dispatch,user,0x239f0,object,state,0,0).rax;
    uint32_t change=u32(st+0x30)+1u;
    w32(st+0x30,timer_result==0?change:0);
    int32_t phase_active=i32(st+0x34)>0;
    if(phase_active) w32(st+0x34,u32(st+0x34)-1u);

    if(phase_active && fall && (uint8_t)gcall(dispatch,user,0x29f80,0,0,0,0).rax && cfg[0x930]) {
        uint64_t settings=rv(gcall(dispatch,user,0x22cf0,object,q(ctx+0x18),0,0));
        uint64_t value=rv(gcall(dispatch,user,0x25080,object,settings,0,0));
        if((uint8_t)gcall(dispatch,user,0x25490,object,value,0,0).rax) {
            uint64_t angle=rv(gcall(dispatch,user,0x23170,object,state,0,0));
            uint64_t offset=rv(gcall(dispatch,user,0x29850,0,0,0,0));
            angle=rv(gcall(dispatch,user,0x9de0,angle,offset,0,0));
            uint64_t silent=rv(gcall(dispatch,user,0x29ff0,0,0,0,0));
            double multiplier=f64(st+0x90)<0.0 ? f64(image+0x156160) : f64(image+0x156158);
            float lo=f32(image+0x156168), hi=f32(image+0x15616c);
            float a=rf(gcall(dispatch,user,0xa3e0,rv(xcall(dispatch,user,0xa050,fb(lo),fb(hi),0)),0,0,0));
            float lo_scaled=(float)((double)a*multiplier);
            float b=rf(gcall(dispatch,user,0xa3e0,rv(xcall(dispatch,user,0xa050,fb(lo),fb(hi),0)),0,0,0));
            float hi_scaled=(float)((double)b*multiplier);
            w64(st+0x90,db(f64(st+0x90)+(double)lo_scaled));
            uint64_t random_pair=rv(invoke(dispatch,user,0x9e60,packed2(lo_scaled,hi_scaled),0,0,0,0,fb(f32(cfg+0x868)),0,0,0,0));
            uint64_t sum=rv(gcall(dispatch,user,0x9de0,silent,random_pair,0,0));
            uint64_t delta=rv(gcall(dispatch,user,0x9e20,sum,angle,0,0));
            uint32_t adjusted=(uint32_t)xcall(dispatch,user,0xa210,(uint32_t)delta,0,0).xmm0;
            uint64_t final=(delta&UINT64_C(0xffffffff00000000))|adjusted;
            (void)gcall(dispatch,user,0x29820,final,0,0,0);
            image[0x304a2d]=1;
            w32(st+0x38,(uint32_t)cvtt(f32(image+0x2f57f8)));
            return;
        }
    }

    /* The placement search uses copied bounding boxes and checkpoint-owned
       tables; the source below retains their instruction-level order. */
    uint64_t aabb=rv(gcall(dispatch,user,0x23670,object,state,0,0));
    uint8_t base_box[0x60]={0};
    (void)gcall(dispatch,user,0x25640,ptr(base_box),object,aabb,0);
    uint64_t local=rv(gcall(dispatch,user,0x23990,object,state,0,0));
    uint8_t target_box[0x60]={0};
    (void)gcall(dispatch,user,0x25540,ptr(target_box),object,local,0);
    uint64_t yaw=rv(gcall(dispatch,user,0x23170,object,state,0,0));
    uint64_t off=rv(gcall(dispatch,user,0x29850,0,0,0,0));
    yaw=rv(gcall(dispatch,user,0x9de0,yaw,off,0,0));
    uint64_t stored_yaw=yaw;
    if((cfg[0x950]&fall)==0 && (i32(st+0x30)<11 || !cfg[0x970])) {
        uint64_t target=rv(gcall(dispatch,user,0x23930,object,state,0,0));
        if(target==0) {
            if(cfg[0x990]==1) {
                uint8_t orientation[0x40]={0};
                (void)gcall(dispatch,user,0x23550,ptr(orientation),object,state,0);
                double dot=rd(xcall(dispatch,user,0x13cfd0,q(orientation),q(orientation+16),0));
                if(dot==0.0) goto no_search;
                uint32_t angle_bits=(uint32_t)gcall(dispatch,user,0x23170,object,state,0,0).rax;
                float angle;memcpy(&angle,&angle_bits,4);
                double scale=f64(image+0x156080);
                float normalized=(float)((double)angle*scale/f64(image+0x156088)+scale);
                float fx=rf(xcall(dispatch,user,0xb1cf0,fb(normalized),0,0));
                float fy=rf(xcall(dispatch,user,0xb3590,fb(normalized),0,0));
                double ratio=((double)fy*f64(orientation+16)+(double)fx*f64(orientation))/dot;
                ratio=rd(xcall(dispatch,user,0x13cfa0,db(ratio),0,0));
                if(!(f64(image+0x156090)>ratio)) goto no_search;
            }
do_search:
            image[0x304a2c]=0;
            double ox=f64(base_box), oy=f64(base_box+8), oz=f64(base_box+16);
            double tx=f64(target_box), ty=f64(target_box+8), tz=f64(target_box+16);
            double gx=(ox+f64(base_box+24))*f64(image+0x156098);
            double gy=oy+f64(image+0x1560a0);
            double gz=(oz+f64(base_box+40))*f64(image+0x156098);
            uint64_t world=0;
            uint64_t vt=q((void *)(uintptr_t)object);
            if(*(int32_t *)(uintptr_t)vt!=0) world=rv(gcall(dispatch,user,0x242c0,object,0,0,0));
            double dx=rd(xcall(dispatch,user,0xb29b0,db(gx),0,0));
            double dy=rd(xcall(dispatch,user,0xb29b0,db(gy),0,0));
            double dz=rd(xcall(dispatch,user,0xb29b0,db(gz),0,0));
            int32_t ix=cvttd(dx),iy=cvttd(dy),iz=cvttd(dz);
            uint32_t vertical=0;
            if(f32(cfg+0x9c8)>0.0f) {
                float n=0.0f;
                int32_t step=1,query_y=iy;
                do {
                    clutch_result block=gstack(dispatch,user,0x24720,object,q(ctx+0x20),world,(uint32_t)ix,(uint32_t)query_y,(uint32_t)iz);
                    if((int32_t)gcall(dispatch,user,0x24280,object,rv(block),0,0).rax!=0) goto finish_search;
                    int32_t compared_step=step;
                    step=(int32_t)((uint32_t)step+1u);
                    query_y=(int32_t)((uint32_t)query_y-1u);
                    vertical++;
                    if(!(f32(cfg+0x9c8)>(float)compared_step))break;
                } while(1);

            }

            int32_t center[3]={ix,iy,iz},best[3]={ix,iy,iz};
            double start[3]={gx,gy,gz},target_start[3]={tx,ty,tz};
            double best_pos[3]={gx,gy,gz},best_target[3]={tx,ty,tz};
            float best_score=f32(image+0x1560a8);
            int64_t max_distance=-3; /* 0x49468 sentinel used before any retained winner */
            uint32_t attempts=0;
            int16_t *count_table=(int16_t *)(void *)(image+0x156280);
            int32_t select=cvtt(f32(cfg+0xa00));
            uint32_t count=(uint16_t)count_table[select];
            const uint16_t *points=(const uint16_t *)(const void *)(image+0x156290);

            /* Score the retained placement before testing the configured
               candidate table. 49f40 is an explicit internal-helper endpoint. */
            if((double)i32(st+0x24)<=gy) {
                clutch_result block=gstack(dispatch,user,0x24720,object,q(ctx+0x20),world,(uint32_t)i32(st+0x20),(uint32_t)i32(st+0x24),(uint32_t)i32(st+0x28));
                if((int32_t)gcall(dispatch,user,0x24280,object,rv(block),0,0).rax) {
                    uint8_t result_box[0x30]={0};
                    uint32_t retained_block[3]={(uint32_t)i32(st+0x20),(uint32_t)i32(st+0x24),(uint32_t)i32(st+0x28)};
                    uint32_t retained_direction[3]={(uint32_t)(retained_block[0]-(uint32_t)center[0]),(uint32_t)(retained_block[1]-(uint32_t)center[1]),(uint32_t)(retained_block[2]-(uint32_t)center[2])};
                    clutch_result eval=gstack(dispatch,user,0x49f40,ptr(target_start),stored_yaw,ptr(start),ptr(center),ptr(retained_direction),ptr(result_box));
                    float score=rf(eval);
                    /* 49554/4955b rejects only ordered score > threshold. */
                    if(!(score>f32(cfg+0xa38))) {
                        double dist=rd(gcall(dispatch,user,0x94b0,ptr(target_start),ptr(result_box),0,0));
                        if(dist<f64(image+0x1560b0)) {
                            uint64_t va=rv(gcall(dispatch,user,0x254f0,object,ptr(target_start),0,0));
                            uint64_t vb=rv(gcall(dispatch,user,0x254f0,object,ptr(result_box),0,0));
                            clutch_result found=gstack(dispatch,user,0x24860,object,q(ctx+0x20),va,vb,0,1);
                            if(rv(found)) {
                                uint32_t returned[3]={0};(void)gcall(dispatch,user,0x24ce0,ptr(returned),object,rv(found),0);
                                if(returned[0]==(uint32_t)i32(st+0x20)&&returned[1]==(uint32_t)i32(st+0x24)&&returned[2]==(uint32_t)i32(st+0x28)) {
                                    memcpy(best_target,result_box,24);
                                    best[0]=i32(st+0x20);best[1]=i32(st+0x24);best[2]=i32(st+0x28);
                                    best_score=score;
                                }
                            }
                        }
                    }
                }
            }

            if(best_score!=f32(image+0x1560a8) || best_score!=best_score) {
                uint32_t manhattan=wrapped_abs_difference((uint32_t)best[0],(uint32_t)center[0])+
                    wrapped_abs_difference((uint32_t)best[1],(uint32_t)center[1])+
                    wrapped_abs_difference((uint32_t)best[2],(uint32_t)center[2]);
                /* 49bee subtracts two from the zero-extended R8D sum in 64 bits. */
                max_distance=(int64_t)(uint64_t)manhattan-2;
            }
            for(uint32_t k=0;k<count;k++) {
                uint16_t code=points[k];int32_t oxp=(code&15)-8,oyp=((code>>4)&15)-8,ozp=((code>>8)&15)-8;
                int32_t cx=(int32_t)((uint32_t)center[0]+(uint32_t)oxp),cy=(int32_t)((uint32_t)center[1]+(uint32_t)oyp),cz=(int32_t)((uint32_t)center[2]+(uint32_t)ozp);
                clutch_result block=gstack(dispatch,user,0x24720,object,q(ctx+0x20),world,(uint32_t)cx,(uint32_t)cy,(uint32_t)cz);
                if((int32_t)gcall(dispatch,user,0x24280,object,rv(block),0,0).rax==0)continue;
                if(oxp==0 && ozp==0) {
                    if(cfg[0xa58])goto finish_search;
                    /* The centered hole is patched with two independently
                       smoothed random offsets before publishing the vectors. */
                    float spread=f32(cfg+0x868);
                    uint64_t r0=rv(xcall(dispatch,user,0xa050,0,fb(f32(image+0x1560b8)),0));
                    float jx=rf(gx4call(dispatch,user,0xa510,ptr(st+0xb8),r0,0,0,db(f64(image+0x1560c0)),0));
                    double random_x=f64(image+0x1560c8)+(double)(jx*spread);
                    uint64_t r1=rv(xcall(dispatch,user,0xa050,fb(f32(image+0x1560d0)),fb(f32(image+0x1560d4)),0));
                    float sy=rf(gx4call(dispatch,user,0xa510,ptr(st+0x98),r1,0,0,db(f64(image+0x1560c0)),0));
                    uint64_t r2=rv(xcall(dispatch,user,0xa050,fb(f32(image+0x1560d0)),fb(f32(image+0x1560d4)),0));
                    float sz=rf(gx4call(dispatch,user,0xa510,ptr(st+0xa8),r2,0,0,db(f64(image+0x1560c0)),0));
                    int32_t cx_next=(int32_t)((uint32_t)cx+1u),cz_next=(int32_t)((uint32_t)cz+1u);
                    float ax0=(float)((double)cx+random_x),ax1=(float)((double)cx_next-random_x);
                    float ax2=(float)(gx+(double)(sy*spread));
                    float az0=(float)((double)cz+random_x),az1=(float)((double)cz_next-random_x);
                    float az2=(float)(gz+(double)(sz*spread));
                    clutch_result ax=x4call(dispatch,user,0xa1f0,fb(ax0),fb(ax1),fb(ax2),0);
                    clutch_result az=x4call(dispatch,user,0xa1f0,fb(az0),fb(az1),fb(az2),0);
                    uint8_t picked[0x40]={0};
                    (void)invoke(dispatch,user,0x93b0,ptr(picked),0,0,0,0,db((double)rf(ax)),db(f64(image+0x1560c0)),db((double)rf(az)),0,0);
                    memcpy(st+0x48,picked,24);w32(st+0x20,(uint32_t)cx);w32(st+0x24,(uint32_t)cy);w32(st+0x28,(uint32_t)cz);image[0x304a2c]=1;
                    goto placement_found;
                }
                int64_t distance=(int64_t)abs(oxp)+abs(oyp)+abs(ozp);
                count=(uint16_t)count_table[distance];
                uint32_t candidate_block[3]={(uint32_t)center[0],(uint32_t)center[1],(uint32_t)center[2]};
                uint32_t candidate_direction[3]={(uint32_t)oxp,(uint32_t)oyp,(uint32_t)ozp};
                double evalbox[3]={0};
                clutch_result eval=gstack(dispatch,user,0x49f40,ptr(target_start),stored_yaw,ptr(start),ptr(candidate_block),ptr(candidate_direction),ptr(evalbox));
                float score=rf(eval);
                if(candidate_score_rejected(score,best_score,max_distance,distance))continue;
                double dist=rd(gcall(dispatch,user,0x94b0,ptr(target_start),ptr(evalbox),0,0));
                if(dist<f64(image+0x1560b0)) {
                    memcpy(best_target,evalbox,24);best[0]=cx;best[1]=cy;best[2]=cz;best_score=score;
                }
                attempts++;
            }
            if(best_score>f32(cfg+0xa38))goto finish_search;
            /* 498ba/498c5 publish one 24-byte helper output vector at
               image+304a48 (the 16-byte SIMD store overlaps the final
               qword store at +304a58). The normal winner route does not set
               the separate centered-placement flag at 304a2c. */
            memcpy(st+0x48,best_target,24);w32(st+0x20,(uint32_t)best[0]);w32(st+0x24,(uint32_t)best[1]);w32(st+0x28,(uint32_t)best[2]);
placement_found:
            (void)attempts;
            if(u32(cfg+0xac8)==1) (void)gcall(dispatch,user,0x2af50,ptr(ctx),0x1802f5580,0,0);
            else if(u32(cfg+0xac8)==2) (void)gcall(dispatch,user,0x2af50,ptr(ctx),0x1802f5580,1,0);
            uint64_t held=rv(gcall(dispatch,user,0x28a50,object,state,0,0));
            image[0x304a1c]=(uint8_t)gcall(dispatch,user,0x28b00,object,held,0,0).rax;
            if(image[0x304a1c]) {
                float amount=f32(cfg+0x830), low=f32(cfg+0x868);
                float high=(float)((double)low*f64(image+0x156098)+f64(image+0x1560c0));
                uint64_t rand=rv(xcall(dispatch,user,0xa050,fb(f32(image+0x1560d8)),fb(high),0));
                float sample=rf(gcall(dispatch,user,0xa3e0,rand,0,0,0));
                w32(st+0x38,(uint32_t)cvtt(_mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(sample),_mm_set_ss(amount)))));
                w32(st+0x34,10);image[0x304a3c]=cfg[0xaf0];
                goto timer_poll;
            }
        }
    }
finish_search:
    ;
no_search:
    /* 48d13-48d60: shared fallback timer state, reached after rejected
       searches and every no-search gate. */
    image[0x304a1c]=0;
    if(i32(st+0x38)>0) {
        w32(st+0x38,u32(st+0x38)-1u);
        w32(st+0x40,(uint32_t)cvtt(f32(cfg+0x7f8)));
        goto timer_poll;
    }
    if(i32(st+0x40)>0) {
        w32(st+0x40,u32(st+0x40)-1u);
        goto timer_poll;
    }
    if(image[0x304a3c]!=1) return;
    (void)gcall(dispatch,user,0x284f0,q(ctx+8),0x1802f5580,0,0);
    image[0x304a3c]=0;
    return;

timer_poll:
    if((uint8_t)gcall(dispatch,user,0x29800,1000,0,0,0).rax==0) return;
    image[0x304a2d]=1;
    if(image[0x304a1c]==0) {
        if(i32(st+0x38)>0) return;
        if(i32(st+0x40)<1) {
            /* 48ffc disables the latched input only when it was armed. */
            if(image[0x304a3c]!=1) return;
            (void)gcall(dispatch,user,0x284f0,q(ctx+8),0x1802f5580,0,0);
            image[0x304a3c]=0;
            return;
        }
        if((uint8_t)gcall(dispatch,user,0x29f80,0,0,0,0).rax==0) return;
        uint64_t angle=rv(gcall(dispatch,user,0x23170,object,state,0,0));
        uint64_t offset=rv(gcall(dispatch,user,0x29850,0,0,0,0));
        uint64_t shifted=rv(gcall(dispatch,user,0x9de0,angle,offset,0,0));
        uint64_t phase=rv(gcall(dispatch,user,0x29ff0,0,0,0,0));
        uint64_t delta=rv(gcall(dispatch,user,0x9e20,phase,shifted,0,0));
        uint32_t adjusted=(uint32_t)xcall(dispatch,user,0xa210,(uint32_t)delta,0,0).xmm0;
        float rate=(float)((double)f32(image+0x1560d8)/(double)i32(st+0x40));
        uint64_t packed=(delta&UINT64_C(0xffffffff00000000))|adjusted;
        uint64_t final=rv(invoke(dispatch,user,0x9e60,packed,0,0,0,0,fb(rate),0,0,0,0));
        (void)gcall(dispatch,user,0x29820,final,0,0,0);
    } else {
        /* 48d81 onward: active-latch geometry gate and recovered smoothing
           continuation. Game and math calls remain explicit dependencies. */
        double current[4]={0}, expanded[4]={0};
        (void)invoke(dispatch,user,0x233b0,ptr(current),object,state,0,0,0,0,0,0,0);
        (void)invoke(dispatch,user,0x9430,ptr(expanded),ptr(current),0,0,0,0,
                     q(image+0x1560e8),0,0,0);
        double query[6]={
            (double)i32(st+0x20)+f64(image+0x1560f0),
            (double)i32(st+0x24)+f64(image+0x1560f8),
            (double)i32(st+0x28)+f64(image+0x156100),
            (double)i32(st+0x20)+f64(image+0x156108),
            (double)i32(st+0x24)+1.0,
            (double)i32(st+0x28)+f64(image+0x1560e0)};
        double target[3]={f64(target_box),f64(target_box+8),f64(target_box+16)};
        double collision[3]={expanded[0],expanded[1],expanded[2]},collision_out[3]={0};
        uint64_t hit=rv(gcall(dispatch,user,0x9b00,ptr(query),ptr(target),ptr(collision),ptr(collision_out)));
        if((uint8_t)hit && collision_out[1]<(double)i32(st+0x24)+f64(image+0x156110)) return;
        double selected[3]={f64(target_box),f64(target_box+8),f64(target_box+16)};
        double retained[3]={f64(st+0x48),f64(st+0x50),f64(st+0x58)};
        uint64_t packed=rv(gcall(dispatch,user,0x9f80,ptr(selected),ptr(retained),0,0));
        uint32_t gate_bits=(uint32_t)(packed>>32); float gate; memcpy(&gate,&gate_bits,4);
        uint64_t mixed=rv(gcall(dispatch,user,0x9e20,packed,stored_yaw,0,0));
        uint32_t high_bits=(uint32_t)(mixed>>32); float high; memcpy(&high,&high_bits,4);
        float gate_value;
        if(!((double)gate>f64(image+0x156118))) {
            gate_value=rf(xcall(dispatch,user,0xa210,(uint32_t)mixed,0,0));
        } else {
            uint64_t random=rv(xcall(dispatch,user,0xa050,fb(f32(image+0x156120)),fb(f32(image+0x156124)),0));
            gate_value=rf(gx4call(dispatch,user,0xa510,ptr(st+0x60),random,0,0,q(image+0x156098),0))*f32(image+0x2f5868);
        }
        float cfg_scale=f32(cfg+0x868);
        double scale=f64(image+0x156128), bias=f64(image+0x1560c0);
        float random_low=(float)((double)cfg_scale*scale+bias);
        float random_high=f32(image+0x1560d8);
        float state_scale=f32(cfg+0x8a0);
        uint64_t ra=rv(xcall(dispatch,user,0xa050,fb(random_low),fb(random_high),0));
        float state_a=rf(gx4call(dispatch,user,0xa870,ptr(image+0x304a70),ra,0,0,
                                 q(image+0x156130),q(image+0x1560c0)))*state_scale;
        float random_low2=(float)((double)cfg_scale*scale+bias);
        uint64_t rb=rv(xcall(dispatch,user,0xa050,fb(random_low2),fb(random_high),0));
        float state_b=rf(gx4call(dispatch,user,0xa870,ptr(image+0x304a80),rb,0,0,
                                 q(image+0x156130),q(image+0x1560c0)))*state_scale;
        uint32_t sign_mask=u32(image+0x156140);
        uint32_t first=(uint32_t)xcall(dispatch,user,0xa1f0,fb(state_a)^sign_mask,fb(state_a),fb(gate_value)).xmm0;
        uint32_t second=(uint32_t)xcall(dispatch,user,0xa1f0,fb(state_b)^sign_mask,fb(state_b),fb(high)).xmm0;
        float accum_a=f32(cfg+0x8d8);
        float lo=f32(image+0x156150),hi=f32(image+0x1560b8);
        uint64_t rc=rv(xcall(dispatch,user,0xa050,fb(lo),fb(hi),0));
        accum_a+=rf(gx4call(dispatch,user,0xa870,ptr(image+0x304a70),rc,0,0,
                             q(image+0x156130),q(image+0x1560c0)));
        float accum_b=f32(cfg+0x8d8);
        uint64_t rd0=rv(xcall(dispatch,user,0xa050,fb(lo),fb(hi),0));
        accum_b+=rf(gx4call(dispatch,user,0xa870,ptr(image+0x304a80),rd0,0,0,
                            q(image+0x156130),q(image+0x1560c0)));
        accum_a=accum_a*gate_value;
        accum_b=accum_b*high;
        float out_lo=rf(xcall(dispatch,user,0xa2b0,first,fb(accum_a),fb(f32(cfg+0x910))));
        float out_hi=rf(xcall(dispatch,user,0xa2b0,second,fb(accum_b),fb(f32(cfg+0x910))));
        (void)gcall(dispatch,user,0x29820,packed2(out_lo,out_hi),0,0,0);
    }
    return;
}
