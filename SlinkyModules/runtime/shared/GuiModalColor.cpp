#include "GuiModalColor.hpp"
#include "ByteStrings.hpp"
#include "Geometry.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>
#include <intrin.h>

namespace reconstruction::gui {
namespace {
using W=std::uint64_t;
template<class T>T read(const void *p){T v;std::memcpy(&v,p,sizeof v);return v;}
template<class T>void write(void *p,T v){std::memcpy(p,&v,sizeof v);_ReadWriteBarrier();}
W ptr(const void *p){return reinterpret_cast<std::uintptr_t>(p);}
W bits(float f){return std::bit_cast<std::uint32_t>(f);}
float single(W w){return std::bit_cast<float>(std::uint32_t(w));}
float f(const std::uint8_t *im,std::size_t rva){return read<float>(im+rva);}
float add(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float sub(float a,float b){return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float mul(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float div(float a,float b){return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a),_mm_set_ss(b)));}
__m128 select(__m128 mask,__m128 first,__m128 second){return _mm_or_ps(_mm_and_ps(mask,first),_mm_andnot_ps(mask,second));}
void gray(float *rgba,float value,RecoveredFrameInvoker call){call(0x74150,ptr(rgba),bits(value),bits(value),bits(value),bits(1.f));}
void hsl(float *rgba,std::uint8_t *state,float hue,float saturation,float lightness,RecoveredFrameInvoker call){
    call(0x74220,ptr(rgba),bits(hue),bits(saturation),bits(lightness));
}
// Both native RGB conversion blocks preserve their own max/min selector order.
void rgbToHsl(std::uint8_t *state,const std::uint8_t *image,bool history){
    const auto red=_mm_set_ss(read<float>(state+0x430)),green=_mm_set_ss(read<float>(state+0x434)),blue=_mm_set_ss(read<float>(state+0x438));
    __m128 maximum,minimum;
    if(history){
        maximum=blue;
        if(!(_mm_movemask_ps(_mm_cmpunord_ss(green,green))&1))maximum=_mm_max_ss(maximum,green);
        if(!(_mm_movemask_ps(_mm_cmpunord_ss(red,red))&1))maximum=_mm_max_ss(maximum,red);
        const auto gb=select(_mm_cmpunord_ss(green,green),blue,_mm_min_ss(blue,green));
        minimum=select(_mm_cmpunord_ss(red,red),gb,_mm_min_ss(gb,red));
    }else{
        const auto gb=select(_mm_cmpunord_ss(green,green),blue,_mm_max_ss(blue,green));
        maximum=select(_mm_cmpunord_ss(red,red),gb,_mm_max_ss(gb,red));
        minimum=blue;
        if(!(_mm_movemask_ps(_mm_cmpunord_ss(green,green))&1))minimum=_mm_min_ss(minimum,green);
        if(!(_mm_movemask_ps(_mm_cmpunord_ss(red,red))&1))minimum=_mm_min_ss(minimum,red);
    }
    auto hue=_mm_setzero_ps(),saturation=_mm_setzero_ps();
    const auto sum=_mm_add_ss(maximum,minimum),half=_mm_set_ss(f(image,0x140edc));
    const auto lightness=_mm_mul_ss(half,sum);
    if(_mm_cvtss_f32(maximum)!=_mm_cvtss_f32(minimum)){
        const auto difference=_mm_sub_ss(maximum,minimum);
        const auto complement=_mm_sub_ss(_mm_sub_ss(_mm_set_ss(f(image,0x140eb4)),maximum),minimum);
        const auto denominator=select(_mm_cmplt_ss(half,lightness),complement,sum);
        if(_mm_cvtss_f32(maximum)==_mm_cvtss_f32(red))hue=_mm_add_ss(_mm_and_ps(_mm_set_ss(f(image,0x140f00)),_mm_cmplt_ss(green,blue)),_mm_div_ss(_mm_sub_ss(green,blue),difference));
        else if(_mm_cvtss_f32(maximum)==_mm_cvtss_f32(green))hue=_mm_add_ss(_mm_div_ss(_mm_sub_ss(blue,red),difference),_mm_set_ss(f(image,0x140eb4)));
        else if(_mm_cvtss_f32(maximum)==_mm_cvtss_f32(blue))hue=_mm_add_ss(_mm_div_ss(_mm_sub_ss(red,green),difference),_mm_set_ss(f(image,0x140ecc)));
        else hue=lightness;
        saturation=_mm_div_ss(difference,denominator);hue=_mm_div_ss(hue,_mm_set_ss(f(image,0x140f00)));
    }
    write(state+0x43c,_mm_cvtss_f32(hue));write(state+0x440,_mm_cvtss_f32(saturation));write(state+0x444,_mm_cvtss_f32(lightness));
}
}

std::uint64_t filterHexColor_18830(std::uint8_t *text,std::uint32_t character){
    const auto length=recovered_string_length_ab840(text);
    if(length<=5){
        auto byte=std::uint8_t(character);
        if(std::uint8_t(byte-0x41)<=5)byte|=0x20;
        else if(std::uint8_t(byte-0x61)>=6&&std::uint8_t(byte-0x30)>=10)return length;
        write(text+length,byte);
    }
    return length;
}

std::uint8_t modalColorSlider_18880(std::uint8_t *state,std::uint8_t *ui,const float *rectangle,std::uint32_t component,const float *rgba,const std::uint8_t *image,RecoveredFrameInvoker call){
    auto canvas=read<W>(ui);float color[4],copy[4];
    const auto grayValue=f(image,0x140f20),lineWidth=f(image,0x140f24),radius=f(image,0x140f2c);
    gray(color,grayValue,call);call(0x74de0,canvas,ptr(color));call(0x749e0,canvas,bits(lineWidth));
    std::memcpy(copy,rectangle,16);call(0x10b00,ptr(ui),ptr(copy),bits(f(image,0x140f28)));
    const auto y=read<float>(rectangle+1),width=read<float>(rectangle+2),height=read<float>(rectangle+3);
    const auto x=add(mul(add(width,f(image,0x140f30)),read<float>(state+0x43c+4*component)),add(read<float>(rectangle),radius));
    std::memcpy(copy,rgba,16);canvas=read<W>(ui);call(0x75bc0,canvas);
    const auto middle=_mm_cvtsd_f64(_mm_add_sd(_mm_mul_sd(_mm_set_sd(double(height)),_mm_set_sd(read<double>(image+0x140f38))),_mm_set_sd(double(y))));
    call(0x76f40,canvas,bits(x),bits(_mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(middle)))),bits(radius));
    call(0x74ef0,canvas,ptr(copy));call(0x77210,canvas);
    gray(copy,grayValue,call);call(0x74de0,canvas,ptr(copy));call(0x749e0,canvas,bits(lineWidth));call(0x77f80,canvas);
    std::memcpy(copy,rectangle,16);
    if(std::uint8_t(call(0x111f0,ptr(state),ptr(copy)))){
        write(state+0x448+component,std::uint8_t(1));
    }else if(state[0x4c8]){
        if(state[0x448+component]!=1)return 0;
    }else{write(state+0x448+component,std::uint8_t(0));return 0;}
    const auto fraction=div(sub(read<float>(state+0x4a8),read<float>(rectangle)),read<float>(rectangle+2));
    write(state+0x43c+4*component,recovered_float_clamp_a1f0(0,f(image,0x140f40),fraction));
    return 1;
}

