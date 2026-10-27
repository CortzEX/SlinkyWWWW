// Velocity

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Velocity.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Velocity.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Velocity: lib_win settings 0x30a90.
static constexpr SettingsStep settings_steps_Surface_Velocity[] = {
    {SettingsControl::choice, "mode", 0x2eaa20},
    {SettingsControl::number, "reduce_chance", 0x2eab98},
    {SettingsControl::number, "fov", 0x2eac40},
    {SettingsControl::number, "reduce_amount", 0x2eac08},
    {SettingsControl::number, "reduce_delay", 0x2eabd0},
    {SettingsControl::number, "jump_chance", 0x2eac78},
    {SettingsControl::boolean, "reduce_multiple_per_tick", 0x2eab78},
    {SettingsControl::choice, "ignore_vertical", 0x2eab38},
    {SettingsControl::number, "ignore_chance", 0x2eaa60},
    {SettingsControl::boolean, "require_target", 0x2eaaf8},
    {SettingsControl::boolean, "require_mouse", 0x2eaab8},
    {SettingsControl::boolean, "require_forward", 0x2eaa98},
    {SettingsControl::boolean, "require_weapon", 0x2eaad8},
    {SettingsControl::boolean, "require_sprinting_jump", 0x2eacb0},
};
static constexpr ModuleSurface surface_Surface_Velocity{nullptr, 0, settings_steps_Surface_Velocity,
                                                        std::size(settings_steps_Surface_Velocity)};

extern "C" __declspec(dllexport) void
recovered_velocity_settings(SettingsContext *context, std::uint8_t *image,
                            const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Velocity, context, image, *dependencies);
}

