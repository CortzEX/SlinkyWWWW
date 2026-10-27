// Clutch

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Clutch.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Clutch.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Clutch: lib_win settings 0x49da0.
// UI 0x49c00.
static constexpr UiStep ui_steps_Surface_Clutch[] = {
    {UiControl::section, "Main", 0},          {UiControl::number, nullptr, 0x2f59d0},
    {UiControl::number, nullptr, 0x2f5a08},   {UiControl::number, nullptr, 0x2f5998},
    {UiControl::number, nullptr, 0x2f5790},   {UiControl::number, nullptr, 0x2f5838},
    {UiControl::choice, nullptr, 0x2f5a98},   {UiControl::checkbox, nullptr, 0x2f5a40},
    {UiControl::section, "Aim", 0},           {UiControl::number, nullptr, 0x2f5870},
    {UiControl::number, nullptr, 0x2f58a8},   {UiControl::number, nullptr, 0x2f58e0},
    {UiControl::checkbox, nullptr, 0x2f5a60}, {UiControl::section, "Snap-back", 0},
    {UiControl::number, nullptr, 0x2f5800},   {UiControl::number, nullptr, 0x2f57c8},
    {UiControl::checkbox, nullptr, 0x2f5918}, {UiControl::checkbox, nullptr, 0x2f5ad8},
    {UiControl::section, "Conditions", 0},    {UiControl::checkbox, nullptr, 0x2f5938},
    {UiControl::checkbox, nullptr, 0x2f5958}, {UiControl::checkbox, nullptr, 0x2f5978},
};
static constexpr SettingsStep settings_steps_Surface_Clutch[] = {
    {SettingsControl::number, "range", 0x2f59d0},
    {SettingsControl::number, "max_aim_dist", 0x2f5a08},
    {SettingsControl::number, "min_height", 0x2f5998},
    {SettingsControl::number, "click_speed", 0x2f5790},
    {SettingsControl::number, "randomization", 0x2f5838},
    {SettingsControl::choice, "select_blocks", 0x2f5a98},
    {SettingsControl::boolean, "sideways_only", 0x2f5a40},
    {SettingsControl::number, "aim_speed", 0x2f5870},
    {SettingsControl::number, "aim_mult", 0x2f58a8},
    {SettingsControl::number, "aim_mult_strength", 0x2f58e0},
    {SettingsControl::boolean, "aim_multipoint", 0x2f5a60},
    {SettingsControl::number, "snapback_delay", 0x2f5800},
    {SettingsControl::number, "snapback_duration", 0x2f57c8},
    {SettingsControl::boolean, "snapback_instant_on_jump", 0x2f5918},
    {SettingsControl::boolean, "snapback_disable_after", 0x2f5ad8},
    {SettingsControl::boolean, "require_air", 0x2f5938},
    {SettingsControl::boolean, "require_damage", 0x2f5958},
    {SettingsControl::boolean, "require_backwards", 0x2f5978},
};
static constexpr ModuleSurface surface_Surface_Clutch{
    ui_steps_Surface_Clutch, std::size(ui_steps_Surface_Clutch), settings_steps_Surface_Clutch,
    std::size(settings_steps_Surface_Clutch)};

extern "C" __declspec(dllexport) void
recovered_clutch_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                    const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Clutch, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_clutch_settings(SettingsContext *context, std::uint8_t *image,
                          const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Clutch, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Clutch.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Clutch/clutch_events.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_00755C4460E084055719
#define SLINKY_SHARE_00755C4460E084055719
// BEGIN SOURCE modules/Clutch/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Clutch {
namespace Storage {
inline constexpr std::uint32_t nativeData_13cfa0 = 0x13cfa0;
inline constexpr std::uint32_t nativeData_13cfd0 = 0x13cfd0;
inline constexpr std::uint32_t nativeData_156070 = 0x156070;
inline constexpr std::uint32_t nativeData_156074 = 0x156074;
inline constexpr std::uint32_t nativeData_156080 = 0x156080;
inline constexpr std::uint32_t nativeData_156088 = 0x156088;
inline constexpr std::uint32_t nativeData_156090 = 0x156090;
inline constexpr std::uint32_t nativeData_156098 = 0x156098;
inline constexpr std::uint32_t nativeData_1560a0 = 0x1560a0;
inline constexpr std::uint32_t nativeData_1560a8 = 0x1560a8;
inline constexpr std::uint32_t nativeData_1560b0 = 0x1560b0;
inline constexpr std::uint32_t nativeData_1560b8 = 0x1560b8;
inline constexpr std::uint32_t nativeData_1560c0 = 0x1560c0;
inline constexpr std::uint32_t nativeData_1560c8 = 0x1560c8;
inline constexpr std::uint32_t nativeData_1560d0 = 0x1560d0;
inline constexpr std::uint32_t nativeData_1560d4 = 0x1560d4;
inline constexpr std::uint32_t nativeData_1560d8 = 0x1560d8;
inline constexpr std::uint32_t nativeData_1560e0 = 0x1560e0;
inline constexpr std::uint32_t nativeData_1560e8 = 0x1560e8;
inline constexpr std::uint32_t nativeData_1560f0 = 0x1560f0;
inline constexpr std::uint32_t nativeData_1560f8 = 0x1560f8;
inline constexpr std::uint32_t nativeData_156100 = 0x156100;
inline constexpr std::uint32_t nativeData_156108 = 0x156108;
inline constexpr std::uint32_t nativeData_156110 = 0x156110;
inline constexpr std::uint32_t nativeData_156118 = 0x156118;
inline constexpr std::uint32_t nativeData_156120 = 0x156120;
inline constexpr std::uint32_t nativeData_156124 = 0x156124;
inline constexpr std::uint32_t nativeData_156128 = 0x156128;
inline constexpr std::uint32_t nativeData_156130 = 0x156130;
inline constexpr std::uint32_t nativeData_156140 = 0x156140;
inline constexpr std::uint32_t nativeData_156150 = 0x156150;
inline constexpr std::uint32_t nativeData_156158 = 0x156158;
inline constexpr std::uint32_t nativeData_156160 = 0x156160;
inline constexpr std::uint32_t nativeData_156168 = 0x156168;
inline constexpr std::uint32_t nativeData_15616c = 0x15616c;
inline constexpr std::uint32_t nativeData_156280 = 0x156280;
inline constexpr std::uint32_t nativeData_156290 = 0x156290;
inline constexpr std::uint32_t nativeData_2f5000 = 0x2f5000;
inline constexpr std::uint32_t moduleDescriptor = 0x2f5580;
inline constexpr std::uint32_t click_speedRecord = 0x2f5790;
inline constexpr std::uint32_t click_speedCurrent = 0x2f57c0;
inline constexpr std::uint32_t snapback_durationRecord = 0x2f57c8;
inline constexpr std::uint32_t snapback_durationCurrent = 0x2f57f8;
inline constexpr std::uint32_t snapback_delayRecord = 0x2f5800;
inline constexpr std::uint32_t snapback_delayCurrent = 0x2f5830;
inline constexpr std::uint32_t randomizationRecord = 0x2f5838;
inline constexpr std::uint32_t randomizationCurrent = 0x2f5868;
inline constexpr std::uint32_t aim_speedRecord = 0x2f5870;
inline constexpr std::uint32_t aim_speedCurrent = 0x2f58a0;
inline constexpr std::uint32_t aim_multRecord = 0x2f58a8;
inline constexpr std::uint32_t aim_multCurrent = 0x2f58d8;
inline constexpr std::uint32_t aim_mult_strengthRecord = 0x2f58e0;
inline constexpr std::uint32_t aim_mult_strengthCurrent = 0x2f5910;
inline constexpr std::uint32_t snapback_instant_on_jumpRecord = 0x2f5918;
inline constexpr std::uint32_t snapback_instant_on_jumpCurrent = 0x2f5930;
inline constexpr std::uint32_t require_airRecord = 0x2f5938;
inline constexpr std::uint32_t require_airCurrent = 0x2f5950;
inline constexpr std::uint32_t require_damageRecord = 0x2f5958;
inline constexpr std::uint32_t require_damageCurrent = 0x2f5970;
inline constexpr std::uint32_t require_backwardsRecord = 0x2f5978;
inline constexpr std::uint32_t require_backwardsCurrent = 0x2f5990;
inline constexpr std::uint32_t min_heightRecord = 0x2f5998;
inline constexpr std::uint32_t min_heightCurrent = 0x2f59c8;
inline constexpr std::uint32_t rangeRecord = 0x2f59d0;
inline constexpr std::uint32_t rangeCurrent = 0x2f5a00;
inline constexpr std::uint32_t max_aim_distRecord = 0x2f5a08;
inline constexpr std::uint32_t max_aim_distCurrent = 0x2f5a38;
inline constexpr std::uint32_t sideways_onlyRecord = 0x2f5a40;
inline constexpr std::uint32_t sideways_onlyCurrent = 0x2f5a58;
inline constexpr std::uint32_t aim_multipointRecord = 0x2f5a60;
inline constexpr std::uint32_t aim_multipointCurrent = 0x2f5a78;
inline constexpr std::uint32_t select_blocksRecord = 0x2f5a98;
inline constexpr std::uint32_t select_blocksCurrent = 0x2f5ac8;
inline constexpr std::uint32_t snapback_disable_afterRecord = 0x2f5ad8;
inline constexpr std::uint32_t snapback_disable_afterCurrent = 0x2f5af0;
inline constexpr std::uint32_t nativeData_304a00 = 0x304a00;
inline constexpr std::uint32_t nativeData_304a18 = 0x304a18;
inline constexpr std::uint32_t nativeData_304a1c = 0x304a1c;
inline constexpr std::uint32_t nativeData_304a20 = 0x304a20;
inline constexpr std::uint32_t nativeData_304a24 = 0x304a24;
inline constexpr std::uint32_t nativeData_304a28 = 0x304a28;
inline constexpr std::uint32_t nativeData_304a2c = 0x304a2c;
inline constexpr std::uint32_t nativeData_304a2d = 0x304a2d;
inline constexpr std::uint32_t nativeData_304a3c = 0x304a3c;
inline constexpr std::uint32_t nativeData_304a70 = 0x304a70;
inline constexpr std::uint32_t nativeData_304a80 = 0x304a80;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &range() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::rangeRecord);
    }
    NumberSetting &max_aim_dist() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::max_aim_distRecord);
    }
    NumberSetting &min_height() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::min_heightRecord);
    }
    NumberSetting &click_speed() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::click_speedRecord);
    }
    NumberSetting &randomization() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::randomizationRecord);
    }
    ChoiceSetting &select_blocks() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::select_blocksRecord);
    }
    BooleanSetting &sideways_only() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::sideways_onlyRecord);
    }
    NumberSetting &aim_speed() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::aim_speedRecord);
    }
    NumberSetting &aim_mult() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::aim_multRecord);
    }
    NumberSetting &aim_mult_strength() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::aim_mult_strengthRecord);
    }
    BooleanSetting &aim_multipoint() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::aim_multipointRecord);
    }
    NumberSetting &snapback_delay() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::snapback_delayRecord);
    }
    NumberSetting &snapback_duration() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::snapback_durationRecord);
    }
    BooleanSetting &snapback_instant_on_jump() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::snapback_instant_on_jumpRecord);
    }
    BooleanSetting &snapback_disable_after() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::snapback_disable_afterRecord);
    }
    BooleanSetting &require_air() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_airRecord);
    }
    BooleanSetting &require_damage() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_damageRecord);
    }
    BooleanSetting &require_backwards() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_backwardsRecord);
    }
};
// Runtime-observed native labels for config key "select_blocks". Numeric values preserved.
enum class Select_blocksMode : std::uint32_t {
    No = 0,
    On_depletion = 1,
    Always = 2,
};
} // namespace reconstruction::Clutch
// END SOURCE modules/Clutch/Settings.hpp

