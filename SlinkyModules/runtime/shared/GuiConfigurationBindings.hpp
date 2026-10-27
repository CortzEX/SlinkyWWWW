#ifndef SLINKY_SHARE_465651A787E6BF8EC143
#define SLINKY_SHARE_465651A787E6BF8EC143
#include "GuiRuntime.hpp"
#include "ProfileManager.hpp"
namespace reconstruction::gui {
// Return an ordinary dependency value. Its context and all referenced services
// remain caller-owned; no callbacks recover the current context from globals.
inline ConfigurationCalls configurationCalls(configuration::ProfileManagerDependencies&d){
    using D=configuration::ProfileManagerDependencies;
    return {&d,
      [](void*c,std::uint64_t p){return configuration::refreshProfiles_ead0(reinterpret_cast<std::uint8_t*>(std::uintptr_t(p)),*static_cast<D*>(c));},
      [](void*,std::uint64_t p,std::uint64_t*n){return configuration::profileRecords_eea0(reinterpret_cast<const std::uint8_t*>(std::uintptr_t(p)),n);},
      [](void*,std::uint64_t p){return configuration::profileMetadata_ea90(reinterpret_cast<const std::uint8_t*>(std::uintptr_t(p)));},
      [](void*c,std::uint64_t n,std::uint64_t m){return configuration::loadProfile_be40(reinterpret_cast<const std::uint8_t*>(std::uintptr_t(n)),reinterpret_cast<const std::uint8_t*>(std::uintptr_t(m)),static_cast<D*>(c)->paths);},
      [](void*c,std::uint64_t n,std::uint8_t mode,std::uint64_t m){return configuration::saveProfile_c0b0(reinterpret_cast<const std::uint8_t*>(std::uintptr_t(n)),mode,reinterpret_cast<const std::uint8_t*>(std::uintptr_t(m)),static_cast<D*>(c)->paths);},
      [](void*c){return configuration::currentProfile_c1f0(static_cast<D*>(c)->paths);},
      [](void*c){return configuration::pendingChanges_c200(static_cast<D*>(c)->paths);}
    };
}
}
#endif // SLINKY_SHARE_465651A787E6BF8EC143
