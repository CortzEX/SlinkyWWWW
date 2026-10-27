#include "module_runtime.hpp"

extern "C" __declspec(dllexport) std::uint32_t recovered_module_sort_index = 0;

// lib_win RVA 0x28320. The subtraction intentionally wraps at 32 bits.
extern "C" __declspec(dllexport) int recovered_compare_module_priority(
    const void *left, const void *right) {
    const auto *a = *static_cast<const std::uint8_t *const *>(left);
    const auto *b = *static_cast<const std::uint8_t *const *>(right);
    const auto offset = 0x50 + static_cast<std::size_t>(recovered_module_sort_index) * 16;
    const std::uint32_t difference = module_read_u32(b, offset) - module_read_u32(a, offset);
    std::int32_t result;
    std::memcpy(&result, &difference, sizeof(result));
    return result;
}

// lib_win RVA 0x28000. Allocation failure leaves the partially built registry intact.
extern "C" __declspec(dllexport) std::uint64_t recovered_initialize_module_registry(
    ModuleRegistry *registry, void *context, const std::uint8_t *const modules[66],
    const RegistryDependencies *deps) {
    std::memset(reinterpret_cast<std::uint8_t *>(registry) + 0x10, 0, 0x300);
    registry->all.count = 66;
    registry->all.items = static_cast<const std::uint8_t **>(deps->allocate(66, 8));
    if (!registry->all.items) return 1005;
    std::memcpy(registry->all.items, modules, 66 * 8);

    for (std::size_t i = 0; i < 66; ++i) {
        const auto *module = modules[i];
        ++registry->categories[module_read_u32(module, 0x10)].count;
        for (std::size_t event = 0; event < 27; ++event)
            if (module_read_pointer(module, 0x48 + event * 16)) ++registry->events[event].count;
    }
    for (std::size_t category = 0; category < 5; ++category) {
        auto *list = &registry->categories[category];
        list->items = static_cast<const std::uint8_t **>(deps->allocate(list->count, 8));
        if (!list->items) return 1005;
        list->count = 0;
    }
    for (std::size_t event = 0; event < 27; ++event) {
        auto *list = &registry->events[event];
        const auto count = list->count;
        list->items = static_cast<const std::uint8_t **>(deps->allocate(count, 8));
        if (!list->items) return 1005;
        registry->scratch[event] = static_cast<const std::uint8_t **>(deps->allocate(count + 1, 8));
        if (!registry->scratch[event]) return 1005;
        list->count = 0;
    }
    for (auto &extra : registry->extra) {
        extra.items = static_cast<const std::uint8_t **>(deps->allocate(66, 8));
        if (!extra.items) return 1005;
    }

    for (std::size_t i = 0; i < 66; ++i) {
        const auto *module = modules[i];
        auto *category = &registry->categories[module_read_u32(module, 0x10)];
        category->items[category->count++] = module;
        for (std::size_t event = 0; event < 27; ++event) {
            if (module_read_pointer(module, 0x48 + event * 16)) {
                auto *list = &registry->events[event];
                list->items[list->count++] = module;
            }
        }
    }
    for (std::uint32_t event = 0; event < 27; ++event) {
        recovered_module_sort_index = event;
        deps->sort(registry->events[event].items, registry->events[event].count, 8,
                   recovered_compare_module_priority);
    }
    registry->context = context;
    return 0;
}
