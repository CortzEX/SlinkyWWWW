// Knockback Displace

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Knockback_Displace.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Knockback_Displace.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Knockback Displace: lib_win settings 0x4aa20.
static constexpr SettingsStep settings_steps_Surface_Knockback_Displace[] = {
    {SettingsControl::choice, "direction", 0x2f6088},
    {SettingsControl::boolean, "use_last_strafe", 0x2f60e8},
    {SettingsControl::number, "angle", 0x2f5fa8},
    {SettingsControl::number, "cooldown", 0x2f5f70},
    {SettingsControl::boolean, "hide_rotation", 0x2f60c8},
    {SettingsControl::boolean, "require_no_kb", 0x2f5fe0},
    {SettingsControl::boolean, "require_weapon", 0x2f6000},
    {SettingsControl::boolean, "require_kb_enchant", 0x2f6020},
    {SettingsControl::boolean, "require_facing_away", 0x2f6040},
};
static constexpr ModuleSurface surface_Surface_Knockback_Displace{
    nullptr, 0, settings_steps_Surface_Knockback_Displace,
    std::size(settings_steps_Surface_Knockback_Displace)};

extern "C" __declspec(dllexport) void
recovered_knockback_displace_settings(SettingsContext *context, std::uint8_t *image,
                                      const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Knockback_Displace, context, image, *dependencies);
}

// Knockback Displace: lib_win runtime UI 0x4a930.
extern "C" __declspec(dllexport) void
recovered_knockback_displace_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                                const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, image + 0x2f6088);
    const auto mode = read_surface_value<std::uint32_t>(image, 0x2f60b8);
    if (mode == 3 || mode == 4) {
        dependencies->checkbox(layout, ui, image + 0x2f60e8);
    }
    dependencies->number(layout, ui, image + 0x2f5f70);
    dependencies->number(layout, ui, image + 0x2f5fa8);
    dependencies->checkbox(layout, ui, image + 0x2f60c8);
    dependencies->section(ui, layout, "Condition");
    dependencies->checkbox(layout, ui, image + 0x2f5fe0);
    dependencies->checkbox(layout, ui, image + 0x2f6000);
    dependencies->checkbox(layout, ui, image + 0x2f6020);
    dependencies->checkbox(layout, ui, image + 0x2f6040);
}
// END SOURCE native/verified/surfaces/Surface_Knockback_Displace.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Knockback_Displace/knockback_displace.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_F4A5AF7A30361D5F575B
#define SLINKY_SHARE_F4A5AF7A30361D5F575B
// BEGIN SOURCE modules/Knockback_Displace/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Knockback_Displace {
namespace Storage {
inline constexpr std::uint32_t nativeData_156680 = 0x156680;
inline constexpr std::uint32_t nativeData_156684 = 0x156684;
inline constexpr std::uint32_t nativeData_156688 = 0x156688;
inline constexpr std::uint32_t nativeData_156690 = 0x156690;
inline constexpr std::uint32_t nativeData_1566a0 = 0x1566a0;
inline constexpr std::uint32_t nativeData_1566b0 = 0x1566b0;
inline constexpr std::uint32_t nativeData_1566b4 = 0x1566b4;
inline constexpr std::uint32_t nativeData_2f3174 = 0x2f3174;
inline constexpr std::uint32_t moduleDescriptor = 0x2f5d60;
inline constexpr std::uint32_t cooldownRecord = 0x2f5f70;
inline constexpr std::uint32_t cooldownCurrent = 0x2f5fa0;
inline constexpr std::uint32_t angleRecord = 0x2f5fa8;
inline constexpr std::uint32_t angleCurrent = 0x2f5fd8;
inline constexpr std::uint32_t require_no_kbRecord = 0x2f5fe0;
inline constexpr std::uint32_t require_no_kbCurrent = 0x2f5ff8;
inline constexpr std::uint32_t require_weaponRecord = 0x2f6000;
inline constexpr std::uint32_t require_weaponCurrent = 0x2f6018;
inline constexpr std::uint32_t require_kb_enchantRecord = 0x2f6020;
inline constexpr std::uint32_t require_kb_enchantCurrent = 0x2f6038;
inline constexpr std::uint32_t require_facing_awayRecord = 0x2f6040;
inline constexpr std::uint32_t require_facing_awayCurrent = 0x2f6058;
inline constexpr std::uint32_t directionRecord = 0x2f6088;
inline constexpr std::uint32_t directionCurrent = 0x2f60b8;
inline constexpr std::uint32_t hide_rotationRecord = 0x2f60c8;
inline constexpr std::uint32_t hide_rotationCurrent = 0x2f60e0;
inline constexpr std::uint32_t use_last_strafeRecord = 0x2f60e8;
inline constexpr std::uint32_t use_last_strafeCurrent = 0x2f6100;
inline constexpr std::uint32_t nativeData_3043d8 = 0x3043d8;
inline constexpr std::uint32_t nativeData_3043dc = 0x3043dc;
inline constexpr std::uint32_t packetDispatchPending = 0x304af0;
inline constexpr std::uint32_t displacementActive = 0x304af1;
inline constexpr std::uint32_t displacementWasActive = 0x304af2;
inline constexpr std::uint32_t targetInputSeen = 0x304af3;
inline constexpr std::uint32_t targetInputTicks = 0x304af4;
inline constexpr std::uint32_t activationTicks = 0x304af8;
inline constexpr std::uint32_t retainedRotation = 0x304b00;
inline constexpr std::uint32_t movementDirection = 0x304b08;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    ChoiceSetting &direction() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::directionRecord);
    }
    BooleanSetting &use_last_strafe() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::use_last_strafeRecord);
    }
    NumberSetting &angle() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::angleRecord);
    }
    NumberSetting &cooldown() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::cooldownRecord);
    }
    BooleanSetting &hide_rotation() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::hide_rotationRecord);
    }
    BooleanSetting &require_no_kb() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_no_kbRecord);
    }
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_weaponRecord);
    }
    BooleanSetting &require_kb_enchant() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_kb_enchantRecord);
    }
    BooleanSetting &require_facing_away() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_facing_awayRecord);
    }
};
// Runtime-observed native labels for config key "direction". Numeric values preserved.
enum class DirectionMode : std::uint32_t {
    Left = 0,
    Right = 1,
    Random = 2,
    Strafe = 3,
    Strafe__inverted = 4,
};
} // namespace reconstruction::Knockback_Displace
// END SOURCE modules/Knockback_Displace/Settings.hpp

