#include "module_range_settings.hpp"

#include <cmath>
#include <cstring>

extern "C" __declspec(dllexport) void recovered_range_settings(
    SettingsContext *context, const char *key, RangeSetting *setting,
    const ColorSettingsDependencies *dependencies) {
    if (context->error) return;

    switch (context->action) {
    case 0: {
        void *object = dependencies->lookup(context->root, key);
        float result[2];
        std::memcpy(result, setting->saved, sizeof(result));
        const float minimum = setting->minimum;
        const float maximum = setting->maximum;
        if (dependencies->is_object(object)) {
            float low = static_cast<float>(dependencies->read_number(
                dependencies->lookup(object, "min")));
            if (!std::isnan(low)) {
                float high = static_cast<float>(dependencies->read_number(
                    dependencies->lookup(object, "max")));
                if (!std::isnan(high)) {
                    if (high < low) low = high;
                    result[0] = low;
                    if (minimum > low) result[0] = minimum;
                    else if (low > maximum) result[0] = maximum;
                    result[1] = high;
                    if (minimum > high) result[1] = minimum;
                    else if (high > maximum) result[1] = maximum;
                }
            }
        }
        std::memcpy(setting->current, result, sizeof(result));
        break;
    }
    case 1: {
        void *object = dependencies->create_object(context->root);
        if (!object) {
            context->error = 1;
            break;
        }
        context->error |= dependencies->write_number(
            object, "min", static_cast<double>(setting->current[0])) == nullptr;
        context->error |= dependencies->write_number(
            object, "max", static_cast<double>(setting->current[1])) == nullptr;
        break;
    }
    case 2:
        std::memcpy(setting->saved, setting->current, sizeof(setting->current));
        break;
    case 3:
        std::memcpy(setting->current, setting->saved, sizeof(setting->current));
        break;
    }
}
