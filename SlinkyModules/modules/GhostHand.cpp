// Ghost Hand

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Ghost_Hand.md

#include "../runtime/native/verified/module_surface.hpp"

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Ghost_Hand/Ghost_Hand.cpp
#include "../runtime/native/verified/event_callbacks.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <initializer_list>

// lib_win RVA 0x46e30: event 8 callback.
extern "C" __declspec(dllexport) void recovered_ghost_hand(std::uint8_t *event) {
    event[0x10] = 1;
}

// lib_win RVA 0x46f70. The records start at 0x2f4ac0 in the supplied image.
extern "C" __declspec(dllexport) void
recovered_ghost_hand_settings(SettingsContext *context, BooleanSetting *settings,
                              const SettingsDependencies *dependencies) {
    struct Binding {
        const char *key;
        unsigned index;
    };
    static constexpr Binding bindings[] = {
        {"non_players", 8},        {"friendlies", 10},         {"bots", 9},
        {"enemies", 11},           {"allow_using_sword", 2},   {"allow_using_tools", 3},
        {"allow_using_fists", 1},  {"allow_using_buckets", 4}, {"allow_using_fns", 5},
        {"allow_using_cobweb", 6}, {"allow_using_other", 7},   {"require_mouse_pressed", 0},
    };
    for (const auto &binding : bindings)
        recovered_boolean_settings(context, binding.key, settings + binding.index, dependencies);
}

struct GhostHandUiDependencies {
    void (*section)(std::uint64_t ui, std::uint64_t layout, const char *label);
    void (*checkbox)(std::uint64_t layout, std::uint64_t ui, BooleanSetting *setting);
};

// lib_win RVA 0x46e40. The final checkbox is a native tail call.
extern "C" __declspec(dllexport) void
recovered_ghost_hand_ui(std::uint64_t ui, std::uint64_t layout, BooleanSetting *settings,
                        const GhostHandUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Interact through");
    for (unsigned index : {8u, 10u, 9u, 11u})
        dependencies->checkbox(layout, ui, settings + index);
    dependencies->section(ui, layout, "Allow while using");
    for (unsigned index : {2u, 3u, 1u, 4u, 5u, 6u, 7u})
        dependencies->checkbox(layout, ui, settings + index);
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, settings);
}
// END SOURCE modules/Ghost_Hand/Ghost_Hand.cpp

// BEGIN SOURCE modules/Ghost_Hand/Query.cpp
// Native RVA 0x46d10, descriptor 0x2f48b0. The original candidate file was Null Move.
// Item-ID groups were checked against all 104 entries of the native jump table.
#ifndef SLINKY_SHARE_20DDC575E7B8541DF9DC
#define SLINKY_SHARE_20DDC575E7B8541DF9DC
// BEGIN SOURCE modules/Ghost_Hand/Query.hpp
#include "../runtime/native/verified/Timer.hpp"
#include <cstdint>
namespace reconstruction::ghost_hand {
struct QueryDependencies {
    std::uint64_t (*mousePressed)(TimerGame *);                          // 0x29080, tests AL
    std::uintptr_t (*itemObject)(GameAccessBridge *, std::uintptr_t);    // 0x28a50
    std::int32_t (*itemIdentifier)(GameAccessBridge *, std::uintptr_t);  // 0x25c50
    std::uintptr_t (*resolvePlayer)(GameAccessBridge *, std::uintptr_t); // 0x24120
    std::uint64_t (*classification)(GameAccessBridge *, std::uintptr_t); // 0x2acb0
};
std::uint8_t canInteractThrough(TimerGame *, std::uintptr_t target, const std::uint8_t *stateImage,
                                const QueryDependencies &);
} // namespace reconstruction::ghost_hand
// END SOURCE modules/Ghost_Hand/Query.hpp

#endif // SLINKY_SHARE_20DDC575E7B8541DF9DC

