#ifndef SLINKY_SHARE_4C32EE7D5556A183FE67
#define SLINKY_SHARE_4C32EE7D5556A183FE67
#include <cstdint>
// Native scalar/SSE order retained. Semantic names are assigned during recovery.
float *recovered_hsl_74220(float *,float hue,float saturation,float lightness,
    const std::uint8_t *constantImage);
float *recovered_hsla_74250(float *,float hue,float saturation,float lightness,
    std::uint8_t alpha,const std::uint8_t *constantImage);
float recovered_floor_b2a70(float,const std::uint8_t *constantImage);
#endif // SLINKY_SHARE_4C32EE7D5556A183FE67
