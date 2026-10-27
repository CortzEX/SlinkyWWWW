#include "event_callbacks.hpp"
#include <cmath>
#include <cstring>

// lib_win RVA 0x2ffb0: event 8 callback. State mirrors the module's persistent fields.
extern "C" __declspec(dllexport) void recovered_reach(
    std::uint8_t *event, ReachState *state, const Dependencies *deps) {
    std::uintptr_t frame;
    std::memcpy(&frame, event + 8, sizeof(frame));
    auto *fields = reinterpret_cast<const std::uint8_t *>(frame);
    std::uintptr_t game, target;
    std::memcpy(&game, fields, sizeof(game));
    std::memcpy(&target, fields + 0x28, sizeof(target));

    if (state->timer > 0) --state->timer;
    if (state->require_sprint == 1 && !deps->dep_180023690(game, target)) return;

    std::memcpy(&game, fields, sizeof(game));
    std::memcpy(&target, fields + 0x28, sizeof(target));
    if (state->timer == 0) {
        const auto identifier = deps->dep_1800239d0(game, target);
        if (identifier != state->previous_target) {
            state->timer = 9;
            state->previous_target = identifier;
        }
    }

    const float count = static_cast<float>(state->timer);
    const float threshold = state->activation_threshold;
    if (std::isnan(threshold) || threshold <= count) return;

    event[0x10] = 1;
    const double value = static_cast<double>(state->reach_value);
    std::memcpy(event + 0x18, &value, sizeof(value));
}
