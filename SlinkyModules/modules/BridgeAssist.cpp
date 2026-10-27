// Bridge Assist

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Bridge_Assist.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Bridge_Assist.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Bridge Assist: lib_win settings 0x2e6c0.
// UI 0x2e5d0.
static constexpr UiStep ui_steps_Surface_Bridge_Assist[] = {
    {UiControl::section, "Main", 0},          {UiControl::number, nullptr, 0x2e9dc8},
    {UiControl::number, nullptr, 0x2e9e40},   {UiControl::choice, nullptr, 0x2e9d48},
    {UiControl::checkbox, nullptr, 0x2e9e00}, {UiControl::checkbox, nullptr, 0x2e9da8},
    {UiControl::checkbox, nullptr, 0x2e9e20}, {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2e9cd0}, {UiControl::checkbox, nullptr, 0x2e9d88},
    {UiControl::checkbox, nullptr, 0x2e9cf0}, {UiControl::checkbox, nullptr, 0x2e9d10},
};
static constexpr SettingsStep settings_steps_Surface_Bridge_Assist[] = {
    {SettingsControl::number, "edge_offset", 0x2e9dc8},
    {SettingsControl::number, "unsneak_delay", 0x2e9e40},
    {SettingsControl::choice, "select_blocks", 0x2e9d48},
    {SettingsControl::boolean, "randomize", 0x2e9e00},
    {SettingsControl::boolean, "sneak_on_jump", 0x2e9da8},
    {SettingsControl::boolean, "avoid_double_sneak", 0x2e9e20},
    {SettingsControl::boolean, "require_sneak", 0x2e9cd0},
    {SettingsControl::boolean, "require_holding_blocks", 0x2e9d88},
    {SettingsControl::boolean, "require_looking_down", 0x2e9cf0},
    {SettingsControl::boolean, "require_not_forward", 0x2e9d10},
};
static constexpr ModuleSurface surface_Surface_Bridge_Assist{
    ui_steps_Surface_Bridge_Assist, std::size(ui_steps_Surface_Bridge_Assist),
    settings_steps_Surface_Bridge_Assist, std::size(settings_steps_Surface_Bridge_Assist)};

