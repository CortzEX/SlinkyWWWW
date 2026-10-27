#ifndef SLINKY_SHARE_20DDC575E7B8541DF9DC
#define SLINKY_SHARE_20DDC575E7B8541DF9DC
#include "../../native/verified/Timer.hpp"
#include <cstdint>
namespace reconstruction::ghost_hand {
struct QueryDependencies {
    std::uint64_t (*mousePressed)(TimerGame *);                          // 0x29080, tests AL
    std::uintptr_t (*itemObject)(GameAccessBridge *, std::uintptr_t);    // 0x28a50
    std::int32_t (*itemIdentifier)(GameAccessBridge *, std::uintptr_t);  // 0x25c50
    std::uintptr_t (*resolvePlayer)(GameAccessBridge *, std::uintptr_t); // 0x24120
    std::uint64_t (*classification)(GameAccessBridge *, std::uintptr_t); // 0x2acb0
};
std::uint8_t canInteractThrough(TimerGame *, std::uintptr_t target, const std::uint8_t *stateImage,
                                const QueryDependencies &);
} // namespace reconstruction::ghost_hand
#endif // SLINKY_SHARE_20DDC575E7B8541DF9DC
