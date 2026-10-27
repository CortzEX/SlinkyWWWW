// Item Use Fix

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Item_Use_Fix.md

#include "../runtime/native/verified/module_surface.hpp"

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Item_Use_Fix/Item_Use_Fix.cpp
#include "../runtime/native/verified/access_events.hpp"

// lib_win RVA 0x42b80: event 14 callback.
extern "C" __declspec(dllexport) void
recovered_item_use_fix_42b80(void *event, AccessGlobals *globals, const AccessDependencies *deps) {
    if (static_cast<std::uint8_t *>(event)[0x10] != 0)
        return;
    auto *payload = reinterpret_cast<std::uint64_t *>(access_word(event, 8));
    const auto value = access_call(deps, 0x22df0, payload[0], payload[3]);
    globals->state_42b80 = static_cast<std::uint8_t>(
        static_cast<std::uint8_t>(access_call(deps, 0x27e90, payload[0], value)) != 0);
    if (globals->state_42b80)
        access_call(deps, 0x27eb0, payload[0], value);
}

// lib_win RVA 0x42be0: event 15 callback.
extern "C" __declspec(dllexport) void
recovered_item_use_fix_42be0(void *event, AccessGlobals *globals, const AccessDependencies *deps) {
    if (globals->state_42b80 != 1 || static_cast<std::uint8_t *>(event)[0x10] != 0)
        return;
    auto *payload = reinterpret_cast<std::uint64_t *>(access_word(event, 8));
    const auto value = access_call(deps, 0x22df0, payload[0], payload[3]);
    access_call(deps, 0x27eb0, payload[0], value, globals->state_42b80);
}
// END SOURCE modules/Item_Use_Fix/Item_Use_Fix.cpp

// BEGIN SOURCE modules/Item_Use_Fix/Item_Use_Fix_typed.cpp
#ifndef SLINKY_SHARE_6F9A667DF7AD28E2F360
#define SLINKY_SHARE_6F9A667DF7AD28E2F360
// BEGIN SOURCE native/verified/Item_Use_Fix_typed.hpp
#include "../runtime/native/verified/Timer.hpp"

struct ItemUseFixEvent {
    std::uintptr_t type;
    TimerGame *game;
    std::uint8_t cancelled;
    std::uint8_t padding[7];
};
struct ItemUseFixState {
    volatile std::uint8_t restore_breaking;
};
struct ItemUseFixDependencies {
    std::uintptr_t (*controller)(GameAccessBridge *, std::uintptr_t client);
    std::uint8_t (*breaking_block)(GameAccessBridge *, std::uintptr_t controller);
    void (*set_breaking_block)(GameAccessBridge *, std::uintptr_t controller, std::uint32_t value);
};
static_assert(sizeof(ItemUseFixEvent) == 24);
static_assert(offsetof(ItemUseFixEvent, cancelled) == 16);
static_assert(sizeof(ItemUseFixState) == 1);
static_assert(sizeof(ItemUseFixDependencies) == 24);

extern "C" {
__declspec(dllexport) void recovered_bind_item_use_fix_access(ItemUseFixDependencies *);
__declspec(dllexport) void recovered_item_use_fix_typed_before(ItemUseFixEvent *, ItemUseFixState *,
                                                               const ItemUseFixDependencies *);
__declspec(dllexport) void recovered_item_use_fix_typed_after(ItemUseFixEvent *, ItemUseFixState *,
                                                              const ItemUseFixDependencies *);
}

class ItemUseFixModule {
  public:
    static constexpr const char *name = "Item Use Fix";
    static constexpr const char *description = "Allows using items while breaking blocks.";
    static constexpr std::uint32_t before_event = 14, after_event = 15;
    static constexpr std::int32_t event_priority = 0;
    ItemUseFixState state{};
    ItemUseFixDependencies access{};
    ItemUseFixModule() {
        recovered_bind_item_use_fix_access(&access);
    }
    void before(ItemUseFixEvent &event) {
        recovered_item_use_fix_typed_before(&event, &state, &access);
    }
    void after(ItemUseFixEvent &event) {
        recovered_item_use_fix_typed_after(&event, &state, &access);
    }
};
// END SOURCE native/verified/Item_Use_Fix_typed.hpp

#endif // SLINKY_SHARE_6F9A667DF7AD28E2F360

#include "../runtime/native/verified/module_access_helpers.hpp"

namespace {
std::uintptr_t controller(GameAccessBridge *bridge, std::uintptr_t client) {
    return recovered_access_helper(bridge, 0x22df0, client, 0, 0);
}
std::uint8_t breaking_block(GameAccessBridge *bridge, std::uintptr_t controller) {
    return static_cast<std::uint8_t>(recovered_access_helper(bridge, 0x27e90, controller, 0, 0));
}
void set_breaking_block(GameAccessBridge *bridge, std::uintptr_t controller, std::uint32_t value) {
    recovered_access_helper(bridge, 0x27eb0, controller, value, 0);
}
} // namespace
extern "C" __declspec(dllexport) void
recovered_bind_item_use_fix_access(ItemUseFixDependencies *access) {
    *access = {controller, breaking_block, set_breaking_block};
}

// 0x42b80 retains the captured game and controller, refreshing the bridge
// between queries and clearing only when the original predicate's AL is nonzero.
extern "C" __declspec(dllexport) void
recovered_item_use_fix_typed_before(ItemUseFixEvent *event, ItemUseFixState *state,
                                    const ItemUseFixDependencies *access) {
    if (event->cancelled != 0)
        return;
    auto *game = event->game;
    const auto controller = access->controller(game->bridge, game->client);
    const auto restore = access->breaking_block(game->bridge, controller) != 0;
    state->restore_breaking = static_cast<std::uint8_t>(restore);
    if (restore)
        access->set_breaking_block(game->bridge, controller, 0);
}

// 0x42be0 checks saved state before touching the event. The state sent to
// the setter is read again after querying the current controller.
extern "C" __declspec(dllexport) void
recovered_item_use_fix_typed_after(ItemUseFixEvent *event, ItemUseFixState *state,
                                   const ItemUseFixDependencies *access) {
    if (state->restore_breaking != 1 || event->cancelled != 0)
        return;
    auto *game = event->game;
    const auto controller = access->controller(game->bridge, game->client);
    access->set_breaking_block(game->bridge, controller, state->restore_breaking);
}
// END SOURCE modules/Item_Use_Fix/Item_Use_Fix_typed.cpp

#ifndef SLINKY_SHARE_D31AABD0AF7DC12C02FE
#define SLINKY_SHARE_D31AABD0AF7DC12C02FE
// BEGIN SOURCE modules/Item_Use_Fix/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Item_Use_Fix/Api.hpp

#endif // SLINKY_SHARE_D31AABD0AF7DC12C02FE

// Convenient borrowed-state interface

namespace shareable {
using ItemUseFix = ::ItemUseFixModule;
}
