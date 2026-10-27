#ifndef SLINKY_SHARE_E4EA706BF4697715CEF5
#define SLINKY_SHARE_E4EA706BF4697715CEF5
#include "Timer.hpp"
#include "module_ui_controls.hpp"

struct NoSlowSettings {
    NumberSetting bow;
    NumberSetting sword;
    NumberSetting consumables;
};
struct NoSlowEvent {
    std::uintptr_t type;
    TimerGame *game;
    float sideways, forward;
    std::uint8_t remaining[8];
};
struct NoSlowDependencies {
    std::uint8_t (*using_item)(GameAccessBridge *, std::uintptr_t player);
    std::uintptr_t (*held_item)(GameAccessBridge *, std::uintptr_t player);
    std::int32_t (*item_type)(GameAccessBridge *, std::uintptr_t item);
};
static_assert(sizeof(NoSlowSettings) == 168);
static_assert(offsetof(NoSlowSettings, sword) == 56);
static_assert(offsetof(NoSlowSettings, consumables) == 112);
static_assert(sizeof(NoSlowEvent) == 32);
static_assert(offsetof(NoSlowEvent, sideways) == 16);
static_assert(sizeof(NoSlowDependencies) == 24);

extern "C" {
__declspec(dllexport) void recovered_bind_no_slow_access(NoSlowDependencies *);
__declspec(dllexport) void recovered_no_slow_initialize_settings(NoSlowSettings *);
__declspec(dllexport) void recovered_no_slow_typed_update(NoSlowEvent *, const NoSlowSettings *,
    const double *slowdown_divisor, const NoSlowDependencies *);
__declspec(dllexport) std::uint64_t recovered_no_slow_typed_ui(std::uint64_t ui, std::uint64_t layout,
    NoSlowSettings *, UiDirtyState *, const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_no_slow_typed_settings(SettingsContext *, NoSlowSettings *,
    const ValueSettingsDependencies *);
}

class NoSlowModule {
public:
    static constexpr const char *name = "No Slow";
    static constexpr std::uint32_t event_type = 21;
    static constexpr std::int32_t event_priority = 200;
    NoSlowSettings settings{};
    // Captured baseline, not a recovered startup constructor.
    double slowdown_divisor = 0.2;
    NoSlowDependencies access{};
    NoSlowModule() {
        recovered_no_slow_initialize_settings(&settings);
        recovered_bind_no_slow_access(&access);
    }
    void update(NoSlowEvent &event) {
        recovered_no_slow_typed_update(&event, &settings, &slowdown_divisor, &access);
    }
    std::uint64_t render(std::uint64_t ui, std::uint64_t layout, UiDirtyState &dirty,
                         const SettingsUiEndpoints &endpoints) {
        return recovered_no_slow_typed_ui(ui, layout, &settings, &dirty, &endpoints);
    }
    void configure(SettingsContext &context, const ValueSettingsDependencies &endpoints) {
        recovered_no_slow_typed_settings(&context, &settings, &endpoints);
    }
};
#endif // SLINKY_SHARE_E4EA706BF4697715CEF5
