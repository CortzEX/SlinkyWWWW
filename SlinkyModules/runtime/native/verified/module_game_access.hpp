#ifndef SLINKY_SHARE_73EB45D09127613B79ED
#define SLINKY_SHARE_73EB45D09127613B79ED
#include "event_callbacks.hpp"
#include <cstddef>
#include <cstdint>

struct GameAccessBridge {
    const std::uint8_t *metadata;
    std::uintptr_t *environment;
};
static_assert(sizeof(GameAccessBridge) == 16);
static_assert(offsetof(GameAccessBridge, environment) == 8);

extern "C" {
__declspec(dllexport) std::int32_t recovered_game_last_attacker_time(GameAccessBridge *, std::uintptr_t entity);
__declspec(dllexport) std::uintptr_t recovered_game_inventory(GameAccessBridge *, std::uintptr_t player);
__declspec(dllexport) std::int32_t recovered_game_inventory_index(GameAccessBridge *, std::uintptr_t inventory);
__declspec(dllexport) std::uintptr_t recovered_game_inventory_array(GameAccessBridge *, std::uintptr_t inventory);
__declspec(dllexport) std::int32_t recovered_game_item_numeric_id(GameAccessBridge *, std::uintptr_t item);
__declspec(dllexport) std::uintptr_t recovered_game_s00_keepalive_predicate(GameAccessBridge *, std::uintptr_t packet);
__declspec(dllexport) std::uintptr_t recovered_game_c00_keepalive_predicate(GameAccessBridge *, std::uintptr_t packet);
__declspec(dllexport) std::uintptr_t recovered_game_item_object(GameAccessBridge *, std::uintptr_t player);
__declspec(dllexport) std::uint8_t recovered_game_sprinting(GameAccessBridge *, std::uintptr_t player);
__declspec(dllexport) std::uint8_t recovered_game_using_item(GameAccessBridge *, std::uintptr_t player);

// No Slow, Reach and Ping Fix use these recovered helpers through the bridge.
__declspec(dllexport) void recovered_bind_game_access(Dependencies *dependencies);
}
#endif // SLINKY_SHARE_73EB45D09127613B79ED
