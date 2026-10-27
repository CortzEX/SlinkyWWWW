#ifndef SLINKY_SHARE_FFF1BC2AC76F381F2172
#define SLINKY_SHARE_FFF1BC2AC76F381F2172
#include "Sprint.hpp"
#include "module_float_ceiling.hpp"
#include "module_ui_controls.hpp"
#include "module_format.hpp"

struct FastMineEvent { std::uintptr_t type; SprintGame *game; };
struct FastMineSettings {
    NumberSetting break_delay;
    BooleanSetting decrement_block_hit_delay;
    NumberSetting speed;
};
struct FastMineState { std::int32_t last_current; float saved_progress; };
struct FastMineConstants { float progress_unit; std::uint32_t padding; double speed_unit; };
struct FastMineDependencies {
    std::uintptr_t (*controller)(GameAccessBridge *, std::uintptr_t);
    float (*progress)(GameAccessBridge *, std::uintptr_t);
    void (*set_progress)(GameAccessBridge *, std::uintptr_t, float);
    std::int32_t (*current)(GameAccessBridge *, std::uintptr_t);
    void (*set_current)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
};
static_assert(sizeof(FastMineEvent) == 16);
static_assert(sizeof(FastMineSettings) == 144);
static_assert(offsetof(FastMineSettings, decrement_block_hit_delay) == 56);
static_assert(offsetof(FastMineSettings, speed) == 88);
static_assert(sizeof(FastMineState) == 8);
static_assert(sizeof(FastMineConstants) == 16);
static_assert(sizeof(FastMineDependencies) == 40);

extern "C" {
__declspec(dllexport) void recovered_bind_fast_mine_access(FastMineDependencies *);
__declspec(dllexport) void recovered_fast_mine_update(FastMineEvent *, const FastMineSettings *,
    FastMineState *, const FastMineDependencies *);
__declspec(dllexport) void recovered_fast_mine_progress(FastMineEvent *, const FastMineSettings *,
    const FastMineState *, const FastMineConstants *, const FloatCeilingConstants *, const FastMineDependencies *);
__declspec(dllexport) std::uint64_t recovered_fast_mine_typed_ui(std::uint64_t ui, std::uint64_t layout,
    FastMineSettings *, UiDirtyState *, const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_fast_mine_typed_settings(SettingsContext *, FastMineSettings *,
    const SettingsDependencies *, const ValueSettingsDependencies *);
__declspec(dllexport) std::uint64_t recovered_fast_mine_label(char *, const FastMineSettings *, FormatState *);
}
#endif // SLINKY_SHARE_FFF1BC2AC76F381F2172
