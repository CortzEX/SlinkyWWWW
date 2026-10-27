#include "../module_surface.hpp"

// Backtrack: lib_win settings 0x36870. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::range, "target_dist", 0x2eddb0},
    {SettingsControl::number, "delay", 0x2ede00},
    {SettingsControl::number, "max_hurt_time", 0x2edd78},
    {SettingsControl::number, "cooldown", 0x2ede38},
    {SettingsControl::boolean, "disable_on_hit", 0x2edeb0},
    {SettingsControl::boolean, "render_remote_pos", 0x2eded0},
    {SettingsControl::color, "indicator_color", 0x2edd18},
    {SettingsControl::number, "indicator_line_width", 0x2edce0},
    {SettingsControl::boolean, "indicator_filled", 0x2edd58},
    {SettingsControl::boolean, "indicator_rotate", 0x2edd38},
    {SettingsControl::boolean, "require_mouse_pressed", 0x2ede70},
    {SettingsControl::boolean, "require_weapon", 0x2ede90},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_backtrack_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Backtrack: lib_win runtime UI 0x36740.
extern "C" __declspec(dllexport) void recovered_backtrack_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->range(layout, ui, image + 0x2eddb0);
    dependencies->number(layout, ui, image + 0x2ede00);
    dependencies->number(layout, ui, image + 0x2edd78);
    dependencies->number(layout, ui, image + 0x2ede38);
    dependencies->checkbox(layout, ui, image + 0x2edeb0);
    dependencies->section(ui, layout, "Real position indicator");
    dependencies->checkbox(layout, ui, image + 0x2eded0);
    if (image[0x2edee8] == 1) {
        dependencies->color(layout, ui, image + 0x2edd18);
        dependencies->number(layout, ui, image + 0x2edce0);
        dependencies->checkbox(layout, ui, image + 0x2edd58);
        dependencies->checkbox(layout, ui, image + 0x2edd38);
    }
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2ede70);
    dependencies->checkbox(layout, ui, image + 0x2ede90);
}
