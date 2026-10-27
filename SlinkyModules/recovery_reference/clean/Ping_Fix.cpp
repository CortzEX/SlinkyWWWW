#include "event_callbacks.hpp"
#include <cstring>

// lib_win RVAs 0x3e6d0 and 0x3e700: inbound and outbound packet callbacks.
extern "C" __declspec(dllexport) void recovered_ping_fix_3e6d0(
    std::uint8_t *event, const Dependencies *deps) {
    std::uintptr_t first, second;
    std::memcpy(&first, event + 8, sizeof(first));
    std::memcpy(&second, event + 0x10, sizeof(second));
    if (deps->dep_180026c80(first, second)) {
        constexpr std::uint32_t result = 3;
        std::memcpy(event + 0x24, &result, sizeof(result));
    }
}

extern "C" __declspec(dllexport) void recovered_ping_fix_3e700(
    std::uint8_t *event, const Dependencies *deps) {
    std::uintptr_t first, second;
    std::memcpy(&first, event + 8, sizeof(first));
    std::memcpy(&second, event + 0x10, sizeof(second));
    if (deps->dep_180026cc0(first, second)) {
        constexpr std::uint32_t result = 3;
        std::memcpy(event + 0x24, &result, sizeof(result));
    }
}
