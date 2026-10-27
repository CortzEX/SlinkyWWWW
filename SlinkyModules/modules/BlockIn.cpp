// Block In

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Block_In.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Block_In.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Block In: lib_win settings 0x4bc20.
// UI 0x4bbc0.
static constexpr UiStep ui_steps_Surface_Block_In[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2f6338},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2f6318},
};
static constexpr SettingsStep settings_steps_Surface_Block_In[] = {
    {SettingsControl::number, "speed", 0x2f6338},
    {SettingsControl::boolean, "require_ground", 0x2f6318},
};
static constexpr ModuleSurface surface_Surface_Block_In{
    ui_steps_Surface_Block_In, std::size(ui_steps_Surface_Block_In),
    settings_steps_Surface_Block_In, std::size(settings_steps_Surface_Block_In)};

extern "C" __declspec(dllexport) void
recovered_block_in_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                      const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Block_In, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_block_in_settings(SettingsContext *context, std::uint8_t *image,
                            const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Block_In, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Block_In.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Block_In/block_in_events.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_FFFAE54EBF0A4204E69C
#define SLINKY_SHARE_FFFAE54EBF0A4204E69C
// BEGIN SOURCE modules/Block_In/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Block_In {
namespace Storage {
inline constexpr std::uint32_t nativeData_156870 = 0x156870;
inline constexpr std::uint32_t nativeData_156880 = 0x156880;
inline constexpr std::uint32_t nativeData_156890 = 0x156890;
inline constexpr std::uint32_t nativeData_1568a0 = 0x1568a0;
inline constexpr std::uint32_t nativeData_1568a8 = 0x1568a8;
inline constexpr std::uint32_t nativeData_1568b0 = 0x1568b0;
inline constexpr std::uint32_t nativeData_1568b4 = 0x1568b4;
inline constexpr std::uint32_t nativeData_1568b8 = 0x1568b8;
inline constexpr std::uint32_t nativeData_1568c0 = 0x1568c0;
inline constexpr std::uint32_t nativeData_1568c8 = 0x1568c8;
inline constexpr std::uint32_t nativeData_1568d0 = 0x1568d0;
inline constexpr std::uint32_t nativeData_1568d8 = 0x1568d8;
inline constexpr std::uint32_t nativeData_1568dc = 0x1568dc;
inline constexpr std::uint32_t nativeData_1568e4 = 0x1568e4;
inline constexpr std::uint32_t nativeData_1568e8 = 0x1568e8;
inline constexpr std::uint32_t nativeData_1568ec = 0x1568ec;
inline constexpr std::uint32_t nativeData_1568f0 = 0x1568f0;
inline constexpr std::uint32_t nativeData_1568f4 = 0x1568f4;
inline constexpr std::uint32_t nativeData_1568f8 = 0x1568f8;
inline constexpr std::uint32_t nativeData_156900 = 0x156900;
inline constexpr std::uint32_t nativeData_156910 = 0x156910;
inline constexpr std::uint32_t nativeData_156920 = 0x156920;
inline constexpr std::uint32_t nativeData_156930 = 0x156930;
inline constexpr std::uint32_t nativeData_156940 = 0x156940;
inline constexpr std::uint32_t nativeData_156b80 = 0x156b80;
inline constexpr std::uint32_t nativeData_156b9e = 0x156b9e;
inline constexpr std::uint32_t nativeData_156b9f = 0x156b9f;
inline constexpr std::uint32_t nativeData_156ba8 = 0x156ba8;
inline constexpr std::uint32_t nativeData_156bb0 = 0x156bb0;
inline constexpr std::uint32_t moduleDescriptor = 0x2f6108;
inline constexpr std::uint32_t require_groundRecord = 0x2f6318;
inline constexpr std::uint32_t require_groundCurrent = 0x2f6330;
inline constexpr std::uint32_t speedRecord = 0x2f6338;
inline constexpr std::uint32_t speedCurrent = 0x2f6368;
inline constexpr std::uint32_t nativeData_304b10 = 0x304b10;
inline constexpr std::uint32_t nativeData_304b18 = 0x304b18;
inline constexpr std::uint32_t nativeData_304b1c = 0x304b1c;
inline constexpr std::uint32_t nativeData_304b20 = 0x304b20;
inline constexpr std::uint32_t nativeData_304b28 = 0x304b28;
inline constexpr std::uint32_t nativeData_304b30 = 0x304b30;
inline constexpr std::uint32_t nativeData_304b38 = 0x304b38;
inline constexpr std::uint32_t nativeData_304b48 = 0x304b48;
inline constexpr std::uint32_t nativeData_304b58 = 0x304b58;
inline constexpr std::uint32_t nativeData_304b68 = 0x304b68;
inline constexpr std::uint32_t nativeData_304b78 = 0x304b78;
inline constexpr std::uint32_t nativeData_304b88 = 0x304b88;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &speed() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::speedRecord);
    }
    BooleanSetting &require_ground() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_groundRecord);
    }
};
} // namespace reconstruction::Block_In
// END SOURCE modules/Block_In/Settings.hpp

