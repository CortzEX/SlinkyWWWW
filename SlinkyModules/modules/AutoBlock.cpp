// Auto Block

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Auto_Block.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Auto_Block.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Auto Block: lib_win settings 0x31cf0.
static constexpr SettingsStep settings_steps_Surface_Auto_Block[] = {
    {SettingsControl::number, "range", 0x2eb388},
    {SettingsControl::number, "max_hurt_time", 0x2eb2b0},
    {SettingsControl::number, "max_hold_time", 0x2eb208},
    {SettingsControl::boolean, "fake_block_animation", 0x2eb348},
    {SettingsControl::boolean, "fake_block_animation_require_target", 0x2eb368},
    {SettingsControl::number, "lag_chance", 0x2eb240},
    {SettingsControl::number, "lag_duration", 0x2eb278},
    {SettingsControl::boolean, "lag_flush_attack", 0x2eb3c0},
    {SettingsControl::boolean, "lag_reblock", 0x2eb3e0},
    {SettingsControl::boolean, "require_left_mouse_pressed", 0x2eb2e8},
    {SettingsControl::boolean, "require_right_mouse_pressed", 0x2eb308},
    {SettingsControl::boolean, "require_damage", 0x2eb328},
};
static constexpr ModuleSurface surface_Surface_Auto_Block{
    nullptr, 0, settings_steps_Surface_Auto_Block, std::size(settings_steps_Surface_Auto_Block)};

extern "C" __declspec(dllexport) void
recovered_auto_block_settings(SettingsContext *context, std::uint8_t *image,
                              const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Auto_Block, context, image, *dependencies);
}

