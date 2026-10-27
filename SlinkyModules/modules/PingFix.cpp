// Ping Fix

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Ping_Fix.md

#include "../runtime/native/verified/module_surface.hpp"

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Ping_Fix/Ping_Fix.cpp
#include "../runtime/native/verified/event_callbacks.hpp"
#include <cstring>

// lib_win RVAs 0x3e6d0 and 0x3e700: inbound and outbound packet callbacks.
extern "C" __declspec(dllexport) void recovered_ping_fix_3e6d0(std::uint8_t *event,
                                                               const Dependencies *deps) {
    std::uintptr_t first, second;
    std::memcpy(&first, event + 8, sizeof(first));
    std::memcpy(&second, event + 0x10, sizeof(second));
    if (deps->dep_180026c80(first, second)) {
        constexpr std::uint32_t result = 3;
        std::memcpy(event + 0x24, &result, sizeof(result));
    }
}

extern "C" __declspec(dllexport) void recovered_ping_fix_3e700(std::uint8_t *event,
                                                               const Dependencies *deps) {
    std::uintptr_t first, second;
    std::memcpy(&first, event + 8, sizeof(first));
    std::memcpy(&second, event + 0x10, sizeof(second));
    if (deps->dep_180026cc0(first, second)) {
        constexpr std::uint32_t result = 3;
        std::memcpy(event + 0x24, &result, sizeof(result));
    }
}
// END SOURCE modules/Ping_Fix/Ping_Fix.cpp

// BEGIN SOURCE modules/Ping_Fix/Ping_Fix_typed.cpp
#ifndef SLINKY_SHARE_0CC34832DEE85C51AF32
#define SLINKY_SHARE_0CC34832DEE85C51AF32
// BEGIN SOURCE native/verified/Ping_Fix_typed.hpp
#include "../runtime/native/verified/module_game_access.hpp"

struct PingFixEvent {
    std::uintptr_t type;
    GameAccessBridge *bridge;
    std::uintptr_t packet;
    std::uint8_t opaque[12];
    std::uint32_t dispatch_mode;
};
struct PingFixDependencies {
    std::uintptr_t (*server_keep_alive)(GameAccessBridge *, std::uintptr_t packet);
    std::uintptr_t (*client_keep_alive)(GameAccessBridge *, std::uintptr_t packet);
};
static_assert(sizeof(PingFixEvent) == 40);
static_assert(offsetof(PingFixEvent, dispatch_mode) == 36);
static_assert(sizeof(PingFixDependencies) == 16);
extern "C" {
__declspec(dllexport) void recovered_bind_ping_fix_access(PingFixDependencies *);
__declspec(dllexport) void recovered_ping_fix_typed_inbound(PingFixEvent *,
                                                            const PingFixDependencies *);
__declspec(dllexport) void recovered_ping_fix_typed_outbound(PingFixEvent *,
                                                             const PingFixDependencies *);
}
class PingFixModule {
  public:
    static constexpr const char *name = "Ping Fix";
    static constexpr const char *description = "Shows your real ping while using lag mods.";
    static constexpr std::uint32_t inbound_event = 2, outbound_event = 3;
    static constexpr std::int32_t event_priority = -1000;
    PingFixDependencies access{};
    PingFixModule() {
        recovered_bind_ping_fix_access(&access);
    }
    void inbound(PingFixEvent &event) {
        recovered_ping_fix_typed_inbound(&event, &access);
    }
    void outbound(PingFixEvent &event) {
        recovered_ping_fix_typed_outbound(&event, &access);
    }
};
// END SOURCE native/verified/Ping_Fix_typed.hpp

#endif // SLINKY_SHARE_0CC34832DEE85C51AF32

extern "C" __declspec(dllexport) void recovered_bind_ping_fix_access(PingFixDependencies *access) {
    *access = {recovered_game_s00_keepalive_predicate, recovered_game_c00_keepalive_predicate};
}
// 0x3e6d0 retains the full returned packet handle, including its upper bytes.
extern "C" __declspec(dllexport) void
recovered_ping_fix_typed_inbound(PingFixEvent *event, const PingFixDependencies *access) {
    if (access->server_keep_alive(event->bridge, event->packet))
        event->dispatch_mode = 3;
}
// 0x3e700 applies the same policy to outgoing client keep-alive packets.
extern "C" __declspec(dllexport) void
recovered_ping_fix_typed_outbound(PingFixEvent *event, const PingFixDependencies *access) {
    if (access->client_keep_alive(event->bridge, event->packet))
        event->dispatch_mode = 3;
}
// END SOURCE modules/Ping_Fix/Ping_Fix_typed.cpp

#ifndef SLINKY_SHARE_80581872BA95D47AF1E7
#define SLINKY_SHARE_80581872BA95D47AF1E7
// BEGIN SOURCE modules/Ping_Fix/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Ping_Fix/Api.hpp

#endif // SLINKY_SHARE_80581872BA95D47AF1E7

// Convenient borrowed-state interface

namespace shareable {
using PingFix = ::PingFixModule;
}
