#ifndef SLINKY_SHARE_AF64B4C6D3DD77D3C9F5
#define SLINKY_SHARE_AF64B4C6D3DD77D3C9F5
#include "module_settings.hpp"

struct ColorSetting {
    std::uint8_t metadata[8];
    float current[3];
    float saved[3];
};

struct ColorSettingsDependencies {
    void *(*lookup)(void *root, const char *key);
    int (*is_object)(const void *node);
    double (*read_number)(const void *node);
    void *(*create_object)(void *root);
    void *(*write_number)(void *root, const char *key, double value);
};

static_assert(sizeof(ColorSetting) == 32);
static_assert(offsetof(ColorSetting, current) == 8);
static_assert(offsetof(ColorSetting, saved) == 20);

extern "C" __declspec(dllexport) void recovered_color_settings(
    SettingsContext *context, const char *key, ColorSetting *setting,
    const ColorSettingsDependencies *dependencies);
#endif // SLINKY_SHARE_AF64B4C6D3DD77D3C9F5
