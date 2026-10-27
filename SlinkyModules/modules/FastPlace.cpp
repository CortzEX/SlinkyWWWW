// Fast Place

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Fast_Place.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Fast_Place.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Fast Place: lib_win settings 0x2ff30.
// UI 0x2fee0.
static constexpr UiStep ui_steps_Surface_Fast_Place[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2ea4e0},
    {UiControl::number, nullptr, 0x2ea518},
};
static constexpr SettingsStep settings_steps_Surface_Fast_Place[] = {
    {SettingsControl::number, "max_cps", 0x2ea4e0},
    {SettingsControl::number, "activate_delay", 0x2ea518},
};
static constexpr ModuleSurface surface_Surface_Fast_Place{
    ui_steps_Surface_Fast_Place, std::size(ui_steps_Surface_Fast_Place),
    settings_steps_Surface_Fast_Place, std::size(settings_steps_Surface_Fast_Place)};

extern "C" __declspec(dllexport) void
recovered_fast_place_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                        const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Fast_Place, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_fast_place_settings(SettingsContext *context, std::uint8_t *image,
                              const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Fast_Place, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Fast_Place.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Fast_Place/Fast_Place.cpp
#ifndef SLINKY_SHARE_404FBF70964ACBDFC910
#define SLINKY_SHARE_404FBF70964ACBDFC910
// BEGIN SOURCE native/verified/Fast_Place.hpp
#include "../runtime/native/verified/Timer.hpp"
#include "../runtime/native/verified/module_random_policy.hpp"
#include "../runtime/native/verified/module_ui_controls.hpp"
#include "../runtime/native/verified/module_format.hpp"

struct PlacementPosition {
    double x, y, z;
};
struct PlacementBox {
    PlacementPosition minimum, maximum;
};

struct FastPlaceSettings {
    NumberSetting maximum_cps;
    NumberSetting activation_delay;
};

struct FastPlaceState {
    volatile float timer;
    volatile std::uint8_t previously_pressed;
    std::uint8_t padding[3];
    volatile std::int32_t activation_countdown;
    std::uint8_t padding2[4];
    SmoothRandomState placement_gate;
};

struct FastPlaceConstants {
    float tick_step;
    std::uint8_t padding[4];
    double rate_scale;
    double block_extent;
    float gate_lower, gate_upper;
};

struct FastPlaceAccessContext;

struct FastPlaceDependencies {
    std::uintptr_t (*options)(GameAccessBridge *, std::uintptr_t client);
    std::uintptr_t (*use_key)(GameAccessBridge *, std::uintptr_t options);
    std::uint8_t (*physical_key)(GameAccessBridge *, std::uintptr_t key);
    std::int32_t (*queued_presses)(GameAccessBridge *, std::uintptr_t key);
    void (*increment_presses)(GameAccessBridge *, std::uintptr_t key);
    std::uintptr_t (*held_item)(GameAccessBridge *, std::uintptr_t player);
    std::uint8_t (*block_item)(GameAccessBridge *, std::uintptr_t item);
    std::uintptr_t (*mouse_over)(GameAccessBridge *, std::uintptr_t client);
    std::uint32_t (*hit_type)(GameAccessBridge *, std::uintptr_t hit);
    std::uint32_t (*item_type)(GameAccessBridge *, std::uintptr_t item);
    void (*adjacent_position)(PlacementPosition *, GameAccessBridge *, std::uintptr_t hit,
                              const FastPlaceAccessContext *);
    void (*position)(PlacementPosition *, double x, double y, double z);
    void (*add)(PlacementPosition *, const PlacementPosition *, const PlacementPosition *);
    void (*box)(PlacementBox *, const PlacementPosition *, const PlacementPosition *);
    std::uintptr_t (*player_box)(GameAccessBridge *, std::uintptr_t player);
    void (*read_box)(PlacementBox *, GameAccessBridge *, std::uintptr_t box);
    std::uint8_t (*intersects)(const PlacementBox *, const PlacementBox *);
    std::uint64_t (*random_bounds)(float lower, float upper);
    std::uint8_t (*placement_allowed)(SmoothRandomState *, std::uint64_t bounds, double duration,
                                      const FastPlaceAccessContext *);
    const FastPlaceAccessContext *context;
};

static_assert(sizeof(PlacementPosition) == 24);
static_assert(sizeof(PlacementBox) == 48);
static_assert(sizeof(FastPlaceSettings) == 112);
static_assert(sizeof(FastPlaceState) == 32);
static_assert(offsetof(FastPlaceState, activation_countdown) == 8);
static_assert(offsetof(FastPlaceState, placement_gate) == 16);
static_assert(sizeof(FastPlaceConstants) == 32);
static_assert(offsetof(FastPlaceConstants, rate_scale) == 8);
static_assert(sizeof(FastPlaceDependencies) == 160);
static_assert(offsetof(FastPlaceDependencies, context) == 152);

extern "C" __declspec(dllexport) void
recovered_fast_place_typed_update(TimerEvent *, const FastPlaceSettings *, FastPlaceState *,
                                  const FastPlaceConstants *, const FastPlaceDependencies *);

extern "C" {
__declspec(dllexport) std::uint64_t
recovered_fast_place_typed_ui(std::uint64_t ui, std::uint64_t layout, FastPlaceSettings *,
                              UiDirtyState *, const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_fast_place_typed_settings(SettingsContext *,
                                                               FastPlaceSettings *,
                                                               const ValueSettingsDependencies *);
__declspec(dllexport) std::uint64_t recovered_fast_place_label(char *, const FastPlaceSettings *,
                                                               FormatState *);
}
// END SOURCE native/verified/Fast_Place.hpp

#endif // SLINKY_SHARE_404FBF70964ACBDFC910

#include <cmath>
#include <emmintrin.h>

namespace {
// Preserve the temporary record identities at helper boundaries. Every field
// used below is filled by an operation before it is read.
struct PlacementWorkspace {
    PlacementPosition maximum, extent;
    PlacementBox placed, player, computed, fetched;
    std::uint8_t padding[8];
    PlacementPosition adjacent;
};
static_assert(offsetof(PlacementWorkspace, adjacent) == 248);

bool unordered_or_nonpositive(float value) {
    return std::isnan(value) || value <= 0.0f;
}
} // namespace

// 0x2fbc0. Check the timer before touching the event, retain the use-key handle,
// and reload the bridge/player/client fields after each external operation.
extern "C" __declspec(dllexport) void
recovered_fast_place_typed_update(TimerEvent *event, const FastPlaceSettings *settings,
                                  FastPlaceState *state, const FastPlaceConstants *constants,
                                  const FastPlaceDependencies *access) {
    if (!unordered_or_nonpositive(state->timer)) {
        state->timer = state->timer + constants->tick_step;
        if (!std::isnan(state->timer) && state->timer > 0.0f)
            return;
    }
    auto *game = event->game;
    if (game->ready != 1)
        return;
    const auto options = access->options(game->bridge, game->client);
    const auto key = access->use_key(game->bridge, options);
    const auto pressed = access->physical_key(game->bridge, key);
    const auto previous = state->previously_pressed;
    state->previously_pressed = pressed;
    if (!pressed) {
        state->activation_countdown =
            _mm_cvttss_si32(_mm_set_ss(settings->activation_delay.current));
        return;
    }
    if (state->activation_countdown >= 1) {
        state->activation_countdown = state->activation_countdown - 1;
        return;
    }
    if (access->queued_presses(game->bridge, key) > 0)
        return;
    if (std::isnan(state->timer) || state->timer > 0.0f)
        return;

    const double rate = constants->rate_scale;
    const double extent = constants->block_extent;
    const float lower = constants->gate_lower, upper = constants->gate_upper;
    auto phase = static_cast<std::uint8_t>(previous ^ 1);
    do {
        state->timer =
            static_cast<float>(static_cast<double>(state->timer) +
                               rate / static_cast<double>(settings->maximum_cps.current));
        if (!(phase & 1)) {
            auto *bridge = game->bridge;
            auto item = access->held_item(bridge, game->player);
            if (access->block_item(bridge, item)) {
                const auto hit = access->mouse_over(game->bridge, game->client);
                bool use_gate = !hit;
                if (!use_gate)
                    use_gate = access->hit_type(game->bridge, hit) != 1;
                bool skip_geometry = false;
                if (!use_gate) {
                    item = access->held_item(game->bridge, game->player);
                    if (item)
                        skip_geometry = access->item_type(game->bridge, item) == 0x41;
                }
                if (!use_gate && !skip_geometry) {
                    PlacementWorkspace work;
                    access->adjacent_position(&work.adjacent, game->bridge, hit, access->context);
                    access->position(&work.extent, extent, extent, extent);
                    work.computed.minimum = work.adjacent;
                    access->add(&work.maximum, &work.computed.minimum, &work.extent);
                    work.fetched.minimum = work.adjacent;
                    access->box(&work.computed, &work.fetched.minimum, &work.maximum);
                    bridge = game->bridge;
                    const auto player = game->player;
                    const auto player_box = access->player_box(bridge, player);
                    access->read_box(&work.fetched, bridge, player_box);
                    work.placed = work.computed;
                    work.player = work.fetched;
                    if (access->intersects(&work.placed, &work.player))
                        use_gate = true;
                }
                if (use_gate) {
                    const auto bounds = access->random_bounds(lower, upper);
                    if (!access->placement_allowed(&state->placement_gate, bounds, rate,
                                                   access->context))
                        goto advance;
                }
                access->increment_presses(game->bridge, key);
            }
        }
    advance:
        phase = 0;
    } while (!std::isnan(state->timer) && state->timer <= 0.0f);
}
// END SOURCE modules/Fast_Place/Fast_Place.cpp

// BEGIN SOURCE modules/Fast_Place/Fast_Place_access.cpp
#ifndef SLINKY_SHARE_27F2A8BBC1AE5D5B7462
#define SLINKY_SHARE_27F2A8BBC1AE5D5B7462
// BEGIN SOURCE native/verified/Fast_Place_access.hpp
struct FastPlaceAccessContext {
    const PlacementPosition *directions;
    RandomState *random;
    const double *clock;
    const RandomPolicyConstants *policy;
};
static_assert(sizeof(FastPlaceAccessContext) == 32);

extern "C" {
__declspec(dllexport) void recovered_bind_fast_place_access(FastPlaceDependencies *,
                                                            const FastPlaceAccessContext *);
__declspec(dllexport) void recovered_fast_place_adjacent_position(PlacementPosition *,
                                                                  GameAccessBridge *,
                                                                  std::uintptr_t hit,
                                                                  const FastPlaceAccessContext *);
__declspec(dllexport) void recovered_fast_place_read_box(PlacementBox *, GameAccessBridge *,
                                                         std::uintptr_t box);
__declspec(dllexport) std::int32_t recovered_fast_place_press_count(GameAccessBridge *,
                                                                    std::uintptr_t key);
__declspec(dllexport) void recovered_fast_place_increment_presses(GameAccessBridge *,
                                                                  std::uintptr_t key);
}
// END SOURCE native/verified/Fast_Place_access.hpp

#endif // SLINKY_SHARE_27F2A8BBC1AE5D5B7462

#include "../runtime/native/verified/module_placement_geometry.hpp"
#include "../runtime/native/verified/module_access_helpers.hpp"
#include "../runtime/native/verified/Safe_Walk.hpp"
#include <cstring>

namespace {
using Word = std::uintptr_t;
Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word value;
    std::memcpy(&value, bridge->metadata + offset, sizeof(value));
    return value;
}
template <class Function> Function slot(const GameAccessBridge *bridge, std::size_t offset) {
    const auto *table = reinterpret_cast<const Word *>(*bridge->environment);
    return reinterpret_cast<Function>(table[offset / sizeof(Word)]);
}
bool modern(GameAccessBridge *bridge) {
    std::uint32_t version;
    std::memcpy(&version, bridge->metadata, sizeof(version));
    return version != 0;
}
Word object_field(GameAccessBridge *bridge, Word object, std::size_t offset) {
    using Getter_Fast_Place_access = Word (*)(Word *, Word, Word);
    return slot<Getter_Fast_Place_access>(bridge, 0x2f8)(bridge->environment, object,
                                                         identifier(bridge, offset));
}
std::int32_t integer_field(GameAccessBridge *bridge, Word object, std::size_t offset) {
    using Getter_Fast_Place_access = std::int32_t (*)(Word *, Word, Word);
    return slot<Getter_Fast_Place_access>(bridge, 0x320)(bridge->environment, object,
                                                         identifier(bridge, offset));
}
double real_field(GameAccessBridge *bridge, Word object, std::size_t offset) {
    using Getter_Fast_Place_access = double (*)(Word *, Word, Word);
    return slot<Getter_Fast_Place_access>(bridge, 0x338)(bridge->environment, object,
                                                         identifier(bridge, offset));
}
void integer_position(PlacementPosition *out, GameAccessBridge *bridge, Word object,
                      std::size_t offset) {
    const double x = integer_field(bridge, object, offset);
    const double y = integer_field(bridge, object, offset + 8);
    const double z = integer_field(bridge, object, offset + 16);
    recovered_placement_position(out, x, y, z);
}
void real_position(PlacementPosition *out, GameAccessBridge *bridge, Word object,
                   std::size_t offset) {
    const double x = real_field(bridge, object, offset);
    const double y = real_field(bridge, object, offset + 8);
    const double z = real_field(bridge, object, offset + 16);
    recovered_placement_position(out, x, y, z);
}
Word options(GameAccessBridge *bridge, Word client) {
    return recovered_access_helper(bridge, 0x22cf0, client, 0, 0);
}
Word use_key(GameAccessBridge *bridge, Word options) {
    return recovered_access_helper(bridge, 0x24f90, options, 0, 0);
}
std::uint8_t physical_key(GameAccessBridge *bridge, Word key) {
    return static_cast<std::uint8_t>(recovered_access_helper(bridge, 0x25490, key, 0, 0));
}
Word mouse_over(GameAccessBridge *bridge, Word client) {
    return recovered_access_helper(bridge, 0x22e10, client, 0, 0);
}
std::uint32_t hit_type(GameAccessBridge *bridge, Word hit) {
    return static_cast<std::uint32_t>(recovered_access_helper(bridge, 0x24b50, hit, 0, 0));
}
std::uint32_t item_type(GameAccessBridge *bridge, Word item) {
    return static_cast<std::uint32_t>(recovered_game_item_numeric_id(bridge, item));
}
Word player_box(GameAccessBridge *bridge, Word player) {
    return object_field(bridge, player, 0x2d0);
}
void position(PlacementPosition *out, double x, double y, double z) {
    recovered_placement_position(out, x, y, z);
}
void add(PlacementPosition *out, const PlacementPosition *a, const PlacementPosition *b) {
    recovered_placement_add(out, a, b);
}
void box(PlacementBox *out, const PlacementPosition *minimum, const PlacementPosition *maximum) {
    recovered_placement_box(out, minimum, maximum);
}
std::uint8_t allowed(SmoothRandomState *sampler, std::uint64_t bounds, double duration,
                     const FastPlaceAccessContext *context) {
    return recovered_policy_gate(sampler, bounds, duration, context->random, context->clock,
                                 context->policy);
}
} // namespace

// 0x25360/0x25380 preserve the signed query and wrapping DWORD increment,
// then reload the setter target, environment and field after the query.
extern "C" __declspec(dllexport) std::int32_t
recovered_fast_place_press_count(GameAccessBridge *bridge, Word key) {
    return integer_field(bridge, key, 0x480);
}
extern "C" __declspec(dllexport) void
recovered_fast_place_increment_presses(GameAccessBridge *bridge, Word key) {
    const auto next =
        static_cast<std::uint32_t>(recovered_fast_place_press_count(bridge, key)) + 1u;
    using Setter = void (*)(Word *, Word, Word, std::uint32_t);
    slot<Setter>(bridge, 0x368)(bridge->environment, key, identifier(bridge, 0x480), next);
}

// 0x24d80 queries the block position using 0x24c10/0x24310, then rereads the
// version to select an integer facing or its enum ordinal. Direction data is
// supplied explicitly and read after those calls.
extern "C" __declspec(dllexport) void
recovered_fast_place_adjacent_position(PlacementPosition *out, GameAccessBridge *bridge, Word hit,
                                       const FastPlaceAccessContext *context) {
    PlacementPosition position;
    if (modern(bridge)) {
        const auto block = object_field(bridge, hit, 0x410);
        integer_position(&position, bridge, block, 0x458);
    } else
        integer_position(&position, bridge, hit, 0x3f8);
    std::uint32_t facing;
    if (modern(bridge)) {
        const auto face = object_field(bridge, hit, 0x3f0);
        facing = static_cast<std::uint32_t>(recovered_access_helper(bridge, 0x271a0, face, 0, 0));
    } else
        facing = static_cast<std::uint32_t>(integer_field(bridge, hit, 0x3e8));
    const auto first = position;
    const auto direction = context->directions[facing];
    recovered_placement_add(out, &first, &direction);
}

// 0x25640 captures each triple in order, with fresh bridge metadata/JNI targets
// for all six reads, and writes the box after both triples are complete.
extern "C" __declspec(dllexport) void
recovered_fast_place_read_box(PlacementBox *out, GameAccessBridge *bridge, Word object) {
    PlacementPosition minimum, maximum;
    real_position(&minimum, bridge, object, 0x4a8);
    real_position(&maximum, bridge, object, 0x4c0);
    recovered_placement_box(out, &minimum, &maximum);
}

extern "C" __declspec(dllexport) void
recovered_bind_fast_place_access(FastPlaceDependencies *dependencies,
                                 const FastPlaceAccessContext *context) {
    SafeWalkDependencies shared;
    recovered_bind_safe_walk_access(&shared);
    *dependencies = {options,
                     use_key,
                     physical_key,
                     recovered_fast_place_press_count,
                     recovered_fast_place_increment_presses,
                     shared.held_item,
                     shared.block_item,
                     mouse_over,
                     hit_type,
                     item_type,
                     recovered_fast_place_adjacent_position,
                     position,
                     add,
                     box,
                     player_box,
                     recovered_fast_place_read_box,
                     recovered_placement_intersects,
                     recovered_random_bounds,
                     allowed,
                     context};
}
// END SOURCE modules/Fast_Place/Fast_Place_access.cpp

// BEGIN SOURCE modules/Fast_Place/Fast_Place_local.cpp
// 0x2fee0 renders both numeric controls and returns the last wrapper's full word.
extern "C" __declspec(dllexport) std::uint64_t
recovered_fast_place_typed_ui(std::uint64_t ui, std::uint64_t layout, FastPlaceSettings *settings,
                              UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Main");
    recovered_number_control(layout, ui, &settings->maximum_cps, dirty, &endpoints->controls);
    return recovered_number_control(layout, ui, &settings->activation_delay, dirty,
                                    &endpoints->controls);
}

// 0x2ff30 persists both controls without normalizing captured saved values.
extern "C" __declspec(dllexport) void
recovered_fast_place_typed_settings(SettingsContext *context, FastPlaceSettings *settings,
                                    const ValueSettingsDependencies *endpoints) {
    recovered_number_settings(context, "max_cps", &settings->maximum_cps, endpoints);
    recovered_number_settings(context, "activate_delay", &settings->activation_delay, endpoints);
}

// 0x2ff70 promotes the current binary32 value to the original binary64 argument.
extern "C" __declspec(dllexport) std::uint64_t
recovered_fast_place_label(char *destination, const FastPlaceSettings *settings,
                           FormatState *format) {
    return recovered_format(format, destination, 32, "%.1f",
                            static_cast<double>(settings->maximum_cps.current));
}
// END SOURCE modules/Fast_Place/Fast_Place_local.cpp

// BEGIN SOURCE modules/Fast_Place/Fast_Place_module.cpp
#ifndef SLINKY_SHARE_D605C37A8258F1B2C48D
#define SLINKY_SHARE_D605C37A8258F1B2C48D
// BEGIN SOURCE native/verified/Fast_Place_module.hpp
extern "C" __declspec(dllexport) void recovered_fast_place_initialize_settings(FastPlaceSettings *);

class FastPlaceModule {
  public:
    static constexpr const char *name = "Fast Place";
    static constexpr const char *description = "Allows placing blocks faster.";
    static constexpr std::uint32_t event_type = 0;
    static constexpr std::int32_t event_priority = -1000;
    FastPlaceSettings settings{};
    FastPlaceState state{};
    // Captured constants and baseline state, not a recovered startup routine.
    FastPlaceConstants constants{-1.0f, {}, 20.0, 1.0, 0.02f, 0.08f};
    FastPlaceDependencies access;

    explicit FastPlaceModule(const FastPlaceDependencies &dependencies) : access(dependencies) {
        recovered_fast_place_initialize_settings(&settings);
    }
    void update(TimerEvent &event) {
        recovered_fast_place_typed_update(&event, &settings, &state, &constants, &access);
    }
    std::uint64_t render(std::uint64_t ui, std::uint64_t layout, UiDirtyState &dirty,
                         const SettingsUiEndpoints &endpoints) {
        return recovered_fast_place_typed_ui(ui, layout, &settings, &dirty, &endpoints);
    }
    void configure(SettingsContext &context, const ValueSettingsDependencies &endpoints) {
        recovered_fast_place_typed_settings(&context, &settings, &endpoints);
    }
    std::uint64_t status(char (&destination)[32], FormatState &format) const {
        return recovered_fast_place_label(destination, &settings, &format);
    }
};
// END SOURCE native/verified/Fast_Place_module.hpp

#endif // SLINKY_SHARE_D605C37A8258F1B2C48D

#include <cstring>

namespace {
template <class Value> void metadata(std::uint8_t *bytes, std::size_t offset, Value value) {
    std::memcpy(bytes + offset, &value, sizeof(value));
}
} // namespace

extern "C" __declspec(dllexport) void
recovered_fast_place_initialize_settings(FastPlaceSettings *settings) {
    *settings = {};
    auto &cps = settings->maximum_cps;
    metadata(cps.metadata, 16, "Maximum CPS");
    metadata(cps.metadata, 24, "%0.1f CPS");
    metadata(cps.metadata, 32, 0.1f);
    cps.minimum = 10.0f;
    cps.maximum = 50.0f;
    cps.current = 20.0f;
    auto &delay = settings->activation_delay;
    metadata(delay.metadata, 16, "Activate delay");
    metadata(delay.metadata, 24, "%0.0f ms");
    metadata(delay.metadata, 32, 1.0f);
    metadata(delay.metadata, 36, 50.0f);
    delay.maximum = 10.0f;
}
// END SOURCE modules/Fast_Place/Fast_Place_module.cpp

#ifndef SLINKY_SHARE_E3FB2DF1009C6786ABBD
#define SLINKY_SHARE_E3FB2DF1009C6786ABBD
// BEGIN SOURCE modules/Fast_Place/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Fast_Place/Api.hpp

#endif // SLINKY_SHARE_E3FB2DF1009C6786ABBD

// Convenient borrowed-state interface

namespace shareable {
using FastPlace = ::FastPlaceModule;
}
