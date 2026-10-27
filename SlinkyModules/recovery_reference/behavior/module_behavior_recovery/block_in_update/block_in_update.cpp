#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
#include "../random_primitives/random_primitives.h"

typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
typedef uint64_t (*dependency4)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
double *recovered_vector_adjust_95c0(double *,const double *,uint8_t *);
void *recovered_geometry_add_9400(double *,const double *,const double *);
void *recovered_geometry_pair_96b0(void *,const void *,const void *);
uint8_t recovered_geometry_intersects_97d0(const double *,const double *);
uint64_t recovered_angle_add_9de0(uint64_t,uint64_t);
uint64_t recovered_angle_subtract_9e20(uint64_t,uint64_t);
uint64_t recovered_angle_scale_9e60(uint64_t,float);
uint64_t recovered_target_angle_9f80(const double *,const double *,uint8_t *,dependency4);
float recovered_angle_wrap_a210(float,uint8_t *,dependency4);
float recovered_float_clamp_a1f0(float,float,float);

static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static double g(const void *p){double v;memcpy(&v,p,8);return v;}
static uint32_t fb(float v){return d(&v);}
static float ff(uint64_t v){uint32_t b=(uint32_t)v;return f(&b);}
static uint64_t pack(float a,float b){return fb(a)|((uint64_t)fb(b)<<32);}
static void wq(void *p,uint64_t v){memcpy(p,&v,8);}
static void wd(void *p,uint32_t v){memcpy(p,&v,4);}
static float af(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float sf(float a,float b){return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float mf(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static double ad(double a,double b){return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(a),_mm_set_sd(b)));}
static double sd(double a,double b){return _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(a),_mm_set_sd(b)));}
static double md(double a,double b){return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(a),_mm_set_sd(b)));}
static float narrow(double v){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(v)));}
static float intfloat(uint32_t v){return _mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),(int32_t)v));}
static double intdouble(uint32_t v){return (double)(int32_t)v;}
static uint32_t trunc32(double v){return (uint32_t)_mm_cvttsd_si32(_mm_set_sd(v));}
static double absolute(double v,uint64_t mask){uint64_t b=q(&v)&mask;return g(&b);}

__declspec(dllexport) uint64_t recovered_angle_lerp_9e90(uint64_t a,uint64_t b,float t){
    return pack(af(mf(sf(ff(b),ff(a)),t),ff(a)),af(mf(sf(ff(b>>32),ff(a>>32)),t),ff(a>>32)));
}
__declspec(dllexport) uint64_t block_in_lerp_adapter(uint8_t *event,uint8_t *image,dependency call){
    (void)image;(void)call;return recovered_angle_lerp_9e90(q(event),q(event+8),f(event+16));
}

