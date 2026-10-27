// Friends

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Friends.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Friends.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Friends: lib_win settings 0x3b640.
// UI 0x3b600.
static constexpr UiStep ui_steps_Surface_Friends[] = {
    {UiControl::section, "Main", 0},
    {UiControl::checkbox, nullptr, 0x2f0248},
};
static constexpr SettingsStep settings_steps_Surface_Friends[] = {
    {SettingsControl::boolean, "middle_click_add", 0x2f0248},
    {SettingsControl::list, "friends", 0x2f0268},
};
static constexpr ModuleSurface surface_Surface_Friends{
    ui_steps_Surface_Friends, std::size(ui_steps_Surface_Friends), settings_steps_Surface_Friends,
    std::size(settings_steps_Surface_Friends)};

extern "C" __declspec(dllexport) void
recovered_friends_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                     const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Friends, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_friends_settings(SettingsContext *context, std::uint8_t *image,
                           const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Friends, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Friends.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Friends/Commands.cpp
// Native command bodies 0x3b680,0x3b700,0x3b7a0,0x3b9d0 and resolver 0x3ba20.
// Recovered from the supplied raw view and runtime-observed instructions.
// Native count reloads, unsigned lengths, partial-register results and early
// ambiguity returns are preserved. Java and message endpoints remain explicit.
#ifndef SLINKY_SHARE_D766BCB5917DB0D0CF04
#define SLINKY_SHARE_D766BCB5917DB0D0CF04
// BEGIN SOURCE modules/Friends/Commands.hpp
#ifndef SLINKY_SHARE_1E2AFD8CC83BC7BD2513
#define SLINKY_SHARE_1E2AFD8CC83BC7BD2513
// BEGIN SOURCE native/verified/Friends_actions.hpp
#include "../runtime/native/verified/module_game_access.hpp"
#include "../runtime/native/verified/module_sorted_table.hpp"
#include "../runtime/native/verified/module_uuid.hpp"

struct FriendRecord {
    UuidKey key;
    std::uint64_t timestamp, reserved;
};
struct FriendAction {
    std::uint32_t event_type, padding;
    std::uint8_t added, remaining[63];
};
static_assert(sizeof(FriendRecord) == 32);
static_assert(sizeof(FriendAction) == 72);
static_assert(offsetof(FriendAction, added) == 8);

struct FriendsActionDependencies {
    std::uintptr_t (*current)(GameAccessBridge *);
    std::uintptr_t (*context)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*object)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*entity)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*uuid)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*high)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*low)(GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*flags)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    std::uint64_t (*timestamp)();
    void (*emit)(std::uintptr_t context, const FriendAction *);
    const ListMemoryDependencies *memory;
};

extern "C" {
__declspec(dllexport) void recovered_bind_friends_action_access(FriendsActionDependencies *);
__declspec(dllexport) void recovered_friends_action(GameAccessBridge *,
                                                    std::uintptr_t action_context,
                                                    const std::uint8_t *enabled, SortedTable *,
                                                    const FriendsActionDependencies *);
}
// END SOURCE native/verified/Friends_actions.hpp

#endif // SLINKY_SHARE_1E2AFD8CC83BC7BD2513

#include "../runtime/native/verified/Timer.hpp"
namespace reconstruction::friends {
using CommandEndpoint = std::uint64_t (*)(std::uint64_t, std::uint64_t, std::uint64_t,
                                          std::uint64_t, std::uint64_t, std::uint64_t);
struct CommandDependencies {
    CommandEndpoint invoke;
    const ListMemoryDependencies *memory;
};
struct NameSlice {
    const char *data;
    std::uint64_t length;
};
struct NearbyArguments {
    std::uint64_t radius, reserved;
    std::uint8_t replace;
};
static_assert(sizeof(NameSlice) == 16);
static_assert(offsetof(NearbyArguments, replace) == 16);
std::uint64_t resolveNamePrefix(TimerGame *, const NameSlice *, FriendRecord *, char *name,
                                const std::uint8_t *stateImage, const CommandDependencies &);
std::uint64_t addByName(TimerGame *, const NameSlice *, std::uint8_t *stateImage,
                        const CommandDependencies &);
std::uint64_t removeByName(TimerGame *, const NameSlice *, std::uint8_t *stateImage,
                           const CommandDependencies &);
std::uint64_t addNearby(TimerGame *, const NearbyArguments *, std::uint8_t *stateImage,
                        const CommandDependencies &);
std::uint64_t clearAll(TimerGame *, std::uint8_t *stateImage, const CommandDependencies &);
} // namespace reconstruction::friends
// END SOURCE modules/Friends/Commands.hpp

#endif // SLINKY_SHARE_D766BCB5917DB0D0CF04

