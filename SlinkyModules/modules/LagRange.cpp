// Lag Range

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Lag_Range.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Lag_Range.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Lag Range: lib_win settings 0x3ac00.
static constexpr SettingsStep settings_steps_Surface_Lag_Range[] = {
    {SettingsControl::number, "delay", 0x2efc48},
    {SettingsControl::boolean, "flush_sprint_reset", 0x2efcc0},
    {SettingsControl::boolean, "flush_splash_potion", 0x2efca0},
    {SettingsControl::boolean, "render_remote_pos", 0x2efce0},
    {SettingsControl::color, "indicator_color", 0x2efc08},
    {SettingsControl::number, "indicator_line_width", 0x2efbd0},
    {SettingsControl::boolean, "indicator_filled", 0x2efc28},
    {SettingsControl::boolean, "require_weapon", 0x2efc80},
};
static constexpr ModuleSurface surface_Surface_Lag_Range{
    nullptr, 0, settings_steps_Surface_Lag_Range, std::size(settings_steps_Surface_Lag_Range)};

extern "C" __declspec(dllexport) void
recovered_lag_range_settings(SettingsContext *context, std::uint8_t *image,
                             const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Lag_Range, context, image, *dependencies);
}

// Lag Range: lib_win runtime UI 0x3ab00.
extern "C" __declspec(dllexport) void
recovered_lag_range_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                       const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2efc48);
    dependencies->section(ui, layout, "Flush if");
    dependencies->checkbox(layout, ui, image + 0x2efcc0);
    dependencies->checkbox(layout, ui, image + 0x2efca0);
    dependencies->section(ui, layout, "Real position indicator");
    dependencies->checkbox(layout, ui, image + 0x2efce0);
    if (image[0x2efcf8] == 1) {
        dependencies->color(layout, ui, image + 0x2efc08);
        dependencies->number(layout, ui, image + 0x2efbd0);
        dependencies->checkbox(layout, ui, image + 0x2efc28);
    }
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2efc80);
}
// END SOURCE native/verified/surfaces/Surface_Lag_Range.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Lag_Range
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Lag_Range.cpp
extern "C" __declspec(dllexport) void
recovered_lag_range_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                             const BoundSurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2efc48);
    dependencies->section(ui, layout, "Flush if");
    dependencies->checkbox(layout, ui, image + 0x2efcc0);
    dependencies->checkbox(layout, ui, image + 0x2efca0);
    dependencies->section(ui, layout, "Real position indicator");
    dependencies->checkbox(layout, ui, image + 0x2efce0);
    if (image[0x2efcf8] == 1) {
        dependencies->color(layout, ui, image + 0x2efc08);
        dependencies->number(layout, ui, image + 0x2efbd0);
        dependencies->checkbox(layout, ui, image + 0x2efc28);
    }
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2efc80);
}
// END SOURCE shared/BoundSurfaces.cpp@Lag_Range

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Lag_Range/Bindings.cpp
#ifndef SLINKY_SHARE_15E3DBAD089DFF1867F4
#define SLINKY_SHARE_15E3DBAD089DFF1867F4
// BEGIN SOURCE modules/Lag_Range/Dependencies.hpp
#include <cstdint>
#include "../runtime/modules/Aim_Assist/Support.hpp"
#include "../runtime/shared/Geometry.hpp"
// Each endpoint has one named native role. The callback bodies contain the
// module algorithms. Unbound endpoints are listed in the module report.
namespace lag_range {
using Word = std::uint64_t;
struct Endpoint {
    void *context;
    Word (*function)(void *, Word, Word, Word, Word);
    Word operator()(Word a, Word b, Word c, Word d) const {
        return function(context, a, b, c, d);
    }
};
struct GraphicsEndpoint {
    void *context;
    Word (*function)(void *, Word, Word, Word, Word, Word);
    Word operator()(Word target, Word a, Word b, Word c, Word d) const {
        return function(context, target, a, b, c, d);
    }
};
struct Dependencies {
    Endpoint adjustPositionY;                              // 0x95c0
    Endpoint randomBounds;                                 // 0xa050
    Endpoint smoothRandom;                                 // 0xa510
    Endpoint clientOptions;                                // 0x22cf0
    Endpoint positionModeIsZero;                           // 0x23020
    Endpoint entityPosition;                               // 0x23030
    Endpoint entitySprinting;                              // 0x23690
    Endpoint entityTicks;                                  // 0x23760
    Endpoint lastAttackerTime;                             // 0x239d0
    Endpoint entityHurtTime;                               // 0x239f0
    Endpoint inventory;                                    // 0x23f40
    Endpoint serverPosition;                               // 0x24160
    Endpoint viewMode;                                     // 0x25310
    Endpoint selectedSlot;                                 // 0x25a60
    Endpoint itemId;                                       // 0x25c50
    Endpoint stackDamage;                                  // 0x25dc0
    Endpoint inventoryItem;                                // 0x26140
    Endpoint movementPacket;                               // 0x26350
    Endpoint movementHasPosition;                          // 0x26390
    Endpoint movementPosition;                             // 0x26450
    Endpoint attackPacket;                                 // 0x265e0
    Endpoint entityActionPacket;                           // 0x26620
    Endpoint entityActionCode;                             // 0x26660
    Endpoint heldItem;                                     // 0x28a50
    Endpoint weaponAllowed;                                // 0x380b0
    Endpoint beginBox, drawFilledBox, drawWireBox, endBox; // 293c0,29400,29430,295a0
    GraphicsEndpoint
        graphics; // external engine target plus argument bits; render order remains explicit
};
} // namespace lag_range
namespace lag_range {
void packet(uint8_t *event, uint8_t *image, const Dependencies &dependencies);
void input(uint8_t *event, uint8_t *image, const Dependencies &dependencies);
void render(uint8_t *event, uint8_t *image, const Dependencies &dependencies);
void update(uint8_t *event, uint8_t *image, const Dependencies &dependencies);
} // namespace lag_range

