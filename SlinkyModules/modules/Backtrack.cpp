// Backtrack

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Backtrack.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Backtrack.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Backtrack: lib_win settings 0x36870.
static constexpr SettingsStep settings_steps_Surface_Backtrack[] = {
    {SettingsControl::range, "target_dist", 0x2eddb0},
    {SettingsControl::number, "delay", 0x2ede00},
    {SettingsControl::number, "max_hurt_time", 0x2edd78},
    {SettingsControl::number, "cooldown", 0x2ede38},
    {SettingsControl::boolean, "disable_on_hit", 0x2edeb0},
    {SettingsControl::boolean, "render_remote_pos", 0x2eded0},
    {SettingsControl::color, "indicator_color", 0x2edd18},
    {SettingsControl::number, "indicator_line_width", 0x2edce0},
    {SettingsControl::boolean, "indicator_filled", 0x2edd58},
    {SettingsControl::boolean, "indicator_rotate", 0x2edd38},
    {SettingsControl::boolean, "require_mouse_pressed", 0x2ede70},
    {SettingsControl::boolean, "require_weapon", 0x2ede90},
};
static constexpr ModuleSurface surface_Surface_Backtrack{
    nullptr, 0, settings_steps_Surface_Backtrack, std::size(settings_steps_Surface_Backtrack)};

extern "C" __declspec(dllexport) void
recovered_backtrack_settings(SettingsContext *context, std::uint8_t *image,
                             const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Backtrack, context, image, *dependencies);
}

// Backtrack: lib_win runtime UI 0x36740.
extern "C" __declspec(dllexport) void
recovered_backtrack_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                       const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->range(layout, ui, image + 0x2eddb0);
    dependencies->number(layout, ui, image + 0x2ede00);
    dependencies->number(layout, ui, image + 0x2edd78);
    dependencies->number(layout, ui, image + 0x2ede38);
    dependencies->checkbox(layout, ui, image + 0x2edeb0);
    dependencies->section(ui, layout, "Real position indicator");
    dependencies->checkbox(layout, ui, image + 0x2eded0);
    if (image[0x2edee8] == 1) {
        dependencies->color(layout, ui, image + 0x2edd18);
        dependencies->number(layout, ui, image + 0x2edce0);
        dependencies->checkbox(layout, ui, image + 0x2edd58);
        dependencies->checkbox(layout, ui, image + 0x2edd38);
    }
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2ede70);
    dependencies->checkbox(layout, ui, image + 0x2ede90);
}
// END SOURCE native/verified/surfaces/Surface_Backtrack.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Backtrack
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Backtrack.cpp
extern "C" __declspec(dllexport) void
recovered_backtrack_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                             const BoundSurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->range(layout, ui, image + 0x2eddb0);
    dependencies->number(layout, ui, image + 0x2ede00);
    dependencies->number(layout, ui, image + 0x2edd78);
    dependencies->number(layout, ui, image + 0x2ede38);
    dependencies->checkbox(layout, ui, image + 0x2edeb0);
    dependencies->section(ui, layout, "Real position indicator");
    dependencies->checkbox(layout, ui, image + 0x2eded0);
    if (image[0x2edee8] == 1) {
        dependencies->color(layout, ui, image + 0x2edd18);
        dependencies->number(layout, ui, image + 0x2edce0);
        dependencies->checkbox(layout, ui, image + 0x2edd58);
        dependencies->checkbox(layout, ui, image + 0x2edd38);
    }
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2ede70);
    dependencies->checkbox(layout, ui, image + 0x2ede90);
}
// END SOURCE shared/BoundSurfaces.cpp@Backtrack

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Backtrack/backtrack_packet.cpp
#ifndef SLINKY_SHARE_0EB8E8FCC3B97108779A
#define SLINKY_SHARE_0EB8E8FCC3B97108779A
// BEGIN SOURCE modules/Backtrack/Dependencies.hpp
#include <cstdint>
#include "../runtime/modules/Aim_Assist/Support.hpp"
#include "../runtime/shared/Geometry.hpp"
// Each endpoint has one named native role. The callback bodies contain the
// module algorithms. Unbound endpoints are listed in the module report.
namespace backtrack {
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
    Endpoint positionModeIsZero;                           // 0x23020
    Endpoint entityPosition;                               // 0x23030
    Endpoint entityRotation;                               // 0x23170
    Endpoint entityId;                                     // 0x23720
    Endpoint entityTicks;                                  // 0x23760
    Endpoint lastAttackerTime;                             // 0x239d0
    Endpoint entityHurtTime;                               // 0x239f0
    Endpoint serverPosition;                               // 0x24160
    Endpoint velocityPacket;                               // 0x266b0
    Endpoint velocityEntityId;                             // 0x266f0
    Endpoint relativeMovePacket;                           // 0x26a30
    Endpoint relativeMoveEntityId;                         // 0x26a70
    Endpoint headLookPacket;                               // 0x26a90
    Endpoint teleportPacket;                               // 0x26ad0
    Endpoint explosionPacket;                              // 0x26b10
    Endpoint attackInput;                                  // 0x29080
    Endpoint publishBacktrackPosition;                     // 0x369d0
    Endpoint backtrackMetric;                              // 0x36cf0
    Endpoint updateBacktrackPosition;                      // 0x36d80
    Endpoint activateBacktrack;                            // 0x36f60
    Endpoint weaponAllowed;                                // 0x380b0
    Endpoint entityRelativePacket;                         // 0x26800
    Endpoint relativeEntityId;                             // 0x26840
    Endpoint relativeX;                                    // 0x26860
    Endpoint relativeY;                                    // 0x26880
    Endpoint relativeZ;                                    // 0x268a0
    Endpoint relativeYaw;                                  // 0x268c0
    Endpoint relativeHasRotation;                          // 0x26900
    Endpoint entityTeleportPacket;                         // 0x26930
    Endpoint teleportEntityId;                             // 0x26970
    Endpoint teleportX;                                    // 0x26990
    Endpoint teleportY;                                    // 0x269b0
    Endpoint teleportZ;                                    // 0x269d0
    Endpoint teleportYaw;                                  // 0x269f0
    Endpoint beginBox, drawFilledBox, drawWireBox, endBox; // 293c0,29400,29430,295a0
    GraphicsEndpoint
        graphics; // external engine target plus argument bits; render order remains explicit
};
} // namespace backtrack
namespace backtrack {
void packet(uint8_t *event, uint8_t *image, const Dependencies &dependencies);
void render(uint8_t *event, uint8_t *image, const Dependencies &dependencies);
void update(uint8_t *event, uint8_t *image, const Dependencies &dependencies);
} // namespace backtrack
namespace backtrack {
double metric(const double *, const double *, const double *);
bool activate(aim_assist::Frame &, aim_assist::EntityRef, const double *, std::uint8_t *);
void updatePosition(const double *, float, std::uint8_t *, const aim_assist::Runtime &);
void publishPacket(std::uint8_t *, std::uint8_t, std::uint8_t *, const Dependencies &);
struct LocalBindings {
    aim_assist::Runtime &runtime;
    Dependencies &dependencies;
};
void bindLocal(Dependencies &, LocalBindings &);
} // namespace backtrack

