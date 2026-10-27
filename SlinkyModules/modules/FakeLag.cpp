// Fake Lag

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Fake_Lag.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Fake_Lag.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Fake Lag: lib_win settings 0x32e20.
// UI 0x32d60.
static constexpr UiStep ui_steps_Surface_Fake_Lag[] = {
    {UiControl::section, "Delay", 0},         {UiControl::choice, nullptr, 0x2ebf70},
    {UiControl::number, nullptr, 0x2ebed0},   {UiControl::number, nullptr, 0x2ebf08},
    {UiControl::checkbox, nullptr, 0x2ebf40}, {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2ebfd0}, {UiControl::checkbox, nullptr, 0x2ebff0},
    {UiControl::checkbox, nullptr, 0x2ebfb0},
};
static constexpr SettingsStep settings_steps_Surface_Fake_Lag[] = {
    {SettingsControl::choice, "mode", 0x2ebf70},
    {SettingsControl::number, "inbound", 0x2ebed0},
    {SettingsControl::number, "outbound", 0x2ebf08},
    {SettingsControl::boolean, "realtime_damage", 0x2ebf40},
    {SettingsControl::boolean, "require_weapon", 0x2ebfd0},
    {SettingsControl::boolean, "require_attack", 0x2ebff0},
    {SettingsControl::boolean, "require_ingame", 0x2ebfb0},
};
static constexpr ModuleSurface surface_Surface_Fake_Lag{
    ui_steps_Surface_Fake_Lag, std::size(ui_steps_Surface_Fake_Lag),
    settings_steps_Surface_Fake_Lag, std::size(settings_steps_Surface_Fake_Lag)};

extern "C" __declspec(dllexport) void
recovered_fake_lag_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                      const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Fake_Lag, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_fake_lag_settings(SettingsContext *context, std::uint8_t *image,
                            const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Fake_Lag, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Fake_Lag.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Fake_Lag
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Fake_Lag.cpp
static constexpr UiStep surface_fake_lag_ui_steps[] = {
    {UiControl::section, "Delay", 0},         {UiControl::choice, nullptr, 0x2ebf70},
    {UiControl::number, nullptr, 0x2ebed0},   {UiControl::number, nullptr, 0x2ebf08},
    {UiControl::checkbox, nullptr, 0x2ebf40}, {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2ebfd0}, {UiControl::checkbox, nullptr, 0x2ebff0},
    {UiControl::checkbox, nullptr, 0x2ebfb0},
};
static constexpr SettingsStep surface_fake_lag_settings_steps[] = {
    {SettingsControl::choice, "mode", 0x2ebf70},
    {SettingsControl::number, "inbound", 0x2ebed0},
    {SettingsControl::number, "outbound", 0x2ebf08},
    {SettingsControl::boolean, "realtime_damage", 0x2ebf40},
    {SettingsControl::boolean, "require_weapon", 0x2ebfd0},
    {SettingsControl::boolean, "require_attack", 0x2ebff0},
    {SettingsControl::boolean, "require_ingame", 0x2ebfb0},
};
static constexpr ModuleSurface surface_fake_lag_surface{
    surface_fake_lag_ui_steps, std::size(surface_fake_lag_ui_steps),
    surface_fake_lag_settings_steps, std::size(surface_fake_lag_settings_steps)};

extern "C" __declspec(dllexport) void
recovered_fake_lag_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                            const BoundSurfaceUiDependencies *dependencies) {
    render_module_surface(surface_fake_lag_surface, ui, layout, image, *dependencies);
}
// END SOURCE shared/BoundSurfaces.cpp@Fake_Lag

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Fake_Lag/Bindings.cpp
#ifndef SLINKY_SHARE_E4F25B90EAA79F2554FF
#define SLINKY_SHARE_E4F25B90EAA79F2554FF
// BEGIN SOURCE modules/Fake_Lag/FakeLag.hpp
#ifndef SEMANTIC_FAKE_LAG_H
#define SEMANTIC_FAKE_LAG_H

#include <stdint.h>

typedef struct {
    volatile uint32_t last_state;     /* Native RVA 0x2fa304 */
    volatile uint32_t pulse_timer;    /* Native RVA 0x2fa308 */
    volatile uint32_t inbound_value;  /* Native RVA 0x2fa30c */
    volatile uint32_t outbound_value; /* Native RVA 0x2fa310 */
    volatile uint8_t shared_byte;     /* Native RVA 0x2fa314 */
    volatile uint8_t inbound_block;   /* Native RVA 0x2fa315 */
    volatile uint8_t outbound_block;  /* Native RVA 0x2fa316 */
    uint8_t reserved;
    volatile uint16_t inbound_amount;  /* Native RVA 0x2fa318 */
    volatile uint16_t outbound_amount; /* Native RVA 0x2fa31a */
} fake_lag_state;

