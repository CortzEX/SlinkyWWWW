#ifndef SLINKY_SHARE_24067D8DCA488C7C5604
#define SLINKY_SHARE_24067D8DCA488C7C5604
#include "module_game_access.hpp"
#include "module_surface.hpp"

struct TimerGame {
    GameAccessBridge *bridge;
    std::uintptr_t reserved[2];
    std::uintptr_t client;
    std::uintptr_t world;
    std::uintptr_t player;
    const std::uint8_t *input;
    std::uintptr_t reserved2;
    std::uint8_t ready;
    std::uint8_t padding[7];
};

struct TimerEvent {
    std::uintptr_t event_type;
    TimerGame *game;
    std::uintptr_t module;
    std::uint8_t enabled;
    std::uint8_t padding[7];
};

struct TimerSettings {
    NumberSetting speed;
    BooleanSetting require_mouse;
    BooleanSetting require_falling;
    BooleanSetting require_damage;
};

struct TimerVelocity { double x, y, z; };

struct TimerDependencies {
    std::uintptr_t (*timer)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*mouse)(TimerGame *);
    std::uint8_t (*on_ground)(GameAccessBridge *, std::uintptr_t);
    void (*velocity)(TimerVelocity *, GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*damage)(GameAccessBridge *, std::uintptr_t);
    void (*set_speed)(GameAccessBridge *, std::uintptr_t, float);
};

static_assert(sizeof(TimerGame) == 72);
static_assert(offsetof(TimerGame, input) == 48);
static_assert(offsetof(TimerGame, ready) == 64);
static_assert(sizeof(TimerEvent) == 32);
static_assert(offsetof(TimerEvent, module) == 16);
static_assert(offsetof(TimerEvent, enabled) == 24);
static_assert(sizeof(TimerSettings) == 152);
static_assert(offsetof(TimerSettings, speed) == 0);
static_assert(offsetof(TimerSettings, require_mouse) == 56);
static_assert(offsetof(TimerSettings, require_falling) == 88);
static_assert(offsetof(TimerSettings, require_damage) == 120);
static_assert(sizeof(TimerVelocity) == 24);
static_assert(sizeof(TimerDependencies) == 48);

extern "C" {
__declspec(dllexport) void recovered_timer_update(TimerEvent *, const TimerSettings *, const TimerDependencies *);
__declspec(dllexport) void recovered_timer_lifecycle(TimerEvent *, std::uintptr_t module_identity, const TimerDependencies *);
__declspec(dllexport) void recovered_bind_timer_access(TimerDependencies *);
__declspec(dllexport) void recovered_timer_typed_ui(std::uint64_t ui, std::uint64_t layout, TimerSettings *, const SurfaceUiDependencies *);
__declspec(dllexport) void recovered_timer_typed_settings(SettingsContext *, TimerSettings *, const SettingsDependencies *, const ValueSettingsDependencies *);
}
#endif // SLINKY_SHARE_24067D8DCA488C7C5604
