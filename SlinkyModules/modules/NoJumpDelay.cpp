// No Jump Delay

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/No_Jump_Delay.md

#include "../runtime/native/verified/module_surface.hpp"

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/No_Jump_Delay/No_Jump_Delay.cpp
#include "../runtime/native/verified/access_events.hpp"

// lib_win RVA 0x35d50: event 17 callback.
extern "C" __declspec(dllexport) void
recovered_no_jump_delay_35d50(void *event, const AccessDependencies *deps) {
    auto *payload = reinterpret_cast<std::uint64_t *>(access_word(event, 8));
    if (reinterpret_cast<std::uint8_t *>(payload)[0x40] == 1)
        access_call(deps, 0x23b80, payload[0], payload[5]);
}
// END SOURCE modules/No_Jump_Delay/No_Jump_Delay.cpp

// BEGIN SOURCE modules/No_Jump_Delay/No_Jump_Delay_typed.cpp
#ifndef SLINKY_SHARE_E0AE0A95129221F6AACE
#define SLINKY_SHARE_E0AE0A95129221F6AACE
// BEGIN SOURCE native/verified/No_Jump_Delay_typed.hpp
#include "../runtime/native/verified/Timer.hpp"

struct NoJumpDelayEvent {
    std::uintptr_t type;
    TimerGame *game;
};
struct NoJumpDelayDependencies {
    void (*set_jump_delay)(GameAccessBridge *, std::uintptr_t player, std::uint32_t ticks);
};
static_assert(sizeof(NoJumpDelayEvent) == 16);
static_assert(sizeof(NoJumpDelayDependencies) == 8);
extern "C" {
__declspec(dllexport) void recovered_bind_no_jump_delay_access(NoJumpDelayDependencies *);
__declspec(dllexport) void recovered_no_jump_delay_typed_update(NoJumpDelayEvent *,
                                                                const NoJumpDelayDependencies *);
}
class NoJumpDelayModule {
  public:
    static constexpr const char *name = "No Jump Delay";
    static constexpr const char *description = "Removes cooldown when holding jump key.";
    static constexpr std::uint32_t event_type = 17;
    static constexpr std::int32_t event_priority = 100;
    NoJumpDelayDependencies access{};
    NoJumpDelayModule() {
        recovered_bind_no_jump_delay_access(&access);
    }
    void update(NoJumpDelayEvent &event) {
        recovered_no_jump_delay_typed_update(&event, &access);
    }
};
// END SOURCE native/verified/No_Jump_Delay_typed.hpp

#endif // SLINKY_SHARE_E0AE0A95129221F6AACE

#include "../runtime/native/verified/module_access_helpers.hpp"

namespace {
void set_jump_delay(GameAccessBridge *bridge, std::uintptr_t player, std::uint32_t ticks) {
    recovered_access_helper(bridge, 0x23b80, player, ticks, 0);
}
} // namespace
extern "C" __declspec(dllexport) void
recovered_bind_no_jump_delay_access(NoJumpDelayDependencies *access) {
    *access = {set_jump_delay};
}
// 0x35d50 clears the player's cooldown only for the exact ready byte 1.
extern "C" __declspec(dllexport) void
recovered_no_jump_delay_typed_update(NoJumpDelayEvent *event,
                                     const NoJumpDelayDependencies *access) {
    auto *game = event->game;
    if (game->ready == 1)
        access->set_jump_delay(game->bridge, game->player, 0);
}
// END SOURCE modules/No_Jump_Delay/No_Jump_Delay_typed.cpp

#ifndef SLINKY_SHARE_30B9102D8AFC5ACCCC06
#define SLINKY_SHARE_30B9102D8AFC5ACCCC06
// BEGIN SOURCE modules/No_Jump_Delay/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/No_Jump_Delay/Api.hpp

#endif // SLINKY_SHARE_30B9102D8AFC5ACCCC06

// Convenient borrowed-state interface

namespace shareable {
using NoJumpDelay = ::NoJumpDelayModule;
}