#include "../runtime/shared/Geometry.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>
namespace reconstruction::friends {
namespace {
template <class T> T load(const void *p) {
    T v;
    std::memcpy(&v, p, sizeof v);
    return v;
}
template <class T> void store(void *p, T v) {
    std::memcpy(p, &v, sizeof v);
}
std::uintptr_t address(const void *p) {
    return reinterpret_cast<std::uintptr_t>(p);
}
std::uint64_t bridge(TimerGame *context) {
    return address(context->bridge);
}
std::uint64_t jniTarget(std::uintptr_t environment, std::size_t slot) {
    return load<std::uint64_t>(reinterpret_cast<const std::uint8_t *>(load<std::uintptr_t>(
                                   reinterpret_cast<const void *>(environment))) +
                               slot);
}
std::uint64_t message(TimerGame *context, const std::uint8_t *image, std::uint32_t format,
                      std::uint64_t first, std::uint64_t second, std::uint64_t third,
                      const CommandDependencies &deps) {
    return deps.invoke(0x291f0, bridge(context), address(image + format), first, second, third);
}
std::uint8_t folded(std::uint8_t byte) {
    return static_cast<std::uint8_t>(byte +
                                     (static_cast<std::uint8_t>(byte - 0x41) < 0x1a ? 0x20 : 0));
}
std::uint64_t isSelf(TimerGame *context, std::uint64_t entity, const CommandDependencies &deps) {
    auto *current = context->bridge;
    const auto player = context->player;
    const auto environment = address(current->environment);
    return deps.invoke(jniTarget(environment, 0xc0), environment, entity, player, 0, 0);
}
void insert(FriendRecord *record, std::uint8_t *image, const CommandDependencies &deps) {
    recovered_list_insert(image + 0x2fc8c0, 32, image + 0x2fc8c8, record, recovered_uuid_compare,
                          deps.memory);
}
std::uint64_t uuidRecord(TimerGame *context, std::uint64_t entity, FriendRecord *output,
                         const CommandDependencies &deps) {
    const auto uuid = deps.invoke(0x23740, bridge(context), entity, 0, 0, 0);
    const auto high = deps.invoke(0x27dc0, bridge(context), uuid, 0, 0, 0);
    const auto low = deps.invoke(0x27d90, bridge(context), uuid, 0, 0, 0);
    output->key.words[0] = high;
    output->key.words[1] = low;
    output->timestamp = 0;
    output->reserved = 0;
    return low;
}
} // namespace
std::uint64_t resolveNamePrefix(TimerGame *context, const NameSlice *request, FriendRecord *output,
                                char *name, const std::uint8_t *image,
                                const CommandDependencies &deps) {
    const auto length = request->length;
    auto *initialBridge = context->bridge;
    if (length >= 17) {
        deps.invoke(0x291f0, address(initialBridge), address(image + 0x1535a7), 0, 0, 0);
        return 0;
    }
    const auto *text = request->data;
    const auto environment = address(initialBridge->environment);
    char temporary[32];
    deps.memory->copy(temporary, text, length);
    temporary[length] = 0;
    if (!deps.invoke(jniTarget(environment, 0x538), environment, address(temporary), 0, 0, 0))
        return 0;
    const auto list = deps.invoke(0x24600, bridge(context), context->world, 0, 0, 0);
    auto count = static_cast<std::uint32_t>(deps.invoke(0x24e50, bridge(context), list, 0, 0, 0));
    std::uint64_t found = 0;
    if (std::bit_cast<std::int32_t>(count) > 0) {
        std::uint32_t index = 0;
        do {
            const auto entity = deps.invoke(0x24e80, bridge(context), list, index, 0, 0);
            if (static_cast<std::uint8_t>(isSelf(context, entity, deps)) == 0) {
                const auto string = deps.invoke(0x23830, bridge(context), entity, 0, 0, 0);
                const auto rawLength = static_cast<std::uint32_t>(
                    deps.invoke(jniTarget(environment, 0x540), environment, string, 0, 0, 0));
                const auto signedLength = std::bit_cast<std::int32_t>(rawLength);
                if (length <= static_cast<std::uint64_t>(static_cast<std::int64_t>(signedLength))) {
                    const auto characters =
                        deps.invoke(jniTarget(environment, 0x548), environment, string, 0, 0, 0);
                    bool matches = true;
                    for (std::uint64_t i = 0; i < length; ++i) {
                        const auto candidate = load<std::uint8_t>(
                            reinterpret_cast<const std::uint8_t *>(characters) + i);
                        const auto requested = load<std::uint8_t>(text + i);
                        if (folded(requested) != folded(candidate)) {
                            matches = false;
                            break;
                        }
                    }
                    if (matches) {
                        if (found) {
                            // Native ambiguity returns before releasing the current UTF chars.
                            message(context, image, 0x1535c0, static_cast<std::uint32_t>(length),
                                    address(text), 0, deps);
                            return 0;
                        }
                        const auto copyLength = signedLength >= 16 ? 16 : signedLength;
                        deps.memory->copy(
                            name, reinterpret_cast<const void *>(characters),
                            static_cast<std::uint64_t>(static_cast<std::int64_t>(copyLength)));
                        name[copyLength] = 0;
                        found = entity;
                    }
                    deps.invoke(jniTarget(environment, 0x550), environment, string, characters, 0,
                                0);
                }
            }
            ++index;
            count =
                static_cast<std::uint32_t>(deps.invoke(0x24e50, bridge(context), list, 0, 0, 0));
        } while (std::bit_cast<std::int32_t>(index) < std::bit_cast<std::int32_t>(count));
        if (found) {
            const auto low = uuidRecord(context, found, output, deps);
            return (low & ~std::uint64_t{0xff}) | 1;
        }
    }
    message(context, image, 0x1535ee, 0, 0, 0, deps);
    return 0;
}
std::uint64_t addByName(TimerGame *context, const NameSlice *request, std::uint8_t *image,
                        const CommandDependencies &deps) {
    NameSlice copied;
    std::memcpy(&copied, request, 16);
    FriendRecord record;
    char name[32];
    const auto result = resolveNamePrefix(context, &copied, &record, name, image, deps);
    if (static_cast<std::uint8_t>(result) == 0)
        return result;
    const auto retained = static_cast<std::uint32_t>(result);
    insert(&record, image, deps);
    message(context, image, 0x153590, address(name), 0, 0, deps);
    return retained;
}
std::uint64_t removeByName(TimerGame *context, const NameSlice *request, std::uint8_t *image,
                           const CommandDependencies &deps) {
    NameSlice copied;
    std::memcpy(&copied, request, 16);
    FriendRecord record;
    char name[32];
    const auto result = resolveNamePrefix(context, &copied, &record, name, image, deps);
    if (static_cast<std::uint8_t>(result) == 0)
        return result;
    const auto retained = static_cast<std::uint32_t>(result);
    const auto capacity = reinterpret_cast<std::uint32_t *>(image + 0x2fc8c8);
    const auto found = recovered_sorted_lookup(
        reinterpret_cast<const void *>(load<std::uintptr_t>(image + 0x2fc8c0)), 32, capacity,
        &record, recovered_uuid_compare);
    if (found)
        recovered_sorted_remove(reinterpret_cast<void *>(load<std::uintptr_t>(image + 0x2fc8c0)),
                                32, capacity, found, deps.memory);
    message(context, image, 0x153603, address(name), 0, 0, deps);
    return retained;
}
std::uint64_t addNearby(TimerGame *context, const NearbyArguments *arguments, std::uint8_t *image,
                        const CommandDependencies &deps) {
    const auto radius = arguments->radius;
    const auto replace = arguments->replace;
    const auto oldCount = load<std::uint32_t>(image + 0x2fc8cc);
    if (replace == 1)
        store(image + 0x2fc8cc, std::uint32_t(0));
    double origin[3];
    deps.invoke(0x23030, address(origin), bridge(context), context->player, 0, 0);
    const auto list = deps.invoke(0x24600, bridge(context), context->world, 0, 0, 0);
    auto count = static_cast<std::uint32_t>(deps.invoke(0x24e50, bridge(context), list, 0, 0, 0));
    std::uint64_t added = 0;
    if (std::bit_cast<std::int32_t>(count) > 0) {
        const auto packed = _mm_loadl_epi64(reinterpret_cast<const __m128i *>(&radius));
        const auto unpacked = _mm_unpacklo_epi32(
            packed, _mm_loadu_si128(reinterpret_cast<const __m128i *>(image + 0x153180)));
        const auto lanes =
            _mm_sub_pd(_mm_castsi128_pd(unpacked),
                       _mm_loadu_pd(reinterpret_cast<const double *>(image + 0x153190)));
        const auto sum = _mm_add_sd(_mm_unpackhi_pd(lanes, lanes), lanes);
        const auto squared = _mm_cvtsd_f64(_mm_mul_sd(sum, sum));
        std::uint32_t index = 0;
        do {
            const auto entity = deps.invoke(0x24e80, bridge(context), list, index, 0, 0);
            if (static_cast<std::uint8_t>(isSelf(context, entity, deps)) == 0 &&
                static_cast<std::uint8_t>(deps.invoke(0x2ace0, bridge(context), entity, 2, 0, 0)) ==
                    0) {
                double position[3];
                deps.invoke(0x23030, address(position), bridge(context), entity, 0, 0);
                const auto distance = recovered_vector_distance_squared(origin, position);
                // Native UCOMISD/JA accepts unordered distances rather than rejecting them.
                if (!(distance > squared)) {
                    FriendRecord record;
                    uuidRecord(context, entity, &record, deps);
                    insert(&record, image, deps);
                    ++added;
                }
            }
            ++index;
            count =
                static_cast<std::uint32_t>(deps.invoke(0x24e50, bridge(context), list, 0, 0, 0));
        } while (std::bit_cast<std::int32_t>(index) < std::bit_cast<std::int32_t>(count));
    }
    const auto plural = address(image + (added == 1 ? 0x153640 : 0x153641));
    const auto result = replace != 0
                            ? message(context, image, 0x15361c, oldCount, added, plural, deps)
                            : message(context, image, 0x153643, added, plural, 0, deps);
    return (result & ~std::uint64_t{0xff}) | 1;
}
std::uint64_t clearAll(TimerGame *context, std::uint8_t *image, const CommandDependencies &deps) {
    const auto count = load<std::uint32_t>(image + 0x2fc8cc);
    const auto result = message(context, image, 0x15365a, count,
                                address(image + (count == 1 ? 0x153640 : 0x153641)), 0, deps);
    store(image + 0x2fc8cc, std::uint32_t(0));
    return (result & ~std::uint64_t{0xff}) | 1;
}
} // namespace reconstruction::friends
// END SOURCE modules/Friends/Commands.cpp