namespace backtrack {
void bindKnown(Dependencies &, aim_assist::Runtime &);
}
#ifndef SLINKY_SHARE_B853E90E472DB25938A3
#define SLINKY_SHARE_B853E90E472DB25938A3
// BEGIN SOURCE modules/Backtrack/BoxRender.hpp
#include "../runtime/shared/Graphics.hpp"
namespace box_render {
struct Context {
    std::uint8_t *constantImage;
    RecoveredGraphicsEndpoint engine;
};
} // namespace box_render
// END SOURCE modules/Backtrack/BoxRender.hpp

#endif // SLINKY_SHARE_B853E90E472DB25938A3

namespace backtrack {
void bindRender(Dependencies &, box_render::Context &);
}
// END SOURCE modules/Backtrack/Dependencies.hpp

#endif // SLINKY_SHARE_0EB8E8FCC3B97108779A

#include <stdint.h>
#include <string.h>
#include <intrin.h>
namespace backtrack {
static uint64_t u64_backtrack_packet(const void *p) {
    return *(const volatile uint64_t *)p;
}
static uint32_t u32_backtrack_packet(const void *p) {
    return *(const volatile uint32_t *)p;
}
static int32_t s32_backtrack_packet(uint32_t b) {
    int32_t v;
    memcpy(&v, &b, 4);
    return v;
}
static int64_t s64(uint64_t b) {
    int64_t v;
    memcpy(&v, &b, 8);
    return v;
}
static void put32_backtrack_packet(void *p, uint32_t v) {
    *(volatile uint32_t *)p = v;
}

void packet(uint8_t *event, uint8_t *image, const Dependencies &dependencies) {
    volatile uint8_t *state = image;
    while (_InterlockedExchange8((volatile char *)(image + 0x2fc458), 1))
        _mm_pause();
    const auto evaluate = [&] {
        if (state[0x2fc470] != 1)
            return;
        uint64_t packet = dependencies.relativeMovePacket(u64_backtrack_packet(event + 8),
                                                          u64_backtrack_packet(event + 0x10), 0, 0);
        uint64_t game = u64_backtrack_packet(event + 8);
        if (packet) {
            uint32_t id = (uint32_t)dependencies.relativeMoveEntityId(game, packet, 0, 0);
            if (id == u32_backtrack_packet(image + 0x2fc468)) {
                put32_backtrack_packet(event + 0x24, 3);
                return;
            }
        } else {
            if (dependencies.teleportPacket(game, u64_backtrack_packet(event + 0x10), 0, 0)) {
                put32_backtrack_packet(event + 0x24, 3);
                return;
            }
            if (dependencies.headLookPacket(u64_backtrack_packet(event + 8),
                                            u64_backtrack_packet(event + 0x10), 0, 0)) {
                put32_backtrack_packet(event + 0x24, 3);
                return;
            }
        }
        packet = dependencies.velocityPacket(u64_backtrack_packet(event + 8),
                                             u64_backtrack_packet(event + 0x10), 0, 0);
        if (packet) {
            if (state[0x2fc471]) {
                uint32_t id = (uint32_t)dependencies.velocityEntityId(
                    u64_backtrack_packet(event + 8), packet, 0, 0);
                if (id == u32_backtrack_packet(image + 0x2fc46c)) {
                    state[0x2fc470] = 0;
                    return;
                }
            }
        } else if (dependencies.explosionPacket(u64_backtrack_packet(event + 8),
                                                u64_backtrack_packet(event + 0x10), 0, 0)) {
            state[0x2fc470] = 0;
            return;
        }
        if (s64(u64_backtrack_packet(event + 0x18)) <=
            s64(u64_backtrack_packet(image + 0x2fc460))) {
            put32_backtrack_packet(event + 0x24, 1);
            uint32_t stamp = u32_backtrack_packet(event + 0x20);
            if (s32_backtrack_packet(stamp) >
                s32_backtrack_packet(u32_backtrack_packet(image + 0x2fc450))) {
                put32_backtrack_packet(image + 0x2fc450, stamp);
                dependencies.publishBacktrackPosition((uintptr_t)(event + 8), 0, 0, 0);
            }
        } else if (!u32_backtrack_packet(event + 0x24) &&
                   s32_backtrack_packet(u32_backtrack_packet(event + 0x20)) >
                       s32_backtrack_packet(u32_backtrack_packet(image + 0x2fc454))) {
            dependencies.publishBacktrackPosition((uintptr_t)(event + 8), 1, 0, 0);
            put32_backtrack_packet(image + 0x2fc454, u32_backtrack_packet(event + 0x20));
        }
        return;
    };
    evaluate();
    state[0x2fc458] = 0;
}

} // namespace backtrack
// END SOURCE modules/Backtrack/backtrack_packet.cpp

