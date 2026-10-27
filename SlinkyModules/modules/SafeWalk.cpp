// Safe Walk

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Safe_Walk.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Safe_Walk.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Safe Walk: lib_win settings 0x41ed0.
// UI 0x41e50.
static constexpr UiStep ui_steps_Surface_Safe_Walk[] = {
    {UiControl::section, "Main", 0},          {UiControl::number, nullptr, 0x2f2240},
    {UiControl::section, "Conditions", 0},    {UiControl::checkbox, nullptr, 0x2f22b8},
    {UiControl::checkbox, nullptr, 0x2f2278}, {UiControl::checkbox, nullptr, 0x2f2298},
};
static constexpr SettingsStep settings_steps_Surface_Safe_Walk[] = {
    {SettingsControl::number, "motion_multiplier", 0x2f2240},
    {SettingsControl::boolean, "require_holding_blocks", 0x2f22b8},
    {SettingsControl::boolean, "require_looking_down", 0x2f2278},
    {SettingsControl::boolean, "require_not_forward", 0x2f2298},
};
static constexpr ModuleSurface surface_Surface_Safe_Walk{
    ui_steps_Surface_Safe_Walk, std::size(ui_steps_Surface_Safe_Walk),
    settings_steps_Surface_Safe_Walk, std::size(settings_steps_Surface_Safe_Walk)};

extern "C" __declspec(dllexport) void
recovered_safe_walk_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                       const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Safe_Walk, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_safe_walk_settings(SettingsContext *context, std::uint8_t *image,
                             const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Safe_Walk, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Safe_Walk.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Safe_Walk/Safe_Walk.cpp
#ifndef SLINKY_SHARE_10E361EFF44ADFD74355
#define SLINKY_SHARE_10E361EFF44ADFD74355
// BEGIN SOURCE native/verified/Safe_Walk.hpp
#include "../runtime/native/verified/No_Hurt_Cam.hpp"
#include "../runtime/native/verified/Keep_Sprint.hpp"
#include "../runtime/native/verified/module_ui_controls.hpp"

struct SafeWalkEvent {
    std::uintptr_t type;
    TimerGame *game;
};
struct SafeWalkSettings {
    NumberSetting speed;
    BooleanSetting require_pitch;
    BooleanSetting require_not_forward;
    BooleanSetting require_block_item;
};
struct SafeWalkConstants {
    float minimum_pitch, unscaled_speed;
};
struct SafeWalkState {
    std::uint8_t allowed;
};
struct SafeWalkDependencies {
    std::uint64_t (*player_angles)(GameAccessBridge *, std::uintptr_t);
    float (*forward_input)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*held_item)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*block_item)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*on_ground)(GameAccessBridge *, std::uintptr_t);
    void (*velocity)(TimerVelocity *, GameAccessBridge *, std::uintptr_t);
    void (*set_velocity)(GameAccessBridge *, std::uintptr_t, const TimerVelocity *);
    std::uintptr_t (*client)(GameAccessBridge *);
    std::uintptr_t (*entity)(GameAccessBridge *, std::uintptr_t);
    std::uint64_t (*same_object)(std::uintptr_t *, std::uintptr_t, std::uintptr_t);
    std::uint64_t (*fallback)(GameAccessBridge *, std::uintptr_t);
};
static_assert(sizeof(SafeWalkEvent) == 16);
static_assert(sizeof(SafeWalkSettings) == 152);
static_assert(offsetof(SafeWalkSettings, require_pitch) == 56);
static_assert(offsetof(SafeWalkSettings, require_not_forward) == 88);
static_assert(offsetof(SafeWalkSettings, require_block_item) == 120);
static_assert(sizeof(SafeWalkConstants) == 8);
static_assert(sizeof(SafeWalkDependencies) == 88);