#endif // SLINKY_SHARE_F4A5AF7A30361D5F575B

#include <intrin.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
namespace reconstruction::Knockback_Displace {
using dependency = native_binding::WordEndpoints;
// Native entry 0x9de0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t addRotation(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                            uint64_t a4) {
    return api(0x9de0, a0, a1, a2, a3, a4);
}
// Native entry 0x9e20; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t subtractRotation(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                                 uint64_t a4) {
    return api(0x9e20, a0, a1, a2, a3, a4);
}
// Native entry 0xa050; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t randomRangeBits(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                                uint64_t a4) {
    return api(0xa050, a0, a1, a2, a3, a4);
}
// Native entry 0xa210; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t wrapYaw(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                        uint64_t a4) {
    return api(0xa210, a0, a1, a2, a3, a4);
}
// Native entry 0xa3e0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t randomRangeSample(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                  uint64_t a3, uint64_t a4) {
    return api(0xa3e0, a0, a1, a2, a3, a4);
}
// Native entry 0xa460; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t probabilityGate(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                                uint64_t a4) {
    return api(0xa460, a0, a1, a2, a3, a4);
}
// Native entry 0x22cf0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t clientOptions(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                              uint64_t a4) {
    return api(0x22cf0, a0, a1, a2, a3, a4);
}
// Native entry 0x22e10; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t currentHitResult(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                                 uint64_t a4) {
    return api(0x22e10, a0, a1, a2, a3, a4);
}
// Native entry 0x22eb0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t updateClientInput(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                  uint64_t a3, uint64_t a4) {
    return api(0x22eb0, a0, a1, a2, a3, a4);
}
// Native entry 0x23170; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityRotation(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                               uint64_t a4) {
    return api(0x23170, a0, a1, a2, a3, a4);
}
// Native entry 0x23690; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entitySprinting(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                                uint64_t a4) {
    return api(0x23690, a0, a1, a2, a3, a4);
}
// Native entry 0x23ae0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_23ae0(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4) {
    return api(0x23ae0, a0, a1, a2, a3, a4);
}
// Native entry 0x24120; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_24120(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4) {
    return api(0x24120, a0, a1, a2, a3, a4);
}
// Native entry 0x24220; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_24220(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4) {
    return api(0x24220, a0, a1, a2, a3, a4);
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
// Native entry 0x25270; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t attackKey(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                          uint64_t a4) {
    return api(0x25270, a0, a1, a2, a3, a4);
}
// Native entry 0x25380; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t pressKey(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                         uint64_t a4) {
    return api(0x25380, a0, a1, a2, a3, a4);
}
// Native entry 0x29800; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t claimRotationPriority(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                      uint64_t a3, uint64_t a4) {
    return api(0x29800, a0, a1, a2, a3, a4);
}
// Native entry 0x29820; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t publishRotationDelta(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4) {
    return api(0x29820, a0, a1, a2, a3, a4);
}
// Native entry 0x29850; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t rotationOffset(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                               uint64_t a4) {
    return api(0x29850, a0, a1, a2, a3, a4);
}
// Native entry 0x29950; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t applyRotation(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                              uint64_t a4) {
    return api(0x29950, a0, a1, a2, a3, a4);
}
// Native entry 0x29d90; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_29d90(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4) {
    return api(0x29d90, a0, a1, a2, a3, a4);
}
// Native entry 0x2ace0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityPolicyPredicate(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                      uint64_t a3, uint64_t a4) {
    return api(0x2ace0, a0, a1, a2, a3, a4);
}
// Native entry 0x37e50; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t weaponClassification(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4) {
    return api(0x37e50, a0, a1, a2, a3, a4);
}

