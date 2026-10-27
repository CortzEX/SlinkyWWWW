#pragma once

#include "Timer.hpp"
#include "module_random.hpp"

struct KeepSprintStatus {
    std::uint8_t reserved[24];
    std::uint8_t reducing;
};

struct KeepSprintGame {
    GameAccessBridge *bridge;
    std::uintptr_t reserved[4];
    std::uintptr_t player;
    std::uintptr_t reserved2;
    const KeepSprintStatus *status;
    std::uint8_t ready;
    std::uint8_t padding[7];
};

struct KeepSprintEvent {
    std::uintptr_t event_type;
    KeepSprintGame *game;
    std::uint8_t active;
    std::uint8_t padding[7];
};

struct KeepSprintSettings {
    NumberSetting chance;
    NumberSetting motion_multiplier;
    BooleanSetting require_on_ground;
    BooleanSetting allow_reduce;
};

struct KeepSprintState {
    TimerVelocity movement;
    std::uint8_t armed, pending;
    std::uint8_t padding[6];
};

struct KeepSprintDependencies {
    std::uint8_t (*sprinting)(GameAccessBridge *, std::uintptr_t);
    void (*velocity)(TimerVelocity *, GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*on_ground)(GameAccessBridge *, std::uintptr_t);
    std::int32_t (*counter)(GameAccessBridge *, std::uintptr_t);
    std::int32_t (*last_attacker_time)(GameAccessBridge *, std::uintptr_t);
    void (*set_velocity)(GameAccessBridge *, std::uintptr_t, const TimerVelocity *);
    void (*set_sprinting)(GameAccessBridge *, std::uintptr_t, std::uint8_t);
};

static_assert(sizeof(KeepSprintGame) == 72);
static_assert(offsetof(KeepSprintGame, player) == 40);
static_assert(offsetof(KeepSprintGame, status) == 56);
static_assert(offsetof(KeepSprintGame, ready) == 64);
static_assert(offsetof(KeepSprintStatus, reducing) == 24);
static_assert(sizeof(KeepSprintEvent) == 24);
static_assert(offsetof(KeepSprintEvent, active) == 16);
static_assert(sizeof(KeepSprintSettings) == 176);
static_assert(offsetof(KeepSprintSettings, motion_multiplier) == 56);
static_assert(offsetof(KeepSprintSettings, require_on_ground) == 112);
static_assert(offsetof(KeepSprintSettings, allow_reduce) == 144);
static_assert(sizeof(KeepSprintState) == 32);
static_assert(offsetof(KeepSprintState, armed) == 24);
static_assert(offsetof(KeepSprintState, pending) == 25);
static_assert(sizeof(KeepSprintDependencies) == 56);

extern "C" {
__declspec(dllexport) void recovered_keep_sprint_sample(KeepSprintEvent *, const KeepSprintSettings *, KeepSprintState *, RandomState *, const RandomConstants *, const KeepSprintDependencies *);
__declspec(dllexport) void recovered_keep_sprint_apply(KeepSprintEvent *, const KeepSprintSettings *, KeepSprintState *, const KeepSprintDependencies *);
__declspec(dllexport) void recovered_keep_sprint_finish(KeepSprintEvent *, KeepSprintState *, const KeepSprintDependencies *);
__declspec(dllexport) void recovered_bind_keep_sprint_access(KeepSprintDependencies *);
__declspec(dllexport) std::int32_t recovered_keep_sprint_counter(GameAccessBridge *, std::uintptr_t);
__declspec(dllexport) void recovered_keep_sprint_set_velocity(GameAccessBridge *, std::uintptr_t, const TimerVelocity *);
__declspec(dllexport) void recovered_keep_sprint_typed_ui(std::uint64_t ui, std::uint64_t layout, KeepSprintSettings *, const SurfaceUiDependencies *);
__declspec(dllexport) void recovered_keep_sprint_typed_settings(SettingsContext *, KeepSprintSettings *, const SettingsDependencies *, const ValueSettingsDependencies *);
}
