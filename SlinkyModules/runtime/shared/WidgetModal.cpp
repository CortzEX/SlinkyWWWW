#include "WidgetModal.hpp"
#include "WidgetState.hpp"
#include <bit>
#include <cstring>
#include <initializer_list>
#include <emmintrin.h>
#include <intrin.h>
namespace {
using W=std::uint64_t;
template<class T>T get(const void *p){T v;std::memcpy(&v,p,sizeof v);return v;}
template<class T>void put(void *p,T v){std::memcpy(p,&v,sizeof v);_ReadWriteBarrier();}
W address(const void *p){return std::uintptr_t(p);}
__m128 load(const std::uint8_t *image,std::size_t rva){return _mm_set_ss(get<float>(image+rva));}
__m128 select(__m128 mask,__m128 first,__m128 second){return _mm_or_ps(_mm_and_ps(mask,first),_mm_andnot_ps(mask,second));}
void zero(std::uint8_t *state,std::size_t offset){_mm_storeu_ps(reinterpret_cast<float *>(state+offset),_mm_setzero_ps());_ReadWriteBarrier();}
}
// Captured16600 retains the SSE NaN selectors and operation order of its RGB
// to HSL conversion. The clock and modal completion are caller-owned frames.
std::uint32_t recovered_color_modal_16600(std::uint8_t *state,W title,W user,const std::uint8_t *rgb,W completion,const std::uint8_t *image,RecoveredFrameInvoker call){
    call(0x169c0,address(state),1);const auto now=call(0x4c270);
    const auto blueBits=get<std::uint32_t>(rgb+8);const auto firstPair=get<W>(rgb);
    const auto red=_mm_set_ss(get<float>(rgb)),green=_mm_set_ss(get<float>(rgb+4)),blue=_mm_set_ss(get<float>(rgb+8));
    const auto maxGb=select(_mm_cmpunord_ss(green,green),blue,_mm_max_ss(blue,green));
    const auto maximum=select(_mm_cmpunord_ss(red,red),maxGb,_mm_max_ss(maxGb,red));
    auto minimum=blue;
    if(!(_mm_movemask_ps(_mm_cmpunord_ss(green,green))&1))minimum=_mm_min_ss(minimum,green);
    if(!(_mm_movemask_ps(_mm_cmpunord_ss(red,red))&1))minimum=_mm_min_ss(minimum,red);
    const auto sum=_mm_add_ss(maximum,minimum),lightness=_mm_mul_ss(load(image,0x140e60),sum);
    auto saturation=_mm_setzero_ps(),hue=_mm_setzero_ps();
    if(_mm_cvtss_f32(maximum)!=_mm_cvtss_f32(minimum)){
        const auto difference=_mm_sub_ss(maximum,minimum);
        const auto complement=_mm_sub_ss(_mm_sub_ss(load(image,0x140e64),maximum),minimum);
        const auto denominator=select(_mm_cmplt_ss(load(image,0x140e60),lightness),complement,sum);
        if(_mm_cvtss_f32(maximum)==_mm_cvtss_f32(red)){
            const auto part=_mm_div_ss(_mm_sub_ss(green,blue),difference);
            hue=_mm_add_ss(_mm_and_ps(load(image,0x140e6c),_mm_cmplt_ss(green,blue)),part);
        }else if(_mm_cvtss_f32(maximum)==_mm_cvtss_f32(green))hue=_mm_add_ss(_mm_div_ss(_mm_sub_ss(blue,red),difference),load(image,0x140e64));
        else if(_mm_cvtss_f32(maximum)==_mm_cvtss_f32(blue))hue=_mm_add_ss(_mm_div_ss(_mm_sub_ss(red,green),difference),load(image,0x140e68));
        else hue=lightness;
        saturation=_mm_div_ss(difference,denominator);hue=_mm_div_ss(hue,load(image,0x140e6c));
    }
    put(state+0x3f8,W(2));put(state+0x400,user);put(state+0x408,title);put(state+0x410,now);zero(state,0x418);put(state+0x428,completion);
    put(state+0x430,firstPair);put(state+0x438,blueBits);put(state+0x43c,_mm_cvtss_f32(hue));put(state+0x440,_mm_cvtss_f32(saturation));put(state+0x444,_mm_cvtss_f32(lightness));
    for(auto offset:{0x448,0x458,0x468,0x478,0x488})zero(state,offset);
    return blueBits;
}
void recovered_suggestion_modal_168f0(std::uint8_t *state,W title,W user,W filter,W completion,W options,W count,RecoveredFrameInvoker call){
    call(0x169c0,address(state),1);const auto now=call(0x4c270);
    put(state+0x3f8,W(4));put(state+0x400,user);put(state+0x408,title);put(state+0x410,now);zero(state,0x418);put(state+0x428,filter);
    put(state+0x430,completion);put(state+0x438,options);put(state+0x440,count);
    for(auto offset:{0x448,0x458,0x468,0x478,0x488})zero(state,offset);
    recovered_widget_input_112d0(state,filter,address(state+0x3f8));recovered_widget_release_11370(state);
}