#endif // SLINKY_SHARE_00755C4460E084055719

#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
namespace reconstruction::Clutch {
#define API
using Dispatch = native_binding::WordEndpoints;
// Native entry 0x22cf0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t clientOptions(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x22cf0, a0, a1, a2, a3);
}
// Native entry 0x22e10; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t currentHitResult(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x22e10, a0, a1, a2, a3);
}
// Native entry 0x24b50; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t hitResultType(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x24b50, a0, a1, a2, a3);
}
// Native entry 0x24b90; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t hitResultFace(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x24b90, a0, a1, a2, a3);
}
// Native entry 0x24ce0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t hitIntegerBlockCoordinates(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2,
                                           uint64_t a3) {
    return api(0x24ce0, a0, a1, a2, a3);
}
// Native entry 0x24d80; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t hitPosition(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x24d80, a0, a1, a2, a3);
}
// Native entry 0x24f90; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t useItemKey(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x24f90, a0, a1, a2, a3);
}
// Native entry 0x25380; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t pressKey(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x25380, a0, a1, a2, a3);
}

static uint64_t loadWord64_clutch_events(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t loadWord32(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static float loadFloat(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static uint64_t p(const void *v) {
    return (uint64_t)(uintptr_t)v;
}
API void onPlacementTick(uint8_t *event, uint8_t *image, Dispatch call) {
    float time = loadFloat(image + Storage::nativeData_304a18);
    if (time > 0) {
        time = _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(time),
                                        _mm_set_ss(loadFloat(image + Storage::nativeData_156070))));
        memcpy(image + Storage::nativeData_304a18, &time, 4);
        if (time > 0)
            return;
    }
    float step =
        _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(loadFloat(image + Storage::nativeData_156074)),
                                 _mm_set_ss(loadFloat(image + Storage::click_speedCurrent))));
    time = _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(step), _mm_set_ss(time)));
    memcpy(image + Storage::nativeData_304a18, &time, 4);
    uint8_t *ctx = (uint8_t *)(uintptr_t)loadWord64_clutch_events(event + 8);
    if (ctx[0x40] != 1 || !image[Storage::nativeData_304a1c])
        return;
    uint64_t target = currentHitResult(call, loadWord64_clutch_events(ctx),
                                       loadWord64_clutch_events(ctx + 0x18), 0, 0);
    if (!target)
        return;
    if ((uint32_t)hitResultType(call, loadWord64_clutch_events(ctx), target, 0, 0) != 1)
        return;
    uint32_t block[3];
    hitIntegerBlockCoordinates(call, p(block), loadWord64_clutch_events(ctx), target, 0);
    if (block[0] != loadWord32(image + Storage::nativeData_304a20) ||
        block[1] != loadWord32(image + Storage::nativeData_304a24) ||
        block[2] != loadWord32(image + Storage::nativeData_304a28))
        return;
    uint8_t side = (uint32_t)hitResultFace(call, loadWord64_clutch_events(ctx), target, 0, 0) != 1;
    if (image[Storage::nativeData_304a2c] == side)
        return;
    uint64_t settings = clientOptions(call, loadWord64_clutch_events(ctx),
                                      loadWord64_clutch_events(ctx + 0x18), 0, 0);
    uint64_t key = useItemKey(call, loadWord64_clutch_events(ctx), settings, 0, 0);
    pressKey(call, loadWord64_clutch_events(ctx), key, 0, 0);
    double hit[3];
    hitPosition(call, p(hit), loadWord64_clutch_events(ctx), target, 0);
    uint32_t converted[3];
    for (unsigned i = 0; i < 3; i++)
        converted[i] = (uint32_t)_mm_cvttsd_si32(_mm_set_sd(hit[i]));
    memcpy(image + Storage::nativeData_304a20, converted, 12);
}
API void onMovementCorrection(uint8_t *event, uint8_t *image, Dispatch call) {
    (void)call;
    if (image[Storage::nativeData_304a2d] == 1) {
        event[8] = 1;
        event[9] = 1;
    }
}

} // namespace reconstruction::Clutch
// END SOURCE modules/Clutch/clutch_events.cpp

// BEGIN SOURCE modules/Clutch/clutch_update.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"