extern "C" __declspec(dllexport) void
recovered_bridge_assist_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                           const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Bridge_Assist, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_bridge_assist_settings(SettingsContext *context, std::uint8_t *image,
                                 const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Bridge_Assist, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Bridge_Assist.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Bridge_Assist/bridge_events.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_E821A7064FCF3A6B3EB8
#define SLINKY_SHARE_E821A7064FCF3A6B3EB8
// BEGIN SOURCE modules/Bridge_Assist/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Bridge_Assist {
namespace Storage {
inline constexpr std::uint32_t nativeData_150760 = 0x150760;
inline constexpr std::uint32_t nativeData_150770 = 0x150770;
inline constexpr std::uint32_t nativeData_150780 = 0x150780;
inline constexpr std::uint32_t nativeData_150784 = 0x150784;
inline constexpr std::uint32_t nativeData_150790 = 0x150790;
inline constexpr std::uint32_t nativeData_1507a0 = 0x1507a0;
inline constexpr std::uint32_t nativeData_1507a8 = 0x1507a8;
inline constexpr std::uint32_t nativeData_1507b0 = 0x1507b0;
inline constexpr std::uint32_t nativeData_1507b8 = 0x1507b8;
inline constexpr std::uint32_t nativeData_1507c0 = 0x1507c0;
inline constexpr std::uint32_t nativeData_1507c4 = 0x1507c4;
inline constexpr std::uint32_t nativeData_1507c8 = 0x1507c8;
inline constexpr std::uint32_t nativeData_1507cc = 0x1507cc;
inline constexpr std::uint32_t nativeData_1507d0 = 0x1507d0;
inline constexpr std::uint32_t nativeData_1507d8 = 0x1507d8;
inline constexpr std::uint32_t nativeData_1507dc = 0x1507dc;
inline constexpr std::uint32_t nativeData_1507e0 = 0x1507e0;
inline constexpr std::uint32_t nativeData_1507e8 = 0x1507e8;
inline constexpr std::uint32_t moduleDescriptor = 0x2e9ac0;
inline constexpr std::uint32_t require_sneakRecord = 0x2e9cd0;
inline constexpr std::uint32_t require_sneakCurrent = 0x2e9ce8;
inline constexpr std::uint32_t require_looking_downRecord = 0x2e9cf0;
inline constexpr std::uint32_t require_looking_downCurrent = 0x2e9d08;
inline constexpr std::uint32_t require_not_forwardRecord = 0x2e9d10;
inline constexpr std::uint32_t require_not_forwardCurrent = 0x2e9d28;
inline constexpr std::uint32_t select_blocksRecord = 0x2e9d48;
inline constexpr std::uint32_t select_blocksCurrent = 0x2e9d78;
inline constexpr std::uint32_t require_holding_blocksRecord = 0x2e9d88;
inline constexpr std::uint32_t require_holding_blocksCurrent = 0x2e9da0;
inline constexpr std::uint32_t sneak_on_jumpRecord = 0x2e9da8;
inline constexpr std::uint32_t sneak_on_jumpCurrent = 0x2e9dc0;
inline constexpr std::uint32_t edge_offsetRecord = 0x2e9dc8;
inline constexpr std::uint32_t edge_offsetCurrent = 0x2e9df8;
inline constexpr std::uint32_t randomizeRecord = 0x2e9e00;
inline constexpr std::uint32_t randomizeCurrent = 0x2e9e18;
inline constexpr std::uint32_t avoid_double_sneakRecord = 0x2e9e20;
inline constexpr std::uint32_t avoid_double_sneakCurrent = 0x2e9e38;
inline constexpr std::uint32_t unsneak_delayRecord = 0x2e9e40;
inline constexpr std::uint32_t unsneak_delayCurrent = 0x2e9e70;
inline constexpr std::uint32_t sneakStateOwned = 0x2f7dc8;
inline constexpr std::uint32_t placementCooldown = 0x2f7dcc;
inline constexpr std::uint32_t placementInputGate = 0x2f7dd0;
inline constexpr std::uint32_t placementActionGate = 0x2f7dd1;
inline constexpr std::uint32_t unsneakCountdown = 0x2f7dd4;
inline constexpr std::uint32_t heldBlockGraceTicks = 0x2f7dd8;
inline constexpr std::uint32_t nativeData_2f7df0 = 0x2f7df0;
inline constexpr std::uint32_t nativeData_2f7e00 = 0x2f7e00;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &edge_offset() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::edge_offsetRecord);
    }
    NumberSetting &unsneak_delay() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::unsneak_delayRecord);
    }
    ChoiceSetting &select_blocks() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::select_blocksRecord);
    }
    BooleanSetting &randomize() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::randomizeRecord);
    }
    BooleanSetting &sneak_on_jump() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::sneak_on_jumpRecord);
    }
    BooleanSetting &avoid_double_sneak() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::avoid_double_sneakRecord);
    }
    BooleanSetting &require_sneak() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_sneakRecord);
    }
    BooleanSetting &require_holding_blocks() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_holding_blocksRecord);
    }
    BooleanSetting &require_looking_down() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_looking_downRecord);
    }
    BooleanSetting &require_not_forward() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_not_forwardRecord);
    }
};
// Runtime-observed native labels for config key "select_blocks". Numeric values preserved.
enum class Select_blocksMode : std::uint32_t {
    No = 0,
    On_depletion = 1,
    Always = 2,
};
} // namespace reconstruction::Bridge_Assist
// END SOURCE modules/Bridge_Assist/Settings.hpp

#endif // SLINKY_SHARE_E821A7064FCF3A6B3EB8

