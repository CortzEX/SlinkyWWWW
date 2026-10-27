#include "../module_surface.hpp"

// Trajectories: lib_win settings 0x45e90. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "line_width", 0x2f4000},
    {SettingsControl::color, "color_hit", 0x2f4038},
    {SettingsControl::color, "color_miss", 0x2f4058},
    {SettingsControl::boolean, "render_throwables", 0x2f40d8},
    {SettingsControl::boolean, "render_pearls", 0x2f40b8},
    {SettingsControl::boolean, "render_bow", 0x2f4078},
    {SettingsControl::boolean, "render_uncharged_bow", 0x2f4098},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_trajectories_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Trajectories: lib_win runtime UI 0x45dc0.
extern "C" __declspec(dllexport) void recovered_trajectories_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f4000);
    dependencies->color(layout, ui, image + 0x2f4038);
    dependencies->color(layout, ui, image + 0x2f4058);
    dependencies->section(ui, layout, "Render when holding");
    dependencies->checkbox(layout, ui, image + 0x2f40d8);
    dependencies->checkbox(layout, ui, image + 0x2f40b8);
    dependencies->checkbox(layout, ui, image + 0x2f4078);
    if (image[0x2f4090] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2f4098);
    }
}
