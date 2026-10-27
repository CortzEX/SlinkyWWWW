// Knockback Delay

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Knockback_Delay.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Knockback_Delay.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Knockback Delay: lib_win settings 0x465f0.
// UI 0x46530.
static constexpr UiStep ui_steps_Surface_Knockback_Delay[] = {
    {UiControl::section, "Main", 0},          {UiControl::number, nullptr, 0x2f4360},
    {UiControl::number, nullptr, 0x2f43f8},   {UiControl::number, nullptr, 0x2f4308},
    {UiControl::section, "Conditions", 0},    {UiControl::checkbox, nullptr, 0x2f4340},
    {UiControl::checkbox, nullptr, 0x2f43d8}, {UiControl::checkbox, nullptr, 0x2f43b8},
    {UiControl::checkbox, nullptr, 0x2f4398},
};
static constexpr SettingsStep settings_steps_Surface_Knockback_Delay[] = {
    {SettingsControl::number, "range", 0x2f4360},
    {SettingsControl::number, "chance", 0x2f43f8},
    {SettingsControl::number, "max_delay", 0x2f4308},
    {SettingsControl::boolean, "require_air", 0x2f4340},
    {SettingsControl::boolean, "require_target", 0x2f43d8},
    {SettingsControl::boolean, "require_mouse", 0x2f43b8},
    {SettingsControl::boolean, "require_weapon", 0x2f4398},
};
static constexpr ModuleSurface surface_Surface_Knockback_Delay{
    ui_steps_Surface_Knockback_Delay, std::size(ui_steps_Surface_Knockback_Delay),
    settings_steps_Surface_Knockback_Delay, std::size(settings_steps_Surface_Knockback_Delay)};

extern "C" __declspec(dllexport) void
recovered_knockback_delay_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                             const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Knockback_Delay, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_knockback_delay_settings(SettingsContext *context, std::uint8_t *image,
                                   const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Knockback_Delay, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Knockback_Delay.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Knockback_Delay
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Knockback_Delay.cpp
static constexpr UiStep surface_knockback_delay_ui_steps[] = {
    {UiControl::section, "Main", 0},          {UiControl::number, nullptr, 0x2f4360},
    {UiControl::number, nullptr, 0x2f43f8},   {UiControl::number, nullptr, 0x2f4308},
    {UiControl::section, "Conditions", 0},    {UiControl::checkbox, nullptr, 0x2f4340},
    {UiControl::checkbox, nullptr, 0x2f43d8}, {UiControl::checkbox, nullptr, 0x2f43b8},
    {UiControl::checkbox, nullptr, 0x2f4398},
};
static constexpr SettingsStep surface_knockback_delay_settings_steps[] = {
    {SettingsControl::number, "range", 0x2f4360},
    {SettingsControl::number, "chance", 0x2f43f8},
    {SettingsControl::number, "max_delay", 0x2f4308},
    {SettingsControl::boolean, "require_air", 0x2f4340},
    {SettingsControl::boolean, "require_target", 0x2f43d8},
    {SettingsControl::boolean, "require_mouse", 0x2f43b8},
    {SettingsControl::boolean, "require_weapon", 0x2f4398},
};
static constexpr ModuleSurface surface_knockback_delay_surface{
    surface_knockback_delay_ui_steps, std::size(surface_knockback_delay_ui_steps),
    surface_knockback_delay_settings_steps, std::size(surface_knockback_delay_settings_steps)};

extern "C" __declspec(dllexport) void
recovered_knockback_delay_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                                   const BoundSurfaceUiDependencies *dependencies) {
    render_module_surface(surface_knockback_delay_surface, ui, layout, image, *dependencies);
}
// END SOURCE shared/BoundSurfaces.cpp@Knockback_Delay

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Knockback_Delay/Bindings.cpp
#ifndef SLINKY_SHARE_EBCC92369978FA0FCCF3
#define SLINKY_SHARE_EBCC92369978FA0FCCF3
// BEGIN SOURCE modules/Knockback_Delay/Dependencies.hpp
#include <cstdint>
#include "../runtime/modules/Aim_Assist/Support.hpp"
#include "../runtime/shared/Geometry.hpp"
// Each endpoint has one named native role. The callback bodies contain the
// module algorithms. Unbound endpoints are listed in the module report.
namespace knockback_delay {
using Word = std::uint64_t;
struct Endpoint {
    void *context;
    Word (*function)(void *, Word, Word, Word, Word);
    Word operator()(Word a, Word b, Word c, Word d) const {
        return function(context, a, b, c, d);
    }
};
struct Dependencies {
    Endpoint distanceSquared;    // 0x94b0
    Endpoint rotationTo;         // 0x9f80
    Endpoint randomBounds;       // 0xa050
    Endpoint wrapAngle;          // 0xa210
    Endpoint randomGate;         // 0xaa30
    Endpoint entityPosition;     // 0x23030
    Endpoint entityRotation;     // 0x23170
    Endpoint entityId;           // 0x23720
    Endpoint entityOnGround;     // 0x23780
    Endpoint worldPlayers;       // 0x24600
    Endpoint listSize;           // 0x24e50
    Endpoint listElement;        // 0x24e80
    Endpoint velocityPacket;     // 0x266b0
    Endpoint velocityEntityId;   // 0x266f0
    Endpoint relativeMovePacket; // 0x26a30
    Endpoint headLookPacket;     // 0x26a90
    Endpoint teleportPacket;     // 0x26ad0
    Endpoint attackInput;        // 0x29080
    Endpoint weaponAllowed;      // 0x380b0
    Endpoint sameJavaObject;     // 0x800000c0
};
} // namespace knockback_delay
namespace knockback_delay {}

