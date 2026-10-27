#include "../module_surface.hpp"

// Hit Select: lib_win settings 0x37cf0. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::choice, "mode", 0x2ee870},
    {SettingsControl::number, "cancel_rate", 0x2ee7e0},
    {SettingsControl::number, "cancel_rate_air", 0x2ee700},
    {SettingsControl::number, "pause_dur", 0x2ee738},
    {SettingsControl::number, "wait_for_damage_dur", 0x2ee770},
    {SettingsControl::number, "trades_delay", 0x2ee7a8},
    {SettingsControl::boolean, "use_server_time", 0x2ee8b0},
    {SettingsControl::boolean, "fake_swing", 0x2ee910},
    {SettingsControl::boolean, "crits_allow_reduce", 0x2ee8d0},
    {SettingsControl::boolean, "require_damage", 0x2ee8f0},
    {SettingsControl::boolean, "require_sprint", 0x2ee818},
    {SettingsControl::boolean, "require_weapon", 0x2ee838},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_hit_select_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Hit Select: lib_win runtime UI 0x37bb0.
extern "C" __declspec(dllexport) void recovered_hit_select_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, image + 0x2ee870);
    dependencies->number(layout, ui, image + 0x2ee738);
    if (read_surface_value<std::uint32_t>(image, 0x2ee8a0) == 0) {
        dependencies->number(layout, ui, image + 0x2ee770);
        dependencies->number(layout, ui, image + 0x2ee7a8);
    }
    dependencies->checkbox(layout, ui, image + 0x2ee8b0);
    dependencies->checkbox(layout, ui, image + 0x2ee910);
    if (read_surface_value<std::uint32_t>(image, 0x2ee8a0) == 1) {
        dependencies->checkbox(layout, ui, image + 0x2ee8d0);
        dependencies->checkbox(layout, ui, image + 0x2ee8f0);
    }
    dependencies->section(ui, layout, "Cancel rate");
    dependencies->number(layout, ui, image + 0x2ee7e0);
    dependencies->number(layout, ui, image + 0x2ee700);
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2ee818);
    dependencies->checkbox(layout, ui, image + 0x2ee838);
}
