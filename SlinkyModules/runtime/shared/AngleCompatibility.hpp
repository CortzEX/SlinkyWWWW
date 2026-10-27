#ifndef SLINKY_SHARE_1C08C05AA034B5089343
#define SLINKY_SHARE_1C08C05AA034B5089343
#include <cstdint>

using RecoveredAngleEndpoint = std::uint64_t (*)(std::uint32_t target,
    std::uint64_t first, std::uint64_t second, std::uint64_t third, std::uint64_t fourth);

// Compatibility with the recovered callback ABI. The local remainder algorithm
// is available, so the endpoint is retained for signature compatibility only.
float recovered_angle_wrap_a210(float angle, std::uint8_t *constantImage,
    RecoveredAngleEndpoint endpoint);
#endif // SLINKY_SHARE_1C08C05AA034B5089343
