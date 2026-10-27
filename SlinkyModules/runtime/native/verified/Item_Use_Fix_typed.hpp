#ifndef SLINKY_SHARE_6F9A667DF7AD28E2F360
#define SLINKY_SHARE_6F9A667DF7AD28E2F360
#include "Timer.hpp"

struct ItemUseFixEvent {
    std::uintptr_t type;
    TimerGame *game;
    std::uint8_t cancelled;
    std::uint8_t padding[7];
};
struct ItemUseFixState { volatile std::uint8_t restore_breaking; };
struct ItemUseFixDependencies {
    std::uintptr_t (*controller)(GameAccessBridge *, std::uintptr_t client);
    std::uint8_t (*breaking_block)(GameAccessBridge *, std::uintptr_t controller);
    void (*set_breaking_block)(GameAccessBridge *, std::uintptr_t controller, std::uint32_t value);
};
static_assert(sizeof(ItemUseFixEvent)==24);
static_assert(offsetof(ItemUseFixEvent,cancelled)==16);
static_assert(sizeof(ItemUseFixState)==1);
static_assert(sizeof(ItemUseFixDependencies)==24);

extern "C" {
__declspec(dllexport) void recovered_bind_item_use_fix_access(ItemUseFixDependencies *);
__declspec(dllexport) void recovered_item_use_fix_typed_before(ItemUseFixEvent *, ItemUseFixState *, const ItemUseFixDependencies *);
__declspec(dllexport) void recovered_item_use_fix_typed_after(ItemUseFixEvent *, ItemUseFixState *, const ItemUseFixDependencies *);
}

class ItemUseFixModule {
public:
    static constexpr const char *name="Item Use Fix";
    static constexpr const char *description="Allows using items while breaking blocks.";
    static constexpr std::uint32_t before_event=14, after_event=15;
    static constexpr std::int32_t event_priority=0;
    ItemUseFixState state{};
    ItemUseFixDependencies access{};
    ItemUseFixModule() { recovered_bind_item_use_fix_access(&access); }
    void before(ItemUseFixEvent &event) { recovered_item_use_fix_typed_before(&event,&state,&access); }
    void after(ItemUseFixEvent &event) { recovered_item_use_fix_typed_after(&event,&state,&access); }
};
#endif // SLINKY_SHARE_6F9A667DF7AD28E2F360
