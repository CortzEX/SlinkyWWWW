#include "../module_surface.hpp"

// Auto Clicker: lib_win settings 0x2d290. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::choice, "pattern", 0x2e9650},
    {SettingsControl::number, "target_cps", 0x2e95e8},
    {SettingsControl::boolean, "randomize_cps", 0x2e9620},
    {SettingsControl::boolean, "exhaust", 0x2e9690},
    {SettingsControl::boolean, "allow_block_break", 0x2e9588},
    {SettingsControl::boolean, "allow_inventory", 0x2e9548},
    {SettingsControl::boolean, "inventory_randomize", 0x2e9568},
    {SettingsControl::boolean, "require_weapon", 0x2e95a8},
    {SettingsControl::boolean, "require_not_using_item", 0x2e95c8},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_auto_clicker_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Auto Clicker: lib_win runtime UI 0x2d190.
extern "C" __declspec(dllexport) void recovered_auto_clicker_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "In-game");
    dependencies->choice(layout, ui, image + 0x2e9650);
    dependencies->number(layout, ui, image + 0x2e95e8);
    dependencies->checkbox(layout, ui, image + 0x2e9620);
    dependencies->checkbox(layout, ui, image + 0x2e9690);
    dependencies->checkbox(layout, ui, image + 0x2e9588);
    dependencies->section(ui, layout, "Inventory");
    dependencies->checkbox(layout, ui, image + 0x2e9548);
    if (image[0x2e9560] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2e9568);
    }
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2e95a8);
    dependencies->checkbox(layout, ui, image + 0x2e95c8);
}
