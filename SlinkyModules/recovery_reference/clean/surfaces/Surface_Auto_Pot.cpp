#include "../module_surface.hpp"

// Auto Pot: lib_win settings 0x39670. 
// UI 0x39600.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2ef358},
    {UiControl::checkbox, nullptr, 0x2ef390},
    {UiControl::checkbox, nullptr, 0x2ef3b0},
    {UiControl::checkbox, nullptr, 0x2ef338},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "delay", 0x2ef358},
    {SettingsControl::boolean, "prevent_waste", 0x2ef390},
    {SettingsControl::boolean, "double_splash", 0x2ef3b0},
    {SettingsControl::boolean, "use_non_health", 0x2ef338},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_auto_pot_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_auto_pot_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