#include <emmintrin.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
namespace reconstruction::Clutch {
namespace NativeEntry {
inline constexpr uint32_t squaredVectorDistance = 0x94b0;
inline constexpr uint32_t addRotation = 0x9de0;
inline constexpr uint32_t subtractRotation = 0x9e20;
inline constexpr uint32_t scaleRotation = 0x9e60;
inline constexpr uint32_t rotationTo = 0x9f80;
inline constexpr uint32_t randomRangeBits = 0xa050;
inline constexpr uint32_t clampFloat = 0xa1f0;
inline constexpr uint32_t wrapYaw = 0xa210;
inline constexpr uint32_t randomRangeSample = 0xa3e0;
inline constexpr uint32_t smoothedRandomSample = 0xa510;
inline constexpr uint32_t clientOptions = 0x22cf0;
inline constexpr uint32_t entityRotation = 0x23170;
inline constexpr uint32_t entityVelocity = 0x23550;
inline constexpr uint32_t entityBoundingBox = 0x23670;
inline constexpr uint32_t entityOnGround = 0x23780;
inline constexpr uint32_t entityHurtTime = 0x239f0;
inline constexpr uint32_t hitIntegerBlockCoordinates = 0x24ce0;
inline constexpr uint32_t jumpKey = 0x25080;
inline constexpr uint32_t physicalKeyWord = 0x25490;
inline constexpr uint32_t scheduleModuleAction = 0x284f0;
inline constexpr uint32_t heldItem = 0x28a50;
inline constexpr uint32_t itemIsBlock = 0x28b00;
inline constexpr uint32_t claimRotationPriority = 0x29800;
inline constexpr uint32_t publishRotationDelta = 0x29820;
inline constexpr uint32_t rotationOffset = 0x29850;
inline constexpr uint32_t rotationStateAvailable = 0x29f80;
inline constexpr uint32_t retainedRotation = 0x29ff0;
inline constexpr uint32_t floorBinary64 = 0xb29b0;
} // namespace NativeEntry

typedef struct clutch_args {
    uint64_t gpr[4];   /* RCX, RDX, R8, R9 */
    uint64_t xmm[4];   /* XMM0..XMM3 low 64-bit lanes */
    uint64_t stack[4]; /* first four stack arguments */
} clutch_args;
typedef struct clutch_result {
    uint64_t rax, xmm0;
} clutch_result;
struct clutch_dispatch {
    native_binding::Context &native;
    void (*unresolved)(uint32_t, const clutch_args *, clutch_result *, void *);
    void operator()(uint32_t rva, const clutch_args *args, clutch_result *result,
                    void *user) const {
        native_binding::Value value;
        if (native_binding::resolveFrame(native, rva, args->gpr, args->xmm, args->stack, value)) {
            if (value.floating) {
                result->xmm0 = value.bits;
                result->rax = 0;
            } else {
                result->rax = value.bits;
                result->xmm0 = 0;
            }
            return;
        }
        unresolved(rva, args, result, user);
    }
};

static uint64_t loadWord64_clutch_update(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t u32(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static int32_t i32(const void *p) {
    int32_t v;
    memcpy(&v, p, 4);
    return v;
}
static uint32_t wrapped_abs_difference(uint32_t a, uint32_t b) {
    uint32_t ab = a - b, ba = b - a;
    return (int32_t)b < (int32_t)a ? ab : ba;
}
static int candidate_score_rejected(float score, float best_score, int64_t max_distance,
                                    int64_t distance) {
    /* UCOMISS/JBE accepts unordered scores as well as score <= best. */
    return score > best_score && max_distance <= distance;
}
/* Exposes the exact arithmetic primitive only to the bounded verifier. */
uint32_t clutch_absdiff_test_adapter(uint32_t a, uint32_t b) {
    return wrapped_abs_difference(a, b);
}
int clutch_score_gate_test_adapter(uint32_t score_bits, uint32_t best_bits, int64_t max_distance,
                                   int64_t distance) {
    float score, best;
    memcpy(&score, &score_bits, 4);
    memcpy(&best, &best_bits, 4);
    return candidate_score_rejected(score, best, max_distance, distance);
}
int clutch_threshold_test_adapter(uint32_t score_bits, uint32_t threshold_bits) {
    float score, threshold;
    memcpy(&score, &score_bits, 4);
    memcpy(&threshold, &threshold_bits, 4);
    return score > threshold;
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
static void w32(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
static void w64(void *p, uint64_t v) {
    memcpy(p, &v, 8);
}
static uint32_t floatBits(float v) {
    uint32_t b;
    memcpy(&b, &v, 4);
    return b;
}
static uint64_t db(double v) {
    uint64_t b;
    memcpy(&b, &v, 8);
    return b;
}
static int32_t cvtt(float x) {
    return _mm_cvttss_si32(_mm_set_ss(x));
}
static int32_t cvttd(double x) {
    return _mm_cvttsd_si32(_mm_set_sd(x));
}
static uint64_t ptr(const void *p) {
    return (uint64_t)(uintptr_t)p;
}

static clutch_result invoke(clutch_dispatch d, void *user, uint32_t r, uint64_t rcx, uint64_t rdx,
                            uint64_t r8, uint64_t r9, uint64_t x0, uint64_t x1, uint64_t x2,
                            uint64_t x3, uint64_t s0, uint64_t s1) {
    clutch_args a = {{rcx, rdx, r8, r9}, {x0, x1, x2, x3}, {s0, s1, 0, 0}};
    clutch_result out = {0, 0};
    d(r, &a, &out, user);
    return out;
}
static clutch_result gcall(clutch_dispatch d, void *u, uint32_t r, uint64_t a, uint64_t b,
                           uint64_t c, uint64_t e) {
    return invoke(d, u, r, a, b, c, e, 0, 0, 0, 0, 0, 0);
}
static clutch_result xcall(clutch_dispatch d, void *u, uint32_t r, uint64_t x0, uint64_t x1,
                           uint64_t x2) {
    return invoke(d, u, r, 0, 0, 0, 0, x0, x1, x2, 0, 0, 0);
}
static clutch_result gxcall(clutch_dispatch d, void *u, uint32_t r, uint64_t rcx, uint64_t rdx,
                            uint64_t x0, uint64_t x1, uint64_t x2) {
    return invoke(d, u, r, rcx, rdx, 0, 0, x0, x1, x2, 0, 0, 0);
}
static clutch_result gx4call(clutch_dispatch d, void *u, uint32_t r, uint64_t rcx, uint64_t rdx,
                             uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3) {
    return invoke(d, u, r, rcx, rdx, 0, 0, x0, x1, x2, x3, 0, 0);
}
static clutch_result x4call(clutch_dispatch d, void *u, uint32_t r, uint64_t x0, uint64_t x1,
                            uint64_t x2, uint64_t x3) {
    return invoke(d, u, r, 0, 0, 0, 0, x0, x1, x2, x3, 0, 0);
}
static clutch_result gstack(clutch_dispatch d, void *u, uint32_t r, uint64_t a, uint64_t b,
                            uint64_t c, uint64_t e, uint64_t s0, uint64_t s1) {
    return invoke(d, u, r, a, b, c, e, 0, 0, 0, 0, s0, s1);
}
static uint64_t rv(clutch_result r) {
    return r.rax;
}
static float rf(clutch_result r) {
    uint32_t b = (uint32_t)r.xmm0;
    float f;
    memcpy(&f, &b, 4);
    return f;
}
static double rd(clutch_result r) {
    double d;
    memcpy(&d, &r.xmm0, 8);
    return d;
}
static uint64_t packed2(float lo, float hi) {
    return (uint64_t)floatBits(lo) | ((uint64_t)floatBits(hi) << 32);
}

static double dadd(double a, double b) {
    return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double dsub(double a, double b) {
    return _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double dmul(double a, double b) {
    return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static float narrow(double value) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(value)));
}
static int32_t signedBits(uint32_t bits) {
    int32_t value;
    memcpy(&value, &bits, 4);
    return value;
}
static uint32_t nativeMagnitude(uint32_t value) {
    uint32_t negated = 0u - value;
    return signedBits(negated) < 0 ? value : negated;
}
// RVA 0x49f40. Build a randomized point on the candidate block face and return
// the absolute yaw-plus-pitch correction. The vector bias keeps native lane
// order.
static float scorePlacementFace(const double *eye, uint64_t rotation, const double *position,
                                const uint32_t *block, const uint32_t *direction, double *result,
                                uint8_t *image, clutch_dispatch dispatch, void *user) {
    float margin = f32(image + 0x2f5868);
    uint32_t bx = block[0], by = block[1], bz = block[2];
    uint32_t dx = direction[0], dy = direction[1], dz = direction[2];
    uint64_t random =
        rv(xcall(dispatch, user, NativeEntry::randomRangeBits, 0, u32(image + 0x156170), 0));
    double initialPeriod = f64(image + 0x156178);
    float inward = rf(gxcall(dispatch, user, NativeEntry::smoothedRandomSample,
                             ptr(image + 0x304ab8), random, 0, 0, db(initialPeriod)));
    uint32_t freshDx = direction[0], freshDz = direction[2];
    float xAmount = f32(image + 0x2f5868);
    uint32_t low = u32(image + 0x156180), high = u32(image + 0x156184);
    random = rv(xcall(dispatch, user, NativeEntry::randomRangeBits, low, high, 0));
    double jitterPeriod = f64(image + 0x156188);
    float jitterX = rf(gxcall(dispatch, user, NativeEntry::smoothedRandomSample,
                              ptr(image + 0x304ac8), random, 0, 0, db(jitterPeriod)));
    float zAmount = f32(image + 0x2f5868);
    random = rv(xcall(dispatch, user, NativeEntry::randomRangeBits, low, high, 0));
    float jitterZ = rf(gxcall(dispatch, user, NativeEntry::smoothedRandomSample,
                              ptr(image + 0x304ad8), random, 0, 0, db(jitterPeriod)));
    __m128 factors = _mm_set_ps(0, 0, xAmount, zAmount),
           samples = _mm_set_ps(0, 0, jitterX, jitterZ);
    __m128d jitter = _mm_cvtps_pd(_mm_mul_ps(samples, factors)); // low Z, high X.
    double positionX = position[0];
    if (image[0x2f5a78] == 0) {
        double period = f64(image + 0x156178);
        double remainderX = rd(xcall(dispatch, user, 0xb2170, db(positionX), db(period), 0));
        double positionZ = position[2];
        double remainderZ = rd(xcall(dispatch, user, 0xb2170, db(positionZ), db(period), 0));
        __m128d absoluteMask = _mm_loadu_pd(reinterpret_cast<double *>(image + 0x156190));
        __m128d remainder = _mm_and_pd(_mm_set_pd(remainderZ, remainderX), absoluteMask);
        __m128d beyond =
            _mm_cmplt_pd(_mm_loadu_pd(reinterpret_cast<double *>(image + 0x1561a0)), remainder);
        __m128d adjustment = _mm_loadu_pd(reinterpret_cast<double *>(image + 0x1561b0));
        __m128d unchanged = _mm_andnot_pd(beyond, remainder);
        remainder = _mm_add_pd(remainder, adjustment);
        __m128d observed = _mm_set_pd(positionX, positionZ);
        __m128d previous = _mm_set_pd(f64(image + 0x304a48), f64(image + 0x304a58));
        __m128d moved = _mm_cmplt_pd(previous, observed);
        __m128d weights = _mm_or_pd(
            _mm_and_pd(adjustment, moved),
            _mm_andnot_pd(moved, _mm_loadu_pd(reinterpret_cast<double *>(image + 0x1561c0))));
        remainder = _mm_or_pd(_mm_and_pd(_mm_and_pd(remainder, absoluteMask), beyond), unchanged);
        jitter = _mm_add_pd(jitter, _mm_mul_pd(remainder, weights));
    }
    uint32_t ax = nativeMagnitude(dx), az = nativeMagnitude(dz);
    float product = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(margin), _mm_set_ss(inward)));
    double offset = dadd(double(product), f64(image + 0x1561d0));
    double inverse = dsub(initialPeriod, offset);
    double xLow = offset, xHigh = inverse, zLow = double(dz >> 31), zHigh = double(dz >> 31);
    if (az < ax) {
        xLow = double(dx >> 31);
        xHigh = xLow;
        zLow = offset;
        zHigh = inverse;
    }
    uint32_t blockX = dx + bx, blockY = dy + by, blockZ = dz + bz;
    double jitterLanes[2];
    _mm_storeu_pd(jitterLanes, jitter);
    float x = rf(xcall(dispatch, user, NativeEntry::clampFloat,
                       floatBits(narrow(dadd(xLow, double(signedBits(blockX))))),
                       floatBits(narrow(dadd(xHigh, double(signedBits(blockX))))),
                       floatBits(narrow(dadd(jitterLanes[1], positionX)))));
    double half = f64(image + 0x1561d8), baseY = dadd(double(signedBits(blockY)), half);
    uint32_t magnitude = nativeMagnitude(freshDx) + nativeMagnitude(freshDz);
    float y = rf(xcall(dispatch, user, NativeEntry::clampFloat, 0, u32(image + 0x1561e0),
                       floatBits(narrow(dmul(double(signedBits(magnitude)), half)))));
    double finalY = dadd(double(y), baseY);
    float z = rf(xcall(dispatch, user, NativeEntry::clampFloat,
                       floatBits(narrow(dadd(zLow, double(signedBits(blockZ))))),
                       floatBits(narrow(dadd(zHigh, double(signedBits(blockZ))))),
                       floatBits(narrow(dadd(jitterLanes[0], position[2])))));
    double point[3] = {double(x), finalY, double(z)}, from[3], to[3];
    memcpy(from, eye, 24);
    memcpy(to, point, 24);
    uint64_t desired = rv(gcall(dispatch, user, NativeEntry::rotationTo, ptr(from), ptr(to), 0, 0));
    uint64_t difference =
        rv(gcall(dispatch, user, NativeEntry::subtractRotation, desired, rotation, 0, 0));
    uint32_t pitch = uint32_t(difference >> 32) & 0x7fffffff;
    clutch_result wrapped = xcall(dispatch, user, NativeEntry::wrapYaw, uint32_t(difference), 0, 0);
    uint32_t yaw = uint32_t(wrapped.xmm0) & u32(image + 0x1561f0);
    float yawValue, pitchValue;
    memcpy(&yawValue, &yaw, 4);
    memcpy(&pitchValue, &pitch, 4);
    memcpy(result, point, 24);
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(yawValue), _mm_set_ss(pitchValue)));
}

/* RVA 0x48a50. Every non-local game/runtime call stays an explicit endpoint. */
void updatePlacementRotation(uint8_t *event, uint8_t *image, clutch_dispatch dispatch, void *user) {
    uint8_t *ctx = (uint8_t *)(uintptr_t)loadWord64_clutch_update(event + 8);
    uint64_t object = loadWord64_clutch_update(ctx), state = loadWord64_clutch_update(ctx + 0x28);
    uint8_t *st = image + Storage::nativeData_304a00;
    uint8_t *cfg = image + Storage::nativeData_2f5000;
    image[Storage::nativeData_304a1c] = 0;
    image[Storage::nativeData_304a2d] = 0;
    if (ctx[0x40] != 1)
        return;

    uint8_t fall =
        (uint8_t)gcall(dispatch, user, NativeEntry::entityOnGround, object, state, 0, 0).rax;
    uint32_t timer_result =
        (uint32_t)gcall(dispatch, user, NativeEntry::entityHurtTime, object, state, 0, 0).rax;
    uint32_t change = u32(st + 0x30) + 1u;
    w32(st + 0x30, timer_result == 0 ? change : 0);
    int32_t phase_active = i32(st + 0x34) > 0;
    if (phase_active)
        w32(st + 0x34, u32(st + 0x34) - 1u);

    if (phase_active && fall &&
        (uint8_t)gcall(dispatch, user, NativeEntry::rotationStateAvailable, 0, 0, 0, 0).rax &&
        cfg[0x930]) {
        uint64_t settings = rv(gcall(dispatch, user, NativeEntry::clientOptions, object,
                                     loadWord64_clutch_update(ctx + 0x18), 0, 0));
        uint64_t value = rv(gcall(dispatch, user, NativeEntry::jumpKey, object, settings, 0, 0));
        if ((uint8_t)gcall(dispatch, user, NativeEntry::physicalKeyWord, object, value, 0, 0).rax) {
            uint64_t angle =
                rv(gcall(dispatch, user, NativeEntry::entityRotation, object, state, 0, 0));
            uint64_t offset = rv(gcall(dispatch, user, NativeEntry::rotationOffset, 0, 0, 0, 0));
            angle = rv(gcall(dispatch, user, NativeEntry::addRotation, angle, offset, 0, 0));
            uint64_t silent = rv(gcall(dispatch, user, NativeEntry::retainedRotation, 0, 0, 0, 0));
            double multiplier = f64(st + 0x90) < 0.0 ? f64(image + Storage::nativeData_156160)
                                                     : f64(image + Storage::nativeData_156158);
            float lo = f32(image + Storage::nativeData_156168),
                  hi = f32(image + Storage::nativeData_15616c);
            float a = rf(gcall(dispatch, user, NativeEntry::randomRangeSample,
                               rv(xcall(dispatch, user, NativeEntry::randomRangeBits, floatBits(lo),
                                        floatBits(hi), 0)),
                               0, 0, 0));
            float lo_scaled = (float)((double)a * multiplier);
            float b = rf(gcall(dispatch, user, NativeEntry::randomRangeSample,
                               rv(xcall(dispatch, user, NativeEntry::randomRangeBits, floatBits(lo),
                                        floatBits(hi), 0)),
                               0, 0, 0));
            float hi_scaled = (float)((double)b * multiplier);
            w64(st + 0x90, db(f64(st + 0x90) + (double)lo_scaled));
            uint64_t random_pair =
                rv(invoke(dispatch, user, NativeEntry::scaleRotation, packed2(lo_scaled, hi_scaled),
                          0, 0, 0, 0, floatBits(f32(cfg + 0x868)), 0, 0, 0, 0));
            uint64_t sum =
                rv(gcall(dispatch, user, NativeEntry::addRotation, silent, random_pair, 0, 0));
            uint64_t delta =
                rv(gcall(dispatch, user, NativeEntry::subtractRotation, sum, angle, 0, 0));
            uint32_t adjusted =
                (uint32_t)xcall(dispatch, user, NativeEntry::wrapYaw, (uint32_t)delta, 0, 0).xmm0;
            uint64_t final = (delta & UINT64_C(0xffffffff00000000)) | adjusted;
            (void)gcall(dispatch, user, NativeEntry::publishRotationDelta, final, 0, 0, 0);
            image[Storage::nativeData_304a2d] = 1;
            w32(st + 0x38, (uint32_t)cvtt(f32(image + Storage::snapback_durationCurrent)));
            return;
        }
    }

    /* The placement search uses copied bounding boxes and checkpoint-owned
       tables; the source below retains their instruction-level order. */
    uint64_t aabb = rv(gcall(dispatch, user, NativeEntry::entityBoundingBox, object, state, 0, 0));
    uint8_t base_box[0x60] = {0};
    (void)gcall(dispatch, user, 0x25640, ptr(base_box), object, aabb, 0);
    uint64_t local = rv(gcall(dispatch, user, 0x23990, object, state, 0, 0));
    uint8_t target_box[0x60] = {0};
    (void)gcall(dispatch, user, 0x25540, ptr(target_box), object, local, 0);
    uint64_t yaw = rv(gcall(dispatch, user, NativeEntry::entityRotation, object, state, 0, 0));
    uint64_t off = rv(gcall(dispatch, user, NativeEntry::rotationOffset, 0, 0, 0, 0));
    yaw = rv(gcall(dispatch, user, NativeEntry::addRotation, yaw, off, 0, 0));
    uint64_t stored_yaw = yaw;
    if ((cfg[0x950] & fall) == 0 && (i32(st + 0x30) < 11 || !cfg[0x970])) {
        uint64_t target = rv(gcall(dispatch, user, 0x23930, object, state, 0, 0));
        if (target == 0) {
            if (cfg[0x990] == 1) {
                uint8_t orientation[0x40] = {0};
                (void)gcall(dispatch, user, NativeEntry::entityVelocity, ptr(orientation), object,
                            state, 0);
                double dot = rd(xcall(dispatch, user, Storage::nativeData_13cfd0,
                                      loadWord64_clutch_update(orientation),
                                      loadWord64_clutch_update(orientation + 16), 0));
                if (dot == 0.0)
                    goto no_search;
                uint32_t angle_bits = (uint32_t)gcall(dispatch, user, NativeEntry::entityRotation,
                                                      object, state, 0, 0)
                                          .rax;
                float angle;
                memcpy(&angle, &angle_bits, 4);
                double scale = f64(image + Storage::nativeData_156080);
                float normalized =
                    (float)((double)angle * scale / f64(image + Storage::nativeData_156088) +
                            scale);
                float fx = rf(xcall(dispatch, user, 0xb1cf0, floatBits(normalized), 0, 0));
                float fy = rf(xcall(dispatch, user, 0xb3590, floatBits(normalized), 0, 0));
                double ratio =
                    ((double)fy * f64(orientation + 16) + (double)fx * f64(orientation)) / dot;
                ratio = rd(xcall(dispatch, user, Storage::nativeData_13cfa0, db(ratio), 0, 0));
                if (!(f64(image + Storage::nativeData_156090) > ratio))
                    goto no_search;
            }
            image[Storage::nativeData_304a2c] = 0;
            double ox = f64(base_box), oy = f64(base_box + 8), oz = f64(base_box + 16);
            double tx = f64(target_box), ty = f64(target_box + 8), tz = f64(target_box + 16);
            double gx = (ox + f64(base_box + 24)) * f64(image + Storage::nativeData_156098);
            double gy = oy + f64(image + Storage::nativeData_1560a0);
            double gz = (oz + f64(base_box + 40)) * f64(image + Storage::nativeData_156098);
            uint64_t world = 0;
            uint64_t vt = loadWord64_clutch_update((void *)(uintptr_t)object);
            if (*(int32_t *)(uintptr_t)vt != 0)
                world = rv(gcall(dispatch, user, 0x242c0, object, 0, 0, 0));
            double dx = rd(xcall(dispatch, user, NativeEntry::floorBinary64, db(gx), 0, 0));
            double dy = rd(xcall(dispatch, user, NativeEntry::floorBinary64, db(gy), 0, 0));
            double dz = rd(xcall(dispatch, user, NativeEntry::floorBinary64, db(gz), 0, 0));
            int32_t ix = cvttd(dx), iy = cvttd(dy), iz = cvttd(dz);
            uint32_t vertical = 0;
            if (f32(cfg + 0x9c8) > 0.0f) {
                float n = 0.0f;
                int32_t step = 1, query_y = iy;
                do {
                    clutch_result block = gstack(dispatch, user, 0x24720, object,
                                                 loadWord64_clutch_update(ctx + 0x20), world,
                                                 (uint32_t)ix, (uint32_t)query_y, (uint32_t)iz);
                    if ((int32_t)gcall(dispatch, user, 0x24280, object, rv(block), 0, 0).rax != 0)
                        goto finish_search;
                    int32_t compared_step = step;
                    step = (int32_t)((uint32_t)step + 1u);
                    query_y = (int32_t)((uint32_t)query_y - 1u);
                    vertical++;
                    if (!(f32(cfg + 0x9c8) > (float)compared_step))
                        break;
                } while (1);
            }

            int32_t center[3] = {ix, iy, iz}, best[3] = {ix, iy, iz};
            double start[3] = {gx, gy, gz}, target_start[3] = {tx, ty, tz};
            double best_pos[3] = {gx, gy, gz}, best_target[3] = {tx, ty, tz};
            float best_score = f32(image + Storage::nativeData_1560a8);
            int64_t max_distance = -3; /* 0x49468 sentinel used before any retained winner */
            uint32_t attempts = 0;
            int16_t *count_table = (int16_t *)(void *)(image + Storage::nativeData_156280);
            int32_t select = cvtt(f32(cfg + 0xa00));
            uint32_t count = (uint16_t)count_table[select];
            const uint16_t *points =
                (const uint16_t *)(const void *)(image + Storage::nativeData_156290);

            /* Score the retained placement before testing the configured
               candidate table. The face scorer is recovered above at RVA 0x49f40. */
            if ((double)i32(st + 0x24) <= gy) {
                clutch_result block = gstack(
                    dispatch, user, 0x24720, object, loadWord64_clutch_update(ctx + 0x20), world,
                    (uint32_t)i32(st + 0x20), (uint32_t)i32(st + 0x24), (uint32_t)i32(st + 0x28));
                if ((int32_t)gcall(dispatch, user, 0x24280, object, rv(block), 0, 0).rax) {
                    uint8_t result_box[0x30] = {0};
                    uint32_t retained_block[3] = {(uint32_t)i32(st + 0x20),
                                                  (uint32_t)i32(st + 0x24),
                                                  (uint32_t)i32(st + 0x28)};
                    uint32_t retained_direction[3] = {
                        (uint32_t)(retained_block[0] - (uint32_t)center[0]),
                        (uint32_t)(retained_block[1] - (uint32_t)center[1]),
                        (uint32_t)(retained_block[2] - (uint32_t)center[2])};
                    float score = scorePlacementFace(
                        target_start, stored_yaw, start, reinterpret_cast<uint32_t *>(center),
                        retained_direction, reinterpret_cast<double *>(result_box), image, dispatch,
                        user);
                    /* 49554/4955b rejects only ordered score > threshold. */
                    if (!(score > f32(cfg + 0xa38))) {
                        double dist = rd(gcall(dispatch, user, NativeEntry::squaredVectorDistance,
                                               ptr(target_start), ptr(result_box), 0, 0));
                        if (dist < f64(image + Storage::nativeData_1560b0)) {
                            uint64_t va =
                                rv(gcall(dispatch, user, 0x254f0, object, ptr(target_start), 0, 0));
                            uint64_t vb =
                                rv(gcall(dispatch, user, 0x254f0, object, ptr(result_box), 0, 0));
                            clutch_result found =
                                gstack(dispatch, user, 0x24860, object,
                                       loadWord64_clutch_update(ctx + 0x20), va, vb, 0, 1);
                            if (rv(found)) {
                                uint32_t returned[3] = {0};
                                (void)gcall(dispatch, user, NativeEntry::hitIntegerBlockCoordinates,
                                            ptr(returned), object, rv(found), 0);
                                if (returned[0] == (uint32_t)i32(st + 0x20) &&
                                    returned[1] == (uint32_t)i32(st + 0x24) &&
                                    returned[2] == (uint32_t)i32(st + 0x28)) {
                                    memcpy(best_target, result_box, 24);
                                    best[0] = i32(st + 0x20);
                                    best[1] = i32(st + 0x24);
                                    best[2] = i32(st + 0x28);
                                    best_score = score;
                                }
                            }
                        }
                    }
                }
            }

            if (best_score != f32(image + Storage::nativeData_1560a8) || best_score != best_score) {
                uint32_t manhattan =
                    wrapped_abs_difference((uint32_t)best[0], (uint32_t)center[0]) +
                    wrapped_abs_difference((uint32_t)best[1], (uint32_t)center[1]) +
                    wrapped_abs_difference((uint32_t)best[2], (uint32_t)center[2]);
                /* 49bee subtracts two from the zero-extended R8D sum in 64 bits. */
                max_distance = (int64_t)(uint64_t)manhattan - 2;
            }
            for (uint32_t k = 0; k < count; k++) {
                uint16_t code = points[k];
                int32_t oxp = (code & 15) - 8, oyp = ((code >> 4) & 15) - 8,
                        ozp = ((code >> 8) & 15) - 8;
                int32_t cx = (int32_t)((uint32_t)center[0] + (uint32_t)oxp),
                        cy = (int32_t)((uint32_t)center[1] + (uint32_t)oyp),
                        cz = (int32_t)((uint32_t)center[2] + (uint32_t)ozp);
                clutch_result block =
                    gstack(dispatch, user, 0x24720, object, loadWord64_clutch_update(ctx + 0x20),
                           world, (uint32_t)cx, (uint32_t)cy, (uint32_t)cz);
                if ((int32_t)gcall(dispatch, user, 0x24280, object, rv(block), 0, 0).rax == 0)
                    continue;
                if (oxp == 0 && ozp == 0) {
                    if (cfg[0xa58])
                        goto finish_search;
                    /* The centered hole is patched with two independently
                       smoothed random offsets before publishing the vectors. */
                    float spread = f32(cfg + 0x868);
                    uint64_t r0 = rv(xcall(dispatch, user, NativeEntry::randomRangeBits, 0,
                                           floatBits(f32(image + Storage::nativeData_1560b8)), 0));
                    float jx = rf(gx4call(dispatch, user, NativeEntry::smoothedRandomSample,
                                          ptr(st + 0xb8), r0, 0, 0,
                                          db(f64(image + Storage::nativeData_1560c0)), 0));
                    double random_x =
                        f64(image + Storage::nativeData_1560c8) + (double)(jx * spread);
                    uint64_t r1 = rv(xcall(dispatch, user, NativeEntry::randomRangeBits,
                                           floatBits(f32(image + Storage::nativeData_1560d0)),
                                           floatBits(f32(image + Storage::nativeData_1560d4)), 0));
                    float sy = rf(gx4call(dispatch, user, NativeEntry::smoothedRandomSample,
                                          ptr(st + 0x98), r1, 0, 0,
                                          db(f64(image + Storage::nativeData_1560c0)), 0));
                    uint64_t r2 = rv(xcall(dispatch, user, NativeEntry::randomRangeBits,
                                           floatBits(f32(image + Storage::nativeData_1560d0)),
                                           floatBits(f32(image + Storage::nativeData_1560d4)), 0));
                    float sz = rf(gx4call(dispatch, user, NativeEntry::smoothedRandomSample,
                                          ptr(st + 0xa8), r2, 0, 0,
                                          db(f64(image + Storage::nativeData_1560c0)), 0));
                    int32_t cx_next = (int32_t)((uint32_t)cx + 1u),
                            cz_next = (int32_t)((uint32_t)cz + 1u);
                    float ax0 = (float)((double)cx + random_x),
                          ax1 = (float)((double)cx_next - random_x);
                    float ax2 = (float)(gx + (double)(sy * spread));
                    float az0 = (float)((double)cz + random_x),
                          az1 = (float)((double)cz_next - random_x);
                    float az2 = (float)(gz + (double)(sz * spread));
                    clutch_result ax = x4call(dispatch, user, NativeEntry::clampFloat,
                                              floatBits(ax0), floatBits(ax1), floatBits(ax2), 0);
                    clutch_result az = x4call(dispatch, user, NativeEntry::clampFloat,
                                              floatBits(az0), floatBits(az1), floatBits(az2), 0);
                    uint8_t picked[0x40] = {0};
                    (void)invoke(dispatch, user, 0x93b0, ptr(picked), 0, 0, 0, 0,
                                 db((double)rf(ax)), db(f64(image + Storage::nativeData_1560c0)),
                                 db((double)rf(az)), 0, 0);
                    memcpy(st + 0x48, picked, 24);
                    w32(st + 0x20, (uint32_t)cx);
                    w32(st + 0x24, (uint32_t)cy);
                    w32(st + 0x28, (uint32_t)cz);
                    image[Storage::nativeData_304a2c] = 1;
                    goto placement_found;
                }
                int64_t distance = (int64_t)abs(oxp) + abs(oyp) + abs(ozp);
                count = (uint16_t)count_table[distance];
                uint32_t candidate_block[3] = {(uint32_t)center[0], (uint32_t)center[1],
                                               (uint32_t)center[2]};
                uint32_t candidate_direction[3] = {(uint32_t)oxp, (uint32_t)oyp, (uint32_t)ozp};
                double evalbox[3] = {0};
                float score =
                    scorePlacementFace(target_start, stored_yaw, start, candidate_block,
                                       candidate_direction, evalbox, image, dispatch, user);
                if (candidate_score_rejected(score, best_score, max_distance, distance))
                    continue;
                double dist = rd(gcall(dispatch, user, NativeEntry::squaredVectorDistance,
                                       ptr(target_start), ptr(evalbox), 0, 0));
                if (dist < f64(image + Storage::nativeData_1560b0)) {
                    memcpy(best_target, evalbox, 24);
                    best[0] = cx;
                    best[1] = cy;
                    best[2] = cz;
                    best_score = score;
                }
                attempts++;
            }
            if (best_score > f32(cfg + 0xa38))
                goto finish_search;
            /* 498ba/498c5 publish one 24-byte helper output vector at
               image+304a48 (the 16-byte SIMD store overlaps the final
               qword store at +304a58). The normal winner route does not set
               the separate centered-placement flag at 304a2c. */
            memcpy(st + 0x48, best_target, 24);
            w32(st + 0x20, (uint32_t)best[0]);
            w32(st + 0x24, (uint32_t)best[1]);
            w32(st + 0x28, (uint32_t)best[2]);
        placement_found:
            (void)attempts;
            if (u32(cfg + 0xac8) == 1)
                (void)gcall(dispatch, user, 0x2af50, ptr(ctx), 0x1802f5580, 0, 0);
            else if (u32(cfg + 0xac8) == 2)
                (void)gcall(dispatch, user, 0x2af50, ptr(ctx), 0x1802f5580, 1, 0);
            uint64_t held = rv(gcall(dispatch, user, NativeEntry::heldItem, object, state, 0, 0));
            image[Storage::nativeData_304a1c] =
                (uint8_t)gcall(dispatch, user, NativeEntry::itemIsBlock, object, held, 0, 0).rax;
            if (image[Storage::nativeData_304a1c]) {
                float amount = f32(cfg + 0x830), low = f32(cfg + 0x868);
                float high = (float)((double)low * f64(image + Storage::nativeData_156098) +
                                     f64(image + Storage::nativeData_1560c0));
                uint64_t rand = rv(xcall(dispatch, user, NativeEntry::randomRangeBits,
                                         floatBits(f32(image + Storage::nativeData_1560d8)),
                                         floatBits(high), 0));
                float sample =
                    rf(gcall(dispatch, user, NativeEntry::randomRangeSample, rand, 0, 0, 0));
                w32(st + 0x38, (uint32_t)cvtt(_mm_cvtss_f32(
                                   _mm_mul_ss(_mm_set_ss(sample), _mm_set_ss(amount)))));
                w32(st + 0x34, 10);
                image[Storage::nativeData_304a3c] = cfg[0xaf0];
                goto timer_poll;
            }
        }
    }
finish_search:;
no_search:
    /* 48d13-48d60: shared fallback timer state, reached after rejected
       searches and every no-search gate. */
    image[Storage::nativeData_304a1c] = 0;
    if (i32(st + 0x38) > 0) {
        w32(st + 0x38, u32(st + 0x38) - 1u);
        w32(st + 0x40, (uint32_t)cvtt(f32(cfg + 0x7f8)));
        goto timer_poll;
    }
    if (i32(st + 0x40) > 0) {
        w32(st + 0x40, u32(st + 0x40) - 1u);
        goto timer_poll;
    }
    if (image[Storage::nativeData_304a3c] != 1)
        return;
    (void)gcall(dispatch, user, NativeEntry::scheduleModuleAction,
                loadWord64_clutch_update(ctx + 8), 0x1802f5580, 0, 0);
    image[Storage::nativeData_304a3c] = 0;
    return;

timer_poll:
    if ((uint8_t)gcall(dispatch, user, NativeEntry::claimRotationPriority, 1000, 0, 0, 0).rax == 0)
        return;
    image[Storage::nativeData_304a2d] = 1;
    if (image[Storage::nativeData_304a1c] == 0) {
        if (i32(st + 0x38) > 0)
            return;
        if (i32(st + 0x40) < 1) {
            /* 48ffc disables the latched input only when it was armed. */
            if (image[Storage::nativeData_304a3c] != 1)
                return;
            (void)gcall(dispatch, user, NativeEntry::scheduleModuleAction,
                        loadWord64_clutch_update(ctx + 8), 0x1802f5580, 0, 0);
            image[Storage::nativeData_304a3c] = 0;
            return;
        }
        if ((uint8_t)gcall(dispatch, user, NativeEntry::rotationStateAvailable, 0, 0, 0, 0).rax ==
            0)
            return;
        uint64_t angle =
            rv(gcall(dispatch, user, NativeEntry::entityRotation, object, state, 0, 0));
        uint64_t offset = rv(gcall(dispatch, user, NativeEntry::rotationOffset, 0, 0, 0, 0));
        uint64_t shifted = rv(gcall(dispatch, user, NativeEntry::addRotation, angle, offset, 0, 0));
        uint64_t phase = rv(gcall(dispatch, user, NativeEntry::retainedRotation, 0, 0, 0, 0));
        uint64_t delta =
            rv(gcall(dispatch, user, NativeEntry::subtractRotation, phase, shifted, 0, 0));
        uint32_t adjusted =
            (uint32_t)xcall(dispatch, user, NativeEntry::wrapYaw, (uint32_t)delta, 0, 0).xmm0;
        float rate =
            (float)((double)f32(image + Storage::nativeData_1560d8) / (double)i32(st + 0x40));
        uint64_t packed = (delta & UINT64_C(0xffffffff00000000)) | adjusted;
        uint64_t final = rv(invoke(dispatch, user, NativeEntry::scaleRotation, packed, 0, 0, 0, 0,
                                   floatBits(rate), 0, 0, 0, 0));
        (void)gcall(dispatch, user, NativeEntry::publishRotationDelta, final, 0, 0, 0);
    } else {
        /* 48d81 onward: active-latch geometry gate and recovered smoothing
           continuation. Game and math calls remain explicit dependencies. */
        double current[4] = {0}, expanded[4] = {0};
        (void)invoke(dispatch, user, 0x233b0, ptr(current), object, state, 0, 0, 0, 0, 0, 0, 0);
        (void)invoke(dispatch, user, 0x9430, ptr(expanded), ptr(current), 0, 0, 0, 0,
                     loadWord64_clutch_update(image + Storage::nativeData_1560e8), 0, 0, 0);
        double query[6] = {(double)i32(st + 0x20) + f64(image + Storage::nativeData_1560f0),
                           (double)i32(st + 0x24) + f64(image + Storage::nativeData_1560f8),
                           (double)i32(st + 0x28) + f64(image + Storage::nativeData_156100),
                           (double)i32(st + 0x20) + f64(image + Storage::nativeData_156108),
                           (double)i32(st + 0x24) + 1.0,
                           (double)i32(st + 0x28) + f64(image + Storage::nativeData_1560e0)};
        double target[3] = {f64(target_box), f64(target_box + 8), f64(target_box + 16)};
        double collision[3] = {expanded[0], expanded[1], expanded[2]}, collision_out[3] = {0};
        uint64_t hit = rv(gcall(dispatch, user, 0x9b00, ptr(query), ptr(target), ptr(collision),
                                ptr(collision_out)));
        if ((uint8_t)hit &&
            collision_out[1] < (double)i32(st + 0x24) + f64(image + Storage::nativeData_156110))
            return;
        double selected[3] = {f64(target_box), f64(target_box + 8), f64(target_box + 16)};
        double retained[3] = {f64(st + 0x48), f64(st + 0x50), f64(st + 0x58)};
        uint64_t packed =
            rv(gcall(dispatch, user, NativeEntry::rotationTo, ptr(selected), ptr(retained), 0, 0));
        uint32_t gate_bits = (uint32_t)(packed >> 32);
        float gate;
        memcpy(&gate, &gate_bits, 4);
        uint64_t mixed =
            rv(gcall(dispatch, user, NativeEntry::subtractRotation, packed, stored_yaw, 0, 0));
        uint32_t high_bits = (uint32_t)(mixed >> 32);
        float high;
        memcpy(&high, &high_bits, 4);
        float gate_value;
        if (!((double)gate > f64(image + Storage::nativeData_156118))) {
            gate_value = rf(xcall(dispatch, user, NativeEntry::wrapYaw, (uint32_t)mixed, 0, 0));
        } else {
            uint64_t random = rv(xcall(dispatch, user, NativeEntry::randomRangeBits,
                                       floatBits(f32(image + Storage::nativeData_156120)),
                                       floatBits(f32(image + Storage::nativeData_156124)), 0));
            gate_value =
                rf(gx4call(dispatch, user, NativeEntry::smoothedRandomSample, ptr(st + 0x60),
                           random, 0, 0,
                           loadWord64_clutch_update(image + Storage::nativeData_156098), 0)) *
                f32(image + Storage::randomizationCurrent);
        }
        float cfg_scale = f32(cfg + 0x868);
        double scale = f64(image + Storage::nativeData_156128),
               bias = f64(image + Storage::nativeData_1560c0);
        float random_low = (float)((double)cfg_scale * scale + bias);
        float random_high = f32(image + Storage::nativeData_1560d8);
        float state_scale = f32(cfg + 0x8a0);
        uint64_t ra = rv(xcall(dispatch, user, NativeEntry::randomRangeBits, floatBits(random_low),
                               floatBits(random_high), 0));
        float state_a =
            rf(gx4call(dispatch, user, 0xa870, ptr(image + Storage::nativeData_304a70), ra, 0, 0,
                       loadWord64_clutch_update(image + Storage::nativeData_156130),
                       loadWord64_clutch_update(image + Storage::nativeData_1560c0))) *
            state_scale;
        float random_low2 = (float)((double)cfg_scale * scale + bias);
        uint64_t rb = rv(xcall(dispatch, user, NativeEntry::randomRangeBits, floatBits(random_low2),
                               floatBits(random_high), 0));
        float state_b =
            rf(gx4call(dispatch, user, 0xa870, ptr(image + Storage::nativeData_304a80), rb, 0, 0,
                       loadWord64_clutch_update(image + Storage::nativeData_156130),
                       loadWord64_clutch_update(image + Storage::nativeData_1560c0))) *
            state_scale;
        uint32_t sign_mask = u32(image + Storage::nativeData_156140);
        uint32_t first =
            (uint32_t)xcall(dispatch, user, NativeEntry::clampFloat, floatBits(state_a) ^ sign_mask,
                            floatBits(state_a), floatBits(gate_value))
                .xmm0;
        uint32_t second =
            (uint32_t)xcall(dispatch, user, NativeEntry::clampFloat, floatBits(state_b) ^ sign_mask,
                            floatBits(state_b), floatBits(high))
                .xmm0;
        float accum_a = f32(cfg + 0x8d8);
        float lo = f32(image + Storage::nativeData_156150),
              hi = f32(image + Storage::nativeData_1560b8);
        uint64_t rc = rv(
            xcall(dispatch, user, NativeEntry::randomRangeBits, floatBits(lo), floatBits(hi), 0));
        accum_a += rf(gx4call(dispatch, user, 0xa870, ptr(image + Storage::nativeData_304a70), rc,
                              0, 0, loadWord64_clutch_update(image + Storage::nativeData_156130),
                              loadWord64_clutch_update(image + Storage::nativeData_1560c0)));
        float accum_b = f32(cfg + 0x8d8);
        uint64_t rd0 = rv(
            xcall(dispatch, user, NativeEntry::randomRangeBits, floatBits(lo), floatBits(hi), 0));
        accum_b += rf(gx4call(dispatch, user, 0xa870, ptr(image + Storage::nativeData_304a80), rd0,
                              0, 0, loadWord64_clutch_update(image + Storage::nativeData_156130),
                              loadWord64_clutch_update(image + Storage::nativeData_1560c0)));
        accum_a = accum_a * gate_value;
        accum_b = accum_b * high;
        float out_lo = rf(
            xcall(dispatch, user, 0xa2b0, first, floatBits(accum_a), floatBits(f32(cfg + 0x910))));
        float out_hi = rf(
            xcall(dispatch, user, 0xa2b0, second, floatBits(accum_b), floatBits(f32(cfg + 0x910))));
        (void)gcall(dispatch, user, NativeEntry::publishRotationDelta, packed2(out_lo, out_hi), 0,
                    0, 0);
    }
    return;
}

} // namespace reconstruction::Clutch
// END SOURCE modules/Clutch/clutch_update.cpp

