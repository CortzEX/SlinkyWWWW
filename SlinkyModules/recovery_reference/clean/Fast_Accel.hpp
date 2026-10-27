#pragma once
#include "Keep_Sprint.hpp"
#include "Weapons.hpp"
#include "module_float_distance.hpp"
#include "module_ui_controls.hpp"

struct FastAccelEvent {
    std::uintptr_t event_type;
    TimerGame *game;
    float sideways, forward, factor;
    std::uint8_t jump, padding[3];
};
struct FastAccelSettings {
    NumberSetting acceleration;
    BooleanSetting require_weapon, require_not_damaged;
};
struct FastAccelConstants {
    float minimum;
    std::uint32_t padding;
    double decay, jump_increment;
};
struct FastAccelDependencies {
    std::uint32_t (*damage)(GameAccessBridge *, std::uintptr_t);
    void (*velocity)(TimerVelocity *, GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*on_ground)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*sprinting)(GameAccessBridge *, std::uintptr_t);
    void (*set_velocity)(GameAccessBridge *, std::uintptr_t, const TimerVelocity *);
    WeaponCache *weapon_cache;
    const WeaponSettings *weapon_settings;
    const ItemPolicyTable *weapon_policy;
    const WeaponDependencies *weapon_access;
    const FloatDistanceConstants *distance_constants;
    const std::uint8_t *encoded_numeric_target;
};
static_assert(sizeof(FastAccelEvent) == 32);
static_assert(offsetof(FastAccelEvent, sideways) == 16);
static_assert(offsetof(FastAccelEvent, jump) == 28);
static_assert(sizeof(FastAccelSettings) == 120);
static_assert(offsetof(FastAccelSettings, require_weapon) == 56);
static_assert(sizeof(FastAccelConstants) == 24);
static_assert(sizeof(FastAccelDependencies) == 88);

extern "C" {
// Binds five existing motion helpers, retaining the six caller-supplied data pointers.
__declspec(dllexport) void recovered_bind_fast_accel_access(FastAccelDependencies *);
__declspec(dllexport) void recovered_fast_accel_update(FastAccelEvent *, const FastAccelSettings *,
    const FastAccelConstants *, const FastAccelDependencies *);
__declspec(dllexport) std::uint64_t recovered_fast_accel_typed_ui(std::uint64_t ui, std::uint64_t layout,
    FastAccelSettings *, UiDirtyState *, const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_fast_accel_typed_settings(SettingsContext *, FastAccelSettings *,
    const SettingsDependencies *, const ValueSettingsDependencies *);
}
