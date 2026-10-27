#include "../module_surface.hpp"

// Keep Sprint: lib_win settings 0x3a310. 
// UI 0x3a290.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2ef910},
    {UiControl::number, nullptr, 0x2ef948},
    {UiControl::checkbox, nullptr, 0x2ef9a0},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2ef980},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "chance", 0x2ef910},
    {SettingsControl::number, "motion_mult", 0x2ef948},
    {SettingsControl::boolean, "allow_reduce", 0x2ef9a0},
    {SettingsControl::boolean, "require_on_ground", 0x2ef980},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_keep_sprint_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_keep_sprint_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
