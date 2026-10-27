#ifndef SLINKY_SHARE_EE7A20DC5FDD87278217
#define SLINKY_SHARE_EE7A20DC5FDD87278217
#include "module_game_access.hpp"
#include "module_surface.hpp"
#include "module_float_math.hpp"

struct CameraRotation { float yaw, pitch; };
struct CameraAngleState {
    CameraRotation rotation;
    std::uint8_t active;
    std::uint8_t updated;
    std::uint8_t padding[6];
};
struct FreeLookState {
    std::uintptr_t reserved;
    std::uint8_t enabled;
    std::uint8_t padding[7];
    CameraRotation saved_rotation;
    std::uint32_t saved_perspective;
    std::uint32_t reserved2;
};
struct FreeLookGame {
    GameAccessBridge *bridge;
    std::uintptr_t reserved[2];
    std::uintptr_t client;
    std::uintptr_t world;
    std::uintptr_t player;
};
struct FreeLookEvent {
    std::uintptr_t event_type;
    FreeLookGame *game;
    std::uintptr_t module;
    std::uint8_t enabled;
    std::uint8_t padding[7];
};
struct FreeLookRotationEvent {
    std::uintptr_t event_type;
    std::uint8_t override_rotation;
    std::uint8_t padding[3];
    CameraRotation rotation;
};
struct FreeLookDependencies {
    std::uint64_t (*player_angles)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*options)(GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*perspective)(GameAccessBridge *, std::uintptr_t);
    void (*set_perspective)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
};

static_assert(sizeof(CameraRotation) == 8);
static_assert(sizeof(CameraAngleState) == 16);
static_assert(offsetof(CameraAngleState, active) == 8);
static_assert(offsetof(CameraAngleState, updated) == 9);
static_assert(sizeof(FreeLookState) == 32);
static_assert(offsetof(FreeLookState, enabled) == 8);
static_assert(offsetof(FreeLookState, saved_rotation) == 16);
static_assert(offsetof(FreeLookState, saved_perspective) == 24);
static_assert(sizeof(FreeLookGame) == 48);
static_assert(offsetof(FreeLookGame, world) == 32);
static_assert(offsetof(FreeLookGame, player) == 40);
static_assert(sizeof(FreeLookEvent) == 32);
static_assert(offsetof(FreeLookEvent, module) == 16);
static_assert(offsetof(FreeLookEvent, enabled) == 24);
static_assert(offsetof(FreeLookRotationEvent, override_rotation) == 8);
static_assert(offsetof(FreeLookRotationEvent, rotation) == 12);
static_assert(sizeof(FreeLookDependencies) == 32);

extern "C" {
__declspec(dllexport) void recovered_bind_free_look_access(FreeLookDependencies *);
__declspec(dllexport) void recovered_free_look_lifecycle(FreeLookEvent *, std::uintptr_t module_identity,
    const ChoiceSetting *, FreeLookState *, CameraAngleState *, const AngleWrapConstants *, const FreeLookDependencies *);
__declspec(dllexport) void recovered_free_look_rotation(FreeLookRotationEvent *, const FreeLookState *);
__declspec(dllexport) void recovered_free_look_restore(CameraAngleState *, const AngleWrapConstants *, std::uint64_t packed_rotation);
__declspec(dllexport) void recovered_free_look_typed_ui(std::uint64_t ui, std::uint64_t layout, ChoiceSetting *, const SurfaceUiDependencies *);
__declspec(dllexport) void recovered_free_look_typed_settings(SettingsContext *, ChoiceSetting *, const ValueSettingsDependencies *);
}
#endif // SLINKY_SHARE_EE7A20DC5FDD87278217
