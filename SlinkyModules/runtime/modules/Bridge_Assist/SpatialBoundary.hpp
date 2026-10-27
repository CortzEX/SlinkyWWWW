#ifndef SLINKY_SHARE_CD64DB488C387F810C07
#define SLINKY_SHARE_CD64DB488C387F810C07
#include "../../shared/OwnedNativeBindings.hpp"
#include <cstdint>
namespace reconstruction::Bridge_Assist {
// Typed calls preserve the fifth native stack argument omitted by the old test
// adapter. Both targets now call concrete recovered bodies with borrowed state.
struct SpatialBoundary {
 native_binding::Context& native;
 void movementVector(double*out,std::uint64_t rotation,float forward,float strafe,float speed)const{native_state::movementVector(out,rotation,forward,strafe,speed,native.image);}
 std::uint64_t worldBlockAt(std::uint64_t game,std::uint64_t world,std::int32_t x,std::int32_t y,std::int32_t z)const{return game_access::worldBlockAt(reinterpret_cast<GameAccessBridge*>(game),world,std::bit_cast<std::uint32_t>(x),std::bit_cast<std::uint32_t>(y),std::bit_cast<std::uint32_t>(z));}
};
}
#endif // SLINKY_SHARE_CD64DB488C387F810C07
