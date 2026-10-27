// Auto Soup

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Auto_Soup.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Auto_Soup.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Auto Soup: lib_win settings 0x2dc70.
static constexpr SettingsStep settings_steps_Surface_Auto_Soup[] = {
    {SettingsControl::number, "single_soup_max_hp", 0x2e98c0},
    {SettingsControl::number, "double_soup_max_hp", 0x2e9930},
    {SettingsControl::number, "randomization", 0x2e99d8},
    {SettingsControl::number, "delay_before", 0x2e98f8},
    {SettingsControl::number, "delay_between", 0x2e9968},
    {SettingsControl::number, "delay_after", 0x2e99a0},
    {SettingsControl::boolean, "drop_bowls", 0x2e9a30},
    {SettingsControl::boolean, "override_item", 0x2e9a10},
    {SettingsControl::list, "allowed_items", 0x2e9a50},
};
static constexpr ModuleSurface surface_Surface_Auto_Soup{
    nullptr, 0, settings_steps_Surface_Auto_Soup, std::size(settings_steps_Surface_Auto_Soup)};

extern "C" __declspec(dllexport) void
recovered_auto_soup_settings(SettingsContext *context, std::uint8_t *image,
                             const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Auto_Soup, context, image, *dependencies);
}

// Auto Soup: lib_win runtime UI 0x2db50.
extern "C" __declspec(dllexport) void
recovered_auto_soup_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                       const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Maximum health");
    dependencies->number(layout, ui, image + 0x2e98c0);
    if (read_surface_value<float>(image, 0x2e9960) > read_surface_value<float>(image, 0x2e98f0)) {
        std::memcpy(image + 0x2e9960, image + 0x2e98f0, sizeof(float));
    }
    dependencies->number(layout, ui, image + 0x2e9930);
    dependencies->section(ui, layout, "Delays");
    dependencies->number(layout, ui, image + 0x2e99d8);
    dependencies->number(layout, ui, image + 0x2e98f8);
    dependencies->number(layout, ui, image + 0x2e9968);
    dependencies->number(layout, ui, image + 0x2e99a0);
    dependencies->section(ui, layout, "Extra");
    dependencies->checkbox(layout, ui, image + 0x2e9a30);
    dependencies->checkbox(layout, ui, image + 0x2e9a10);
    if (image[0x2e9a28] == 1) {
        dependencies->list(layout, ui, image + 0x2e9a50);
    }
}
// END SOURCE native/verified/surfaces/Surface_Auto_Soup.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Auto_Soup/auto_soup.cpp
#ifndef SLINKY_SHARE_AF2CEAD1D0B7970C3411
#define SLINKY_SHARE_AF2CEAD1D0B7970C3411
// BEGIN SOURCE modules/Auto_Soup/NativeAbi.hpp
#ifndef AUTO_SOUP_H
#define AUTO_SOUP_H
#include "../runtime/shared/OwnedNativeBindings.hpp"
#include <stdint.h>
typedef struct soup_args {
    uint64_t rcx, rdx, r8, r9, xmm0, xmm1, xmm2;
    /* Original stack argument 5; the indirect item call uses this field to expose
     * its loaded target. */
    uint64_t stack5;
} soup_args;
typedef struct soup_result {
    uint64_t rax, xmm0;
} soup_result;
struct soup_dispatch {
    reconstruction::native_binding::Context &native;
    void (*unresolved)(uint32_t, const soup_args *, soup_result *, void *);
    void operator()(uint32_t rva, const soup_args *args, soup_result *result, void *user) const {
        uint64_t g[4] = {args->rcx, args->rdx, args->r8, args->r9},
                 x[4] = {args->xmm0, args->xmm1, args->xmm2, 0}, st[2] = {args->stack5, 0};
        reconstruction::native_binding::Value value;
        if (reconstruction::native_binding::resolveFrame(native, rva, g, x, st, value)) {
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
void recovered_auto_soup_2d510(uint8_t *event, uint8_t *image, soup_dispatch call, void *user);
void recovered_auto_soup_2dae0(uint8_t *event, uint8_t *image);
void recovered_auto_soup_2db10(uint8_t *event, uint8_t *image);
#endif
// END SOURCE modules/Auto_Soup/NativeAbi.hpp

#endif // SLINKY_SHARE_AF2CEAD1D0B7970C3411

#ifndef SLINKY_SHARE_1A5B0F139D71941AA7EF
#define SLINKY_SHARE_1A5B0F139D71941AA7EF
// BEGIN SOURCE modules/Auto_Soup/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Auto_Soup {
namespace Storage {
inline constexpr std::uint32_t nativeData_1505a8 = 0x1505a8;
inline constexpr std::uint32_t nativeData_1505ac = 0x1505ac;
inline constexpr std::uint32_t nativeData_1505b0 = 0x1505b0;
inline constexpr std::uint32_t nativeData_1505b8 = 0x1505b8;
inline constexpr std::uint32_t nativeData_1505c0 = 0x1505c0;
inline constexpr std::uint32_t moduleDescriptor = 0x2e96b0;
inline constexpr std::uint32_t single_soup_max_hpRecord = 0x2e98c0;
inline constexpr std::uint32_t single_soup_max_hpCurrent = 0x2e98f0;
inline constexpr std::uint32_t delay_beforeRecord = 0x2e98f8;
inline constexpr std::uint32_t delay_beforeCurrent = 0x2e9928;
inline constexpr std::uint32_t double_soup_max_hpRecord = 0x2e9930;
inline constexpr std::uint32_t double_soup_max_hpCurrent = 0x2e9960;
inline constexpr std::uint32_t delay_betweenRecord = 0x2e9968;
inline constexpr std::uint32_t delay_betweenCurrent = 0x2e9998;
inline constexpr std::uint32_t delay_afterRecord = 0x2e99a0;
inline constexpr std::uint32_t delay_afterCurrent = 0x2e99d0;
inline constexpr std::uint32_t randomizationRecord = 0x2e99d8;
inline constexpr std::uint32_t randomizationCurrent = 0x2e9a08;
inline constexpr std::uint32_t override_itemRecord = 0x2e9a10;
inline constexpr std::uint32_t override_itemCurrent = 0x2e9a28;
inline constexpr std::uint32_t drop_bowlsRecord = 0x2e9a30;
inline constexpr std::uint32_t drop_bowlsCurrent = 0x2e9a48;
inline constexpr std::uint32_t allowed_itemsRecord = 0x2e9a50;
inline constexpr std::uint32_t cancelRequested = 0x2f7d68;
inline constexpr std::uint32_t soupPhase = 0x2f7d6c;
inline constexpr std::uint32_t reusePreviousSlot = 0x2f7d70;
inline constexpr std::uint32_t selectedSoupSlot = 0x2f7d74;
inline constexpr std::uint32_t previousSlot = 0x2f7d78;
inline constexpr std::uint32_t repeatUsePending = 0x2f7d7c;
inline constexpr std::uint32_t selectedItemIsSoup = 0x2f7d7d;
inline constexpr std::uint32_t remainingDelay = 0x2f7d80;
inline constexpr std::uint32_t nativeData_2f7da8 = 0x2f7da8;
inline constexpr std::uint32_t nativeData_2f7db8 = 0x2f7db8;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &single_soup_max_hp() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::single_soup_max_hpRecord);
    }
    NumberSetting &double_soup_max_hp() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::double_soup_max_hpRecord);
    }
    NumberSetting &randomization() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::randomizationRecord);
    }
    NumberSetting &delay_before() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::delay_beforeRecord);
    }
    NumberSetting &delay_between() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::delay_betweenRecord);
    }
    NumberSetting &delay_after() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::delay_afterRecord);
    }
    BooleanSetting &drop_bowls() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::drop_bowlsRecord);
    }
    BooleanSetting &override_item() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::override_itemRecord);
    }
    ListSetting &allowed_items() const {
        return *reinterpret_cast<ListSetting *>(image + Storage::allowed_itemsRecord);
    }
};
} // namespace reconstruction::Auto_Soup
// END SOURCE modules/Auto_Soup/Settings.hpp

