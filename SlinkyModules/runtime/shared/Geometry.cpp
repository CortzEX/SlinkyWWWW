// Source-equivalent reconstruction corroborated against the supplied offline
// runtime image. The packed lib_win has no file-backed bytes at these RVAs.
// Original names and inline boundaries are unavailable. Independent captured
// instruction listings are in reports/native; no captured settings are defaults.
#include "Geometry.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>
#include <intrin.h>

namespace {
__m128 scalar_word(std::uint32_t bits) {
    return _mm_castsi128_ps(_mm_cvtsi32_si128(std::bit_cast<std::int32_t>(bits)));
}
std::uint32_t word(__m128 value) {
    return static_cast<std::uint32_t>(_mm_cvtsi128_si32(_mm_castps_si128(value)));
}
std::uint64_t pack(__m128 yaw, __m128 pitch) {
    return word(yaw) | (std::uint64_t{word(pitch)} << 32);
}
__m128d ignore_nan_right_max(__m128d left, __m128d right) {
    const auto unordered = _mm_cmpunord_sd(right, right);
    return _mm_or_pd(_mm_and_pd(unordered, left),
        _mm_andnot_pd(unordered, _mm_max_sd(left, right)));
}
__m128d ignore_nan_right_min(__m128d left, __m128d right) {
    const auto unordered = _mm_cmpunord_sd(right, right);
    return _mm_or_pd(_mm_and_pd(unordered, left),
        _mm_andnot_pd(unordered, _mm_min_sd(left, right)));
}
__m128d round_trip_binary32(__m128d value) {
    return _mm_cvtss_sd(_mm_setzero_pd(), _mm_cvtsd_ss(_mm_setzero_ps(), value));
}
}

// 0x93B0. Three stores in X/Y/Z order, destination returned unchanged.
void *recovered_geometry_construct_93b0(void *destination, double x, double y, double z) {
    auto *out = static_cast<double *>(destination);
    _mm_store_sd(out, _mm_set_sd(x));
    _ReadWriteBarrier();
    _mm_store_sd(out + 1, _mm_set_sd(y));
    _ReadWriteBarrier();
    _mm_store_sd(out + 2, _mm_set_sd(z));
    return destination;
}

// 0x93D0. The XY store precedes both Z reads, including overlapping records.
double *recovered_vector_subtract_93d0(double *out, const double *left, const double *right) {
    const auto left_xy = _mm_loadu_pd(left);
    const auto right_xy = _mm_loadu_pd(right);
    _mm_storeu_pd(out, _mm_sub_pd(left_xy, right_xy));
    _ReadWriteBarrier();
    const auto left_z = _mm_load_sd(left + 2);
    const auto right_z = _mm_load_sd(right + 2);
    _mm_store_sd(out + 2, _mm_sub_sd(left_z, right_z));
    return out;
}

// 0x9400. XY is left+right, Z is right+left. Do not commute the Z operands.
void *recovered_geometry_add_9400(double *out, const double *left, const double *right) {
    const auto right_xy = _mm_loadu_pd(right);
    const auto left_xy = _mm_loadu_pd(left);
    _mm_storeu_pd(out, _mm_add_pd(left_xy, right_xy));
    _ReadWriteBarrier();
    const auto right_z = _mm_load_sd(right + 2);
    const auto left_z = _mm_load_sd(left + 2);
    _mm_store_sd(out + 2, _mm_add_sd(right_z, left_z));
    return out;
}

// 0x9430. Scale is the first multiplication operand in each lane.
double *recovered_vector_scale_9430(double *out, const double *value, double scale) {
    const auto xy = _mm_loadu_pd(value);
    const auto factor = _mm_set1_pd(scale);
    _mm_storeu_pd(out, _mm_mul_pd(factor, xy));
    _ReadWriteBarrier();
    _mm_store_sd(out + 2, _mm_mul_sd(_mm_set_sd(scale), _mm_load_sd(value + 2)));
    return out;
}

