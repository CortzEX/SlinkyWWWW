#include "module_color_settings.hpp"

#include <cstring>

extern "C" __declspec(dllexport) void recovered_color_settings(
    SettingsContext *context, const char *key, ColorSetting *setting,
    const ColorSettingsDependencies *dependencies) {
    if (context->error) return;

    static constexpr const char *channels[] = {"r", "g", "b"};
    switch (context->action) {
    case 0: {
        void *node = dependencies->lookup(context->root, key);
        float values[3];
        if (dependencies->is_object(node)) {
            for (int i = 0; i < 3; ++i) {
                values[i] = static_cast<float>(dependencies->read_number(
                    dependencies->lookup(node, channels[i])));
                if (!(values[i] >= 0.0f && values[i] <= 1.0f)) {
                    std::memcpy(setting->current, setting->saved, sizeof(setting->current));
                    return;
                }
            }
            std::memcpy(setting->current, values, sizeof(values));
        } else {
            std::memcpy(setting->current, setting->saved, sizeof(setting->current));
        }
        break;
    }
    case 1: {
        void *object = dependencies->create_object(context->root);
        if (!object) {
            context->error = 1;
            break;
        }
        for (int i = 0; i < 3; ++i) {
            context->error |= dependencies->write_number(
                object, channels[i], static_cast<double>(setting->current[i])) == nullptr;
        }
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
