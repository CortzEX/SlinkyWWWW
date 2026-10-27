// Auto Pot

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Auto_Pot.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Auto_Pot.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Auto Pot: lib_win settings 0x39670.
// UI 0x39600.
static constexpr UiStep ui_steps_Surface_Auto_Pot[] = {
    {UiControl::section, "Main", 0},          {UiControl::number, nullptr, 0x2ef358},
    {UiControl::checkbox, nullptr, 0x2ef390}, {UiControl::checkbox, nullptr, 0x2ef3b0},
    {UiControl::checkbox, nullptr, 0x2ef338},
};
static constexpr SettingsStep settings_steps_Surface_Auto_Pot[] = {
    {SettingsControl::number, "delay", 0x2ef358},
    {SettingsControl::boolean, "prevent_waste", 0x2ef390},
    {SettingsControl::boolean, "double_splash", 0x2ef3b0},
    {SettingsControl::boolean, "use_non_health", 0x2ef338},
};
static constexpr ModuleSurface surface_Surface_Auto_Pot{
    ui_steps_Surface_Auto_Pot, std::size(ui_steps_Surface_Auto_Pot),
    settings_steps_Surface_Auto_Pot, std::size(settings_steps_Surface_Auto_Pot)};

extern "C" __declspec(dllexport) void
recovered_auto_pot_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                      const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Auto_Pot, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_auto_pot_settings(SettingsContext *context, std::uint8_t *image,
                            const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Auto_Pot, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Auto_Pot.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Auto_Pot/auto_pot.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_F1C492C66827E0B71BB1
#define SLINKY_SHARE_F1C492C66827E0B71BB1
// BEGIN SOURCE modules/Auto_Pot/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Auto_Pot {
namespace Storage {
inline constexpr std::uint32_t nativeData_152c38 = 0x152c38;
inline constexpr std::uint32_t nativeData_152c3c = 0x152c3c;
inline constexpr std::uint32_t nativeData_152c58 = 0x152c58;
inline constexpr std::uint32_t nativeData_152c60 = 0x152c60;
inline constexpr std::uint32_t nativeData_152c68 = 0x152c68;
inline constexpr std::uint32_t nativeData_152c70 = 0x152c70;
inline constexpr std::uint32_t nativeData_152c78 = 0x152c78;
inline constexpr std::uint32_t nativeData_152c7c = 0x152c7c;
inline constexpr std::uint32_t nativeData_152c80 = 0x152c80;
inline constexpr std::uint32_t nativeData_152c88 = 0x152c88;
inline constexpr std::uint32_t moduleDescriptor = 0x2ef128;
inline constexpr std::uint32_t use_non_healthRecord = 0x2ef338;
inline constexpr std::uint32_t use_non_healthCurrent = 0x2ef350;
inline constexpr std::uint32_t delayRecord = 0x2ef358;
inline constexpr std::uint32_t delayCurrent = 0x2ef388;
inline constexpr std::uint32_t prevent_wasteRecord = 0x2ef390;
inline constexpr std::uint32_t prevent_wasteCurrent = 0x2ef3a8;
inline constexpr std::uint32_t double_splashRecord = 0x2ef3b0;
inline constexpr std::uint32_t double_splashCurrent = 0x2ef3c8;
inline constexpr std::uint32_t potionPhase = 0x2fc640;
inline constexpr std::uint32_t potionSlot = 0x2fc644;
inline constexpr std::uint32_t previousSlot = 0x2fc648;
inline constexpr std::uint32_t continueSelection = 0x2fc64c;
inline constexpr std::uint32_t remainingDelay = 0x2fc650;
inline constexpr std::uint32_t remainingUses = 0x2fc654;
inline constexpr std::uint32_t nativeData_2fc658 = 0x2fc658;
inline constexpr std::uint32_t nativeData_2fc668 = 0x2fc668;
inline constexpr std::uint32_t pendingActionRequests = 0x2fc678;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &delay() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::delayRecord);
    }
    BooleanSetting &prevent_waste() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::prevent_wasteRecord);
    }
    BooleanSetting &double_splash() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::double_splashRecord);
    }
    BooleanSetting &use_non_health() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::use_non_healthRecord);
    }
};
} // namespace reconstruction::Auto_Pot
// END SOURCE modules/Auto_Pot/Settings.hpp

#endif // SLINKY_SHARE_F1C492C66827E0B71BB1

