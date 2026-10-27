#include "FontRuntime.hpp"
#include <bit>
#include <cstring>
#include <immintrin.h>

namespace reconstruction::drawing {
namespace {
template<class T> T load(const void *source) {
    T value;
    std::memcpy(&value, source, sizeof value);
    return value;
}
template<class T> void store(void *destination, T value) {
    std::memcpy(destination, &value, sizeof value);
}
std::uint8_t *selectedSlot(std::uint8_t *canvas) {
    const auto index = static_cast<std::int64_t>(load<std::int32_t>(canvas + 0x2288));
    const auto address = reinterpret_cast<std::uintptr_t>(canvas) +
        static_cast<std::uint64_t>(index * 0x110);
    return reinterpret_cast<std::uint8_t *>(address);
}
float add(float a,float b) { return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b))); }
float sub(float a,float b) { return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b))); }
float mul(float a,float b) { return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b))); }
float div(float a,float b) { return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a),_mm_set_ss(b))); }
float min(float a,float b) { return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a),_mm_set_ss(b))); }
std::int32_t cvtt(float a) { return _mm_cvttss_si32(_mm_set_ss(a)); }
float negate(float a,const std::uint8_t *image) {
    return std::bit_cast<float>(std::bit_cast<std::uint32_t>(a)^load<std::uint32_t>(image+0x2B54F0));
}
std::uint8_t *pointer(const void *p) { return reinterpret_cast<std::uint8_t *>(load<std::uintptr_t>(p)); }
float fontScale(std::uint8_t *canvas,std::uint8_t *slot,const std::uint8_t *image,std::uint32_t constants) {
    const auto a=_mm_castsi128_ps(_mm_cvtsi64_si128(load<std::int64_t>(slot+0x38)));
    const auto b=_mm_castsi128_ps(_mm_cvtsi64_si128(load<std::int64_t>(slot+0x40)));
    const auto roots=_mm_sqrt_ps(_mm_add_ps(_mm_mul_ps(a,a),_mm_mul_ps(b,b)));
    float average=add(_mm_cvtss_f32(_mm_shuffle_ps(roots,roots,0x55)),_mm_cvtss_f32(roots));
    const float bias=load<float>(image+constants), quantum=load<float>(image+constants+4);
    average=add(div(mul(average,bias),quantum),bias);
    float quantized=_mm_cvtss_f32(_mm_cvtepi32_ps(_mm_cvttps_epi32(_mm_set_ss(average))));
    return mul(min(mul(quantized,quantum),load<float>(image+constants+8)),load<float>(canvas+0x22A4));
}
void configureFont(std::uint8_t *font,std::uint8_t *state,float scale,std::uint32_t id) {
    const auto index=static_cast<std::int64_t>(load<std::int32_t>(font+0x526C));
    auto *fstate=font+index*24+0x5074;
    store(fstate+8,mul(load<float>(state+0xF8),scale));
    const float spacing=load<float>(state+0xFC), blur=load<float>(state+0x104);
    const auto pair=_mm_mul_ps(_mm_setr_ps(blur,spacing,0,0),_mm_setr_ps(scale,scale,0,0));
    _mm_storel_pi(reinterpret_cast<__m64 *>(fstate+16),pair);
    store(fstate+4,load<std::uint32_t>(state+0x108));
    store(fstate,id);
}
void drawVertices(std::uint8_t *canvas,void *vertices,std::uint32_t count,const FontDependencies &d) {
    auto *state=selectedSlot(canvas)-0x88;
    alignas(16) std::uint8_t paint[76],composite[16];
    // The text path loads its final paint qword before the four main chunks.
    store(paint+64,load<std::uint64_t>(state+0x54));
    for(int offset=0;offset<64;offset+=16) std::memcpy(paint+offset,state+0x14+offset,16);
    const auto imageIndex=static_cast<std::int64_t>(load<std::int32_t>(canvas+0x22C0));
    store(paint+72,load<std::uint32_t>(canvas+0x22B0+imageIndex*4));
    const float alpha=load<float>(state+0xBC);
    store(paint+52,mul(load<float>(paint+52),alpha));
    store(paint+68,mul(alpha,load<float>(paint+68)));
    const auto user=load<std::uint64_t>(canvas),target=load<std::uint64_t>(canvas+0x60);
    const float fringe=load<float>(canvas+0x22A0);
    std::memcpy(composite,state,16);
    d.renderText(d.context,target,user,paint,composite,state+0xD8,vertices,
        std::bit_cast<std::int32_t>(count),fringe);
    store(canvas+0x22C4,load<std::uint32_t>(canvas+0x22C4)+1);
    const auto triangles=std::bit_cast<std::int32_t>(count)/3;
    store(canvas+0x22D0,load<std::uint32_t>(canvas+0x22D0)+static_cast<std::uint32_t>(triangles));
}
}

