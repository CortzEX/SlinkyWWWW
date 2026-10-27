// Teams

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Teams.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Teams.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Teams: lib_win settings 0x32130.
static constexpr SettingsStep settings_steps_Surface_Teams[] = {
    {SettingsControl::boolean, "match_self_color", 0x2eb610},
    {SettingsControl::list, "team_colors", 0x2eb630},
};
static constexpr ModuleSurface surface_Surface_Teams{nullptr, 0, settings_steps_Surface_Teams,
                                                     std::size(settings_steps_Surface_Teams)};

extern "C" __declspec(dllexport) void
recovered_teams_settings(SettingsContext *context, std::uint8_t *image,
                         const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Teams, context, image, *dependencies);
}

// Teams: lib_win runtime UI 0x320e0.
extern "C" __declspec(dllexport) void
recovered_teams_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                   const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->checkbox(layout, ui, image + 0x2eb610);
    dependencies->list(layout, ui, image + 0x2eb630);
}
// END SOURCE native/verified/surfaces/Surface_Teams.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Teams
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Teams.cpp
extern "C" __declspec(dllexport) void
recovered_teams_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                         const BoundSurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->checkbox(layout, ui, image + 0x2eb610);
    dependencies->list(layout, ui, image + 0x2eb630);
}
// END SOURCE shared/BoundSurfaces.cpp@Teams

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Teams/Surface.cpp
#ifndef SLINKY_SHARE_3C1BB6D300A6E7AEE69B
#define SLINKY_SHARE_3C1BB6D300A6E7AEE69B
// BEGIN SOURCE modules/Teams/Surface.hpp
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/native/verified/module_format.hpp"
namespace teams {
void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                    const BoundSurfaceUiDependencies &);
void serializeConfig(SettingsContext &, std::uint8_t *image, const SurfaceSettingsDependencies &);
} // namespace teams
// END SOURCE modules/Teams/Surface.hpp

#endif // SLINKY_SHARE_3C1BB6D300A6E7AEE69B

extern "C" void recovered_teams_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                         const BoundSurfaceUiDependencies *);
extern "C" void recovered_teams_settings(SettingsContext *, std::uint8_t *,
                                         const SurfaceSettingsDependencies *);
namespace teams {
void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                    const BoundSurfaceUiDependencies &dependencies) {
    recovered_teams_bound_ui(ui, layout, image, &dependencies);
}
void serializeConfig(SettingsContext &context, std::uint8_t *image,
                     const SurfaceSettingsDependencies &dependencies) {
    recovered_teams_settings(&context, image, &dependencies);
}
} // namespace teams
// END SOURCE modules/Teams/Surface.cpp

// BEGIN SOURCE modules/Teams/Teams.cpp
#ifndef SLINKY_SHARE_B61CAA87E171D6E52902
#define SLINKY_SHARE_B61CAA87E171D6E52902
// BEGIN SOURCE modules/Teams/Teams.hpp
#include "../runtime/modules/Aim_Assist/Support.hpp"
#include "../runtime/native/verified/Friends_runtime.hpp"
#include "../runtime/native/verified/module_sorted_table.hpp"
#include "../runtime/native/verified/module_named_lists.hpp"
namespace teams {
std::uint16_t prefixColor(GameAccessBridge *, std::uintptr_t);    // 0x28b40
std::uint16_t componentColor(GameAccessBridge *, std::uintptr_t); // 0x28d20
std::uint16_t entityColor(GameAccessBridge *, std::uintptr_t);    // 0x28e10
void update(aim_assist::WorldUpdateEvent *, std::uint8_t *);
void disable(aim_assist::StateChangedEvent *, std::uint8_t *);
void cleanup(std::uint8_t *,
             void (*release)(void *)); // indirect external endpoint cell at native0x13cf70
std::int32_t compare(std::uint64_t, const void *, const void *); // 0x32170
} // namespace teams

namespace teams {
void colorNames(std::uint8_t *image, const char *const **table, std::uint64_t *count);
} // namespace teams
// END SOURCE modules/Teams/Teams.hpp

#endif // SLINKY_SHARE_B61CAA87E171D6E52902

