#include "../module_surface.hpp"

// Sprint Reset: lib_win settings 0x3b070. 
// UI 0x3afc0.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::choice, nullptr, 0x2eff28},
    {UiControl::number, nullptr, 0x2eff68},
    {UiControl::number, nullptr, 0x2f0000},
    {UiControl::checkbox, nullptr, 0x2effa0},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2effc0},
    {UiControl::checkbox, nullptr, 0x2effe0},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::choice, "mode", 0x2eff28},
    {SettingsControl::number, "delay", 0x2eff68},
    {SettingsControl::number, "duration", 0x2f0000},
    {SettingsControl::boolean, "randomize", 0x2effa0},
    {SettingsControl::boolean, "wait_for_damage", 0x2effc0},
    {SettingsControl::boolean, "require_weapon", 0x2effe0},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_sprint_reset_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_sprint_reset_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