// RVA 74A60.
void setStrokeWidth_74a60(std::uint8_t *canvas, float width) {
    setGlobalAlpha_74a60(canvas,width);
}
void setGlobalAlpha_74a60(std::uint8_t *canvas,float alpha) {
    store(selectedSlot(canvas)+0x34,alpha);
}

// RVA 74EF0. Capture the color before overlapping state writes. The identity
// transform is loaded from the supplied constant image, not installed globally.
void setFillColor_74ef0(std::uint8_t *canvas, const void *rgba,
    const std::uint8_t *constantImage) {
    auto *slot = selectedSlot(canvas);
    std::uint8_t color[16];
    std::memcpy(color, rgba, sizeof color);
    std::memset(slot - 0x5C, 0, 16);
    std::memset(slot - 0x3C, 0, 16);
    std::memset(slot - 0x4C, 0, 16);
    store(slot - 0x2C, std::uint32_t(0));
    std::uint8_t transform[16];
    std::memcpy(transform, constantImage + 0x2B5290, sizeof transform);
    std::memcpy(slot - 0x74, transform, sizeof transform);
    store(slot - 0x64, std::uint64_t(0));
    store(slot - 0x50, std::uint32_t(0x3F800000));
    std::memcpy(slot - 0x4C, color, sizeof color);
    std::memcpy(slot - 0x3C, color, sizeof color);
}

// RVA 75BC0. Reset path command count and the two cached tessellation counts.
void beginPath_75bc0(std::uint8_t *canvas) {
    store(canvas + 0x7C, std::uint32_t(0));
    auto *cache = reinterpret_cast<std::uint8_t *>(load<std::uintptr_t>(canvas + 0x2290));
    store(cache + 8, std::uint32_t(0));
    store(cache + 0x18, std::uint32_t(0));
}

// RVA 79610.
void setFontSize_79610(std::uint8_t *canvas, float size) {
    store(selectedSlot(canvas) + 0x70, size);
}
// RVA 79630.
void setFontBlur_79630(std::uint8_t *canvas, float blur) {
    store(selectedSlot(canvas) + 0x7C, blur);
}
// RVA 79650.
void setLetterSpacing_79650(std::uint8_t *canvas, float spacing) {
    store(selectedSlot(canvas) + 0x74, spacing);
}
// RVA 79670.
void setLineHeight_79670(std::uint8_t *canvas, float height) {
    store(selectedSlot(canvas) + 0x78, height);
}
// RVA 79690.
void setTextAlignment_79690(std::uint8_t *canvas, std::uint32_t alignment) {
    store(selectedSlot(canvas) + 0x80, alignment);
}
// RVA 796B0.
void setFontIndex_796b0(std::uint8_t *canvas, std::uint32_t index) {
    store(selectedSlot(canvas) + 0x84, index);
}