void renderModalColorSection(ModalFrame &frame,const PageDependencies &d){
    auto *state=frame.state,*ui=frame.ui;auto *image=d.image;const auto call=d.calls;
    auto canvas=read<W>(ui);float row[4],copy[4],preview[4],color[4],labelRect[4],editRect[4];
    call(0x10860,ptr(row),ptr(state),bits(f(image,0x140ee8)));
    std::memcpy(copy,row,16);const auto hovering=std::uint8_t(call(0x11180,ptr(state),ptr(copy)));
    call(0x74130,ptr(color),read<std::uint32_t>(state+0x430),read<std::uint32_t>(state+0x434),read<std::uint32_t>(state+0x438));
    call(0x74ef0,canvas,ptr(color));
    preview[0]=row[0];preview[1]=row[1];preview[2]=preview[3]=row[3];
    call(0x10a60,ptr(ui),ptr(preview),bits(f(image,0x140ee4)));
    gray(color,f(image,0x140ec8),call);call(0x74de0,canvas,ptr(color));call(0x749e0,canvas,bits(f(image,0x140eb4)));call(0x77f80,canvas);
    call(0x79610,canvas,bits(f(image,0x140e98)));gray(color,f(image,0x140ea8),call);call(0x74ef0,canvas,ptr(color));
    const auto labelX=add(add(row[0],row[3]),f(image,0x140e9c)),labelWidth=sub(row[2],sub(row[0],labelX));
    labelRect[0]=labelX;labelRect[1]=row[1];labelRect[2]=labelWidth;labelRect[3]=row[3];
    const auto advance=single(call(0x10cb0,ptr(ui),ptr(labelRect),0,0,ptr(image+0x140f79)));
    editRect[0]=advance;editRect[1]=row[1];editRect[2]=sub(labelWidth,sub(labelX,advance));editRect[3]=row[3];
    std::memcpy(copy,row,16);
    if(std::uint8_t(call(0x16330,ptr(state),ptr(ui),ptr(copy),d.hexFilterCallback_18830,ptr(state+0x428)))){
        gray(color,f(image,0x140e90),call);call(0x74ef0,canvas,ptr(color));
        call(0x16430,ptr(state),ptr(ui),ptr(editRect),0);
        const auto *text=reinterpret_cast<const std::uint8_t *>(std::uintptr_t(call(0x11390,ptr(state))));
        if(text){
            if(recovered_string_length_ab840(text)>5){
                for(std::size_t component=0;component<3;++component){
                    const auto first=read<std::uint8_t>(text+2*component),second=read<std::uint8_t>(text+2*component+1);
                    const auto high=std::uint8_t(first+(std::int8_t(first)>=0x61?0xa9:0xd0));
                    const auto low=std::uint8_t(second+(std::int8_t(second)>=0x61?0xa9:0xd0));
                    const auto value=std::uint32_t(high)<<4|std::uint32_t(low);
                    const auto normalized=_mm_div_sd(_mm_cvtsi32_sd(_mm_setzero_pd(),std::int32_t(value)),_mm_set_sd(read<double>(image+0x140ef8)));
                    write(state+0x430+4*component,_mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),normalized)));
                }
            }
            rgbToHsl(state,image,false);
        }
    }else{
        W rgb[3];for(std::size_t component=0;component<3;++component)rgb[component]=std::uint8_t(_mm_cvttss_si64(_mm_set_ss(mul(read<float>(state+0x430+4*component),f(image,0x140eec)))));
        call(0xab710,ptr(image+0x2f7720),7,ptr(image+0x140f7b),rgb[0],rgb[1],rgb[2]);
        gray(color,f(image,hovering?0x140ef0:0x140ea8),call);call(0x74ef0,canvas,ptr(color));
        call(0x10cb0,ptr(ui),ptr(editRect),0,0,ptr(image+0x2f7720));
    }
    call(0x13e90,ptr(state),ptr(ui),ptr(image+0x140f52));canvas=read<W>(ui);
    float hueRect[4],first[4],second[4],paint[19];
    call(0x10860,ptr(hueRect),ptr(state),bits(f(image,0x140ec4)));
    const auto cell=div(hueRect[2],f(image,0x140f00));
    const auto drawnWidth=single(call(0xb2920,bits(cell)));
    for(std::uint64_t index=0;index<6;++index){
        const auto x=single(call(0xb2a70,bits(add(mul(float(index),cell),hueRect[0]))));
        hsl(first,state,div(float(index),f(image,0x140f00)),read<float>(state+0x440),read<float>(state+0x444),call);
        hsl(second,state,div(float(index+1),f(image,0x140f00)),read<float>(state+0x440),read<float>(state+0x444),call);
        call(0x75340,ptr(paint),canvas,bits(x),bits(hueRect[1]),bits(add(cell,x)),bits(hueRect[1]),ptr(first),ptr(second));
        call(0x75bc0,canvas);
        if(index==0)call(0x76a10,canvas,bits(x),bits(hueRect[1]),bits(drawnWidth),bits(hueRect[3]),bits(5.f),0,0,bits(5.f));
        else if(index==5)call(0x76a10,canvas,bits(x),bits(hueRect[1]),bits(drawnWidth),bits(hueRect[3]),0,bits(5.f),bits(5.f),0);
        else call(0x76950,canvas,bits(x),bits(hueRect[1]),bits(drawnWidth),bits(hueRect[3]));
        call(0x74f60,canvas,ptr(paint));call(0x77210,canvas);
    }
    hsl(color,state,read<float>(state+0x43c),read<float>(state+0x440),read<float>(state+0x444),call);
    std::memcpy(copy,hueRect,16);const auto changedHue=std::uint8_t(call(0x18880,ptr(state),ptr(ui),ptr(copy),0,ptr(color)));
    call(0x13e90,ptr(state),ptr(ui),ptr(image+0x140f56));
    hsl(first,state,read<float>(state+0x43c),0,read<float>(state+0x444),call);
    const auto one=f(image,0x140e90);
    hsl(second,state,read<float>(state+0x43c),one,read<float>(state+0x444),call);
    call(0x741d0,ptr(color),ptr(first),ptr(second),bits(read<float>(state+0x440)));
    canvas=read<W>(ui);call(0x10860,ptr(row),ptr(state),bits(f(image,0x140ec4)));
    call(0x75340,ptr(paint),canvas,bits(row[0]),bits(row[1]),bits(add(row[2],row[0])),bits(add(row[3],row[1])),ptr(first),ptr(second));
    call(0x74f60,canvas,ptr(paint));std::memcpy(copy,row,16);call(0x10a60,ptr(ui),ptr(copy),bits(f(image,0x140ee4)));
    std::memcpy(copy,row,16);const auto changedSat=std::uint8_t(call(0x18880,ptr(state),ptr(ui),ptr(copy),1,ptr(color)));
    call(0x13e90,ptr(state),ptr(ui),ptr(image+0x140f61));
    hsl(first,state,read<float>(state+0x43c),read<float>(state+0x440),0,call);
    hsl(second,state,read<float>(state+0x43c),read<float>(state+0x440),one,call);
    call(0x741d0,ptr(color),ptr(first),ptr(second),bits(read<float>(state+0x444)));
    canvas=read<W>(ui);call(0x10860,ptr(row),ptr(state),bits(f(image,0x140ec4)));
    call(0x75340,ptr(paint),canvas,bits(row[0]),bits(row[1]),bits(add(row[2],row[0])),bits(add(row[3],row[1])),ptr(first),ptr(second));
    call(0x74f60,canvas,ptr(paint));std::memcpy(copy,row,16);call(0x10a60,ptr(ui),ptr(copy),bits(f(image,0x140ee4)));
    std::memcpy(copy,row,16);const auto changedLight=std::uint8_t(call(0x18880,ptr(state),ptr(ui),ptr(copy),2,ptr(color)));
    if(changedHue||changedSat||changedLight){
        hsl(color,state,read<float>(state+0x43c),read<float>(state+0x440),read<float>(state+0x444),call);
        write(state+0x430,read<W>(color));write(state+0x438,read<std::uint32_t>(color+2));
    }
    call(0x13e90,ptr(state),ptr(ui),ptr(image+0x140f6b));canvas=read<W>(ui);
    call(0x10860,ptr(row),ptr(state),bits(f(image,0x140ed8)));
    auto x=row[0];const auto width=mul(add(row[2],f(image,0x140f04)),f(image,0x140f08));
    const auto spacing=add(f(image,0x140e9c),width);
    call(0x749e0,canvas,bits(f(image,0x140eb4)));W selected=8;
    for(W offset=W(-8);offset!=0;++offset){
        const auto count=read<W>(image+0x2f76b0),plain=count+offset,wrapped=plain+8;
        const auto index=wrapped<8?wrapped:plain;
        float rectangle[4]={x,row[1],width,row[3]};std::memcpy(copy,rectangle,16);
        const auto over=std::uint8_t(call(0x11180,ptr(state),ptr(copy)));
        gray(color,f(image,over?0x140f0c:0x140ec8),call);call(0x74de0,canvas,ptr(color));
        auto *entry=image+0x2f76c0+12*index;
        std::memcpy(copy,rectangle,16);if(std::uint8_t(call(0x111f0,ptr(state),ptr(copy))))selected=index;
        call(0x75bc0,canvas);call(0x769d0,canvas,bits(rectangle[0]),bits(rectangle[1]),bits(rectangle[2]),bits(rectangle[3]),bits(5.f));
        call(0x74130,ptr(color),read<std::uint32_t>(entry),read<std::uint32_t>(entry+4),read<std::uint32_t>(entry+8));
        call(0x74ef0,canvas,ptr(color));call(0x77210,canvas);call(0x77f80,canvas);
        x=add(x,spacing);
    }
    if(selected!=8){
        const auto *entry=image+0x2f76c0+12*selected;
        write(state+0x438,read<std::uint32_t>(entry+8));write(state+0x430,read<W>(entry));
        rgbToHsl(state,image,true);
    }
    frame.finishMode=0;
}
}
