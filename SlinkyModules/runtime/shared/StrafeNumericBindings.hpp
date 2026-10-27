#ifndef SLINKY_SHARE_21371891B1B2D715E909
#define SLINKY_SHARE_21371891B1B2D715E909
#include "DecodedNumericService.hpp"
#include "../native/verified/Strafe.hpp"
namespace reconstruction::strafe {
// Context remains borrowed by this invocation. The legacy callback entry and
// retained evidence keep their original ABI; this entry reloads the native
// encoded 0x13CFD0 cell at the existing motion body's speed call.
void motionNumeric(StrafeEvent *, const StrafeSettings *, const std::uint8_t *,
                   const StrafeConstants *, const StrafeDependencies *,
                   const numeric_service::Context &);
}
#endif // SLINKY_SHARE_21371891B1B2D715E909
