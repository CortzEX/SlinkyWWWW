#include "Inv_Walk_module.hpp"
#include <cstring>

namespace {
constexpr const char *modes[] = {"Vanilla", "Spoof"};

template<class Value>
void metadata(std::uint8_t *bytes, std::size_t offset, Value value) {
    std::memcpy(bytes + offset, &value, sizeof(value));
}

void choice(ChoiceSetting &setting, const char *label, std::uint32_t count,
            const char *const *options) {
    metadata(setting.metadata, 24, label);
    setting.count = count;
    setting.options = options;
}
}

// The checkpoint records contain these values. Text and option pointers refer
// to this source's static storage; no captured addresses are used.
extern "C" __declspec(dllexport) void recovered_inv_walk_initialize_settings(InvWalkSettings *settings) {
    *settings = {};
    settings->stop_options[0] = "Full";
    settings->stop_options[1] = "Partial";
    settings->stop_options[2] = "No";
    choice(settings->mode, "Mode", 2, modes);
    choice(settings->stop_on_click, "Stop on interact", 3, settings->stop_options);
    choice(settings->stop_non_inventory, "Always stop", 3, settings->stop_options);
    auto &duration = settings->stop_duration;
    metadata(duration.metadata, 16, "Stop duration");
    metadata(duration.metadata, 24, "%.0f ms");
    metadata(duration.metadata, 32, 1.0f);
    metadata(duration.metadata, 36, 50.0f);
    duration.minimum = 1.0f;
    duration.maximum = 20.0f;
    duration.current = 2.0f;
}
