#include "GuiRuntime.hpp"
#include "GuiMemory.hpp"
#include "DisplayGeometry.hpp"
#include "SharedNativeState.hpp"
#include "Geometry.hpp"
#include <cstring>
namespace reconstruction::gui {
static const char *text(const std::uint8_t *image,std::size_t rva) { return reinterpret_cast<const char*>(image+rva); }
static void gray(std::uint8_t *c,float value,const std::uint8_t *image,float alpha=1) {
    float rgba[4];recovered_color_74150(rgba,value,value,value,alpha);drawing::setFillColor_74ef0(c,rgba,image);
}
static void errorEvent(std::uint64_t manager,std::uint32_t error,const char *message) {
    alignas(16) std::uint8_t event[72]{};write(event,0,std::uint32_t(12));write(event,8,error);write(event,16,std::uint64_t(std::uintptr_t(message)));
    native_state::dispatchEvent(manager,std::uintptr_t(event));
}
static void actionEvent(std::uint64_t manager,std::uint64_t name,std::uint32_t action,std::uint8_t *state) {
    alignas(16) std::uint8_t event[72]{};write(event,0,std::uint32_t(11));write(event,8,name);write(event,16,action);
    native_state::dispatchEvent(manager,std::uintptr_t(event));write(state,0x4a0,std::uint64_t(0xbff0000000000000));
}
void fadeBackdrop_128c0(std::uint8_t *u,float fade,const RuntimeDependencies &d) {
    const auto *image=d.controls.image;
    const auto factor=sub(read<float>(image,0x1409c4),fade);
    const auto transformed=d.binaryScalar_13cfe0(d.protectedContext,factor,read<float>(image,0x1409c8));
    const auto opacity=sub(read<float>(image,0x1409c4),transformed);auto *c=canvas(u);drawing::setStrokeWidth_74a60(c,opacity);
    float source[4],rgba[4];const auto value=read<float>(image,0x1409cc);recovered_color_74150(source,value,value,value,1);
    recovered_color_741b0(rgba,source,read<float>(image,0x1409d0));drawing::setFillColor_74ef0(c,rgba,image);
    float rect[4];recovered_rect_a070(rect,0,0,read<float>(u,0x18),read<float>(u,0x1c));fillRectangle_10a10(u,rect,d.controls.fonts);
    translateCanvas_74b40(c,0,read<float>(image,0x1409d4));translateCanvas_74b40(c,0,mul(opacity,read<float>(image,0x1409d8)));
}
static void profiles(std::uint8_t *s,std::uint8_t *u,std::uint64_t manager,std::uint64_t registry,const RuntimeDependencies &d) {
    const auto &control=d.controls;const auto *image=control.image;const auto &cfg=d.configuration;const auto &pages=d.pages;
    if(read<std::uint32_t>(s,0x370)==0&&read<double>(u,8)>read<double>(s,0x4a0)+read<double>(image,0x140918)) {
        const auto error=cfg.refresh_ead0(cfg.context,registry);if(error)errorEvent(manager,error,nullptr);write(s,0x4a0,read<double>(u,8));
    }
    auto *backgroundCanvas=canvas(u);autoColumns_10780(s,read<float>(image,0x140920),image);
    std::uint64_t count;const auto records=cfg.records_eea0(cfg.context,registry,&count);
    const auto background=read<float>(image,0x140924),radius=read<float>(image,0x140928),font=read<float>(image,0x14092c),foreground=read<float>(image,0x140930),disabledAlpha=read<float>(image,0x1408cc);
    const auto half=read<double>(image,0x140938);const auto dateGray=read<float>(image,0x140944);
    for(std::uint64_t row=0;row<=count;++row) {
        float rect[4],viewport[4],copy[4];ui::nextColumnRect_10860(rect,s,read<float>(s,0x4c4),image);
        recovered_rect_a070(viewport,0,read<float>(s,0x4bc),read<float>(u,0x18),read<float>(u,0x1c));
        if(!intersectsRect_a0e0(viewport,rect))continue;
        auto *profile=row?reinterpret_cast<std::uint8_t*>(std::uintptr_t(records+(row<<6)-64)):nullptr;
        gray(backgroundCanvas,background,image);std::memcpy(copy,rect,16);ui::fillRoundedRect_10a60(u,copy,radius,image,control.fonts);
        std::memcpy(copy,rect,16);pushScissor_104f0(u,s,copy,read<float>(image,0x1408f8),12,image);setColumns_106b0(s,1,image);
        auto *rowCanvas=canvas(u);float inner[4];ui::nextColumnRect_10860(inner,s,radius,image);drawing::setFontSize_79610(rowCanvas,font);gray(rowCanvas,foreground,image);
        if(profile) {
            const auto name=read<std::uint64_t>(profile),end=read<std::uint64_t>(profile,8);std::memcpy(copy,inner,16);
            const auto width=measuredText_10da0(u,copy,0,0,reinterpret_cast<const char*>(std::uintptr_t(name)),reinterpret_cast<const char*>(std::uintptr_t(end)),control);
            float field[4];recovered_rect_a070(field,add(width,read<float>(image,0x140934)),inner[1],add(sub(inner[2],width),inner[0]),inner[3]);
            const auto metadata=cfg.metadata_ea90(cfg.context,registry);const auto id=read<std::uint32_t>(profile,0x38);
            pages.profileText_13420(pages.context,s,u,metadata,profile,id,0,field);
        } else { std::memcpy(copy,inner,16);measuredText_10da0(u,copy,0,0,text(image,0x140aca),nullptr,control); }
        for(std::uint32_t action=0;action!=4;++action) {
            float iconRect[4];const auto x=sub(sub(add(inner[0],inner[2]),float(80-20*std::int32_t(action))),float(36-12*std::int32_t(action)));
            recovered_rect_a070(iconRect,x,inner[1],radius,20);auto alpha=disabledAlpha;
            if(!(std::uint8_t(action)&std::uint8_t(profile==nullptr))) {
                alpha=1;std::memcpy(copy,iconRect,16);
                if(hovered_11180(s,copy)) {
                    const auto labelRva=std::int64_t(0x140ad4)+read<std::int32_t>(image,0x140ad4+action*4);
                    const auto center=_mm_cvttsd_si32(_mm_set_sd(double(iconRect[0])+double(iconRect[2])*half));
                    tooltip_14cb0(s,u,text(image,std::size_t(labelRva)),center,truncateInt(iconRect[1]),control);
                    std::memcpy(copy,iconRect,16);
                    if(clicked_111f0(s,copy)) {
                        const auto name=profile?read<std::uint64_t>(profile):0;
                        bool complete=false;std::uint32_t error=0;
                        if(action==0) {
                            if(cfg.pending_c200(cfg.context))pages.profilePopup_138f0(pages.context,s,manager,registry,reinterpret_cast<const char*>(name),0);
                            else { error=cfg.load_be40(cfg.context,name,manager);complete=!error; }
                        } else if(action==1) {
                            if(!profile)error=6003;
                            else {
                                const auto current=cfg.current_c1f0(cfg.context);
                                if(current&&d.compare_13d0a0(d.protectedContext,name,cfg.current_c1f0(cfg.context))==0) {
                                    error=cfg.save_c0b0(cfg.context,name,1,manager);complete=!error;
                                } else pages.profilePopup_138f0(pages.context,s,manager,registry,reinterpret_cast<const char*>(name),1);
                            }
                        } else if(action==2)pages.profilePopup_138f0(pages.context,s,manager,registry,reinterpret_cast<const char*>(name),2);
                        else if(profile)pages.profilePopup_138f0(pages.context,s,manager,registry,reinterpret_cast<const char*>(name),3);
                        else error=6004;
                        if(error)errorEvent(manager,error,error==6004?text(image,0x140b65):error==6003?text(image,0x140b87):nullptr);
                        else if(complete)actionEvent(manager,name,action,s);
                    }
                }
            }
            std::memcpy(copy,iconRect,16);drawIcon_10ba0(u,copy,read<std::uint32_t>(image,0x140af0+action*4),alpha,control);
        }
        if(!read<std::uint8_t>(s,0x4cc)) {
            float date[4];ui::nextColumnRect_10860(date,s,radius,image);drawing::setFontSize_79610(rowCanvas,read<float>(image,0x140940));gray(rowCanvas,dateGray,image);
            std::memcpy(copy,date,16);ui::drawAlignedText_10cb0(u,copy,0,0,profile?reinterpret_cast<const char*>(profile+16):text(image,0x140b00),image,control.fonts);
        }
        write(s,0x4c4,endLayout_105b0(u,s,image));
    }
    auto *c=canvas(u);float outer[4],copy[4];ui::nextColumnRect_10860(outer,s,read<float>(s,0x4c4),image);gray(c,background,image,disabledAlpha);
    std::memcpy(copy,outer,16);ui::fillRoundedRect_10a60(u,copy,radius,image,control.fonts);std::memcpy(copy,outer,16);
    if(textButton_16330(s,u,copy,d.profileNameCallback_13ad0,0)) {
        drawing::setFontSize_79610(c,font);gray(c,read<float>(image,0x1408d0),image);
        float input[4];recovered_rect_a070(input,outer[0],fromDouble(double(outer[1])+double(outer[3])*half+read<double>(image,0x140950)),outer[2],read<float>(image,0x140964));
        textEntry_16380(s,u,input,control);auto *submitted=consumeSubmitted_11390(s);
        if(submitted) {
            const auto name=std::uint64_t(std::uintptr_t(submitted));const auto error=cfg.save_c0b0(cfg.context,name,0,manager);
            if(error)errorEvent(manager,error,error==1012?text(image,0x140c06):nullptr);else actionEvent(manager,name,1,s);
        }
    } else {
        drawing::setFontSize_79610(c,read<float>(image,0x140948));std::memcpy(copy,outer,16);
        gray(c,hovered_11180(s,copy)?read<float>(image,0x1408d0):foreground,image);std::memcpy(copy,outer,16);
        ui::drawAlignedText_10cb0(u,copy,1,1,text(image,0x140c1d),image,control.fonts);
    }
}
void render_11820(std::uint8_t *s,std::uint8_t *u,std::uint64_t manager,std::uint64_t registry,const RuntimeDependencies &d) {
    const auto &control=d.controls;const auto *image=control.image;auto *savedCanvas=canvas(u);saveCanvas_73a70(savedCanvas);
    fadeBackdrop_128c0(u,read<float>(s,0x4b8),d);
    const auto width=read<float>(u,0x18);const auto wide=read<std::uint8_t>(s,0x4cd)!=0;
    const auto panelWidth=minimum(add(width,read<float>(image,0x1408c0)),read<float>(image,wide?0x1408c4:0x1408c8));
    const auto left=mul(sub(width,panelWidth),read<float>(image,0x1408cc));
    auto scroll=read<float>(s,0x4bc);if(0>scroll) { scroll=0;write(s,0x4bc,scroll); }else if(scroll>read<float>(s,0x4c0)) { scroll=read<float>(s,0x4c0);write(s,0x4bc,scroll); }
    const auto scale=div(read<float>(image,0x1408d0),read<float>(u,0x20));
    write(s,0x4a8,recovered_angle_scale_9e60(read<std::uint64_t>(s,0x4b0),scale));write(s,0x4ac,add(read<float>(s,0x4ac),read<float>(s,0x4bc)));
    const auto negativeScroll=std::bit_cast<float>(std::bit_cast<std::uint32_t>(read<float>(s,0x4bc))^read<std::uint32_t>(image,0x1408e0));
    translateCanvas_74b40(canvas(u),0,negativeScroll);resetLayout_10360(s);
    float panel[4];recovered_rect_a070(panel,left,0,panelWidth,read<float>(u,0x1c));
    const auto elapsed=fromDouble(read<double>(u,8)-read<double>(s,0x498));const auto elapsedDouble=double(elapsed);
    write(s,0x4b8,minimum(read<float>(image,0x1408d0),fromDouble(double(read<float>(s,0x4b8))+elapsedDouble/read<double>(image,0x1408f0))));
    float copy[4];std::memcpy(copy,panel,16);pushLayout_10380(s,copy,read<float>(image,0x1408f8),read<float>(image,0x1408fc));setColumns_106b0(s,1,image);tabs_113f0(s,u,elapsed,control);
    auto selected=read<std::uint64_t>(s,0x350);const auto difference=sub(unsignedFloat(selected),read<float>(s,0x358));
    if(difference!=0) {
        auto *c=canvas(u);const auto magnitude=std::bit_cast<float>(std::bit_cast<std::uint32_t>(difference)&read<std::uint32_t>(image,0x140900));
        const auto fade=sub(read<float>(image,0x1408d0),add(magnitude,magnitude));
        const auto alpha=_mm_cvtss_f32(_mm_andnot_ps(_mm_cmplt_ss(_mm_set_ss(read<float>(image,0x1408cc)),_mm_set_ss(magnitude)),_mm_set_ss(fade)));
        drawing::setStrokeWidth_74a60(c,alpha);const auto displacement=fromDouble(double(difference)*(double(read<float>(u,0x18))*read<double>(image,0x140910)));
        translateCanvas_74b40(c,displacement,0);selected=read<std::uint64_t>(s,0x350);
    }
    const auto page=read<std::uint32_t>(s,0x2e0+(selected<<4));
    if(page<5)d.pages.category_12b20(d.pages.context,s,u,manager,page,elapsed);
    else if(page==5)profiles(s,u,manager,registry,d);
    endLayout_105b0(u,s,image);
    if(read<std::uint8_t>(s,0x268)) {
        write(s,0x2d8,fromDouble(double(read<float>(s,0x2d8))+elapsedDouble/read<double>(image,0x140970)));auto *c=canvas(u);saveCanvas_73a70(c);translateCanvas_74b40(c,read<float>(s,0x2d0),read<float>(s,0x2d4));
        const auto progress=read<float>(s,0x2d8);
        if(progress>read<float>(image,0x1408d0))write(s,0x2d8,1.0f);
        else { const auto smooth=recovered_smooth_a280(progress,image);drawing::setStrokeWidth_74a60(c,smooth);scaleCanvas_74d40(c,smooth,smooth); }
        drawing::setFontSize_79610(c,read<float>(image,0x140940));const auto *message=reinterpret_cast<const char*>(s+0x26a);
        const auto messageWidth=drawing::textBounds_7ae90(c,0,0,message,nullptr,nullptr,image,control.fonts);
        float toast[4];recovered_rect_a070(toast,fromDouble(double(messageWidth)*read<double>(image,0x140978)+read<double>(image,0x140980)),read<float>(image,0x14098c),add(messageWidth,read<float>(image,0x140988)),20);
        gray(c,read<float>(image,0x140990),image);std::memcpy(copy,toast,16);ui::fillRoundedRect_10a60(u,copy,read<float>(image,0x140934),image,control.fonts);
        gray(c,read<float>(image,0x140930),image);std::memcpy(copy,toast,16);ui::drawAlignedText_10cb0(u,copy,1,0,message,image,control.fonts);restoreCanvas_749a0(c);write(s,0x268,std::uint8_t(0));
    } else write(s,0x2d8,0.0f);
    restoreCanvas_749a0(savedCanvas);
    write(s,0x4c0,maximum(0,add(sub(float(read<std::int32_t>(s,0x260)),read<float>(u,0x1c)),read<float>(image,0x1408fc))));
    if(modalVisible_16c80(s)) {
        saveCanvas_73a70(savedCanvas);const auto alpha=read<float>(s,0x418);write(s,0x4ac,sub(read<float>(s,0x4ac),read<float>(s,0x4bc)));fadeBackdrop_128c0(u,alpha,d);resetLayout_10360(s);
        float modal[4];std::memcpy(modal,panel,16);
        if(modal[2]>read<float>(image,0x140994)) { modal[0]=fromDouble(double(modal[0])+double(add(modal[2],read<float>(image,0x140998)))*read<double>(image,0x140938));modal[2]=read<float>(image,0x140994); }
        pushLayout_10380(s,modal,read<float>(image,0x1408f8),read<float>(image,0x1408fc));d.pages.modal_16ca0(d.pages.context,s,u);endLayout_105b0(u,s,image);restoreCanvas_749a0(savedCanvas);
    }
    consumeClick_11270(s);write(s,0x4c9,read<std::uint8_t>(s,0x4c8));write(s,0x498,read<double>(u,8));
}
void clearInteraction_12a90(std::uint8_t *s) { write(s,0x370,std::uint32_t(0));write(s,0x4c8,std::uint8_t(0)); }
std::uint8_t closeRequested_12ab0(std::uint8_t *s) { return read<std::uint8_t>(s,0x4cb); }
std::uint8_t viewportIntersects_12ac0(std::uint8_t *s,std::uint8_t *u,const float *r) { float viewport[4],copy[4];recovered_rect_a070(viewport,0,read<float>(s,0x4bc),read<float>(u,0x18),read<float>(u,0x1c));std::memcpy(copy,r,16);return intersectsRect_a0e0(viewport,copy); }
}
