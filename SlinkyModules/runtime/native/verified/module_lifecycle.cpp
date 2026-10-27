#include "module_runtime.hpp"

extern "C" __declspec(dllexport) std::uintptr_t recovered_selected_module_2f7ba8 = 0;

static std::uint32_t mark_modules(void *registry, std::size_t queue, std::uint64_t count,
                                  std::uint8_t state) {
    auto *items = reinterpret_cast<std::uintptr_t *>(module_read_pointer(registry, queue));
    std::uint32_t affected = 0;
    for (std::uint64_t i = 0; i < count; ++i) {
        auto *module = reinterpret_cast<std::uint8_t *>(items[i]);
        module[0x14] = state;
        for (std::uint32_t event = 0; event < 27; ++event)
            if (module_read_pointer(module, 0x48 + event * 16)) affected |= std::uint32_t{1} << event;
    }
    return affected;
}

static void rebuild_lists(void *registry, std::uint32_t affected) {
    for (std::uint32_t event = 0; event < 27; ++event) {
        if (!(affected & (std::uint32_t{1} << event))) continue;
        auto *output = reinterpret_cast<std::uintptr_t *>(module_read_pointer(registry, 0x210 + event * 8));
        const auto count = module_read_pointer(registry, 0x68 + event * 16);
        for (std::uint64_t i = 0; i < count; ++i) {
            auto *items = reinterpret_cast<std::uintptr_t *>(module_read_pointer(registry, 0x60 + event * 16));
            auto *module = reinterpret_cast<std::uint8_t *>(items[i]);
            if (module[0x14] == 1) {
                const auto callback = module_read_pointer(module, 0x48 + event * 16);
                if (callback) *output++ = callback;
            }
        }
        *output = 0;
    }
}

static int notify(void *context, std::uintptr_t module, std::uint8_t state) {
    std::uint64_t event[9] = {5, reinterpret_cast<std::uintptr_t>(context), module, state};
    auto *registry = reinterpret_cast<void *>(module_read_pointer(context, 8));
    auto *next = reinterpret_cast<EventCallback *>(module_read_pointer(registry, 0x238));
    EventCallback callback = *next++;
    if (!callback) return 0;
    do {
        callback(event);
        callback = *next++;
    } while (callback);
    return 1;
}

// lib_win RVA 0x285d0, including selected-module cleanup at 0x2aab0.
extern "C" __declspec(dllexport) void recovered_apply_module_changes(void *context) {
    auto *registry = reinterpret_cast<void *>(module_read_pointer(context, 8));
    auto count = module_read_pointer(registry, 0x2f0);
    if (count) {
        const auto affected = mark_modules(registry, 0x2e8, count, 1);
        rebuild_lists(registry, affected);
        std::uint64_t i = 0;
        do {
            auto *items = reinterpret_cast<std::uintptr_t *>(module_read_pointer(registry, 0x2e8));
            if (notify(context, items[i], 1)) count = module_read_pointer(registry, 0x2f0);
        } while (++i < count);
        module_write_pointer(registry, 0x2f0, 0);
        registry = reinterpret_cast<void *>(module_read_pointer(context, 8));
    }
    count = module_read_pointer(registry, 0x300);
    if (count) {
        const auto affected = mark_modules(registry, 0x2f8, count, 0);
        std::uint64_t i = 0;
        do {
            auto *items = reinterpret_cast<std::uintptr_t *>(module_read_pointer(registry, 0x2f8));
            const auto module = items[i];
            notify(context, module, 0);
            if (recovered_selected_module_2f7ba8 == module) recovered_selected_module_2f7ba8 = 0;
        } while (++i < module_read_pointer(registry, 0x300));
        rebuild_lists(registry, affected);
        module_write_pointer(registry, 0x300, 0);
    }
}
