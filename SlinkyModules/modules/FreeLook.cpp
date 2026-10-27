// Free Look

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Free_Look.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Free_Look.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Free Look: lib_win settings 0x37160.
// UI 0x37120.
static constexpr UiStep ui_steps_Surface_Free_Look[] = {
    {UiControl::section, "Main", 0},
    {UiControl::choice, nullptr, 0x2ee118},
};
static constexpr SettingsStep settings_steps_Surface_Free_Look[] = {
    {SettingsControl::choice, "target_perspective", 0x2ee118},
};
static constexpr ModuleSurface surface_Surface_Free_Look{
    ui_steps_Surface_Free_Look, std::size(ui_steps_Surface_Free_Look),
    settings_steps_Surface_Free_Look, std::size(settings_steps_Surface_Free_Look)};

extern "C" __declspec(dllexport) void
recovered_free_look_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                       const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Free_Look, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_free_look_settings(SettingsContext *context, std::uint8_t *image,
                             const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Free_Look, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Free_Look.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Free_Look/Free_Look.cpp
#ifndef SLINKY_SHARE_EE7A20DC5FDD87278217
#define SLINKY_SHARE_EE7A20DC5FDD87278217
// BEGIN SOURCE native/verified/Free_Look.hpp
#include "../runtime/native/verified/module_game_access.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/native/verified/module_float_math.hpp"

struct CameraRotation {
    float yaw, pitch;
};
struct CameraAngleState {
    CameraRotation rotation;
    std::uint8_t active;
    std::uint8_t updated;
    std::uint8_t padding[6];
};
struct FreeLookState {
    std::uintptr_t reserved;
    std::uint8_t enabled;
    std::uint8_t padding[7];
    CameraRotation saved_rotation;
    std::uint32_t saved_perspective;
    std::uint32_t reserved2;
};
struct FreeLookGame {
    GameAccessBridge *bridge;
    std::uintptr_t reserved[2];
    std::uintptr_t client;
    std::uintptr_t world;
    std::uintptr_t player;
};
struct FreeLookEvent {
    std::uintptr_t event_type;
    FreeLookGame *game;
    std::uintptr_t module;
    std::uint8_t enabled;
    std::uint8_t padding[7];
};
struct FreeLookRotationEvent {
    std::uintptr_t event_type;
    std::uint8_t override_rotation;
    std::uint8_t padding[3];
    CameraRotation rotation;
};
struct FreeLookDependencies {
    std::uint64_t (*player_angles)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*options)(GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*perspective)(GameAccessBridge *, std::uintptr_t);
    void (*set_perspective)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
};

static_assert(sizeof(CameraRotation) == 8);
static_assert(sizeof(CameraAngleState) == 16);
static_assert(offsetof(CameraAngleState, active) == 8);
static_assert(offsetof(CameraAngleState, updated) == 9);
static_assert(sizeof(FreeLookState) == 32);
static_assert(offsetof(FreeLookState, enabled) == 8);
static_assert(offsetof(FreeLookState, saved_rotation) == 16);
static_assert(offsetof(FreeLookState, saved_perspective) == 24);
static_assert(sizeof(FreeLookGame) == 48);
static_assert(offsetof(FreeLookGame, world) == 32);
static_assert(offsetof(FreeLookGame, player) == 40);
static_assert(sizeof(FreeLookEvent) == 32);
static_assert(offsetof(FreeLookEvent, module) == 16);
static_assert(offsetof(FreeLookEvent, enabled) == 24);
static_assert(offsetof(FreeLookRotationEvent, override_rotation) == 8);
static_assert(offsetof(FreeLookRotationEvent, rotation) == 12);
static_assert(sizeof(FreeLookDependencies) == 32);

