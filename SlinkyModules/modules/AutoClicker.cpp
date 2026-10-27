// Auto Clicker

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Auto_Clicker.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Auto_Clicker.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Auto Clicker: lib_win settings 0x2d290.
static constexpr SettingsStep settings_steps_Surface_Auto_Clicker[] = {
    {SettingsControl::choice, "pattern", 0x2e9650},
    {SettingsControl::number, "target_cps", 0x2e95e8},
    {SettingsControl::boolean, "randomize_cps", 0x2e9620},
    {SettingsControl::boolean, "exhaust", 0x2e9690},
    {SettingsControl::boolean, "allow_block_break", 0x2e9588},
    {SettingsControl::boolean, "allow_inventory", 0x2e9548},
    {SettingsControl::boolean, "inventory_randomize", 0x2e9568},
    {SettingsControl::boolean, "require_weapon", 0x2e95a8},
    {SettingsControl::boolean, "require_not_using_item", 0x2e95c8},
};
static constexpr ModuleSurface surface_Surface_Auto_Clicker{
    nullptr, 0, settings_steps_Surface_Auto_Clicker,
    std::size(settings_steps_Surface_Auto_Clicker)};

extern "C" __declspec(dllexport) void
recovered_auto_clicker_settings(SettingsContext *context, std::uint8_t *image,
                                const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Auto_Clicker, context, image, *dependencies);
}

