#include "Widgets.hpp"
#include "WidgetState.hpp"
#include "DisplayGeometry.hpp"
#include "Geometry.hpp"
#include "Rounding.hpp"
#include "ByteStrings.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>
#include <intrin.h>
namespace {
using W=std::uint64_t;
template<class T>T get(const void *p){T v;std::memcpy(&v,p,sizeof v);return v;}
template<class T>void put(void *p,T v){std::memcpy(p,&v,sizeof v);}
W address(const void *p){return std::uintptr_t(p);}
std::uint32_t bits(float value){return std::bit_cast<std::uint32_t>(value);}
float add(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float subtract(float a,float b){return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float multiply(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
}

// Native164F0 appends permitted byte characters without storing a terminator.
// The exact length100 is rejected; larger lengths are not normalized.
std::uint64_t recovered_numeric_filter_164f0(std::uint8_t *text,std::uint32_t character){
    const auto length=recovered_string_length_ab840(text);
    const auto digit=std::uint8_t(character-0x30);
    const auto punctuation=std::uint8_t(character-0x2c);
    if(length!=100&&(digit<10||punctuation<3))text[length]=std::uint8_t(character);
    return length;
}

std::uint64_t recovered_color_accept_158c0(std::uint8_t *destination,const std::uint8_t *source){
    put(destination+8,get<std::uint32_t>(source+8));_ReadWriteBarrier();
    const auto pair=get<std::uint64_t>(source);put(destination,pair);return pair;
}

std::uint32_t recovered_color_widget_155a0(std::uint8_t *state,std::uint8_t *draw,std::uint64_t label,std::uint32_t *current,const std::uint8_t *image,std::uint64_t acceptEndpoint,RecoveredFrameInvoker call){
    const auto canvas=get<W>(draw);float rectangle[4];call(0x10860,address(rectangle),address(state),get<std::uint32_t>(image+0x140d88));
    float labelRect[4];std::memcpy(labelRect,rectangle,12);labelRect[3]=20.0f;
    float color[4];auto shade=get<float>(image+0x140d8c);recovered_color_74150(color,shade,shade,shade,1.0f);
    call(0x74ef0,canvas,address(color));call(0x79610,canvas,get<std::uint32_t>(image+0x140d90));
    call(0x10cb0,address(draw),address(labelRect),0,0,label);
    float preview[4];recovered_rect_a070(preview,add(add(rectangle[0],rectangle[2]),get<float>(image+0x140d94)),rectangle[1],get<float>(image+0x140d98),20.0f);
    shade=get<float>(image+0x140d9c);recovered_color_74150(color,shade,shade,shade,1.0f);
    call(0x74de0,canvas,address(color));call(0x749e0,canvas,get<std::uint32_t>(image+0x140da0));
    float copy[4];std::memcpy(copy,preview,16);const auto radius=get<std::uint32_t>(image+0x140da4);
    call(0x10b00,address(draw),address(copy),radius);
    const auto x=preview[0],y=preview[1],end=add(preview[2],x);
    std::uint32_t solid[4];recovered_color_74130(solid,current[0],current[1],current[2]);
    float translucent[4];recovered_color_74150(translucent,std::bit_cast<float>(current[0]),std::bit_cast<float>(current[1]),std::bit_cast<float>(current[2]),0.25f);
    alignas(16) std::uint8_t paint[76];
    call(0x75340,address(paint),canvas,bits(x),bits(y),bits(end),bits(y),address(solid),address(translucent));
    call(0x74f60,canvas,address(paint));std::memcpy(copy,preview,16);call(0x10a60,address(draw),address(copy),radius);
    const auto center=_mm_cvtsd_ss(_mm_setzero_ps(),_mm_add_sd(_mm_mul_sd(_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(rectangle[2])),_mm_set_sd(get<double>(image+0x140da8))),_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(rectangle[0]))));
    float hit[4];recovered_rect_a070(hit,_mm_cvtss_f32(center),rectangle[1],multiply(rectangle[2],get<float>(image+0x140db0)),rectangle[3]);
    std::memcpy(copy,hit,16);const auto clicked=recovered_widget_click_111f0(state,copy);
    if(clicked&0xff){std::uint32_t initial[3];initial[2]=current[2];std::memcpy(initial,current,8);call(0x16600,address(state),label,address(current),address(initial),acceptEndpoint);}
    return clicked;
}
// Captured13B20: animate before hit-testing, draw the interpolated background,
// consume the first click, mutate the inset rectangle, then draw the circle.
std::uint32_t recovered_toggle_widget_13b20(std::uint8_t *state,std::uint8_t *draw,float *rectangle,std::uint8_t *animation,std::uint8_t *current,const std::uint8_t *image,RecoveredFrameInvoker call){
    const auto now=get<double>(draw+8);
    const auto elapsed=_mm_cvtss_sd(_mm_setzero_pd(),_mm_cvtsd_ss(_mm_setzero_ps(),_mm_sub_sd(_mm_set_sd(now),_mm_set_sd(get<double>(animation+8)))));
    const auto enabled=*current;float value;
    const auto duration=get<double>(image+0x140c40);
    if(_mm_cvtsd_f64(elapsed)>duration){
        value=_mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),enabled));put(animation,value);
    }else{
        value=get<float>(animation);
        if(enabled){
            const auto one=get<float>(image+0x140c50);
            if(one>value){
                const auto sum=_mm_add_sd(_mm_div_sd(elapsed,_mm_set_sd(duration)),_mm_set_sd(double(value)));
                value=_mm_cvtss_f32(_mm_min_ss(_mm_cvtsd_ss(_mm_setzero_ps(),sum),_mm_set_ss(one)));put(animation,value);
            }
        }else if(value>0.0f){
            const auto sum=_mm_add_sd(_mm_div_sd(elapsed,_mm_set_sd(get<double>(image+0x140c48))),_mm_set_sd(double(value)));
            value=_mm_cvtss_f32(_mm_max_ss(_mm_cvtsd_ss(_mm_setzero_ps(),sum),_mm_setzero_ps()));put(animation,value);
        }
    }
    put(animation+8,now);const auto canvas=get<W>(draw);const auto amount=recovered_smooth_a280(value,image);
    float copy[4];std::memcpy(copy,rectangle,16);
    const auto hovering=recovered_widget_hover_11180(state,copy);
    const auto grey=get<float>(image+(hovering&0xff?0x140c58:0x140c54));
    float first[4],second[4],color[4];recovered_color_74150(first,grey,grey,grey,1.0f);
    std::memcpy(second,state+0x360,16);recovered_color_blend_741d0(color,first,second,amount,image);
    call(0x74ef0,canvas,address(color));std::memcpy(copy,rectangle,16);
    call(0x10a60,address(draw),address(copy),get<std::uint32_t>(image+0x140c5c));
    std::memcpy(copy,rectangle,16);const auto clicked=recovered_widget_click_111f0(state,copy);
    if(clicked&0xff)*current^=1;
    float inset[4];std::memcpy(copy,rectangle,16);recovered_rectangle_inset_a130(inset,copy,get<float>(image+0x140c60));
    std::memcpy(rectangle,inset,16);const auto height=rectangle[3];
    const auto white=get<float>(image+0x140c64);recovered_color_74150(color,white,white,white,1.0f);
    call(0x74ef0,canvas,address(color));call(0x75bc0,canvas);
    const auto integerHeight=_mm_cvttss_si32(_mm_set_ss(height));
    const auto rounded=_mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),integerHeight));
    const auto half=multiply(rounded,get<float>(image+0x140c68));
    const auto firstX=add(half,rectangle[0]);const auto secondX=subtract(add(rectangle[0],rectangle[2]),half);
    const auto x=recovered_scalar_lerp_a2b0(firstX,secondX,amount);const auto y=add(half,rectangle[1]);
    call(0x76f40,canvas,bits(x),bits(y),bits(rounded));call(0x77210,canvas);
    return clicked;
}
//13D90 preserves label rendering order before constructing its toggle rectangle.
std::uint64_t recovered_checkbox_widget_13d90(std::uint8_t *state,std::uint8_t *draw,const char *label,std::uint8_t *animation,std::uint8_t *current,const std::uint8_t *image,RecoveredFrameInvoker call){
    const auto canvas=get<W>(draw);float rectangle[4];
    call(0x10860,address(rectangle),address(state),get<std::uint32_t>(image+0x140c6c));
    const auto grey=get<float>(image+0x140c70);float color[4];recovered_color_74150(color,grey,grey,grey,1.0f);
    call(0x74ef0,canvas,address(color));call(0x79610,canvas,get<std::uint32_t>(image+0x140c74));
    float copy[4];std::memcpy(copy,rectangle,16);call(0x10cb0,address(draw),address(copy),0,0,address(label));
    float toggle[4];recovered_rect_a070(toggle,add(add(rectangle[0],rectangle[2]),get<float>(image+0x140c78)),rectangle[1],get<float>(image+0x140c7c),rectangle[3]);
    std::memcpy(copy,toggle,16);return recovered_toggle_widget_13b20(state,draw,copy,animation,current,image,call);
}

