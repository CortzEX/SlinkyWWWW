#ifndef SLINKY_SHARE_4579A4F73F95E8A94A43
#define SLINKY_SHARE_4579A4F73F95E8A94A43
#include "StartupRuntime.hpp"
#include "CrtNativeBindings.hpp"
namespace reconstruction::startup {
// The supplied native callback tokens require explicit callable bindings.
// The ordinary initializer/shutdown bodies still use their borrowed image.
struct BoundDependencies {
    const Dependencies &source;
    const crt_service::BoundServices &services;
    Dependencies value;
    BoundDependencies(const Dependencies &original,const crt_service::BoundServices &crt)
        :source(original),services(crt),value{this,callback,lifecycle,registration} {}
    BoundDependencies(const BoundDependencies &)=delete;
    static void callback(void *opaque,Word target) {
        const auto &original=static_cast<BoundDependencies *>(opaque)->source;
        original.callback(original.context,target);
    }
    static void lifecycle(void *opaque,Word module,std::uint32_t reason,Word reserved) {
        const auto &original=static_cast<BoundDependencies *>(opaque)->source;
        original.lifecycle_f4730(original.context,module,reason,reserved);
    }
    static Word registration(void *opaque,Word state,Word token) {
        auto &frame=*static_cast<BoundDependencies *>(opaque);
        Word result;const Word arguments[]{state,token};
        if(frame.services.resolve(0x13d030,arguments,result))return result;
        return frame.source.register_13d030(frame.source.context,state,token);
    }
};
}
#endif // SLINKY_SHARE_4579A4F73F95E8A94A43
