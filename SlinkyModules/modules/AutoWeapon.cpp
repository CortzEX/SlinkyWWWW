// Auto Weapon

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Auto_Weapon.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Auto_Weapon.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Auto Weapon: lib_win settings 0x4a4e0.
// UI 0x4a480.
static constexpr UiStep ui_steps_Surface_Auto_Weapon[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2f5d08},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2f5d40},
};
static constexpr SettingsStep settings_steps_Surface_Auto_Weapon[] = {
    {SettingsControl::number, "activation_time", 0x2f5d08},
    {SettingsControl::boolean, "require_mouse_pressed", 0x2f5d40},
};
static constexpr ModuleSurface surface_Surface_Auto_Weapon{
    ui_steps_Surface_Auto_Weapon, std::size(ui_steps_Surface_Auto_Weapon),
    settings_steps_Surface_Auto_Weapon, std::size(settings_steps_Surface_Auto_Weapon)};

extern "C" __declspec(dllexport) void
recovered_auto_weapon_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                         const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Auto_Weapon, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_auto_weapon_settings(SettingsContext *context, std::uint8_t *image,
                               const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Auto_Weapon, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Auto_Weapon.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Auto_Weapon/auto_weapon.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_7B7034FCA0DDFF3E51E7
#define SLINKY_SHARE_7B7034FCA0DDFF3E51E7
// BEGIN SOURCE modules/Auto_Weapon/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Auto_Weapon {
namespace Storage {
inline constexpr std::uint32_t moduleDescriptor = 0x2f5af8;
inline constexpr std::uint32_t activation_timeRecord = 0x2f5d08;
inline constexpr std::uint32_t activation_timeCurrent = 0x2f5d38;
inline constexpr std::uint32_t require_mouse_pressedRecord = 0x2f5d40;
inline constexpr std::uint32_t require_mouse_pressedCurrent = 0x2f5d58;
inline constexpr std::uint32_t selectionDelayTicks = 0x304ae8;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &activation_time() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::activation_timeRecord);
    }
    BooleanSetting &require_mouse_pressed() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_mouse_pressedRecord);
    }
};
} // namespace reconstruction::Auto_Weapon
// END SOURCE modules/Auto_Weapon/Settings.hpp

#endif // SLINKY_SHARE_7B7034FCA0DDFF3E51E7

#include <stdint.h>
#include <string.h>
namespace reconstruction::Auto_Weapon {
using helper = native_binding::WordEndpoints;
// Native entry 0x22e10; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t currentHitResult(helper api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x22e10, a0, a1, a2, a3);
}
// Native entry 0x23f00; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t nativeBoundary_23f00(helper api, uint64_t a0, uint64_t a1, uint64_t a2,
                                     uint64_t a3) {
    return api(0x23f00, a0, a1, a2, a3);
}
// Native entry 0x23f40; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityInventory(helper api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x23f40, a0, a1, a2, a3);
}
// Native entry 0x23f90; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityUsingItem(helper api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x23f90, a0, a1, a2, a3);
}
// Native entry 0x24b50; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t hitResultType(helper api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x24b50, a0, a1, a2, a3);
}
// Native entry 0x24e30; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t hitEntity(helper api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x24e30, a0, a1, a2, a3);
}
// Native entry 0x25a60; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t inventorySelectedSlot(helper api, uint64_t a0, uint64_t a1, uint64_t a2,
                                      uint64_t a3) {
    return api(0x25a60, a0, a1, a2, a3);
}
// Native entry 0x25a80; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t selectInventorySlot(helper api, uint64_t a0, uint64_t a1, uint64_t a2,
                                    uint64_t a3) {
    return api(0x25a80, a0, a1, a2, a3);
}
// Native entry 0x29080; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t attackMousePressed(helper api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x29080, a0, a1, a2, a3);
}
// Native entry 0x2aa80; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t claimModuleAction(helper api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x2aa80, a0, a1, a2, a3);
}
// Native entry 0x2aab0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t releaseModuleAction(helper api, uint64_t a0, uint64_t a1, uint64_t a2,
                                    uint64_t a3) {
    return api(0x2aab0, a0, a1, a2, a3);
}
// Native entry 0x2ace0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t entityPolicyPredicate(helper api, uint64_t a0, uint64_t a1, uint64_t a2,
                                      uint64_t a3) {
    return api(0x2ace0, a0, a1, a2, a3);
}
// Native entry 0x380b0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t weaponEligibility(helper api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x380b0, a0, a1, a2, a3);
}
// Native entry 0x380c0; concrete implementation: shared/OwnedNativeBindings.hpp.
static uint64_t bestWeaponSlot(helper api, uint64_t a0, uint64_t a1, uint64_t a2, uint64_t a3) {
    return api(0x380c0, a0, a1, a2, a3);
}

