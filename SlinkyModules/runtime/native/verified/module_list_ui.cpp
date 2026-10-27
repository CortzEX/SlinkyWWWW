#include "module_list_ui.hpp"
#include <cstring>

// 0xd0e0 reads metadata after the optional suggestion callback returns.
extern "C" __declspec(dllexport) std::uint64_t recovered_list_control(std::uint64_t layout,
    std::uint64_t ui, ListUiSetting *setting, UiDirtyState *dirty, const ListUiEndpoint *endpoint) {
    std::uintptr_t suggestions[2]{};
    if (setting->suggestions) setting->suggestions(&suggestions[0], &suggestions[1]);
    std::uintptr_t metadata[3];
    std::memcpy(metadata, setting->value.metadata, sizeof(metadata));
    const auto result = endpoint->render(ui, layout, metadata[0], metadata[1], metadata[2],
        setting->value.kind, &setting->value.state, suggestions[0], suggestions[1]);
    if (result & 0xff) {
        setting->modified = 1;
        recovered_mark_ui_dirty(dirty, 1);
    }
    return result;
}
