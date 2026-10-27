#include "module_sorted_table.hpp"
#include <cstring>

static std::uint32_t count(const std::uint32_t *capacity_count) {
    std::uint32_t value;
    std::memcpy(&value, reinterpret_cast<const std::uint8_t *>(capacity_count) + 4, sizeof(value));
    return value;
}

extern "C" __declspec(dllexport) void *recovered_sorted_lookup(const void *data, std::uint32_t stride,
    const std::uint32_t *capacity_count, const void *key, StorageCompare compare) {
    std::uint32_t first = 0, last = count(capacity_count);
    const auto base = reinterpret_cast<std::uintptr_t>(data);
    while (first < last) {
        const auto middle = first + ((last - first) >> 1);
        auto *candidate = reinterpret_cast<void *>(base + middle * stride);
        const auto order = compare(0, key, candidate);
        if (order == 0) return candidate;
        if (order < 0) last = middle;
        else first = middle + 1;
    }
    return nullptr;
}

extern "C" __declspec(dllexport) void *recovered_sorted_remove(void *data, std::uint32_t stride,
    std::uint32_t *capacity_count, const void *found, const ListMemoryDependencies *memory) {
    const auto base = reinterpret_cast<std::uintptr_t>(data);
    const auto distance = reinterpret_cast<std::uintptr_t>(found) - base;
    const auto index = static_cast<std::uint32_t>(distance / stride);
    const auto remaining = count(capacity_count) - 1;
    std::memcpy(reinterpret_cast<std::uint8_t *>(capacity_count) + 4, &remaining, sizeof(remaining));
    auto *destination = reinterpret_cast<void *>(base + index * stride);
    const auto *source = reinterpret_cast<const void *>(base + (index + 1) * stride);
    return memory->move(destination, source, (remaining - index) * stride);
}