static uint64_t r64(const void *p, unsigned n) {
    uint64_t v;
    memcpy(&v, (const char *)p + n, 8);
    return v;
}
static int32_t i32(const void *p, unsigned n) {
    int32_t v;
    memcpy(&v, (const char *)p + n, 4);
    return v;
}
static float f32(const void *p, unsigned n) {
    float v;
    memcpy(&v, (const char *)p + n, 4);
    return v;
}
static void w32(void *p, unsigned n, uint32_t v) {
    memcpy((char *)p + n, &v, 4);
}

/* RVA 4a340. Dependencies retain address names; the image parameter supplies
 * data only. */
void selectWeaponForTarget(uint8_t *event, uint8_t *image, helper call) {
    uint8_t *game = (uint8_t *)(uintptr_t)r64(event, 8);
    uint64_t hit, target, inventory;
    int32_t current, selected;
    {
        if (game[64] != 1)
            goto reset;
        if ((uint8_t)entityUsingItem(call, r64(game, 0), r64(game, 40), 0, 0))
            goto reset;
        if (image[Storage::require_mouse_pressedCurrent] == 1 &&
            !(uint8_t)attackMousePressed(call, (uintptr_t)game, 0, 0, 0))
            goto reset;
        hit = currentHitResult(call, r64(game, 0), r64(game, 24), 0, 0);
        if (!hit || (int32_t)hitResultType(call, r64(game, 0), hit, 0, 0) != 2)
            goto reset;
        target = hitEntity(call, r64(game, 0), hit, 0, 0);
        target = nativeBoundary_23f00(call, r64(game, 0), target, 0, 0);
        if (!target || (uint8_t)entityPolicyPredicate(call, r64(game, 0), target, 7, 0))
            goto reset;
        if ((uint8_t)weaponEligibility(call, r64(game, 0), r64(game, 40), 0, 0))
            goto reset;
        inventory = entityInventory(call, r64(game, 0), r64(game, 40), 0, 0);
        current = (int32_t)inventorySelectedSlot(call, r64(game, 0), inventory, 0, 0);
        selected = (int32_t)bestWeaponSlot(call, (uintptr_t)game, inventory, 0, 0);
        if (selected == -1 || selected == current)
            goto reset;
        int32_t count = i32(image, Storage::selectionDelayTicks);
        if (f32(image, Storage::activation_timeCurrent) > (float)count) {
            w32(image, Storage::selectionDelayTicks, (uint32_t)count + 1);
            return;
        }
        if (!(uint8_t)claimModuleAction(call, UINT64_C(0x1802f5af8), 0, 0, 0))
            return;
        selectInventorySlot(call, r64(game, 0), inventory, (uint32_t)selected, 0);
        releaseModuleAction(call, UINT64_C(0x1802f5af8), 0, 0, 0);
        return;
    }
reset:
    w32(image, Storage::selectionDelayTicks, 0);
}

} // namespace reconstruction::Auto_Weapon
// END SOURCE modules/Auto_Weapon/auto_weapon.cpp

// Convenient borrowed-state interface

namespace shareable {
class AutoWeapon {
  public:
    static constexpr const char *kName = "Auto Weapon";
    static constexpr const char *kDescription = "Selects your weapon when aiming on players.";
    explicit AutoWeapon(std::uint8_t *image) : image_(image) {}
    // Activation time. Config key: activation_time.
    NumberSetting &activation_time() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f5d08);
    }
    // Mouse pressed. Config key: require_mouse_pressed.
    BooleanSetting &require_mouse_pressed() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f5d40);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_auto_weapon_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_auto_weapon_settings(&context, image_, &dependencies);
    }
    void selectWeaponForTarget(uint8_t *event, ::reconstruction::Auto_Weapon::helper call) {
        ::reconstruction::Auto_Weapon::selectWeaponForTarget(event, image_, call);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
