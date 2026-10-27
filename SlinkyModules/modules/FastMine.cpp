// Fast Mine

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Fast_Mine.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Fast_Mine.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Fast Mine: lib_win settings 0x41c80.
// UI 0x41c20.
static constexpr UiStep ui_steps_Surface_Fast_Mine[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2f1ff8},
    {UiControl::number, nullptr, 0x2f1fa0},
    {UiControl::checkbox, nullptr, 0x2f1fd8},
};
static constexpr SettingsStep settings_steps_Surface_Fast_Mine[] = {
    {SettingsControl::number, "speed", 0x2f1ff8},
    {SettingsControl::number, "break_delay", 0x2f1fa0},
    {SettingsControl::boolean, "decr_block_hit_delay", 0x2f1fd8},
};
static constexpr ModuleSurface surface_Surface_Fast_Mine{
    ui_steps_Surface_Fast_Mine, std::size(ui_steps_Surface_Fast_Mine),
    settings_steps_Surface_Fast_Mine, std::size(settings_steps_Surface_Fast_Mine)};

extern "C" __declspec(dllexport) void
recovered_fast_mine_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                       const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Fast_Mine, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_fast_mine_settings(SettingsContext *context, std::uint8_t *image,
                             const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Fast_Mine, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Fast_Mine.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Fast_Mine/Fast_Mine.cpp
#ifndef SLINKY_SHARE_FFF1BC2AC76F381F2172
#define SLINKY_SHARE_FFF1BC2AC76F381F2172
// BEGIN SOURCE native/verified/Fast_Mine.hpp
#include "../runtime/native/verified/Sprint.hpp"
#include "../runtime/native/verified/module_float_ceiling.hpp"
#include "../runtime/native/verified/module_ui_controls.hpp"
#include "../runtime/native/verified/module_format.hpp"

struct FastMineEvent {
    std::uintptr_t type;
    SprintGame *game;
};
struct FastMineSettings {
    NumberSetting break_delay;
    BooleanSetting decrement_block_hit_delay;
    NumberSetting speed;
};
struct FastMineState {
    std::int32_t last_current;
    float saved_progress;
};
struct FastMineConstants {
    float progress_unit;
    std::uint32_t padding;
    double speed_unit;
};
struct FastMineDependencies {
    std::uintptr_t (*controller)(GameAccessBridge *, std::uintptr_t);
    float (*progress)(GameAccessBridge *, std::uintptr_t);
    void (*set_progress)(GameAccessBridge *, std::uintptr_t, float);
    std::int32_t (*current)(GameAccessBridge *, std::uintptr_t);
    void (*set_current)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
};
static_assert(sizeof(FastMineEvent) == 16);
static_assert(sizeof(FastMineSettings) == 144);
static_assert(offsetof(FastMineSettings, decrement_block_hit_delay) == 56);
static_assert(offsetof(FastMineSettings, speed) == 88);
static_assert(sizeof(FastMineState) == 8);
static_assert(sizeof(FastMineConstants) == 16);
static_assert(sizeof(FastMineDependencies) == 40);

extern "C" {
__declspec(dllexport) void recovered_bind_fast_mine_access(FastMineDependencies *);
__declspec(dllexport) void recovered_fast_mine_update(FastMineEvent *, const FastMineSettings *,
                                                      FastMineState *,
                                                      const FastMineDependencies *);
__declspec(dllexport) void recovered_fast_mine_progress(FastMineEvent *, const FastMineSettings *,
                                                        const FastMineState *,
                                                        const FastMineConstants *,
                                                        const FloatCeilingConstants *,
                                                        const FastMineDependencies *);
__declspec(dllexport) std::uint64_t recovered_fast_mine_typed_ui(std::uint64_t ui,
                                                                 std::uint64_t layout,
                                                                 FastMineSettings *, UiDirtyState *,
                                                                 const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_fast_mine_typed_settings(SettingsContext *, FastMineSettings *,
                                                              const SettingsDependencies *,
                                                              const ValueSettingsDependencies *);
__declspec(dllexport) std::uint64_t recovered_fast_mine_label(char *, const FastMineSettings *,
                                                              FormatState *);
}
// END SOURCE native/verified/Fast_Mine.hpp

#endif // SLINKY_SHARE_FFF1BC2AC76F381F2172

#include "../runtime/native/verified/module_access_helpers.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>

using Word = std::uintptr_t;
static Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word value;
    std::memcpy(&value, bridge->metadata + offset, sizeof(value));
    return value;
}
template <class Function> static Function slot(const GameAccessBridge *bridge, std::size_t offset) {
    const auto *table = reinterpret_cast<const Word *>(*bridge->environment);
    return reinterpret_cast<Function>(table[offset / sizeof(Word)]);
}
static Word controller(GameAccessBridge *bridge, Word client) {
    return recovered_access_helper(bridge, 0x22df0, client, 0, 0);
}
// 0x27df0 / 0x27e10 use the float getter return and the fourth setter argument.
static float progress(GameAccessBridge *bridge, Word object) {
    using Call_Fast_Mine = float (*)(Word *, Word, Word);
    return slot<Call_Fast_Mine>(bridge, 0x330)(bridge->environment, object,
                                               identifier(bridge, 0xbc8));
}
static void set_progress(GameAccessBridge *bridge, Word object, float value) {
    using Call_Fast_Mine = void (*)(Word *, Word, Word, float);
    slot<Call_Fast_Mine>(bridge, 0x378)(bridge->environment, object, identifier(bridge, 0xbc8),
                                        value);
}
// 0x27e40 / 0x27e60 read signed current state and write the raw low DWORD.
static std::int32_t current(GameAccessBridge *bridge, Word object) {
    using Call_Fast_Mine = std::int32_t (*)(Word *, Word, Word);
    return slot<Call_Fast_Mine>(bridge, 0x320)(bridge->environment, object,
                                               identifier(bridge, 0xbd0));
}
static void set_current(GameAccessBridge *bridge, Word object, std::uint32_t value) {
    using Call_Fast_Mine = void (*)(Word *, Word, Word, std::uint32_t);
    slot<Call_Fast_Mine>(bridge, 0x368)(bridge->environment, object, identifier(bridge, 0xbd0),
                                        value);
}
extern "C" __declspec(dllexport) void
recovered_bind_fast_mine_access(FastMineDependencies *dependencies) {
    *dependencies = {controller, progress, set_progress, current, set_current};
}

// 0x41a90 stores the original counter even after clamping or decrementing it.
extern "C" __declspec(dllexport) void
recovered_fast_mine_update(FastMineEvent *event, const FastMineSettings *settings,
                           FastMineState *state, const FastMineDependencies *dependencies) {
    auto *game = event->game;
    const auto object = dependencies->controller(game->bridge, game->client);
    std::int32_t value = 0;
    if (object) {
        state->saved_progress = dependencies->progress(game->bridge, object);
        value = dependencies->current(game->bridge, object);
        const auto limit = settings->break_delay.current;
        const auto converted = _mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(), value));
        if (converted > limit) {
            dependencies->set_current(
                game->bridge, object,
                static_cast<std::uint32_t>(_mm_cvttss_si32(_mm_set_ss(limit))));
        } else if (value > 0 && settings->decrement_block_hit_delay.current &&
                   value == state->last_current) {
            dependencies->set_current(game->bridge, object, static_cast<std::uint32_t>(value) - 1u);
        }
    }
    state->last_current = value;
}

