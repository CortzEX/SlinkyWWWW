#pragma once
#include "module_list_settings.hpp"
#include "module_ui_controls.hpp"

struct ListUiSetting {
    ListSetting value;
    void (*suggestions)(std::uintptr_t *first, std::uintptr_t *second);
    std::uint8_t modified, padding[7];
};
struct ListUiEndpoint {
    std::uint64_t (*render)(std::uint64_t ui, std::uint64_t layout,
        std::uintptr_t first_metadata, std::uintptr_t second_metadata, std::uintptr_t third_metadata,
        std::uint32_t kind, void *payload, std::uintptr_t first_suggestion, std::uintptr_t second_suggestion);
};
static_assert(offsetof(ListUiSetting, suggestions) == 0x58);
static_assert(offsetof(ListUiSetting, modified) == 0x60);
static_assert(sizeof(ListUiSetting) == 0x68);

extern "C" __declspec(dllexport) std::uint64_t recovered_list_control(
    std::uint64_t layout, std::uint64_t ui, ListUiSetting *, UiDirtyState *, const ListUiEndpoint *);