namespace lag_range {
void bindKnown(Dependencies &, aim_assist::Runtime &);
}
#include "../runtime/modules/Backtrack/BoxRender.hpp"
namespace lag_range {
void bindRender(Dependencies &, box_render::Context &);
}
// END SOURCE modules/Lag_Range/Dependencies.hpp

#endif // SLINKY_SHARE_15E3DBAD089DFF1867F4

#include "../runtime/shared/JniAccess.hpp"
namespace lag_range {
using namespace recovered_jni;
void bindKnown(Dependencies &dependencies, aim_assist::Runtime &runtime) {
    dependencies.adjustPositionY = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            auto *rt = static_cast<aim_assist::Runtime *>(user);
            return reinterpret_cast<Word>(recovered_vector_adjust_95c0(
                reinterpret_cast<double *>(a), reinterpret_cast<const double *>(b), rt->image));
        }};
    dependencies.randomBounds = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                     return recovered_random_bounds(floatValue(a), floatValue(b));
                                 }};
    dependencies.smoothRandom = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                     auto *rt = static_cast<aim_assist::Runtime *>(user);
                                     return recovered_policy_smooth_bits(
                                         reinterpret_cast<SmoothRandomState *>(a), b,
                                         doubleValue(c), rt->random, rt->clock,
                                         rt->randomPolicyConstants);
                                 }};
    dependencies.clientOptions = {&runtime,
                                  +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                      return recovered_access_helper(bridge(a), 0x22cf0, b, 0, 0);
                                  }};
    dependencies.positionModeIsZero = {&runtime,
                                       +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                           return aim_assist::mc::positionModeIsZero(bridge(a));
                                       }};
    dependencies.entityPosition = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return storedVector(a, aim_assist::mc::entityPosition(bridge(b), object(c)));
        }};
    dependencies.entitySprinting = {&runtime,
                                    +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                        return recovered_game_sprinting(bridge(a), b);
                                    }};
    dependencies.entityTicks = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                    return field<std::uint32_t, 0x320>(bridge(a), b, 0x2d8);
                                }};
    dependencies.lastAttackerTime = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return static_cast<std::uint32_t>(recovered_game_last_attacker_time(bridge(a), b));
        }};
    dependencies.entityHurtTime = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return static_cast<std::uint32_t>(aim_assist::mc::entityHurtTime(bridge(a), object(b)));
        }};
    dependencies.inventory = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                  return recovered_game_inventory(bridge(a), b);
                              }};
    dependencies.serverPosition = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return storedVector(
                a, aim_assist::mc::entityOtherPlayerServerPosition(bridge(b), object(c)));
        }};
    dependencies.viewMode = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                 return field<std::uint32_t, 0x320>(bridge(a), b, 0x3c0);
                             }};
    dependencies.selectedSlot = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                     return static_cast<std::uint32_t>(
                                         recovered_game_inventory_index(bridge(a), b));
                                 }};
    dependencies.itemId = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                               return static_cast<std::uint32_t>(
                                   recovered_game_item_numeric_id(bridge(a), b));
                           }};
    dependencies.stackDamage = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                    return field<std::uint32_t, 0x320>(bridge(a), b, 0x630);
                                }};
    dependencies.inventoryItem = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return indexedMethod(bridge(a), b, 0x6e0, static_cast<std::uint32_t>(c));
        }};
    dependencies.movementPacket = {&runtime,
                                   +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                       return instance(bridge(a), b, 0x708);
                                   }};
    dependencies.movementHasPosition = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return field<std::uint8_t, 0x300>(bridge(a), b, 0x710) != 0;
        }};
    dependencies.movementPosition = {&runtime,
                                     +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                         return getPosition(a, b, c, 0x720);
                                     }};
    dependencies.attackPacket = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                     return instance(bridge(a), b, 0xa28);
                                 }};
    dependencies.entityActionPacket = {&runtime,
                                       +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                           return instance(bridge(a), b, 0xa30);
                                       }};
    dependencies.entityActionCode = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            if (aim_assist::mc::positionModeIsZero(bridge(a)))
                return field<std::uint32_t, 0x320>(bridge(a), b, 0xa38);
            const auto value = objectField(bridge(a), b, 0xa38);
            return recovered_access_helper(bridge(a), 0x271a0, value, 0, 0);
        }};
    dependencies.heldItem = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                 return recovered_game_item_object(bridge(a), b);
                             }};
    dependencies.weaponAllowed = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return static_cast<aim_assist::Runtime *>(user)->isWeapon(bridge(a), object(b));
        }};
}
} // namespace lag_range
// END SOURCE modules/Lag_Range/Bindings.cpp

