#ifndef SLINKY_SHARE_5EAF49D48D577CE28ADD
#define SLINKY_SHARE_5EAF49D48D577CE28ADD
#include <cstdint>
// Native mathematical routines reconstructed from the supplied capture. Constants
// remain caller-owned. No standard-library trig routine is substituted.
std::int32_t recovered_reduce_large_ad400(const double *input,double *output,
    std::int32_t exponent,std::int32_t count,std::int32_t precision,const std::uint8_t *constant_image);
std::int32_t recovered_reduce_float_af1b0(float,double *output,const std::uint8_t *constant_image);
float recovered_sine_b1cf0(float,const std::uint8_t *constant_image);
float recovered_cosine_b3590(float,const std::uint8_t *constant_image);
double recovered_scale_binary64_ae570(double,std::int32_t,const std::uint8_t *constant_image);
double recovered_floor_binary64_b29b0(double,const std::uint8_t *constant_image);
#endif // SLINKY_SHARE_5EAF49D48D577CE28ADD
