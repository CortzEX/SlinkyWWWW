#include "GuiPages.hpp"
#include "GuiMemory.hpp"
#include "SharedNativeState.hpp"
#include "DisplayGeometry.hpp"
#include "KeyNames.hpp"
#include "Widgets.hpp"
#include "ScalarCeiling.hpp"
#include <bit>
#include <cstring>
namespace reconstruction::gui {
// RVA 12B20. Category lists contain descriptor pointers; count and list storage
// are reread after each row so callbacks retain native mutation visibility.
void renderCategory_12b20(std::uint8_t *state,std::uint8_t *ui,std::uint64_t manager,
    std::uint32_t category,float elapsed,const PageDependencies &d) {
    auto *image=d.image,*background=canvas(ui);const auto &fonts=d.controls.fonts;
    autoColumns_10780(state,read<float>(image,0x1409E0),image);
    auto *categoryList=reinterpret_cast<std::uint8_t *>(manager+static_cast<std::uint64_t>(category)*16+0x10);
    if(read<std::uint64_t>(categoryList,8)==0)return;
    const auto quotient=_mm_div_sd(_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(elapsed)),_mm_set_sd(read<double>(image,0x1409E8)));
    const float animation=_mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),quotient));
    const float grayBackground=read<float>(image,0x1409F0),radius=read<float>(image,0x1409F4),padding=read<float>(image,0x1409F8);
    const float titleGray=read<float>(image,0x140A00),titleAccent=read<float>(image,0x140A04);
    const float upperIntRange=read<float>(image,0x140A1C),descriptionGray=read<float>(image,0x140A14),descriptionAccent=read<float>(image,0x140A18);
    auto makeGray=[](float *out,float gray){recovered_color_74150(out,gray,gray,gray,1);};
    for(std::uint64_t row=0;row<read<std::uint64_t>(categoryList,8);++row) {
        auto *module=reinterpret_cast<std::uint8_t *>(read<std::uintptr_t>(reinterpret_cast<void *>(read<std::uintptr_t>(categoryList)),static_cast<std::ptrdiff_t>(row*8)));
        float outer[4],viewport[4],copy[4];ui::nextColumnRect_10860(outer,state,read<float>(module,0x38),image);
        recovered_rect_a070(viewport,0,read<float>(state,0x4BC),read<float>(ui,0x18),read<float>(ui,0x1C));
        std::memcpy(copy,outer,16);if(!intersectsRect_a0e0(viewport,copy))continue;
        float rgba[4];makeGray(rgba,grayBackground);drawing::setFillColor_74ef0(background,rgba,image);
        std::memcpy(copy,outer,16);ui::fillRoundedRect_10a60(ui,copy,radius,image,fonts);
        std::memcpy(copy,outer,16);pushScissor_104f0(ui,state,copy,padding,12,image);setColumns_106b0(state,1,image);
        auto *c=canvas(ui);float titleRect[4];ui::nextColumnRect_10860(titleRect,state,radius,image);
        float titleAdvance;
        if(read<std::uint8_t>(state,0x4CC)==1) {
            float normal[4],accent[4];makeGray(normal,titleGray);makeGray(accent,titleAccent);std::memcpy(copy,titleRect,16);
            titleAdvance=moduleText_130c0(state,ui,module,copy,16,normal,accent,reinterpret_cast<const char *>(read<std::uintptr_t>(module)),d);
        } else {
            drawing::setFontSize_79610(c,read<float>(image,0x1409FC));makeGray(rgba,titleGray);drawing::setFillColor_74ef0(c,rgba,image);
            const auto *name=reinterpret_cast<const char *>(read<std::uintptr_t>(module));std::memcpy(copy,titleRect,16);
            titleAdvance=ui::drawAlignedText_10cb0(ui,copy,0,0,name,image,fonts);
        }
        auto flags=read<std::uint32_t>(module,0x18);
        if((flags&1)==0) {
            float bindingRect[4];recovered_rect_a070(bindingRect,add(titleAdvance,read<float>(image,0x140A08)),titleRect[1],add(sub(titleRect[2],titleAdvance),titleRect[0]),titleRect[3]);
            const auto metadata=read<std::uint64_t>(reinterpret_cast<void *>(manager),0x308);
            const auto key=read<std::uint32_t>(module,0x1C);
            auto *flag=(read<std::uint8_t>(module,0x18)&8)?nullptr:module+0x20;
            std::memcpy(copy,bindingRect,16);profileTextInput_13420(state,ui,metadata,module,key,flag,copy,d);
            flags=read<std::uint32_t>(module,0x18);
        }
        if((flags&2)==0) {
            float toggleRect[4];recovered_rect_a070(toggleRect,add(add(titleRect[0],titleRect[2]),read<float>(image,0x140A0C)),titleRect[1],read<float>(image,0x140A10),titleRect[3]);
            auto enabled=read<std::uint8_t>(module,0x14);std::memcpy(copy,toggleRect,16);
            recovered_toggle_widget_13b20(state,ui,copy,module+0x28,&enabled,image,d.calls);
            if(enabled!=read<std::uint8_t>(module,0x14))native_state::scheduleModuleAction(manager,reinterpret_cast<std::uintptr_t>(module),enabled);
        }
        if(read<std::uint8_t>(state,0x4CC)==0) {
            float descriptionRect[4],normal[4],accent[4];ui::nextColumnRect_10860(descriptionRect,state,radius,image);
            makeGray(normal,descriptionGray);makeGray(accent,descriptionAccent);const auto *description=reinterpret_cast<const char *>(read<std::uintptr_t>(module,8));
            std::memcpy(copy,descriptionRect,16);moduleText_130c0(state,ui,module,copy,14,normal,accent,description,d);
        }
        if(read<std::uint8_t>(module,0x40)==1) {
            const auto callback=read<std::uint64_t>(module,0x1F8);
            if(callback!=0)d.input.invoke(d.input.context,callback,reinterpret_cast<std::uintptr_t>(state),reinterpret_cast<std::uintptr_t>(ui),0);
        }
        const float layoutHeight=endLayout_105b0(ui,state,image);
        const auto signedValue=_mm_cvttss_si64(_mm_set_ss(layoutHeight));
        const auto adjusted=_mm_cvttss_si64(_mm_set_ss(sub(layoutHeight,upperIntRange)));
        const auto sign=static_cast<std::uint64_t>(signedValue>>63);
        const auto raw=static_cast<std::uint64_t>(signedValue)|(static_cast<std::uint64_t>(adjusted)&sign);
        float nextHeight=unsignedFloat(raw);const float oldHeight=read<float>(module,0x38);
        if(oldHeight!=0)nextHeight=interpolate_a260(oldHeight,nextHeight,animation,image);
        write(module,0x38,nextHeight);
    }
}