// Auto Clicker: lib_win runtime UI 0x2d190.
extern "C" __declspec(dllexport) void
recovered_auto_clicker_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                          const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "In-game");
    dependencies->choice(layout, ui, image + 0x2e9650);
    dependencies->number(layout, ui, image + 0x2e95e8);
    dependencies->checkbox(layout, ui, image + 0x2e9620);
    dependencies->checkbox(layout, ui, image + 0x2e9690);
    dependencies->checkbox(layout, ui, image + 0x2e9588);
    dependencies->section(ui, layout, "Inventory");
    dependencies->checkbox(layout, ui, image + 0x2e9548);
    if (image[0x2e9560] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2e9568);
    }
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2e95a8);
    dependencies->checkbox(layout, ui, image + 0x2e95c8);
}
// END SOURCE native/verified/surfaces/Surface_Auto_Clicker.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Auto_Clicker/auto_clicker.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_12CB6F2AB19DAA190A04
#define SLINKY_SHARE_12CB6F2AB19DAA190A04
// BEGIN SOURCE modules/Auto_Clicker/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Auto_Clicker {
namespace Storage {
inline constexpr std::uint32_t nativeData_150328 = 0x150328;
inline constexpr std::uint32_t nativeData_150330 = 0x150330;
inline constexpr std::uint32_t nativeData_150338 = 0x150338;
inline constexpr std::uint32_t nativeData_15033c = 0x15033c;
inline constexpr std::uint32_t nativeData_150340 = 0x150340;
inline constexpr std::uint32_t nativeData_150348 = 0x150348;
inline constexpr std::uint32_t nativeData_150350 = 0x150350;
inline constexpr std::uint32_t nativeData_150354 = 0x150354;
inline constexpr std::uint32_t nativeData_150358 = 0x150358;
inline constexpr std::uint32_t nativeData_150360 = 0x150360;
inline constexpr std::uint32_t nativeData_150368 = 0x150368;
inline constexpr std::uint32_t nativeData_150370 = 0x150370;
inline constexpr std::uint32_t nativeData_150374 = 0x150374;
inline constexpr std::uint32_t nativeData_150378 = 0x150378;
inline constexpr std::uint32_t nativeData_150380 = 0x150380;
inline constexpr std::uint32_t nativeData_150384 = 0x150384;
inline constexpr std::uint32_t nativeData_150388 = 0x150388;
inline constexpr std::uint32_t nativeData_150390 = 0x150390;
inline constexpr std::uint32_t nativeData_150394 = 0x150394;
inline constexpr std::uint32_t nativeData_150398 = 0x150398;
inline constexpr std::uint32_t nativeData_1503a0 = 0x1503a0;
inline constexpr std::uint32_t nativeData_1503a4 = 0x1503a4;
inline constexpr std::uint32_t nativeData_1503a8 = 0x1503a8;
inline constexpr std::uint32_t nativeData_1503b0 = 0x1503b0;
inline constexpr std::uint32_t nativeData_1503b8 = 0x1503b8;
inline constexpr std::uint32_t nativeData_1503c0 = 0x1503c0;
inline constexpr std::uint32_t nativeData_1503c8 = 0x1503c8;
inline constexpr std::uint32_t nativeData_1503d0 = 0x1503d0;
inline constexpr std::uint32_t nativeData_1503d4 = 0x1503d4;
inline constexpr std::uint32_t nativeData_1505a0 = 0x1505a0;
inline constexpr std::uint32_t moduleDescriptor = 0x2e9330;
inline constexpr std::uint32_t nativeData_2e9540 = 0x2e9540;
inline constexpr std::uint32_t allow_inventoryRecord = 0x2e9548;
inline constexpr std::uint32_t allow_inventoryCurrent = 0x2e9560;
inline constexpr std::uint32_t inventory_randomizeRecord = 0x2e9568;
inline constexpr std::uint32_t inventory_randomizeCurrent = 0x2e9580;
inline constexpr std::uint32_t allow_block_breakRecord = 0x2e9588;
inline constexpr std::uint32_t allow_block_breakCurrent = 0x2e95a0;
inline constexpr std::uint32_t require_weaponRecord = 0x2e95a8;
inline constexpr std::uint32_t require_weaponCurrent = 0x2e95c0;
inline constexpr std::uint32_t require_not_using_itemRecord = 0x2e95c8;
inline constexpr std::uint32_t require_not_using_itemCurrent = 0x2e95e0;
inline constexpr std::uint32_t target_cpsRecord = 0x2e95e8;
inline constexpr std::uint32_t target_cpsCurrent = 0x2e9618;
inline constexpr std::uint32_t randomize_cpsRecord = 0x2e9620;
inline constexpr std::uint32_t randomize_cpsCurrent = 0x2e9638;
inline constexpr std::uint32_t patternRecord = 0x2e9650;
inline constexpr std::uint32_t patternCurrent = 0x2e9680;
inline constexpr std::uint32_t exhaustRecord = 0x2e9690;
inline constexpr std::uint32_t exhaustCurrent = 0x2e96a8;
inline constexpr std::uint32_t previousRotation = 0x2f7c88;
inline constexpr std::uint32_t primaryButtonSelector = 0x2f7c90;
inline constexpr std::uint32_t remainingClickTime = 0x2f7c98;
inline constexpr std::uint32_t previousClickInterval = 0x2f7ca0;
inline constexpr std::uint32_t nativeData_2f7ca8 = 0x2f7ca8;
inline constexpr std::uint32_t inventoryPrimaryWasPressed = 0x2f7cb8;
inline constexpr std::uint32_t nativeData_2f7cc0 = 0x2f7cc0;
inline constexpr std::uint32_t currentHitKind = 0x2f7cd0;
inline constexpr std::uint32_t nativeData_2f7cd8 = 0x2f7cd8;
inline constexpr std::uint32_t nativeData_2f7ce8 = 0x2f7ce8;
inline constexpr std::uint32_t nativeData_2f7cf8 = 0x2f7cf8;
inline constexpr std::uint32_t quickClickPending = 0x2f7d00;
inline constexpr std::uint32_t nativeData_2f7d08 = 0x2f7d08;
inline constexpr std::uint32_t nativeData_2f7d18 = 0x2f7d18;
inline constexpr std::uint32_t nativeData_2f7d28 = 0x2f7d28;
inline constexpr std::uint32_t intervalAdjustmentCountdown = 0x2f7d60;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    ChoiceSetting &pattern() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::patternRecord);
    }
    NumberSetting &target_cps() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::target_cpsRecord);
    }
    BooleanSetting &randomize_cps() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::randomize_cpsRecord);
    }
    BooleanSetting &exhaust() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::exhaustRecord);
    }
    BooleanSetting &allow_block_break() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::allow_block_breakRecord);
    }
    BooleanSetting &allow_inventory() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::allow_inventoryRecord);
    }
    BooleanSetting &inventory_randomize() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::inventory_randomizeRecord);
    }
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_weaponRecord);
    }
    BooleanSetting &require_not_using_item() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_not_using_itemRecord);
    }
};
// Runtime-observed native labels for config key "pattern". Numeric values preserved.
enum class PatternMode : std::uint32_t {
    Jitter = 0,
    Butterfly = 1,
};
} // namespace reconstruction::Auto_Clicker
// END SOURCE modules/Auto_Clicker/Settings.hpp

