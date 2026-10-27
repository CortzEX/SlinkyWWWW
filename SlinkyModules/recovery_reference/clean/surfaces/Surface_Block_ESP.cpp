#include "../module_surface.hpp"

// Block ESP: lib_win settings 0x3fbe0. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "range", 0x2f1a28},
    {SettingsControl::list, "allowed_blocks", 0x2f1950},
    {SettingsControl::boolean, "should_limit_block_render", 0x2f1a60},
    {SettingsControl::number, "block_render_limit", 0x2f19f0},
    {SettingsControl::number, "line_width", 0x2f19b8},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_block_esp_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Block ESP: lib_win runtime UI 0x3fb30.
extern "C" __declspec(dllexport) void recovered_block_esp_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f1a28);
    dependencies->list(layout, ui, image + 0x2f1950);
    dependencies->section(ui, layout, "Block render limit");
    dependencies->checkbox(layout, ui, image + 0x2f1a60);
    if (image[0x2f1a78] == 1) {
        dependencies->number(layout, ui, image + 0x2f19f0);
    }
    dependencies->section(ui, layout, "Customization");
    dependencies->number(layout, ui, image + 0x2f19b8);
}