// BEGIN SOURCE modules/Backtrack/backtrack_render.cpp
#include <stdint.h>
#include <string.h>
#include <emmintrin.h>
namespace backtrack {
static uint64_t u64_backtrack_render(const void *p) {
    return *(const volatile uint64_t *)p;
}
static uint32_t u32_backtrack_render(const void *p) {
    return *(const volatile uint32_t *)p;
}
static float f32_backtrack_render(const void *p) {
    uint32_t b = u32_backtrack_render(p);
    float v;
    memcpy(&v, &b, 4);
    return v;
}
static double f64(const void *p) {
    uint64_t b = u64_backtrack_render(p);
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
    return u64_backtrack_render((void *)(uintptr_t)u64_backtrack_render(image + slot));
}

void render(uint8_t *event, uint8_t *image, const Dependencies &dependencies) {
    if (image[0x2fc4a0] != 1)
        return;
    double fraction = (double)f32_backtrack_render(event + 0x28);
    double previous[3], current[3], position[3], camera[3], relative[3];
    memcpy(previous, image + 0x2fc4a8, 24);
    memcpy(current, image + 0x2fc4c0, 24);
    recovered_vector_lerp_9460(position, previous, current, fraction);
    memcpy(camera, event + 8, 24);
    recovered_vector_subtract_93d0(relative, position, camera);
    dependencies.beginBox(0, 0, 0, 0);
    dependencies.graphics(method(image, 0x150cb0), u32_backtrack_render(image + 0x2edd10), 0, 0, 0);
    dependencies.graphics(method(image, 0x150cc0), 0, 0, 0, 0);
    dependencies.graphics(method(image, 0x150cd8), fb((float)relative[0]),
                          fb((float)(relative[1] + f64(image + 0x152178))), fb((float)relative[2]),
                          0);
    dependencies.graphics(method(image, 0x150cd0), u32_backtrack_render(image + 0x152184),
                          u32_backtrack_render(image + 0x152180),
                          u32_backtrack_render(image + 0x152184), 0);
    if (image[0x2edd50] == 1) {
        float angle = recovered_scalar_lerp_a2b0(f32_backtrack_render(image + 0x2fc4d8),
                                                 f32_backtrack_render(image + 0x2fc4dc),
                                                 f32_backtrack_render(event + 0x28));
        dependencies.graphics(method(image, 0x150cc8),
                              fb(f32_backtrack_render(image + 0x152188) - angle), 0,
                              u32_backtrack_render(image + 0x152180), 0);
    }
    if (image[0x2edd70] == 1) {
        dependencies.graphics(method(image, 0x13e448), u32_backtrack_render(image + 0x2edd20),
                              u32_backtrack_render(image + 0x2edd24),
                              u32_backtrack_render(image + 0x2edd28),
                              u32_backtrack_render(image + 0x15218c));
        dependencies.drawFilledBox(0, 0, 0, 0);
    }
    dependencies.graphics(method(image, 0x150ca0), u32_backtrack_render(image + 0x2edd20),
                          u32_backtrack_render(image + 0x2edd24),
                          u32_backtrack_render(image + 0x2edd28), 0);
    dependencies.drawWireBox(0, 0, 0, 0);
    dependencies.graphics(method(image, 0x150cb8), 0, 0, 0, 0);
    dependencies.endBox(0, 0, 0, 0);
}

} // namespace backtrack
// END SOURCE modules/Backtrack/backtrack_render.cpp

