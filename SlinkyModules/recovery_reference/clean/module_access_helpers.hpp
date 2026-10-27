#pragma once

#include "access_events.hpp"
#include "module_game_access.hpp"

// 0x23bb0 forwards the caller's saved RBP as a fifth JNI argument.
struct AccessHelperContext {
    std::uintptr_t caller_frame_token;
};

extern "C" {
__declspec(dllexport) std::uint64_t recovered_access_helper(
    GameAccessBridge *, std::uint32_t helper_rva, std::uint64_t object,
    std::uint64_t value, std::uintptr_t caller_frame_token);
__declspec(dllexport) void recovered_bind_access_helpers(AccessDependencies *, AccessHelperContext *);
}
