#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
typedef uint64_t (*endpoint)(uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t,uint64_t);
static uint64_t q(const void *p){uint64_t v;memcpy(&v,p,8);return v;}
static uint32_t d(const void *p){uint32_t v;memcpy(&v,p,4);return v;}
static float f(const void *p){float v;memcpy(&v,p,4);return v;}
static double g(const void *p){double v;memcpy(&v,p,8);return v;}
static uint32_t bits(float v){uint32_t b;memcpy(&b,&v,4);return b;}
static float af(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float sf(float a,float b){return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b)));}
static float mf(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
uint32_t *recovered_color_74130(uint32_t *,uint32_t,uint32_t,uint32_t);
__declspec(dllexport) float *recovered_rect_a070(float *out,float x,float y,float width,float height){out[0]=x;out[1]=y;out[2]=width;out[3]=height;return out;}
__declspec(dllexport) float recovered_smooth_a280(float value,uint8_t *image){float square=mf(value,value);return mf(sf(f(image+0x13e8d4),af(value,value)),square);}
__declspec(dllexport) void *recovered_theme_324b0(void *out,uint8_t *image){memcpy((uint8_t *)out+8,image+0x2eb730,4);memcpy(out,image+0x2eb728,8);return out;}
__declspec(dllexport) float *recovered_color_74150(float *out,float red,float green,float blue,float alpha){out[0]=red;out[1]=green;out[2]=blue;out[3]=alpha;return out;}
__declspec(dllexport) float *recovered_color_741b0(float *out,float *source,float alpha){source[3]=alpha;__m128 v=_mm_loadu_ps(source);_mm_storeu_ps(out,v);return out;}
__declspec(dllexport) void recovered_notifications_354b0(uint8_t *event,uint8_t *image,endpoint call){
    if(!q(image+0x2fbfd8))return;
    if(image[0x2ed628]==1 && !*(uint8_t *)(uintptr_t)(q(image+0x13e498)+0x14))return;
    uint8_t *draw=(void *)(uintptr_t)q(event+0x10);uint64_t saved_canvas=q(draw);
    call(0x79610,saved_canvas,d(image+0x151e60),0,0,0,0);
    if(q(image+0x2fbfd8)){
        float y=f(image+0x151e64),initial_x=y,one=f(image+0x151e70),white=f(image+0x151e8c),dark=f(image+0x151ea4),padding=f(image+0x151eac),shrink=f(image+0x151eb0);
        double duration=g(image+0x151e68);
        for(uint64_t i=0;;++i){
            uint8_t *row=image+0x2fbfe0+112*((q(image+0x2fc440)+i)%10);
            double age=(double)f(row+0x6c);float amount=one;
            if(duration>age)amount=recovered_smooth_a280((float)(age/duration),image);
            else if(age>g(image+0x151e78))amount=recovered_smooth_a280((float)((g(image+0x151e80)-age)/duration),image);
            amount=_mm_cvtss_f32(_mm_min_ss(_mm_set_ss(one),_mm_set_ss(amount)));
            call(0x74a60,saved_canvas,bits(amount),0,0,0,0);
            float x=af(mf(sf(one,amount),f(image+0x151e88)),initial_x);uint64_t canvas=q(draw);float color[4],main_rect[4],stripe[4],temporary[4],copy[4],text_rect[4];
            switch(d(row)){
                case 0:recovered_color_74150(color,f(image+0x151e94),f(image+0x151e98),f(image+0x151e9c),1.f);break;
                case 1:recovered_theme_324b0(main_rect,image);recovered_color_74130((uint32_t *)color,bits(main_rect[0]),bits(main_rect[1]),bits(main_rect[2]));break;
                case 2:recovered_color_74150(color,white,f(image+0x151e90),f(image+0x151e90),1.f);break;
                default:recovered_color_74150(color,white,white,white,1.f);break;
            }
            uint8_t *text=row+4;uint32_t width_bits=(uint32_t)call(0x7ae90,canvas,0,0,(uintptr_t)text,0,0);float width;memcpy(&width,&width_bits,4);
            recovered_rect_a070(main_rect,x,y,af(width,f(image+0x151ea0)),42.f);
            recovered_color_74150(temporary,dark,dark,dark,1.f);call(0x74ef0,canvas,(uintptr_t)temporary,0,0,0,0);
            memcpy(copy,main_rect,16);call(0x10a60,(uintptr_t)draw,(uintptr_t)copy,d(image+0x151ea8),0,0,0);
            recovered_rect_a070(stripe,af(main_rect[0],padding),af(main_rect[1],padding),f(image+0x151eb4),af(main_rect[3],shrink));
            memcpy(copy,color,16);recovered_color_741b0(temporary,copy,f(image+0x151eb8));call(0x74ef0,canvas,(uintptr_t)temporary,0,0,0,0);
            memcpy(copy,stripe,16);call(0x10a60,(uintptr_t)draw,(uintptr_t)copy,d(image+0x151ebc),0,0,0);
            memcpy(copy,color,16);call(0x74ef0,canvas,(uintptr_t)copy,0,0,0,0);
            memcpy(copy,stripe,16);call(0x10cb0,(uintptr_t)draw,(uintptr_t)copy,1,0,(uintptr_t)(image+0x151f88),0);
            recovered_rect_a070(text_rect,af(af(stripe[0],stripe[2]),padding),main_rect[1],af(sf(main_rect[2],stripe[2]),shrink),main_rect[3]);
            recovered_color_74150(temporary,white,white,white,1.f);call(0x74ef0,canvas,(uintptr_t)temporary,0,0,0,0);
            memcpy(copy,text_rect,16);call(0x10cb0,(uintptr_t)draw,(uintptr_t)copy,0,0,(uintptr_t)text,0);
            y=af(y,mf(amount,f(image+0x151ec0)));if(i+1>=q(image+0x2fbfd8))break;
        }
    }
    call(0x74a60,saved_canvas,d(image+0x151e70),0,0,0,0);
}
