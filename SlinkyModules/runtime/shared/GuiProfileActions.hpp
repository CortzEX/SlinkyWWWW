#ifndef SLINKY_SHARE_F2A9941E47BED18D68D2
#define SLINKY_SHARE_F2A9941E47BED18D68D2
// Ordinary C220/C290/4C7B0 instructions from the supplied runtime observation.
// The platform service is explicit; no original protected code is invoked.
#include "ConfigurationPersistence.hpp"
namespace reconstruction::gui {
struct ProfileActionDependencies {
    const configuration::Dependencies &paths;
    void *context;
    std::uint64_t (*directoryService)(void *,std::uint32_t entryRva,
        std::uint64_t owner,const std::uint16_t *operation,
        const std::uint16_t *path,std::uint64_t parameters,
        std::uint64_t directory,std::uint32_t show);
};
std::uint32_t deleteProfile_c220(const char *,const configuration::Dependencies &);
std::uint32_t exploreDirectory_4c7b0(std::uint16_t **,const ProfileActionDependencies &);
std::uint32_t openProfileDirectory_c290(const ProfileActionDependencies &);
}
#endif // SLINKY_SHARE_F2A9941E47BED18D68D2