static uint64_t u64(const void *p) {
    return *(const volatile uint64_t *)p;
}
static uint32_t u32(const void *p) {
    return *(const volatile uint32_t *)p;
}
static int32_t s32(uint32_t b) {
    int32_t v;
    memcpy(&v, &b, 4);
    return v;
}
static float f32(const void *p) {
    uint32_t b = u32(p);
    float v;
    memcpy(&v, &b, 4);
    return v;
}
static double f64(const void *p) {
    uint64_t b = u64(p);
    double v;
    memcpy(&v, &b, 8);
    return v;
}
static uint32_t floatBits(float v) {
    uint32_t b;
    memcpy(&b, &v, 4);
    return b;
}
static void put32(void *p, uint32_t v) {
    *(volatile uint32_t *)p = v;
}

uint8_t recovered_timer_range_query(uint8_t *image) {
    if (image[Storage::nativeData_2f3174] != 1)
        return 0;
    return ((s32(u32(image + Storage::nativeData_3043d8)) > 0) |
            image[Storage::nativeData_3043dc]) &
           1;
}
uint8_t targetAngleAllowsDisplacement(uint8_t *ctx, uint64_t angle, uint64_t target, uint8_t *image,
                                      dependency call) {
    uint64_t bits = nativeBoundary_24220(call, u64(ctx), target, 0, 0, 0);
    float difference = (float)f64(&bits) - f32(&angle);
    uint32_t normalized = (uint32_t)wrapYaw(call, floatBits(difference), 0, 0, 0, 0);
    normalized &= u32(image + Storage::nativeData_1566a0);
    return f32(image + Storage::nativeData_1566b0) > f32(&normalized);
}
uint32_t selectDisplacementDirection(uint8_t *image, dependency call) {
    switch (u32(image + Storage::directionCurrent)) {
    case 0:
        return 0xffffffffu;
    case 1:
        return 1;
    case 2:
        return ((uint32_t)(uint8_t)probabilityGate(call, u32(image + Storage::nativeData_1566b4), 0,
                                                   0, 0, 0) -
                1u) |
               1u;
    case 3:
        return u32(image + Storage::movementDirection);
    case 4:
        return 0u - u32(image + Storage::movementDirection);
    default:
        abort();
    }
}
void onPacketDispatch(uint8_t *event, uint8_t *image, dependency unused) {
    (void)unused;
    if (image[Storage::packetDispatchPending] & 1)
        put32(event + 0x24, 1);
}
void onMovementCorrection(uint8_t *event, uint8_t *image, dependency unused) {
    (void)unused;
    if (image[Storage::displacementActive] || image[Storage::displacementWasActive])
        event[9] = 0;
}
void onAfterInput(uint8_t *event, uint8_t *image, dependency unused) {
    (void)unused;
    if (event[0x10] == 1 && u32(image + Storage::targetInputTicks) >= 10 &&
        (image[Storage::targetInputSeen] & 1))
        put32(image + Storage::targetInputTicks, 0);
}
void onInput(uint8_t *event, uint8_t *image, dependency call) {
    volatile uint8_t *state = image;
    if (state[Storage::displacementActive] == 1) {
        event[0x11] = 1;
        return;
    }
    if (event[0x10] != 1)
        return;
    uint8_t *ctx = (uint8_t *)(uintptr_t)u64(event + 8);
    uint64_t target = currentHitResult(call, u64(ctx), u64(ctx + 0x18), 0, 0, 0);
    if (!target || (uint32_t)hitResultType(call, u64(ctx), target, 0, 0, 0) != 2)
        return;
    uint64_t entity = hitEntity(call, u64(ctx), target, 0, 0, 0);
    entity = nativeBoundary_24120(call, u64(ctx), entity, 0, 0, 0);
    if (!entity || (uint8_t)entityPolicyPredicate(call, u64(ctx), entity, 7, 0, 0))
        return;
    state[Storage::targetInputSeen] = 1;
    if (state[Storage::displacementWasActive] || u32(image + Storage::targetInputTicks) < 9)
        return;
    if (f32(image + Storage::cooldownCurrent) >
        (float)(uint64_t)u32(image + Storage::activationTicks))
        return;
    if (recovered_timer_range_query(image))
        return;
    if (state[Storage::require_no_kbCurrent] == 1) {
        uint8_t *target_state = (uint8_t *)(uintptr_t)u64(ctx + 0x38);
        if (target_state[0x18])
            return;
    }
    uint32_t weapon_flags;
    uint8_t weapon = (uint8_t)weaponClassification(call, u64(ctx), u64(ctx + 0x28),
                                                   (uintptr_t)&weapon_flags, 0, 0);
    if (state[Storage::require_weaponCurrent] == 1 && !weapon)
        return;
    if (!(weapon_flags & 2)) {
        if (state[Storage::require_kb_enchantCurrent] ||
            !(uint8_t)entitySprinting(call, u64(ctx), u64(ctx + 0x28), 0, 0, 0))
            return;
    }
    uint64_t angle = entityRotation(call, u64(ctx), u64(ctx + 0x28), 0, 0, 0);
    *(volatile uint64_t *)(image + Storage::retainedRotation) = angle;
    if (state[Storage::require_facing_awayCurrent] == 1 &&
        !targetAngleAllowsDisplacement(ctx, angle, entity, image, call))
        return;
    uint32_t direction = selectDisplacementDirection(image, call);
    if (!direction || !(uint8_t)claimRotationPriority(call, 200, 0, 0, 0, 0))
        return;
    nativeBoundary_29d90(call, (uintptr_t)ctx, 1, 0, 0, u64(image + Storage::retainedRotation));
    state[Storage::displacementActive] = 1;
    uint8_t sign =
        (uint8_t)probabilityGate(call, u32(image + Storage::nativeData_156680), 0, 0, 0, 0);
    float direction_float = (float)s32(direction);
    float strength = f32(image + Storage::angleCurrent);
    uint32_t ten = u32(image + Storage::nativeData_156684);
    uint64_t random = randomRangeBits(call, 0, ten, 0, 0, 0);
    uint32_t jitter = (uint32_t)randomRangeSample(call, random, 0, 0, 0, 0);
    strength = (strength - f32(&jitter)) * direction_float;
    random = randomRangeBits(call, ten, u32(image + Storage::nativeData_156688), 0, 0, 0);
    uint32_t vertical = (uint32_t)randomRangeSample(call, random, 0, 0, 0, 0);
    if (!sign)
        vertical ^= u32(image + Storage::nativeData_156690);
    uint64_t displacement = (uint64_t)floatBits(strength) | ((uint64_t)vertical << 32);
    publishRotationDelta(call, displacement, 0, 0, 0, 0);
    applyRotation(call, u64(ctx), u64(ctx + 0x28), 0, 0, 0);
    if (state[Storage::hide_rotationCurrent] == 1)
        _InterlockedExchange8((volatile char *)(image + Storage::packetDispatchPending), 1);
    event[0x11] = 1;
    put32(image + Storage::activationTicks, 0);
}
void updateDisplacementRotation(uint8_t *event, uint8_t *image, dependency call) {
    volatile uint8_t *state = image;
    put32(image + Storage::targetInputTicks, u32(image + Storage::targetInputTicks) + 1u);
    put32(image + Storage::activationTicks, u32(image + Storage::activationTicks) + 1u);
    state[Storage::displacementWasActive] = state[Storage::displacementActive];
    state[Storage::targetInputSeen] = 0;
    uint8_t *ctx = (uint8_t *)(uintptr_t)u64(event + 8);
    {
        if (ctx[0x40] != 1)
            goto clear;
        uint32_t movement_bits =
            (uint32_t)nativeBoundary_23ae0(call, u64(ctx), u64(ctx + 0x28), 0, 0, 0);
        float movement = f32(&movement_bits);
        uint32_t sign = (uint32_t)((movement > 0.0f) - (movement < 0.0f));
        if (state[Storage::use_last_strafeCurrent] != 1 || sign)
            put32(image + Storage::movementDirection, sign);
        if (state[Storage::displacementActive] != 1)
            goto finish;
        if (!(uint8_t)claimRotationPriority(call, 200, 0, 0, 0, 0))
            goto clear;
        uint64_t angle = entityRotation(call, u64(ctx), u64(ctx + 0x28), 0, 0, 0);
        uint64_t displacement = rotationOffset(call, 0, 0, 0, 0, 0);
        displacement = addRotation(call, angle, displacement, 0, 0, 0);
        displacement =
            subtractRotation(call, u64(image + Storage::retainedRotation), displacement, 0, 0, 0);
        publishRotationDelta(call, displacement, 0, 0, 0, 0);
        applyRotation(call, u64(ctx), u64(ctx + 0x28), 0, 0, 0);
        uint64_t inventory = clientOptions(call, u64(ctx), u64(ctx + 0x18), 0, 0, 0);
        updateClientInput(call, u64(ctx), u64(ctx + 0x18), 0, 0, 0);
        uint64_t slot = attackKey(call, u64(ctx), inventory, 0, 0, 0);
        pressKey(call, u64(ctx), slot, 0, 0, 0);
    }
clear:
    state[Storage::displacementActive] = 0;
finish:
    uint32_t packet_flag =
        state[Storage::displacementWasActive] ? u32(image + Storage::hide_rotationCurrent) : 0;
    _InterlockedExchange8((volatile char *)(image + Storage::packetDispatchPending),
                          (char)packet_flag);
}

