#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <emmintrin.h>
typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
typedef uint64_t (*short_endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static double g(const void *p){double v;memcpy(&v,p,8);return v;}
static void wq(void *p,uint64_t v){memcpy(p,&v,8);}
static void wd(void *p,uint32_t v){memcpy(p,&v,4);}
static void wf(void *p,float v){memcpy(p,&v,4);}
static float narrow(double v){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(v)));}
static float af(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float mf(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float df(float a,float b){return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float minf(float a,float b){return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static __declspec(thread) endpoint current_endpoint;
static uint64_t short_call(uint64_t r,uint64_t a,uint64_t b,uint64_t c,uint64_t d){return current_endpoint(r,a,b,c,d,0,0,0);}
void recovered_trajectory_launch_45f40(uint8_t *,double *,uint64_t,float,double *,double *,uint8_t *,short_endpoint);
double *recovered_vector_scale_9430(double *,const double *,double);
double *recovered_vector_subtract_93d0(double *,const double *,const double *);
void *recovered_geometry_add_9400(double *,const double *,const double *);
void *recovered_geometry_pair_96b0(void *,const void *,const void *);
uint8_t recovered_geometry_intersects_97d0(const double *,const double *);
double *recovered_vector_reciprocal_9650(double *,const double *,const uint8_t *);
uint32_t recovered_box_ray_98e0(const double *,const double *,const double *,const uint8_t *);

__declspec(dllexport) double *recovered_box_sorted_96e0(double *out,const double *a,const double *b){
    __m128d az=_mm_load_sd(a+2),bz=_mm_load_sd(b+2),mask=_mm_cmpunord_sd(az,az);
    __m128d lo=_mm_or_pd(_mm_and_pd(mask,bz),_mm_andnot_pd(mask,_mm_min_sd(bz,az)));
    __m128d hi=_mm_or_pd(_mm_and_pd(mask,bz),_mm_andnot_pd(mask,_mm_max_sd(bz,az)));
    _mm_store_sd(out+2,lo);
    __m128d av=_mm_loadu_pd(a),bv=_mm_loadu_pd(b);mask=_mm_cmpunord_pd(av,av);
    lo=_mm_or_pd(_mm_and_pd(mask,bv),_mm_andnot_pd(mask,_mm_min_pd(bv,av)));
    __m128d high=_mm_or_pd(_mm_and_pd(mask,bv),_mm_andnot_pd(mask,_mm_max_pd(bv,av)));
    _mm_storeu_pd(out,lo);_mm_storeu_pd(out+3,high);_mm_store_sd(out+5,hi);return out;
}
__declspec(dllexport) double *recovered_box_expand_9770(double *out,double *box,double margin){
    __m128d amount=_mm_set1_pd(margin);_mm_storeu_pd(box,_mm_sub_pd(_mm_loadu_pd(box),amount));
    _mm_store_sd(box+2,_mm_sub_sd(_mm_load_sd(box+2),amount));
    _mm_storeu_pd(box+3,_mm_add_pd(_mm_loadu_pd(box+3),amount));
    _mm_store_sd(box+5,_mm_add_sd(amount,_mm_load_sd(box+5)));
    _mm_storeu_pd(out+4,_mm_loadu_pd(box+4));_mm_storeu_pd(out+2,_mm_loadu_pd(box+2));_mm_storeu_pd(out,_mm_loadu_pd(box));return out;
}
__declspec(dllexport) uint8_t *recovered_vector_index_ddc0(uint8_t *data,uint32_t stride,const void *state,uint32_t index){(void)state;return data+(uint32_t)(stride*index);}
__declspec(dllexport) uint64_t recovered_vector_append_ddd0(uint8_t *pointer,uint32_t stride,uint8_t *state,const void *value,endpoint call){
    uint32_t capacity=d(state),count=d(state+4);uint64_t data=q(pointer);
    if(count>=capacity){
        uint32_t next=capacity?capacity+capacity:8;wd(state,next);
        data=call(0x13cf90,data,(uint32_t)(next*stride),0,0,0,0,0);
        if(!data){call(0x13d040,0,0,0,0,0,0,0);abort();}
        wq(pointer,data);count=d(state+4);
    }
    wd(state+4,count+1);return call(0xabbf0,data+(uint32_t)(count*stride),(uintptr_t)value,stride,0,0,0,0);
}
static float charge(uint32_t ticks,uint8_t *image){
    float t=df(_mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),(int32_t)ticks)),f(image+0x154e08));
    return df(af(mf(t,t),af(t,t)),f(image+0x154e0c));
}
static float speed(float strength,uint8_t *image){double v=(double)minf(f(image+0x154e18),strength)*g(image+0x154e20);return narrow(v+v);}
static void update(uint8_t *event,uint8_t *image,endpoint call){
    uint8_t *ctx=(void *)(uintptr_t)q(event+8);
    if(ctx[0x40]!=1 || (uint8_t)call(0x29f80,0,0,0,0,0,0,0))goto inactive;
    uint64_t settings=call(0x22cf0,q(ctx),q(ctx+0x18),0,0,0,0,0);
    if((uint32_t)call(0x25310,q(ctx),settings,0,0,0,0,0))goto inactive;
    uint64_t item=call(0x28a50,q(ctx),q(ctx+0x28),0,0,0,0,0);if(!item)goto inactive;
    uint32_t id=(uint32_t)call(0x25c50,q(ctx),item,0,0,0,0,0);uint8_t block_flag=0,entity_flag=1;
    if(id==368){if(image[0x2f40d0]!=1)goto inactive;block_flag=1;entity_flag=0;}
    else if(id==332 || id==344){if(image[0x2f40f0]!=1)goto inactive;}
    else if(id!=261)goto inactive;
    if(id!=261){wf(image+0x30498c,1.5f);wf(image+0x304990,1.5f);wd(image+0x304988,0x3cf5c28f);}
    else{
        if(image[0x2f4090]!=1)goto inactive;wd(image+0x304988,0x3d4ccccd);
        if((uint8_t)call(0x23f90,q(ctx),q(ctx+0x28),0,0,0,0,0)){
            uint32_t ticks=(uint32_t)call(0x23fc0,q(ctx),q(ctx+0x28),0,0,0,0,0);float now=charge(72000u-ticks,image);
            double threshold=g(image+0x154e10);if(threshold>(double)now){wf(image+0x304990,0);goto inactive;}
            float current=speed(now,image);wf(image+0x304990,current);if(current==0)goto inactive;
            float before=charge(71999u-ticks,image);wf(image+0x30498c,threshold>(double)before?0.f:speed(before,image));
        }else{if(image[0x2f40b0]!=1)goto inactive;wf(image+0x30498c,3.f);wf(image+0x304990,3.f);}
    }
    uint64_t angle=call(0x23170,q(ctx),q(ctx+0x28),0,0,0,0,0);double input[3],position[3],velocity[3];
    call(0x23030,(uintptr_t)input,q(ctx),q(ctx+0x28),0,0,0,0);recovered_trajectory_launch_45f40(ctx,input,angle,0.f,position,velocity,image,short_call);
    wd(image+0x304484,0);wd(image+0x304494,0);
    uint64_t list=call(0x24620,q(ctx),q(ctx+0x20),0,0,0,0,0);
    double horizontal=g(image+0x154e28),low[3]={position[0],-100.,position[2]},high[3]={velocity[0]*horizontal+position[0],position[1]+g(image+0x154e30),horizontal*velocity[2]+position[2]},broad[6];
    recovered_box_sorted_96e0(broad,low,high);
    if((int32_t)call(0x24e50,q(ctx),list,0,0,0,0,0)>0){
        double margin=g(image+0x154e38);uint32_t index=0;
        do{
            uint64_t entity=call(0x24e80,q(ctx),list,index,0,0,0,0),env=q((void *)(uintptr_t)(q(ctx)+8));
            uint64_t equal=q((void *)(uintptr_t)(q((void *)(uintptr_t)env)+0xc0));
            if((uint8_t)call(equal,env,entity,q(ctx+0x28),0,0,0,0))goto next;
            if(!(uint8_t)call(0x23900,q(ctx),entity,0,0,0,0,0))goto next;
            uint64_t box_object=call(0x23670,q(ctx),entity,0,0,0,0,0);double box[6],expanded[6];
            call(0x25640,(uintptr_t)box,q(ctx),box_object,0,0,0,0);recovered_box_expand_9770(expanded,box,margin);
            if(recovered_geometry_intersects_97d0(expanded,broad)){
                recovered_vector_append_ddd0(image+0x304478,8,image+0x304480,&entity,call);
                recovered_vector_append_ddd0(image+0x304488,48,image+0x304490,expanded,call);
            }
next:       ++index;
        }while((int32_t)index<(int32_t)call(0x24e50,q(ctx),list,0,0,0,0,0));
    }
    double drag=g(image+0x154e48),block_size=g(image+0x154e40);
    for(uint32_t step=0;step!=100;++step){
        double old[3],v[3],temporary[3],inverse[3];memcpy(old,position,24);memcpy(v,velocity,24);recovered_geometry_add_9400(position,old,v);
        memcpy(temporary,old,24);uint64_t from=call(0x254f0,q(ctx),(uintptr_t)temporary,0,0,0,0,0);
        memcpy(temporary,position,24);uint64_t to=call(0x254f0,q(ctx),(uintptr_t)temporary,0,0,0,0,0);
        uint64_t hit=call(0x24860,q(ctx),q(ctx+0x20),from,to,0,1,0);
        if(hit){
            wd(image+0x304498,step+1);image[0x304950]=1;image[0x30449c]=block_flag;
            uint64_t point=call(0x24bf0,q(ctx),hit,0,0,0,0,0);call(0x25540,(uintptr_t)position,q(ctx),point,0,0,0,0);
            recovered_vector_subtract_93d0(velocity,position,old);
            double corner[3],size[3]={block_size,block_size,block_size},end[3],box[6];call(0x24c10,(uintptr_t)corner,q(ctx),hit,0,0,0,0);
            recovered_geometry_add_9400(end,corner,size);recovered_geometry_pair_96b0(box,corner,end);memcpy(image+0x304958,box,48);memset(image+0x304460,0,24);
        }
        memcpy(v,velocity,24);recovered_vector_reciprocal_9650(inverse,v,image);
        for(uint64_t index=0;index<d(image+0x304494);++index){
            double box[6];memcpy(box,recovered_vector_index_ddc0((void *)(uintptr_t)q(image+0x304488),48,image+0x304490,(uint32_t)index),48);
            if((uint8_t)recovered_box_ray_98e0(box,old,inverse,image)){
                wd(image+0x304498,step+1);image[0x304950]=1;image[0x30449c]=entity_flag;memcpy(image+0x304958,box,48);
                uint64_t entity=q(recovered_vector_index_ddc0((void *)(uintptr_t)q(image+0x304478),8,image+0x304480,(uint32_t)index));
                double current[3],previous[3],movement[3];call(0x23030,(uintptr_t)current,q(ctx),entity,0,0,0,0);call(0x230d0,(uintptr_t)previous,q(ctx),entity,0,0,0,0);
                recovered_vector_subtract_93d0(movement,current,previous);memcpy(image+0x304460,movement,24);return;
            }
        }
        if(hit)return;
        memcpy(v,velocity,24);recovered_vector_scale_9430(velocity,v,drag);velocity[1]-=(double)f(image+0x304988);
    }
    wd(image+0x304498,100);image[0x304950]=0;image[0x30449c]=0;return;
inactive:wd(image+0x304498,0);
}
__declspec(dllexport) void recovered_trajectories_45370(uint8_t *event,uint8_t *image,endpoint call){endpoint saved=current_endpoint;current_endpoint=call;update(event,image,call);current_endpoint=saved;}
__declspec(dllexport) void trajectory_sorted_adapter(uint8_t *event,uint8_t *image,endpoint call){(void)image;(void)call;recovered_box_sorted_96e0((void *)(uintptr_t)q(event),(void *)(uintptr_t)q(event+8),(void *)(uintptr_t)q(event+16));}
__declspec(dllexport) void trajectory_expand_adapter(uint8_t *event,uint8_t *image,endpoint call){(void)image;(void)call;recovered_box_expand_9770((void *)(uintptr_t)q(event),(void *)(uintptr_t)q(event+8),g(event+16));}