// BEGIN SOURCE modules/Friends/Friends.cpp
#ifndef SLINKY_SHARE_5E1C2FA15FE43248B9FF
#define SLINKY_SHARE_5E1C2FA15FE43248B9FF
// BEGIN SOURCE native/verified/Friends.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_ui_controls.hpp"

struct FriendsSettings {
    BooleanSetting middle_click_add;
    ListSetting friends;
};
struct FriendsListDependencies {
    std::size_t (*length)(const char *);
    decltype(&recovered_list_insert) insert;
    const ListMemoryDependencies *memory;
};
struct FriendsListState {
    SortedTable *table;
    char *scratch;
    const std::uint8_t *digits;
    const FriendsListDependencies *dependencies;
};
static_assert(sizeof(FriendsSettings) == 120);
static_assert(offsetof(FriendsSettings, friends) == 32);
static_assert(sizeof(FriendsListDependencies) == 24);
static_assert(sizeof(FriendsListState) == 32);

extern "C" {
__declspec(dllexport) void recovered_bind_friends_list_storage(FriendsListDependencies *);
__declspec(dllexport) void recovered_bind_friends_typed_list(ListSetting *, FriendsListState *);
__declspec(dllexport) std::size_t recovered_friends_typed_count(const FriendsListState *);
__declspec(dllexport) const char *recovered_friends_typed_name(const FriendsListState *,
                                                               std::size_t index);
__declspec(dllexport) bool recovered_friends_typed_add(const FriendsListState *, const char *name);
__declspec(dllexport) void *recovered_friends_typed_remove(const FriendsListState *,
                                                           std::size_t index);
__declspec(dllexport) void recovered_friends_typed_clear(const FriendsListState *);
__declspec(dllexport) std::uint64_t recovered_friends_typed_ui(std::uint64_t ui,
                                                               std::uint64_t layout,
                                                               FriendsSettings *, UiDirtyState *,
                                                               const SettingsUiEndpoints *);
__declspec(dllexport) void recovered_friends_typed_settings(SettingsContext *, FriendsSettings *,
                                                            const SettingsDependencies *,
                                                            const ListSettingsDependencies *);
}
// END SOURCE native/verified/Friends.hpp