#endif // SLINKY_SHARE_12CB6F2AB19DAA190A04

#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
namespace reconstruction::Auto_Clicker {
using dependency = native_binding::WordEndpoints;
// Native entry 0x9ee0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t rotationDistance(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                 uint64_t a3) {
    return api(0x9ee0, a0, a1, a2, a3);
}
// Native entry 0xa050; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t randomRangeBits(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                uint64_t a3) {
    return api(0xa050, a0, a1, a2, a3);
}
// Native entry 0xa3e0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t randomRangeSample(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                  uint64_t a3) {
    return api(0xa3e0, a0, a1, a2, a3);
}
// Native entry 0xa460; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t probabilityGate(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                uint64_t a3) {
    return api(0xa460, a0, a1, a2, a3);
}
// Native entry 0xa510; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t smoothedRandomSample(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0xa510, a0, a1, a2, a3);
}
// Native entry 0xaa30; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t smoothedProbabilityGate(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                        uint64_t a3) {
    return api(0xaa30, a0, a1, a2, a3);
}
// Native entry 0xab00; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t randomWaveSample(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                 uint64_t a3) {
    return api(0xab00, a0, a1, a2, a3);
}
// Native entry 0x22c70; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t clientTimer(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x22c70, a0, a1, a2, a3);
}
// Native entry 0x22c90; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t currentScreen(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x22c90, a0, a1, a2, a3);
}
// Native entry 0x22cf0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t clientOptions(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x22cf0, a0, a1, a2, a3);
}
// Native entry 0x22e10; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t currentHitResult(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                 uint64_t a3) {
    return api(0x22e10, a0, a1, a2, a3);
}
// Native entry 0x22eb0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t updateClientInput(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                  uint64_t a3) {
    return api(0x22eb0, a0, a1, a2, a3);
}
// Native entry 0x23170; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityRotation(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x23170, a0, a1, a2, a3);
}
// Native entry 0x23f40; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityInventory(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                uint64_t a3) {
    return api(0x23f40, a0, a1, a2, a3);
}
// Native entry 0x23f90; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityUsingItem(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                uint64_t a3) {
    return api(0x23f90, a0, a1, a2, a3);
}
// Native entry 0x24b50; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t hitResultType(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x24b50, a0, a1, a2, a3);
}
// Native entry 0x25270; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t attackKey(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x25270, a0, a1, a2, a3);
}
// Native entry 0x25410; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t keyCode(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x25410, a0, a1, a2, a3);
}
// Native entry 0x259a0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_259a0(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x259a0, a0, a1, a2, a3);
}
// Native entry 0x25ad0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_25ad0(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x25ad0, a0, a1, a2, a3);
}
// Native entry 0x25b60; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_25b60(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x25b60, a0, a1, a2, a3);
}
// Native entry 0x26190; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_26190(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x26190, a0, a1, a2, a3);
}
// Native entry 0x261b0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_261b0(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x261b0, a0, a1, a2, a3);
}
// Native entry 0x380b0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t weaponEligibility(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                  uint64_t a3) {
    return api(0x380b0, a0, a1, a2, a3);
}
// Native entry 0x4c390; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_4c390(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x4c390, a0, a1, a2, a3);
}