//14370 accepts comma or dot decimals, wraps integer accumulation in DWORD,
// applies the display divisor and native roundf step, then ordered bounds.
std::uint32_t recovered_numeric_action_14370(std::uint8_t *state,const float *track,const float *hit,float minimum,float maximum,float step,float displayScale,std::uint8_t *active,float *current,std::uint64_t filterEndpoint,const std::uint8_t *image){
    float copy[4];std::memcpy(copy,hit,16);
    if(recovered_widget_click_111f0(state,copy)&0xff){
        *active=1;
        if(state[0x4ca]==1)recovered_widget_input_112d0(state,filterEndpoint,address(current));
    }else if(state[0x4c8]==0&&!recovered_widget_identity_11340(state,address(current)))*active=0;
    const auto result=*active;if(result!=1)return result;
    float value;
    if(recovered_widget_identity_11340(state,address(current))){
        const char *text=recovered_widget_take_text_11390(state);if(!text)return result;
        const bool negative=*text=='-';const auto sign=negative?std::uint32_t(-1):std::uint32_t(1);text+=negative;
        std::uint32_t integer=0;
        auto character=std::int32_t(static_cast<signed char>(*text));
        auto digit=std::uint32_t(character-0x30);
        if(digit<=9){
            do{integer=integer*10+digit;character=std::int32_t(static_cast<signed char>(*++text));digit=std::uint32_t(character-0x30);}while(digit<10);
        }
        if((std::uint8_t(character)|2)==0x2e){
            digit=std::uint32_t(std::int32_t(static_cast<signed char>(text[1]))-0x30);
            float fraction=0;
            if(digit<=9){
                text+=2;float multiplier=get<float>(image+0x140cd8);const auto reduction=get<double>(image+0x140ce0);
                do{
                    const auto integerDigit=_mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),std::bit_cast<std::int32_t>(digit)));
                    fraction=add(fraction,multiply(integerDigit,multiplier));
                    const auto next=_mm_mul_sd(_mm_set_sd(double(multiplier)),_mm_set_sd(reduction));
                    multiplier=_mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),next));
                    digit=std::uint32_t(std::int32_t(static_cast<signed char>(*text++))-0x30);
                }while(digit<10);
            }
            const auto number=_mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),std::bit_cast<std::int32_t>(integer)));
            const auto signedUnit=_mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),std::bit_cast<std::int32_t>(sign)));
            value=multiply(add(number,fraction),signedUnit);
        }else value=_mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),std::bit_cast<std::int32_t>(integer*sign)));
        if(displayScale!=0.0f)value=_mm_cvtss_f32(_mm_div_ss(_mm_set_ss(value),_mm_set_ss(displayScale)));
    }else{
        const auto position=_mm_div_ss(_mm_sub_ss(_mm_set_ss(get<float>(state+0x4a8)),_mm_set_ss(track[0])),_mm_set_ss(track[2]));
        const auto difference=_mm_sub_ss(_mm_set_ss(maximum),_mm_set_ss(minimum));
        value=_mm_cvtss_f32(_mm_add_ss(_mm_mul_ss(difference,position),_mm_set_ss(minimum)));
    }
    if(step!=0.0f){
        value=_mm_cvtss_f32(_mm_div_ss(_mm_set_ss(value),_mm_set_ss(step)));
        value=multiply(recovered_round_float_b1fb0(value,image),step);
    }
    *current=value;
    if(minimum>=value)*current=minimum;
    else if(value>=maximum)*current=maximum;
    return result;
}

