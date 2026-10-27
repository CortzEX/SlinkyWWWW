#include "module_named_lists.hpp"

#include <bit>
#include <cstring>
#include <initializer_list>

template <class T>
static T read(const std::uint8_t *image, std::uint32_t offset) {
    T value;
    std::memcpy(&value, image + offset, sizeof(value));
    return value;
}

static void *record_at(const std::uint8_t *image, std::uint32_t table, std::uint32_t stride, std::size_t index) {
    const auto offset = static_cast<std::uint32_t>(index) * stride;
    return reinterpret_cast<void *>(read<std::uintptr_t>(image, table) + offset);
}

static void *remove_at(std::uint8_t *image, std::uint32_t table, std::uint32_t stride,
                       std::size_t index, const NamedListDependencies &dependencies) {
    const auto base = read<std::uintptr_t>(image, table);
    const auto count = read<std::uint32_t>(image, table + 12) - 1;
    std::memcpy(image + table + 12, &count, sizeof(count));
    const auto slot = static_cast<std::uint32_t>(index);
    return dependencies.move(reinterpret_cast<void *>(base + slot * stride),
                             reinterpret_cast<void *>(base + (slot + 1) * stride),
                             (count - slot) * stride);
}

// Teams: count/name/add/remove/clear at 0x321d0/0x321e0/0x32220/0x32400/0x32420.
extern "C" __declspec(dllexport) std::size_t recovered_teams_list_count(const std::uint8_t *image) {
    return read<std::uint32_t>(image, 0x2f9e2c);
}

extern "C" __declspec(dllexport) const char *recovered_teams_list_name(const std::uint8_t *image, std::size_t index) {
    const auto color = *static_cast<const std::int8_t *>(record_at(image, 0x2f9e20, 1, index));
    const char *name;
    std::memcpy(&name, image + 0x2eb6a0 + static_cast<std::ptrdiff_t>(color) * 8, sizeof(name));
    return name;
}

extern "C" __declspec(dllexport) std::int32_t recovered_teams_list_compare(
    std::uint64_t, const void *key, const void *candidate) {
    return *static_cast<const std::int8_t *>(key) - *static_cast<const std::int8_t *>(candidate);
}

extern "C" __declspec(dllexport) bool recovered_teams_list_add(
    std::uint8_t *image, const char *name, const NamedListDependencies *dependencies) {
    for (std::uint8_t color = 0; color < 16; ++color) {
        if (dependencies->compare_strings(name, read<const char *>(image, 0x2eb6a0 + color * 8)) != 0) continue;
        dependencies->insert(image + 0x2f9e20, 1, &color, recovered_teams_list_compare);
        return true;
    }
    return false;
}

extern "C" __declspec(dllexport) void *recovered_teams_list_remove(
    std::uint8_t *image, std::size_t index, const NamedListDependencies *dependencies) {
    return remove_at(image, 0x2f9e20, 1, index, *dependencies);
}

extern "C" __declspec(dllexport) void recovered_teams_list_clear(std::uint8_t *image) {
    const std::uint32_t zero = 0;
    std::memcpy(image + 0x2f9e2c, &zero, sizeof(zero));
}

// The native input helper appends one byte without writing a terminator.
extern "C" __declspec(dllexport) void recovered_teams_list_input(
    char *buffer, std::uint32_t character, const NamedListDependencies *dependencies) {
    const auto length = dependencies->length(buffer);
    const auto byte = static_cast<std::uint8_t>(character);
    if (length <= 99 && (static_cast<std::uint8_t>(byte - 'a') < 26 ||
                        static_cast<std::uint8_t>(byte - 'A') < 26 || byte == ' '))
        buffer[length] = std::bit_cast<char>(byte);
}

// Friends: count/name/add/remove/clear at 0x3bca0/0x3bcb0/0x3beb0/0x3c170/0x3c190.
extern "C" __declspec(dllexport) std::size_t recovered_friends_list_count(const std::uint8_t *image) {
    return read<std::uint32_t>(image, 0x2fc8cc);
}

