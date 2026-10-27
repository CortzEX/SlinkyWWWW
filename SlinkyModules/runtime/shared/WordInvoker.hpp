#ifndef SLINKY_SHARE_67FFAB30FC67C3891898
#define SLINKY_SHARE_67FFAB30FC67C3891898
#include <cstdint>
#include <cstddef>
#include <array>

// A non-owning, caller-owned view of a four-payload native call boundary.
// Stack adapters can retain an enclosing callback's wider argument frame.
struct RecoveredWordInvoker {
    void *context;
    std::uint64_t (*invoke)(void *, std::uint64_t, std::uint64_t,
        std::uint64_t, std::uint64_t, std::uint64_t);
    std::uint64_t operator()(std::uint64_t target, std::uint64_t first,
        std::uint64_t second, std::uint64_t third, std::uint64_t fourth) const {
        return invoke(context, target, first, second, third, fourth);
    }
};

// Explicit caller-owned frame for wider Windows x64 GPR/stack payloads.
struct RecoveredFrameInvoker {
    void *context;
    std::uint64_t (*invoke)(void *,std::uint64_t,const std::uint64_t *,std::size_t);
    template<class... Args> std::uint64_t operator()(std::uint64_t target,Args... args) const {
        const std::array<std::uint64_t,sizeof...(Args)> words{std::uint64_t(args)...};
        return invoke(context,target,words.data(),words.size());
    }
};
#endif // SLINKY_SHARE_67FFAB30FC67C3891898
