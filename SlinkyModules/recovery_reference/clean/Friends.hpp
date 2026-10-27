#pragma once
#include "Friends_actions.hpp"
#include "module_list_settings.hpp"
#include "module_ui_controls.hpp"

struct FriendsSettings { BooleanSetting middle_click_add; ListSetting friends; };
struct FriendsListDependencies {
    std::size_t (*length)(const char *);
    decltype(&recovered_list_insert) insert;
    const ListMemoryDependencies *memory;
};
struct FriendsListState {
    SortedTable *table;
    char *scratch;
    const std::uint8_t *digits;
    const FriendsListDependencies *dependencies;
};
static_assert(sizeof(FriendsSettings) == 120);
static_assert(offsetof(FriendsSettings, friends) == 32);
static_assert(sizeof(FriendsListDependencies) == 24);
static_assert(sizeof(FriendsListState) == 32);

extern "C" {
__declspec(dllexport) void recovered_bind_friends_list_storage(FriendsListDependencies *);
__declspec(dllexport) void recovered_bind_friends_typed_list(ListSetting *, FriendsListState *);
__declspec(dllexport) std::size_t recovered_friends_typed_count(const FriendsListState *);
__declspec(dllexport) const char *recovered_friends_typed_name(const FriendsListState *, std::size_t index);
__declspec(dllexport) bool recovered_friends_typed_add(const FriendsListState *, const char *name);
__declspec(dllexport) void *recovered_friends_typed_remove(const FriendsListState *, std::size_t index);
__declspec(dllexport) void recovered_friends_typed_clear(const FriendsListState *);
__declspec(dllexport) std::uint64_t recovered_friends_typed_ui(std::uint64_t ui, std::uint64_t layout,
    FriendsSettings *, UiDirtyState *, const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_friends_typed_settings(SettingsContext *, FriendsSettings *,
    const SettingsDependencies *, const ListSettingsDependencies *);
}
