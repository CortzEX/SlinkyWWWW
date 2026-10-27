#include "../module_surface.hpp"

// Pointers: lib_win settings 0x3e400. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "range", 0x2f0a98},
    {SettingsControl::number, "ignore_fov", 0x2f0ad0},
    {SettingsControl::boolean, "hide_friendlies", 0x2f0b48},
    {SettingsControl::choice, "style", 0x2f09e0},
    {SettingsControl::choice, "color_mode", 0x2f0a58},
    {SettingsControl::range, "near_far_range", 0x2f08d0},
    {SettingsControl::color, "color_near", 0x2f0990},
    {SettingsControl::color, "color_far", 0x2f09b0},
    {SettingsControl::color, "color_enemies", 0x2f0b28},
    {SettingsControl::color, "color_friendlies", 0x2f0b08},
    {SettingsControl::number, "scale", 0x2f0920},
    {SettingsControl::number, "radius", 0x2f0958},
    {SettingsControl::boolean, "scale_radius", 0x2f0a20},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_pointers_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Pointers: lib_win runtime UI 0x3e2d0.
extern "C" __declspec(dllexport) void recovered_pointers_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f0a98);
    dependencies->number(layout, ui, image + 0x2f0ad0);
    dependencies->checkbox(layout, ui, image + 0x2f0b48);
    dependencies->section(ui, layout, "Customization");
    dependencies->choice(layout, ui, image + 0x2f09e0);
    dependencies->choice(layout, ui, image + 0x2f0a58);
    dependencies->range(layout, ui, image + 0x2f08d0);
    const auto color_mode = read_surface_value<std::uint32_t>(image, 0x2f0a88);
    if (color_mode == 2) {
        dependencies->color(layout, ui, image + 0x2f0b28);
        if (image[0x2f0b60] == 0) {
            dependencies->color(layout, ui, image + 0x2f0b08);
        }
    } else if (color_mode == 0) {
        dependencies->color(layout, ui, image + 0x2f0990);
        dependencies->color(layout, ui, image + 0x2f09b0);
    }
    dependencies->number(layout, ui, image + 0x2f0920);
    dependencies->number(layout, ui, image + 0x2f0958);
    dependencies->checkbox(layout, ui, image + 0x2f0a20);
}
