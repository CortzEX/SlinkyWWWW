#include "Friends_actions.hpp"
#include "Chams.hpp"
#include <cstring>

using AccessCall = std::uintptr_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t);
static std::uintptr_t access(GameAccessBridge *bridge, std::uintptr_t object,
    std::size_t slot, std::size_t field) {
    std::uintptr_t identifier;
    std::memcpy(&identifier, bridge->metadata + field, sizeof(identifier));
    const auto *table = reinterpret_cast<const std::uintptr_t *>(*bridge->environment);
    return reinterpret_cast<AccessCall>(table[slot / 8])(bridge->environment, object, identifier);
}
static std::uintptr_t current(GameAccessBridge *bridge) {
    std::uintptr_t clazz;
    std::memcpy(&clazz, bridge->metadata + 0x150, sizeof(clazz));
    return access(bridge, clazz, 0x488, 0x180);
}
static std::uintptr_t context(GameAccessBridge *bridge, std::uintptr_t object) {
    return access(bridge, object, 0x2f8, 0x1b0);
}
static std::uintptr_t object(GameAccessBridge *bridge, std::uintptr_t value) {
    return access(bridge, value, 0x2f8, 0x418);
}
static std::uintptr_t entity(GameAccessBridge *bridge, std::uintptr_t object) {
    return static_cast<std::uint8_t>(access(bridge, object, 0x100, 0x870)) ? object : 0;
}
static std::uintptr_t uuid(GameAccessBridge *bridge, std::uintptr_t object) {
    return access(bridge, object, 0x2f8, 0x2e8);
}
static std::uintptr_t high(GameAccessBridge *bridge, std::uintptr_t uuid) {
    return access(bridge, uuid, 0x1a0, 0xba8);
}
static std::uintptr_t low(GameAccessBridge *bridge, std::uintptr_t uuid) {
    return access(bridge, uuid, 0x1a0, 0xba0);
}
extern "C" __declspec(dllexport) void recovered_bind_friends_action_access(FriendsActionDependencies *dependencies) {
    dependencies->current = current;
    dependencies->context = context;
    dependencies->object = object;
    dependencies->entity = entity;
    dependencies->uuid = uuid;
    dependencies->high = high;
    dependencies->low = low;
    dependencies->flags = recovered_chams_flags;
}

extern "C" __declspec(dllexport) void recovered_friends_action(GameAccessBridge *bridge,
    std::uintptr_t action_context, const std::uint8_t *enabled, SortedTable *table,
    const FriendsActionDependencies *dependencies) {
    if (*enabled != 1) return;
    const auto context = dependencies->context(bridge, dependencies->current(bridge));
    if (!context) return;
    const auto object = dependencies->object(bridge, context);
    if (!object) return;
    const auto entity = dependencies->entity(bridge, object);
    if (!entity) return;
    const auto uuid = dependencies->uuid(bridge, entity);
    FriendRecord record;
    record.key.words[0] = dependencies->high(bridge, uuid);
    record.key.words[1] = dependencies->low(bridge, uuid);
    record.timestamp = dependencies->timestamp();
    record.reserved = 0;
    FriendAction action{};
    auto *found = recovered_sorted_lookup(table->data, sizeof(record), &table->capacity, &record, recovered_uuid_compare);
    if (found) {
        action.event_type = 19;
        recovered_sorted_remove(table->data, sizeof(record), &table->capacity, found, dependencies->memory);
    } else {
        if (static_cast<std::uint8_t>(dependencies->flags(bridge, entity, 2))) return;
        action.event_type = 19;
        action.added = 1;
        recovered_list_insert(&table->data, sizeof(record), &table->capacity, &record, recovered_uuid_compare, dependencies->memory);
    }
    dependencies->emit(action_context, &action);
}