struct fake_lag_config {
    volatile float &inbound_delta, &outbound_delta;
    volatile uint8_t &inbound_token;
    volatile uint32_t &advance_mode;
    volatile uint8_t &require_ingame, &require_weapon, &require_attack;
    explicit fake_lag_config(uint8_t *image)
        : inbound_delta(*reinterpret_cast<volatile float *>(image + 0x2ebf00)),
          outbound_delta(*reinterpret_cast<volatile float *>(image + 0x2ebf38)),
          inbound_token(image[0x2ebf58]),
          advance_mode(*reinterpret_cast<volatile uint32_t *>(image + 0x2ebfa0)),
          require_ingame(image[0x2ebfc8]), require_weapon(image[0x2ebfe8]),
          require_attack(image[0x2ec008]) {}
};
enum class FakeLagMode : uint32_t { Static = 0, Pulse = 1 };

typedef struct {
    uint64_t object;
    uint8_t reserved0[0x18];
    uint64_t required_object;
    uint64_t target;
    uint8_t reserved1[0x10];
    uint8_t in_game;
} fake_lag_event0_payload;

typedef struct {
    uint64_t reserved;
    fake_lag_event0_payload *payload; /* Native callback reads this at +8 */
} fake_lag_event0;

typedef struct {
    uint32_t type;
    uint32_t reserved0;
    uint64_t object_a;
    uint64_t object_b;
    int64_t remaining;
    uint32_t reserved1;
    uint32_t result; /* Native callback writes this at +0x24 */
} fake_lag_packet_event;

typedef struct {
    int32_t (*sample_state)(uint64_t object, uint64_t target, void *user);
    uint8_t (*weapon_allowed)(uint64_t object, uint64_t target, void *user);
    uint64_t (*packet_predicate_a)(uint64_t object_a, uint64_t object_b, void *user);
    uint64_t (*packet_predicate_b)(uint64_t object_a, uint64_t object_b, void *user);
    uint64_t (*packet_predicate_c)(uint64_t object_a, uint64_t object_b, void *user);
} fake_lag_dependencies;

void bind_fake_lag_known(fake_lag_dependencies *);

/* Event 0 callback at RVA 0x32b30. Query implementations are injected. */
#ifdef __cplusplus
extern "C" {
#endif
__declspec(dllexport) uint32_t semantic_fake_lag_update(fake_lag_state *state,
                                                        fake_lag_config *config,
                                                        fake_lag_event0 *event,
                                                        const fake_lag_dependencies *dependencies,
                                                        void *user);

/* Event 2/3 callback at RVA 0x32cb0. Both registry entries share this body. */
__declspec(dllexport) void semantic_fake_lag_packet(fake_lag_state *state,
                                                    volatile fake_lag_packet_event *event,
                                                    const fake_lag_dependencies *dependencies,
                                                    void *user);
#ifdef __cplusplus
}
#endif

#endif
// END SOURCE modules/Fake_Lag/FakeLag.hpp

#endif // SLINKY_SHARE_E4F25B90EAA79F2554FF

#include "../runtime/modules/Aim_Assist/Support.hpp"
#include "../runtime/shared/JniAccess.hpp"
static int32_t sampled(uint64_t bridge, uint64_t entity, void *) {
    return recovered_game_last_attacker_time(reinterpret_cast<GameAccessBridge *>(bridge), entity);
}
static uint8_t weapon(uint64_t bridge, uint64_t entity, void *context) {
    return static_cast<aim_assist::Runtime *>(context)->isWeapon(
        reinterpret_cast<GameAccessBridge *>(bridge), reinterpret_cast<void *>(entity));
}
void bind_fake_lag_known(fake_lag_dependencies *dependencies) {
    dependencies->sample_state = sampled;
    dependencies->weapon_allowed = weapon;
    dependencies->packet_predicate_a = +[](uint64_t a, uint64_t b, void *) -> uint64_t {
        return recovered_jni::instance(recovered_jni::bridge(a), b, 0x850);
    };
    dependencies->packet_predicate_b = +[](uint64_t a, uint64_t b, void *) -> uint64_t {
        return recovered_jni::instance(recovered_jni::bridge(a), b, 0x868);
    };
    dependencies->packet_predicate_c = +[](uint64_t a, uint64_t b, void *) -> uint64_t {
        return recovered_jni::instance(recovered_jni::bridge(a), b, 0x860);
    };
}
static_assert(sizeof(fake_lag_state) == 24);
static_assert(offsetof(fake_lag_state, inbound_amount) == 20);
// END SOURCE modules/Fake_Lag/Bindings.cpp

