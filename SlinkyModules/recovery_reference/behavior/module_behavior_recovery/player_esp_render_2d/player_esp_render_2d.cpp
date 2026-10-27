#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static uint32_t fb(float v){return d(&v);}
static uint64_t method(uint8_t *image,uint32_t slot){return q((void *)(uintptr_t)q(image+slot));}
static float add(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float sub(float a,float b){return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float recovered_scalar_lerp_a2b0(float,float,float);
double *recovered_vector_lerp_9460(double *,const double *,const double *,double);
double *recovered_vector_subtract_93d0(double *,const double *,const double *);
void *recovered_geometry_add_9400(double *,const double *,const double *);
uint32_t recovered_screen_project_295c0(uint8_t *,const double *,float *,uint8_t *);
uint64_t recovered_render_29460(uint8_t *,endpoint);
uint64_t recovered_render_294a0(uint8_t *,endpoint);
uint64_t recovered_render_294d0(uint8_t *,endpoint);
uint64_t recovered_render_295a0(uint8_t *,endpoint);
uint64_t recovered_player_esp_health_2fa30(uint8_t *,float,float,float,uint8_t *,endpoint);

__declspec(dllexport) void recovered_player_esp_2eea0(uint8_t *event,uint8_t *image,endpoint call){
    if(!q(image+0x2f7e10)||d(image+0x2ea110)!=0)return;
    call(method(image,0x13e458),0xbe2,0,0,0);call(method(image,0x150cb0),d(image+0x2ea0c0),0,0,0);
    if(!q(image+0x2f7e10))return;
    float partial=f(event+0x40);double fraction=(double)partial,first_corner[3];
    memcpy(first_corner,image+0x150aa0,16);first_corner[2]=-.4;
    uint64_t index=0;
    do{
        uint8_t *row=image+0x2f7e20+80*index;
        double previous[3],current[3],position[3],camera[3],relative[3],point[3];float screen[2];
        memcpy(previous,row,24);memcpy(current,row+0x18,24);recovered_vector_lerp_9460(position,previous,current,fraction);
        memcpy(camera,event+8,24);recovered_vector_subtract_93d0(relative,position,camera);
        recovered_geometry_add_9400(point,relative,first_corner);
        if(!recovered_screen_project_295c0(event+8,point,screen,image))goto next;
        float minx=screen[0],maxx=screen[0],miny=screen[1],maxy=screen[1];
        for(unsigned offset=24;offset!=192;offset+=24){
            double corner[3];memcpy(corner,image+0x150aa0+offset,24);recovered_geometry_add_9400(point,relative,corner);
            if(!recovered_screen_project_295c0(event+8,point,screen,image))goto next;
            if(minx>screen[0])minx=screen[0];else if(screen[0]>maxx)maxx=screen[0];
            if(miny>screen[1])miny=screen[1];else if(screen[1]>maxy)maxy=screen[1];
        }
        float width=f(event+0x28),height=f(event+0x2c);
        if((0>minx||0>miny||minx>width||miny>height)&&(0>maxx||maxx>width||0>maxy||maxy>height))goto next;
        int32_t hurt=(int32_t)d(row+0x40);float red=f(row+0x30),green=f(row+0x34),blue=f(row+0x38);
        if(hurt>0&&image[0x2ea158]){
            __m128 elapsed=_mm_sub_ss(_mm_cvtsi32_ss(_mm_setzero_ps(),hurt),_mm_set_ss(partial));
            float t=_mm_cvtss_f32(_mm_mul_ss(_mm_min_ss(_mm_set_ss(f(image+0x150a08)),elapsed),_mm_set_ss(f(image+0x150a0c))));
            red=recovered_scalar_lerp_a2b0(red,f(image+0x150a10),t);green=recovered_scalar_lerp_a2b0(green,0,t);blue=recovered_scalar_lerp_a2b0(blue,0,t);
        }
        if(image[0x2ea138]||row[0x4c]==1){
            recovered_render_29460(image,call);call(method(image,0x150cc0),0,0,0,0);
            call(method(image,0x150cd8),fb(minx),fb(miny),0,0);
            call(method(image,0x150cd0),fb(sub(maxx,minx)),fb(sub(maxy,miny)),d(image+0x150a10),0);
            if(image[0x2ea178]==1){call(method(image,0x13e448),fb(red),fb(green),fb(blue),d(image+0x150a14));recovered_render_294a0(image,call);}
            call(method(image,0x150ca0),fb(red),fb(green),fb(blue),0);recovered_render_294d0(image,call);call(method(image,0x150cb8),0,0,0,0);recovered_render_295a0(image,call);
        }
        if(image[0x2ea198]==1){
            float x=add(add(sub(minx,f(image+0x2ea0c0)),f(image+0x150a18)),f(image+0x150a1c));
            recovered_player_esp_health_2fa30(row,x,miny,maxy,image,call);
        }
next: ++index;
    }while(index<q(image+0x2f7e10));
}
