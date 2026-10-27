#include "access_events.hpp"

// lib_win RVA 0x35d50: event 17 callback.
extern "C" __declspec(dllexport) void recovered_no_jump_delay_35d50(
    void *event, const AccessDependencies *deps) {
    auto *payload = reinterpret_cast<std::uint64_t *>(access_word(event, 8));
    if (reinterpret_cast<std::uint8_t *>(payload)[0x40] == 1)
        access_call(deps, 0x23b80, payload[0], payload[5]);
}
