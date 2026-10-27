#pragma once

#include <cstddef>
#include <cstdint>

struct SettingsContext {
    void *root;
    std::uint32_t action;
    std::uint8_t error;
    std::uint8_t padding[3];
};

struct BooleanSetting {
    std::uint8_t metadata[24];
    std::uint8_t current;
    std::uint8_t saved;
    std::uint8_t padding[6];
};

struct SettingsDependencies {
    void *(*lookup)(void *root, const char *key);
    void *(*write_boolean)(void *root, const char *key, int value);
};

struct NumberSetting {
    std::uint8_t metadata[40];
    float minimum;
    float maximum;
    float current;
    float saved;
};

struct ChoiceSetting {
    std::uint8_t metadata[32];
    std::uint32_t count;
    std::uint32_t padding;
    const char *const *options;
    std::uint32_t current;
    std::uint32_t saved;
};

struct ValueSettingsDependencies {
    void *(*lookup)(void *root, const char *key);
    void *(*write_number)(void *root, const char *key, double value);
    void *(*write_string)(void *root, const char *key, const char *value);
    int (*compare_strings)(const char *left, const char *right);
};

static_assert(offsetof(SettingsContext, error) == 12);
static_assert(sizeof(BooleanSetting) == 32);
static_assert(sizeof(NumberSetting) == 56);
static_assert(offsetof(NumberSetting, current) == 0x30);
static_assert(sizeof(ChoiceSetting) == 56);
static_assert(offsetof(ChoiceSetting, options) == 0x28);
static_assert(offsetof(ChoiceSetting, current) == 0x30);

extern "C" __declspec(dllexport) void recovered_boolean_settings(
    SettingsContext *context, const char *key, BooleanSetting *setting,
    const SettingsDependencies *dependencies);
extern "C" __declspec(dllexport) void recovered_number_settings(
    SettingsContext *context, const char *key, NumberSetting *setting,
    const ValueSettingsDependencies *dependencies);
extern "C" __declspec(dllexport) void recovered_choice_settings(
    SettingsContext *context, const char *key, ChoiceSetting *setting,
    const ValueSettingsDependencies *dependencies);