// BEGIN SOURCE modules/Lag_Range/lag_range_packet.cpp
#include <stdint.h>
#include <string.h>
#include <intrin.h>
namespace lag_range {
static uint64_t u64_lag_range_packet(const void *p) {
    return *(const volatile uint64_t *)p;
}
static uint32_t u32_lag_range_packet(const void *p) {
    return *(const volatile uint32_t *)p;
}
static int32_t s32_lag_range_packet(uint32_t b) {
    int32_t v;
    memcpy(&v, &b, 4);
    return v;
}
static int64_t s64(uint64_t b) {
    int64_t v;
    memcpy(&v, &b, 8);
    return v;
}
static void put32_lag_range_packet(void *p, uint32_t v) {
    *(volatile uint32_t *)p = v;
}

void packet(uint8_t *event, uint8_t *image, const Dependencies &dependencies) {
    volatile uint8_t *state = image;
    while (_InterlockedExchange8((volatile char *)(image + 0x2fc7c8), 1))
        _mm_pause();
    const auto evaluate = [&] {
        uint8_t active = state[0x2fc7f8];
        if (s32_lag_range_packet(u32_lag_range_packet(event + 0x20)) >
            s32_lag_range_packet(u32_lag_range_packet(image + 0x2fc7c0))) {
            if (active) {
                uint64_t packet = dependencies.movementPacket(
                    u64_lag_range_packet(event + 8), u64_lag_range_packet(event + 0x10), 0, 0);
                if (packet && (uint8_t)dependencies.movementHasPosition(
                                  u64_lag_range_packet(event + 8), packet, 0, 0)) {
                    double position[3], target[3], previous[3];
                    dependencies.movementPosition((uintptr_t)position,
                                                  u64_lag_range_packet(event + 8), packet, 0);
                    memcpy(target, image + 0x2fc7e0, 24);
                    memcpy(previous, image + 0x2fc808, 24);
                    double before = recovered_vector_distance_squared(target, previous);
                    memcpy(target, image + 0x2fc7e0, 24);
                    double after = recovered_vector_distance_squared(target, position);
                    state[0x2fc7d8] = before > after;
                }
            }
            put32_lag_range_packet(image + 0x2fc7c0, u32_lag_range_packet(event + 0x20));
            active = state[0x2fc7f8];
        }
        if (active && state[0x2fc7d8] && !state[0x2fc7d9] && !state[0x2fc7db] && !state[0x2fc7da] &&
            s64(u64_lag_range_packet(event + 0x18)) < s64(u64_lag_range_packet(image + 0x2fc7d0))) {
            put32_lag_range_packet(event + 0x24, 1);
            return;
        }
        if (u32_lag_range_packet(event + 0x24))
            return;
        {
            uint64_t packet = dependencies.movementPacket(u64_lag_range_packet(event + 8),
                                                          u64_lag_range_packet(event + 0x10), 0, 0);
            if (packet) {
                state[0x2fc7db] = 0;
                if ((uint8_t)dependencies.movementHasPosition(u64_lag_range_packet(event + 8),
                                                              packet, 0, 0)) {
                    double position[3];
                    dependencies.movementPosition((uintptr_t)position,
                                                  u64_lag_range_packet(event + 8), packet, 0);
                    memcpy(image + 0x2fc808, position, 24);
                }
                return;
            }
            packet = dependencies.attackPacket(u64_lag_range_packet(event + 8),
                                               u64_lag_range_packet(event + 0x10), 0, 0);
            if (packet) {
                if (state[0x2fc7d9]) {
                    state[0x2fc7d9] = 0;
                    state[0x2fc7db] = 1;
                }
                return;
            }
            packet = dependencies.entityActionPacket(u64_lag_range_packet(event + 8),
                                                     u64_lag_range_packet(event + 0x10), 0, 0);
            if (packet && state[0x2fc7da] &&
                (uint32_t)dependencies.entityActionCode(u64_lag_range_packet(event + 8), packet, 0,
                                                        0) == 4)
                *(volatile uint16_t *)(image + 0x2fc7da) = 0x100;
        }
    };
    evaluate();
    state[0x2fc7c8] = 0;
}

void input(uint8_t *event, uint8_t *image, const Dependencies &dependencies) {
    if (event[0x10] != 1)
        return;
    uint8_t *ctx = (uint8_t *)(uintptr_t)u64_lag_range_packet(event + 8);
    uint32_t current = (uint32_t)dependencies.entityTicks(u64_lag_range_packet(ctx),
                                                          u64_lag_range_packet(ctx + 0x28), 0, 0);
    uint32_t previous = (uint32_t)dependencies.lastAttackerTime(
        u64_lag_range_packet(ctx), u64_lag_range_packet(ctx + 0x28), 0, 0);
    image[0x2fc858] = current == previous;
}

} // namespace lag_range
// END SOURCE modules/Lag_Range/lag_range_packet.cpp