// BEGIN SOURCE modules/Backtrack/backtrack_update.cpp
#include <stdint.h>
#include <string.h>
#include <intrin.h>
namespace backtrack {
static uint64_t u64_backtrack_update(const void *p) {
    return *(const volatile uint64_t *)p;
}
static uint32_t u32_backtrack_update(const void *p) {
    return *(const volatile uint32_t *)p;
}
static int32_t s32_backtrack_update(uint32_t b) {
    int32_t v;
    memcpy(&v, &b, 4);
    return v;
}
static double d64(uint64_t b) {
    double v;
    memcpy(&v, &b, 8);
    return v;
}
static float f32_backtrack_update(const void *p) {
    uint32_t b = u32_backtrack_update(p);
    float v;
    memcpy(&v, &b, 4);
    return v;
}
static void put32_backtrack_update(void *p, uint32_t v) {
    *(volatile uint32_t *)p = v;
}
static void put64(void *p, uint64_t v) {
    *(volatile uint64_t *)p = v;
}
static void lock(uint8_t *image) {
    while (_InterlockedExchange8((volatile char *)(image + 0x2fc458), 1))
        _mm_pause();
}

void update(uint8_t *event, uint8_t *image, const Dependencies &dependencies) {
    uint8_t *ctx = (uint8_t *)(uintptr_t)u64_backtrack_update(event + 8);
    volatile uint8_t *state = image;
    uint32_t cooldown = u32_backtrack_update(image + 0x2fc4e0);
    if (s32_backtrack_update(cooldown) > 0) {
        put32_backtrack_update(image + 0x2fc4e0, cooldown - 1);
        if (cooldown != 1)
            return;
    }
    bool accepted = false;
    const auto evaluate = [&] {
        if (ctx[0x40] != 1)
            return;
        if (state[0x2ede88] == 1 && !(uint8_t)dependencies.attackInput((uintptr_t)ctx, 0, 0, 0))
            return;
        if (state[0x2edea8] == 1 &&
            !(uint8_t)dependencies.weaponAllowed(u64_backtrack_update(ctx),
                                                 u64_backtrack_update(ctx + 0x28), 0, 0))
            return;
        uint32_t previous = (uint32_t)dependencies.lastAttackerTime(
            u64_backtrack_update(ctx), u64_backtrack_update(ctx + 0x28), 0, 0);
        uint32_t current = (uint32_t)dependencies.entityTicks(
            u64_backtrack_update(ctx), u64_backtrack_update(ctx + 0x28), 0, 0);
        if (s32_backtrack_update(current - previous) > 20)
            return;
        uint8_t *target = (uint8_t *)(uintptr_t)u64_backtrack_update(ctx + 0x38);
        uint64_t entity = u64_backtrack_update(target + 8);
        if (!entity)
            return;
        uint32_t hurt =
            (uint32_t)dependencies.entityHurtTime(u64_backtrack_update(ctx), entity, 0, 0);
        if ((float)s32_backtrack_update(hurt) > f32_backtrack_update(image + 0x2edda8))
            return;
        float minimum = f32_backtrack_update(image + 0x2eddf0);
        minimum = minimum * minimum;
        double distance = d64(u64_backtrack_update(target + 0x10));
        if ((double)minimum > distance)
            return;
        float maximum = f32_backtrack_update(image + 0x2eddf4);
        maximum = maximum * maximum;
        if (distance > (double)maximum)
            return;
        double self[3], position[3], candidate[3], copy[3];
        dependencies.entityPosition((uintptr_t)self, u64_backtrack_update(ctx),
                                    u64_backtrack_update(ctx + 0x28), 0);
        if ((uint8_t)dependencies.positionModeIsZero(u64_backtrack_update(ctx), 0, 0, 0)) {
            double adjusted[3];
            memcpy(copy, self, 24);
            recovered_vector_adjust_95c0(adjusted, copy, image);
            memcpy(self, adjusted, 24);
        }
        dependencies.serverPosition((uintptr_t)position, u64_backtrack_update(ctx),
                                    u64_backtrack_update(target + 8), 0);
        uint64_t angles = dependencies.entityRotation(u64_backtrack_update(ctx),
                                                      u64_backtrack_update(target + 8), 0, 0);
        uint32_t target_id = (uint32_t)dependencies.entityId(
            u64_backtrack_update(ctx), u64_backtrack_update(target + 8), 0, 0);
        uint32_t self_id = (uint32_t)dependencies.entityId(u64_backtrack_update(ctx),
                                                           u64_backtrack_update(ctx + 0x28), 0, 0);
        lock(image);
        int64_t limit = _mm_cvttss_si64(_mm_set_ss(f32_backtrack_update(image + 0x2ede30)));
        uint32_t old_id = u32_backtrack_update(image + 0x2fc468);
        put64(image + 0x2fc460, (uint64_t)limit);
        put32_backtrack_update(image + 0x2fc468, target_id);
        put32_backtrack_update(image + 0x2fc46c, self_id);
        state[0x2fc471] = state[0x2edec8];
        if (state[0x2fc470] != 1) {
            memcpy(copy, self, 24);
            if (!(uint8_t)dependencies.activateBacktrack(
                    (uintptr_t)ctx, u64_backtrack_update(target + 8), (uintptr_t)copy, 0)) {
                state[0x2fc4a0] = 0;
                {
                    state[0x2fc458] = 0;
                    accepted = true;
                    return;
                }
            }
            state[0x2fc470] = 1;
            recovered_geometry_construct_93b0(copy, 0., 0., 0.);
            memcpy(image + 0x2fc478, copy, 24);
            state[0x2fc490] = 0;
            state[0x2fc498] = 0;
            dependencies.entityPosition((uintptr_t)copy, u64_backtrack_update(ctx),
                                        u64_backtrack_update(target + 8), 0);
            memcpy(image + 0x2fc4a8, copy, 24);
            memcpy(image + 0x2fc4c0, copy, 24);
            memcpy(image + 0x2fc4e8, copy, 24);
            put32_backtrack_update(image + 0x2fc4d8, (uint32_t)angles);
            put32_backtrack_update(image + 0x2fc4dc, (uint32_t)angles);
            put32_backtrack_update(image + 0x2fc500, (uint32_t)angles);
            state[0x2fc4a0] = state[0x2edee8];
            {
                state[0x2fc458] = 0;
                accepted = true;
                return;
            }
        }
        if (state[0x2fc490] == 1)
            memcpy(candidate, image + 0x2fc478, 24);
        else {
            double position_copy[3];
            memcpy(copy, image + 0x2fc478, 24);
            memcpy(position_copy, position, 24);
            recovered_geometry_add_9400(candidate, copy, position_copy);
        }
        double self_copy[3], position_copy[3], candidate_copy[3];
        memcpy(self_copy, self, 24);
        memcpy(position_copy, position, 24);
        memcpy(candidate_copy, candidate, 24);
        double metric = d64(dependencies.backtrackMetric(
            (uintptr_t)self_copy, (uintptr_t)position_copy, (uintptr_t)candidate_copy, 0));
        if (d64(u64_backtrack_update(image + 0x152190)) > metric || old_id != target_id) {
            recovered_geometry_construct_93b0(copy, 0., 0., 0.);
            memcpy(image + 0x2fc478, copy, 24);
            state[0x2fc490] = 0;
            state[0x2fc498] = 0;
            uint32_t next =
                (uint32_t)_mm_cvttss_si32(_mm_set_ss(f32_backtrack_update(image + 0x2ede68)));
            state[0x2fc4a0] = 0;
            state[0x2fc470] = 0;
            put32_backtrack_update(image + 0x2fc4e0, next);
        } else {
            uint32_t angle =
                state[0x2fc498] ? u32_backtrack_update(image + 0x2fc494) : (uint32_t)angles;
            memcpy(copy, candidate, 24);
            dependencies.updateBacktrackPosition((uintptr_t)copy, angle, 0, 0);
        }
        state[0x2fc458] = 0;
        accepted = true;
        return;
    };
    evaluate();
    if (accepted)
        return;
    lock(image);
    if (state[0x2fc470] == 1) {
        put32_backtrack_update(image + 0x2fc4e0, (uint32_t)_mm_cvttss_si32(_mm_set_ss(
                                                     f32_backtrack_update(image + 0x2ede68))));
        state[0x2fc470] = 0;
    }
    state[0x2fc458] = 0;
    state[0x2fc4a0] = 0;
}

} // namespace backtrack
// END SOURCE modules/Backtrack/backtrack_update.cpp

