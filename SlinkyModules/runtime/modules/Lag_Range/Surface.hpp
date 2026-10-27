#ifndef SLINKY_SHARE_52A406DE7D7C6BA74950
#define SLINKY_SHARE_52A406DE7D7C6BA74950
#include "../../native/verified/module_surface.hpp"
#include "../../native/verified/module_format.hpp"
namespace lag_range {
void renderSettings(std::uint64_t ui,std::uint64_t layout,std::uint8_t *image,const BoundSurfaceUiDependencies &);
void serializeConfig(SettingsContext &,std::uint8_t *image,const SurfaceSettingsDependencies &);
void writeStatus(FormatState *,char *destination,const std::uint8_t *image);
}
#endif // SLINKY_SHARE_52A406DE7D7C6BA74950
