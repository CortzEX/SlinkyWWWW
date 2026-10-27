#include "module_runtime.hpp"

// lib_win RVA 0x28480. The selected callback list stays fixed during this walk.
extern "C" __declspec(dllexport) void recovered_dispatch_event(void *registry, void *event) {
    const auto type = module_read_u32(event, 0);
    auto *next = reinterpret_cast<EventCallback *>(module_read_pointer(registry, 0x210 + type * 8));
    EventCallback callback;
    while ((callback = *next++) != nullptr) callback(event);
}

// lib_win RVA 0x284d0.
extern "C" __declspec(dllexport) std::uint8_t recovered_event_list_empty(
    void *registry, std::uint32_t type) {
    return *reinterpret_cast<std::uintptr_t *>(module_read_pointer(registry, 0x210 + type * 8)) == 0;
}

// lib_win RVA 0x284f0. This queues a state change without changing the module byte.
extern "C" __declspec(dllexport) std::uint8_t recovered_queue_module_state(
    void *registry, void *module, std::uint8_t state) {
    if (static_cast<std::uint8_t *>(module)[0x14] == state) return 1;
    std::size_t offset = 0x2e8;
    if (!state) {
        std::uint64_t event[9] = {4, reinterpret_cast<std::uintptr_t>(module)};
        recovered_dispatch_event(registry, event);
        if (event[2] & 1) return 0;
        offset = 0x2f8;
    }
    auto *items = reinterpret_cast<std::uintptr_t *>(module_read_pointer(registry, offset));
    auto count = module_read_pointer(registry, offset + 8);
    items[count++] = reinterpret_cast<std::uintptr_t>(module);
    module_write_pointer(registry, offset + 8, count);
    return 1;
}

// lib_win RVA 0x285b0.
extern "C" __declspec(dllexport) std::uint8_t recovered_module_changes_pending(void *registry) {
    return module_read_pointer(registry, 0x300) != 0 || module_read_pointer(registry, 0x2f0) != 0;
}
