// Runtime instruction corroboration: reports/native/render_293c0_29820.asm.
// Image constants and populated dispatch cells belong to the caller. Neither
// this source nor the captured bytes establish startup graphics targets.
#include "Graphics.hpp"
#include <cstring>
#include <emmintrin.h>
#include <intrin.h>

namespace {
template<class T> T read(const void *address) {
    T value; std::memcpy(&value, address, sizeof(value)); return value;
}
std::uint64_t target(std::uint8_t *image, unsigned rva) {
    return read<std::uint64_t>(reinterpret_cast<const void *>(read<std::uintptr_t>(image + rva)));
}
std::uint64_t vertex_array(std::uint8_t *image, RecoveredWordInvoker invoke,
    unsigned dimensions, unsigned array_rva) {
    invoke(target(image, 0x14fd10), dimensions, 0x1406, 0,
        reinterpret_cast<std::uintptr_t>(image + array_rva));
    // Reload the cell after the external operation, as in the native wrapper.
    return invoke(target(image, 0x14fd08), 0x8074, 0, 0, 0);
}
std::uint64_t indices(std::uint8_t *image, RecoveredWordInvoker invoke,
    unsigned mode, unsigned count, unsigned array_rva) {
    return invoke(target(image, 0x14fd00), mode, count, 0x1401,
        reinterpret_cast<std::uintptr_t>(image + array_rva));
}
__m128 load(const float *p) { return _mm_load_ss(p); }
__m128 row(const float *matrix, unsigned index, __m128 x, __m128 y,
    __m128 z, __m128 w, bool value_first) {
    const auto yp = value_first ? _mm_mul_ss(y, load(matrix + index + 4))
                                : _mm_mul_ss(load(matrix + index + 4), y);
    const auto xp = value_first ? _mm_mul_ss(x, load(matrix + index))
                                : _mm_mul_ss(load(matrix + index), x);
    const auto xy = _mm_add_ss(xp, yp);
    const auto zp = value_first ? _mm_mul_ss(z, load(matrix + index + 8))
                                : _mm_mul_ss(load(matrix + index + 8), z);
    const auto xyz = _mm_add_ss(zp, xy);
    const auto wp = value_first ? _mm_mul_ss(w, load(matrix + index + 12))
                                : _mm_mul_ss(load(matrix + index + 12), w);
    return _mm_add_ss(wp, xyz);
}
__m128 model_row(const float *matrix, unsigned index, __m128 x, __m128 y, __m128 z) {
    const auto yp = _mm_mul_ss(load(matrix + index + 4), y);
    const auto xp = _mm_mul_ss(load(matrix + index), x);
    const auto xy = _mm_add_ss(xp, yp);
    const auto zp = _mm_mul_ss(load(matrix + index + 8), z);
    return _mm_add_ss(_mm_add_ss(zp, xy), load(matrix + index + 12));
}
}

// 0x293C0.
std::uint64_t recovered_render_293c0(std::uint8_t *image, RecoveredWordInvoker invoke) {
    return vertex_array(image, invoke, 3, 0x14fc10);
}
// 0x29400.
std::uint64_t recovered_render_29400(std::uint8_t *image, RecoveredWordInvoker invoke) {
    return indices(image, invoke, 5, 14, 0x14fc70);
}
// 0x29430.
std::uint64_t recovered_render_29430(std::uint8_t *image, RecoveredWordInvoker invoke) {
    return indices(image, invoke, 1, 24, 0x14fc80);
}
// 0x29460.
std::uint64_t recovered_render_29460(std::uint8_t *image, RecoveredWordInvoker invoke) {
    return vertex_array(image, invoke, 2, 0x14fca0);
}
// 0x294A0.
std::uint64_t recovered_render_294a0(std::uint8_t *image, RecoveredWordInvoker invoke) {
    return indices(image, invoke, 5, 4, 0x14fcc0);
}
// 0x294D0.
std::uint64_t recovered_render_294d0(std::uint8_t *image, RecoveredWordInvoker invoke) {
    return indices(image, invoke, 2, 4, 0x14fcc4);
}
// 0x29500.
std::uint64_t recovered_render_29500(std::uint8_t *image, RecoveredWordInvoker invoke) {
    return vertex_array(image, invoke, 2, 0x14fcd0);
}
// 0x29540.
std::uint64_t recovered_render_29540(std::uint8_t *image, RecoveredWordInvoker invoke) {
    return indices(image, invoke, 6, 4, 0x14fcf0);
}
// 0x29570.
std::uint64_t recovered_render_29570(std::uint8_t *image, RecoveredWordInvoker invoke) {
    return indices(image, invoke, 2, 4, 0x14fcf4);
}
// 0x295A0.
std::uint64_t recovered_render_295a0(std::uint8_t *image, RecoveredWordInvoker invoke) {
    return invoke(target(image, 0x14fcf8), 0x8074, 0, 0, 0);
}

// 0x295C0. Copy Z then XY before the projection consumes caller-owned matrices.
std::uint32_t recovered_screen_project_295c0(std::uint8_t *context,
    const double *point, float *screen, std::uint8_t *image) {
    double snapshot[3];
    std::memcpy(snapshot + 2, point + 2, 8);
    _ReadWriteBarrier();
    std::memcpy(snapshot, point, 16);
    return recovered_screen_project_295f0(context, snapshot, screen, nullptr, image);
}