// BEGIN SOURCE modules/Lag_Range/lag_range_render.cpp
#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
namespace lag_range {
static uint64_t u64_lag_range_render(const void *p) {
    return *(const volatile uint64_t *)p;
}
static uint32_t u32_lag_range_render(const void *p) {
    return *(const volatile uint32_t *)p;
}
static float f32_lag_range_render(const void *p) {
    uint32_t b = u32_lag_range_render(p);
    float v;
    memcpy(&v, &b, 4);
    return v;
}
static double f64_lag_range_render(const void *p) {
    uint64_t b = u64_lag_range_render(p);
    double v;
    memcpy(&v, &b, 8);
    return v;
}
static uint32_t fb(float v) {
    uint32_t b;
    memcpy(&b, &v, 4);
    return b;
}
static uint64_t method(uint8_t *image, uint32_t slot) {
    return u64_lag_range_render((void *)(uintptr_t)u64_lag_range_render(image + slot));
}

void render(uint8_t *event, uint8_t *image, const Dependencies &dependencies) {
    if (image[0x2fc820] != 1)
        return;
    double fraction = (double)f32_lag_range_render(event + 0x28);
    double previous[3], current[3], position[3], camera[3], relative[3];
    memcpy(previous, image + 0x2fc828, 24);
    memcpy(current, image + 0x2fc840, 24);
    recovered_vector_lerp_9460(position, previous, current, fraction);
    memcpy(camera, event + 8, 24);
    recovered_vector_subtract_93d0(relative, position, camera);
    dependencies.beginBox(0, 0, 0, 0);
    dependencies.graphics(method(image, 0x150cb0), u32_lag_range_render(image + 0x2efc00), 0, 0, 0);
    dependencies.graphics(method(image, 0x150cc0), 0, 0, 0, 0);
    dependencies.graphics(method(image, 0x150cd8), fb((float)relative[0]),
                          fb((float)(relative[1] + f64_lag_range_render(image + 0x152ed8))),
                          fb((float)relative[2]), 0);
    dependencies.graphics(method(image, 0x150cd0), u32_lag_range_render(image + 0x152ee4),
                          u32_lag_range_render(image + 0x152ee0),
                          u32_lag_range_render(image + 0x152ee4), 0);
    if (image[0x2efc40] == 1) {
        dependencies.graphics(method(image, 0x13e448), u32_lag_range_render(image + 0x2efc10),
                              u32_lag_range_render(image + 0x2efc14),
                              u32_lag_range_render(image + 0x2efc18),
                              u32_lag_range_render(image + 0x152ee8));
        dependencies.drawFilledBox(0, 0, 0, 0);
    }
    dependencies.graphics(method(image, 0x150ca0), u32_lag_range_render(image + 0x2efc10),
                          u32_lag_range_render(image + 0x2efc14),
                          u32_lag_range_render(image + 0x2efc18), 0);
    dependencies.drawWireBox(0, 0, 0, 0);
    dependencies.graphics(method(image, 0x150cb8), 0, 0, 0, 0);
    dependencies.endBox(0, 0, 0, 0);
}

} // namespace lag_range
// END SOURCE modules/Lag_Range/lag_range_render.cpp

