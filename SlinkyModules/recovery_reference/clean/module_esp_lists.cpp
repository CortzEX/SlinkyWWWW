#include "module_esp_lists.hpp"

#include <bit>
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

static std::uint8_t *record(const EspListTable *table, std::uint64_t index) {
    return reinterpret_cast<std::uint8_t *>(reinterpret_cast<std::uintptr_t>(table->records) + index * 24);
}

extern "C" __declspec(dllexport) std::uint64_t recovered_esp_list_count(const EspListTable *table) {
    return table->count;
}
extern "C" __declspec(dllexport) const char *recovered_esp_list_name(const EspListTable *table, std::uint64_t index) {
    return read<const char *>(record(table, index));
}
extern "C" __declspec(dllexport) float *recovered_esp_list_color(const EspListTable *table, std::uint64_t index) {
    return reinterpret_cast<float *>(record(table, index) + 8);
}
extern "C" __declspec(dllexport) std::int32_t recovered_esp_list_compare(const void *key, const void *candidate) {
    return std::bit_cast<std::int32_t>(read<std::uint32_t>(key) - read<std::uint32_t>(
        static_cast<const std::uint8_t *>(candidate) + 20));
}

static void clear_block_cache(std::uint8_t *image, const EspListDependencies &dependencies) {
    if (read<std::uint64_t>(image + 0x3020f0)) {
        std::uint64_t index = 0;
        do {
            auto *row = read<std::uint8_t *>(image + 0x302100) + index * 80;
            std::memset(row + 8, 0, 16);
            dependencies.release(read<void *>(row + 24));
            std::memset(row + 24, 0, 24);
            dependencies.release(read<void *>(row + 48));
            std::memset(row + 48, 0, 24);
            dependencies.release(read<void *>(row + 72));
            std::memset(row + 72, 0, 8);
        } while (++index < read<std::uint64_t>(image + 0x3020f0));
    }
    std::memset(image + 0x3020f0, 0, 16);
    dependencies.release(read<void *>(image + 0x302100));
    std::memset(image + 0x302100, 0, 8);
    image[0x302108] = 1;
}

template <bool Block>
static std::uint32_t add(EspListTable *table, std::uint8_t *image, const char *name,
                         const float *color, const EspListDependencies &dependencies) {
    constexpr auto offset = Block ? 0x302110 : 0x3043a0;
    auto *global = reinterpret_cast<EspListTable *>(image + offset);
    auto identifier = dependencies.find_identifier(name);
    if (identifier == -1) return 0;
    if (global->records && dependencies.search(&identifier, global->records, global->count, 24,
                                               recovered_esp_list_compare)) return 0;
    std::uint64_t slot = 0;
    const auto count = table->count;
    for (; slot < count; ++slot) {
        if (identifier <= read<std::int32_t>(record(table, slot) + 20)) break;
    }
    const auto *canonical_name = dependencies.find_name(identifier);
    std::uint8_t color_bytes[12];
    std::memcpy(color_bytes, color, sizeof(color_bytes));
    const auto saved_identifier = identifier;
    if constexpr (Block) clear_block_cache(image, dependencies);
    const auto result = dependencies.grow(&global->records, 24, global->count, &global->capacity);
    if (static_cast<std::uint8_t>(result)) {
        auto *destination = record(global, slot);
        dependencies.move(destination + 24, destination, (global->count - slot) * 24);
        write(destination, canonical_name);
        std::memcpy(destination + 8, color_bytes, sizeof(color_bytes));
        write(destination + 20, saved_identifier);
        ++global->count;
    }
    return result;
}

extern "C" __declspec(dllexport) std::uint32_t recovered_block_esp_list_add(
    EspListTable *table, std::uint8_t *image, const char *name, const float *color, const EspListDependencies *dependencies) {
    return add<true>(table, image, name, color, *dependencies);
}
extern "C" __declspec(dllexport) std::uint32_t recovered_item_esp_list_add(
    EspListTable *table, std::uint8_t *image, const char *name, const float *color, const EspListDependencies *dependencies) {
    return add<false>(table, image, name, color, *dependencies);
}

extern "C" __declspec(dllexport) void *recovered_item_esp_list_remove(
    EspListTable *table, std::uint64_t index, const EspListDependencies *dependencies) {
    auto *destination = record(table, index);
    const auto count = table->count - 1;
    table->count = count;
    return dependencies->move(destination, reinterpret_cast<void *>(reinterpret_cast<std::uintptr_t>(destination) + 24),
                              (count - index) * 24);
}
extern "C" __declspec(dllexport) void recovered_block_esp_list_remove(
    EspListTable *table, std::uint8_t *image, std::uint64_t index, const EspListDependencies *dependencies) {
    recovered_item_esp_list_remove(table, index, dependencies);
    clear_block_cache(image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_item_esp_list_clear(
    EspListTable *table, const EspListDependencies *dependencies) {
    table->count = table->capacity = 0;
    dependencies->release(table->records);
    table->records = nullptr;
}
extern "C" __declspec(dllexport) void recovered_block_esp_list_clear(
    EspListTable *table, std::uint8_t *image, const EspListDependencies *dependencies) {
    recovered_item_esp_list_clear(table, dependencies);
    clear_block_cache(image, *dependencies);
}

static std::size_t count(void *context) {
    return recovered_esp_list_count(static_cast<EspListState *>(context)->table);
}
static const char *name(void *context, std::size_t index) {
    return recovered_esp_list_name(static_cast<EspListState *>(context)->table, index);
}
static const float *color(void *context, std::size_t index) {
    return recovered_esp_list_color(static_cast<EspListState *>(context)->table, index);
}
template <bool Block>
static void add(void *context, const char *name, const float *color) {
    const auto &state = *static_cast<EspListState *>(context);
    add<Block>(state.table, state.image, name, color, *state.dependencies);
}
template <bool Block>
static void remove(void *context, std::size_t index) {
    const auto &state = *static_cast<EspListState *>(context);
    if constexpr (Block) recovered_block_esp_list_remove(state.table, state.image, index, state.dependencies);
    else recovered_item_esp_list_remove(state.table, index, state.dependencies);
}
template <bool Block>
static void clear(void *context) {
    const auto &state = *static_cast<EspListState *>(context);
    if constexpr (Block) recovered_block_esp_list_clear(state.table, state.image, state.dependencies);
    else recovered_item_esp_list_clear(state.table, state.dependencies);
}
template <bool Block>
static void bind(ListSetting *setting, EspListState *state) {
    setting->state = state;
    setting->count = count;
    setting->name = name;
    setting->color = color;
    setting->add = add<Block>;
    setting->remove = remove<Block>;
    setting->clear = clear<Block>;
}
extern "C" __declspec(dllexport) void recovered_bind_block_esp_list(ListSetting *setting, EspListState *state) {
    bind<true>(setting, state);
}
extern "C" __declspec(dllexport) void recovered_bind_item_esp_list(ListSetting *setting, EspListState *state) {
    bind<false>(setting, state);
}
