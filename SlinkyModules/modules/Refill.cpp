// Refill

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Refill.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Refill.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Refill: lib_win settings 0x38c90.
static constexpr SettingsStep settings_steps_Surface_Refill[] = {
    {SettingsControl::boolean, "refill_potion", 0x2ef068},
    {SettingsControl::boolean, "refill_potion_non_health", 0x2ef088},
    {SettingsControl::boolean, "refill_soup", 0x2ef048},
    {SettingsControl::choice, "simulate_button", 0x2ef0e8},
    {SettingsControl::number, "delay_after_open", 0x2eefd8},
    {SettingsControl::number, "delay_before_close", 0x2eefa0},
    {SettingsControl::number, "speed", 0x2ef010},
    {SettingsControl::boolean, "smart_speed", 0x2ef0a8},
};
static constexpr ModuleSurface surface_Surface_Refill{nullptr, 0, settings_steps_Surface_Refill,
                                                      std::size(settings_steps_Surface_Refill)};

extern "C" __declspec(dllexport) void
recovered_refill_settings(SettingsContext *context, std::uint8_t *image,
                          const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Refill, context, image, *dependencies);
}

// Refill: lib_win runtime UI 0x38bc0.
extern "C" __declspec(dllexport) void
recovered_refill_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                    const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Items");
    dependencies->checkbox(layout, ui, image + 0x2ef068);
    if (image[0x2ef080] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2ef088);
    }
    dependencies->checkbox(layout, ui, image + 0x2ef048);
    dependencies->section(ui, layout, "Clicks");
    dependencies->choice(layout, ui, image + 0x2ef0e8);
    dependencies->number(layout, ui, image + 0x2eefd8);
    dependencies->number(layout, ui, image + 0x2eefa0);
    dependencies->number(layout, ui, image + 0x2ef010);
    dependencies->checkbox(layout, ui, image + 0x2ef0a8);
}
// END SOURCE native/verified/surfaces/Surface_Refill.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Refill/refill.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_40316CCE03B36E53764C
#define SLINKY_SHARE_40316CCE03B36E53764C
// BEGIN SOURCE modules/Refill/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Refill {
namespace Storage {
inline constexpr std::uint32_t nativeData_152a30 = 0x152a30;
inline constexpr std::uint32_t nativeData_152a34 = 0x152a34;
inline constexpr std::uint32_t nativeData_152a38 = 0x152a38;
inline constexpr std::uint32_t nativeData_152a40 = 0x152a40;
inline constexpr std::uint32_t nativeData_152a44 = 0x152a44;
inline constexpr std::uint32_t nativeData_152a48 = 0x152a48;
inline constexpr std::uint32_t nativeData_152a50 = 0x152a50;
inline constexpr std::uint32_t nativeData_152a58 = 0x152a58;
inline constexpr std::uint32_t nativeData_152a60 = 0x152a60;
inline constexpr std::uint32_t nativeData_152a64 = 0x152a64;
inline constexpr std::uint32_t nativeData_152a68 = 0x152a68;
inline constexpr std::uint32_t nativeData_152a6c = 0x152a6c;
inline constexpr std::uint32_t nativeData_152a70 = 0x152a70;
inline constexpr std::uint32_t nativeData_152a74 = 0x152a74;
inline constexpr std::uint32_t nativeData_152a78 = 0x152a78;
inline constexpr std::uint32_t nativeData_152a7c = 0x152a7c;
inline constexpr std::uint32_t moduleDescriptor = 0x2eed90;
inline constexpr std::uint32_t delay_before_closeRecord = 0x2eefa0;
inline constexpr std::uint32_t delay_before_closeCurrent = 0x2eefd0;
inline constexpr std::uint32_t delay_after_openRecord = 0x2eefd8;
inline constexpr std::uint32_t delay_after_openCurrent = 0x2ef008;
inline constexpr std::uint32_t speedRecord = 0x2ef010;
inline constexpr std::uint32_t speedCurrent = 0x2ef040;
inline constexpr std::uint32_t refill_soupRecord = 0x2ef048;
inline constexpr std::uint32_t refill_soupCurrent = 0x2ef060;
inline constexpr std::uint32_t refill_potionRecord = 0x2ef068;
inline constexpr std::uint32_t refill_potionCurrent = 0x2ef080;
inline constexpr std::uint32_t refill_potion_non_healthRecord = 0x2ef088;
inline constexpr std::uint32_t refill_potion_non_healthCurrent = 0x2ef0a0;
inline constexpr std::uint32_t smart_speedRecord = 0x2ef0a8;
inline constexpr std::uint32_t smart_speedCurrent = 0x2ef0c0;
inline constexpr std::uint32_t simulate_buttonRecord = 0x2ef0e8;
inline constexpr std::uint32_t simulate_buttonCurrent = 0x2ef118;
inline constexpr std::uint32_t refillPhase = 0x2fc580;
inline constexpr std::uint32_t nativeData_2fc588 = 0x2fc588;
inline constexpr std::uint32_t nativeData_2fc598 = 0x2fc598;
inline constexpr std::uint32_t nativeData_2fc5a8 = 0x2fc5a8;
inline constexpr std::uint32_t nativeData_2fc5b8 = 0x2fc5b8;
inline constexpr std::uint32_t nativeData_2fc5c8 = 0x2fc5c8;
inline constexpr std::uint32_t remainingDelay = 0x2fc5d0;
inline constexpr std::uint32_t candidateSlotMask = 0x2fc5e0;
inline constexpr std::uint32_t previousSelection = 0x2fc5fc;
inline constexpr std::uint32_t selectionAngle = 0x2fc600;
inline constexpr std::uint32_t selectedSlot = 0x2fc604;
inline constexpr std::uint32_t alternateAction = 0x2fc608;
inline constexpr std::uint32_t nativeData_2fc610 = 0x2fc610;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    BooleanSetting &refill_potion() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::refill_potionRecord);
    }
    BooleanSetting &refill_potion_non_health() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::refill_potion_non_healthRecord);
    }
    BooleanSetting &refill_soup() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::refill_soupRecord);
    }
    ChoiceSetting &simulate_button() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::simulate_buttonRecord);
    }
    NumberSetting &delay_after_open() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::delay_after_openRecord);
    }
    NumberSetting &delay_before_close() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::delay_before_closeRecord);
    }
    NumberSetting &speed() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::speedRecord);
    }
    BooleanSetting &smart_speed() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::smart_speedRecord);
    }
};
// Runtime-observed native labels for config key "simulate_button". Numeric values preserved.
enum class Simulate_buttonMode : std::uint32_t {
    Left = 0,
    Right = 1,
    Left___right = 2,
};
} // namespace reconstruction::Refill
// END SOURCE modules/Refill/Settings.hpp