extern "C" __declspec(dllexport) const char *recovered_friends_list_name(std::uint8_t *image, std::size_t index) {
    const auto *source = static_cast<const volatile std::uint8_t *>(record_at(image, 0x2fc8c0, 32, index));
    auto *output = image + 0x2fc8d0;
    const auto *digits = image + 0x1536b0;
    for (int i = 0; i < 24; ++i) {
        output[i * 2] = digits[source[i] >> 4];
        output[i * 2 + 1] = digits[source[i] & 15];
    }
    output[48] = 0;
    return reinterpret_cast<const char *>(output);
}

static bool friend_digit(std::uint8_t byte, std::uint8_t &value) {
    value = static_cast<std::uint8_t>(byte - '0');
    if (value < 10) return true;
    if (static_cast<std::uint8_t>(byte - 'a') >= 26) return false;
    value = static_cast<std::uint8_t>(byte + 0xa9);
    return true;
}

extern "C" __declspec(dllexport) std::int32_t recovered_friends_list_compare(
    std::uint64_t, const void *key, const void *candidate) {
    const auto order = std::memcmp(key, candidate, 16);
    return order == 0 ? 0 : order > 0 ? 1 : -1;
}

extern "C" __declspec(dllexport) bool recovered_friends_list_add(
    std::uint8_t *image, const char *name, const NamedListDependencies *dependencies) {
    const auto length = dependencies->length(name);
    if (length < 48) return false;
    std::uint8_t record[32]{};
    // Invalid prefix characters end only the first loop; the suffix is still parsed.
    for (const auto end : {16, 24}) {
        for (int i = end == 16 ? 0 : 16; i < end; ++i) {
            std::uint8_t high, low;
            if (!friend_digit(static_cast<std::uint8_t>(name[i * 2]), high) ||
                !friend_digit(static_cast<std::uint8_t>(name[i * 2 + 1]), low)) break;
            record[i] = static_cast<std::uint8_t>((high << 4) | low);
        }
    }
    dependencies->insert(image + 0x2fc8c0, 32, record, recovered_friends_list_compare);
    return true;
}

extern "C" __declspec(dllexport) void *recovered_friends_list_remove(
    std::uint8_t *image, std::size_t index, const NamedListDependencies *dependencies) {
    return remove_at(image, 0x2fc8c0, 32, index, *dependencies);
}

extern "C" __declspec(dllexport) void recovered_friends_list_clear(std::uint8_t *image) {
    const std::uint32_t zero = 0;
    std::memcpy(image + 0x2fc8cc, &zero, sizeof(zero));
}

template <bool Friends>
static std::size_t count(void *context) {
    const auto &state = *static_cast<NamedListState *>(context);
    return Friends ? recovered_friends_list_count(state.image) : recovered_teams_list_count(state.image);
}

template <bool Friends>
static const char *name(void *context, std::size_t index) {
    const auto &state = *static_cast<NamedListState *>(context);
    return Friends ? recovered_friends_list_name(state.image, index) : recovered_teams_list_name(state.image, index);
}

template <bool Friends>
static void add(void *context, const char *value, const float *) {
    const auto &state = *static_cast<NamedListState *>(context);
    if constexpr (Friends) recovered_friends_list_add(state.image, value, state.dependencies);
    else recovered_teams_list_add(state.image, value, state.dependencies);
}

template <bool Friends>
static void remove(void *context, std::size_t index) {
    const auto &state = *static_cast<NamedListState *>(context);
    if constexpr (Friends) recovered_friends_list_remove(state.image, index, state.dependencies);
    else recovered_teams_list_remove(state.image, index, state.dependencies);
}

template <bool Friends>
static void clear(void *context) {
    const auto &state = *static_cast<NamedListState *>(context);
    if constexpr (Friends) recovered_friends_list_clear(state.image);
    else recovered_teams_list_clear(state.image);
}

template <bool Friends>
static void bind(ListSetting *setting, NamedListState *state) {
    setting->state = state;
    setting->count = count<Friends>;
    setting->name = name<Friends>;
    setting->add = add<Friends>;
    setting->remove = remove<Friends>;
    setting->clear = clear<Friends>;
}

extern "C" __declspec(dllexport) void recovered_bind_teams_list(ListSetting *setting, NamedListState *state) {
    bind<false>(setting, state);
}
extern "C" __declspec(dllexport) void recovered_bind_friends_list(ListSetting *setting, NamedListState *state) {
    bind<true>(setting, state);
}