// RVA 130C0. A module with a settings callback gets an expandable title area;
// the button toggles its byte40 and draws a plus/minus indicator.
float moduleText_130c0(std::uint8_t *state,std::uint8_t *ui,std::uint8_t *module,
    const float *rect,float font,const float *normal,const float *highlight,const char *text,
    const PageDependencies &d) {
    auto *c=canvas(ui),*image=d.image;const auto &fonts=d.controls.fonts;float copy[4],color[4];
    if(read<std::uint64_t>(module,0x1F8)==0) {
        drawing::setFontSize_79610(c,font);std::memcpy(color,normal,16);drawing::setFillColor_74ef0(c,color,image);
        std::memcpy(copy,rect,16);return ui::drawAlignedText_10cb0(ui,copy,0,0,text,image,fonts);
    }
    float expander[4];recovered_rect_a070(expander,rect[0],rect[1],rect[3],rect[3]);
    const float spacing=read<float>(image,0x140A20),textX=add(add(expander[0],expander[2]),spacing);
    const float advance=drawing::textBounds_7ae90(c,textX,rect[1],text,nullptr,nullptr,image,fonts);
    float textRect[4];recovered_rect_a070(textRect,textX,rect[1],advance,rect[3]);
    float combined[4];recovered_rect_a070(combined,rect[0],rect[1],add(add(expander[2],textRect[2]),spacing),rect[3]);
    std::memcpy(copy,combined,16);if(clicked_111f0(state,copy))write(module,0x40,std::uint8_t(read<std::uint8_t>(module,0x40)^1));
    std::memcpy(copy,combined,16);const auto hovering=hovered_11180(state,copy);
    drawing::setFontSize_79610(c,font);std::memcpy(color,hovering?highlight:normal,16);drawing::setFillColor_74ef0(c,color,image);
    std::memcpy(copy,textRect,16);ui::drawAlignedText_10cb0(ui,copy,0,0,text,image,fonts);
    const float background=read<float>(image,hovering?0x140A28:0x140A24);
    recovered_color_74150(color,background,background,background,1);drawing::setFillColor_74ef0(c,color,image);
    std::memcpy(copy,expander,16);ui::fillRoundedRect_10a60(ui,copy,read<float>(image,0x140A2C),image,fonts);
    std::memcpy(copy,expander,16);float indicator[4];insetRect_a130(indicator,copy,read<float>(image,0x140A30));
    const float foreground=read<float>(image,hovering?0x140A38:0x140A34);
    recovered_color_74150(color,foreground,foreground,foreground,1);strokeColor_74de0(c,color,image);
    drawing::beginPath_75bc0(c);float half=read<float>(image,0x140A3C);
    moveTo_75bf0(c,indicator[0],add(mul(indicator[3],half),indicator[1]),fonts);
    lineTo_75ec0(c,add(indicator[0],indicator[2]),add(mul(indicator[3],half),indicator[1]),fonts);
    if(read<std::uint8_t>(module,0x40)==0) {
        moveTo_75bf0(c,add(mul(indicator[2],half),indicator[0]),indicator[1],fonts);
        half=add(mul(half,indicator[2]),indicator[0]);
        lineTo_75ec0(c,half,add(indicator[1],indicator[3]),fonts);
    }
    lineWidth_749e0(c,read<float>(image,0x140A40));drawing::stroke_77f80(c,image,fonts);
    return add(combined[0],combined[2]);
}
// RVA B2920. The ADDSS is evaluated for native floating-point side effects,
// but the rounded result is built from the original input bits.
float ceilFloat_b2920(float value,const std::uint8_t *image) {
    return recovered_ceiling_float_b2920(value,image);
}

