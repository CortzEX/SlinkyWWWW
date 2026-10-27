#include "../module_surface.hpp"

// Auto Soup: lib_win settings 0x2dc70. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "single_soup_max_hp", 0x2e98c0},
    {SettingsControl::number, "double_soup_max_hp", 0x2e9930},
    {SettingsControl::number, "randomization", 0x2e99d8},
    {SettingsControl::number, "delay_before", 0x2e98f8},
    {SettingsControl::number, "delay_between", 0x2e9968},
    {SettingsControl::number, "delay_after", 0x2e99a0},
    {SettingsControl::boolean, "drop_bowls", 0x2e9a30},
    {SettingsControl::boolean, "override_item", 0x2e9a10},
    {SettingsControl::list, "allowed_items", 0x2e9a50},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_auto_soup_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Auto Soup: lib_win runtime UI 0x2db50.
extern "C" __declspec(dllexport) void recovered_auto_soup_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Maximum health");
    dependencies->number(layout, ui, image + 0x2e98c0);
    if (read_surface_value<float>(image, 0x2e9960) > read_surface_value<float>(image, 0x2e98f0)) {
        std::memcpy(image + 0x2e9960, image + 0x2e98f0, sizeof(float));
    }
    dependencies->number(layout, ui, image + 0x2e9930);
    dependencies->section(ui, layout, "Delays");
    dependencies->number(layout, ui, image + 0x2e99d8);
    dependencies->number(layout, ui, image + 0x2e98f8);
    dependencies->number(layout, ui, image + 0x2e9968);
    dependencies->number(layout, ui, image + 0x2e99a0);
    dependencies->section(ui, layout, "Extra");
    dependencies->checkbox(layout, ui, image + 0x2e9a30);
    dependencies->checkbox(layout, ui, image + 0x2e9a10);
    if (image[0x2e9a28] == 1) {
        dependencies->list(layout, ui, image + 0x2e9a50);
    }
}
