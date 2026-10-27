// Timer Range

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Timer_Range.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Timer_Range.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Timer Range: lib_win settings 0x43ad0.
static constexpr SettingsStep settings_steps_Surface_Timer_Range[] = {
    {SettingsControl::choice, "mode", 0x2f33e0},
    {SettingsControl::number, "min_dist", 0x2f34e8},
    {SettingsControl::number, "duration", 0x2f3478},
    {SettingsControl::number, "duration_legit", 0x2f34b0},
    {SettingsControl::number, "cooldown", 0x2f3440},
    {SettingsControl::boolean, "block_while_frozen", 0x2f3420},
    {SettingsControl::boolean, "require_mouse_pressed", 0x2f3370},
    {SettingsControl::boolean, "require_weapon", 0x2f3390},
    {SettingsControl::boolean, "require_not_using_item", 0x2f33b0},
};
static constexpr ModuleSurface surface_Surface_Timer_Range{
    nullptr, 0, settings_steps_Surface_Timer_Range, std::size(settings_steps_Surface_Timer_Range)};

extern "C" __declspec(dllexport) void
recovered_timer_range_settings(SettingsContext *context, std::uint8_t *image,
                               const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Timer_Range, context, image, *dependencies);
}

// Timer Range: lib_win runtime UI 0x439e0.
extern "C" __declspec(dllexport) void
recovered_timer_range_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                         const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, image + 0x2f33e0);
    dependencies->number(layout, ui, image + 0x2f34e8);
    dependencies->number(
        layout, ui,
        image + (read_surface_value<std::uint32_t>(image, 0x2f3410) == 0 ? 0x2f3478 : 0x2f34b0));
    dependencies->number(layout, ui, image + 0x2f3440);
    if (read_surface_value<std::uint32_t>(image, 0x2f3410) == 0) {
        dependencies->checkbox(layout, ui, image + 0x2f3420);
    }
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2f3370);
    dependencies->checkbox(layout, ui, image + 0x2f3390);
    dependencies->checkbox(layout, ui, image + 0x2f33b0);
}
// END SOURCE native/verified/surfaces/Surface_Timer_Range.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Timer_Range
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Timer_Range.cpp
extern "C" __declspec(dllexport) void
recovered_timer_range_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                               const BoundSurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, image + 0x2f33e0);
    dependencies->number(layout, ui, image + 0x2f34e8);
    dependencies->number(
        layout, ui,
        image + (read_surface_value<std::uint32_t>(image, 0x2f3410) == 0 ? 0x2f3478 : 0x2f34b0));
    dependencies->number(layout, ui, image + 0x2f3440);
    if (read_surface_value<std::uint32_t>(image, 0x2f3410) == 0) {
        dependencies->checkbox(layout, ui, image + 0x2f3420);
    }
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2f3370);
    dependencies->checkbox(layout, ui, image + 0x2f3390);
    dependencies->checkbox(layout, ui, image + 0x2f33b0);
}
// END SOURCE shared/BoundSurfaces.cpp@Timer_Range

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Timer_Range/Bindings.cpp
#ifndef SLINKY_SHARE_910DA9095F2F1D477AA5
#define SLINKY_SHARE_910DA9095F2F1D477AA5
// BEGIN SOURCE modules/Timer_Range/Dependencies.hpp
#include <cstdint>
#include "../runtime/modules/Aim_Assist/Support.hpp"
#include "../runtime/shared/Geometry.hpp"
// Each endpoint has one named native role. The callback bodies contain the
// module algorithms. Unbound endpoints are listed in the module report.
namespace timer_range {
using Word = std::uint64_t;
struct Endpoint {
    void *context;
    Word (*function)(void *, Word, Word, Word, Word);
    Word operator()(Word a, Word b, Word c, Word d) const {
        return function(context, a, b, c, d);
    }
};
struct Dependencies {
    Endpoint clientTimer;              // 0x22c70
    Endpoint clientOptions;            // 0x22cf0
    Endpoint mouseOver;                // 0x22e10
    Endpoint refreshMouseOver;         // 0x22eb0
    Endpoint positionModeIsZero;       // 0x23020
    Endpoint entityPosition;           // 0x23030
    Endpoint entityRotation;           // 0x23170
    Endpoint entityVelocity;           // 0x23550
    Endpoint entityOnGround;           // 0x23780
    Endpoint entityHurtTime;           // 0x239f0
    Endpoint movementSpeed;            // 0x23b40
    Endpoint usingItem;                // 0x23f90
    Endpoint serverPosition;           // 0x24160
    Endpoint serverInterpolationTicks; // 0x24200
    Endpoint hitType;                  // 0x24b50
    Endpoint useItemKey;               // 0x24f90
    Endpoint jumpKey;                  // 0x25080
    Endpoint forwardKey;               // 0x250d0
    Endpoint backKey;                  // 0x25120
    Endpoint leftKey;                  // 0x25170
    Endpoint rightKey;                 // 0x251c0
    Endpoint attackKey;                // 0x25270
    Endpoint updateKey;                // 0x25380
    Endpoint keyPressed;               // 0x25430
    Endpoint setKeyPressed;            // 0x25460
    Endpoint setTimerSpeed;            // 0x259c0
    Endpoint setTimerPartialTicks;     // 0x25a10
    Endpoint heldItem;                 // 0x28a50
    Endpoint isBlockingItem;           // 0x28ac0
    Endpoint worldRayClear;            // 0x29000
    Endpoint attackInput;              // 0x29080
    Endpoint weaponAllowed;            // 0x380b0
    Endpoint sine;                     // 0xb1cf0
    Endpoint cosine;                   // 0xb3590
    Endpoint hypotenuse;               // 0x13cfd0
};
enum class Mode : std::uint32_t { Regular = 0, Legit = 1 };
double *movementPrediction(double *, Word, float, float, float, std::uint8_t *,
                           const Dependencies &); // native 0x29290
} // namespace timer_range
namespace timer_range {
void sampleMovementKeys(uint64_t game, uint64_t settings, uint8_t *image,
                        const Dependencies &dependencies);
void beginFreeze(uint8_t *ctx, uint8_t *image, const Dependencies &dependencies);
void onTick(uint8_t *event, uint8_t *image, const Dependencies &dependencies);
void onPacket(uint8_t *event, uint8_t *image, const Dependencies &dependencies);
void onDisabled(uint8_t *event, uint8_t *image, const Dependencies &dependencies);
void onRotationFrame(uint8_t *event, uint8_t *image, const Dependencies &dependencies);
} // namespace timer_range

