#include "StartupReasonRuntime.hpp"
#include <cstring>

namespace reconstruction::startup {
namespace {
template<class T> T read(const void *pointer) {
    T value; std::memcpy(&value,pointer,sizeof value); return value;
}
using SectionEndpoint = std::int32_t (*)(void *);
SectionEndpoint endpoint(const std::uint8_t *cell, Word addend) {
    return reinterpret_cast<SectionEndpoint>(
        std::uintptr_t(read<Word>(cell)+addend));
}
}
std::int32_t NativeServices::initialize(void *section) const {
    const auto *cell=initializeCell ? initializeCell : image+0x33b543;
    return endpoint(cell,Word(0x25a6ac40))(section);
}
std::int32_t NativeServices::destroy(void *section) const {
    const auto *cell=deleteCell ? deleteCell : image+0xbd64d6;
    return endpoint(cell,Word(0)-Word(0x24693085))(section);
}

std::int32_t NativeServices::enter(void *section) const {
    const auto *cell=enterCell ? enterCell : image+0xf94ba9;
    return endpoint(cell,Word(0x7e3634dc))(section);
}
std::int32_t NativeServices::leave(void *section) const {
    const auto *cell=leaveCell ? leaveCell : image+0xfc80e4;
    return endpoint(cell,Word(0x5cbcb3b5))(section);
}
NativeServices::TlsEndpoint NativeServices::resolveTls() const {
    const auto *cell=tlsCell ? tlsCell : image+0xea03ed;
    return reinterpret_cast<TlsEndpoint>(
        std::uintptr_t(read<Word>(cell)+Word(0x300ce5cc)));
}
NativeServices::ErrorEndpoint NativeServices::resolveLastError() const {
    const auto *cell=lastErrorCell ? lastErrorCell : image+0x2cbfb8;
    return reinterpret_cast<ErrorEndpoint>(std::uintptr_t(read<Word>(cell)));
}
void NativeServices::release(void *node) const {
    const auto *cell=freeCell ? freeCell : image+0x2cc178;
    reinterpret_cast<void (*)(void *)>(std::uintptr_t(read<Word>(cell)))(node);
}

Word lifecycle_f4730(std::uint32_t reason,std::uint8_t *image,
                     const NativeServices &services,
                     const ArchitectureOperations &architecture,
                     const CallbackOperations &callbacks) {
    // F473F tests unsigned EDX before any global access.
    if (reason>3) return 1;
    if (reason==2) {
        initializeX87_12ccf0(architecture);
        return 1;
    }
    const auto guard=read<std::uint32_t>(image+0x3065b0);
    if (reason==1) {
        if (!guard) services.initialize(image+0x306588);
        // F484D writes this even if initialization returns a failure status
        // or mutates the guard. No status test precedes the write.
        const std::uint32_t one=1;
        std::memcpy(image+0x3065b0,&one,sizeof one);
        return 1;
    }
    if (guard) {
        services.enter(image+0x306588);
        auto node=read<Word>(image+0x3065f0);
        if (node) {
            // Each reason resolves once before the loop. A service/callback
            // may mutate the cells, but the cached engines remain in use.
            const auto tls=services.resolveTls();
            const auto lastError=services.resolveLastError();
            for (;;) {
                const auto *record=reinterpret_cast<const std::uint8_t *>(std::uintptr_t(node));
                const auto value=tls(read<std::uint32_t>(record));
                const auto error=lastError();
                if (!error && value)
                    callbacks.invoke(callbacks.context,read<Word>(record+8),value);
                // F47A0/F4810 read next only after all preceding calls.
                node=read<Word>(record+16);
                if (!node) break;
            }
        }
        services.leave(image+0x306588);
    }
    if (reason==3) return 1;
    // Reason0 reloads the guard after release (also after its zero-guard
    // initial jump). Only the exact value1 enters process-list cleanup.
    if (read<std::uint32_t>(image+0x3065b0)==1) {
        auto node=read<Word>(image+0x3065f0);
        while (node) {
            const auto *record=reinterpret_cast<const std::uint8_t *>(std::uintptr_t(node));
            const auto next=read<Word>(record+16);  // Retained across free.
            services.release(reinterpret_cast<void *>(std::uintptr_t(node)));
            node=next;
        }
        const Word zero=0;
        std::memcpy(image+0x3065f0,&zero,sizeof zero);
        const std::uint32_t clear=0;
        std::memcpy(image+0x3065b0,&clear,sizeof clear);
        services.destroy(image+0x306588);
    }
    return 1;
}

void BoundLifecycleDependencies::callback(void *opaque,Word target) {
    const auto &source=static_cast<BoundLifecycleDependencies *>(opaque)->source;
    source.callback(source.context,target);
}
void BoundLifecycleDependencies::lifecycle(void *opaque,Word module,
                                         std::uint32_t reason,Word reserved) {
    auto &frame=*static_cast<BoundLifecycleDependencies *>(opaque);
    (void)module; (void)reserved;
    lifecycle_f4730(reason,frame.image,frame.services,frame.architecture,frame.callbacks);
}
Word BoundLifecycleDependencies::registration(void *opaque,Word state,Word callback) {
    const auto &source=static_cast<BoundLifecycleDependencies *>(opaque)->source;
    return source.register_13d030(source.context,state,callback);
}
}