// RVA 0x4ab00. Native disassembly retains RCX output, correcting raw prototype.
void formatStatus(char *output, uint8_t *image, dependency call) {
    double value = double(f32(image + 0x2f5fd8));
    uint64_t bits;
    memcpy(&bits, &value, 8);
    call(0xab710, uintptr_t(output), 32, uintptr_t(image + 0x1567a7), bits, 0);
}
} // namespace reconstruction::Knockback_Displace
// END SOURCE modules/Knockback_Displace/knockback_displace.cpp

// Convenient borrowed-state interface

namespace shareable {
class KnockbackDisplace {
  public:
    static constexpr const char *kName = "Knockback Displace";
    static constexpr const char *kDescription = "Allows dealing knockback at a different angle.";
    explicit KnockbackDisplace(std::uint8_t *image) : image_(image) {}
    // Direction. Config key: direction.
    ChoiceSetting &direction() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f6088);
    }
    // Option labels observed in the captured metadata.
    enum class DirectionMode : std::uint32_t {
        Left = 0,
        Right = 1,
        Random = 2,
        Strafe = 3,
        StrafeInverted = 4
    };
    // Use last strafe direction. Config key: use_last_strafe.
    BooleanSetting &use_last_strafe() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f60e8);
    }
    // Angle. Config key: angle.
    NumberSetting &angle() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f5fa8);
    }
    // Cooldown. Config key: cooldown.
    NumberSetting &cooldown() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f5f70);
    }
    // Hide rotation from players. Config key: hide_rotation.
    BooleanSetting &hide_rotation() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f60c8);
    }
    // Not taking knockback. Config key: require_no_kb.
    BooleanSetting &require_no_kb() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f5fe0);
    }
    // Holding weapon. Config key: require_weapon.
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f6000);
    }
    // Knockback enchantment. Config key: require_kb_enchant.
    BooleanSetting &require_kb_enchant() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f6020);
    }
    // Target facing away. Config key: require_facing_away.
    BooleanSetting &require_facing_away() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f6040);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_knockback_displace_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_knockback_displace_settings(&context, image_, &dependencies);
    }
    uint8_t timerRangeQuery() {
        return ::reconstruction::Knockback_Displace::recovered_timer_range_query(image_);
    }
    uint8_t targetAngleAllowsDisplacement(uint8_t *ctx, uint64_t angle, uint64_t target,
                                          ::reconstruction::Knockback_Displace::dependency call) {
        return ::reconstruction::Knockback_Displace::targetAngleAllowsDisplacement(
            ctx, angle, target, image_, call);
    }
    uint32_t selectDisplacementDirection(::reconstruction::Knockback_Displace::dependency call) {
        return ::reconstruction::Knockback_Displace::selectDisplacementDirection(image_, call);
    }
    void onPacketDispatch(uint8_t *event, ::reconstruction::Knockback_Displace::dependency unused) {
        ::reconstruction::Knockback_Displace::onPacketDispatch(event, image_, unused);
    }
    void onMovementCorrection(uint8_t *event,
                              ::reconstruction::Knockback_Displace::dependency unused) {
        ::reconstruction::Knockback_Displace::onMovementCorrection(event, image_, unused);
    }
    void onAfterInput(uint8_t *event, ::reconstruction::Knockback_Displace::dependency unused) {
        ::reconstruction::Knockback_Displace::onAfterInput(event, image_, unused);
    }
    void onInput(uint8_t *event, ::reconstruction::Knockback_Displace::dependency call) {
        ::reconstruction::Knockback_Displace::onInput(event, image_, call);
    }
    void updateDisplacementRotation(uint8_t *event,
                                    ::reconstruction::Knockback_Displace::dependency call) {
        ::reconstruction::Knockback_Displace::updateDisplacementRotation(event, image_, call);
    }
    void formatStatus(char *output, ::reconstruction::Knockback_Displace::dependency call) {
        ::reconstruction::Knockback_Displace::formatStatus(output, image_, call);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