namespace timer_range {
void bindKnown(Dependencies &, aim_assist::Runtime &);
}

namespace timer_range {
std::uint8_t isFrozen(const std::uint8_t *image);
} // namespace timer_range
// END SOURCE modules/Timer_Range/Dependencies.hpp

#endif // SLINKY_SHARE_910DA9095F2F1D477AA5

#include "../runtime/shared/JniAccess.hpp"
#include "../runtime/shared/Trigonometry.hpp"
#include "../runtime/shared/DecodedNumericService.hpp"
namespace timer_range {
using namespace recovered_jni;
void bindKnown(Dependencies &dependencies, aim_assist::Runtime &runtime) {
    dependencies.hypotenuse = {
        &runtime, +[](void *user, Word a, Word b, Word, Word) -> Word {
            auto &rt = *static_cast<aim_assist::Runtime *>(user);
            return doubleBits(reconstruction::numeric_service::pair_13cfd0(
                {rt.image, rt.numericPairEncodedCell_13cfd0}, doubleValue(a), doubleValue(b)));
        }};
    dependencies.sine = {&runtime, +[](void *user, Word a, Word, Word, Word) -> Word {
                             return floatBits(recovered_sine_b1cf0(
                                 floatValue(a), static_cast<aim_assist::Runtime *>(user)->image));
                         }};
    dependencies.cosine = {&runtime, +[](void *user, Word a, Word, Word, Word) -> Word {
                               return floatBits(recovered_cosine_b3590(
                                   floatValue(a), static_cast<aim_assist::Runtime *>(user)->image));
                           }};
    dependencies.clientTimer = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                    return objectField(bridge(a), b, 0x198);
                                }};
    dependencies.clientOptions = {&runtime,
                                  +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                      return recovered_access_helper(bridge(a), 0x22cf0, b, 0, 0);
                                  }};
    dependencies.mouseOver = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                  return recovered_access_helper(bridge(a), 0x22e10, b, 0, 0);
                              }};
    dependencies.refreshMouseOver = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return recovered_access_helper(bridge(a), 0x22eb0, b, c, 0);
        }};
    dependencies.positionModeIsZero = {&runtime,
                                       +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                           return aim_assist::mc::positionModeIsZero(bridge(a));
                                       }};
    dependencies.entityPosition = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return storedVector(a, aim_assist::mc::entityPosition(bridge(b), object(c)));
        }};
    dependencies.entityRotation = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return aim_assist::packed(aim_assist::mc::entityRotation(bridge(a), object(b)));
        }};
    dependencies.entityVelocity = {&runtime,
                                   +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                       return getPosition(a, b, c, 0x2b8);
                                   }};
    dependencies.entityOnGround = {&runtime,
                                   +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                       return field<std::uint8_t, 0x300>(bridge(a), b, 0x2f0) != 0;
                                   }};
    dependencies.entityHurtTime = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return static_cast<std::uint32_t>(aim_assist::mc::entityHurtTime(bridge(a), object(b)));
        }};
    dependencies.movementSpeed = {&runtime,
                                  +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                      return floatBits(field<float, 0x330>(bridge(a), b, 0x568));
                                  }};
    dependencies.usingItem = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                  return recovered_game_using_item(bridge(a), b);
                              }};
    dependencies.serverPosition = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return storedVector(
                a, aim_assist::mc::entityOtherPlayerServerPosition(bridge(b), object(c)));
        }};
    dependencies.serverInterpolationTicks = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return field<std::uint32_t, 0x320>(bridge(a), b, 0x878);
        }};
    dependencies.hitType = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                return recovered_access_helper(bridge(a), 0x24b50, b, 0, 0);
                            }};
    dependencies.useItemKey = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                   return recovered_access_helper(bridge(a), 0x24f90, b, 0, 0);
                               }};
    dependencies.jumpKey = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                return recovered_null_move_key(bridge(a), b, 6);
                            }};
    dependencies.forwardKey = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                   return recovered_null_move_key(bridge(a), b, 2);
                               }};
    dependencies.backKey = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                return recovered_null_move_key(bridge(a), b, 4);
                            }};
    dependencies.leftKey = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                return recovered_null_move_key(bridge(a), b, 3);
                            }};
    dependencies.rightKey = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                 return recovered_null_move_key(bridge(a), b, 5);
                             }};
    dependencies.attackKey = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                  return recovered_null_move_key(bridge(a), b, 0);
                              }};
    dependencies.updateKey = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                  const auto value =
                                      field<std::uint32_t, 0x320>(bridge(a), b, 0x480);
                                  integerField(bridge(a), b, 0x480, value + 1);
                                  return 0;
                              }};
    dependencies.keyPressed = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                   return recovered_access_helper(bridge(a), 0x25430, b, 0, 0);
                               }};
    dependencies.setKeyPressed = {&runtime,
                                  +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                      return recovered_access_helper(bridge(a), 0x25460, b, c, 0);
                                  }};
    dependencies.setTimerSpeed = {&runtime,
                                  +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                      floatField(bridge(a), b, 0x390, floatValue(c));
                                      return 0;
                                  }};
    dependencies.setTimerPartialTicks = {&runtime,
                                         +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                             floatField(bridge(a), b, 0x398, floatValue(c));
                                             return 0;
                                         }};
    dependencies.heldItem = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                 return recovered_game_item_object(bridge(a), b);
                             }};
    dependencies.isBlockingItem = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            if (!b)
                return 0;
            const auto id =
                static_cast<std::uint32_t>(recovered_game_item_numeric_id(bridge(a), b));
            const auto index = id - 0x10bu;
            if (index > 16)
                return 0;
            return (0x10223u >> index) & 0xffffff01u;
        }};
    dependencies.worldRayClear = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return aim_assist::mc::clearWorldRayBetween(
                bridge(a), object(b), *reinterpret_cast<const aim_assist::Vec3d *>(c),
                *reinterpret_cast<const aim_assist::Vec3d *>(d));
        }};
    dependencies.attackInput = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                    return aim_assist::attackInputDown(
                                        *reinterpret_cast<const aim_assist::Frame *>(a));
                                }};
    dependencies.weaponAllowed = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return static_cast<aim_assist::Runtime *>(user)->isWeapon(bridge(a), object(b));
        }};
}
} // namespace timer_range
// END SOURCE modules/Timer_Range/Bindings.cpp

