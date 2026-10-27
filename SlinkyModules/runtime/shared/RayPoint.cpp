#include "RayPoint.hpp"
#include <cstring>
#include <emmintrin.h>
#include <intrin.h>
namespace {
std::uint32_t word(__m128 x) { return std::uint32_t(_mm_cvtsi128_si32(_mm_castps_si128(x))); }
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
// Captured9B00 computes its own reciprocal direction and writes a hit point.
// Unordered success comparisons differ from98E0; upper EAX is retained.
std::uint32_t recovered_box_ray_point_9b00(const double *box, const double *origin,
    const double *direction, double *hit, const std::uint8_t *image) {
    const auto direction_z = _mm_load_sd(direction + 2);
    double numerator; std::memcpy(&numerator,image+0x13e888,8);
    const auto reciprocal_z = _mm_div_sd(_mm_set_sd(numerator), direction_z);
    const auto direction_xy = _mm_loadu_pd(direction);
    const auto reciprocal_x = _mm_div_sd(_mm_set_sd(numerator), direction_xy);
    const auto reciprocal_y = _mm_div_sd(_mm_set_sd(numerator), _mm_unpackhi_pd(direction_xy,direction_xy));
    const auto lower_x = _mm_load_sd(box);
    const auto lower_y = _mm_load_sd(box + 1);
    const auto lower_z = _mm_load_sd(box + 2);
    const auto upper_x = _mm_load_sd(box + 3);
    const auto upper_y = _mm_load_sd(box + 4);
    const auto upper_z = _mm_load_sd(box + 5);
    const auto origin_xy = _mm_loadu_pd(origin);
    const auto origin_x = origin_xy;
    const auto origin_y = _mm_unpackhi_pd(origin_xy,origin_xy);
    const auto x0 = round_trip_binary32(_mm_mul_sd(_mm_sub_sd(lower_x, origin_x), reciprocal_x));
    const auto x1 = round_trip_binary32(_mm_mul_sd(_mm_sub_sd(upper_x, origin_x), reciprocal_x));
    const auto zero = _mm_setzero_pd();
    const auto entry_x = round_trip_binary32(_mm_min_sd(_mm_max_sd(x0, zero), _mm_max_sd(x1, zero)));
    double maximum;
    std::memcpy(&maximum, image + 0x13e890, 8);
    const auto limit = _mm_set_sd(maximum);
    const auto exit_x = round_trip_binary32(_mm_max_sd(_mm_min_sd(x0, limit), _mm_min_sd(x1, limit)));
    const auto y0 = round_trip_binary32(_mm_mul_sd(_mm_sub_sd(lower_y, origin_y), reciprocal_y));
    const auto y1 = round_trip_binary32(_mm_mul_sd(_mm_sub_sd(upper_y, origin_y), reciprocal_y));
    const auto origin_z = _mm_load_sd(origin + 2);
    const auto entry_y = round_trip_binary32(_mm_min_sd(_mm_max_sd(y0, entry_x), _mm_max_sd(y1, entry_x)));
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
    std::memcpy(&maximum_entry, image + 0x13e898, 4);
    const auto mask = _mm_and_ps(_mm_cmpnle_ss(exit, entry), _mm_cmpnlt_ss(_mm_set_ss(maximum_entry), entry));
    const auto result = word(mask);
    if(result & 1u) {
        const auto factor=_mm_cvtss_sd(_mm_setzero_pd(),entry);
        const auto z=_mm_add_sd(origin_z,_mm_mul_sd(direction_z,factor));
        _mm_storeu_pd(hit,_mm_add_pd(origin_xy,_mm_mul_pd(direction_xy,_mm_unpacklo_pd(factor,factor))));
        _ReadWriteBarrier(); _mm_store_sd(hit+2,z);
    }
    return (result & 0xffffff00u) | (result & 1u);
}