extern "C" {
__declspec(dllexport) void recovered_bind_free_look_access(FreeLookDependencies *);
__declspec(dllexport) void
recovered_free_look_lifecycle(FreeLookEvent *, std::uintptr_t module_identity,
                              const ChoiceSetting *, FreeLookState *, CameraAngleState *,
                              const AngleWrapConstants *, const FreeLookDependencies *);
__declspec(dllexport) void recovered_free_look_rotation(FreeLookRotationEvent *,
                                                        const FreeLookState *);
__declspec(dllexport) void recovered_free_look_restore(CameraAngleState *,
                                                       const AngleWrapConstants *,
                                                       std::uint64_t packed_rotation);
__declspec(dllexport) void recovered_free_look_typed_ui(std::uint64_t ui, std::uint64_t layout,
                                                        ChoiceSetting *,
                                                        const SurfaceUiDependencies *);
__declspec(dllexport) void recovered_free_look_typed_settings(SettingsContext *, ChoiceSetting *,
                                                              const ValueSettingsDependencies *);
}
// END SOURCE native/verified/Free_Look.hpp

#endif // SLINKY_SHARE_EE7A20DC5FDD87278217

#include "../runtime/native/verified/module_access_helpers.hpp"
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

// 0x23170 / 0x9dc0 reload bridge pointers between yaw and pitch, retaining the player.
static std::uint64_t player_angles(GameAccessBridge *bridge, Word player) {
    using Getter_Free_Look = float (*)(Word *, Word, Word);
    const auto yaw = slot<Getter_Free_Look>(bridge, 0x330)(bridge->environment, player,
                                                           identifier(bridge, 0x298));
    const auto pitch = slot<Getter_Free_Look>(bridge, 0x330)(bridge->environment, player,
                                                             identifier(bridge, 0x2a0));
    return std::bit_cast<std::uint64_t>(CameraRotation{yaw, pitch});
}
static Word options(GameAccessBridge *bridge, Word client) {
    return recovered_access_helper(bridge, 0x22cf0, client, 0, 0);
}
// 0x25310 and 0x25330.
static std::uint32_t perspective(GameAccessBridge *bridge, Word options_object) {
    using Getter_Free_Look = std::uint32_t (*)(Word *, Word, Word);
    return slot<Getter_Free_Look>(bridge, 0x320)(bridge->environment, options_object,
                                                 identifier(bridge, 0x3c0));
}
static void set_perspective(GameAccessBridge *bridge, Word options_object, std::uint32_t value) {
    using Setter = void (*)(Word *, Word, Word, std::uint32_t);
    slot<Setter>(bridge, 0x368)(bridge->environment, options_object, identifier(bridge, 0x3c0),
                                value);
}
extern "C" __declspec(dllexport) void
recovered_bind_free_look_access(FreeLookDependencies *dependencies) {
    *dependencies = {player_angles, options, perspective, set_perspective};
}

// 0x29fa0 wraps the yaw difference, marks the angle updated, then reloads current yaw.
extern "C" __declspec(dllexport) void
recovered_free_look_restore(CameraAngleState *angles, const AngleWrapConstants *constants,
                            std::uint64_t packed_rotation) {
    const auto incoming = std::bit_cast<CameraRotation>(packed_rotation);
    const auto difference =
        _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(incoming.yaw), _mm_set_ss(angles->rotation.yaw)));
    const auto wrapped = recovered_wrap_angle(difference, constants);
    angles->updated = 1;
    angles->rotation.yaw =
        _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(wrapped), _mm_set_ss(angles->rotation.yaw)));
    angles->rotation.pitch = incoming.pitch;
}