// Velocity: lib_win runtime UI 0x30930.
extern "C" __declspec(dllexport) void
recovered_velocity_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                      const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, image + 0x2eaa20);
    switch (read_surface_value<std::uint32_t>(image, 0x2eaa50)) {
    case 0:
        dependencies->number(layout, ui, image + 0x2eab98);
        dependencies->number(layout, ui, image + 0x2eac40);
        dependencies->number(layout, ui, image + 0x2eac08);
        dependencies->number(layout, ui, image + 0x2eabd0);
        break;
    case 1:
        dependencies->number(layout, ui, image + 0x2eac78);
        break;
    case 2:
        dependencies->checkbox(layout, ui, image + 0x2eab78);
        break;
    case 3:
        dependencies->choice(layout, ui, image + 0x2eab38);
        dependencies->number(layout, ui, image + 0x2eaa60);
        break;
    }
    dependencies->section(ui, layout, "Conditions");
    if (read_surface_value<std::uint32_t>(image, 0x2eaa50) != 2) {
        dependencies->checkbox(layout, ui, image + 0x2eaaf8);
        dependencies->checkbox(layout, ui, image + 0x2eaab8);
    }
    dependencies->checkbox(layout, ui, image + 0x2eaa98);
    dependencies->checkbox(layout, ui, image + 0x2eaad8);
    if (read_surface_value<std::uint32_t>(image, 0x2eaa50) == 1) {
        dependencies->checkbox(layout, ui, image + 0x2eacb0);
    }
}
// END SOURCE native/verified/surfaces/Surface_Velocity.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Velocity/velocity.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_A5EC6F1D4D6341E6AA53
#define SLINKY_SHARE_A5EC6F1D4D6341E6AA53
// BEGIN SOURCE modules/Velocity/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Velocity {
namespace Storage {
inline constexpr std::uint32_t nativeData_13cfa0 = 0x13cfa0;
inline constexpr std::uint32_t nativeData_13cfd0 = 0x13cfd0;
inline constexpr std::uint32_t nativeData_150e20 = 0x150e20;
inline constexpr std::uint32_t nativeData_150e48 = 0x150e48;
inline constexpr std::uint32_t nativeData_150e50 = 0x150e50;
inline constexpr std::uint32_t nativeData_150e58 = 0x150e58;
inline constexpr std::uint32_t nativeData_150e80 = 0x150e80;
inline constexpr std::uint32_t nativeData_150e88 = 0x150e88;
inline constexpr std::uint32_t moduleDescriptor = 0x2ea7f0;
inline constexpr std::uint32_t modeRecord = 0x2eaa20;
inline constexpr std::uint32_t modeCurrent = 0x2eaa50;
inline constexpr std::uint32_t ignore_chanceRecord = 0x2eaa60;
inline constexpr std::uint32_t ignore_chanceCurrent = 0x2eaa90;
inline constexpr std::uint32_t require_forwardRecord = 0x2eaa98;
inline constexpr std::uint32_t require_forwardCurrent = 0x2eaab0;
inline constexpr std::uint32_t require_mouseRecord = 0x2eaab8;
inline constexpr std::uint32_t require_mouseCurrent = 0x2eaad0;
inline constexpr std::uint32_t require_weaponRecord = 0x2eaad8;
inline constexpr std::uint32_t require_weaponCurrent = 0x2eaaf0;
inline constexpr std::uint32_t require_targetRecord = 0x2eaaf8;
inline constexpr std::uint32_t require_targetCurrent = 0x2eab10;
inline constexpr std::uint32_t ignore_verticalRecord = 0x2eab38;
inline constexpr std::uint32_t ignore_verticalCurrent = 0x2eab68;
inline constexpr std::uint32_t reduce_multiple_per_tickRecord = 0x2eab78;
inline constexpr std::uint32_t reduce_multiple_per_tickCurrent = 0x2eab90;
inline constexpr std::uint32_t reduce_chanceRecord = 0x2eab98;
inline constexpr std::uint32_t reduce_chanceCurrent = 0x2eabc8;
inline constexpr std::uint32_t reduce_delayRecord = 0x2eabd0;
inline constexpr std::uint32_t reduce_delayCurrent = 0x2eac00;
inline constexpr std::uint32_t reduce_amountRecord = 0x2eac08;
inline constexpr std::uint32_t reduce_amountCurrent = 0x2eac38;
inline constexpr std::uint32_t fovRecord = 0x2eac40;
inline constexpr std::uint32_t fovCurrent = 0x2eac70;
inline constexpr std::uint32_t jump_chanceRecord = 0x2eac78;
inline constexpr std::uint32_t jump_chanceCurrent = 0x2eaca8;
inline constexpr std::uint32_t require_sprinting_jumpRecord = 0x2eacb0;
inline constexpr std::uint32_t require_sprinting_jumpCurrent = 0x2eacc8;
inline constexpr std::uint32_t packetResetPending = 0x2f9d88;
inline constexpr std::uint32_t storedVelocityPending = 0x2f9d89;
inline constexpr std::uint32_t storedVelocityX = 0x2f9d90;
inline constexpr std::uint32_t storedVelocityY = 0x2f9d98;
inline constexpr std::uint32_t storedVelocityZ = 0x2f9da0;
inline constexpr std::uint32_t nativeData_2f9da8 = 0x2f9da8;
inline constexpr std::uint32_t localEntityIdentifier = 0x2f9db8;
inline constexpr std::uint32_t knockbackPacketPending = 0x2f9dbc;
inline constexpr std::uint32_t inputVelocityX = 0x2f9dc0;
inline constexpr std::uint32_t inputVelocityZ = 0x2f9dd0;
inline constexpr std::uint32_t attackVelocityApplied = 0x2f9dd8;
inline constexpr std::uint32_t horizontalDelayTicks = 0x2f9ddc;
inline constexpr std::uint32_t jumpKeyOwned = 0x2f9de0;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    ChoiceSetting &mode() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::modeRecord);
    }
    NumberSetting &reduce_chance() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::reduce_chanceRecord);
    }
    NumberSetting &fov() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::fovRecord);
    }
    NumberSetting &reduce_amount() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::reduce_amountRecord);
    }
    NumberSetting &reduce_delay() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::reduce_delayRecord);
    }
    NumberSetting &jump_chance() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::jump_chanceRecord);
    }
    BooleanSetting &reduce_multiple_per_tick() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::reduce_multiple_per_tickRecord);
    }
    ChoiceSetting &ignore_vertical() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::ignore_verticalRecord);
    }
    NumberSetting &ignore_chance() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::ignore_chanceRecord);
    }
    BooleanSetting &require_target() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_targetRecord);
    }
    BooleanSetting &require_mouse() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_mouseRecord);
    }
    BooleanSetting &require_forward() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_forwardRecord);
    }
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_weaponRecord);
    }
    BooleanSetting &require_sprinting_jump() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_sprinting_jumpRecord);
    }
};
// Runtime-observed native labels for config key "mode". Numeric values preserved.
enum class ModeMode : std::uint32_t {
    Regular = 0,
    Jump = 1,
    Reduce = 2,
    Ignore = 3,
};
// Runtime-observed native labels for config key "ignore_vertical". Numeric values preserved.
enum class Ignore_verticalMode : std::uint32_t {
    Never = 0,
    Only_in_air = 1,
    Always = 2,
};
} // namespace reconstruction::Velocity
// END SOURCE modules/Velocity/Settings.hpp

