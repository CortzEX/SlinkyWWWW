// Fast Accel

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Fast_Accel.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Fast_Accel.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Fast Accel: lib_win settings 0x425f0.
// UI 0x42580.
static constexpr UiStep ui_steps_Surface_Fast_Accel[] = {
    {UiControl::section, "Main", 0},          {UiControl::number, nullptr, 0x2f2a08},
    {UiControl::section, "Conditions", 0},    {UiControl::checkbox, nullptr, 0x2f2a60},
    {UiControl::checkbox, nullptr, 0x2f2a40},
};
static constexpr SettingsStep settings_steps_Surface_Fast_Accel[] = {
    {SettingsControl::number, "acceleration", 0x2f2a08},
    {SettingsControl::boolean, "require_not_damaged", 0x2f2a60},
    {SettingsControl::boolean, "require_weapon", 0x2f2a40},
};
static constexpr ModuleSurface surface_Surface_Fast_Accel{
    ui_steps_Surface_Fast_Accel, std::size(ui_steps_Surface_Fast_Accel),
    settings_steps_Surface_Fast_Accel, std::size(settings_steps_Surface_Fast_Accel)};

extern "C" __declspec(dllexport) void
recovered_fast_accel_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                        const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Fast_Accel, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_fast_accel_settings(SettingsContext *context, std::uint8_t *image,
                              const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Fast_Accel, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Fast_Accel.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Fast_Accel/Fast_Accel.cpp
#ifndef SLINKY_SHARE_0CC862CEABDCA75FA1A6
#define SLINKY_SHARE_0CC862CEABDCA75FA1A6
// BEGIN SOURCE native/verified/Fast_Accel.hpp
#include "../runtime/native/verified/Keep_Sprint.hpp"
#include "../runtime/native/verified/Weapons.hpp"
#include "../runtime/native/verified/module_float_distance.hpp"
#include "../runtime/native/verified/module_ui_controls.hpp"

struct FastAccelEvent {
    std::uintptr_t event_type;
    TimerGame *game;
    float sideways, forward, factor;
    std::uint8_t jump, padding[3];
};
struct FastAccelSettings {
    NumberSetting acceleration;
    BooleanSetting require_weapon, require_not_damaged;
};
struct FastAccelConstants {
    float minimum;
    std::uint32_t padding;
    double decay, jump_increment;
};
struct FastAccelDependencies {
    std::uint32_t (*damage)(GameAccessBridge *, std::uintptr_t);
    void (*velocity)(TimerVelocity *, GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*on_ground)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*sprinting)(GameAccessBridge *, std::uintptr_t);
    void (*set_velocity)(GameAccessBridge *, std::uintptr_t, const TimerVelocity *);
    WeaponCache *weapon_cache;
    const WeaponSettings *weapon_settings;
    const ItemPolicyTable *weapon_policy;
    const WeaponDependencies *weapon_access;
    const FloatDistanceConstants *distance_constants;
    const std::uint8_t *encoded_numeric_target;
};
static_assert(sizeof(FastAccelEvent) == 32);
static_assert(offsetof(FastAccelEvent, sideways) == 16);
static_assert(offsetof(FastAccelEvent, jump) == 28);
static_assert(sizeof(FastAccelSettings) == 120);
static_assert(offsetof(FastAccelSettings, require_weapon) == 56);
static_assert(sizeof(FastAccelConstants) == 24);
static_assert(sizeof(FastAccelDependencies) == 88);