// BEGIN SOURCE modules/Backtrack/Bindings.cpp
#include "../runtime/shared/JniAccess.hpp"
namespace backtrack {
using namespace recovered_jni;
void bindKnown(Dependencies &dependencies, aim_assist::Runtime &runtime) {
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
    dependencies.entityId = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                 return static_cast<std::uint32_t>(
                                     aim_assist::mc::entityNumericId(bridge(a), object(b)));
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
    dependencies.serverPosition = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return storedVector(
                a, aim_assist::mc::entityOtherPlayerServerPosition(bridge(b), object(c)));
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
    dependencies.relativeMoveEntityId = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return field<std::uint32_t, 0x320>(bridge(a), b, 0x858);
        }};
    dependencies.headLookPacket = {&runtime,
                                   +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                       return instance(bridge(a), b, 0x860);
                                   }};
    dependencies.teleportPacket = {&runtime,
                                   +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                       return instance(bridge(a), b, 0x868);
                                   }};
    dependencies.explosionPacket = {&runtime,
                                    +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                        return instance(bridge(a), b, 0xa40);
                                    }};
    dependencies.attackInput = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                    return aim_assist::attackInputDown(
                                        *reinterpret_cast<const aim_assist::Frame *>(a));
                                }};
    dependencies.weaponAllowed = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return static_cast<aim_assist::Runtime *>(user)->isWeapon(bridge(a), object(b));
        }};
    dependencies.entityRelativePacket = {&runtime,
                                         +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                             return instance(bridge(a), b, 0x7d8);
                                         }};
    dependencies.relativeEntityId = {&runtime,
                                     +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                         return field<std::uint32_t, 0x320>(bridge(a), b, 0x7e0);
                                     }};
    dependencies.relativeX = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                  return field<std::uint8_t, 0x308>(bridge(a), b, 0x7e8);
                              }};
    dependencies.relativeY = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                  return field<std::uint8_t, 0x308>(bridge(a), b, 0x7f0);
                              }};
    dependencies.relativeZ = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                  return field<std::uint8_t, 0x308>(bridge(a), b, 0x7f8);
                              }};
    dependencies.relativeYaw = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                    return field<std::uint8_t, 0x308>(bridge(a), b, 0x800);
                                }};
    dependencies.relativeHasRotation = {
        &runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
            return field<std::uint8_t, 0x300>(bridge(a), b, 0x810) != 0;
        }};
    dependencies.entityTeleportPacket = {&runtime,
                                         +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                             return instance(bridge(a), b, 0x818);
                                         }};
    dependencies.teleportEntityId = {&runtime,
                                     +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                         return field<std::uint32_t, 0x320>(bridge(a), b, 0x820);
                                     }};
    dependencies.teleportX = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                  return field<std::uint32_t, 0x320>(bridge(a), b, 0x828);
                              }};
    dependencies.teleportY = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                  return field<std::uint32_t, 0x320>(bridge(a), b, 0x830);
                              }};
    dependencies.teleportZ = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                  return field<std::uint32_t, 0x320>(bridge(a), b, 0x838);
                              }};
    dependencies.teleportYaw = {&runtime, +[](void *user, Word a, Word b, Word c, Word d) -> Word {
                                    return field<std::uint8_t, 0x308>(bridge(a), b, 0x840);
                                }};
}
} // namespace backtrack
namespace backtrack {
void bindLocal(Dependencies &dependencies, LocalBindings &context) {
    dependencies.activateBacktrack = {
        &context, +[](void *user, Word frame, Word entity, Word self, Word) -> Word {
            auto &c = *static_cast<LocalBindings *>(user);
            return activate(*reinterpret_cast<aim_assist::Frame *>(frame),
                            reinterpret_cast<void *>(entity),
                            reinterpret_cast<const double *>(self), c.runtime.image);
        }};
    dependencies.backtrackMetric = {
        &context, +[](void *, Word self, Word server, Word delayed, Word) -> Word {
            return recovered_jni::doubleBits(metric(reinterpret_cast<const double *>(self),
                                                    reinterpret_cast<const double *>(server),
                                                    reinterpret_cast<const double *>(delayed)));
        }};
    dependencies.updateBacktrackPosition = {
        &context, +[](void *user, Word point, Word yaw, Word, Word) -> Word {
            auto &c = *static_cast<LocalBindings *>(user);
            updatePosition(reinterpret_cast<const double *>(point), recovered_jni::floatValue(yaw),
                           c.runtime.image, c.runtime);
            return 0;
        }};
    dependencies.publishBacktrackPosition = {
        &context, +[](void *user, Word packet, Word reconcile, Word, Word) -> Word {
            auto &c = *static_cast<LocalBindings *>(user);
            publishPacket(reinterpret_cast<std::uint8_t *>(packet),
                          static_cast<std::uint8_t>(reconcile), c.runtime.image, c.dependencies);
            return 0;
        }};
}
} // namespace backtrack
// END SOURCE modules/Backtrack/Bindings.cpp