#endif // SLINKY_SHARE_5E1C2FA15FE43248B9FF

#include <initializer_list>

extern "C" __declspec(dllexport) void
recovered_bind_friends_list_storage(FriendsListDependencies *dependencies) {
    dependencies->insert = recovered_list_insert;
}
extern "C" __declspec(dllexport) std::size_t
recovered_friends_typed_count(const FriendsListState *state) {
    return state->table->count;
}
extern "C" __declspec(dllexport) const char *
recovered_friends_typed_name(const FriendsListState *state, std::size_t index) {
    const auto offset = static_cast<std::uint32_t>(index) * 32;
    const auto *source = reinterpret_cast<const volatile std::uint8_t *>(
        reinterpret_cast<std::uintptr_t>(state->table->data) + offset);
    auto *output = state->scratch;
    const auto *digits = state->digits;
    for (int i = 0; i < 24; ++i) {
        output[i * 2] = digits[source[i] >> 4];
        output[i * 2 + 1] = digits[source[i] & 15];
    }
    output[48] = 0;
    return output;
}
static bool digit(std::uint8_t byte, std::uint8_t &value) {
    value = static_cast<std::uint8_t>(byte - '0');
    if (value < 10)
        return true;
    if (static_cast<std::uint8_t>(byte - 'a') >= 26)
        return false;
    value = static_cast<std::uint8_t>(byte + 0xa9);
    return true;
}
extern "C" __declspec(dllexport) bool recovered_friends_typed_add(const FriendsListState *state,
                                                                  const char *name) {
    if (state->dependencies->length(name) < 48)
        return false;
    std::uint8_t record[32]{};
    for (const auto end : {16, 24}) {
        for (int i = end == 16 ? 0 : 16; i < end; ++i) {
            std::uint8_t high, low;
            if (!digit(static_cast<std::uint8_t>(name[i * 2]), high) ||
                !digit(static_cast<std::uint8_t>(name[i * 2 + 1]), low))
                break;
            record[i] = static_cast<std::uint8_t>((high << 4) | low);
        }
    }
    auto *table = state->table;
    state->dependencies->insert(&table->data, 32, &table->capacity, record, recovered_uuid_compare,
                                state->dependencies->memory);
    return true;
}
extern "C" __declspec(dllexport) void *recovered_friends_typed_remove(const FriendsListState *state,
                                                                      std::size_t index) {
    auto *table = state->table;
    const auto base = reinterpret_cast<std::uintptr_t>(table->data);
    const auto count_Friends = --table->count;
    const auto slot = static_cast<std::uint32_t>(index);
    return state->dependencies->memory->move(reinterpret_cast<void *>(base + slot * 32),
                                             reinterpret_cast<const void *>(base + (slot + 1) * 32),
                                             (count_Friends - slot) * 32);
}
extern "C" __declspec(dllexport) void recovered_friends_typed_clear(const FriendsListState *state) {
    state->table->count = 0;
}
static std::size_t count_Friends(void *state) {
    return recovered_friends_typed_count(static_cast<FriendsListState *>(state));
}
static const char *name(void *state, std::size_t index) {
    return recovered_friends_typed_name(static_cast<FriendsListState *>(state), index);
}
static void add(void *state, const char *name, const float *) {
    recovered_friends_typed_add(static_cast<FriendsListState *>(state), name);
}
static void remove(void *state, std::size_t index) {
    recovered_friends_typed_remove(static_cast<FriendsListState *>(state), index);
}
static void clear(void *state) {
    recovered_friends_typed_clear(static_cast<FriendsListState *>(state));
}
extern "C" __declspec(dllexport) void recovered_bind_friends_typed_list(ListSetting *setting,
                                                                        FriendsListState *state) {
    setting->state = state;
    setting->count = count_Friends;
    setting->name = name;
    setting->add = add;
    setting->remove = remove;
    setting->clear = clear;
}
extern "C" __declspec(dllexport) std::uint64_t
recovered_friends_typed_ui(std::uint64_t ui, std::uint64_t layout, FriendsSettings *settings,
                           UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
    endpoints->section(ui, layout, "Main");
    return recovered_checkbox_control(layout, ui, &settings->middle_click_add, dirty,
                                      &endpoints->controls);
}
extern "C" __declspec(dllexport) void
recovered_friends_typed_settings(SettingsContext *context, FriendsSettings *settings,
                                 const SettingsDependencies *boolean,
                                 const ListSettingsDependencies *lists) {
    recovered_boolean_settings(context, "middle_click_add", &settings->middle_click_add, boolean);
    recovered_list_settings(context, "friends", &settings->friends, lists);
}
// END SOURCE modules/Friends/Friends.cpp

