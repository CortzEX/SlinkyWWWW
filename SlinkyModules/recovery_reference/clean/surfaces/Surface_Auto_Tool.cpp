#include "../module_surface.hpp"

// Auto Tool: lib_win settings 0x375e0. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::number, "activation_time", 0x2ee370},
    {SettingsControl::boolean, "switch_back", 0x2ee468},
    {SettingsControl::boolean, "allow_using_sword", 0x2ee3c8},
    {SettingsControl::boolean, "allow_using_tools", 0x2ee3e8},
    {SettingsControl::boolean, "allow_using_fists", 0x2ee3a8},
    {SettingsControl::boolean, "allow_using_other", 0x2ee408},
    {SettingsControl::boolean, "require_sneak", 0x2ee428},
    {SettingsControl::boolean, "restrict_allowed_blocks", 0x2ee448},
    {SettingsControl::list, "allowed_blocks", 0x2ee488},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_auto_tool_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Auto Tool: lib_win runtime UI 0x374e0.
extern "C" __declspec(dllexport) void recovered_auto_tool_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2ee370);
    dependencies->checkbox(layout, ui, image + 0x2ee468);
    dependencies->section(ui, layout, "Allow while using");
    dependencies->checkbox(layout, ui, image + 0x2ee3c8);
    dependencies->checkbox(layout, ui, image + 0x2ee3e8);
    dependencies->checkbox(layout, ui, image + 0x2ee3a8);
    dependencies->checkbox(layout, ui, image + 0x2ee408);
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2ee428);
    dependencies->checkbox(layout, ui, image + 0x2ee448);
    if (image[0x2ee460] == 1) {
        dependencies->list(layout, ui, image + 0x2ee488);
    }
}
