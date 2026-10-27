#ifndef SLINKY_SHARE_8A4EC9E4B7F856A28453
#define SLINKY_SHARE_8A4EC9E4B7F856A28453
#include "Friends_actions.hpp"
#include "Timer.hpp"

struct FriendsRuntimeDependencies {
    std::uintptr_t (*list)(GameAccessBridge *, std::uintptr_t);
    std::int32_t (*count)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*item)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    std::uint8_t (*same)(GameAccessBridge *, std::uintptr_t, std::uintptr_t);
    std::uintptr_t (*add_flags)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    std::uintptr_t (*remove_flags)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    void (*release)(void *);
    const FriendsActionDependencies *identity;
};
static_assert(sizeof(FriendsRuntimeDependencies) == 64);

extern "C" {
__declspec(dllexport) void recovered_bind_friends_runtime_access(FriendsRuntimeDependencies *);
__declspec(dllexport) void recovered_friends_scan(TimerEvent *, SortedTable *, const FriendsRuntimeDependencies *);
__declspec(dllexport) void recovered_friends_disable(TimerEvent *, std::uintptr_t module_identity, const FriendsRuntimeDependencies *);
__declspec(dllexport) void recovered_friends_release(SortedTable *, const FriendsRuntimeDependencies *);
__declspec(dllexport) std::uintptr_t recovered_entity_flags_add(GameAccessBridge *, std::uintptr_t, std::uint32_t);
__declspec(dllexport) std::uintptr_t recovered_entity_flags_remove(GameAccessBridge *, std::uintptr_t, std::uint32_t);
}
#endif // SLINKY_SHARE_8A4EC9E4B7F856A28453
