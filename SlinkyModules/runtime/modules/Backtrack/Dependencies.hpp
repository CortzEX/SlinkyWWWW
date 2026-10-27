#ifndef SLINKY_SHARE_0EB8E8FCC3B97108779A
#define SLINKY_SHARE_0EB8E8FCC3B97108779A
#include <cstdint>
#include "../Aim_Assist/Support.hpp"
#include "../../shared/Geometry.hpp"
// Each endpoint has one named native role. The callback bodies contain the
// module algorithms. Unbound endpoints are listed in the module report.
namespace backtrack {
using Word = std::uint64_t;
struct Endpoint {
    void *context;
    Word (*function)(void *, Word, Word, Word, Word);
    Word operator()(Word a, Word b, Word c, Word d) const { return function(context, a, b, c, d); }
};
struct GraphicsEndpoint {
    void *context;
    Word (*function)(void *, Word, Word, Word, Word, Word);
    Word operator()(Word target, Word a, Word b, Word c, Word d) const { return function(context, target, a, b, c, d); }
};
struct Dependencies {
    Endpoint positionModeIsZero; // 0x23020
    Endpoint entityPosition; // 0x23030
    Endpoint entityRotation; // 0x23170
    Endpoint entityId; // 0x23720
    Endpoint entityTicks; // 0x23760
    Endpoint lastAttackerTime; // 0x239d0
    Endpoint entityHurtTime; // 0x239f0
    Endpoint serverPosition; // 0x24160
    Endpoint velocityPacket; // 0x266b0
    Endpoint velocityEntityId; // 0x266f0
    Endpoint relativeMovePacket; // 0x26a30
    Endpoint relativeMoveEntityId; // 0x26a70
    Endpoint headLookPacket; // 0x26a90
    Endpoint teleportPacket; // 0x26ad0
    Endpoint explosionPacket; // 0x26b10
    Endpoint attackInput; // 0x29080
    Endpoint publishBacktrackPosition; // 0x369d0
    Endpoint backtrackMetric; // 0x36cf0
    Endpoint updateBacktrackPosition; // 0x36d80
    Endpoint activateBacktrack; // 0x36f60
    Endpoint weaponAllowed; // 0x380b0
    Endpoint entityRelativePacket; // 0x26800
    Endpoint relativeEntityId; // 0x26840
    Endpoint relativeX; // 0x26860
    Endpoint relativeY; // 0x26880
    Endpoint relativeZ; // 0x268a0
    Endpoint relativeYaw; // 0x268c0
    Endpoint relativeHasRotation; // 0x26900
    Endpoint entityTeleportPacket; // 0x26930
    Endpoint teleportEntityId; // 0x26970
    Endpoint teleportX; // 0x26990
    Endpoint teleportY; // 0x269b0
    Endpoint teleportZ; // 0x269d0
    Endpoint teleportYaw; // 0x269f0
    Endpoint beginBox, drawFilledBox, drawWireBox, endBox; // 293c0,29400,29430,295a0
    GraphicsEndpoint graphics; // external engine target plus argument bits; render order remains explicit
};
}
namespace backtrack {
void packet(uint8_t *event,uint8_t *image,const Dependencies &dependencies);
void render(uint8_t *event,uint8_t *image,const Dependencies &dependencies);
void update(uint8_t *event,uint8_t *image,const Dependencies &dependencies);
}
namespace backtrack {
double metric(const double *,const double *,const double *);
bool activate(aim_assist::Frame &,aim_assist::EntityRef,const double *,std::uint8_t *);
void updatePosition(const double *,float,std::uint8_t *,const aim_assist::Runtime &);
void publishPacket(std::uint8_t *,std::uint8_t,std::uint8_t *,const Dependencies &);
struct LocalBindings { aim_assist::Runtime &runtime; Dependencies &dependencies; };
void bindLocal(Dependencies &,LocalBindings &);
}

namespace backtrack { void bindKnown(Dependencies &,aim_assist::Runtime &); }

#include "../Backtrack/BoxRender.hpp"
namespace backtrack { void bindRender(Dependencies &,box_render::Context &); }
#endif // SLINKY_SHARE_0EB8E8FCC3B97108779A
