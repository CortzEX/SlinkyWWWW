#include "event_callbacks.hpp"
#include <cstring>

// lib_win RVA 0x42a20: event 21 callback. Game access remains an injected dependency.
extern "C" __declspec(dllexport) void recovered_no_slow(
    std::uint8_t *event, const float multipliers[3], double divisor, const Dependencies *deps) {
    std::uintptr_t frame;
    std::memcpy(&frame, event + 8, sizeof(frame));
    auto *fields = reinterpret_cast<const std::uint8_t *>(frame);

    std::uintptr_t game, target;
    std::memcpy(&game, fields, sizeof(game));
    std::memcpy(&target, fields + 0x28, sizeof(target));
    if (!deps->dep_180023f90(game, target)) return;

    std::memcpy(&game, fields, sizeof(game));
    std::memcpy(&target, fields + 0x28, sizeof(target));
    const auto item = deps->dep_180028a50(game, target);
    if (!item) return;

    std::memcpy(&game, fields, sizeof(game));
    const auto type = deps->dep_180025c50(game, item);
    const auto bucket = static_cast<std::uint32_t>(type) - 0x105u;
    float multiplier;
    if (bucket < 0x17u && ((0x4088c0u >> (bucket & 31u)) & 1u)) {
        multiplier = multipliers[0];
    } else if (bucket == 0) {
        multiplier = multipliers[1];
    } else {
        multiplier = multipliers[2];
    }

    const double ratio = static_cast<double>(multiplier) / divisor;
    float sideways, forward;
    std::memcpy(&sideways, event + 0x10, sizeof(sideways));
    std::memcpy(&forward, event + 0x14, sizeof(forward));
    sideways = static_cast<float>(ratio * static_cast<double>(sideways));
    forward = static_cast<float>(ratio * static_cast<double>(forward));
    std::memcpy(event + 0x10, &sideways, sizeof(sideways));
    std::memcpy(event + 0x14, &forward, sizeof(forward));
}
