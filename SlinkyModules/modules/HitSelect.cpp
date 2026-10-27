// Hit Select

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Hit_Select.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Hit_Select.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Hit Select: lib_win settings 0x37cf0.
static constexpr SettingsStep settings_steps_Surface_Hit_Select[] = {
    {SettingsControl::choice, "mode", 0x2ee870},
    {SettingsControl::number, "cancel_rate", 0x2ee7e0},
    {SettingsControl::number, "cancel_rate_air", 0x2ee700},
    {SettingsControl::number, "pause_dur", 0x2ee738},
    {SettingsControl::number, "wait_for_damage_dur", 0x2ee770},
    {SettingsControl::number, "trades_delay", 0x2ee7a8},
    {SettingsControl::boolean, "use_server_time", 0x2ee8b0},
    {SettingsControl::boolean, "fake_swing", 0x2ee910},
    {SettingsControl::boolean, "crits_allow_reduce", 0x2ee8d0},
    {SettingsControl::boolean, "require_damage", 0x2ee8f0},
    {SettingsControl::boolean, "require_sprint", 0x2ee818},
    {SettingsControl::boolean, "require_weapon", 0x2ee838},
};
static constexpr ModuleSurface surface_Surface_Hit_Select{
    nullptr, 0, settings_steps_Surface_Hit_Select, std::size(settings_steps_Surface_Hit_Select)};

extern "C" __declspec(dllexport) void
recovered_hit_select_settings(SettingsContext *context, std::uint8_t *image,
                              const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Hit_Select, context, image, *dependencies);
}

// Hit Select: lib_win runtime UI 0x37bb0.
extern "C" __declspec(dllexport) void
recovered_hit_select_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                        const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, image + 0x2ee870);
    dependencies->number(layout, ui, image + 0x2ee738);
    if (read_surface_value<std::uint32_t>(image, 0x2ee8a0) == 0) {
        dependencies->number(layout, ui, image + 0x2ee770);
        dependencies->number(layout, ui, image + 0x2ee7a8);
    }
    dependencies->checkbox(layout, ui, image + 0x2ee8b0);
    dependencies->checkbox(layout, ui, image + 0x2ee910);
    if (read_surface_value<std::uint32_t>(image, 0x2ee8a0) == 1) {
        dependencies->checkbox(layout, ui, image + 0x2ee8d0);
        dependencies->checkbox(layout, ui, image + 0x2ee8f0);
    }
    dependencies->section(ui, layout, "Cancel rate");
    dependencies->number(layout, ui, image + 0x2ee7e0);
    dependencies->number(layout, ui, image + 0x2ee700);
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2ee818);
    dependencies->checkbox(layout, ui, image + 0x2ee838);
}
// END SOURCE native/verified/surfaces/Surface_Hit_Select.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Hit_Select/hit_select.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_50C5F13F6BA9E103F21D
#define SLINKY_SHARE_50C5F13F6BA9E103F21D
// BEGIN SOURCE modules/Hit_Select/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Hit_Select {
namespace Storage {
inline constexpr std::uint32_t moduleDescriptor = 0x2ee4f0;
inline constexpr std::uint32_t cancel_rate_airRecord = 0x2ee700;
inline constexpr std::uint32_t cancel_rate_airCurrent = 0x2ee730;
inline constexpr std::uint32_t pause_durRecord = 0x2ee738;
inline constexpr std::uint32_t pause_durCurrent = 0x2ee768;
inline constexpr std::uint32_t wait_for_damage_durRecord = 0x2ee770;
inline constexpr std::uint32_t wait_for_damage_durCurrent = 0x2ee7a0;
inline constexpr std::uint32_t trades_delayRecord = 0x2ee7a8;
inline constexpr std::uint32_t trades_delayCurrent = 0x2ee7d8;
inline constexpr std::uint32_t cancel_rateRecord = 0x2ee7e0;
inline constexpr std::uint32_t cancel_rateCurrent = 0x2ee810;
inline constexpr std::uint32_t require_sprintRecord = 0x2ee818;
inline constexpr std::uint32_t require_sprintCurrent = 0x2ee830;
inline constexpr std::uint32_t require_weaponRecord = 0x2ee838;
inline constexpr std::uint32_t require_weaponCurrent = 0x2ee850;
inline constexpr std::uint32_t modeRecord = 0x2ee870;
inline constexpr std::uint32_t modeCurrent = 0x2ee8a0;
inline constexpr std::uint32_t use_server_timeRecord = 0x2ee8b0;
inline constexpr std::uint32_t use_server_timeCurrent = 0x2ee8c8;
inline constexpr std::uint32_t crits_allow_reduceRecord = 0x2ee8d0;
inline constexpr std::uint32_t crits_allow_reduceCurrent = 0x2ee8e8;
inline constexpr std::uint32_t require_damageRecord = 0x2ee8f0;
inline constexpr std::uint32_t require_damageCurrent = 0x2ee908;
inline constexpr std::uint32_t fake_swingRecord = 0x2ee910;
inline constexpr std::uint32_t fake_swingCurrent = 0x2ee928;
inline constexpr std::uint32_t attackDecisionReady = 0x2fc538;
inline constexpr std::uint32_t unhurtTicks = 0x2fc53c;
inline constexpr std::uint32_t cancelAttackDecision = 0x2fc540;
inline constexpr std::uint32_t targetHistoryTicks = 0x2fc544;
inline constexpr std::uint32_t consecutiveTargetChecks = 0x2fc548;
inline constexpr std::uint32_t newHurtWindow = 0x2fc54c;
inline constexpr std::uint32_t previousTargetIdentifier = 0x2fc550;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    ChoiceSetting &mode() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::modeRecord);
    }
    NumberSetting &cancel_rate() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::cancel_rateRecord);
    }
    NumberSetting &cancel_rate_air() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::cancel_rate_airRecord);
    }
    NumberSetting &pause_dur() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::pause_durRecord);
    }
    NumberSetting &wait_for_damage_dur() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::wait_for_damage_durRecord);
    }
    NumberSetting &trades_delay() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::trades_delayRecord);
    }
    BooleanSetting &use_server_time() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::use_server_timeRecord);
    }
    BooleanSetting &fake_swing() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::fake_swingRecord);
    }
    BooleanSetting &crits_allow_reduce() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::crits_allow_reduceRecord);
    }
    BooleanSetting &require_damage() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_damageRecord);
    }
    BooleanSetting &require_sprint() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_sprintRecord);
    }
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_weaponRecord);
    }
};
// Runtime-observed native labels for config key "mode". Numeric values preserved.
enum class ModeMode : std::uint32_t {
    Burst = 0,
    Criticals = 1,
};
} // namespace reconstruction::Hit_Select
// END SOURCE modules/Hit_Select/Settings.hpp