// BEGIN SOURCE modules/Friends/Friends_actions.cpp
#include "../runtime/native/verified/Chams.hpp"
#include <cstring>

using AccessCall = std::uintptr_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t);
static std::uintptr_t access(GameAccessBridge *bridge, std::uintptr_t object, std::size_t slot,
                             std::size_t field) {
    std::uintptr_t identifier;
    std::memcpy(&identifier, bridge->metadata + field, sizeof(identifier));
    const auto *table = reinterpret_cast<const std::uintptr_t *>(*bridge->environment);
    return reinterpret_cast<AccessCall>(table[slot / 8])(bridge->environment, object, identifier);
}
static std::uintptr_t current(GameAccessBridge *bridge) {
    std::uintptr_t clazz;
    std::memcpy(&clazz, bridge->metadata + 0x150, sizeof(clazz));
    return access(bridge, clazz, 0x488, 0x180);
}
static std::uintptr_t context(GameAccessBridge *bridge, std::uintptr_t object) {
    return access(bridge, object, 0x2f8, 0x1b0);
}
static std::uintptr_t object(GameAccessBridge *bridge, std::uintptr_t value) {
    return access(bridge, value, 0x2f8, 0x418);
}
static std::uintptr_t entity(GameAccessBridge *bridge, std::uintptr_t object) {
    return static_cast<std::uint8_t>(access(bridge, object, 0x100, 0x870)) ? object : 0;
}
static std::uintptr_t uuid(GameAccessBridge *bridge, std::uintptr_t object) {
    return access(bridge, object, 0x2f8, 0x2e8);
}
static std::uintptr_t high(GameAccessBridge *bridge, std::uintptr_t uuid) {
    return access(bridge, uuid, 0x1a0, 0xba8);
}
static std::uintptr_t low(GameAccessBridge *bridge, std::uintptr_t uuid) {
    return access(bridge, uuid, 0x1a0, 0xba0);
}
extern "C" __declspec(dllexport) void
recovered_bind_friends_action_access(FriendsActionDependencies *dependencies) {
    dependencies->current = current;
    dependencies->context = context;
    dependencies->object = object;
    dependencies->entity = entity;
    dependencies->uuid = uuid;
    dependencies->high = high;
    dependencies->low = low;
    dependencies->flags = recovered_chams_flags;
}

