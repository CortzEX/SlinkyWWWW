#include "Inv_Walk.hpp"
#include "Null_Move.hpp"
#include "Sprint_Reset_runtime.hpp"
#include "module_access_helpers.hpp"
#include <cstring>

namespace {
using Word = std::uintptr_t;
using ObjectGetter = Word (*)(Word *, Word, Word);
using Predicate = std::uint8_t (*)(Word *, Word, Word);
using ObjectMethod = Word (*)(Word *, Word, Word, ...);

Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word value;
    std::memcpy(&value, bridge->metadata + offset, sizeof(value));
    return value;
}
template <class Function>
Function slot(const GameAccessBridge *bridge, std::size_t offset) {
    return reinterpret_cast<Function>(reinterpret_cast<const Word *>(*bridge->environment)[offset / sizeof(Word)]);
}
template <std::size_t Offset>
Word object_field(GameAccessBridge *bridge, Word object) {
    return slot<ObjectGetter>(bridge, 0x2f8)(bridge->environment, object, identifier(bridge, Offset));
}
template <std::uint32_t Index>
Word key(GameAccessBridge *bridge, Word options) {
    return recovered_null_move_key(bridge, options, Index);
}
Word options(GameAccessBridge *bridge, Word client) {
    return recovered_access_helper(bridge, 0x22cf0, client, 0, 0);
}
void set_key(GameAccessBridge *bridge, Word key, std::uint32_t value) {
    recovered_access_helper(bridge, 0x25460, key, value, 0);
}
void set_sprinting(GameAccessBridge *bridge, Word player, std::uint32_t value) {
    recovered_sprint_set_player(bridge, player, static_cast<std::uint8_t>(value));
}
// 0x22d10: unlike a field getter, interaction uses CallObjectMethod.
Word interaction(GameAccessBridge *bridge, Word client) {
    return slot<ObjectMethod>(bridge, 0x110)(bridge->environment, client, identifier(bridge, 0x158));
}
std::uint8_t inventory_screen(GameAccessBridge *bridge, Word screen) {
    return slot<Predicate>(bridge, 0x100)(bridge->environment, screen, identifier(bridge, 0x8a0)) != 0;
}
// 0x26ec0 / 0x26f00 / 0x26ff0 retain the caller's packet when AL is nonzero.
template <std::size_t Class>
Word packet(GameAccessBridge *bridge, Word object) {
    return slot<Predicate>(bridge, 0x100)(bridge->environment, object, identifier(bridge, Class)) ? object : 0;
}
// 0x26fb0 reloads the bridge for the enum ordinal after fetching the enum object.
std::uint32_t packet_action_type(GameAccessBridge *bridge, Word packet) {
    const auto type = object_field<0xc68>(bridge, packet);
    return static_cast<std::uint32_t>(recovered_access_helper(bridge, 0x271a0, type, 0, 0));
}
// 0x26f40.
Word action_type(GameAccessBridge *bridge) {
    return slot<ObjectGetter>(bridge, 0x488)(bridge->environment, identifier(bridge, 0xc78), identifier(bridge, 0xc80));
}
// 0x26f70 / 0x27030. The latter forwards only the low DWORD.
Word open_action(GameAccessBridge *bridge, Word type) {
    return slot<ObjectMethod>(bridge, 0xe0)(bridge->environment, identifier(bridge, 0xc60), identifier(bridge, 0xc70), type);
}
Word close_action(GameAccessBridge *bridge, std::uint32_t value) {
    return slot<ObjectMethod>(bridge, 0xe0)(bridge->environment, identifier(bridge, 0xc88), identifier(bridge, 0xc90), value);
}
// 0x25f80 selects the overload before the array call, then rereads metadata,
// environment and the JNI target. The overload selection survives those changes.
void send(GameAccessBridge *bridge, Word destination, Word packet) {
    using Method = void (*)(Word *, Word, Word, ...);
    if (identifier(bridge, 0x6f8)) {
        using Array = Word (*)(Word *, std::uint32_t, Word, Word);
        const auto array = slot<Array>(bridge, 0x560)(bridge->environment, 0, identifier(bridge, 0xc58), 0);
        slot<Method>(bridge, 0x1e8)(bridge->environment, destination, identifier(bridge, 0x6f8), packet, array);
    } else {
        slot<Method>(bridge, 0x1e8)(bridge->environment, destination, identifier(bridge, 0x700), packet);
    }
}
// 0x25900 / 0x257a0 have three JNI arguments; physical-key queries have four.
template <std::size_t Class, std::size_t Method>
std::uint8_t drain(GameAccessBridge *bridge) {
    return slot<Predicate>(bridge, 0x3a8)(bridge->environment, identifier(bridge, Class), identifier(bridge, Method)) != 0;
}
}

extern "C" __declspec(dllexport) void recovered_bind_inv_walk_access(InvWalkDependencies *dependencies) {
    WeaponDependencies weapons;
    recovered_bind_weapon_access(&weapons);
    *dependencies = {
        recovered_sprint_screen, options, key<4>, key<3>, key<5>, key<2>, key<6>,
        recovered_sprint_reset_physical_word, inventory_screen, recovered_game_inventory,
        interaction, object_field<0x698>, object_field<0x5e0>, object_field<0x5b0>, object_field<0xca0>,
        weapons.item_at, close_action, action_type, open_action, send, set_key, set_sprinting,
        recovered_sprint_key, packet<0xc60>, packet_action_type, packet<0xbe8>, packet<0xc88>,
        drain<0x88, 0xa8>, drain<0x60, 0x70>
    };
}
