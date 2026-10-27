#include "access_events.hpp"

// lib_win RVA 0x44940: event 18 callback.
extern "C" __declspec(dllexport) void recovered_anti_debuff_44940(
    void *event, AccessGlobals *globals, const AccessDependencies *deps) {
    auto *payload = reinterpret_cast<std::uint64_t *>(access_word(event, 8));
    if (globals->enabled_44940 == 1) {
        const auto value = access_call(deps, 0x27960, payload[0], 0xf);
        const auto found = access_call(deps, 0x23c10, payload[0], payload[5], value);
        if (found != 0) access_call(deps, 0x279c0, payload[0], found);
    }
    if (globals->enabled_44940_second == 1) {
        deps->invoke_23e60(payload[0], payload[5], 0.0f);
        deps->invoke_23e90(payload[0], payload[5], 0.0f);
    }
}
