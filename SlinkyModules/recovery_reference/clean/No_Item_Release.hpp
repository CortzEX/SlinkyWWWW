#pragma once

#include "module_game_access.hpp"
#include "module_surface.hpp"
#include "module_format.hpp"

struct NoItemReleaseEvent {
    std::uintptr_t event_type;
    GameAccessBridge *bridge;
    std::uintptr_t packet;
    std::uintptr_t reserved;
    std::uint32_t reserved2;
    std::uint32_t disposition;
};
struct NoItemReleaseState { std::uint8_t active; };
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
__declspec(dllexport) void recovered_no_item_release_packet(NoItemReleaseEvent *, const ChoiceSetting *mode, NoItemReleaseState *, const NoItemReleaseDependencies *);
__declspec(dllexport) void recovered_bind_no_item_release_access(NoItemReleaseDependencies *);
__declspec(dllexport) std::uintptr_t recovered_no_item_release_use_packet(GameAccessBridge *, std::uintptr_t);
__declspec(dllexport) std::uintptr_t recovered_no_item_release_release_packet(GameAccessBridge *, std::uintptr_t);
__declspec(dllexport) std::uint32_t recovered_no_item_release_action(GameAccessBridge *, std::uintptr_t);
__declspec(dllexport) std::uintptr_t recovered_no_item_release_packet_stack(GameAccessBridge *, std::uintptr_t);
__declspec(dllexport) std::uintptr_t recovered_no_item_release_stack_item(GameAccessBridge *, std::uintptr_t);
__declspec(dllexport) void recovered_no_item_release_typed_ui(std::uint64_t ui, std::uint64_t layout, ChoiceSetting *mode, const SurfaceUiDependencies *);
__declspec(dllexport) void recovered_no_item_release_typed_settings(SettingsContext *, ChoiceSetting *mode, const ValueSettingsDependencies *);
__declspec(dllexport) std::uint64_t recovered_no_item_release_label(char *destination, const ChoiceSetting *mode, const char *const *labels, FormatState *);
}