// RVA 75C30. Command/state aliasing and post-callback count reloads are visible.
void appendCommands_75c30(std::uint8_t *canvas,float *commands,std::uint32_t count,const FontDependencies &d) {
    const auto stateIndex=static_cast<std::int64_t>(load<std::int32_t>(canvas+0x2288));
    const auto needed=load<std::uint32_t>(canvas+0x7C)+count;
    const auto capacity=load<std::uint32_t>(canvas+0x78);
    if(std::bit_cast<std::int32_t>(needed)>std::bit_cast<std::int32_t>(capacity)) {
        const auto half=std::bit_cast<std::int32_t>(capacity+(capacity>>31))>>1;
        const auto next=needed+static_cast<std::uint32_t>(half);
        const auto bytes=static_cast<std::uint64_t>(static_cast<std::int64_t>(std::bit_cast<std::int32_t>(next)))<<2;
        auto *result=d.resize(d.context,pointer(canvas+0x70),bytes);
        if(result==nullptr) return;
        store(canvas+0x70,reinterpret_cast<std::uintptr_t>(result));
        store(canvas+0x78,next);
    }
    const auto signedCount=static_cast<std::int64_t>(std::bit_cast<std::int32_t>(count));
    if(static_cast<std::uint32_t>(cvtt(load<float>(commands)))-3>=2) {
        store(canvas+0x80,load<float>(commands+signedCount-2));
        store(canvas+0x84,load<float>(commands+signedCount-1));
    }
    auto *state=reinterpret_cast<std::uint8_t *>(reinterpret_cast<std::uintptr_t>(canvas)+static_cast<std::uint64_t>(stateIndex*0x110))-0x88;
    for(std::uint32_t index=0;std::bit_cast<std::int32_t>(index)<signedCount;) {
        const auto op=static_cast<std::uint32_t>(cvtt(load<float>(commands+index)));
        auto transform=[&](std::uint32_t xy) {
            float x=load<float>(commands+xy),y=load<float>(commands+xy+1);
            float cy=mul(load<float>(state+0xC8),y),cx=mul(load<float>(state+0xC0),x);
            store(commands+xy,add(add(cx,cy),load<float>(state+0xD0)));
            y=mul(y,load<float>(state+0xCC));x=mul(x,load<float>(state+0xC4));
            store(commands+xy+1,add(add(x,y),load<float>(state+0xD4)));
        };
        if(op<=1) { transform(index+1);index+=3; }
        else if(op==2) { transform(index+1);transform(index+3);transform(index+5);index+=7; }
        else index+=(op==4?2:1);
    }
    auto address=load<std::uintptr_t>(canvas+0x70)+(static_cast<std::uint64_t>(static_cast<std::int64_t>(load<std::int32_t>(canvas+0x7C)))<<2);
    d.copy(d.context,reinterpret_cast<void *>(address),commands,static_cast<std::uint64_t>(signedCount)<<2);
    store(canvas+0x7C,load<std::uint32_t>(canvas+0x7C)+count);
}

// RVA 76A10. The scalar and packed corner arithmetic follows the capture.
void roundedRectVarying_76a10(std::uint8_t *canvas,float x,float y,float width,float height,
    float tl,float tr,float br,float bl,const std::uint8_t *image,const FontDependencies &d) {
    const float threshold=load<float>(image+0x2B54E0);
    if(threshold>tl && threshold>tr && threshold>br && threshold>bl) {
        const float yh=add(height,y),xw=add(width,x);
        float commands[]={0,x,y,1,x,yh,1,xw,yh,1,xw,y,3};
        appendCommands_75c30(canvas,commands,13,d);return;
    }
    const float nw=negate(width,image),nh=negate(height,image);
    const float half=load<float>(image+0x2B5500);
    const float hw=mul(width>=nw?width:nw,half),hh=mul(height>=nh?height:nh,half);
    const float sx=load<float>(image+(nw<=width?0x2B5504:0x2B5508));
    const float sy=load<float>(image+(nh<=height?0x2B5504:0x2B5508));
    const float rxbl=mul(min(bl,hw),sx),rybl=mul(min(bl,hh),sy);
    const float rxbr=mul(min(br,hw),sx),rybr=mul(min(br,hh),sy);
    const float rxtr=mul(min(tr,hw),sx),rytr=mul(min(tr,hh),sy);
    const float rxtl=mul(min(tl,hw),sx),rytl=mul(min(tl,hh),sy);
    const float yh=add(height,y),xw=add(width,x);
    const float coefficient=load<float>(image+0x2B5520);
    const float packed0=load<float>(image+0x2B5510),packed1=load<float>(image+0x2B5514);
    float commands[]={0,x,add(y,rytl),1,x,sub(yh,rybl),
        2,x,add(mul(negate(rybl,image),packed0),yh),add(mul(rxbl,packed1),x),yh,add(rxbl,x),yh,
        1,sub(xw,rxbr),yh,2,sub(xw,mul(rxbr,coefficient)),yh,xw,sub(yh,mul(rybr,coefficient)),xw,sub(yh,rybr),
        1,xw,add(rytr,y),2,xw,add(mul(rytr,packed0),y),add(mul(negate(rxtr,image),packed1),xw),y,sub(xw,rxtr),y,
        1,add(x,rxtl),y,2,add(mul(rxtl,coefficient),x),y,x,add(mul(rytl,coefficient),y),x,add(y,rytl),3};
    appendCommands_75c30(canvas,commands,44,d);
}