// Auto Block: lib_win runtime UI 0x31bb0.
extern "C" __declspec(dllexport) void
recovered_auto_block_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                        const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2eb388);
    dependencies->number(layout, ui, image + 0x2eb2b0);
    dependencies->number(layout, ui, image + 0x2eb208);
    dependencies->section(ui, layout, "Force block animation");
    dependencies->checkbox(layout, ui, image + 0x2eb348);
    if (image[0x2eb360] == 1) {
        dependencies->checkbox(layout, ui, image + 0x2eb368);
    }
    dependencies->section(ui, layout, "Lag");
    dependencies->number(layout, ui, image + 0x2eb240);
    dependencies->number(layout, ui, image + 0x2eb278);
    dependencies->checkbox(layout, ui, image + 0x2eb3c0);
    dependencies->checkbox(layout, ui, image + 0x2eb3e0);
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2eb2e8);
    dependencies->checkbox(layout, ui, image + 0x2eb308);
    dependencies->checkbox(layout, ui, image + 0x2eb328);
}
// END SOURCE native/verified/surfaces/Surface_Auto_Block.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Auto_Block/BlockingState.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_8A56E7354D15C4624391
#define SLINKY_SHARE_8A56E7354D15C4624391
// BEGIN SOURCE modules/Auto_Block/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Auto_Block {
namespace Storage {
inline constexpr std::uint32_t moduleDescriptor = 0x2eaff8;
inline constexpr std::uint32_t max_hold_timeRecord = 0x2eb208;
inline constexpr std::uint32_t max_hold_timeCurrent = 0x2eb238;
inline constexpr std::uint32_t lag_chanceRecord = 0x2eb240;
inline constexpr std::uint32_t lag_chanceCurrent = 0x2eb270;
inline constexpr std::uint32_t lag_durationRecord = 0x2eb278;
inline constexpr std::uint32_t lag_durationCurrent = 0x2eb2a8;
inline constexpr std::uint32_t max_hurt_timeRecord = 0x2eb2b0;
inline constexpr std::uint32_t max_hurt_timeCurrent = 0x2eb2e0;
inline constexpr std::uint32_t require_left_mouse_pressedRecord = 0x2eb2e8;
inline constexpr std::uint32_t require_left_mouse_pressedCurrent = 0x2eb300;
inline constexpr std::uint32_t require_right_mouse_pressedRecord = 0x2eb308;
inline constexpr std::uint32_t require_right_mouse_pressedCurrent = 0x2eb320;
inline constexpr std::uint32_t require_damageRecord = 0x2eb328;
inline constexpr std::uint32_t require_damageCurrent = 0x2eb340;
inline constexpr std::uint32_t fake_block_animationRecord = 0x2eb348;
inline constexpr std::uint32_t fake_block_animationCurrent = 0x2eb360;
inline constexpr std::uint32_t fake_block_animation_require_targetRecord = 0x2eb368;
inline constexpr std::uint32_t fake_block_animation_require_targetCurrent = 0x2eb380;
inline constexpr std::uint32_t rangeRecord = 0x2eb388;
inline constexpr std::uint32_t rangeCurrent = 0x2eb3b8;
inline constexpr std::uint32_t lag_flush_attackRecord = 0x2eb3c0;
inline constexpr std::uint32_t lag_flush_attackCurrent = 0x2eb3d8;
inline constexpr std::uint32_t lag_reblockRecord = 0x2eb3e0;
inline constexpr std::uint32_t lag_reblockCurrent = 0x2eb3f8;
inline constexpr std::uint32_t nativeData_2f9e00 = 0x2f9e00;
inline constexpr std::uint32_t nativeData_2f9e04 = 0x2f9e04;
inline constexpr std::uint32_t nativeData_2f9e08 = 0x2f9e08;
inline constexpr std::uint32_t nativeData_2f9e0c = 0x2f9e0c;
inline constexpr std::uint32_t nativeData_2f9e10 = 0x2f9e10;
inline constexpr std::uint32_t nativeData_2f9e11 = 0x2f9e11;
inline constexpr std::uint32_t nativeData_2f9e12 = 0x2f9e12;
inline constexpr std::uint32_t nativeData_2f9e14 = 0x2f9e14;
inline constexpr std::uint32_t nativeData_2f9e18 = 0x2f9e18;
inline constexpr std::uint32_t nativeData_2f9e19 = 0x2f9e19;
inline constexpr std::uint32_t nativeData_2f9e1c = 0x2f9e1c;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &range() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::rangeRecord);
    }
    NumberSetting &max_hurt_time() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::max_hurt_timeRecord);
    }
    NumberSetting &max_hold_time() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::max_hold_timeRecord);
    }
    BooleanSetting &fake_block_animation() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::fake_block_animationRecord);
    }
    BooleanSetting &fake_block_animation_require_target() const {
        return *reinterpret_cast<BooleanSetting *>(
            image + Storage::fake_block_animation_require_targetRecord);
    }
    NumberSetting &lag_chance() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::lag_chanceRecord);
    }
    NumberSetting &lag_duration() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::lag_durationRecord);
    }
    BooleanSetting &lag_flush_attack() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::lag_flush_attackRecord);
    }
    BooleanSetting &lag_reblock() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::lag_reblockRecord);
    }
    BooleanSetting &require_left_mouse_pressed() const {
        return *reinterpret_cast<BooleanSetting *>(image +
                                                   Storage::require_left_mouse_pressedRecord);
    }
    BooleanSetting &require_right_mouse_pressed() const {
        return *reinterpret_cast<BooleanSetting *>(image +
                                                   Storage::require_right_mouse_pressedRecord);
    }
    BooleanSetting &require_damage() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_damageRecord);
    }
};
} // namespace reconstruction::Auto_Block
// END SOURCE modules/Auto_Block/Settings.hpp

#endif // SLINKY_SHARE_8A56E7354D15C4624391