namespace knockback_delay {
void update(std::uint8_t *, std::uint8_t *, const Dependencies &);
void packet(std::uint8_t *, std::uint8_t *, const Dependencies &);
} // namespace knockback_delay

namespace knockback_delay {
void bindKnown(Dependencies &, aim_assist::Runtime &);
}
// END SOURCE modules/Knockback_Delay/Dependencies.hpp

#endif // SLINKY_SHARE_EBCC92369978FA0FCCF3

#include "../runtime/shared/JniAccess.hpp"
namespace knockback_delay {
using namespace recovered_jni;
void bindKnown(Dependencies &dependencies, aim_assist::Runtime &runtime) {
    dependencies.distanceSquared = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return doubleBits(recovered_vector_distance_squared(
                reinterpret_cast<const double *>(a), reinterpret_cast<const double *>(b)));
        }};
    dependencies.rotationTo = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                   auto *rt = static_cast<aim_assist::Runtime *>(user);
                                   return aim_assist::packed(aim_assist::angularRotation(
                                       *rt, *reinterpret_cast<const aim_assist::Vec3d *>(a),
                                       *reinterpret_cast<const aim_assist::Vec3d *>(b)));
                               }};
    dependencies.randomBounds = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                     return recovered_random_bounds(floatValue(a), floatValue(b));
                                 }};
    dependencies.wrapAngle = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return floatBits(static_cast<aim_assist::Runtime *>(user)->wrap(floatValue(a)));
        }};
    dependencies.randomGate = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                   auto *rt = static_cast<aim_assist::Runtime *>(user);
                                   return recovered_policy_gate(
                                       reinterpret_cast<SmoothRandomState *>(a), b, doubleValue(c),
                                       rt->random, rt->clock, rt->randomPolicyConstants);
                               }};
    dependencies.entityPosition = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return storedVector(a, aim_assist::mc::entityPosition(bridge(b), object(c)));
        }};
    dependencies.entityRotation = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return aim_assist::packed(aim_assist::mc::entityRotation(bridge(a), object(b)));
        }};
    dependencies.entityId = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                 return static_cast<std::uint32_t>(
                                     aim_assist::mc::entityNumericId(bridge(a), object(b)));
                             }};
    dependencies.entityOnGround = {&runtime,
                                   +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                       return field<std::uint8_t, 0x300>(bridge(a), b, 0x2f0) != 0;
                                   }};
    dependencies.worldPlayers = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return pointer(aim_assist::mc::worldPlayerEntityList(bridge(a), object(b)));
        }};
    dependencies.listSize = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                 return static_cast<std::uint32_t>(
                                     aim_assist::mc::javaListSize(bridge(a), object(b)));
                             }};
    dependencies.listElement = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                    return pointer(aim_assist::mc::javaListElement(
                                        bridge(a), object(b), static_cast<std::int32_t>(c)));
                                }};
    dependencies.velocityPacket = {&runtime,
                                   +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                       return instance(bridge(a), b, 0x788);
                                   }};
    dependencies.velocityEntityId = {&runtime,
                                     +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                         return field<std::uint32_t, 0x320>(bridge(a), b, 0x790);
                                     }};
    dependencies.relativeMovePacket = {&runtime,
                                       +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                           return instance(bridge(a), b, 0x850);
                                       }};
    dependencies.headLookPacket = {&runtime,
                                   +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                       return instance(bridge(a), b, 0x860);
                                   }};
    dependencies.teleportPacket = {&runtime,
                                   +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                       return instance(bridge(a), b, 0x868);
                                   }};
    dependencies.attackInput = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                    return aim_assist::attackInputDown(
                                        *reinterpret_cast<const aim_assist::Frame *>(a));
                                }};
    dependencies.weaponAllowed = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return static_cast<aim_assist::Runtime *>(user)->isWeapon(bridge(a), object(b));
        }};
    dependencies.sameJavaObject = {&runtime,
                                   +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                       using Query = std::uint8_t (*)(std::uintptr_t *, Word, Word);
                                       auto *environment = reinterpret_cast<std::uintptr_t *>(a);
                                       return slot<Query>(environment, 0xc0)(environment, b, c);
                                   }};
}
} // namespace knockback_delay
// END SOURCE modules/Knockback_Delay/Bindings.cpp

