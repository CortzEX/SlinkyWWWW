// Anti Bot

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Anti_Bot.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Anti_Bot.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Anti Bot: lib_win settings 0x31490.
// UI 0x313f0.
static constexpr UiStep ui_steps_Surface_Anti_Bot[] = {
    {UiControl::section, "Main", 0},          {UiControl::choice, nullptr, 0x2eaf58},
    {UiControl::checkbox, nullptr, 0x2eafd8}, {UiControl::checkbox, nullptr, 0x2eafb8},
    {UiControl::checkbox, nullptr, 0x2eaf18}, {UiControl::checkbox, nullptr, 0x2eaf98},
    {UiControl::number, nullptr, 0x2eaee0},
};
static constexpr SettingsStep settings_steps_Surface_Anti_Bot[] = {
    {SettingsControl::choice, "invalid_uuid", 0x2eaf58},
    {SettingsControl::boolean, "invalid_username", 0x2eafd8},
    {SettingsControl::boolean, "always_invis", 0x2eafb8},
    {SettingsControl::boolean, "always_stationary", 0x2eaf18},
    {SettingsControl::boolean, "sleeping", 0x2eaf98},
    {SettingsControl::number, "min_age", 0x2eaee0},
};
static constexpr ModuleSurface surface_Surface_Anti_Bot{
    ui_steps_Surface_Anti_Bot, std::size(ui_steps_Surface_Anti_Bot),
    settings_steps_Surface_Anti_Bot, std::size(settings_steps_Surface_Anti_Bot)};

extern "C" __declspec(dllexport) void
recovered_anti_bot_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                      const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Anti_Bot, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_anti_bot_settings(SettingsContext *context, std::uint8_t *image,
                            const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Anti_Bot, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Anti_Bot.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Anti_Bot/anti_bot.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_914EE2AD87EA5C9E3E50
#define SLINKY_SHARE_914EE2AD87EA5C9E3E50
// BEGIN SOURCE modules/Anti_Bot/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Anti_Bot {
namespace Storage {
inline constexpr std::uint32_t nativeData_13cf70 = 0x13cf70;
inline constexpr std::uint32_t nativeData_1510c8 = 0x1510c8;
inline constexpr std::uint32_t moduleDescriptor = 0x2eacd0;
inline constexpr std::uint32_t min_ageRecord = 0x2eaee0;
inline constexpr std::uint32_t min_ageCurrent = 0x2eaf10;
inline constexpr std::uint32_t always_stationaryRecord = 0x2eaf18;
inline constexpr std::uint32_t always_stationaryCurrent = 0x2eaf30;
inline constexpr std::uint32_t invalid_uuidRecord = 0x2eaf58;
inline constexpr std::uint32_t invalid_uuidCurrent = 0x2eaf88;
inline constexpr std::uint32_t sleepingRecord = 0x2eaf98;
inline constexpr std::uint32_t sleepingCurrent = 0x2eafb0;
inline constexpr std::uint32_t always_invisRecord = 0x2eafb8;
inline constexpr std::uint32_t always_invisCurrent = 0x2eafd0;
inline constexpr std::uint32_t invalid_usernameRecord = 0x2eafd8;
inline constexpr std::uint32_t invalid_usernameCurrent = 0x2eaff0;
inline constexpr std::uint32_t cachedWorldIdentifier = 0x2f9de8;
inline constexpr std::uint32_t playerHistoryTable = 0x2f9df0;
inline constexpr std::uint32_t playerHistoryCount = 0x2f9df8;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    ChoiceSetting &invalid_uuid() const {
        return *reinterpret_cast<ChoiceSetting *>(image + Storage::invalid_uuidRecord);
    }
    BooleanSetting &invalid_username() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::invalid_usernameRecord);
    }
    BooleanSetting &always_invis() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::always_invisRecord);
    }
    BooleanSetting &always_stationary() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::always_stationaryRecord);
    }
    BooleanSetting &sleeping() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::sleepingRecord);
    }
    NumberSetting &min_age() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::min_ageRecord);
    }
};
// Runtime-observed native labels for config key "invalid_uuid". Numeric values preserved.
enum class Invalid_uuidMode : std::uint32_t {
    Off = 0,
    Stationary_only = 1,
    Always = 2,
};
} // namespace reconstruction::Anti_Bot
// END SOURCE modules/Anti_Bot/Settings.hpp

#endif // SLINKY_SHARE_914EE2AD87EA5C9E3E50

