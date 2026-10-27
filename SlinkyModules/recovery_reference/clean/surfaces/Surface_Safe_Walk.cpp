#include "../module_surface.hpp"

// Safe Walk: lib_win settings 0x41ed0. 
// UI 0x41e50.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2f2240},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2f22b8},
    {UiControl::checkbox, nullptr, 0x2f2278},
    {UiControl::checkbox, nullptr, 0x2f2298},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "motion_multiplier", 0x2f2240},
    {SettingsControl::boolean, "require_holding_blocks", 0x2f22b8},
    {SettingsControl::boolean, "require_looking_down", 0x2f2278},
    {SettingsControl::boolean, "require_not_forward", 0x2f2298},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_safe_walk_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_safe_walk_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
