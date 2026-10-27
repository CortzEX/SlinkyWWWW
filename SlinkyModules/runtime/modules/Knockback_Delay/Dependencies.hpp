#ifndef SLINKY_SHARE_EBCC92369978FA0FCCF3
#define SLINKY_SHARE_EBCC92369978FA0FCCF3
#include <cstdint>
#include "../Aim_Assist/Support.hpp"
#include "../../shared/Geometry.hpp"
// Each endpoint has one named native role. The callback bodies contain the
// module algorithms. Unbound endpoints are listed in the module report.
namespace knockback_delay {
using Word = std::uint64_t;
struct Endpoint {
    void *context;
    Word (*function)(void *, Word, Word, Word, Word);
    Word operator()(Word a, Word b, Word c, Word d) const { return function(context, a, b, c, d); }
};
struct Dependencies {
    Endpoint distanceSquared; // 0x94b0
    Endpoint rotationTo; // 0x9f80
    Endpoint randomBounds; // 0xa050
    Endpoint wrapAngle; // 0xa210
    Endpoint randomGate; // 0xaa30
    Endpoint entityPosition; // 0x23030
    Endpoint entityRotation; // 0x23170
    Endpoint entityId; // 0x23720
    Endpoint entityOnGround; // 0x23780
    Endpoint worldPlayers; // 0x24600
    Endpoint listSize; // 0x24e50
    Endpoint listElement; // 0x24e80
    Endpoint velocityPacket; // 0x266b0
    Endpoint velocityEntityId; // 0x266f0
    Endpoint relativeMovePacket; // 0x26a30
    Endpoint headLookPacket; // 0x26a90
    Endpoint teleportPacket; // 0x26ad0
    Endpoint attackInput; // 0x29080
    Endpoint weaponAllowed; // 0x380b0
    Endpoint sameJavaObject; // 0x800000c0
};
}
namespace knockback_delay {
}

namespace knockback_delay {
void update(std::uint8_t *,std::uint8_t *,const Dependencies &);
void packet(std::uint8_t *,std::uint8_t *,const Dependencies &);
}

namespace knockback_delay { void bindKnown(Dependencies &,aim_assist::Runtime &); }
#endif // SLINKY_SHARE_EBCC92369978FA0FCCF3
