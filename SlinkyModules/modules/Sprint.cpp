// Sprint

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Sprint.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Sprint.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Sprint: lib_win settings 0x35f60.
// UI 0x35ef0.
static constexpr UiStep ui_steps_Surface_Sprint[] = {
    {UiControl::section, "Allow while", 0},   {UiControl::checkbox, nullptr, 0x2eda70},
    {UiControl::checkbox, nullptr, 0x2eda90}, {UiControl::checkbox, nullptr, 0x2edab0},
    {UiControl::checkbox, nullptr, 0x2eda50},
};
static constexpr SettingsStep settings_steps_Surface_Sprint[] = {
    {SettingsControl::boolean, "while_using_item", 0x2eda70},
    {SettingsControl::boolean, "while_backwards", 0x2eda90},
    {SettingsControl::boolean, "while_sideways", 0x2edab0},
    {SettingsControl::boolean, "while_in_gui", 0x2eda50},
};
static constexpr ModuleSurface surface_Surface_Sprint{
    ui_steps_Surface_Sprint, std::size(ui_steps_Surface_Sprint), settings_steps_Surface_Sprint,
    std::size(settings_steps_Surface_Sprint)};

extern "C" __declspec(dllexport) void
recovered_sprint_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Sprint, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_sprint_settings(SettingsContext *context, std::uint8_t *image,
                          const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Sprint, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Sprint.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Sprint/Sprint.cpp
#ifndef SLINKY_SHARE_C31B512FB5954E922485
#define SLINKY_SHARE_C31B512FB5954E922485
// BEGIN SOURCE native/verified/Sprint.hpp
#include "../runtime/native/verified/module_game_access.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include <cstddef>
#include <cstdint>

struct SprintGame {
    GameAccessBridge *bridge;
    std::uintptr_t reserved[2];
    std::uintptr_t client;
    std::uintptr_t reserved2;
    std::uintptr_t player;
};

struct SprintEvent {
    std::uintptr_t event_type;
    SprintGame *game;
    float sideways;
    float forward;
    float scale;
};

struct SprintSettings {
    BooleanSetting while_in_gui;
    BooleanSetting while_using_item;
    BooleanSetting while_backwards;
    BooleanSetting while_sideways;
};

struct SprintDependencies {
    std::uintptr_t (*screen)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*options)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*sprint_key)(GameAccessBridge *, std::uintptr_t);
    void (*set_key)(GameAccessBridge *, std::uintptr_t, std::uint8_t);
    std::uint8_t (*ready)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*using_item)(GameAccessBridge *, std::uintptr_t);
    void (*set_sprinting)(GameAccessBridge *, std::uintptr_t, std::uint8_t);
};

static_assert(sizeof(SprintGame) == 48);
static_assert(offsetof(SprintGame, player) == 40);
static_assert(sizeof(SprintEvent) == 32);
static_assert(offsetof(SprintEvent, forward) == 20);
static_assert(offsetof(SprintEvent, scale) == 24);
static_assert(sizeof(SprintSettings) == 128);
static_assert(offsetof(SprintSettings, while_using_item) == 32);
static_assert(offsetof(SprintSettings, while_backwards) == 64);
static_assert(offsetof(SprintSettings, while_sideways) == 96);
static_assert(sizeof(SprintDependencies) == 56);

extern "C" {
__declspec(dllexport) void recovered_sprint_update(SprintEvent *, const SprintSettings *,
                                                   std::uint8_t *last_state,
                                                   const SprintDependencies *);
__declspec(dllexport) void recovered_sprint_movement(SprintEvent *, const SprintSettings *,
                                                     const SprintDependencies *);
__declspec(dllexport) std::uintptr_t recovered_sprint_screen(GameAccessBridge *,
                                                             std::uintptr_t client);
__declspec(dllexport) std::uintptr_t recovered_sprint_key(GameAccessBridge *,
                                                          std::uintptr_t options);
__declspec(dllexport) void recovered_sprint_set_player(GameAccessBridge *, std::uintptr_t player,
                                                       std::uint8_t value);
__declspec(dllexport) void recovered_bind_sprint_access(SprintDependencies *);
__declspec(dllexport) void recovered_sprint_typed_ui(std::uint64_t ui, std::uint64_t layout,
                                                     SprintSettings *,
                                                     const SurfaceUiDependencies *);
__declspec(dllexport) void recovered_sprint_typed_settings(SettingsContext *, SprintSettings *,
                                                           const SettingsDependencies *);
}
// END SOURCE native/verified/Sprint.hpp

