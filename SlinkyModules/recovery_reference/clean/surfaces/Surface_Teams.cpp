#include "../module_surface.hpp"

// Teams: lib_win settings 0x32130. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::boolean, "match_self_color", 0x2eb610},
    {SettingsControl::list, "team_colors", 0x2eb630},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_teams_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Teams: lib_win runtime UI 0x320e0.
extern "C" __declspec(dllexport) void recovered_teams_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->checkbox(layout, ui, image + 0x2eb610);
    dependencies->list(layout, ui, image + 0x2eb630);
}
