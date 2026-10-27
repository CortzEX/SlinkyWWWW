#include "../module_surface.hpp"

// Inv Manager: lib_win settings 0x476e0. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "delay_after_open", 0x2f4e50},
    {SettingsControl::number, "speed", 0x2f5230},
    {SettingsControl::boolean, "smart_speed", 0x2f5268},
    {SettingsControl::boolean, "randomize", 0x2f5210},
    {SettingsControl::boolean, "equip_armor", 0x2f4e88},
    {SettingsControl::boolean, "sort_hotbar", 0x2f4ea8},
    {SettingsControl::boolean, "sort_hotbar_fallback", 0x2f51f0},
    {SettingsControl::choice, "1", 0x2f4fb0},
    {SettingsControl::choice, "2", 0x2f4ff0},
    {SettingsControl::choice, "3", 0x2f5030},
    {SettingsControl::choice, "4", 0x2f5070},
    {SettingsControl::choice, "5", 0x2f50b0},
    {SettingsControl::choice, "6", 0x2f50f0},
    {SettingsControl::choice, "7", 0x2f5130},
    {SettingsControl::choice, "8", 0x2f5170},
    {SettingsControl::choice, "9", 0x2f51b0},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_inv_manager_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Inv Manager: lib_win runtime UI 0x47560.
extern "C" __declspec(dllexport) void recovered_inv_manager_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2f4e50);
    dependencies->number(layout, ui, image + 0x2f5230);
    dependencies->checkbox(layout, ui, image + 0x2f5268);
    dependencies->checkbox(layout, ui, image + 0x2f5210);
    dependencies->section(ui, layout, "Equip armor");
    dependencies->checkbox(layout, ui, image + 0x2f4e88);
    dependencies->section(ui, layout, "Sort hotbar");
    dependencies->checkbox(layout, ui, image + 0x2f4ea8);
    if (image[0x2f4ec0] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2f51f0);
        dependencies->choice(layout, ui, image + 0x2f4fb0);
        dependencies->choice(layout, ui, image + 0x2f4ff0);
        dependencies->choice(layout, ui, image + 0x2f5030);
        dependencies->choice(layout, ui, image + 0x2f5070);
        dependencies->choice(layout, ui, image + 0x2f50b0);
        dependencies->choice(layout, ui, image + 0x2f50f0);
        dependencies->choice(layout, ui, image + 0x2f5130);
        dependencies->choice(layout, ui, image + 0x2f5170);
        dependencies->choice(layout, ui, image + 0x2f51b0);
    }
}