#include <cstring>
namespace teams {
namespace {
using Word = std::uintptr_t;
Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word value;
    std::memcpy(&value, bridge->metadata + offset, sizeof value);
    return value;
}
template <class F_Teams> F_Teams slot(Word *environment, std::size_t offset) {
    return reinterpret_cast<F_Teams>(reinterpret_cast<const Word *>(*environment)[offset / 8]);
}
Word objectField(GameAccessBridge *b, Word entity, std::size_t offset) {
    using F_Teams = Word (*)(Word *, Word, Word);
    return slot<F_Teams>(b->environment, 0x2f8)(b->environment, entity, identifier(b, offset));
}
Word objectMethod(GameAccessBridge *b, Word entity, std::size_t offset) {
    using F_Teams = Word (*)(Word *, Word, Word, ...);
    return slot<F_Teams>(b->environment, 0x110)(b->environment, entity, identifier(b, offset));
}
Word instance(GameAccessBridge *b, Word entity, std::size_t offset) {
    using F_Teams = std::uint8_t (*)(Word *, Word, Word);
    return slot<F_Teams>(b->environment, 0x100)(b->environment, entity, identifier(b, offset))
               ? entity
               : 0;
}
std::int32_t length(Word *environment, Word text) {
    using F_Teams = std::int32_t (*)(Word *, Word);
    return slot<F_Teams>(environment, 0x520)(environment, text);
}
const std::uint16_t *characters(Word *environment, Word text) {
    using F_Teams = const std::uint16_t *(*)(Word *, Word, void *);
    return slot<F_Teams>(environment, 0x700)(environment, text, nullptr);
}
void releaseCharacters(Word *environment, Word text, const std::uint16_t *data) {
    using F_Teams = void (*)(Word *, Word, const std::uint16_t *);
    slot<F_Teams>(environment, 0x708)(environment, text, data);
}
bool formatColor(std::uint16_t c) {
    return static_cast<std::uint16_t>(c - 0x30) < 10 || static_cast<std::uint16_t>(c - 0x61) < 6 ||
           c == 0x72;
}
bool nameCharacter(std::uint16_t c) {
    return c == 0x5f || static_cast<std::uint16_t>(c - 0x30) < 10 ||
           static_cast<std::uint16_t>((c & 0xffdf) - 0x41) < 26;
}
std::uint16_t leadingColor(GameAccessBridge *bridge, Word text) {
    Word *environment = bridge->environment;
    const auto *data = characters(environment, text);
    std::uint16_t result = 0;
    bool previousSection = false;
    if (length(environment, text) > 0) {
        std::uint64_t index = 0;
        for (;;) {
            const auto c = data[index];
            const bool escaped = previousSection;
            previousSection = c == 0xa7;
            if (c != 0xa7) {
                if (escaped) {
                    if (formatColor(c))
                        result = c;
                } else if (nameCharacter(c))
                    break;
            }
            ++index;
            if (static_cast<std::int64_t>(index) >=
                static_cast<std::int64_t>(length(environment, text))) {
                result = 0;
                break;
            }
        }
    }
    releaseCharacters(environment, text, data);
    return result;
}
std::uint16_t trailingColor(GameAccessBridge *bridge, Word text) {
    Word *environment = bridge->environment;
    const auto count = length(environment, text);
    if (count == 0)
        return 0x66;
    const auto *data = characters(environment, text);
    std::uint16_t result = 0x66, selected = 0;
    bool valid = false;
    if (count > 0) {
        std::uint64_t cursor = static_cast<std::uint32_t>(count) + std::uint64_t{1};
        do {
            const std::uint16_t c = data[cursor - 2];
            if (c == 0xa7) {
                if (valid) {
                    result = selected;
                    break;
                } else
                    valid = false;
            } else {
                valid = formatColor(c);
                if (valid)
                    selected = c;
            }
            --cursor;
        } while (cursor > 1);
    }
    releaseCharacters(environment, text, data);
    return result;
}
Word frameHandle(aim_assist::ObjectRef p) {
    return reinterpret_cast<Word>(p);
}
} // namespace
std::uint16_t prefixColor(GameAccessBridge *b, Word text) {
    return leadingColor(b, text);
}
std::uint16_t componentColor(GameAccessBridge *b, Word component) {
    const Word text = objectField(b, component, 0x680); // 0x27300
    return text ? trailingColor(b, text) : 0x66;
}
std::uint16_t entityColor(GameAccessBridge *b, Word entity) {
    const Word name = objectMethod(b, entity, 0x248); // 0x23830
    const auto initial = leadingColor(b, name);
    if (initial)
        return initial;
    Word component = instance(b, entity, 0x4f8); // 0x23950
    if (!component)
        return 0x66;
    component = objectMethod(b, component, 0x518); // 0x23be0
    if (!component)
        return 0x66;
    component = instance(b, component, 0x678); // 0x272c0
    if (!component)
        return 0x66;
    component = objectField(b, component, 0x680); // 0x27300
    return component ? trailingColor(b, component) : 0x66;
}
std::int32_t compare(std::uint64_t, const void *left, const void *right) {
    return static_cast<std::int32_t>(*static_cast<const std::int8_t *>(left)) -
           static_cast<std::int32_t>(*static_cast<const std::int8_t *>(right));
}
void update(aim_assist::WorldUpdateEvent *event, std::uint8_t *image) {
    using namespace aim_assist;
    auto &frame = *event->frame;
    if (!frame.player)
        return;
    std::uint16_t owner = 0;
    bool ownerFound = false;
    if (!mc::positionModeIsZero(frame.jni)) {
        Word first = objectMethod(frame.jni, frameHandle(frame.minecraft), 0x158);    // 0x22d10
        first = objectField(frame.jni, first, 0x690);                                 // 0x25eb0
        const Word target = objectField(frame.jni, frameHandle(frame.player), 0x2e8); // 0x23740
        using Find = Word (*)(Word *, Word, Word, ...);
        const Word component = slot<Find>(frame.jni->environment, 0x110)(
            frame.jni->environment, first, identifier(frame.jni, 0x58), target);
        if (component) {
            Word result = objectField(frame.jni, component, 0xc48); // 0x26010
            if (result) {
                result = objectMethod(frame.jni, result, 0x6a8); // 0x26090
                owner = prefixColor(frame.jni, result);
                if (!owner)
                    owner = 0x72;
                ownerFound = true;
            } else {
                result = objectMethod(frame.jni, component, 0xc50); // 0x26030
                if (result) {
                    owner = componentColor(frame.jni, result);
                    ownerFound = true;
                }
            }
        }
    }
    if (!ownerFound)
        owner = entityColor(frame.jni, frameHandle(frame.player));
    const auto players = mc::worldPlayerEntityList(frame.jni, frame.world);
    std::int32_t count = mc::javaListSize(frame.jni, players);
    if (count <= 0)
        return;
    std::uint32_t index = 0;
    do {
        const auto entity =
            mc::javaListElement(frame.jni, players, static_cast<std::int32_t>(index));
        if (!mc::sameJavaObject(frame.jni, frame.player, entity)) {
            const auto code = entityColor(frame.jni, frameHandle(entity));
            bool member = image[0x2eb628] == 1 && code == owner;
            if (!member) {
                const auto low = static_cast<std::uint8_t>(code);
                const std::uint8_t character = static_cast<std::uint8_t>(
                    (static_cast<std::int8_t>(low) >= 0x61 ? 0xa9 : 0xd0) + low);
                member = recovered_sorted_lookup(
                             at<void *>(image, 0x2f9e20), 1,
                             reinterpret_cast<const std::uint32_t *>(image + 0x2f9e28), &character,
                             compare) != nullptr;
            }
            if (member)
                recovered_entity_flags_add(frame.jni, frameHandle(entity), 1);
            else
                recovered_entity_flags_remove(frame.jni, frameHandle(entity), 1);
        }
        ++index;
        count = mc::javaListSize(frame.jni, players);
    } while (static_cast<std::int32_t>(index) < count);
}
void disable(aim_assist::StateChangedEvent *event, std::uint8_t *image) {
    using namespace aim_assist;
    if (event->descriptor != image + 0x2eb400 || event->enabled != 0)
        return;
    auto &frame = *event->frame;
    if (!frame.world)
        return;
    const auto players = mc::worldPlayerEntityList(frame.jni, frame.world);
    std::int32_t count = mc::javaListSize(frame.jni, players);
    if (count <= 0)
        return;
    std::uint32_t index = 0;
    do {
        const auto entity =
            mc::javaListElement(frame.jni, players, static_cast<std::int32_t>(index));
        if (!mc::sameJavaObject(frame.jni, frame.player, entity))
            recovered_entity_flags_remove(frame.jni, frameHandle(entity), 1);
        ++index;
        count = mc::javaListSize(frame.jni, players);
    } while (static_cast<std::int32_t>(index) < count);
}
void cleanup(std::uint8_t *image, void (*release)(void *)) {
    release(aim_assist::at<void *>(image, 0x2f9e20));
    std::memset(image + 0x2f9e20, 0, 16);
}
} // namespace teams

