#pragma once
#include "module_ui_controls.hpp"

using ChoiceUiEndpoint = std::uint64_t (*)(std::uint64_t ui, std::uint64_t layout,
    std::uintptr_t description, ChoiceSetting *, std::uint32_t count, const char *const *options,
    std::uint32_t *current, std::uint8_t flag);
struct ChoiceUiEndpoints { SettingsUiEndpoints standard; ChoiceUiEndpoint choice; };
static_assert(sizeof(ChoiceUiEndpoints) == 32);

extern "C" __declspec(dllexport) std::uint64_t recovered_choice_control(std::uint64_t layout,
    std::uint64_t ui, ChoiceSetting *, std::uint8_t flag, UiDirtyState *, ChoiceUiEndpoint);