// BEGIN SOURCE modules/Timer_Range/FrozenQuery.cpp
#include "../runtime/shared/SharedNativeState.hpp"
namespace timer_range {
std::uint8_t isFrozen(const std::uint8_t *image) {
    return reconstruction::native_state::timerRangeFrozen(image);
}
} // namespace timer_range
// END SOURCE modules/Timer_Range/FrozenQuery.cpp

// BEGIN SOURCE modules/Timer_Range/MovementPrediction.cpp
#include <cstring>
#include <emmintrin.h>

namespace timer_range {
namespace {
template <class T> T constant(const std::uint8_t *image, std::uint32_t rva) {
    T result;
    std::memcpy(&result, image + rva, sizeof result);
    return result;
}
float asFloat(Word bits) {
    const auto low = static_cast<std::uint32_t>(bits);
    float value;
    std::memcpy(&value, &low, 4);
    return value;
}
std::uint32_t asBits(float value) {
    std::uint32_t result;
    std::memcpy(&result, &value, 4);
    return result;
}
} // namespace
// Runtime instruction evidence: 0x29290..0x293b9. Constants remain in the
// caller-supplied constant image; no native capture is used as startup state.
double *movementPrediction(double *out, Word rotation, float longitudinal, float lateral,
                           float speed, std::uint8_t *image, const Dependencies &dependencies) {
    using namespace aim_assist::native;
    const float inputScale = constant<float>(image, 0x14fbd8);
    longitudinal = roundedMul(longitudinal, inputScale);
    lateral = roundedMul(lateral, inputScale);
    const float longitudinalSquared = roundedMul(longitudinal, longitudinal);
    const float lateralSquared = roundedMul(lateral, lateral);
    const float squared = roundedAdd(lateralSquared, longitudinalSquared);
    if (constant<float>(image, 0x14fbdc) > squared) {
        recovered_geometry_construct_93b0(out, 0.0, 0.0, 0.0);
        return out;
    }
    const float speedScale = roundedMul(speed, constant<float>(image, 0x14fbe0));
    const float magnitude = _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(squared)));
    const float divisor = maxFloatSse(constant<float>(image, 0x14fbe4), magnitude);
    const float fraction = roundedDiv(speedScale, divisor);
    lateral = roundedMul(lateral, fraction);
    longitudinal = roundedMul(longitudinal, fraction);
    const double scaledYaw =
        roundedMulDouble(static_cast<double>(asFloat(rotation)), constant<double>(image, 0x14fbe8));
    const float radians =
        static_cast<float>(roundedDivDouble(scaledYaw, constant<double>(image, 0x14fbf0)));
    const float sine = asFloat(dependencies.sine(asBits(radians), 0, 0, 0));
    const float cosine = asFloat(dependencies.cosine(asBits(radians), 0, 0, 0));
    const float forwardX = roundedMul(longitudinal, sine);
    const float sideX = roundedMul(lateral, cosine);
    out[0] = static_cast<double>(roundedSub(sideX, forwardX));
    std::uint64_t zero = 0;
    std::memcpy(out + 1, &zero, 8);
    const float sideZ = roundedMul(lateral, sine);
    const float forwardZ = roundedMul(longitudinal, cosine);
    out[2] = static_cast<double>(roundedAdd(forwardZ, sideZ));
    return out;
}
} // namespace timer_range
// END SOURCE modules/Timer_Range/MovementPrediction.cpp

