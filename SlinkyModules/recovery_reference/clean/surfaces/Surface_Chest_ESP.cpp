#include "../module_surface.hpp"

// Chest ESP: lib_win settings 0x33eb0. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "range", 0x2ecb18},
    {SettingsControl::boolean, "render_chest", 0x2ecb50},
    {SettingsControl::boolean, "render_ender_chest", 0x2ecb70},
    {SettingsControl::boolean, "render_trapped_chest", 0x2ecb90},
    {SettingsControl::boolean, "render_beacon", 0x2ecbb0},
    {SettingsControl::number, "line_width", 0x2ecbd0},
    {SettingsControl::color, "color_chest", 0x2ecc68},
    {SettingsControl::color, "color_ender_chest", 0x2ecc08},
    {SettingsControl::color, "color_trapped_chest", 0x2ecc28},
    {SettingsControl::color, "color_beacon", 0x2ecc48},
    {SettingsControl::boolean, "filled", 0x2ecc88},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_chest_esp_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Chest ESP: lib_win runtime UI 0x33d60.
extern "C" __declspec(dllexport) void recovered_chest_esp_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2ecb18);
    dependencies->section(ui, layout, "Target");
    dependencies->checkbox(layout, ui, image + 0x2ecb50);
    dependencies->checkbox(layout, ui, image + 0x2ecb70);
    dependencies->checkbox(layout, ui, image + 0x2ecb90);
    dependencies->checkbox(layout, ui, image + 0x2ecbb0);
    dependencies->section(ui, layout, "Customization");
    dependencies->number(layout, ui, image + 0x2ecbd0);
    if (image[0x2ecb68] == 1) {
        dependencies->color(layout, ui, image + 0x2ecc68);
    }
    if (image[0x2ecb88] == 1) {
        dependencies->color(layout, ui, image + 0x2ecc08);
    }
    if (image[0x2ecba8] == 1) {
        dependencies->color(layout, ui, image + 0x2ecc28);
    }
    if (image[0x2ecbc8] == 1) {
        dependencies->color(layout, ui, image + 0x2ecc48);
    }
    dependencies->checkbox(layout, ui, image + 0x2ecc88);
}
