#include "module_game_access.hpp"

#include <cstring>

using IntegerField = std::int32_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t);
using ObjectField = std::uintptr_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t);
using Predicate = std::uint8_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t);
using ArrayElement = std::uintptr_t (*)(std::uintptr_t *, std::uintptr_t, std::int32_t);
using IntegerCall = std::int32_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t, std::uintptr_t);

static std::uintptr_t identifier(const GameAccessBridge *bridge, std::size_t offset) {
    std::uintptr_t value;
    std::memcpy(&value, bridge->metadata + offset, sizeof(value));
    return value;
}

template <class Function>
static Function slot(const GameAccessBridge *bridge, std::size_t offset) {
    const auto *table = reinterpret_cast<const std::uintptr_t *>(*bridge->environment);
    return reinterpret_cast<Function>(table[offset / sizeof(std::uintptr_t)]);
}

// 0x239d0: EntityLivingBase.lastAttackerTime, metadata +0x560.
extern "C" __declspec(dllexport) std::int32_t recovered_game_last_attacker_time(
    GameAccessBridge *bridge, std::uintptr_t entity) {
    return slot<IntegerField>(bridge, 0x320)(bridge->environment, entity, identifier(bridge, 0x560));
}

// 0x23f40: EntityPlayer.inventory, metadata +0x5a0.
extern "C" __declspec(dllexport) std::uintptr_t recovered_game_inventory(
    GameAccessBridge *bridge, std::uintptr_t player) {
    return slot<ObjectField>(bridge, 0x2f8)(bridge->environment, player, identifier(bridge, 0x5a0));
}

// 0x25a60 and 0x25ab0: currentItem and mainInventory.
extern "C" __declspec(dllexport) std::int32_t recovered_game_inventory_index(
    GameAccessBridge *bridge, std::uintptr_t inventory) {
    return slot<IntegerField>(bridge, 0x320)(bridge->environment, inventory, identifier(bridge, 0x5d8));
}
extern "C" __declspec(dllexport) std::uintptr_t recovered_game_inventory_array(
    GameAccessBridge *bridge, std::uintptr_t inventory) {
    return slot<ObjectField>(bridge, 0x2f8)(bridge->environment, inventory, identifier(bridge, 0x5d0));
}

// 0x25c50: preserve the four observed register arguments to table slot 0x408.
extern "C" __declspec(dllexport) std::int32_t recovered_game_item_numeric_id(
    GameAccessBridge *bridge, std::uintptr_t item) {
    return slot<IntegerCall>(bridge, 0x408)(bridge->environment, identifier(bridge, 0x638),
                                          identifier(bridge, 0x640), item);
}

// 0x26c80 and 0x26cc0: return the packet only when the predicate's low byte is nonzero.
extern "C" __declspec(dllexport) std::uintptr_t recovered_game_s00_keepalive_predicate(
    GameAccessBridge *bridge, std::uintptr_t packet) {
    return slot<Predicate>(bridge, 0x100)(bridge->environment, packet, identifier(bridge, 0xa68)) ? packet : 0;
}
extern "C" __declspec(dllexport) std::uintptr_t recovered_game_c00_keepalive_predicate(
    GameAccessBridge *bridge, std::uintptr_t packet) {
    return slot<Predicate>(bridge, 0x100)(bridge->environment, packet, identifier(bridge, 0xa70)) ? packet : 0;
}

// 0x28a50 reloads both bridge pointers after each call; none is cached across calls.
extern "C" __declspec(dllexport) std::uintptr_t recovered_game_item_object(
    GameAccessBridge *bridge, std::uintptr_t player) {
    const auto inventory = recovered_game_inventory(bridge, player);
    const auto index = static_cast<std::uint32_t>(recovered_game_inventory_index(bridge, inventory));
    if (index > 8) return 0;
    const auto array = recovered_game_inventory_array(bridge, inventory);
    const auto element = slot<ArrayElement>(bridge, 0x568)(bridge->environment, array, static_cast<std::int32_t>(index));
    if (!element) return 0;
    return slot<ObjectField>(bridge, 0x110)(bridge->environment, element, identifier(bridge, 0x5f8));
}

// 0x23690 and 0x23f90 normalize the Boolean method result to 0 or 1.
extern "C" __declspec(dllexport) std::uint8_t recovered_game_sprinting(
    GameAccessBridge *bridge, std::uintptr_t player) {
    return slot<Predicate>(bridge, 0x128)(bridge->environment, player, identifier(bridge, 0x228)) != 0;
}
extern "C" __declspec(dllexport) std::uint8_t recovered_game_using_item(
    GameAccessBridge *bridge, std::uintptr_t player) {
    return slot<Predicate>(bridge, 0x128)(bridge->environment, player, identifier(bridge, 0x588)) != 0;
}

template <auto Function>
static auto access(std::uintptr_t bridge, std::uintptr_t object) {
    return Function(reinterpret_cast<GameAccessBridge *>(bridge), object);
}

extern "C" __declspec(dllexport) void recovered_bind_game_access(Dependencies *dependencies) {
    dependencies->dep_180023f90 = access<recovered_game_using_item>;
    dependencies->dep_180028a50 = access<recovered_game_item_object>;
    dependencies->dep_180025c50 = access<recovered_game_item_numeric_id>;
    dependencies->dep_180023690 = access<recovered_game_sprinting>;
    dependencies->dep_1800239d0 = access<recovered_game_last_attacker_time>;
    dependencies->dep_180026c80 = access<recovered_game_s00_keepalive_predicate>;
    dependencies->dep_180026cc0 = access<recovered_game_c00_keepalive_predicate>;
}
