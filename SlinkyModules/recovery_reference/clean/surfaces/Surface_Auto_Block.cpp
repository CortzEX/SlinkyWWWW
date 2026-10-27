#include "../module_surface.hpp"

// Auto Block: lib_win settings 0x31cf0. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "range", 0x2eb388},
    {SettingsControl::number, "max_hurt_time", 0x2eb2b0},
    {SettingsControl::number, "max_hold_time", 0x2eb208},
    {SettingsControl::boolean, "fake_block_animation", 0x2eb348},
    {SettingsControl::boolean, "fake_block_animation_require_target", 0x2eb368},
    {SettingsControl::number, "lag_chance", 0x2eb240},
    {SettingsControl::number, "lag_duration", 0x2eb278},
    {SettingsControl::boolean, "lag_flush_attack", 0x2eb3c0},
    {SettingsControl::boolean, "lag_reblock", 0x2eb3e0},
    {SettingsControl::boolean, "require_left_mouse_pressed", 0x2eb2e8},
    {SettingsControl::boolean, "require_right_mouse_pressed", 0x2eb308},
    {SettingsControl::boolean, "require_damage", 0x2eb328},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_auto_block_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Auto Block: lib_win runtime UI 0x31bb0.
extern "C" __declspec(dllexport) void recovered_auto_block_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2eb388);
    dependencies->number(layout, ui, image + 0x2eb2b0);
    dependencies->number(layout, ui, image + 0x2eb208);
    dependencies->section(ui, layout, "Force block animation");
    dependencies->checkbox(layout, ui, image + 0x2eb348);
    if (image[0x2eb360] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2eb368);
    }
    dependencies->section(ui, layout, "Lag");
    dependencies->number(layout, ui, image + 0x2eb240);
    dependencies->number(layout, ui, image + 0x2eb278);
    dependencies->checkbox(layout, ui, image + 0x2eb3c0);
    dependencies->checkbox(layout, ui, image + 0x2eb3e0);
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2eb2e8);
    dependencies->checkbox(layout, ui, image + 0x2eb308);
    dependencies->checkbox(layout, ui, image + 0x2eb328);
}