#endif // SLINKY_SHARE_50C5F13F6BA9E103F21D

#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
namespace reconstruction::Hit_Select {

using dependency = native_binding::WordEndpoints;
// Native entry 0x95c0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t adjustVectorForEnvironment(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                           uint64_t a3, uint64_t a4) {
    return api(0x95c0, a0, a1, a2, a3, a4);
}
// Native entry 0xa460; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t probabilityGate(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                                uint64_t a4) {
    return api(0xa460, a0, a1, a2, a3, a4);
}
// Native entry 0x22e10; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t currentHitResult(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                                 uint64_t a4) {
    return api(0x22e10, a0, a1, a2, a3, a4);
}
// Native entry 0x23020; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_23020(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4) {
    return api(0x23020, a0, a1, a2, a3, a4);
}
// Native entry 0x23030; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityPosition(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                               uint64_t a4) {
    return api(0x23030, a0, a1, a2, a3, a4);
}
// Native entry 0x23550; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityVelocity(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                               uint64_t a4) {
    return api(0x23550, a0, a1, a2, a3, a4);
}
// Native entry 0x23690; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entitySprinting(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                                uint64_t a4) {
    return api(0x23690, a0, a1, a2, a3, a4);
}
// Native entry 0x23720; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityIdentifier(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                                 uint64_t a4) {
    return api(0x23720, a0, a1, a2, a3, a4);
}
// Native entry 0x23760; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityTicksExisted(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                   uint64_t a3, uint64_t a4) {
    return api(0x23760, a0, a1, a2, a3, a4);
}
// Native entry 0x23780; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityOnGround(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                               uint64_t a4) {
    return api(0x23780, a0, a1, a2, a3, a4);
}
// Native entry 0x237e0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_237e0(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4) {
    return api(0x237e0, a0, a1, a2, a3, a4);
}
// Native entry 0x239d0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t lastAttackerTime(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                                 uint64_t a4) {
    return api(0x239d0, a0, a1, a2, a3, a4);
}
// Native entry 0x239f0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityHurtTime(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                               uint64_t a4) {
    return api(0x239f0, a0, a1, a2, a3, a4);
}
// Native entry 0x23bb0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_23bb0(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4) {
    return api(0x23bb0, a0, a1, a2, a3, a4);
}
// Native entry 0x23f90; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityUsingItem(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                                uint64_t a4) {
    return api(0x23f90, a0, a1, a2, a3, a4);
}
// Native entry 0x24280; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_24280(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4) {
    return api(0x24280, a0, a1, a2, a3, a4);
}
// Native entry 0x24690; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_24690(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4) {
    return api(0x24690, a0, a1, a2, a3, a4);
}
// Native entry 0x24b50; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t hitResultType(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                              uint64_t a4) {
    return api(0x24b50, a0, a1, a2, a3, a4);
}
// Native entry 0x24e30; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t hitEntity(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                          uint64_t a4) {
    return api(0x24e30, a0, a1, a2, a3, a4);
}
// Native entry 0x380b0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t weaponEligibility(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                  uint64_t a3, uint64_t a4) {
    return api(0x380b0, a0, a1, a2, a3, a4);
}
// Native entry 0xb29b0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t floorBinary64(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                              uint64_t a4) {
    return api(0xb29b0, a0, a1, a2, a3, a4);
}