#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <windows.h>
#include <xmmintrin.h>
namespace reconstruction::Auto_Block {
namespace NativeEntry {
inline constexpr uint32_t probabilityGate = 0xa460;
inline constexpr uint32_t clientOptions = 0x22cf0;
inline constexpr uint32_t entityIdentifier = 0x23720;
inline constexpr uint32_t entityTicksExisted = 0x23760;
inline constexpr uint32_t lastAttackerTime = 0x239d0;
inline constexpr uint32_t entityHurtTime = 0x239f0;
inline constexpr uint32_t entityUsingItem = 0x23f90;
inline constexpr uint32_t useItemKey = 0x24f90;
inline constexpr uint32_t pressKey = 0x25380;
inline constexpr uint32_t setKeyDownRaw = 0x25460;
inline constexpr uint32_t physicalKeyWord = 0x25490;
inline constexpr uint32_t heldItem = 0x28a50;
inline constexpr uint32_t heldItemCanBlock = 0x28ac0;
} // namespace NativeEntry
struct ab_dispatch {
    native_binding::Context &native;
    uint64_t (*unresolved)(void *, uint32_t, uint64_t, uint64_t, uint64_t, uint64_t, uint32_t,
                           uint64_t);
    uint32_t (*postCallR8)(void *);
    uint64_t operator()(void *user, uint32_t rva, uint64_t a, uint64_t b, uint64_t c, uint64_t d,
                        uint32_t xmm0, uint64_t stack) const {
        uint64_t g[4] = {a, b, c, d}, x[4] = {xmm0, 0, 0, 0}, stackArgs[2] = {stack, 0};
        native_binding::Value value;
        if (native_binding::resolveFrame(native, rva, g, x, stackArgs, value))
            return value.bits;
        return unresolved(user, rva, a, b, c, d, xmm0, stack);
    }
};
struct BlockingExecution {
    uint8_t *image;
    ab_dispatch dispatch;
    void *opaque;
    uint8_t *img(void) {
        return image;
    }
    uint8_t r8(size_t o) {
        return img()[o];
    }
    uint32_t r32(size_t o) {
        uint32_t v;
        memcpy(&v, img() + o, 4);
        return v;
    }
    uint64_t r64p(const void *p, size_t o) {
        uint64_t v;
        memcpy(&v, (const uint8_t *)p + o, 8);
        return v;
    }
    float rf32(size_t o) {
        uint32_t b = r32(o);
        float v;
        memcpy(&v, &b, 4);
        return v;
    }
    double rd64p(const void *p, size_t o) {
        double v;
        memcpy(&v, (const uint8_t *)p + o, 8);
        return v;
    }
    void w8(size_t o, uint8_t v) {
        img()[o] = v;
    }
    void w32(size_t o, uint32_t v) {
        memcpy(img() + o, &v, 4);
    }
    uint32_t xchg32(size_t o, uint32_t v) {
        return (uint32_t)InterlockedExchange((volatile LONG *)(void *)(img() + o), (LONG)v);
    }
    uint32_t dec32(size_t o) {
        return (uint32_t)InterlockedDecrement((volatile LONG *)(void *)(img() + o));
    }
    int32_t cvttss_i32(float v) {
        return _mm_cvttss_si32(_mm_set_ss(v));
    }
    float subss(float a, float b) {
        return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a), _mm_set_ss(b)));
    }
    uint64_t call(uint32_t rva, uint64_t a, uint64_t b, uint32_t c, uint64_t d, uint32_t xmm0) {
        return dispatch(opaque, rva, a, b, c, d, xmm0, 0);
    }
    uint64_t call0(uint32_t rva) {
        return call(rva, 0, 0, 0, 0, 0);
    }
    uint32_t random_raw(uint32_t bits) {
        return (uint8_t)call(NativeEntry::probabilityGate, 0, 0, 0, 0, bits);
    }
    uint32_t random_byte(float x) {
        uint32_t bits;
        memcpy(&bits, &x, 4);
        return random_raw(bits);
    }
    uint64_t game_of(uint8_t *bridge) {
        return r64p(bridge, 0);
    }
    uint64_t target_of(uint8_t *bridge) {
        return r64p(bridge, 0x38);
    }
    uint64_t rearm(uint8_t *bridge, uint64_t entity, uint32_t mode) {
        uint64_t game = game_of(bridge);
        return call(NativeEntry::setKeyDownRaw, game, entity, mode, 0, 0);
    }
    uint64_t entity_from(uint8_t *bridge) {
        uint64_t game = game_of(bridge);
        uint64_t raw = call(NativeEntry::clientOptions, game, r64p(bridge, 0x18), 0, 0, 0);
        game = game_of(bridge);
        return call(NativeEntry::useItemKey, game, raw, 0, 0, 0);
    }
    uint64_t current_block(uint8_t *bridge) {
        uint64_t game = game_of(bridge), item = r64p(bridge, 0x28);
        uint64_t obj = call(NativeEntry::heldItem, game, item, 0, 0, 0);
        /* The native body captures RCX before 28a50 and reuses that game pointer.
         */
        return call(NativeEntry::heldItemCanBlock, game, obj, 0, 0, 0);
    }
    uint32_t random_integer(float value) {
        int32_t whole = cvttss_i32(value);
        float frac = subss(value, (float)whole);
        return (uint32_t)whole + random_byte(frac);
    }

    uint64_t tick_impl(uint8_t *event) {
        uint8_t *bridge = (uint8_t *)(uintptr_t)r64p(event, 8); /* captured in R14 */
        uint32_t esi = 0, eax = 0, edi = 0, ebx = 0;
        uint8_t r12 = 0, r15 = 0, b6 = 0, b8 = 0;
        int write_state = 0;
        uint64_t uvar14 = 0;
        w8(Storage::nativeData_2f9e10, 0);
        if (r8(Storage::nativeData_2f9e11) == 1) {
            uint64_t item = r64p(bridge, 0x28);
            if (item) {
                uint64_t game = game_of(bridge);
                if ((call(NativeEntry::entityUsingItem, game, item, 0, 0, 0) & 0xff) == 0) {
                    call(0x24020, game, item, 0, 0, 0);
                }
            }
            w8(Storage::nativeData_2f9e11, 0);
        }
        eax = r32(Storage::nativeData_2f9e00);
        if (eax)
            w32(Storage::nativeData_2f9e00, eax - 1);

        if (*(uint8_t *)(bridge + 0x40) == 0) {
            if (r8(Storage::nativeData_2f9e19) == 1) {
                uint64_t entity = entity_from(bridge);
                uint32_t mode =
                    (uint32_t)call(NativeEntry::physicalKeyWord, game_of(bridge), entity, 0, 0, 0);
                rearm(bridge, entity, mode);
                w8(Storage::nativeData_2f9e19, 0);
            }
            w8(Storage::nativeData_2f9e12, 0);
            goto post_main;
        }

        esi = (uint32_t)call(NativeEntry::entityHurtTime, game_of(bridge), r64p(bridge, 0x28), 0, 0,
                             0);
        {
            uint64_t game = game_of(bridge);
            uint64_t item = r64p(bridge, 0x28);
            uint64_t obj = call(NativeEntry::heldItem, game, item, 0, 0, 0);
            uint8_t can = (uint8_t)call(NativeEntry::heldItemCanBlock, game, obj, 0, 0, 0);
            w8(Storage::nativeData_2f9e12, 0);
            if (!can) {
                r12 = 0;
                b6 = 0;
                r15 = 0;
                if (r8(Storage::nativeData_2f9e19) == 1)
                    goto fallback;
                goto after_block_test;
            }
            if (r8(Storage::require_left_mouse_pressedCurrent) == 1) {
                uint64_t tag = r64p(bridge, 0x30);
                if (*(uint8_t *)(uintptr_t)(tag + 1) == 0)
                    goto fallback;
            }
            if ((call0(0x42c30) & 0xff) != 0)
                goto fallback;
            ebx = r8(Storage::require_right_mouse_pressedCurrent);
            w8(Storage::nativeData_2f9e12, (uint8_t)ebx);
            {
                uint64_t tag = r64p(bridge, 0x30);
                if ((uint8_t)ebx != *(uint8_t *)(uintptr_t)(tag + 2))
                    goto fallback;
            }
            r12 = 1;
            if (esi == 0 && r8(Storage::require_damageCurrent) != 0)
                goto fallback;
            {
                float chance = rf32(Storage::max_hurt_timeCurrent);
                int32_t chance_whole = cvttss_i32(chance);
                edi = (uint32_t)chance_whole;
                float frac = subss(chance, (float)chance_whole);
                uint32_t n = (uint32_t)edi + random_byte(frac);
                if ((int32_t)esi > (int32_t)n)
                    goto fallback;
            }
            ebx = r8(Storage::nativeData_2f9e18);
            {
                uint64_t entity = entity_from(bridge);
                rearm(bridge, entity, ebx);
                r15 = 1;
                if ((uint8_t)ebx == 1) {
                    uint64_t game = game_of(bridge);
                    call(NativeEntry::pressKey, game, entity, 0, 0, 0);
                    r12 = 1;
                }
            }
            b6 = 1;
            write_state = 1;
            goto after_block_test;
        }

    fallback: {
        uint64_t entity = entity_from(bridge);
        /* Native captures RBX=game at 3177a before the optional 25490 call. */
        uint64_t captured_game = game_of(bridge);
        uint32_t mode = 0;
        if (r8(Storage::nativeData_2f9e12) == 0)
            mode = (uint32_t)call(NativeEntry::physicalKeyWord, captured_game, entity, 0, 0, 0);
        call(NativeEntry::setKeyDownRaw, captured_game, entity, mode, 0, 0);
    }
        b6 = 0;
        r15 = 0;
        write_state = 1;
        goto after_block_test;

    after_block_test:
        /* Native R15B is assigned from the enabled/configuration branch above. */
        if (write_state)
            w8(Storage::nativeData_2f9e19, r15);
        r12 = (uint8_t)(r12 && r8(Storage::fake_block_animationCurrent) != 0);
        if (r12 && r8(Storage::fake_block_animation_require_targetCurrent) == 1) {
            uint64_t distance = target_of(bridge);
            if (r64p((const void *)(uintptr_t)distance, 8) == 0)
                r12 = 0;
            else {
                float radius = rf32(Storage::rangeCurrent);
                double squared = (double)(radius * radius);
                double actual = rd64p((const void *)(uintptr_t)distance, 0x10);
                r12 = (uint8_t)(squared > actual);
            }
        }
        w8(Storage::nativeData_2f9e10, r12);

        if (esi == 10)
            w32(Storage::nativeData_2f9e00, 0);
        w32(Storage::nativeData_2f9e08, r32(Storage::nativeData_2f9e08) + 1u);
        eax = r32(Storage::nativeData_2f9e08);
        /* Native clears ESI before either counter branch at 31814. */
        esi = 0;
        edi = 0;
        if (eax > 9) {
            edi = (uint32_t)call(NativeEntry::entityTicksExisted, game_of(bridge),
                                 r64p(bridge, 0x28), 0, 0, 0);
            eax = (uint32_t)call(NativeEntry::lastAttackerTime, game_of(bridge), r64p(bridge, 0x28),
                                 0, 0, 0);
            if (edi == eax + 1u) {
                w32(Storage::nativeData_2f9e08, 0);
                b8 = 1;
            }
        }
        {
            uint64_t dist = target_of(bridge);
            if (r64p((const void *)(uintptr_t)dist, 8) != 0)
                esi = (uint32_t)call(NativeEntry::entityIdentifier, game_of(bridge),
                                     r64p((const void *)(uintptr_t)dist, 8), 0, 0, 0);
            /* On a null target the native branch preserves ESI from 239f0. */
        }
        if (esi != r32(Storage::nativeData_2f9e0c)) {
            w32(Storage::nativeData_2f9e08, 0);
            b8 = 1;
            w32(Storage::nativeData_2f9e0c, esi);
        }
        eax = r32(Storage::nativeData_2f9e14);
        uvar14 = eax;
        if (eax) {
            if (((uint32_t)b8 & r8(Storage::lag_flush_attackCurrent)) == 1)
                xchg32(Storage::nativeData_2f9e14, 0);
            else
                dec32(Storage::nativeData_2f9e14);
            if (r8(Storage::lag_reblockCurrent) == 1 && r32(Storage::nativeData_2f9e14) == 0)
                w32(Storage::nativeData_2f9e00, 0);
            uvar14 = eax;
        }
        if (r8(Storage::nativeData_2f9e18) != 0) {
            uint32_t i15 = r32(Storage::nativeData_2f9e04) + 1u;
            float delay = rf32(Storage::max_hold_timeCurrent);
            int32_t whole = cvttss_i32(delay);
            float frac = subss(delay, (float)whole);
            w32(Storage::nativeData_2f9e04, i15);
            uint32_t limit = (uint32_t)whole + random_byte(frac);
            if ((r15 & ((int32_t)i15 < (int32_t)limit)) != 0) {
                return (uint64_t)(((uint32_t)limit & 0xffffff00u) |
                                  ((int32_t)i15 < (int32_t)limit));
            }
            {
                uint64_t entity = entity_from(bridge);
                rearm(bridge, entity, 0);
                w8(Storage::nativeData_2f9e19, 1);
                uint64_t chance_return =
                    call(NativeEntry::probabilityGate, 0, 0, 0, 0, r32(Storage::lag_chanceCurrent));
                if ((chance_return & 0xff) != 0) {
                    float v = rf32(Storage::lag_durationCurrent);
                    int32_t n = cvttss_i32(v);
                    uint32_t newvalue = (uint32_t)n + random_byte(subss(v, (float)n));
                    uvar14 = r32(Storage::nativeData_2f9e14);
                    xchg32(Storage::nativeData_2f9e14, newvalue);
                } else {
                    w8(Storage::nativeData_2f9e18, 0);
                    return chance_return;
                }
            }
            w8(Storage::nativeData_2f9e18, 0);
            return uvar14;
        }
        if (!((r15 && r32(Storage::nativeData_2f9e00) == 0) == 1))
            return (uvar14 & ~UINT64_C(0xff)) | (uint8_t)(r32(Storage::nativeData_2f9e00) == 0);
        {
            uint64_t distance = target_of(bridge);
            if (r64p((const void *)(uintptr_t)distance, 8) == 0)
                return distance;
            float radius = rf32(Storage::rangeCurrent);
            double squared = (double)(radius * radius);
            double actual = rd64p((const void *)(uintptr_t)distance, 0x10);
            if (!(squared > actual))
                return distance;
            {
                uint64_t entity = entity_from(bridge);
                rearm(bridge, entity, (dispatch.postCallR8(opaque) & 0xffffff00u) | 1u);
                uint64_t game = game_of(bridge);
                call(NativeEntry::pressKey, game, entity, 0, 0, 0);
                w8(Storage::nativeData_2f9e19, 1);
                w8(Storage::nativeData_2f9e18, 1);
                w32(Storage::nativeData_2f9e00, 10);
                w32(Storage::nativeData_2f9e04, 0);
            }
        }
    post_main:
        eax = xchg32(Storage::nativeData_2f9e14, 0);
        return eax;
    }

    uint64_t updateBlocking(uint8_t *event, uint8_t *image, ab_dispatch dispatch, void *opaque) {
        uint64_t r = tick_impl(event);

        return r;
    }

    void onPacketDispatch(uint8_t *event, uint8_t *image) {
        uint32_t count;
        memcpy(&count, image + Storage::nativeData_2f9e14, 4);
        if (count != 0) {
            uint32_t one = 1;
            memcpy(event + 0x24, &one, 4);
        }
    }

    uint64_t onModuleStateChanged(uint8_t *event, uint8_t *image, ab_dispatch dispatch,
                                  void *opaque) {
        uint64_t result = UINT64_C(0x1802eaff8);
        if (r64p(event, 0x10) == (uint64_t)(uintptr_t)(image + Storage::moduleDescriptor) &&
            event[0x18] == 0 && (r8(Storage::nativeData_2f9e18) & 1)) {
            if (r8(Storage::nativeData_2f9e19) == 1) {
                uint8_t *bridge = (uint8_t *)(uintptr_t)r64p(event, 8);
                uint64_t entity = entity_from(bridge);
                uint32_t mode =
                    (uint32_t)call(NativeEntry::physicalKeyWord, game_of(bridge), entity, 0, 0, 0);
                rearm(bridge, entity, mode);
                w8(Storage::nativeData_2f9e19, 0);
            }
            w8(Storage::nativeData_2f9e18, 0);
            uint32_t oldcount = xchg32(Storage::nativeData_2f9e14, 0);
            result = oldcount;
        }

        return result;
    }

    void onInput(uint8_t *event, uint8_t *image, ab_dispatch dispatch, void *opaque) {
        if (event[0x10] == 0) {
            uint8_t *bridge = (uint8_t *)(uintptr_t)r64p(event, 8);
            uint64_t game = game_of(bridge), item = r64p(bridge, 0x28);
            uint64_t obj = call(NativeEntry::heldItem, game, item, 0, 0, 0);
            uint8_t can = (uint8_t)call(NativeEntry::heldItemCanBlock, game, obj, 0, 0, 0);
            if (!can)
                w32(Storage::nativeData_2f9e14, 0);
            if (r8(Storage::nativeData_2f9e12) == 1 && (r8(Storage::nativeData_2f9e18) & 1) == 0)
                event[0x11] = 1;
        }
    }

    void onItemUseFrame(uint8_t *event, uint8_t *image, ab_dispatch dispatch, void *opaque) {
        if (r8(Storage::nativeData_2f9e10) == 0)
            w32(Storage::nativeData_2f9e1c, 0x11940);
        else {
            uint8_t *bridge = (uint8_t *)(uintptr_t)r64p(event, 8);
            uint64_t item = r64p(bridge, 0x28);
            if (item) {
                w8(Storage::nativeData_2f9e11, 1);
                uint32_t v = r32(Storage::nativeData_2f9e1c) - 1u;
                w32(Storage::nativeData_2f9e1c, v);
                uint64_t game = game_of(bridge);
                call(0x24020, game, item, v, 0, 0);
            }
        }
    }
};
uint64_t updateBlocking(uint8_t *event, uint8_t *image, ab_dispatch dispatch, void *opaque) {
    BlockingExecution execution{image, dispatch, opaque};
    return execution.updateBlocking(event, image, dispatch, opaque);
}
uint64_t onModuleStateChanged(uint8_t *event, uint8_t *image, ab_dispatch dispatch, void *opaque) {
    BlockingExecution execution{image, dispatch, opaque};
    return execution.onModuleStateChanged(event, image, dispatch, opaque);
}
void onInput(uint8_t *event, uint8_t *image, ab_dispatch dispatch, void *opaque) {
    BlockingExecution execution{image, dispatch, opaque};
    execution.onInput(event, image, dispatch, opaque);
}
void onItemUseFrame(uint8_t *event, uint8_t *image, ab_dispatch dispatch, void *opaque) {
    BlockingExecution execution{image, dispatch, opaque};
    execution.onItemUseFrame(event, image, dispatch, opaque);
}
void onPacketDispatch(uint8_t *event, uint8_t *image) {
    uint32_t count;
    memcpy(&count, image + Storage::nativeData_2f9e14, 4);
    if (count) {
        uint32_t one = 1;
        memcpy(event + 0x24, &one, 4);
    }
}
} // namespace reconstruction::Auto_Block
// END SOURCE modules/Auto_Block/BlockingState.cpp

