#include "../module_surface.hpp"

// Sprint: lib_win settings 0x35f60. 
// UI 0x35ef0.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Allow while", 0},
    {UiControl::checkbox, nullptr, 0x2eda70},
    {UiControl::checkbox, nullptr, 0x2eda90},
    {UiControl::checkbox, nullptr, 0x2edab0},
    {UiControl::checkbox, nullptr, 0x2eda50},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::boolean, "while_using_item", 0x2eda70},
    {SettingsControl::boolean, "while_backwards", 0x2eda90},
    {SettingsControl::boolean, "while_sideways", 0x2edab0},
    {SettingsControl::boolean, "while_in_gui", 0x2eda50},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_sprint_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_sprint_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
