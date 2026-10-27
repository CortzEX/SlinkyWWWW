#include "module_ui_controls.hpp"
#include <cstring>

template <class Value>
static Value metadata(const std::uint8_t *bytes, std::size_t offset) {
    Value value;
    std::memcpy(&value, bytes + offset, sizeof(value));
    return value;
}
// 0xc210 stores the raw byte. Control wrappers pass one after a nonzero AL result.
extern "C" __declspec(dllexport) void recovered_mark_ui_dirty(UiDirtyState *state, std::uint8_t value) {
    state->modified = value;
}
// 0xcef0 forwards the label, record and current-byte address to widget 0x13d90.
extern "C" __declspec(dllexport) std::uint64_t recovered_checkbox_control(std::uint64_t layout,
    std::uint64_t ui, BooleanSetting *setting, UiDirtyState *dirty, const UiControlEndpoints *endpoints) {
    const auto result = endpoints->checkbox(ui, layout,
        metadata<std::uintptr_t>(setting->metadata, 16), setting, &setting->current);
    if (result & 0xff) recovered_mark_ui_dirty(dirty, 1);
    return result;
}
// 0xcf30 captures four float words and both text identities before widget 0x13f40.
extern "C" __declspec(dllexport) std::uint64_t recovered_number_control(std::uint64_t layout,
    std::uint64_t ui, NumberSetting *setting, UiDirtyState *dirty, const UiControlEndpoints *endpoints) {
    const auto result = endpoints->number(ui, layout,
        metadata<std::uintptr_t>(setting->metadata, 16), metadata<std::uintptr_t>(setting->metadata, 24),
        setting, setting->minimum, setting->maximum, metadata<float>(setting->metadata, 32),
        metadata<float>(setting->metadata, 36), &setting->current);
    if (result & 0xff) recovered_mark_ui_dirty(dirty, 1);
    return result;
}