namespace teams {
void colorNames(std::uint8_t *image, const char *const **table, std::uint64_t *count) {
    *table = reinterpret_cast<const char *const *>(image + 0x2eb6a0);
    *count = 16;
}
} // namespace teams
// END SOURCE modules/Teams/Teams.cpp

// Convenient borrowed-state interface

namespace shareable {
class Teams {
  public:
    static constexpr const char *kName = "Teams";
    static constexpr const char *kDescription = "Ignores teammates for specific modules.";
    explicit Teams(std::uint8_t *image) : image_(image) {}
    // Match own nametag. Config key: match_self_color.
    BooleanSetting &match_self_color() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eb610);
    }
    // team_colors. Config key: team_colors.
    ListSetting &team_colors() const {
        return *reinterpret_cast<ListSetting *>(image_ + 0x2eb630);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_teams_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_teams_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_teams_settings(&context, image_, &dependencies);
    }
    static std::uint16_t prefixColor(GameAccessBridge *b, ::teams::Word text) {
        return ::teams::prefixColor(b, text);
    }
    static std::uint16_t componentColor(GameAccessBridge *b, ::teams::Word component) {
        return ::teams::componentColor(b, component);
    }
    static std::uint16_t entityColor(GameAccessBridge *b, ::teams::Word entity) {
        return ::teams::entityColor(b, entity);
    }
    static std::int32_t compare(std::uint64_t argument0, const void *left, const void *right) {
        return ::teams::compare(argument0, left, right);
    }
    void update(aim_assist::WorldUpdateEvent *event) {
        ::teams::update(event, image_);
    }
    void disable(aim_assist::StateChangedEvent *event) {
        ::teams::disable(event, image_);
    }
    void cleanup(void (*release)(void *)) {
        ::teams::cleanup(image_, release);
    }
    void colorNames(const char *const **table, std::uint64_t *count) {
        ::teams::colorNames(image_, table, count);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
