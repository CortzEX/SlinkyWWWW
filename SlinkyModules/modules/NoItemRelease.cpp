// No Item Release

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/No_Item_Release.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_No_Item_Release.cpp
#include "../runtime/native/verified/module_surface.hpp"

// No Item Release: lib_win settings 0x33600.
// UI 0x335c0.
static constexpr UiStep ui_steps_Surface_No_Item_Release[] = {
    {UiControl::section, "Main", 0},
    {UiControl::choice, nullptr, 0x2ec5b8},
};
static constexpr SettingsStep settings_steps_Surface_No_Item_Release[] = {
    {SettingsControl::choice, "mode", 0x2ec5b8},
};
static constexpr ModuleSurface surface_Surface_No_Item_Release{
    ui_steps_Surface_No_Item_Release, std::size(ui_steps_Surface_No_Item_Release),
    settings_steps_Surface_No_Item_Release, std::size(settings_steps_Surface_No_Item_Release)};

extern "C" __declspec(dllexport) void
recovered_no_item_release_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                             const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_No_Item_Release, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_no_item_release_settings(SettingsContext *context, std::uint8_t *image,
                                   const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_No_Item_Release, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_No_Item_Release.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/No_Item_Release/No_Item_Release.cpp
#ifndef SLINKY_SHARE_753257D20A3F3749BE5A
#define SLINKY_SHARE_753257D20A3F3749BE5A
// BEGIN SOURCE native/verified/No_Item_Release.hpp
#include "../runtime/native/verified/module_game_access.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/native/verified/module_format.hpp"

struct NoItemReleaseEvent {
    std::uintptr_t event_type;
    GameAccessBridge *bridge;
    std::uintptr_t packet;
    std::uintptr_t reserved;
    std::uint32_t reserved2;
    std::uint32_t disposition;
};
struct NoItemReleaseState {
    std::uint8_t active;
};
struct NoItemReleaseDependencies {
    std::uintptr_t (*use_packet)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*release_packet)(GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*release_action)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*packet_stack)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*stack_item)(GameAccessBridge *, std::uintptr_t);
    std::int32_t (*item_id)(GameAccessBridge *, std::uintptr_t);
};
static_assert(sizeof(NoItemReleaseEvent) == 40);
static_assert(offsetof(NoItemReleaseEvent, bridge) == 8);
static_assert(offsetof(NoItemReleaseEvent, packet) == 16);
static_assert(offsetof(NoItemReleaseEvent, disposition) == 36);
static_assert(sizeof(NoItemReleaseState) == 1);
static_assert(sizeof(NoItemReleaseDependencies) == 48);

extern "C" {
__declspec(dllexport) void recovered_no_item_release_packet(NoItemReleaseEvent *,
                                                            const ChoiceSetting *mode,
                                                            NoItemReleaseState *,
                                                            const NoItemReleaseDependencies *);
__declspec(dllexport) void recovered_bind_no_item_release_access(NoItemReleaseDependencies *);
__declspec(dllexport) std::uintptr_t recovered_no_item_release_use_packet(GameAccessBridge *,
                                                                          std::uintptr_t);
__declspec(dllexport) std::uintptr_t recovered_no_item_release_release_packet(GameAccessBridge *,
                                                                              std::uintptr_t);
__declspec(dllexport) std::uint32_t recovered_no_item_release_action(GameAccessBridge *,
                                                                     std::uintptr_t);
__declspec(dllexport) std::uintptr_t recovered_no_item_release_packet_stack(GameAccessBridge *,
                                                                            std::uintptr_t);
__declspec(dllexport) std::uintptr_t recovered_no_item_release_stack_item(GameAccessBridge *,
                                                                          std::uintptr_t);
__declspec(dllexport) void recovered_no_item_release_typed_ui(std::uint64_t ui,
                                                              std::uint64_t layout,
                                                              ChoiceSetting *mode,
                                                              const SurfaceUiDependencies *);
__declspec(dllexport) void
recovered_no_item_release_typed_settings(SettingsContext *, ChoiceSetting *mode,
                                         const ValueSettingsDependencies *);
__declspec(dllexport) std::uint64_t recovered_no_item_release_label(char *destination,
                                                                    const ChoiceSetting *mode,
                                                                    const char *const *labels,
                                                                    FormatState *);
}
// END SOURCE native/verified/No_Item_Release.hpp

