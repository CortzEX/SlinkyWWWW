// Auto Rod

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Auto_Rod.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Auto_Rod.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Auto Rod: lib_win settings 0x444f0.
// UI 0x44420.
static constexpr UiStep ui_steps_Surface_Auto_Rod[] = {
    {UiControl::section, "Main", 0},          {UiControl::number, nullptr, 0x2f37f0},
    {UiControl::number, nullptr, 0x2f3798},   {UiControl::checkbox, nullptr, 0x2f37d0},
    {UiControl::checkbox, nullptr, 0x2f3778}, {UiControl::section, "Throwables", 0},
    {UiControl::checkbox, nullptr, 0x2f3758}, {UiControl::number, nullptr, 0x2f3828},
    {UiControl::section, "Main", 0},          {UiControl::checkbox, nullptr, 0x2f3738},
};
static constexpr SettingsStep settings_steps_Surface_Auto_Rod[] = {
    {SettingsControl::number, "retract_speed", 0x2f37f0},
    {SettingsControl::number, "delay", 0x2f3798},
    {SettingsControl::boolean, "randomize_delays", 0x2f37d0},
    {SettingsControl::boolean, "always_switch_to_weapon", 0x2f3778},
    {SettingsControl::boolean, "allow_throwables", 0x2f3758},
    {SettingsControl::number, "throw_speed", 0x2f3828},
    {SettingsControl::boolean, "require_not_mouse_over", 0x2f3738},
};
static constexpr ModuleSurface surface_Surface_Auto_Rod{
    ui_steps_Surface_Auto_Rod, std::size(ui_steps_Surface_Auto_Rod),
    settings_steps_Surface_Auto_Rod, std::size(settings_steps_Surface_Auto_Rod)};

extern "C" __declspec(dllexport) void
recovered_auto_rod_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                      const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Auto_Rod, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_auto_rod_settings(SettingsContext *context, std::uint8_t *image,
                            const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Auto_Rod, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Auto_Rod.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Auto_Rod/RodSequence.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_E72D32150455274ADF81
#define SLINKY_SHARE_E72D32150455274ADF81
// BEGIN SOURCE modules/Auto_Rod/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Auto_Rod {
namespace Storage {
inline constexpr std::uint32_t moduleDescriptor = 0x2f3520;
inline constexpr std::uint32_t nativeData_2f3540 = 0x2f3540;
inline constexpr std::uint32_t nativeData_2f3730 = 0x2f3730;
inline constexpr std::uint32_t require_not_mouse_overRecord = 0x2f3738;
inline constexpr std::uint32_t require_not_mouse_overCurrent = 0x2f3750;
inline constexpr std::uint32_t allow_throwablesRecord = 0x2f3758;
inline constexpr std::uint32_t allow_throwablesCurrent = 0x2f3770;
inline constexpr std::uint32_t always_switch_to_weaponRecord = 0x2f3778;
inline constexpr std::uint32_t always_switch_to_weaponCurrent = 0x2f3790;
inline constexpr std::uint32_t delayRecord = 0x2f3798;
inline constexpr std::uint32_t delayCurrent = 0x2f37c8;
inline constexpr std::uint32_t randomize_delaysRecord = 0x2f37d0;
inline constexpr std::uint32_t randomize_delaysCurrent = 0x2f37e8;
inline constexpr std::uint32_t retract_speedRecord = 0x2f37f0;
inline constexpr std::uint32_t retract_speedCurrent = 0x2f3820;
inline constexpr std::uint32_t throw_speedRecord = 0x2f3828;
inline constexpr std::uint32_t throw_speedCurrent = 0x2f3858;
inline constexpr std::uint32_t nativeData_304400 = 0x304400;
inline constexpr std::uint32_t nativeData_304404 = 0x304404;
inline constexpr std::uint32_t nativeData_304408 = 0x304408;
inline constexpr std::uint32_t nativeData_30440c = 0x30440c;
inline constexpr std::uint32_t nativeData_304410 = 0x304410;
inline constexpr std::uint32_t nativeData_304414 = 0x304414;
inline constexpr std::uint32_t nativeData_304415 = 0x304415;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &retract_speed() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::retract_speedRecord);
    }
    NumberSetting &delay() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::delayRecord);
    }
    BooleanSetting &randomize_delays() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::randomize_delaysRecord);
    }
    BooleanSetting &always_switch_to_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::always_switch_to_weaponRecord);
    }
    BooleanSetting &allow_throwables() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::allow_throwablesRecord);
    }
    NumberSetting &throw_speed() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::throw_speedRecord);
    }
    BooleanSetting &require_not_mouse_over() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_not_mouse_overRecord);
    }
};
} // namespace reconstruction::Auto_Rod
// END SOURCE modules/Auto_Rod/Settings.hpp

