#include "GuiDialogs.hpp"
#include "GuiControls.hpp"
#include "GuiMemory.hpp"
namespace reconstruction::gui {
void openDialog_16820(std::uint8_t*s,std::uint64_t user,std::uint64_t completion,
    const char*format,std::va_list arguments,const DialogDependencies&d){
    ui::finishModal_169c0(s,1,d.image,d.input);
    const auto time=d.clock_4c270(d.context);
    write(s,0x3f8,std::uint64_t(3));write(s,0x400,user);
    write(s,0x408,reinterpret_cast<std::uint64_t>(d.image+0x140f44));
    write(s,0x410,time);const auto zero=_mm_setzero_ps();
    _mm_storeu_ps(reinterpret_cast<float*>(s+0x418),zero);
    write(s,0x428,completion);
    for(std::ptrdiff_t offset=0x430;offset!=0x490;offset+=16)_mm_storeu_ps(reinterpret_cast<float*>(s+offset),zero);
    write(s,0x490,std::uint64_t(0));
    recovered_format_arguments(&d.format,reinterpret_cast<char*>(s+0x430),100,format,arguments);
}
void openDialogText_16820(std::uint8_t*s,std::uint64_t user,std::uint64_t completion,
    const char*format,const char*firstArgument,const DialogDependencies&d){
    // Microsoft x64 va_list is the contiguous native eight-byte argument area.
    // Known page caller supplies exactly one Word; no persistent hidden frame.
    const std::uint64_t words[]{reinterpret_cast<std::uint64_t>(firstArgument)};
    auto arguments=reinterpret_cast<std::va_list>(const_cast<std::uint64_t*>(words));
    openDialog_16820(s,user,completion,format,arguments,d);
}
void openPayloadDialog_168f0(std::uint8_t*s,std::uint64_t title,std::uint64_t user,
    std::uint64_t completion,const void*payload16,std::uint64_t payloadWord,const DialogDependencies&d){
    const auto payload=_mm_loadu_ps(static_cast<const float*>(payload16));
    ui::finishModal_169c0(s,1,d.image,d.input);
    const auto time=d.clock_4c270(d.context);
    write(s,0x3f8,std::uint64_t(4));write(s,0x400,user);write(s,0x408,title);write(s,0x410,time);
    const auto zero=_mm_setzero_ps();_mm_storeu_ps(reinterpret_cast<float*>(s+0x418),zero);
    write(s,0x428,completion);_mm_storeu_ps(reinterpret_cast<float*>(s+0x430),payload);write(s,0x440,payloadWord);
    for(std::ptrdiff_t offset=0x448;offset!=0x498;offset+=16)_mm_storeu_ps(reinterpret_cast<float*>(s+offset),zero);
    activateText_112d0(s,completion,reinterpret_cast<std::uint64_t>(s+0x3f8));finishText_11370(s);
}
}
