#include "../module_surface.hpp"

// Weapons: lib_win settings 0x38330. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::boolean, "fist", 0x2eeb40},
    {SettingsControl::boolean, "swords", 0x2eed00},
    {SettingsControl::boolean, "axes", 0x2eece0},
    {SettingsControl::list, "extra_items", 0x2eed20},
    {SettingsControl::boolean, "enchant_sharpness", 0x2eec80},
    {SettingsControl::boolean, "enchant_knockback", 0x2eeca0},
    {SettingsControl::boolean, "enchant_fire_aspect", 0x2eecc0},
    {SettingsControl::boolean, "1", 0x2eeb60},
    {SettingsControl::boolean, "2", 0x2eeb80},
    {SettingsControl::boolean, "3", 0x2eeba0},
    {SettingsControl::boolean, "4", 0x2eebc0},
    {SettingsControl::boolean, "5", 0x2eebe0},
    {SettingsControl::boolean, "6", 0x2eec00},
    {SettingsControl::boolean, "7", 0x2eec20},
    {SettingsControl::boolean, "8", 0x2eec40},
    {SettingsControl::boolean, "9", 0x2eec60},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_weapons_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Weapons: lib_win runtime UI 0x381c0.
extern "C" __declspec(dllexport) void recovered_weapons_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Item types");
    dependencies->checkbox(layout, ui, image + 0x2eeb40);
    dependencies->checkbox(layout, ui, image + 0x2eed00);
    dependencies->checkbox(layout, ui, image + 0x2eece0);
    dependencies->list(layout, ui, image + 0x2eed20);
    dependencies->section(ui, layout, "Any item with");
    dependencies->checkbox(layout, ui, image + 0x2eec80);
    dependencies->checkbox(layout, ui, image + 0x2eeca0);
    dependencies->checkbox(layout, ui, image + 0x2eecc0);
    dependencies->section(ui, layout, "Any item in");
    dependencies->checkbox(layout, ui, image + 0x2eeb60);
    dependencies->checkbox(layout, ui, image + 0x2eeb80);
    dependencies->checkbox(layout, ui, image + 0x2eeba0);
    dependencies->checkbox(layout, ui, image + 0x2eebc0);
    dependencies->checkbox(layout, ui, image + 0x2eebe0);
    dependencies->checkbox(layout, ui, image + 0x2eec00);
    dependencies->checkbox(layout, ui, image + 0x2eec20);
    dependencies->checkbox(layout, ui, image + 0x2eec40);
    dependencies->checkbox(layout, ui, image + 0x2eec60);
}
