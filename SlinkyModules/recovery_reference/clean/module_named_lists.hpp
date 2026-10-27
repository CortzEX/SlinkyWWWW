#pragma once

#include "module_list_settings.hpp"
#include <cstddef>
#include <cstdint>

using ListRecordCompare = std::int32_t (*)(std::uint64_t, const void *, const void *);

struct NamedListDependencies {
    std::size_t (*length)(const char *text);
    int (*compare_strings)(const char *left, const char *right);
    void *(*insert)(void *table, std::uint32_t stride, const void *record, ListRecordCompare compare);
    void *(*move)(void *destination, const void *source, std::uint32_t bytes);
};

struct NamedListState {
    std::uint8_t *image;
    const NamedListDependencies *dependencies;
};

extern "C" __declspec(dllexport) std::size_t recovered_teams_list_count(const std::uint8_t *image);
extern "C" __declspec(dllexport) const char *recovered_teams_list_name(const std::uint8_t *image, std::size_t index);
extern "C" __declspec(dllexport) bool recovered_teams_list_add(std::uint8_t *image, const char *name, const NamedListDependencies *dependencies);
extern "C" __declspec(dllexport) void *recovered_teams_list_remove(std::uint8_t *image, std::size_t index, const NamedListDependencies *dependencies);
extern "C" __declspec(dllexport) void recovered_teams_list_clear(std::uint8_t *image);
extern "C" __declspec(dllexport) std::int32_t recovered_teams_list_compare(std::uint64_t, const void *key, const void *candidate);
extern "C" __declspec(dllexport) void recovered_teams_list_input(char *buffer, std::uint32_t character, const NamedListDependencies *dependencies);

extern "C" __declspec(dllexport) std::size_t recovered_friends_list_count(const std::uint8_t *image);
extern "C" __declspec(dllexport) const char *recovered_friends_list_name(std::uint8_t *image, std::size_t index);
extern "C" __declspec(dllexport) bool recovered_friends_list_add(std::uint8_t *image, const char *name, const NamedListDependencies *dependencies);
extern "C" __declspec(dllexport) void *recovered_friends_list_remove(std::uint8_t *image, std::size_t index, const NamedListDependencies *dependencies);
extern "C" __declspec(dllexport) void recovered_friends_list_clear(std::uint8_t *image);
extern "C" __declspec(dllexport) std::int32_t recovered_friends_list_compare(std::uint64_t, const void *key, const void *candidate);

extern "C" __declspec(dllexport) void recovered_bind_teams_list(ListSetting *setting, NamedListState *state);
extern "C" __declspec(dllexport) void recovered_bind_friends_list(ListSetting *setting, NamedListState *state);
