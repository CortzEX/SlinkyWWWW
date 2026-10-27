#pragma once

#include "Timer.hpp"
#include "Keep_Sprint.hpp"
#include "module_format.hpp"

extern "C" {
__declspec(dllexport) std::uint64_t recovered_timer_label(char *destination, const TimerSettings *, FormatState *);
__declspec(dllexport) std::uint64_t recovered_keep_sprint_label(char *destination, const KeepSprintSettings *, FormatState *);
}
