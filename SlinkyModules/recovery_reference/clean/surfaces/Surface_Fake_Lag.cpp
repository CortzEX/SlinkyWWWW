#include "../module_surface.hpp"

// Fake Lag: lib_win settings 0x32e20. 
// UI 0x32d60.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Delay", 0},
    {UiControl::choice, nullptr, 0x2ebf70},
    {UiControl::number, nullptr, 0x2ebed0},
    {UiControl::number, nullptr, 0x2ebf08},
    {UiControl::checkbox, nullptr, 0x2ebf40},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2ebfd0},
    {UiControl::checkbox, nullptr, 0x2ebff0},
    {UiControl::checkbox, nullptr, 0x2ebfb0},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::choice, "mode", 0x2ebf70},
    {SettingsControl::number, "inbound", 0x2ebed0},
    {SettingsControl::number, "outbound", 0x2ebf08},
    {SettingsControl::boolean, "realtime_damage", 0x2ebf40},
    {SettingsControl::boolean, "require_weapon", 0x2ebfd0},
    {SettingsControl::boolean, "require_attack", 0x2ebff0},
    {SettingsControl::boolean, "require_ingame", 0x2ebfb0},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_fake_lag_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_fake_lag_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
