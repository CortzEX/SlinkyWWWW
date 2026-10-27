#pragma once
#include "Fast_Place.hpp"

extern "C" __declspec(dllexport) void recovered_fast_place_initialize_settings(FastPlaceSettings *);

class FastPlaceModule {
public:
    static constexpr const char *name = "Fast Place";
    static constexpr const char *description = "Allows placing blocks faster.";
    static constexpr std::uint32_t event_type = 0;
    static constexpr std::int32_t event_priority = -1000;
    FastPlaceSettings settings{};
    FastPlaceState state{};
    // Captured constants and baseline state, not a recovered startup routine.
    FastPlaceConstants constants{-1.0f, {}, 20.0, 1.0, 0.02f, 0.08f};
    FastPlaceDependencies access;

    explicit FastPlaceModule(const FastPlaceDependencies &dependencies) : access(dependencies) {
        recovered_fast_place_initialize_settings(&settings);
    }
    void update(TimerEvent &event) {
        recovered_fast_place_typed_update(&event, &settings, &state, &constants, &access);
    }
    std::uint64_t render(std::uint64_t ui, std::uint64_t layout, UiDirtyState &dirty,
                         const SettingsUiEndpoints &endpoints) {
        return recovered_fast_place_typed_ui(ui, layout, &settings, &dirty, &endpoints);
    }
    void configure(SettingsContext &context, const ValueSettingsDependencies &endpoints) {
        recovered_fast_place_typed_settings(&context, &settings, &endpoints);
    }
    std::uint64_t status(char (&destination)[32], FormatState &format) const {
        return recovered_fast_place_label(destination, &settings, &format);
    }
};
