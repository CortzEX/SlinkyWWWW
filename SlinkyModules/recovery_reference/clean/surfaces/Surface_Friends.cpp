#include "../module_surface.hpp"

// Friends: lib_win settings 0x3b640. 
// UI 0x3b600.
static constexpr UiStep ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::checkbox, nullptr, 0x2f0248},
};
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::boolean, "middle_click_add", 0x2f0248},
    {SettingsControl::list, "friends", 0x2f0268},
};
static constexpr ModuleSurface surface{ui_steps, std::size(ui_steps),
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_friends_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void recovered_friends_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}
