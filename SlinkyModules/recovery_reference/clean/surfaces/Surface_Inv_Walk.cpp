#include "../module_surface.hpp"

// Inv Walk: lib_win settings 0x39f40. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::choice, "mode", 0x2ef5f0},
    {SettingsControl::choice, "stop_on_click", 0x2ef648},
    {SettingsControl::number, "stop_duration", 0x2ef688},
    {SettingsControl::choice, "stop_non_inv", 0x2ef6c0},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_inv_walk_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Inv Walk: lib_win runtime UI 0x39ea0.
extern "C" __declspec(dllexport) void recovered_inv_walk_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, image + 0x2ef5f0);
    if (read_surface_value<std::uint32_t>(image, 0x2ef620) == 0) {
        return;
    }
    dependencies->choice(layout, ui, image + 0x2ef648);
    if (read_surface_value<std::uint32_t>(image, 0x2ef678) != 2) {
        dependencies->number(layout, ui, image + 0x2ef688);
    }
    dependencies->section(ui, layout, "Other containers");
    dependencies->choice(layout, ui, image + 0x2ef6c0);
}
