#include "module_input_query.hpp"

// 0x8bd0 consumes the request again after every external call.
extern "C" __declspec(dllexport) std::uint32_t recovered_input_query(
    InputRequest *request, InputQueryState *state, const InputQueryDependencies *dependencies) {
    std::uint8_t unchanged = 1;
    if (request->type == 2) {
        const auto old = state->bits[request->key];
        const auto bit = static_cast<std::uint8_t>(old & 1);
        auto requested = request->requested;
        if (request->toggle != 1 || bit != requested) {
            if (request->toggle == 1)
                requested = static_cast<std::uint8_t>((requested | (old & 2)) ^ 2);
            state->bits[request->key] = requested;
            unchanged = bit == request->requested;
        }
    }
    using GetEnvironment = std::uint32_t (*)(std::uintptr_t *, std::uintptr_t **, std::uint32_t);
    auto *owner = state->environment_owner;
    const auto *table = reinterpret_cast<const std::uintptr_t *>(*owner);
    std::uintptr_t *environment;
    if (reinterpret_cast<GetEnvironment>(table[0x30 / 8])(owner, &environment, 0x10008) != 0)
        return 0;
    GameAccessBridge bridge{state->metadata, environment};
    const auto result = dependencies->dispatch(request, unchanged, state->action_context);
    if (static_cast<std::uint8_t>(result) || request->type != 2 || unchanged || !request->key)
        return result;
    const auto current = dependencies->current(&bridge);
    if (!static_cast<std::uint8_t>(dependencies->ready(&bridge, current))) return result;
    if (state->ghost->enabled) return result;
    if (state->friends->enabled == 1 && request->type == 2 && request->requested == 1 && request->key == 3)
        dependencies->friend_action(&bridge, state->action_context);
    if (!static_cast<std::uint8_t>(dependencies->keys(state->primary_keys, request->key, request->requested)))
        dependencies->keys(state->secondary_keys, request->key, request->requested);
    return result;
}
