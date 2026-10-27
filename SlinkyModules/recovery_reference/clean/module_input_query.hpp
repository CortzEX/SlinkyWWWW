#pragma once
#include "module_game_access.hpp"

struct InputRequest {
    std::uint32_t type, key, reserved;
    std::uint8_t requested, toggle, padding[2];
};
struct InputModuleGate {
    std::uint8_t prefix[20], enabled, padding[3];
};
struct InputQueryState {
    std::uint8_t *bits;
    std::uintptr_t *environment_owner;
    const std::uint8_t *metadata;
    const InputModuleGate *ghost, *friends;
    std::uintptr_t primary_keys, secondary_keys, action_context;
};
struct InputQueryDependencies {
    std::uint32_t (*dispatch)(InputRequest *, std::uint8_t unchanged, std::uintptr_t context);
    std::uintptr_t (*current)(GameAccessBridge *);
    std::uint8_t (*ready)(GameAccessBridge *, std::uintptr_t);
    void (*friend_action)(GameAccessBridge *, std::uintptr_t context);
    std::uintptr_t (*keys)(std::uintptr_t list, std::uint32_t key, std::uint8_t requested);
};
static_assert(sizeof(InputRequest) == 16);
static_assert(offsetof(InputRequest, requested) == 12);
static_assert(offsetof(InputModuleGate, enabled) == 20);
static_assert(sizeof(InputQueryState) == 64);
static_assert(sizeof(InputQueryDependencies) == 40);

extern "C" __declspec(dllexport) std::uint32_t recovered_input_query(
    InputRequest *, InputQueryState *, const InputQueryDependencies *);