namespace reconstruction::ghost_hand {
namespace {
constexpr std::size_t current(unsigned slot) {
    return 0x2f4ac0 + slot * sizeof(BooleanSetting) + offsetof(BooleanSetting, current);
}
constexpr auto requireMousePressed = current(0);
constexpr auto allowUsingFists = current(1);
constexpr auto allowUsingSword = current(2);
constexpr auto allowUsingTools = current(3);
constexpr auto allowUsingBuckets = current(4);
constexpr auto allowUsingFns = current(5);
constexpr auto allowUsingCobweb = current(6);
constexpr auto allowUsingOther = current(7);
constexpr auto nonPlayers = current(8);
constexpr auto bots = current(9);
constexpr auto friendlies = current(10);
constexpr auto enemies = current(11);
std::size_t itemGate(std::uint32_t identifier) {
    switch (identifier) {
    case 0x100:
    case 0x101:
    case 0x102:
    case 0x10d:
    case 0x10e:
    case 0x10f:
    case 0x111:
    case 0x112:
    case 0x113:
    case 0x115:
    case 0x116:
    case 0x117:
    case 0x11c:
    case 0x11d:
    case 0x11e:
    case 0x167:
        return allowUsingTools;
    case 0x103:
        return allowUsingFns;
    case 0x10b:
    case 0x10c:
    case 0x110:
    case 0x114:
    case 0x11b:
        return allowUsingSword;
    case 0x145:
    case 0x146:
    case 0x147:
        return allowUsingBuckets;
    case 0x1e:
        return allowUsingCobweb;
    default:
        return allowUsingOther;
    }
}
} // namespace
std::uint8_t canInteractThrough(TimerGame *context, std::uintptr_t target,
                                const std::uint8_t *stateImage, const QueryDependencies &deps) {
    if (stateImage[0x2f48c4] != 1)
        return 0;
    if (stateImage[requireMousePressed] == 1 &&
        static_cast<std::uint8_t>(deps.mousePressed(context)) == 0)
        return 0;
    const auto item = deps.itemObject(context->bridge, context->player);
    auto gate = allowUsingFists;
    if (item)
        gate = itemGate(static_cast<std::uint32_t>(deps.itemIdentifier(context->bridge, item)));
    if (stateImage[gate] != 1)
        return 0;
    const auto player = deps.resolvePlayer(context->bridge, target);
    if (!player)
        return stateImage[nonPlayers];
    const auto flags = static_cast<std::uint8_t>(deps.classification(context->bridge, player));
    // Bot bit takes precedence over friendly/team bits, matching the native CMOVs.
    gate = (flags & 2) ? bots : ((flags & 5) ? friendlies : enemies);
    return stateImage[gate];
}
} // namespace reconstruction::ghost_hand
// END SOURCE modules/Ghost_Hand/Query.cpp

#ifndef SLINKY_SHARE_7D1CD141AD911B51EFC6
#define SLINKY_SHARE_7D1CD141AD911B51EFC6
// BEGIN SOURCE modules/Ghost_Hand/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
#include "../runtime/native/verified/event_callbacks.hpp"
#include "../runtime/native/verified/access_events.hpp"
// END SOURCE modules/Ghost_Hand/Api.hpp

#endif // SLINKY_SHARE_7D1CD141AD911B51EFC6

// Convenient borrowed-state interface

namespace shareable {
class GhostHand {
  public:
    static constexpr const char *kName = "Ghost Hand";
    static constexpr const char *kDescription = "Allows interacting with blocks through entities.";
    explicit GhostHand(std::uint8_t *image) : image_(image) {}
    // Non-player entities. Config key: non_players.
    BooleanSetting &non_players() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4bc0);
    }
    // Friendlies. Config key: friendlies.
    BooleanSetting &friendlies() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4c00);
    }
    // Bots. Config key: bots.
    BooleanSetting &bots() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4be0);
    }
    // Enemies. Config key: enemies.
    BooleanSetting &enemies() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4c20);
    }
    // Sword. Config key: allow_using_sword.
    BooleanSetting &allow_using_sword() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4b00);
    }
    // Tool. Config key: allow_using_tools.
    BooleanSetting &allow_using_tools() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4b20);
    }
    // Fists. Config key: allow_using_fists.
    BooleanSetting &allow_using_fists() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4ae0);
    }
    // Bucket. Config key: allow_using_buckets.
    BooleanSetting &allow_using_buckets() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4b40);
    }
    // Flint and steel. Config key: allow_using_fns.
    BooleanSetting &allow_using_fns() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4b60);
    }
    // Cobweb. Config key: allow_using_cobweb.
    BooleanSetting &allow_using_cobweb() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4b80);
    }
    // Other. Config key: allow_using_other.
    BooleanSetting &allow_using_other() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4ba0);
    }
    // Mouse pressed. Config key: require_mouse_pressed.
    BooleanSetting &require_mouse_pressed() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f4ac0);
    }
    static void ghostHand(std::uint8_t *event) {
        ::recovered_ghost_hand(event);
    }
    static void settings(SettingsContext *context, BooleanSetting *settings,
                         const SettingsDependencies *dependencies) {
        ::recovered_ghost_hand_settings(context, settings, dependencies);
    }
    static void ui(std::uint64_t ui, std::uint64_t layout, BooleanSetting *settings,
                   const GhostHandUiDependencies *dependencies) {
        ::recovered_ghost_hand_ui(ui, layout, settings, dependencies);
    }
    static std::uint8_t
    canInteractThrough(TimerGame *context, std::uintptr_t target, const std::uint8_t *stateImage,
                       const ::reconstruction::ghost_hand::QueryDependencies &deps) {
        return ::reconstruction::ghost_hand::canInteractThrough(context, target, stateImage, deps);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
