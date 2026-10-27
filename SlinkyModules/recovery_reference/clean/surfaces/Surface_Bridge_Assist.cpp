#include "../module_surface.hpp"

// Bridge Assist: lib_win settings 0x2e6c0. 
// UI 0x2e5d0.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2e9dc8},
    {UiControl::number, nullptr, 0x2e9e40},
    {UiControl::choice, nullptr, 0x2e9d48},
    {UiControl::checkbox, nullptr, 0x2e9e00},
    {UiControl::checkbox, nullptr, 0x2e9da8},
    {UiControl::checkbox, nullptr, 0x2e9e20},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2e9cd0},
    {UiControl::checkbox, nullptr, 0x2e9d88},
    {UiControl::checkbox, nullptr, 0x2e9cf0},
    {UiControl::checkbox, nullptr, 0x2e9d10},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "edge_offset", 0x2e9dc8},
    {SettingsControl::number, "unsneak_delay", 0x2e9e40},
    {SettingsControl::choice, "select_blocks", 0x2e9d48},
    {SettingsControl::boolean, "randomize", 0x2e9e00},
    {SettingsControl::boolean, "sneak_on_jump", 0x2e9da8},
    {SettingsControl::boolean, "avoid_double_sneak", 0x2e9e20},
    {SettingsControl::boolean, "require_sneak", 0x2e9cd0},
    {SettingsControl::boolean, "require_holding_blocks", 0x2e9d88},
    {SettingsControl::boolean, "require_looking_down", 0x2e9cf0},
    {SettingsControl::boolean, "require_not_forward", 0x2e9d10},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_bridge_assist_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_bridge_assist_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
