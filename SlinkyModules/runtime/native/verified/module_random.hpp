#ifndef SLINKY_SHARE_DD57C10A36F62979FA0C
#define SLINKY_SHARE_DD57C10A36F62979FA0C
#include <cstdint>

struct RandomState { std::uint32_t words[4]; };
struct RandomConstants { float interval_scale, chance_upper, chance_scale; };
static_assert(sizeof(RandomState) == 16);
static_assert(sizeof(RandomConstants) == 12);

extern "C" {
__declspec(dllexport) std::uint64_t recovered_random_bounds(float low, float high);
__declspec(dllexport) float recovered_random_interval(RandomState *, const RandomConstants *, std::uint64_t bounds);
__declspec(dllexport) std::uint32_t recovered_random_chance(RandomState *, const RandomConstants *, float threshold);
}
#endif // SLINKY_SHARE_DD57C10A36F62979FA0C
