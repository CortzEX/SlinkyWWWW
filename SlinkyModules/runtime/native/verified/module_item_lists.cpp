#include "module_item_lists.hpp"

#include <bit>
#include <cstring>

static std::uint8_t *entry_address(const ItemPolicyTable *table, std::uint32_t index) {
    const auto offset = index * std::uint32_t{sizeof(ItemPolicyEntry)};
    return reinterpret_cast<std::uint8_t *>(reinterpret_cast<std::uintptr_t>(table->entries) + offset);
}

// Shared by Auto Soup, Auto Tool, and Weapons. Original RVAs 0x2ab70-0x2ac50.
extern "C" __declspec(dllexport) std::size_t recovered_item_policy_count(const ItemPolicyTable *table) {
    return table->count;
}

extern "C" __declspec(dllexport) const char *recovered_item_policy_name(
    const ItemPolicyTable *table, std::size_t index) {
    const char *name;
    std::memcpy(&name, entry_address(table, static_cast<std::uint32_t>(index)), sizeof(name));
    return name;
}

extern "C" __declspec(dllexport) std::int32_t recovered_item_policy_compare(
    std::uint64_t, const ItemPolicyEntry *key, const ItemPolicyEntry *candidate) {
    return std::bit_cast<std::int32_t>(key->identifier - candidate->identifier);
}

extern "C" __declspec(dllexport) bool recovered_item_policy_add(
    ItemPolicyTable *table, const char *name, const ItemPolicyListDependencies *dependencies) {
    const auto identifier = dependencies->find_identifier(name);
    if (identifier == -1) return false;
    const ItemPolicyEntry entry{dependencies->find_name(identifier),
                               static_cast<std::uint32_t>(identifier), 0};
    dependencies->insert(table, &entry, recovered_item_policy_compare);
    return true;
}

extern "C" __declspec(dllexport) void *recovered_item_policy_remove(
    ItemPolicyTable *table, std::size_t index, const ItemPolicyListDependencies *dependencies) {
    const auto slot = static_cast<std::uint32_t>(index);
    const auto count = --table->count;
    const auto bytes = (count - slot) * std::uint32_t{sizeof(ItemPolicyEntry)};
    return dependencies->move(entry_address(table, slot), entry_address(table, slot + 1), bytes);
}

extern "C" __declspec(dllexport) void recovered_item_policy_clear(ItemPolicyTable *table) {
    table->count = 0;
}

static std::size_t list_count(void *state) {
    return recovered_item_policy_count(static_cast<ItemPolicyListState *>(state)->table);
}

static const char *list_name(void *state, std::size_t index) {
    return recovered_item_policy_name(static_cast<ItemPolicyListState *>(state)->table, index);
}

static void list_add(void *state, const char *name, const float *) {
    auto &list = *static_cast<ItemPolicyListState *>(state);
    recovered_item_policy_add(list.table, name, list.dependencies);
}

static void list_clear(void *state) {
    recovered_item_policy_clear(static_cast<ItemPolicyListState *>(state)->table);
}

static void list_remove(void *state, std::size_t index) {
    auto &list = *static_cast<ItemPolicyListState *>(state);
    recovered_item_policy_remove(list.table, index, list.dependencies);
}

extern "C" __declspec(dllexport) void recovered_bind_item_policy_list(
    ListSetting *setting, ItemPolicyListState *state) {
    setting->state = state;
    setting->count = list_count;
    setting->name = list_name;
    setting->add = list_add;
    setting->remove = list_remove;
    setting->clear = list_clear;
}
