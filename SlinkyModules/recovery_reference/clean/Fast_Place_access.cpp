#include "Fast_Place_access.hpp"
#include "module_placement_geometry.hpp"
#include "module_access_helpers.hpp"
#include "Safe_Walk.hpp"
#include <cstring>

namespace {
using Word = std::uintptr_t;
Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word value;
    std::memcpy(&value, bridge->metadata + offset, sizeof(value));
    return value;
}
template<class Function>
Function slot(const GameAccessBridge *bridge, std::size_t offset) {
    const auto *table = reinterpret_cast<const Word *>(*bridge->environment);
    return reinterpret_cast<Function>(table[offset / sizeof(Word)]);
}
bool modern(GameAccessBridge *bridge) {
    std::uint32_t version;
    std::memcpy(&version, bridge->metadata, sizeof(version));
    return version != 0;
}
Word object_field(GameAccessBridge *bridge, Word object, std::size_t offset) {
    using Getter = Word (*)(Word *, Word, Word);
    return slot<Getter>(bridge, 0x2f8)(bridge->environment, object, identifier(bridge, offset));
}
std::int32_t integer_field(GameAccessBridge *bridge, Word object, std::size_t offset) {
    using Getter = std::int32_t (*)(Word *, Word, Word);
    return slot<Getter>(bridge, 0x320)(bridge->environment, object, identifier(bridge, offset));
}
double real_field(GameAccessBridge *bridge, Word object, std::size_t offset) {
    using Getter = double (*)(Word *, Word, Word);
    return slot<Getter>(bridge, 0x338)(bridge->environment, object, identifier(bridge, offset));
}
void integer_position(PlacementPosition *out, GameAccessBridge *bridge, Word object, std::size_t offset) {
    const double x = integer_field(bridge, object, offset);
    const double y = integer_field(bridge, object, offset + 8);
    const double z = integer_field(bridge, object, offset + 16);
    recovered_placement_position(out, x, y, z);
}
void real_position(PlacementPosition *out, GameAccessBridge *bridge, Word object, std::size_t offset) {
    const double x = real_field(bridge, object, offset);
    const double y = real_field(bridge, object, offset + 8);
    const double z = real_field(bridge, object, offset + 16);
    recovered_placement_position(out, x, y, z);
}
Word options(GameAccessBridge *bridge, Word client) { return recovered_access_helper(bridge, 0x22cf0, client, 0, 0); }
Word use_key(GameAccessBridge *bridge, Word options) { return recovered_access_helper(bridge, 0x24f90, options, 0, 0); }
std::uint8_t physical_key(GameAccessBridge *bridge, Word key) { return static_cast<std::uint8_t>(recovered_access_helper(bridge, 0x25490, key, 0, 0)); }
Word mouse_over(GameAccessBridge *bridge, Word client) { return recovered_access_helper(bridge, 0x22e10, client, 0, 0); }
std::uint32_t hit_type(GameAccessBridge *bridge, Word hit) { return static_cast<std::uint32_t>(recovered_access_helper(bridge, 0x24b50, hit, 0, 0)); }
std::uint32_t item_type(GameAccessBridge *bridge, Word item) { return static_cast<std::uint32_t>(recovered_game_item_numeric_id(bridge, item)); }
Word player_box(GameAccessBridge *bridge, Word player) { return object_field(bridge, player, 0x2d0); }
void position(PlacementPosition *out, double x, double y, double z) { recovered_placement_position(out, x, y, z); }
void add(PlacementPosition *out, const PlacementPosition *a, const PlacementPosition *b) { recovered_placement_add(out, a, b); }
void box(PlacementBox *out, const PlacementPosition *minimum, const PlacementPosition *maximum) { recovered_placement_box(out, minimum, maximum); }
std::uint8_t allowed(SmoothRandomState *sampler, std::uint64_t bounds, double duration, const FastPlaceAccessContext *context) {
    return recovered_policy_gate(sampler, bounds, duration, context->random, context->clock, context->policy);
}
}

// 0x25360/0x25380 preserve the signed query and wrapping DWORD increment,
// then reload the setter target, environment and field after the query.
extern "C" __declspec(dllexport) std::int32_t recovered_fast_place_press_count(GameAccessBridge *bridge, Word key) {
    return integer_field(bridge, key, 0x480);
}
extern "C" __declspec(dllexport) void recovered_fast_place_increment_presses(GameAccessBridge *bridge, Word key) {
    const auto next = static_cast<std::uint32_t>(recovered_fast_place_press_count(bridge, key)) + 1u;
    using Setter = void (*)(Word *, Word, Word, std::uint32_t);
    slot<Setter>(bridge, 0x368)(bridge->environment, key, identifier(bridge, 0x480), next);
}

// 0x24d80 queries the block position using 0x24c10/0x24310, then rereads the
// version to select an integer facing or its enum ordinal. Direction data is
// supplied explicitly and read after those calls.
extern "C" __declspec(dllexport) void recovered_fast_place_adjacent_position(
    PlacementPosition *out, GameAccessBridge *bridge, Word hit, const FastPlaceAccessContext *context) {
    PlacementPosition position;
    if (modern(bridge)) {
        const auto block = object_field(bridge, hit, 0x410);
        integer_position(&position, bridge, block, 0x458);
    } else integer_position(&position, bridge, hit, 0x3f8);
    std::uint32_t facing;
    if (modern(bridge)) {
        const auto face = object_field(bridge, hit, 0x3f0);
        facing = static_cast<std::uint32_t>(recovered_access_helper(bridge, 0x271a0, face, 0, 0));
    } else facing = static_cast<std::uint32_t>(integer_field(bridge, hit, 0x3e8));
    const auto first = position;
    const auto direction = context->directions[facing];
    recovered_placement_add(out, &first, &direction);
}

// 0x25640 captures each triple in order, with fresh bridge metadata/JNI targets
// for all six reads, and writes the box after both triples are complete.
extern "C" __declspec(dllexport) void recovered_fast_place_read_box(
    PlacementBox *out, GameAccessBridge *bridge, Word object) {
    PlacementPosition minimum, maximum;
    real_position(&minimum, bridge, object, 0x4a8);
    real_position(&maximum, bridge, object, 0x4c0);
    recovered_placement_box(out, &minimum, &maximum);
}

extern "C" __declspec(dllexport) void recovered_bind_fast_place_access(
    FastPlaceDependencies *dependencies, const FastPlaceAccessContext *context) {
    SafeWalkDependencies shared;
    recovered_bind_safe_walk_access(&shared);
    *dependencies = {options, use_key, physical_key, recovered_fast_place_press_count,
        recovered_fast_place_increment_presses, shared.held_item, shared.block_item,
        mouse_over, hit_type, item_type, recovered_fast_place_adjacent_position,
        position, add, box, player_box, recovered_fast_place_read_box,
        recovered_placement_intersects, recovered_random_bounds, allowed, context};
}
