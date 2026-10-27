#include "../module_surface.hpp"

// No Slow: lib_win settings 0x42b20. 
// UI 0x42ac0.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Retained speed", 0},
    {UiControl::number, nullptr, 0x2f2ed8},
    {UiControl::number, nullptr, 0x2f2ea0},
    {UiControl::number, nullptr, 0x2f2f10},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "mult_sword", 0x2f2ed8},
    {SettingsControl::number, "mult_bow", 0x2f2ea0},
    {SettingsControl::number, "mult_consumables", 0x2f2f10},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_no_slow_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_no_slow_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
