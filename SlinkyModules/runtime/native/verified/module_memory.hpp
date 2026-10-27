#ifndef SLINKY_SHARE_18E80DB166E52E2C0064
#define SLINKY_SHARE_18E80DB166E52E2C0064
#include <cstddef>

extern "C" {
__declspec(dllexport) void *recovered_memory_move(void *destination, const void *source, std::size_t count);
__declspec(dllexport) void *recovered_memory_copy(void *destination, const void *source, std::size_t count);
}
#endif // SLINKY_SHARE_18E80DB166E52E2C0064
