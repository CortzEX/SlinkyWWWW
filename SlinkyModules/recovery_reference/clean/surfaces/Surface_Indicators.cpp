#include "../module_surface.hpp"

// Indicators: lib_win settings 0x3f360. 
// UI 0x3f2a0.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2f1650},
    {UiControl::number, nullptr, 0x2f1688},
    {UiControl::section, "Warn for", 0},
    {UiControl::checkbox, nullptr, 0x2f16c0},
    {UiControl::checkbox, nullptr, 0x2f16e0},
    {UiControl::checkbox, nullptr, 0x2f1700},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2f1720},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "scale", 0x2f1650},
    {SettingsControl::number, "radius", 0x2f1688},
    {SettingsControl::boolean, "show_arrow", 0x2f16c0},
    {SettingsControl::boolean, "show_fireball", 0x2f16e0},
    {SettingsControl::boolean, "show_pearl", 0x2f1700},
    {SettingsControl::boolean, "require_coming_closer", 0x2f1720},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_indicators_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_indicators_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