#endif // SLINKY_SHARE_FFFAE54EBF0A4204E69C

#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
namespace reconstruction::Block_In {
#define API
using Dispatch = native_binding::WordEndpoints;
// Native entry 0x22cf0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t clientOptions_block_in_events(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2,
                                              uint64_t a3) {
    return api(0x22cf0, a0, a1, a2, a3);
}
// Native entry 0x23170; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityRotation_block_in_events(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2,
                                               uint64_t a3) {
    return api(0x23170, a0, a1, a2, a3);
}
// Native entry 0x250d0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t backwardKey(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x250d0, a0, a1, a2, a3);
}
// Native entry 0x25120; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t forwardKey(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x25120, a0, a1, a2, a3);
}
// Native entry 0x25170; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t leftKey(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x25170, a0, a1, a2, a3);
}
// Native entry 0x251c0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t rightKey(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x251c0, a0, a1, a2, a3);
}
// Native entry 0x25460; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t setKeyDownRaw(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x25460, a0, a1, a2, a3);
}
// Native entry 0x25490; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t physicalKeyWord(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x25490, a0, a1, a2, a3);
}
// Native entry 0xb1fb0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_b1fb0(Dispatch api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0xb1fb0, a0, a1, a2, a3);
}

static uint64_t loadWord64_block_in_events(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t loadWord32_block_in_events(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static float loadFloat_block_in_events(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static uint8_t *ptr(uint64_t v) {
    return (uint8_t *)(uintptr_t)v;
}
static void collect(uint8_t *ctx, uint64_t keys[4], Dispatch call) {
    uint64_t settings = clientOptions_block_in_events(call, loadWord64_block_in_events(ctx),
                                                      loadWord64_block_in_events(ctx + 0x18), 0, 0);
    keys[0] = backwardKey(call, loadWord64_block_in_events(ctx), settings, 0, 0);
    keys[1] = forwardKey(call, loadWord64_block_in_events(ctx), settings, 0, 0);
    keys[2] = leftKey(call, loadWord64_block_in_events(ctx), settings, 0, 0);
    keys[3] = rightKey(call, loadWord64_block_in_events(ctx), settings, 0, 0);
}
API void onTick(uint8_t *event, uint8_t *image, Dispatch call) {
    (void)event;
    (void)image;
    (void)call;
}
API void onModuleStateChanged(uint8_t *event, uint8_t *image, Dispatch call) {
    if (loadWord64_block_in_events(event + 0x10) !=
        (uint64_t)(uintptr_t)(image + Storage::moduleDescriptor))
        return;
    uint8_t *ctx = ptr(loadWord64_block_in_events(event + 8));
    if (event[0x18] == 1) {
        memset(image + Storage::nativeData_304b10, 0, 8);
        uint32_t angle = (uint32_t)entityRotation_block_in_events(
            call, loadWord64_block_in_events(ctx), loadWord64_block_in_events(ctx + 0x28), 0, 0);
        float value;
        memcpy(&value, &angle, 4);
        value = _mm_cvtss_f32(
            _mm_div_ss(_mm_set_ss(value),
                       _mm_set_ss(loadFloat_block_in_events(image + Storage::nativeData_156870))));
        uint32_t bits;
        memcpy(&bits, &value, 4);
        bits = (uint32_t)nativeBoundary_b1fb0(call, bits, 0, 0, 0);
        memcpy(&value, &bits, 4);
        uint32_t n = (uint32_t)_mm_cvttss_si32(_mm_set_ss(value));
        uint32_t aligned = ((n & 0x80000000u) ? n + 3 : n) & ~3u;
        n -= aligned;
        memcpy(image + Storage::nativeData_304b18, &n, 4);
        return;
    }
    uint64_t keys[4];
    collect(ctx, keys, call);
    for (unsigned i = 0; i < 4; i++) {
        uint64_t game = loadWord64_block_in_events(ctx);
        uint32_t pressed = (uint32_t)physicalKeyWord(call, game, keys[i], 0, 0);
        setKeyDownRaw(call, game, keys[i], pressed, 0);
    }
}
API void onMovementCorrection(uint8_t *event, uint8_t *image, Dispatch call) {
    (void)call;
    if (image[Storage::nativeData_304b1c] != 1)
        return;
    event[8] = 1;
    event[9] = 1;
    if (loadWord32_block_in_events(image + Storage::nativeData_304b20) == 1)
        memcpy(event + 0xc, image + Storage::nativeData_304b28, 8);
}
API void onMovementInput(uint8_t *event, uint8_t *image, Dispatch call) {
    if (!loadWord32_block_in_events(image + Storage::nativeData_304b20))
        return;
    uint8_t *ctx = ptr(loadWord64_block_in_events(event + 8));
    uint64_t keys[4];
    collect(ctx, keys, call);
    setKeyDownRaw(call, loadWord64_block_in_events(ctx), keys[0],
                  loadWord32_block_in_events(image + Storage::nativeData_304b20) == 1, 0);
    for (unsigned i = 1; i < 4; i++)
        setKeyDownRaw(call, loadWord64_block_in_events(ctx), keys[i], 0, 0);
}

} // namespace reconstruction::Block_In
// END SOURCE modules/Block_In/block_in_events.cpp

// BEGIN SOURCE modules/Block_In/block_in_update.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_044269840BFEDE82917A
#define SLINKY_SHARE_044269840BFEDE82917A
// BEGIN SOURCE modules/Block_In/NativeRandom.hpp
// Native RNG contracts are implemented by the supplied shared clean bodies.
#include "../runtime/native/verified/module_random.hpp"
// END SOURCE modules/Block_In/NativeRandom.hpp

#endif // SLINKY_SHARE_044269840BFEDE82917A

#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
namespace reconstruction::Block_In {

using dependency = native_binding::WordEndpoints;
// Native entry 0xa510; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t smoothedRandomSample(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4, uint64_t a5) {
    return api(0xa510, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x22cf0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t clientOptions_block_in_update(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                              uint64_t a3, uint64_t a4, uint64_t a5) {
    return api(0x22cf0, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x23020; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_23020(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4, uint64_t a5) {
    return api(0x23020, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x23030; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityPosition(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                               uint64_t a4, uint64_t a5) {
    return api(0x23030, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x23170; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityRotation_block_in_update(dependency api, uint64_t a0, uint64_t a1,
                                               uint64_t a2, uint64_t a3, uint64_t a4, uint64_t a5) {
    return api(0x23170, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x23670; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityBoundingBox(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                  uint64_t a3, uint64_t a4, uint64_t a5) {
    return api(0x23670, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x23780; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityOnGround(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                               uint64_t a4, uint64_t a5) {
    return api(0x23780, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x23990; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_23990(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4, uint64_t a5) {
    return api(0x23990, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x24280; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_24280(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4, uint64_t a5) {
    return api(0x24280, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x242c0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_242c0(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4, uint64_t a5) {
    return api(0x242c0, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x24720; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_24720(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4, uint64_t a5) {
    return api(0x24720, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x24f90; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t useItemKey(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                           uint64_t a4, uint64_t a5) {
    return api(0x24f90, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x25380; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t pressKey(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                         uint64_t a4, uint64_t a5) {
    return api(0x25380, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x25540; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_25540(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4, uint64_t a5) {
    return api(0x25540, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x25640; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_25640(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4, uint64_t a5) {
    return api(0x25640, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x284f0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t scheduleModuleAction(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4, uint64_t a5) {
    return api(0x284f0, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x28a50; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t heldItem(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                         uint64_t a4, uint64_t a5) {
    return api(0x28a50, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x28b00; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t itemIsBlock(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                            uint64_t a4, uint64_t a5) {
    return api(0x28b00, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x29800; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t claimRotationPriority(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                      uint64_t a3, uint64_t a4, uint64_t a5) {
    return api(0x29800, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x29820; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t publishRotationDelta(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4, uint64_t a5) {
    return api(0x29820, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x29850; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t rotationOffset(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3,
                               uint64_t a4, uint64_t a5) {
    return api(0x29850, a0, a1, a2, a3, a4, a5);
}
// Native entry 0x2ade0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_2ade0(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3, uint64_t a4, uint64_t a5) {
    return api(0x2ade0, a0, a1, a2, a3, a4, a5);
}

static uint64_t loadWord64_block_in_update(const void *p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t loadWord32_block_in_update(const void *p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
static float loadFloat_block_in_update(const void *p) {
    float v;
    memcpy(&v, p, 4);
    return v;
}
static double loadDouble(const void *p) {
    double v;
    memcpy(&v, p, 8);
    return v;
}
static uint32_t floatBits(float v) {
    return loadWord32_block_in_update(&v);
}
static float floatFromWord(uint64_t v) {
    uint32_t b = (uint32_t)v;
    return loadFloat_block_in_update(&b);
}
static uint64_t pack(float a, float b) {
    return floatBits(a) | ((uint64_t)floatBits(b) << 32);
}
static void storeWord64(void *p, uint64_t v) {
    memcpy(p, &v, 8);
}
static void storeWord32(void *p, uint32_t v) {
    memcpy(p, &v, 4);
}
static float addFloatSse(float a, float b) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float subtractFloatSse(float a, float b) {
    return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static float multiplyFloatSse(float a, float b) {
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
static double addDoubleSse(double a, double b) {
    return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double subtractDoubleSse(double a, double b) {
    return _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double multiplyDoubleSse(double a, double b) {
    return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static float narrow(double v) {
    return _mm_cvtss_f32(_mm_cvtsd_ss(_mm_setzero_ps(), _mm_set_sd(v)));
}
static float intfloat(uint32_t v) {
    return _mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(), (int32_t)v));
}
static double intdouble(uint32_t v) {
    return (double)(int32_t)v;
}
static uint32_t trunc32(double v) {
    return (uint32_t)_mm_cvttsd_si32(_mm_set_sd(v));
}
static double absolute(double v, uint64_t mask) {
    uint64_t b = loadWord64_block_in_update(&v) & mask;
    return loadDouble(&b);
}

uint64_t recovered_angle_lerp_9e90(uint64_t a, uint64_t b, float t) {
    return pack(
        addFloatSse(multiplyFloatSse(subtractFloatSse(floatFromWord(b), floatFromWord(a)), t),
                    floatFromWord(a)),
        addFloatSse(
            multiplyFloatSse(subtractFloatSse(floatFromWord(b >> 32), floatFromWord(a >> 32)), t),
            floatFromWord(a >> 32)));
}
uint64_t block_in_lerp_adapter(uint8_t *event, uint8_t *image, dependency call) {
    (void)image;
    (void)call;
    return recovered_angle_lerp_9e90(loadWord64_block_in_update(event),
                                     loadWord64_block_in_update(event + 8),
                                     loadFloat_block_in_update(event + 16));
}

static float smooth(uint8_t *image, dependency call, uint32_t state, uint64_t bounds,
                    uint64_t period) {
    return floatFromWord(
        smoothedRandomSample(call, (uintptr_t)(image + state), bounds, period, 0, 0, 0));
}
static double library_double(dependency call, uint32_t r, double a, double b) {
    uint64_t result =
        call(r, loadWord64_block_in_update(&a), loadWord64_block_in_update(&b), 0, 0, 0, 0);
    return loadDouble(&result);
}
static int allowed(uint8_t *ctx, dependency call, uint64_t cache, uint32_t x, uint32_t y,
                   uint32_t z) {
    uint64_t block = nativeBoundary_24720(call, loadWord64_block_in_update(ctx),
                                          loadWord64_block_in_update(ctx + 0x20), cache, x, y, z);
    uint32_t type =
        (uint32_t)nativeBoundary_24280(call, loadWord64_block_in_update(ctx), block, 0, 0, 0, 0);
    return type <= 31 && ((UINT32_C(0x80000301) >> type) & 1);
}
static int centered(const double *self, uint8_t *image, dependency call) {
    double sx = self[0], sz = self[2], one = loadDouble(image + Storage::nativeData_1568c0);
    double ax = library_double(call, 0xb2170, sx, one);
    uint64_t mask = loadWord64_block_in_update(image + Storage::nativeData_156890);
    ax = absolute(ax, mask);
    double az = library_double(call, 0xb2170, sz, one);
    double upper = loadDouble(image + Storage::nativeData_1568c8),
           lower = loadDouble(image + Storage::nativeData_1568d0);
    az = absolute(az, mask);
    return upper >= ax && ax >= lower && az >= lower && upper >= az;
}
static void update(uint8_t *event, uint8_t *image, dependency call) {
    image[Storage::nativeData_304b1c] = 0;
    storeWord32(image + Storage::nativeData_304b20, 0);
    uint8_t *ctx = (uint8_t *)(uintptr_t)loadWord64_block_in_update(event + 8);
    {
        if (ctx[0x40] != 1)
            goto cleanup;
        uint8_t ground =
            (uint8_t)entityOnGround(call, loadWord64_block_in_update(ctx),
                                    loadWord64_block_in_update(ctx + 0x28), 0, 0, 0, 0);
        if (!((~image[Storage::require_groundCurrent] | ground) & 1))
            goto cleanup;
        double self[3];
        entityPosition(call, (uintptr_t)self, loadWord64_block_in_update(ctx),
                       loadWord64_block_in_update(ctx + 0x28), 0, 0, 0);
        if ((uint8_t)nativeBoundary_23020(call, loadWord64_block_in_update(ctx), 0, 0, 0, 0, 0)) {
            double copy[3];
            memcpy(copy, self, 24);
            recovered_vector_adjust_95c0(self, copy, image);
        }
        double selfy = self[1], fx = library_double(call, 0xb29b0, self[0], 0.);
        double fy = addDoubleSse(library_double(call, 0xb29b0, selfy, 0.),
                                 loadDouble(image + Storage::nativeData_156880));
        double fz = library_double(call, 0xb29b0, self[2], 0.);
        if (absolute(subtractDoubleSse(selfy, loadDouble(image + Storage::nativeData_304b30)),
                     loadWord64_block_in_update(image + Storage::nativeData_156890)) >
            loadDouble(image + Storage::nativeData_1568a0))
            storeWord64(image + Storage::nativeData_304b10, 0);
        uint32_t x = trunc32(fx), y = trunc32(fy), z = trunc32(fz);
        storeWord64(image + Storage::nativeData_304b30, loadWord64_block_in_update(&selfy));
        uint64_t cache = 0, game = loadWord64_block_in_update(ctx);
        if (loadWord32_block_in_update(
                (void *)(uintptr_t)loadWord64_block_in_update((void *)(uintptr_t)game)))
            cache = nativeBoundary_242c0(call, game, 0, 0, 0, 0, 0);
        unsigned probe;
        for (probe = 0; probe < 10; probe++) {
            if ((loadWord64_block_in_update(image + Storage::nativeData_304b10) >> probe) &
                UINT64_C(0x100000000))
                break;
            const int8_t *offset = (const int8_t *)(image + Storage::nativeData_156b80 + probe * 3);
            if (!allowed(ctx, call, cache, x + (uint32_t)offset[0], y + (uint32_t)offset[1],
                         z + (uint32_t)offset[2]))
                break;
        }
        double target[3];
        unsigned bit;
        if (probe == 0 || probe == 10) {
            double size[3] = {loadDouble(image + Storage::nativeData_156ba8),
                              loadDouble(image + Storage::nativeData_156bb0), 1.};
            for (unsigned attempt = 0; attempt < 4; attempt++) {
                unsigned dir =
                    (loadWord32_block_in_update(image + Storage::nativeData_304b18) + attempt) & 3;
                int8_t dx = (int8_t)image[Storage::nativeData_156b9e + dir * 2],
                       dz = (int8_t)image[Storage::nativeData_156b9f + dir * 2];
                uint64_t captured_game = loadWord64_block_in_update(ctx),
                         box_object =
                             entityBoundingBox(call, captured_game,
                                               loadWord64_block_in_update(ctx + 0x28), 0, 0, 0, 0);
                double playerbox[6];
                nativeBoundary_25640(call, (uintptr_t)playerbox, captured_game, box_object, 0, 0,
                                     0);
                uint32_t nx = x + (uint32_t)dx, nz = z + (uint32_t)dz;
                double base[3] = {intdouble(nx), intdouble(y), intdouble(nz)}, end[3], box[6];
                recovered_geometry_add_9400(end, base, size);
                recovered_geometry_pair_96b0(box, base, end);
                if (recovered_geometry_intersects_97d0(playerbox, box))
                    continue;
                unsigned level;
                for (level = 0; level < 3; level++) {
                    if ((loadWord32_block_in_update(image + Storage::nativeData_304b10) >>
                         ((dir * 3 + level) & 31)) &
                        1)
                        continue;
                    if (allowed(ctx, call, cache, nx, y + level, nz) &&
                        !allowed(ctx, call, cache, nx, y + level - 1, nz))
                        break;
                }
                if (level == 3)
                    continue;
                uint32_t bounds_rva =
                    level ? Storage::nativeData_1568b0 : Storage::nativeData_1568a8;
                uint64_t bounds =
                    recovered_random_bounds(loadFloat_block_in_update(image + bounds_rva),
                                            loadFloat_block_in_update(image + bounds_rva + 4));
                uint64_t period = loadWord64_block_in_update(image + Storage::nativeData_1568b8);
                double half = loadDouble(&period);
                float a = smooth(image, call, Storage::nativeData_304b58, bounds, period);
                double tx = subtractDoubleSse(half, (double)multiplyFloatSse(a, (float)dx));
                float b = smooth(image, call, Storage::nativeData_304b68, bounds, period);
                double tz = subtractDoubleSse(half, (double)multiplyFloatSse(b, (float)dz));
                target[0] = addDoubleSse(tx, intdouble(nx));
                target[1] = intdouble(y + level);
                target[2] = addDoubleSse(tz, intdouble(nz));
                bit = dir * 3 + level;
                goto aim;
            }
            if ((ground & 1) && centered(self, image, call))
                goto cleanup;
            return;
        }
        {
            bit = 32 + (probe >= 5 && probe <= 8 ? probe - 4 : 0);
            unsigned direct = probe >= 5 && probe <= 8 ? probe - 4 : probe;
            if (direct == 1 || direct == 3) {
                target[0] = intdouble(x + (direct == 3));
                float yfloat = intfloat(y);
                uint64_t bounds = recovered_random_bounds(
                    loadFloat_block_in_update(image + Storage::nativeData_1568e4),
                    loadFloat_block_in_update(image + Storage::nativeData_1568e8));
                uint64_t period = loadWord64_block_in_update(image + Storage::nativeData_1568b8);
                target[1] = (double)addFloatSse(
                    smooth(image, call, Storage::nativeData_304b38, bounds, period), yfloat);
                float zfloat = intfloat(z);
                uint32_t r = direct == 1 ? Storage::nativeData_1568dc : Storage::nativeData_1568ec;
                bounds = recovered_random_bounds(loadFloat_block_in_update(image + r),
                                                 loadFloat_block_in_update(image + r + 4));
                target[2] = (double)addFloatSse(
                    smooth(image, call, Storage::nativeData_304b48, bounds, period), zfloat);
            } else if (direct == 2 || direct == 4) {
                float xfloat = intfloat(x), yfloat = intfloat(y);
                uint32_t r = direct == 2 ? Storage::nativeData_1568ec : Storage::nativeData_1568dc;
                uint64_t bounds = recovered_random_bounds(loadFloat_block_in_update(image + r),
                                                          loadFloat_block_in_update(image + r + 4));
                uint64_t period = loadWord64_block_in_update(image + Storage::nativeData_1568b8);
                float a = smooth(image, call, Storage::nativeData_304b38, bounds, period);
                bounds = recovered_random_bounds(
                    loadFloat_block_in_update(image + Storage::nativeData_1568e4),
                    loadFloat_block_in_update(image + Storage::nativeData_1568e8));
                float b = smooth(image, call, Storage::nativeData_304b48, bounds, period);
                target[0] = (double)addFloatSse(a, xfloat);
                target[1] = (double)addFloatSse(b, yfloat);
                target[2] = intdouble(z + (direct == 4));
            } else {
                float xfloat = intfloat(x),
                      lo = loadFloat_block_in_update(image + Storage::nativeData_1568b4),
                      hi = loadFloat_block_in_update(image + Storage::nativeData_1568d8);
                uint64_t bounds = recovered_random_bounds(lo, hi),
                         period = loadWord64_block_in_update(image + Storage::nativeData_1568b8);
                target[0] = (double)addFloatSse(
                    smooth(image, call, Storage::nativeData_304b38, bounds, period), xfloat);
                target[1] = intdouble(y + 4);
                float zfloat = intfloat(z);
                bounds = recovered_random_bounds(lo, hi);
                target[2] = (double)addFloatSse(
                    smooth(image, call, Storage::nativeData_304b48, bounds, period), zfloat);
            }
        }
    aim:
        if (!(uint8_t)claimRotationPriority(call, 500, 0, 0, 0, 0, 0))
            goto cleanup;
        nativeBoundary_2ade0(call, (uintptr_t)ctx, (uintptr_t)(image + Storage::moduleDescriptor),
                             1, reinterpret_cast<uintptr_t>(&native_state::blockInItemRank), 0, 0);
        uint64_t item = heldItem(call, loadWord64_block_in_update(ctx),
                                 loadWord64_block_in_update(ctx + 0x28), 0, 0, 0, 0);
        if (!(uint8_t)itemIsBlock(call, loadWord64_block_in_update(ctx), item, 0, 0, 0, 0))
            goto cleanup;
        uint64_t angle = entityRotation_block_in_update(call, loadWord64_block_in_update(ctx),
                                                        loadWord64_block_in_update(ctx + 0x28), 0,
                                                        0, 0, 0),
                 offset = rotationOffset(call, 0, 0, 0, 0, 0, 0);
        uint64_t combined = call(0x9de0, angle, offset, 0, 0, 0, 0);
        uint64_t position =
            nativeBoundary_23990(call, loadWord64_block_in_update(ctx),
                                 loadWord64_block_in_update(ctx + 0x28), 0, 0, 0, 0);
        double eye[3];
        nativeBoundary_25540(call, (uintptr_t)eye, loadWord64_block_in_update(ctx), position, 0, 0,
                             0);
        uint64_t desired = call(0x9f80, uintptr_t(eye), uintptr_t(target), 0, 0, 0, 0);
        uint64_t delta = call(0x9e20, desired, combined, 0, 0, 0, 0);
        float pitch = floatFromWord(delta >> 32),
              yaw = floatFromWord(call(0xa210, uint32_t(delta), 0, 0, 0, 0, 0));
        double half = loadDouble(image + Storage::nativeData_1568b8);
        float factor = narrow(addDoubleSse(
            multiplyDoubleSse((double)loadFloat_block_in_update(image + Storage::speedCurrent),
                              half),
            half));
        uint64_t scaled = recovered_angle_scale_9e60(pack(yaw, pitch), factor);
        float lo = loadFloat_block_in_update(image + Storage::nativeData_1568f4),
              hi = loadFloat_block_in_update(image + Storage::nativeData_1568f0);
        uint64_t bounds = recovered_random_bounds(lo, hi),
                 period = loadWord64_block_in_update(image + Storage::nativeData_1568f8);
        float rx = smooth(image, call, Storage::nativeData_304b78, bounds, period);
        bounds = recovered_random_bounds(lo, hi);
        float ry = smooth(image, call, Storage::nativeData_304b88, bounds, period);
        float rate = loadFloat_block_in_update(image + Storage::nativeData_156900);
        rx = multiplyFloatSse(rx, rate);
        float setting = loadFloat_block_in_update(image + Storage::speedCurrent);
        rx = multiplyFloatSse(rx, setting);
        ry = multiplyFloatSse(multiplyFloatSse(rate, ry), setting);
        uint32_t sign = loadWord32_block_in_update(image + Storage::nativeData_156910);
        float cx = recovered_float_clamp_a1f0(floatFromWord(floatBits(rx) ^ sign), rx, yaw),
              cy = recovered_float_clamp_a1f0(floatFromWord(sign ^ floatBits(ry)), ry, pitch);
        uint64_t result = recovered_angle_lerp_9e90(
            scaled, pack(cx, cy), loadFloat_block_in_update(image + Storage::nativeData_156920));
        publishRotationDelta(call, result, 0, 0, 0, 0, 0);
        uint32_t mask = loadWord32_block_in_update(image + Storage::nativeData_156930);
        float ax = floatFromWord(floatBits(subtractFloatSse(yaw, floatFromWord(result))) & mask),
              ay = floatFromWord(floatBits(subtractFloatSse(pitch, floatFromWord(result >> 32))) &
                                 mask);
        if (loadFloat_block_in_update(image + Storage::nativeData_156940) > addFloatSse(ay, ax)) {
            uint64_t a =
                clientOptions_block_in_update(call, loadWord64_block_in_update(ctx),
                                              loadWord64_block_in_update(ctx + 0x18), 0, 0, 0, 0);
            a = useItemKey(call, loadWord64_block_in_update(ctx), a, 0, 0, 0, 0);
            pressKey(call, loadWord64_block_in_update(ctx), a, 0, 0, 0, 0);
            storeWord64(image + Storage::nativeData_304b10,
                        loadWord64_block_in_update(image + Storage::nativeData_304b10) |
                            (UINT64_C(1) << (bit & 63)));
        }
        image[Storage::nativeData_304b1c] = 1;
        double sx = self[0], sz = self[2];
        if (centered(self, image, call)) {
            storeWord32(image + Storage::nativeData_304b20, 2);
            return;
        }
        double center[3];
        center[0] = addDoubleSse(library_double(call, 0xb29b0, sx, 0.), half);
        center[1] = self[1];
        center[2] = addDoubleSse(library_double(call, 0xb29b0, sz, 0.), half);
        storeWord32(image + Storage::nativeData_304b20, 1);
        storeWord64(image + Storage::nativeData_304b28,
                    call(0x9f80, uintptr_t(self), uintptr_t(center), 0, 0, 0, 0));
        return;
    }
cleanup:
    scheduleModuleAction(call, loadWord64_block_in_update(ctx + 8),
                         (uintptr_t)(image + Storage::moduleDescriptor), 0, 0, 0, 0);
}
void updatePlacementRotation(uint8_t *event, uint8_t *image, dependency call) {
    update(event, image, call);
}

} // namespace reconstruction::Block_In
// END SOURCE modules/Block_In/block_in_update.cpp

// Convenient borrowed-state interface

namespace shareable {
class BlockIn {
  public:
    static constexpr const char *kName = "Block In";
    static constexpr const char *kDescription = "Places blocks around you.";
    explicit BlockIn(std::uint8_t *image) : image_(image) {}
    // Speed. Config key: speed.
    NumberSetting &speed() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f6338);
    }
    // On ground. Config key: require_ground.
    BooleanSetting &require_ground() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f6318);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_block_in_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_block_in_settings(&context, image_, &dependencies);
    }
    static uint64_t angleLerp9E90(uint64_t a, uint64_t b, float t) {
        return ::reconstruction::Block_In::recovered_angle_lerp_9e90(a, b, t);
    }
    uint64_t block_in_lerp_adapter(uint8_t *event, ::reconstruction::Block_In::dependency call) {
        return ::reconstruction::Block_In::block_in_lerp_adapter(event, image_, call);
    }
    void updatePlacementRotation(uint8_t *event, ::reconstruction::Block_In::dependency call) {
        ::reconstruction::Block_In::updatePlacementRotation(event, image_, call);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