static uint64_t u64(const void *p) {
    return *(const volatile uint64_t *)p;
}
static uint32_t u32(const void *p) {
    return *(const volatile uint32_t *)p;
}
static float f32(const void *p) {
    uint32_t b = u32(p);
    float v;
    memcpy(&v, &b, 4);
    return v;
}
static uint32_t floatBits(float v) {
    uint32_t b;
    memcpy(&b, &v, 4);
    return b;
}
static uint64_t db(double v) {
    uint64_t b;
    memcpy(&b, &v, 8);
    return b;
}
static double fd(uint64_t b) {
    double v;
    memcpy(&v, &b, 8);
    return v;
}
static void put32(void *p, uint32_t v) {
    *(volatile uint32_t *)p = v;
}
static uint32_t rounded_count(uint8_t *image, uint32_t setting, dependency call) {
    float value = f32(image + setting);
    int64_t whole = _mm_cvttss_si64(_mm_set_ss(value));
    float fraction = value - (float)(uint64_t)(uint32_t)whole;
    return (uint32_t)whole + (uint8_t)probabilityGate(call, floatBits(fraction), 0, 0, 0, 0);
}

void onTick(uint8_t *event, uint8_t *image, dependency call) {
    image[Storage::attackDecisionReady] = 0;
    uint8_t *ctx = (uint8_t *)(uintptr_t)u64(event + 8);
    uint32_t count = 0;
    if (ctx[0x40] == 1 && (uint32_t)entityHurtTime(call, u64(ctx), u64(ctx + 0x28), 0, 0, 0) == 0)
        count = u32(image + Storage::unhurtTicks) + 1u;
    put32(image + Storage::unhurtTicks, count);
}

