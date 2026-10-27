#include "No_Item_Release.hpp"
#include "module_access_helpers.hpp"
#include <cstring>

using Word = std::uintptr_t;

static Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word result;
    std::memcpy(&result, bridge->metadata + offset, sizeof(result));
    return result;
}

template <class Function>
static Function slot(const GameAccessBridge *bridge, std::size_t offset) {
    const auto *table = reinterpret_cast<const Word *>(*bridge->environment);
    return reinterpret_cast<Function>(table[offset / sizeof(Word)]);
}

static Word packet_of_class(GameAccessBridge *bridge, Word packet, std::size_t offset) {
    using Predicate = std::uint8_t (*)(Word *, Word, Word);
    return slot<Predicate>(bridge, 0x100)(bridge->environment, packet, identifier(bridge, offset)) ? packet : 0;
}

// 0x26580/0x264f0 retain the original packet when the JNI predicate's low byte is nonzero.
extern "C" __declspec(dllexport) Word recovered_no_item_release_use_packet(GameAccessBridge *bridge, Word packet) {
    return packet_of_class(bridge, packet, 0x748);
}
extern "C" __declspec(dllexport) Word recovered_no_item_release_release_packet(GameAccessBridge *bridge, Word packet) {
    return packet_of_class(bridge, packet, 0x738);
}

// 0x26530 chooses its ABI from the version captured before the first getter.
extern "C" __declspec(dllexport) std::uint32_t recovered_no_item_release_action(GameAccessBridge *bridge, Word packet) {
    std::uint32_t version;
    std::memcpy(&version, bridge->metadata, sizeof(version));
    if (!version) {
        using IntegerGetter = std::uint32_t (*)(Word *, Word, Word);
        return slot<IntegerGetter>(bridge, 0x320)(bridge->environment, packet, identifier(bridge, 0x740));
    }
    using ObjectGetter = Word (*)(Word *, Word, Word);
    const auto action = slot<ObjectGetter>(bridge, 0x2f8)(bridge->environment, packet, identifier(bridge, 0x740));
    return static_cast<std::uint32_t>(recovered_access_helper(bridge, 0x271a0, action, 0, 0));
}

// 0x265c0 and 0x25d10 use distinct object getter slots.
extern "C" __declspec(dllexport) Word recovered_no_item_release_packet_stack(GameAccessBridge *bridge, Word packet) {
    using Getter = Word (*)(Word *, Word, Word);
    return slot<Getter>(bridge, 0x2f8)(bridge->environment, packet, identifier(bridge, 0x750));
}
extern "C" __declspec(dllexport) Word recovered_no_item_release_stack_item(GameAccessBridge *bridge, Word stack) {
    using Getter = Word (*)(Word *, Word, Word);
    return slot<Getter>(bridge, 0x110)(bridge->environment, stack, identifier(bridge, 0x5f8));
}

extern "C" __declspec(dllexport) void recovered_bind_no_item_release_access(NoItemReleaseDependencies *dependencies) {
    *dependencies = {recovered_no_item_release_use_packet, recovered_no_item_release_release_packet,
                     recovered_no_item_release_action, recovered_no_item_release_packet_stack,
                     recovered_no_item_release_stack_item, recovered_game_item_numeric_id};
}

// 0x334c0 retains the bridge read after the first predicate through the use-item chain.
extern "C" __declspec(dllexport) void recovered_no_item_release_packet(
    NoItemReleaseEvent *event, const ChoiceSetting *mode, NoItemReleaseState *state,
    const NoItemReleaseDependencies *dependencies) {
    const auto use_packet = dependencies->use_packet(event->bridge, event->packet);
    auto *bridge = event->bridge;
    if (!use_packet) {
        const auto release_packet = dependencies->release_packet(bridge, event->packet);
        if (!release_packet || !state->active) return;
        if (dependencies->release_action(event->bridge, release_packet) == 5) event->disposition = 2;
        state->active = 0;
        return;
    }
    const auto stack = dependencies->packet_stack(bridge, use_packet);
    if (!stack) { state->active = 0; return; }
    const auto item = dependencies->stack_item(bridge, stack);
    if (!item) { state->active = 0; return; }
    auto id = static_cast<std::uint32_t>(dependencies->item_id(bridge, item));
    const auto bit = id - 0x105u;
    if (bit < 23 && ((0x4088c0u >> bit) & 1)) {
        if (mode->current == 1) { state->active = 0; return; }
    } else if (id == 0x105 || id == 0x15a || mode->current == 0) {
        state->active = 0;
        return;
    }
    id = static_cast<std::uint32_t>(dependencies->item_id(bridge, item));
    state->active = id != 0x105 && id != 0x15a;
}

// 0x335c0 / 0x33600.
extern "C" __declspec(dllexport) void recovered_no_item_release_typed_ui(
    std::uint64_t ui, std::uint64_t layout, ChoiceSetting *mode, const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, mode);
}
extern "C" __declspec(dllexport) void recovered_no_item_release_typed_settings(
    SettingsContext *context, ChoiceSetting *mode, const ValueSettingsDependencies *dependencies) {
    recovered_choice_settings(context, "mode", mode, dependencies);
}

// 0x33620 indexes the caller's original label table, independently of mode->options.
extern "C" __declspec(dllexport) std::uint64_t recovered_no_item_release_label(
    char *destination, const ChoiceSetting *mode, const char *const *labels, FormatState *format) {
    return recovered_format(format, destination, 32, "%s", labels[mode->current]);
}