// BEGIN SOURCE modules/Lag_Range/lag_range_update.cpp
#include <stdint.h>
#include <string.h>
#include <intrin.h>
#include <emmintrin.h>
namespace lag_range {
static uint64_t u64_lag_range_update(const void *p) {
    return *(const volatile uint64_t *)p;
}
static uint32_t u32_lag_range_update(const void *p) {
    return *(const volatile uint32_t *)p;
}
static int32_t s32_lag_range_update(uint32_t b) {
    int32_t v;
    memcpy(&v, &b, 4);
    return v;
}
static float f32_lag_range_update(const void *p) {
    uint32_t b = u32_lag_range_update(p);
    float v;
    memcpy(&v, &b, 4);
    return v;
}
static double f64_lag_range_update(const void *p) {
    uint64_t b = u64_lag_range_update(p);
    double v;
    memcpy(&v, &b, 8);
    return v;
}
static void put32_lag_range_update(void *p, uint32_t v) {
    *(volatile uint32_t *)p = v;
}
static void lock(uint8_t *image) {
    while (_InterlockedExchange8((volatile char *)(image + 0x2fc7c8), 1))
        _mm_pause();
}

void update(uint8_t *event, uint8_t *image, const Dependencies &dependencies) {
    volatile uint8_t *state = image;
    uint8_t input = state[0x2fc858];
    state[0x2fc858] = 0;
    uint8_t *ctx = (uint8_t *)(uintptr_t)u64_lag_range_update(event + 8);
    bool accepted = false;
    const auto evaluate = [&] {
        if (ctx[0x40] != 1)
            return;
        if (state[0x2efc98] == 1 &&
            !(uint8_t)dependencies.weaponAllowed(u64_lag_range_update(ctx),
                                                 u64_lag_range_update(ctx + 0x28), 0, 0))
            return;
        if (state[0x2efcb8] == 1) {
            uint64_t inventory = dependencies.inventory(u64_lag_range_update(ctx),
                                                        u64_lag_range_update(ctx + 0x28), 0, 0);
            uint32_t slot =
                (uint32_t)dependencies.selectedSlot(u64_lag_range_update(ctx), inventory, 0, 0);
            uint64_t stack =
                dependencies.inventoryItem(u64_lag_range_update(ctx), inventory, slot, 0);
            if (stack) {
                uint64_t item = dependencies.heldItem(u64_lag_range_update(ctx),
                                                      u64_lag_range_update(ctx + 0x28), 0, 0);
                if (item &&
                    (uint32_t)dependencies.itemId(u64_lag_range_update(ctx), item, 0, 0) == 0x175 &&
                    ((uint32_t)dependencies.stackDamage(u64_lag_range_update(ctx), stack, 0, 0) &
                     0x4000)) {
                    put32_lag_range_update(image + 0x2fc85c, 15);
                    return;
                }
            }
            uint32_t cooldown = u32_lag_range_update(image + 0x2fc85c);
            if (s32_lag_range_update(cooldown) > 0) {
                put32_lag_range_update(image + 0x2fc85c, cooldown - 1);
                return;
            }
        }
        uint8_t sprint = (uint8_t)dependencies.entitySprinting(
            u64_lag_range_update(ctx), u64_lag_range_update(ctx + 0x28), 0, 0);
        uint32_t sprint_delay = (state[0x2fc859] & 1) ? u32_lag_range_update(image + 0x2efcd8) : 0;
        if (sprint)
            sprint_delay = 0;
        state[0x2fc859] = sprint;
        double position[3];
        dependencies.entityPosition((uintptr_t)position, u64_lag_range_update(ctx),
                                    u64_lag_range_update(ctx + 0x28), 0);
        if ((uint8_t)dependencies.positionModeIsZero(u64_lag_range_update(ctx), 0, 0, 0)) {
            double copy[3], adjusted[3];
            memcpy(copy, position, 24);
            dependencies.adjustPositionY((uintptr_t)adjusted, (uintptr_t)copy, 0, 0);
            memcpy(position, adjusted, 24);
        }
        uint8_t *target = (uint8_t *)(uintptr_t)u64_lag_range_update(ctx + 0x38);
        if (!u64_lag_range_update(target + 8))
            return;
        double distance = f64_lag_range_update(target + 0x10);
        uint64_t random = dependencies.randomBounds(u32_lag_range_update(image + 0x152ef0),
                                                    u32_lag_range_update(image + 0x152ef4), 0, 0);
        uint32_t radius_bits = (uint32_t)dependencies.smoothRandom(
            (uintptr_t)(image + 0x2fc860), random, u64_lag_range_update(image + 0x152ef8), 0);
        double radius = (double)f32_lag_range_update(&radius_bits);
        if (distance > radius * radius)
            return;
        uint8_t fresh = s32_lag_range_update((uint32_t)dependencies.entityHurtTime(
                            u64_lag_range_update(ctx), u64_lag_range_update(target + 8), 0, 0)) < 5;
        uint8_t render = 0;
        if (state[0x2efcf8] == 1) {
            uint64_t view = dependencies.clientOptions(u64_lag_range_update(ctx),
                                                       u64_lag_range_update(ctx + 0x18), 0, 0);
            render = (uint32_t)dependencies.viewMode(u64_lag_range_update(ctx), view, 0, 0) != 0;
        }
        input &= fresh;
        double target_position[3];
        dependencies.serverPosition((uintptr_t)target_position, u64_lag_range_update(ctx),
                                    u64_lag_range_update(target + 8), 0);
        lock(image);
        *(volatile uint64_t *)(image + 0x2fc7d0) =
            (uint64_t)_mm_cvttss_si64(_mm_set_ss(f32_lag_range_update(image + 0x2efc78)));
        state[0x2fc7d9] = input;
        state[0x2fc7da] = (uint8_t)sprint_delay;
        state[0x2fc7f8] = 1;
        memcpy(image + 0x2fc7e0, target_position, 24);
        memcpy(image + 0x2fc828, image + (state[0x2fc820] == 1 ? 0x2fc840 : 0x2fc808), 24);
        memcpy(image + 0x2fc840, image + 0x2fc808, 24);
        state[0x2fc820] = render ? (uint8_t)u32_lag_range_update(image + 0x2fc7d8) : 0;
        state[0x2fc7c8] = 0;
        accepted = true;
        return;
    };
    evaluate();
    if (accepted)
        return;
    lock(image);
    state[0x2fc7db] = 0;
    *(volatile uint16_t *)(image + 0x2fc7d9) = 0;
    state[0x2fc7f8] = 0;
    state[0x2fc7c8] = 0;
    state[0x2fc820] = 0;
}

} // namespace lag_range
// END SOURCE modules/Lag_Range/lag_range_update.cpp