// 0x41b30 keeps scalar SSE conversions and modulo-32-bit step arithmetic.
extern "C" __declspec(dllexport) void
recovered_fast_mine_progress(FastMineEvent *event, const FastMineSettings *settings,
                             const FastMineState *state, const FastMineConstants *constants,
                             const FloatCeilingConstants *ceiling,
                             const FastMineDependencies *dependencies) {
    auto *game = event->game;
    const auto object = dependencies->controller(game->bridge, game->client);
    if (!object)
        return;
    const auto value = dependencies->progress(game->bridge, object);
    if (value == 0.0f || state->saved_progress != 0.0f)
        return;
    const auto promoted = _mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(value));
    const auto first_argument =
        _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(constants->progress_unit), _mm_set_ss(value)));
    const auto first = _mm_cvttss_si64(_mm_set_ss(std::bit_cast<float>(
        recovered_float_ceiling_bits(std::bit_cast<std::uint32_t>(first_argument), ceiling))));
    const auto speed = _mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(settings->speed.current));
    const auto quotient =
        _mm_div_sd(_mm_div_sd(_mm_set_sd(constants->speed_unit), speed), promoted);
    const auto second_argument = _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), quotient));
    const auto second = _mm_cvttss_si64(_mm_set_ss(std::bit_cast<float>(
        recovered_float_ceiling_bits(std::bit_cast<std::uint32_t>(second_argument), ceiling))));
    const auto steps = static_cast<std::uint32_t>(first) - static_cast<std::uint32_t>(second) + 1u;
    const auto factor = _mm_cvtsi64_ss(_mm_setzero_ps(), static_cast<std::int64_t>(steps));
    const auto result = _mm_cvtss_f32(_mm_mul_ss(factor, _mm_set_ss(value)));
    dependencies->set_progress(game->bridge, object, result);
}

