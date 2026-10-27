#ifndef SLINKY_SHARE_C31B512FB5954E922485
#define SLINKY_SHARE_C31B512FB5954E922485
#include "module_game_access.hpp"
#include "module_surface.hpp"
#include <cstddef>
#include <cstdint>

struct SprintGame {
    GameAccessBridge *bridge;
    std::uintptr_t reserved[2];
    std::uintptr_t client;
    std::uintptr_t reserved2;
    std::uintptr_t player;
};

struct SprintEvent {
    std::uintptr_t event_type;
    SprintGame *game;
    float sideways;
    float forward;
    float scale;
};

struct SprintSettings {
    BooleanSetting while_in_gui;
    BooleanSetting while_using_item;
    BooleanSetting while_backwards;
    BooleanSetting while_sideways;
};

struct SprintDependencies {
    std::uintptr_t (*screen)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*options)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*sprint_key)(GameAccessBridge *, std::uintptr_t);
    void (*set_key)(GameAccessBridge *, std::uintptr_t, std::uint8_t);
    std::uint8_t (*ready)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*using_item)(GameAccessBridge *, std::uintptr_t);
    void (*set_sprinting)(GameAccessBridge *, std::uintptr_t, std::uint8_t);
};

static_assert(sizeof(SprintGame) == 48);
static_assert(offsetof(SprintGame, player) == 40);
static_assert(sizeof(SprintEvent) == 32);
static_assert(offsetof(SprintEvent, forward) == 20);
static_assert(offsetof(SprintEvent, scale) == 24);
static_assert(sizeof(SprintSettings) == 128);
static_assert(offsetof(SprintSettings, while_using_item) == 32);
static_assert(offsetof(SprintSettings, while_backwards) == 64);
static_assert(offsetof(SprintSettings, while_sideways) == 96);
static_assert(sizeof(SprintDependencies) == 56);

extern "C" {
__declspec(dllexport) void recovered_sprint_update(SprintEvent *, const SprintSettings *, std::uint8_t *last_state, const SprintDependencies *);
__declspec(dllexport) void recovered_sprint_movement(SprintEvent *, const SprintSettings *, const SprintDependencies *);
__declspec(dllexport) std::uintptr_t recovered_sprint_screen(GameAccessBridge *, std::uintptr_t client);
__declspec(dllexport) std::uintptr_t recovered_sprint_key(GameAccessBridge *, std::uintptr_t options);
__declspec(dllexport) void recovered_sprint_set_player(GameAccessBridge *, std::uintptr_t player, std::uint8_t value);
__declspec(dllexport) void recovered_bind_sprint_access(SprintDependencies *);
__declspec(dllexport) void recovered_sprint_typed_ui(std::uint64_t ui, std::uint64_t layout, SprintSettings *, const SurfaceUiDependencies *);
__declspec(dllexport) void recovered_sprint_typed_settings(SettingsContext *, SprintSettings *, const SettingsDependencies *);
}
#endif // SLINKY_SHARE_C31B512FB5954E922485