// BEGIN SOURCE modules/Lag_Range/RenderBindings.cpp
namespace lag_range {
void bindRender(Dependencies &dependencies, box_render::Context &context) {
    dependencies.beginBox = {&context, +[](void *user, Word, Word, Word, Word) -> Word {
                                 auto &c = *static_cast<box_render::Context *>(user);
                                 return recovered_render_293c0(c.constantImage, c.engine);
                             }};
    dependencies.drawFilledBox = {&context, +[](void *user, Word, Word, Word, Word) -> Word {
                                      auto &c = *static_cast<box_render::Context *>(user);
                                      return recovered_render_29400(c.constantImage, c.engine);
                                  }};
    dependencies.drawWireBox = {&context, +[](void *user, Word, Word, Word, Word) -> Word {
                                    auto &c = *static_cast<box_render::Context *>(user);
                                    return recovered_render_29430(c.constantImage, c.engine);
                                }};
    dependencies.endBox = {&context, +[](void *user, Word, Word, Word, Word) -> Word {
                               auto &c = *static_cast<box_render::Context *>(user);
                               return recovered_render_295a0(c.constantImage, c.engine);
                           }};
    dependencies.graphics = {
        &context, +[](void *user, Word target, Word a, Word b, Word c, Word d) -> Word {
            return static_cast<box_render::Context *>(user)->engine(target, a, b, c, d);
        }};
}
} // namespace lag_range
// END SOURCE modules/Lag_Range/RenderBindings.cpp

