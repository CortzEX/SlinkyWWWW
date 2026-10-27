#include "../module_surface.hpp"

// GUI: lib_win settings 0x32870. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::choice, "scale", 0x2eb970},
    {SettingsControl::color, "accent_color", 0x2eb720},
    {SettingsControl::boolean, "allow_input", 0x2eb9b0},
    {SettingsControl::boolean, "compact", 0x2eb9d0},
    {SettingsControl::boolean, "wide", 0x2eb9f0},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_gui_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// GUI: lib_win runtime UI 0x327d0.
extern "C" __declspec(dllexport) void recovered_gui_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, image + 0x2eb970);
    dependencies->color(layout, ui, image + 0x2eb720);
    dependencies->checkbox(layout, ui, image + 0x2eb9b0);
    dependencies->section(ui, layout, "Layout");
    dependencies->checkbox(layout, ui, image + 0x2eb9d0);
    dependencies->checkbox(layout, ui, image + 0x2eb9f0);
}
