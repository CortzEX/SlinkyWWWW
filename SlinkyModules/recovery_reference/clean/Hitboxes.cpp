#include "event_callbacks.hpp"
#include <cstring>

// lib_win RVA 0x33fc0: event 8 callback. expand is the module's stored setting.
extern "C" __declspec(dllexport) void recovered_hitboxes(std::uint8_t *event, float expand) {
    const double value = static_cast<double>(expand);
    event[0x10] = 1;
    std::memcpy(event + 0x20, &value, sizeof(value));
}