std::uint32_t recovered_number_widget_13f40(std::uint8_t *state,std::uint8_t *draw,const char *label,const char *format,std::uint8_t *animation,float minimum,float maximum,float step,float displayScale,float *current,std::uint8_t *image,std::uint64_t filterEndpoint,RecoveredFrameInvoker call){
    const auto canvas=get<W>(draw);float rectangle[4];call(0x10860,address(rectangle),address(state),get<std::uint32_t>(image+0x140c90));
    float color[4];const auto grey=get<float>(image+0x140c94);recovered_color_74150(color,grey,grey,grey,1.0f);
    call(0x74ef0,canvas,address(color));call(0x79610,canvas,get<std::uint32_t>(image+0x140c98));
    float copy[4];std::memcpy(copy,rectangle,16);call(0x10cb0,address(draw),address(copy),0,0,address(label));
    auto y=add(rectangle[1],get<float>(image+0x140c9c));
    auto halfWidth=_mm_mul_sd(_mm_set_sd(double(rectangle[2])),_mm_set_sd(get<double>(image+0x140ca0)));
    const auto x=_mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_add_sd(_mm_set_sd(double(rectangle[0])),halfWidth)));
    y=add(y,get<float>(image+0x140ca8));
    const auto width=_mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_add_sd(halfWidth,_mm_set_sd(get<double>(image+0x140cb0)))));
    float track[4];recovered_rect_a070(track,x,y,width,4.0f);
    std::memcpy(copy,rectangle,16);const auto hovering=recovered_widget_hover_11180(state,copy);
    const auto shade=get<float>(image+(hovering&0xff?0x140cbc:0x140cb8));recovered_color_74150(color,shade,shade,shade,1.0f);
    call(0x74ef0,canvas,address(color));std::memcpy(copy,track,16);const auto radius=get<float>(image+0x140cc0);
    call(0x10a60,address(draw),address(copy),bits(radius));
    const auto relative=_mm_div_ss(_mm_sub_ss(_mm_set_ss(*current),_mm_set_ss(minimum)),_mm_sub_ss(_mm_set_ss(maximum),_mm_set_ss(minimum)));
    const auto fraction=recovered_float_clamp_a1f0(0.0f,get<float>(image+0x140cc4),_mm_cvtss_f32(relative));
    const auto elapsed=_mm_cvtsd_ss(_mm_setzero_ps(),_mm_sub_sd(_mm_set_sd(get<double>(draw+8)),_mm_set_sd(get<double>(animation+8))));
    const auto durationRatio=_mm_cvtsd_ss(_mm_setzero_ps(),_mm_div_sd(_mm_cvtss_sd(_mm_setzero_pd(),elapsed),_mm_set_sd(get<double>(image+0x140cc8))));
    const auto amount=recovered_limited_lerp_a260(get<float>(animation+4),fraction,_mm_cvtss_f32(durationRatio),image);
    put(animation+4,amount);put(animation+8,get<double>(draw+8));
    const auto end=recovered_scalar_lerp_a2b0(x,add(width,x),amount);
    float filled[4];recovered_rect_a070(filled,x,y,subtract(end,x),4.0f);
    std::memcpy(color,state+0x360,16);call(0x74ef0,canvas,address(color));std::memcpy(copy,filled,16);
    call(0x10a60,address(draw),address(copy),bits(radius));call(0x75bc0,canvas);
    const auto centerY=add(radius,y);call(0x76f40,canvas,bits(end),bits(centerY),get<std::uint32_t>(image+0x140cd0));call(0x77210,canvas);
    float hit[4];std::memcpy(copy,track,16);std::memcpy(hit,rectangle,16);
    const auto result=recovered_numeric_action_14370(state,copy,hit,minimum,maximum,step,displayScale,animation,current,filterEndpoint,image);
    const char *tooltip=nullptr;
    if(*animation!=0){
        if(recovered_widget_identity_11340(state,address(current)))tooltip=reinterpret_cast<const char *>(state+0x378);
        else goto format_tooltip;
    }else{
        std::memcpy(copy,rectangle,16);
        if(!(recovered_widget_hover_11180(state,copy)&0xff)||state[0x4c8]!=0)return result;
        if(recovered_widget_identity_11340(state,address(current)))tooltip=reinterpret_cast<const char *>(state+0x378);
        else {
format_tooltip:
            const auto original=_mm_set_ss(*current);const auto scaled=_mm_mul_ss(_mm_set_ss(displayScale),original);
            const auto enabled=_mm_cmpneq_ss(_mm_setzero_ps(),_mm_set_ss(displayScale));
            const auto selected=_mm_or_ps(_mm_and_ps(scaled,enabled),_mm_andnot_ps(enabled,original));
            const auto value=_mm_cvtss_sd(_mm_setzero_pd(),selected);
            tooltip=reinterpret_cast<const char *>(image+0x2f7670);
            call(0xab710,address(tooltip),0x40,address(format?format:reinterpret_cast<const char *>(image+0x140e53)),std::bit_cast<W>(_mm_cvtsd_f64(value)));
        }
    }
    const auto packed=_mm_unpacklo_ps(_mm_set_ss(end),_mm_set_ss(y));
    const auto integerPosition=_mm_cvttps_epi32(packed);state[0x268]=1;
    //13D0B0 is the exact captured protected copy transfer. Preserve its contract.
    call(0x13d0b0,address(state+0x26a),address(tooltip),0x64);
    _mm_storel_pi(reinterpret_cast<__m64 *>(state+0x2d0),_mm_cvtepi32_ps(integerPosition));return result;
}