#endif // SLINKY_SHARE_E72D32150455274ADF81

#include <emmintrin.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
namespace reconstruction::Auto_Rod {
namespace NativeEntry {
inline constexpr uint32_t entityPosition = 0x23030;
inline constexpr uint32_t randomRangeSample = 0xa3e0;
inline constexpr uint32_t smoothedProbabilityGate = 0xaa30;
inline constexpr uint32_t smoothedRandomSample = 0xa510;
inline constexpr uint32_t randomRangeBits = 0xa050;
inline constexpr uint32_t clientOptions = 0x22cf0;
inline constexpr uint32_t currentHitResult = 0x22e10;
inline constexpr uint32_t entityInventory = 0x23f40;
inline constexpr uint32_t hitResultType = 0x24b50;
inline constexpr uint32_t useItemKey = 0x24f90;
inline constexpr uint32_t inventorySelectedSlot = 0x25a60;
inline constexpr uint32_t selectInventorySlot = 0x25a80;
inline constexpr uint32_t itemNumericType = 0x25c50;
inline constexpr uint32_t stackItem = 0x25d10;
inline constexpr uint32_t inventoryStackAt = 0x26140;
inline constexpr uint32_t scheduleModuleAction = 0x284f0;
inline constexpr uint32_t heldItem = 0x28a50;
inline constexpr uint32_t claimModuleAction = 0x2aa80;
inline constexpr uint32_t releaseModuleAction = 0x2aab0;
inline constexpr uint32_t bestWeaponSlot = 0x380c0;
} // namespace NativeEntry

/* Unknown game/runtime methods remain explicit RVA-keyed boundaries. */
struct rod_dispatch {
    native_binding::Context &native;
    uint64_t (*unresolved)(void *, uint32_t, uint64_t, uint64_t, uint64_t, uint64_t, uint64_t);
    uint64_t operator()(void *user, uint32_t rva, uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                        uint64_t stack) const {
        const uint64_t words[5] = {a, b, c, d, stack};
        native_binding::Value value;
        if (native_binding::resolve(native, rva, words, value))
            return value.bits;
        return unresolved(user, rva, a, b, c, d, stack);
    }
};

static uint64_t load64(const void *p, size_t off) {
    uint64_t v;
    memcpy(&v, (const uint8_t *)p + off, 8);
    return v;
}
static uint32_t load32(const void *p, size_t off) {
    uint32_t v;
    memcpy(&v, (const uint8_t *)p + off, 4);
    return v;
}
static uint8_t load8(const void *p, size_t off) {
    return *((const uint8_t *)p + off);
}
static void store32(void *p, size_t off, uint32_t v) {
    memcpy((uint8_t *)p + off, &v, 4);
}
static void store8(void *p, size_t off, uint8_t v) {
    *((uint8_t *)p + off) = v;
}
struct RodExecution {
    uint8_t *image;
    rod_dispatch dispatch;
    void *opaque;
    uint64_t image64(size_t off) {
        return load64(image, off);
    }
    uint32_t image32(size_t off) {
        return load32(image, off);
    }
    uint8_t image8(size_t off) {
        return load8(image, off);
    }
    void set32(size_t off, uint32_t v) {
        store32(image, off, v);
    }
    void set8(size_t off, uint8_t v) {
        store8(image, off, v);
    }
    uint64_t call5(uint32_t rva, uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                   uint64_t stack_arg) {
        return dispatch(opaque, rva, a, b, c, d, stack_arg);
    }
    uint64_t call0(uint32_t rva) {
        return call5(rva, 0, 0, 0, 0, 0);
    }
    float f32_from_bits(uint32_t bits) {
        float f;
        memcpy(&f, &bits, 4);
        return f;
    }
    float call_f32(uint32_t rva) {
        return f32_from_bits((uint32_t)call0(rva));
    }

