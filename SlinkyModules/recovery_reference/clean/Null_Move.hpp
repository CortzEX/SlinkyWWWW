#pragma once

#include "Sprint.hpp"

using NullMoveGame = SprintGame;
struct NullMoveEvent { std::uintptr_t event_type; NullMoveGame *game; };
struct NullMoveState { std::uint32_t saved_stamps[4]; };
struct NullMoveDependencies {
    std::uint8_t (*ready)(GameAccessBridge *, std::uintptr_t client);
    std::int32_t (*stamp)(GameAccessBridge *, std::uintptr_t player);
    std::uintptr_t (*options)(GameAccessBridge *, std::uintptr_t client);
    std::uintptr_t (*keys[4])(GameAccessBridge *, std::uintptr_t options);
    std::uint8_t (*pressed)(GameAccessBridge *, std::uintptr_t key);
    std::uint8_t (*physical)(GameAccessBridge *, std::uintptr_t key);
    void (*set_key)(GameAccessBridge *, std::uintptr_t key, std::uint8_t value);
};
static_assert(sizeof(NullMoveEvent) == 16);
static_assert(offsetof(NullMoveEvent, game) == 8);
static_assert(sizeof(NullMoveState) == 16);
static_assert(sizeof(NullMoveDependencies) == 80);

extern "C" {
__declspec(dllexport) void recovered_null_move_update(NullMoveEvent *, NullMoveState *, const NullMoveDependencies *);
__declspec(dllexport) void recovered_bind_null_move_access(NullMoveDependencies *);
__declspec(dllexport) std::uint8_t recovered_null_move_ready(GameAccessBridge *, std::uintptr_t client);
__declspec(dllexport) std::uintptr_t recovered_null_move_key(GameAccessBridge *, std::uintptr_t options, std::uint32_t index);
}