#endif // SLINKY_SHARE_A5EC6F1D4D6341E6AA53

#include <emmintrin.h>
#include <intrin.h>
#include <stdint.h>
#include <string.h>
namespace reconstruction::Velocity {
using dependency = native_binding::WordEndpoints;
// Native entry 0xa050; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t randomRangeBits(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                uint64_t a3) {
    return api(0xa050, a0, a1, a2, a3);
}
// Native entry 0xaa30; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t smoothedProbabilityGate(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                        uint64_t a3) {
    return api(0xaa30, a0, a1, a2, a3);
}
// Native entry 0x22cf0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t clientOptions(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x22cf0, a0, a1, a2, a3);
}
// Native entry 0x23170; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityRotation(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x23170, a0, a1, a2, a3);
}
// Native entry 0x23550; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityVelocity(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x23550, a0, a1, a2, a3);
}
// Native entry 0x235f0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t setEntityVelocity(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                  uint64_t a3) {
    return api(0x235f0, a0, a1, a2, a3);
}
// Native entry 0x23690; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entitySprinting(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                uint64_t a3) {
    return api(0x23690, a0, a1, a2, a3);
}
// Native entry 0x23720; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityIdentifier(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                 uint64_t a3) {
    return api(0x23720, a0, a1, a2, a3);
}
// Native entry 0x23760; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityTicksExisted(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                   uint64_t a3) {
    return api(0x23760, a0, a1, a2, a3);
}
// Native entry 0x23780; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityOnGround(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x23780, a0, a1, a2, a3);
}
// Native entry 0x239d0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t lastAttackerTime(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                 uint64_t a3) {
    return api(0x239d0, a0, a1, a2, a3);
}
// Native entry 0x23ac0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_23ac0(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x23ac0, a0, a1, a2, a3);
}
// Native entry 0x23c10; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityEffect(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x23c10, a0, a1, a2, a3);
}
// Native entry 0x25080; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t jumpKey(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x25080, a0, a1, a2, a3);
}
// Native entry 0x25430; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t keyDown(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x25430, a0, a1, a2, a3);
}
// Native entry 0x25460; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t setKeyDownRaw(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x25460, a0, a1, a2, a3);
}
// Native entry 0x25490; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t physicalKeyWord(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                uint64_t a3) {
    return api(0x25490, a0, a1, a2, a3);
}
// Native entry 0x266b0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_266b0(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x266b0, a0, a1, a2, a3);
}
// Native entry 0x266f0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_266f0(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x266f0, a0, a1, a2, a3);
}
// Native entry 0x26b10; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_26b10(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x26b10, a0, a1, a2, a3);
}
// Native entry 0x26b50; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_26b50(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x26b50, a0, a1, a2, a3);
}
// Native entry 0x26b90; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_26b90(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x26b90, a0, a1, a2, a3);
}
// Native entry 0x26c30; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_26c30(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x26c30, a0, a1, a2, a3);
}
// Native entry 0x27960; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t effectByIndex(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x27960, a0, a1, a2, a3);
}
// Native entry 0x380b0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t weaponEligibility(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                  uint64_t a3) {
    return api(0x380b0, a0, a1, a2, a3);
}
// Native entry 0xb1cf0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_b1cf0(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0xb1cf0, a0, a1, a2, a3);
}
// Native entry 0xb3590; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_b3590(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0xb3590, a0, a1, a2, a3);
}

