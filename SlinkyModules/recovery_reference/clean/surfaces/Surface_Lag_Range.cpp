#include "../module_surface.hpp"

// Lag Range: lib_win settings 0x3ac00. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "delay", 0x2efc48},
    {SettingsControl::boolean, "flush_sprint_reset", 0x2efcc0},
    {SettingsControl::boolean, "flush_splash_potion", 0x2efca0},
    {SettingsControl::boolean, "render_remote_pos", 0x2efce0},
    {SettingsControl::color, "indicator_color", 0x2efc08},
    {SettingsControl::number, "indicator_line_width", 0x2efbd0},
    {SettingsControl::boolean, "indicator_filled", 0x2efc28},
    {SettingsControl::boolean, "require_weapon", 0x2efc80},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_lag_range_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Lag Range: lib_win runtime UI 0x3ab00.
extern "C" __declspec(dllexport) void recovered_lag_range_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2efc48);
    dependencies->section(ui, layout, "Flush if");
    dependencies->checkbox(layout, ui, image + 0x2efcc0);
    dependencies->checkbox(layout, ui, image + 0x2efca0);
    dependencies->section(ui, layout, "Real position indicator");
    dependencies->checkbox(layout, ui, image + 0x2efce0);
    if (image[0x2efcf8] == 1) {
        dependencies->color(layout, ui, image + 0x2efc08);
        dependencies->number(layout, ui, image + 0x2efbd0);
        dependencies->checkbox(layout, ui, image + 0x2efc28);
    }
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2efc80);
}