#include <stdint.h>
#include <string.h>
namespace reconstruction::Bridge_Assist {
using dependency = native_binding::WordEndpoints;
// Native entry 0x22cf0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t clientOptions_bridge_events(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                            uint64_t a3) {
    return api(0x22cf0, a0, a1, a2, a3);
}
// Native entry 0x22e10; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t currentHitResult(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                 uint64_t a3) {
    return api(0x22e10, a0, a1, a2, a3);
}
// Native entry 0x23020; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_23020(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x23020, a0, a1, a2, a3);
}
// Native entry 0x23030; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityPosition(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x23030, a0, a1, a2, a3);
}
// Native entry 0x23170; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityRotation_bridge_events(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                             uint64_t a3) {
    return api(0x23170, a0, a1, a2, a3);
}
// Native entry 0x23780; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityOnGround_bridge_events(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                             uint64_t a3) {
    return api(0x23780, a0, a1, a2, a3);
}
// Native entry 0x24b50; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t hitResultType(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x24b50, a0, a1, a2, a3);
}
// Native entry 0x24b90; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t hitResultFace(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x24b90, a0, a1, a2, a3);
}
// Native entry 0x24bf0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_24bf0(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x24bf0, a0, a1, a2, a3);
}
// Native entry 0x24d80; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t hitPosition(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x24d80, a0, a1, a2, a3);
}
// Native entry 0x25030; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t sneakKey_bridge_events(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                       uint64_t a3) {
    return api(0x25030, a0, a1, a2, a3);
}
// Native entry 0x25120; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t forwardKey(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x25120, a0, a1, a2, a3);
}
// Native entry 0x25170; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t leftKey(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x25170, a0, a1, a2, a3);
}
// Native entry 0x251c0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t rightKey(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x251c0, a0, a1, a2, a3);
}
// Native entry 0x25430; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t keyDown_bridge_events(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                      uint64_t a3) {
    return api(0x25430, a0, a1, a2, a3);
}
// Native entry 0x25460; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t setKeyDownRaw_bridge_events(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                            uint64_t a3) {
    return api(0x25460, a0, a1, a2, a3);
}
// Native entry 0x25490; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t physicalKeyWord_bridge_events(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                              uint64_t a3) {
    return api(0x25490, a0, a1, a2, a3);
}
// Native entry 0x25540; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_25540(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x25540, a0, a1, a2, a3);
}
// Native entry 0x28a50; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t heldItem_bridge_events(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                       uint64_t a3) {
    return api(0x28a50, a0, a1, a2, a3);
}
// Native entry 0x28b00; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t itemIsBlock_bridge_events(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                          uint64_t a3) {
    return api(0x28b00, a0, a1, a2, a3);
}
// Native entry 0x2af50; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_2af50(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x2af50, a0, a1, a2, a3);
}
// Native entry 0xb2170; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t binary64Remainder(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                  uint64_t a3) {
    return api(0xb2170, a0, a1, a2, a3);
}

static uint64_t u64_bridge_events(const void *p) {
    return *(const volatile uint64_t *)p;
}
static uint32_t u32_bridge_events(const void *p) {
    return *(const volatile uint32_t *)p;
}
static double d64(uint64_t b) {
    double v;
    memcpy(&v, &b, 8);
    return v;
}
static float f32_bridge_events(uint32_t b) {
    float v;
    memcpy(&v, &b, 4);
    return v;
}
static uint64_t db(double v) {
    uint64_t b;
    memcpy(&b, &v, 8);
    return b;
}
static uint32_t floatBits_bridge_events(float v) {
    uint32_t b;
    memcpy(&b, &v, 4);
    return b;
}
static double absolute(double v, uint8_t *image) {
    return d64(db(v) & u64_bridge_events(image + Storage::nativeData_150790));
}

void onModuleStateChanged(uint8_t *event, uint8_t *image, dependency call) {
    if (u64_bridge_events(event + 0x10) != (uintptr_t)(image + Storage::moduleDescriptor) ||
        event[0x18] || !(image[Storage::sneakStateOwned] & 1))
        return;
    uint8_t *ctx = (uint8_t *)(uintptr_t)u64_bridge_events(event + 8);
    uint64_t settings = clientOptions_bridge_events(call, u64_bridge_events(ctx),
                                                    u64_bridge_events(ctx + 0x18), 0, 0);
    uint64_t key = sneakKey_bridge_events(call, u64_bridge_events(ctx), settings, 0, 0);
    uint32_t pressed =
        (uint32_t)physicalKeyWord_bridge_events(call, u64_bridge_events(ctx), key, 0, 0);
    setKeyDownRaw_bridge_events(call, u64_bridge_events(ctx), key, pressed, 0);
    image[Storage::sneakStateOwned] = 0;
}

void onPlacementAction(uint8_t *event, uint8_t *image, dependency call) {
    if (image[Storage::placementActionGate] == 1)
        nativeBoundary_2af50(call, u64_bridge_events(event + 8),
                             (uintptr_t)(image + Storage::moduleDescriptor),
                             u32_bridge_events(image + Storage::select_blocksCurrent) == 2, 0);
}

