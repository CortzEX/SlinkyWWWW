// Null Move

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Null_Move.md

#include "../runtime/native/verified/module_surface.hpp"

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Null_Move/Null_Move.cpp
#ifndef SLINKY_SHARE_91C4213D0EDEB5A89BA9
#define SLINKY_SHARE_91C4213D0EDEB5A89BA9
// BEGIN SOURCE native/verified/Null_Move.hpp
#include "../runtime/native/verified/Sprint.hpp"

using NullMoveGame = SprintGame;
struct NullMoveEvent {
    std::uintptr_t event_type;
    NullMoveGame *game;
};
struct NullMoveState {
    std::uint32_t saved_stamps[4];
};
struct NullMoveDependencies {
    std::uint8_t (*ready)(GameAccessBridge *, std::uintptr_t client);
    std::int32_t (*stamp)(GameAccessBridge *, std::uintptr_t player);
    std::uintptr_t (*options)(GameAccessBridge *, std::uintptr_t client);
    std::uintptr_t (*keys[4])(GameAccessBridge *, std::uintptr_t options);
    std::uint8_t (*pressed)(GameAccessBridge *, std::uintptr_t key);
    std::uint8_t (*physical)(GameAccessBridge *, std::uintptr_t key);
    void (*set_key)(GameAccessBridge *, std::uintptr_t key, std::uint8_t value);
};
static_assert(sizeof(NullMoveEvent) == 16);
static_assert(offsetof(NullMoveEvent, game) == 8);
static_assert(sizeof(NullMoveState) == 16);
static_assert(sizeof(NullMoveDependencies) == 80);

extern "C" {
__declspec(dllexport) void recovered_null_move_update(NullMoveEvent *, NullMoveState *,
                                                      const NullMoveDependencies *);
__declspec(dllexport) void recovered_bind_null_move_access(NullMoveDependencies *);
__declspec(dllexport) std::uint8_t recovered_null_move_ready(GameAccessBridge *,
                                                             std::uintptr_t client);
__declspec(dllexport) std::uintptr_t
recovered_null_move_key(GameAccessBridge *, std::uintptr_t options, std::uint32_t index);
}
// END SOURCE native/verified/Null_Move.hpp

#endif // SLINKY_SHARE_91C4213D0EDEB5A89BA9

#include "../runtime/native/verified/Keep_Sprint.hpp"
#include "../runtime/native/verified/module_access_helpers.hpp"
#include <cstring>

using Word = std::uintptr_t;

static Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word value;
    std::memcpy(&value, bridge->metadata + offset, sizeof(value));
    return value;
}

template <class Function> static Function slot(const GameAccessBridge *bridge, std::size_t offset) {
    const auto *table = reinterpret_cast<const Word *>(*bridge->environment);
    return reinterpret_cast<Function>(table[offset / sizeof(Word)]);
}

// 0x22e60 normalizes only the JNI Boolean's low byte.
extern "C" __declspec(dllexport) std::uint8_t recovered_null_move_ready(GameAccessBridge *bridge,
                                                                        Word client) {
    using Getter_Null_Move = std::uint8_t (*)(Word *, Word, Word);
    return slot<Getter_Null_Move>(bridge, 0x300)(bridge->environment, client,
                                                 identifier(bridge, 0x1a8)) != 0;
}

// 0x250d0/0x25170/0x25120/0x251c0 use indices 2/3/4/5 and reload the environment after the getter.
extern "C" __declspec(dllexport) Word recovered_null_move_key(GameAccessBridge *bridge,
                                                              Word options, std::uint32_t index) {
    using Getter_Null_Move = Word (*)(Word *, Word, Word);
    const auto array = slot<Getter_Null_Move>(bridge, 0x2f8)(bridge->environment, options,
                                                             identifier(bridge, 0x3b8));
    using Element = Word (*)(Word *, Word, std::uint32_t);
    return slot<Element>(bridge, 0x568)(bridge->environment, array, index);
}

