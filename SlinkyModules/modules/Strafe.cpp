// Strafe

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Strafe.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Strafe.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Strafe: lib_win settings 0x422a0.
// UI 0x42200.
static constexpr UiStep ui_steps_Surface_Strafe[] = {
    {UiControl::section, "Strength", 0},      {UiControl::number, nullptr, 0x2f2768},
    {UiControl::number, nullptr, 0x2f27a0},   {UiControl::number, nullptr, 0x2f2730},
    {UiControl::section, "Conditions", 0},    {UiControl::number, nullptr, 0x2f26f8},
    {UiControl::checkbox, nullptr, 0x2f27d8},
};
static constexpr SettingsStep settings_steps_Surface_Strafe[] = {
    {SettingsControl::number, "strength_jump", 0x2f2768},
    {SettingsControl::number, "strength_ground", 0x2f27a0},
    {SettingsControl::number, "strength_air", 0x2f2730},
    {SettingsControl::number, "max_hurt_time", 0x2f26f8},
    {SettingsControl::boolean, "require_weapon", 0x2f27d8},
};
static constexpr ModuleSurface surface_Surface_Strafe{
    ui_steps_Surface_Strafe, std::size(ui_steps_Surface_Strafe), settings_steps_Surface_Strafe,
    std::size(settings_steps_Surface_Strafe)};

extern "C" __declspec(dllexport) void
recovered_strafe_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Strafe, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_strafe_settings(SettingsContext *context, std::uint8_t *image,
                          const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Strafe, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Strafe.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Strafe/Strafe.cpp
#ifndef SLINKY_SHARE_DF29A02B09A7E30B1271
#define SLINKY_SHARE_DF29A02B09A7E30B1271
// BEGIN SOURCE native/verified/Strafe.hpp
#include "../runtime/native/verified/Timer.hpp"
#include "../runtime/native/verified/Keep_Sprint.hpp"
#include "../runtime/native/verified/Weapons.hpp"
#include "../runtime/native/verified/module_ui_controls.hpp"

struct StrafeEvent {
    std::uintptr_t type;
    TimerGame *game;
    float sideways, forward, reserved;
    std::uint8_t jump, padding[3];
};
struct StrafeSettings {
    NumberSetting max_hurt_time, air, jump, ground;
    BooleanSetting require_weapon;
};
struct StrafeConstants {
    double boost, negative_side, positive_side, zero_factor, half_turn;
    double backward_factor, forward_factor, angle_scale;
    std::uint32_t sign_mask, padding;
};
struct StrafeWeaponBinding {
    WeaponCache *cache;
    const WeaponSettings *settings;
    const ItemPolicyTable *policy;
    const WeaponDependencies *access;
};
struct StrafeDependencies {
    std::uint8_t (*sprinting)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*weapon)(GameAccessBridge *, std::uintptr_t, const StrafeWeaponBinding *);
    std::uint32_t (*damage)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*on_ground)(GameAccessBridge *, std::uintptr_t);
    void (*velocity)(TimerVelocity *, GameAccessBridge *, std::uintptr_t);
    std::uint64_t (*rotation)(GameAccessBridge *, std::uintptr_t);
    void (*set_velocity)(GameAccessBridge *, std::uintptr_t, const TimerVelocity *);
    double (*speed)(double, double);
    float (*sine)(float);
    float (*cosine)(float);
    const StrafeWeaponBinding *weapon_state;
};
static_assert(sizeof(StrafeEvent) == 32);
static_assert(offsetof(StrafeEvent, jump) == 28);
static_assert(sizeof(StrafeSettings) == 256);
static_assert(offsetof(StrafeSettings, require_weapon) == 224);
static_assert(sizeof(StrafeConstants) == 72);
static_assert(offsetof(StrafeConstants, sign_mask) == 64);
static_assert(sizeof(StrafeDependencies) == 88);

