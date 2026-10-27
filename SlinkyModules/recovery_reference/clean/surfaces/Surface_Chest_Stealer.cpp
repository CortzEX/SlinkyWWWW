#include "../module_surface.hpp"

// Chest Stealer: lib_win settings 0x48790. 
// UI 0x486f0.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2f5498},
    {UiControl::number, nullptr, 0x2f54f0},
    {UiControl::number, nullptr, 0x2f5528},
    {UiControl::checkbox, nullptr, 0x2f5560},
    {UiControl::section, "Main", 0},
    {UiControl::checkbox, nullptr, 0x2f54d0},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "delay_after_open", 0x2f5498},
    {SettingsControl::number, "delay_before_close", 0x2f54f0},
    {SettingsControl::number, "speed", 0x2f5528},
    {SettingsControl::boolean, "smart_speed", 0x2f5560},
    {SettingsControl::boolean, "require_vanilla_title", 0x2f54d0},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_chest_stealer_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_chest_stealer_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
