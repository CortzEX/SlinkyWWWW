#include "module_placement_geometry.hpp"
#include <emmintrin.h>
#include <intrin.h>

// 0x93b0 stores each raw double and returns the destination.
extern "C" __declspec(dllexport) PlacementPosition *recovered_placement_position(
    PlacementPosition *out, double x, double y, double z) {
    out->x = x;
    out->y = y;
    out->z = z;
    return out;
}

// 0x9400 captures XY before storing it, then reads Z. Z uses right + left,
// which affects NaN payloads and partially overlapping input/output records.
extern "C" __declspec(dllexport) PlacementPosition *recovered_placement_add(
    PlacementPosition *out, const PlacementPosition *left, const PlacementPosition *right) {
    const auto rxy = _mm_loadu_pd(&right->x);
    const auto lxy = _mm_loadu_pd(&left->x);
    _mm_storeu_pd(&out->x, _mm_add_pd(lxy, rxy));
    _ReadWriteBarrier();
    const auto rz = _mm_load_sd(&right->z);
    const auto lz = _mm_load_sd(&left->z);
    _mm_store_sd(&out->z, _mm_add_sd(rz, lz));
    return out;
}

// 0x96b0's store order is observable when a corner overlaps the destination.
extern "C" __declspec(dllexport) PlacementBox *recovered_placement_box(
    PlacementBox *out, const PlacementPosition *minimum, const PlacementPosition *maximum) {
    _mm_store_sd(&out->minimum.z, _mm_load_sd(&minimum->z));
    _ReadWriteBarrier();
    _mm_storeu_pd(&out->minimum.x, _mm_loadu_pd(&minimum->x));
    _ReadWriteBarrier();
    _mm_storeu_pd(&out->maximum.x, _mm_loadu_pd(&maximum->x));
    _ReadWriteBarrier();
    _mm_store_sd(&out->maximum.z, _mm_load_sd(&maximum->z));
    return out;
}

// 0x97d0 requires positive overlap on all axes. Touching or NaN fails.
extern "C" __declspec(dllexport) std::uint8_t recovered_placement_intersects(
    const PlacementBox *a, const PlacementBox *b) {
    return b->maximum.x > a->minimum.x && a->maximum.x > b->minimum.x &&
           b->maximum.y > a->minimum.y && a->maximum.y > b->minimum.y &&
           b->maximum.z > a->minimum.z && a->maximum.z > b->minimum.z;
}
