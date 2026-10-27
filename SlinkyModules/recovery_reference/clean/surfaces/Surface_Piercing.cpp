#include "../module_surface.hpp"

// Piercing: lib_win settings 0x44d70. 
// UI 0x44ca0.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Always hit through", 0},
    {UiControl::choice, nullptr, 0x2f3d90},
    {UiControl::checkbox, nullptr, 0x2f3d00},
    {UiControl::checkbox, nullptr, 0x2f3d20},
    {UiControl::checkbox, nullptr, 0x2f3d40},
    {UiControl::checkbox, nullptr, 0x2f3d60},
    {UiControl::checkbox, nullptr, 0x2f3dd0},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2f3ce0},
    {UiControl::checkbox, nullptr, 0x2f3cc0},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::choice, "sort_by", 0x2f3d90},
    {SettingsControl::boolean, "non_players", 0x2f3d00},
    {SettingsControl::boolean, "friendlies", 0x2f3d20},
    {SettingsControl::boolean, "bots", 0x2f3d40},
    {SettingsControl::boolean, "enemies", 0x2f3d60},
    {SettingsControl::boolean, "blocks", 0x2f3dd0},
    {SettingsControl::boolean, "require_weapon", 0x2f3ce0},
    {SettingsControl::boolean, "require_inside_bb", 0x2f3cc0},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_piercing_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_piercing_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
