#pragma once
#include "module_list_storage.hpp"

struct SortedTable { void *data; std::uint32_t capacity, count; };
static_assert(sizeof(SortedTable) == 16);
static_assert(offsetof(SortedTable, capacity) == 8);

extern "C" {
__declspec(dllexport) void *recovered_sorted_lookup(const void *data, std::uint32_t stride,
    const std::uint32_t *capacity_count, const void *key, StorageCompare compare);
__declspec(dllexport) void *recovered_sorted_remove(void *data, std::uint32_t stride,
    std::uint32_t *capacity_count, const void *found, const ListMemoryDependencies *memory);
}