// RVA 77210. Tessellation is an explicit, independently recoverable dependency.
void fill_77210(std::uint8_t *canvas,const FontDependencies &d) {
    auto *state=selectedSlot(canvas)-0x88;
    alignas(16) std::uint8_t paint[76],composite[16];
    std::memcpy(paint+60,state+0x50,16);
    for(int off=0;off<64;off+=16) std::memcpy(paint+off,state+0x14+off,16);
    d.flattenPaths(d.context,canvas);
    float width=0;
    if(load<std::uint32_t>(canvas+8)!=0 &&load<std::uint32_t>(state+0x10)!=0) width=load<float>(canvas+0x22A0);
    d.expandFill(d.context,canvas,width);
    const float alpha=load<float>(state+0xBC);
    store(paint+52,mul(load<float>(paint+52),alpha));store(paint+68,mul(alpha,load<float>(paint+68)));
    const auto user=load<std::uint64_t>(canvas),target=load<std::uint64_t>(canvas+0x50);
    const float fringe=load<float>(canvas+0x22A0);auto *cache=pointer(canvas+0x2290);
    auto *paths=pointer(cache+0x10);const auto count=load<std::int32_t>(cache+0x18);
    std::memcpy(composite,state,16);
    d.renderFill(d.context,target,user,paint,composite,state+0xD8,fringe,cache+0x30,paths,count);
    cache=pointer(canvas+0x2290);const auto observed=load<std::int32_t>(cache+0x18);
    if(observed<=0)return;
    paths=pointer(cache+0x10);auto draw=load<std::uint32_t>(canvas+0x22C4),triangles=load<std::uint32_t>(canvas+0x22C8);
    for(std::int64_t i=0;i<observed;++i)triangles+=load<std::uint32_t>(paths+i*0x38+0x28)+load<std::uint32_t>(paths+i*0x38+0x18)-4;
    store(canvas+0x22C8,triangles);store(canvas+0x22C4,draw+static_cast<std::uint32_t>(observed)*2);
}

