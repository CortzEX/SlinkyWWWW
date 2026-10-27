#include "../module_surface.hpp"

// Reach: lib_win settings 0x300e0. 
// UI 0x30060.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2ea760},
    {UiControl::section, "Advanced", 0},
    {UiControl::number, nullptr, 0x2ea798},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2ea7d0},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "distance", 0x2ea760},
    {SettingsControl::number, "activate_time", 0x2ea798},
    {SettingsControl::boolean, "require_sprint", 0x2ea7d0},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_reach_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_reach_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
