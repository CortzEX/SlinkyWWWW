#include "Blink.hpp"
#include "module_access_helpers.hpp"

#include <cstdlib>
#include <cstring>

extern "C" __declspec(dllexport) std::uint64_t recovered_blink_packet(
    std::uint64_t bridge_address, std::uint64_t packet, std::uint32_t helper_rva) {
    std::size_t offset;
    switch (helper_rva) {
    case 0x26a30: offset = 0x850; break;
    case 0x26ad0: offset = 0x868; break;
    case 0x26a90: offset = 0x860; break;
    case 0x27160: offset = 0xd08; break;
    default: std::abort();
    }
    const auto *bridge = reinterpret_cast<const GameAccessBridge *>(bridge_address);
    std::uintptr_t identifier;
    std::memcpy(&identifier, bridge->metadata + offset, sizeof(identifier));
    const auto *table = reinterpret_cast<const std::uintptr_t *>(*bridge->environment);
    using Predicate = std::uint8_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t);
    const auto predicate = reinterpret_cast<Predicate>(table[0x100 / sizeof(std::uintptr_t)]);
    return predicate(bridge->environment, packet, identifier) ? packet : 0;
}

template <std::uint32_t Rva>
static std::uint64_t packet(std::uint64_t bridge, std::uint64_t object) {
    return recovered_blink_packet(bridge, object, Rva);
}

static std::int32_t current(std::uint64_t bridge, std::uint64_t object) {
    return recovered_game_last_attacker_time(reinterpret_cast<GameAccessBridge *>(bridge), object);
}

static std::uint64_t hit(std::uint64_t bridge, std::uint64_t object) {
    return recovered_access_helper(reinterpret_cast<GameAccessBridge *>(bridge), 0x22e10, object, 0, 0);
}

static std::int32_t hit_type(std::uint64_t bridge, std::uint64_t object) {
    return static_cast<std::int32_t>(recovered_access_helper(
        reinterpret_cast<GameAccessBridge *>(bridge), 0x24b50, object, 0, 0));
}

extern "C" __declspec(dllexport) void recovered_bind_blink_access(BlinkDependencies *dependencies) {
    dependencies->current_239d0 = current;
    dependencies->packet_26a30 = packet<0x26a30>;
    dependencies->packet_26ad0 = packet<0x26ad0>;
    dependencies->packet_26a90 = packet<0x26a90>;
    dependencies->packet_27160 = packet<0x27160>;
    dependencies->hit_22e10 = hit;
    dependencies->hit_type_24b50 = hit_type;
}