static uint64_t loadWord64(const void *p) {
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
static double loadDouble(const void *p) {
    double v;
    memcpy(&v, p, 8);
    return v;
}
static void storeWord32(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
static void storeDouble(void *p, double v) {
    memcpy(p, &v, 8);
}
static float floatFromWord(uint64_t n) {
    uint32_t v = (uint32_t)n;
    return loadFloat(&v);
}
static uint32_t floatBits(float v) {
    return loadWord32(&v);
}
static double add(double a, double b) {
    return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double mul(double a, double b) {
    return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double divide(double a, double b) {
    return _mm_cvtsd_f64(_mm_div_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static float roundf(double a) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(a)));
}
static float addFloatSse(float a, float b) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float multiplyFloatSse(float a, float b) {
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float divideFloatSse(float a, float b) {
    return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static uint64_t random_range(dependency call, float lo, float hi) {
    return randomRangeBits(call, floatBits(lo), floatBits(hi), 0, 0);
}
static float smooth(dependency call, uint8_t *image, uint32_t state, uint64_t sample,
                    uint64_t period) {
    return floatFromWord(smoothedRandomSample(call, (uintptr_t)(image + state), sample, period, 0));
}
static void emit(dependency call, uint8_t button, uint8_t pressed) {
    nativeBoundary_4c390(call, button, pressed, 0, 0);
}

// RVA 0x2d3b0. The raw pseudocode associates the final additions incorrectly.
// Runtime-observed instructions add the bias to the scaled wave first, then
// add the promoted interval. UCOMISS/JA also sends unordered values to retry.
static uint8_t adjustInterval(uint8_t *image, dependency api, float *interval, float turnBias) {
    uint32_t rawCount = loadWord32(image + Storage::intervalAdjustmentCountdown);
    int32_t count;
    memcpy(&count, &rawCount, 4);
    if (count < 1) {
        if (image[Storage::exhaustCurrent] != 1)
            return 0;
        double promotedBias = static_cast<double>(turnBias);
        float lower = roundf(add(loadDouble(image + 0x1503d8), promotedBias));
        float upper = roundf(add(promotedBias, loadDouble(image + 0x1503e0)));
        uint64_t bounds = floatBits(lower) | (uint64_t(floatBits(upper)) << 32);
        if (!uint8_t(smoothedProbabilityGate(api, uintptr_t(image + 0x2f7d38), bounds,
                                             loadWord64(image + 0x1503e8), 0)))
            return 0;
        uint64_t sample = random_range(api, 0.0f, loadFloat(image + 0x1503f0));
        float threshold = floatFromWord(randomRangeSample(api, sample, 0, 0, 0));
        sample = random_range(api, loadFloat(image + 0x1503f4), loadFloat(image + 0x1503f8));
        float first = smooth(api, image, 0x2f7d48, sample, loadWord64(image + 0x150400));
        count = 3;
        if (!(first > threshold)) {
            sample = random_range(api, loadFloat(image + 0x150408), loadFloat(image + 0x15040c));
            float retry = smooth(api, image, 0x2f7d48, sample, loadWord64(image + 0x150400));
            count = uint32_t(retry > threshold) + 1;
        }
    }
    storeWord32(image + Storage::intervalAdjustmentCountdown, uint32_t(count) - 1u);
    float wave = floatFromWord(randomWaveSample(api, uintptr_t(image + 0x2f7d58), 0, 0, 0));
    double scaled = mul(static_cast<double>(wave), loadDouble(image + 0x150410));
    double offset = add(scaled, loadDouble(image + 0x1503d8));
    double result = add(static_cast<double>(*interval), offset);
    *interval = roundf(result);
    return 1;
}

void onTick(uint8_t *event, uint8_t *image, dependency call) {
    uint8_t *ctx = (uint8_t *)(uintptr_t)loadWord64(event + 8);
    uint64_t settings = clientOptions(call, loadWord64(ctx), loadWord64(ctx + 0x18), 0, 0);
    uint64_t key = attackKey(call, loadWord64(ctx), settings, 0, 0);
    uint32_t code = (uint32_t)keyCode(call, loadWord64(ctx), key, 0, 0);
    image[Storage::primaryButtonSelector] = (code == 0xffffff9d);
    if (ctx[0x40] != 1)
        return;
    uint64_t angle = entityRotation(call, loadWord64(ctx), loadWord64(ctx + 0x28), 0, 0);
    memcpy(image + Storage::previousRotation, &angle, 8);
    uint8_t *other = (uint8_t *)(uintptr_t)loadWord64(image + Storage::nativeData_1505a0);
    if (other[0x14] == 0)
        updateClientInput(call, loadWord64(ctx), loadWord64(ctx + 0x18), 0, 0);
}
void updateHitKind(uint8_t *event, uint8_t *image, dependency call) {
    uint8_t *ctx = (uint8_t *)(uintptr_t)loadWord64(event + 8);
    if (ctx[0x40] != 1)
        return;
    uint64_t hit = currentHitResult(call, loadWord64(ctx), loadWord64(ctx + 0x18), 0, 0);
    uint32_t kind = hit ? (uint32_t)hitResultType(call, loadWord64(ctx), hit, 0, 0) : 0;
    storeWord32(image + Storage::currentHitKind, kind);
}
static void cleanup(uint8_t *image, double delay) {
    storeDouble(image + Storage::remainingClickTime, delay);
    storeWord32(image + Storage::nativeData_2e9540, 0xffffffff);
}
static void menu(uint8_t *ctx, uint8_t *image, dependency call, uint8_t physical, uint8_t synthetic,
                 double idle) {
    uint64_t game, screen, inventory, slot;
    uint32_t slot_id;
    if (synthetic & 1)
        emit(call, image[Storage::primaryButtonSelector] ^ 1, (uint8_t)(~physical) & 1);
    if (!currentScreen(call, loadWord64(ctx), loadWord64(ctx + 0x18), 0, 0)) {
        cleanup(image, idle);
        return;
    }
    uint8_t *keys = (uint8_t *)(uintptr_t)loadWord64(ctx + 0x30);
    uint8_t primary = keys[1];
    if (primary != 1 || image[Storage::inventoryPrimaryWasPressed] != 1) {
        image[Storage::inventoryPrimaryWasPressed] = (primary == 1);
        goto idle_delay;
    }
    if (image[Storage::allow_inventoryCurrent] != 1 || !((keys[0x62] | keys[0x63]) & 1))
        goto idle_delay;
    game = loadWord64(ctx);
    screen = currentScreen(call, game, loadWord64(ctx + 0x18), 0, 0);
    inventory = entityInventory(call, game, loadWord64(ctx + 0x28), 0, 0);
    slot = nativeBoundary_25b60(call, game, screen, 0, 0);
    if (!slot)
        goto idle_delay;
    if (nativeBoundary_25ad0(call, game, inventory, 0, 0))
        goto idle_delay;
    slot_id = (uint32_t)nativeBoundary_26190(call, game, slot, 0, 0);
    if (slot_id == loadWord32(image + Storage::nativeData_2e9540))
        goto idle_delay;
    storeWord32(image + Storage::nativeData_2e9540, slot_id);
    if (!nativeBoundary_261b0(call, game, slot, 0, 0)) {
        uint64_t sample = random_range(call, loadFloat(image + Storage::nativeData_150338),
                                       loadFloat(image + Storage::nativeData_15033c));
        if ((uint8_t)smoothedProbabilityGate(call, (uintptr_t)(image + Storage::nativeData_2f7cc0),
                                             sample, loadWord64(image + Storage::nativeData_150340),
                                             0))
            goto idle_delay;
    }
    emit(call, 1, 1);
    if (image[Storage::inventory_randomizeCurrent] == 1) {
        uint64_t sample = random_range(call, loadFloat(image + Storage::nativeData_150350),
                                       loadFloat(image + Storage::nativeData_150354));
        uint8_t longer = (uint8_t)smoothedProbabilityGate(
            call, (uintptr_t)(image + Storage::nativeData_2f7ca8), sample,
            loadWord64(image + Storage::nativeData_150340), 0);
        uint32_t range = longer ? Storage::nativeData_150360 : Storage::nativeData_150358;
        sample = random_range(call, loadFloat(image + range), loadFloat(image + range + 4));
        float delay = floatFromWord(randomRangeSample(call, sample, 0, 0, 0));
        storeDouble(image + Storage::remainingClickTime,
                    add((double)delay, loadDouble(image + Storage::remainingClickTime)));
        return;
    }
    storeDouble(image + Storage::remainingClickTime,
                add(loadDouble(image + Storage::nativeData_150348),
                    loadDouble(image + Storage::remainingClickTime)));
    return;
idle_delay:
    storeDouble(image + Storage::remainingClickTime,
                add(loadDouble(image + (image[Storage::inventory_randomizeCurrent] != 0
                                            ? Storage::nativeData_150368
                                            : Storage::nativeData_150348)),
                    loadDouble(image + Storage::remainingClickTime)));
}
void advanceClickSequence(uint8_t *event, uint8_t *image, dependency call) {
    uint8_t *ctx = (uint8_t *)(uintptr_t)loadWord64(event + 8);
    uint64_t timer_obj = clientTimer(call, loadWord64(ctx), loadWord64(ctx + 0x18), 0, 0);
    double elapsed = loadDouble(event + 0x18);
    float speed = floatFromWord(nativeBoundary_259a0(call, loadWord64(ctx), timer_obj, 0, 0));
    double consumed = mul((double)speed, elapsed);
    double remaining = _mm_cvtsd_f64(_mm_sub_sd(
        _mm_set_sd(loadDouble(image + Storage::remainingClickTime)), _mm_set_sd(consumed)));
    remaining = _mm_cvtsd_f64(_mm_max_sd(
        _mm_load_sd((double *)(image + Storage::nativeData_150328)), _mm_set_sd(remaining)));
    storeDouble(image + Storage::remainingClickTime, remaining);
    if (!(0.0 >= remaining))
        return;
    uint8_t *keys = (uint8_t *)(uintptr_t)loadWord64(ctx + 0x30);
    uint8_t physical = keys[image[Storage::primaryButtonSelector] + 1],
            synthetic = (physical & 2) >> 1;
    double idle = loadDouble(image + Storage::nativeData_150330);
    uint64_t period = loadWord64(image + Storage::nativeData_150378);
    float random_high = loadFloat(image + Storage::nativeData_150384),
          one = loadFloat(image + Storage::nativeData_1503a0),
          divisor = loadFloat(image + Storage::nativeData_1503a8);
    for (;;) {
        if (ctx[0x40] == 0) {
            menu(ctx, image, call, physical, synthetic, idle);
            return;
        }
        if (!((physical | synthetic) & 1)) {
            cleanup(image, idle);
            return;
        }
        if (loadWord32(image + Storage::currentHitKind) == 1 &&
            image[Storage::allow_block_breakCurrent] != 0)
            goto reject;
        if (image[Storage::require_weaponCurrent] == 1 &&
            !(uint8_t)weaponEligibility(call, loadWord64(ctx), loadWord64(ctx + 0x28), 0, 0))
            goto reject;
        if (image[Storage::require_not_using_itemCurrent] == 1) {
            if ((uint8_t)entityUsingItem(call, loadWord64(ctx), loadWord64(ctx + 0x28), 0, 0))
                goto reject;
            if ((physical & synthetic) & 1)
                goto reject;
        } else if ((physical & synthetic) & 1) {
            physical = 1;
            goto release_cleanup;
        }
        if (physical & 1) {
            emit(call, image[Storage::primaryButtonSelector] ^ 1, 0);
            remaining = add(loadDouble(image + Storage::previousClickInterval),
                            loadDouble(image + Storage::remainingClickTime));
            storeDouble(image + Storage::remainingClickTime, remaining);
        } else {
            emit(call, image[Storage::primaryButtonSelector] ^ 1, 1);
            float rate = loadFloat(image + Storage::target_cpsCurrent);
            if (image[Storage::randomize_cpsCurrent] == 1) {
                uint64_t sample = random_range(call, loadFloat(image + Storage::nativeData_150370),
                                               loadFloat(image + Storage::nativeData_150374));
                float amplitude = smooth(call, image, Storage::nativeData_2f7ce8, sample, period);
                float low = loadFloat(image + Storage::nativeData_150380);
                sample = random_range(call, low, random_high);
                float slow = smooth(call, image, Storage::nativeData_2f7d08, sample,
                                    loadWord64(image + Storage::nativeData_150388));
                sample = random_range(call, low, random_high);
                float medium = smooth(call, image, Storage::nativeData_2f7d18, sample, period);
                sample = random_range(call, loadFloat(image + Storage::nativeData_150390),
                                      loadFloat(image + Storage::nativeData_150394));
                float fast = smooth(call, image, Storage::nativeData_2f7d28, sample,
                                    loadWord64(image + Storage::nativeData_150398));
                rate = multiplyFloatSse(
                    rate, addFloatSse(addFloatSse(addFloatSse(slow, one), medium), fast));
                float wave = floatFromWord(randomWaveSample(
                    call, (uintptr_t)(image + Storage::nativeData_2f7cf8), 0, 0, 0));
                rate = multiplyFloatSse(rate, addFloatSse(multiplyFloatSse(wave, amplitude), one));
            }
            float interval;
            uint32_t mode = loadWord32(image + Storage::patternCurrent);
            if (mode == 1 && image[Storage::quickClickPending] == 1) {
                uint32_t quick = 0x3c656042;
                interval = loadFloat(&quick);
                image[Storage::quickClickPending] = 0;
            } else {
                interval =
                    mode == 1 ? roundf(add(divide(loadDouble(image + Storage::nativeData_1503c0),
                                                  (double)rate),
                                           loadDouble(image + Storage::nativeData_1503c8)))
                              : divideFloatSse(loadFloat(image + Storage::nativeData_1503a4), rate);
                uint64_t angle =
                    entityRotation(call, loadWord64(ctx), loadWord64(ctx + 0x28), 0, 0);
                float turn = floatFromWord(rotationDistance(
                    call, angle, loadWord64(image + Storage::previousRotation), 0, 0));
                float adjustment = addFloatSse(divideFloatSse(turn, divisor), 0.0f);
                uint8_t *target = (uint8_t *)(uintptr_t)loadWord64(ctx + 0x38);
                if (!loadWord64(target + 8) ||
                    loadDouble(target + 0x10) > loadDouble(image + Storage::nativeData_1503b0))
                    adjustment = roundf(
                        add((double)adjustment, loadDouble(image + Storage::nativeData_1503b8)));
                uint8_t adjusted = (uint8_t)adjustInterval(image, call, &interval, adjustment);
                if (mode == 1 && !adjusted) {
                    uint64_t sample =
                        random_range(call, loadFloat(image + Storage::nativeData_1503d0),
                                     loadFloat(image + Storage::nativeData_1503d4));
                    uint8_t gate = (uint8_t)smoothedProbabilityGate(
                        call, (uintptr_t)(image + Storage::nativeData_2f7cd8), sample, period, 0);
                    image[Storage::quickClickPending] =
                        (uint8_t)probabilityGate(call, floatBits((float)gate), 0, 0, 0);
                }
            }
            remaining = add(loadDouble(image + Storage::remainingClickTime), (double)interval);
            storeDouble(image + Storage::remainingClickTime, remaining);
            storeDouble(image + Storage::previousClickInterval, (double)interval);
        }
        physical ^= 1;
        synthetic ^= 1;
        if (!(0.0 >= remaining))
            return;
        continue;
    reject:
        idle = 0.;
        if (!(synthetic & 1)) {
            cleanup(image, idle);
            return;
        }
    release_cleanup:
        physical = (uint8_t)(~physical) & 1;
        emit(call, image[Storage::primaryButtonSelector] ^ 1, physical);
        cleanup(image, 0.);
        return;
    }
}

// RVA 0x2d370. Native option index and label pointers are retained.
void formatStatus(char *output, uint8_t *image, dependency call) {
    uint32_t mode = loadWord32(image + 0x2e9680);
    call(0xab710, uintptr_t(output), 32, uintptr_t(image + 0x15059a),
         loadWord64(image + 0x2e9640 + uint64_t(mode) * 8));
}
} // namespace reconstruction::Auto_Clicker
// END SOURCE modules/Auto_Clicker/auto_clicker.cpp

// Convenient borrowed-state interface

namespace shareable {
class AutoClicker {
  public:
    static constexpr const char *kName = "Auto Clicker";
    static constexpr const char *kDescription = "Clicks for you when holding down left-click.";
    explicit AutoClicker(std::uint8_t *image) : image_(image) {}
    // Click pattern. Config key: pattern.
    ChoiceSetting &pattern() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2e9650);
    }
    // Option labels observed in the captured metadata.
    enum class PatternMode : std::uint32_t { Jitter = 0, Butterfly = 1 };
    // Target CPS. Config key: target_cps.
    NumberSetting &target_cps() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2e95e8);
    }
    // Randomize. Config key: randomize_cps.
    BooleanSetting &randomize_cps() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2e9620);
    }
    // Simulate exhaust. Config key: exhaust.
    BooleanSetting &exhaust() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2e9690);
    }
    // Allow breaking blocks. Config key: allow_block_break.
    BooleanSetting &allow_block_break() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2e9588);
    }
    // Click in inventory. Config key: allow_inventory.
    BooleanSetting &allow_inventory() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2e9548);
    }
    // Randomize speed. Config key: inventory_randomize.
    BooleanSetting &inventory_randomize() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2e9568);
    }
    // Holding weapon. Config key: require_weapon.
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2e95a8);
    }
    // Not using item. Config key: require_not_using_item.
    BooleanSetting &require_not_using_item() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2e95c8);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_auto_clicker_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_auto_clicker_settings(&context, image_, &dependencies);
    }
    void onTick(uint8_t *event, ::reconstruction::Auto_Clicker::dependency call) {
        ::reconstruction::Auto_Clicker::onTick(event, image_, call);
    }
    void updateHitKind(uint8_t *event, ::reconstruction::Auto_Clicker::dependency call) {
        ::reconstruction::Auto_Clicker::updateHitKind(event, image_, call);
    }
    void advanceClickSequence(uint8_t *event, ::reconstruction::Auto_Clicker::dependency call) {
        ::reconstruction::Auto_Clicker::advanceClickSequence(event, image_, call);
    }
    void formatStatus(char *output, ::reconstruction::Auto_Clicker::dependency call) {
        ::reconstruction::Auto_Clicker::formatStatus(output, image_, call);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
