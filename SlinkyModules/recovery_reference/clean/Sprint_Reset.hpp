#pragma once
#include "module_choice_ui.hpp"
#include "module_format.hpp"
#include <cstddef>

struct SprintResetSettings {
    ChoiceSetting mode;
    std::uint8_t choice_flag, padding[7];
    NumberSetting delay;
    BooleanSetting randomize, wait_for_damage, require_weapon;
    NumberSetting duration;
};
static_assert(sizeof(SprintResetSettings) == 272);
static_assert(offsetof(SprintResetSettings, delay) == 64);
static_assert(offsetof(SprintResetSettings, randomize) == 120);
static_assert(offsetof(SprintResetSettings, wait_for_damage) == 152);
static_assert(offsetof(SprintResetSettings, require_weapon) == 184);
static_assert(offsetof(SprintResetSettings, duration) == 216);

extern "C" {
__declspec(dllexport) std::uint64_t recovered_sprint_reset_typed_ui(std::uint64_t ui, std::uint64_t layout,
    SprintResetSettings *, UiDirtyState *, const ChoiceUiEndpoints *);
__declspec(dllexport) void recovered_sprint_reset_typed_settings(SettingsContext *, SprintResetSettings *,
    const SettingsDependencies *, const ValueSettingsDependencies *);
__declspec(dllexport) std::uint64_t recovered_sprint_reset_label(char *destination, const ChoiceSetting *,
    const char *const *labels, FormatState *);
}