#endif // SLINKY_SHARE_C31B512FB5954E922485

#include "../runtime/native/verified/module_access_helpers.hpp"
#include <cstring>

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

// 0x22c90 reloads both bridge pointers after fetching the screen object.
extern "C" __declspec(dllexport) Word recovered_sprint_screen(GameAccessBridge *bridge,
                                                              Word client) {
    using ObjectField = Word (*)(Word *, Word, Word);
    using Predicate = std::uint8_t (*)(Word *, Word, Word);
    const auto screen =
        slot<ObjectField>(bridge, 0x2f8)(bridge->environment, client, identifier(bridge, 0x1c8));
    return slot<Predicate>(bridge, 0x100)(bridge->environment, screen, identifier(bridge, 0x4d8))
               ? screen
               : 0;
}

// 0x25210 reads the version after the array getter returns. Zero selects 17; nonzero selects 8.
extern "C" __declspec(dllexport) Word recovered_sprint_key(GameAccessBridge *bridge, Word options) {
    using ObjectField = Word (*)(Word *, Word, Word);
    using ArrayElement = Word (*)(Word *, Word, std::int32_t);
    const auto array =
        slot<ObjectField>(bridge, 0x2f8)(bridge->environment, options, identifier(bridge, 0x3b8));
    std::uint32_t version;
    std::memcpy(&version, bridge->metadata, sizeof(version));
    return slot<ArrayElement>(bridge, 0x568)(bridge->environment, array, version == 0 ? 17 : 8);
}

// 0x236c0 promotes the Boolean argument to int for the variadic JNI method.
extern "C" __declspec(dllexport) void recovered_sprint_set_player(GameAccessBridge *bridge,
                                                                  Word player, std::uint8_t value) {
    using VoidMethod = void (*)(Word *, Word, Word, ...);
    slot<VoidMethod>(bridge, 0x1e8)(bridge->environment, player, identifier(bridge, 0x230),
                                    static_cast<int>(value));
}

static Word options(GameAccessBridge *bridge, Word client) {
    return recovered_access_helper(bridge, 0x22cf0, client, 0, 0);
}

static void set_key(GameAccessBridge *bridge, Word key, std::uint8_t value) {
    recovered_access_helper(bridge, 0x25460, key, value, 0);
}

extern "C" __declspec(dllexport) void
recovered_bind_sprint_access(SprintDependencies *dependencies) {
    dependencies->screen = recovered_sprint_screen;
    dependencies->options = options;
    dependencies->sprint_key = recovered_sprint_key;
    dependencies->set_key = set_key;
    dependencies->ready = recovered_game_sprinting;
    dependencies->using_item = recovered_game_using_item;
    dependencies->set_sprinting = recovered_sprint_set_player;
}

// 0x35d80. When a player exists but active is zero, last_state is retained.
extern "C" __declspec(dllexport) void
recovered_sprint_update(SprintEvent *event, const SprintSettings *settings,
                        std::uint8_t *last_state, const SprintDependencies *dependencies) {
    auto *game = event->game;
    const auto screen = dependencies->screen(game->bridge, game->client);
    const auto active =
        static_cast<std::uint8_t>(((screen == 0) | settings->while_in_gui.current) & 1);
    const auto configuration = dependencies->options(game->bridge, game->client);
    const auto key = dependencies->sprint_key(game->bridge, configuration);
    dependencies->set_key(game->bridge, key, active);
    if (game->player) {
        if (!active) {
            if (*last_state == 1)
                dependencies->set_sprinting(game->bridge, game->player, 0);
            return;
        }
        if (dependencies->ready(game->bridge, game->player))
            dependencies->set_sprinting(game->bridge, game->player, 1);
    }
    *last_state = active;
}

// 0x35e30 converts the scale to double for multiplication, then rounds back to float.
extern "C" __declspec(dllexport) void
recovered_sprint_movement(SprintEvent *event, const SprintSettings *settings,
                          const SprintDependencies *dependencies) {
    auto *game = event->game;
    if (event->forward == 0.0f && event->sideways == 0.0f)
        return;
    const auto using_item = dependencies->using_item(game->bridge, game->player);
    if (using_item && !settings->while_using_item.current)
        return;
    const auto forward = event->forward;
    if (forward < 0.0f) {
        if (!settings->while_backwards.current)
            return;
    } else if (forward == 0.0f && event->sideways != 0.0f) {
        if (!settings->while_sideways.current)
            return;
    } else if (!using_item)
        return;
    event->scale = static_cast<float>(static_cast<double>(event->scale) * 1.3);
    dependencies->set_sprinting(game->bridge, game->player, 1);
}

