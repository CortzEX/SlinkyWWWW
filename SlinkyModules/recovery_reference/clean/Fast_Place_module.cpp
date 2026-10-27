#include "Fast_Place_module.hpp"
#include <cstring>

namespace {
template<class Value>
void metadata(std::uint8_t *bytes, std::size_t offset, Value value) {
    std::memcpy(bytes + offset, &value, sizeof(value));
}
}

extern "C" __declspec(dllexport) void recovered_fast_place_initialize_settings(FastPlaceSettings *settings) {
    *settings = {};
    auto &cps = settings->maximum_cps;
    metadata(cps.metadata, 16, "Maximum CPS");
    metadata(cps.metadata, 24, "%0.1f CPS");
    metadata(cps.metadata, 32, 0.1f);
    cps.minimum = 10.0f;
    cps.maximum = 50.0f;
    cps.current = 20.0f;
    auto &delay = settings->activation_delay;
    metadata(delay.metadata, 16, "Activate delay");
    metadata(delay.metadata, 24, "%0.0f ms");
    metadata(delay.metadata, 32, 1.0f);
    metadata(delay.metadata, 36, 50.0f);
    delay.maximum = 10.0f;
}
