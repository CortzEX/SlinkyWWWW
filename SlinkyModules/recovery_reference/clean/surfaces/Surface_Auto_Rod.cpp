#include "../module_surface.hpp"

// Auto Rod: lib_win settings 0x444f0. 
// UI 0x44420.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2f37f0},
    {UiControl::number, nullptr, 0x2f3798},
    {UiControl::checkbox, nullptr, 0x2f37d0},
    {UiControl::checkbox, nullptr, 0x2f3778},
    {UiControl::section, "Throwables", 0},
    {UiControl::checkbox, nullptr, 0x2f3758},
    {UiControl::number, nullptr, 0x2f3828},
    {UiControl::section, "Main", 0},
    {UiControl::checkbox, nullptr, 0x2f3738},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "retract_speed", 0x2f37f0},
    {SettingsControl::number, "delay", 0x2f3798},
    {SettingsControl::boolean, "randomize_delays", 0x2f37d0},
    {SettingsControl::boolean, "always_switch_to_weapon", 0x2f3778},
    {SettingsControl::boolean, "allow_throwables", 0x2f3758},
    {SettingsControl::number, "throw_speed", 0x2f3828},
    {SettingsControl::boolean, "require_not_mouse_over", 0x2f3738},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_auto_rod_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_auto_rod_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