// 0x35ef0. Control order follows the original, with GUI last.
extern "C" __declspec(dllexport) void
recovered_sprint_typed_ui(std::uint64_t ui, std::uint64_t layout, SprintSettings *settings,
                          const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Allow while");
    dependencies->checkbox(layout, ui, &settings->while_using_item);
    dependencies->checkbox(layout, ui, &settings->while_backwards);
    dependencies->checkbox(layout, ui, &settings->while_sideways);
    dependencies->checkbox(layout, ui, &settings->while_in_gui);
}

// 0x35f60 uses the same record order and shared Boolean settings helper.
extern "C" __declspec(dllexport) void
recovered_sprint_typed_settings(SettingsContext *context, SprintSettings *settings,
                                const SettingsDependencies *dependencies) {
    recovered_boolean_settings(context, "while_using_item", &settings->while_using_item,
                               dependencies);
    recovered_boolean_settings(context, "while_backwards", &settings->while_backwards,
                               dependencies);
    recovered_boolean_settings(context, "while_sideways", &settings->while_sideways, dependencies);
    recovered_boolean_settings(context, "while_in_gui", &settings->while_in_gui, dependencies);
}
// END SOURCE modules/Sprint/Sprint.cpp

#ifndef SLINKY_SHARE_F12359B77EA4D284CB89
#define SLINKY_SHARE_F12359B77EA4D284CB89
// BEGIN SOURCE modules/Sprint/Api.hpp
// Reuse the exact recovered ABI records and function declarations.

#ifndef SLINKY_SHARE_313109E60B317702A855
#define SLINKY_SHARE_313109E60B317702A855
// BEGIN SOURCE native/verified/Sprint_Reset.hpp
#include "../runtime/native/verified/module_choice_ui.hpp"
#include "../runtime/native/verified/module_format.hpp"
#include <cstddef>

struct SprintResetSettings {
    ChoiceSetting mode;
    std::uint8_t choice_flag, padding[7];
    NumberSetting delay;
    BooleanSetting randomize, wait_for_damage, require_weapon;
    NumberSetting duration;
};
static_assert(sizeof(SprintResetSettings) == 272);
static_assert(offsetof(SprintResetSettings, delay) == 64);
static_assert(offsetof(SprintResetSettings, randomize) == 120);
static_assert(offsetof(SprintResetSettings, wait_for_damage) == 152);
static_assert(offsetof(SprintResetSettings, require_weapon) == 184);
static_assert(offsetof(SprintResetSettings, duration) == 216);

extern "C" {
__declspec(dllexport) std::uint64_t
recovered_sprint_reset_typed_ui(std::uint64_t ui, std::uint64_t layout, SprintResetSettings *,
                                UiDirtyState *, const ChoiceUiEndpoints *);
__declspec(dllexport) void recovered_sprint_reset_typed_settings(SettingsContext *,
                                                                 SprintResetSettings *,
                                                                 const SettingsDependencies *,
                                                                 const ValueSettingsDependencies *);
__declspec(dllexport) std::uint64_t recovered_sprint_reset_label(char *destination,
                                                                 const ChoiceSetting *,
                                                                 const char *const *labels,
                                                                 FormatState *);
}
// END SOURCE native/verified/Sprint_Reset.hpp

#endif // SLINKY_SHARE_313109E60B317702A855

#ifndef SLINKY_SHARE_0656B1C9495EA064A9F0
#define SLINKY_SHARE_0656B1C9495EA064A9F0
// BEGIN SOURCE native/verified/Sprint_Reset_runtime.hpp
#include "../runtime/native/verified/Timer.hpp"
#include "../runtime/native/verified/Weapons.hpp"
#include "../runtime/native/verified/module_random_policy.hpp"

