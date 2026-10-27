#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
typedef uint64_t (*endpoint4)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static __declspec(thread) endpoint active;
static uint64_t bridge(uint64_t r,uint64_t a,uint64_t b,uint64_t c,uint64_t d){return active(r,a,b,c,d,0,0,0,0);}
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static uint16_t h(const void *p){uint16_t v;memcpy(&v,p,2);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static void wq(void *p,uint64_t v){memcpy(p,&v,8);}
static void wd(void *p,uint32_t v){memcpy(p,&v,4);}
static void wh(void *p,uint16_t v){memcpy(p,&v,2);}
static void wf(void *p,float v){memcpy(p,&v,4);}
static float ff(uint64_t v){uint32_t b=(uint32_t)v;return f(&b);}
static double gf(uint64_t v){double a;memcpy(&a,&v,8);return a;}
static uint64_t gb(double v){return q(&v);}
static float narrow(double v){return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(v)));}
static float mf(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static uint64_t method(uint64_t env,uint32_t slot){return q((void *)(uintptr_t)(q((void *)(uintptr_t)env)+slot));}
static uint64_t env_of(uint8_t *ctx){return q((void *)(uintptr_t)(q(ctx)+8));}
static uint64_t c3(endpoint call,uint64_t r,uint64_t a,uint64_t b,uint64_t c){return call(r,a,b,c,0,0,0,0,0);}
void recovered_name_tags_release_3d800(uint8_t *,uint8_t *,endpoint);
void recovered_text_initialize_dc20(uint8_t *,uint8_t *,uint64_t);
uint8_t recovered_text_append_dc40(uint8_t *,const char *,endpoint4);
uint8_t recovered_text_format_dca0(uint8_t *,const char *,const uint64_t *,endpoint4);
uint8_t recovered_text_byte_dd10(uint8_t *,uint8_t);
uint8_t recovered_text_finish_dd40(uint8_t *);
double recovered_vector_distance_squared(const double *,const double *);
double recovered_vector_distance_94f0(const double *,const double *);
double *recovered_vector_adjust_95c0(double *,const double *,uint8_t *);
float recovered_float_clamp_a1f0(float,float,float);
__declspec(dllexport) int32_t recovered_name_tags_compare_3da40(const uint8_t *a,const uint8_t *b){return _mm_cvttss_si32(_mm_sub_ss(_mm_load_ss((const float *)(b+0x48)),_mm_load_ss((const float *)(a+0x48))));}
__declspec(dllexport) int32_t recovered_enchant_compare_3da60(const uint8_t *a,const uint8_t *b,uint8_t *image){uint32_t v=d(image+0x153ac0+4*(int64_t)(int16_t)h(a))-d(image+0x153ac0+4*(int64_t)(int16_t)h(b));int32_t result;memcpy(&result,&v,4);return result;}
static void update(uint8_t *event,uint8_t *image,endpoint call){
    uint8_t *ctx=(void *)(uintptr_t)q(event+8);
    recovered_name_tags_release_3d800((void *)(uintptr_t)q(ctx),image,call);
    if(!q(ctx+0x20))return;
    if(!q(image+0x3007a0)){
        uint64_t game=q(ctx),env=q((void *)(uintptr_t)(game+8)),renderer;
        if(d((void *)(uintptr_t)q((void *)(uintptr_t)game))){renderer=c3(call,0x22db0,game,q(ctx+0x18),0);}
        else{renderer=c3(call,0x27b20,game,0,0);if(!renderer)goto renderer_done;}
        wq(image+0x3007a0,c3(call,method(env,0xa8),env,renderer,0));
    }
renderer_done:;
    double self[3],self_previous[3];
    c3(call,0x23030,(uintptr_t)self,q(ctx),q(ctx+0x28));c3(call,0x230d0,(uintptr_t)self_previous,q(ctx),q(ctx+0x28));
    uint64_t list=c3(call,0x24600,q(ctx),q(ctx+0x20),0),saved_env=env_of(ctx);
    uint64_t font=c3(call,0x22d40,q(ctx),q(ctx+0x18),0);font=c3(call,0x272a0,q(ctx),font,0);if(!font)return;
    uint64_t id_key=c3(call,method(saved_env,0x538),saved_env,(uintptr_t)(image+0x1537bb),0),level_key=c3(call,method(saved_env,0x538),saved_env,(uintptr_t)(image+0x1537be),0);if(!id_key||!level_key)return;
    int32_t length=(int32_t)c3(call,0x24e50,q(ctx),list,0);if(length<=0)goto sorted;
    float max_health=f(image+0x15371c),max_absorb=f(image+0x153720),health_yellow=f(image+0x153724),health_red=f(image+0x153728),health_scale=f(image+0x15372c),distance_red=f(image+0x153734);
    for(uint32_t index=0;;++index){
        uint64_t entity=c3(call,0x24e80,q(ctx),list,index),env=env_of(ctx);
        uint8_t is_self=(uint8_t)c3(call,method(env,0xc0),env,entity,q(ctx+0x28));
        if(is_self){if(image[0x2f0608]!=1)goto next;uint64_t settings=c3(call,0x22cf0,q(ctx),q(ctx+0x18),0);if(!(uint32_t)c3(call,0x25310,q(ctx),settings,0))goto next;}
        uint32_t flags=(uint32_t)c3(call,0x2acb0,q(ctx),entity,0);if(flags&2)goto next;
        if((uint8_t)c3(call,0x237b0,q(ctx),entity,0))goto next;
        double position[3],previous[3],copy_a[3],copy_b[3];c3(call,0x23030,(uintptr_t)position,q(ctx),entity);
        memcpy(copy_a,position,24);memcpy(copy_b,self,24);double distance=recovered_vector_distance_squared(copy_a,copy_b);float range=f(image+0x2f05e8);if(distance>(double)mf(range,range))goto next;
        env=env_of(ctx);uint64_t name;
        if(image[0x2f0628]==1){name=c3(call,0x23800,q(ctx),entity,0);name=c3(call,0x26090,q(ctx),name,0);if(!image[0x2f0648]&&!image[0x2f0668])goto label_ready;}
        else name=c3(call,0x23830,q(ctx),entity,0);
        {
            int32_t raw_length=(int32_t)c3(call,method(env,0x540),env,name,0),limit=raw_length<64?raw_length:64;
            uint8_t *chars=(void *)(uintptr_t)c3(call,method(env,0x548),env,name,0);uint8_t builder[24];recovered_text_initialize_dc20(builder,image+0x3007b0,128);
            if(image[0x2f0648]==1){
                float health=recovered_float_clamp_a1f0(0,max_health,ff(c3(call,0x23a40,q(ctx),entity,0))),absorb=recovered_float_clamp_a1f0(0,max_absorb,ff(c3(call,0x23fe0,q(ctx),entity,0)));
                uint32_t color=health_yellow>health?'e':'a';if(health_red>health)color='c';uint32_t precision=d(image+0x2f06b0)==1;
                if(precision){health=mf(health,health_scale);absorb=mf(absorb,health_scale);}
                uint64_t args[3]={color,precision,gb((double)health)};
                if(!recovered_text_format_dca0(builder,(char *)(image+0x1537e7),args,bridge))goto label_ready;
                if(absorb>0){uint64_t more[2]={precision,gb((double)absorb)};if(!recovered_text_format_dca0(builder,(char *)(image+0x1537f0),more,bridge))goto label_ready;}
                if(!recovered_text_append_dc40(builder,(char *)(image+0x1537f9),bridge))goto label_ready;
            }
            if(image[0x2f0628]==1){if(!recovered_text_append_dc40(builder,(char *)chars,bridge))goto label_ready;}
            else{
                if(!recovered_text_append_dc40(builder,(char *)(image+0x153801),bridge))goto label_ready;
                if(!recovered_text_byte_dd10(builder,(flags&5)?'a':'c'))goto label_ready;
                if(raw_length>0)for(int32_t i=0;i<limit;++i){if(chars[i]==0xc2){i+=2;continue;}if(!recovered_text_byte_dd10(builder,chars[i]))goto label_ready;}
            }
            if(image[0x2f0668]==1){uint64_t current_env=env_of(ctx);if(!(uint8_t)c3(call,method(current_env,0xc0),current_env,q(ctx+0x28),entity)){
                double root=distance>=0?_mm_cvtsd_f64(_mm_sqrt_sd(_mm_setzero_pd(),_mm_set_sd(distance))):gf(c3(call,0xaf2f0,gb(distance),0,0));float short_distance=narrow(root);
                uint32_t color=f(image+0x153730)>short_distance?'e':'a';if(distance_red>short_distance)color='c';uint64_t args[2]={color,gb(root)};
                if(!recovered_text_format_dca0(builder,(char *)(image+0x153804),args,bridge))goto label_ready;
            }}
            c3(call,method(env,0x550),env,name,(uintptr_t)chars);
            if(recovered_text_finish_dd40(builder))name=c3(call,method(env,0x538),env,(uintptr_t)(image+0x3007b0),0);
        }
label_ready:
        if(!name)goto sorted;uint64_t label=c3(call,method(env,0xa8),env,name,0);if(!label)goto sorted;
        uint64_t global_entity=c3(call,method(saved_env,0xa8),saved_env,entity,0);if(!global_entity){c3(call,method(saved_env,0xb0),saved_env,label,0);goto sorted;}
        c3(call,0x230d0,(uintptr_t)previous,q(ctx),entity);uint8_t version=(uint8_t)c3(call,0x23020,q(ctx),0,0);
        if(is_self&&version){memcpy(copy_a,position,24);recovered_vector_adjust_95c0(copy_b,copy_a,image);memcpy(position,copy_b,24);memcpy(copy_a,previous,24);recovered_vector_adjust_95c0(copy_b,copy_a,image);memcpy(previous,copy_b,24);}
        uint64_t count=q(image+0x2fc910);wq(image+0x2fc910,count+1);uint8_t *row=image+0x2fc920+160*count;
        memcpy(row+0x28,position+2,8);memcpy(row+0x18,position,16);memcpy(row+0x10,previous+2,8);memcpy(row,previous,16);wq(row+0x30,global_entity);
        float dist=narrow(distance);dist=dist>=0?_mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(dist))):ff(c3(call,0xaf4a0,d(&dist),0,0));wf(row+0x48,dist);
        memcpy(copy_a,self_previous,24);memcpy(copy_b,row,24);wf(row+0x44,narrow(recovered_vector_distance_94f0(copy_a,copy_b)));wq(row+0x38,label);
        wd(row+0x40,(uint32_t)c3(call,0x27560,q(ctx),font,label));wd(row+0x4c,0);
        for(uint32_t slot=0;slot<5;++slot){uint8_t present=c3(call,0x24050,q(ctx),entity,slot)!=0;if(present)wd(row+0x4c,d(row+0x4c)+1);row[0x50+16*slot]=present;}
        if(image[0x2f05b0]==1){
            uint64_t enchant_env=env_of(ctx);
            for(uint32_t slot=0;slot<5;++slot){
                uint8_t *equipment=row+0x50+16*slot;wq(equipment+8,0);wd(equipment+4,0);
                uint64_t item=c3(call,0x24050,q(ctx),entity,slot);if(!item)continue;uint64_t tags=c3(call,0x25de0,q(ctx),item,0);if(!tags)continue;
                int32_t raw_count=(int32_t)c3(call,0x27f10,q(ctx),tags,0),limit=raw_count<25?raw_count:25;
                for(int32_t i=0;i<limit;++i){uint64_t tag=c3(call,0x27f40,q(ctx),tags,(uint32_t)i);uint16_t id=(uint16_t)c3(call,0x27f70,q(ctx),tag,id_key);if(id>62 || ((UINT64_C(0x1ff0fff0ffc0fe00)>>id)&1))continue;
                    int16_t level=(int16_t)c3(call,0x27f70,q(ctx),tag,level_key);if(level<=0)level=0;if(level>=99)level=99;wh(image+0x300830+4*i,id);wh(image+0x300832+4*i,(uint16_t)level);
                }
                call(0x13d0f0,(uintptr_t)(image+0x300830),(uint64_t)(int64_t)limit,4,UINT64_C(0x18003da60),0,0,0,0);
                int32_t shown=raw_count<4?raw_count:4;uint64_t array=c3(call,0x13cf60,(uint64_t)(int64_t)shown,8,0);wq(equipment+8,array);if(!array)goto record_done;
                for(int32_t i=0;i<shown;++i){uint16_t id=h(image+0x300830+4*i);uint64_t abbr=id<=62?q(image+0x153870+8*id):0;if(abbr)abbr=(uintptr_t)image+(abbr-UINT64_C(0x180000000));
                    call(0xab710,(uintptr_t)(image+0x300894),6,(uintptr_t)(image+0x153864),abbr,(uint32_t)(int32_t)(int16_t)h(image+0x300832+4*i),0,0,0);
                    uint64_t text=c3(call,method(enchant_env,0x538),enchant_env,(uintptr_t)(image+0x300894),0);if(!text)goto record_done;
                    text=c3(call,method(enchant_env,0xa8),enchant_env,text,0);if(!text)goto record_done;wq((void *)(uintptr_t)(q(equipment+8)+8*i),text);wd(equipment+4,d(equipment+4)+1);
                }
            }
        }
record_done:
        if(q(image+0x2fc910)==100)break;
next:
        length=(int32_t)c3(call,0x24e50,q(ctx),list,0);if((int32_t)(index+1)>=length)break;
    }
sorted:
    call(0x13d0f0,(uintptr_t)(image+0x2fc920),q(image+0x2fc910),160,UINT64_C(0x18003da40),0,0,0,0);
}
__declspec(dllexport) void recovered_name_tags_update_3ca20(uint8_t *event,uint8_t *image,endpoint call){endpoint previous=active;active=call;update(event,image,call);active=previous;}
