#include "../module_surface.hpp"

// Fast Mine: lib_win settings 0x41c80. 
// UI 0x41c20.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2f1ff8},
    {UiControl::number, nullptr, 0x2f1fa0},
    {UiControl::checkbox, nullptr, 0x2f1fd8},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "speed", 0x2f1ff8},
    {SettingsControl::number, "break_delay", 0x2f1fa0},
    {SettingsControl::boolean, "decr_block_hit_delay", 0x2f1fd8},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_fast_mine_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_fast_mine_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
