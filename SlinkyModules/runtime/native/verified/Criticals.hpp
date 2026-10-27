#ifndef SLINKY_SHARE_DC03B211020E2A1221B7
#define SLINKY_SHARE_DC03B211020E2A1221B7
#include "Timer.hpp"
#include "Weapons.hpp"
#include "module_random.hpp"
#include "module_choice_ui.hpp"
#include "module_format.hpp"

struct CriticalsSettings {
    NumberSetting max_delay, chance;
    BooleanSetting require_mouse, require_weapon;
    std::uint8_t reserved[16];
    ChoiceSetting mode;
    std::uint8_t choice_flag, reserved2[7];
    NumberSetting timer_speed, boost;
};
struct CriticalsState {
    std::uint8_t eligible, reserved;
    std::uint16_t limit;
    std::uint8_t active, padding[3];
    std::uint32_t chance_counter;
    std::uint8_t cached_chance, restore_timer, padding2[2];
    double accumulated;
    std::uint32_t packet_count, reserved2;
    double previous_y;
    std::uint32_t last_packet_id;
    std::uint8_t falling, padding3[3];
};
struct CriticalsConstants {
    double threshold;
    float normal_speed;
    std::uint32_t padding;
    double time_scale;
    float disable_speed;
    std::uint32_t padding2;
};
struct CriticalsTimerEvent {
    std::uintptr_t type;
    TimerGame *game;
    std::uintptr_t reserved;
    double elapsed;
};
struct CriticalsPacketEvent {
    std::uintptr_t type;
    GameAccessBridge *bridge;
    std::uintptr_t object;
    std::uint64_t timestamp;
    std::uint32_t id, action;
};
struct CriticalsDependencies {
    TimerDependencies timer;
    const WeaponDependencies *weapon_access;
    WeaponCache *weapon_cache;
    const WeaponSettings *weapon_settings;
    const ItemPolicyTable *weapon_policy;
    RandomState *random_state;
    const RandomConstants *random_constants;
};
static_assert(sizeof(CriticalsSettings) == 368);
static_assert(offsetof(CriticalsSettings, mode) == 192);
static_assert(offsetof(CriticalsSettings, timer_speed) == 256);
static_assert(sizeof(CriticalsState) == 48);
static_assert(offsetof(CriticalsState, chance_counter) == 8);
static_assert(offsetof(CriticalsState, accumulated) == 16);
static_assert(offsetof(CriticalsState, previous_y) == 32);
static_assert(offsetof(CriticalsState, falling) == 44);
static_assert(sizeof(CriticalsConstants) == 32);
static_assert(sizeof(CriticalsTimerEvent) == 32);
static_assert(sizeof(CriticalsPacketEvent) == 40);
static_assert(sizeof(CriticalsDependencies) == 96);

extern "C" {
__declspec(dllexport) void recovered_bind_criticals_access(CriticalsDependencies *);
__declspec(dllexport) void recovered_criticals_typed_update(TimerEvent *, const CriticalsSettings *,
    volatile CriticalsState *, const CriticalsDependencies *);
__declspec(dllexport) void recovered_criticals_typed_timer(CriticalsTimerEvent *, const CriticalsSettings *,
    volatile CriticalsState *, const CriticalsConstants *, const CriticalsDependencies *);
__declspec(dllexport) void recovered_criticals_typed_packet(CriticalsPacketEvent *, volatile CriticalsState *);
__declspec(dllexport) void recovered_criticals_typed_disable(TimerEvent *, std::uintptr_t module_identity,
    volatile CriticalsState *, const CriticalsConstants *, const CriticalsDependencies *);
__declspec(dllexport) std::uint64_t recovered_criticals_typed_ui(std::uint64_t ui, std::uint64_t layout,
    CriticalsSettings *, UiDirtyState *, const ChoiceUiEndpoints *);
__declspec(dllexport) void recovered_criticals_typed_settings(SettingsContext *, CriticalsSettings *,
    const SettingsDependencies *, const ValueSettingsDependencies *);
__declspec(dllexport) std::uint64_t recovered_criticals_label(char *, const ChoiceSetting *,
    const char *const *labels, FormatState *);
}
#endif // SLINKY_SHARE_DC03B211020E2A1221B7
