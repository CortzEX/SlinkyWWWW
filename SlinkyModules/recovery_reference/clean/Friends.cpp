#include "Friends.hpp"
#include <initializer_list>

extern "C" __declspec(dllexport) void recovered_bind_friends_list_storage(FriendsListDependencies *dependencies) {
    dependencies->insert = recovered_list_insert;
}
extern "C" __declspec(dllexport) std::size_t recovered_friends_typed_count(const FriendsListState *state) {
    return state->table->count;
}
extern "C" __declspec(dllexport) const char *recovered_friends_typed_name(const FriendsListState *state, std::size_t index) {
    const auto offset = static_cast<std::uint32_t>(index) * 32;
    const auto *source = reinterpret_cast<const volatile std::uint8_t *>(
        reinterpret_cast<std::uintptr_t>(state->table->data) + offset);
    auto *output = state->scratch;
    const auto *digits = state->digits;
    for (int i = 0; i < 24; ++i) {
        output[i * 2] = digits[source[i] >> 4];
        output[i * 2 + 1] = digits[source[i] & 15];
    }
    output[48] = 0;
    return output;
}
static bool digit(std::uint8_t byte, std::uint8_t &value) {
    value = static_cast<std::uint8_t>(byte - '0');
    if (value < 10) return true;
    if (static_cast<std::uint8_t>(byte - 'a') >= 26) return false;
    value = static_cast<std::uint8_t>(byte + 0xa9);
    return true;
}
extern "C" __declspec(dllexport) bool recovered_friends_typed_add(const FriendsListState *state, const char *name) {
    if (state->dependencies->length(name) < 48) return false;
    std::uint8_t record[32]{};
    for (const auto end : {16, 24}) {
        for (int i = end == 16 ? 0 : 16; i < end; ++i) {
            std::uint8_t high, low;
            if (!digit(static_cast<std::uint8_t>(name[i * 2]), high) ||
                !digit(static_cast<std::uint8_t>(name[i * 2 + 1]), low)) break;
            record[i] = static_cast<std::uint8_t>((high << 4) | low);
        }
    }
    auto *table = state->table;
    state->dependencies->insert(&table->data, 32, &table->capacity, record,
        recovered_uuid_compare, state->dependencies->memory);
    return true;
}
extern "C" __declspec(dllexport) void *recovered_friends_typed_remove(const FriendsListState *state, std::size_t index) {
    auto *table = state->table;
    const auto base = reinterpret_cast<std::uintptr_t>(table->data);
    const auto count = --table->count;
    const auto slot = static_cast<std::uint32_t>(index);
    return state->dependencies->memory->move(reinterpret_cast<void *>(base + slot * 32),
        reinterpret_cast<const void *>(base + (slot + 1) * 32), (count - slot) * 32);
}
extern "C" __declspec(dllexport) void recovered_friends_typed_clear(const FriendsListState *state) {
    state->table->count = 0;
}
static std::size_t count(void *state) { return recovered_friends_typed_count(static_cast<FriendsListState *>(state)); }
static const char *name(void *state, std::size_t index) { return recovered_friends_typed_name(static_cast<FriendsListState *>(state), index); }
static void add(void *state, const char *name, const float *) { recovered_friends_typed_add(static_cast<FriendsListState *>(state), name); }
static void remove(void *state, std::size_t index) { recovered_friends_typed_remove(static_cast<FriendsListState *>(state), index); }
static void clear(void *state) { recovered_friends_typed_clear(static_cast<FriendsListState *>(state)); }
extern "C" __declspec(dllexport) void recovered_bind_friends_typed_list(ListSetting *setting, FriendsListState *state) {
    setting->state = state;
    setting->count = count;
    setting->name = name;
    setting->add = add;
    setting->remove = remove;
    setting->clear = clear;
}
extern "C" __declspec(dllexport) std::uint64_t recovered_friends_typed_ui(std::uint64_t ui, std::uint64_t layout,
    FriendsSettings *settings, UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Main");
    return recovered_checkbox_control(layout, ui, &settings->middle_click_add, dirty, &endpoints->controls);
}
extern "C" __declspec(dllexport) void recovered_friends_typed_settings(SettingsContext *context, FriendsSettings *settings,
    const SettingsDependencies *boolean, const ListSettingsDependencies *lists) {
    recovered_boolean_settings(context, "middle_click_add", &settings->middle_click_add, boolean);
    recovered_list_settings(context, "friends", &settings->friends, lists);
}
