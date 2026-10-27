#include "../module_surface.hpp"

// Aim Assist: lib_win settings 0x2bd00. 
static constexpr SettingsStep settings_steps[] = {
    {SettingsControl::choice, "mode", 0x2e8ff0},
    {SettingsControl::number, "hor_speed", 0x2e8f20},
    {SettingsControl::number, "ver_speed", 0x2e8f58},
    {SettingsControl::boolean, "lock_on_vertical", 0x2e8f90},
    {SettingsControl::boolean, "silent_move_correct", 0x2e9050},
    {SettingsControl::boolean, "silent_ignore_manual_aim", 0x2e9030},
    {SettingsControl::number, "predict", 0x2e9190},
    {SettingsControl::number, "aim_randomization", 0x2e9238},
    {SettingsControl::number, "hor_hitbox_correct", 0x2e91c8},
    {SettingsControl::number, "ver_hitbox_correct", 0x2e9200},
    {SettingsControl::choice, "mode_target", 0x2e9150},
    {SettingsControl::choice, "sort_by", 0x2e92f0},
    {SettingsControl::boolean, "allow_exceed_fov", 0x2e9290},
    {SettingsControl::range, "range", 0x2e9070},
    {SettingsControl::range, "fov", 0x2e8ed0},
    {SettingsControl::boolean, "require_sprint", 0x2e90c0},
    {SettingsControl::boolean, "require_mouse_pressed", 0x2e90e0},
    {SettingsControl::boolean, "require_mouse_moved", 0x2e8fb0},
    {SettingsControl::boolean, "disable_on_block_break", 0x2e9100},
    {SettingsControl::boolean, "require_weapon", 0x2e9120},
    {SettingsControl::boolean, "ignore_invis", 0x2e9270},
    {SettingsControl::boolean, "require_line_of_sight", 0x2e92b0},
};
static constexpr ModuleSurface surface{nullptr, 0,
                                      settings_steps, std::size(settings_steps)};

extern "C" __declspec(dllexport) void recovered_aim_assist_settings(
    SettingsContext *context, std::uint8_t *image,
    const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface, context, image, *dependencies);
}

// Aim Assist: lib_win runtime UI 0x2bae0.
extern "C" __declspec(dllexport) void recovered_aim_assist_ui(
    std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Aim");
    dependencies->choice(layout, ui, image + 0x2e8ff0);
    const auto mode = read_surface_value<std::uint32_t>(image, 0x2e9020);
    if (mode == 2) {
        dependencies->checkbox(layout, ui, image + 0x2e8f90);
    } else {
        if (mode == 3) {
            dependencies->checkbox(layout, ui, image + 0x2e9050);
            dependencies->checkbox(layout, ui, image + 0x2e9030);
        }
        dependencies->number(layout, ui, image + 0x2e8f20);
        dependencies->number(layout, ui, image + 0x2e8f58);
    }
    dependencies->number(layout, ui, image + 0x2e9190);
    dependencies->number(layout, ui, image + 0x2e9238);
    dependencies->section(ui, layout, "Multi-point");
    dependencies->number(layout, ui, image + 0x2e91c8);
    dependencies->number(layout, ui, image + 0x2e9200);
    dependencies->section(ui, layout, "Target");
    dependencies->choice(layout, ui, image + 0x2e9150);
    const auto target_mode = read_surface_value<std::uint32_t>(image, 0x2e9180);
    if (target_mode == 1) {
        dependencies->choice(layout, ui, image + 0x2e92f0);
    } else if (target_mode == 0) {
        dependencies->checkbox(layout, ui, image + 0x2e9290);
    }
    dependencies->range(layout, ui, image + 0x2e9070);
    dependencies->range(layout, ui, image + 0x2e8ed0);
    dependencies->section(ui, layout, "Conditions");
    if (read_surface_value<std::uint32_t>(image, 0x2e9020) != 3) {
        dependencies->checkbox(layout, ui, image + 0x2e90c0);
    }
    dependencies->checkbox(layout, ui, image + 0x2e90e0);
    dependencies->checkbox(layout, ui, image + 0x2e8fb0);
    dependencies->checkbox(layout, ui, image + 0x2e9100);
    dependencies->checkbox(layout, ui, image + 0x2e9120);
    dependencies->checkbox(layout, ui, image + 0x2e9270);
    dependencies->checkbox(layout, ui, image + 0x2e92b0);
}
