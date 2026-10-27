#include "../module_surface.hpp"

// Debug: lib_win settings 0x46a60. 
// UI 0x46a00.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::checkbox, nullptr, 0x2f4680},
    {UiControl::checkbox, nullptr, 0x2f4640},
    {UiControl::checkbox, nullptr, 0x2f4660},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::boolean, "clicks", 0x2f4680},
    {SettingsControl::boolean, "hurt_time", 0x2f4640},
    {SettingsControl::boolean, "item_use_state", 0x2f4660},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_debug_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_debug_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
