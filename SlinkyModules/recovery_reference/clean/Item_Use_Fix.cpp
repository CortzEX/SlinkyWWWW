#include "access_events.hpp"

// lib_win RVA 0x42b80: event 14 callback.
extern "C" __declspec(dllexport) void recovered_item_use_fix_42b80(
    void *event, AccessGlobals *globals, const AccessDependencies *deps) {
    if (static_cast<std::uint8_t *>(event)[0x10] != 0) return;
    auto *payload = reinterpret_cast<std::uint64_t *>(access_word(event, 8));
    const auto value = access_call(deps, 0x22df0, payload[0], payload[3]);
    globals->state_42b80 = static_cast<std::uint8_t>(
        static_cast<std::uint8_t>(access_call(deps, 0x27e90, payload[0], value)) != 0);
    if (globals->state_42b80) access_call(deps, 0x27eb0, payload[0], value);
}

// lib_win RVA 0x42be0: event 15 callback.
extern "C" __declspec(dllexport) void recovered_item_use_fix_42be0(
    void *event, AccessGlobals *globals, const AccessDependencies *deps) {
    if (globals->state_42b80 != 1 || static_cast<std::uint8_t *>(event)[0x10] != 0) return;
    auto *payload = reinterpret_cast<std::uint64_t *>(access_word(event, 8));
    const auto value = access_call(deps, 0x22df0, payload[0], payload[3]);
    access_call(deps, 0x27eb0, payload[0], value, globals->state_42b80);
}
