#include "../module_surface.hpp"

// Mod Overlay: lib_win settings 0x34b90. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::boolean, "show_combat", 0x2ed100},
    {SettingsControl::boolean, "show_move", 0x2ed120},
    {SettingsControl::boolean, "show_block", 0x2ed140},
    {SettingsControl::boolean, "show_visual", 0x2ed160},
    {SettingsControl::boolean, "show_utility", 0x2ed180},
    {SettingsControl::number, "text_size", 0x2ed200},
    {SettingsControl::number, "padding_x", 0x2ed2b0},
    {SettingsControl::number, "padding_y", 0x2ed2e8},
    {SettingsControl::number, "bg_rounding", 0x2ed278},
    {SettingsControl::color, "name_color", 0x2ed238},
    {SettingsControl::color, "details_color", 0x2ed258},
    {SettingsControl::boolean, "lowercase", 0x2ed1c0},
    {SettingsControl::boolean, "show_details", 0x2ed1e0},
    {SettingsControl::boolean, "require_bound", 0x2ed1a0},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_mod_overlay_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Mod Overlay: lib_win runtime UI 0x34a40.
extern "C" __declspec(dllexport) void recovered_mod_overlay_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Visible categories");
    dependencies->checkbox(layout, ui, image + 0x2ed100);
    dependencies->checkbox(layout, ui, image + 0x2ed120);
    dependencies->checkbox(layout, ui, image + 0x2ed140);
    dependencies->checkbox(layout, ui, image + 0x2ed160);
    dependencies->checkbox(layout, ui, image + 0x2ed180);
    dependencies->section(ui, layout, "Customization");
    dependencies->number(layout, ui, image + 0x2ed200);
    dependencies->number(layout, ui, image + 0x2ed2b0);
    dependencies->number(layout, ui, image + 0x2ed2e8);
    dependencies->number(layout, ui, image + 0x2ed278);
    dependencies->color(layout, ui, image + 0x2ed238);
    dependencies->color(layout, ui, image + 0x2ed258);
    dependencies->checkbox(layout, ui, image + 0x2ed1c0);
    dependencies->checkbox(layout, ui, image + 0x2ed1e0);
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2ed1a0);
}
