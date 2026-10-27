#ifndef SLINKY_SHARE_3C1BB6D300A6E7AEE69B
#define SLINKY_SHARE_3C1BB6D300A6E7AEE69B
#include "../../native/verified/module_surface.hpp"
#include "../../native/verified/module_format.hpp"
namespace teams {
void renderSettings(std::uint64_t ui,std::uint64_t layout,std::uint8_t *image,const BoundSurfaceUiDependencies &);
void serializeConfig(SettingsContext &,std::uint8_t *image,const SurfaceSettingsDependencies &);
}
#endif // SLINKY_SHARE_3C1BB6D300A6E7AEE69B