extern "C" {
__declspec(dllexport) void recovered_bind_safe_walk_access(SafeWalkDependencies *);
__declspec(dllexport) void recovered_safe_walk_update(SafeWalkEvent *, const SafeWalkSettings *,
                                                      SafeWalkState *, const SafeWalkConstants *,
                                                      const SafeWalkDependencies *);
__declspec(dllexport) std::uint8_t recovered_safe_walk_state(const SafeWalkState *);
__declspec(dllexport) std::uint64_t
recovered_safe_walk_query_typed(const std::uint8_t *const *metadata, std::uintptr_t *environment,
                                std::uintptr_t target, const NoHurtCamDescriptor *const *descriptor,
                                const SafeWalkState *, const SafeWalkDependencies *);
__declspec(dllexport) std::uint64_t recovered_safe_walk_typed_ui(std::uint64_t ui,
                                                                 std::uint64_t layout,
                                                                 SafeWalkSettings *, UiDirtyState *,
                                                                 const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_safe_walk_typed_settings(SettingsContext *, SafeWalkSettings *,
                                                              const SettingsDependencies *,
                                                              const ValueSettingsDependencies *);
}
// END SOURCE native/verified/Safe_Walk.hpp

#endif // SLINKY_SHARE_10E361EFF44ADFD74355

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
// 0x23ac0 supplies the float tested by the persisted "require_not_forward" flag.
static float forward_input(GameAccessBridge *bridge, Word player) {
    using Getter = float (*)(Word *, Word, Word);
    return slot<Getter>(bridge, 0x330)(bridge->environment, player, identifier(bridge, 0x540));
}
// 0x28b00 calls 0x24240 and 0x24280, testing the latter's full low DWORD.
static std::uint8_t block_item(GameAccessBridge *bridge, Word item) {
    if (!item)
        return 0;
    using Block = Word (*)(Word *, Word, Word, Word);
    const auto block = slot<Block>(bridge, 0x390)(bridge->environment, identifier(bridge, 0x430),
                                                  identifier(bridge, 0x440), item);
    if (!block)
        return 0;
    using Integer = std::uint32_t (*)(Word *, Word, Word, Word);
    return slot<Integer>(bridge, 0x408)(bridge->environment, identifier(bridge, 0x430),
                                        identifier(bridge, 0x438), block) != 0;
}
static std::uint64_t same_object(Word *environment, Word entity, Word target) {
    using Call = std::uint64_t (*)(Word *, Word, Word);
    const auto *table = reinterpret_cast<const Word *>(*environment);
    return reinterpret_cast<Call>(table[0xc0 / sizeof(Word)])(environment, entity, target);
}
// 0x236f0 normalizes only AL, retaining the upper returned bytes.
static std::uint64_t fallback(GameAccessBridge *bridge, Word target) {
    using Call = std::uint64_t (*)(Word *, Word, Word);
    const auto result =
        slot<Call>(bridge, 0x128)(bridge->environment, target, identifier(bridge, 0x238));
    return (result & ~std::uint64_t{0xff}) | ((result & 0xff) != 0);
}
extern "C" __declspec(dllexport) void
recovered_bind_safe_walk_access(SafeWalkDependencies *dependencies) {
    NoHurtCamDependencies camera;
    recovered_bind_no_hurt_cam_access(&camera);
    TimerDependencies movement;
    recovered_bind_timer_access(&movement);
    *dependencies = {camera.player_angles,
                     forward_input,
                     recovered_game_item_object,
                     block_item,
                     movement.on_ground,
                     movement.velocity,
                     recovered_keep_sprint_set_velocity,
                     camera.client,
                     camera.entity,
                     same_object,
                     fallback};
}

// 0x41d30 keeps the initial game pointer and reloads its bridge/player between helpers.
extern "C" __declspec(dllexport) void
recovered_safe_walk_update(SafeWalkEvent *event, const SafeWalkSettings *settings,
                           SafeWalkState *state, const SafeWalkConstants *constants,
                           const SafeWalkDependencies *dependencies) {
    auto *game = event->game;
    if (game->ready != 1)
        return;
    if (settings->require_pitch.current == 1) {
        const auto rotation =
            std::bit_cast<CameraRotation>(dependencies->player_angles(game->bridge, game->player));
        if (constants->minimum_pitch > rotation.pitch) {
            state->allowed = 0;
            return;
        }
    }
    if (settings->require_not_forward.current == 1 &&
        dependencies->forward_input(game->bridge, game->player) > 0.0f) {
        state->allowed = 0;
        return;
    }
    if (settings->require_block_item.current == 1) {
        const auto item = dependencies->held_item(game->bridge, game->player);
        if (!dependencies->block_item(game->bridge, item)) {
            state->allowed = 0;
            return;
        }
    }
    state->allowed = 1;
    if (dependencies->on_ground(game->bridge, game->player) &&
        settings->speed.current != constants->unscaled_speed) {
        TimerVelocity movement;
        dependencies->velocity(&movement, game->bridge, game->player);
        const auto factor =
            _mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(settings->speed.current)));
        movement.x = _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(movement.x), _mm_set_sd(factor)));
        movement.z = _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(factor), _mm_set_sd(movement.z)));
        const auto copy = movement;
        dependencies->set_velocity(game->bridge, game->player, &copy);
    }
}
// 0x41d20 exposes the raw saved flag.
extern "C" __declspec(dllexport) std::uint8_t
recovered_safe_walk_state(const SafeWalkState *state) {
    return state->allowed;
}
// 0x86e0 captures metadata once; the query uses the flag left by the update.
extern "C" __declspec(dllexport) std::uint64_t
recovered_safe_walk_query_typed(const std::uint8_t *const *metadata, Word *environment, Word target,
                                const NoHurtCamDescriptor *const *descriptor,
                                const SafeWalkState *state,
                                const SafeWalkDependencies *dependencies) {
    GameAccessBridge bridge{*metadata, environment};
    if ((*descriptor)->enabled == 1) {
        const auto client = dependencies->client(&bridge);
        const auto entity = dependencies->entity(&bridge, client);
        if (entity && (dependencies->same_object(bridge.environment, entity, target) & 0xff) &&
            recovered_safe_walk_state(state))
            return 1;
    }
    return dependencies->fallback(&bridge, target);
}

