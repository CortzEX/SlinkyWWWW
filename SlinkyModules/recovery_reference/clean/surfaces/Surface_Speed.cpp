#include "../module_surface.hpp"

// Speed: lib_win settings 0x4bc20. 
// UI 0x4bbc0.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2f6338},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2f6318},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "speed", 0x2f6338},
    {SettingsControl::boolean, "require_ground", 0x2f6318},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_speed_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_speed_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