#include <stdint.h>
#include <string.h>
namespace reconstruction::Anti_Bot {
namespace NativeEntry {
inline constexpr uint32_t entityPosition = 0x23030;
inline constexpr uint32_t previousEntityPosition = 0x230d0;
inline constexpr uint32_t entityUuidObject = 0x23740;
inline constexpr uint32_t entityTicksExisted = 0x23760;
inline constexpr uint32_t entityInventory = 0x23f40;
inline constexpr uint32_t entityInvisible = 0x240a0;
inline constexpr uint32_t worldPlayerList = 0x24600;
inline constexpr uint32_t listSize = 0x24e50;
inline constexpr uint32_t listElement = 0x24e80;
inline constexpr uint32_t itemNumericType = 0x25c50;
inline constexpr uint32_t stackItem = 0x25d10;
inline constexpr uint32_t inventoryStackAt = 0x26140;
inline constexpr uint32_t uuidLeastWord = 0x27d90;
inline constexpr uint32_t uuidMostWord = 0x27dc0;
inline constexpr uint32_t markEntityRejected = 0x2ad20;
inline constexpr uint32_t clearEntityRejected = 0x2ad80;
inline constexpr uint32_t jniSameObject = 0x800000c0;
inline constexpr uint32_t jniStringLength = 0x80000520;
inline constexpr uint32_t jniAcquireStringCritical = 0x80000700;
inline constexpr uint32_t jniReleaseStringCritical = 0x80000708;
} // namespace NativeEntry

using antibot_dispatch = native_binding::WordEndpoints;
int32_t compareUuidRecords(const uint8_t *, const uint64_t *, const uint64_t *);
static int32_t storageCompareUuidRecords(uint64_t, const void *left, const void *right) {
    return compareUuidRecords(nullptr, static_cast<const uint64_t *>(left),
                              static_cast<const uint64_t *>(right));
}

static uint64_t read64(const void *p) {
    uint64_t value;
    memcpy(&value, p, sizeof(value));
    return value;
}

static uint32_t read32(const void *p) {
    uint32_t value;
    memcpy(&value, p, sizeof(value));
    return value;
}

static void write_zero(void *p, size_t size) {
    memset(p, 0, size);
}

static uint64_t call2(antibot_dispatch call, uint32_t rva, uint64_t a, uint64_t b) {
    return call(rva, a, b, 0, 0, 0, 0);
}

static uint64_t call3(antibot_dispatch call, uint32_t rva, uint64_t a, uint64_t b, uint64_t c) {
    return call(rva, a, b, c, 0, 0, 0);
}

static uint64_t indirect3(antibot_dispatch call, uint32_t id, uint64_t a, uint64_t b, uint64_t c,
                          uint64_t target) {
    return call(id, a, b, c, 0, 0, target);
}

static void update_cache_world(uint8_t *image, uint32_t world, antibot_dispatch call) {
    if (read32(image + Storage::cachedWorldIdentifier) == world)
        return;
    call(Storage::nativeData_13cf70, read64(image + Storage::playerHistoryTable), 0, 0, 0, 0, 0);
    write_zero(image + Storage::playerHistoryTable, 16);
    memcpy(image + Storage::cachedWorldIdentifier, &world, sizeof(world));
}

void updatePlayerCache(uint8_t *event, uint8_t *image, antibot_dispatch call) {
    uint8_t *context = (uint8_t *)(uintptr_t)read64(event + 8);
    uint64_t target = read64(context + 0x20);
    uint32_t world = target ? (uint32_t)call2(call, 0x26060, read64(context), target) : 0;
    update_cache_world(image, world, call);
    if (!read64(context + 0x20))
        return;

    uint64_t collection =
        call2(call, NativeEntry::worldPlayerList, read64(context), read64(context + 0x20));
    int32_t count = (int32_t)call2(call, NativeEntry::listSize, read64(context), collection);
    if (count <= 0)
        return;

    uint32_t index = 0;
    const double distance_limit =
        *(const double *)(const void *)(image + Storage::nativeData_1510c8);
    for (;;) {
        uint64_t item = call3(call, NativeEntry::listElement, read64(context), collection, index);
        uint64_t controller = read64((const void *)(uintptr_t)(read64(context) + 8));
        uint64_t table = read64((const void *)(uintptr_t)controller);
        uint64_t target_fn = read64((const void *)(uintptr_t)(table + 0xc0));
        uint8_t isLocalPlayer = (uint8_t)indirect3(call, NativeEntry::jniSameObject, controller,
                                                   read64(context + 0x28), item, target_fn);
        if (!isLocalPlayer) {
            uint64_t entity = call2(call, NativeEntry::entityUuidObject, read64(context), item);
            uint64_t key0 = call2(call, NativeEntry::uuidMostWord, read64(context), entity);
            uint64_t key1 = call2(call, NativeEntry::uuidLeastWord, read64(context), entity);
            uint64_t key[4] = {key0, key1, 0, 0};
            uint64_t entry_ptr = reinterpret_cast<uintptr_t>(recovered_list_insert(
                image + Storage::playerHistoryTable, 0x20, image + Storage::playerHistoryCount, key,
                storageCompareUuidRecords, &call.native.listMemory));
            uint8_t *entry = (uint8_t *)(uintptr_t)entry_ptr;
            double a[3] = {0, 0, 0}, b[3] = {0, 0, 0};
            call3(call, NativeEntry::previousEntityPosition, (uintptr_t)a, read64(context), item);
            call3(call, NativeEntry::entityPosition, (uintptr_t)b, read64(context), item);
            double dx = a[0] - b[0];
            double dz = a[2] - b[2];
            double dz_squared = dz * dz;
            double dx_squared = dx * dx;
            double planar = dx_squared + dz_squared;
            double distance = planar + *(double *)(void *)(entry + 0x10);
            memcpy(entry + 0x10, &distance, sizeof(distance));

            {
                if (image[Storage::always_stationaryCurrent] == 1 && distance_limit > distance)
                    goto ignored;
                uint32_t mode = read32(image + Storage::invalid_uuidCurrent);
                if (mode != 0) {
                    uint32_t group = read32(entry) & 0xf000;
                    if (group == 0x2000 && (mode == 2 || distance_limit > distance))
                        goto ignored;
                }
                if (image[Storage::sleepingCurrent] == 1 &&
                    (uint8_t)call2(call, NativeEntry::entityInvisible, read64(context), item))
                    goto ignored;

                int32_t age =
                    (int32_t)call2(call, NativeEntry::entityTicksExisted, read64(context), item);
                if (image[Storage::always_invisCurrent] == 1 && entry[0x19] == 0) {
                    uint64_t armor_game = read64(context);
                    uint8_t should_check =
                        (uint8_t)call3(call, 0x23f60, armor_game, item, read64(context + 0x28));
                    if (should_check) {
                        uint64_t armor_object =
                            call2(call, NativeEntry::entityInventory, armor_game, item);
                        const uint32_t slots[] = {0x24, 0x25, 0x26, 0x27};
                        for (unsigned i = 0; i < 4; ++i) {
                            uint64_t descriptor = call3(call, NativeEntry::inventoryStackAt,
                                                        armor_game, armor_object, slots[i]);
                            if (!descriptor)
                                continue;
                            uint64_t slot =
                                call2(call, NativeEntry::stackItem, armor_game, descriptor);
                            if (!slot)
                                continue;
                            uint32_t occupied = (uint32_t)call2(call, NativeEntry::itemNumericType,
                                                                armor_game, slot);
                            if (occupied != 0)
                                goto armor_found;
                        }
                        goto ignored;
                    }
                armor_found:
                    if (age >= 21)
                        entry[0x19] = 1;
                }
            {
                float threshold;
                memcpy(&threshold, image + Storage::min_ageCurrent, sizeof(threshold));
                if (0.0f < threshold && (int8_t)entry[0x18] == 0) {
                    float age_as_float = (float)age;
                    if (age_as_float < threshold)
                        goto ignored;
                    entry[0x18] = 1;
                }
            }

                if (image[Storage::invalid_usernameCurrent] == 1 && entry[0x1a] == 0) {
                    uint64_t name_controller =
                        read64((const void *)(uintptr_t)(read64(context) + 8));
                    uint64_t name_object = call2(call, 0x23830, read64(context), item);
                    uint64_t name_table = read64((const void *)(uintptr_t)name_controller);
                    int32_t name_length = (int32_t)indirect3(
                        call, NativeEntry::jniStringLength, name_controller, name_object, 0,
                        read64((const void *)(uintptr_t)(name_table + 0x520)));
                    name_table = read64((const void *)(uintptr_t)name_controller);
                    uint64_t name = indirect3(
                        call, NativeEntry::jniAcquireStringCritical, name_controller, name_object,
                        0, read64((const void *)(uintptr_t)(name_table + 0x700)));
                    int32_t i = 0;
                    while (name_length > 0 && i < name_length) {
                        uint16_t ch = *(const uint16_t *)(uintptr_t)(name + (uint64_t)i * 2);
                        if (ch == 0xa7) {
                            ++i;
                        } else {
                            uint16_t upper = (uint16_t)(ch & 0xffdf);
                            if ((uint16_t)(upper - 0x41) < 0x1a || ch == 0x5f ||
                                (uint16_t)(ch - 0x30) < 10) {
                                entry[0x1a] = 1;
                                break;
                            }
                        }
                        ++i;
                    }
                    uint64_t release_table = read64((const void *)(uintptr_t)name_controller);
                    uint64_t release_target =
                        read64((const void *)(uintptr_t)(release_table + 0x708));
                    (void)call(NativeEntry::jniReleaseStringCritical, name_controller, name_object,
                               name, release_table, 0, release_target);
                    if (entry[0x1a] == 0)
                        goto ignored;
                }
                call3(call, NativeEntry::clearEntityRejected, read64(context), item, 2);
                goto next;
            }
        ignored:
            call3(call, NativeEntry::markEntityRejected, read64(context), item, 2);
        }
    next:
        ++index;
        count = (int32_t)call2(call, NativeEntry::listSize, read64(context), collection);
        if ((int32_t)index >= count)
            return;
    }
}

void onModuleStateChanged(uint8_t *event, uint8_t *image, antibot_dispatch call) {
    if (read64(event + 0x10) != (uintptr_t)(image + Storage::moduleDescriptor) || event[0x18] != 0)
        return;
    call(Storage::nativeData_13cf70, read64(image + Storage::playerHistoryTable), 0, 0, 0, 0, 0);
    write_zero(image + Storage::playerHistoryTable, 16);
    uint8_t *context = (uint8_t *)(uintptr_t)read64(event + 8);
    uint64_t target = read64(context + 0x20);
    if (!target)
        return;
    uint64_t collection = call2(call, NativeEntry::worldPlayerList, read64(context), target);
    int32_t count = (int32_t)call2(call, NativeEntry::listSize, read64(context), collection);
    if (count <= 0)
        return;
    uint32_t index = 0;
    do {
        uint64_t item = call3(call, NativeEntry::listElement, read64(context), collection, index);
        uint64_t controller = read64((const void *)(uintptr_t)(read64(context) + 8));
        uint64_t table = read64((const void *)(uintptr_t)controller);
        uint64_t target_fn = read64((const void *)(uintptr_t)(table + 0xc0));
        uint8_t isLocalPlayer = (uint8_t)indirect3(call, NativeEntry::jniSameObject, controller,
                                                   read64(context + 0x28), item, target_fn);
        if (!isLocalPlayer)
            call3(call, NativeEntry::clearEntityRejected, read64(context), item, 2);
        ++index;
        count = (int32_t)call2(call, NativeEntry::listSize, read64(context), collection);
    } while ((int32_t)index < count);
}

/* Comparator is lexicographic on the two qwords after big-endian byte swap. */
int32_t compareUuidRecords(const uint8_t *unused, const uint64_t *left, const uint64_t *right) {
    (void)unused;
    uint64_t l0 = left[0], r0 = right[0], l1 = left[1], r1 = right[1];
    uint64_t b0 = 0, b1 = 0, c0 = 0, c1 = 0;
    for (unsigned i = 0; i < 8; ++i) {
        b0 = (b0 << 8) | ((l0 >> (i * 8)) & 0xff);
        c0 = (c0 << 8) | ((r0 >> (i * 8)) & 0xff);
        b1 = (b1 << 8) | ((l1 >> (i * 8)) & 0xff);
        c1 = (c1 << 8) | ((r1 >> (i * 8)) & 0xff);
    }
    if (b0 != c0)
        return b0 < c0 ? -1 : 1;
    if (b1 == c1)
        return 0;
    return b1 < c1 ? -1 : 1;
}

} // namespace reconstruction::Anti_Bot
// END SOURCE modules/Anti_Bot/anti_bot.cpp

