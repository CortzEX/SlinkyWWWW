#include "../module_surface.hpp"

// Velocity: lib_win settings 0x30a90. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::choice, "mode", 0x2eaa20},
    {SettingsControl::number, "reduce_chance", 0x2eab98},
    {SettingsControl::number, "fov", 0x2eac40},
    {SettingsControl::number, "reduce_amount", 0x2eac08},
    {SettingsControl::number, "reduce_delay", 0x2eabd0},
    {SettingsControl::number, "jump_chance", 0x2eac78},
    {SettingsControl::boolean, "reduce_multiple_per_tick", 0x2eab78},
    {SettingsControl::choice, "ignore_vertical", 0x2eab38},
    {SettingsControl::number, "ignore_chance", 0x2eaa60},
    {SettingsControl::boolean, "require_target", 0x2eaaf8},
    {SettingsControl::boolean, "require_mouse", 0x2eaab8},
    {SettingsControl::boolean, "require_forward", 0x2eaa98},
    {SettingsControl::boolean, "require_weapon", 0x2eaad8},
    {SettingsControl::boolean, "require_sprinting_jump", 0x2eacb0},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_velocity_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Velocity: lib_win runtime UI 0x30930.
extern "C" __declspec(dllexport) void recovered_velocity_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, image + 0x2eaa20);
    switch (read_surface_value<std::uint32_t>(image, 0x2eaa50)) {
    case 0:
        dependencies->number(layout, ui, image + 0x2eab98);
        dependencies->number(layout, ui, image + 0x2eac40);
        dependencies->number(layout, ui, image + 0x2eac08);
        dependencies->number(layout, ui, image + 0x2eabd0);
        break;
    case 1:
        dependencies->number(layout, ui, image + 0x2eac78);
        break;
    case 2:
        dependencies->checkbox(layout, ui, image + 0x2eab78);
        break;
    case 3:
        dependencies->choice(layout, ui, image + 0x2eab38);
        dependencies->number(layout, ui, image + 0x2eaa60);
        break;
    }
    dependencies->section(ui, layout, "Conditions");
    if (read_surface_value<std::uint32_t>(image, 0x2eaa50) != 2) {
        dependencies->checkbox(layout, ui, image + 0x2eaaf8);
        dependencies->checkbox(layout, ui, image + 0x2eaab8);
    }
    dependencies->checkbox(layout, ui, image + 0x2eaa98);
    dependencies->checkbox(layout, ui, image + 0x2eaad8);
    if (read_surface_value<std::uint32_t>(image, 0x2eaa50) == 1) {
        dependencies->checkbox(layout, ui, image + 0x2eacb0);
    }
}
