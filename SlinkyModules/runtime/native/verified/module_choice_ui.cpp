#include "module_choice_ui.hpp"
#include <cstring>

// 0xd040 snapshots the +0x18 text, DWORD count, option table and flag before rendering.
extern "C" __declspec(dllexport) std::uint64_t recovered_choice_control(std::uint64_t layout,
    std::uint64_t ui, ChoiceSetting *setting, std::uint8_t flag, UiDirtyState *dirty, ChoiceUiEndpoint endpoint) {
    std::uintptr_t description;
    std::memcpy(&description, setting->metadata + 24, sizeof(description));
    const auto result = endpoint(ui, layout, description, setting, setting->count,
        setting->options, &setting->current, flag);
    if (result & 0xff) recovered_mark_ui_dirty(dirty, 1);
    return result;
}