// Convenient borrowed-state interface

namespace shareable {
class AntiBot {
  public:
    static constexpr const char *kName = "Anti Bot";
    static constexpr const char *kDescription = "Ignores NPCs for specific modules.";
    explicit AntiBot(std::uint8_t *image) : image_(image) {}
    // Invalid UUID. Config key: invalid_uuid.
    ChoiceSetting &invalid_uuid() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2eaf58);
    }
    // Option labels observed in the captured metadata.
    enum class InvalidUuidMode : std::uint32_t { Off = 0, StationaryOnly = 1, Always = 2 };
    // Invalid username. Config key: invalid_username.
    BooleanSetting &invalid_username() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eafd8);
    }
    // Always invisible. Config key: always_invis.
    BooleanSetting &always_invis() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eafb8);
    }
    // Always stationary. Config key: always_stationary.
    BooleanSetting &always_stationary() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eaf18);
    }
    // Sleeping. Config key: sleeping.
    BooleanSetting &sleeping() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2eaf98);
    }
    // Minimum entity age. Config key: min_age.
    NumberSetting &min_age() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2eaee0);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_anti_bot_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_anti_bot_settings(&context, image_, &dependencies);
    }
    void updatePlayerCache(uint8_t *event, ::reconstruction::Anti_Bot::antibot_dispatch call) {
        ::reconstruction::Anti_Bot::updatePlayerCache(event, image_, call);
    }
    void onModuleStateChanged(uint8_t *event, ::reconstruction::Anti_Bot::antibot_dispatch call) {
        ::reconstruction::Anti_Bot::onModuleStateChanged(event, image_, call);
    }
    static int32_t compareUuidRecords(const uint8_t *unused, const uint64_t *left,
                                      const uint64_t *right) {
        return ::reconstruction::Anti_Bot::compareUuidRecords(unused, left, right);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
