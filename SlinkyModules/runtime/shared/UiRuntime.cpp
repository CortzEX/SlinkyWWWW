#include "UiRuntime.hpp"
#include "Rounding.hpp"
#include <bit>
#include <cstring>
#include <immintrin.h>

namespace reconstruction::ui {
namespace {
template<class T> T load(const void *p) {T v;std::memcpy(&v,p,sizeof v);return v;}
template<class T> void store(void *p,T v) {std::memcpy(p,&v,sizeof v);}
std::uint8_t *pointer(const void *p) {return reinterpret_cast<std::uint8_t *>(load<std::uintptr_t>(p));}
float add(float a,float b) {return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float sub(float a,float b) {return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float mul(float a,float b) {return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float div(float a,float b) {return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float unsignedFloat(std::uint64_t value) {
    if((value>>63)==0)return _mm_cvtss_f32(_mm_cvtsi64_ss(_mm_setzero_ps(),static_cast<std::int64_t>(value)));
    const auto half=(value>>1)|(value&1);
    const auto converted=_mm_cvtsi64_ss(_mm_setzero_ps(),static_cast<std::int64_t>(half));
    return _mm_cvtss_f32(_mm_add_ss(converted,converted));
}
float halfAndOffset(float dimension,float coordinate,const std::uint8_t *image) {
    const auto product=_mm_mul_sd(_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(dimension)),_mm_set_sd(load<double>(image+0x140838)));
    const auto sum=_mm_add_sd(product,_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(coordinate)));
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),sum));
}
}

// RVA 10340. Snapshot canvas before reading the selected font index.
void selectFont_10340(std::uint8_t *ui,std::uint32_t style) {
    auto *canvas=pointer(ui);
    drawing::setFontIndex_796b0(canvas,load<std::uint32_t>(ui+0x40+static_cast<std::uint64_t>(style)*4));
}

// RVA 10860. Four-slot column rectangles; division intentionally retains the
// native nonzero-column-count precondition, rather than installing a default.
float *nextColumnRect_10860(float *out,std::uint8_t *ui,float height,const std::uint8_t *image) {
    const auto index=load<std::uint64_t>(ui+0x258);
    auto *slot=reinterpret_cast<std::uint8_t *>(reinterpret_cast<std::uintptr_t>(ui)+index*0x78);
    const auto columns=load<std::uint64_t>(slot-0x50),current=load<std::uint64_t>(slot-8);
    store(slot-8,current+1);
    auto *previous=slot-0x48+((static_cast<std::uint32_t>(current)-static_cast<std::uint32_t>(columns))&3)*16;
    auto *rect=slot-0x48+(static_cast<std::uint32_t>(current)&3)*16;
    auto *layout=slot-0x78;
    std::uint64_t remainder;
    if(((current|columns)>>32)==0)remainder=static_cast<std::uint32_t>(current)%static_cast<std::uint32_t>(columns);
    else remainder=current%columns;
    if(remainder!=0) {
        auto *left=slot-0x48+((static_cast<std::uint32_t>(current)-1)&3)*16;
        const float width=load<float>(left+8),x=load<float>(left);
        store(rect,add(add(x,width),load<float>(layout+0x10)));store(rect+8,width);
        float y=load<float>(layout+0x20);
        if(current>=columns)y=add(load<float>(layout+0x10),add(load<float>(previous+4),load<float>(previous+12)));
        store(rect+4,y);
    } else {
        store(rect,load<float>(layout+0x1C));
        float width;
        if(current<columns) {
            store(rect+4,load<float>(layout+0x20));
            width=load<float>(layout+8);
            width=sub(width,mul(unsignedFloat(columns-1),load<float>(layout+0x10)));
            width=div(width,unsignedFloat(columns));
        } else {
            store(rect+4,add(add(load<float>(previous+4),load<float>(previous+12)),load<float>(layout+0x10)));
            width=load<float>(previous+8);
        }
        store(rect+8,width);
    }
    store(rect+12,height);
    std::uint8_t captured[16];std::memcpy(captured,rect,16);
    float values[4];std::memcpy(values,captured,16);
    const float x=values[0],y=values[1];
    const float rx=recovered_round_float_b1fb0(x,image),ry=recovered_round_float_b1fb0(y,image);
    const float rw=recovered_round_float_b1fb0(values[2],image),rh=recovered_round_float_b1fb0(values[3],image);
    store(out,rx);store(out+1,ry);store(out+2,rw);store(out+3,rh);return out;
}

