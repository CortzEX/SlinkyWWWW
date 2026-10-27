#ifndef SLINKY_SHARE_E569C3D0B766448A5461
#define SLINKY_SHARE_E569C3D0B766448A5461
#include <cstdint>
namespace reconstruction::no_hit_delay {
using StatusEndpoint = std::uint64_t (*)(std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t,
                                         std::uint64_t);
void writeStatus(char *, const std::uint8_t *stateImage, StatusEndpoint);
} // namespace reconstruction::no_hit_delay
#endif // SLINKY_SHARE_E569C3D0B766448A5461
