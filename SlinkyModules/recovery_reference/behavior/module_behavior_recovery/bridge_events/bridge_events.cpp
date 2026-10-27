#include <stdint.h>
#include <string.h>
typedef uint64_t (*dependency)(uint32_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t u64(const void *p){return *(const volatile uint64_t *)p;}
static uint32_t u32(const void *p){return *(const volatile uint32_t *)p;}
static double d64(uint64_t b){double v;memcpy(&v,&b,8);return v;}
static float f32(uint32_t b){float v;memcpy(&v,&b,4);return v;}
static uint64_t db(double v){uint64_t b;memcpy(&b,&v,8);return b;}
static uint32_t fb(float v){uint32_t b;memcpy(&b,&v,4);return b;}
static double absolute(double v,uint8_t *image){return d64(db(v)&u64(image+0x150790));}
double *recovered_vector_adjust_95c0(double *,const double *,uint8_t *);

__declspec(dllexport) void recovered_bridge_disable(uint8_t *event,uint8_t *image,dependency call){
    if(u64(event+0x10)!=(uintptr_t)(image+0x2e9ac0) || event[0x18] || !(image[0x2f7dc8]&1)) return;
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    uint64_t settings=call(0x22cf0,u64(ctx),u64(ctx+0x18),0,0);
    uint64_t key=call(0x25030,u64(ctx),settings,0,0);
    uint32_t pressed=(uint32_t)call(0x25490,u64(ctx),key,0,0);
    call(0x25460,u64(ctx),key,pressed,0);
    image[0x2f7dc8]=0;
}

__declspec(dllexport) void recovered_bridge_action(uint8_t *event,uint8_t *image,dependency call){
    if(image[0x2f7dd1]==1)
        call(0x2af50,u64(event+8),(uintptr_t)(image+0x2e9ac0),u32(image+0x2e9d78)==2,0);
}

__declspec(dllexport) void recovered_bridge_input(uint8_t *event,uint8_t *image,dependency call){
    if(event[0x10] || u32(image+0x2f7dcc)==20) return;
    uint8_t *ctx=(uint8_t *)(uintptr_t)u64(event+8);
    if(image[0x2f7dd0]!=1) goto fallback;
    uint64_t hit=call(0x22e10,u64(ctx),u64(ctx+0x18),0,0);
    if(!hit) goto fallback;
    if((uint32_t)call(0x24b50,u64(ctx),hit,0,0)!=1) goto fallback;
    if((uint32_t)call(0x24b90,u64(ctx),hit,0,0)<2) goto fallback;
    if(!(uint8_t)call(0x23780,u64(ctx),u64(ctx+0x28),0,0)) goto fallback;
    uint64_t settings=call(0x22cf0,u64(ctx),u64(ctx+0x18),0,0);
    uint64_t forward=call(0x25120,u64(ctx),settings,0,0);
    uint64_t left=call(0x25170,u64(ctx),settings,0,0);
    uint64_t right=call(0x251c0,u64(ctx),settings,0,0);
    if(!(uint8_t)call(0x25430,u64(ctx),forward,0,0)) goto fallback;
    if((uint8_t)call(0x25430,u64(ctx),left,0,0)) goto fallback;
    if((uint8_t)call(0x25430,u64(ctx),right,0,0)) goto fallback;
    uint64_t packed=call(0x23170,u64(ctx),u64(ctx+0x28),0,0);
    double angle=d64(call(0xb2170,db((double)f32((uint32_t)packed)),u64(image+0x150760),0,0));
    float folded=f32(fb((float)angle)&u32(image+0x150770));
    if(f32(u32(image+0x150780))>folded || folded>f32(u32(image+0x150784))) goto fallback;
    double self[3],point[3],block[3];
    call(0x23030,(uintptr_t)self,u64(ctx),u64(ctx+0x28),0);
    if((uint8_t)call(0x23020,u64(ctx),0,0,0)){
        double copy[3],adjusted[3];memcpy(copy,self,24);
        recovered_vector_adjust_95c0(adjusted,copy,image);memcpy(self,adjusted,24);
    }
    uint64_t object=call(0x24bf0,u64(ctx),hit,0,0);
    call(0x25540,(uintptr_t)point,u64(ctx),object,0);
    if(absolute(point[0]-self[0],image)>d64(u64(image+0x1507a0))) goto fallback;
    double dy=point[1]-self[1];
    if(d64(u64(image+0x1507a8))>dy || dy>0.) goto fallback;
    if(absolute(point[2]-self[2],image)>d64(u64(image+0x1507a0))) goto fallback;
    call(0x24d80,(uintptr_t)block,u64(ctx),hit,0);
    double unit=d64(u64(image+0x1507a0));
    uint8_t inside_z=block[2]<self[2] && self[2]<block[2]+unit;
    double end_x=block[0]+unit;
    double rx=absolute(d64(call(0xb2170,db(point[0]),db(unit),0,0)),image);
    double rz=d64(call(0xb2170,db(point[2]),db(unit),0,0));
    double margin=d64(u64(image+0x1507b8));
    if(block[0]<self[0] && self[0]<end_x && inside_z) margin=d64(u64(image+0x1507b0));
    double upper=unit-margin;
    if(!(upper<rx) && !(rx<margin)) goto cancel;
    rz=absolute(rz,image);
    if(!(upper<rz) && !(rz<margin)) goto cancel;
fallback:
    {
        uint64_t object=call(0x28a50,u64(ctx),u64(ctx+0x28),0,0);
        if((uint8_t)call(0x28b00,u64(ctx),object,0,0)) *(volatile uint32_t *)(image+0x2f7dcc)=20;
    }
    return;
cancel:
    event[0x11]=1;
}
