#include "GuiModal.hpp"
#include "GuiMemory.hpp"
#include "DisplayGeometry.hpp"
#include <cstring>
namespace reconstruction::gui {
namespace {
void color(std::uint8_t *canvas,float gray,const std::uint8_t *image) {
    float rgba[4];recovered_color_74150(rgba,gray,gray,gray,1);
    drawing::setFillColor_74ef0(canvas,rgba,image);
}
bool inputRow(ModalFrame &f,float *rectangle,const PageDependencies &d) {
    auto *c=canvas(f.ui);ui::nextColumnRect_10860(rectangle,f.state,read<float>(d.image,0x140EC0),d.image);
    drawing::setFontSize_79610(c,read<float>(d.image,0x140EC4));
    float rgba[4];const float gray=read<float>(d.image,0x140EC8);recovered_color_74150(rgba,gray,gray,gray,1);
    strokeColor_74de0(c,rgba,d.image);lineWidth_749e0(c,read<float>(d.image,0x140EB4));
    float copy[4];std::memcpy(copy,rectangle,16);ui::strokeRoundedRect_10b00(f.ui,copy,read<float>(d.image,0x140E9C),d.image,d.controls.fonts);
    return textActive_11340(f.state,reinterpret_cast<std::uintptr_t>(f.state+0x3F8))!=0;
}
void textModal(ModalFrame &f,const PageDependencies &d) {
    float rectangle[4];if(!inputRow(f,rectangle,d))return;
    float copy[4],inner[4];std::memcpy(copy,rectangle,16);insetRect_a130(inner,copy,read<float>(d.image,0x140ECC));
    std::memcpy(copy,inner,16);textEntry_16380(f.state,f.ui,copy,d.controls);
    auto *submitted=consumeSubmitted_11390(f.state);
    if(submitted==nullptr){f.finishMode=0;return;}
    const auto user=read<std::uint64_t>(f.state,0x400),callback=read<std::uint64_t>(f.state,0x428);
    d.input.invoke(d.input.context,callback,user,reinterpret_cast<std::uintptr_t>(submitted),0);
    f.finishMode=2;
}
void promptModal(ModalFrame &f,const PageDependencies &d) {
    auto *c=canvas(f.ui);float rectangle[4];const float height=read<float>(d.image,0x140EC0);
    ui::nextColumnRect_10860(rectangle,f.state,height,d.image);
    drawing::setFontSize_79610(c,read<float>(d.image,0x140EC4));color(c,read<float>(d.image,0x140EA4),d.image);
    float copy[4];std::memcpy(copy,rectangle,16);
    ui::drawAlignedText_10cb0(f.ui,copy,0,0,reinterpret_cast<const char *>(f.state+0x430),d.image,d.controls.fonts);
    float button[4];ui::nextColumnRect_10860(button,f.state,height,d.image);std::memcpy(copy,button,16);
    const bool hovering=hovered_11180(f.state,copy)!=0;
    float rgba[4];recovered_color_74150(rgba,read<float>(d.image,hovering?0x140EAC:0x140EA4),
        read<float>(d.image,hovering?0x140EB0:0x140EE0),read<float>(d.image,hovering?0x140EB0:0x140EE0),1);
    drawing::setFillColor_74ef0(c,rgba,d.image);std::memcpy(copy,button,16);
    ui::fillRoundedRect_10a60(f.ui,copy,read<float>(d.image,0x140EE4),d.image,d.controls.fonts);
    color(c,read<float>(d.image,0x140E90),d.image);std::memcpy(copy,button,16);
    f.finishMode=0;
    ui::drawAlignedText_10cb0(f.ui,copy,1,0,reinterpret_cast<const char *>(d.image+0x140F88),d.image,d.controls.fonts);
    std::memcpy(copy,button,16);if(!clicked_111f0(f.state,copy))return;
    d.input.invoke(d.input.context,read<std::uint64_t>(f.state,0x428),read<std::uint64_t>(f.state,0x400),0,0);
    f.finishMode=2;
}
std::uint8_t asciiLower(std::uint8_t value) {
    const auto distance=static_cast<std::uint8_t>(value-0x41);
    return distance<0x1A?static_cast<std::uint8_t>(value|0x20):value;
}
bool substring(const char *candidate,std::uint64_t extra,const char *search,std::uint64_t length) {
    if(length==0)return true;
    for(std::uint64_t start=0;start<=extra;++start) {
        std::uint64_t matched=0;
        while(asciiLower(read<std::uint8_t>(candidate,static_cast<std::ptrdiff_t>(start+matched)))==asciiLower(read<std::uint8_t>(search,static_cast<std::ptrdiff_t>(matched)))) {
            ++matched;if(matched==length)return true;
        }
    }
    return false;
}
void listModal(ModalFrame &f,const PageDependencies &d) {
    float rectangle[4];if(!inputRow(f,rectangle,d))return;
    float copy[4],inner[4];std::memcpy(copy,rectangle,16);insetRect_a130(inner,copy,read<float>(d.image,0x140ECC));
    std::memcpy(copy,inner,16);textEntry_16380(f.state,f.ui,copy,d.controls);
    const auto *search=textBuffer_113d0(f.state);const double now=read<double>(f.ui,8);
    const double elapsed=_mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(now),_mm_set_sd(read<double>(f.state,0x448))));
    if(!(read<double>(d.image,0x140ED0)>elapsed)) {
        auto *collection=reinterpret_cast<std::uint8_t *>(read<std::uintptr_t>(f.state,0x450));
        if(collection==nullptr) {
            collection=static_cast<std::uint8_t *>(d.allocateZeroed(d.context,1,24));
            write(f.state,0x450,reinterpret_cast<std::uintptr_t>(collection));
        }
        if(collection!=nullptr) {
            std::memset(collection,0,16);d.input.release(d.input.context,reinterpret_cast<void *>(read<std::uintptr_t>(collection,16)));
            write(collection,16,std::uint64_t(0));write(f.state,0x458,std::uint64_t(0));
            for(std::uint64_t row=0;row<read<std::uint64_t>(f.state,0x440);++row) {
                auto *options=reinterpret_cast<std::uint8_t *>(read<std::uintptr_t>(f.state,0x438));
                const auto *candidate=reinterpret_cast<const char *>(read<std::uintptr_t>(options,static_cast<std::ptrdiff_t>(row*8)));
                const auto candidateLength=d.controls.fonts.length(d.controls.fonts.context,candidate);
                const auto searchLength=d.controls.fonts.length(d.controls.fonts.context,search);
                if(candidateLength<searchLength||!substring(candidate,candidateLength-searchLength,search,searchLength))continue;
                collection=reinterpret_cast<std::uint8_t *>(read<std::uintptr_t>(f.state,0x450));const auto count=read<std::uint64_t>(collection);
                if(count>=30){write(f.state,0x458,read<std::uint64_t>(f.state,0x458)+1);continue;}
                if((recovered_list_growth(collection+16,16,count,collection+8,static_cast<std::uint32_t>(reinterpret_cast<std::uintptr_t>(collection)),&d.listMemory)&0xFF)==0)continue;
                const auto after=read<std::uint64_t>(collection);auto *records=reinterpret_cast<std::uint8_t *>(read<std::uintptr_t>(collection,16));
                write(records,static_cast<std::ptrdiff_t>(after*16),row);write(records,static_cast<std::ptrdiff_t>(after*16+8),reinterpret_cast<std::uintptr_t>(candidate));
                write(collection,0,read<std::uint64_t>(collection)+1);
            }
            write(f.state,0x448,now);
        }
    }
    // Native continuation dereferences the collection even after allocation
    // failure. A valid caller-owned collection is therefore a retained contract.
    auto *collection=reinterpret_cast<std::uint8_t *>(read<std::uintptr_t>(f.state,0x450));
    const auto count=read<std::uint64_t>(collection);if(count==0){f.finishMode=0;return;}
    auto *c=canvas(f.ui);drawing::setFontSize_79610(c,read<float>(d.image,0x140EA0));
    const float half=read<float>(d.image,0x140EDC),hoverGray=read<float>(d.image,0x140E90),normalGray=read<float>(d.image,0x140EA4),rowHeight=read<float>(d.image,0x140ED8);
    const char *selected=nullptr;std::uint64_t selectedIndex=0;float paired[4];
    for(std::uint64_t row=0;row<count;++row) {
        if((row&1)==0)ui::nextColumnRect_10860(paired,f.state,rowHeight,d.image);
        float button[4]={paired[0],paired[1],mul(paired[2],half),paired[3]};if(row&1)button[0]=add(paired[0],button[2]);
        std::memcpy(copy,button,16);color(c,hovered_11180(f.state,copy)?hoverGray:normalGray,d.image);
        collection=reinterpret_cast<std::uint8_t *>(read<std::uintptr_t>(f.state,0x450));auto *records=reinterpret_cast<std::uint8_t *>(read<std::uintptr_t>(collection,16));
        const auto index=read<std::uint64_t>(records,static_cast<std::ptrdiff_t>(row*16));const auto *candidate=reinterpret_cast<const char *>(read<std::uintptr_t>(records,static_cast<std::ptrdiff_t>(row*16+8)));
        std::memcpy(copy,button,16);ui::drawAlignedText_10cb0(f.ui,copy,0,0,candidate,d.image,d.controls.fonts);
        std::memcpy(copy,button,16);if(clicked_111f0(f.state,copy)){selected=candidate;selectedIndex=index;}
    }
    const auto overflow=read<std::uint64_t>(f.state,0x458);
    if(overflow!=0) {
        char message[16];d.calls(0xAB710,reinterpret_cast<std::uintptr_t>(message),14,reinterpret_cast<std::uintptr_t>(d.image+0x140F91),overflow<9999?overflow:9999);
        float note[4];ui::nextColumnRect_10860(note,f.state,rowHeight,d.image);color(c,read<float>(d.image,0x140EA8),d.image);
        drawing::setFontSize_79610(c,read<float>(d.image,0x140EC4));std::memcpy(copy,note,16);ui::drawAlignedText_10cb0(f.ui,copy,0,0,message,d.image,d.controls.fonts);
    }
    if(selected==nullptr){f.finishMode=0;return;}
    d.input.invoke(d.input.context,read<std::uint64_t>(f.state,0x430),read<std::uint64_t>(f.state,0x400),selectedIndex,reinterpret_cast<std::uintptr_t>(selected));
    f.finishMode=2;
}
}