// Convenient borrowed-state interface

namespace shareable {
class AutoBlock {
  public:
    static constexpr const char *kName = "Auto Block";
    static constexpr const char *kDescription = "Blocks your sword for you in combat.";
    explicit AutoBlock(std::uint8_t *image) : image_(image) {}
    // Range. Config key: range.
    NumberSetting &range() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2eb388);
    }
    // Maximum hurt time. Config key: max_hurt_time.
    NumberSetting &max_hurt_time() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2eb2b0);
    }
    // Maximum hold duration. Config key: max_hold_time.
    NumberSetting &max_hold_time() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2eb208);
    }
    // Enabled. Config key: fake_block_animation.
    BooleanSetting &fake_block_animation() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eb348);
    }
    // Only within range. Config key: fake_block_animation_require_target.
    BooleanSetting &fake_block_animation_require_target() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eb368);
    }
    // Chance. Config key: lag_chance.
    NumberSetting &lag_chance() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2eb240);
    }
    // Maximum duration. Config key: lag_duration.
    NumberSetting &lag_duration() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2eb278);
    }
    // Prevent delaying attacks. Config key: lag_flush_attack.
    BooleanSetting &lag_flush_attack() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eb3c0);
    }
    // Block again immediately. Config key: lag_reblock.
    BooleanSetting &lag_reblock() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eb3e0);
    }
    // Left mouse pressed. Config key: require_left_mouse_pressed.
    BooleanSetting &require_left_mouse_pressed() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eb2e8);
    }
    // Right mouse pressed. Config key: require_right_mouse_pressed.
    BooleanSetting &require_right_mouse_pressed() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eb308);
    }
    // Damaged. Config key: require_damage.
    BooleanSetting &require_damage() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eb328);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_auto_block_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_auto_block_settings(&context, image_, &dependencies);
    }
    uint64_t updateBlocking(uint8_t *event, ::reconstruction::Auto_Block::ab_dispatch dispatch,
                            void *opaque) {
        return ::reconstruction::Auto_Block::updateBlocking(event, image_, dispatch, opaque);
    }
    uint64_t onModuleStateChanged(uint8_t *event,
                                  ::reconstruction::Auto_Block::ab_dispatch dispatch,
                                  void *opaque) {
        return ::reconstruction::Auto_Block::onModuleStateChanged(event, image_, dispatch, opaque);
    }
    void onInput(uint8_t *event, ::reconstruction::Auto_Block::ab_dispatch dispatch, void *opaque) {
        ::reconstruction::Auto_Block::onInput(event, image_, dispatch, opaque);
    }
    void onItemUseFrame(uint8_t *event, ::reconstruction::Auto_Block::ab_dispatch dispatch,
                        void *opaque) {
        ::reconstruction::Auto_Block::onItemUseFrame(event, image_, dispatch, opaque);
    }
    void onPacketDispatch(uint8_t *event) {
        ::reconstruction::Auto_Block::onPacketDispatch(event, image_);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
