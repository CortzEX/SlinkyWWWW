#include "Sprint_Reset.hpp"

// 0x3afc0 uses the shared choice, number and checkbox controls in this order.
extern "C" __declspec(dllexport) std::uint64_t recovered_sprint_reset_typed_ui(std::uint64_t ui,
    std::uint64_t layout, SprintResetSettings *settings, UiDirtyState *dirty, const ChoiceUiEndpoints *endpoints) {
    const auto &standard = endpoints->standard;
    standard.section(ui, layout, "Main");
    recovered_choice_control(layout, ui, &settings->mode, settings->choice_flag, dirty, endpoints->choice);
    recovered_number_control(layout, ui, &settings->delay, dirty, &standard.controls);
    recovered_number_control(layout, ui, &settings->duration, dirty, &standard.controls);
    recovered_checkbox_control(layout, ui, &settings->randomize, dirty, &standard.controls);
    standard.section(ui, layout, "Conditions");
    recovered_checkbox_control(layout, ui, &settings->wait_for_damage, dirty, &standard.controls);
    return recovered_checkbox_control(layout, ui, &settings->require_weapon, dirty, &standard.controls);
}
// 0x3b070 persists each setting independently of the selected mode.
extern "C" __declspec(dllexport) void recovered_sprint_reset_typed_settings(SettingsContext *context,
    SprintResetSettings *settings, const SettingsDependencies *booleans, const ValueSettingsDependencies *values) {
    recovered_choice_settings(context, "mode", &settings->mode, values);
    recovered_number_settings(context, "delay", &settings->delay, values);
    recovered_number_settings(context, "duration", &settings->duration, values);
    recovered_boolean_settings(context, "randomize", &settings->randomize, booleans);
    recovered_boolean_settings(context, "wait_for_damage", &settings->wait_for_damage, booleans);
    recovered_boolean_settings(context, "require_weapon", &settings->require_weapon, booleans);
}
// 0x3b110 indexes an independent label table, not the choice control's options.
extern "C" __declspec(dllexport) std::uint64_t recovered_sprint_reset_label(char *destination,
    const ChoiceSetting *mode, const char *const *labels, FormatState *format) {
    return recovered_format(format, destination, 32, "%s", labels[mode->current]);
}