// RVAs 76DE0 and 76F40 construct the same cubic ellipse command sequence.
// Circle's native body inlines this arithmetic with both radii in XMM3.
void ellipse_76de0(std::uint8_t *canvas,float x,float y,float rx,float ry,
    const std::uint8_t *image,const FontDependencies &d) {
    const float nx=std::bit_cast<float>(std::bit_cast<std::uint32_t>(rx)^load<std::uint32_t>(image+0x2B5530));
    const float ny=std::bit_cast<float>(std::bit_cast<std::uint32_t>(ry)^load<std::uint32_t>(image+0x2B5530));
    const float coefficient0=load<float>(image+0x2B5540),coefficient1=load<float>(image+0x2B5544);
    const float left=sub(x,rx),right=add(x,rx),bottom=add(y,ry),top=sub(y,ry);
    const float bottomControl=add(mul(ry,coefficient0),y),leftControl=add(mul(nx,coefficient1),x);
    const float topControl=add(mul(ny,coefficient0),y),rightControl=add(mul(rx,coefficient1),x);
    float commands[]={0,left,y,2,left,bottomControl,leftControl,bottom,x,bottom,
        2,rightControl,bottom,right,bottomControl,right,y,
        2,right,topControl,rightControl,top,x,top,
        2,leftControl,top,left,topControl,left,y,3};
    appendCommands_75c30(canvas,commands,32,d);
}
void circle_76f40(std::uint8_t *canvas,float x,float y,float radius,
    const std::uint8_t *image,const FontDependencies &d) {
    const float negative=std::bit_cast<float>(std::bit_cast<std::uint32_t>(radius)^load<std::uint32_t>(image+0x2B5550));
    const float c0=load<float>(image+0x2B5560),c1=load<float>(image+0x2B5564);
    const float left=sub(x,radius),bottom=add(y,radius),right=add(x,radius),top=sub(y,radius);
    const float bc=add(mul(radius,c0),y),lc=add(mul(negative,c1),x);
    const float tc=add(mul(negative,c0),y),rc=add(mul(radius,c1),x);
    float commands[]={0,left,y,2,left,bc,lc,bottom,x,bottom,
        2,rc,bottom,right,bc,right,y,2,right,tc,rc,top,x,top,
        2,lc,top,left,tc,left,y,3};
    appendCommands_75c30(canvas,commands,32,d);
}

// RVA 75340. The hidden paint-result pointer is explicit; native canvas input
// is unused. The 76-byte paint construction preserves late color reads.
void *linearGradient_75340(void *out,float sx,float sy,float ex,float ey,
    const void *inner,const void *outer,const std::uint8_t *image) {
    auto *paint=static_cast<std::uint8_t *>(out);store(paint+72,std::uint32_t(0));
    const auto start=_mm_setr_ps(sx,sy,0,0);
    auto delta=_mm_sub_ps(_mm_setr_ps(ex,ey,0,0),start);
    const auto squared=_mm_mul_ps(delta,delta);
    const auto squareSum=_mm_add_ss(squared,_mm_shuffle_ps(squared,squared,0x55));
    const float length=_mm_cvtss_f32(_mm_sqrt_ss(squareSum));
    const bool regular=length>load<float>(image+0x2B52A0);
    const float extent=mul(load<float>(image+0x2B52E0),length);
    const float feather=_mm_cvtss_f32(_mm_max_ss(_mm_set_ss(load<float>(image+0x2B52E8)),_mm_set_ss(length)));
    delta=_mm_div_ps(delta,_mm_set1_ps(length));
    const auto flag=_mm_castsi128_ps(_mm_setr_epi32(regular?-1:0,regular?-1:0,0,0));
    delta=_mm_and_ps(delta,flag);
    const auto normal=_mm_or_ps(delta,_mm_andnot_ps(flag,_mm_loadu_ps(reinterpret_cast<const float *>(image+0x2B52B0))));
    store(paint,_mm_cvtss_f32(_mm_shuffle_ps(normal,normal,0x55)));
    store(paint+4,_mm_cvtss_f32(_mm_xor_ps(delta,_mm_loadu_ps(reinterpret_cast<const float *>(image+0x2B52C0)))));
    const auto translated=_mm_add_ps(_mm_mul_ps(_mm_loadu_ps(reinterpret_cast<const float *>(image+0x2B52D0)),normal),start);
    _mm_storeu_ps(reinterpret_cast<float *>(paint+8),_mm_movelh_ps(normal,translated));
    store(paint+24,std::uint32_t(0x47C35000));store(paint+28,add(extent,load<float>(image+0x2B52E4)));
    store(paint+32,std::uint32_t(0));store(paint+36,feather);
    std::uint8_t color[16];std::memcpy(color,inner,16);std::memcpy(paint+40,color,16);
    std::memcpy(color,outer,16);std::memcpy(paint+56,color,16);return out;
}

