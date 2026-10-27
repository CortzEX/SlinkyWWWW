#include "../module_surface.hpp"

// Timer: lib_win settings 0x32a80. 
// UI 0x32a00.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2ebc20},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2ebc58},
    {UiControl::checkbox, nullptr, 0x2ebc98},
    {UiControl::checkbox, nullptr, 0x2ebc78},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "speed", 0x2ebc20},
    {SettingsControl::boolean, "require_mouse", 0x2ebc58},
    {SettingsControl::boolean, "require_damage", 0x2ebc98},
    {SettingsControl::boolean, "require_falling", 0x2ebc78},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_timer_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_timer_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
