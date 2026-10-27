#include "../module_surface.hpp"

// Name Tags: lib_win settings 0x3d6e0. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "range", 0x2f05b8},
    {SettingsControl::number, "scale", 0x2f04e0},
    {SettingsControl::boolean, "show_own_name_tag", 0x2f05f0},
    {SettingsControl::boolean, "use_display_name", 0x2f0610},
    {SettingsControl::boolean, "distance_scaling", 0x2f0518},
    {SettingsControl::boolean, "background", 0x2f0538},
    {SettingsControl::boolean, "text_shadow", 0x2f0558},
    {SettingsControl::boolean, "show_health", 0x2f0630},
    {SettingsControl::choice, "health_fmt", 0x2f0680},
    {SettingsControl::boolean, "show_distance", 0x2f0650},
    {SettingsControl::boolean, "show_equipment", 0x2f0578},
    {SettingsControl::boolean, "show_enchants", 0x2f0598},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_name_tags_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Name Tags: lib_win runtime UI 0x3d5b0.
extern "C" __declspec(dllexport) void recovered_name_tags_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f05b8);
    dependencies->number(layout, ui, image + 0x2f04e0);
    dependencies->checkbox(layout, ui, image + 0x2f05f0);
    dependencies->checkbox(layout, ui, image + 0x2f0610);
    dependencies->checkbox(layout, ui, image + 0x2f0518);
    dependencies->checkbox(layout, ui, image + 0x2f0538);
    dependencies->checkbox(layout, ui, image + 0x2f0558);
    dependencies->section(ui, layout, "Extra info");
    dependencies->checkbox(layout, ui, image + 0x2f0630);
    if (image[0x2f0648] == 1) {
        dependencies->choice(layout, ui, image + 0x2f0680);
    }
    dependencies->checkbox(layout, ui, image + 0x2f0650);
    dependencies->checkbox(layout, ui, image + 0x2f0578);
    if (image[0x2f0590] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2f0598);
    }
}