// 0x9460. XY uses fraction*delta + first. Z uses delta*fraction + first.
double *recovered_vector_lerp_9460(double *out, const double *first, const double *second, double fraction) {
    const auto first_xy = _mm_loadu_pd(first);
    const auto second_xy = _mm_loadu_pd(second);
    const auto difference_xy = _mm_sub_pd(second_xy, first_xy);
    const auto scaled_xy = _mm_mul_pd(_mm_set1_pd(fraction), difference_xy);
    _mm_storeu_pd(out, _mm_add_pd(scaled_xy, first_xy));
    _ReadWriteBarrier();
    const auto first_z = _mm_load_sd(first + 2);
    const auto second_z = _mm_load_sd(second + 2);
    const auto difference_z = _mm_sub_sd(second_z, first_z);
    const auto scaled_z = _mm_mul_sd(difference_z, _mm_set_sd(fraction));
    _mm_store_sd(out + 2, _mm_add_sd(scaled_z, first_z));
    return out;
}

// 0x94B0. Reduction is Z^2 + (X^2 + Y^2), with separate intermediate rounding.
double recovered_vector_distance_squared(const double *left, const double *right) {
    const auto x = _mm_sub_sd(_mm_load_sd(left), _mm_load_sd(right));
    const auto y = _mm_sub_sd(_mm_load_sd(left + 1), _mm_load_sd(right + 1));
    const auto z = _mm_sub_sd(_mm_load_sd(left + 2), _mm_load_sd(right + 2));
    const auto y_squared = _mm_mul_sd(y, y);
    const auto x_squared = _mm_mul_sd(x, x);
    const auto xy_squared = _mm_add_sd(x_squared, y_squared);
    const auto z_squared = _mm_mul_sd(z, z);
    return _mm_cvtsd_f64(_mm_add_sd(z_squared, xy_squared));
}

// 0x94F0. SQRTSD consumes the same ordered squared sum as 0x94B0.
double recovered_vector_distance_94f0(const double *left, const double *right) {
    const auto sum = _mm_set_sd(recovered_vector_distance_squared(left, right));
    return _mm_cvtsd_f64(_mm_sqrt_sd(_mm_setzero_pd(), sum));
}

// 0x9650. Caller supplies the three constant words at original RVA 0x13E860.
// XY is loaded before its store; the Z numerator and input are loaded afterward.
double *recovered_vector_reciprocal_9650(double *out, const double *value, const std::uint8_t *image) {
    const auto xy = _mm_loadu_pd(value);
    __m128d numerator;
    std::memcpy(&numerator, image + 0x13e860, 16);
    _mm_storeu_pd(out, _mm_div_pd(numerator, xy));
    _ReadWriteBarrier();
    double z_numerator;
    std::memcpy(&z_numerator, image + 0x13e870, 8);
    _mm_store_sd(out + 2, _mm_div_sd(_mm_set_sd(z_numerator), _mm_load_sd(value + 2)));
    return out;
}

// 0x96B0. Store minimum Z, minimum XY, maximum XY, maximum Z in that order.
void *recovered_geometry_pair_96b0(void *destination, const void *minimum, const void *maximum) {
    auto *out = static_cast<double *>(destination);
    const auto *lower = static_cast<const double *>(minimum);
    const auto *upper = static_cast<const double *>(maximum);
    _mm_store_sd(out + 2, _mm_load_sd(lower + 2));
    _ReadWriteBarrier();
    _mm_storeu_pd(out, _mm_loadu_pd(lower));
    _ReadWriteBarrier();
    _mm_storeu_pd(out + 3, _mm_loadu_pd(upper));
    _ReadWriteBarrier();
    _mm_store_sd(out + 5, _mm_load_sd(upper + 2));
    return destination;
}

