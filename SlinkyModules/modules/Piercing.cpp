// Piercing

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Piercing.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Piercing.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Piercing: lib_win settings 0x44d70.
// UI 0x44ca0.
static constexpr UiStep ui_steps_Surface_Piercing[] = {
    {UiControl::section, "Always hit through", 0}, {UiControl::choice, nullptr, 0x2f3d90},
    {UiControl::checkbox, nullptr, 0x2f3d00},      {UiControl::checkbox, nullptr, 0x2f3d20},
    {UiControl::checkbox, nullptr, 0x2f3d40},      {UiControl::checkbox, nullptr, 0x2f3d60},
    {UiControl::checkbox, nullptr, 0x2f3dd0},      {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2f3ce0},      {UiControl::checkbox, nullptr, 0x2f3cc0},
};
static constexpr SettingsStep settings_steps_Surface_Piercing[] = {
    {SettingsControl::choice, "sort_by", 0x2f3d90},
    {SettingsControl::boolean, "non_players", 0x2f3d00},
    {SettingsControl::boolean, "friendlies", 0x2f3d20},
    {SettingsControl::boolean, "bots", 0x2f3d40},
    {SettingsControl::boolean, "enemies", 0x2f3d60},
    {SettingsControl::boolean, "blocks", 0x2f3dd0},
    {SettingsControl::boolean, "require_weapon", 0x2f3ce0},
    {SettingsControl::boolean, "require_inside_bb", 0x2f3cc0},
};
static constexpr ModuleSurface surface_Surface_Piercing{
    ui_steps_Surface_Piercing, std::size(ui_steps_Surface_Piercing),
    settings_steps_Surface_Piercing, std::size(settings_steps_Surface_Piercing)};