    // RVA 0x445a0. Current values are read afresh, never used as startup
    // defaults.
    float sampleSwitchDelay() {
        float original = f32_from_bits(image32(Storage::delayCurrent));
        float result = original;
        if (image8(Storage::randomize_delaysCurrent) == 1) {
            uint64_t sample = call5(NativeEntry::randomRangeBits, 0, image32(0x154ab8), 0, 0, 0);
            float adjustment = f32_from_bits(
                uint32_t(call5(NativeEntry::smoothedRandomSample, uintptr_t(image + 0x304418),
                               sample, image64(0x154ac0), 0, 0)));
            __m128 difference = _mm_sub_ss(_mm_set_ss(original), _mm_set_ss(adjustment));
            // Runtime instruction MAXSS selects the source for NaN and equal zeros.
            result = _mm_cvtss_f32(_mm_max_ss(_mm_setzero_ps(), difference));
            sample =
                call5(NativeEntry::randomRangeBits, image32(0x154ac8), image32(0x154acc), 0, 0, 0);
            if (uint8_t(call5(NativeEntry::smoothedProbabilityGate, uintptr_t(image + 0x304428),
                              sample, image64(0x154ad0), 0, 0))) {
                sample = call5(NativeEntry::randomRangeBits, image32(0x154ab8), image32(0x154ad8),
                               0, 0, 0);
                result = result + f32_from_bits(uint32_t(
                                      call5(NativeEntry::randomRangeSample, sample, 0, 0, 0, 0)));
            }
        }
        return result;
    }
    // RVA 0x44860. Zero disables randomization; any other raw byte enables it.
    float sampleThrowDelay() {
        float result = f32_from_bits(image32(Storage::throw_speedCurrent));
        if (image8(Storage::randomize_delaysCurrent) == 0)
            return f32_from_bits(image32(0x154af8)) / result;
        uint64_t sample =
            call5(NativeEntry::randomRangeBits, image32(0x154afc), image32(0x154b00), 0, 0, 0);
        float factor = f32_from_bits(
            uint32_t(call5(NativeEntry::smoothedRandomSample, uintptr_t(image + 0x304438), sample,
                           image64(0x154b08), 0, 0)));
        result = f32_from_bits(image32(0x154af8)) / (result * factor);
        sample = call5(NativeEntry::randomRangeBits, image32(0x154b10), image32(0x154b14), 0, 0, 0);
        if (uint8_t(call5(NativeEntry::smoothedProbabilityGate, uintptr_t(image + 0x304448), sample,
                          image64(0x154b18), 0, 0))) {
            sample =
                call5(NativeEntry::randomRangeBits, image32(0x154b00), image32(0x154b20), 0, 0, 0);
            result =
                result +
                f32_from_bits(uint32_t(call5(NativeEntry::randomRangeSample, sample, 0, 0, 0, 0)));
        }
        return result;
    }

    uint64_t descriptor(void) {
        return (uint64_t)(uintptr_t)(image + Storage::moduleDescriptor);
    }

    uint64_t game_of(uint8_t *bridge) {
        return load64(bridge, 0);
    }

    uint64_t current_item(uint8_t *bridge) {
        uint64_t game = game_of(bridge);
        uint64_t slotptr = load64(bridge, 0x28);
        return call5(NativeEntry::entityInventory, game, slotptr, 0, 0, 0);
    }

    void select_slot(uint8_t *bridge, uint64_t item, uint32_t slot) {
        uint64_t game = game_of(bridge);
        call5(NativeEntry::selectInventorySlot, game, item, (uint32_t)slot, 0, 0);
    }

    void restore_selected(uint8_t *bridge) {
        if ((int32_t)image32(Storage::nativeData_2f3730) != -1) {
            uint64_t item = current_item(bridge);
            select_slot(bridge, item, image32(Storage::nativeData_2f3730));
            set32(Storage::nativeData_2f3730, UINT32_MAX);
        }
    }

    void unregister_module(void) {
        call5(NativeEntry::releaseModuleAction, descriptor(), 0, 0, 0, 0);
    }

