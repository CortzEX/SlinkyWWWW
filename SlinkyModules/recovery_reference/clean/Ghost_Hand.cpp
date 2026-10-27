#include "event_callbacks.hpp"
#include "module_settings.hpp"
#include <initializer_list>

// lib_win RVA 0x46e30: event 8 callback.
extern "C" __declspec(dllexport) void recovered_ghost_hand(std::uint8_t *event) {
    event[0x10] = 1;
}

// lib_win RVA 0x46f70. The records start at 0x2f4ac0 in the supplied image.
extern "C" __declspec(dllexport) void recovered_ghost_hand_settings(
    SettingsContext *context, BooleanSetting *settings,
    const SettingsDependencies *dependencies) {
    struct Binding { const char *key; unsigned index; };
    static constexpr Binding bindings[] = {
        {"non_players", 8}, {"friendlies", 10}, {"bots", 9}, {"enemies", 11},
        {"allow_using_sword", 2}, {"allow_using_tools", 3},
        {"allow_using_fists", 1}, {"allow_using_buckets", 4},
        {"allow_using_fns", 5}, {"allow_using_cobweb", 6},
        {"allow_using_other", 7}, {"require_mouse_pressed", 0},
    };
    for (const auto &binding : bindings)
        recovered_boolean_settings(context, binding.key, settings + binding.index, dependencies);
}

struct GhostHandUiDependencies {
    void (*section)(std::uint64_t ui, std::uint64_t layout, const char *label);
    void (*checkbox)(std::uint64_t layout, std::uint64_t ui, BooleanSetting *setting);
};

// lib_win RVA 0x46e40. The final checkbox is a native tail call.
extern "C" __declspec(dllexport) void recovered_ghost_hand_ui(
    std::uint64_t ui, std::uint64_t layout, BooleanSetting *settings,
    const GhostHandUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Interact through");
    for (unsigned index : {8u, 10u, 9u, 11u})
        dependencies->checkbox(layout, ui, settings + index);
    dependencies->section(ui, layout, "Allow while using");
    for (unsigned index : {2u, 3u, 1u, 4u, 5u, 6u, 7u})
        dependencies->checkbox(layout, ui, settings + index);
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, settings);
}
