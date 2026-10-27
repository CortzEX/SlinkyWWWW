#ifndef SLINKY_SHARE_22C75FF64F57F4F12B27
#define SLINKY_SHARE_22C75FF64F57F4F12B27
#include "DecodedCrtServices.hpp"
#include <cstddef>
namespace reconstruction::crt_service {
// Callback tokens in recovered images are data. The caller supplies actual
// callable equivalents of the separately reconstructed comparator bodies.
struct ComparatorBinding {std::uint64_t token;Compare callable;};
struct ExitBinding {std::uint64_t token;ExitCallback callable;};
struct BoundServices {
    Context services;
    const ComparatorBinding *comparators=nullptr;
    std::size_t comparatorCount=0;
    const ExitBinding *exitCallbacks=nullptr;
    std::size_t exitCount=0;
    Compare comparator(std::uint64_t token) const {
        for(std::size_t i=0;i<comparatorCount;++i)
            if(comparators[i].token==token)return comparators[i].callable;
        return nullptr;
    }
    ExitCallback exitCallback(std::uint64_t token) const {
        for(std::size_t i=0;i<exitCount;++i)
            if(exitCallbacks[i].token==token)return exitCallbacks[i].callable;
        return nullptr;
    }
    bool resolve(std::uint64_t rva,const std::uint64_t *a,std::uint64_t &result) const {
        auto pointer=[](std::uint64_t value){return reinterpret_cast<void *>(std::uintptr_t(value));};
        switch(rva) {
        case 0x13d0b0:
            result=std::uintptr_t(copy_13d0b0(services,static_cast<char *>(pointer(a[0])),
                static_cast<const char *>(pointer(a[1])),a[2]));return true;
        case 0x13d0a0:
            result=std::uint32_t(compare_13d0a0(services,static_cast<const char *>(pointer(a[0])),
                static_cast<const char *>(pointer(a[1]))));return true;
        case 0x13d0d0:
            result=std::uint64_t(clock_13d0d0(services,static_cast<std::int64_t *>(pointer(a[0]))));return true;
        case 0x13d0e0: {
            const auto callback=comparator(a[4]);if(!callback)return false;
            result=std::uintptr_t(search_13d0e0(services,pointer(a[0]),pointer(a[1]),a[2],a[3],callback));return true;
        }
        case 0x13d0f0: {
            const auto callback=comparator(a[3]);if(!callback)return false;
            sort_13d0f0(services,pointer(a[0]),a[1],a[2],callback);result=0;return true;
        }
        case 0x13d030: {
            const auto callback=exitCallback(a[1]);if(!callback)return false;
            result=std::uint32_t(registerExit_13d030(services,pointer(a[0]),callback));return true;
        }
        default:return false;
        }
    }
};
}
#endif // SLINKY_SHARE_22C75FF64F57F4F12B27
