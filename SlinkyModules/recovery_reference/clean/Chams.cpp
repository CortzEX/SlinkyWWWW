#include "Chams.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>

using Word = std::uintptr_t;
static Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word value;
    std::memcpy(&value, bridge->metadata + offset, sizeof(value));
    return value;
}
template <class Function>
static Function slot(const GameAccessBridge *bridge, std::size_t offset) {
    const auto *table = reinterpret_cast<const Word *>(*bridge->environment);
    return reinterpret_cast<Function>(table[offset / sizeof(Word)]);
}
// 0x2ace0 calls float getter 0x240d0 and retains the high word of its raw bits.
extern "C" __declspec(dllexport) std::uint32_t recovered_chams_flags(GameAccessBridge *bridge,
    Word entity, std::uint32_t mask) {
    using Getter = float (*)(Word *, Word, Word);
    const auto bits = std::bit_cast<std::uint32_t>(slot<Getter>(bridge, 0x330)(
        bridge->environment, entity, identifier(bridge, 0x5c0)));
    const auto high = bits & 0xffff0000u;
    const auto flags = high == 0xb3150000u ? bits & 0xffffu : 0u;
    return high | ((flags & mask) != 0);
}
// 0x274f0 forwards three doubles and promotes both float stack arguments.
extern "C" __declspec(dllexport) std::uint64_t recovered_chams_forward(const ChamsRenderRequest *request) {
    const auto copy = *request;
    auto *bridge = copy.bridge;
    using Render = std::uint64_t (*)(Word *, Word, Word, Word, Word, double, double, double, double, double);
    const auto fourth = _mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(copy.fourth)));
    const auto fifth = _mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(copy.fifth)));
    return slot<Render>(bridge, 0x2d8)(bridge->environment, copy.receiver,
        identifier(bridge, 0x948), identifier(bridge, 0x990), copy.entity,
        copy.first, copy.second, copy.third, fourth, fifth);
}
// 0x3e730 snapshots arguments, but reloads graphics cells after dependency calls.
extern "C" __declspec(dllexport) std::uint64_t recovered_chams_wrapper(const ChamsRenderRequest *request,
    std::uint8_t enabled, const BooleanSetting *hide_friendlies, const ChamsGraphics *graphics,
    const ChamsOffsetConstants *constants) {
    const auto copy = *request;
    if (enabled == 1 && !(recovered_chams_flags(copy.bridge, copy.entity,
        static_cast<std::uint32_t>(hide_friendlies->current) * 5u + 2u) & 0xff)) {
        (*graphics->begin)(0x8037);
        (*graphics->set_offset)(constants->first, constants->second);
        recovered_chams_forward(&copy);
        return (*graphics->end)(0x8037);
    }
    return recovered_chams_forward(&copy);
}
// 0x8350 captures metadata and incoming JNI environment in a local two-word bridge.
extern "C" __declspec(dllexport) std::uint64_t recovered_chams_hook(const std::uint8_t *const *metadata,
    Word *environment, const ChamsRenderRequest *request, std::uint8_t enabled,
    const BooleanSetting *hide_friendlies, const ChamsGraphics *graphics, const ChamsOffsetConstants *constants) {
    GameAccessBridge bridge{*metadata, environment};
    auto copy = *request;
    copy.bridge = &bridge;
    return recovered_chams_wrapper(&copy, enabled, hide_friendlies, graphics, constants);
}
// 0x3e880 / 0x3e8c0 share the checkbox and Boolean persistence helpers.
extern "C" __declspec(dllexport) std::uint64_t recovered_chams_typed_ui(std::uint64_t ui,
    std::uint64_t layout, BooleanSetting *hide_friendlies, UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Main");
    return recovered_checkbox_control(layout, ui, hide_friendlies, dirty, &endpoints->controls);
}
extern "C" __declspec(dllexport) void recovered_chams_typed_settings(SettingsContext *context,
    BooleanSetting *hide_friendlies, const SettingsDependencies *dependencies) {
    recovered_boolean_settings(context, "hide_friendlies", hide_friendlies, dependencies);
}