// RVA 13420. A binding button and optional adjacent mode toggle; R9 identifies
// the record and the fifth argument is its key DWORD, not a profile string.
void profileTextInput_13420(std::uint8_t *state,std::uint8_t *ui,std::uint64_t metadata,
    std::uint8_t *record,std::uint32_t key,std::uint8_t *flag,const float *rectangle,
    const PageDependencies &d) {
    auto *c=canvas(ui);auto *image=d.image;const auto &fonts=d.controls.fonts;
    drawing::setFontSize_79610(c,read<float>(image,0x140A44));ui::selectFont_10340(ui,1);
    const auto active=active_112b0(state,reinterpret_cast<std::uintptr_t>(record));
    const auto measure=[&](const char *text) {
        return ceilFloat_b2920(drawing::textBounds_7ae90(c,0,0,text,nullptr,nullptr,image,fonts),image);
    };
    float width;
    if(active)width=measure(reinterpret_cast<const char *>(image+0x140AB6));
    else {
        width=read<float>(image,0x2F7490+static_cast<std::uint64_t>(key)*4);
        if(width==0) {
            width=measure(recovered_key_name_9380(key,image));
            write(image,0x2F7490+static_cast<std::uint64_t>(key)*4,width);
        }
    }
    float button[4];recovered_rect_a070(button,rectangle[0],rectangle[1],add(width,read<float>(image,0x140A44)),rectangle[3]);
    auto gray=[&](float value,float *out) {recovered_color_74150(out,value,value,value,1);};
    float color[4],source[4];
    if(key!=0)std::memcpy(source,state+0x360,16);
    else gray(read<float>(image,0x140A4C),source);
    recovered_color_741b0(color,source,read<float>(image,0x140A48));drawing::setFillColor_74ef0(c,color,image);
    float copied[4];std::memcpy(copied,button,16);ui::fillRoundedRect_10a60(ui,copied,read<float>(image,0x140A50),image,fonts);
    std::memcpy(copied,button,16);
    if(hovered_11180(state,copied))gray(read<float>(image,0x140A54),color);
    else if(key!=0)std::memcpy(color,state+0x360,16);
    else gray(read<float>(image,0x140A4C),color);
    drawing::setFillColor_74ef0(c,color,image);
    const char *label=active?reinterpret_cast<const char *>(image+0x140AB6):recovered_key_name_9380(key,image);
    std::memcpy(copied,button,16);ui::drawAlignedText_10cb0(ui,copied,1,1,label,image,fonts);
    std::memcpy(copied,button,16);
    if(clicked_111f0(state,copied))activate_11290(state,metadata,reinterpret_cast<std::uintptr_t>(record));
    if(key==0) {if(flag!=nullptr)write(flag,0,std::uint8_t(0));return;}
    if(flag==nullptr)return;
    const auto *toggleLabel=reinterpret_cast<const char *>(image+0x140AC5);
    const float toggleWidth=measure(toggleLabel);float toggle[4];
    recovered_rect_a070(toggle,add(add(button[0],button[2]),read<float>(image,0x140A50)),button[1],add(toggleWidth,read<float>(image,0x140A44)),button[3]);
    bool selected=read<std::uint8_t>(flag)!=0;
    if(!selected) {
        std::memcpy(copied,rectangle,16);if(!hovered_11180(state,copied))return;
        selected=read<std::uint8_t>(flag)==1;
    }
    gray(read<float>(image,selected?0x140A58:0x140A4C),source);
    recovered_color_741b0(color,source,read<float>(image,0x140A48));drawing::setFillColor_74ef0(c,color,image);
    std::memcpy(copied,toggle,16);ui::fillRoundedRect_10a60(ui,copied,read<float>(image,0x140A50),image,fonts);
    std::memcpy(copied,toggle,16);
    gray(read<float>(image,hovered_11180(state,copied)?0x140A58:0x140A4C),color);drawing::setFillColor_74ef0(c,color,image);
    std::memcpy(copied,toggle,16);ui::drawAlignedText_10cb0(ui,copied,1,1,toggleLabel,image,fonts);
    std::memcpy(copied,toggle,16);if(clicked_111f0(state,copied))write(flag,0,std::uint8_t(read<std::uint8_t>(flag)^1));
}
// RVA 138F0. R9 is an optional profile name, not the UI/canvas pointer.
void profilePopup_138f0(std::uint8_t *state,std::uint64_t manager,std::uint64_t configuration,
    const char *name,std::uint32_t mode,const PageDependencies &d) {
    auto *record=static_cast<std::uint8_t *>(d.allocate(d.context,40));
    if(record==nullptr)return;
    write(record,0,reinterpret_cast<std::uintptr_t>(state));write(record,8,manager);
    write(record,16,configuration);write(record,24,std::uint64_t(0));write(record,32,mode);
    const char *initial=name;
    if(name!=nullptr) {
        const auto length=d.controls.fonts.length(d.controls.fonts.context,name);
        auto *copy=static_cast<char *>(d.allocate(d.context,length+1));
        if(copy==nullptr){d.input.release(d.input.context,record);return;}
        d.controls.copyTooltip_13d0b0(d.controls.context,copy,name,length);
        write(copy,static_cast<std::ptrdiff_t>(length),std::uint8_t(0));
        write(record,24,reinterpret_cast<std::uintptr_t>(copy));
    } else initial=reinterpret_cast<const char *>(d.image+0x140ACA);
    const auto relative=read<std::int32_t>(d.image,0x140C30+static_cast<std::uint64_t>(mode)*4);
    const auto title=reinterpret_cast<std::uintptr_t>(d.image+0x140C30)+static_cast<std::uint64_t>(static_cast<std::int64_t>(relative));
    d.openDialog_16820(d.context,state,reinterpret_cast<std::uintptr_t>(record),
        d.completionCallback_139d0,reinterpret_cast<const char *>(title),initial);
}

