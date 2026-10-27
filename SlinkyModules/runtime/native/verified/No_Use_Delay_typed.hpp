#ifndef SLINKY_SHARE_C59304725AA6C0FB8E1B
#define SLINKY_SHARE_C59304725AA6C0FB8E1B
#include "Timer.hpp"
#include "module_ui_controls.hpp"

struct NoUseDelaySettings { BooleanSetting allow_desync; };
struct NoUseDelayState {
    volatile std::int32_t countdown;
    volatile std::int32_t last_slot;
};
struct NoUseDelayEvent { std::uintptr_t type; TimerGame *game; };
struct NoUseDelayDependencies {
    std::uintptr_t (*options)(GameAccessBridge *, std::uintptr_t client);
    std::uintptr_t (*use_key)(GameAccessBridge *, std::uintptr_t options);
    std::uint8_t (*use_pressed)(GameAccessBridge *, std::uintptr_t key);
    std::uintptr_t (*inventory)(GameAccessBridge *, std::uintptr_t player);
    std::int32_t (*selected_slot)(GameAccessBridge *, std::uintptr_t inventory);
    std::uint32_t (*physical_key)(GameAccessBridge *, std::uintptr_t key);
    void (*set_key)(GameAccessBridge *, std::uintptr_t key, std::uint32_t value);
    std::int32_t (*item_use_count)(GameAccessBridge *, std::uintptr_t player);
};
static_assert(sizeof(NoUseDelaySettings) == 32);
static_assert(sizeof(NoUseDelayState) == 8);
static_assert(offsetof(NoUseDelayState, last_slot) == 4);
static_assert(sizeof(NoUseDelayEvent) == 16);
static_assert(sizeof(NoUseDelayDependencies) == 64);

extern "C" {
__declspec(dllexport) void recovered_bind_no_use_delay_access(NoUseDelayDependencies *);
__declspec(dllexport) void recovered_no_use_delay_initialize_settings(NoUseDelaySettings *);
__declspec(dllexport) void recovered_no_use_delay_typed_update(NoUseDelayEvent *, const NoUseDelaySettings *,
    NoUseDelayState *, const NoUseDelayDependencies *);
__declspec(dllexport) std::uint64_t recovered_no_use_delay_typed_ui(std::uint64_t ui, std::uint64_t layout,
    NoUseDelaySettings *, UiDirtyState *, const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_no_use_delay_typed_settings(SettingsContext *, NoUseDelaySettings *,
    const SettingsDependencies *);
}

class NoUseDelayModule {
public:
    static constexpr const char *name = "No Use Delay";
    static constexpr const char *description = "Removes vanilla delay when consuming items.";
    static constexpr std::uint32_t event_type = 18;
    static constexpr std::int32_t event_priority = 0;
    NoUseDelaySettings settings{};
    NoUseDelayState state{};
    NoUseDelayDependencies access{};
    // Captured settings/state baseline; original startup construction remains unresolved.
    NoUseDelayModule() {
        recovered_no_use_delay_initialize_settings(&settings);
        recovered_bind_no_use_delay_access(&access);
    }
    void update(NoUseDelayEvent &event) {
        recovered_no_use_delay_typed_update(&event, &settings, &state, &access);
    }
    std::uint64_t render(std::uint64_t ui, std::uint64_t layout, UiDirtyState &dirty,
                         const SettingsUiEndpoints &endpoints) {
        return recovered_no_use_delay_typed_ui(ui, layout, &settings, &dirty, &endpoints);
    }
    void configure(SettingsContext &context, const SettingsDependencies &endpoints) {
        recovered_no_use_delay_typed_settings(&context, &settings, &endpoints);
    }
};
#endif // SLINKY_SHARE_C59304725AA6C0FB8E1B
