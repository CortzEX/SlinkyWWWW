#include "../module_surface.hpp"

// Fast Accel: lib_win settings 0x425f0. 
// UI 0x42580.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2f2a08},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2f2a60},
    {UiControl::checkbox, nullptr, 0x2f2a40},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "acceleration", 0x2f2a08},
    {SettingsControl::boolean, "require_not_damaged", 0x2f2a60},
    {SettingsControl::boolean, "require_weapon", 0x2f2a40},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_fast_accel_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_fast_accel_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