// RVA 139D0. Configuration errors select event kind12; successful/default
// modes select kind11 and preserve profile pointer and mode DWORD.
void completeProfilePopup_139d0(std::uint8_t *record,const PageDependencies &d) {
    auto mode=read<std::uint32_t>(record,32);std::uint32_t error=0;
    if(mode==0)error=d.loadProfile_be40(d.context,reinterpret_cast<const char *>(read<std::uintptr_t>(record,24)),read<std::uint64_t>(record,8));
    else if(mode==1)error=d.saveProfile_c0b0(d.context,reinterpret_cast<const char *>(read<std::uintptr_t>(record,24)),1,read<std::uint64_t>(record,8));
    else if(mode==2)error=d.openProfileDirectory_c290(d.context);
    else if(mode==3)error=d.deleteProfile_c220(d.context,reinterpret_cast<const char *>(read<std::uintptr_t>(record,24)));
    alignas(16) std::uint8_t event[72]{};
    if(error!=0){write(event,0,std::uint32_t(12));write(event,8,error);}
    else {mode=read<std::uint32_t>(record,32);write(event,0,std::uint32_t(11));write(event,8,read<std::uint64_t>(record,24));write(event,16,mode);}
    native_state::dispatchEvent(read<std::uint64_t>(record,8),reinterpret_cast<std::uintptr_t>(event));
    auto *state=reinterpret_cast<std::uint8_t *>(read<std::uintptr_t>(record));
    write(state,0x4A0,std::uint64_t(0xBFF0000000000000));
    d.input.release(d.input.context,reinterpret_cast<void *>(read<std::uintptr_t>(record,24)));
    d.input.release(d.input.context,record);
}

// RVA 16530. These literals initialize a dialog at this observed transition;
// they are not a claim about process startup state.
void beginModal_16530(std::uint8_t *state,std::uint64_t title,std::uint64_t user,
    std::uint64_t filterCallback,std::uint64_t completion,const PageDependencies &d) {
    ui::finishModal_169c0(state,1,d.image,d.input);
    const double now=d.clock(d.context);
    write(state,0x3F8,std::uint64_t(1));write(state,0x400,user);write(state,0x408,title);
    write(state,0x410,now);std::memset(state+0x418,0,16);write(state,0x428,completion);write(state,0x430,filterCallback);
    for(std::ptrdiff_t offset=0x438;offset<=0x488;offset+=16)std::memset(state+offset,0,16);
    activateText_112d0(state,filterCallback,reinterpret_cast<std::uintptr_t>(state+0x3F8));
}
}