// RVA 10A60, with the 769D0 equal-radius forwarding call made explicit.
void fillRoundedRect_10a60(std::uint8_t *ui,const float *rect,float radius,
    const std::uint8_t *image,const drawing::FontDependencies &d) {
    float captured[4];std::memcpy(captured,rect,16);auto *canvas=pointer(ui);
    drawing::beginPath_75bc0(canvas);
    drawing::roundedRectVarying_76a10(canvas,captured[0],captured[1],captured[2],captured[3],radius,radius,radius,radius,image,d);
    drawing::fill_77210(canvas,d);
}
// RVA 10B00.
void strokeRoundedRect_10b00(std::uint8_t *ui,const float *rect,float radius,
    const std::uint8_t *image,const drawing::FontDependencies &d) {
    float captured[4];std::memcpy(captured,rect,16);auto *canvas=pointer(ui);
    drawing::beginPath_75bc0(canvas);
    drawing::roundedRectVarying_76a10(canvas,captured[0],captured[1],captured[2],captured[3],radius,radius,radius,radius,image,d);
    drawing::stroke_77f80(canvas,image,d);
}

// RVA 10CB0. Native centering uses binary64 multiply/add then narrows once.
float drawAlignedText_10cb0(std::uint8_t *ui,const float *rect,std::uint32_t alignment,
    std::uint32_t style,const char *text,const std::uint8_t *image,const drawing::FontDependencies &d) {
    float captured[4];std::memcpy(captured,rect,16);
    selectFont_10340(ui,style);auto *canvas=pointer(ui);
    drawing::setTextAlignment_79690(canvas,load<std::uint32_t>(image+0x14085C+static_cast<std::uint64_t>(alignment)*4));
    float x=captured[0];
    if(alignment==2)x=add(x,captured[2]);
    else if(alignment!=0)x=halfAndOffset(captured[2],x,image);
    float y=add(captured[1],load<float>(image+0x140840));
    y=halfAndOffset(captured[3],y,image);
    return drawing::text_79770(canvas,x,y,text,nullptr,image,d);
}

// RVA 169C0. Callback reads and subsequent state reads remain separate.
void finishModal_169c0(std::uint8_t *state,std::uint8_t apply,std::uint8_t *image,const UiDependencies &d) {
    store(state+0x370,std::uint32_t(0));const auto mode=load<std::uint32_t>(state+0x3F8);
    if(mode==1) {
        if(apply!=0)d.invoke(d.context,load<std::uint64_t>(state+0x428),load<std::uint64_t>(state+0x400),0,0);
    } else if(mode==2) {
        if(apply!=0) {
            const auto user=load<std::uint64_t>(state+0x400),target=load<std::uint64_t>(state+0x428);
            std::uint8_t color[12];store(color+8,load<std::uint32_t>(state+0x438));store(color,load<std::uint64_t>(state+0x430));
            d.invoke(d.context,target,user,reinterpret_cast<std::uintptr_t>(color),0);
        }
        float color[3];std::memcpy(color,state+0x430,12);
        const auto index=load<std::uint64_t>(image+0x2F76B0);auto *history=image+0x2F76C0;
        bool found=false;
        for(std::uint64_t back=8;back!=0;--back) {
            const auto candidate=(index>=back?index-back:index+8-back);
            auto *record=reinterpret_cast<std::uint8_t *>(reinterpret_cast<std::uintptr_t>(history)+candidate*12);
            if(color[0]==load<float>(record)&&color[1]==load<float>(record+4)&&color[2]==load<float>(record+8)){found=true;break;}
        }
        if(!found) {
            const auto next=index>=1?index-1:7;
            store(image+0x2F76B0,next);auto *record=history+next*12;
            store(record,load<std::uint64_t>(color));store(record+8,load<std::uint32_t>(color+2));
        }
    } else if(mode==4) {
        if(apply!=0)d.invoke(d.context,load<std::uint64_t>(state+0x430),load<std::uint64_t>(state+0x400),0,0);
        auto *buffer=pointer(state+0x450);
        if(buffer!=nullptr) {
            std::memset(buffer,0,16);d.release(d.context,pointer(buffer+0x10));store(buffer+0x10,std::uint64_t(0));
            d.release(d.context,pointer(state+0x450));store(state+0x450,std::uint64_t(0));
        }
    }
    if(mode!=0)store(state+0x3F8,std::uint32_t(0));
}
// RVA 165F0.
void resetModal_165f0(std::uint8_t *state,std::uint8_t *image,const UiDependencies &d) {
    finishModal_169c0(state,1,image,d);
}