// 0x41c20 / 0x41c80 share the recovered control and persistence helpers.
extern "C" __declspec(dllexport) std::uint64_t
recovered_fast_mine_typed_ui(std::uint64_t ui, std::uint64_t layout, FastMineSettings *settings,
                             UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Main");
    recovered_number_control(layout, ui, &settings->speed, dirty, &endpoints->controls);
    recovered_number_control(layout, ui, &settings->break_delay, dirty, &endpoints->controls);
    return recovered_checkbox_control(layout, ui, &settings->decrement_block_hit_delay, dirty,
                                      &endpoints->controls);
}
extern "C" __declspec(dllexport) void
recovered_fast_mine_typed_settings(SettingsContext *context, FastMineSettings *settings,
                                   const SettingsDependencies *booleans,
                                   const ValueSettingsDependencies *numbers) {
    recovered_number_settings(context, "speed", &settings->speed, numbers);
    recovered_number_settings(context, "break_delay", &settings->break_delay, numbers);
    recovered_boolean_settings(context, "decr_block_hit_delay",
                               &settings->decrement_block_hit_delay, booleans);
}
// 0x41ce0 promotes the configured speed before passing it to the formatter.
extern "C" __declspec(dllexport) std::uint64_t
recovered_fast_mine_label(char *destination, const FastMineSettings *settings,
                          FormatState *format) {
    return recovered_format(format, destination, 32, "%.2fx",
                            static_cast<double>(settings->speed.current));
}
// END SOURCE modules/Fast_Mine/Fast_Mine.cpp

#ifndef SLINKY_SHARE_17204DF5F2968D430BB0
#define SLINKY_SHARE_17204DF5F2968D430BB0
// BEGIN SOURCE modules/Fast_Mine/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Fast_Mine/Api.hpp

#endif // SLINKY_SHARE_17204DF5F2968D430BB0

// Convenient borrowed-state interface

namespace shareable {
class FastMine {
  public:
    static constexpr const char *kName = "Fast Mine";
    static constexpr const char *kDescription = "Increases block mining speed.";
    explicit FastMine(std::uint8_t *image) : image_(image) {}
    // Speed. Config key: speed.
    NumberSetting &speed() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f1ff8);
    }
    // Break delay. Config key: break_delay.
    NumberSetting &break_delay() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f1fa0);
    }
    // Always decrease break delay. Config key: decr_block_hit_delay.
    BooleanSetting &decr_block_hit_delay() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f1fd8);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_fast_mine_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_fast_mine_settings(&context, image_, &dependencies);
    }
    static void bindAccess(FastMineDependencies *dependencies) {
        ::recovered_bind_fast_mine_access(dependencies);
    }
    static void update(FastMineEvent *event, const FastMineSettings *settings, FastMineState *state,
                       const FastMineDependencies *dependencies) {
        ::recovered_fast_mine_update(event, settings, state, dependencies);
    }
    static void progress(FastMineEvent *event, const FastMineSettings *settings,
                         const FastMineState *state, const FastMineConstants *constants,
                         const FloatCeilingConstants *ceiling,
                         const FastMineDependencies *dependencies) {
        ::recovered_fast_mine_progress(event, settings, state, constants, ceiling, dependencies);
    }
    static std::uint64_t typedUi(std::uint64_t ui, std::uint64_t layout, FastMineSettings *settings,
                                 UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
        return ::recovered_fast_mine_typed_ui(ui, layout, settings, dirty, endpoints);
    }
    static void typedSettings(SettingsContext *context, FastMineSettings *settings,
                              const SettingsDependencies *booleans,
                              const ValueSettingsDependencies *numbers) {
        ::recovered_fast_mine_typed_settings(context, settings, booleans, numbers);
    }
    static std::uint64_t label(char *destination, const FastMineSettings *settings,
                               FormatState *format) {
        return ::recovered_fast_mine_label(destination, settings, format);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
