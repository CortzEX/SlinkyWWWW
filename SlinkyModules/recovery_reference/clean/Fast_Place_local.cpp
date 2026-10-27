#include "Fast_Place.hpp"

// 0x2fee0 renders both numeric controls and returns the last wrapper's full word.
extern "C" __declspec(dllexport) std::uint64_t recovered_fast_place_typed_ui(
    std::uint64_t ui, std::uint64_t layout, FastPlaceSettings *settings,
    UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Main");
    recovered_number_control(layout, ui, &settings->maximum_cps, dirty, &endpoints->controls);
    return recovered_number_control(layout, ui, &settings->activation_delay, dirty, &endpoints->controls);
}

// 0x2ff30 persists both controls without normalizing captured saved values.
extern "C" __declspec(dllexport) void recovered_fast_place_typed_settings(
    SettingsContext *context, FastPlaceSettings *settings, const ValueSettingsDependencies *endpoints) {
    recovered_number_settings(context, "max_cps", &settings->maximum_cps, endpoints);
    recovered_number_settings(context, "activate_delay", &settings->activation_delay, endpoints);
}

// 0x2ff70 promotes the current binary32 value to the original binary64 argument.
extern "C" __declspec(dllexport) std::uint64_t recovered_fast_place_label(
    char *destination, const FastPlaceSettings *settings, FormatState *format) {
    return recovered_format(format, destination, 32, "%.1f", static_cast<double>(settings->maximum_cps.current));
}
