#include "module_list_storage.hpp"
#include "module_memory.hpp"

#include <cstdlib>
#include <cstring>

template <class T>
static T read(const void *pointer) {
    T value;
    std::memcpy(&value, pointer, sizeof(value));
    return value;
}
template <class T>
static void write(void *pointer, T value) {
    std::memcpy(pointer, &value, sizeof(value));
}
static void *at(std::uintptr_t base, std::uint32_t index, std::uint32_t stride) {
    return reinterpret_cast<void *>(base + index * stride);
}

extern "C" __declspec(dllexport) void recovered_bind_list_memory(ListMemoryDependencies *dependencies) {
    dependencies->move = recovered_memory_move;
    dependencies->copy = recovered_memory_copy;
}

extern "C" __declspec(dllexport) void *recovered_list_insert(
    void *data_slot, std::uint32_t stride, void *capacity_count, const void *record,
    StorageCompare compare, const ListMemoryDependencies *dependencies) {
    auto *metadata = static_cast<std::uint8_t *>(capacity_count);
    std::uint32_t first = 0;
    auto last = read<std::uint32_t>(metadata + 4);
    if (last) {
        const auto base = read<std::uintptr_t>(data_slot);
        while (first < last) {
            const auto middle = first + ((last - first) >> 1);
            const auto order = compare(0, record, at(base, middle, stride));
            if (order == 0) return at(read<std::uintptr_t>(data_slot), middle, stride);
            if (order < 0) last = middle;
            else first = middle + 1;
        }
    }
    auto count = read<std::uint32_t>(metadata + 4);
    const auto capacity = read<std::uint32_t>(metadata);
    auto base = read<std::uintptr_t>(data_slot);
    if (count >= capacity) {
        const auto grown = capacity ? capacity * 2 : 8;
        write(metadata, grown);
        auto *replacement = dependencies->reallocate(reinterpret_cast<void *>(base), grown * stride);
        if (!replacement) {
            dependencies->allocation_failure();
            std::abort();
        }
        base = reinterpret_cast<std::uintptr_t>(replacement);
        write(data_slot, base);
        count = read<std::uint32_t>(metadata + 4);
    }
    auto *destination = at(base, first, stride);
    dependencies->move(at(base, first + 1, stride), destination, (count - first) * stride);
    dependencies->copy(destination, record, stride);
    write(metadata + 4, read<std::uint32_t>(metadata + 4) + 1);
    return destination;
}

extern "C" __declspec(dllexport) std::uint32_t recovered_list_growth(
    void *data_slot, std::uint64_t stride, std::uint64_t count,
    void *capacity_slot, std::uint32_t incoming_rsi, const ListMemoryDependencies *dependencies) {
    auto capacity = read<std::uint64_t>(capacity_slot);
    const auto result = (incoming_rsi & 0xffffff00u) | 1u;
    if (count < capacity) return result;
    const auto old = read<std::uintptr_t>(data_slot);
    void *replacement;
    if (old) {
        capacity *= 2;
        replacement = dependencies->reallocate(reinterpret_cast<void *>(old), stride * capacity);
    } else {
        capacity = 8;
        replacement = dependencies->allocate(8);
    }
    if (!replacement) return 0;
    write(data_slot, reinterpret_cast<std::uintptr_t>(replacement));
    write(capacity_slot, capacity);
    return result;
}