void filterPlacementInput(uint8_t *event, uint8_t *image, dependency call) {
    if (event[0x10] || u32_bridge_events(image + Storage::placementCooldown) == 20)
        return;
    uint8_t *ctx = (uint8_t *)(uintptr_t)u64_bridge_events(event + 8);
    {
        if (image[Storage::placementInputGate] != 1)
            goto fallback;
        uint64_t hit =
            currentHitResult(call, u64_bridge_events(ctx), u64_bridge_events(ctx + 0x18), 0, 0);
        if (!hit)
            goto fallback;
        if ((uint32_t)hitResultType(call, u64_bridge_events(ctx), hit, 0, 0) != 1)
            goto fallback;
        if ((uint32_t)hitResultFace(call, u64_bridge_events(ctx), hit, 0, 0) < 2)
            goto fallback;
        if (!(uint8_t)entityOnGround_bridge_events(call, u64_bridge_events(ctx),
                                                   u64_bridge_events(ctx + 0x28), 0, 0))
            goto fallback;
        uint64_t settings = clientOptions_bridge_events(call, u64_bridge_events(ctx),
                                                        u64_bridge_events(ctx + 0x18), 0, 0);
        uint64_t forward = forwardKey(call, u64_bridge_events(ctx), settings, 0, 0);
        uint64_t left = leftKey(call, u64_bridge_events(ctx), settings, 0, 0);
        uint64_t right = rightKey(call, u64_bridge_events(ctx), settings, 0, 0);
        if (!(uint8_t)keyDown_bridge_events(call, u64_bridge_events(ctx), forward, 0, 0))
            goto fallback;
        if ((uint8_t)keyDown_bridge_events(call, u64_bridge_events(ctx), left, 0, 0))
            goto fallback;
        if ((uint8_t)keyDown_bridge_events(call, u64_bridge_events(ctx), right, 0, 0))
            goto fallback;
        uint64_t packed = entityRotation_bridge_events(call, u64_bridge_events(ctx),
                                                       u64_bridge_events(ctx + 0x28), 0, 0);
        double angle =
            d64(binary64Remainder(call, db((double)f32_bridge_events((uint32_t)packed)),
                                  u64_bridge_events(image + Storage::nativeData_150760), 0, 0));
        float folded = f32_bridge_events(floatBits_bridge_events((float)angle) &
                                         u32_bridge_events(image + Storage::nativeData_150770));
        if (f32_bridge_events(u32_bridge_events(image + Storage::nativeData_150780)) > folded ||
            folded > f32_bridge_events(u32_bridge_events(image + Storage::nativeData_150784)))
            goto fallback;
        double self[3], point[3], block[3];
        entityPosition(call, (uintptr_t)self, u64_bridge_events(ctx), u64_bridge_events(ctx + 0x28),
                       0);
        if ((uint8_t)nativeBoundary_23020(call, u64_bridge_events(ctx), 0, 0, 0)) {
            double copy[3], adjusted[3];
            memcpy(copy, self, 24);
            recovered_vector_adjust_95c0(adjusted, copy, image);
            memcpy(self, adjusted, 24);
        }
        uint64_t object = nativeBoundary_24bf0(call, u64_bridge_events(ctx), hit, 0, 0);
        nativeBoundary_25540(call, (uintptr_t)point, u64_bridge_events(ctx), object, 0);
        if (absolute(point[0] - self[0], image) >
            d64(u64_bridge_events(image + Storage::nativeData_1507a0)))
            goto fallback;
        double dy = point[1] - self[1];
        if (d64(u64_bridge_events(image + Storage::nativeData_1507a8)) > dy || dy > 0.)
            goto fallback;
        if (absolute(point[2] - self[2], image) >
            d64(u64_bridge_events(image + Storage::nativeData_1507a0)))
            goto fallback;
        hitPosition(call, (uintptr_t)block, u64_bridge_events(ctx), hit, 0);
        double unit = d64(u64_bridge_events(image + Storage::nativeData_1507a0));
        uint8_t inside_z = block[2] < self[2] && self[2] < block[2] + unit;
        double end_x = block[0] + unit;
        double rx = absolute(d64(binary64Remainder(call, db(point[0]), db(unit), 0, 0)), image);
        double rz = d64(binary64Remainder(call, db(point[2]), db(unit), 0, 0));
        double margin = d64(u64_bridge_events(image + Storage::nativeData_1507b8));
        if (block[0] < self[0] && self[0] < end_x && inside_z)
            margin = d64(u64_bridge_events(image + Storage::nativeData_1507b0));
        double upper = unit - margin;
        if (!(upper < rx) && !(rx < margin))
            goto cancel;
        rz = absolute(rz, image);
        if (!(upper < rz) && !(rz < margin))
            goto cancel;
    }
fallback: {
    uint64_t object =
        heldItem_bridge_events(call, u64_bridge_events(ctx), u64_bridge_events(ctx + 0x28), 0, 0);
    if ((uint8_t)itemIsBlock_bridge_events(call, u64_bridge_events(ctx), object, 0, 0))
        *(volatile uint32_t *)(image + Storage::placementCooldown) = 20;
}
    return;
cancel:
    event[0x11] = 1;
}

} // namespace reconstruction::Bridge_Assist
// END SOURCE modules/Bridge_Assist/bridge_events.cpp

