#include "access_events.hpp"

// lib_win RVA 0x3e590: event 14 callback.
extern "C" __declspec(dllexport) void recovered_no_hit_delay_3e590(
    void *event, AccessGlobals *globals, const AccessDependencies *deps) {
    if (static_cast<std::uint8_t *>(event)[0x10] != 1) return;
    auto *payload = reinterpret_cast<std::uint64_t *>(access_word(event, 8));
    const auto header = access_word(reinterpret_cast<const void *>(static_cast<std::uintptr_t>(payload[0])), 0);
    if (*reinterpret_cast<std::int32_t *>(static_cast<std::uintptr_t>(header)) == 0) return;
    const auto count = static_cast<std::int32_t>(access_call(deps, 0x22e90, payload[0], payload[3]));
    if (count <= 0) return;

    if (globals->state_3e590 == 1) {
        const auto token = access_call(deps, 0x22e10, payload[0], payload[3]);
        if (token != 0 && static_cast<std::int32_t>(access_call(deps, 0x24b50, payload[0], token)) != 0) {
            access_call(deps, 0x22eb0, payload[0], payload[3]);
            return;
        }
    } else {
        access_call(deps, 0x22eb0, payload[0], payload[3]);
        return;
    }
    if (static_cast<std::uint8_t>(access_call(deps, 0x23f90, payload[0], payload[5])) == 0)
        access_call(deps, 0x23bb0, payload[0], payload[5]);
}