    uint32_t item_kind(uint8_t *bridge, uint64_t item) {
        uint64_t game = game_of(bridge);
        uint64_t obj = call5(NativeEntry::stackItem, game, item, 0, 0, 0);
        if (!obj)
            return 0;
        game = game_of(bridge);
        return (uint32_t)call5(NativeEntry::itemNumericType, game, obj, 0, 0, 0);
    }

    // RVA 0x44660. Capture target first; optional position adjustment and each
    // vector copy follow the runtime-observed native order. Delay is ceil(float).
    int32_t computeRetractTicks(uint8_t *bridge) {
        uint64_t targetState = load64(bridge, 0x38);
        uint64_t target = load64(reinterpret_cast<void *>(uintptr_t(targetState)), 8);
        float delay;
        if (!target) {
            float distance = f32_from_bits(image32(0x154af0));
            float speed = f32_from_bits(image32(Storage::retract_speedCurrent));
            delay = _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(distance), _mm_set_ss(speed)));
        } else {
            double origin[3];
            call5(NativeEntry::entityPosition, uintptr_t(origin), game_of(bridge),
                  load64(bridge, 0x28), 0, 0);
            if (!uint8_t(call5(0x23020, game_of(bridge), 0, 0, 0, 0))) {
                double input[3], adjusted[3];
                memcpy(input, origin, 24);
                call5(0x9590, uintptr_t(adjusted), uintptr_t(input), 0, 0, 0);
                memcpy(origin, adjusted, 24);
            }
            double targetPosition[3];
            call5(0x24160, uintptr_t(targetPosition), game_of(bridge), target, 0, 0);
            uint64_t widthBits = image64(0x154ae0), heightBits = image64(0x154ae8);
            double width, height;
            memcpy(&width, &widthBits, 8);
            memcpy(&height, &heightBits, 8);
            double lower[3], upper[3];
            lower[0] = _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(targetPosition[0]), _mm_set_sd(width)));
            lower[1] = _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(targetPosition[1]), _mm_setzero_pd()));
            lower[2] = _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(targetPosition[2]), _mm_set_sd(width)));
            upper[0] = _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(targetPosition[0]), _mm_set_sd(width)));
            upper[1] = _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(targetPosition[1]), _mm_set_sd(height)));
            upper[2] = _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(targetPosition[2]), _mm_set_sd(width)));
            double box[6];
            memcpy(box, lower, 24);
            memcpy(box + 3, upper, 24);
            double boxCopy[6], pointCopy[3], closest[3];
            memcpy(boxCopy, box, 48);
            memcpy(pointCopy, origin, 24);
            call5(0x9880, uintptr_t(closest), uintptr_t(boxCopy), uintptr_t(pointCopy), 0, 0);
            double originCopy[3], closestCopy[3];
            memcpy(originCopy, origin, 24);
            memcpy(closestCopy, closest, 24);
            uint64_t distanceBits =
                call5(0x94f0, uintptr_t(originCopy), uintptr_t(closestCopy), 0, 0, 0);
            double distance;
            memcpy(&distance, &distanceBits, 8);
            double speed = double(f32_from_bits(image32(Storage::retract_speedCurrent)));
            double quotient = _mm_cvtsd_f64(_mm_div_sd(_mm_set_sd(distance), _mm_set_sd(speed)));
            delay = _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(quotient)));
        }
        uint32_t delayBits;
        memcpy(&delayBits, &delay, 4);
        float rounded = f32_from_bits(uint32_t(call5(0xb2920, delayBits, 0, 0, 0, 0)));
        return _mm_cvttss_si32(_mm_set_ss(rounded));
    }

    int32_t scan_rod_slot(uint8_t *bridge, uint64_t held, uint8_t *recognized) {
        int32_t candidate = -1;
        for (uint32_t i = 0; i < 9; ++i) {
            uint64_t game = game_of(bridge);
            uint64_t item = call5(NativeEntry::inventoryStackAt, game, held, i, 0, 0);
            if (!item)
                continue;
            uint32_t kind = item_kind(bridge, item);
            if (kind == 0x14c || kind == 0x158) {
                if (image8(Storage::allow_throwablesCurrent) == 1) {
                    *recognized = 0;
                    return (int32_t)i;
                }
            } else if (kind == 0x15a) {
                *recognized = 1;
                set8(Storage::nativeData_304414, 1);
                candidate = (int32_t)i;
                if (image8(Storage::allow_throwablesCurrent) == 0)
                    return candidate;
            }
        }
        return candidate;
    }

    void schedule_event(uint8_t *bridge) {
        uint64_t context = load64(bridge, 8);
        call5(NativeEntry::scheduleModuleAction, context, descriptor(), 0, 0, 0);
    }

    void auto_rod_impl_43d80(uint8_t *event, uint8_t *image) {
        uint8_t *bridge = (uint8_t *)(uintptr_t)load64(event, 8);
        if (load8(bridge, 0x40) != 1)
            return;

        if (image8(Storage::nativeData_304400) != 0) {
            restore_selected(bridge);
            unregister_module();
            uint64_t context = load64(bridge, 8);
            call5(NativeEntry::scheduleModuleAction, context, descriptor(), 0, 0, 0);
            set8(Storage::nativeData_304400, 0);
            return;
        }

        for (uint32_t iteration = 0; iteration < 3; ++iteration) {
            if (image8(Storage::require_not_mouse_overCurrent) == 1) {
                uint64_t game = game_of(bridge);
                uint64_t target =
                    call5(NativeEntry::currentHitResult, game, load64(bridge, 0x18), 0, 0, 0);
                if (target) {
                    game = game_of(bridge);
                    uint32_t result =
                        (uint32_t)call5(NativeEntry::hitResultType, game, target, 0, 0, 0);
                    if (result == 2) {
                        restore_selected(bridge);
                        unregister_module();
                        set32(Storage::nativeData_304404, 6);
                        goto finish_state6;
                    }
                }
            }

            if (image32(Storage::nativeData_304404) == 7) {
                restore_selected(bridge);
                unregister_module();
                set32(Storage::nativeData_304404, 0);
                return;
            }

            if (image32(Storage::nativeData_304410) != 0)
                set32(Storage::nativeData_304410, image32(Storage::nativeData_304410) - 1);
            float delay = f32_from_bits(image32(Storage::nativeData_30440c));
            if (delay > 0.0f) {
                delay = delay - 1.0f;
                uint32_t bits;
                memcpy(&bits, &delay, 4);
                set32(Storage::nativeData_30440c, bits);
                if (delay > 0.0f)
                    break;
            }

            uint64_t held = current_item(bridge);
            uint32_t held_slot =
                (uint32_t)call5(NativeEntry::inventorySelectedSlot, game_of(bridge), held, 0, 0, 0);
            uint32_t state = image32(Storage::nativeData_304404);
            if (state > 1 && held_slot != image32(Storage::nativeData_304408)) {
                unregister_module();
                set32(Storage::nativeData_304404, 6);
                goto finish_state6;
            }
            if (state > 5)
                break;

            if (state == 0) {
                set8(Storage::nativeData_304414, 0);
                uint8_t recognized = 0;
                int32_t selected = scan_rod_slot(bridge, held, &recognized);
                if (selected < 0) {
                    set32(Storage::nativeData_304404, 6);
                    goto finish_state6;
                }
                if ((uint8_t)call5(NativeEntry::claimModuleAction, descriptor(), 0, 0, 0, 0) == 0) {
                    set32(Storage::nativeData_304404, 6);
                    goto finish_state6;
                }
                set32(Storage::nativeData_2f3730, held_slot);
                set32(Storage::nativeData_304408, (uint32_t)selected);
                if (image8(Storage::always_switch_to_weaponCurrent) == 1) {
                    uint32_t better = (uint32_t)call5(NativeEntry::bestWeaponSlot,
                                                      (uint64_t)(uintptr_t)bridge, held, 0, 0, 0);
                    if (better != UINT32_MAX)
                        set32(Storage::nativeData_2f3730, better);
                    held_slot = image32(Storage::nativeData_2f3730);
                }
                set32(Storage::nativeData_304404,
                      image32(Storage::nativeData_304408) == held_slot ? 2 : 1);
                goto next_iteration;
            } else if (state == 1) {
                /* 0x43ec3 reloads the selected slot after the getter call. */
                select_slot(bridge, held, image32(Storage::nativeData_304408));
                set32(Storage::nativeData_304404, 2);
                set8(Storage::nativeData_304415, 0);
            } else if (state == 2) {
                set8(Storage::nativeData_304414, 0);
                uint8_t recognized = 0;
                int32_t selected = scan_rod_slot(bridge, held, &recognized);
                if (selected < 0) {
                    set32(Storage::nativeData_304404, 5);
                    return;
                }
                if ((uint32_t)selected == held_slot) {
                    uint64_t game = game_of(bridge);
                    uint64_t target =
                        call5(NativeEntry::clientOptions, game, load64(bridge, 0x18), 0, 0, 0);
                    game = game_of(bridge);
                    target = call5(NativeEntry::useItemKey, game, target, 0, 0, 0);
                    game = game_of(bridge);
                    call5(0x253e0, game, target, 1, 0, 0);
                    if (image8(Storage::nativeData_304414) == 1) {
                        set32(Storage::nativeData_304404, 3);
                        set32(Storage::nativeData_304410,
                              (uint32_t)uint32_t(computeRetractTicks(bridge)));
                        float delta = sampleSwitchDelay();
                        float previous = f32_from_bits(image32(Storage::nativeData_30440c));
                        float d = delta + previous;
                        uint32_t bits;
                        memcpy(&bits, &d, 4);
                        set32(Storage::nativeData_30440c, bits);
                        return;
                    }
                    if (image8(Storage::nativeData_2f3540) != 1) {
                        set32(Storage::nativeData_304404, 5);
                        float delta = sampleSwitchDelay();
                        float previous = f32_from_bits(image32(Storage::nativeData_30440c));
                        float d = delta + previous;
                        uint32_t bits;
                        memcpy(&bits, &d, 4);
                        set32(Storage::nativeData_30440c, bits);
                        return;
                    } else {
                        float delta = sampleThrowDelay();
                        float previous = f32_from_bits(image32(Storage::nativeData_30440c));
                        float d = delta + previous;
                        uint32_t bits;
                        memcpy(&bits, &d, 4);
                        set32(Storage::nativeData_30440c, bits);
                        return;
                    }
                } else {
                    set32(Storage::nativeData_304404, 1);
                    set32(Storage::nativeData_304408, (uint32_t)selected);
                    float delta = sampleSwitchDelay();
                    float previous = f32_from_bits(image32(Storage::nativeData_30440c));
                    float d = delta + previous;
                    uint32_t bits;
                    memcpy(&bits, &d, 4);
                    set32(Storage::nativeData_30440c, bits);
                    goto next_iteration;
                }
            } else if (state == 3) {
                if (image32(Storage::nativeData_304410) != 0)
                    break;
                set32(Storage::nativeData_304404,
                      ((image32(Storage::nativeData_2f3730) == image32(Storage::nativeData_304408))
                           ? 1u
                           : 0u) ^
                          5u);
            } else if (state == 4) {
                int32_t slot = (int32_t)image32(Storage::nativeData_2f3730);
                uint32_t wrapped = (uint32_t)slot + 1u;
                int32_t signed_wrapped;
                memcpy(&signed_wrapped, &wrapped, sizeof(wrapped));
                int32_t next = signed_wrapped % 9;
                select_slot(bridge, held, (uint32_t)next);
                set32(Storage::nativeData_304404, 5);
                return;
            } else if (state == 5) {
                set32(Storage::nativeData_304404, 6);
                restore_selected(bridge);
                unregister_module();
                float delta = sampleSwitchDelay();
                float previous = f32_from_bits(image32(Storage::nativeData_30440c));
                float d = delta + previous;
                uint32_t bits;
                memcpy(&bits, &d, 4);
                set32(Storage::nativeData_30440c, bits);
                goto finish_state6;
            }
            {
                float delta = sampleSwitchDelay();
                float previous = f32_from_bits(image32(Storage::nativeData_30440c));
                float d = delta + previous;
                uint32_t bits;
                memcpy(&bits, &d, 4);
                set32(Storage::nativeData_30440c, bits);
            }
        next_iteration:;
        }
        if (image32(Storage::nativeData_304404) == 6)
            goto finish_state6;
        return;

    finish_state6:
        if (image32(Storage::nativeData_304404) != 6)
            return;
        if (image8(Storage::nativeData_2f3540) == 1) {
            set32(Storage::nativeData_304404, 0);
            return;
        }
        schedule_event(bridge);
    }
};

