#include "Friends_runtime.hpp"
#include <bit>
#include <cstring>

static std::uintptr_t identifier(GameAccessBridge *bridge, std::size_t offset) {
    std::uintptr_t value;
    std::memcpy(&value, bridge->metadata + offset, sizeof(value));
    return value;
}
template <class Function>
static Function method(GameAccessBridge *bridge, std::size_t offset) {
    const auto *table = reinterpret_cast<const std::uintptr_t *>(*bridge->environment);
    return reinterpret_cast<Function>(table[offset / 8]);
}
static std::uintptr_t list(GameAccessBridge *bridge, std::uintptr_t world) {
    using Getter = std::uintptr_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t);
    return method<Getter>(bridge, 0x2f8)(bridge->environment, world, identifier(bridge, 0x360));
}
static std::int32_t count(GameAccessBridge *bridge, std::uintptr_t list) {
    using Counter = std::int32_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t);
    return method<Counter>(bridge, 0x188)(bridge->environment, list, identifier(bridge, 0x28));
}
static std::uintptr_t item(GameAccessBridge *bridge, std::uintptr_t list, std::uint32_t index) {
    using Getter = std::uintptr_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t, std::uint32_t);
    return method<Getter>(bridge, 0x110)(bridge->environment, list, identifier(bridge, 0x30), index);
}
static std::uint8_t same(GameAccessBridge *bridge, std::uintptr_t player, std::uintptr_t entity) {
    using Predicate = std::uint8_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t);
    return method<Predicate>(bridge, 0xc0)(bridge->environment, player, entity);
}
static std::uint32_t field_bits(GameAccessBridge *bridge, std::uintptr_t entity) {
    using Getter = float (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t);
    return std::bit_cast<std::uint32_t>(method<Getter>(bridge, 0x330)(bridge->environment, entity, identifier(bridge, 0x5c0)));
}
static std::uintptr_t set_field_bits(GameAccessBridge *bridge, std::uintptr_t entity, std::uint32_t bits) {
    using Setter = std::uintptr_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t, float);
    return method<Setter>(bridge, 0x378)(bridge->environment, entity, identifier(bridge, 0x5c0), std::bit_cast<float>(bits));
}
extern "C" __declspec(dllexport) std::uintptr_t recovered_entity_flags_add(
    GameAccessBridge *bridge, std::uintptr_t entity, std::uint32_t mask) {
    const auto bits = field_bits(bridge, entity);
    const auto old = (bits & 0xffff0000u) == 0xb3150000u ? bits : 0xb3150000u;
    return set_field_bits(bridge, entity, 0xb3150000u | ((old | mask) & 0xffffu));
}
extern "C" __declspec(dllexport) std::uintptr_t recovered_entity_flags_remove(
    GameAccessBridge *bridge, std::uintptr_t entity, std::uint32_t mask) {
    const auto bits = field_bits(bridge, entity);
    const auto old = (bits & 0xffff0000u) == 0xb3150000u ? bits & 0xffffu : 0xb3150000u;
    return set_field_bits(bridge, entity, (old & ~mask) | 0xb3150000u);
}
extern "C" __declspec(dllexport) void recovered_bind_friends_runtime_access(FriendsRuntimeDependencies *dependencies) {
    dependencies->list = list;
    dependencies->count = count;
    dependencies->item = item;
    dependencies->same = same;
    dependencies->add_flags = recovered_entity_flags_add;
    dependencies->remove_flags = recovered_entity_flags_remove;
}

extern "C" __declspec(dllexport) void recovered_friends_scan(
    TimerEvent *event, SortedTable *table, const FriendsRuntimeDependencies *dependencies) {
    auto *game = event->game;
    if (!game->player) return;
    const auto timestamp = dependencies->identity->timestamp();
    const auto entities = dependencies->list(game->bridge, game->world);
    auto count = dependencies->count(game->bridge, entities);
    for (std::uint32_t index = 0; std::bit_cast<std::int32_t>(index) < count; ++index) {
        const auto entity = dependencies->item(game->bridge, entities, index);
        if (!dependencies->same(game->bridge, game->player, entity)) {
            const auto uuid = dependencies->identity->uuid(game->bridge, entity);
            FriendRecord record{};
            record.key.words[0] = dependencies->identity->high(game->bridge, uuid);
            record.key.words[1] = dependencies->identity->low(game->bridge, uuid);
            auto *found = static_cast<FriendRecord *>(recovered_sorted_lookup(table->data, sizeof(record),
                &table->capacity, &record, recovered_uuid_compare));
            if (found) {
                dependencies->add_flags(game->bridge, entity, 4);
                found->timestamp = timestamp;
            } else dependencies->remove_flags(game->bridge, entity, 4);
        }
        count = dependencies->count(game->bridge, entities);
    }
}
extern "C" __declspec(dllexport) void recovered_friends_disable(
    TimerEvent *event, std::uintptr_t module_identity, const FriendsRuntimeDependencies *dependencies) {
    if (event->module != module_identity || event->enabled != 0) return;
    auto *game = event->game;
    if (!game->world) return;
    const auto entities = dependencies->list(game->bridge, game->world);
    auto count = dependencies->count(game->bridge, entities);
    for (std::uint32_t index = 0; std::bit_cast<std::int32_t>(index) < count; ++index) {
        const auto entity = dependencies->item(game->bridge, entities, index);
        if (!dependencies->same(game->bridge, game->player, entity)) dependencies->remove_flags(game->bridge, entity, 4);
        count = dependencies->count(game->bridge, entities);
    }
}
extern "C" __declspec(dllexport) void recovered_friends_release(
    SortedTable *table, const FriendsRuntimeDependencies *dependencies) {
    dependencies->release(table->data);
    std::memset(table, 0, sizeof(*table));
}