// BEGIN SOURCE modules/Backtrack/Local.cpp
#include <cstring>
namespace backtrack {
namespace {
template <class T> T read(const std::uint8_t *image, std::uint32_t rva) {
    T value;
    std::memcpy(&value, image + rva, sizeof value);
    return value;
}
template <class T> void store(std::uint8_t *image, std::uint32_t rva, T value) {
    std::memcpy(image + rva, &value, sizeof value);
}
} // namespace
// 0x36cf0 compares the distances to the server and delayed positions.
double metric(const double *self, const double *server, const double *delayed) {
    double a[3], b[3];
    std::memcpy(a, self, 24);
    std::memcpy(b, server, 24);
    const double serverDistance = recovered_vector_distance_94f0(a, b);
    std::memcpy(a, self, 24);
    std::memcpy(b, delayed, 24);
    const double delayedDistance = recovered_vector_distance_94f0(a, b);
    return aim_assist::native::roundedSubDouble(delayedDistance, serverDistance);
}
// 0x36f60. Entity access has concrete bodies in Aim_Assist/Support.cpp.
bool activate(aim_assist::Frame &frame, aim_assist::EntityRef entity, const double *self,
              std::uint8_t *image) {
    const auto client = aim_assist::mc::entityPosition(frame.jni, entity);
    const auto server = aim_assist::mc::entityOtherPlayerServerPosition(frame.jni, entity);
    double a[3], b[3];
    std::memcpy(a, self, 24);
    std::memcpy(b, &client, 24);
    const double clientDistance = recovered_vector_distance_94f0(a, b);
    std::memcpy(a, self, 24);
    std::memcpy(b, &server, 24);
    const double serverDistance = recovered_vector_distance_94f0(a, b);
    return read<double>(image, 0x1521b0) <
           aim_assist::native::roundedSubDouble(serverDistance, clientDistance);
}
// 0x36d80. Position equality is a byte comparison; yaw equality is ordered.
void updatePosition(const double *position, float yaw, std::uint8_t *image,
                    const aim_assist::Runtime &runtime) {
    const auto first = _mm_loadu_si128(reinterpret_cast<const __m128i *>(image + 0x2fc4e8));
    const auto incoming = _mm_loadu_si128(reinterpret_cast<const __m128i *>(position));
    const auto tail = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(image + 0x2fc4f8));
    const auto incomingTail = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(position + 2));
    const auto tailMatch = _mm_cmpeq_epi8(tail, incomingTail);
    const auto combined = _mm_and_si128(_mm_cmpeq_epi8(first, incoming), tailMatch);
    if (_mm_movemask_epi8(combined) != 0xffff || !(yaw == read<float>(image, 0x2fc500)))
        store<std::int32_t>(image, 0x2fc504, 3);
    store<double>(image, 0x2fc4f8, position[2]);
    store<double>(image, 0x2fc4e8, position[0]);
    store<double>(image, 0x2fc4f0, position[1]);
    std::memcpy(image + 0x2fc4a8, image + 0x2fc4c0, 24);
    store<float>(image, 0x2fc4d8, read<float>(image, 0x2fc4dc));
    store<float>(image, 0x2fc500, yaw);
    auto remaining = read<std::int32_t>(image, 0x2fc504);
    if (remaining < 1)
        std::memcpy(image + 0x2fc4c0, position, 24);
    else {
        const double fraction = aim_assist::native::roundedDivDouble(
            read<double>(image, 0x1521a8), static_cast<double>(remaining));
        double delta[3], scaled[3], current[3], result[3];
        std::memcpy(current, image + 0x2fc4c0, 24);
        recovered_vector_subtract_93d0(delta, position, current);
        recovered_vector_scale_9430(scaled, delta, fraction);
        recovered_geometry_add_9400(result, current, scaled);
        std::memcpy(image + 0x2fc4c0, result, 24);
        const float wrapped = runtime.wrap(aim_assist::native::roundedSub(
            read<float>(image, 0x2fc500), read<float>(image, 0x2fc4dc)));
        const float narrowed = static_cast<float>(
            aim_assist::native::roundedMulDouble(static_cast<double>(wrapped), fraction));
        yaw = aim_assist::native::roundedAdd(narrowed, read<float>(image, 0x2fc4dc));
        store<std::uint32_t>(image, 0x2fc504, static_cast<std::uint32_t>(remaining) - 1);
    }
    store<float>(image, 0x2fc4dc, yaw);
}
// 0x369d0 consumes relative-move or teleport packet values. Packet accessors
// remain named and individually accounted; all offset/yaw mutation is here.
void publishPacket(std::uint8_t *context, std::uint8_t reconcile, std::uint8_t *image,
                   const Dependencies &dependencies) {
    const auto bridge = read<Word>(context, 0), original = read<Word>(context, 8);
    const auto stamp = read<std::int32_t>(context, 0x18);
    if (reconcile != 0 && read<std::int32_t>(image, 0x2fc49c) > stamp)
        return;
    const Word relative = dependencies.entityRelativePacket(bridge, original, 0, 0);
    const Word packet =
        relative ? relative : dependencies.entityTeleportPacket(bridge, original, 0, 0);
    if (!packet)
        return;
    const Word id = relative ? dependencies.relativeEntityId(bridge, packet, 0, 0)
                             : dependencies.teleportEntityId(bridge, packet, 0, 0);
    if (static_cast<std::uint32_t>(id) != read<std::uint32_t>(image, 0x2fc468))
        return;
    const auto component = [&](Endpoint relativeGetter, Endpoint absoluteGetter) {
        const auto raw =
            relative ? relativeGetter(bridge, packet, 0, 0) : absoluteGetter(bridge, packet, 0, 0);
        const auto signedValue = relative ? static_cast<std::int32_t>(static_cast<std::int8_t>(raw))
                                          : static_cast<std::int32_t>(raw);
        return aim_assist::native::roundedMulDouble(static_cast<double>(signedValue),
                                                    read<double>(image, 0x152198));
    };
    const double x = component(dependencies.relativeX, dependencies.teleportX);
    const double y = component(dependencies.relativeY, dependencies.teleportY);
    const double z = component(dependencies.relativeZ, dependencies.teleportZ);
    double delta[3], previous[3], result[3];
    recovered_geometry_construct_93b0(delta, x, y, z);
    if (reconcile != 0) {
        std::memcpy(previous, image + 0x2fc478, 24);
        recovered_vector_subtract_93d0(result, previous, delta);
        std::memcpy(image + 0x2fc478, result, 24);
        if (!relative)
            image[0x2fc490] = 0;
        return;
    }
    if (relative) {
        std::memcpy(previous, image + 0x2fc478, 24);
        recovered_geometry_add_9400(result, previous, delta);
        std::memcpy(image + 0x2fc478, result, 24);
        if (!static_cast<std::uint8_t>(dependencies.relativeHasRotation(bridge, packet, 0, 0)))
            return;
    } else {
        std::memcpy(image + 0x2fc478, delta, 24);
        image[0x2fc490] = 1;
    }
    const auto yawBits = relative ? dependencies.relativeYaw(bridge, packet, 0, 0)
                                  : dependencies.teleportYaw(bridge, packet, 0, 0);
    const float angle = static_cast<float>(static_cast<std::int8_t>(yawBits));
    const float scaled = aim_assist::native::roundedMul(angle, read<float>(image, 0x1521a0));
    store<float>(image, 0x2fc494,
                 aim_assist::native::roundedMul(scaled, read<float>(image, 0x1521a4)));
    image[0x2fc498] = 1;
    if (!relative)
        store<std::int32_t>(image, 0x2fc49c, stamp);
}
} // namespace backtrack
// END SOURCE modules/Backtrack/Local.cpp

