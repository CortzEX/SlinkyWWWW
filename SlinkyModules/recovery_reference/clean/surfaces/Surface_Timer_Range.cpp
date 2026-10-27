#include "../module_surface.hpp"

// Timer Range: lib_win settings 0x43ad0. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::choice, "mode", 0x2f33e0},
    {SettingsControl::number, "min_dist", 0x2f34e8},
    {SettingsControl::number, "duration", 0x2f3478},
    {SettingsControl::number, "duration_legit", 0x2f34b0},
    {SettingsControl::number, "cooldown", 0x2f3440},
    {SettingsControl::boolean, "block_while_frozen", 0x2f3420},
    {SettingsControl::boolean, "require_mouse_pressed", 0x2f3370},
    {SettingsControl::boolean, "require_weapon", 0x2f3390},
    {SettingsControl::boolean, "require_not_using_item", 0x2f33b0},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_timer_range_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Timer Range: lib_win runtime UI 0x439e0.
extern "C" __declspec(dllexport) void recovered_timer_range_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, image + 0x2f33e0);
    dependencies->number(layout, ui, image + 0x2f34e8);
    dependencies->number(layout, ui, image + (read_surface_value<std::uint32_t>(image, 0x2f3410) == 0 ? 0x2f3478 : 0x2f34b0));
    dependencies->number(layout, ui, image + 0x2f3440);
    if (read_surface_value<std::uint32_t>(image, 0x2f3410) == 0) {
        dependencies->checkbox(layout, ui, image + 0x2f3420);
    }
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2f3370);
    dependencies->checkbox(layout, ui, image + 0x2f3390);
    dependencies->checkbox(layout, ui, image + 0x2f33b0);
}
