#ifndef SLINKY_SHARE_0CC34832DEE85C51AF32
#define SLINKY_SHARE_0CC34832DEE85C51AF32
#include "module_game_access.hpp"

struct PingFixEvent {
    std::uintptr_t type;
    GameAccessBridge *bridge;
    std::uintptr_t packet;
    std::uint8_t opaque[12];
    std::uint32_t dispatch_mode;
};
struct PingFixDependencies {
    std::uintptr_t (*server_keep_alive)(GameAccessBridge *,std::uintptr_t packet);
    std::uintptr_t (*client_keep_alive)(GameAccessBridge *,std::uintptr_t packet);
};
static_assert(sizeof(PingFixEvent)==40);
static_assert(offsetof(PingFixEvent,dispatch_mode)==36);
static_assert(sizeof(PingFixDependencies)==16);
extern "C" {
__declspec(dllexport) void recovered_bind_ping_fix_access(PingFixDependencies *);
__declspec(dllexport) void recovered_ping_fix_typed_inbound(PingFixEvent *,const PingFixDependencies *);
__declspec(dllexport) void recovered_ping_fix_typed_outbound(PingFixEvent *,const PingFixDependencies *);
}
class PingFixModule {
public:
    static constexpr const char *name="Ping Fix";
    static constexpr const char *description="Shows your real ping while using lag mods.";
    static constexpr std::uint32_t inbound_event=2, outbound_event=3;
    static constexpr std::int32_t event_priority=-1000;
    PingFixDependencies access{};
    PingFixModule() { recovered_bind_ping_fix_access(&access); }
    void inbound(PingFixEvent &event) { recovered_ping_fix_typed_inbound(&event,&access); }
    void outbound(PingFixEvent &event) { recovered_ping_fix_typed_outbound(&event,&access); }
};
#endif // SLINKY_SHARE_0CC34832DEE85C51AF32
