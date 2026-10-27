#ifndef SLINKY_SHARE_6DBF483B0BE5E985B9D7
#define SLINKY_SHARE_6DBF483B0BE5E985B9D7
#include "../../native/verified/module_surface.hpp"
#include "../../native/verified/module_format.hpp"
namespace fake_lag {
void renderSettings(std::uint64_t ui,std::uint64_t layout,std::uint8_t *image,const BoundSurfaceUiDependencies &);
void serializeConfig(SettingsContext &,std::uint8_t *image,const SurfaceSettingsDependencies &);
void writeStatus(FormatState *,char *destination,const std::uint8_t *image,const char *const *labels);
}
#endif // SLINKY_SHARE_6DBF483B0BE5E985B9D7