// 0x97D0. JBE rejects each unordered comparison as well as touching bounds.
std::uint8_t recovered_geometry_intersects_97d0(const double *a, const double *b) {
    if (!(b[3] > a[0])) return 0;
    if (!(a[3] > b[0])) return 0;
    if (!(b[4] > a[1])) return 0;
    if (!(a[4] > b[1])) return 0;
    if (!(b[5] > a[2])) return 0;
    return a[5] > b[2];
}

// 0x9880. The same MIN/mask policy as A1F0, first XY then Z after storing XY.
double *recovered_box_clamp_9880(double *out, const double *box, const double *point) {
    const auto lower_xy = _mm_loadu_pd(box);
    const auto upper_xy = _mm_loadu_pd(box + 3);
    const auto value_xy = _mm_loadu_pd(point);
    const auto high_xy = _mm_min_pd(upper_xy, value_xy);
    const auto below_xy = _mm_cmplt_pd(value_xy, lower_xy);
    _mm_storeu_pd(out, _mm_or_pd(_mm_and_pd(lower_xy, below_xy), _mm_andnot_pd(below_xy, high_xy)));
    _ReadWriteBarrier();
    const auto lower_z = _mm_load_sd(box + 2);
    const auto upper_z = _mm_load_sd(box + 5);
    const auto value_z = _mm_load_sd(point + 2);
    const auto high_z = _mm_min_sd(upper_z, value_z);
    const auto below_z = _mm_cmplt_sd(value_z, lower_z);
    _mm_store_sd(out + 2, _mm_or_pd(_mm_and_pd(lower_z, below_z), _mm_andnot_pd(below_z, high_z)));
    return out;
}

// 0x98E0. Slab ray test deliberately rounds each parameter and each reduction
// to binary32. The Z reductions suppress a NaN in their right operands.
// Native AND AL,1 leaves upper EAX bits set on success: return 0xFFFFFF01.
std::uint32_t recovered_box_ray_98e0(const double *box, const double *origin,
    const double *inverse_direction, const std::uint8_t *image) {
    const auto lower_x = _mm_load_sd(box);
    const auto lower_y = _mm_load_sd(box + 1);
    const auto lower_z = _mm_load_sd(box + 2);
    const auto upper_x = _mm_load_sd(box + 3);
    const auto upper_y = _mm_load_sd(box + 4);
    const auto upper_z = _mm_load_sd(box + 5);
    const auto origin_x = _mm_load_sd(origin);
    const auto origin_y = _mm_load_sd(origin + 1);
    const auto reciprocal_x = _mm_load_sd(inverse_direction);
    const auto reciprocal_y = _mm_load_sd(inverse_direction + 1);
    const auto x0 = round_trip_binary32(_mm_mul_sd(_mm_sub_sd(lower_x, origin_x), reciprocal_x));
    const auto x1 = round_trip_binary32(_mm_mul_sd(_mm_sub_sd(upper_x, origin_x), reciprocal_x));
    const auto zero = _mm_setzero_pd();
    const auto entry_x = round_trip_binary32(_mm_min_sd(_mm_max_sd(x0, zero), _mm_max_sd(x1, zero)));
    double maximum;
    std::memcpy(&maximum, image + 0x13e878, 8);
    const auto limit = _mm_set_sd(maximum);
    const auto exit_x = round_trip_binary32(_mm_max_sd(_mm_min_sd(x0, limit), _mm_min_sd(x1, limit)));
    const auto y0 = round_trip_binary32(_mm_mul_sd(_mm_sub_sd(lower_y, origin_y), reciprocal_y));
    const auto y1 = round_trip_binary32(_mm_mul_sd(_mm_sub_sd(upper_y, origin_y), reciprocal_y));
    const auto origin_z = _mm_load_sd(origin + 2);
    const auto entry_y = round_trip_binary32(_mm_min_sd(_mm_max_sd(y0, entry_x), _mm_max_sd(y1, entry_x)));
    const auto reciprocal_z = _mm_load_sd(inverse_direction + 2);
    const auto exit_y = round_trip_binary32(_mm_max_sd(_mm_min_sd(y0, exit_x), _mm_min_sd(y1, exit_x)));
    const auto z0 = round_trip_binary32(_mm_mul_sd(_mm_sub_sd(lower_z, origin_z), reciprocal_z));
    const auto z1 = round_trip_binary32(_mm_mul_sd(_mm_sub_sd(upper_z, origin_z), reciprocal_z));
    const auto entry_z0 = ignore_nan_right_max(entry_y, z0);
    const auto entry_z1 = ignore_nan_right_max(entry_y, z1);
    const auto entry = _mm_cvtsd_ss(_mm_setzero_ps(), ignore_nan_right_min(entry_z1, entry_z0));
    const auto exit_z0 = ignore_nan_right_min(exit_y, z0);
    const auto exit_z1 = ignore_nan_right_min(exit_y, z1);
    const auto exit = _mm_cvtsd_ss(_mm_setzero_ps(), ignore_nan_right_max(exit_z1, exit_z0));
    float maximum_entry;
    std::memcpy(&maximum_entry, image + 0x13e880, 4);
    const auto mask = _mm_and_ps(_mm_cmplt_ss(entry, exit), _mm_cmple_ss(entry, _mm_set_ss(maximum_entry)));
    const auto result = word(mask);
    return (result & 0xffffff00u) | (result & 1u);
}

