// No Hurt Cam

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/No_Hurt_Cam.md

#include "../runtime/native/verified/module_surface.hpp"

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/No_Hurt_Cam/No_Hurt_Cam.cpp
#ifndef SLINKY_SHARE_FC8D4BBF571D9E1D0843
#define SLINKY_SHARE_FC8D4BBF571D9E1D0843
// BEGIN SOURCE native/verified/No_Hurt_Cam.hpp
#include "../runtime/native/verified/Free_Look.hpp"

struct NoHurtCamDescriptor {
    std::uint8_t reserved[20];
    std::uint8_t enabled;
    std::uint8_t padding[3];
};
struct AngleRestoreState {
    CameraAngleState camera;
    CameraRotation observed;
    std::uint8_t applied;
    std::uint8_t padding[7];
};
struct PitchRange {
    float lower, upper;
};
struct AngleRestoreBounds {
    PitchRange current, previous;
};
struct NoHurtCamDependencies {
    std::uintptr_t (*client)(GameAccessBridge *);
    std::uintptr_t (*entity)(GameAccessBridge *, std::uintptr_t);
    std::uint64_t (*player_angles)(GameAccessBridge *, std::uintptr_t);
    void (*set_current_angles)(GameAccessBridge *, std::uintptr_t, std::uint64_t,
                               const PitchRange *);
    void (*set_previous_angles)(GameAccessBridge *, std::uintptr_t, std::uint64_t,
                                const PitchRange *);
    void (*set_hurt_time)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    std::uint64_t (*final_call)(GameAccessBridge *);
};
static_assert(offsetof(NoHurtCamDescriptor, enabled) == 20);
static_assert(sizeof(AngleRestoreState) == 32);
static_assert(offsetof(AngleRestoreState, observed) == 16);
static_assert(offsetof(AngleRestoreState, applied) == 24);
static_assert(sizeof(AngleRestoreBounds) == 16);
static_assert(sizeof(NoHurtCamDependencies) == 56);

extern "C" {
__declspec(dllexport) void recovered_bind_no_hurt_cam_access(NoHurtCamDependencies *);
__declspec(dllexport) void recovered_angle_restore(GameAccessBridge *, AngleRestoreState *,
                                                   const AngleRestoreBounds *,
                                                   const NoHurtCamDependencies *);
__declspec(dllexport) std::uint64_t
recovered_no_hurt_cam_hook(const std::uint8_t *const *metadata, std::uintptr_t *environment,
                           const NoHurtCamDescriptor *const *descriptor, AngleRestoreState *,
                           const AngleRestoreBounds *, const NoHurtCamDependencies *);
}
// END SOURCE native/verified/No_Hurt_Cam.hpp

#endif // SLINKY_SHARE_FC8D4BBF571D9E1D0843

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

// 0x22c00 and 0x22c30.
static Word client(GameAccessBridge *bridge) {
    using Getter = Word (*)(Word *, Word, Word);
    return slot<Getter>(bridge, 0x488)(bridge->environment, identifier(bridge, 0x150),
                                       identifier(bridge, 0x180));
}
static Word entity(GameAccessBridge *bridge, Word client_object) {
    using Getter = Word (*)(Word *, Word, Word);
    return slot<Getter>(bridge, 0x2f8)(bridge->environment, client_object,
                                       identifier(bridge, 0x188));
}

// 0xa1f0 preserves MINSS operand order and the ordered lower-bound selection.
static float clamp_pitch(float value, const PitchRange *bounds) {
    const auto incoming = _mm_set_ss(value);
    const auto lower = _mm_set_ss(bounds->lower);
    const auto upper = _mm_min_ss(_mm_set_ss(bounds->upper), incoming);
    const auto below = _mm_cmplt_ss(incoming, lower);
    return _mm_cvtss_f32(_mm_or_ps(_mm_and_ps(lower, below), _mm_andnot_ps(below, upper)));
}

// 0x231e0 / 0x232e0 retain packed pitch and entity, reloading bridge after yaw.
template <std::size_t Field>
static void set_angles(GameAccessBridge *bridge, Word player, std::uint64_t packed,
                       const PitchRange *bounds) {
    using Setter_No_Hurt_Cam = void (*)(Word *, Word, Word, float);
    const auto rotation = std::bit_cast<CameraRotation>(packed);
    slot<Setter_No_Hurt_Cam>(bridge, 0x378)(bridge->environment, player, identifier(bridge, Field),
                                            rotation.yaw);
    const auto target = slot<Setter_No_Hurt_Cam>(bridge, 0x378);
    auto *environment = bridge->environment;
    const auto field = identifier(bridge, Field + 8);
    const auto pitch = clamp_pitch(rotation.pitch, bounds);
    target(environment, player, field, pitch);
}
// 0x23a10.
static void set_hurt_time(GameAccessBridge *bridge, Word player, std::uint32_t value) {
    using Setter_No_Hurt_Cam = void (*)(Word *, Word, Word, std::uint32_t);
    slot<Setter_No_Hurt_Cam>(bridge, 0x368)(bridge->environment, player, identifier(bridge, 0x550),
                                            value);
}
// 0x27a20 changes only AL in the returned register.
static std::uint64_t final_call(GameAccessBridge *bridge) {
    using Call = std::uint64_t (*)(Word *, Word, Word);
    const auto result = slot<Call>(bridge, 0x3a8)(bridge->environment, identifier(bridge, 0xb8),
                                                  identifier(bridge, 0xc8));
    return (result & ~std::uint64_t{0xff}) | ((result & 0xff) != 0);
}
extern "C" __declspec(dllexport) void
recovered_bind_no_hurt_cam_access(NoHurtCamDependencies *dependencies) {
    FreeLookDependencies camera;
    recovered_bind_free_look_access(&camera);
    *dependencies = {
        client,        entity,    camera.player_angles, set_angles<0x298>, set_angles<0x2a8>,
        set_hurt_time, final_call};
}