// RVA 77F80. Coverage correction precedes tessellation; callbacks may mutate
// the cache, which is loaded again for drawing and counter accumulation.
void stroke_77f80(std::uint8_t *canvas,const std::uint8_t *image,const FontDependencies &d) {
    auto *slot=selectedSlot(canvas),*state=slot-0x88;
    const auto a=_mm_castsi128_ps(_mm_cvtsi64_si128(load<std::int64_t>(slot+0x38)));
    const auto b=_mm_castsi128_ps(_mm_cvtsi64_si128(load<std::int64_t>(slot+0x40)));
    const auto roots=_mm_sqrt_ps(_mm_add_ps(_mm_mul_ps(a,a),_mm_mul_ps(b,b)));
    float width=mul(add(_mm_cvtss_f32(_mm_shuffle_ps(roots,roots,0x55)),_mm_cvtss_f32(roots)),load<float>(image+0x2B5600));
    width=mul(width,load<float>(slot+0x24));
    const float clamped=min(load<float>(image+0x2B5604),width);
    width=_mm_cvtss_f32(_mm_andnot_ps(_mm_cmplt_ss(_mm_set_ss(width),_mm_setzero_ps()),_mm_set_ss(clamped)));
    alignas(16) std::uint8_t paint[76],composite[16];
    std::memcpy(paint+60,slot+0x14,16);
    for(int off=0;off<64;off+=16)std::memcpy(paint+off,slot-0x28+off,16);
    float drawWidth=load<float>(canvas+0x22A0),inner=load<float>(paint+52),outer=load<float>(paint+68);
    if(drawWidth>width) {
        float ratio=div(width,drawWidth);const float maximum=min(load<float>(image+0x2B5608),ratio);
        ratio=_mm_cvtss_f32(_mm_andnot_ps(_mm_cmplt_ss(_mm_set_ss(ratio),_mm_setzero_ps()),_mm_set_ss(maximum)));
        ratio=mul(ratio,ratio);inner=mul(inner,ratio);outer=mul(ratio,outer);
    } else drawWidth=width;
    const float alpha=load<float>(state+0xBC);store(paint+52,mul(inner,alpha));store(paint+68,mul(outer,alpha));
    d.flattenPaths(d.context,canvas);
    float fringe=0;
    if(load<std::uint32_t>(canvas+8)!=0&&load<std::uint32_t>(state+0x10)!=0)fringe=load<float>(canvas+0x22A0);
    const float halfWidth=mul(load<float>(image+0x2B5600),drawWidth);
    const auto cap=load<std::uint32_t>(state+0xB8),join=load<std::uint32_t>(state+0xB4);const float miter=load<float>(state+0xB0);
    d.expandStroke(d.context,canvas,halfWidth,fringe,cap,join,miter);
    const auto user=load<std::uint64_t>(canvas),target=load<std::uint64_t>(canvas+0x58);const float backendFringe=load<float>(canvas+0x22A0);
    auto *cache=pointer(canvas+0x2290),*paths=pointer(cache+0x10);const auto count=load<std::int32_t>(cache+0x18);
    std::memcpy(composite,state,16);
    d.renderStroke(d.context,target,user,paint,composite,state+0xD8,backendFringe,drawWidth,paths,count);
    cache=pointer(canvas+0x2290);const auto observed=load<std::int32_t>(cache+0x18);if(observed<=0)return;
    paths=pointer(cache+0x10);const auto draw=load<std::uint32_t>(canvas+0x22C4);auto triangles=load<std::uint32_t>(canvas+0x22CC);
    for(std::int64_t index=0;index<observed;++index)triangles+=load<std::uint32_t>(paths+index*0x38+0x28)-2;
    store(canvas+0x22CC,triangles);store(canvas+0x22C4,draw+static_cast<std::uint32_t>(observed));
}

