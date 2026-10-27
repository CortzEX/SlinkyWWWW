#include "module_settings.hpp"
#include <cmath>
#include <cstring>

// lib_win RVA 0xc3b0. Actions load, save, capture, and restore a Boolean setting.
extern "C" __declspec(dllexport) void recovered_boolean_settings(
    SettingsContext *context, const char *key, BooleanSetting *setting,
    const SettingsDependencies *dependencies) {
    if (context->error) return;
    switch (context->action) {
    case 0: {
        const auto saved = setting->saved;
        const auto *node = static_cast<const std::uint8_t *>(dependencies->lookup(context->root, key));
        setting->current = node && (node[24] & 3) ? node[24] == 2 : saved;
        break;
    }
    case 1:
        context->error |= dependencies->write_boolean(context->root, key, setting->current) == nullptr;
        break;
    case 2:
        setting->saved = setting->current;
        break;
    case 3:
        setting->current = setting->saved;
        break;
    }
}

// lib_win RVA 0xc450. Numeric values are stored as floats and saved as JSON numbers.
extern "C" __declspec(dllexport) void recovered_number_settings(
    SettingsContext *context, const char *key, NumberSetting *setting,
    const ValueSettingsDependencies *dependencies) {
    if (context->error) return;
    switch (context->action) {
    case 0: {
        const auto *node = static_cast<const std::uint8_t *>(
            dependencies->lookup(context->root, key));
        float value = setting->saved;
        const float minimum = setting->minimum;
        const float maximum = setting->maximum;
        if (node && node[0x18] == 8) {
            double stored;
            std::memcpy(&stored, node + 0x30, sizeof(stored));
            const float converted = static_cast<float>(stored);
            if (!std::isnan(converted)) {
                value = minimum;
                if (!(minimum > converted)) {
                    value = converted;
                    if (maximum < converted) value = maximum;
                }
            }
        }
        setting->current = value;
        break;
    }
    case 1:
        context->error |= dependencies->write_number(
            context->root, key, static_cast<double>(setting->current)) == nullptr;
        break;
    case 2:
        setting->saved = setting->current;
        break;
    case 3:
        setting->current = setting->saved;
        break;
    }
}

// lib_win RVA 0xc6f0. Choice labels are compared in stored order.
extern "C" __declspec(dllexport) void recovered_choice_settings(
    SettingsContext *context, const char *key, ChoiceSetting *setting,
    const ValueSettingsDependencies *dependencies) {
    if (context->error) return;
    switch (context->action) {
    case 0: {
        std::uint32_t selected = setting->saved;
        const auto *node = static_cast<const std::uint8_t *>(
            dependencies->lookup(context->root, key));
        if (node && node[0x18] == 0x10) {
            const auto count = setting->count;
            if (count) {
                const auto *options = setting->options;
                const char *value;
                std::memcpy(&value, node + 0x20, sizeof(value));
                for (std::uint32_t i = 0; i < count; ++i) {
                    if (dependencies->compare_strings(options[i], value) == 0) {
                        selected = i;
                        break;
                    }
                }
            }
        }
        setting->current = selected;
        break;
    }
    case 1:
        context->error |= dependencies->write_string(
            context->root, key, setting->options[setting->current]) == nullptr;
        break;
    case 2:
        setting->saved = setting->current;
        break;
    case 3:
        setting->current = setting->saved;
        break;
    }
}