// 0x295F0. Column-major matrices, binary32 intermediates, native reduction
// order and open depth interval. Unordered depth survives both JAE branches.
// The optional output is the half-scaled reciprocal W, not normalized depth.
std::uint32_t recovered_screen_project_295f0(std::uint8_t *context,
    const double *point, float *screen, float *reciprocal_output, std::uint8_t *image) {
    const auto x = _mm_cvtsd_ss(_mm_setzero_ps(), _mm_load_sd(point));
    const auto y = _mm_cvtsd_ss(_mm_setzero_ps(), _mm_load_sd(point + 1));
    const auto z = _mm_cvtsd_ss(_mm_setzero_ps(), _mm_load_sd(point + 2));
    const auto *model = read<const float *>(context + 0x28);
    const auto *projection = read<const float *>(context + 0x30);
    const auto mx = model_row(model, 0, x, y, z);
    const auto my = model_row(model, 1, x, y, z);
    const auto mz = model_row(model, 2, x, y, z);
    const auto wxy = _mm_add_ss(_mm_mul_ss(x, load(model + 3)), _mm_mul_ss(y, load(model + 7)));
    const auto mw = _mm_add_ss(_mm_add_ss(_mm_mul_ss(z, load(model + 11)), wxy), load(model + 15));
    const auto clip_w = row(projection, 3, mx, my, mz, mw, false);
    if (_mm_cvtss_f32(clip_w) == 0.0f) return 0;
    const auto clip_z = row(projection, 2, mx, my, mz, mw, false);
    const auto one = load(reinterpret_cast<const float *>(image + 0x14fc00));
    const auto half = load(reinterpret_cast<const float *>(image + 0x14fc04));
    const auto reciprocal = _mm_mul_ss(_mm_div_ss(one, clip_w), half);
    const auto depth = _mm_add_ss(_mm_mul_ss(clip_z, reciprocal), half);
    if (0.0f >= _mm_cvtss_f32(depth) || _mm_cvtss_f32(depth) >= _mm_cvtss_f32(one)) return 0;
    const auto py = _mm_add_ss(_mm_mul_ss(row(projection, 1, mx, my, mz, mw, false), reciprocal), half);
    const auto px = _mm_add_ss(_mm_mul_ss(row(projection, 0, mx, my, mz, mw, true), reciprocal), half);
    const auto height = load(reinterpret_cast<const float *>(context + 0x24));
    const auto width = load(reinterpret_cast<const float *>(context + 0x20));
    _mm_store_ss(screen, _mm_mul_ss(px, width));
    _ReadWriteBarrier();
    _mm_store_ss(screen + 1, _mm_sub_ss(height, _mm_mul_ss(py, height)));
    if (reciprocal_output) _mm_store_ss(reciprocal_output, reciprocal);
    return 1;
}

namespace {
std::uint64_t legacyInvoke(void *context, std::uint64_t target, std::uint64_t a,
    std::uint64_t b, std::uint64_t c, std::uint64_t d) {
    return (*static_cast<RecoveredGraphicsEndpoint *>(context))(target, a, b, c, d);
}
}
std::uint64_t recovered_render_293c0(std::uint8_t *image, RecoveredGraphicsEndpoint endpoint) {
    return recovered_render_293c0(image, RecoveredWordInvoker{&endpoint, legacyInvoke});
}
std::uint64_t recovered_render_29400(std::uint8_t *image, RecoveredGraphicsEndpoint endpoint) {
    return recovered_render_29400(image, RecoveredWordInvoker{&endpoint, legacyInvoke});
}
std::uint64_t recovered_render_29430(std::uint8_t *image, RecoveredGraphicsEndpoint endpoint) {
    return recovered_render_29430(image, RecoveredWordInvoker{&endpoint, legacyInvoke});
}
std::uint64_t recovered_render_29460(std::uint8_t *image, RecoveredGraphicsEndpoint endpoint) {
    return recovered_render_29460(image, RecoveredWordInvoker{&endpoint, legacyInvoke});
}
std::uint64_t recovered_render_294a0(std::uint8_t *image, RecoveredGraphicsEndpoint endpoint) {
    return recovered_render_294a0(image, RecoveredWordInvoker{&endpoint, legacyInvoke});
}
std::uint64_t recovered_render_294d0(std::uint8_t *image, RecoveredGraphicsEndpoint endpoint) {
    return recovered_render_294d0(image, RecoveredWordInvoker{&endpoint, legacyInvoke});
}
std::uint64_t recovered_render_29500(std::uint8_t *image, RecoveredGraphicsEndpoint endpoint) {
    return recovered_render_29500(image, RecoveredWordInvoker{&endpoint, legacyInvoke});
}
std::uint64_t recovered_render_29540(std::uint8_t *image, RecoveredGraphicsEndpoint endpoint) {
    return recovered_render_29540(image, RecoveredWordInvoker{&endpoint, legacyInvoke});
}
std::uint64_t recovered_render_29570(std::uint8_t *image, RecoveredGraphicsEndpoint endpoint) {
    return recovered_render_29570(image, RecoveredWordInvoker{&endpoint, legacyInvoke});
}
std::uint64_t recovered_render_295a0(std::uint8_t *image, RecoveredGraphicsEndpoint endpoint) {
    return recovered_render_295a0(image, RecoveredWordInvoker{&endpoint, legacyInvoke});
}