// Convenient borrowed-state interface

namespace shareable {
class Clutch {
  public:
    static constexpr const char *kName = "Clutch";
    static constexpr const char *kDescription = "Clutches for you when falling.";
    explicit Clutch(std::uint8_t *image) : image_(image) {}
    // Range. Config key: range.
    NumberSetting &range() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f59d0);
    }
    // FOV. Config key: max_aim_dist.
    NumberSetting &max_aim_dist() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f5a08);
    }
    // Minimum height. Config key: min_height.
    NumberSetting &min_height() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f5998);
    }
    // Click speed. Config key: click_speed.
    NumberSetting &click_speed() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f5790);
    }
    // Randomization. Config key: randomization.
    NumberSetting &randomization() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f5838);
    }
    // Select blocks. Config key: select_blocks.
    ChoiceSetting &select_blocks() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f5a98);
    }
    // Option labels observed in the captured metadata.
    enum class SelectBlocksMode : std::uint32_t { No = 0, OnDepletion = 1, Always = 2 };
    // Only place sideways. Config key: sideways_only.
    BooleanSetting &sideways_only() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f5a40);
    }
    // Base speed. Config key: aim_speed.
    NumberSetting &aim_speed() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f5870);
    }
    // Acceleration. Config key: aim_mult.
    NumberSetting &aim_mult() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f58a8);
    }
    // Acceleration strength. Config key: aim_mult_strength.
    NumberSetting &aim_mult_strength() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f58e0);
    }
    // Multipoint. Config key: aim_multipoint.
    BooleanSetting &aim_multipoint() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f5a60);
    }
    // Delay. Config key: snapback_delay.
    NumberSetting &snapback_delay() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f5800);
    }
    // Duration. Config key: snapback_duration.
    NumberSetting &snapback_duration() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f57c8);
    }
    // Keep jump direction. Config key: snapback_instant_on_jump.
    BooleanSetting &snapback_instant_on_jump() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f5918);
    }
    // Disable afterwards. Config key: snapback_disable_after.
    BooleanSetting &snapback_disable_after() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f5ad8);
    }
    // In air. Config key: require_air.
    BooleanSetting &require_air() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f5938);
    }
    // Damaged. Config key: require_damage.
    BooleanSetting &require_damage() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f5958);
    }
    // Moving backwards. Config key: require_backwards.
    BooleanSetting &require_backwards() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f5978);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_clutch_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_clutch_settings(&context, image_, &dependencies);
    }
    static uint32_t clutch_absdiff_test_adapter(uint32_t a, uint32_t b) {
        return ::reconstruction::Clutch::clutch_absdiff_test_adapter(a, b);
    }
    static int clutch_score_gate_test_adapter(uint32_t score_bits, uint32_t best_bits,
                                              int64_t max_distance, int64_t distance) {
        return ::reconstruction::Clutch::clutch_score_gate_test_adapter(score_bits, best_bits,
                                                                        max_distance, distance);
    }
    static int clutch_threshold_test_adapter(uint32_t score_bits, uint32_t threshold_bits) {
        return ::reconstruction::Clutch::clutch_threshold_test_adapter(score_bits, threshold_bits);
    }
    void updatePlacementRotation(uint8_t *event, ::reconstruction::Clutch::clutch_dispatch dispatch,
                                 void *user) {
        ::reconstruction::Clutch::updatePlacementRotation(event, image_, dispatch, user);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