// RVA16CA0 common frame and explicit text/prompt/list/color section dispatch.
void renderModal_16ca0(std::uint8_t *state,std::uint8_t *ui,const PageDependencies &d) {
    write(state,0x420,std::uint8_t(1));
    const auto elapsed=_mm_div_sd(_mm_sub_sd(_mm_set_sd(read<double>(ui,8)),_mm_set_sd(read<double>(state,0x410))),_mm_set_sd(read<double>(d.image,0x140E88)));
    const auto accumulated=_mm_add_sd(_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(read<float>(state,0x418))),elapsed);
    const float progress=_mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),accumulated));
    write(state,0x418,minimum(read<float>(d.image,0x140E90),progress));
    setColumns_106b0(state,1,d.image);float outer[4],copy[4];ui::nextColumnRect_10860(outer,state,read<float>(state,0x41C),d.image);
    auto *c=canvas(ui);color(c,read<float>(d.image,0x140E94),d.image);const float radius=read<float>(d.image,0x140E98);
    std::memcpy(copy,outer,16);ui::fillRoundedRect_10a60(ui,copy,radius,d.image,d.controls.fonts);
    std::memcpy(copy,outer,16);pushScissor_104f0(ui,state,copy,read<float>(d.image,0x140E9C),12,d.image);setColumns_106b0(state,1,d.image);
    c=canvas(ui);float heading[4];ui::nextColumnRect_10860(heading,state,radius,d.image);drawing::setFontSize_79610(c,read<float>(d.image,0x140EA0));
    color(c,read<float>(d.image,0x140EA4),d.image);std::memcpy(copy,heading,16);ui::drawAlignedText_10cb0(ui,copy,0,0,reinterpret_cast<const char *>(read<std::uintptr_t>(state,0x408)),d.image,d.controls.fonts);
    const float x=add(sub(heading[2],heading[3]),heading[0]),y=heading[1],size=heading[3];float button[4]={x,y,size,size};std::memcpy(copy,button,16);
    const bool hover=hovered_11180(state,copy)!=0;float rgba[4];
    if(hover)recovered_color_74150(rgba,read<float>(d.image,0x140EAC),read<float>(d.image,0x140EB0),read<float>(d.image,0x140EB0),1);
    else {const float gray=read<float>(d.image,0x140EA8);recovered_color_74150(rgba,gray,gray,gray,1);}
    strokeColor_74de0(c,rgba,d.image);lineWidth_749e0(c,read<float>(d.image,0x140EB4));
    const float inset=fromDouble(_mm_cvtsd_f64(_mm_mul_sd(_mm_cvtss_sd(_mm_setzero_pd(),_mm_set_ss(size)),_mm_set_sd(read<double>(d.image,0x140EB8)))));
    drawing::beginPath_75bc0(c);const float x0=add(x,inset),y0=add(y,inset),x1=sub(add(size,x),inset),y1=sub(add(y,size),inset);
    moveTo_75bf0(c,x0,y0,d.controls.fonts);lineTo_75ec0(c,x1,y1,d.controls.fonts);moveTo_75bf0(c,x1,y0,d.controls.fonts);lineTo_75ec0(c,x0,y1,d.controls.fonts);drawing::stroke_77f80(c,d.image,d.controls.fonts);
    std::memcpy(copy,button,16);ModalFrame frame{state,ui,clicked_111f0(state,copy),1};
    const auto mode=read<std::uint32_t>(state,0x3F8);
    if(mode==1)textModal(frame,d);else if(mode==2)renderModalColorSection(frame,d);else if(mode==3)promptModal(frame,d);else if(mode==4)listModal(frame,d);
    write(state,0x41C,endLayout_105b0(ui,state,d.image));write(state,0x420,std::uint8_t(0));write(state,0x410,read<double>(ui,8));
    if(frame.finishMode!=0)ui::finishModal_169c0(state,frame.finishMode==1,d.image,d.input);
    else if(frame.closeButton!=0)ui::finishModal_169c0(state,1,d.image,d.input);
}
}
