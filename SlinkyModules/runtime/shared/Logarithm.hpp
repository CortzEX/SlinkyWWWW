#ifndef SLINKY_SHARE_69877F97816100092461
#define SLINKY_SHARE_69877F97816100092461
#include <cstdint>

// Runtime instruction evidence: reports/native/float_logarithm_b2050.asm.
// Polynomial coefficients and split ln(2) are borrowed from the captured image.
float recovered_logarithm_b2050(float value, const std::uint8_t *constant_image);
#endif // SLINKY_SHARE_69877F97816100092461