static uint64_t loadWord64(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t loadWord32(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static int32_t s(uint32_t v) {
    int32_t n;
    memcpy(&n, &v, 4);
    return n;
}
static float loadFloat(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static double loadDouble(const void *p) {
    double v;
    memcpy(&v, p, 8);
    return v;
}
static void storeWord32(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
static void storeDouble(void *p, double v) {
    memcpy(p, &v, 8);
}
static uint32_t floatBits(float v) {
    return loadWord32(&v);
}
static uint64_t doubleBits(double v) {
    return loadWord64(&v);
}
static float floatFromWord(uint64_t v) {
    uint32_t n = (uint32_t)v;
    return loadFloat(&n);
}
static double doubleFromWord(uint64_t v) {
    return loadDouble(&v);
}
static double add(double a, double b) {
    return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double mul(double a, double b) {
    return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double divd(double a, double b) {
    return _mm_cvtsd_f64(_mm_div_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static float roundf32(double a) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(a)));
}
static uint8_t chance(float value, uint32_t constants, uint8_t *image, dependency call) {
    if (value > loadFloat(image + constants))
        return 1;
    double fraction = (double)roundf32(mul((double)value, loadDouble(image + constants + 8)));
    float lower = roundf32(add(loadDouble(image + constants + 16), fraction));
    float upper = roundf32(add(fraction, loadDouble(image + constants + 24)));
    uint64_t random = randomRangeBits(call, floatBits(lower), floatBits(upper), 0, 0);
    return (uint8_t)smoothedProbabilityGate(call, (uintptr_t)(image + Storage::nativeData_2f9da8),
                                            random, loadWord64(image + constants + 32), 0);
}
static void velocity_get(double *v, uint8_t *ctx, dependency call) {
    entityVelocity(call, (uintptr_t)v, loadWord64(ctx), loadWord64(ctx + 0x28), 0);
}
static void velocity_set(const double *v, uint8_t *ctx, dependency call) {
    double copy[3];
    memcpy(copy, v, 24);
    setEntityVelocity(call, loadWord64(ctx), loadWord64(ctx + 0x28), (uintptr_t)copy, 0);
}

// RVA 0x30c50. Known callers consume AL. Native higher result bits depend on
// incoming RDI on the fast path and the search index on a matching path.
static bool velocityEligible(uint8_t *ctx, uint8_t *image, dependency call) {
    if (image[Storage::require_forwardCurrent] == 1) {
        float forward = floatFromWord(
            nativeBoundary_23ac0(call, loadWord64(ctx), loadWord64(ctx + 0x28), 0, 0));
        if (0.0f >= forward)
            return false; // UCOMISS/JAE accepts unordered input.
    }
    if (image[Storage::require_mouseCurrent] == 1 &&
        !uint8_t(call(0x29080, uintptr_t(ctx), 0, 0, 0)))
        return false;
    if (image[Storage::require_weaponCurrent] == 1 &&
        !uint8_t(weaponEligibility(call, loadWord64(ctx), loadWord64(ctx + 0x28), 0, 0)))
        return false;
    if (image[Storage::require_targetCurrent] != 1)
        return true;
    double origin[3];
    call(0x23030, uintptr_t(origin), loadWord64(ctx), loadWord64(ctx + 0x28), 0);
    float yaw = floatFromWord(entityRotation(call, loadWord64(ctx), loadWord64(ctx + 0x28), 0, 0));
    uint64_t players = call(0x24600, loadWord64(ctx), loadWord64(ctx + 0x20), 0, 0);
    int32_t count = s(uint32_t(call(0x24e50, loadWord64(ctx), players, 0, 0)));
    if (count < 1)
        return false;
    double distanceLimit = loadDouble(image + 0x150eb0);
    uint32_t absoluteMask = loadWord32(image + 0x150ec0);
    float angleLimit = loadFloat(image + 0x150ed0);
    uint32_t index = 0;
    do {
        uint64_t candidate = call(0x24e80, loadWord64(ctx), players, index, 0);
        uint64_t game = loadWord64(ctx);
        uint64_t environment = loadWord64(reinterpret_cast<void *>(game + 8));
        if (!uint8_t(call(0x800000c0, environment, loadWord64(ctx + 0x28), candidate, 0))) {
            double from[3], position[3], a[3], b[3];
            memcpy(from, origin, 24);
            call(0x23030, uintptr_t(position), loadWord64(ctx), candidate, 0);
            memcpy(a, from, 24);
            memcpy(b, position, 24);
            double distance = doubleFromWord(call(0x94b0, uintptr_t(a), uintptr_t(b), 0, 0));
            if (!(distance > distanceLimit)) {
                memcpy(a, from, 24);
                memcpy(b, position, 24);
                float targetYaw = floatFromWord(call(0x9f80, uintptr_t(a), uintptr_t(b), 0, 0));
                float difference =
                    _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(targetYaw), _mm_set_ss(yaw)));
                uint32_t bits =
                    uint32_t(call(0xa210, floatBits(difference), 0, 0, 0)) & absoluteMask;
                if (!(loadFloat(&bits) > angleLimit))
                    return true; // JA also accepts NaNs.
            }
        }
        ++index;
        count = s(uint32_t(call(0x24e50, loadWord64(ctx), players, 0, 0)));
    } while (s(index) < count);
    return false;
}
// RVA 0x30be0. Formatting itself remains native printf-compatible ABI 0xab710.
void formatStatus(char *output, uint8_t *image, dependency call) {
    uint32_t mode = loadWord32(image + Storage::modeCurrent);
    if (mode == 0) {
        float value =
            _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(loadFloat(image + Storage::reduce_amountCurrent)),
                                     _mm_set_ss(loadFloat(image + 0x150ea0))));
        call(0xab710, uintptr_t(output), 32, uintptr_t(image + 0x150f6c),
             doubleBits(double(value)));
    } else
        call(0xab710, uintptr_t(output), 32, uintptr_t(image + 0x1510c5),
             loadWord64(image + 0x2eaa00 + uint64_t(mode) * 8));
}

void applyStoredVelocity(uint8_t *event, uint8_t *image, dependency call) {
    if (loadWord32(image + Storage::modeCurrent) != 3)
        return;
    uint8_t *ctx = (uint8_t *)(uintptr_t)loadWord64(event + 8);
    if (ctx[0x40] != 1)
        return;
    if (image[Storage::packetResetPending] & 1) {
        _InterlockedExchange8((volatile char *)(image + Storage::packetResetPending), 0);
        return;
    }
    if (image[Storage::storedVelocityPending] != 1)
        return;
    if (!(uint8_t)velocityEligible(ctx, image, call))
        return;
    if (!chance(loadFloat(image + Storage::ignore_chanceCurrent), Storage::nativeData_150e20, image,
                call))
        return;
    double v[3];
    velocity_get(v, ctx, call);
    v[0] = loadDouble(image + Storage::storedVelocityX);
    uint32_t mode = loadWord32(image + Storage::ignore_verticalCurrent);
    if (mode == 2 || (mode == 1 && !(uint8_t)entityOnGround(call, loadWord64(ctx),
                                                            loadWord64(ctx + 0x28), 0, 0)))
        v[1] = loadDouble(image + Storage::storedVelocityY);
    v[2] = loadDouble(image + Storage::storedVelocityZ);
    velocity_set(v, ctx, call);
    image[Storage::storedVelocityPending] = 0;
}
void onPacket(uint8_t *event, uint8_t *image, dependency call) {
    if (loadWord32(event + 0x24) != 0)
        return;
    uint64_t packet =
        nativeBoundary_266b0(call, loadWord64(event + 8), loadWord64(event + 0x10), 0, 0);
    if (packet) {
        uint32_t id = (uint32_t)nativeBoundary_266f0(call, loadWord64(event + 8), packet, 0, 0);
        if (id == loadWord32(image + Storage::localEntityIdentifier))
            _InterlockedExchange8((volatile char *)(image + Storage::knockbackPacketPending), 1);
        return;
    }
    packet = nativeBoundary_26b50(call, loadWord64(event + 8), loadWord64(event + 0x10), 0, 0);
    if (packet) {
        float x = floatFromWord(nativeBoundary_26b90(call, loadWord64(event + 8), packet, 0, 0));
        float z = floatFromWord(nativeBoundary_26c30(call, loadWord64(event + 8), packet, 0, 0));
        __m128 xx = _mm_mul_ss(_mm_set_ss(x), _mm_set_ss(x));
        __m128 zz = _mm_mul_ss(_mm_set_ss(z), _mm_set_ss(z));
        float squared = _mm_cvtss_f32(_mm_add_ss(xx, zz));
        _InterlockedExchange8(
            (volatile char *)(image + Storage::knockbackPacketPending),
            (char)((double)squared > loadDouble(image + Storage::nativeData_150e48)));
        return;
    }
    if (nativeBoundary_26b10(call, loadWord64(event + 8), loadWord64(event + 0x10), 0, 0))
        _InterlockedExchange8((volatile char *)(image + Storage::packetResetPending), 1);
}
void onModuleStateChanged(uint8_t *event, uint8_t *image, dependency call) {
    (void)call;
    if (loadWord64(event + 0x10) == (uintptr_t)(image + Storage::moduleDescriptor))
        image[Storage::storedVelocityPending] = 0;
}
void captureInputVelocity(uint8_t *event, uint8_t *image, dependency call) {
    if (event[0x10] != 1)
        return;
    uint8_t *ctx = (uint8_t *)(uintptr_t)loadWord64(event + 8);
    if (!loadWord64(ctx + 0x28))
        return;
    double v[3];
    velocity_get(v, ctx, call);
    memcpy(image + Storage::inputVelocityZ, v + 2, 8);
    memcpy(image + Storage::inputVelocityX, v, 16);
}
void applyAttackVelocity(uint8_t *event, uint8_t *image, dependency call) {
    if (loadWord32(image + Storage::modeCurrent) != 2)
        return;
    if (image[Storage::attackVelocityApplied] == 1 &&
        image[Storage::reduce_multiple_per_tickCurrent] == 0)
        return;
    if (event[0x10] != 1)
        return;
    uint8_t *ctx = (uint8_t *)(uintptr_t)loadWord64(event + 8);
    uint64_t player = loadWord64(ctx + 0x28);
    if (!player)
        return;
    uint8_t *target = (uint8_t *)(uintptr_t)loadWord64(ctx + 0x38);
    if (target[0x18] != 1)
        return;
    if (image[Storage::require_forwardCurrent] == 1) {
        float vertical = floatFromWord(nativeBoundary_23ac0(call, loadWord64(ctx), player, 0, 0));
        if (0.0f >= vertical)
            return;
        player = loadWord64(ctx + 0x28);
    }
    if (image[Storage::require_weaponCurrent] == 1) {
        if (!(uint8_t)weaponEligibility(call, loadWord64(ctx), player, 0, 0))
            return;
        player = loadWord64(ctx + 0x28);
    }
    uint32_t tick = (uint32_t)entityTicksExisted(call, loadWord64(ctx), player, 0, 0);
    uint32_t prior =
        (uint32_t)lastAttackerTime(call, loadWord64(ctx), loadWord64(ctx + 0x28), 0, 0);
    if (tick != prior)
        return;
    double scale = loadDouble(image + Storage::nativeData_150e50);
    storeDouble(image + Storage::inputVelocityX,
                mul(loadDouble(image + Storage::inputVelocityX), scale));
    storeDouble(image + Storage::inputVelocityZ,
                mul(scale, loadDouble(image + Storage::inputVelocityZ)));
    double v[3];
    memcpy(v, image + Storage::inputVelocityX, 24);
    velocity_set(v, ctx, call);
    image[Storage::attackVelocityApplied] = 1;
}
void captureRotationVelocity(uint8_t *event, uint8_t *image, dependency call) {
    uint8_t *ctx = (uint8_t *)(uintptr_t)loadWord64(event + 8);
    if (!loadWord64(ctx + 0x28))
        return;
    double v[3];
    velocity_get(v, ctx, call);
    memcpy(image + Storage::storedVelocityZ, v + 2, 8);
    memcpy(image + Storage::storedVelocityX, v, 16);
    image[Storage::storedVelocityPending] = 1;
}
static void scale_current(uint8_t *ctx, uint8_t *image, dependency call) {
    double v[3];
    velocity_get(v, ctx, call);
    double factor = (double)loadFloat(image + Storage::reduce_amountCurrent);
    v[0] = mul(v[0], factor);
    v[2] = mul(factor, v[2]);
    velocity_set(v, ctx, call);
}
void updateVelocityMode(uint8_t *event, uint8_t *image, dependency call) {
    image[Storage::attackVelocityApplied] = 0;
    if (loadWord32(image + Storage::modeCurrent) == 2)
        return;
    uint8_t *ctx = (uint8_t *)(uintptr_t)loadWord64(event + 8);
    if (ctx[0x40] != 1)
        return;
    uint32_t id = (uint32_t)entityIdentifier(call, loadWord64(ctx), loadWord64(ctx + 0x28), 0, 0);
    _InterlockedExchange((volatile long *)(image + Storage::localEntityIdentifier), (long)id);
    uint32_t mode = loadWord32(image + Storage::modeCurrent);
    if (mode == 1) {
        if (image[Storage::jumpKeyOwned] == 1) {
            uint64_t settings = clientOptions(call, loadWord64(ctx), loadWord64(ctx + 0x18), 0, 0);
            uint64_t key = jumpKey(call, loadWord64(ctx), settings, 0, 0);
            uint64_t game = loadWord64(ctx);
            uint8_t pressed = (uint8_t)physicalKeyWord(call, game, key, 0, 0);
            setKeyDownRaw(call, game, key, pressed, 0);
            image[Storage::jumpKeyOwned] = 0;
            return;
        }
        if (!(uint8_t)velocityEligible(ctx, image, call))
            return;
        if (!chance(loadFloat(image + Storage::jump_chanceCurrent), Storage::nativeData_150e58,
                    image, call))
            return;
        if (image[Storage::require_sprinting_jumpCurrent] == 1 &&
            !(uint8_t)entitySprinting(call, loadWord64(ctx), loadWord64(ctx + 0x28), 0, 0))
            return;
        if (!(uint8_t)entityOnGround(call, loadWord64(ctx), loadWord64(ctx + 0x28), 0, 0))
            return;
        double v[3];
        velocity_get(v, ctx, call);
        if (0.0 >= v[1])
            return;
        uint64_t effect = effectByIndex(call, loadWord64(ctx), 8, 0, 0);
        if (entityEffect(call, loadWord64(ctx), loadWord64(ctx + 0x28), effect, 0))
            return;
        uint64_t settings = clientOptions(call, loadWord64(ctx), loadWord64(ctx + 0x18), 0, 0);
        uint64_t key = jumpKey(call, loadWord64(ctx), settings, 0, 0);
        if ((uint8_t)keyDown(call, loadWord64(ctx), key, 0, 0))
            return;
        setKeyDownRaw(call, loadWord64(ctx), key, 1, 0);
        image[Storage::jumpKeyOwned] = 1;
        return;
    }
    if (mode != 0)
        return;
    uint32_t countdown = loadWord32(image + Storage::horizontalDelayTicks);
    if (s(countdown) > 0) {
        countdown--;
        storeWord32(image + Storage::horizontalDelayTicks, countdown);
        if (countdown != 0)
            return;
        scale_current(ctx, image, call);
        return;
    }
    if (_InterlockedCompareExchange8((volatile char *)(image + Storage::knockbackPacketPending), 0,
                                     1) != 1)
        return;
    if (!(uint8_t)velocityEligible(ctx, image, call))
        return;
    if (!chance(loadFloat(image + Storage::reduce_chanceCurrent), Storage::nativeData_150e58, image,
                call))
        return;
    double v[3];
    velocity_get(v, ctx, call);
    double length =
        doubleFromWord(call(Storage::nativeData_13cfd0, doubleBits(v[0]), doubleBits(v[2]), 0, 0));
    if (length == 0.0)
        return;
    uint32_t yaw = (uint32_t)entityRotation(call, loadWord64(ctx), loadWord64(ctx + 0x28), 0, 0);
    double pi = loadDouble(image + Storage::nativeData_150e80);
    float angle = roundf32(
        add(divd(mul((double)loadFloat(&yaw), pi), loadDouble(image + Storage::nativeData_150e88)),
            pi));
    float sine = floatFromWord(nativeBoundary_b1cf0(call, floatBits(angle), 0, 0, 0));
    float cosine = floatFromWord(nativeBoundary_b3590(call, floatBits(angle), 0, 0, 0));
    double projection = divd(add(mul((double)sine, v[0]), mul((double)cosine, v[2])), length);
    double angle_measure =
        doubleFromWord(call(Storage::nativeData_13cfa0, doubleBits(projection), 0, 0, 0));
    if (!((double)loadFloat(image + Storage::fovCurrent) >= angle_measure))
        return;
    countdown =
        (uint32_t)_mm_cvttss_si32(_mm_load_ss((float *)(image + Storage::reduce_delayCurrent)));
    storeWord32(image + Storage::horizontalDelayTicks, countdown);
    if (s(countdown) > 0) {
        countdown--;
        storeWord32(image + Storage::horizontalDelayTicks, countdown);
        if (countdown != 0)
            return;
    }
    scale_current(ctx, image, call);
}

} // namespace reconstruction::Velocity
// END SOURCE modules/Velocity/velocity.cpp