// 0x9E60. Packed yaw/pitch words scale independently without normalization.
std::uint64_t recovered_angle_scale_9e60(std::uint64_t rotation, float scale) {
    const auto yaw = scalar_word(static_cast<std::uint32_t>(rotation));
    const auto pitch = scalar_word(static_cast<std::uint32_t>(rotation >> 32));
    const auto factor = _mm_set_ss(scale);
    return pack(_mm_mul_ss(yaw, factor), _mm_mul_ss(pitch, factor));
}

// 0x9E90. Each lane is (second-first)*fraction + first, with no angle wrapping.
std::uint64_t recovered_angle_lerp_9e90(std::uint64_t first, std::uint64_t second, float fraction) {
    const auto a_yaw = scalar_word(static_cast<std::uint32_t>(first));
    const auto a_pitch = scalar_word(static_cast<std::uint32_t>(first >> 32));
    const auto b_yaw = scalar_word(static_cast<std::uint32_t>(second));
    const auto b_pitch = scalar_word(static_cast<std::uint32_t>(second >> 32));
    const auto factor = _mm_set_ss(fraction);
    return pack(_mm_add_ss(_mm_mul_ss(_mm_sub_ss(b_yaw, a_yaw), factor), a_yaw),
                _mm_add_ss(_mm_mul_ss(_mm_sub_ss(b_pitch, a_pitch), factor), a_pitch));
}

// 0xA1F0. MINSS and the explicit mask retain native NaN and signed-zero rules.
float recovered_float_clamp_a1f0(float lower, float upper, float value) {
    const auto low = _mm_set_ss(lower);
    const auto high = _mm_set_ss(upper);
    const auto input = _mm_set_ss(value);
    const auto bounded_high = _mm_min_ss(high, input);
    const auto below_low = _mm_cmplt_ss(input, low);
    return _mm_cvtss_f32(_mm_or_ps(_mm_and_ps(low, below_low), _mm_andnot_ps(below_low, bounded_high)));
}

// 0xA2B0. Separate SUBSS, MULSS and ADDSS, no FMA or fraction clamp.
float recovered_scalar_lerp_a2b0(float first, float second, float fraction) {
    const auto a = _mm_set_ss(first);
    const auto difference = _mm_sub_ss(_mm_set_ss(second), a);
    const auto scaled = _mm_mul_ss(difference, _mm_set_ss(fraction));
    return _mm_cvtss_f32(_mm_add_ss(a, scaled));
}

