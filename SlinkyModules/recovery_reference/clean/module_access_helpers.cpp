#include "module_access_helpers.hpp"

#include <cstdlib>
#include <cstring>

using Word = std::uintptr_t;
using ObjectGetter = Word (*)(Word *, Word, Word);
using IntegerGetter = std::int32_t (*)(Word *, Word, Word);
using BooleanGetter = std::uint8_t (*)(Word *, Word, Word);
using IntegerSetter = void (*)(Word *, Word, Word, std::uint32_t);
using FloatSetter = void (*)(Word *, Word, Word, float);
using ObjectCall = Word (*)(Word *, Word, Word, Word);
using ActionCall = void (*)(Word *, Word, Word, Word, Word);
using ArrayElement = Word (*)(Word *, Word, std::int32_t);
using PhysicalKey = std::uint8_t (*)(Word *, Word, Word, std::uint32_t);

static Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word result;
    std::memcpy(&result, bridge->metadata + offset, sizeof(result));
    return result;
}

template <class Function>
static Function slot(Word *environment, std::size_t offset) {
    const auto *table = reinterpret_cast<const Word *>(*environment);
    return reinterpret_cast<Function>(table[offset / sizeof(Word)]);
}

static Word object_field(GameAccessBridge *bridge, Word object, std::size_t offset) {
    return slot<ObjectGetter>(bridge->environment, 0x2f8)(
        bridge->environment, object, identifier(bridge, offset));
}

static std::uint32_t integer_field(GameAccessBridge *bridge, Word object, std::size_t offset) {
    return static_cast<std::uint32_t>(slot<IntegerGetter>(bridge->environment, 0x320)(
        bridge->environment, object, identifier(bridge, offset)));
}

static void set_integer(GameAccessBridge *bridge, Word object, std::size_t offset,
                        std::size_t table_offset, std::uint32_t value) {
    slot<IntegerSetter>(bridge->environment, table_offset)(
        bridge->environment, object, identifier(bridge, offset), value);
}

// 0x27960 retains the first environment pointer, but reloads its function table.
static Word effect_by_index(GameAccessBridge *bridge, std::uint32_t index) {
    if (index > 255) return 0;
    auto *environment = bridge->environment;
    const auto array = slot<ObjectGetter>(environment, 0x488)(
        environment, identifier(bridge, 0xa78), identifier(bridge, 0xa80));
    return slot<ArrayElement>(environment, 0x568)(environment, array, static_cast<std::int32_t>(index));
}

// 0x24f90 reloads the environment after retrieving the key array.
static Word use_key(GameAccessBridge *bridge, Word options) {
    const auto array = object_field(bridge, options, 0x3b8);
    return slot<ArrayElement>(bridge->environment, 0x568)(bridge->environment, array, 1);
}

// 0x271a0, reached by 0x24b50 after its first object query.
static std::uint32_t target_kind(GameAccessBridge *bridge, Word target) {
    return static_cast<std::uint32_t>(slot<IntegerGetter>(bridge->environment, 0x188)(
        bridge->environment, target, identifier(bridge, 0x148)));
}

// 0x25760 and 0x258c0 normalize the returned Boolean's low byte.
static std::uint8_t physical_key(GameAccessBridge *bridge, std::uint32_t key, bool mouse) {
    return slot<PhysicalKey>(bridge->environment, 0x3a8)(bridge->environment,
        identifier(bridge, mouse ? 0x88 : 0x60), identifier(bridge, mouse ? 0xa0 : 0x68), key) != 0;
}

// 0x25490 uses signed key codes. Its negative-code adjustment wraps at 32 bits.
static std::uint8_t key_pressed(GameAccessBridge *bridge, Word key) {
    const auto code = integer_field(bridge, key, 0x488);
    if (code & 0x80000000u) return physical_key(bridge, code + 100u, true);
    return code <= 256u ? physical_key(bridge, code, false) : 0;
}

// 0x23e60 / 0x23e90 move caller XMM2 to the JNI setter's XMM3 argument.
static std::uint64_t set_float(Word bridge_address, Word object, float value, std::size_t offset) {
    auto *bridge = reinterpret_cast<GameAccessBridge *>(bridge_address);
    slot<FloatSetter>(bridge->environment, 0x378)(bridge->environment, object, identifier(bridge, offset), value);
    return 0;
}

