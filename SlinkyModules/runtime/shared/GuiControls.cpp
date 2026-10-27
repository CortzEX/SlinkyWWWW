#include "GuiControls.hpp"
#include "GuiMemory.hpp"
#include "ByteStrings.hpp"
#include "DisplayGeometry.hpp"
#include "Trigonometry.hpp"
#include <cstring>
#include <initializer_list>
namespace reconstruction::drawing { void stroke_77f80(std::uint8_t*,const std::uint8_t*,const FontDependencies&); }
namespace reconstruction::gui {
static std::uint8_t *top(std::uint8_t *state) { return state+(read<std::uint64_t>(state,0x258)-1)*0x78; }
void resetLayout_10360(std::uint8_t *state) { write(state,0x258,std::uint64_t(0));write(state,0x260,std::uint32_t(0)); }
void pushLayout_10380(std::uint8_t *state,float *r,float spacing,float inset) {
    const auto n=read<std::uint64_t>(state,0x258);
    if(n) {
        const auto *parent=state+(n-1)*0x78;
        const auto px=read<float>(parent),py=read<float>(parent,4),pw=read<float>(parent,8),ph=read<float>(parent,12);
        auto x=r[0],y=r[1];
        if(px>x) r[0]=x=px;
        if(py>y) r[1]=y=py;
        const auto right=add(px,pw),bottom=add(py,ph);
        if(add(r[2],x)>right) { r[2]=sub(right,x);if(0>r[2])r[2]=0; }
        if(add(r[3],y)>bottom) { r[3]=sub(bottom,y);if(0>r[3])r[3]=0; }
    }
    auto *block=state+n*0x78;write(state,0x258,n+1);
    float old[4],inner[4];std::memcpy(old,r,16);insetRect_a130(inner,old,inset);std::memcpy(r,inner,16);
    const auto zero=_mm_setzero_ps();
    for(int offset=0x60;offset>=0;offset-=0x10) _mm_storeu_ps(reinterpret_cast<float*>(block+offset),zero);
    write(block,0x70,std::uint64_t(0));std::memcpy(block,r,16);write(block,0x10,spacing);write(block,0x14,inset);
    float copy[4];std::memcpy(copy,r,16);write(block,0x1c,rectPosition_a1e0(copy));
}
void pushScissor_104f0(std::uint8_t *ui,std::uint8_t *state,float *r,float spacing,float inset,const std::uint8_t *image) {
    auto *savedCanvas=canvas(ui);float copy[4];std::memcpy(copy,r,16);pushLayout_10380(state,copy,spacing,inset);
    write(top(state),0x18,std::uint8_t(1));float rounded[4];std::memcpy(copy,r,16);roundRect_a160(rounded,copy,image);std::memcpy(r,rounded,16);
    saveCanvas_73a70(savedCanvas);
    const auto negated=std::bit_cast<float>(read<std::uint32_t>(image,0x140810)^std::bit_cast<std::uint32_t>(spacing));
    const auto doubleNegative=sub(negated,spacing);
    scissorCanvas_75630(savedCanvas,add(r[0],spacing),add(r[1],spacing),add(r[2],doubleNegative),add(doubleNegative,r[3]),image);
}
// Native row flushing samples the last cached column once, then compares that
// same endpoint repeatedly. It does not scan all cached column rectangles.
static void flushRow(std::uint8_t *block,float initial) {
    const auto count=read<std::uint64_t>(block,0x70);if(!count)return;
    const auto last=count-1,columns=read<std::uint64_t>(block,0x28);
    const auto remainder=((last|columns)>>32)?last%columns:std::uint32_t(last)%std::uint32_t(columns);
    const auto first=last-remainder;
    const auto offset=(last&3)*16;
    const auto bottom=add(read<float>(block,0x34+offset),read<float>(block,0x3c+offset));
    auto result=initial;
    for(auto i=first;;++i) { result=maximum(bottom,result);if(i==last)break; }
    if(result!=initial) write(block,0x20,add(result,read<float>(block,0x10)));
}
float endLayout_105b0(std::uint8_t *ui,std::uint8_t *state,const std::uint8_t *image) {
    auto *block=top(state);flushRow(block,read<float>(image,0x140820));
    if(read<std::uint8_t>(block,0x18)==1)restoreCanvas_749a0(canvas(ui));
    const auto bottom=read<float>(block,0x20);
    if(bottom>float(read<std::int32_t>(state,0x260)))write(state,0x260,truncateInt(bottom));
    write(state,0x258,read<std::uint64_t>(state,0x258)-1);
    const auto height=sub(bottom,read<float>(block,4)),spacing=read<float>(block,0x10);
    return add(add(spacing,spacing),height);
}
static void assignColumns(std::uint8_t *block,std::int32_t requested) {
    const auto bounded=requested<4?requested:4;
    write(block,0x28,std::uint64_t(std::int64_t(requested?bounded:1)));write(block,0x70,std::uint64_t(0));
}
void setColumns_106b0(std::uint8_t *state,std::int32_t requested,const std::uint8_t *image) { auto *block=top(state);flushRow(block,read<float>(image,0x140824));assignColumns(block,requested); }
void autoColumns_10780(std::uint8_t *state,float width,const std::uint8_t *image) {
    auto *block=top(state);const auto parentWidth=read<float>(block,8),spacing=read<float>(block,0x10);
    flushRow(block,read<float>(image,0x140828));assignColumns(block,truncateInt(div(add(parentWidth,spacing),add(width,spacing))));
}
void fillRectangle_10a10(std::uint8_t *ui,const float *r,const drawing::FontDependencies &fonts) {
    auto *c=canvas(ui);drawing::beginPath_75bc0(c);rectPath_76950(c,r[0],r[1],r[2],r[3],fonts);drawing::fill_77210(c,fonts);
}
void drawIcon_10ba0(std::uint8_t *ui,const float *r,std::uint32_t icon,float alpha,const ControlDependencies &deps) {
    auto *c=canvas(ui);const auto unit=read<float>(deps.image,0x140830);
    const auto sx=div(r[2],unit),sy=div(r[3],unit);
    const auto x=sub(r[0],mul(deps.iconOrigins[icon*2],sx));
    const auto y=sub(r[1],mul(deps.iconOrigins[icon*2+1],sy));
    const auto width=mul(sx,read<float>(ui,0x4c)),height=mul(sy,read<float>(ui,0x50));
    alignas(16) std::uint8_t paint[80];imagePaint_75520(paint,c,x,y,width,height,0,read<std::int32_t>(ui,0x48),alpha,deps.image);
    drawing::beginPath_75bc0(c);rectPath_76950(c,r[0],r[1],r[2],r[3],deps.fonts);
    alignas(16) std::uint8_t copy[80];std::memcpy(copy,paint,76);fillPaint_74f60(c,copy);drawing::fill_77210(c,deps.fonts);
}
float measuredText_10da0(std::uint8_t *ui,float *r,std::uint32_t align,std::uint32_t style,const char *text,const char *end,const ControlDependencies &deps) {
    ui::selectFont_10340(ui,style);auto *c=canvas(ui);
    drawing::setTextAlignment_79690(c,read<std::uint32_t>(deps.image,0x14085c+align*4));
    const auto baseline=add(r[1],read<float>(deps.image,0x140848));r[1]=baseline;
    auto x=r[0];if(align==2)x=add(x,r[2]);else if(align)x=fromDouble(double(x)+double(r[2])*read<double>(deps.image,0x140850));
    const auto y=fromDouble(double(baseline)+double(r[3])*read<double>(deps.image,0x140850));
    return drawing::text_79770(c,x,y,text,end,deps.image,deps.fonts);
}
void drawCaret_10e70(std::uint8_t *ui,const float *r,const float *rgba,float frequency,float width,const ControlDependencies &deps) {
    auto *c=canvas(ui);const auto phase=fromDouble(double(frequency)*read<double>(ui,8));
    const auto sine=recovered_sine_b1cf0(phase,deps.image),half=read<float>(deps.image,0x140858);
    const auto alpha=add(half,mul(sine,half));drawing::beginPath_75bc0(c);
    float color[4],copy[4];std::memcpy(copy,rgba,16);recovered_color_741b0(color,copy,alpha);
    strokeColor_74de0(c,color,deps.image);lineWidth_749e0(c,width);
    moveTo_75bf0(c,r[0],r[1],deps.fonts);lineTo_75ec0(c,r[0],add(r[1],r[3]),deps.fonts);
    drawing::stroke_77f80(c,deps.image,deps.fonts);
}
std::uint8_t modalVisible_16c80(std::uint8_t *s) { return read<std::uint32_t>(s,0x3f8)!=0; }
std::uint8_t modalAllows_16c90(std::uint8_t *s) { return read<std::uint8_t>(s,0x420); }
std::uint8_t hovered_11180(std::uint8_t *s,const float *r) {
    if(modalVisible_16c80(s)&&!modalAllows_16c90(s))return 0;
    float copy[4];std::memcpy(copy,r,16);if(!containsPoint_a0a0(copy,read<std::uint64_t>(s,0x4a8)))return 0;
    const auto mode=read<std::uint32_t>(s,0x370);return mode==0||mode==3;
}
std::uint8_t clicked_111f0(std::uint8_t *s,const float *r) {
    float copy[4];std::memcpy(copy,r,16);if(modalVisible_16c80(s)&&!modalAllows_16c90(s))return 0;
    if(!containsPoint_a0a0(copy,read<std::uint64_t>(s,0x4a8)))return 0;
    const auto mode=read<std::uint32_t>(s,0x370);if(mode!=0&&mode!=3)return 0;
    if(read<std::uint8_t>(s,0x4c8)!=1||read<std::uint8_t>(s,0x4c9)!=0)return 0;
    write(s,0x4c9,std::uint8_t(1));return 1;
}
void consumeClick_11270(std::uint8_t *s) { if(read<std::uint8_t>(s,0x4c8)==1&&read<std::uint8_t>(s,0x4c9)==0)write(s,0x4c9,std::uint8_t(1)); }
void activate_11290(std::uint8_t *s,std::uint64_t first,std::uint64_t id) { write(s,0x370,std::uint32_t(1));write(s,0x378,first);write(s,0x380,id); }
std::uint8_t active_112b0(std::uint8_t *s,std::uint64_t id) { return read<std::uint32_t>(s,0x370)==1&&read<std::uint64_t>(s,0x380)==id; }
void activateText_112d0(std::uint8_t *s,std::uint64_t callback,std::uint64_t id) {
    if((read<std::uint32_t>(s,0x370)&~1u)==2&&read<std::uint64_t>(s,0x3e8)==id)return;
    write(s,0x370,std::uint32_t(2));const auto zero=_mm_setzero_ps();
    for(auto offset:{0x3d8,0x3e8,0x378,0x388,0x398,0x3a8,0x3b8,0x3c8})_mm_storeu_ps(reinterpret_cast<float*>(s+offset),zero);
    write(s,0x3e0,callback);write(s,0x3e8,id);
}
std::uint8_t textActive_11340(std::uint8_t *s,std::uint64_t id) { return (read<std::uint32_t>(s,0x370)&~1u)==2&&read<std::uint64_t>(s,0x3e8)==id; }
void finishText_11370(std::uint8_t *s) { if(read<std::uint32_t>(s,0x370)==2)write(s,0x370,std::uint32_t(3)); }
char *consumeSubmitted_11390(std::uint8_t *s) {
    if((read<std::uint32_t>(s,0x370)&~1u)!=2||read<std::uint8_t>(s,0x3f0)!=1)return nullptr;
    auto *out=reinterpret_cast<char*>(s+0x378);write(s,0x370,std::uint32_t(0));write(s,0x3f0,std::uint8_t(0));return out;
}
char *textBuffer_113d0(std::uint8_t *s) { return (read<std::uint32_t>(s,0x370)&~1u)==2?reinterpret_cast<char*>(s+0x378):nullptr; }
void requestClose_117f0(std::uint8_t *s) { write(s,0x4cb,std::uint8_t(1)); }
void tabs_113f0(std::uint8_t *s,std::uint8_t *u,float elapsed,const ControlDependencies &d) {
    auto *savedCanvas=canvas(u);float row[4];ui::nextColumnRect_10860(row,s,read<float>(d.image,0x140880),d.image);
    float color[4];auto gray=read<float>(d.image,0x140884);recovered_color_74150(color,gray,gray,gray,1);drawing::setFillColor_74ef0(savedCanvas,color,d.image);
    float copy[4];std::memcpy(copy,row,16);ui::fillRoundedRect_10a60(u,copy,read<float>(d.image,0x140888),d.image,d.fonts);
    auto x=row[0];const auto y=row[1],w=div(row[2],read<float>(d.image,0x14088c)),h=row[3];
    const auto amount=fromDouble(double(elapsed)/read<double>(d.image,0x140890));
    const auto animated=interpolate_a260(read<float>(s,0x358),unsignedFloat(read<std::uint64_t>(s,0x350)),amount,d.image);write(s,0x358,animated);x=add(x,mul(animated,w));
    float highlight[4];recovered_rect_a070(copy,x,y,w,h);insetRect_a130(highlight,copy,read<float>(d.image,0x140898));
    auto *currentCanvas=canvas(u);gray=read<float>(d.image,0x14089c);recovered_color_74150(color,gray,gray,gray,1);drawing::setFillColor_74ef0(currentCanvas,color,d.image);
    std::memcpy(copy,highlight,16);ui::fillRoundedRect_10a60(u,copy,read<float>(d.image,0x1408a0),d.image,d.fonts);drawing::setFontSize_79610(savedCanvas,read<float>(d.image,0x1408a4));
    const auto divisor=read<float>(d.image,0x14088c),inset=read<float>(d.image,0x140898);
    const auto neutral=read<float>(d.image,0x1408a8),closeR=read<float>(d.image,0x1408b4),closeGB=read<float>(d.image,0x1408b8),selectedGray=read<float>(d.image,0x1408ac),closeGBIdle=read<float>(d.image,0x1408b0);
    for(std::uint64_t i=0;i!=7;++i) {
        const auto *descriptor=s+0x2e0+i*16;
        float segment[4];recovered_rect_a070(segment,add(mul(float(std::int64_t(i)),div(row[2],divisor)),row[0]),row[1],div(row[2],divisor),row[3]);
        std::memcpy(copy,segment,16);
        if(clicked_111f0(s,copy)) {
            if(read<std::uint32_t>(descriptor)==6)d.openDialog_16820(d.context,s,std::uintptr_t(s),d.closeCallback,reinterpret_cast<const char*>(d.image+0x140a6c));
            else { write(s,0x350,i);write(s,0x370,std::uint32_t(0)); }
        }
        float inner[4];std::memcpy(copy,segment,16);insetRect_a130(inner,copy,inset);
        std::memcpy(copy,inner,16);const auto over=hovered_11180(s,copy);
        if(read<std::uint32_t>(descriptor)==6)recovered_color_74150(color,over?closeR:neutral,over?closeGB:closeGBIdle,over?closeGB:closeGBIdle,1);
        else { gray=over?selectedGray:neutral;recovered_color_74150(color,gray,gray,gray,1); }
        drawing::setFillColor_74ef0(canvas(u),color,d.image);
        const auto *label=reinterpret_cast<const char*>(std::uintptr_t(read<std::uint64_t>(descriptor,8)));
        std::memcpy(copy,inner,16);ui::drawAlignedText_10cb0(u,copy,1,0,label,d.image,d.fonts);
    }
}
void tooltip_14cb0(std::uint8_t *s,std::uint8_t*,const char *text,std::int32_t x,std::int32_t y,const ControlDependencies &d) {
    write(s,0x268,std::uint8_t(1));d.copyTooltip_13d0b0(d.context,reinterpret_cast<char*>(s+0x26a),text,100);
    const auto pair=_mm_cvtepi32_ps(_mm_set_epi32(0,0,y,x));_mm_storel_pi(reinterpret_cast<__m64*>(s+0x2d0),pair);
}
std::uint8_t textButton_16330(std::uint8_t *s,std::uint8_t*,const float *r,std::uint64_t callback,std::uint64_t id) {
    float copy[4];std::memcpy(copy,r,16);if(clicked_111f0(s,copy))activateText_112d0(s,callback,id);return textActive_11340(s,id);
}
void textEntry_16380(std::uint8_t *s,std::uint8_t *u,const float *r,const ControlDependencies &d) {
    float rect[4],copy[4];std::memcpy(rect,r,16);std::memcpy(copy,r,16);
    const auto advance=add(ui::drawAlignedText_10cb0(u,copy,1,0,reinterpret_cast<const char*>(s+0x378),d.image,d.fonts),read<float>(d.image,0x140e14));
    float color[4];const auto gray=read<float>(d.image,0x140e18);recovered_color_74150(color,gray,gray,gray,1);
    float caret[]{advance,rect[1],rect[2],rect[3]};drawCaret_10e70(u,caret,color,read<float>(d.image,0x140e1c),1,d);
}
void alignedTextEntry_16430(std::uint8_t *s,std::uint8_t *u,const float *r,std::uint32_t align,const ControlDependencies &d) {
    float copy[4];std::memcpy(copy,r,16);const auto advance=ui::drawAlignedText_10cb0(u,copy,align,0,reinterpret_cast<const char*>(s+0x378),d.image,d.fonts);
    const auto y=r[1],w=r[2],h=r[3];float color[4];const auto gray=read<float>(d.image,0x140e24);recovered_color_74150(color,gray,gray,gray,1);
    float caret[]{add(advance,read<float>(d.image,0x140e20)),y,w,h};drawCaret_10e70(u,caret,color,read<float>(d.image,0x140e28),1,d);
}
void filterNumber_164f0(char *s,std::uint32_t character) {
    const auto length=recovered_string_length_ab840(reinterpret_cast<const std::uint8_t*>(s));if(length==100)return;
    const auto c=std::uint8_t(character);if(std::uint8_t(c-0x30)<10||std::uint8_t(c-0x2c)<3)s[length]=char(c);
}
void filterProfileName_13ad0(char *s,std::uint32_t character) {
    const auto length=recovered_string_length_ab840(reinterpret_cast<const std::uint8_t*>(s));const auto c=std::uint8_t(character);
    if(length>=15||std::uint8_t(c-0x20)>=0x5f||c==0x2f||c==0x5c)return;
    s[length]=char(c);
}
}
