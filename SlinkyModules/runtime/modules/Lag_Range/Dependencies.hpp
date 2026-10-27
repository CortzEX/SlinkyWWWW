#ifndef SLINKY_SHARE_15E3DBAD089DFF1867F4
#define SLINKY_SHARE_15E3DBAD089DFF1867F4
#include <cstdint>
#include "../Aim_Assist/Support.hpp"
#include "../../shared/Geometry.hpp"
// Each endpoint has one named native role. The callback bodies contain the
// module algorithms. Unbound endpoints are listed in the module report.
namespace lag_range {
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
    Endpoint adjustPositionY; // 0x95c0
    Endpoint randomBounds; // 0xa050
    Endpoint smoothRandom; // 0xa510
    Endpoint clientOptions; // 0x22cf0
    Endpoint positionModeIsZero; // 0x23020
    Endpoint entityPosition; // 0x23030
    Endpoint entitySprinting; // 0x23690
    Endpoint entityTicks; // 0x23760
    Endpoint lastAttackerTime; // 0x239d0
    Endpoint entityHurtTime; // 0x239f0
    Endpoint inventory; // 0x23f40
    Endpoint serverPosition; // 0x24160
    Endpoint viewMode; // 0x25310
    Endpoint selectedSlot; // 0x25a60
    Endpoint itemId; // 0x25c50
    Endpoint stackDamage; // 0x25dc0
    Endpoint inventoryItem; // 0x26140
    Endpoint movementPacket; // 0x26350
    Endpoint movementHasPosition; // 0x26390
    Endpoint movementPosition; // 0x26450
    Endpoint attackPacket; // 0x265e0
    Endpoint entityActionPacket; // 0x26620
    Endpoint entityActionCode; // 0x26660
    Endpoint heldItem; // 0x28a50
    Endpoint weaponAllowed; // 0x380b0
    Endpoint beginBox, drawFilledBox, drawWireBox, endBox; // 293c0,29400,29430,295a0
    GraphicsEndpoint graphics; // external engine target plus argument bits; render order remains explicit
};
}
namespace lag_range {
void packet(uint8_t *event,uint8_t *image,const Dependencies &dependencies);
void input(uint8_t *event,uint8_t *image,const Dependencies &dependencies);
void render(uint8_t *event,uint8_t *image,const Dependencies &dependencies);
void update(uint8_t *event,uint8_t *image,const Dependencies &dependencies);
}

namespace lag_range { void bindKnown(Dependencies &,aim_assist::Runtime &); }

#include "../Backtrack/BoxRender.hpp"
namespace lag_range { void bindRender(Dependencies &,box_render::Context &); }
#endif // SLINKY_SHARE_15E3DBAD089DFF1867F4