// 0x37020 retains the initial game pointer, but rereads the event flag after options lookup.
extern "C" __declspec(dllexport) void
recovered_free_look_lifecycle(FreeLookEvent *event, Word module_identity,
                              const ChoiceSetting *setting, FreeLookState *state,
                              CameraAngleState *angles, const AngleWrapConstants *constants,
                              const FreeLookDependencies *dependencies) {
    if (event->module != module_identity)
        return;
    auto *game = event->game;
    if (!game->world)
        return;
    if (event->enabled == 1) {
        state->enabled = 1;
        // 0x29f80 / 0x29f90 read the active byte and packed camera rotation.
        state->saved_rotation = angles->active
                                    ? angles->rotation
                                    : std::bit_cast<CameraRotation>(
                                          dependencies->player_angles(game->bridge, game->player));
    }
    const auto options_object = dependencies->options(game->bridge, game->client);
    if (event->enabled) {
        state->saved_perspective = dependencies->perspective(game->bridge, options_object);
        dependencies->set_perspective(game->bridge, options_object, setting->current);
    } else {
        dependencies->set_perspective(game->bridge, options_object, state->saved_perspective);
        if (state->enabled == 1) {
            recovered_free_look_restore(angles, constants,
                                        std::bit_cast<std::uint64_t>(state->saved_rotation));
            state->enabled = 0;
        }
    }
}

// 0x37100 preserves all bytes outside the flag and packed yaw/pitch fields.
extern "C" __declspec(dllexport) void recovered_free_look_rotation(FreeLookRotationEvent *event,
                                                                   const FreeLookState *state) {
    event->override_rotation = 1;
    event->rotation = state->saved_rotation;
}

// 0x37120 and 0x37160 use a single choice record.
extern "C" __declspec(dllexport) void
recovered_free_look_typed_ui(std::uint64_t ui, std::uint64_t layout, ChoiceSetting *setting,
                             const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, setting);
}
extern "C" __declspec(dllexport) void
recovered_free_look_typed_settings(SettingsContext *context, ChoiceSetting *setting,
                                   const ValueSettingsDependencies *dependencies) {
    recovered_choice_settings(context, "target_perspective", setting, dependencies);
}
// END SOURCE modules/Free_Look/Free_Look.cpp

#ifndef SLINKY_SHARE_EB2D7F9A856F31953181
#define SLINKY_SHARE_EB2D7F9A856F31953181
// BEGIN SOURCE modules/Free_Look/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Free_Look/Api.hpp

#endif // SLINKY_SHARE_EB2D7F9A856F31953181

// Convenient borrowed-state interface

namespace shareable {
class FreeLook {
  public:
    static constexpr const char *kName = "Free Look";
    static constexpr const char *kDescription = "Freely move the camera around.";
    explicit FreeLook(std::uint8_t *image) : image_(image) {}
    // Switch to. Config key: target_perspective.
    ChoiceSetting &target_perspective() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2ee118);
    }
    // Option labels observed in the captured metadata.
    enum class TargetPerspectiveMode : std::uint32_t {
        FirstPerson = 0,
        ThirdPerson = 1,
        ThirdPersonReverse = 2
    };
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_free_look_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_free_look_settings(&context, image_, &dependencies);
    }
    static void bindAccess(FreeLookDependencies *dependencies) {
        ::recovered_bind_free_look_access(dependencies);
    }
    static void restore(CameraAngleState *angles, const AngleWrapConstants *constants,
                        std::uint64_t packed_rotation) {
        ::recovered_free_look_restore(angles, constants, packed_rotation);
    }
    static void lifecycle(FreeLookEvent *event, Word module_identity, const ChoiceSetting *setting,
                          FreeLookState *state, CameraAngleState *angles,
                          const AngleWrapConstants *constants,
                          const FreeLookDependencies *dependencies) {
        ::recovered_free_look_lifecycle(event, module_identity, setting, state, angles, constants,
                                        dependencies);
    }
    static void rotation(FreeLookRotationEvent *event, const FreeLookState *state) {
        ::recovered_free_look_rotation(event, state);
    }
    static void typedUi(std::uint64_t ui, std::uint64_t layout, ChoiceSetting *setting,
                        const SurfaceUiDependencies *dependencies) {
        ::recovered_free_look_typed_ui(ui, layout, setting, dependencies);
    }
    static void typedSettings(SettingsContext *context, ChoiceSetting *setting,
                              const ValueSettingsDependencies *dependencies) {
        ::recovered_free_look_typed_settings(context, setting, dependencies);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
