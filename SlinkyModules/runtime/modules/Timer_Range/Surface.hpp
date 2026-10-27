#ifndef SLINKY_SHARE_3DF67E15F2A4A5073FB8
#define SLINKY_SHARE_3DF67E15F2A4A5073FB8
#include "../../native/verified/module_surface.hpp"
#include "../../native/verified/module_format.hpp"
namespace timer_range {
void renderSettings(std::uint64_t ui,std::uint64_t layout,std::uint8_t *image,const BoundSurfaceUiDependencies &);
void serializeConfig(SettingsContext &,std::uint8_t *image,const SurfaceSettingsDependencies &);
void writeStatus(FormatState *,char *destination,const std::uint8_t *image,const char *const *labels);
}
#endif // SLINKY_SHARE_3DF67E15F2A4A5073FB8