// BEGIN SOURCE modules/Bridge_Assist/bridge_update.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"

#ifndef SLINKY_SHARE_CD64DB488C387F810C07
#define SLINKY_SHARE_CD64DB488C387F810C07
// BEGIN SOURCE modules/Bridge_Assist/SpatialBoundary.hpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#include <cstdint>
namespace reconstruction::Bridge_Assist {
// Typed calls preserve the fifth native stack argument omitted by the old test
// adapter. Both targets now call concrete recovered bodies with borrowed state.
struct SpatialBoundary {
    native_binding::Context &native;
    void movementVector(double *out, std::uint64_t rotation, float forward, float strafe,
                        float speed) const {
        native_state::movementVector(out, rotation, forward, strafe, speed, native.image);
    }
    std::uint64_t worldBlockAt(std::uint64_t game, std::uint64_t world, std::int32_t x,
                               std::int32_t y, std::int32_t z) const {
        return game_access::worldBlockAt(
            reinterpret_cast<GameAccessBridge *>(game), world, std::bit_cast<std::uint32_t>(x),
            std::bit_cast<std::uint32_t>(y), std::bit_cast<std::uint32_t>(z));
    }
};
} // namespace reconstruction::Bridge_Assist
// END SOURCE modules/Bridge_Assist/SpatialBoundary.hpp

#endif // SLINKY_SHARE_CD64DB488C387F810C07

#include <emmintrin.h>
#include <stdint.h>
#include <string.h>
namespace reconstruction::Bridge_Assist {
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
static uint64_t clientOptions_bridge_update(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                            uint64_t a3) {
    return api(0x22cf0, a0, a1, a2, a3);
}
// Native entry 0x23170; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityRotation_bridge_update(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                             uint64_t a3) {
    return api(0x23170, a0, a1, a2, a3);
}
// Native entry 0x23550; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityVelocity(dependency api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x23550, a0, a1, a2, a3);
}
// Native entry 0x23780; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityOnGround_bridge_update(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                             uint64_t a3) {
    return api(0x23780, a0, a1, a2, a3);
}
// Native entry 0x23ac0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_23ac0(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x23ac0, a0, a1, a2, a3);
}
// Native entry 0x25030; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t sneakKey_bridge_update(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                       uint64_t a3) {
    return api(0x25030, a0, a1, a2, a3);
}
// Native entry 0x25430; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t keyDown_bridge_update(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                      uint64_t a3) {
    return api(0x25430, a0, a1, a2, a3);
}
// Native entry 0x25460; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t setKeyDownRaw_bridge_update(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                            uint64_t a3) {
    return api(0x25460, a0, a1, a2, a3);
}
// Native entry 0x25490; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t physicalKeyWord_bridge_update(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                              uint64_t a3) {
    return api(0x25490, a0, a1, a2, a3);
}
// Native entry 0x28a50; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t heldItem_bridge_update(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                       uint64_t a3) {
    return api(0x28a50, a0, a1, a2, a3);
}
// Native entry 0x28b00; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t itemIsBlock_bridge_update(dependency api, uint64_t a0, uint64_t a1, uint64_t a2,
                                          uint64_t a3) {
    return api(0x28b00, a0, a1, a2, a3);
}

static uint64_t u64_bridge_update(const void *p) {
    return *(const volatile uint64_t *)p;
}
static uint32_t u32_bridge_update(const void *p) {
    return *(const volatile uint32_t *)p;
}
static int32_t s32(uint32_t b) {
    int32_t v;
    memcpy(&v, &b, 4);
    return v;
}
static float f32_bridge_update(uint32_t b) {
    float v;
    memcpy(&v, &b, 4);
    return v;
}
static uint32_t floatBits_bridge_update(float v) {
    uint32_t b;
    memcpy(&b, &v, 4);
    return b;
}
static void put32(void *p, uint32_t v) {
    *(volatile uint32_t *)p = v;
}

