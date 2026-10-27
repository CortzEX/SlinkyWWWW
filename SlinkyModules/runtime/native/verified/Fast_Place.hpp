#ifndef SLINKY_SHARE_404FBF70964ACBDFC910
#define SLINKY_SHARE_404FBF70964ACBDFC910
#include "Timer.hpp"
#include "module_random_policy.hpp"
#include "module_ui_controls.hpp"
#include "module_format.hpp"

struct PlacementPosition { double x, y, z; };
struct PlacementBox { PlacementPosition minimum, maximum; };

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
    void (*adjacent_position)(PlacementPosition *, GameAccessBridge *, std::uintptr_t hit, const FastPlaceAccessContext *);
    void (*position)(PlacementPosition *, double x, double y, double z);
    void (*add)(PlacementPosition *, const PlacementPosition *, const PlacementPosition *);
    void (*box)(PlacementBox *, const PlacementPosition *, const PlacementPosition *);
    std::uintptr_t (*player_box)(GameAccessBridge *, std::uintptr_t player);
    void (*read_box)(PlacementBox *, GameAccessBridge *, std::uintptr_t box);
    std::uint8_t (*intersects)(const PlacementBox *, const PlacementBox *);
    std::uint64_t (*random_bounds)(float lower, float upper);
    std::uint8_t (*placement_allowed)(SmoothRandomState *, std::uint64_t bounds, double duration, const FastPlaceAccessContext *);
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

extern "C" __declspec(dllexport) void recovered_fast_place_typed_update(
    TimerEvent *, const FastPlaceSettings *, FastPlaceState *,
    const FastPlaceConstants *, const FastPlaceDependencies *);

extern "C" {
__declspec(dllexport) std::uint64_t recovered_fast_place_typed_ui(std::uint64_t ui,
    std::uint64_t layout, FastPlaceSettings *, UiDirtyState *, const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_fast_place_typed_settings(SettingsContext *,
    FastPlaceSettings *, const ValueSettingsDependencies *);
__declspec(dllexport) std::uint64_t recovered_fast_place_label(char *, const FastPlaceSettings *, FormatState *);
}
#endif // SLINKY_SHARE_404FBF70964ACBDFC910