#endif // SLINKY_SHARE_1A5B0F139D71941AA7EF

#include <emmintrin.h>
#include <string.h>
namespace reconstruction::Auto_Soup {
namespace NativeEntry {
inline constexpr uint32_t randomRangeSample = 0xa3e0;
inline constexpr uint32_t smoothedRandomSample = 0xa510;
inline constexpr uint32_t randomRangeBits = 0xa050;
inline constexpr uint32_t smoothedProbabilityGate = 0xaa30;
inline constexpr uint32_t clientOptions = 0x22cf0;
inline constexpr uint32_t entityHealth = 0x23a40;
inline constexpr uint32_t entityInventory = 0x23f40;
inline constexpr uint32_t entityUsingItem = 0x23f90;
inline constexpr uint32_t useItemKey = 0x24f90;
inline constexpr uint32_t dropItemKey = 0x24fe0;
inline constexpr uint32_t pressKey = 0x25380;
inline constexpr uint32_t inventorySelectedSlot = 0x25a60;
inline constexpr uint32_t selectInventorySlot = 0x25a80;
inline constexpr uint32_t inventoryMainList = 0x25ab0;
inline constexpr uint32_t itemNumericType = 0x25c50;
inline constexpr uint32_t stackItem = 0x25d10;
inline constexpr uint32_t scheduleModuleAction = 0x284f0;
inline constexpr uint32_t claimModuleAction = 0x2aa80;
inline constexpr uint32_t releaseModuleAction = 0x2aab0;
inline constexpr uint32_t itemPolicyMatches = 0x2ac60;
} // namespace NativeEntry

#define ENABLED Storage::cancelRequested
#define STATE Storage::soupPhase
#define FLAG Storage::reusePreviousSlot
#define ITEM_ID Storage::selectedSoupSlot
#define ITEM_KIND Storage::previousSlot
#define HAS_TARGET Storage::repeatUsePending
#define SELECTED Storage::selectedItemIsSoup
#define TIMER Storage::remainingDelay
#define ITEM_FILTER Storage::nativeData_2f7db8
#define DESC Storage::moduleDescriptor
#define F32(x) fbits((float)(x))

static uint8_t get8(const uint8_t *p, uint32_t o) {
    return p[o];
}
static uint32_t get32(const uint8_t *p, uint32_t o) {
    uint32_t v;
    memcpy(&v, p + o, 4);
    return v;
}
static uint64_t get64(const uint8_t *p, uint32_t o) {
    uint64_t v;
    memcpy(&v, p + o, 8);
    return v;
}
static void put8(uint8_t *p, uint32_t o, uint8_t v) {
    p[o] = v;
}
static void put32(uint8_t *p, uint32_t o, uint32_t v) {
    memcpy(p + o, &v, 4);
}
static float getf(const uint8_t *p, uint32_t o) {
    float v;
    memcpy(&v, p + o, 4);
    return v;
}
static void putf(uint8_t *p, uint32_t o, float v) {
    memcpy(p + o, &v, 4);
}
static uint64_t fbits(float v) {
    uint32_t b;
    memcpy(&b, &v, 4);
    return b;
}
static void invoke(soup_dispatch call, void *user, uint32_t rva, uint64_t rcx, uint64_t rdx,
                   uint64_t r8, uint64_t r9, uint64_t xmm0, uint64_t xmm1, uint64_t xmm2,
                   soup_result *out) {
    soup_args a = {rcx, rdx, r8, r9, xmm0, xmm1, xmm2, 0};
    out->rax = 0;
    out->xmm0 = 0;
    call(rva, &a, out, user);
}
static void invoke_vtable(soup_dispatch call, void *user, uint64_t target, uint64_t rcx,
                          uint64_t rdx, uint64_t r8, soup_result *out) {
    soup_args a = {rcx, rdx, r8, 0, 0, 0, 0, target};
    out->rax = 0;
    out->xmm0 = 0;
    call(0x70000000, &a, out, user);
}
static uint64_t image_address(uint8_t *image, uint32_t offset) {
    return (uint64_t)(uintptr_t)(image + offset);
}

// RVA 0x2dd50. Runtime instructions capture upper/period once, add the second
// sample to the first in that operand order, then multiply before adding base.
static float sampleSoupDelay(uint8_t *image, soup_dispatch api, void *user, float base) {
    float upper = getf(image, 0x1505e0);
    uint64_t firstPeriod = get64(image, 0x1505e8);
    soup_result value;
    invoke(api, user, NativeEntry::randomRangeBits, 0, 0, 0, 0, F32(0.0f), F32(upper), 0, &value);
    invoke(api, user, NativeEntry::smoothedRandomSample, image_address(image, 0x2f7d88), value.rax,
           0, 0, 0, 0, firstPeriod, &value);
    float first;
    uint32_t word = uint32_t(value.xmm0);
    memcpy(&first, &word, 4);
    invoke(api, user, NativeEntry::randomRangeBits, 0, 0, 0, 0, F32(0.0f), F32(upper), 0, &value);
    invoke(api, user, NativeEntry::smoothedRandomSample, image_address(image, 0x2f7d88), value.rax,
           0, 0, 0, 0, get64(image, 0x1505f0), &value);
    float second;
    word = uint32_t(value.xmm0);
    memcpy(&second, &word, 4);
    float sum = _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(second), _mm_set_ss(first)));
    invoke(api, user, NativeEntry::randomRangeBits, 0, 0, 0, 0, F32(getf(image, 0x1505f8)),
           F32(getf(image, 0x1505fc)), 0, &value);
    invoke(api, user, NativeEntry::smoothedProbabilityGate, image_address(image, 0x2f7d98),
           value.rax, 0, 0, 0, 0, firstPeriod, &value);
    if (uint8_t(value.rax)) {
        invoke(api, user, NativeEntry::randomRangeBits, 0, 0, 0, 0, F32(getf(image, 0x1505e0)),
               F32(getf(image, 0x150600)), 0, &value);
        invoke(api, user, NativeEntry::randomRangeSample, value.rax, 0, 0, 0, 0, 0, 0, &value);
        float extra;
        word = uint32_t(value.xmm0);
        memcpy(&extra, &word, 4);
        sum = _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(sum), _mm_set_ss(extra)));
    }
    float scale = getf(image, 0x2e9a08);
    float scaled = _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(sum), _mm_set_ss(scale)));
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(scaled), _mm_set_ss(base)));
}