// Convenient borrowed-state interface

namespace shareable {
class Velocity {
  public:
    static constexpr const char *kName = "Velocity";
    static constexpr const char *kDescription = "Reduces the amount of knockback you take.";
    explicit Velocity(std::uint8_t *image) : image_(image) {}
    // Mode. Config key: mode.
    ChoiceSetting &mode() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2eaa20);
    }
    // Option labels observed in the captured metadata.
    enum class ModeMode : std::uint32_t { Regular = 0, Jump = 1, Reduce = 2, Ignore = 3 };
    // Chance. Config key: reduce_chance.
    NumberSetting &reduce_chance() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2eab98);
    }
    // FOV. Config key: fov.
    NumberSetting &fov() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2eac40);
    }
    // Reduce to. Config key: reduce_amount.
    NumberSetting &reduce_amount() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2eac08);
    }
    // Reduce delay. Config key: reduce_delay.
    NumberSetting &reduce_delay() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2eabd0);
    }
    // Chance. Config key: jump_chance.
    NumberSetting &jump_chance() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2eac78);
    }
    // Allow for double-clicks. Config key: reduce_multiple_per_tick.
    BooleanSetting &reduce_multiple_per_tick() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eab78);
    }
    // Ignore vertical. Config key: ignore_vertical.
    ChoiceSetting &ignore_vertical() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2eab38);
    }
    // Option labels observed in the captured metadata.
    enum class IgnoreVerticalMode : std::uint32_t { Never = 0, OnlyInAir = 1, Always = 2 };
    // Chance. Config key: ignore_chance.
    NumberSetting &ignore_chance() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2eaa60);
    }
    // Looking at player. Config key: require_target.
    BooleanSetting &require_target() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eaaf8);
    }
    // Mouse pressed. Config key: require_mouse.
    BooleanSetting &require_mouse() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eaab8);
    }
    // Moving forward. Config key: require_forward.
    BooleanSetting &require_forward() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eaa98);
    }
    // Holding weapon. Config key: require_weapon.
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eaad8);
    }
    // Sprinting. Config key: require_sprinting_jump.
    BooleanSetting &require_sprinting_jump() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eacb0);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_velocity_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_velocity_settings(&context, image_, &dependencies);
    }
    void formatStatus(char *output, ::reconstruction::Velocity::dependency call) {
        ::reconstruction::Velocity::formatStatus(output, image_, call);
    }
    void applyStoredVelocity(uint8_t *event, ::reconstruction::Velocity::dependency call) {
        ::reconstruction::Velocity::applyStoredVelocity(event, image_, call);
    }
    void onPacket(uint8_t *event, ::reconstruction::Velocity::dependency call) {
        ::reconstruction::Velocity::onPacket(event, image_, call);
    }
    void onModuleStateChanged(uint8_t *event, ::reconstruction::Velocity::dependency call) {
        ::reconstruction::Velocity::onModuleStateChanged(event, image_, call);
    }
    void captureInputVelocity(uint8_t *event, ::reconstruction::Velocity::dependency call) {
        ::reconstruction::Velocity::captureInputVelocity(event, image_, call);
    }
    void applyAttackVelocity(uint8_t *event, ::reconstruction::Velocity::dependency call) {
        ::reconstruction::Velocity::applyAttackVelocity(event, image_, call);
    }
    void captureRotationVelocity(uint8_t *event, ::reconstruction::Velocity::dependency call) {
        ::reconstruction::Velocity::captureRotationVelocity(event, image_, call);
    }
    void updateVelocityMode(uint8_t *event, ::reconstruction::Velocity::dependency call) {
        ::reconstruction::Velocity::updateVelocityMode(event, image_, call);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
