#include "../module_surface.hpp"

// Clutch: lib_win settings 0x49da0. 
// UI 0x49c00.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2f59d0},
    {UiControl::number, nullptr, 0x2f5a08},
    {UiControl::number, nullptr, 0x2f5998},
    {UiControl::number, nullptr, 0x2f5790},
    {UiControl::number, nullptr, 0x2f5838},
    {UiControl::choice, nullptr, 0x2f5a98},
    {UiControl::checkbox, nullptr, 0x2f5a40},
    {UiControl::section, "Aim", 0},
    {UiControl::number, nullptr, 0x2f5870},
    {UiControl::number, nullptr, 0x2f58a8},
    {UiControl::number, nullptr, 0x2f58e0},
    {UiControl::checkbox, nullptr, 0x2f5a60},
    {UiControl::section, "Snap-back", 0},
    {UiControl::number, nullptr, 0x2f5800},
    {UiControl::number, nullptr, 0x2f57c8},
    {UiControl::checkbox, nullptr, 0x2f5918},
    {UiControl::checkbox, nullptr, 0x2f5ad8},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2f5938},
    {UiControl::checkbox, nullptr, 0x2f5958},
    {UiControl::checkbox, nullptr, 0x2f5978},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "range", 0x2f59d0},
    {SettingsControl::number, "max_aim_dist", 0x2f5a08},
    {SettingsControl::number, "min_height", 0x2f5998},
    {SettingsControl::number, "click_speed", 0x2f5790},
    {SettingsControl::number, "randomization", 0x2f5838},
    {SettingsControl::choice, "select_blocks", 0x2f5a98},
    {SettingsControl::boolean, "sideways_only", 0x2f5a40},
    {SettingsControl::number, "aim_speed", 0x2f5870},
    {SettingsControl::number, "aim_mult", 0x2f58a8},
    {SettingsControl::number, "aim_mult_strength", 0x2f58e0},
    {SettingsControl::boolean, "aim_multipoint", 0x2f5a60},
    {SettingsControl::number, "snapback_delay", 0x2f5800},
    {SettingsControl::number, "snapback_duration", 0x2f57c8},
    {SettingsControl::boolean, "snapback_instant_on_jump", 0x2f5918},
    {SettingsControl::boolean, "snapback_disable_after", 0x2f5ad8},
    {SettingsControl::boolean, "require_air", 0x2f5938},
    {SettingsControl::boolean, "require_damage", 0x2f5958},
    {SettingsControl::boolean, "require_backwards", 0x2f5978},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_clutch_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_clutch_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