static double observedDouble(uint8_t *image, uint32_t rva) {
    uint64_t bits = u64_bridge_update(image + rva);
    double value;
    memcpy(&value, &bits, 8);
    return value;
}
static uint64_t doubleWord(double value) {
    uint64_t bits;
    memcpy(&bits, &value, 8);
    return bits;
}
static double doubleResult(uint64_t bits) {
    double value;
    memcpy(&value, &bits, 8);
    return value;
}
static double addScalar(double a, double b) {
    return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double subScalar(double a, double b) {
    return _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
static double multiplyScalar(double a, double b) {
    return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
// RVA 0x2e7b0. True means all unique projected footprint corners are air.
static bool projectedFootprintIsAir(uint64_t game, uint64_t options, uint64_t world,
                                    uint64_t player, uint8_t *image, dependency call,
                                    const SpatialBoundary &spatial) {
    uint64_t box = call(0x23670, game, player, 0, 0);
    double bounds[6];
    call(0x25640, uintptr_t(bounds), game, box, 0);
    double half = observedDouble(image, 0x1507f0);
    double base[3] = {multiplyScalar(addScalar(bounds[0], bounds[3]), half),
                      addScalar(bounds[1], observedDouble(image, 0x1507f8)),
                      multiplyScalar(addScalar(bounds[2], bounds[5]), half)};
    double velocity[3];
    entityVelocity(call, uintptr_t(velocity), game, player, 0);
    double radius =
        double(f32_bridge_update(u32_bridge_update(image + Storage::edge_offsetCurrent)));
    if (image[Storage::randomizeCurrent] == 1) {
        uint64_t random = randomRangeBits(call, 0, u32_bridge_update(image + 0x150800), 0, 0);
        float sample = f32_bridge_update(uint32_t(smoothedRandomSample(
            call, uintptr_t(image + 0x2f7de0), random, u64_bridge_update(image + 0x150808), 0)));
        radius = subScalar(radius, double(sample));
        if (0.0 > radius)
            radius = 0.0;
    }
    uint64_t backward = call(0x250d0, game, options, 0, 0),
             forward = call(0x25120, game, options, 0, 0),
             left = call(0x25170, game, options, 0, 0), right = call(0x251c0, game, options, 0, 0);
    uint8_t pressed = uint8_t(keyDown_bridge_update(call, game, backward, 0, 0));
    float negative = f32_bridge_update(u32_bridge_update(image + 0x150810));
    float forwardInput = pressed ? negative : 0.0f;
    pressed = uint8_t(keyDown_bridge_update(call, game, forward, 0, 0));
    float positive = f32_bridge_update(u32_bridge_update(image + 0x150814));
    if (pressed)
        forwardInput = _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(forwardInput), _mm_set_ss(positive)));
    float strafe = uint8_t(keyDown_bridge_update(call, game, left, 0, 0)) ? negative : 0.0f;
    if (uint8_t(keyDown_bridge_update(call, game, right, 0, 0)))
        strafe = _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(strafe), _mm_set_ss(positive)));
    uint64_t rotation = entityRotation_bridge_update(call, game, player, 0, 0);
    float speed = f32_bridge_update(uint32_t(call(0x23b40, game, player, 0, 0)));
    double generated[3];
    spatial.movementVector(generated, rotation, forwardInput, strafe, speed);
    double copy[3], motion[3], projected[3], baseCopy[3];
    memcpy(copy, velocity, 24);
    call(0x9400, uintptr_t(motion), uintptr_t(copy), uintptr_t(generated), 0);
    memcpy(baseCopy, base, 24);
    memcpy(copy, motion, 24);
    call(0x9400, uintptr_t(projected), uintptr_t(baseCopy), uintptr_t(copy), 0);
    auto floorNative = [&](double value) {
        return doubleResult(call(0xb29b0, doubleWord(value), 0, 0, 0));
    };
    auto integer = [](double value) { return _mm_cvttsd_si32(_mm_set_sd(value)); };
    int32_t lowX = integer(floorNative(subScalar(projected[0], radius)));
    int32_t lowZ = integer(floorNative(subScalar(projected[2], radius)));
    int32_t y = integer(floorNative(projected[1]));
    double highXDouble = floorNative(addScalar(projected[0], radius));
    double highZDouble = floorNative(addScalar(radius, projected[2]));
    auto isAir = [&](int32_t x, int32_t z) {
        uint64_t block = spatial.worldBlockAt(game, world, x, y, z);
        return uint32_t(call(0x24280, game, block, 0, 0)) == 0;
    };
    if (!isAir(lowX, lowZ))
        return false;
    int32_t highZ = integer(highZDouble);
    if (lowZ != highZ && !isAir(lowX, highZ))
        return false;
    int32_t highX = integer(highXDouble);
    if (lowX != highX) {
        if (!isAir(highX, lowZ))
            return false;
        if (lowZ != highZ && !isAir(highX, highZ))
            return false;
    }
    return true;
}

