#ifndef SLINKY_SHARE_23FB334FC7B9138FC0D3
#define SLINKY_SHARE_23FB334FC7B9138FC0D3
#include "Timer.hpp"
#include "module_ui_controls.hpp"

struct AntiDebuffSettings {
    BooleanSetting blindness;
    BooleanSetting nausea;
};
struct AntiDebuffEvent {
    std::uintptr_t type;
    TimerGame *game;
};
struct AntiDebuffDependencies {
    std::uintptr_t (*effect_by_id)(GameAccessBridge *, std::uint32_t id);
    std::uintptr_t (*player_effect)(GameAccessBridge *, std::uintptr_t player, std::uintptr_t effect);
    void (*set_effect_value)(GameAccessBridge *, std::uintptr_t effect, std::uint32_t value);
    void (*set_nausea_strength)(GameAccessBridge *, std::uintptr_t player, float value);
    void (*set_previous_nausea_strength)(GameAccessBridge *, std::uintptr_t player, float value);
};
static_assert(sizeof(AntiDebuffSettings) == 64);
static_assert(offsetof(AntiDebuffSettings, nausea) == 32);
static_assert(sizeof(AntiDebuffEvent) == 16);
static_assert(sizeof(AntiDebuffDependencies) == 40);
extern "C" {
__declspec(dllexport) void recovered_bind_anti_debuff_access(AntiDebuffDependencies *);
__declspec(dllexport) void recovered_anti_debuff_initialize_settings(AntiDebuffSettings *);
__declspec(dllexport) void recovered_anti_debuff_typed_update(AntiDebuffEvent *, const AntiDebuffSettings *,
    const AntiDebuffDependencies *);
__declspec(dllexport) std::uint64_t recovered_anti_debuff_typed_ui(std::uint64_t ui, std::uint64_t layout,
    AntiDebuffSettings *, UiDirtyState *, const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_anti_debuff_typed_settings(SettingsContext *, AntiDebuffSettings *,
    const SettingsDependencies *);
}
class AntiDebuffModule {
public:
    static constexpr const char *name = "Anti Debuff";
    static constexpr const char *description = "Removes negative visual effects.";
    static constexpr std::uint32_t event_type = 18;
    static constexpr std::int32_t event_priority = 0;
    AntiDebuffSettings settings{};
    AntiDebuffDependencies access{};
    // Captured baseline, not a recovered original startup constructor.
    AntiDebuffModule() {
        recovered_anti_debuff_initialize_settings(&settings);
        recovered_bind_anti_debuff_access(&access);
    }
    void update(AntiDebuffEvent &event) {
        recovered_anti_debuff_typed_update(&event, &settings, &access);
    }
    std::uint64_t render(std::uint64_t ui, std::uint64_t layout, UiDirtyState &dirty,
                         const SettingsUiEndpoints &endpoints) {
        return recovered_anti_debuff_typed_ui(ui, layout, &settings, &dirty, &endpoints);
    }
    void configure(SettingsContext &context, const SettingsDependencies &endpoints) {
        recovered_anti_debuff_typed_settings(&context, &settings, &endpoints);
    }
};
#endif // SLINKY_SHARE_23FB334FC7B9138FC0D3