template <std::uint32_t Index> static Word key(GameAccessBridge *bridge, Word options) {
    return recovered_null_move_key(bridge, options, Index);
}
static Word options(GameAccessBridge *bridge, Word client) {
    return recovered_access_helper(bridge, 0x22cf0, client, 0, 0);
}
static std::uint8_t pressed(GameAccessBridge *bridge, Word key) {
    return static_cast<std::uint8_t>(recovered_access_helper(bridge, 0x25430, key, 0, 0));
}
static std::uint8_t physical(GameAccessBridge *bridge, Word key) {
    return static_cast<std::uint8_t>(recovered_access_helper(bridge, 0x25490, key, 0, 0));
}
static void set_key(GameAccessBridge *bridge, Word key, std::uint8_t value) {
    recovered_access_helper(bridge, 0x25460, key, value, 0);
}

extern "C" __declspec(dllexport) void
recovered_bind_null_move_access(NullMoveDependencies *dependencies) {
    *dependencies = {recovered_null_move_ready,
                     recovered_keep_sprint_counter,
                     options,
                     {key<2>, key<3>, key<4>, key<5>},
                     pressed,
                     physical,
                     set_key};
}

// 0x46ac0 updates saved timestamps after each opposite-key operation, in original order.
extern "C" __declspec(dllexport) void
recovered_null_move_update(NullMoveEvent *event, NullMoveState *state,
                           const NullMoveDependencies *dependencies) {
    auto *game = event->game;
    if (!dependencies->ready(game->bridge, game->client))
        return;
    const auto stamp = static_cast<std::uint32_t>(dependencies->stamp(game->bridge, game->player));
    const auto settings = dependencies->options(game->bridge, game->client);
    Word keys[4];
    for (unsigned i = 0; i < 4; ++i)
        keys[i] = dependencies->keys[i](game->bridge, settings);
    static constexpr unsigned opposite[4] = {2, 3, 0, 1};
    for (unsigned i = 0; i < 4; ++i) {
        const auto previous = state->saved_stamps[i];
        const auto other = opposite[i];
        const auto is_pressed = dependencies->pressed(game->bridge, keys[i]);
        const auto other_pressed = dependencies->pressed(game->bridge, keys[other]);
        auto next = std::uint32_t{0};
        if (is_pressed) {
            next = stamp;
            if (!previous && (other_pressed & 1))
                dependencies->set_key(game->bridge, keys[other], 0);
        } else if (previous && dependencies->physical(game->bridge, keys[other])) {
            dependencies->set_key(game->bridge, keys[other], 1);
        }
        state->saved_stamps[i] = next;
    }
}
// END SOURCE modules/Null_Move/Null_Move.cpp

#ifndef SLINKY_SHARE_83A849E67F2ADE650703
#define SLINKY_SHARE_83A849E67F2ADE650703
// BEGIN SOURCE modules/Null_Move/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Null_Move/Api.hpp

#endif // SLINKY_SHARE_83A849E67F2ADE650703

// Convenient borrowed-state interface

namespace shareable {
class NullMove {
  public:
    static constexpr const char *kName = "Null Move";
    static constexpr const char *kDescription =
        "Makes it easier to switch move direction instantly.";
    explicit NullMove(std::uint8_t *image) : image_(image) {}
    static std::uint8_t ready(GameAccessBridge *bridge, Word client) {
        return ::recovered_null_move_ready(bridge, client);
    }
    static Word key(GameAccessBridge *bridge, Word options, std::uint32_t index) {
        return ::recovered_null_move_key(bridge, options, index);
    }
    static void bindAccess(NullMoveDependencies *dependencies) {
        ::recovered_bind_null_move_access(dependencies);
    }
    static void update(NullMoveEvent *event, NullMoveState *state,
                       const NullMoveDependencies *dependencies) {
        ::recovered_null_move_update(event, state, dependencies);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
