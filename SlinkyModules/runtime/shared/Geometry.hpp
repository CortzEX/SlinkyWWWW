#ifndef SLINKY_SHARE_E91147C6DA6F12185A92
#define SLINKY_SHARE_E91147C6DA6F12185A92
#include <cstdint>

// Semantic names assigned during recovery. See Geometry.cpp for native RVAs.
// These retain native arithmetic and alias ordering. Captured bytes are runtime
// instruction evidence, not proof of original source spelling or startup values.
void *recovered_geometry_construct_93b0(void *, double, double, double);
double *recovered_vector_subtract_93d0(double *, const double *, const double *);
void *recovered_geometry_add_9400(double *, const double *, const double *);
double *recovered_vector_scale_9430(double *, const double *, double);
double *recovered_vector_lerp_9460(double *, const double *, const double *, double);
double recovered_vector_distance_squared(const double *, const double *);
double recovered_vector_distance_94f0(const double *, const double *);
double *recovered_vector_reciprocal_9650(double *, const double *, const std::uint8_t *constant_image);
void *recovered_geometry_pair_96b0(void *, const void *, const void *);
std::uint8_t recovered_geometry_intersects_97d0(const double *, const double *);
double *recovered_box_clamp_9880(double *, const double *box, const double *point);
std::uint32_t recovered_box_ray_98e0(const double *box, const double *origin,
    const double *inverse_direction, const std::uint8_t *constant_image);
std::uint64_t recovered_angle_scale_9e60(std::uint64_t, float);
std::uint64_t recovered_angle_lerp_9e90(std::uint64_t, std::uint64_t, float);
// Native argument order is lower, upper, value, rather than value, lower, upper.
float recovered_float_clamp_a1f0(float lower, float upper, float value);
float recovered_scalar_lerp_a2b0(float first, float second, float fraction);
double recovered_scalar_lerp_a2d0(double first, double second, double fraction);

double *recovered_vector_y_offset_9590(double *,const double *,const std::uint8_t *constant_image);
double *recovered_vector_adjust_95c0(double *,const double *,const std::uint8_t *constant_image);

#include "../native/verified/module_float_distance.hpp"
double *recovered_box_expand_9770(double *out,double *source,double amount);
std::uint64_t recovered_angle_add_9de0(std::uint64_t first,std::uint64_t second);
std::uint64_t recovered_angle_subtract_9e20(std::uint64_t first,std::uint64_t second);
std::uint32_t recovered_angle_magnitude_9f60(std::uint64_t,const FloatDistanceConstants *);
#endif // SLINKY_SHARE_E91147C6DA6F12185A92
