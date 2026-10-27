#include "No_Jump_Delay_typed.hpp"
#include "module_access_helpers.hpp"

namespace {
void set_jump_delay(GameAccessBridge *bridge,std::uintptr_t player,std::uint32_t ticks) {
    recovered_access_helper(bridge,0x23b80,player,ticks,0);
}
}
extern "C" __declspec(dllexport) void recovered_bind_no_jump_delay_access(NoJumpDelayDependencies *access) {
    *access={set_jump_delay};
}
// 0x35d50 clears the player's cooldown only for the exact ready byte 1.
extern "C" __declspec(dllexport) void recovered_no_jump_delay_typed_update(NoJumpDelayEvent *event,
    const NoJumpDelayDependencies *access) {
    auto *game=event->game;
    if (game->ready==1) access->set_jump_delay(game->bridge,game->player,0);
}
