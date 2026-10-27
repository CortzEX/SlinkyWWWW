#include "../module_surface.hpp"

// Player ESP: lib_win settings 0x2f8c0. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::choice, "mode", 0x2ea0e0},
    {SettingsControl::number, "range", 0x2ea1a0},
    {SettingsControl::boolean, "hide_friendlies", 0x2ea238},
    {SettingsControl::choice, "color_mode", 0x2ea290},
    {SettingsControl::color, "color_enemies", 0x2ea218},
    {SettingsControl::color, "color_friendlies", 0x2ea1f8},
    {SettingsControl::boolean, "override_target_color", 0x2ea258},
    {SettingsControl::color, "color_target", 0x2ea1d8},
    {SettingsControl::number, "line_width", 0x2ea090},
    {SettingsControl::boolean, "hurt_effect", 0x2ea140},
    {SettingsControl::boolean, "filled", 0x2ea160},
    {SettingsControl::boolean, "show_2d_box", 0x2ea120},
    {SettingsControl::boolean, "show_health_bar", 0x2ea180},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_player_esp_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Player ESP: lib_win runtime UI 0x2f770.
extern "C" __declspec(dllexport) void recovered_player_esp_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2ea1a0);
    dependencies->checkbox(layout, ui, image + 0x2ea238);
    dependencies->section(ui, layout, "Customization");
    dependencies->choice(layout, ui, image + 0x2ea0e0);
    dependencies->choice(layout, ui, image + 0x2ea290);
    if (read_surface_value<std::uint32_t>(image, 0x2ea2c0) == 1) {
        dependencies->color(layout, ui, image + 0x2ea218);
        if (image[0x2ea250] == 0) {
            dependencies->color(layout, ui, image + 0x2ea1f8);
        }
    }
    dependencies->checkbox(layout, ui, image + 0x2ea258);
    if (image[0x2ea270] == 1) {
        dependencies->color(layout, ui, image + 0x2ea1d8);
    }
    dependencies->number(layout, ui, image + 0x2ea090);
    dependencies->checkbox(layout, ui, image + 0x2ea120);
    if (image[0x2ea138] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2ea160);
        dependencies->checkbox(layout, ui, image + 0x2ea140);
    }
    dependencies->checkbox(layout, ui, image + 0x2ea180);
}