#endif // SLINKY_SHARE_753257D20A3F3749BE5A

#include "../runtime/native/verified/module_access_helpers.hpp"
#include <cstring>

using Word = std::uintptr_t;

static Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word result;
    std::memcpy(&result, bridge->metadata + offset, sizeof(result));
    return result;
}

template <class Function> static Function slot(const GameAccessBridge *bridge, std::size_t offset) {
    const auto *table = reinterpret_cast<const Word *>(*bridge->environment);
    return reinterpret_cast<Function>(table[offset / sizeof(Word)]);
}

static Word packet_of_class(GameAccessBridge *bridge, Word packet, std::size_t offset) {
    using Predicate = std::uint8_t (*)(Word *, Word, Word);
    return slot<Predicate>(bridge, 0x100)(bridge->environment, packet, identifier(bridge, offset))
               ? packet
               : 0;
}

// 0x26580/0x264f0 retain the original packet when the JNI predicate's low byte is nonzero.
extern "C" __declspec(dllexport) Word recovered_no_item_release_use_packet(GameAccessBridge *bridge,
                                                                           Word packet) {
    return packet_of_class(bridge, packet, 0x748);
}
extern "C" __declspec(dllexport) Word
recovered_no_item_release_release_packet(GameAccessBridge *bridge, Word packet) {
    return packet_of_class(bridge, packet, 0x738);
}

// 0x26530 chooses its ABI from the version captured before the first getter.
extern "C" __declspec(dllexport) std::uint32_t
recovered_no_item_release_action(GameAccessBridge *bridge, Word packet) {
    std::uint32_t version;
    std::memcpy(&version, bridge->metadata, sizeof(version));
    if (!version) {
        using IntegerGetter = std::uint32_t (*)(Word *, Word, Word);
        return slot<IntegerGetter>(bridge, 0x320)(bridge->environment, packet,
                                                  identifier(bridge, 0x740));
    }
    using ObjectGetter = Word (*)(Word *, Word, Word);
    const auto action =
        slot<ObjectGetter>(bridge, 0x2f8)(bridge->environment, packet, identifier(bridge, 0x740));
    return static_cast<std::uint32_t>(recovered_access_helper(bridge, 0x271a0, action, 0, 0));
}

// 0x265c0 and 0x25d10 use distinct object getter slots.
extern "C" __declspec(dllexport) Word
recovered_no_item_release_packet_stack(GameAccessBridge *bridge, Word packet) {
    using Getter = Word (*)(Word *, Word, Word);
    return slot<Getter>(bridge, 0x2f8)(bridge->environment, packet, identifier(bridge, 0x750));
}
extern "C" __declspec(dllexport) Word recovered_no_item_release_stack_item(GameAccessBridge *bridge,
                                                                           Word stack) {
    using Getter = Word (*)(Word *, Word, Word);
    return slot<Getter>(bridge, 0x110)(bridge->environment, stack, identifier(bridge, 0x5f8));
}

extern "C" __declspec(dllexport) void
recovered_bind_no_item_release_access(NoItemReleaseDependencies *dependencies) {
    *dependencies = {recovered_no_item_release_use_packet, recovered_no_item_release_release_packet,
                     recovered_no_item_release_action,     recovered_no_item_release_packet_stack,
                     recovered_no_item_release_stack_item, recovered_game_item_numeric_id};
}

// 0x334c0 retains the bridge read after the first predicate through the use-item chain.
extern "C" __declspec(dllexport) void
recovered_no_item_release_packet(NoItemReleaseEvent *event, const ChoiceSetting *mode,
                                 NoItemReleaseState *state,
                                 const NoItemReleaseDependencies *dependencies) {
    const auto use_packet = dependencies->use_packet(event->bridge, event->packet);
    auto *bridge = event->bridge;
    if (!use_packet) {
        const auto release_packet = dependencies->release_packet(bridge, event->packet);
        if (!release_packet || !state->active)
            return;
        if (dependencies->release_action(event->bridge, release_packet) == 5)
            event->disposition = 2;
        state->active = 0;
        return;
    }
    const auto stack = dependencies->packet_stack(bridge, use_packet);
    if (!stack) {
        state->active = 0;
        return;
    }
    const auto item = dependencies->stack_item(bridge, stack);
    if (!item) {
        state->active = 0;
        return;
    }
    auto id = static_cast<std::uint32_t>(dependencies->item_id(bridge, item));
    const auto bit = id - 0x105u;
    if (bit < 23 && ((0x4088c0u >> bit) & 1)) {
        if (mode->current == 1) {
            state->active = 0;
            return;
        }
    } else if (id == 0x105 || id == 0x15a || mode->current == 0) {
        state->active = 0;
        return;
    }
    id = static_cast<std::uint32_t>(dependencies->item_id(bridge, item));
    state->active = id != 0x105 && id != 0x15a;
}

