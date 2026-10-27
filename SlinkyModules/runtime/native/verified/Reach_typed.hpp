#ifndef SLINKY_SHARE_AE9A28D04532673A8633
#define SLINKY_SHARE_AE9A28D04532673A8633
#include "Timer.hpp"
#include "module_ui_controls.hpp"
#include "module_format.hpp"

struct ReachSettings {
    NumberSetting distance;
    NumberSetting activation_ticks;
    BooleanSetting require_sprint;
};
struct ReachRuntimeState {
    volatile std::int32_t previous_attacker_time;
    volatile std::int32_t countdown;
};
struct ReachEvent {
    std::uintptr_t type;
    TimerGame *game;
    std::uint8_t enabled;
    std::uint8_t padding[7];
    double distance;
};
struct ReachDependencies {
    std::uint8_t (*sprinting)(GameAccessBridge *, std::uintptr_t player);
    std::int32_t (*last_attacker_time)(GameAccessBridge *, std::uintptr_t player);
};
static_assert(sizeof(ReachSettings) == 144);
static_assert(offsetof(ReachSettings, activation_ticks) == 56);
static_assert(offsetof(ReachSettings, require_sprint) == 112);
static_assert(sizeof(ReachRuntimeState) == 8);
static_assert(sizeof(ReachEvent) == 32);
static_assert(offsetof(ReachEvent, distance) == 24);
static_assert(sizeof(ReachDependencies) == 16);

extern "C" {
__declspec(dllexport) void recovered_bind_reach_access(ReachDependencies *);
__declspec(dllexport) void recovered_reach_initialize_settings(ReachSettings *);
__declspec(dllexport) void recovered_reach_typed_update(ReachEvent *, const ReachSettings *,
    ReachRuntimeState *, const ReachDependencies *);
__declspec(dllexport) std::uint64_t recovered_reach_typed_ui(std::uint64_t ui, std::uint64_t layout,
    ReachSettings *, UiDirtyState *, const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_reach_typed_settings(SettingsContext *, ReachSettings *,
    const ValueSettingsDependencies *, const SettingsDependencies *);
__declspec(dllexport) std::uint64_t recovered_reach_typed_label(char *, const ReachSettings *, FormatState *);
}

class ReachModule {
public:
    static constexpr const char *name = "Reach";
    static constexpr const char *description = "Increases your melee range.";
    static constexpr std::uint32_t event_type = 8;
    static constexpr std::int32_t event_priority = 0;
    ReachSettings settings{};
    ReachRuntimeState state{};
    ReachDependencies access{};
    // Restore the captured baseline; the original startup constructor is unresolved.
    ReachModule() {
        recovered_reach_initialize_settings(&settings);
        recovered_bind_reach_access(&access);
    }
    void update(ReachEvent &event) {
        recovered_reach_typed_update(&event, &settings, &state, &access);
    }
    std::uint64_t render(std::uint64_t ui, std::uint64_t layout, UiDirtyState &dirty,
                         const SettingsUiEndpoints &endpoints) {
        return recovered_reach_typed_ui(ui, layout, &settings, &dirty, &endpoints);
    }
    void configure(SettingsContext &context, const ValueSettingsDependencies &values,
                   const SettingsDependencies &booleans) {
        recovered_reach_typed_settings(&context, &settings, &values, &booleans);
    }
    std::uint64_t label(char *destination, FormatState &format) const {
        return recovered_reach_typed_label(destination, &settings, &format);
    }
};
#endif // SLINKY_SHARE_AE9A28D04532673A8633