// RVA 10F30. Public return is the observed AL contract; native upper EAX bits
// follow a saved-register value and are not a canonical boolean representation.
std::uint8_t processInput_10f30(std::uint8_t *state,const std::uint8_t *event,std::uint8_t *image,const UiDependencies &d) {
    const auto kind=load<std::uint32_t>(event);
    if(kind==1) {
        store(state+0x4B0,_mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),load<std::int32_t>(event+4))));
        store(state+0x4B4,_mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),load<std::int32_t>(event+8))));return 0;
    }
    if(kind==3) {
        if(load<std::uint32_t>(state+0x3F8)!=0)return 0;
        store(state+0x4BC,add(mul(load<float>(event+4),load<float>(image+0x140870)),load<float>(state+0x4BC)));return 0;
    }
    if(kind!=2)return 0;
    if(load<std::uint8_t>(event+12)==1) {
        const auto mode=load<std::uint32_t>(state+0x370);
        if(mode-2<2) {
            const auto key=load<std::uint32_t>(event+4);
            if(key==1&&mode!=3) {store(state+0x370,std::uint32_t(0));return 1;}
            if(key==0x53) {
                auto *text=reinterpret_cast<char *>(state+0x378);const auto length=d.length(d.context,text);
                if(length!=0)store(text+length-1,std::uint8_t(0));return 1;
            }
            if(key==0x55) {if(load<std::uint8_t>(state+0x378)!=0)store(state+0x3F0,std::uint8_t(1));return 1;}
            if(key==0x57) {store(state+0x370,std::uint32_t(0));return 1;}
            if(key!=1) {
                for(unsigned offset=8;offset<12;++offset) {
                    const auto byte=load<std::uint8_t>(event+offset);if(byte==0)break;
                    const auto user=load<std::uint64_t>(state+0x3E8);
                    d.invoke(d.context,load<std::uint64_t>(state+0x3E0),reinterpret_cast<std::uintptr_t>(state+0x378),byte,user);
                }
                return 1;
            }
        } else if(mode==1) {
            const auto key=load<std::uint32_t>(event+4),candidate=(key==1||key==0x57)?0:key;
            const auto target=load<std::uint64_t>(state+0x378),user=load<std::uint64_t>(state+0x380);
            d.invoke(d.context,target,user,candidate,0);store(state+0x370,std::uint32_t(0));return 1;
        } else if(mode==0&&load<std::uint32_t>(state+0x3F8)!=0&&load<std::uint32_t>(event+4)==0x57) {
            resetModal_165f0(state,image,d);return 1;
        }
    }
    const auto key=load<std::uint32_t>(event+4);
    if(key-100<2)store(state+0x4CA,load<std::uint8_t>(event+12));
    else if(key==1)store(state+0x4C8,load<std::uint8_t>(event+12));
    return 0;
}

// Preserve MOV SIL,1 / MOV EAX,ESI exactly when a caller needs more than AL.
// Text-mode branches retain incoming RSI, whereas key-binding and modal-reset
// branches replace RSI with state before changing its low byte.
std::uint64_t processInputWord_10f30(std::uint8_t *state,const std::uint8_t *event,
    std::uint8_t *image,std::uint64_t incomingRsi,const UiDependencies &d) {
    auto saved=incomingRsi;
    if(load<std::uint32_t>(event)==2&&load<std::uint8_t>(event+12)==1) {
        const auto mode=load<std::uint32_t>(state+0x370);
        if(mode<=1)saved=reinterpret_cast<std::uintptr_t>(state);
    }
    const auto accepted=processInput_10f30(state,event,image,d);
    if(accepted==0)return 0;
    return (static_cast<std::uint32_t>(saved)&0xFFFFFF00U)|1U;
}
}
