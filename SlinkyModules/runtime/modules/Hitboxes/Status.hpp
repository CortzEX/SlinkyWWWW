#ifndef SLINKY_SHARE_D2841F11326653C19EBF
#define SLINKY_SHARE_D2841F11326653C19EBF
#include <cstdint>
namespace reconstruction::hitboxes {
using StatusEndpoint = std::uint64_t (*)(std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t,
                                         std::uint64_t);
void writeStatus(char *, const std::uint8_t *stateImage, StatusEndpoint);
} // namespace reconstruction::hitboxes
#endif // SLINKY_SHARE_D2841F11326653C19EBF