// RVA 7AE90. The FontStash parameter writes are local native operations.
float textBounds_7ae90(std::uint8_t *canvas,float x,float y,const char *text,const char *end,float *bounds,
    const std::uint8_t *image,const FontDependencies &d) {
    auto *slot=selectedSlot(canvas);const auto fontID=load<std::uint32_t>(slot+0x84);
    if(fontID==0xFFFFFFFF)return 0;
    const float scale=fontScale(canvas,slot,image,0x2B5710);
    const float inverse=div(load<float>(image+0x2B571C),scale);
    auto *font=pointer(canvas+0x22A8);configureFont(font,slot-0x88,scale,fontID);
    const float scaledX=mul(x,scale),scaledY=mul(y,scale);
    const float width=d.fontBounds(d.context,font,scaledX,scaledY,text,end,bounds);
    if(bounds!=nullptr) {
        d.fontLineBounds(d.context,pointer(canvas+0x22A8),scaledY,bounds+1,bounds+3);
        _mm_storeu_ps(bounds,_mm_mul_ps(_mm_set1_ps(inverse),_mm_loadu_ps(bounds)));
    }
    return mul(inverse,width);
}

// RVA 79770. The 80-byte iterator and 32-byte glyph quad belong to FontStash.
float text_79770(std::uint8_t *canvas,float x,float y,const char *text,const char *end,
    const std::uint8_t *image,const FontDependencies &d) {
    auto *slot=selectedSlot(canvas),*state=slot-0x88;
    float initialTransform[4];std::memcpy(initialTransform,slot+0x38,16);
    const float scale=fontScale(canvas,slot,image,0x2B5688);
    if(end==nullptr)end=reinterpret_cast<const char *>(reinterpret_cast<std::uintptr_t>(text)+d.length(d.context,text));
    const auto fontID=load<std::uint32_t>(state+0x10C);if(fontID==0xFFFFFFFF)return x;
    auto *font=pointer(canvas+0x22A8);configureFont(font,state,scale,fontID);
    const auto length=static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(end))-static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(text));
    const auto capacity=(std::bit_cast<std::int32_t>(length)>=3?length:2)*6;
    auto *cache=pointer(canvas+0x2290);std::uint8_t *vertices;
    if(std::bit_cast<std::int32_t>(capacity)>load<std::int32_t>(cache+0x2C)) {
        const auto next=(capacity+0xFF)&0x7FFFFF00;
        vertices=static_cast<std::uint8_t *>(d.resize(d.context,pointer(cache+0x20),static_cast<std::uint64_t>(next)<<4));
        if(vertices==nullptr)return x;
        cache=pointer(canvas+0x2290);store(cache+0x20,reinterpret_cast<std::uintptr_t>(vertices));store(cache+0x2C,next);
        font=pointer(canvas+0x22A8);
    } else { vertices=pointer(cache+0x20);if(vertices==nullptr)return x; }
    alignas(16) std::uint8_t iterator[80],previous[80];float quad[8];
    d.fontIteratorInit(d.context,font,iterator,mul(x,scale),mul(y,scale),text,end,2);
    std::memcpy(previous,iterator,80);
    auto exists=d.fontIteratorNext(d.context,pointer(canvas+0x22A8),iterator,quad);
    std::uint32_t count=0;
    const float determinant=sub(mul(initialTransform[3],initialTransform[0]),mul(initialTransform[1],initialTransform[2]));
    const float inverse=div(load<float>(image+0x2B5694),scale);
    while(exists!=0) {
        if(load<std::int32_t>(iterator+0x28)==-1) {
            if(count!=0)drawVertices(canvas,vertices,count,d);
            if(d.allocateTextAtlas(d.context,canvas)==0){count=0;break;}
            std::memcpy(iterator,previous,80);
            d.fontIteratorNext(d.context,pointer(canvas+0x22A8),iterator,quad);
            count=0;if(load<std::int32_t>(iterator+0x28)==-1)break;
        }
        std::memcpy(previous,iterator,80);
        if(0>determinant) {const float y0=quad[1],t0=quad[3];quad[1]=quad[5];quad[5]=y0;quad[3]=quad[7];quad[7]=t0;}
        const auto next=count+6;
        if(std::bit_cast<std::int32_t>(next)<=std::bit_cast<std::int32_t>(capacity)) {
            const float x0=mul(quad[0],inverse),y0=mul(quad[1],inverse),x1=mul(quad[4],inverse),y1=mul(quad[5],inverse);
            const auto a=_mm_castsi128_ps(_mm_cvtsi64_si128(load<std::int64_t>(state+0xC0)));
            const auto b=_mm_castsi128_ps(_mm_cvtsi64_si128(load<std::int64_t>(state+0xC8)));
            const auto t=_mm_castsi128_ps(_mm_cvtsi64_si128(load<std::int64_t>(state+0xD0)));
            const auto xa=_mm_mul_ps(_mm_set1_ps(x0),a),xb=_mm_mul_ps(_mm_set1_ps(x1),a);
            const auto ya=_mm_mul_ps(_mm_set1_ps(y0),b),yb=_mm_mul_ps(_mm_set1_ps(y1),b);
            const auto c0=_mm_add_ps(_mm_add_ps(xa,ya),t),c2=_mm_add_ps(_mm_add_ps(xb,yb),t);
            const auto c1=_mm_add_ps(_mm_add_ps(xb,ya),t),c3=_mm_add_ps(_mm_add_ps(yb,xa),t);
            auto *out=vertices+(static_cast<std::uint64_t>(static_cast<std::int64_t>(std::bit_cast<std::int32_t>(count)))<<4);
            _mm_storel_pi(reinterpret_cast<__m64 *>(out),c0);
            const auto uv0=_mm_castsi128_ps(_mm_cvtsi64_si128(load<std::int64_t>(quad+2)));
            const auto uv1=_mm_castsi128_ps(_mm_cvtsi64_si128(load<std::int64_t>(quad+6)));
            _mm_storeu_ps(reinterpret_cast<float *>(out+8),_mm_movelh_ps(uv0,c2));
            _mm_storeu_ps(reinterpret_cast<float *>(out+24),_mm_movelh_ps(uv1,c1));
            store(out+40,quad[6]);store(out+44,quad[3]);
            _mm_storeu_ps(reinterpret_cast<float *>(out+48),_mm_movelh_ps(c0,uv0));
            _mm_storel_pi(reinterpret_cast<__m64 *>(out+64),c3);store(out+72,quad[2]);store(out+76,quad[7]);
            _mm_storeu_ps(reinterpret_cast<float *>(out+80),_mm_movelh_ps(c2,uv1));count=next;
        }
        exists=d.fontIteratorNext(d.context,pointer(canvas+0x22A8),iterator,quad);
    }
    font=pointer(canvas+0x22A8);const auto dirtyX=load<std::uint32_t>(font+0x50),dirtyY=load<std::uint32_t>(font+0x54);
    const auto width=load<std::uint32_t>(font+0x58)-dirtyX,height=load<std::uint32_t>(font+0x5C)-dirtyY;
    if(std::bit_cast<std::int32_t>(width)>0&&std::bit_cast<std::int32_t>(height)>0) {
        store(font+0x50,load<std::uint64_t>(font));store(font+0x58,std::uint64_t(0));
        const auto index=static_cast<std::int64_t>(load<std::int32_t>(canvas+0x22C0));
        const auto texture=load<std::int32_t>(canvas+0x22B0+index*4);
        if(texture!=0)d.updateTexture(d.context,load<std::uint64_t>(canvas+0x28),load<std::uint64_t>(canvas),texture,
            std::bit_cast<std::int32_t>(dirtyX),std::bit_cast<std::int32_t>(dirtyY),std::bit_cast<std::int32_t>(width),std::bit_cast<std::int32_t>(height),pointer(font+0x48));
    }
    drawVertices(canvas,vertices,count,d);
    return div(load<float>(iterator+8),scale);
}
}
