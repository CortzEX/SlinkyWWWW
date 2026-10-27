#ifndef SLINKY_SHARE_CEF54C3AC1DB96B217E0
#define SLINKY_SHARE_CEF54C3AC1DB96B217E0
#include "ConfigurationPersistence.hpp"
#include "../native/verified/module_format.hpp"
#include "../native/verified/module_list_storage.hpp"

namespace reconstruction::configuration {
using ProfileCompare=std::int32_t(*)(void*,const void*,const void*);
struct FileProfile {const char *name;std::uint64_t modificationAgeSeconds;};
using FileProfileCallback=std::uint32_t(*)(void*,const FileProfile*,void*);
// These are actual platform/protected service contracts. The thread filename
// buffer is explicitly borrowed by the caller; there is no hidden TLS frame.
struct ProfileFileServices {
    void *context;
    Word (*findFirst)(void*,const std::uint16_t*,std::uint8_t*findData);
    void (*systemTime)(void*,std::uint64_t*fileTime);
    char *(*threadFilename)(void*);
    std::int32_t (*findNext)(void*,Word,std::uint8_t*findData);
    void (*findClose)(void*,Word);
    std::uint64_t (*formatOptions)(void*);
    std::int32_t (*formatNarrow)(void*,std::uint64_t,char*,std::uint64_t,
        std::uint64_t,const char*,Word,const Word*arguments);
};
struct ProfileManagerDependencies {
    const Dependencies &paths;
    const ProfileFileServices &files;
    const ListMemoryDependencies &memory;
    FormatState &format;
    void *context;
    void (*copyString_13d0b0)(void*,char*,const char*,std::uint64_t);
    std::int32_t (*compareString_13d0a0)(void*,const char*,const char*);
    void (*sort_13d0f0)(void*,void*,std::uint64_t,std::uint64_t,ProfileCompare,void*);
    void *(*find_13d0e0)(void*,const void*,const void*,std::uint64_t,
        std::uint64_t,ProfileCompare,void*);
};
std::int32_t compareProfileName_eca0(const void*,const void*,const ProfileManagerDependencies&);
std::int32_t compareProfileAge_ee70(const void*,const void*,const ProfileManagerDependencies&);
std::uint32_t collectProfile_ecb0(const FileProfile*,void*collection,const ProfileManagerDependencies&);
std::uint32_t refreshProfiles_ead0(std::uint8_t*profiles,const ProfileManagerDependencies&);
std::int32_t formatFilename_4c9d0(char*,const std::uint16_t*,const ProfileManagerDependencies&);
std::uint32_t enumerateFiles_4c800(std::uint16_t**path,void*user,
    FileProfileCallback,void*callbackContext,const ProfileManagerDependencies&);
std::uint32_t enumerateProfiles_c320(void*user,FileProfileCallback,
    void*callbackContext,const ProfileManagerDependencies&);
}
#endif // SLINKY_SHARE_CEF54C3AC1DB96B217E0
