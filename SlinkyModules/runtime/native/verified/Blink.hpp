#ifndef SLINKY_SHARE_CE70567B6FD61DA7B100
#define SLINKY_SHARE_CE70567B6FD61DA7B100
#include <cstdint>

struct BlinkDependencies {
    std::int32_t (*current_239d0)(std::uint64_t, std::uint64_t);
    void (*queue_state_284f0)(std::uint64_t, std::uint64_t, std::uint8_t);
    std::uint64_t (*packet_26a30)(std::uint64_t, std::uint64_t);
    std::uint64_t (*packet_26ad0)(std::uint64_t, std::uint64_t);
    std::uint64_t (*packet_26a90)(std::uint64_t, std::uint64_t);
    std::uint64_t (*packet_27160)(std::uint64_t, std::uint64_t);
    std::uint64_t (*hit_22e10)(std::uint64_t, std::uint64_t);
    std::int32_t (*hit_type_24b50)(std::uint64_t, std::uint64_t);
};
static_assert(sizeof(BlinkDependencies) == 64);

extern "C" {
__declspec(dllexport) void blink_0(std::uint8_t *, std::uint8_t *settings, std::uint8_t *state, const BlinkDependencies *);
__declspec(dllexport) void blink_2(std::uint8_t *, std::uint8_t *state, const BlinkDependencies *);
__declspec(dllexport) void blink_3(std::uint8_t *, std::uint8_t *state);
__declspec(dllexport) void blink_5(std::uint8_t *, std::uint8_t *settings, std::uint8_t *state);
__declspec(dllexport) void blink_14(std::uint8_t *, std::uint8_t *settings, const BlinkDependencies *);
__declspec(dllexport) std::uint64_t recovered_blink_packet(std::uint64_t bridge, std::uint64_t packet, std::uint32_t helper_rva);
// Bind seven game-access helpers. The state-queue endpoint is supplied by the caller.
__declspec(dllexport) void recovered_bind_blink_access(BlinkDependencies *);
}
#endif // SLINKY_SHARE_CE70567B6FD61DA7B100
