#include "../module_surface.hpp"

// Criticals: lib_win settings 0x333d0. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::choice, "mode", 0x2ec2e0},
    {SettingsControl::number, "chance", 0x2ec258},
    {SettingsControl::number, "max_delay", 0x2ec220},
    {SettingsControl::number, "timer_speed", 0x2ec320},
    {SettingsControl::number, "boost", 0x2ec358},
    {SettingsControl::boolean, "require_weapon", 0x2ec2b0},
    {SettingsControl::boolean, "require_mouse_pressed", 0x2ec290},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_criticals_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Criticals: lib_win runtime UI 0x33310.
extern "C" __declspec(dllexport) void recovered_criticals_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, image + 0x2ec2e0);
    dependencies->number(layout, ui, image + 0x2ec258);
    if (read_surface_value<std::uint32_t>(image, 0x2ec310) != 0) {
        dependencies->number(layout, ui, image + 0x2ec320);
        dependencies->number(layout, ui, image + 0x2ec358);
    } else {
        dependencies->number(layout, ui, image + 0x2ec220);
    }
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2ec2b0);
    dependencies->checkbox(layout, ui, image + 0x2ec290);
}