extern "C" __declspec(dllexport) void
recovered_friends_action(GameAccessBridge *bridge, std::uintptr_t action_context,
                         const std::uint8_t *enabled, SortedTable *table,
                         const FriendsActionDependencies *dependencies) {
    if (*enabled != 1)
        return;
    const auto context = dependencies->context(bridge, dependencies->current(bridge));
    if (!context)
        return;
    const auto object = dependencies->object(bridge, context);
    if (!object)
        return;
    const auto entity = dependencies->entity(bridge, object);
    if (!entity)
        return;
    const auto uuid = dependencies->uuid(bridge, entity);
    FriendRecord record;
    record.key.words[0] = dependencies->high(bridge, uuid);
    record.key.words[1] = dependencies->low(bridge, uuid);
    record.timestamp = dependencies->timestamp();
    record.reserved = 0;
    FriendAction action{};
    auto *found = recovered_sorted_lookup(table->data, sizeof(record), &table->capacity, &record,
                                          recovered_uuid_compare);
    if (found) {
        action.event_type = 19;
        recovered_sorted_remove(table->data, sizeof(record), &table->capacity, found,
                                dependencies->memory);
    } else {
        if (static_cast<std::uint8_t>(dependencies->flags(bridge, entity, 2)))
            return;
        action.event_type = 19;
        action.added = 1;
        recovered_list_insert(&table->data, sizeof(record), &table->capacity, &record,
                              recovered_uuid_compare, dependencies->memory);
    }
    dependencies->emit(action_context, &action);
}
// END SOURCE modules/Friends/Friends_actions.cpp

// BEGIN SOURCE modules/Friends/Friends_runtime.cpp
#ifndef SLINKY_SHARE_8A4EC9E4B7F856A28453
#define SLINKY_SHARE_8A4EC9E4B7F856A28453
// BEGIN SOURCE native/verified/Friends_runtime.hpp
#include "../runtime/native/verified/Timer.hpp"

struct FriendsRuntimeDependencies {
    std::uintptr_t (*list)(GameAccessBridge *, std::uintptr_t);
    std::int32_t (*count)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*item)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    std::uint8_t (*same)(GameAccessBridge *, std::uintptr_t, std::uintptr_t);
    std::uintptr_t (*add_flags)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    std::uintptr_t (*remove_flags)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    void (*release)(void *);
    const FriendsActionDependencies *identity;
};
static_assert(sizeof(FriendsRuntimeDependencies) == 64);

extern "C" {
__declspec(dllexport) void recovered_bind_friends_runtime_access(FriendsRuntimeDependencies *);
__declspec(dllexport) void recovered_friends_scan(TimerEvent *, SortedTable *,
                                                  const FriendsRuntimeDependencies *);
__declspec(dllexport) void recovered_friends_disable(TimerEvent *, std::uintptr_t module_identity,
                                                     const FriendsRuntimeDependencies *);
__declspec(dllexport) void recovered_friends_release(SortedTable *,
                                                     const FriendsRuntimeDependencies *);
__declspec(dllexport) std::uintptr_t recovered_entity_flags_add(GameAccessBridge *, std::uintptr_t,
                                                                std::uint32_t);
__declspec(dllexport) std::uintptr_t recovered_entity_flags_remove(GameAccessBridge *,
                                                                   std::uintptr_t, std::uint32_t);
}
// END SOURCE native/verified/Friends_runtime.hpp

#endif // SLINKY_SHARE_8A4EC9E4B7F856A28453

#include <bit>
#include <cstring>

