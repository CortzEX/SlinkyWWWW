#include "module_list_settings.hpp"

#include <cstring>
#include <limits>

static void read_color(void *node, float out[3], const ListSettingsDependencies &d) {
    const float white[3] = {1.0f, 1.0f, 1.0f};
    std::memcpy(out, white, sizeof(white));
    if (!d.is_object(node)) return;
    static constexpr const char *channels[] = {"r", "g", "b"};
    float values[3];
    for (int i = 0; i < 3; ++i) {
        const auto *number = static_cast<const std::uint8_t *>(d.lookup(node, channels[i]));
        double raw = std::numeric_limits<double>::quiet_NaN();
        if (number && number[0x18] == 8) std::memcpy(&raw, number + 0x30, sizeof(raw));
        values[i] = static_cast<float>(raw);
        if (!(values[i] >= 0.0f && values[i] <= 1.0f)) return;
    }
    std::memcpy(out, values, sizeof(values));
}

extern "C" __declspec(dllexport) void recovered_list_settings(
    SettingsContext *context, const char *key, ListSetting *setting,
    const ListSettingsDependencies *dependencies) {
    if (context->error) return;
    auto &d = *dependencies;

    if (context->action == 0) {
        setting->clear(setting->state);
        auto *array = static_cast<std::uint8_t *>(d.lookup(context->root, key));
        if (!d.is_array(array) || !array) return;
        auto *entry = *reinterpret_cast<std::uint8_t **>(array + 0x10);
        while (entry) {
            if (setting->kind == 0) {
                if (d.is_string(entry)) {
                    const char *name;
                    std::memcpy(&name, entry + 0x20, sizeof(name));
                    const float zero[3] = {0.0f, 0.0f, 0.0f};
                    setting->add(setting->state, name, zero);
                }
            } else if (setting->kind == 1 && d.is_object(entry)) {
                auto *name_node = static_cast<std::uint8_t *>(d.lookup(entry, "name"));
                if (d.is_string(name_node)) {
                    const char *name;
                    std::memcpy(&name, name_node + 0x20, sizeof(name));
                    float color[3];
                    read_color(d.lookup(entry, "color"), color, d);
                    setting->add(setting->state, name, color);
                }
            }
            std::memcpy(&entry, entry, sizeof(entry));
        }
        return;
    }

    if (context->action == 3) {
        setting->clear(setting->state);
        return;
    }
    if (context->action != 1) return;

    void *array = d.create_array(context->root);
    if (!array) {
        context->error = 1;
        return;
    }
    for (std::size_t i = 0; i < setting->count(setting->state); ++i) {
        if (setting->kind == 0) {
            const char *name = setting->name(setting->state, i);
            void *value = d.create_string(name);
            context->error |= !value || !d.append(array, value);
        } else if (setting->kind == 1) {
            void *value = d.create_object();
            bool ok = value != nullptr;
            if (ok) {
                const char *name = setting->name(setting->state, i);
                ok = d.write_string(value, "name", name) != nullptr;
            }
            void *color_object = ok ? d.create_child_object(value, "color") : nullptr;
            ok = color_object != nullptr;
            if (ok) {
                const float *color = setting->color(setting->state, i);
                static constexpr const char *channels[] = {"r", "g", "b"};
                for (int j = 0; j < 3 && ok; ++j)
                    ok = d.write_number(color_object, channels[j], color[j]) != nullptr;
            }
            if (ok) ok = d.append(array, value) != 0;
            context->error |= !ok;
        }
    }
}