extern "C" __declspec(dllexport) std::uint64_t recovered_access_helper(
    GameAccessBridge *bridge, std::uint32_t helper_rva, std::uint64_t object,
    std::uint64_t value, std::uintptr_t caller_frame_token) {
    switch (helper_rva) {
    case 0x27960: return effect_by_index(bridge, static_cast<std::uint32_t>(object));
    case 0x23c10: return slot<ObjectCall>(bridge->environment, 0x110)(
        bridge->environment, object, identifier(bridge, 0x530), value);
    case 0x279c0: set_integer(bridge, object, 0xc38, 0x368, static_cast<std::uint32_t>(value)); return 0;
    case 0x23e60:
    case 0x23e90: {
        const auto bits = static_cast<std::uint32_t>(value);
        float number;
        std::memcpy(&number, &bits, sizeof(number));
        return set_float(reinterpret_cast<Word>(bridge), object, number, helper_rva == 0x23e60 ? 0x8d0 : 0x8d8);
    }
    case 0x23b80: set_integer(bridge, object, 0x570, 0x368, static_cast<std::uint32_t>(value)); return 0;
    case 0x22df0: return object_field(bridge, object, 0x218);
    case 0x27e90: return slot<BooleanGetter>(bridge->environment, 0x300)(
        bridge->environment, object, identifier(bridge, 0xbd8));
    case 0x27eb0: set_integer(bridge, object, 0xbd8, 0x348, static_cast<std::uint32_t>(value)); return 0;
    case 0x22e90: return integer_field(bridge, object, 0x1b8);
    case 0x22e10: return object_field(bridge, object, 0x1b0);
    case 0x24b50: return target_kind(bridge, object_field(bridge, object, 0x3d8));
    case 0x271a0: return target_kind(bridge, object);
    case 0x22eb0: set_integer(bridge, object, 0x1b8, 0x368, static_cast<std::uint32_t>(value)); return 0;
    case 0x23bb0: slot<ActionCall>(bridge->environment, 0x2d8)(bridge->environment, object,
        identifier(bridge, 0x4f8), identifier(bridge, 0x520), caller_frame_token); return 0;
    case 0x23f90: return recovered_game_using_item(bridge, object);
    case 0x22cf0: return object_field(bridge, object, 0x1a0);
    case 0x24f90: return use_key(bridge, object);
    case 0x25430: return slot<BooleanGetter>(bridge->environment, 0x300)(
        bridge->environment, object, identifier(bridge, 0x478)) != 0;
    case 0x23f40: return recovered_game_inventory(bridge, object);
    case 0x25a60: return static_cast<std::uint32_t>(recovered_game_inventory_index(bridge, object));
    case 0x25490: return key_pressed(bridge, object);
    case 0x25760: return physical_key(bridge, static_cast<std::uint32_t>(object), false);
    case 0x258c0: return physical_key(bridge, static_cast<std::uint32_t>(object), true);
    case 0x25460: set_integer(bridge, object, 0x478, 0x348, static_cast<std::uint32_t>(value)); return 0;
    case 0x23fc0: return integer_field(bridge, object, 0x5a8);
    default: std::abort();
    }
}

static std::uint64_t invoke(void *context, std::uint32_t helper, std::uint64_t bridge,
                            std::uint64_t object, std::uint64_t value, std::uint64_t) {
    return recovered_access_helper(reinterpret_cast<GameAccessBridge *>(bridge), helper, object, value,
        static_cast<const AccessHelperContext *>(context)->caller_frame_token);
}

static std::uint64_t float_23e60(std::uint64_t bridge, std::uint64_t object, float value) {
    return set_float(bridge, object, value, 0x8d0);
}
static std::uint64_t float_23e90(std::uint64_t bridge, std::uint64_t object, float value) {
    return set_float(bridge, object, value, 0x8d8);
}

extern "C" __declspec(dllexport) void recovered_bind_access_helpers(
    AccessDependencies *dependencies, AccessHelperContext *context) {
    dependencies->invoke = invoke;
    dependencies->context = context;
    dependencies->invoke_23e60 = float_23e60;
    dependencies->invoke_23e90 = float_23e90;
}
