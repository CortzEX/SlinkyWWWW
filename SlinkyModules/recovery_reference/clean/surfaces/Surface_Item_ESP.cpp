#include "../module_surface.hpp"

// Item ESP: lib_win settings 0x417b0. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "range", 0x2f1cb0},
    {SettingsControl::boolean, "show_count", 0x2f1c90},
    {SettingsControl::list, "allowed_items", 0x2f1d28},
    {SettingsControl::boolean, "highlight_all", 0x2f1d08},
    {SettingsControl::color, "default_color", 0x2f1ce8},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_item_esp_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Item ESP: lib_win runtime UI 0x41700.
extern "C" __declspec(dllexport) void recovered_item_esp_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f1cb0);
    dependencies->section(ui, layout, "Customization");
    dependencies->checkbox(layout, ui, image + 0x2f1c90);
    dependencies->list(layout, ui, image + 0x2f1d28);
    dependencies->checkbox(layout, ui, image + 0x2f1d08);
    if (image[0x2f1d20] == 1) {
        dependencies->color(layout, ui, image + 0x2f1ce8);
    }
}
