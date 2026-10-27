#ifndef SLINKY_SHARE_1E2AFD8CC83BC7BD2513
#define SLINKY_SHARE_1E2AFD8CC83BC7BD2513
#include "module_game_access.hpp"
#include "module_sorted_table.hpp"
#include "module_uuid.hpp"

struct FriendRecord { UuidKey key; std::uint64_t timestamp, reserved; };
struct FriendAction {
    std::uint32_t event_type, padding;
    std::uint8_t added, remaining[63];
};
static_assert(sizeof(FriendRecord) == 32);
static_assert(sizeof(FriendAction) == 72);
static_assert(offsetof(FriendAction, added) == 8);

struct FriendsActionDependencies {
    std::uintptr_t (*current)(GameAccessBridge *);
    std::uintptr_t (*context)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*object)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*entity)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*uuid)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*high)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*low)(GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*flags)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    std::uint64_t (*timestamp)();
    void (*emit)(std::uintptr_t context, const FriendAction *);
    const ListMemoryDependencies *memory;
};

extern "C" {
__declspec(dllexport) void recovered_bind_friends_action_access(FriendsActionDependencies *);
__declspec(dllexport) void recovered_friends_action(GameAccessBridge *, std::uintptr_t action_context,
    const std::uint8_t *enabled, SortedTable *, const FriendsActionDependencies *);
}
#endif // SLINKY_SHARE_1E2AFD8CC83BC7BD2513