static float random_add(uint8_t *image, soup_dispatch api, void *user, float scale) {
    float sampled = sampleSoupDelay(image, api, user, scale);
    return getf(image, TIMER) + sampled;
}
static void post_action(uint8_t *image, soup_dispatch call, void *user) {
    soup_result r;
    put32(image, STATE, 5);
    if (get32(image, ITEM_ID) != get32(image, ITEM_KIND)) {
        putf(image, TIMER,
             random_add(image, call, user, getf(image, Storage::delay_betweenCurrent)));
        if (getf(image, TIMER) <= 0.0f)
            putf(image, TIMER, getf(image, TIMER) + *(float *)(image + Storage::nativeData_1505a8));
    }
}
static uint64_t query_player(const uint8_t *ctx) {
    return get64(ctx, 0);
}
static uint64_t query_second(const uint8_t *ctx, uint32_t off) {
    return get64(ctx, off);
}

void advanceSoupSequence(uint8_t *event, uint8_t *image, soup_dispatch call, void *user) {
    uint8_t *ctx = (uint8_t *)(uintptr_t)get64(event, 8);
    uint32_t state = get32(image, STATE);
    if (get8(image, ENABLED) == 1 && (state == 6 || state == 0)) {
        soup_result r;
        invoke(call, user, NativeEntry::scheduleModuleAction, get64(ctx, 8),
               image_address(image, DESC), 0, 0, 0, 0, 0, &r);
        return;
    }
    if (get8(ctx, 0x40) != 1) {
        put8(image, FLAG, 0);
        put32(image, STATE, 0);
        return;
    }
    for (uint32_t pass = 0; pass < 3; pass++) {
        float timer = getf(image, TIMER);
        if (timer > 0.0f) {
            timer += *(float *)(image + Storage::nativeData_1505c0);
            putf(image, TIMER, timer);
            return;
        }
        state = get32(image, STATE);
        soup_result r;
        switch (state) {
        case 0: {
            invoke(call, user, NativeEntry::entityHealth, query_player(ctx),
                   query_second(ctx, 0x28), 0, 0, 0, 0, 0, &r);
            float value = *(float *)&r.xmm0;
            if (value > getf(image, Storage::single_soup_max_hpCurrent))
                return;
            putf(image, TIMER,
                 random_add(image, call, user, getf(image, Storage::delay_beforeCurrent)));
            put8(image, HAS_TARGET,
                 (uint8_t)(value <= getf(image, Storage::double_soup_max_hpCurrent)));
            put32(image, STATE, 1);
            break;
        }
        case 4: {
            invoke(call, user, NativeEntry::clientOptions, query_player(ctx),
                   query_second(ctx, 0x18), 0, 0, 0, 0, 0, &r);
            uint64_t v = r.rax;
            invoke(call, user, NativeEntry::dropItemKey, query_player(ctx), v, 0, 0, 0, 0, 0, &r);
            v = r.rax;
            invoke(call, user, NativeEntry::pressKey, query_player(ctx), v, 0, 0, 0, 0, 0, &r);
            post_action(image, call, user);
            break;
        }
        case 2: {
            invoke(call, user, NativeEntry::claimModuleAction, image_address(image, DESC), 0, 0, 0,
                   0, 0, 0, &r);
            if ((uint8_t)r.rax == 0) {
                put32(image, STATE, 0);
                return;
            }
            invoke(call, user, NativeEntry::entityInventory, query_player(ctx),
                   query_second(ctx, 0x28), 0, 0, 0, 0, 0, &r);
            uint64_t inv = r.rax;
            invoke(call, user, NativeEntry::selectInventorySlot, query_player(ctx), inv,
                   get32(image, ITEM_ID), 0, 0, 0, 0, &r);
            put32(image, STATE, 3);
            putf(image, TIMER,
                 random_add(image, call, user, getf(image, Storage::delay_betweenCurrent)));
            invoke(call, user, NativeEntry::entityUsingItem, query_player(ctx),
                   query_second(ctx, 0x28), 0, 0, 0, 0, 0, &r);
            if ((uint8_t)r.rax != 0 && getf(image, TIMER) <= 0.0f)
                putf(image, TIMER,
                     getf(image, TIMER) + *(float *)(image + Storage::nativeData_1505a8));
            break;
        }
        case 3: {
            invoke(call, user, NativeEntry::clientOptions, query_player(ctx),
                   query_second(ctx, 0x18), 0, 0, 0, 0, 0, &r);
            uint64_t v = r.rax;
            invoke(call, user, NativeEntry::useItemKey, query_player(ctx), v, 0, 0, 0, 0, 0, &r);
            v = r.rax;
            invoke(call, user, NativeEntry::pressKey, query_player(ctx), v, 0, 0, 0, 0, 0, &r);
            if (get8(image, Storage::drop_bowlsCurrent) == 1 && get8(image, SELECTED) != 0) {
                put32(image, STATE, 4);
                float t = random_add(image, call, user, getf(image, Storage::delay_betweenCurrent));
                if (t <= 0.0f)
                    t += *(float *)(image + Storage::nativeData_1505a8);
                putf(image, TIMER, t);
            } else
                post_action(image, call, user);
            break;
        }
        case 1: {
            invoke(call, user, NativeEntry::entityInventory, query_player(ctx),
                   query_second(ctx, 0x28), 0, 0, 0, 0, 0, &r);
            uint64_t inv = r.rax;
            uint8_t skip_current = get8(image, FLAG);
            invoke(call, user, NativeEntry::inventorySelectedSlot, query_player(ctx), inv, 0, 0, 0,
                   0, 0, &r);
            int32_t start = (int32_t)(uint32_t)r.rax;
            invoke(call, user, NativeEntry::inventoryMainList, query_player(ctx), inv, 0, 0, 0, 0,
                   0, &r);
            uint64_t stack = r.rax;
            int32_t selected = -1;
            int32_t candidate = -1;
            uint32_t kind = 0;
            for (int32_t i = 0; i < 9; i++) {
                uint32_t wrapped = (uint32_t)start + (uint32_t)i;
                int32_t signed_wrapped = (int32_t)wrapped;
                int32_t rem = signed_wrapped % 9;
                candidate = rem;
                if (candidate == start && (skip_current & 1))
                    continue;
                uint64_t item = 0;
                uint64_t game = query_player(ctx),
                         endpoint_object = get64((const uint8_t *)(uintptr_t)game, 8);
                uint64_t endpoint_vtable = get64((const uint8_t *)(uintptr_t)endpoint_object, 0);
                uint64_t target = get64((const uint8_t *)(uintptr_t)endpoint_vtable, 0x568);
                invoke_vtable(call, user, target, endpoint_object, stack, (uint32_t)candidate, &r);
                item = r.rax;
                if (item) {
                    invoke(call, user, NativeEntry::stackItem, game, item, 0, 0, 0, 0, 0, &r);
                    invoke(call, user, NativeEntry::itemNumericType, game, r.rax, 0, 0, 0, 0, 0,
                           &r);
                    kind = (uint32_t)r.rax;
                } else
                    kind = 0;
                uint8_t filtered = get8(image, Storage::override_itemCurrent) == 1;
                if (filtered) {
                    invoke(call, user, NativeEntry::itemPolicyMatches,
                           image_address(image, ITEM_FILTER), kind, 0, 0, 0, 0, 0, &r);
                    if ((uint8_t)r.rax == 0)
                        continue;
                } else if (kind != 0x19d && kind != 0x11a)
                    continue;
                {
                    put8(image, SELECTED, (uint8_t)(kind == 0x19d || kind == 0x11a));
                    invoke(call, user, NativeEntry::randomRangeBits, 0, 0, 0, 0,
                           F32(getf(image, Storage::nativeData_1505ac)),
                           F32(getf(image, Storage::nativeData_1505b0)), 0, &r);
                    invoke(call, user, NativeEntry::smoothedProbabilityGate,
                           image_address(image, Storage::nativeData_2f7da8), r.rax, 0, 0, 0, 0,
                           get64(image, Storage::nativeData_1505b8), &r);
                    selected = candidate;
                    if ((uint8_t)r.rax == 0)
                        break;
                }
            }
            if (selected == -1) {
                uint8_t flag = get8(image, FLAG);
                put32(image, STATE, 6 - flag);
                put8(image, FLAG, 0);
                return;
            }
            put32(image, ITEM_ID, (uint32_t)selected);
            uint32_t current;
            if (get8(image, FLAG) == 1)
                current = get32(image, ITEM_KIND);
            else {
                invoke(call, user, NativeEntry::inventorySelectedSlot, query_player(ctx), inv, 0, 0,
                       0, 0, 0, &r);
                current = (uint32_t)r.rax;
                put32(image, ITEM_KIND, current);
            }
            uint32_t selected_after_reload = get32(image, ITEM_ID);
            put8(image, FLAG, 0);
            put32(image, STATE, (selected_after_reload == current) + 2);
            break;
        }
        case 5: {
            invoke(call, user, NativeEntry::releaseModuleAction, image_address(image, DESC), 0, 0,
                   0, 0, 0, 0, &r);
            if (get8(image, HAS_TARGET) == 1) {
                put8(image, HAS_TARGET, 0);
                put8(image, FLAG, 1);
                put32(image, STATE, 1);
            } else {
                invoke(call, user, NativeEntry::entityInventory, query_player(ctx),
                       query_second(ctx, 0x28), 0, 0, 0, 0, 0, &r);
                uint64_t inv = r.rax;
                invoke(call, user, NativeEntry::selectInventorySlot, query_player(ctx), inv,
                       get32(image, ITEM_KIND), 0, 0, 0, 0, &r);
                put32(image, STATE, 6);
            }
            break;
        }
        case 6: {
            put8(image, FLAG, 0);
            putf(image, TIMER,
                 random_add(image, call, user, getf(image, Storage::delay_afterCurrent)));
            put32(image, STATE, 0);
            break;
        }
        default:
            return;
        }
    }
}