extern "C" __declspec(dllexport) void
recovered_piercing_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                      const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Piercing, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_piercing_settings(SettingsContext *context, std::uint8_t *image,
                            const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Piercing, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Piercing.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Piercing/Piercing.cpp
#include "../runtime/native/verified/event_callbacks.hpp"

// lib_win RVA 0x44c90: event 8 callback.
extern "C" __declspec(dllexport) void recovered_piercing(std::uint8_t *event) {
    event[0x10] = 1;
}
// END SOURCE modules/Piercing/Piercing.cpp

// BEGIN SOURCE modules/Piercing/Queries.cpp
// Native 0x44a50 and 0x44c40. Ownership follows descriptor 0x2f3ab0,
// not their placement in the supplied Anti_Debuff candidate interval.
#ifndef SLINKY_SHARE_85188B6FD87E87371A63
#define SLINKY_SHARE_85188B6FD87E87371A63
// BEGIN SOURCE modules/Piercing/Queries.hpp
#include "../runtime/native/verified/Timer.hpp"
#include <cstdint>

namespace reconstruction::piercing {
// Native access helpers stay typed at the Java/weapon boundaries.
struct QueryDependencies {
    std::uint64_t (*weaponAllowed)(GameAccessBridge *, std::uintptr_t);    // 0x380b0, tests AL
    std::uintptr_t (*resolvePlayer)(GameAccessBridge *, std::uintptr_t);   // 0x24120
    std::uint64_t (*classification)(GameAccessBridge *, std::uintptr_t);   // 0x2acb0
    std::int32_t (*hurtTime)(GameAccessBridge *, std::uintptr_t);          // 0x239f0
    float (*health)(GameAccessBridge *, std::uintptr_t);                   // 0x23a40
    std::uint32_t (*counter)(GameAccessBridge *, std::uintptr_t);          // 0x23760
    std::uint32_t (*lastAttackerTime)(GameAccessBridge *, std::uintptr_t); // 0x23720
};
// The returned 0/1/2 decisions retain the native ranking convention.
std::uint32_t rankTargetPair(TimerGame *, std::uintptr_t first, std::uintptr_t second,
                             std::uint8_t insideBoundingBox, const std::uint8_t *stateImage,
                             const QueryDependencies &);
// The native helper changes AL only after the weapon query. Its consumer tests AL.
std::uint64_t shouldPierceBlocks(TimerGame *, const std::uint8_t *stateImage,
                                 const QueryDependencies &);
} // namespace reconstruction::piercing
// END SOURCE modules/Piercing/Queries.hpp

#endif // SLINKY_SHARE_85188B6FD87E87371A63

#include <bit>
#include <cstring>

namespace reconstruction::piercing {
namespace {
constexpr std::size_t enabled = 0x2f3ac4;
constexpr std::size_t requireInside = 0x2f3cc0 + offsetof(BooleanSetting, current);
constexpr std::size_t requireWeapon = 0x2f3ce0 + offsetof(BooleanSetting, current);
constexpr std::size_t nonPlayers = 0x2f3d00 + offsetof(BooleanSetting, current);
constexpr std::size_t friendlies = 0x2f3d20 + offsetof(BooleanSetting, current);
constexpr std::size_t bots = 0x2f3d40 + offsetof(BooleanSetting, current);
constexpr std::size_t enemies = 0x2f3d60 + offsetof(BooleanSetting, current);
constexpr std::size_t sortBy = 0x2f3d90 + offsetof(ChoiceSetting, current);
constexpr std::size_t blocks = 0x2f3dd0 + offsetof(BooleanSetting, current);
std::uint32_t read32(const void *pointer) {
    std::uint32_t value;
    std::memcpy(&value, pointer, 4);
    return value;
}
std::uint32_t mixedCounter(TimerGame *context, std::uintptr_t entity,
                           const QueryDependencies &deps) {
    const auto first = deps.counter(context->bridge, entity);
    auto value = first + deps.lastAttackerTime(context->bridge, entity);
    value = (value ^ (value >> 16)) * 0x45d9f3bu;
    value = (value ^ (value >> 16)) * 0x45d9f3bu;
    return value ^ (value >> 16);
}
} // namespace
std::uint32_t rankTargetPair(TimerGame *context, std::uintptr_t first, std::uintptr_t second,
                             std::uint8_t insideBoundingBox, const std::uint8_t *stateImage,
                             const QueryDependencies &deps) {
    if (stateImage[enabled] != 1 || (!insideBoundingBox && stateImage[requireInside] != 0))
        return 2;
    if (stateImage[requireWeapon] == 1 &&
        static_cast<std::uint8_t>(deps.weaponAllowed(context->bridge, context->player)) == 0)
        return 2;
    const auto secondPlayer = deps.resolvePlayer(context->bridge, second);
    if (!secondPlayer)
        return 2u - stateImage[nonPlayers];
    const auto flags =
        static_cast<std::uint32_t>(deps.classification(context->bridge, secondPlayer));
    if ((stateImage[friendlies] & static_cast<std::uint8_t>((flags & 5) != 0)) != 0 ||
        (stateImage[bots] & static_cast<std::uint8_t>((flags & 2) >> 1)) != 0)
        return 1;
    const auto firstPlayer = deps.resolvePlayer(context->bridge, first);
    if (!firstPlayer)
        return 0;
    if (stateImage[enemies] != 1)
        return 2;
    const auto mode = read32(stateImage + sortBy);
    if (mode == 1) {
        const auto firstHealth = deps.health(context->bridge, firstPlayer);
        const auto secondHealth = deps.health(context->bridge, secondPlayer);
        if (secondHealth > firstHealth)
            return 1;
        if (firstHealth > secondHealth)
            return 0;
        // Both native UCOMISS/JA tests fall through when either lane is NaN.
    } else if (mode == 0) {
        const auto firstHurt = deps.hurtTime(context->bridge, firstPlayer);
        const auto secondHurt = deps.hurtTime(context->bridge, secondPlayer);
        if (secondHurt > firstHurt)
            return 1;
        if (secondHurt < firstHurt)
            return 0;
    }
    const auto firstHash = mixedCounter(context, firstPlayer, deps);
    const auto secondHash = mixedCounter(context, secondPlayer, deps);
    return std::bit_cast<std::int32_t>(secondHash) <= std::bit_cast<std::int32_t>(firstHash);
}
std::uint64_t shouldPierceBlocks(TimerGame *context, const std::uint8_t *stateImage,
                                 const QueryDependencies &deps) {
    if (stateImage[enabled] != 1 || stateImage[blocks] == 0)
        return 0;
    if (stateImage[requireWeapon] == 1) {
        const auto result = deps.weaponAllowed(context->bridge, context->player);
        if (static_cast<std::uint8_t>(result) == 0)
            return 0;
        return (result & ~std::uint64_t{0xff}) | 1;
    }
    return 1;
}
} // namespace reconstruction::piercing
// END SOURCE modules/Piercing/Queries.cpp

#ifndef SLINKY_SHARE_E6EC438A84894D56174E
#define SLINKY_SHARE_E6EC438A84894D56174E
// BEGIN SOURCE modules/Piercing/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
#include "../runtime/native/verified/event_callbacks.hpp"
#include "../runtime/native/verified/access_events.hpp"
// END SOURCE modules/Piercing/Api.hpp

#endif // SLINKY_SHARE_E6EC438A84894D56174E

// Convenient borrowed-state interface

namespace shareable {
class Piercing {
  public:
    static constexpr const char *kName = "Piercing";
    static constexpr const char *kDescription = "Allows hitting entities through obstructions.";
    explicit Piercing(std::uint8_t *image) : image_(image) {}
    // Sort targets by. Config key: sort_by.
    ChoiceSetting &sort_by() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f3d90);
    }
    // Option labels observed in the captured metadata.
    enum class SortByMode : std::uint32_t { HurtTime = 0, Health = 1 };
    // Non-player entities. Config key: non_players.
    BooleanSetting &non_players() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f3d00);
    }
    // Friendlies. Config key: friendlies.
    BooleanSetting &friendlies() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f3d20);
    }
    // Bots. Config key: bots.
    BooleanSetting &bots() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f3d40);
    }
    // Enemies. Config key: enemies.
    BooleanSetting &enemies() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f3d60);
    }
    // Blocks. Config key: blocks.
    BooleanSetting &blocks() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f3dd0);
    }
    // Holding weapon. Config key: require_weapon.
    BooleanSetting &require_weapon() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f3ce0);
    }
    // Inside entity hitbox. Config key: require_inside_bb.
    BooleanSetting &require_inside_bb() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f3cc0);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_piercing_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_piercing_settings(&context, image_, &dependencies);
    }
    static void piercing(std::uint8_t *event) {
        ::recovered_piercing(event);
    }
    static std::uint32_t rankTargetPair(TimerGame *context, std::uintptr_t first,
                                        std::uintptr_t second, std::uint8_t insideBoundingBox,
                                        const std::uint8_t *stateImage,
                                        const ::reconstruction::piercing::QueryDependencies &deps) {
        return ::reconstruction::piercing::rankTargetPair(context, first, second, insideBoundingBox,
                                                          stateImage, deps);
    }
    static std::uint64_t
    shouldPierceBlocks(TimerGame *context, const std::uint8_t *stateImage,
                       const ::reconstruction::piercing::QueryDependencies &deps) {
        return ::reconstruction::piercing::shouldPierceBlocks(context, stateImage, deps);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