// BEGIN SOURCE modules/Lag_Range/Surface.cpp
#ifndef SLINKY_SHARE_52A406DE7D7C6BA74950
#define SLINKY_SHARE_52A406DE7D7C6BA74950
// BEGIN SOURCE modules/Lag_Range/Surface.hpp
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/native/verified/module_format.hpp"
namespace lag_range {
void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                    const BoundSurfaceUiDependencies &);
void serializeConfig(SettingsContext &, std::uint8_t *image, const SurfaceSettingsDependencies &);
void writeStatus(FormatState *, char *destination, const std::uint8_t *image);
} // namespace lag_range
// END SOURCE modules/Lag_Range/Surface.hpp

#endif // SLINKY_SHARE_52A406DE7D7C6BA74950

extern "C" void recovered_lag_range_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                             const BoundSurfaceUiDependencies *);
extern "C" void recovered_lag_range_settings(SettingsContext *, std::uint8_t *,
                                             const SurfaceSettingsDependencies *);
namespace lag_range {
void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                    const BoundSurfaceUiDependencies &dependencies) {
    recovered_lag_range_bound_ui(ui, layout, image, &dependencies);
}
void serializeConfig(SettingsContext &context, std::uint8_t *image,
                     const SurfaceSettingsDependencies &dependencies) {
    recovered_lag_range_settings(&context, image, &dependencies);
}
void writeStatus(FormatState *format, char *destination, const std::uint8_t *image) {
    recovered_format(format, destination, 0x20, "%.0fms",
                     static_cast<double>(read_surface_value<float>(image, 0x2efc78)));
}
} // namespace lag_range
// END SOURCE modules/Lag_Range/Surface.cpp

