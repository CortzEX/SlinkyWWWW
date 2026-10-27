#ifndef SLINKY_SHARE_D766BCB5917DB0D0CF04
#define SLINKY_SHARE_D766BCB5917DB0D0CF04
#include "../../native/verified/Friends_actions.hpp"
#include "../../native/verified/Timer.hpp"
namespace reconstruction::friends {
using CommandEndpoint = std::uint64_t (*)(std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t,
                                          std::uint64_t, std::uint64_t);
struct CommandDependencies {
    CommandEndpoint invoke;
    const ListMemoryDependencies *memory;
};
struct NameSlice {
    const char *data;
    std::uint64_t length;
};
struct NearbyArguments {
    std::uint64_t radius, reserved;
    std::uint8_t replace;
};
static_assert(sizeof(NameSlice) == 16);
static_assert(offsetof(NearbyArguments, replace) == 16);
std::uint64_t resolveNamePrefix(TimerGame *, const NameSlice *, FriendRecord *, char *name,
                                const std::uint8_t *stateImage, const CommandDependencies &);
std::uint64_t addByName(TimerGame *, const NameSlice *, std::uint8_t *stateImage,
                        const CommandDependencies &);
std::uint64_t removeByName(TimerGame *, const NameSlice *, std::uint8_t *stateImage,
                           const CommandDependencies &);
std::uint64_t addNearby(TimerGame *, const NearbyArguments *, std::uint8_t *stateImage,
                        const CommandDependencies &);
std::uint64_t clearAll(TimerGame *, std::uint8_t *stateImage, const CommandDependencies &);
} // namespace reconstruction::friends
#endif // SLINKY_SHARE_D766BCB5917DB0D0CF04
