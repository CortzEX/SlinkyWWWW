#pragma once

#include <cstddef>

extern "C" {
__declspec(dllexport) void *recovered_memory_move(void *destination, const void *source, std::size_t count);
__declspec(dllexport) void *recovered_memory_copy(void *destination, const void *source, std::size_t count);
}