extern "C" {
// Binds five existing motion helpers, retaining the six caller-supplied data pointers.
__declspec(dllexport) void recovered_bind_fast_accel_access(FastAccelDependencies *);
__declspec(dllexport) void recovered_fast_accel_update(FastAccelEvent *, const FastAccelSettings *,
                                                       const FastAccelConstants *,
                                                       const FastAccelDependencies *);
__declspec(dllexport) std::uint64_t
recovered_fast_accel_typed_ui(std::uint64_t ui, std::uint64_t layout, FastAccelSettings *,
                              UiDirtyState *, const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_fast_accel_typed_settings(SettingsContext *,
                                                               FastAccelSettings *,
                                                               const SettingsDependencies *,
                                                               const ValueSettingsDependencies *);
}
// END SOURCE native/verified/Fast_Accel.hpp

#endif // SLINKY_SHARE_0CC862CEABDCA75FA1A6

#include "../runtime/shared/DecodedNumericService.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>

extern "C" __declspec(dllexport) void
recovered_bind_fast_accel_access(FastAccelDependencies *dependencies) {
    TimerDependencies timer;
    recovered_bind_timer_access(&timer);
    dependencies->damage = timer.damage;
    dependencies->velocity = timer.velocity;
    dependencies->on_ground = timer.on_ground;
    dependencies->sprinting = recovered_game_sprinting;
    dependencies->set_velocity = recovered_keep_sprint_set_velocity;
}
// 0x13cfd0 reads an unaligned encoded cell immediately before the external numeric call.
static double numeric_pair(const std::uint8_t *cell, double first, double second) {
    return reconstruction::numeric_service::pairCell_13cfd0(cell, first, second);
}
// 0x42320 snapshots the game pointer and reloads its bridge/player at each helper boundary.
extern "C" __declspec(dllexport) void
recovered_fast_accel_update(FastAccelEvent *event, const FastAccelSettings *settings,
                            const FastAccelConstants *constants,
                            const FastAccelDependencies *dependencies) {
    if (event->forward == 0.0f && event->sideways == 0.0f)
        return;
    auto *game = event->game;
    if (settings->require_weapon.current == 1 &&
        !recovered_weapon_cached_query(game->bridge, game->player, dependencies->weapon_cache,
                                       dependencies->weapon_settings, dependencies->weapon_policy,
                                       dependencies->weapon_access))
        return;
    if (settings->require_not_damaged.current == 1 &&
        std::bit_cast<std::int32_t>(dependencies->damage(game->bridge, game->player)) > 0)
        return;
    TimerVelocity motion;
    dependencies->velocity(&motion, game->bridge, game->player);
    const auto speed = numeric_pair(dependencies->encoded_numeric_target, motion.x, motion.z);
    if (speed == 0.0 || !dependencies->on_ground(game->bridge, game->player))
        return;
    const auto side = event->sideways, forward = event->forward, factor = event->factor;
    const auto distance = [&](float first, float second) {
        return std::bit_cast<float>(recovered_float_distance(std::bit_cast<std::uint32_t>(first),
                                                             std::bit_cast<std::uint32_t>(second),
                                                             dependencies->distance_constants));
    };
    const auto length = distance(side, forward);
    const auto denominator = _mm_max_ss(_mm_set_ss(constants->minimum), _mm_set_ss(length));
    const auto scale = _mm_div_ss(_mm_set_ss(factor), denominator);
    const auto x = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(side), scale));
    const auto z = _mm_cvtss_f32(_mm_mul_ss(scale, _mm_set_ss(forward)));
    const auto step = _mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(distance(x, z)));
    auto limit = _mm_add_sd(_mm_setzero_pd(), step);
    const auto decay = _mm_set_sd(constants->decay);
    for (int index = 0; index < 19; ++index)
        limit = _mm_add_sd(_mm_mul_sd(limit, decay), step);
    if (event->jump == 1 && dependencies->sprinting(game->bridge, game->player))
        limit = _mm_add_sd(limit, _mm_set_sd(constants->jump_increment));
    if (speed > _mm_cvtsd_f64(limit))
        return;
    const auto original = _mm_set_sd(speed);
    const auto amount = _mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(settings->acceleration.current));
    const auto accelerated = _mm_add_sd(original, _mm_mul_sd(_mm_sub_sd(limit, original), amount));
    motion.x = _mm_cvtsd_f64(_mm_mul_sd(_mm_div_sd(_mm_set_sd(motion.x), original), accelerated));
    motion.z = _mm_cvtsd_f64(_mm_mul_sd(_mm_div_sd(_mm_set_sd(motion.z), original), accelerated));
    const TimerVelocity copy = motion;
    dependencies->set_velocity(game->bridge, game->player, &copy);
}

// 0x42580 / 0x425f0 retain the original order and shared helper behavior.
extern "C" __declspec(dllexport) std::uint64_t
recovered_fast_accel_typed_ui(std::uint64_t ui, std::uint64_t layout, FastAccelSettings *settings,
                              UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Main");
    recovered_number_control(layout, ui, &settings->acceleration, dirty, &endpoints->controls);
    endpoints->section(ui, layout, "Conditions");
    recovered_checkbox_control(layout, ui, &settings->require_not_damaged, dirty,
                               &endpoints->controls);
    return recovered_checkbox_control(layout, ui, &settings->require_weapon, dirty,
                                      &endpoints->controls);
}
extern "C" __declspec(dllexport) void
recovered_fast_accel_typed_settings(SettingsContext *context, FastAccelSettings *settings,
                                    const SettingsDependencies *booleans,
                                    const ValueSettingsDependencies *numbers) {
    recovered_number_settings(context, "acceleration", &settings->acceleration, numbers);
    recovered_boolean_settings(context, "require_not_damaged", &settings->require_not_damaged,
                               booleans);
    recovered_boolean_settings(context, "require_weapon", &settings->require_weapon, booleans);
}
// END SOURCE modules/Fast_Accel/Fast_Accel.cpp

#ifndef SLINKY_SHARE_B32487D67EA7DACA9B26
#define SLINKY_SHARE_B32487D67EA7DACA9B26
// BEGIN SOURCE modules/Fast_Accel/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Fast_Accel/Api.hpp

#endif // SLINKY_SHARE_B32487D67EA7DACA9B26

// Convenient borrowed-state interface

namespace shareable {
class FastAccel {
  public:
    static constexpr const char *kName = "Fast Accel";
    static constexpr const char *kDescription = "Speeds up acceleration.";
    explicit FastAccel(std::uint8_t *image) : image_(image) {}
    // Boost. Config key: acceleration.
    NumberSetting &acceleration() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f2a08);
    }
    // Not damaged. Config key: require_not_damaged.
    BooleanSetting &require_not_damaged() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f2a60);
    }
    // Holding weapon. Config key: require_weapon.
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f2a40);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_fast_accel_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_fast_accel_settings(&context, image_, &dependencies);
    }
    static void bindAccess(FastAccelDependencies *dependencies) {
        ::recovered_bind_fast_accel_access(dependencies);
    }
    static void update(FastAccelEvent *event, const FastAccelSettings *settings,
                       const FastAccelConstants *constants,
                       const FastAccelDependencies *dependencies) {
        ::recovered_fast_accel_update(event, settings, constants, dependencies);
    }
    static std::uint64_t typedUi(std::uint64_t ui, std::uint64_t layout,
                                 FastAccelSettings *settings, UiDirtyState *dirty,
                                 const SettingsUiEndpoints *endpoints) {
        return ::recovered_fast_accel_typed_ui(ui, layout, settings, dirty, endpoints);
    }
    static void typedSettings(SettingsContext *context, FastAccelSettings *settings,
                              const SettingsDependencies *booleans,
                              const ValueSettingsDependencies *numbers) {
        ::recovered_fast_accel_typed_settings(context, settings, booleans, numbers);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
