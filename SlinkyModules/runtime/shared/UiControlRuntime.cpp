#include "UiControlRuntime.hpp"
#include "DisplayGeometry.hpp"
#include <cstring>
#include <emmintrin.h>
namespace {
using W=std::uint64_t;
template<class T>T get(const void *p){T v;std::memcpy(&v,p,sizeof v);return v;}
W address(const void *p){return std::uintptr_t(p);}
W dirty(W result,std::uint8_t *image){if(result&0xff)image[0x2f7338]=1;return result;}
}
// These wrappers capture metadata and float STACK words before invoking the
// concrete widget entry. Widget bodies retain explicit caller-owned contracts.
W recovered_ui_checkbox_cef0(W layout,W ui,std::uint8_t *setting,std::uint8_t *image,RecoveredFrameInvoker call){
    return dirty(call(0x13d90,ui,layout,get<W>(setting+0x10),address(setting),address(setting+0x18)),image);
}
W recovered_ui_number_cf30(W layout,W ui,std::uint8_t *setting,std::uint8_t *image,RecoveredFrameInvoker call){
    return dirty(call(0x13f40,ui,layout,get<W>(setting+0x10),get<W>(setting+0x18),address(setting),
        get<std::uint32_t>(setting+0x28),get<std::uint32_t>(setting+0x2c),get<std::uint32_t>(setting+0x20),get<std::uint32_t>(setting+0x24),address(setting+0x30)),image);
}
W recovered_ui_range_cfb0(W layout,W ui,std::uint8_t *setting,std::uint8_t *image,RecoveredFrameInvoker call){
    return dirty(call(0x14580,ui,layout,get<W>(setting+0x18),get<W>(setting+0x20),get<W>(setting+0x28),address(setting),
        get<std::uint32_t>(setting+0x38),get<std::uint32_t>(setting+0x3c),get<std::uint32_t>(setting+0x30),get<std::uint32_t>(setting+0x34),address(setting+0x40),address(setting+0x44)),image);
}
W recovered_ui_choice_d040(W layout,W ui,std::uint8_t *setting,std::uint8_t *image,RecoveredFrameInvoker call){
    return dirty(call(0x14d00,ui,layout,get<W>(setting+0x18),address(setting),get<std::uint32_t>(setting+0x20),get<W>(setting+0x28),address(setting+0x30),setting[0x38]),image);
}
W recovered_ui_color_d0a0(W layout,W ui,std::uint8_t *setting,std::uint8_t *image,RecoveredFrameInvoker call){
    return dirty(call(0x155a0,ui,layout,get<W>(setting),address(setting+8)),image);
}
W recovered_ui_list_d0e0(W layout,W ui,std::uint8_t *setting,std::uint8_t *image,RecoveredFrameInvoker call){
    W first=0,second=0;const auto suggestions=get<W>(setting+0x58);
    if(suggestions)call(suggestions,address(&first),address(&second));
    const auto result=call(0x158e0,ui,layout,get<W>(setting),get<W>(setting+8),get<W>(setting+0x10),
        get<std::uint32_t>(setting+0x18),address(setting+0x20),first,second);
    if(result&0xff){setting[0x60]=1;image[0x2f7338]=1;}return result;
}
W recovered_ui_section_13e90(W layout,W ui,const char *label,std::uint8_t *image,RecoveredFrameInvoker call){
    float rectangle[4];const auto canvas=get<W>(reinterpret_cast<void *>(std::uintptr_t(ui)));
    call(0x10860,address(rectangle),layout,get<std::uint32_t>(image+0x140c80));
    rectangle[1]=_mm_cvtss_f32(_mm_add_ss(_mm_set_ss(rectangle[1]),_mm_set_ss(get<float>(image+0x140c84))));
    float color[4];const auto grey=get<float>(image+0x140c88);
    recovered_color_74150(color,grey,grey,grey,1.0f);
    call(0x74ef0,canvas,address(color));call(0x79610,canvas,get<std::uint32_t>(image+0x140c8c));
    float copy[4];std::memcpy(copy,rectangle,16);
    return call(0x10cb0,ui,address(copy),0,0,address(label));
}
