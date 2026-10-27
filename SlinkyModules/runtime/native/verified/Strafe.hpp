#ifndef SLINKY_SHARE_DF29A02B09A7E30B1271
#define SLINKY_SHARE_DF29A02B09A7E30B1271
#include "Timer.hpp"
#include "Keep_Sprint.hpp"
#include "Weapons.hpp"
#include "module_ui_controls.hpp"

struct StrafeEvent {
    std::uintptr_t type;
    TimerGame *game;
    float sideways, forward, reserved;
    std::uint8_t jump, padding[3];
};
struct StrafeSettings {
    NumberSetting max_hurt_time, air, jump, ground;
    BooleanSetting require_weapon;
};
struct StrafeConstants {
    double boost, negative_side, positive_side, zero_factor, half_turn;
    double backward_factor, forward_factor, angle_scale;
    std::uint32_t sign_mask, padding;
};
struct StrafeWeaponBinding {
    WeaponCache *cache;
    const WeaponSettings *settings;
    const ItemPolicyTable *policy;
    const WeaponDependencies *access;
};
struct StrafeDependencies {
    std::uint8_t (*sprinting)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*weapon)(GameAccessBridge *, std::uintptr_t, const StrafeWeaponBinding *);
    std::uint32_t (*damage)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*on_ground)(GameAccessBridge *, std::uintptr_t);
    void (*velocity)(TimerVelocity *, GameAccessBridge *, std::uintptr_t);
    std::uint64_t (*rotation)(GameAccessBridge *, std::uintptr_t);
    void (*set_velocity)(GameAccessBridge *, std::uintptr_t, const TimerVelocity *);
    double (*speed)(double, double);
    float (*sine)(float);
    float (*cosine)(float);
    const StrafeWeaponBinding *weapon_state;
};
static_assert(sizeof(StrafeEvent) == 32);
static_assert(offsetof(StrafeEvent, jump) == 28);
static_assert(sizeof(StrafeSettings) == 256);
static_assert(offsetof(StrafeSettings, require_weapon) == 224);
static_assert(sizeof(StrafeConstants) == 72);
static_assert(offsetof(StrafeConstants, sign_mask) == 64);
static_assert(sizeof(StrafeDependencies) == 88);

extern "C" {
__declspec(dllexport) void recovered_bind_strafe_access(StrafeDependencies *);
__declspec(dllexport) void recovered_strafe_typed_sample(StrafeEvent *, std::uint8_t *sampled, const StrafeDependencies *);
__declspec(dllexport) void recovered_strafe_typed_motion(StrafeEvent *, const StrafeSettings *, const std::uint8_t *sampled,
    const StrafeConstants *, const StrafeDependencies *);
__declspec(dllexport) double recovered_strafe_interpolate(double current, double target, double amount);
__declspec(dllexport) std::uint64_t recovered_strafe_typed_ui(std::uint64_t ui, std::uint64_t layout,
    StrafeSettings *, UiDirtyState *, const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_strafe_typed_settings(SettingsContext *, StrafeSettings *,
    const SettingsDependencies *, const ValueSettingsDependencies *);
}
#endif // SLINKY_SHARE_DF29A02B09A7E30B1271
