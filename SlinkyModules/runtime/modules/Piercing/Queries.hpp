#ifndef SLINKY_SHARE_85188B6FD87E87371A63
#define SLINKY_SHARE_85188B6FD87E87371A63
#include "../../native/verified/Timer.hpp"
#include <cstdint>

namespace reconstruction::piercing {
// Native access helpers stay typed at the Java/weapon boundaries.
struct QueryDependencies {
    std::uint64_t (*weaponAllowed)(GameAccessBridge *, std::uintptr_t);    // 0x380b0, tests AL
    std::uintptr_t (*resolvePlayer)(GameAccessBridge *, std::uintptr_t);   // 0x24120
    std::uint64_t (*classification)(GameAccessBridge *, std::uintptr_t);   // 0x2acb0
    std::int32_t (*hurtTime)(GameAccessBridge *, std::uintptr_t);          // 0x239f0
    float (*health)(GameAccessBridge *, std::uintptr_t);                   // 0x23a40
    std::uint32_t (*counter)(GameAccessBridge *, std::uintptr_t);          // 0x23760
    std::uint32_t (*lastAttackerTime)(GameAccessBridge *, std::uintptr_t); // 0x23720
};
// The returned 0/1/2 decisions retain the native ranking convention.
std::uint32_t rankTargetPair(TimerGame *, std::uintptr_t first, std::uintptr_t second,
                             std::uint8_t insideBoundingBox, const std::uint8_t *stateImage,
                             const QueryDependencies &);
// The native helper changes AL only after the weapon query. Its consumer tests AL.
std::uint64_t shouldPierceBlocks(TimerGame *, const std::uint8_t *stateImage, const QueryDependencies &);
} // namespace reconstruction::piercing
#endif // SLINKY_SHARE_85188B6FD87E87371A63