static std::uintptr_t identifier(GameAccessBridge *bridge, std::size_t offset) {
    std::uintptr_t value;
    std::memcpy(&value, bridge->metadata + offset, sizeof(value));
    return value;
}
template <class Function> static Function method(GameAccessBridge *bridge, std::size_t offset) {
    const auto *table = reinterpret_cast<const std::uintptr_t *>(*bridge->environment);
    return reinterpret_cast<Function>(table[offset / 8]);
}
static std::uintptr_t list(GameAccessBridge *bridge, std::uintptr_t world) {
    using Getter_Friends_runtime =
        std::uintptr_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t);
    return method<Getter_Friends_runtime>(bridge, 0x2f8)(bridge->environment, world,
                                                         identifier(bridge, 0x360));
}
static std::int32_t count_Friends_runtime(GameAccessBridge *bridge, std::uintptr_t list) {
    using Counter = std::int32_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t);
    return method<Counter>(bridge, 0x188)(bridge->environment, list, identifier(bridge, 0x28));
}
static std::uintptr_t item(GameAccessBridge *bridge, std::uintptr_t list, std::uint32_t index) {
    using Getter_Friends_runtime =
        std::uintptr_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t, std::uint32_t);
    return method<Getter_Friends_runtime>(bridge, 0x110)(bridge->environment, list,
                                                         identifier(bridge, 0x30), index);
}
static std::uint8_t same(GameAccessBridge *bridge, std::uintptr_t player, std::uintptr_t entity) {
    using Predicate = std::uint8_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t);
    return method<Predicate>(bridge, 0xc0)(bridge->environment, player, entity);
}
static std::uint32_t field_bits(GameAccessBridge *bridge, std::uintptr_t entity) {
    using Getter_Friends_runtime = float (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t);
    return std::bit_cast<std::uint32_t>(method<Getter_Friends_runtime>(bridge, 0x330)(
        bridge->environment, entity, identifier(bridge, 0x5c0)));
}
static std::uintptr_t set_field_bits(GameAccessBridge *bridge, std::uintptr_t entity,
                                     std::uint32_t bits) {
    using Setter = std::uintptr_t (*)(std::uintptr_t *, std::uintptr_t, std::uintptr_t, float);
    return method<Setter>(bridge, 0x378)(bridge->environment, entity, identifier(bridge, 0x5c0),
                                         std::bit_cast<float>(bits));
}
extern "C" __declspec(dllexport) std::uintptr_t
recovered_entity_flags_add(GameAccessBridge *bridge, std::uintptr_t entity, std::uint32_t mask) {
    const auto bits = field_bits(bridge, entity);
    const auto old = (bits & 0xffff0000u) == 0xb3150000u ? bits : 0xb3150000u;
    return set_field_bits(bridge, entity, 0xb3150000u | ((old | mask) & 0xffffu));
}
extern "C" __declspec(dllexport) std::uintptr_t
recovered_entity_flags_remove(GameAccessBridge *bridge, std::uintptr_t entity, std::uint32_t mask) {
    const auto bits = field_bits(bridge, entity);
    const auto old = (bits & 0xffff0000u) == 0xb3150000u ? bits & 0xffffu : 0xb3150000u;
    return set_field_bits(bridge, entity, (old & ~mask) | 0xb3150000u);
}
extern "C" __declspec(dllexport) void
recovered_bind_friends_runtime_access(FriendsRuntimeDependencies *dependencies) {
    dependencies->list = list;
    dependencies->count = count_Friends_runtime;
    dependencies->item = item;
    dependencies->same = same;
    dependencies->add_flags = recovered_entity_flags_add;
    dependencies->remove_flags = recovered_entity_flags_remove;
}

extern "C" __declspec(dllexport) void
recovered_friends_scan(TimerEvent *event, SortedTable *table,
                       const FriendsRuntimeDependencies *dependencies) {
    auto *game = event->game;
    if (!game->player)
        return;
    const auto timestamp = dependencies->identity->timestamp();
    const auto entities = dependencies->list(game->bridge, game->world);
    auto count_Friends_runtime = dependencies->count(game->bridge, entities);
    for (std::uint32_t index = 0; std::bit_cast<std::int32_t>(index) < count_Friends_runtime;
         ++index) {
        const auto entity = dependencies->item(game->bridge, entities, index);
        if (!dependencies->same(game->bridge, game->player, entity)) {
            const auto uuid = dependencies->identity->uuid(game->bridge, entity);
            FriendRecord record{};
            record.key.words[0] = dependencies->identity->high(game->bridge, uuid);
            record.key.words[1] = dependencies->identity->low(game->bridge, uuid);
            auto *found = static_cast<FriendRecord *>(recovered_sorted_lookup(
                table->data, sizeof(record), &table->capacity, &record, recovered_uuid_compare));
            if (found) {
                dependencies->add_flags(game->bridge, entity, 4);
                found->timestamp = timestamp;
            } else
                dependencies->remove_flags(game->bridge, entity, 4);
        }
        count_Friends_runtime = dependencies->count(game->bridge, entities);
    }
}
extern "C" __declspec(dllexport) void
recovered_friends_disable(TimerEvent *event, std::uintptr_t module_identity,
                          const FriendsRuntimeDependencies *dependencies) {
    if (event->module != module_identity || event->enabled != 0)
        return;
    auto *game = event->game;
    if (!game->world)
        return;
    const auto entities = dependencies->list(game->bridge, game->world);
    auto count_Friends_runtime = dependencies->count(game->bridge, entities);
    for (std::uint32_t index = 0; std::bit_cast<std::int32_t>(index) < count_Friends_runtime;
         ++index) {
        const auto entity = dependencies->item(game->bridge, entities, index);
        if (!dependencies->same(game->bridge, game->player, entity))
            dependencies->remove_flags(game->bridge, entity, 4);
        count_Friends_runtime = dependencies->count(game->bridge, entities);
    }
}
extern "C" __declspec(dllexport) void
recovered_friends_release(SortedTable *table, const FriendsRuntimeDependencies *dependencies) {
    dependencies->release(table->data);
    std::memset(table, 0, sizeof(*table));
}
// END SOURCE modules/Friends/Friends_runtime.cpp

