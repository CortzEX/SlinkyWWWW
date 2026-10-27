#ifndef RANDOM_PRIMITIVES_H
#define RANDOM_PRIMITIVES_H
#include <stdint.h>
/* a050 receives its bounds in XMM0/XMM1 and packs their low float bits. */
__declspec(dllexport) uint64_t recovered_a050(float xmm0_low, float xmm1_low);
/* packed_bounds is the exact RCX token: low float bits, then high float bits.
   The float result is returned through the C/XMM0 float ABI. */
__declspec(dllexport) float recovered_a3e0(uint8_t *image, uint64_t packed_bounds);
/* Test adapter: capture the returned XMM0 float as raw bits without host NaN
   conversions in ctypes. The recovered helper remains the float-return API. */
__declspec(dllexport) uint32_t recovered_a3e0_result_bits(uint8_t *image, uint64_t packed_bounds);
/* threshold_bits is the original low-XMM0 token. Return all of EAX, including
   the upper 24 bits preserved by SETA after the RNG state rotate. */
__declspec(dllexport) uint32_t recovered_a460(uint8_t *image, uint32_t threshold_bits);
#endif
