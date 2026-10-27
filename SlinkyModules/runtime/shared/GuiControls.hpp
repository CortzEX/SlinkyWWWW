#ifndef SLINKY_SHARE_8A48E95CE0C0C89845D6
#define SLINKY_SHARE_8A48E95CE0C0C89845D6
#include "GuiCanvas.hpp"
#include "UiRuntime.hpp"
namespace reconstruction::gui {
struct ControlDependencies {
    const std::uint8_t *image;
    const drawing::FontDependencies &fonts;
    const float *iconOrigins; // Borrowed table pointed to by image RVA0x140868.
    std::uint64_t closeCallback; // Native callback word for RVA0x117F0; never executed here.
    void *context;
    void (*copyTooltip_13d0b0)(void*,char*,const char*,std::uint64_t);
    void (*openDialog_16820)(void*,std::uint8_t*,std::uint64_t,std::uint64_t,const char*);
};
void resetLayout_10360(std::uint8_t*);
void pushLayout_10380(std::uint8_t*,float*,float,float);
void pushScissor_104f0(std::uint8_t*,std::uint8_t*,float*,float,float,const std::uint8_t*);
float endLayout_105b0(std::uint8_t*,std::uint8_t*,const std::uint8_t*);
void setColumns_106b0(std::uint8_t*,std::int32_t,const std::uint8_t*);
void autoColumns_10780(std::uint8_t*,float,const std::uint8_t*);
void fillRectangle_10a10(std::uint8_t*,const float*,const drawing::FontDependencies&);
void drawIcon_10ba0(std::uint8_t*,const float*,std::uint32_t,float,const ControlDependencies&);
float measuredText_10da0(std::uint8_t*,float*,std::uint32_t,std::uint32_t,const char*,const char*,const ControlDependencies&);
void drawCaret_10e70(std::uint8_t*,const float*,const float*,float,float,const ControlDependencies&);
std::uint8_t hovered_11180(std::uint8_t*,const float*);
std::uint8_t clicked_111f0(std::uint8_t*,const float*);
void consumeClick_11270(std::uint8_t*);
void activate_11290(std::uint8_t*,std::uint64_t,std::uint64_t);
std::uint8_t active_112b0(std::uint8_t*,std::uint64_t);
void activateText_112d0(std::uint8_t*,std::uint64_t,std::uint64_t);
std::uint8_t textActive_11340(std::uint8_t*,std::uint64_t);
void finishText_11370(std::uint8_t*);
char *consumeSubmitted_11390(std::uint8_t*);
char *textBuffer_113d0(std::uint8_t*);
void tabs_113f0(std::uint8_t*,std::uint8_t*,float,const ControlDependencies&);
void requestClose_117f0(std::uint8_t*);
void tooltip_14cb0(std::uint8_t*,std::uint8_t*,const char*,std::int32_t,std::int32_t,const ControlDependencies&);
std::uint8_t textButton_16330(std::uint8_t*,std::uint8_t*,const float*,std::uint64_t,std::uint64_t);
void textEntry_16380(std::uint8_t*,std::uint8_t*,const float*,const ControlDependencies&);
void alignedTextEntry_16430(std::uint8_t*,std::uint8_t*,const float*,std::uint32_t,const ControlDependencies&);
void filterNumber_164f0(char*,std::uint32_t);
void filterProfileName_13ad0(char*,std::uint32_t);
std::uint8_t modalVisible_16c80(std::uint8_t*);
std::uint8_t modalAllows_16c90(std::uint8_t*);
}
#endif // SLINKY_SHARE_8A48E95CE0C0C89845D6
