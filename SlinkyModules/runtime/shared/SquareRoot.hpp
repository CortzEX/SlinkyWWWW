#ifndef SLINKY_SHARE_F6ECEA97FC5479CF4E41
#define SLINKY_SHARE_F6ECEA97FC5479CF4E41
#include <cstdint>

// Caller-owned image supplies the shared 128-entry reciprocal seed table and
// subnormal scaling constants; no host sqrt library replacement is used.
double recovered_square_root_af2f0(double, const std::uint8_t *constant_image);
float recovered_square_root_af4a0(float, const std::uint8_t *constant_image);
#endif // SLINKY_SHARE_F6ECEA97FC5479CF4E41
