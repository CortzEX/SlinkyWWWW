#include "module_labels.hpp"
#include <emmintrin.h>

// 0x32af0 promotes the current float without additional arithmetic.
extern "C" __declspec(dllexport) std::uint64_t recovered_timer_label(
    char *destination, const TimerSettings *settings, FormatState *format) {
    return recovered_format(format, destination, 32, "%.2fx", static_cast<double>(settings->speed.current));
}

// 0x3a380 multiplies in single precision before promoting its percentage.
extern "C" __declspec(dllexport) std::uint64_t recovered_keep_sprint_label(
    char *destination, const KeepSprintSettings *settings, FormatState *format) {
    const auto percent = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(settings->motion_multiplier.current), _mm_set_ss(100.0f)));
    return recovered_format(format, destination, 32, "%.0f%%", static_cast<double>(percent));
}