std::uint32_t recovered_range_widget_14580(std::uint8_t *state,std::uint8_t *draw,const char *label,const char *format,const char *pairFormat,std::uint8_t *animation,float minimum,float maximum,float step,float displayScale,float *lower,float *upper,std::uint8_t *image,std::uint64_t filterEndpoint,RecoveredFrameInvoker call){
    const auto canvas=get<W>(draw);float rectangle[4];call(0x10860,address(rectangle),address(state),get<std::uint32_t>(image+0x140ce8));
    float color[4];const auto grey=get<float>(image+0x140cec);recovered_color_74150(color,grey,grey,grey,1.0f);
    call(0x74ef0,canvas,address(color));call(0x79610,canvas,get<std::uint32_t>(image+0x140cf0));
    float copy[4];std::memcpy(copy,rectangle,16);call(0x10cb0,address(draw),address(copy),0,0,address(label));
    auto y=add(rectangle[1],get<float>(image+0x140cf4));
    const auto halfWidth=_mm_mul_sd(_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(rectangle[2])),_mm_set_sd(get<double>(image+0x140cf8)));
    const auto x=_mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_add_sd(_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(rectangle[0])),halfWidth)));
    y=add(y,get<float>(image+0x140d00));
    const auto width=_mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_add_sd(halfWidth,_mm_set_sd(get<double>(image+0x140d08)))));
    float track[4];recovered_rect_a070(track,x,y,width,4.0f);
    std::memcpy(copy,rectangle,16);const auto hovering=recovered_widget_hover_11180(state,copy);
    const auto shade=get<float>(image+(hovering&0xff?0x140d14:0x140d10));recovered_color_74150(color,shade,shade,shade,1.0f);
    call(0x74ef0,canvas,address(color));std::memcpy(copy,track,16);const auto radius=get<float>(image+0x140d18);
    call(0x10a60,address(draw),address(copy),bits(radius));
    const auto difference=subtract(maximum,minimum);
    const auto lowAmount=recovered_float_clamp_a1f0(0.0f,get<float>(image+0x140d1c),_mm_cvtss_f32(_mm_div_ss(_mm_set_ss(subtract(*lower,minimum)),_mm_set_ss(difference))));
    const auto highAmount=recovered_float_clamp_a1f0(0.0f,get<float>(image+0x140d1c),_mm_cvtss_f32(_mm_div_ss(_mm_set_ss(subtract(*upper,minimum)),_mm_set_ss(difference))));
    const auto elapsed=_mm_cvtsd_ss(_mm_setzero_ps(),_mm_sub_sd(_mm_set_sd(get<double>(draw+8)),_mm_set_sd(get<double>(animation+0x10))));
    const auto ratio=_mm_cvtsd_ss(_mm_setzero_ps(),_mm_div_sd(_mm_cvtss_sd(_mm_setzero_pd(),elapsed),_mm_set_sd(get<double>(image+0x140d20))));
    put(animation+4,recovered_limited_lerp_a260(get<float>(animation+4),lowAmount,_mm_cvtss_f32(ratio),image));
    put(animation+8,recovered_limited_lerp_a260(get<float>(animation+8),highAmount,_mm_cvtss_f32(ratio),image));put(animation+0x10,get<double>(draw+8));
    const auto end=add(x,width);const auto lowX=recovered_scalar_lerp_a2b0(x,end,get<float>(animation+4));
    const auto highX=recovered_scalar_lerp_a2b0(x,end,get<float>(animation+8));
    float filled[4];recovered_rect_a070(filled,lowX,y,subtract(highX,lowX),4.0f);
    std::memcpy(color,state+0x360,16);call(0x74ef0,canvas,address(color));std::memcpy(copy,filled,16);call(0x10a60,address(draw),address(copy),bits(radius));
    const auto centerY=add(radius,y);const auto circleRadius=get<std::uint32_t>(image+0x140d28);
    call(0x75bc0,canvas);call(0x76f40,canvas,bits(lowX),bits(centerY),circleRadius);call(0x77210,canvas);
    call(0x75bc0,canvas);call(0x76f40,canvas,bits(highX),bits(centerY),circleRadius);call(0x77210,canvas);
    const auto centerDouble=_mm_mul_sd(_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(add(lowX,highX))),_mm_set_sd(get<double>(image+0x140cf8)));
    const auto center=_mm_cvtss_f32(_mm_cvtepi32_ps(_mm_cvttpd_epi32(centerDouble)));
    const auto distance=subtract(center,x),extra=get<float>(image+0x140d30);
    float lowHit[4],highHit[4];recovered_rect_a070(lowHit,add(get<float>(image+0x140d2c),x),rectangle[1],add(distance,extra),rectangle[3]);
    recovered_rect_a070(highHit,center,rectangle[1],add(subtract(width,distance),extra),rectangle[3]);
    std::memcpy(copy,track,16);float hit[4];std::memcpy(hit,lowHit,16);
    const auto lowerResult=recovered_numeric_action_14370(state,copy,hit,minimum,maximum,step,displayScale,animation,lower,filterEndpoint,image);
    const char *tooltip=nullptr;std::int32_t anchor;std::uint32_t result;
    auto formatOne=[&](float *current){
        const auto raw=_mm_set_ss(*current),scaled=_mm_mul_ss(_mm_set_ss(displayScale),raw),mask=_mm_cmpneq_ss(_mm_setzero_ps(),_mm_set_ss(displayScale));
        const auto selected=_mm_or_ps(_mm_and_ps(scaled,mask),_mm_andnot_ps(mask,raw));
        const auto value=_mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(),selected));
        const auto *out=reinterpret_cast<const char *>(image+0x2f7670);
        call(0xab710,address(out),0x40,address(format?format:reinterpret_cast<const char *>(image+0x140e53)),std::bit_cast<W>(value));return out;
    };
    if(lowerResult&0xff){
        if(*lower>*upper)*upper=*lower;
        tooltip=recovered_widget_identity_11340(state,address(lower))?reinterpret_cast<const char *>(state+0x378):formatOne(lower);
        anchor=_mm_cvttss_si32(_mm_set_ss(lowX));result=(std::uint32_t(address(animation))&0xffffff00u)|1;
    }else{
        std::memcpy(copy,track,16);std::memcpy(hit,highHit,16);
        const auto upperResult=recovered_numeric_action_14370(state,copy,hit,minimum,maximum,step,displayScale,animation+1,upper,filterEndpoint,image);
        if(upperResult&0xff){
            if(*lower>*upper)*lower=*upper;
            tooltip=recovered_widget_identity_11340(state,address(upper))?reinterpret_cast<const char *>(state+0x378):formatOne(upper);
            anchor=_mm_cvttss_si32(_mm_set_ss(highX));result=(std::uint32_t(address(animation))&0xffffff00u)|1;
        }else{
            std::memcpy(copy,rectangle,16);
            if(!(recovered_widget_hover_11180(state,copy)&0xff))return 0;
            if(state[0x4c8]==1&&animation[0]==0&&animation[1]!=1)return 0;
            const auto low=displayScale!=0.0f?multiply(displayScale,*lower):*lower;
            const auto high=displayScale!=0.0f?multiply(displayScale,*upper):*upper;
            tooltip=reinterpret_cast<const char *>(image+0x2f7630);
            call(0xab710,address(tooltip),0x40,address(pairFormat?pairFormat:reinterpret_cast<const char *>(image+0x140e2c)),std::bit_cast<W>(double(low)),std::bit_cast<W>(double(high)));
            const auto sum=add(add(lowHit[0],lowHit[2]),highHit[0]);
            anchor=_mm_cvttsd_si32(_mm_mul_sd(_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(sum)),_mm_set_sd(get<double>(image+0x140cf8))));result=0;
        }
    }
    const auto integerY=_mm_cvttss_si32(_mm_set_ss(y));state[0x268]=1;call(0x13d0b0,address(state+0x26a),address(tooltip),0x64);
    _mm_storel_pi(reinterpret_cast<__m64 *>(state+0x2d0),_mm_cvtepi32_ps(_mm_set_epi32(0,0,integerY,anchor)));return result;
}

