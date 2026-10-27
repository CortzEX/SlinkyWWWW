#include "../module_surface.hpp"

// Refill: lib_win settings 0x38c90. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::boolean, "refill_potion", 0x2ef068},
    {SettingsControl::boolean, "refill_potion_non_health", 0x2ef088},
    {SettingsControl::boolean, "refill_soup", 0x2ef048},
    {SettingsControl::choice, "simulate_button", 0x2ef0e8},
    {SettingsControl::number, "delay_after_open", 0x2eefd8},
    {SettingsControl::number, "delay_before_close", 0x2eefa0},
    {SettingsControl::number, "speed", 0x2ef010},
    {SettingsControl::boolean, "smart_speed", 0x2ef0a8},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_refill_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Refill: lib_win runtime UI 0x38bc0.
extern "C" __declspec(dllexport) void recovered_refill_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Items");
    dependencies->checkbox(layout, ui, image + 0x2ef068);
    if (image[0x2ef080] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2ef088);
    }
    dependencies->checkbox(layout, ui, image + 0x2ef048);
    dependencies->section(ui, layout, "Clicks");
    dependencies->choice(layout, ui, image + 0x2ef0e8);
    dependencies->number(layout, ui, image + 0x2eefd8);
    dependencies->number(layout, ui, image + 0x2eefa0);
    dependencies->number(layout, ui, image + 0x2ef010);
    dependencies->checkbox(layout, ui, image + 0x2ef0a8);
}