void advanceRodSequence(uint8_t *event, uint8_t *image, rod_dispatch dispatch, void *opaque) {
    RodExecution execution{image, dispatch, opaque};
    execution.auto_rod_impl_43d80(event, image);
}

void onActionRequest(uint8_t *event, uint8_t *image) {
    if (load8(image, Storage::nativeData_304400) != 0)
        return;
    if (load64(event, 8) != (uint64_t)(uintptr_t)(image + Storage::moduleDescriptor))
        return;
    if (load8(image, Storage::nativeData_2f3540) == 1)
        store8(image, Storage::nativeData_304400, 1);
    else {
        uint32_t state = load32(image, Storage::nativeData_304404);
        if (state == 6)
            return;
        if (state == 3)
            store32(image, Storage::nativeData_304404, 7);
    }
    store8(event, 0x10, 1);
}

void onModuleStateChanged(uint8_t *event, uint8_t *image) {
    if (load64(event, 0x10) == (uint64_t)(uintptr_t)(image + Storage::moduleDescriptor) &&
        load8(event, 0x18) == 1)
        store32(image, Storage::nativeData_304404, 0);
}

void onInput(uint8_t *event, uint8_t *image, rod_dispatch dispatch, void *opaque) {
    if (load8(event, 0x10) != 0)
        return;
    uint8_t *bridge = (uint8_t *)(uintptr_t)load64(event, 8);
    uint64_t obj =
        dispatch(opaque, NativeEntry::heldItem, load64(bridge, 0), load64(bridge, 0x28), 0, 0, 0);
    if (!obj)
        return;
    uint32_t kind =
        (uint32_t)dispatch(opaque, NativeEntry::itemNumericType, load64(bridge, 0), obj, 0, 0, 0);
    if (kind == 0x15a) {
        if (load8(image, Storage::nativeData_304415) == 0)
            store8(image, Storage::nativeData_304415, 1);
        else
            store8(event, 0x11, 1);
    }
}

} // namespace reconstruction::Auto_Rod
// END SOURCE modules/Auto_Rod/RodSequence.cpp

