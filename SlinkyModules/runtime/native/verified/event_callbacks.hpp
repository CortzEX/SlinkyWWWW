#ifndef SLINKY_SHARE_CE936FC3EDED5BDD03DF
#define SLINKY_SHARE_CE936FC3EDED5BDD03DF
#include <cstdint>

using DepBool2 = std::uint8_t (*)(std::uintptr_t, std::uintptr_t);
using DepPtr2 = std::uintptr_t (*)(std::uintptr_t, std::uintptr_t);
using DepInt2 = std::int32_t (*)(std::uintptr_t, std::uintptr_t);

struct Dependencies {
    DepBool2 dep_180023f90;
    DepPtr2 dep_180028a50;
    DepInt2 dep_180025c50;
    DepBool2 dep_180023690;
    DepInt2 dep_1800239d0;
    DepPtr2 dep_180026c80;
    DepPtr2 dep_180026cc0;
};

struct ReachState {
    std::int32_t timer;
    std::int32_t previous_target;
    std::int32_t require_sprint;
    std::int32_t event_type;
    float activation_threshold;
    float reach_value;
};

static_assert(sizeof(Dependencies) == 56);
static_assert(sizeof(ReachState) == 24);
#endif // SLINKY_SHARE_CE936FC3EDED5BDD03DF
