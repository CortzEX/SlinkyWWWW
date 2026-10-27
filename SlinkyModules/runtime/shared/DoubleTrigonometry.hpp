#ifndef SLINKY_SHARE_265E8FE344751682A449
#define SLINKY_SHARE_265E8FE344751682A449
#include <cstdint>

// Source-equivalent native binary64 routines. Original source identifiers and
// inline boundaries are unavailable; image-backed constants remain borrowed.
std::int32_t recovered_reduce_double_aec00(double value, double* residual,
    const std::uint8_t* constant_image);
double recovered_sine_b1990(double value, const std::uint8_t* constant_image);
#endif // SLINKY_SHARE_265E8FE344751682A449
