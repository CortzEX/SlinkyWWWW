#ifndef SLINKY_SHARE_27F2A8BBC1AE5D5B7462
#define SLINKY_SHARE_27F2A8BBC1AE5D5B7462
#include "Fast_Place.hpp"

struct FastPlaceAccessContext {
    const PlacementPosition *directions;
    RandomState *random;
    const double *clock;
    const RandomPolicyConstants *policy;
};
static_assert(sizeof(FastPlaceAccessContext) == 32);

extern "C" {
__declspec(dllexport) void recovered_bind_fast_place_access(FastPlaceDependencies *, const FastPlaceAccessContext *);
__declspec(dllexport) void recovered_fast_place_adjacent_position(PlacementPosition *, GameAccessBridge *, std::uintptr_t hit, const FastPlaceAccessContext *);
__declspec(dllexport) void recovered_fast_place_read_box(PlacementBox *, GameAccessBridge *, std::uintptr_t box);
__declspec(dllexport) std::int32_t recovered_fast_place_press_count(GameAccessBridge *, std::uintptr_t key);
__declspec(dllexport) void recovered_fast_place_increment_presses(GameAccessBridge *, std::uintptr_t key);
}
#endif // SLINKY_SHARE_27F2A8BBC1AE5D5B7462