// 0xA2D0. Binary64 counterpart with the same operand and reduction order.
double recovered_scalar_lerp_a2d0(double first, double second, double fraction) {
    const auto a = _mm_set_sd(first);
    const auto difference = _mm_sub_sd(_mm_set_sd(second), a);
    const auto scaled = _mm_mul_sd(difference, _mm_set_sd(fraction));
    return _mm_cvtsd_f64(_mm_add_sd(a, scaled));
}

// 0x9590/0x95C0. Each store precedes the next input load. The native constants
// are caller-owned; these routines preserve overlapping records and Y operand order.
namespace {
double *offset_y(double *out,const double *in,const std::uint8_t *image,std::uint32_t rva) {
    _mm_store_sd(out,_mm_load_sd(in));
    _ReadWriteBarrier();
    _mm_store_sd(out+1,_mm_add_sd(_mm_load_sd(in+1),_mm_load_sd(reinterpret_cast<const double *>(image+rva))));
    _ReadWriteBarrier();
    _mm_store_sd(out+2,_mm_load_sd(in+2));
    return out;
}
}
double *recovered_vector_y_offset_9590(double *out,const double *in,const std::uint8_t *image) {
    return offset_y(out,in,image,0x13e850);
}
double *recovered_vector_adjust_95c0(double *out,const double *in,const std::uint8_t *image) {
    return offset_y(out,in,image,0x13e858);
}

// 0x9770 mutates its source record before copying the three 16-byte blocks to
// the destination in descending address order. Z upper addition is amount+Z.
double *recovered_box_expand_9770(double *out,double *source,double amount) {
    const auto scale=_mm_set1_pd(amount);
    _mm_storeu_pd(source,_mm_sub_pd(_mm_loadu_pd(source),scale));
    _ReadWriteBarrier();
    _mm_store_sd(source+2,_mm_sub_sd(_mm_load_sd(source+2),_mm_set_sd(amount)));
    _ReadWriteBarrier();
    _mm_storeu_pd(source+3,_mm_add_pd(_mm_loadu_pd(source+3),scale));
    _ReadWriteBarrier();
    _mm_store_sd(source+5,_mm_add_sd(_mm_set_sd(amount),_mm_load_sd(source+5)));
    _ReadWriteBarrier();
    _mm_storeu_pd(out+4,_mm_loadu_pd(source+4));
    _ReadWriteBarrier();
    _mm_storeu_pd(out+2,_mm_loadu_pd(source+2));
    _ReadWriteBarrier();
    _mm_storeu_pd(out,_mm_loadu_pd(source));
    return out;
}
// 0x9DE0. The second packed angle is the first ADDSS operand in both lanes.
std::uint64_t recovered_angle_add_9de0(std::uint64_t first,std::uint64_t second) {
    return pack(_mm_add_ss(scalar_word(static_cast<std::uint32_t>(second)),scalar_word(static_cast<std::uint32_t>(first))),
        _mm_add_ss(scalar_word(static_cast<std::uint32_t>(second>>32)),scalar_word(static_cast<std::uint32_t>(first>>32))));
}
// 0x9E20. Both lanes use first-second.
std::uint64_t recovered_angle_subtract_9e20(std::uint64_t first,std::uint64_t second) {
    return pack(_mm_sub_ss(scalar_word(static_cast<std::uint32_t>(first)),scalar_word(static_cast<std::uint32_t>(second))),
        _mm_sub_ss(scalar_word(static_cast<std::uint32_t>(first>>32)),scalar_word(static_cast<std::uint32_t>(second>>32))));
}
// 0x9F60 tail-calls 0xAB7C0 with the two binary32 lanes, with no subtraction.
std::uint32_t recovered_angle_magnitude_9f60(std::uint64_t value,const FloatDistanceConstants *constants) {
    return recovered_float_distance(static_cast<std::uint32_t>(value),static_cast<std::uint32_t>(value>>32),constants);
}
