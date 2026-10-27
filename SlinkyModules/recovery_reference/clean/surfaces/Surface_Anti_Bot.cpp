#include "../module_surface.hpp"

// Anti Bot: lib_win settings 0x31490. 
// UI 0x313f0.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::choice, nullptr, 0x2eaf58},
    {UiControl::checkbox, nullptr, 0x2eafd8},
    {UiControl::checkbox, nullptr, 0x2eafb8},
    {UiControl::checkbox, nullptr, 0x2eaf18},
    {UiControl::checkbox, nullptr, 0x2eaf98},
    {UiControl::number, nullptr, 0x2eaee0},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::choice, "invalid_uuid", 0x2eaf58},
    {SettingsControl::boolean, "invalid_username", 0x2eafd8},
    {SettingsControl::boolean, "always_invis", 0x2eafb8},
    {SettingsControl::boolean, "always_stationary", 0x2eaf18},
    {SettingsControl::boolean, "sleeping", 0x2eaf98},
    {SettingsControl::number, "min_age", 0x2eaee0},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_anti_bot_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_anti_bot_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
