#ifndef SLINKY_SHARE_C91A19FD5B2E64EB10BB
#define SLINKY_SHARE_C91A19FD5B2E64EB10BB
#include "../../native/verified/module_surface.hpp"
#include "../../native/verified/module_format.hpp"
namespace knockback_delay {
void renderSettings(std::uint64_t ui,std::uint64_t layout,std::uint8_t *image,const BoundSurfaceUiDependencies &);
void serializeConfig(SettingsContext &,std::uint8_t *image,const SurfaceSettingsDependencies &);
void writeStatus(FormatState *,char *destination,const std::uint8_t *image);
}
#endif // SLINKY_SHARE_C91A19FD5B2E64EB10BB