#endif // SLINKY_SHARE_40316CCE03B36E53764C

#include <emmintrin.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
namespace reconstruction::Refill {
namespace NativeEntry {
inline constexpr uint32_t stackDamage = 0x25dc0;
inline constexpr uint32_t probabilityGate = 0xa460;
inline constexpr uint32_t gridDistance = 0x9ee0;
inline constexpr uint32_t gridBearing = 0x9f10;
inline constexpr uint32_t wrapYaw = 0xa210;
inline constexpr uint32_t randomRangeBits = 0xa050;
inline constexpr uint32_t randomRangeSample = 0xa3e0;
inline constexpr uint32_t smoothedRandomSample = 0xa510;
inline constexpr uint32_t smoothedProbabilityGate = 0xaa30;
inline constexpr uint32_t randomWaveSample = 0xab00;
inline constexpr uint32_t currentScreen = 0x22c90;
inline constexpr uint32_t clientOptions = 0x22cf0;
inline constexpr uint32_t entityInventory = 0x23f40;
inline constexpr uint32_t inventoryKey = 0x252c0;
inline constexpr uint32_t pressKey = 0x25380;
inline constexpr uint32_t inventoryScreenPredicate = 0x25b80;
inline constexpr uint32_t inventoryClick = 0x25be0;
inline constexpr uint32_t itemNumericType = 0x25c50;
inline constexpr uint32_t stackItem = 0x25d10;
inline constexpr uint32_t inventoryStackAt = 0x26140;
inline constexpr uint32_t scheduleModuleAction = 0x284f0;
} // namespace NativeEntry

struct refill_dispatch {
    native_binding::Context &native;
    void *user;
    uint64_t (*unresolved)(void *, uint32_t, const uint64_t *, const uint64_t *, uint64_t);
    uint64_t operator()(uint32_t rva, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint64_t x0,
                        uint64_t x1, uint64_t x2, uint64_t stack) const {
        uint64_t g[4] = {a, b, c, d}, x[4] = {x0, x1, x2, 0}, st[2] = {stack, 0};
        native_binding::Value value;
        if (native_binding::resolveFrame(native, rva, g, x, st, value))
            return value.bits;
        return unresolved(user, rva, g, x, stack);
    }
};
static uint64_t u64(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t u32(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static int32_t s32(uint32_t v) {
    int32_t s;
    memcpy(&s, &v, 4);
    return s;
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
static float from_fb(uint64_t b) {
    uint32_t low = (uint32_t)b;
    return f32(&low);
}
static void put32(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
static void putf(void *p, float v) {
    memcpy(p, &v, 4);
}
static double max_zero(double v) {
    return _mm_cvtsd_f64(_mm_max_sd(_mm_set_sd(v), _mm_setzero_pd()));
}
static uint64_t draw(refill_dispatch call, float lo, float hi) {
    return call(NativeEntry::randomRangeBits, 0, 0, 0, 0, floatBits(lo), floatBits(hi), 0, 0);
}
static float sample(refill_dispatch call, uint8_t *storage, uint64_t random, double scale) {
    return from_fb(call(NativeEntry::smoothedRandomSample, (uintptr_t)storage, random, 0, 0, 0, 0,
                        db(scale), 0));
}
static float random_float(refill_dispatch call, float lo, float hi) {
    return from_fb(call(NativeEntry::randomRangeSample, draw(call, lo, hi), 0, 0, 0, 0, 0, 0, 0));
}

// RVA 0x38d60. JNI method identity remains concrete metadata at game +0xcb0.
static void finishRefill(uint8_t *ctx, uint8_t *image, refill_dispatch call) {
    call(NativeEntry::scheduleModuleAction, u64(ctx + 8),
         uintptr_t(image + Storage::moduleDescriptor), 0, 0, 0, 0, 0, 0);
    uint64_t game = u64(ctx);
    uint64_t screen = call(NativeEntry::currentScreen, game, u64(ctx + 0x18), 0, 0, 0, 0, 0, 0);
    if (screen) {
        call(0x25af0, game, screen, 0, 1, 0, 0, 0, 0);
    }
}
// RVA 0x38dc0. Mask 0 = empty, 1 = unavailable, 2 = requested refill item.
static void classifyRefillSlots(uint8_t *ctx, uint8_t *image, refill_dispatch call) {
    uint64_t inventory =
        call(NativeEntry::entityInventory, u64(ctx), u64(ctx + 0x28), 0, 0, 0, 0, 0, 0);
    for (uint32_t slot = 0; slot != 27; ++slot) {
        uint8_t mark = 0;
        uint64_t stack =
            call(NativeEntry::inventoryStackAt, u64(ctx), inventory, slot + 9, 0, 0, 0, 0, 0);
        if (stack) {
            uint64_t game = u64(ctx);
            uint64_t item = call(NativeEntry::stackItem, game, stack, 0, 0, 0, 0, 0, 0);
            if (item) {
                uint32_t type =
                    uint32_t(call(NativeEntry::itemNumericType, game, item, 0, 0, 0, 0, 0, 0));
                if (type) {
                    mark = 1;
                    if (type == 0x175) {
                        if (image[Storage::refill_potionCurrent] == 1) {
                            uint32_t damage = uint32_t(
                                call(NativeEntry::stackDamage, game, stack, 0, 0, 0, 0, 0, 0));
                            if (damage & 0x4000)
                                mark =
                                    (damage & 15) == 5
                                        ? 2
                                        : uint8_t(image[Storage::refill_potion_non_healthCurrent] +
                                                  1);
                        }
                    } else if (type == 0x11a)
                        mark = uint8_t(image[Storage::refill_soupCurrent] + 1);
                }
            }
        }
        image[Storage::candidateSlotMask + slot] = mark;
    }
}
static uint64_t gridPoint(float x, float y) {
    return uint64_t(floatBits(x)) | (uint64_t(floatBits(y)) << 32);
}
// RVA 0x38ed0. MINSS and CMOVBE are preserved for NaNs, signed zeros and ties.
static uint32_t chooseRefillSlot(int32_t previous, float angle, float *output, uint8_t *image,
                                 refill_dispatch call) {
    uint64_t origin = gridPoint(float(previous % 9), float(previous / 9));
    float initial = f32(image + 0x152aa0), angleWeight = f32(image + 0x152aa4),
          distanceWeight = f32(image + 0x152ac0);
    float bestScore = initial, secondScore = initial, emptyScore = initial;
    float bestBearing = 0, secondBearing = 0, emptyBearing = 0;
    uint32_t best = UINT32_MAX, second = UINT32_MAX, empty = UINT32_MAX;
    for (uint32_t slot = 0; slot != 27; ++slot) {
        uint8_t mark = image[Storage::candidateSlotMask + slot];
        if (mark != 2 && (mark != 0 || uint8_t(call(NativeEntry::probabilityGate, 0, 0, 0, 0,
                                                    floatBits(angleWeight), 0, 0, 0))))
            continue;
        uint64_t point = gridPoint(float(int8_t(uint8_t(slot) - uint8_t(slot) / 9 * 9)),
                                   float(uint8_t(slot) / 9));
        float distance = from_fb(call(NativeEntry::gridDistance, origin, point, 0, 0, 0, 0, 0, 0));
        float bearing = from_fb(call(NativeEntry::gridBearing, origin, point, 0, 0, 0, 0, 0, 0));
        float difference = _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(bearing), _mm_set_ss(angle)));
        uint32_t wrapped =
            uint32_t(call(NativeEntry::wrapYaw, 0, 0, 0, 0, floatBits(difference), 0, 0, 0));
        uint32_t absoluteBits = wrapped & u32(image + 0x152ab0);
        float absolute = f32(&absoluteBits);
        float angular = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(absolute), _mm_set_ss(angleWeight)));
        float weightedDistance =
            _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(distance), _mm_set_ss(distanceWeight)));
        float score = _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(weightedDistance), _mm_set_ss(angular)));
        if (mark == 0) {
            if (!(emptyScore < score))
                emptyBearing = bearing;
            if (!(score > emptyScore))
                empty = slot;
            emptyScore = _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(emptyScore), _mm_set_ss(score)));
        } else {
            bool replaces = !(score > bestScore);
            if (replaces) {
                secondScore = bestScore;
                second = best;
            }
            if (!(bestScore < score))
                secondBearing = bestBearing;
            if (replaces)
                bestBearing = bearing;
            if (replaces)
                best = slot;
            bestScore = _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(bestScore), _mm_set_ss(score)));
        }
    }
    auto gate = [&](uint32_t state, uint32_t period) {
        uint64_t random = draw(call, f32(image + 0x152ac4), f32(image + 0x152ac8));
        return uint8_t(call(NativeEntry::smoothedProbabilityGate, uintptr_t(image + state), random,
                            0, 0, 0, 0, u64(image + period), 0));
    };
    uint32_t selected = best;
    float score = bestScore, bearing = bestBearing;
    if (bestScore > emptyScore && gate(0x2fc620, 0x152ad0)) {
        selected = empty;
        score = emptyScore;
        bearing = emptyBearing;
    } else if (second != UINT32_MAX &&
               (double(bestScore) * f64(image + 0x152ad8) > double(secondScore)) &&
               gate(0x2fc630, 0x152ae0)) {
        selected = second;
        score = secondScore;
        bearing = secondBearing;
    }
    putf(output, score);
    putf(image + Storage::selectionAngle, bearing);
    return selected;
}

