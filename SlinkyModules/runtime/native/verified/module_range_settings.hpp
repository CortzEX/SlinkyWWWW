#ifndef SLINKY_SHARE_072097065DC558BF2044
#define SLINKY_SHARE_072097065DC558BF2044
#include "module_color_settings.hpp"

struct RangeSetting {
    std::uint8_t metadata[56];
    float minimum;
    float maximum;
    float current[2];
    float saved[2];
};

static_assert(sizeof(RangeSetting) == 80);
static_assert(offsetof(RangeSetting, current) == 0x40);
static_assert(offsetof(RangeSetting, saved) == 0x48);

extern "C" __declspec(dllexport) void recovered_range_settings(
    SettingsContext *context, const char *key, RangeSetting *setting,
    const ColorSettingsDependencies *dependencies);
#endif // SLINKY_SHARE_072097065DC558BF2044
