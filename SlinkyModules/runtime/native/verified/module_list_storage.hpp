#ifndef SLINKY_SHARE_753C293820C471949445
#define SLINKY_SHARE_753C293820C471949445
#include <cstddef>
#include <cstdint>

using StorageCompare = std::int32_t (*)(std::uint64_t, const void *, const void *);
struct ListMemoryDependencies {
    void *(*allocateZeroed)(std::uint64_t count,std::uint64_t stride);
    void *(*reallocate)(void *data, std::uint64_t bytes);
    void *(*move)(void *destination, const void *source, std::uint64_t bytes);
    void *(*copy)(void *destination, const void *source, std::uint64_t bytes);
    void (*allocation_failure)();
};

// Bind the recovered in-image movement/copy routines. Allocation stays external.
extern "C" __declspec(dllexport) void recovered_bind_list_memory(ListMemoryDependencies *dependencies);

extern "C" __declspec(dllexport) void *recovered_list_insert(
    void *data_slot, std::uint32_t stride, void *capacity_count,
    const void *record, StorageCompare compare, const ListMemoryDependencies *dependencies);

// incoming_rsi supplies the register bytes preserved by native helper 0xe310.
extern "C" __declspec(dllexport) std::uint32_t recovered_list_growth(
    void *data_slot, std::uint64_t stride, std::uint64_t count,
    void *capacity_slot, std::uint32_t incoming_rsi, const ListMemoryDependencies *dependencies);
#endif // SLINKY_SHARE_753C293820C471949445
