#ifndef SLINKY_SHARE_48213181467ACC791A40
#define SLINKY_SHARE_48213181467ACC791A40
#include "module_list_settings.hpp"
#include <cstddef>
#include <cstdint>

struct ItemPolicyEntry {
    const char *name;
    std::uint32_t identifier;
    std::uint32_t reserved;
};

struct ItemPolicyTable {
    ItemPolicyEntry *entries;
    std::uint32_t capacity;
    std::uint32_t count;
};

using ItemPolicyCompare = std::int32_t (*)(std::uint64_t, const ItemPolicyEntry *, const ItemPolicyEntry *);

struct ItemPolicyListDependencies {
    std::int32_t (*find_identifier)(const char *name);
    const char *(*find_name)(std::int32_t identifier);
    ItemPolicyEntry *(*insert)(ItemPolicyTable *table, const ItemPolicyEntry *entry, ItemPolicyCompare compare);
    void *(*move)(void *destination, const void *source, std::uint32_t bytes);
};

struct ItemPolicyListState {
    ItemPolicyTable *table;
    const ItemPolicyListDependencies *dependencies;
};

static_assert(sizeof(ItemPolicyEntry) == 16);
static_assert(sizeof(ItemPolicyTable) == 16);
static_assert(offsetof(ItemPolicyTable, count) == 12);

extern "C" __declspec(dllexport) std::size_t recovered_item_policy_count(const ItemPolicyTable *table);
extern "C" __declspec(dllexport) const char *recovered_item_policy_name(const ItemPolicyTable *table, std::size_t index);
extern "C" __declspec(dllexport) bool recovered_item_policy_add(
    ItemPolicyTable *table, const char *name, const ItemPolicyListDependencies *dependencies);
extern "C" __declspec(dllexport) std::int32_t recovered_item_policy_compare(
    std::uint64_t context, const ItemPolicyEntry *key, const ItemPolicyEntry *candidate);
extern "C" __declspec(dllexport) void *recovered_item_policy_remove(
    ItemPolicyTable *table, std::size_t index, const ItemPolicyListDependencies *dependencies);
extern "C" __declspec(dllexport) void recovered_item_policy_clear(ItemPolicyTable *table);

// The caller owns this state for as long as the setting uses its callbacks.
extern "C" __declspec(dllexport) void recovered_bind_item_policy_list(
    ListSetting *setting, ItemPolicyListState *state);
#endif // SLINKY_SHARE_48213181467ACC791A40