void filterAttackInput(uint8_t *event, uint8_t *image, dependency call) {
    if (event[0x10] != 1)
        return;
    uint8_t *ctx = (uint8_t *)(uintptr_t)u64(event + 8);
    {
        if (image[Storage::attackDecisionReady] == 1) {
            if (!image[Storage::cancelAttackDecision])
                return;
            goto cancel;
        }
        if (image[Storage::require_sprintCurrent] == 1 &&
            !(uint8_t)entitySprinting(call, u64(ctx), u64(ctx + 0x28), 0, 0, 0))
            goto allow;
        if (image[Storage::require_weaponCurrent] == 1 &&
            !(uint8_t)weaponEligibility(call, u64(ctx), u64(ctx + 0x28), 0, 0, 0))
            goto allow;
        uint64_t target = currentHitResult(call, u64(ctx), u64(ctx + 0x18), 0, 0, 0);
        uint8_t missing_target = 1;
        if (target) {
            uint32_t kind = (uint32_t)hitResultType(call, u64(ctx), target, 0, 0, 0);
            if (kind == 1)
                goto allow;
            if (kind == 0 && (uint8_t)probabilityGate(
                                 call, u32(image + Storage::cancel_rate_airCurrent), 0, 0, 0, 0))
                goto always_cancel;
            if (kind == 2)
                missing_target = hitEntity(call, u64(ctx), target, 0, 0, 0) == 0;
        }
        uint32_t threshold = rounded_count(image, Storage::pause_durCurrent, call);
        uint8_t ground = (uint8_t)entityOnGround(call, u64(ctx), u64(ctx + 0x28), 0, 0, 0);
        uint8_t rising = 1;
        if (ground) {
            double velocity[3];
            entityVelocity(call, (uintptr_t)velocity, u64(ctx), u64(ctx + 0x28), 0, 0);
            rising = velocity[1] > 0.0;
        }
        uint8_t *state = (uint8_t *)(uintptr_t)u64(ctx + 0x38);
        rising &= state[0x18];
        uint32_t mode = u32(image + Storage::modeCurrent);
        if (mode == 0) {
            if (rising)
                goto allow;
            if (u32(image + Storage::targetHistoryTicks) < 15)
                put32(image + Storage::consecutiveTargetChecks, 0);
            else if (!missing_target) {
                uint32_t count = u32(image + Storage::consecutiveTargetChecks) + 1u;
                put32(image + Storage::consecutiveTargetChecks, count);
                if (count <= rounded_count(image, Storage::wait_for_damage_durCurrent, call))
                    goto always_cancel;
            }
            if (u32(image + Storage::unhurtTicks) <= 9)
                threshold += rounded_count(image, Storage::trades_delayCurrent, call);
            if (image[Storage::newHurtWindow] == 1) {
                image[Storage::newHurtWindow] = 0;
                goto allow;
            }
        } else if (mode == 1) {
            uint8_t window =
                (uint8_t)((u32(image + Storage::targetHistoryTicks) - 9u) < 0xfffffff9u);
            window |= image[Storage::use_server_timeCurrent];
            uint8_t descending = 0;
            if (!ground) {
                uint32_t b =
                    (uint32_t)nativeBoundary_237e0(call, u64(ctx), u64(ctx + 0x28), 0, 0, 0);
                descending = f32(&b) > 0.0f;
                if (descending & window)
                    goto allow;
            }
            if (rising && (!(window & rising) || image[Storage::crits_allow_reduceCurrent] != 0))
                goto allow;
            double position[3];
            entityPosition(call, (uintptr_t)position, u64(ctx), u64(ctx + 0x28), 0, 0);
            if ((uint8_t)nativeBoundary_23020(call, u64(ctx), 0, 0, 0, 0)) {
                double copy[3], output[3];
                memcpy(copy, position, 24);
                adjustVectorForEnvironment(call, (uintptr_t)output, (uintptr_t)copy, 0, 0, 0);
                memcpy(position, output, 24);
            }
            uint32_t coords[3];
            for (unsigned i = 0; i < 3; i++)
                coords[i] = (uint32_t)_mm_cvttsd_si32(
                    _mm_set_sd(fd(floorBinary64(call, db(position[i]), 0, 0, 0, 0))));
            uint64_t block = nativeBoundary_24690(call, u64(ctx), u64(ctx + 0x20), coords[0],
                                                  coords[1], coords[2]);
            if ((uint32_t)nativeBoundary_24280(call, u64(ctx), block, 0, 0, 0) != 0)
                goto allow;
            if (!(ground | descending)) {
                if (image[Storage::require_damageCurrent] != 1 ||
                    (uint32_t)entityHurtTime(call, u64(ctx), u64(ctx + 0x28), 0, 0, 0) != 0)
                    goto always_cancel;
            }
        } else
            goto allow;
        if (threshold <= u32(image + Storage::targetHistoryTicks) + 1u)
            goto allow;
        image[Storage::cancelAttackDecision] =
            (uint8_t)probabilityGate(call, u32(image + Storage::cancel_rateCurrent), 0, 0, 0, 0);
        image[Storage::attackDecisionReady] = 1;
        if (!image[Storage::cancelAttackDecision])
            return;
        goto cancel;
    }
always_cancel:
    image[Storage::cancelAttackDecision] = 1;
    image[Storage::attackDecisionReady] = 1;
cancel:
    event[0x11] = 1;
    if (image[Storage::fake_swingCurrent] == 1) {
        uint64_t entity = u64(ctx + 0x28);
        if (entity && !(uint8_t)entityUsingItem(call, u64(ctx), entity, 0, 0, 0))
            nativeBoundary_23bb0(call, u64(ctx), u64(ctx + 0x28), 0, 0, 0);
    }
    return;
allow:
    image[Storage::cancelAttackDecision] = 0;
    image[Storage::attackDecisionReady] = 1;
}

