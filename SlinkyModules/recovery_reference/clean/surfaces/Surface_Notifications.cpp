#include "../module_surface.hpp"

// Notifications: lib_win settings 0x35c80. 
// UI 0x35bb0.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Hide if", 0},
    {UiControl::checkbox, nullptr, 0x2ed610},
    {UiControl::checkbox, nullptr, 0x2ed550},
    {UiControl::checkbox, nullptr, 0x2ed530},
    {UiControl::section, "Visible mod categories", 0},
    {UiControl::checkbox, nullptr, 0x2ed570},
    {UiControl::checkbox, nullptr, 0x2ed590},
    {UiControl::checkbox, nullptr, 0x2ed5b0},
    {UiControl::checkbox, nullptr, 0x2ed5d0},
    {UiControl::checkbox, nullptr, 0x2ed5f0},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::boolean, "hide_ingame", 0x2ed610},
    {SettingsControl::boolean, "hide_hold_notifs", 0x2ed550},
    {SettingsControl::boolean, "hide_bind_only", 0x2ed530},
    {SettingsControl::boolean, "show_combat", 0x2ed570},
    {SettingsControl::boolean, "show_move", 0x2ed590},
    {SettingsControl::boolean, "show_block", 0x2ed5b0},
    {SettingsControl::boolean, "show_visual", 0x2ed5d0},
    {SettingsControl::boolean, "show_utility", 0x2ed5f0},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_notifications_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_notifications_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