std::uint64_t recovered_choice_filter_15540(std::uint8_t *text,std::uint32_t character){
    const auto length=recovered_string_length_ab840(text);
    const auto letter=std::uint8_t((std::uint8_t(character)&0xdf)-0x41),digit=std::uint8_t(character-0x30);
    if(length<=99&&(letter<26||digit<10||std::uint8_t(character)==0x20))text[length]=std::uint8_t(character);
    return length;
}
void recovered_choice_accept_15590(std::uint32_t *current,std::uint32_t index,std::uint64_t option){if(option)*current=index+1;}

std::uint32_t recovered_choice_widget_14d00(std::uint8_t *state,std::uint8_t *draw,std::uint64_t label,std::uint8_t *animation,std::uint32_t count,const std::uint64_t *options,std::uint32_t *current,std::uint8_t flag,const std::uint8_t *image,std::uint64_t filterEndpoint,std::uint64_t acceptEndpoint,RecoveredFrameInvoker call){
    const auto canvas=get<W>(draw);
    const auto elapsed=_mm_cvtsd_ss(_mm_setzero_ps(),_mm_sub_sd(_mm_set_sd(get<double>(draw+8)),_mm_set_sd(get<double>(animation+8))));
    const auto target=animation[0x14]?_mm_cvtss_f32(_mm_cvtsi64_ss(_mm_setzero_ps(),std::int64_t(std::uint32_t(count*28)))):get<float>(image+0x140d38);
    const auto ratio=_mm_cvtsd_ss(_mm_setzero_ps(),_mm_div_sd(_mm_cvtss_sd(_mm_setzero_pd(),elapsed),_mm_set_sd(get<double>(image+0x140d40))));
    const auto height=recovered_limited_lerp_a260(get<float>(animation+0x10),target,_mm_cvtss_f32(ratio),image);
    put(animation+0x10,height);put(animation+8,get<double>(draw+8));
    float rectangle[4];call(0x10860,address(rectangle),address(state),bits(height));
    float color[4];auto shade=get<float>(image+0x140d48);recovered_color_74150(color,shade,shade,shade,1.0f);
    call(0x74ef0,canvas,address(color));call(0x79610,canvas,get<std::uint32_t>(image+0x140d4c));
    float labelRect[4];std::memcpy(labelRect,rectangle,12);labelRect[3]=20.0f;call(0x10cb0,address(draw),address(labelRect),0,0,label);
    const auto x=_mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_add_sd(_mm_mul_sd(_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(rectangle[2])),_mm_set_sd(get<double>(image+0x140d50))),_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(rectangle[0])))));
    float selection[4];recovered_rect_a070(selection,x,rectangle[1],multiply(rectangle[2],get<float>(image+0x140d58)),rectangle[3]);
    shade=get<float>(image+0x140d5c);recovered_color_74150(color,shade,shade,shade,1.0f);call(0x74de0,canvas,address(color));call(0x749e0,canvas,get<std::uint32_t>(image+0x140d60));
    float copy[4];std::memcpy(copy,selection,16);call(0x10b00,address(draw),address(copy),get<std::uint32_t>(image+0x140d64));
    if(animation[0x14]){
        float alpha[4];recovered_color_74150(alpha,shade,shade,shade,1.0f);recovered_color_741b0(color,alpha,get<float>(image+0x140d58));call(0x74de0,canvas,address(color));
        if(!count)return 0;
        const auto rowHeight=_mm_cvtss_f32(_mm_div_ss(_mm_set_ss(selection[3]),_mm_cvtsi64_ss(_mm_setzero_ps(),std::int64_t(std::uint64_t(count)))));
        const auto inverted=std::uint8_t(flag^1);std::uint32_t selected=0;
        for(std::uint64_t index=0;index<count;++index){
            const auto rowY=add(multiply(_mm_cvtss_f32(_mm_cvtsi64_ss(_mm_setzero_ps(),std::int64_t(std::uint32_t(index)))),rowHeight),selection[1]);
            float row[4];recovered_rect_a070(row,selection[0],rowY,selection[2],rowHeight);const auto option=options[index];
            std::memcpy(copy,row,16);const auto hovering=recovered_widget_hover_11180(state,copy);const auto chosen=*current;
            if(index==chosen)std::memcpy(color,state+0x360,16);
            else{
                const auto permitted=std::uint8_t((index!=0)|inverted);
                const auto rowShade=get<float>(image+((hovering&0xff)?(std::uint8_t((index==0)|inverted)?0x140d78:0x140d80):(permitted?0x140d48:0x140d7c)));
                recovered_color_74150(color,rowShade,rowShade,rowShade,1.0f);
            }
            call(0x74ef0,canvas,address(color));std::memcpy(copy,row,16);call(0x10cb0,address(draw),address(copy),1,0,option);
            if(!(selected&1)){
                std::memcpy(copy,row,16);
                if(recovered_widget_click_111f0(state,copy)&0xff){*current=std::uint32_t(index);animation[0x14]=0;selected=1;}
                else selected=0;
            }else selected=1;
            if(index){call(0x75bc0,canvas);call(0x75bf0,canvas,bits(row[0]),bits(row[1]));call(0x75ec0,canvas,bits(add(row[0],row[2])),bits(row[1]));call(0x77f80,canvas);}
        }
        return selected;
    }
    std::memcpy(copy,selection,16);auto hovering=recovered_widget_hover_11180(state,copy);auto chosen=*current;
    if(std::uint8_t((flag^1)|(count<6))==0&&chosen){
        float clear[4];recovered_rect_a070(clear,add(subtract(selection[2],selection[3]),selection[0]),selection[1],selection[3],selection[3]);
        std::memcpy(copy,clear,16);const auto clearHover=recovered_widget_hover_11180(state,copy);
        if(clearHover&0xff)recovered_color_74150(color,get<float>(image+0x140d68),get<float>(image+0x140d6c),get<float>(image+0x140d6c),1.0f);
        else recovered_color_74150(color,shade,shade,shade,1.0f);
        call(0x74de0,canvas,address(color));
        const auto inset=_mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_mul_sd(_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(clear[3])),_mm_set_sd(get<double>(image+0x140d70)))));
        const auto left=add(clear[0],inset),top=add(clear[1],inset),right=subtract(add(clear[3],clear[0]),inset),bottom=subtract(add(clear[1],clear[3]),inset);
        call(0x75bc0,canvas);call(0x75bf0,canvas,bits(left),bits(top));call(0x75ec0,canvas,bits(right),bits(bottom));call(0x75bf0,canvas,bits(right),bits(top));call(0x75ec0,canvas,bits(left),bits(bottom));call(0x77f80,canvas);
        std::memcpy(copy,clear,16);if(recovered_widget_click_111f0(state,copy)&0xff){*current=0;chosen=0;}else chosen=*current;
        hovering=(hovering&0xffffff00u)|(std::uint8_t(hovering)&std::uint8_t(std::uint8_t(clearHover)^1));
    }
    const auto textShade=get<float>(image+((flag!=0&&chosen==0)?((hovering&0xff)?0x140d80:0x140d7c):((hovering&0xff)?0x140d78:0x140d48)));
    recovered_color_74150(color,textShade,textShade,textShade,1.0f);call(0x74ef0,canvas,address(color));
    const auto option=options[*current];std::memcpy(copy,selection,16);call(0x10cb0,address(draw),address(copy),1,0,option);
    std::memcpy(copy,selection,16);if(recovered_widget_click_111f0(state,copy)&0xff){
        if(count<6)animation[0x14]=1;
        else call(0x168f0,address(state),address(image+0x140e3a),address(current),filterEndpoint,acceptEndpoint,address(options+1),std::uint64_t(count-1));
    }
    return 0;
}