struct SprintResetEvent {
    std::uintptr_t event_type;
    TimerGame *game;
};
struct SprintResetState {
    volatile std::uint32_t phase;
    volatile float timer;
    volatile double last_sample_time;
    volatile std::uint8_t have_state;
    std::uint8_t padding[3];
    volatile std::uint32_t sample_count;
    SmoothRandomState delay_random, duration_random, gate_random;
};
struct SprintResetConstants {
    double minimum_elapsed;
    float decrement, one;
    double suppression_window;
    float gate_low, gate_high, two;
    std::uint32_t padding;
    double delay_window;
};
struct SprintResetDependencies {
    std::uint32_t (*counter)(GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*other_counter)(GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*damage)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*options)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*forward_key)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*sneak_key)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*sprint_key)(GameAccessBridge *, std::uintptr_t);
    void (*set_sprinting)(GameAccessBridge *, std::uintptr_t, std::uint8_t);
    std::uint32_t (*physical_key)(GameAccessBridge *, std::uintptr_t);
    void (*set_key)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    // The boundary provider records R8 after each JNI call. 0x3b150 retains its upper DWORD bytes.
    const volatile std::uint32_t *post_call_r8;
    std::uint64_t *frequency_bits;
    const std::uint8_t *frequency_target, *counter_target;
    WeaponCache *weapon_cache;
    const WeaponSettings *weapon_settings;
    const ItemPolicyTable *weapon_policy;
    const WeaponDependencies *weapons;
    RandomState *random;
    const RandomConstants *random_constants;
    const RandomPolicyConstants *policy_constants;
    const double *policy_clock;
};
static_assert(sizeof(SprintResetEvent) == 16);
static_assert(sizeof(SprintResetState) == 72);
static_assert(offsetof(SprintResetState, delay_random) == 24);
static_assert(offsetof(SprintResetState, duration_random) == 40);
static_assert(offsetof(SprintResetState, gate_random) == 56);
static_assert(sizeof(SprintResetConstants) == 48);
static_assert(offsetof(SprintResetConstants, delay_window) == 40);
static_assert(sizeof(SprintResetDependencies) == 176);

extern "C" {
__declspec(dllexport) void recovered_bind_sprint_reset_access(SprintResetDependencies *);
__declspec(dllexport) std::uint32_t recovered_sprint_reset_other_counter(GameAccessBridge *,
                                                                         std::uintptr_t);
__declspec(dllexport) std::uint32_t recovered_sprint_reset_physical_word(GameAccessBridge *,
                                                                         std::uintptr_t);
__declspec(dllexport) void recovered_sprint_reset_action(TimerGame *, const SprintResetSettings *,
                                                         std::uint32_t active_word,
                                                         const SprintResetDependencies *);
__declspec(dllexport) void
recovered_sprint_reset_update(SprintResetEvent *, const SprintResetSettings *, SprintResetState *,
                              const SprintResetConstants *, const SprintResetDependencies *);
}
// END SOURCE native/verified/Sprint_Reset_runtime.hpp

#endif // SLINKY_SHARE_0656B1C9495EA064A9F0
// END SOURCE modules/Sprint/Api.hpp

#endif // SLINKY_SHARE_F12359B77EA4D284CB89

// Convenient borrowed-state interface

namespace shareable {
class Sprint {
  public:
    static constexpr const char *kName = "Sprint";
    static constexpr const char *kDescription = "Automatically sprints for you.";
    explicit Sprint(std::uint8_t *image) : image_(image) {}
    // Using item. Config key: while_using_item.
    BooleanSetting &while_using_item() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eda70);
    }
    // Backwards. Config key: while_backwards.
    BooleanSetting &while_backwards() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eda90);
    }
    // Sideways. Config key: while_sideways.
    BooleanSetting &while_sideways() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2edab0);
    }
    // In inventory. Config key: while_in_gui.
    BooleanSetting &while_in_gui() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eda50);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_sprint_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_sprint_settings(&context, image_, &dependencies);
    }
    static Word screen(GameAccessBridge *bridge, Word client) {
        return ::recovered_sprint_screen(bridge, client);
    }
    static Word key(GameAccessBridge *bridge, Word options) {
        return ::recovered_sprint_key(bridge, options);
    }
    static void setPlayer(GameAccessBridge *bridge, Word player, std::uint8_t value) {
        ::recovered_sprint_set_player(bridge, player, value);
    }
    static void bindAccess(SprintDependencies *dependencies) {
        ::recovered_bind_sprint_access(dependencies);
    }
    static void update(SprintEvent *event, const SprintSettings *settings, std::uint8_t *last_state,
                       const SprintDependencies *dependencies) {
        ::recovered_sprint_update(event, settings, last_state, dependencies);
    }
    static void movement(SprintEvent *event, const SprintSettings *settings,
                         const SprintDependencies *dependencies) {
        ::recovered_sprint_movement(event, settings, dependencies);
    }
    static void typedUi(std::uint64_t ui, std::uint64_t layout, SprintSettings *settings,
                        const SurfaceUiDependencies *dependencies) {
        ::recovered_sprint_typed_ui(ui, layout, settings, dependencies);
    }
    static void typedSettings(SettingsContext *context, SprintSettings *settings,
                              const SettingsDependencies *dependencies) {
        ::recovered_sprint_typed_settings(context, settings, dependencies);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