// BEGIN SOURCE modules/Fake_Lag/FakeLag.cpp
#include <stddef.h>
#include <emmintrin.h>
#include <intrin.h>

static_assert(offsetof(fake_lag_event0, payload) == 8, "event 0 payload offset");
static_assert(offsetof(fake_lag_event0_payload, required_object) == 0x20, "event 0 gate offset");
static_assert(offsetof(fake_lag_event0_payload, target) == 0x28, "event 0 target offset");
static_assert(offsetof(fake_lag_event0_payload, in_game) == 0x40, "event 0 in-game offset");
static_assert(offsetof(fake_lag_packet_event, object_a) == 8, "packet object A offset");
static_assert(offsetof(fake_lag_packet_event, object_b) == 0x10, "packet object B offset");
static_assert(offsetof(fake_lag_packet_event, remaining) == 0x18, "packet delay offset");
static_assert(offsetof(fake_lag_packet_event, result) == 0x24, "packet result offset");

static int32_t cvttss_i32(float value) {
    return _mm_cvttss_si32(_mm_set_ss(value));
}

static int32_t add_i32_and_float_truncate(int32_t value, float increment) {
    __m128 converted = _mm_cvtsi32_ss(_mm_setzero_ps(), value);
    __m128 sum = _mm_add_ss(converted, _mm_set_ss(increment));
    return _mm_cvttss_si32(sum);
}

/* Callback body RVA 0x32b30 (registry event 0). */
__declspec(dllexport) uint32_t semantic_fake_lag_update(fake_lag_state *state,
                                                        fake_lag_config *config,
                                                        fake_lag_event0 *event,
                                                        const fake_lag_dependencies *dependencies,
                                                        void *user) {
    uint32_t result;
    int32_t current;
    int32_t sampled_state;
    uint8_t send;

    current = (int32_t)state->pulse_timer;
    if (current > 0)
        state->pulse_timer = (uint32_t)(current - 1);

    /* MOVZX loads the config byte, then XCHG replaces only the shared byte. */
    (void)_InterlockedExchange8((volatile char *)&state->shared_byte, (char)config->inbound_token);

    if (config->advance_mode == 1) {
        current = (int32_t)state->inbound_value;
        if (current < 1) {
            state->inbound_value =
                (uint32_t)add_i32_and_float_truncate(current, config->inbound_delta);
        } else {
            state->inbound_value = (uint32_t)current - 0x32u;
        }
        (void)_InterlockedExchange8((volatile char *)&state->inbound_block,
                                    (char)(current >= 1 && (uint32_t)current < 0x33u));

        current = (int32_t)state->outbound_value;
        if (current < 1) {
            state->outbound_value =
                (uint32_t)add_i32_and_float_truncate(current, config->outbound_delta);
        } else {
            state->outbound_value = (uint32_t)current - 0x32u;
        }
        (void)_InterlockedExchange8((volatile char *)&state->outbound_block,
                                    (char)(current >= 1 && (uint32_t)current < 0x33u));
    }

    /* The native code captures the payload pointer after the counter phases. */
    volatile fake_lag_event0_payload *payload = event->payload;
    if (payload->required_object == 0 || (config->require_ingame == 1 && payload->in_game == 0)) {
        state->pulse_timer = 0;
    } else {
        sampled_state = dependencies->sample_state(payload->object, payload->target, user);
        if (config->require_weapon == 1 &&
            dependencies->weapon_allowed(payload->object, payload->target, user) == 0) {
            state->pulse_timer = 0;
            send = 0;
        } else {
            /* These globals are loaded after the helper boundary in the original. */
            send = (uint8_t)((config->require_attack ^ 1u) | (state->pulse_timer != 0));
        }
        if ((uint32_t)sampled_state != state->last_state)
            state->pulse_timer = 0x14;
        state->last_state = (uint32_t)sampled_state;

        if (send != 0) {
            int32_t converted_inbound = cvttss_i32(config->inbound_delta);
            uint16_t previous_outbound;
            (void)_InterlockedExchange16((volatile short *)&state->inbound_amount,
                                         (short)converted_inbound);
            {
                int32_t converted_outbound = cvttss_i32(config->outbound_delta);
                previous_outbound = (uint16_t)_InterlockedExchange16(
                    (volatile short *)&state->outbound_amount, (short)converted_outbound);
                result = ((uint32_t)converted_outbound & 0xffff0000u) | previous_outbound;
            }
            return result;
        }
    }

    (void)_InterlockedExchange16((volatile short *)&state->outbound_amount, 0);
    result = (uint16_t)_InterlockedExchange16((volatile short *)&state->inbound_amount, 0);
    return result;
}

