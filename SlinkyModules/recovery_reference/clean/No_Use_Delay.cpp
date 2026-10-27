#include "access_events.hpp"

// lib_win RVA 0x3e8e0: event 18 callback.
extern "C" __declspec(dllexport) void recovered_no_use_delay_3e8e0(
    void *event, AccessGlobals *globals, const AccessDependencies *deps) {
    auto *payload = reinterpret_cast<std::uint64_t *>(access_word(event, 8));
    if (reinterpret_cast<std::uint8_t *>(payload)[0x40] == 0) {
        globals->countdown_3e8e0 = 0;
        return;
    }

    auto selected = access_call(deps, 0x22cf0, payload[0], payload[3]);
    selected = access_call(deps, 0x24f90, payload[0], selected);
    const auto active = static_cast<std::uint8_t>(access_call(deps, 0x25430, payload[0], selected));
    const auto item = access_call(deps, 0x23f40, payload[0], payload[5]);
    const auto item_id = static_cast<std::int32_t>(access_call(deps, 0x25a60, payload[0], item));
    if (item_id != globals->last_value_3e8e0) {
        globals->countdown_3e8e0 = 0;
        globals->last_value_3e8e0 = item_id;
        const auto object = payload[0];
        const auto arg = static_cast<std::uint32_t>(access_call(deps, 0x25490, object, selected));
        access_call(deps, 0x25460, object, selected, arg);
    }
    if (!active) return;

    const auto use_result = static_cast<std::int32_t>(access_call(deps, 0x23fc0, payload[0], payload[5]));
    if (globals->countdown_3e8e0 > 0) {
        --globals->countdown_3e8e0;
        if (globals->countdown_3e8e0 == 0 || (use_result == 0 && (globals->gate_3e8e0 & 1) != 0))
            access_call(deps, 0x25460, payload[0], selected);
        return;
    }
    globals->countdown_3e8e0 = use_result;
}
