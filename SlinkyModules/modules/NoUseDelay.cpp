// No Use Delay

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/No_Use_Delay.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_No_Use_Delay.cpp
#include "../runtime/native/verified/module_surface.hpp"

// No Use Delay: lib_win settings 0x3ea20.
// UI 0x3e9e0.
static constexpr UiStep ui_steps_Surface_No_Use_Delay[] = {
    {UiControl::section, "Main", 0},
    {UiControl::checkbox, nullptr, 0x2f1420},
};
static constexpr SettingsStep settings_steps_Surface_No_Use_Delay[] = {
    {SettingsControl::boolean, "allow_desync", 0x2f1420},
};
static constexpr ModuleSurface surface_Surface_No_Use_Delay{
    ui_steps_Surface_No_Use_Delay, std::size(ui_steps_Surface_No_Use_Delay),
    settings_steps_Surface_No_Use_Delay, std::size(settings_steps_Surface_No_Use_Delay)};

extern "C" __declspec(dllexport) void
recovered_no_use_delay_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                          const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_No_Use_Delay, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_no_use_delay_settings(SettingsContext *context, std::uint8_t *image,
                                const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_No_Use_Delay, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_No_Use_Delay.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/No_Use_Delay/No_Use_Delay.cpp
#include "../runtime/native/verified/access_events.hpp"

// lib_win RVA 0x3e8e0: event 18 callback.
extern "C" __declspec(dllexport) void
recovered_no_use_delay_3e8e0(void *event, AccessGlobals *globals, const AccessDependencies *deps) {
    auto *payload = reinterpret_cast<std::uint64_t *>(access_word(event, 8));
    if (reinterpret_cast<std::uint8_t *>(payload)[0x40] == 0) {
        globals->countdown_3e8e0 = 0;
        return;
    }

    auto selected = access_call(deps, 0x22cf0, payload[0], payload[3]);
    selected = access_call(deps, 0x24f90, payload[0], selected);
    const auto active = static_cast<std::uint8_t>(access_call(deps, 0x25430, payload[0], selected));
    const auto item = access_call(deps, 0x23f40, payload[0], payload[5]);
    const auto item_id = static_cast<std::int32_t>(access_call(deps, 0x25a60, payload[0], item));
    if (item_id != globals->last_value_3e8e0) {
        globals->countdown_3e8e0 = 0;
        globals->last_value_3e8e0 = item_id;
        const auto object = payload[0];
        const auto arg = static_cast<std::uint32_t>(access_call(deps, 0x25490, object, selected));
        access_call(deps, 0x25460, object, selected, arg);
    }
    if (!active)
        return;

    const auto use_result =
        static_cast<std::int32_t>(access_call(deps, 0x23fc0, payload[0], payload[5]));
    if (globals->countdown_3e8e0 > 0) {
        --globals->countdown_3e8e0;
        if (globals->countdown_3e8e0 == 0 || (use_result == 0 && (globals->gate_3e8e0 & 1) != 0))
            access_call(deps, 0x25460, payload[0], selected);
        return;
    }
    globals->countdown_3e8e0 = use_result;
}
// END SOURCE modules/No_Use_Delay/No_Use_Delay.cpp

// BEGIN SOURCE modules/No_Use_Delay/No_Use_Delay_typed.cpp
#ifndef SLINKY_SHARE_C59304725AA6C0FB8E1B
#define SLINKY_SHARE_C59304725AA6C0FB8E1B
// BEGIN SOURCE native/verified/No_Use_Delay_typed.hpp
#include "../runtime/native/verified/Timer.hpp"
#include "../runtime/native/verified/module_ui_controls.hpp"

struct NoUseDelaySettings {
    BooleanSetting allow_desync;
};
struct NoUseDelayState {
    volatile std::int32_t countdown;
    volatile std::int32_t last_slot;
};
struct NoUseDelayEvent {
    std::uintptr_t type;
    TimerGame *game;
};
struct NoUseDelayDependencies {
    std::uintptr_t (*options)(GameAccessBridge *, std::uintptr_t client);
    std::uintptr_t (*use_key)(GameAccessBridge *, std::uintptr_t options);
    std::uint8_t (*use_pressed)(GameAccessBridge *, std::uintptr_t key);
    std::uintptr_t (*inventory)(GameAccessBridge *, std::uintptr_t player);
    std::int32_t (*selected_slot)(GameAccessBridge *, std::uintptr_t inventory);
    std::uint32_t (*physical_key)(GameAccessBridge *, std::uintptr_t key);
    void (*set_key)(GameAccessBridge *, std::uintptr_t key, std::uint32_t value);
    std::int32_t (*item_use_count)(GameAccessBridge *, std::uintptr_t player);
};
static_assert(sizeof(NoUseDelaySettings) == 32);
static_assert(sizeof(NoUseDelayState) == 8);
static_assert(offsetof(NoUseDelayState, last_slot) == 4);
static_assert(sizeof(NoUseDelayEvent) == 16);
static_assert(sizeof(NoUseDelayDependencies) == 64);

extern "C" {
__declspec(dllexport) void recovered_bind_no_use_delay_access(NoUseDelayDependencies *);
__declspec(dllexport) void recovered_no_use_delay_initialize_settings(NoUseDelaySettings *);
__declspec(dllexport) void recovered_no_use_delay_typed_update(NoUseDelayEvent *,
                                                               const NoUseDelaySettings *,
                                                               NoUseDelayState *,
                                                               const NoUseDelayDependencies *);
__declspec(dllexport) std::uint64_t
recovered_no_use_delay_typed_ui(std::uint64_t ui, std::uint64_t layout, NoUseDelaySettings *,
                                UiDirtyState *, const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_no_use_delay_typed_settings(SettingsContext *,
                                                                 NoUseDelaySettings *,
                                                                 const SettingsDependencies *);
}

class NoUseDelayModule {
  public:
    static constexpr const char *name = "No Use Delay";
    static constexpr const char *description = "Removes vanilla delay when consuming items.";
    static constexpr std::uint32_t event_type = 18;
    static constexpr std::int32_t event_priority = 0;
    NoUseDelaySettings settings{};
    NoUseDelayState state{};
    NoUseDelayDependencies access{};
    // Captured settings/state baseline; original startup construction remains unresolved.
    NoUseDelayModule() {
        recovered_no_use_delay_initialize_settings(&settings);
        recovered_bind_no_use_delay_access(&access);
    }
    void update(NoUseDelayEvent &event) {
        recovered_no_use_delay_typed_update(&event, &settings, &state, &access);
    }
    std::uint64_t render(std::uint64_t ui, std::uint64_t layout, UiDirtyState &dirty,
                         const SettingsUiEndpoints &endpoints) {
        return recovered_no_use_delay_typed_ui(ui, layout, &settings, &dirty, &endpoints);
    }
    void configure(SettingsContext &context, const SettingsDependencies &endpoints) {
        recovered_no_use_delay_typed_settings(&context, &settings, &endpoints);
    }
};
// END SOURCE native/verified/No_Use_Delay_typed.hpp

#endif // SLINKY_SHARE_C59304725AA6C0FB8E1B

#include "../runtime/native/verified/module_access_helpers.hpp"
#include "../runtime/native/verified/Sprint_Reset_runtime.hpp"
#include <cstring>

namespace {
std::uintptr_t options(GameAccessBridge *bridge, std::uintptr_t client) {
    return recovered_access_helper(bridge, 0x22cf0, client, 0, 0);
}
std::uintptr_t use_key(GameAccessBridge *bridge, std::uintptr_t options) {
    return recovered_access_helper(bridge, 0x24f90, options, 0, 0);
}
std::uint8_t use_pressed(GameAccessBridge *bridge, std::uintptr_t key) {
    return static_cast<std::uint8_t>(recovered_access_helper(bridge, 0x25430, key, 0, 0));
}
void set_key(GameAccessBridge *bridge, std::uintptr_t key, std::uint32_t value) {
    recovered_access_helper(bridge, 0x25460, key, value, 0);
}
std::int32_t item_use_count(GameAccessBridge *bridge, std::uintptr_t player) {
    return static_cast<std::int32_t>(recovered_access_helper(bridge, 0x23fc0, player, 0, 0));
}
} // namespace

extern "C" __declspec(dllexport) void
recovered_bind_no_use_delay_access(NoUseDelayDependencies *access) {
    *access = {options,
               use_key,
               use_pressed,
               recovered_game_inventory,
               recovered_game_inventory_index,
               recovered_sprint_reset_physical_word,
               set_key,
               item_use_count};
}

// 0x3e8e0 retains the selected key, its active byte and the bridge across physical-query/setter
// calls.
extern "C" __declspec(dllexport) void
recovered_no_use_delay_typed_update(NoUseDelayEvent *event, const NoUseDelaySettings *settings,
                                    NoUseDelayState *state, const NoUseDelayDependencies *access) {
    auto *game = event->game;
    if (!game->ready) {
        state->countdown = 0;
        return;
    }
    const auto options = access->options(game->bridge, game->client);
    const auto key = access->use_key(game->bridge, options);
    const auto active = access->use_pressed(game->bridge, key);
    const auto inventory = access->inventory(game->bridge, game->player);
    const auto selected_slot = access->selected_slot(game->bridge, inventory);
    if (selected_slot != state->last_slot) {
        state->countdown = 0;
        state->last_slot = selected_slot;
        auto *bridge = game->bridge;
        const auto physical = access->physical_key(bridge, key);
        access->set_key(bridge, key, physical);
    }
    if (!active)
        return;
    const auto use_count = access->item_use_count(game->bridge, game->player);
    auto count = state->countdown;
    if (count > 0) {
        state->countdown = --count;
        if (count == 0 ||
            (static_cast<std::uint8_t>(use_count == 0) & settings->allow_desync.current) == 1)
            access->set_key(game->bridge, key, 0);
    } else {
        state->countdown = use_count;
    }
}

extern "C" __declspec(dllexport) std::uint64_t
recovered_no_use_delay_typed_ui(std::uint64_t ui, std::uint64_t layout,
                                NoUseDelaySettings *settings, UiDirtyState *dirty,
                                const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Main");
    return recovered_checkbox_control(layout, ui, &settings->allow_desync, dirty,
                                      &endpoints->controls);
}

extern "C" __declspec(dllexport) void
recovered_no_use_delay_typed_settings(SettingsContext *context, NoUseDelaySettings *settings,
                                      const SettingsDependencies *endpoints) {
    recovered_boolean_settings(context, "allow_desync", &settings->allow_desync, endpoints);
}

extern "C" __declspec(dllexport) void
recovered_no_use_delay_initialize_settings(NoUseDelaySettings *settings) {
    *settings = {};
    const char *label = "Allow desync abuse";
    std::memcpy(settings->allow_desync.metadata + 16, &label, sizeof(label));
}
// END SOURCE modules/No_Use_Delay/No_Use_Delay_typed.cpp

#ifndef SLINKY_SHARE_B07FE6AFC309E9C5DBDA
#define SLINKY_SHARE_B07FE6AFC309E9C5DBDA
// BEGIN SOURCE modules/No_Use_Delay/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/No_Use_Delay/Api.hpp

#endif // SLINKY_SHARE_B07FE6AFC309E9C5DBDA

// Convenient borrowed-state interface

namespace shareable {
using NoUseDelay = ::NoUseDelayModule;
}
