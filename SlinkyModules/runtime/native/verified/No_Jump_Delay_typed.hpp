#ifndef SLINKY_SHARE_E0AE0A95129221F6AACE
#define SLINKY_SHARE_E0AE0A95129221F6AACE
#include "Timer.hpp"

struct NoJumpDelayEvent { std::uintptr_t type; TimerGame *game; };
struct NoJumpDelayDependencies {
    void (*set_jump_delay)(GameAccessBridge *,std::uintptr_t player,std::uint32_t ticks);
};
static_assert(sizeof(NoJumpDelayEvent)==16);
static_assert(sizeof(NoJumpDelayDependencies)==8);
extern "C" {
__declspec(dllexport) void recovered_bind_no_jump_delay_access(NoJumpDelayDependencies *);
__declspec(dllexport) void recovered_no_jump_delay_typed_update(NoJumpDelayEvent *,const NoJumpDelayDependencies *);
}
class NoJumpDelayModule {
public:
    static constexpr const char *name="No Jump Delay";
    static constexpr const char *description="Removes cooldown when holding jump key.";
    static constexpr std::uint32_t event_type=17;
    static constexpr std::int32_t event_priority=100;
    NoJumpDelayDependencies access{};
    NoJumpDelayModule() { recovered_bind_no_jump_delay_access(&access); }
    void update(NoJumpDelayEvent &event) { recovered_no_jump_delay_typed_update(&event,&access); }
};
#endif // SLINKY_SHARE_E0AE0A95129221F6AACE
