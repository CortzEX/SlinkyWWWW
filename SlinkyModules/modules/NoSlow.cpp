// No Slow

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/No_Slow.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_No_Slow.cpp
#include "../runtime/native/verified/module_surface.hpp"

// No Slow: lib_win settings 0x42b20.
// UI 0x42ac0.
static constexpr UiStep ui_steps_Surface_No_Slow[] = {
    {UiControl::section, "Retained speed", 0},
    {UiControl::number, nullptr, 0x2f2ed8},
    {UiControl::number, nullptr, 0x2f2ea0},
    {UiControl::number, nullptr, 0x2f2f10},
};
static constexpr SettingsStep settings_steps_Surface_No_Slow[] = {
    {SettingsControl::number, "mult_sword", 0x2f2ed8},
    {SettingsControl::number, "mult_bow", 0x2f2ea0},
    {SettingsControl::number, "mult_consumables", 0x2f2f10},
};
static constexpr ModuleSurface surface_Surface_No_Slow{
    ui_steps_Surface_No_Slow, std::size(ui_steps_Surface_No_Slow), settings_steps_Surface_No_Slow,
    std::size(settings_steps_Surface_No_Slow)};

extern "C" __declspec(dllexport) void
recovered_no_slow_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                     const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_No_Slow, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_no_slow_settings(SettingsContext *context, std::uint8_t *image,
                           const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_No_Slow, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_No_Slow.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/No_Slow/No_Slow.cpp
#include "../runtime/native/verified/event_callbacks.hpp"
#include <cstring>

// lib_win RVA 0x42a20: event 21 callback. Game access remains an injected dependency.
extern "C" __declspec(dllexport) void recovered_no_slow(std::uint8_t *event,
                                                        const float multipliers[3], double divisor,
                                                        const Dependencies *deps) {
    std::uintptr_t frame;
    std::memcpy(&frame, event + 8, sizeof(frame));
    auto *fields = reinterpret_cast<const std::uint8_t *>(frame);

    std::uintptr_t game, target;
    std::memcpy(&game, fields, sizeof(game));
    std::memcpy(&target, fields + 0x28, sizeof(target));
    if (!deps->dep_180023f90(game, target))
        return;

    std::memcpy(&game, fields, sizeof(game));
    std::memcpy(&target, fields + 0x28, sizeof(target));
    const auto item = deps->dep_180028a50(game, target);
    if (!item)
        return;

    std::memcpy(&game, fields, sizeof(game));
    const auto type = deps->dep_180025c50(game, item);
    const auto bucket = static_cast<std::uint32_t>(type) - 0x105u;
    float multiplier;
    if (bucket < 0x17u && ((0x4088c0u >> (bucket & 31u)) & 1u)) {
        multiplier = multipliers[0];
    } else if (bucket == 0) {
        multiplier = multipliers[1];
    } else {
        multiplier = multipliers[2];
    }

    const double ratio = static_cast<double>(multiplier) / divisor;
    float sideways, forward;
    std::memcpy(&sideways, event + 0x10, sizeof(sideways));
    std::memcpy(&forward, event + 0x14, sizeof(forward));
    sideways = static_cast<float>(ratio * static_cast<double>(sideways));
    forward = static_cast<float>(ratio * static_cast<double>(forward));
    std::memcpy(event + 0x10, &sideways, sizeof(sideways));
    std::memcpy(event + 0x14, &forward, sizeof(forward));
}
// END SOURCE modules/No_Slow/No_Slow.cpp

// BEGIN SOURCE modules/No_Slow/No_Slow_typed.cpp
#ifndef SLINKY_SHARE_E4EA706BF4697715CEF5
#define SLINKY_SHARE_E4EA706BF4697715CEF5
// BEGIN SOURCE native/verified/No_Slow_typed.hpp
#include "../runtime/native/verified/Timer.hpp"
#include "../runtime/native/verified/module_ui_controls.hpp"

struct NoSlowSettings {
    NumberSetting bow;
    NumberSetting sword;
    NumberSetting consumables;
};
struct NoSlowEvent {
    std::uintptr_t type;
    TimerGame *game;
    float sideways, forward;
    std::uint8_t remaining[8];
};
struct NoSlowDependencies {
    std::uint8_t (*using_item)(GameAccessBridge *, std::uintptr_t player);
    std::uintptr_t (*held_item)(GameAccessBridge *, std::uintptr_t player);
    std::int32_t (*item_type)(GameAccessBridge *, std::uintptr_t item);
};
static_assert(sizeof(NoSlowSettings) == 168);
static_assert(offsetof(NoSlowSettings, sword) == 56);
static_assert(offsetof(NoSlowSettings, consumables) == 112);
static_assert(sizeof(NoSlowEvent) == 32);
static_assert(offsetof(NoSlowEvent, sideways) == 16);
static_assert(sizeof(NoSlowDependencies) == 24);

extern "C" {
__declspec(dllexport) void recovered_bind_no_slow_access(NoSlowDependencies *);
__declspec(dllexport) void recovered_no_slow_initialize_settings(NoSlowSettings *);
__declspec(dllexport) void recovered_no_slow_typed_update(NoSlowEvent *, const NoSlowSettings *,
                                                          const double *slowdown_divisor,
                                                          const NoSlowDependencies *);
__declspec(dllexport) std::uint64_t recovered_no_slow_typed_ui(std::uint64_t ui,
                                                               std::uint64_t layout,
                                                               NoSlowSettings *, UiDirtyState *,
                                                               const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_no_slow_typed_settings(SettingsContext *, NoSlowSettings *,
                                                            const ValueSettingsDependencies *);
}

class NoSlowModule {
  public:
    static constexpr const char *name = "No Slow";
    static constexpr std::uint32_t event_type = 21;
    static constexpr std::int32_t event_priority = 200;
    NoSlowSettings settings{};
    // Captured baseline, not a recovered startup constructor.
    double slowdown_divisor = 0.2;
    NoSlowDependencies access{};
    NoSlowModule() {
        recovered_no_slow_initialize_settings(&settings);
        recovered_bind_no_slow_access(&access);
    }
    void update(NoSlowEvent &event) {
        recovered_no_slow_typed_update(&event, &settings, &slowdown_divisor, &access);
    }
    std::uint64_t render(std::uint64_t ui, std::uint64_t layout, UiDirtyState &dirty,
                         const SettingsUiEndpoints &endpoints) {
        return recovered_no_slow_typed_ui(ui, layout, &settings, &dirty, &endpoints);
    }
    void configure(SettingsContext &context, const ValueSettingsDependencies &endpoints) {
        recovered_no_slow_typed_settings(&context, &settings, &endpoints);
    }
};
// END SOURCE native/verified/No_Slow_typed.hpp

#endif // SLINKY_SHARE_E4EA706BF4697715CEF5

#include <cstring>
#include <emmintrin.h>

extern "C" __declspec(dllexport) void recovered_bind_no_slow_access(NoSlowDependencies *access) {
    *access = {recovered_game_using_item, recovered_game_item_object,
               recovered_game_item_numeric_id};
}

// 0x42a20 captures the game, reloading its bridge/player between item queries.
extern "C" __declspec(dllexport) void
recovered_no_slow_typed_update(NoSlowEvent *event, const NoSlowSettings *settings,
                               const double *slowdown_divisor, const NoSlowDependencies *access) {
    auto *game = event->game;
    if (!access->using_item(game->bridge, game->player))
        return;
    const auto item = access->held_item(game->bridge, game->player);
    if (!item)
        return;
    const auto bucket = static_cast<std::uint32_t>(access->item_type(game->bridge, item)) - 0x105u;
    const auto &setting = bucket < 23 && ((0x4088c0u >> (bucket & 31u)) & 1u) ? settings->sword
                          : bucket == 0 ? settings->bow
                                        : settings->consumables;
    const auto ratio =
        _mm_div_sd(_mm_set_sd(static_cast<double>(setting.current)), _mm_set_sd(*slowdown_divisor));
    std::uint64_t input;
    std::memcpy(&input, &event->sideways, sizeof(input));
    const auto movement =
        _mm_cvtps_pd(_mm_castsi128_ps(_mm_cvtsi64_si128(static_cast<std::int64_t>(input))));
    const auto scaled = _mm_cvtpd_ps(_mm_mul_pd(_mm_unpacklo_pd(ratio, ratio), movement));
    const auto output = static_cast<std::uint64_t>(_mm_cvtsi128_si64(_mm_castps_si128(scaled)));
    std::memcpy(&event->sideways, &output, sizeof(output));
}

// 0x42ac0 retains the sword/bow/consumables order and final full wrapper return.
extern "C" __declspec(dllexport) std::uint64_t
recovered_no_slow_typed_ui(std::uint64_t ui, std::uint64_t layout, NoSlowSettings *settings,
                           UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Retained speed");
    recovered_number_control(layout, ui, &settings->sword, dirty, &endpoints->controls);
    recovered_number_control(layout, ui, &settings->bow, dirty, &endpoints->controls);
    return recovered_number_control(layout, ui, &settings->consumables, dirty,
                                    &endpoints->controls);
}

// 0x42b20 uses the same order for all three persistence keys.
extern "C" __declspec(dllexport) void
recovered_no_slow_typed_settings(SettingsContext *context, NoSlowSettings *settings,
                                 const ValueSettingsDependencies *endpoints) {
    recovered_number_settings(context, "mult_sword", &settings->sword, endpoints);
    recovered_number_settings(context, "mult_bow", &settings->bow, endpoints);
    recovered_number_settings(context, "mult_consumables", &settings->consumables, endpoints);
}

extern "C" __declspec(dllexport) void
recovered_no_slow_initialize_settings(NoSlowSettings *settings) {
    *settings = {};
    auto initialize = [](NumberSetting &setting, const char *label) {
        const char *format = "%.0f%%";
        const float percentage = 100.0f;
        std::memcpy(setting.metadata + 16, &label, sizeof(label));
        std::memcpy(setting.metadata + 24, &format, sizeof(format));
        std::memcpy(setting.metadata + 36, &percentage, sizeof(percentage));
        setting.minimum = 0.2f;
        setting.maximum = 1.0f;
        setting.current = 1.0f;
    };
    initialize(settings->bow, "Bow");
    initialize(settings->sword, "Sword");
    initialize(settings->consumables, "Consumables");
}
// END SOURCE modules/No_Slow/No_Slow_typed.cpp

#ifndef SLINKY_SHARE_E597F02233E4938CE536
#define SLINKY_SHARE_E597F02233E4938CE536
// BEGIN SOURCE modules/No_Slow/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/No_Slow/Api.hpp

#endif // SLINKY_SHARE_E597F02233E4938CE536

// Convenient borrowed-state interface

namespace shareable {
using NoSlow = ::NoSlowModule;
}