// BEGIN SOURCE modules/Backtrack/RenderBindings.cpp
namespace backtrack {
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
} // namespace backtrack
// END SOURCE modules/Backtrack/RenderBindings.cpp

// BEGIN SOURCE modules/Backtrack/Surface.cpp
#ifndef SLINKY_SHARE_A5BCFB22788388F849D2
#define SLINKY_SHARE_A5BCFB22788388F849D2
// BEGIN SOURCE modules/Backtrack/Surface.hpp
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/native/verified/module_format.hpp"
namespace backtrack {
void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                    const BoundSurfaceUiDependencies &);
void serializeConfig(SettingsContext &, std::uint8_t *image, const SurfaceSettingsDependencies &);
void writeStatus(FormatState *, char *destination, const std::uint8_t *image);
} // namespace backtrack
// END SOURCE modules/Backtrack/Surface.hpp

#endif // SLINKY_SHARE_A5BCFB22788388F849D2

extern "C" void recovered_backtrack_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                             const BoundSurfaceUiDependencies *);
extern "C" void recovered_backtrack_settings(SettingsContext *, std::uint8_t *,
                                             const SurfaceSettingsDependencies *);
namespace backtrack {
void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                    const BoundSurfaceUiDependencies &dependencies) {
    recovered_backtrack_bound_ui(ui, layout, image, &dependencies);
}
void serializeConfig(SettingsContext &context, std::uint8_t *image,
                     const SurfaceSettingsDependencies &dependencies) {
    recovered_backtrack_settings(&context, image, &dependencies);
}
void writeStatus(FormatState *format, char *destination, const std::uint8_t *image) {
    recovered_format(format, destination, 0x20, "%.0fms",
                     static_cast<double>(read_surface_value<float>(image, 0x2ede30)));
}
} // namespace backtrack
// END SOURCE modules/Backtrack/Surface.cpp

