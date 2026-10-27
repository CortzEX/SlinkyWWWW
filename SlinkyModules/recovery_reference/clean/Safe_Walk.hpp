#pragma once
#include "No_Hurt_Cam.hpp"
#include "Keep_Sprint.hpp"
#include "module_ui_controls.hpp"

struct SafeWalkEvent { std::uintptr_t type; TimerGame *game; };
struct SafeWalkSettings {
    NumberSetting speed;
    BooleanSetting require_pitch;
    BooleanSetting require_not_forward;
    BooleanSetting require_block_item;
};
struct SafeWalkConstants { float minimum_pitch, unscaled_speed; };
struct SafeWalkState { std::uint8_t allowed; };
struct SafeWalkDependencies {
    std::uint64_t (*player_angles)(GameAccessBridge *, std::uintptr_t);
    float (*forward_input)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*held_item)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*block_item)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*on_ground)(GameAccessBridge *, std::uintptr_t);
    void (*velocity)(TimerVelocity *, GameAccessBridge *, std::uintptr_t);
    void (*set_velocity)(GameAccessBridge *, std::uintptr_t, const TimerVelocity *);
    std::uintptr_t (*client)(GameAccessBridge *);
    std::uintptr_t (*entity)(GameAccessBridge *, std::uintptr_t);
    std::uint64_t (*same_object)(std::uintptr_t *, std::uintptr_t, std::uintptr_t);
    std::uint64_t (*fallback)(GameAccessBridge *, std::uintptr_t);
};
static_assert(sizeof(SafeWalkEvent) == 16);
static_assert(sizeof(SafeWalkSettings) == 152);
static_assert(offsetof(SafeWalkSettings, require_pitch) == 56);
static_assert(offsetof(SafeWalkSettings, require_not_forward) == 88);
static_assert(offsetof(SafeWalkSettings, require_block_item) == 120);
static_assert(sizeof(SafeWalkConstants) == 8);
static_assert(sizeof(SafeWalkDependencies) == 88);

extern "C" {
__declspec(dllexport) void recovered_bind_safe_walk_access(SafeWalkDependencies *);
__declspec(dllexport) void recovered_safe_walk_update(SafeWalkEvent *, const SafeWalkSettings *,
    SafeWalkState *, const SafeWalkConstants *, const SafeWalkDependencies *);
__declspec(dllexport) std::uint8_t recovered_safe_walk_state(const SafeWalkState *);
__declspec(dllexport) std::uint64_t recovered_safe_walk_query_typed(const std::uint8_t *const *metadata,
    std::uintptr_t *environment, std::uintptr_t target, const NoHurtCamDescriptor *const *descriptor,
    const SafeWalkState *, const SafeWalkDependencies *);
__declspec(dllexport) std::uint64_t recovered_safe_walk_typed_ui(std::uint64_t ui, std::uint64_t layout,
    SafeWalkSettings *, UiDirtyState *, const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_safe_walk_typed_settings(SettingsContext *, SafeWalkSettings *,
    const SettingsDependencies *, const ValueSettingsDependencies *);
}
