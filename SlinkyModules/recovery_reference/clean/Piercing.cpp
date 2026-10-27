#include "event_callbacks.hpp"

// lib_win RVA 0x44c90: event 8 callback.
extern "C" __declspec(dllexport) void recovered_piercing(std::uint8_t *event) {
    event[0x10] = 1;
}