// Convenient borrowed-state interface

namespace shareable {
class Backtrack {
  public:
    static constexpr const char *kName = "Backtrack";
    static constexpr const char *kDescription = "Uses lag to make players easier to hit.";
    explicit Backtrack(std::uint8_t *image) : image_(image) {}
    // target_dist. Config key: target_dist.
    RangeSetting &target_dist() const {
        return *reinterpret_cast<RangeSetting *>(image_ + 0x2eddb0);
    }
    // Maximum delay. Config key: delay.
    NumberSetting &delay() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ede00);
    }
    // Maximum hurt time. Config key: max_hurt_time.
    NumberSetting &max_hurt_time() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2edd78);
    }
    // Cooldown. Config key: cooldown.
    NumberSetting &cooldown() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ede38);
    }
    // Disable when hit. Config key: disable_on_hit.
    BooleanSetting &disable_on_hit() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2edeb0);
    }
    // Enabled. Config key: render_remote_pos.
    BooleanSetting &render_remote_pos() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eded0);
    }
    // indicator_color. Config key: indicator_color.
    ColorSetting &indicator_color() const {
        return *reinterpret_cast<ColorSetting *>(image_ + 0x2edd18);
    }
    // Line width. Config key: indicator_line_width.
    NumberSetting &indicator_line_width() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2edce0);
    }
    // Filled. Config key: indicator_filled.
    BooleanSetting &indicator_filled() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2edd58);
    }
    // Apply head rotation. Config key: indicator_rotate.
    BooleanSetting &indicator_rotate() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2edd38);
    }
    // Mouse pressed. Config key: require_mouse_pressed.
    BooleanSetting &require_mouse_pressed() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ede70);
    }
    // Holding weapon. Config key: require_weapon.
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ede90);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_backtrack_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_backtrack_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_backtrack_settings(&context, image_, &dependencies);
    }
    void packet(uint8_t *event, const ::backtrack::Dependencies &dependencies) {
        ::backtrack::packet(event, image_, dependencies);
    }
    void render(uint8_t *event, const ::backtrack::Dependencies &dependencies) {
        ::backtrack::render(event, image_, dependencies);
    }
    void update(uint8_t *event, const ::backtrack::Dependencies &dependencies) {
        ::backtrack::update(event, image_, dependencies);
    }
    static void bindKnown(::backtrack::Dependencies &dependencies, aim_assist::Runtime &runtime) {
        ::backtrack::bindKnown(dependencies, runtime);
    }
    static void bindLocal(::backtrack::Dependencies &dependencies,
                          ::backtrack::LocalBindings &context) {
        ::backtrack::bindLocal(dependencies, context);
    }
    static double metric(const double *self, const double *server, const double *delayed) {
        return ::backtrack::metric(self, server, delayed);
    }
    bool activate(aim_assist::Frame &frame, aim_assist::EntityRef entity, const double *self) {
        return ::backtrack::activate(frame, entity, self, image_);
    }
    void updatePosition(const double *position, float yaw, const aim_assist::Runtime &runtime) {
        ::backtrack::updatePosition(position, yaw, image_, runtime);
    }
    void publishPacket(std::uint8_t *context, std::uint8_t reconcile,
                       const ::backtrack::Dependencies &dependencies) {
        ::backtrack::publishPacket(context, reconcile, image_, dependencies);
    }
    static void bindRender(::backtrack::Dependencies &dependencies, box_render::Context &context) {
        ::backtrack::bindRender(dependencies, context);
    }
    static void writeStatus(FormatState *format, char *destination, const std::uint8_t *image) {
        ::backtrack::writeStatus(format, destination, image);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