// BEGIN SOURCE modules/Timer_Range/Surface.cpp
#ifndef SLINKY_SHARE_3DF67E15F2A4A5073FB8
#define SLINKY_SHARE_3DF67E15F2A4A5073FB8
// BEGIN SOURCE modules/Timer_Range/Surface.hpp
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/native/verified/module_format.hpp"
namespace timer_range {
void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                    const BoundSurfaceUiDependencies &);
void serializeConfig(SettingsContext &, std::uint8_t *image, const SurfaceSettingsDependencies &);
void writeStatus(FormatState *, char *destination, const std::uint8_t *image,
                 const char *const *labels);
} // namespace timer_range
// END SOURCE modules/Timer_Range/Surface.hpp

#endif // SLINKY_SHARE_3DF67E15F2A4A5073FB8

extern "C" void recovered_timer_range_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                               const BoundSurfaceUiDependencies *);
extern "C" void recovered_timer_range_settings(SettingsContext *, std::uint8_t *,
                                               const SurfaceSettingsDependencies *);
namespace timer_range {
void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                    const BoundSurfaceUiDependencies &dependencies) {
    recovered_timer_range_bound_ui(ui, layout, image, &dependencies);
}
void serializeConfig(SettingsContext &context, std::uint8_t *image,
                     const SurfaceSettingsDependencies &dependencies) {
    recovered_timer_range_settings(&context, image, &dependencies);
}
void writeStatus(FormatState *format, char *destination, const std::uint8_t *image,
                 const char *const *labels) {
    recovered_format(format, destination, 0x20, "%s",
                     labels[read_surface_value<std::uint32_t>(image, 0x2f3410)]);
}
} // namespace timer_range
// END SOURCE modules/Timer_Range/Surface.cpp

