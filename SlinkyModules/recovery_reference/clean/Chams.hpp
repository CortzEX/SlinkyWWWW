#pragma once
#include "module_game_access.hpp"
#include "module_ui_controls.hpp"

struct ChamsRenderRequest {
    GameAccessBridge *bridge;
    std::uintptr_t receiver, entity;
    double first, second, third;
    float fourth, fifth;
};
using ChamsCapabilityEndpoint = std::uint64_t (*)(std::uint32_t);
using ChamsOffsetEndpoint = std::uint64_t (*)(float, float);
struct ChamsGraphics {
    ChamsCapabilityEndpoint *begin;
    ChamsOffsetEndpoint *set_offset;
    ChamsCapabilityEndpoint *end;
};
struct ChamsOffsetConstants { float first, second; };
static_assert(sizeof(ChamsRenderRequest) == 56);
static_assert(offsetof(ChamsRenderRequest, first) == 24);
static_assert(offsetof(ChamsRenderRequest, fourth) == 48);
static_assert(sizeof(ChamsGraphics) == 24);
static_assert(sizeof(ChamsOffsetConstants) == 8);

extern "C" {
__declspec(dllexport) std::uint32_t recovered_chams_flags(GameAccessBridge *, std::uintptr_t entity, std::uint32_t mask);
__declspec(dllexport) std::uint64_t recovered_chams_forward(const ChamsRenderRequest *);
__declspec(dllexport) std::uint64_t recovered_chams_wrapper(const ChamsRenderRequest *, std::uint8_t enabled,
    const BooleanSetting *hide_friendlies, const ChamsGraphics *, const ChamsOffsetConstants *);
__declspec(dllexport) std::uint64_t recovered_chams_hook(const std::uint8_t *const *metadata,
    std::uintptr_t *environment, const ChamsRenderRequest *, std::uint8_t enabled,
    const BooleanSetting *hide_friendlies, const ChamsGraphics *, const ChamsOffsetConstants *);
__declspec(dllexport) std::uint64_t recovered_chams_typed_ui(std::uint64_t ui, std::uint64_t layout,
    BooleanSetting *hide_friendlies, UiDirtyState *, const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_chams_typed_settings(SettingsContext *, BooleanSetting *hide_friendlies,
    const SettingsDependencies *);
}