void onModuleStateChanged(uint8_t *event, uint8_t *image) {
    if (u64(event + 0x10) == (uintptr_t)(image + Storage::moduleDescriptor) && event[0x18] == 1)
        put32(image + Storage::refillPhase, 0);
}

/* Only original table states 0..4 have translated handlers. The original
   performs an unchecked indirect jump for other values; this adapter traps. */
void advanceRefillSequence(uint8_t *event, uint8_t *image, uint32_t incoming_r13,
                           refill_dispatch call) {
    uint8_t *ctx = (uint8_t *)(uintptr_t)u64(event + 8);
    uint64_t current =
        call(NativeEntry::currentScreen, u64(ctx), u64(ctx + 0x18), 0, 0, 0, 0, 0, 0);
    {
        if (u32(image + Storage::refillPhase) != 0) {
            if (!current)
                goto cleanup;
            if (!(uint8_t)call(NativeEntry::inventoryScreenPredicate, u64(ctx), current, 0, 0, 0, 0,
                               0, 0))
                goto cleanup;
            event[0x10] = 1;
        }
        float delay = f32(image + Storage::remainingDelay);
        if (delay > 0.0f) {
            putf(image + Storage::remainingDelay, delay + f32(image + Storage::nativeData_152a7c));
            return;
        }
        if (!(delay <= 0.0f))
            return;

        uint32_t state = u32(image + Storage::refillPhase);
        float index_limit = f32(image + Storage::nativeData_152a74),
              angle_limit = f32(image + Storage::nativeData_152a78);
        float sample_limit = f32(image + Storage::nativeData_152a70);
        double sample_scale = f64(image + Storage::nativeData_152a48),
               factor_base = f64(image + Storage::nativeData_152a58);
        float chance_low = f32(image + Storage::nativeData_152a60),
              chance_high = f32(image + Storage::nativeData_152a64);
        for (;;) {
            if (state == 4)
                goto cleanup;
            uint64_t target = u64(ctx + 0x28);
            if (!target)
                goto schedule_close;
            uint64_t inventory =
                call(NativeEntry::entityInventory, u64(ctx), target, 0, 0, 0, 0, 0, 0);
            uint32_t index;
            for (index = 0; index < 9; ++index) {
                uint64_t stack =
                    call(NativeEntry::inventoryStackAt, u64(ctx), inventory, index, 0, 0, 0, 0, 0);
                if (!stack)
                    break;
                uint64_t item = call(NativeEntry::stackItem, u64(ctx), stack, 0, 0, 0, 0, 0, 0);
                if (!item)
                    break;
                if (!(uint32_t)call(NativeEntry::itemNumericType, u64(ctx), item, 0, 0, 0, 0, 0, 0))
                    break;
            }
            if (index == 9)
                goto schedule_close;
            state = u32(image + Storage::refillPhase);
            switch (state) {
            case 0: {
                put32(image + Storage::refillPhase, 1);
                if (current)
                    return;
                classifyRefillSlots(ctx, image, call);
                float output;
                uint32_t selected =
                    chooseRefillSlot(s32(u32(image + Storage::previousSelection)),
                                     f32(image + Storage::selectionAngle), &output, image, call);
                if (selected == UINT32_MAX) {
                    finishRefill(ctx, image, call);
                    return;
                }
                uint64_t settings =
                    call(NativeEntry::clientOptions, u64(ctx), u64(ctx + 0x18), 0, 0, 0, 0, 0, 0);
                uint64_t key =
                    call(NativeEntry::inventoryKey, u64(ctx), settings, 0, 0, 0, 0, 0, 0);
                call(NativeEntry::pressKey, u64(ctx), key, 0, 0, 0, 0, 0, 0);
                return;
            }
            case 1: {
                float random_index = random_float(call, 0.0f, index_limit);
                put32(image + Storage::previousSelection,
                      (uint32_t)_mm_cvttss_si32(_mm_set_ss(random_index)));
                putf(image + Storage::selectionAngle, random_float(call, 0.0f, angle_limit));
                put32(image + Storage::refillPhase, 2);
                double setting = (double)f32(image + Storage::delay_after_openCurrent);
                uint64_t random = draw(call, 0.0f, sample_limit);
                double sampled =
                    (double)sample(call, image + Storage::nativeData_2fc588, random, sample_scale);
                double extra = max_zero(setting - sampled);
                delay = (float)((double)f32(image + Storage::remainingDelay) + extra);
                putf(image + Storage::remainingDelay, delay);
                state = u32(image + Storage::refillPhase);
                break;
            }
            case 2: {
                float output;
                uint32_t selected =
                    chooseRefillSlot(s32(u32(image + Storage::previousSelection)),
                                     f32(image + Storage::selectionAngle), &output, image, call);
                put32(image + Storage::selectedSlot, selected);
                if (selected == UINT32_MAX) {
                    double setting = (double)f32(image + Storage::delay_before_closeCurrent);
                    uint64_t random = draw(call, 0.0f, f32(image + Storage::nativeData_152a70));
                    double sampled =
                        (double)sample(call, image + Storage::nativeData_2fc598, random,
                                       f64(image + Storage::nativeData_152a48));
                    delay = (float)((double)f32(image + Storage::remainingDelay) +
                                    max_zero(setting - sampled));
                    putf(image + Storage::remainingDelay, delay);
                    put32(image + Storage::refillPhase, 4);
                    return;
                }
                float speed = f32(image + Storage::speedCurrent);
                uint64_t random = draw(call, f32(image + Storage::nativeData_152a40),
                                       f32(image + Storage::nativeData_152a44));
                float multiplier =
                    sample(call, image + Storage::nativeData_2fc5a8, random, sample_scale) * speed;
                double wave = (double)from_fb(call(NativeEntry::randomWaveSample,
                                                   (uintptr_t)(image + Storage::nativeData_2fc5c8),
                                                   0, 0, 0, 0, 0, 0, 0));
                wave = wave * f64(image + Storage::nativeData_152a50);
                wave = wave + factor_base;
                multiplier = (float)((double)multiplier * wave);
                random = draw(call, chance_low, chance_high);
                uint8_t gate = (uint8_t)call(NativeEntry::smoothedProbabilityGate,
                                             (uintptr_t)(image + Storage::nativeData_2fc5b8),
                                             random, 0, 0, 0, 0, db(sample_scale), 0);
                if (gate)
                    multiplier =
                        multiplier / random_float(call, f32(image + Storage::nativeData_152a68),
                                                  f32(image + Storage::nativeData_152a6c));
                float distance = image[Storage::smart_speedCurrent] != 0
                                     ? output
                                     : f32(image + Storage::nativeData_152a34);
                delay = distance / multiplier;
                delay = delay + f32(image + Storage::remainingDelay);
                putf(image + Storage::remainingDelay, delay);
                put32(image + Storage::previousSelection, u32(image + Storage::selectedSlot));
                put32(image + Storage::refillPhase, 3);
                state = 3;
                break;
            }
            case 3: {
                uint32_t action = u32(image + Storage::simulate_buttonCurrent);
                if (action >= 2) {
                    if (action == 2) {
                        action = u32(image + Storage::alternateAction);
                        uint64_t random = draw(call, f32(image + Storage::nativeData_152a30),
                                               f32(image + Storage::nativeData_152a34));
                        uint8_t gate =
                            (uint8_t)call(NativeEntry::smoothedProbabilityGate,
                                          (uintptr_t)(image + Storage::nativeData_2fc610), random,
                                          0, 0, 0, 0, u64(image + Storage::nativeData_152a38), 0);
                        if (gate)
                            put32(image + Storage::alternateAction,
                                  u32(image + Storage::alternateAction) == 0);
                    } else
                        action = incoming_r13;
                }
                call(NativeEntry::inventoryClick, u64(ctx), current,
                     u32(image + Storage::selectedSlot) + 9u, action, 0, 0, 0, 1);
                int32_t selected = s32(u32(image + Storage::selectedSlot));
                *(image + Storage::candidateSlotMask + (intptr_t)selected) = 0;
                put32(image + Storage::refillPhase, 2);
                state = 2;
                delay = f32(image + Storage::remainingDelay);
                incoming_r13 = action;
                break;
            }
            case 4:
                goto cleanup;
            default:
                abort();
            }
            if (!(delay <= 0.0f))
                return;
        }
    schedule_close: {
        double setting = (double)f32(image + Storage::delay_before_closeCurrent);
        uint64_t random = draw(call, 0.0f, f32(image + Storage::nativeData_152a70));
        double sampled = (double)sample(call, image + Storage::nativeData_2fc598, random,
                                        f64(image + Storage::nativeData_152a48));
        delay = (float)((double)f32(image + Storage::remainingDelay) + max_zero(setting - sampled));
        putf(image + Storage::remainingDelay, delay);
        put32(image + Storage::refillPhase, 4);
        if (!(delay <= 0.0f))
            return;
    }
    }
cleanup:
    finishRefill(ctx, image, call);
}

} // namespace reconstruction::Refill
// END SOURCE modules/Refill/refill.cpp

