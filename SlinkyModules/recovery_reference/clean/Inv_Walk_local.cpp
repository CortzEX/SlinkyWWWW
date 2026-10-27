#include "Inv_Walk.hpp"

// 0x39ea0 reloads both choices after rendering before choosing the next control.
extern "C" __declspec(dllexport) std::uint64_t recovered_inv_walk_typed_ui(
    std::uint64_t ui, std::uint64_t layout, InvWalkSettings *settings,
    UiDirtyState *dirty, const ChoiceUiEndpoints *endpoints) {
    endpoints->standard.section(ui, layout, "Main");
    const auto first = recovered_choice_control(layout, ui, &settings->mode,
        settings->mode_flag, dirty, endpoints->choice);
    if (!settings->mode.current) return first;
    recovered_choice_control(layout, ui, &settings->stop_on_click,
        settings->stop_on_click_flag, dirty, endpoints->choice);
    if (settings->stop_on_click.current != 2)
        recovered_number_control(layout, ui, &settings->stop_duration, dirty, &endpoints->standard.controls);
    endpoints->standard.section(ui, layout, "Other containers");
    return recovered_choice_control(layout, ui, &settings->stop_non_inventory,
        settings->stop_non_inventory_flag, dirty, endpoints->choice);
}

// 0x39f40 persists all choices regardless of which controls are visible.
extern "C" __declspec(dllexport) void recovered_inv_walk_typed_settings(
    SettingsContext *context, InvWalkSettings *settings, const ValueSettingsDependencies *dependencies) {
    recovered_choice_settings(context, "mode", &settings->mode, dependencies);
    recovered_choice_settings(context, "stop_on_click", &settings->stop_on_click, dependencies);
    recovered_number_settings(context, "stop_duration", &settings->stop_duration, dependencies);
    recovered_choice_settings(context, "stop_non_inv", &settings->stop_non_inventory, dependencies);
}

// 0x39fb0 indexes a separate Vanilla/Spoof label table.
extern "C" __declspec(dllexport) std::uint64_t recovered_inv_walk_label(
    char *destination, const ChoiceSetting *mode, const char *const *labels, FormatState *format) {
    return recovered_format(format, destination, 32, "%s", labels[mode->current]);
}
