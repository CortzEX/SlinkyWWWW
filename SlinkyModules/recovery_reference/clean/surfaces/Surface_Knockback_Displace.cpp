#include "../module_surface.hpp"

// Knockback Displace: lib_win settings 0x4aa20. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::choice, "direction", 0x2f6088},
    {SettingsControl::boolean, "use_last_strafe", 0x2f60e8},
    {SettingsControl::number, "angle", 0x2f5fa8},
    {SettingsControl::number, "cooldown", 0x2f5f70},
    {SettingsControl::boolean, "hide_rotation", 0x2f60c8},
    {SettingsControl::boolean, "require_no_kb", 0x2f5fe0},
    {SettingsControl::boolean, "require_weapon", 0x2f6000},
    {SettingsControl::boolean, "require_kb_enchant", 0x2f6020},
    {SettingsControl::boolean, "require_facing_away", 0x2f6040},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_knockback_displace_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Knockback Displace: lib_win runtime UI 0x4a930.
extern "C" __declspec(dllexport) void recovered_knockback_displace_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, image + 0x2f6088);
    const auto mode = read_surface_value<std::uint32_t>(image, 0x2f60b8);
    if (mode == 3 || mode == 4) {
        dependencies->checkbox(layout, ui, image + 0x2f60e8);
    }
    dependencies->number(layout, ui, image + 0x2f5f70);
    dependencies->number(layout, ui, image + 0x2f5fa8);
    dependencies->checkbox(layout, ui, image + 0x2f60c8);
    dependencies->section(ui, layout, "Condition");
    dependencies->checkbox(layout, ui, image + 0x2f5fe0);
    dependencies->checkbox(layout, ui, image + 0x2f6000);
    dependencies->checkbox(layout, ui, image + 0x2f6020);
    dependencies->checkbox(layout, ui, image + 0x2f6040);
}