void updateSneakState(uint8_t *event, uint8_t *image, dependency call,
                      const SpatialBoundary &spatial) {
    image[Storage::placementInputGate] = 0;
    image[Storage::placementActionGate] = 0;
    uint8_t *ctx = (uint8_t *)(uintptr_t)u64_bridge_update(event + 8);
    if (ctx[0x40] != 1)
        return;
    uint64_t settings = clientOptions_bridge_update(call, u64_bridge_update(ctx),
                                                    u64_bridge_update(ctx + 0x18), 0, 0);
    uint32_t cooldown = u32_bridge_update(image + Storage::placementCooldown);
    if (s32(cooldown) > 0)
        put32(image + Storage::placementCooldown, cooldown - 1);
    uint64_t key = sneakKey_bridge_update(call, u64_bridge_update(ctx), settings, 0, 0);
    uint32_t pressed =
        (uint32_t)physicalKeyWord_bridge_update(call, u64_bridge_update(ctx), key, 0, 0);
    {
        if (image[Storage::require_sneakCurrent] != (uint8_t)pressed)
            goto reject;
        uint64_t game = u64_bridge_update(ctx), player = u64_bridge_update(ctx + 0x28);
        if (image[Storage::require_looking_downCurrent] == 1) {
            uint64_t angle = entityRotation_bridge_update(call, game, player, 0, 0);
            if (f32_bridge_update(u32_bridge_update(image + Storage::nativeData_1507c0)) >
                f32_bridge_update((uint32_t)(angle >> 32)))
                goto reject;
        }
        if (image[Storage::require_not_forwardCurrent] == 1) {
            float vertical =
                f32_bridge_update((uint32_t)nativeBoundary_23ac0(call, game, player, 0, 0));
            if (vertical > 0.)
                goto reject;
        }
        image[Storage::placementActionGate] =
            u32_bridge_update(image + Storage::select_blocksCurrent) != 0;
        if (image[Storage::require_holding_blocksCurrent] == 1) {
            uint64_t block = heldItem_bridge_update(call, game, player, 0, 0);
            uint8_t held = (uint8_t)itemIsBlock_bridge_update(call, game, block, 0, 0);
            uint32_t ticks = 2;
            if (!held) {
                ticks = u32_bridge_update(image + Storage::heldBlockGraceTicks);
                if (s32(ticks) <= 0)
                    goto reject;
                --ticks;
            }
            put32(image + Storage::heldBlockGraceTicks, ticks);
        }
        image[Storage::sneakStateOwned] = 1;
        uint8_t down = (uint8_t)keyDown_bridge_update(call, u64_bridge_update(ctx), key, 0, 0);
        game = u64_bridge_update(ctx);
        uint64_t world = u64_bridge_update(ctx + 0x20);
        player = u64_bridge_update(ctx + 0x28);
        if (!down) {
            if (!(uint8_t)entityOnGround_bridge_update(call, game, player, 0, 0)) {
                if (image[Storage::sneak_on_jumpCurrent] != 1)
                    return;
                double velocity[3];
                entityVelocity(call, (uintptr_t)velocity, game, player, 0);
                if (0. > velocity[1])
                    return;
            }
            if (!(uint8_t)projectedFootprintIsAir(game, settings, world, player, image, call,
                                                  spatial))
                return;
            setKeyDownRaw_bridge_update(call, u64_bridge_update(ctx), key, 1, 0);
            goto finish_flag;
        }
        if (image[Storage::require_sneakCurrent] == 1) {
            float vertical =
                f32_bridge_update((uint32_t)nativeBoundary_23ac0(call, game, player, 0, 0));
            if (vertical >= 0.)
                goto finish_flag;
            if (s32(u32_bridge_update(image + Storage::placementCooldown)) <= 0)
                goto finish_flag;
        } else if (!(uint8_t)entityOnGround_bridge_update(call, game, player, 0, 0)) {
            if (image[Storage::sneak_on_jumpCurrent] != 1)
                goto countdown;
            double velocity[3];
            entityVelocity(call, (uintptr_t)velocity, game, player, 0);
            if (0. > velocity[1])
                goto countdown;
        }
        if ((uint8_t)projectedFootprintIsAir(game, settings, world, player, image, call, spatial))
            goto finish_flag;
    countdown: {
        float timer = f32_bridge_update(u32_bridge_update(image + Storage::unsneakCountdown)) +
                      f32_bridge_update(u32_bridge_update(image + Storage::nativeData_1507c4));
        put32(image + Storage::unsneakCountdown, floatBits_bridge_update(timer));
        if (timer > 0.)
            goto finish_flag;
    }
        setKeyDownRaw_bridge_update(call, u64_bridge_update(ctx), key, 0, 0);
        float next = f32_bridge_update(u32_bridge_update(image + Storage::unsneak_delayCurrent));
        if (image[Storage::randomizeCurrent] == 1) {
            uint64_t random =
                randomRangeBits(call, u32_bridge_update(image + Storage::nativeData_1507c8),
                                u32_bridge_update(image + Storage::nativeData_1507cc), 0, 0);
            next += f32_bridge_update((uint32_t)smoothedRandomSample(
                call, (uintptr_t)(image + Storage::nativeData_2f7df0), random,
                u64_bridge_update(image + Storage::nativeData_1507d0), 0));
            random = randomRangeBits(call, u32_bridge_update(image + Storage::nativeData_1507d8),
                                     u32_bridge_update(image + Storage::nativeData_1507dc), 0, 0);
            if ((uint8_t)smoothedProbabilityGate(
                    call, (uintptr_t)(image + Storage::nativeData_2f7e00), random,
                    u64_bridge_update(image + Storage::nativeData_1507e0), 0)) {
                random = randomRangeBits(
                    call, 0, u32_bridge_update(image + Storage::nativeData_1507e8), 0, 0);
                next += f32_bridge_update((uint32_t)randomRangeSample(call, random, 0, 0, 0));
            }
        }
        next += f32_bridge_update(u32_bridge_update(image + Storage::unsneakCountdown));
        put32(image + Storage::unsneakCountdown, floatBits_bridge_update(next));
        return;
    }
finish_flag:
    image[Storage::placementInputGate] = image[Storage::avoid_double_sneakCurrent];
    return;
reject:
    if (image[Storage::sneakStateOwned] == 1)
        setKeyDownRaw_bridge_update(call, u64_bridge_update(ctx), key, pressed, 0);
    image[Storage::sneakStateOwned] = 0;
}

} // namespace reconstruction::Bridge_Assist
// END SOURCE modules/Bridge_Assist/bridge_update.cpp

