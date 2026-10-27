#ifndef SLINKY_SHARE_B69FC78BF6A209A4E3D8
#define SLINKY_SHARE_B69FC78BF6A209A4E3D8
#include "Timer.hpp"
#include "Keep_Sprint.hpp"
#include "module_format.hpp"

extern "C" {
__declspec(dllexport) std::uint64_t recovered_timer_label(char *destination, const TimerSettings *, FormatState *);
__declspec(dllexport) std::uint64_t recovered_keep_sprint_label(char *destination, const KeepSprintSettings *, FormatState *);
}
#endif // SLINKY_SHARE_B69FC78BF6A209A4E3D8
