#ifndef SLINKY_SHARE_EF61703C25503B328AF4
#define SLINKY_SHARE_EF61703C25503B328AF4
#include <bit>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <emmintrin.h>
namespace reconstruction::gui {
template<class T> inline T read(const void *storage, std::ptrdiff_t offset=0) {
    T value; std::memcpy(&value,static_cast<const std::uint8_t*>(storage)+offset,sizeof(value)); return value;
}
template<class T> inline void write(void *storage,std::ptrdiff_t offset,T value) {
    std::memcpy(static_cast<std::uint8_t*>(storage)+offset,&value,sizeof(value));
}
inline float add(float a,float b) { return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b))); }
inline float sub(float a,float b) { return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b))); }
inline float mul(float a,float b) { return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b))); }
inline float div(float a,float b) { return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a),_mm_set_ss(b))); }
inline float minimum(float a,float b) { return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a),_mm_set_ss(b))); }
inline float maximum(float a,float b) { return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a),_mm_set_ss(b))); }
inline float fromDouble(double value) { return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(),_mm_set_sd(value))); }
inline std::int32_t truncateInt(float value) { return _mm_cvtt_ss2si(_mm_set_ss(value)); }
inline float unsignedFloat(std::uint64_t value) {
    if(!(value>>63)) return _mm_cvtss_f32(_mm_cvtsi64_ss(_mm_setzero_ps(),std::int64_t(value)));
    auto half=_mm_cvtsi64_ss(_mm_setzero_ps(),std::int64_t((value>>1)|(value&1)));
    return _mm_cvtss_f32(_mm_add_ss(half,half));
}
inline std::uint8_t *canvas(std::uint8_t *ui) { return reinterpret_cast<std::uint8_t*>(std::uintptr_t(read<std::uint64_t>(ui))); }
}
#endif // SLINKY_SHARE_EF61703C25503B328AF4