__declspec(thread) static dependency active;
static uint64_t bridge(uint32_t r,uint64_t a,uint64_t b,uint64_t c,uint64_t d_){return active(r,a,b,c,d_,0,0);}
static float smooth(uint8_t *image,dependency call,uint32_t state,uint64_t bounds,uint64_t period){
    return ff(call(0xa510,(uintptr_t)(image+state),bounds,period,0,0,0));
}
static double library_double(dependency call,uint32_t r,double a,double b){uint64_t result=call(r,q(&a),q(&b),0,0,0,0);return g(&result);}
static int allowed(uint8_t *ctx,dependency call,uint64_t cache,uint32_t x,uint32_t y,uint32_t z){
    uint64_t block=call(0x24720,q(ctx),q(ctx+0x20),cache,x,y,z);
    uint32_t type=(uint32_t)call(0x24280,q(ctx),block,0,0,0,0);
    return type<=31 && ((UINT32_C(0x80000301)>>type)&1);
}
static int centered(const double *self,uint8_t *image,dependency call){
    double sx=self[0],sz=self[2],one=g(image+0x1568c0);
    double ax=library_double(call,0xb2170,sx,one);
    uint64_t mask=q(image+0x156890);ax=absolute(ax,mask);
    double az=library_double(call,0xb2170,sz,one);
    double upper=g(image+0x1568c8),lower=g(image+0x1568d0);az=absolute(az,mask);
    return upper>=ax && ax>=lower && az>=lower && upper>=az;
}
static void update(uint8_t *event,uint8_t *image,dependency call){
    image[0x304b1c]=0;wd(image+0x304b20,0);
    uint8_t *ctx=(uint8_t *)(uintptr_t)q(event+8);
    if(ctx[0x40]!=1)goto cleanup;
    uint8_t ground=(uint8_t)call(0x23780,q(ctx),q(ctx+0x28),0,0,0,0);
    if(!((~image[0x2f6330]|ground)&1))goto cleanup;
    double self[3];call(0x23030,(uintptr_t)self,q(ctx),q(ctx+0x28),0,0,0);
    if((uint8_t)call(0x23020,q(ctx),0,0,0,0,0)){
        double copy[3];memcpy(copy,self,24);recovered_vector_adjust_95c0(self,copy,image);
    }
    double selfy=self[1],fx=library_double(call,0xb29b0,self[0],0.);
    double fy=ad(library_double(call,0xb29b0,selfy,0.),g(image+0x156880));
    double fz=library_double(call,0xb29b0,self[2],0.);
    if(absolute(sd(selfy,g(image+0x304b30)),q(image+0x156890))>g(image+0x1568a0))wq(image+0x304b10,0);
    uint32_t x=trunc32(fx),y=trunc32(fy),z=trunc32(fz);wq(image+0x304b30,q(&selfy));
    uint64_t cache=0,game=q(ctx);
    if(d((void *)(uintptr_t)q((void *)(uintptr_t)game)))cache=call(0x242c0,game,0,0,0,0,0);
    unsigned probe;
    for(probe=0;probe<10;probe++){
        if((q(image+0x304b10)>>probe)&UINT64_C(0x100000000))break;
        const int8_t *offset=(const int8_t *)(image+0x156b80+probe*3);
        if(!allowed(ctx,call,cache,x+(uint32_t)offset[0],y+(uint32_t)offset[1],z+(uint32_t)offset[2]))break;
    }
    double target[3];unsigned bit;
    if(probe==0||probe==10){
        double size[3]={g(image+0x156ba8),g(image+0x156bb0),1.};
        for(unsigned attempt=0;attempt<4;attempt++){
            unsigned dir=(d(image+0x304b18)+attempt)&3;
            int8_t dx=(int8_t)image[0x156b9e+dir*2],dz=(int8_t)image[0x156b9f+dir*2];
            uint64_t captured_game=q(ctx),box_object=call(0x23670,captured_game,q(ctx+0x28),0,0,0,0);
            double playerbox[6];call(0x25640,(uintptr_t)playerbox,captured_game,box_object,0,0,0);
            uint32_t nx=x+(uint32_t)dx,nz=z+(uint32_t)dz;
            double base[3]={intdouble(nx),intdouble(y),intdouble(nz)},end[3],box[6];
            recovered_geometry_add_9400(end,base,size);recovered_geometry_pair_96b0(box,base,end);
            if(recovered_geometry_intersects_97d0(playerbox,box))continue;
            unsigned level;
            for(level=0;level<3;level++){
                if((d(image+0x304b10)>>((dir*3+level)&31))&1)continue;
                if(allowed(ctx,call,cache,nx,y+level,nz) && !allowed(ctx,call,cache,nx,y+level-1,nz))break;
            }
            if(level==3)continue;
            uint32_t bounds_rva=level?0x1568b0:0x1568a8;
            uint64_t bounds=recovered_a050(f(image+bounds_rva),f(image+bounds_rva+4));
            uint64_t period=q(image+0x1568b8);double half=g(&period);
            float a=smooth(image,call,0x304b58,bounds,period);
            double tx=sd(half,(double)mf(a,(float)dx));
            float b=smooth(image,call,0x304b68,bounds,period);
            double tz=sd(half,(double)mf(b,(float)dz));
            target[0]=ad(tx,intdouble(nx));target[1]=intdouble(y+level);target[2]=ad(tz,intdouble(nz));
            bit=dir*3+level;goto aim;
        }
        if((ground&1)&&centered(self,image,call))goto cleanup;
        return;
    }
    bit=32+(probe>=5&&probe<=8?probe-4:0);
    unsigned direct=probe>=5&&probe<=8?probe-4:probe;
    if(direct==1||direct==3){
        target[0]=intdouble(x+(direct==3));float yfloat=intfloat(y);
        uint64_t bounds=recovered_a050(f(image+0x1568e4),f(image+0x1568e8));
        uint64_t period=q(image+0x1568b8);
        target[1]=(double)af(smooth(image,call,0x304b38,bounds,period),yfloat);
        float zfloat=intfloat(z);uint32_t r=direct==1?0x1568dc:0x1568ec;
        bounds=recovered_a050(f(image+r),f(image+r+4));
        target[2]=(double)af(smooth(image,call,0x304b48,bounds,period),zfloat);
    }else if(direct==2||direct==4){
        float xfloat=intfloat(x),yfloat=intfloat(y);uint32_t r=direct==2?0x1568ec:0x1568dc;
        uint64_t bounds=recovered_a050(f(image+r),f(image+r+4));uint64_t period=q(image+0x1568b8);
        float a=smooth(image,call,0x304b38,bounds,period);
        bounds=recovered_a050(f(image+0x1568e4),f(image+0x1568e8));
        float b=smooth(image,call,0x304b48,bounds,period);
        target[0]=(double)af(a,xfloat);target[1]=(double)af(b,yfloat);target[2]=intdouble(z+(direct==4));
    }else{
        float xfloat=intfloat(x),lo=f(image+0x1568b4),hi=f(image+0x1568d8);
        uint64_t bounds=recovered_a050(lo,hi),period=q(image+0x1568b8);
        target[0]=(double)af(smooth(image,call,0x304b38,bounds,period),xfloat);target[1]=intdouble(y+4);
        float zfloat=intfloat(z);bounds=recovered_a050(lo,hi);
        target[2]=(double)af(smooth(image,call,0x304b48,bounds,period),zfloat);
    }
aim:
    if(!(uint8_t)call(0x29800,500,0,0,0,0,0))goto cleanup;
    call(0x2ade0,(uintptr_t)ctx,(uintptr_t)(image+0x2f6108),1,UINT64_C(0x18004bc60),0,0);
    uint64_t item=call(0x28a50,q(ctx),q(ctx+0x28),0,0,0,0);
    if(!(uint8_t)call(0x28b00,q(ctx),item,0,0,0,0))goto cleanup;
    uint64_t angle=call(0x23170,q(ctx),q(ctx+0x28),0,0,0,0),offset=call(0x29850,0,0,0,0,0,0);
    uint64_t combined=recovered_angle_add_9de0(angle,offset);
    uint64_t position=call(0x23990,q(ctx),q(ctx+0x28),0,0,0,0);double eye[3];
    call(0x25540,(uintptr_t)eye,q(ctx),position,0,0,0);
    uint64_t desired=recovered_target_angle_9f80(eye,target,image,bridge);
    uint64_t delta=recovered_angle_subtract_9e20(desired,combined);
    float pitch=ff(delta>>32),yaw=recovered_angle_wrap_a210(ff(delta),image,bridge);
    double half=g(image+0x1568b8);float factor=narrow(ad(md((double)f(image+0x2f6368),half),half));
    uint64_t scaled=recovered_angle_scale_9e60(pack(yaw,pitch),factor);
    float lo=f(image+0x1568f4),hi=f(image+0x1568f0);
    uint64_t bounds=recovered_a050(lo,hi),period=q(image+0x1568f8);
    float rx=smooth(image,call,0x304b78,bounds,period);
    bounds=recovered_a050(lo,hi);float ry=smooth(image,call,0x304b88,bounds,period);
    float rate=f(image+0x156900);rx=mf(rx,rate);float setting=f(image+0x2f6368);
    rx=mf(rx,setting);ry=mf(mf(rate,ry),setting);
    uint32_t sign=d(image+0x156910);
    float cx=recovered_float_clamp_a1f0(ff(fb(rx)^sign),rx,yaw),cy=recovered_float_clamp_a1f0(ff(sign^fb(ry)),ry,pitch);
    uint64_t result=recovered_angle_lerp_9e90(scaled,pack(cx,cy),f(image+0x156920));
    call(0x29820,result,0,0,0,0,0);
    uint32_t mask=d(image+0x156930);float ax=ff(fb(sf(yaw,ff(result)))&mask),ay=ff(fb(sf(pitch,ff(result>>32)))&mask);
    if(f(image+0x156940)>af(ay,ax)){
        uint64_t a=call(0x22cf0,q(ctx),q(ctx+0x18),0,0,0,0);
        a=call(0x24f90,q(ctx),a,0,0,0,0);call(0x25380,q(ctx),a,0,0,0,0);
        wq(image+0x304b10,q(image+0x304b10)|(UINT64_C(1)<<(bit&63)));
    }
    image[0x304b1c]=1;
    double sx=self[0],sz=self[2];
    if(centered(self,image,call)){wd(image+0x304b20,2);return;}
    double center[3];center[0]=ad(library_double(call,0xb29b0,sx,0.),half);center[1]=self[1];
    center[2]=ad(library_double(call,0xb29b0,sz,0.),half);wd(image+0x304b20,1);
    wq(image+0x304b28,recovered_target_angle_9f80(self,center,image,bridge));return;
cleanup:
    call(0x284f0,q(ctx+8),(uintptr_t)(image+0x2f6108),0,0,0,0);
}
__declspec(dllexport) void recovered_block_in_4ae50(uint8_t *event,uint8_t *image,dependency call){
    dependency previous=active;active=call;update(event,image,call);active=previous;
}
