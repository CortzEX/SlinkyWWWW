#include "Item_Use_Fix_typed.hpp"
#include "module_access_helpers.hpp"

namespace {
std::uintptr_t controller(GameAccessBridge *bridge,std::uintptr_t client) {
    return recovered_access_helper(bridge,0x22df0,client,0,0);
}
std::uint8_t breaking_block(GameAccessBridge *bridge,std::uintptr_t controller) {
    return static_cast<std::uint8_t>(recovered_access_helper(bridge,0x27e90,controller,0,0));
}
void set_breaking_block(GameAccessBridge *bridge,std::uintptr_t controller,std::uint32_t value) {
    recovered_access_helper(bridge,0x27eb0,controller,value,0);
}
}
extern "C" __declspec(dllexport) void recovered_bind_item_use_fix_access(ItemUseFixDependencies *access) {
    *access={controller,breaking_block,set_breaking_block};
}

// 0x42b80 retains the captured game and controller, refreshing the bridge
// between queries and clearing only when the original predicate's AL is nonzero.
extern "C" __declspec(dllexport) void recovered_item_use_fix_typed_before(ItemUseFixEvent *event,
    ItemUseFixState *state,const ItemUseFixDependencies *access) {
    if (event->cancelled!=0) return;
    auto *game=event->game;
    const auto controller=access->controller(game->bridge,game->client);
    const auto restore=access->breaking_block(game->bridge,controller)!=0;
    state->restore_breaking=static_cast<std::uint8_t>(restore);
    if (restore) access->set_breaking_block(game->bridge,controller,0);
}

// 0x42be0 checks saved state before touching the event. The state sent to
// the setter is read again after querying the current controller.
extern "C" __declspec(dllexport) void recovered_item_use_fix_typed_after(ItemUseFixEvent *event,
    ItemUseFixState *state,const ItemUseFixDependencies *access) {
    if (state->restore_breaking!=1 || event->cancelled!=0) return;
    auto *game=event->game;
    const auto controller=access->controller(game->bridge,game->client);
    access->set_breaking_block(game->bridge,controller,state->restore_breaking);
}