// Convenient borrowed-state interface

namespace shareable {
class BridgeAssist {
  public:
    static constexpr const char *kName = "Bridge Assist";
    static constexpr const char *kDescription = "Sneaks and unsneaks for you while bridging.";
    explicit BridgeAssist(std::uint8_t *image) : image_(image) {}
    // Edge offset. Config key: edge_offset.
    NumberSetting &edge_offset() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2e9dc8);
    }
    // Unsneak delay. Config key: unsneak_delay.
    NumberSetting &unsneak_delay() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2e9e40);
    }
    // Select blocks. Config key: select_blocks.
    ChoiceSetting &select_blocks() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2e9d48);
    }
    // Option labels observed in the captured metadata.
    enum class SelectBlocksMode : std::uint32_t { No = 0, OnDepletion = 1, Always = 2 };
    // Randomize. Config key: randomize.
    BooleanSetting &randomize() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2e9e00);
    }
    // Sneak on jump. Config key: sneak_on_jump.
    BooleanSetting &sneak_on_jump() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2e9da8);
    }
    // Avoid double-sneaking. Config key: avoid_double_sneak.
    BooleanSetting &avoid_double_sneak() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2e9e20);
    }
    // Sneak key pressed. Config key: require_sneak.
    BooleanSetting &require_sneak() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2e9cd0);
    }
    // Holding blocks. Config key: require_holding_blocks.
    BooleanSetting &require_holding_blocks() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2e9d88);
    }
    // Looking down. Config key: require_looking_down.
    BooleanSetting &require_looking_down() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2e9cf0);
    }
    // Not moving forward. Config key: require_not_forward.
    BooleanSetting &require_not_forward() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2e9d10);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_bridge_assist_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_bridge_assist_settings(&context, image_, &dependencies);
    }
    void onModuleStateChanged(uint8_t *event, ::reconstruction::Bridge_Assist::dependency call) {
        ::reconstruction::Bridge_Assist::onModuleStateChanged(event, image_, call);
    }
    void onPlacementAction(uint8_t *event, ::reconstruction::Bridge_Assist::dependency call) {
        ::reconstruction::Bridge_Assist::onPlacementAction(event, image_, call);
    }
    void filterPlacementInput(uint8_t *event, ::reconstruction::Bridge_Assist::dependency call) {
        ::reconstruction::Bridge_Assist::filterPlacementInput(event, image_, call);
    }
    void updateSneakState(uint8_t *event, ::reconstruction::Bridge_Assist::dependency call,
                          const ::reconstruction::Bridge_Assist::SpatialBoundary &spatial) {
        ::reconstruction::Bridge_Assist::updateSneakState(event, image_, call, spatial);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