// Convenient borrowed-state interface

namespace shareable {
class Refill {
  public:
    static constexpr const char *kName = "Refill";
    static constexpr const char *kDescription = "Automatically moves items into your hotbar.";
    explicit Refill(std::uint8_t *image) : image_(image) {}
    // Potions. Config key: refill_potion.
    BooleanSetting &refill_potion() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ef068);
    }
    // Allow non-health potions. Config key: refill_potion_non_health.
    BooleanSetting &refill_potion_non_health() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ef088);
    }
    // Soups. Config key: refill_soup.
    BooleanSetting &refill_soup() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ef048);
    }
    // Simulate button. Config key: simulate_button.
    ChoiceSetting &simulate_button() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2ef0e8);
    }
    // Option labels observed in the captured metadata.
    enum class SimulateButtonMode : std::uint32_t { Left = 0, Right = 1, LeftRight = 2 };
    // Delay after open. Config key: delay_after_open.
    NumberSetting &delay_after_open() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2eefd8);
    }
    // Delay before close. Config key: delay_before_close.
    NumberSetting &delay_before_close() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2eefa0);
    }
    // Speed. Config key: speed.
    NumberSetting &speed() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ef010);
    }
    // Smart speed. Config key: smart_speed.
    BooleanSetting &smart_speed() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ef0a8);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_refill_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_refill_settings(&context, image_, &dependencies);
    }
    void onModuleStateChanged(uint8_t *event) {
        ::reconstruction::Refill::onModuleStateChanged(event, image_);
    }
    void advanceRefillSequence(uint8_t *event, uint32_t incoming_r13,
                               ::reconstruction::Refill::refill_dispatch call) {
        ::reconstruction::Refill::advanceRefillSequence(event, image_, incoming_r13, call);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