// 0x335c0 / 0x33600.
extern "C" __declspec(dllexport) void
recovered_no_item_release_typed_ui(std::uint64_t ui, std::uint64_t layout, ChoiceSetting *mode,
                                   const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, mode);
}
extern "C" __declspec(dllexport) void
recovered_no_item_release_typed_settings(SettingsContext *context, ChoiceSetting *mode,
                                         const ValueSettingsDependencies *dependencies) {
    recovered_choice_settings(context, "mode", mode, dependencies);
}

// 0x33620 indexes the caller's original label table, independently of mode->options.
extern "C" __declspec(dllexport) std::uint64_t
recovered_no_item_release_label(char *destination, const ChoiceSetting *mode,
                                const char *const *labels, FormatState *format) {
    return recovered_format(format, destination, 32, "%s", labels[mode->current]);
}
// END SOURCE modules/No_Item_Release/No_Item_Release.cpp

#ifndef SLINKY_SHARE_8FBF829377AA35B066E6
#define SLINKY_SHARE_8FBF829377AA35B066E6
// BEGIN SOURCE modules/No_Item_Release/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/No_Item_Release/Api.hpp

#endif // SLINKY_SHARE_8FBF829377AA35B066E6

// Convenient borrowed-state interface

namespace shareable {
class NoItemRelease {
  public:
    static constexpr const char *kName = "No Item Release";
    static constexpr const char *kDescription = "Hides item release from server.";
    explicit NoItemRelease(std::uint8_t *image) : image_(image) {}
    // Mode. Config key: mode.
    ChoiceSetting &mode() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2ec5b8);
    }
    // Option labels observed in the captured metadata.
    enum class ModeMode : std::uint32_t { Sword = 0, Consumable = 1, All = 2 };
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_no_item_release_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_no_item_release_settings(&context, image_, &dependencies);
    }
    static Word usePacket(GameAccessBridge *bridge, Word packet) {
        return ::recovered_no_item_release_use_packet(bridge, packet);
    }
    static Word releasePacket(GameAccessBridge *bridge, Word packet) {
        return ::recovered_no_item_release_release_packet(bridge, packet);
    }
    static std::uint32_t action(GameAccessBridge *bridge, Word packet) {
        return ::recovered_no_item_release_action(bridge, packet);
    }
    static Word packetStack(GameAccessBridge *bridge, Word packet) {
        return ::recovered_no_item_release_packet_stack(bridge, packet);
    }
    static Word stackItem(GameAccessBridge *bridge, Word stack) {
        return ::recovered_no_item_release_stack_item(bridge, stack);
    }
    static void bindAccess(NoItemReleaseDependencies *dependencies) {
        ::recovered_bind_no_item_release_access(dependencies);
    }
    static void packet(NoItemReleaseEvent *event, const ChoiceSetting *mode,
                       NoItemReleaseState *state, const NoItemReleaseDependencies *dependencies) {
        ::recovered_no_item_release_packet(event, mode, state, dependencies);
    }
    static void typedUi(std::uint64_t ui, std::uint64_t layout, ChoiceSetting *mode,
                        const SurfaceUiDependencies *dependencies) {
        ::recovered_no_item_release_typed_ui(ui, layout, mode, dependencies);
    }
    static void typedSettings(SettingsContext *context, ChoiceSetting *mode,
                              const ValueSettingsDependencies *dependencies) {
        ::recovered_no_item_release_typed_settings(context, mode, dependencies);
    }
    static std::uint64_t label(char *destination, const ChoiceSetting *mode,
                               const char *const *labels, FormatState *format) {
        return ::recovered_no_item_release_label(destination, mode, labels, format);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
