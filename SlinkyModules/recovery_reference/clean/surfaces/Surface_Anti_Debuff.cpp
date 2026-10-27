#include "../module_surface.hpp"

// Anti Debuff: lib_win settings 0x44a10. 
// UI 0x449c0.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Effects", 0},
    {UiControl::checkbox, nullptr, 0x2f3a70},
    {UiControl::checkbox, nullptr, 0x2f3a90},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::boolean, "blindness", 0x2f3a70},
    {SettingsControl::boolean, "nausea", 0x2f3a90},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_anti_debuff_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_anti_debuff_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
