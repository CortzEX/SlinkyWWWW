// Runtime-observed native RVAs C220/C290/4C7B0; provenance and limits are in
// reports/GuiOrdinaryConsumerAudit.json. Captured values are not defaults.
#include "GuiProfileActions.hpp"
#include <bit>
namespace reconstruction::gui {
std::uint32_t deleteProfile_c220(const char *name,const configuration::Dependencies &d) {
    std::uint16_t *path;
    auto status=configuration::initializePath_4c590(&path,d);
    if(status)return status;
    status=configuration::appendPath_4c610(&path,d.image+0x13ec08,d);
    if(!status)status=configuration::appendPath_4c610(&path,d.image+0x13ec30,d);
    if(!status)status=configuration::appendPath_4c610(&path,
        reinterpret_cast<const std::uint8_t *>(name),d);
    if(!status)status=configuration::deletePath_4c780(&path,d);
    configuration::releasePath_4cd20(&path,d);
    return status;
}
std::uint32_t exploreDirectory_4c7b0(std::uint16_t **storedPath,const ProfileActionDependencies &d) {
    // Native loads the path before the service and compares its full RAX as
    // signed 64-bit. A DWORD truncation would change high-bit return cases.
    const auto *path=*storedPath;
    const auto result=d.directoryService(d.context,0xdcdbe0,0,
        reinterpret_cast<const std::uint16_t *>(d.paths.image+0x156ff0),
        path,0,0,1);
    return std::bit_cast<std::int64_t>(result)>=0x21?0:0xfa0;
}
std::uint32_t openProfileDirectory_c290(const ProfileActionDependencies &d) {
    std::uint16_t *path;
    auto status=configuration::initializePath_4c590(&path,d.paths);
    if(status)return status;
    status=configuration::appendPath_4c610(&path,d.paths.image+0x13ec08,d.paths);
    if(!status)status=configuration::appendPath_4c610(&path,d.paths.image+0x13ec30,d.paths);
    if(!status)status=exploreDirectory_4c7b0(&path,d);
    configuration::releasePath_4cd20(&path,d.paths);
    return status;
}
}
