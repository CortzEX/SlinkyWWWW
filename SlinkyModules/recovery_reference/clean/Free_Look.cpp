#include "Free_Look.hpp"
#include "module_access_helpers.hpp"
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

// 0x23170 / 0x9dc0 reload bridge pointers between yaw and pitch, retaining the player.
static std::uint64_t player_angles(GameAccessBridge *bridge, Word player) {
    using Getter = float (*)(Word *, Word, Word);
    const auto yaw = slot<Getter>(bridge, 0x330)(bridge->environment, player, identifier(bridge, 0x298));
    const auto pitch = slot<Getter>(bridge, 0x330)(bridge->environment, player, identifier(bridge, 0x2a0));
    return std::bit_cast<std::uint64_t>(CameraRotation{yaw, pitch});
}
static Word options(GameAccessBridge *bridge, Word client) {
    return recovered_access_helper(bridge, 0x22cf0, client, 0, 0);
}
// 0x25310 and 0x25330.
static std::uint32_t perspective(GameAccessBridge *bridge, Word options_object) {
    using Getter = std::uint32_t (*)(Word *, Word, Word);
    return slot<Getter>(bridge, 0x320)(bridge->environment, options_object, identifier(bridge, 0x3c0));
}
static void set_perspective(GameAccessBridge *bridge, Word options_object, std::uint32_t value) {
    using Setter = void (*)(Word *, Word, Word, std::uint32_t);
    slot<Setter>(bridge, 0x368)(bridge->environment, options_object, identifier(bridge, 0x3c0), value);
}
extern "C" __declspec(dllexport) void recovered_bind_free_look_access(FreeLookDependencies *dependencies) {
    *dependencies = {player_angles, options, perspective, set_perspective};
}

// 0x29fa0 wraps the yaw difference, marks the angle updated, then reloads current yaw.
extern "C" __declspec(dllexport) void recovered_free_look_restore(
    CameraAngleState *angles, const AngleWrapConstants *constants, std::uint64_t packed_rotation) {
    const auto incoming = std::bit_cast<CameraRotation>(packed_rotation);
    const auto difference = _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(incoming.yaw), _mm_set_ss(angles->rotation.yaw)));
    const auto wrapped = recovered_wrap_angle(difference, constants);
    angles->updated = 1;
    angles->rotation.yaw = _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(wrapped), _mm_set_ss(angles->rotation.yaw)));
    angles->rotation.pitch = incoming.pitch;
}

// 0x37020 retains the initial game pointer, but rereads the event flag after options lookup.
extern "C" __declspec(dllexport) void recovered_free_look_lifecycle(
    FreeLookEvent *event, Word module_identity, const ChoiceSetting *setting, FreeLookState *state,
    CameraAngleState *angles, const AngleWrapConstants *constants, const FreeLookDependencies *dependencies) {
    if (event->module != module_identity) return;
    auto *game = event->game;
    if (!game->world) return;
    if (event->enabled == 1) {
        state->enabled = 1;
        // 0x29f80 / 0x29f90 read the active byte and packed camera rotation.
        state->saved_rotation = angles->active ? angles->rotation :
            std::bit_cast<CameraRotation>(dependencies->player_angles(game->bridge, game->player));
    }
    const auto options_object = dependencies->options(game->bridge, game->client);
    if (event->enabled) {
        state->saved_perspective = dependencies->perspective(game->bridge, options_object);
        dependencies->set_perspective(game->bridge, options_object, setting->current);
    } else {
        dependencies->set_perspective(game->bridge, options_object, state->saved_perspective);
        if (state->enabled == 1) {
            recovered_free_look_restore(angles, constants, std::bit_cast<std::uint64_t>(state->saved_rotation));
            state->enabled = 0;
        }
    }
}

// 0x37100 preserves all bytes outside the flag and packed yaw/pitch fields.
extern "C" __declspec(dllexport) void recovered_free_look_rotation(
    FreeLookRotationEvent *event, const FreeLookState *state) {
    event->override_rotation = 1;
    event->rotation = state->saved_rotation;
}

// 0x37120 and 0x37160 use a single choice record.
extern "C" __declspec(dllexport) void recovered_free_look_typed_ui(
    std::uint64_t ui, std::uint64_t layout, ChoiceSetting *setting, const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->choice(layout, ui, setting);
}
extern "C" __declspec(dllexport) void recovered_free_look_typed_settings(
    SettingsContext *context, ChoiceSetting *setting, const ValueSettingsDependencies *dependencies) {
    recovered_choice_settings(context, "target_perspective", setting, dependencies);
}
