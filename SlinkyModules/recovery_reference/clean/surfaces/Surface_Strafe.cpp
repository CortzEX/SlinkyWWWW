#include "../module_surface.hpp"

// Strafe: lib_win settings 0x422a0. 
// UI 0x42200.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Strength", 0},
    {UiControl::number, nullptr, 0x2f2768},
    {UiControl::number, nullptr, 0x2f27a0},
    {UiControl::number, nullptr, 0x2f2730},
    {UiControl::section, "Conditions", 0},
    {UiControl::number, nullptr, 0x2f26f8},
    {UiControl::checkbox, nullptr, 0x2f27d8},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "strength_jump", 0x2f2768},
    {SettingsControl::number, "strength_ground", 0x2f27a0},
    {SettingsControl::number, "strength_air", 0x2f2730},
    {SettingsControl::number, "max_hurt_time", 0x2f26f8},
    {SettingsControl::boolean, "require_weapon", 0x2f27d8},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_strafe_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_strafe_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