// 0x2a000 reloads the saved rotation before each setter and keeps the first entity.
extern "C" __declspec(dllexport) void
recovered_angle_restore(GameAccessBridge *bridge, AngleRestoreState *state,
                        const AngleRestoreBounds *bounds,
                        const NoHurtCamDependencies *dependencies) {
    const auto client_object = dependencies->client(bridge);
    const auto player = dependencies->entity(bridge, client_object);
    if (!player)
        return;
    state->observed = std::bit_cast<CameraRotation>(dependencies->player_angles(bridge, player));
    if (state->camera.updated == 1) {
        state->camera.updated = 0;
        dependencies->set_current_angles(
            bridge, player, std::bit_cast<std::uint64_t>(state->camera.rotation), &bounds->current);
        dependencies->set_previous_angles(bridge, player,
                                          std::bit_cast<std::uint64_t>(state->camera.rotation),
                                          &bounds->previous);
    }
    if (state->camera.active == 1) {
        state->applied = 1;
        dependencies->set_current_angles(
            bridge, player, std::bit_cast<std::uint64_t>(state->camera.rotation), &bounds->current);
    }
}

// 0x76a0 captures metadata before restoration, then reads the current descriptor.
extern "C" __declspec(dllexport) std::uint64_t
recovered_no_hurt_cam_hook(const std::uint8_t *const *metadata, Word *environment,
                           const NoHurtCamDescriptor *const *descriptor, AngleRestoreState *state,
                           const AngleRestoreBounds *bounds,
                           const NoHurtCamDependencies *dependencies) {
    GameAccessBridge bridge{*metadata, environment};
    recovered_angle_restore(&bridge, state, bounds, dependencies);
    if ((*descriptor)->enabled == 1) {
        const auto client_object = dependencies->client(&bridge);
        const auto player = dependencies->entity(&bridge, client_object);
        if (player)
            dependencies->set_hurt_time(&bridge, player, 0x7fffffff);
    }
    return dependencies->final_call(&bridge);
}
// END SOURCE modules/No_Hurt_Cam/No_Hurt_Cam.cpp

// BEGIN SOURCE modules/No_Hurt_Cam/Suppression.cpp
// Native direct entry 0x41f40. This body is embedded in the verified 0x76a0 hook;
// it is exposed here with its standalone native entry semantics.
#ifndef SLINKY_SHARE_D5B29F157D409295D4AC
#define SLINKY_SHARE_D5B29F157D409295D4AC
// BEGIN SOURCE modules/No_Hurt_Cam/Suppression.hpp
namespace reconstruction::no_hurt_cam {
void suppressHurtTime(GameAccessBridge *, const NoHurtCamDependencies &);
}
// END SOURCE modules/No_Hurt_Cam/Suppression.hpp

#endif // SLINKY_SHARE_D5B29F157D409295D4AC

void reconstruction::no_hurt_cam::suppressHurtTime(GameAccessBridge *bridge,
                                                   const NoHurtCamDependencies &deps) {
    const auto client = deps.client(bridge);
    const auto player = deps.entity(bridge, client);
    if (player)
        deps.set_hurt_time(bridge, player, 0x7fffffffu);
}
// END SOURCE modules/No_Hurt_Cam/Suppression.cpp

#ifndef SLINKY_SHARE_10AE5602DA86893BB079
#define SLINKY_SHARE_10AE5602DA86893BB079
// BEGIN SOURCE modules/No_Hurt_Cam/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/No_Hurt_Cam/Api.hpp

#endif // SLINKY_SHARE_10AE5602DA86893BB079

// Convenient borrowed-state interface

namespace shareable {
class NoHurtCam {
  public:
    static constexpr const char *kName = "No Hurt Cam";
    static constexpr const char *kDescription = "Removes camera shake when taking damage.";
    explicit NoHurtCam(std::uint8_t *image) : image_(image) {}
    static void bindAccess(NoHurtCamDependencies *dependencies) {
        ::recovered_bind_no_hurt_cam_access(dependencies);
    }
    static void angleRestore(GameAccessBridge *bridge, AngleRestoreState *state,
                             const AngleRestoreBounds *bounds,
                             const NoHurtCamDependencies *dependencies) {
        ::recovered_angle_restore(bridge, state, bounds, dependencies);
    }
    static std::uint64_t hook(const std::uint8_t *const *metadata, Word *environment,
                              const NoHurtCamDescriptor *const *descriptor,
                              AngleRestoreState *state, const AngleRestoreBounds *bounds,
                              const NoHurtCamDependencies *dependencies) {
        return ::recovered_no_hurt_cam_hook(metadata, environment, descriptor, state, bounds,
                                            dependencies);
    }
    static void suppressHurtTime(GameAccessBridge *bridge, const NoHurtCamDependencies &deps) {
        ::reconstruction::no_hurt_cam::suppressHurtTime(bridge, deps);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