void recovered_list_suggestion_accept_16190(std::uint8_t *list,std::uint64_t option,const std::uint8_t *image,RecoveredFrameInvoker call){
    if(!option)return;const auto context=get<W>(list),endpoint=get<W>(list+0x20);
    std::uint32_t color[3]{get<std::uint32_t>(image+0x140df8),0,0};call(endpoint,context,option,address(color));
}
void recovered_list_text_accept_161d0(std::uint8_t *list,std::uint64_t text,const std::uint8_t *image,RecoveredFrameInvoker call){
    if(!text)return;const auto context=get<W>(list),endpoint=get<W>(list+0x20);
    std::uint32_t color[3]{get<std::uint32_t>(image+0x140dfc),0,0};call(endpoint,context,text,address(color));
}
std::uint32_t recovered_list_widget_158e0(std::uint8_t *state,std::uint8_t *draw,std::uint64_t label,std::uint64_t title,std::uint64_t filter,std::uint32_t kind,std::uint8_t *list,std::uint64_t suggestions,std::uint64_t suggestionCount,const std::uint8_t *image,std::uint64_t colorAccept,std::uint64_t suggestionAccept,std::uint64_t textAccept,RecoveredFrameInvoker call){
    const auto canvas=get<W>(draw);const auto count=call(get<W>(list+8),get<W>(list));const auto rows=count+1;
    auto unsignedFloat=[](W v){
        auto converted=_mm_cvtsi64_ss(_mm_setzero_ps(),std::bit_cast<std::int64_t>(v));
        if(v>>63){converted=_mm_cvtsi64_ss(_mm_setzero_ps(),std::int64_t((v>>1)|(v&1)));converted=_mm_add_ss(converted,converted);}return _mm_cvtss_f32(converted);
    };
    float rectangle[4];call(0x10860,address(rectangle),address(state),bits(unsignedFloat(rows*28)));
    float color[4];auto shade=get<float>(image+0x140db8);recovered_color_74150(color,shade,shade,shade,1.0f);
    call(0x74ef0,canvas,address(color));call(0x79610,canvas,get<std::uint32_t>(image+0x140dbc));
    float labelRect[4];std::memcpy(labelRect,rectangle,12);labelRect[3]=20.0f;call(0x10cb0,address(draw),address(labelRect),0,0,label);
    const auto x=_mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_add_sd(_mm_mul_sd(_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(rectangle[2])),_mm_set_sd(get<double>(image+0x140dc0))),_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(rectangle[0])))));
    float selection[4];recovered_rect_a070(selection,x,rectangle[1],multiply(rectangle[2],get<float>(image+0x140dc8)),rectangle[3]);
    shade=get<float>(image+0x140dcc);recovered_color_74150(color,shade,shade,shade,1.0f);call(0x74de0,canvas,address(color));call(0x749e0,canvas,get<std::uint32_t>(image+0x140dd0));
    float copy[4];std::memcpy(copy,selection,16);call(0x10b00,address(draw),address(copy),get<std::uint32_t>(image+0x140dd4));
    const auto rowHeight=_mm_cvtss_f32(_mm_div_ss(_mm_set_ss(selection[3]),_mm_set_ss(unsignedFloat(rows))));
    W removed=~W(0),result=0;
    for(W index=0;index<count;++index){
        float row[4];recovered_rect_a070(row,selection[0],add(multiply(unsignedFloat(index),rowHeight),selection[1]),selection[2],rowHeight);
        const auto text=call(get<W>(list+0x10),get<W>(list),index);const auto length=recovered_string_length_ab840(reinterpret_cast<const std::uint8_t *>(std::uintptr_t(text)));
        const auto end=text+(length>=20?20:length);recovered_color_74150(color,get<float>(image+0x140db8),get<float>(image+0x140db8),get<float>(image+0x140db8),1.0f);call(0x74ef0,canvas,address(color));
        std::memcpy(copy,row,16);call(0x10da0,address(draw),address(copy),1,0,text,end);
        if(kind==1){
            float square[4],preview[4];recovered_rect_a070(square,row[0],row[1],row[3],row[3]);recovered_rectangle_inset_a130(preview,square,get<float>(image+0x140dd8));
            const auto itemColor=call(get<W>(list+0x18),get<W>(list),index);const auto *rgba=reinterpret_cast<const std::uint32_t *>(std::uintptr_t(itemColor));
            std::uint32_t solid[4];recovered_color_74130(solid,rgba[0],rgba[1],rgba[2]);call(0x74ef0,canvas,address(solid));
            std::memcpy(copy,preview,16);call(0x10a60,address(draw),address(copy),get<std::uint32_t>(image+0x140ddc));
            std::memcpy(copy,preview,16);if(recovered_widget_click_111f0(state,copy)&0xff){
                std::uint32_t initial[3];initial[2]=rgba[2];std::memcpy(initial,rgba,8);
                result=(call(0x16600,address(state),text,itemColor,address(initial),colorAccept)&~W(0xff))|1;
            }
        }
        float remove[4];recovered_rect_a070(remove,add(subtract(row[2],row[3]),row[0]),row[1],row[3],row[3]);
        std::memcpy(copy,remove,16);const auto hovering=recovered_widget_hover_11180(state,copy);
        if(hovering&0xff)recovered_color_74150(color,get<float>(image+0x140de0),get<float>(image+0x140de4),get<float>(image+0x140de4),1.0f);
        else recovered_color_74150(color,shade,shade,shade,1.0f);
        call(0x74de0,canvas,address(color));
        const auto inset=_mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_mul_sd(_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(remove[3])),_mm_set_sd(get<double>(image+0x140de8)))));
        const auto left=add(remove[0],inset),top=add(remove[1],inset),right=subtract(add(remove[3],remove[0]),inset),bottom=subtract(add(remove[1],remove[3]),inset);
        call(0x75bc0,canvas);call(0x75bf0,canvas,bits(left),bits(top));call(0x75ec0,canvas,bits(right),bits(bottom));call(0x75bf0,canvas,bits(right),bits(top));call(0x75ec0,canvas,bits(left),bits(bottom));call(0x77f80,canvas);
        std::memcpy(copy,remove,16);if(recovered_widget_click_111f0(state,copy)&0xff)removed=index;
        float alpha[4];recovered_color_74150(alpha,shade,shade,shade,1.0f);recovered_color_741b0(color,alpha,get<float>(image+0x140dc8));call(0x74de0,canvas,address(color));
        call(0x75bc0,canvas);call(0x75bf0,canvas,bits(row[0]),bits(add(row[1],row[3])));call(0x75ec0,canvas,bits(add(row[0],row[2])),bits(add(row[1],row[3])));call(0x77f80,canvas);
    }
    if(removed!=~W(0)){call(get<W>(list+0x28),get<W>(list),removed);result=(result&~W(0xff))|1;}
    float addRow[4];recovered_rect_a070(addRow,selection[0],add(multiply(unsignedFloat(count),rowHeight),selection[1]),selection[2],rowHeight);
    std::memcpy(copy,addRow,16);const auto hovering=recovered_widget_hover_11180(state,copy);
    shade=get<float>(image+(hovering&0xff?0x140df4:0x140df0));recovered_color_74150(color,shade,shade,shade,1.0f);call(0x74ef0,canvas,address(color));
    std::memcpy(copy,addRow,16);call(0x10cb0,address(draw),address(copy),1,0,address(image+0x140e46));
    std::memcpy(copy,addRow,16);if(recovered_widget_click_111f0(state,copy)&0xff){
        if(suggestions)call(0x168f0,address(state),title,address(list),filter,suggestionAccept,suggestions,suggestionCount);
        else call(0x16530,address(state),title,address(list),filter,textAccept);
        result=(result&~W(0xff))|1;
    }
    return std::uint32_t((result&~W(0xff))|(result&1));
}