#ifndef SLINKY_SHARE_B7C007568C945B1B4878
#define SLINKY_SHARE_B7C007568C945B1B4878
// BEGIN SOURCE modules/Friends/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
// END SOURCE modules/Friends/Api.hpp

#endif // SLINKY_SHARE_B7C007568C945B1B4878

// Convenient borrowed-state interface

namespace shareable {
class Friends {
  public:
    static constexpr const char *kName = "Friends";
    static constexpr const char *kDescription = "Lets you mark other players as friendly.";
    explicit Friends(std::uint8_t *image) : image_(image) {}
    // Middle-click to add. Config key: middle_click_add.
    BooleanSetting &middle_click_add() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f0248);
    }
    // friends. Config key: friends.
    ListSetting &friends() const {
        return *reinterpret_cast<ListSetting *>(image_ + 0x2f0268);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_friends_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_friends_settings(&context, image_, &dependencies);
    }
    static std::uint64_t
    resolveNamePrefix(TimerGame *context, const ::reconstruction::friends::NameSlice *request,
                      FriendRecord *output, char *name, const std::uint8_t *image,
                      const ::reconstruction::friends::CommandDependencies &deps) {
        return ::reconstruction::friends::resolveNamePrefix(context, request, output, name, image,
                                                            deps);
    }
    std::uint64_t addByName(TimerGame *context, const ::reconstruction::friends::NameSlice *request,
                            const ::reconstruction::friends::CommandDependencies &deps) {
        return ::reconstruction::friends::addByName(context, request, image_, deps);
    }
    std::uint64_t removeByName(TimerGame *context,
                               const ::reconstruction::friends::NameSlice *request,
                               const ::reconstruction::friends::CommandDependencies &deps) {
        return ::reconstruction::friends::removeByName(context, request, image_, deps);
    }
    std::uint64_t addNearby(TimerGame *context,
                            const ::reconstruction::friends::NearbyArguments *arguments,
                            const ::reconstruction::friends::CommandDependencies &deps) {
        return ::reconstruction::friends::addNearby(context, arguments, image_, deps);
    }
    std::uint64_t clearAll(TimerGame *context,
                           const ::reconstruction::friends::CommandDependencies &deps) {
        return ::reconstruction::friends::clearAll(context, image_, deps);
    }
    static void bindListStorage(FriendsListDependencies *dependencies) {
        ::recovered_bind_friends_list_storage(dependencies);
    }
    static bool typedAdd(const FriendsListState *state, const char *name) {
        return ::recovered_friends_typed_add(state, name);
    }
    static void typedClear(const FriendsListState *state) {
        ::recovered_friends_typed_clear(state);
    }
    static void bindTypedList(ListSetting *setting, FriendsListState *state) {
        ::recovered_bind_friends_typed_list(setting, state);
    }
    static std::uint64_t typedUi(std::uint64_t ui, std::uint64_t layout, FriendsSettings *settings,
                                 UiDirtyState *dirty, const SettingsUiEndpoints *endpoints) {
        return ::recovered_friends_typed_ui(ui, layout, settings, dirty, endpoints);
    }
    static void typedSettings(SettingsContext *context, FriendsSettings *settings,
                              const SettingsDependencies *boolean,
                              const ListSettingsDependencies *lists) {
        ::recovered_friends_typed_settings(context, settings, boolean, lists);
    }
    static void bindActionAccess(FriendsActionDependencies *dependencies) {
        ::recovered_bind_friends_action_access(dependencies);
    }
    static void action(GameAccessBridge *bridge, std::uintptr_t action_context,
                       const std::uint8_t *enabled, SortedTable *table,
                       const FriendsActionDependencies *dependencies) {
        ::recovered_friends_action(bridge, action_context, enabled, table, dependencies);
    }
    static std::uintptr_t entityFlagsAdd(GameAccessBridge *bridge, std::uintptr_t entity,
                                         std::uint32_t mask) {
        return ::recovered_entity_flags_add(bridge, entity, mask);
    }
    static std::uintptr_t entityFlagsRemove(GameAccessBridge *bridge, std::uintptr_t entity,
                                            std::uint32_t mask) {
        return ::recovered_entity_flags_remove(bridge, entity, mask);
    }
    static void bindRuntimeAccess(FriendsRuntimeDependencies *dependencies) {
        ::recovered_bind_friends_runtime_access(dependencies);
    }
    static void scan(TimerEvent *event, SortedTable *table,
                     const FriendsRuntimeDependencies *dependencies) {
        ::recovered_friends_scan(event, table, dependencies);
    }
    static void disable(TimerEvent *event, std::uintptr_t module_identity,
                        const FriendsRuntimeDependencies *dependencies) {
        ::recovered_friends_disable(event, module_identity, dependencies);
    }
    static void release(SortedTable *table, const FriendsRuntimeDependencies *dependencies) {
        ::recovered_friends_release(table, dependencies);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
