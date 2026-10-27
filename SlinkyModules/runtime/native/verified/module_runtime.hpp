#ifndef SLINKY_SHARE_6F0E7C6C3FD6A727C541
#define SLINKY_SHARE_6F0E7C6C3FD6A727C541
#include <cstddef>
#include <cstdint>
#include <cstring>

struct ModuleList {
    const std::uint8_t **items;
    std::uint64_t count;
};

struct ModuleRegistry {
    ModuleList all;
    ModuleList categories[5];
    ModuleList events[27];
    const std::uint8_t **scratch[27];
    ModuleList extra[2];
    void *context;
};

using ModuleCompare = int (*)(const void *, const void *);
struct RegistryDependencies {
    void *(*allocate)(std::size_t, std::size_t);
    void (*sort)(void *, std::size_t, std::size_t, ModuleCompare);
};

using EventCallback = void (*)(void *);

static_assert(sizeof(ModuleRegistry) == 0x310);
static_assert(offsetof(ModuleRegistry, events) == 0x60);
static_assert(offsetof(ModuleRegistry, scratch) == 0x210);

inline std::uint32_t module_read_u32(const void *base, std::size_t offset) {
    std::uint32_t value;
    std::memcpy(&value, static_cast<const std::uint8_t *>(base) + offset, sizeof(value));
    return value;
}

inline std::uintptr_t module_read_pointer(const void *base, std::size_t offset) {
    std::uintptr_t value;
    std::memcpy(&value, static_cast<const std::uint8_t *>(base) + offset, sizeof(value));
    return value;
}

inline void module_write_pointer(void *base, std::size_t offset, std::uintptr_t value) {
    std::memcpy(static_cast<std::uint8_t *>(base) + offset, &value, sizeof(value));
}

extern "C" {
__declspec(dllexport) extern std::uint32_t recovered_module_sort_index;
__declspec(dllexport) extern std::uintptr_t recovered_selected_module_2f7ba8;
__declspec(dllexport) int recovered_compare_module_priority(const void *left, const void *right);
__declspec(dllexport) void recovered_dispatch_event(void *registry, void *event);
__declspec(dllexport) std::uint8_t recovered_event_list_empty(void *registry, std::uint32_t type);
__declspec(dllexport) std::uint8_t recovered_queue_module_state(void *registry, void *module, std::uint8_t state);
__declspec(dllexport) std::uint8_t recovered_module_changes_pending(void *registry);
__declspec(dllexport) void recovered_apply_module_changes(void *context);
}
#endif // SLINKY_SHARE_6F0E7C6C3FD6A727C541