// BEGIN SOURCE modules/Knockback_Delay/knockback_delay_packet.cpp
#include <stdint.h>
#include <string.h>
#include <intrin.h>
namespace knockback_delay {

static uint64_t u64_knockback_delay_packet(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t u32_knockback_delay_packet(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static uint16_t u16(const void *p) {
    uint16_t v;
    memcpy(&v, p, 2);
    return v;
}
static void put32(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}

/* RVA 0x46140. State production in callback 0x46270 remains separate. */
void packet(uint8_t *event, uint8_t *image, const Dependencies &dependencies) {
    if (u32_knockback_delay_packet(event + 0x24))
        return;
    bool reset = false;
    const auto evaluate = [&] {
        uint64_t packet = dependencies.velocityPacket(
            u64_knockback_delay_packet(event + 8), u64_knockback_delay_packet(event + 0x10), 0, 0);
        uint8_t matches = 0;
        if (packet) {
            uint32_t id = (uint32_t)dependencies.velocityEntityId(
                u64_knockback_delay_packet(event + 8), packet, 0, 0);
            matches = (id == u32_knockback_delay_packet(image + 0x3049a4));
        }
        uint8_t active;
        if (image[0x3049a0] & 1) {
            active = u64_knockback_delay_packet(event + 0x18) == 0 ? (image[0x3049a1] & 1) : 0;
            image[0x304998] = active;
        } else if (image[0x3049a1] & matches & 1) {
            active = 1;
            image[0x304998] = 1;
        } else
            active = image[0x304998];
        if ((matches & active) == 1) {
            uint32_t saved = u32_knockback_delay_packet(image + 0x30499c),
                     stamp = u32_knockback_delay_packet(event + 0x20);
            if (saved && saved != stamp) {
                reset = true;
                return;
            }
            if (!saved)
                put32(image + 0x30499c, stamp);
        } else if (!active)
            return;
        uint64_t remaining_bits = u64_knockback_delay_packet(event + 0x18);
        int64_t remaining;
        memcpy(&remaining, &remaining_bits, 8);
        if (remaining > (int64_t)u16(image + 0x3049a2)) {
            reset = true;
            return;
        }
        uint32_t result = 1;
        if (dependencies.relativeMovePacket(u64_knockback_delay_packet(event + 8),
                                            u64_knockback_delay_packet(event + 0x10), 0, 0) ||
            dependencies.teleportPacket(u64_knockback_delay_packet(event + 8),
                                        u64_knockback_delay_packet(event + 0x10), 0, 0) ||
            dependencies.headLookPacket(u64_knockback_delay_packet(event + 8),
                                        u64_knockback_delay_packet(event + 0x10), 0, 0))
            result = 3;
        put32(event + 0x24, result);
        return;
    };
    evaluate();
    if (!reset)
        return;
    image[0x304998] = 0;
    _InterlockedExchange8((volatile char *)(image + 0x3049a1), 0);
    put32(image + 0x30499c, 0);
}

} // namespace knockback_delay
// END SOURCE modules/Knockback_Delay/knockback_delay_packet.cpp

// BEGIN SOURCE modules/Knockback_Delay/knockback_delay_update.cpp
#include <stdint.h>
#include <string.h>
#include <intrin.h>
#include <emmintrin.h>
namespace knockback_delay {

static uint64_t u64_knockback_delay_update(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t u32_knockback_delay_update(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static int32_t signed32(uint32_t v) {
    int32_t s;
    memcpy(&s, &v, 4);
    return s;
}
static float f32(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static double f64(const void *p) {
    double v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t fb(float v) {
    uint32_t b;
    memcpy(&b, &v, 4);
    return b;
}
static double from_db(uint64_t v) {
    return f64(&v);
}
static float from_fb(uint32_t v) {
    return f32(&v);
}

/* RVA 0x46270. The packet-side consumer is in ../knockback_delay_packet/. */
void update(uint8_t *event, uint8_t *image, const Dependencies &dependencies) {
    uint8_t *game = (uint8_t *)(uintptr_t)u64_knockback_delay_update(event + 8);
    uint64_t target = u64_knockback_delay_update(game + 0x28);
    if (!target)
        return;
    uint32_t id = (uint32_t)dependencies.entityId(u64_knockback_delay_update(game), target, 0, 0);
    _InterlockedExchange((volatile long *)(image + 0x3049a4), (long)id);
    uint8_t ground = 0;
    if (image[0x2f4358] == 1)
        ground = (uint8_t)dependencies.entityOnGround(
            u64_knockback_delay_update(game), u64_knockback_delay_update(game + 0x28), 0, 0);
    _InterlockedExchange8((volatile char *)(image + 0x3049a0), (char)ground);
    uint8_t allowed = 0;
    const auto evaluate = [&] {
        uint8_t *hit = (uint8_t *)(uintptr_t)u64_knockback_delay_update(game + 0x38);
        if (!u64_knockback_delay_update(hit + 8))
            return;
        float range = f32(image + 0x2f4390);
        if (f64(hit + 0x10) > (double)(range * range))
            return;
        if (image[0x2f43b0] == 1 &&
            !(uint8_t)dependencies.weaponAllowed(u64_knockback_delay_update(game),
                                                 u64_knockback_delay_update(game + 0x28), 0, 0))
            return;
        if (image[0x2f43d0] == 1 && !(uint8_t)dependencies.attackInput((uintptr_t)game, 0, 0, 0))
            return;
        if (image[0x2f43f0] == 1) {
            double player[3];
            dependencies.entityPosition((uintptr_t)player, u64_knockback_delay_update(game),
                                        u64_knockback_delay_update(game + 0x28), 0);
            float yaw = from_fb((uint32_t)dependencies.entityRotation(
                u64_knockback_delay_update(game), u64_knockback_delay_update(game + 0x28), 0, 0));
            uint64_t list = dependencies.worldPlayers(
                u64_knockback_delay_update(game), u64_knockback_delay_update(game + 0x20), 0, 0);
            int32_t count = signed32(
                (uint32_t)dependencies.listSize(u64_knockback_delay_update(game), list, 0, 0));
            if (count <= 0)
                return;
            double distance_limit = f64(image + 0x154fa0);
            uint32_t abs_mask = u32_knockback_delay_update(image + 0x154fb0);
            float angle_limit = f32(image + 0x154fc0);
            uint32_t index = 0;
            for (;;) {
                uint64_t entity =
                    dependencies.listElement(u64_knockback_delay_update(game), list, index, 0);
                uint8_t *bridge = (uint8_t *)(uintptr_t)u64_knockback_delay_update(game);
                uint64_t interface_pointer = u64_knockback_delay_update(bridge + 8);
                if (!(uint8_t)dependencies.sameJavaObject(
                        interface_pointer, u64_knockback_delay_update(game + 0x28), entity, 0)) {
                    double first[3], enemy[3], a[3], b[3];
                    memcpy(first, player, 24);
                    dependencies.entityPosition((uintptr_t)enemy, u64_knockback_delay_update(game),
                                                entity, 0);
                    memcpy(a, first, 24);
                    memcpy(b, enemy, 24);
                    double distance =
                        from_db(dependencies.distanceSquared((uintptr_t)a, (uintptr_t)b, 0, 0));
                    if (!(distance > distance_limit)) {
                        memcpy(a, first, 24);
                        memcpy(b, enemy, 24);
                        float angle = from_fb(
                            (uint32_t)dependencies.rotationTo((uintptr_t)a, (uintptr_t)b, 0, 0));
                        float delta = angle - yaw;
                        uint32_t wrapped = (uint32_t)dependencies.wrapAngle(fb(delta), 0, 0, 0);
                        if (!(from_fb(wrapped & abs_mask) > angle_limit))
                            break;
                    }
                }
                ++index;
                count = signed32(
                    (uint32_t)dependencies.listSize(u64_knockback_delay_update(game), list, 0, 0));
                if (signed32(index) >= count)
                    return;
            }
        }
        {
            double chance = (double)f32(image + 0x2f4428);
            allowed = 1;
            if (!(chance > f64(image + 0x154fc8))) {
                float low = (float)(f64(image + 0x154fd0) + chance);
                float high = (float)(chance + f64(image + 0x154fd8));
                uint64_t draw = dependencies.randomBounds(fb(low), fb(high), 0, 0);
                allowed = (uint8_t)dependencies.randomGate(
                    (uintptr_t)(image + 0x3049a8), draw,
                    u64_knockback_delay_update(image + 0x154fe0), 0);
            }
        }
    };
    evaluate();
    _InterlockedExchange8((volatile char *)(image + 0x3049a1), (char)allowed);
    int32_t delay = _mm_cvttss_si32(_mm_set_ss(f32(image + 0x2f4338)));
    _InterlockedExchange16((volatile short *)(image + 0x3049a2), (short)delay);
}

} // namespace knockback_delay
// END SOURCE modules/Knockback_Delay/knockback_delay_update.cpp

// BEGIN SOURCE modules/Knockback_Delay/Surface.cpp
#ifndef SLINKY_SHARE_C91A19FD5B2E64EB10BB
#define SLINKY_SHARE_C91A19FD5B2E64EB10BB
// BEGIN SOURCE modules/Knockback_Delay/Surface.hpp
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/native/verified/module_format.hpp"
namespace knockback_delay {
void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                    const BoundSurfaceUiDependencies &);
void serializeConfig(SettingsContext &, std::uint8_t *image, const SurfaceSettingsDependencies &);
void writeStatus(FormatState *, char *destination, const std::uint8_t *image);
} // namespace knockback_delay
// END SOURCE modules/Knockback_Delay/Surface.hpp

#endif // SLINKY_SHARE_C91A19FD5B2E64EB10BB

extern "C" void recovered_knockback_delay_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                                   const BoundSurfaceUiDependencies *);
extern "C" void recovered_knockback_delay_settings(SettingsContext *, std::uint8_t *,
                                                   const SurfaceSettingsDependencies *);
namespace knockback_delay {
void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                    const BoundSurfaceUiDependencies &dependencies) {
    recovered_knockback_delay_bound_ui(ui, layout, image, &dependencies);
}
void serializeConfig(SettingsContext &context, std::uint8_t *image,
                     const SurfaceSettingsDependencies &dependencies) {
    recovered_knockback_delay_settings(&context, image, &dependencies);
}
void writeStatus(FormatState *format, char *destination, const std::uint8_t *image) {
    recovered_format(format, destination, 0x20, "%.0fms",
                     static_cast<double>(read_surface_value<float>(image, 0x2f4338)));
}
} // namespace knockback_delay
// END SOURCE modules/Knockback_Delay/Surface.cpp

// Convenient borrowed-state interface

namespace shareable {
class KnockbackDelay {
  public:
    static constexpr const char *kName = "Knockback Delay";
    static constexpr const char *kDescription = "Delays your knockback in certain scenarios.";
    explicit KnockbackDelay(std::uint8_t *image) : image_(image) {}
    // Distance to target. Config key: range.
    NumberSetting &range() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f4360);
    }
    // Chance. Config key: chance.
    NumberSetting &chance() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f43f8);
    }
    // Maximum delay. Config key: max_delay.
    NumberSetting &max_delay() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f4308);
    }
    // In air. Config key: require_air.
    BooleanSetting &require_air() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4340);
    }
    // Looking at player. Config key: require_target.
    BooleanSetting &require_target() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f43d8);
    }
    // Mouse pressed. Config key: require_mouse.
    BooleanSetting &require_mouse() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f43b8);
    }
    // Holding weapon. Config key: require_weapon.
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4398);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_knockback_delay_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_knockback_delay_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_knockback_delay_settings(&context, image_, &dependencies);
    }
    static void bindKnown(::knockback_delay::Dependencies &dependencies,
                          aim_assist::Runtime &runtime) {
        ::knockback_delay::bindKnown(dependencies, runtime);
    }
    void packet(uint8_t *event, const ::knockback_delay::Dependencies &dependencies) {
        ::knockback_delay::packet(event, image_, dependencies);
    }
    void update(uint8_t *event, const ::knockback_delay::Dependencies &dependencies) {
        ::knockback_delay::update(event, image_, dependencies);
    }
    static void writeStatus(FormatState *format, char *destination, const std::uint8_t *image) {
        ::knockback_delay::writeStatus(format, destination, image);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