// Convenient borrowed-state interface

namespace shareable {
class AutoRod {
  public:
    static constexpr const char *kName = "Auto Rod";
    static constexpr const char *kDescription = "Throws your fishing rod for you.";
    explicit AutoRod(std::uint8_t *image) : image_(image) {}
    // Retract speed. Config key: retract_speed.
    NumberSetting &retract_speed() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f37f0);
    }
    // Delay between actions. Config key: delay.
    NumberSetting &delay() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f3798);
    }
    // Randomize delays. Config key: randomize_delays.
    BooleanSetting &randomize_delays() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f37d0);
    }
    // Always switch back to weapon. Config key: always_switch_to_weapon.
    BooleanSetting &always_switch_to_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f3778);
    }
    // Allow using snowballs/eggs. Config key: allow_throwables.
    BooleanSetting &allow_throwables() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f3758);
    }
    // Throw speed. Config key: throw_speed.
    NumberSetting &throw_speed() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f3828);
    }
    // Not within melee range. Config key: require_not_mouse_over.
    BooleanSetting &require_not_mouse_over() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f3738);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_auto_rod_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_auto_rod_settings(&context, image_, &dependencies);
    }
    void advanceRodSequence(uint8_t *event, ::reconstruction::Auto_Rod::rod_dispatch dispatch,
                            void *opaque) {
        ::reconstruction::Auto_Rod::advanceRodSequence(event, image_, dispatch, opaque);
    }
    void onActionRequest(uint8_t *event) {
        ::reconstruction::Auto_Rod::onActionRequest(event, image_);
    }
    void onModuleStateChanged(uint8_t *event) {
        ::reconstruction::Auto_Rod::onModuleStateChanged(event, image_);
    }
    void onInput(uint8_t *event, ::reconstruction::Auto_Rod::rod_dispatch dispatch, void *opaque) {
        ::reconstruction::Auto_Rod::onInput(event, image_, dispatch, opaque);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