void updateTargetHistory(uint8_t *event, uint8_t *image, dependency call) {
    uint8_t *ctx = (uint8_t *)(uintptr_t)u64(event + 8);
    uint8_t *state = (uint8_t *)(uintptr_t)u64(ctx + 0x38);
    uint64_t target = u64(state + 8);
    if (image[Storage::use_server_timeCurrent] == 1) {
        if (target && (uint32_t)entityHurtTime(call, u64(ctx), target, 0, 0, 0) == 10) {
            put32(image + Storage::targetHistoryTicks, 0);
            image[Storage::newHurtWindow] = 1;
        } else
            put32(image + Storage::targetHistoryTicks,
                  u32(image + Storage::targetHistoryTicks) + 1u);
        return;
    }
    uint32_t id = target ? (uint32_t)entityIdentifier(call, u64(ctx), target, 0, 0, 0) : 0;
    if (id == u32(image + Storage::previousTargetIdentifier)) {
        uint32_t count = u32(image + Storage::targetHistoryTicks) + 1u;
        put32(image + Storage::targetHistoryTicks, count);
        if (count < 10)
            return;
    } else {
        put32(image + Storage::previousTargetIdentifier, id);
        put32(image + Storage::targetHistoryTicks, 1001);
    }
    uint32_t current = (uint32_t)entityTicksExisted(call, u64(ctx), u64(ctx + 0x28), 0, 0, 0);
    uint32_t previous = (uint32_t)lastAttackerTime(call, u64(ctx), u64(ctx + 0x28), 0, 0, 0);
    if (current == previous)
        put32(image + Storage::targetHistoryTicks, 0);
}

// RVA 0x37e10: status uses the exact configured mode index and label table.
void formatStatus(char *output, uint8_t *image, dependency call) {
    uint32_t mode = u32(image + Storage::modeCurrent);
    call(0xab710, uintptr_t(output), 32, uintptr_t(image + 0x1528f0),
         u64(image + 0x2ee860 + uint64_t(mode) * 8), 0);
}
} // namespace reconstruction::Hit_Select
// END SOURCE modules/Hit_Select/hit_select.cpp

// Convenient borrowed-state interface

namespace shareable {
class HitSelect {
  public:
    static constexpr const char *kName = "Hit Select";
    static constexpr const char *kDescription = "Perfectly times your hits.";
    explicit HitSelect(std::uint8_t *image) : image_(image) {}
    // Mode. Config key: mode.
    ChoiceSetting &mode() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2ee870);
    }
    // Option labels observed in the captured metadata.
    enum class ModeMode : std::uint32_t { Burst = 0, Criticals = 1 };
    // In combat. Config key: cancel_rate.
    NumberSetting &cancel_rate() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ee7e0);
    }
    // Missed swings. Config key: cancel_rate_air.
    NumberSetting &cancel_rate_air() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ee700);
    }
    // Pause duration. Config key: pause_dur.
    NumberSetting &pause_dur() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ee738);
    }
    // Wait for first hit. Config key: wait_for_damage_dur.
    NumberSetting &wait_for_damage_dur() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ee770);
    }
    // Hit later in trades. Config key: trades_delay.
    NumberSetting &trades_delay() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ee7a8);
    }
    // Use server attack time. Config key: use_server_time.
    BooleanSetting &use_server_time() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ee8b0);
    }
    // Fake swing. Config key: fake_swing.
    BooleanSetting &fake_swing() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ee910);
    }
    // Disable during knockback. Config key: crits_allow_reduce.
    BooleanSetting &crits_allow_reduce() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ee8d0);
    }
    // Only while damaged. Config key: require_damage.
    BooleanSetting &require_damage() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ee8f0);
    }
    // Sprinting. Config key: require_sprint.
    BooleanSetting &require_sprint() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ee818);
    }
    // Holding weapon. Config key: require_weapon.
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ee838);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_hit_select_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_hit_select_settings(&context, image_, &dependencies);
    }
    void onTick(uint8_t *event, ::reconstruction::Hit_Select::dependency call) {
        ::reconstruction::Hit_Select::onTick(event, image_, call);
    }
    void filterAttackInput(uint8_t *event, ::reconstruction::Hit_Select::dependency call) {
        ::reconstruction::Hit_Select::filterAttackInput(event, image_, call);
    }
    void updateTargetHistory(uint8_t *event, ::reconstruction::Hit_Select::dependency call) {
        ::reconstruction::Hit_Select::updateTargetHistory(event, image_, call);
    }
    void formatStatus(char *output, ::reconstruction::Hit_Select::dependency call) {
        ::reconstruction::Hit_Select::formatStatus(output, image_, call);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
