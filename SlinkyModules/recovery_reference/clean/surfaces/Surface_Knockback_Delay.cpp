#include "../module_surface.hpp"

// Knockback Delay: lib_win settings 0x465f0. 
// UI 0x46530.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2f4360},
    {UiControl::number, nullptr, 0x2f43f8},
    {UiControl::number, nullptr, 0x2f4308},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2f4340},
    {UiControl::checkbox, nullptr, 0x2f43d8},
    {UiControl::checkbox, nullptr, 0x2f43b8},
    {UiControl::checkbox, nullptr, 0x2f4398},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "range", 0x2f4360},
    {SettingsControl::number, "chance", 0x2f43f8},
    {SettingsControl::number, "max_delay", 0x2f4308},
    {SettingsControl::boolean, "require_air", 0x2f4340},
    {SettingsControl::boolean, "require_target", 0x2f43d8},
    {SettingsControl::boolean, "require_mouse", 0x2f43b8},
    {SettingsControl::boolean, "require_weapon", 0x2f4398},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_knockback_delay_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_knockback_delay_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
