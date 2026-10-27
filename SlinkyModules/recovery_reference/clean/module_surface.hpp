#pragma once

#include "module_settings.hpp"
#include "module_color_settings.hpp"
#include "module_range_settings.hpp"
#include "module_list_settings.hpp"
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iterator>

enum class UiControl : std::uint8_t { section, checkbox, number, choice, range, color, list };
enum class SettingsControl : std::uint8_t { boolean, number, choice, color, range, list };

struct UiStep {
    UiControl control;
    const char *label;
    std::uint32_t setting_rva;
};

struct SettingsStep {
    SettingsControl control;
    const char *key;
    std::uint32_t setting_rva;
};

struct ModuleSurface {
    const UiStep *ui;
    std::size_t ui_count;
    const SettingsStep *settings;
    std::size_t settings_count;
};

struct SurfaceUiDependencies {
    void (*section)(std::uint64_t ui, std::uint64_t layout, const char *label);
    void (*checkbox)(std::uint64_t layout, std::uint64_t ui, void *setting);
    void (*number)(std::uint64_t layout, std::uint64_t ui, void *setting);
    void (*choice)(std::uint64_t layout, std::uint64_t ui, void *setting);
    void (*range)(std::uint64_t layout, std::uint64_t ui, void *setting);
    void (*color)(std::uint64_t layout, std::uint64_t ui, void *setting);
    void (*list)(std::uint64_t layout, std::uint64_t ui, void *setting);
};

template <class T>
T read_surface_value(const std::uint8_t *image, std::uint32_t rva) {
    T value;
    std::memcpy(&value, image + rva, sizeof(value));
    return value;
}

struct SurfaceSettingsDependencies {
    SettingsDependencies boolean;
    ValueSettingsDependencies values;
    ColorSettingsDependencies colors;
    ListSettingsDependencies lists;
};

void render_module_surface(
    const ModuleSurface &surface, std::uint64_t ui, std::uint64_t layout,
    std::uint8_t *image, const SurfaceUiDependencies &dependencies);
void apply_module_settings(
    const ModuleSurface &surface, SettingsContext *context,
    std::uint8_t *image, const SurfaceSettingsDependencies &dependencies);
