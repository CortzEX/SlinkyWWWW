#include "module_surface.hpp"

void render_module_surface(
    const ModuleSurface &surface, std::uint64_t ui, std::uint64_t layout,
    std::uint8_t *image, const SurfaceUiDependencies &dependencies) {
    for (std::size_t i = 0; i < surface.ui_count; ++i) {
        const auto &step = surface.ui[i];
        auto *setting = image + step.setting_rva;
        switch (step.control) {
        case UiControl::section: dependencies.section(ui, layout, step.label); break;
        case UiControl::checkbox: dependencies.checkbox(layout, ui, setting); break;
        case UiControl::number: dependencies.number(layout, ui, setting); break;
        case UiControl::choice: dependencies.choice(layout, ui, setting); break;
        case UiControl::range: dependencies.range(layout, ui, setting); break;
        case UiControl::color: dependencies.color(layout, ui, setting); break;
        case UiControl::list: dependencies.list(layout, ui, setting); break;
        }
    }
}

void apply_module_settings(
    const ModuleSurface &surface, SettingsContext *context,
    std::uint8_t *image, const SurfaceSettingsDependencies &dependencies) {
    for (std::size_t i = 0; i < surface.settings_count; ++i) {
        const auto &step = surface.settings[i];
        auto *setting = image + step.setting_rva;
        switch (step.control) {
        case SettingsControl::boolean:
            recovered_boolean_settings(
                context, step.key, reinterpret_cast<BooleanSetting *>(setting),
                &dependencies.boolean);
            break;
        case SettingsControl::number:
            recovered_number_settings(
                context, step.key, reinterpret_cast<NumberSetting *>(setting),
                &dependencies.values);
            break;
        case SettingsControl::choice:
            recovered_choice_settings(
                context, step.key, reinterpret_cast<ChoiceSetting *>(setting),
                &dependencies.values);
            break;
        case SettingsControl::color:
            recovered_color_settings(
                context, step.key, reinterpret_cast<ColorSetting *>(setting),
                &dependencies.colors);
            break;
        case SettingsControl::range:
            recovered_range_settings(
                context, step.key, reinterpret_cast<RangeSetting *>(setting),
                &dependencies.colors);
            break;
        case SettingsControl::list:
            recovered_list_settings(
                context, step.key, reinterpret_cast<ListSetting *>(setting),
                &dependencies.lists);
            break;
        }
    }
}
