#include "../module_surface.hpp"

// No Hit Delay: lib_win settings 0x3e670. 
// UI 0x3e630.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "In-game", 0},
    {UiControl::choice, nullptr, 0x2f0d90},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::choice, "mode", 0x2f0d90},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_no_hit_delay_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_no_hit_delay_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
