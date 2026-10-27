#ifndef SLINKY_SHARE_910DA9095F2F1D477AA5
#define SLINKY_SHARE_910DA9095F2F1D477AA5
#include <cstdint>
#include "../Aim_Assist/Support.hpp"
#include "../../shared/Geometry.hpp"
// Each endpoint has one named native role. The callback bodies contain the
// module algorithms. Unbound endpoints are listed in the module report.
namespace timer_range {
using Word = std::uint64_t;
struct Endpoint {
    void *context;
    Word (*function)(void *, Word, Word, Word, Word);
    Word operator()(Word a, Word b, Word c, Word d) const { return function(context, a, b, c, d); }
};
struct Dependencies {
    Endpoint clientTimer; // 0x22c70
    Endpoint clientOptions; // 0x22cf0
    Endpoint mouseOver; // 0x22e10
    Endpoint refreshMouseOver; // 0x22eb0
    Endpoint positionModeIsZero; // 0x23020
    Endpoint entityPosition; // 0x23030
    Endpoint entityRotation; // 0x23170
    Endpoint entityVelocity; // 0x23550
    Endpoint entityOnGround; // 0x23780
    Endpoint entityHurtTime; // 0x239f0
    Endpoint movementSpeed; // 0x23b40
    Endpoint usingItem; // 0x23f90
    Endpoint serverPosition; // 0x24160
    Endpoint serverInterpolationTicks; // 0x24200
    Endpoint hitType; // 0x24b50
    Endpoint useItemKey; // 0x24f90
    Endpoint jumpKey; // 0x25080
    Endpoint forwardKey; // 0x250d0
    Endpoint backKey; // 0x25120
    Endpoint leftKey; // 0x25170
    Endpoint rightKey; // 0x251c0
    Endpoint attackKey; // 0x25270
    Endpoint updateKey; // 0x25380
    Endpoint keyPressed; // 0x25430
    Endpoint setKeyPressed; // 0x25460
    Endpoint setTimerSpeed; // 0x259c0
    Endpoint setTimerPartialTicks; // 0x25a10
    Endpoint heldItem; // 0x28a50
    Endpoint isBlockingItem; // 0x28ac0
    Endpoint worldRayClear; // 0x29000
    Endpoint attackInput; // 0x29080
    Endpoint weaponAllowed; // 0x380b0
    Endpoint sine; // 0xb1cf0
    Endpoint cosine; // 0xb3590
    Endpoint hypotenuse; // 0x13cfd0
};
enum class Mode : std::uint32_t { Regular = 0, Legit = 1 };
double *movementPrediction(double *, Word, float, float, float, std::uint8_t *, const Dependencies &); // native 0x29290
}
namespace timer_range {
void sampleMovementKeys(uint64_t game,uint64_t settings,uint8_t *image,const Dependencies &dependencies);
void beginFreeze(uint8_t *ctx,uint8_t *image,const Dependencies &dependencies);
void onTick(uint8_t *event,uint8_t *image,const Dependencies &dependencies);
void onPacket(uint8_t *event,uint8_t *image,const Dependencies &dependencies);
void onDisabled(uint8_t *event,uint8_t *image,const Dependencies &dependencies);
void onRotationFrame(uint8_t *event,uint8_t *image,const Dependencies &dependencies);
}

namespace timer_range { void bindKnown(Dependencies &,aim_assist::Runtime &); }

namespace timer_range { std::uint8_t isFrozen(const std::uint8_t *image); } // native 0x42c30, low-byte return
#endif // SLINKY_SHARE_910DA9095F2F1D477AA5