// 0x41e50 uses the shared controls, including the final checkbox's dirty update and return.
extern "C" __declspec(dllexport) std::uint64_t
recovered_safe_walk_typed_ui(std::uint64_t ui, std::uint64_t layout, SafeWalkSettings *settings,
                             UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Main");
    recovered_number_control(layout, ui, &settings->speed, dirty, &endpoints->controls);
    endpoints->section(ui, layout, "Conditions");
    recovered_checkbox_control(layout, ui, &settings->require_block_item, dirty,
                               &endpoints->controls);
    recovered_checkbox_control(layout, ui, &settings->require_pitch, dirty, &endpoints->controls);
    return recovered_checkbox_control(layout, ui, &settings->require_not_forward, dirty,
                                      &endpoints->controls);
}
// 0x41ed0 calls the same number/Boolean helpers for all four persisted keys.
extern "C" __declspec(dllexport) void
recovered_safe_walk_typed_settings(SettingsContext *context, SafeWalkSettings *settings,
                                   const SettingsDependencies *booleans,
                                   const ValueSettingsDependencies *numbers) {
    recovered_number_settings(context, "motion_multiplier", &settings->speed, numbers);
    recovered_boolean_settings(context, "require_holding_blocks", &settings->require_block_item,
                               booleans);
    recovered_boolean_settings(context, "require_looking_down", &settings->require_pitch, booleans);
    recovered_boolean_settings(context, "require_not_forward", &settings->require_not_forward,
                               booleans);
}
// END SOURCE modules/Safe_Walk/Safe_Walk.cpp

#ifndef SLINKY_SHARE_739D7201DDA1E37EE0FC
#define SLINKY_SHARE_739D7201DDA1E37EE0FC
// BEGIN SOURCE modules/Safe_Walk/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Safe_Walk/Api.hpp

#endif // SLINKY_SHARE_739D7201DDA1E37EE0FC

// Convenient borrowed-state interface

namespace shareable {
class SafeWalk {
  public:
    static constexpr const char *kName = "Safe Walk";
    static constexpr const char *kDescription = "Prevents you from walking off ledges.";
    explicit SafeWalk(std::uint8_t *image) : image_(image) {}
    // Motion. Config key: motion_multiplier.
    NumberSetting &motion_multiplier() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f2240);
    }
    // Holding blocks. Config key: require_holding_blocks.
    BooleanSetting &require_holding_blocks() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f22b8);
    }
    // Looking down. Config key: require_looking_down.
    BooleanSetting &require_looking_down() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f2278);
    }
    // Not moving forward. Config key: require_not_forward.
    BooleanSetting &require_not_forward() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f2298);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_safe_walk_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_safe_walk_settings(&context, image_, &dependencies);
    }
    static void bindAccess(SafeWalkDependencies *dependencies) {
        ::recovered_bind_safe_walk_access(dependencies);
    }
    static void update(SafeWalkEvent *event, const SafeWalkSettings *settings, SafeWalkState *state,
                       const SafeWalkConstants *constants,
                       const SafeWalkDependencies *dependencies) {
        ::recovered_safe_walk_update(event, settings, state, constants, dependencies);
    }
    static std::uint8_t state(const SafeWalkState *state) {
        return ::recovered_safe_walk_state(state);
    }
    static std::uint64_t queryTyped(const std::uint8_t *const *metadata, Word *environment,
                                    Word target, const NoHurtCamDescriptor *const *descriptor,
                                    const SafeWalkState *state,
                                    const SafeWalkDependencies *dependencies) {
        return ::recovered_safe_walk_query_typed(metadata, environment, target, descriptor, state,
                                                 dependencies);
    }
    static std::uint64_t typedUi(std::uint64_t ui, std::uint64_t layout, SafeWalkSettings *settings,
                                 UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
        return ::recovered_safe_walk_typed_ui(ui, layout, settings, dirty, endpoints);
    }
    static void typedSettings(SettingsContext *context, SafeWalkSettings *settings,
                              const SettingsDependencies *booleans,
                              const ValueSettingsDependencies *numbers) {
        ::recovered_safe_walk_typed_settings(context, settings, booleans, numbers);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