#include <emmintrin.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
namespace reconstruction::Auto_Pot {
using dependency = native_binding::WordEndpoints;
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
// Native entry 0x22cf0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t clientOptions(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x22cf0, a0, a1, a2, a3);
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
// Native entry 0x24f90; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t useItemKey(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x24f90, a0, a1, a2, a3);
}
// Native entry 0x25380; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t pressKey(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x25380, a0, a1, a2, a3);
}
// Native entry 0x25a60; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t inventorySelectedSlot(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                      uint64_t a3) {
    return api(0x25a60, a0, a1, a2, a3);
}
// Native entry 0x25a80; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t selectInventorySlot(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                    uint64_t a3) {
    return api(0x25a80, a0, a1, a2, a3);
}
// Native entry 0x25c50; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t itemNumericType(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                uint64_t a3) {
    return api(0x25c50, a0, a1, a2, a3);
}
// Native entry 0x25d10; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t stackItem(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x25d10, a0, a1, a2, a3);
}
// Native entry 0x25dc0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t stackDamage(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x25dc0, a0, a1, a2, a3);
}
// Native entry 0x26140; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t inventoryStackAt(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                 uint64_t a3) {
    return api(0x26140, a0, a1, a2, a3);
}
// Native entry 0x284f0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t scheduleModuleAction(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x284f0, a0, a1, a2, a3);
}
// Native entry 0x2aa80; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t claimModuleAction(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                  uint64_t a3) {
    return api(0x2aa80, a0, a1, a2, a3);
}
// Native entry 0x2aab0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t releaseModuleAction(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                    uint64_t a3) {
    return api(0x2aab0, a0, a1, a2, a3);
}

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
static int32_t signed32(uint32_t v) {
    int32_t s;
    memcpy(&s, &v, 4);
    return s;
}
static float f32(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static void put32(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
static void putf(void *p, float v) {
    memcpy(p, &v, 4);
}
static float add(float a, float b) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float call_float(dependency call, uint32_t rva, uint64_t a, uint64_t b) {
    uint32_t v = (uint32_t)call(rva, a, b, 0, 0);
    return f32(&v);
}
static void schedule(uint8_t *ctx, uint8_t *image, dependency call) {
    scheduleModuleAction(call, u64(ctx + 8), (uintptr_t)(image + Storage::moduleDescriptor), 0, 0);
}
static uint32_t float_bits(float v) {
    return u32(&v);
}
float sampleSwitchDelay(uint8_t *image, dependency call) {
    float base = f32(image + Storage::delayCurrent);
    uint64_t random = randomRangeBits(call, 0, u32(image + Storage::nativeData_152c68), 0, 0);
    uint32_t offset =
        (uint32_t)smoothedRandomSample(call, (uintptr_t)(image + Storage::nativeData_2fc658),
                                       random, u64(image + Storage::nativeData_152c70), 0);
    __m128 adjusted = _mm_sub_ss(_mm_set_ss(base), _mm_set_ss(f32(&offset)));
    float delay = _mm_cvtss_f32(_mm_max_ss(_mm_setzero_ps(), adjusted));
    random = randomRangeBits(call, u32(image + Storage::nativeData_152c78),
                             u32(image + Storage::nativeData_152c7c), 0, 0);
    uint8_t extra =
        (uint8_t)smoothedProbabilityGate(call, (uintptr_t)(image + Storage::nativeData_2fc668),
                                         random, u64(image + Storage::nativeData_152c80), 0);
    if (extra) {
        random = randomRangeBits(call, u32(image + Storage::nativeData_152c68),
                                 u32(image + Storage::nativeData_152c88), 0, 0);
        uint32_t amount = (uint32_t)randomRangeSample(call, random, 0, 0, 0);
        delay = add(delay, f32(&amount));
    }
    return delay;
}
uint64_t recovered_auto_pot_delay_test(uint8_t *event, uint8_t *image, dependency call) {
    (void)event;
    return float_bits(sampleSwitchDelay(image, call));
}

void advancePotionSequence(uint8_t *event, uint8_t *image, dependency call) {
    uint8_t *ctx = (uint8_t *)(uintptr_t)u64(event + 8);
    float after_use = f32(image + Storage::nativeData_152c38);
    for (unsigned pass = 0; pass < 4; pass++) {
        float timer = f32(image + Storage::remainingDelay);
        if (timer > 0.0f) {
            putf(image + Storage::remainingDelay,
                 add(timer, f32(image + Storage::nativeData_152c3c)));
            break;
        }
        if (ctx[0x40] == 0) {
            image[Storage::continueSelection] = 0;
            put32(image + Storage::potionPhase, 4);
            schedule(ctx, image, call);
            return;
        }
        switch (u32(image + Storage::potionPhase)) {
        case 0: {
            uint64_t inventory = entityInventory(call, u64(ctx), u64(ctx + 0x28), 0, 0);
            uint32_t selected;
            for (selected = 0; selected < 9; selected++) {
                uint64_t stack = inventoryStackAt(call, u64(ctx), inventory, selected, 0);
                if (!stack)
                    continue;
                uint64_t item = stackItem(call, u64(ctx), stack, 0, 0);
                if (!item)
                    continue;
                uint32_t kind = (uint32_t)itemNumericType(call, u64(ctx), item, 0, 0);
                if (kind != 0x175)
                    continue;
                uint32_t damage = (uint32_t)stackDamage(call, u64(ctx), stack, 0, 0);
                if (!(damage & 0x4000))
                    continue;
                if ((damage & 15) != 5 && image[Storage::use_non_healthCurrent] == 0)
                    continue;
                break;
            }
            if (selected == 9) {
                put32(image + Storage::remainingUses, 0);
                uint32_t state = 4 - image[Storage::continueSelection];
                put32(image + Storage::potionPhase, state);
                image[Storage::continueSelection] = 0;
                if (state == 4)
                    schedule(ctx, image, call);
                return;
            }
            put32(image + Storage::potionSlot, selected);
            uint32_t previous;
            if (image[Storage::continueSelection] == 1)
                previous = u32(image + Storage::previousSlot);
            else {
                previous = (uint32_t)inventorySelectedSlot(call, u64(ctx), inventory, 0, 0);
                put32(image + Storage::previousSlot, previous);
                selected = u32(image + Storage::potionSlot);
            }
            image[Storage::continueSelection] = 0;
            put32(image + Storage::potionPhase, 1 + (selected == previous));
            break;
        }
        case 1: {
            uint8_t claimed = (uint8_t)claimModuleAction(
                call, (uintptr_t)(image + Storage::moduleDescriptor), 0, 0, 0);
            if (!claimed) {
                put32(image + Storage::potionPhase, 4);
                schedule(ctx, image, call);
                return;
            }
            uint64_t inventory = entityInventory(call, u64(ctx), u64(ctx + 0x28), 0, 0);
            selectInventorySlot(call, u64(ctx), inventory, u32(image + Storage::potionSlot), 0);
            put32(image + Storage::potionPhase, 2);
            float delay = sampleSwitchDelay(image, call);
            putf(image + Storage::remainingDelay, add(delay, f32(image + Storage::remainingDelay)));
            break;
        }
        case 2: {
            if ((uint8_t)entityUsingItem(call, u64(ctx), u64(ctx + 0x28), 0, 0))
                goto finish;
            uint64_t settings = clientOptions(call, u64(ctx), u64(ctx + 0x18), 0, 0);
            uint64_t use = useItemKey(call, u64(ctx), settings, 0, 0);
            pressKey(call, u64(ctx), use, 0, 0);
            put32(image + Storage::remainingUses, u32(image + Storage::remainingUses) - 1);
            put32(image + Storage::potionPhase, 3);
            if (u32(image + Storage::potionSlot) != u32(image + Storage::previousSlot)) {
                float delay = sampleSwitchDelay(image, call);
                delay = add(delay, after_use);
                putf(image + Storage::remainingDelay,
                     add(delay, f32(image + Storage::remainingDelay)));
            }
            break;
        }
        case 3:
            if (signed32(u32(image + Storage::remainingUses)) > 0) {
                image[Storage::continueSelection] = 1;
                put32(image + Storage::potionPhase, 0);
            } else {
                uint64_t inventory = entityInventory(call, u64(ctx), u64(ctx + 0x28), 0, 0);
                selectInventorySlot(call, u64(ctx), inventory, u32(image + Storage::previousSlot),
                                    0);
                put32(image + Storage::potionPhase, 4);
            }
            break;
        case 4:
            releaseModuleAction(call, (uintptr_t)(image + Storage::moduleDescriptor), 0, 0, 0);
            goto finish;
        default:
            abort(); /* Original jump table is defined only for states 0 through 4. */
        }
    }
finish:
    if (u32(image + Storage::potionPhase) == 4)
        schedule(ctx, image, call);
}

void onActionRequest(uint8_t *event, uint8_t *image, dependency call) {
    (void)call;
    uint32_t remaining = u32(image + Storage::pendingActionRequests);
    if (u64(event + 8) != (uintptr_t)(image + Storage::moduleDescriptor) ||
        u32(image + Storage::potionPhase) == 4 || signed32(remaining) <= 0)
        return;
    event[0x10] = 1;
    put32(image + Storage::remainingUses, u32(image + Storage::remainingUses) + 1);
    put32(image + Storage::pendingActionRequests, remaining - 1);
}

void onModuleStateChanged(uint8_t *event, uint8_t *image, dependency call) {
    if (u64(event + 0x10) != (uintptr_t)(image + Storage::moduleDescriptor))
        return;
    if (event[0x18] != 1) {
        put32(image + Storage::potionPhase, 0);
        put32(image + Storage::remainingUses, 0);
        return;
    }
    uint8_t *ctx = (uint8_t *)(uintptr_t)u64(event + 8);
    if (ctx[0x40] != 1)
        return;
    float health = call_float(call, 0x23a40, u64(ctx), u64(ctx + 0x28));
    float maximum = call_float(call, 0x23a80, u64(ctx), u64(ctx + 0x28));
    __m128 difference = _mm_sub_ss(_mm_set_ss(maximum), _mm_set_ss(health));
    __m128d scaled = _mm_cvtss_sd(_mm_setzero_pd(), difference);
    scaled = _mm_add_sd(scaled, _mm_load_sd((double *)(image + Storage::nativeData_152c58)));
    scaled = _mm_mul_sd(scaled, _mm_load_sd((double *)(image + Storage::nativeData_152c60)));
    uint32_t count = (uint32_t)_mm_cvttsd_si32(scaled);
    if (count == 0) {
        count = 1;
        if (image[Storage::prevent_wasteCurrent] == 1) {
            put32(image + Storage::potionPhase, 4);
            return;
        }
    }
    if (image[Storage::double_splashCurrent] == 1) {
        put32(image + Storage::remainingUses, count);
        put32(image + Storage::pendingActionRequests, 0);
    } else {
        put32(image + Storage::remainingUses, 1);
        put32(image + Storage::pendingActionRequests,
              image[Storage::prevent_wasteCurrent] != 0 ? count - 1 : 5);
    }
}

} // namespace reconstruction::Auto_Pot
// END SOURCE modules/Auto_Pot/auto_pot.cpp

// Convenient borrowed-state interface

namespace shareable {
class AutoPot {
  public:
    static constexpr const char *kName = "Auto Pot";
    static constexpr const char *kDescription = "Uses healing potions for you.";
    explicit AutoPot(std::uint8_t *image) : image_(image) {}
    // Delay between actions. Config key: delay.
    NumberSetting &delay() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ef358);
    }
    // Prevent wasting health. Config key: prevent_waste.
    BooleanSetting &prevent_waste() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ef390);
    }
    // Automatically do multiple splashes. Config key: double_splash.
    BooleanSetting &double_splash() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ef3b0);
    }
    // Use non-health potions. Config key: use_non_health.
    BooleanSetting &use_non_health() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ef338);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_auto_pot_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_auto_pot_settings(&context, image_, &dependencies);
    }
    float sampleSwitchDelay(::reconstruction::Auto_Pot::dependency call) {
        return ::reconstruction::Auto_Pot::sampleSwitchDelay(image_, call);
    }
    uint64_t delayTest(uint8_t *event, ::reconstruction::Auto_Pot::dependency call) {
        return ::reconstruction::Auto_Pot::recovered_auto_pot_delay_test(event, image_, call);
    }
    void advancePotionSequence(uint8_t *event, ::reconstruction::Auto_Pot::dependency call) {
        ::reconstruction::Auto_Pot::advancePotionSequence(event, image_, call);
    }
    void onActionRequest(uint8_t *event, ::reconstruction::Auto_Pot::dependency call) {
        ::reconstruction::Auto_Pot::onActionRequest(event, image_, call);
    }
    void onModuleStateChanged(uint8_t *event, ::reconstruction::Auto_Pot::dependency call) {
        ::reconstruction::Auto_Pot::onModuleStateChanged(event, image_, call);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