extern "C" {
__declspec(dllexport) void recovered_bind_strafe_access(StrafeDependencies *);
__declspec(dllexport) void recovered_strafe_typed_sample(StrafeEvent *, std::uint8_t *sampled,
                                                         const StrafeDependencies *);
__declspec(dllexport) void recovered_strafe_typed_motion(StrafeEvent *, const StrafeSettings *,
                                                         const std::uint8_t *sampled,
                                                         const StrafeConstants *,
                                                         const StrafeDependencies *);
__declspec(dllexport) double recovered_strafe_interpolate(double current, double target,
                                                          double amount);
__declspec(dllexport) std::uint64_t recovered_strafe_typed_ui(std::uint64_t ui,
                                                              std::uint64_t layout,
                                                              StrafeSettings *, UiDirtyState *,
                                                              const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_strafe_typed_settings(SettingsContext *, StrafeSettings *,
                                                           const SettingsDependencies *,
                                                           const ValueSettingsDependencies *);
}
// END SOURCE native/verified/Strafe.hpp

#endif // SLINKY_SHARE_DF29A02B09A7E30B1271

#include "../runtime/native/verified/Free_Look.hpp"
#include "../runtime/shared/StrafeNumericBindings.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>

static std::uint8_t weapon(GameAccessBridge *bridge, std::uintptr_t entity,
                           const StrafeWeaponBinding *state) {
    return recovered_weapon_cached_query(bridge, entity, state->cache, state->settings,
                                         state->policy, state->access);
}
extern "C" __declspec(dllexport) void
recovered_bind_strafe_access(StrafeDependencies *dependencies) {
    TimerDependencies timer;
    recovered_bind_timer_access(&timer);
    FreeLookDependencies rotation;
    recovered_bind_free_look_access(&rotation);
    dependencies->sprinting = recovered_game_sprinting;
    dependencies->weapon = weapon;
    dependencies->damage = timer.damage;
    dependencies->on_ground = timer.on_ground;
    dependencies->velocity = timer.velocity;
    dependencies->rotation = rotation.player_angles;
    dependencies->set_velocity = recovered_keep_sprint_set_velocity;
}
extern "C" __declspec(dllexport) double recovered_strafe_interpolate(double current, double target,
                                                                     double amount) {
    const auto a = _mm_set_sd(current);
    return _mm_cvtsd_f64(
        _mm_add_sd(a, _mm_mul_sd(_mm_sub_sd(_mm_set_sd(target), a), _mm_set_sd(amount))));
}
extern "C" __declspec(dllexport) void
recovered_strafe_typed_sample(StrafeEvent *event, std::uint8_t *sampled,
                              const StrafeDependencies *dependencies) {
    auto *game = event->game;
    *sampled = dependencies->sprinting(game->bridge, game->player);
}
static void motion(StrafeEvent *event, const StrafeSettings *settings, const std::uint8_t *sampled,
                   const StrafeConstants *constants, const StrafeDependencies *dependencies,
                   const reconstruction::numeric_service::Context *numeric) {
    if (event->forward == 0.0f && event->sideways == 0.0f)
        return;
    auto *game = event->game;
    if (settings->require_weapon.current == 1 &&
        !dependencies->weapon(game->bridge, game->player, dependencies->weapon_state))
        return;
    const auto damage =
        std::bit_cast<std::int32_t>(dependencies->damage(game->bridge, game->player));
    if (static_cast<float>(damage) > settings->max_hurt_time.current)
        return;
    std::uint8_t boost = 0;
    float amount;
    if (!dependencies->on_ground(game->bridge, game->player))
        amount = settings->air.current;
    else if (event->jump == 1) {
        boost = *sampled ^ 1;
        amount = settings->jump.current;
    } else
        amount = settings->ground.current;
    if (amount == 0.0f)
        return;
    TimerVelocity motion;
    dependencies->velocity(&motion, game->bridge, game->player);
    auto speed = numeric
                     ? reconstruction::numeric_service::pair_13cfd0(*numeric, motion.x, motion.z)
                     : dependencies->speed(motion.x, motion.z);
    if (boost)
        speed += constants->boost;
    const auto yaw_bits =
        static_cast<std::uint32_t>(dependencies->rotation(game->bridge, game->player));
    const auto sideways = event->sideways, forward = event->forward;
    auto turn = sideways < 0.0f ? constants->negative_side : 0.0;
    if (sideways > 0.0f)
        turn = constants->positive_side;
    auto heading = static_cast<double>(std::bit_cast<float>(yaw_bits));
    if (forward > 0.0f)
        turn *= constants->forward_factor;
    else if (forward < 0.0f) {
        heading += constants->half_turn;
        turn *= constants->backward_factor;
    } else
        turn *= constants->zero_factor;
    const auto radians =
        static_cast<float>(((turn + heading) * constants->angle_scale) / constants->half_turn);
    const auto old_x = motion.x;
    const auto sine = std::bit_cast<float>(
        std::bit_cast<std::uint32_t>(dependencies->sine(radians)) ^ constants->sign_mask);
    motion.x = recovered_strafe_interpolate(old_x, static_cast<double>(sine) * speed,
                                            static_cast<double>(amount));
    const auto old_z = motion.z;
    const auto cosine = dependencies->cosine(radians);
    motion.z = recovered_strafe_interpolate(old_z, static_cast<double>(cosine) * speed,
                                            static_cast<double>(amount));
    const auto copy = motion;
    dependencies->set_velocity(game->bridge, game->player, &copy);
}
extern "C" __declspec(dllexport) void
recovered_strafe_typed_motion(StrafeEvent *event, const StrafeSettings *settings,
                              const std::uint8_t *sampled, const StrafeConstants *constants,
                              const StrafeDependencies *dependencies) {
    motion(event, settings, sampled, constants, dependencies, nullptr);
}
void reconstruction::strafe::motionNumeric(StrafeEvent *event, const StrafeSettings *settings,
                                           const std::uint8_t *sampled,
                                           const StrafeConstants *constants,
                                           const StrafeDependencies *dependencies,
                                           const numeric_service::Context &numeric) {
    motion(event, settings, sampled, constants, dependencies, &numeric);
}

extern "C" __declspec(dllexport) std::uint64_t
recovered_strafe_typed_ui(std::uint64_t ui, std::uint64_t layout, StrafeSettings *settings,
                          UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Strength");
    recovered_number_control(layout, ui, &settings->jump, dirty, &endpoints->controls);
    recovered_number_control(layout, ui, &settings->ground, dirty, &endpoints->controls);
    recovered_number_control(layout, ui, &settings->air, dirty, &endpoints->controls);
    endpoints->section(ui, layout, "Conditions");
    recovered_number_control(layout, ui, &settings->max_hurt_time, dirty, &endpoints->controls);
    return recovered_checkbox_control(layout, ui, &settings->require_weapon, dirty,
                                      &endpoints->controls);
}
extern "C" __declspec(dllexport) void
recovered_strafe_typed_settings(SettingsContext *context, StrafeSettings *settings,
                                const SettingsDependencies *booleans,
                                const ValueSettingsDependencies *numbers) {
    recovered_number_settings(context, "strength_jump", &settings->jump, numbers);
    recovered_number_settings(context, "strength_ground", &settings->ground, numbers);
    recovered_number_settings(context, "strength_air", &settings->air, numbers);
    recovered_number_settings(context, "max_hurt_time", &settings->max_hurt_time, numbers);
    recovered_boolean_settings(context, "require_weapon", &settings->require_weapon, booleans);
}
// END SOURCE modules/Strafe/Strafe.cpp

#ifndef SLINKY_SHARE_101096D925EDA47D0223
#define SLINKY_SHARE_101096D925EDA47D0223
// BEGIN SOURCE modules/Strafe/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Strafe/Api.hpp

#endif // SLINKY_SHARE_101096D925EDA47D0223

// Convenient borrowed-state interface

namespace shareable {
class Strafe {
  public:
    static constexpr const char *kName = "Strafe";
    static constexpr const char *kDescription = "Allows faster strafing.";
    explicit Strafe(std::uint8_t *image) : image_(image) {}
    // Jump. Config key: strength_jump.
    NumberSetting &strength_jump() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f2768);
    }
    // Ground. Config key: strength_ground.
    NumberSetting &strength_ground() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f27a0);
    }
    // Air. Config key: strength_air.
    NumberSetting &strength_air() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f2730);
    }
    // Maximum hurt time. Config key: max_hurt_time.
    NumberSetting &max_hurt_time() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f26f8);
    }
    // Holding weapon. Config key: require_weapon.
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f27d8);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_strafe_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_strafe_settings(&context, image_, &dependencies);
    }
    static void bindAccess(StrafeDependencies *dependencies) {
        ::recovered_bind_strafe_access(dependencies);
    }
    static double interpolate(double current, double target, double amount) {
        return ::recovered_strafe_interpolate(current, target, amount);
    }
    static void typedSample(StrafeEvent *event, std::uint8_t *sampled,
                            const StrafeDependencies *dependencies) {
        ::recovered_strafe_typed_sample(event, sampled, dependencies);
    }
    static void typedMotion(StrafeEvent *event, const StrafeSettings *settings,
                            const std::uint8_t *sampled, const StrafeConstants *constants,
                            const StrafeDependencies *dependencies) {
        ::recovered_strafe_typed_motion(event, settings, sampled, constants, dependencies);
    }
    static void motionNumeric(StrafeEvent *event, const StrafeSettings *settings,
                              const std::uint8_t *sampled, const StrafeConstants *constants,
                              const StrafeDependencies *dependencies,
                              const ::reconstruction::numeric_service::Context &numeric) {
        ::reconstruction::strafe::motionNumeric(event, settings, sampled, constants, dependencies,
                                                numeric);
    }
    static std::uint64_t typedUi(std::uint64_t ui, std::uint64_t layout, StrafeSettings *settings,
                                 UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
        return ::recovered_strafe_typed_ui(ui, layout, settings, dirty, endpoints);
    }
    static void typedSettings(SettingsContext *context, StrafeSettings *settings,
                              const SettingsDependencies *booleans,
                              const ValueSettingsDependencies *numbers) {
        ::recovered_strafe_typed_settings(context, settings, booleans, numbers);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
