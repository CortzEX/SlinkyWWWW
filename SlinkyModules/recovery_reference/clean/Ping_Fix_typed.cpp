#include "Ping_Fix_typed.hpp"

extern "C" __declspec(dllexport) void recovered_bind_ping_fix_access(PingFixDependencies *access) {
    *access={recovered_game_s00_keepalive_predicate,recovered_game_c00_keepalive_predicate};
}
// 0x3e6d0 retains the full returned packet handle, including its upper bytes.
extern "C" __declspec(dllexport) void recovered_ping_fix_typed_inbound(PingFixEvent *event,
    const PingFixDependencies *access) {
    if (access->server_keep_alive(event->bridge,event->packet)) event->dispatch_mode=3;
}
// 0x3e700 applies the same policy to outgoing client keep-alive packets.
extern "C" __declspec(dllexport) void recovered_ping_fix_typed_outbound(PingFixEvent *event,
    const PingFixDependencies *access) {
    if (access->client_keep_alive(event->bridge,event->packet)) event->dispatch_mode=3;
}