void onActionRequest(uint8_t *event, uint8_t *image) {
    if (get64(event, 8) != (uint64_t)(uintptr_t)(image + DESC))
        return;
    uint32_t state = get32(image, STATE);
    if (state == 0 || state == 6)
        return;
    put8(event, 0x10, 1);
    put8(image, ENABLED, 1);
}
void onModuleStateChanged(uint8_t *event, uint8_t *image) {
    if (get64(event, 0x10) != (uint64_t)(uintptr_t)(image + DESC) || get8(event, 0x18) != 1)
        return;
    put32(image, STATE, 0);
    put8(image, FLAG, 0);
    putf(image, TIMER, 0.0f);
    put8(image, ENABLED, 0);
}

} // namespace reconstruction::Auto_Soup
// END SOURCE modules/Auto_Soup/auto_soup.cpp

// Convenient borrowed-state interface

namespace shareable {
class AutoSoup {
  public:
    static constexpr const char *kName = "Auto Soup";
    static constexpr const char *kDescription = "Uses soups for you.";
    explicit AutoSoup(std::uint8_t *image) : image_(image) {}
    // Single use. Config key: single_soup_max_hp.
    NumberSetting &single_soup_max_hp() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2e98c0);
    }
    // Double use. Config key: double_soup_max_hp.
    NumberSetting &double_soup_max_hp() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2e9930);
    }
    // Randomization. Config key: randomization.
    NumberSetting &randomization() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2e99d8);
    }
    // Before switching slots. Config key: delay_before.
    NumberSetting &delay_before() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2e98f8);
    }
    // Between actions. Config key: delay_between.
    NumberSetting &delay_between() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2e9968);
    }
    // Cooldown. Config key: delay_after.
    NumberSetting &delay_after() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2e99a0);
    }
    // Drop bowls. Config key: drop_bowls.
    BooleanSetting &drop_bowls() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2e9a30);
    }
    // Override item type. Config key: override_item.
    BooleanSetting &override_item() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2e9a10);
    }
    // allowed_items. Config key: allowed_items.
    ListSetting &allowed_items() const {
        return *reinterpret_cast<ListSetting *>(image_ + 0x2e9a50);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_auto_soup_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_auto_soup_settings(&context, image_, &dependencies);
    }
    void advanceSoupSequence(uint8_t *event, soup_dispatch call, void *user) {
        ::reconstruction::Auto_Soup::advanceSoupSequence(event, image_, call, user);
    }
    void onActionRequest(uint8_t *event) {
        ::reconstruction::Auto_Soup::onActionRequest(event, image_);
    }
    void onModuleStateChanged(uint8_t *event) {
        ::reconstruction::Auto_Soup::onModuleStateChanged(event, image_);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
