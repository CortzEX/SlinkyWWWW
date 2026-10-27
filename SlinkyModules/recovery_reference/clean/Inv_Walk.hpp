#pragma once

#include "Timer.hpp"
#include "module_choice_ui.hpp"
#include "module_format.hpp"

struct InvWalkSettings {
    ChoiceSetting mode;
    std::uint8_t mode_flag;
    std::uint8_t mode_padding[7];
    const char *stop_options[3];
    ChoiceSetting stop_on_click;
    std::uint8_t stop_on_click_flag;
    std::uint8_t stop_on_click_padding[7];
    NumberSetting stop_duration;
    ChoiceSetting stop_non_inventory;
    std::uint8_t stop_non_inventory_flag;
    std::uint8_t padding[7];
};

struct InvWalkState {
    volatile std::uintptr_t packets[32];
    volatile std::uint64_t count;
    volatile std::uint8_t stopped;
    std::uint8_t padding[3];
    volatile std::uint32_t tick;
    volatile std::uint32_t phase;
    volatile std::uint32_t last_tick;
    volatile std::uint8_t busy;
    std::uint8_t padding2[7];
};

struct InvWalkPacketEvent {
    std::uintptr_t event_type;
    GameAccessBridge *bridge;
    std::uintptr_t destination;
    std::uintptr_t packet;
    std::uint8_t cancelled;
    std::uint8_t padding[7];
};

struct InvWalkDependencies {
    std::uintptr_t (*screen)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*options)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*forward_key)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*back_key)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*left_key)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*right_key)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*jump_key)(GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*physical_key)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*inventory_screen)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*inventory)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*interaction)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*destination)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*held_item)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*container)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*slots)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*slot)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    std::uintptr_t (*close_action)(GameAccessBridge *, std::uint32_t);
    std::uintptr_t (*action_type)(GameAccessBridge *);
    std::uintptr_t (*open_action)(GameAccessBridge *, std::uintptr_t);
    void (*send)(GameAccessBridge *, std::uintptr_t, std::uintptr_t);
    void (*set_key)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    void (*set_sprinting)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    std::uintptr_t (*sprint_key)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*action_packet)(GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*packet_action_type)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*click_packet)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*other_packet)(GameAccessBridge *, std::uintptr_t);
    std::uint8_t (*drain_first)(GameAccessBridge *);
    std::uint8_t (*drain_second)(GameAccessBridge *);
};

static_assert(sizeof(InvWalkSettings) == 272);
static_assert(offsetof(InvWalkSettings, mode_flag) == 56);
static_assert(offsetof(InvWalkSettings, stop_options) == 64);
static_assert(offsetof(InvWalkSettings, stop_on_click_flag) == 144);
static_assert(offsetof(InvWalkSettings, stop_non_inventory_flag) == 264);
static_assert(offsetof(InvWalkSettings, stop_on_click) == 88);
static_assert(offsetof(InvWalkSettings, stop_duration) == 152);
static_assert(offsetof(InvWalkSettings, stop_non_inventory) == 208);
static_assert(sizeof(InvWalkState) == 288);
static_assert(offsetof(InvWalkState, count) == 256);
static_assert(offsetof(InvWalkState, stopped) == 264);
static_assert(offsetof(InvWalkState, tick) == 268);
static_assert(offsetof(InvWalkState, phase) == 272);
static_assert(offsetof(InvWalkState, last_tick) == 276);
static_assert(offsetof(InvWalkState, busy) == 280);
static_assert(sizeof(InvWalkPacketEvent) == 40);
static_assert(offsetof(InvWalkPacketEvent, cancelled) == 32);
static_assert(sizeof(InvWalkDependencies) == 232);

extern "C" {
__declspec(dllexport) void recovered_bind_inv_walk_access(InvWalkDependencies *);
__declspec(dllexport) std::uint64_t recovered_inv_walk_typed_ui(std::uint64_t ui, std::uint64_t layout,
    InvWalkSettings *, UiDirtyState *, const ChoiceUiEndpoints *);
__declspec(dllexport) void recovered_inv_walk_typed_settings(SettingsContext *, InvWalkSettings *, const ValueSettingsDependencies *);
__declspec(dllexport) std::uint64_t recovered_inv_walk_label(char *, const ChoiceSetting *, const char *const *labels, FormatState *);
__declspec(dllexport) void recovered_inv_walk_typed_update(TimerEvent *, const InvWalkSettings *, InvWalkState *, const InvWalkDependencies *);
__declspec(dllexport) void recovered_inv_walk_typed_disable(TimerEvent *, std::uintptr_t module_identity, InvWalkState *, const InvWalkDependencies *);
__declspec(dllexport) void recovered_inv_walk_typed_packet(InvWalkPacketEvent *, const InvWalkSettings *, InvWalkState *, const InvWalkDependencies *);
__declspec(dllexport) void recovered_inv_walk_typed_finish(TimerEvent *, InvWalkState *, const InvWalkDependencies *);
__declspec(dllexport) std::uint8_t recovered_inv_walk_typed_flush(GameAccessBridge *, std::uintptr_t client, InvWalkState *, const InvWalkDependencies *);
}
