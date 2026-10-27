#ifndef SLINKY_SHARE_41982F29C4A0573339DB
#define SLINKY_SHARE_41982F29C4A0573339DB
#include "module_color_settings.hpp"

struct ListSetting {
    std::uint8_t metadata[24];
    std::uint32_t kind;
    std::uint32_t padding;
    void *state;
    std::size_t (*count)(void *state);
    const char *(*name)(void *state, std::size_t index);
    const float *(*color)(void *state, std::size_t index);
    void (*add)(void *state, const char *name, const float *color);
    void (*remove)(void *state, std::size_t index);
    void (*clear)(void *state);
};

struct ListSettingsDependencies {
    void *(*lookup)(void *root, const char *key);
    int (*is_array)(const void *node);
    int (*is_object)(const void *node);
    int (*is_string)(const void *node);
    void *(*create_array)(void *root);
    void *(*create_string)(const char *value);
    void *(*create_object)();
    void *(*create_child_object)(void *parent, const char *key);
    void *(*write_string)(void *root, const char *key, const char *value);
    void *(*write_number)(void *root, const char *key, double value);
    int (*append)(void *array, void *value);
};

static_assert(sizeof(ListSetting) == 0x58);
static_assert(offsetof(ListSetting, kind) == 0x18);
static_assert(offsetof(ListSetting, state) == 0x20);
static_assert(offsetof(ListSetting, add) == 0x40);
static_assert(offsetof(ListSetting, clear) == 0x50);
static_assert(offsetof(ListSetting, remove) == 0x48);

extern "C" __declspec(dllexport) void recovered_list_settings(
    SettingsContext *context, const char *key, ListSetting *setting,
    const ListSettingsDependencies *dependencies);
#endif // SLINKY_SHARE_41982F29C4A0573339DB