// BEGIN SOURCE modules/Timer_Range/timer_range_events.cpp
#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
#include <intrin.h>
namespace timer_range {
static uint64_t q_timer_range_events(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t d_timer_range_events(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static float f_timer_range_events(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static double g_timer_range_events(const void *p) {
    double v;
    memcpy(&v, p, 8);
    return v;
}
static void pd_timer_range_events(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
static void pf(void *p, float v) {
    memcpy(p, &v, 4);
}
static float af(float a, float b) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}

void sampleMovementKeys(uint64_t game, uint64_t settings, uint8_t *image,
                        const Dependencies &dependencies) {
    uint64_t forward = dependencies.forwardKey(game, settings, 0, 0),
             backward = dependencies.backKey(game, settings, 0, 0);
    uint64_t left = dependencies.leftKey(game, settings, 0, 0),
             right = dependencies.rightKey(game, settings, 0, 0);
    uint8_t pressed = (uint8_t)dependencies.keyPressed(game, forward, 0, 0);
    float one = f_timer_range_events(image + 0x15493c), longitudinal = pressed ? one : 0.f;
    pressed = (uint8_t)dependencies.keyPressed(game, backward, 0, 0);
    float negative = f_timer_range_events(image + 0x154940);
    if (pressed)
        longitudinal = af(longitudinal, negative);
    pressed = (uint8_t)dependencies.keyPressed(game, left, 0, 0);
    float lateral = pressed ? one : 0.f;
    if ((uint8_t)dependencies.keyPressed(game, right, 0, 0))
        lateral = af(lateral, negative);
    pf(image + 0x3043e0, longitudinal);
    pf(image + 0x3043e4, lateral);
}
void beginFreeze(uint8_t *ctx, uint8_t *image, const Dependencies &dependencies) {
    uint64_t timer =
        dependencies.clientTimer(q_timer_range_events(ctx), q_timer_range_events(ctx + 0x18), 0, 0);
    dependencies.setTimerSpeed(q_timer_range_events(ctx), timer, 0, 0);
    image[0x3043dc] = 1;
    if (d_timer_range_events(image + 0x2f3410) == 1) {
        _InterlockedExchange8((volatile char *)(image + 0x3043e8), 1);
        return;
    }
    if (image[0x2f3438] == 1) {
        uint64_t game = q_timer_range_events(ctx),
                 item = dependencies.heldItem(game, q_timer_range_events(ctx + 0x28), 0, 0);
        if (!(uint8_t)dependencies.isBlockingItem(game, item, 0, 0))
            return;
        uint64_t settings = dependencies.clientOptions(q_timer_range_events(ctx),
                                                       q_timer_range_events(ctx + 0x18), 0, 0),
                 key = dependencies.useItemKey(q_timer_range_events(ctx), settings, 0, 0);
        dependencies.setKeyPressed(q_timer_range_events(ctx), key, 1, 0);
        dependencies.updateKey(q_timer_range_events(ctx), key, 0, 0);
    }
}
void onTick(uint8_t *event, uint8_t *image, const Dependencies &dependencies) {
    uint8_t *ctx = (uint8_t *)(uintptr_t)q_timer_range_events(event + 8);
    if ((int32_t)d_timer_range_events(image + 0x3043d8) > 0) {
        uint64_t settings = dependencies.clientOptions(q_timer_range_events(ctx),
                                                       q_timer_range_events(ctx + 0x18), 0, 0);
        uint32_t remaining = d_timer_range_events(image + 0x3043d8) - 1;
        pd_timer_range_events(image + 0x3043d8, remaining);
        if ((remaining | d_timer_range_events(image + 0x2f3410)) == 0)
            beginFreeze(ctx, image, dependencies);
        if (ctx[0x40] != 1)
            return;
        uint8_t *target = (uint8_t *)(uintptr_t)q_timer_range_events(ctx + 0x38);
        if (!q_timer_range_events(target + 8))
            return;
        uint64_t hit = dependencies.mouseOver(q_timer_range_events(ctx),
                                              q_timer_range_events(ctx + 0x18), 0, 0);
        if (!hit)
            return;
        if ((uint32_t)dependencies.hitType(q_timer_range_events(ctx), hit, 0, 0) != 2)
            return;
        dependencies.refreshMouseOver(q_timer_range_events(ctx), q_timer_range_events(ctx + 0x18),
                                      0, 0);
        uint64_t key = dependencies.attackKey(q_timer_range_events(ctx), settings, 0, 0);
        dependencies.updateKey(q_timer_range_events(ctx), key, 0, 0);
        return;
    }
    image[0x3043dd] = 0;
    if (ctx[0x40] != 1)
        return;
    uint8_t *target = (uint8_t *)(uintptr_t)q_timer_range_events(ctx + 0x38);
    if (!q_timer_range_events(target + 8) ||
        g_timer_range_events(image + 0x1548c0) > g_timer_range_events(target + 0x10))
        return;
    if (!(uint8_t)dependencies.entityOnGround(q_timer_range_events(ctx),
                                              q_timer_range_events(ctx + 0x28), 0, 0))
        return;
    if ((int32_t)dependencies.entityHurtTime(q_timer_range_events(ctx),
                                             q_timer_range_events(target + 8), 0, 0) > 1)
        return;
    if (image[0x2f3388] == 1 && !(uint8_t)dependencies.attackInput((uintptr_t)ctx, 0, 0, 0))
        return;
    if (image[0x2f33a8] == 1 &&
        !(uint8_t)dependencies.weaponAllowed(q_timer_range_events(ctx),
                                             q_timer_range_events(ctx + 0x28), 0, 0))
        return;
    if (image[0x2f33c8] == 1 &&
        (uint8_t)dependencies.usingItem(q_timer_range_events(ctx), q_timer_range_events(ctx + 0x28),
                                        0, 0))
        return;
    double velocity[3];
    dependencies.entityVelocity((uintptr_t)velocity, q_timer_range_events(ctx),
                                q_timer_range_events(ctx + 0x28), 0);
    if (velocity[1] > 0.0)
        return;
    uint64_t settings = dependencies.clientOptions(q_timer_range_events(ctx),
                                                   q_timer_range_events(ctx + 0x18), 0, 0),
             jump = dependencies.jumpKey(q_timer_range_events(ctx), settings, 0, 0);
    if ((uint8_t)dependencies.keyPressed(q_timer_range_events(ctx), jump, 0, 0))
        return;
    double self[3], candidate[3], copy[3];
    dependencies.entityPosition((uintptr_t)self, q_timer_range_events(ctx),
                                q_timer_range_events(ctx + 0x28), 0);
    if (!(uint8_t)dependencies.positionModeIsZero(q_timer_range_events(ctx), 0, 0, 0)) {
        memcpy(copy, self, 24);
        recovered_vector_y_offset_9590(self, copy, image);
    }
    dependencies.serverPosition((uintptr_t)candidate, q_timer_range_events(ctx),
                                q_timer_range_events(target + 8), 0);
    if (!(uint8_t)dependencies.positionModeIsZero(q_timer_range_events(ctx), 0, 0, 0)) {
        memcpy(copy, candidate, 24);
        recovered_vector_y_offset_9590(candidate, copy, image);
    }
    double self_copy[3], candidate_copy[3];
    memcpy(self_copy, self, 24);
    memcpy(candidate_copy, candidate, 24);
    if (!(uint8_t)dependencies.worldRayClear(q_timer_range_events(ctx),
                                             q_timer_range_events(ctx + 0x20), (uintptr_t)self_copy,
                                             (uintptr_t)candidate_copy))
        return;
    sampleMovementKeys(q_timer_range_events(ctx), settings, image, dependencies);
    image[0x3043dd] = (f_timer_range_events(image + 0x3043e0) > 0.f);
}
void onPacket(uint8_t *event, uint8_t *image, const Dependencies &dependencies) {
    if (image[0x3043e8] & 1)
        pd_timer_range_events(event + 0x24, 1);
}
void onDisabled(uint8_t *event, uint8_t *image, const Dependencies &dependencies) {
    if (q_timer_range_events(event + 0x10) != (uintptr_t)(image + 0x2f3160) || event[0x18] != 0)
        return;
    uint8_t *ctx = (uint8_t *)(uintptr_t)q_timer_range_events(event + 8);
    uint64_t timer =
        dependencies.clientTimer(q_timer_range_events(ctx), q_timer_range_events(ctx + 0x18), 0, 0);
    dependencies.setTimerSpeed(q_timer_range_events(ctx), timer,
                               d_timer_range_events(image + 0x154938), 0);
    image[0x3043dc] = 0;
    pd_timer_range_events(image + 0x3043d8, 0);
    _InterlockedExchange8((volatile char *)(image + 0x3043e8), 0);
}

} // namespace timer_range
// END SOURCE modules/Timer_Range/timer_range_events.cpp

// BEGIN SOURCE modules/Timer_Range/timer_range_update.cpp
#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
#include <intrin.h>
namespace timer_range {
static uint64_t q_timer_range_update(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t d_timer_range_update(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static float f_timer_range_update(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static double g_timer_range_update(const void *p) {
    double v;
    memcpy(&v, p, 8);
    return v;
}
static float ff(uint64_t v) {
    uint32_t b = (uint32_t)v;
    return f_timer_range_update(&b);
}
static uint32_t fb(float v) {
    return d_timer_range_update(&v);
}
static void pd_timer_range_update(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
static void pg(void *p, double v) {
    memcpy(p, &v, 8);
}
static double sub(double a, double b) {
    return _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double mul(double a, double b) {
    return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double divide(double a, double b) {
    return _mm_cvtsd_f64(_mm_div_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static float narrow(double a) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(a)));
}
static float mf(float a, float b) {
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float sf(float a, float b) {
    return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
void beginFreeze(uint8_t *, uint8_t *, const Dependencies &);

void onRotationFrame(uint8_t *event, uint8_t *image, const Dependencies &dependencies) {
    uint8_t *ctx = (uint8_t *)(uintptr_t)q_timer_range_update(event + 8);
    uint64_t timer =
        dependencies.clientTimer(q_timer_range_update(ctx), q_timer_range_update(ctx + 0x18), 0, 0);
    if (image[0x3043dc] == 1) {
        double remaining =
            sub(g_timer_range_update(image + 0x3043f8), g_timer_range_update(event + 0x18));
        pg(image + 0x3043f8, remaining);
        if (remaining > 0.) {
            dependencies.setTimerSpeed(q_timer_range_update(ctx), timer, 0, 0);
            return;
        }
        uint64_t fresh = dependencies.clientTimer(q_timer_range_update(ctx),
                                                  q_timer_range_update(ctx + 0x18), 0, 0);
        dependencies.setTimerSpeed(q_timer_range_update(ctx), fresh,
                                   d_timer_range_update(image + 0x1548d0), 0);
        image[0x3043dc] = 0;
        _InterlockedExchange8((volatile char *)(image + 0x3043e8), 0);
        uint32_t mode = d_timer_range_update(image + 0x2f3410);
        if (((mode != 1) & image[0x2f3438]) == 1) {
            uint64_t game = q_timer_range_update(ctx),
                     item = dependencies.heldItem(game, q_timer_range_update(ctx + 0x28), 0, 0);
            if ((uint8_t)dependencies.isBlockingItem(game, item, 0, 0)) {
                uint64_t settings = dependencies.clientOptions(
                    q_timer_range_update(ctx), q_timer_range_update(ctx + 0x18), 0, 0);
                uint64_t key = dependencies.useItemKey(q_timer_range_update(ctx), settings, 0, 0);
                dependencies.setKeyPressed(q_timer_range_update(ctx), key, 0, 0);
            }
            mode = d_timer_range_update(image + 0x2f3410);
        }
        if (mode == 1)
            dependencies.setTimerPartialTicks(
                q_timer_range_update(ctx), timer,
                fb((float)(int32_t)d_timer_range_update(image + 0x3043d8)), 0);
    }
    double cooldown = g_timer_range_update(image + 0x3043f0);
    if (cooldown > 0.) {
        pg(image + 0x3043f0, sub(cooldown, g_timer_range_update(event + 0x18)));
        return;
    }
    if (image[0x3043dd] != 1 || ctx[0x40] != 1)
        return;
    uint8_t *target = (uint8_t *)(uintptr_t)q_timer_range_update(ctx + 0x38);
    if (!q_timer_range_update(target + 8))
        return;
    double velocity[3], self[3], position[3], desired[3], a[3], b[3], out[3];
    dependencies.entityVelocity((uintptr_t)velocity, q_timer_range_update(ctx),
                                q_timer_range_update(ctx + 0x28), 0);
    dependencies.entityPosition((uintptr_t)self, q_timer_range_update(ctx),
                                q_timer_range_update(ctx + 0x28), 0);
    if (!(uint8_t)dependencies.positionModeIsZero(q_timer_range_update(ctx), 0, 0, 0)) {
        memcpy(a, self, 24);
        recovered_vector_y_offset_9590(out, a, image);
        memcpy(self, out, 24);
    }
    dependencies.entityPosition((uintptr_t)position, q_timer_range_update(ctx),
                                q_timer_range_update(target + 8), 0);
    dependencies.serverPosition((uintptr_t)desired, q_timer_range_update(ctx),
                                q_timer_range_update(target + 8), 0);
    int32_t target_ticks = (int32_t)dependencies.serverInterpolationTicks(
        q_timer_range_update(ctx), q_timer_range_update(target + 8), 0, 0);
    uint64_t angles = dependencies.entityRotation(q_timer_range_update(ctx),
                                                  q_timer_range_update(ctx + 0x28), 0, 0);
    double radians = g_timer_range_update(image + 0x1548d8);
    float yaw =
        narrow(sub(g_timer_range_update(image + 0x1548e0), mul((double)ff(angles), radians)));
    float pitch = ff((uint32_t)(angles >> 32) + 0x80000000u);
    float cosine = ff(dependencies.cosine(fb(yaw), 0, 0, 0)),
          sine = ff(dependencies.sine(fb(yaw), 0, 0, 0));
    pitch = narrow(mul((double)pitch, radians));
    float pitch_cos = ff(dependencies.cosine(fb(pitch), 0, 0, 0)),
          pitch_sin = ff(dependencies.sine(fb(pitch), 0, 0, 0));
    uint32_t setting = d_timer_range_update(image + 0x2f3410) == 0 ? 0x2f3478 : 0x2f34b0;
    int32_t steps = _mm_cvttss_si32(_mm_load_ss((const float *)(image + setting + 0x30)));
    if (steps <= 0)
        return;
    pitch_cos = ff(fb(pitch_cos) ^ d_timer_range_update(image + 0x1548f0));
    double direction[3] = {(double)mf(sine, pitch_cos), (double)pitch_sin,
                           (double)mf(cosine, pitch_cos)};
    double bottom = g_timer_range_update(image + 0x154900),
           half = g_timer_range_update(image + 0x154908),
           top = g_timer_range_update(image + 0x154910),
           reach = g_timer_range_update(image + 0x154918);
    double damping = g_timer_range_update(image + 0x154928),
           target_factor = g_timer_range_update(image + 0x154930);
    for (uint32_t step = 1; step <= (uint32_t)steps; ++step) {
        double snapshot[3], target_snapshot[3], box[6], ray[3], inverse[3];
        memcpy(snapshot, self, 24);
        memcpy(target_snapshot, position, 24);
        recovered_geometry_construct_93b0(a, half, bottom, half);
        memcpy(b, target_snapshot, 24);
        recovered_vector_subtract_93d0(box, b, a);
        recovered_geometry_construct_93b0(a, half, top, half);
        memcpy(b, target_snapshot, 24);
        recovered_geometry_add_9400(box + 3, b, a);
        memcpy(a, direction, 24);
        recovered_vector_scale_9430(ray, a, reach);
        memcpy(a, ray, 24);
        recovered_vector_reciprocal_9650(inverse, a, image);
        if ((uint8_t)recovered_box_ray_98e0(box, snapshot, inverse, image)) {
            recovered_box_clamp_9880(out, box, snapshot);
            memcpy(a, snapshot, 24);
            memcpy(b, out, 24);
            double distance = recovered_vector_distance_squared(a, b);
            if (distance > 0.) {
                float radius = f_timer_range_update(image + 0x2f3518);
                if ((double)mf(radius, radius) > distance || step == UINT32_MAX)
                    return;
                float step_float = (float)(int32_t)step;
                if (d_timer_range_update(image + 0x2f3410) == 1)
                    beginFreeze(ctx, image, dependencies);
                else
                    dependencies.setTimerPartialTicks(q_timer_range_update(ctx), timer,
                                                      fb(step_float), 0);
                pd_timer_range_update(image + 0x3043d8, step);
                pg(image + 0x3043f8, mul((double)sf(step_float, f_timer_range_update(event + 0x10)),
                                         g_timer_range_update(image + 0x154920)));
                pg(image + 0x3043f0, (double)f_timer_range_update(image + 0x2f3470));
                return;
            }
        }
        float longitudinal = f_timer_range_update(image + 0x3043e0),
              lateral = f_timer_range_update(image + 0x3043e4);
        float speed = ff(dependencies.movementSpeed(q_timer_range_update(ctx),
                                                    q_timer_range_update(ctx + 0x28), 0, 0));
        double motion[3];
        movementPrediction(motion, angles, longitudinal, lateral, speed, image, dependencies);
        memcpy(a, velocity, 24);
        recovered_geometry_add_9400(out, a, motion);
        memcpy(velocity, out, 24);
        memcpy(a, self, 24);
        memcpy(b, velocity, 24);
        recovered_geometry_add_9400(out, a, b);
        memcpy(self, out, 24);
        memcpy(a, velocity, 24);
        recovered_vector_scale_9430(out, a, damping);
        memcpy(velocity, out, 24);
        if (d_timer_range_update(image + 0x2f3410) == 1) {
            uint64_t result = dependencies.hypotenuse(q_timer_range_update(velocity),
                                                      q_timer_range_update(velocity + 2), 0, 0);
            double length = g_timer_range_update(&result);
            memcpy(a, self, 24);
            memcpy(b, desired, 24);
            recovered_vector_subtract_93d0(out, a, b);
            result = dependencies.hypotenuse(q_timer_range_update(out),
                                             q_timer_range_update(out + 2), 0, 0);
            double scale = divide(length, g_timer_range_update(&result));
            memcpy(a, out, 24);
            recovered_vector_scale_9430(b, a, scale);
            b[1] = 0.;
            memcpy(a, desired, 24);
            recovered_geometry_add_9400(out, a, b);
            memcpy(desired, out, 24);
        }
        if (target_ticks > 0) {
            memcpy(a, desired, 24);
            memcpy(b, position, 24);
            recovered_vector_subtract_93d0(out, a, b);
            memcpy(a, out, 24);
            recovered_vector_scale_9430(b, a, divide(target_factor, (double)target_ticks));
            memcpy(a, position, 24);
            recovered_geometry_add_9400(out, a, b);
            memcpy(position, out, 24);
            --target_ticks;
        }
    }
}

} // namespace timer_range
// END SOURCE modules/Timer_Range/timer_range_update.cpp

// Convenient borrowed-state interface

namespace shareable {
class TimerRange {
  public:
    static constexpr const char *kName = "Timer Range";
    static constexpr const char *kDescription = "Abuses timer lag to teleport you.";
    explicit TimerRange(std::uint8_t *image) : image_(image) {}
    // Mode. Config key: mode.
    ChoiceSetting &mode() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f33e0);
    }
    // Option labels observed in the captured metadata.
    enum class ModeMode : std::uint32_t { Regular = 0, Legit = 1 };
    // Minimum distance. Config key: min_dist.
    NumberSetting &min_dist() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f34e8);
    }
    // Duration. Config key: duration.
    NumberSetting &duration() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f3478);
    }
    // Duration. Config key: duration_legit.
    NumberSetting &duration_legit() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f34b0);
    }
    // Cooldown. Config key: cooldown.
    NumberSetting &cooldown() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f3440);
    }
    // Block while frozen. Config key: block_while_frozen.
    BooleanSetting &block_while_frozen() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f3420);
    }
    // Mouse pressed. Config key: require_mouse_pressed.
    BooleanSetting &require_mouse_pressed() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f3370);
    }
    // Holding weapon. Config key: require_weapon.
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f3390);
    }
    // Not using item. Config key: require_not_using_item.
    BooleanSetting &require_not_using_item() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f33b0);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_timer_range_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_timer_range_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_timer_range_settings(&context, image_, &dependencies);
    }
    static void bindKnown(::timer_range::Dependencies &dependencies, aim_assist::Runtime &runtime) {
        ::timer_range::bindKnown(dependencies, runtime);
    }
    static std::uint8_t isFrozen(const std::uint8_t *image) {
        return ::timer_range::isFrozen(image);
    }
    static void writeStatus(FormatState *format, char *destination, const std::uint8_t *image,
                            const char *const *labels) {
        ::timer_range::writeStatus(format, destination, image, labels);
    }
    void sampleMovementKeys(uint64_t game, uint64_t settings,
                            const ::timer_range::Dependencies &dependencies) {
        ::timer_range::sampleMovementKeys(game, settings, image_, dependencies);
    }
    void beginFreeze(uint8_t *ctx, const ::timer_range::Dependencies &dependencies) {
        ::timer_range::beginFreeze(ctx, image_, dependencies);
    }
    void onTick(uint8_t *event, const ::timer_range::Dependencies &dependencies) {
        ::timer_range::onTick(event, image_, dependencies);
    }
    void onPacket(uint8_t *event, const ::timer_range::Dependencies &dependencies) {
        ::timer_range::onPacket(event, image_, dependencies);
    }
    void onDisabled(uint8_t *event, const ::timer_range::Dependencies &dependencies) {
        ::timer_range::onDisabled(event, image_, dependencies);
    }
    void onRotationFrame(uint8_t *event, const ::timer_range::Dependencies &dependencies) {
        ::timer_range::onRotationFrame(event, image_, dependencies);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