// Convenient borrowed-state interface

namespace shareable {
class LagRange {
  public:
    static constexpr const char *kName = "Lag Range";
    static constexpr const char *kDescription = "Uses lag to stay out of target range.";
    explicit LagRange(std::uint8_t *image) : image_(image) {}
    // Maximum delay. Config key: delay.
    NumberSetting &delay() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2efc48);
    }
    // Sprint reset. Config key: flush_sprint_reset.
    BooleanSetting &flush_sprint_reset() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2efcc0);
    }
    // Used splash potion. Config key: flush_splash_potion.
    BooleanSetting &flush_splash_potion() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2efca0);
    }
    // Enabled. Config key: render_remote_pos.
    BooleanSetting &render_remote_pos() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2efce0);
    }
    // indicator_color. Config key: indicator_color.
    ColorSetting &indicator_color() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2efc08);
    }
    // Line width. Config key: indicator_line_width.
    NumberSetting &indicator_line_width() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2efbd0);
    }
    // Filled. Config key: indicator_filled.
    BooleanSetting &indicator_filled() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2efc28);
    }
    // Holding weapon. Config key: require_weapon.
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2efc80);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_lag_range_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_lag_range_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_lag_range_settings(&context, image_, &dependencies);
    }
    static void bindKnown(::lag_range::Dependencies &dependencies, aim_assist::Runtime &runtime) {
        ::lag_range::bindKnown(dependencies, runtime);
    }
    void packet(uint8_t *event, const ::lag_range::Dependencies &dependencies) {
        ::lag_range::packet(event, image_, dependencies);
    }
    void input(uint8_t *event, const ::lag_range::Dependencies &dependencies) {
        ::lag_range::input(event, image_, dependencies);
    }
    void render(uint8_t *event, const ::lag_range::Dependencies &dependencies) {
        ::lag_range::render(event, image_, dependencies);
    }
    void update(uint8_t *event, const ::lag_range::Dependencies &dependencies) {
        ::lag_range::update(event, image_, dependencies);
    }
    static void bindRender(::lag_range::Dependencies &dependencies, box_render::Context &context) {
        ::lag_range::bindRender(dependencies, context);
    }
    static void writeStatus(FormatState *format, char *destination, const std::uint8_t *image) {
        ::lag_range::writeStatus(format, destination, image);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
