#ifndef SLINKY_SHARE_2D5674F72D633F3FA24F
#define SLINKY_SHARE_2D5674F72D633F3FA24F
#include "module_settings.hpp"

struct UiDirtyState { std::uint8_t modified; };
struct UiControlEndpoints {
    std::uint64_t (*checkbox)(std::uint64_t ui, std::uint64_t layout, std::uintptr_t label,
        BooleanSetting *, std::uint8_t *current);
    std::uint64_t (*number)(std::uint64_t ui, std::uint64_t layout, std::uintptr_t label,
        std::uintptr_t description, NumberSetting *, float minimum, float maximum,
        float parameter_a, float parameter_b, float *current);
};
struct SettingsUiEndpoints {
    void (*section)(std::uint64_t ui, std::uint64_t layout, const char *label);
    UiControlEndpoints controls;
};
static_assert(sizeof(UiControlEndpoints) == 16);
static_assert(sizeof(SettingsUiEndpoints) == 24);

extern "C" {
__declspec(dllexport) void recovered_mark_ui_dirty(UiDirtyState *, std::uint8_t value);
__declspec(dllexport) std::uint64_t recovered_checkbox_control(std::uint64_t layout, std::uint64_t ui,
    BooleanSetting *, UiDirtyState *, const UiControlEndpoints *);
__declspec(dllexport) std::uint64_t recovered_number_control(std::uint64_t layout, std::uint64_t ui,
    NumberSetting *, UiDirtyState *, const UiControlEndpoints *);
}
#endif // SLINKY_SHARE_2D5674F72D633F3FA24F