/* Shared callback body RVA 0x32cb0 (registry events 2 and 3). */
__declspec(dllexport) void semantic_fake_lag_packet(fake_lag_state *state,
                                                    volatile fake_lag_packet_event *event,
                                                    const fake_lag_dependencies *dependencies,
                                                    void *user) {
    uint32_t event_type = event->type;
    uint16_t amount;
    uint8_t blocked;

    if (event_type == 2) {
        if ((state->shared_byte & 1u) != 0) {
            uint64_t a = dependencies->packet_predicate_a(event->object_a, event->object_b, user);
            if (a != 0) {
                event->result = 3;
                return;
            }
            a = dependencies->packet_predicate_b(event->object_a, event->object_b, user);
            if (a != 0) {
                event->result = 3;
                return;
            }
            a = dependencies->packet_predicate_c(event->object_a, event->object_b, user);
            if (a != 0) {
                event->result = 3;
                return;
            }
        }
        blocked = state->inbound_block;
    } else {
        blocked = state->outbound_block;
    }

    if ((blocked & 1u) != 0)
        return;
    amount = event_type == 2 ? state->inbound_amount : state->outbound_amount;

    {
        uint64_t remaining = (uint64_t)event->remaining - (uint64_t)amount;
        event->remaining = (int64_t)remaining;
        /* Native JNS tests the result sign bit directly, including subtraction overflow. */
        if ((remaining & (UINT64_C(1) << 63)) == 0)
            return;
    }
    event->remaining = 0;
    event->result = 1;
}
// END SOURCE modules/Fake_Lag/FakeLag.cpp

// BEGIN SOURCE modules/Fake_Lag/Surface.cpp
#ifndef SLINKY_SHARE_6DBF483B0BE5E985B9D7
#define SLINKY_SHARE_6DBF483B0BE5E985B9D7
// BEGIN SOURCE modules/Fake_Lag/Surface.hpp
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/native/verified/module_format.hpp"
namespace fake_lag {
void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                    const BoundSurfaceUiDependencies &);
void serializeConfig(SettingsContext &, std::uint8_t *image, const SurfaceSettingsDependencies &);
void writeStatus(FormatState *, char *destination, const std::uint8_t *image,
                 const char *const *labels);
} // namespace fake_lag
// END SOURCE modules/Fake_Lag/Surface.hpp

#endif // SLINKY_SHARE_6DBF483B0BE5E985B9D7

extern "C" void recovered_fake_lag_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                            const BoundSurfaceUiDependencies *);
extern "C" void recovered_fake_lag_settings(SettingsContext *, std::uint8_t *,
                                            const SurfaceSettingsDependencies *);
namespace fake_lag {
void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                    const BoundSurfaceUiDependencies &dependencies) {
    recovered_fake_lag_bound_ui(ui, layout, image, &dependencies);
}
void serializeConfig(SettingsContext &context, std::uint8_t *image,
                     const SurfaceSettingsDependencies &dependencies) {
    recovered_fake_lag_settings(&context, image, &dependencies);
}
void writeStatus(FormatState *format, char *destination, const std::uint8_t *image,
                 const char *const *labels) {
    recovered_format(format, destination, 0x20, "%s",
                     labels[read_surface_value<std::uint32_t>(image, 0x2ebfa0)]);
}
} // namespace fake_lag
// END SOURCE modules/Fake_Lag/Surface.cpp

// Convenient borrowed-state interface

namespace shareable {
class FakeLag {
  public:
    static constexpr const char *kName = "Fake Lag";
    static constexpr const char *kDescription = "Adds an artificial delay to your packets.";
    explicit FakeLag(std::uint8_t *image) : image_(image) {}
    // Mode. Config key: mode.
    ChoiceSetting &mode() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2ebf70);
    }
    // Option labels observed in the captured metadata.
    enum class ModeMode : std::uint32_t { Static = 0, Pulse = 1 };
    // Inbound. Config key: inbound.
    NumberSetting &inbound() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ebed0);
    }
    // Outbound. Config key: outbound.
    NumberSetting &outbound() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ebf08);
    }
    // Realtime damage. Config key: realtime_damage.
    BooleanSetting &realtime_damage() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ebf40);
    }
    // Holding weapon. Config key: require_weapon.
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ebfd0);
    }
    // Attacked. Config key: require_attack.
    BooleanSetting &require_attack() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ebff0);
    }
    // In-game. Config key: require_ingame.
    BooleanSetting &require_ingame() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ebfb0);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_fake_lag_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_fake_lag_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_fake_lag_settings(&context, image_, &dependencies);
    }
    static void writeStatus(FormatState *format, char *destination, const std::uint8_t *image,
                            const char *const *labels) {
        ::fake_lag::writeStatus(format, destination, image, labels);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
