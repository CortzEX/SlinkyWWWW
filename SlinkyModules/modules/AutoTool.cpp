// Auto Tool

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Auto_Tool.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Auto_Tool.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Auto Tool: lib_win settings 0x375e0.
static constexpr SettingsStep settings_steps_Surface_Auto_Tool[] = {
    {SettingsControl::number, "activation_time", 0x2ee370},
    {SettingsControl::boolean, "switch_back", 0x2ee468},
    {SettingsControl::boolean, "allow_using_sword", 0x2ee3c8},
    {SettingsControl::boolean, "allow_using_tools", 0x2ee3e8},
    {SettingsControl::boolean, "allow_using_fists", 0x2ee3a8},
    {SettingsControl::boolean, "allow_using_other", 0x2ee408},
    {SettingsControl::boolean, "require_sneak", 0x2ee428},
    {SettingsControl::boolean, "restrict_allowed_blocks", 0x2ee448},
    {SettingsControl::list, "allowed_blocks", 0x2ee488},
};
static constexpr ModuleSurface surface_Surface_Auto_Tool{
    nullptr, 0, settings_steps_Surface_Auto_Tool, std::size(settings_steps_Surface_Auto_Tool)};

extern "C" __declspec(dllexport) void
recovered_auto_tool_settings(SettingsContext *context, std::uint8_t *image,
                             const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Auto_Tool, context, image, *dependencies);
}

// Auto Tool: lib_win runtime UI 0x374e0.
extern "C" __declspec(dllexport) void
recovered_auto_tool_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                       const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Main");
    dependencies->number(layout, ui, image + 0x2ee370);
    dependencies->checkbox(layout, ui, image + 0x2ee468);
    dependencies->section(ui, layout, "Allow while using");
    dependencies->checkbox(layout, ui, image + 0x2ee3c8);
    dependencies->checkbox(layout, ui, image + 0x2ee3e8);
    dependencies->checkbox(layout, ui, image + 0x2ee3a8);
    dependencies->checkbox(layout, ui, image + 0x2ee408);
    dependencies->section(ui, layout, "Conditions");
    dependencies->checkbox(layout, ui, image + 0x2ee428);
    dependencies->checkbox(layout, ui, image + 0x2ee448);
    if (image[0x2ee460] == 1) {
        dependencies->list(layout, ui, image + 0x2ee488);
    }
}
// END SOURCE native/verified/surfaces/Surface_Auto_Tool.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Auto_Tool/auto_tool.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_EAE01518541D4E21C825
#define SLINKY_SHARE_EAE01518541D4E21C825
// BEGIN SOURCE modules/Auto_Tool/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Auto_Tool {
namespace Storage {
inline constexpr std::uint32_t nativeData_13cf70 = 0x13cf70;
inline constexpr std::uint32_t nativeData_152420 = 0x152420;
inline constexpr std::uint32_t moduleDescriptor = 0x2ee158;
inline constexpr std::uint32_t nativeData_2ee368 = 0x2ee368;
inline constexpr std::uint32_t nativeData_2ee36c = 0x2ee36c;
inline constexpr std::uint32_t activation_timeRecord = 0x2ee370;
inline constexpr std::uint32_t activation_timeCurrent = 0x2ee3a0;
inline constexpr std::uint32_t allow_using_fistsRecord = 0x2ee3a8;
inline constexpr std::uint32_t allow_using_fistsCurrent = 0x2ee3c0;
inline constexpr std::uint32_t allow_using_swordRecord = 0x2ee3c8;
inline constexpr std::uint32_t allow_using_swordCurrent = 0x2ee3e0;
inline constexpr std::uint32_t allow_using_toolsRecord = 0x2ee3e8;
inline constexpr std::uint32_t allow_using_toolsCurrent = 0x2ee400;
inline constexpr std::uint32_t allow_using_otherRecord = 0x2ee408;
inline constexpr std::uint32_t allow_using_otherCurrent = 0x2ee420;
inline constexpr std::uint32_t require_sneakRecord = 0x2ee428;
inline constexpr std::uint32_t require_sneakCurrent = 0x2ee440;
inline constexpr std::uint32_t restrict_allowed_blocksRecord = 0x2ee448;
inline constexpr std::uint32_t restrict_allowed_blocksCurrent = 0x2ee460;
inline constexpr std::uint32_t switch_backRecord = 0x2ee468;
inline constexpr std::uint32_t switch_backCurrent = 0x2ee480;
inline constexpr std::uint32_t allowed_blocksRecord = 0x2ee488;
inline constexpr std::uint32_t nativeData_2fc520 = 0x2fc520;
inline constexpr std::uint32_t nativeData_2fc528 = 0x2fc528;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
    NumberSetting &activation_time() const {
        return *reinterpret_cast<NumberSetting *>(image + Storage::activation_timeRecord);
    }
    BooleanSetting &switch_back() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::switch_backRecord);
    }
    BooleanSetting &allow_using_sword() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::allow_using_swordRecord);
    }
    BooleanSetting &allow_using_tools() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::allow_using_toolsRecord);
    }
    BooleanSetting &allow_using_fists() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::allow_using_fistsRecord);
    }
    BooleanSetting &allow_using_other() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::allow_using_otherRecord);
    }
    BooleanSetting &require_sneak() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::require_sneakRecord);
    }
    BooleanSetting &restrict_allowed_blocks() const {
        return *reinterpret_cast<BooleanSetting *>(image + Storage::restrict_allowed_blocksRecord);
    }
    ListSetting &allowed_blocks() const {
        return *reinterpret_cast<ListSetting *>(image + Storage::allowed_blocksRecord);
    }
};
} // namespace reconstruction::Auto_Tool
// END SOURCE modules/Auto_Tool/Settings.hpp

#endif // SLINKY_SHARE_EAE01518541D4E21C825

#include <math.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
namespace reconstruction::Auto_Tool {
namespace NativeEntry {
inline constexpr uint32_t clientOptions = 0x22cf0;
inline constexpr uint32_t currentHitResult = 0x22e10;
inline constexpr uint32_t entityInventory = 0x23f40;
inline constexpr uint32_t entityUsingItem = 0x23f90;
inline constexpr uint32_t hitResultType = 0x24b50;
inline constexpr uint32_t hitBlockCoordinates = 0x24c10;
inline constexpr uint32_t sneakKey = 0x25030;
inline constexpr uint32_t attackKey = 0x25270;
inline constexpr uint32_t keyDown = 0x25430;
inline constexpr uint32_t physicalKeyWord = 0x25490;
inline constexpr uint32_t inventorySelectedSlot = 0x25a60;
inline constexpr uint32_t selectInventorySlot = 0x25a80;
inline constexpr uint32_t itemNumericType = 0x25c50;
inline constexpr uint32_t stackBlockEfficiency = 0x25d40;
inline constexpr uint32_t inventoryStackAt = 0x26140;
inline constexpr uint32_t heldItem = 0x28a50;
inline constexpr uint32_t claimModuleAction = 0x2aa80;
inline constexpr uint32_t releaseModuleAction = 0x2aab0;
inline constexpr uint32_t itemPolicyMatches = 0x2ac60;
} // namespace NativeEntry

struct dispatch_fn {
    native_binding::Context &native;
    void *user;
    uint64_t (*unresolved)(void *, uintptr_t, uint32_t, uint64_t, uint64_t, uint64_t, uint64_t,
                           uint64_t);
    uint64_t operator()(uintptr_t state, uint32_t rva, uint64_t a, uint64_t b, uint64_t c,
                        uint64_t d, uint64_t e) const {
        const uint64_t words[5] = {a, b, c, d, e};
        native_binding::Value value;
        if (native_binding::resolve(native, rva, words, value))
            return value.bits;
        return unresolved(user, state, rva, a, b, c, d, e);
    }
};
typedef struct {
    uintptr_t game;
    uint8_t gap08[0x10];
    uintptr_t key;
    uintptr_t state_arg;
    uintptr_t target;
    uint8_t gap30[0x10];
    uint8_t enabled;
} ToolContext;
typedef struct {
    uintptr_t unused;
    volatile ToolContext *context;
} ToolEvent;
enum {
    SELECTED = Storage::nativeData_2ee368,
    LAST_INDEX = Storage::nativeData_2ee36c,
    GROUP_A = Storage::allow_using_fistsCurrent,
    GROUP_B = Storage::allow_using_swordCurrent,
    GROUP_C = Storage::allow_using_toolsCurrent,
    GROUP_DEFAULT = Storage::allow_using_otherCurrent,
    ACTION_GATE = Storage::require_sneakCurrent,
    MATCH_GATE = Storage::restrict_allowed_blocksCurrent,
    SWITCH_BACK = Storage::switch_backCurrent,
    RESET_DELAY = Storage::activation_timeCurrent,
    COOLDOWN = Storage::nativeData_2fc520,
    SLOT_FILTER = Storage::nativeData_2fc528,
    MIN_SCORE = Storage::nativeData_152420
};
enum {
    H_23F40 = NativeEntry::entityInventory,
    H_25A60 = NativeEntry::inventorySelectedSlot,
    H_28A50 = NativeEntry::heldItem,
    H_25C50 = NativeEntry::itemNumericType,
    H_22CF0 = NativeEntry::clientOptions,
    H_23F90 = NativeEntry::entityUsingItem,
    H_25270 = NativeEntry::attackKey,
    H_25490 = NativeEntry::physicalKeyWord,
    H_25030 = NativeEntry::sneakKey,
    H_25430 = NativeEntry::keyDown,
    H_22E10 = NativeEntry::currentHitResult,
    H_24B50 = NativeEntry::hitResultType,
    H_24C10 = NativeEntry::hitBlockCoordinates,
    H_24690 = 0x24690,
    H_24280 = 0x24280,
    H_2AC60 = NativeEntry::itemPolicyMatches,
    H_26140 = NativeEntry::inventoryStackAt,
    H_25D40 = NativeEntry::stackBlockEfficiency,
    H_2AA80 = NativeEntry::claimModuleAction,
    H_25A80 = NativeEntry::selectInventorySlot,
    H_2AAB0 = NativeEntry::releaseModuleAction,
    H_13CF70 = Storage::nativeData_13cf70
};

static uint32_t read32(const volatile uint8_t *p, uint32_t rva) {
    uint32_t v;
    memcpy(&v, (const void *)(p + rva), 4);
    return v;
}
static uint64_t read64(const volatile uint8_t *p, uint32_t rva) {
    uint64_t v;
    memcpy(&v, (const void *)(p + rva), 8);
    return v;
}
static void write32(volatile uint8_t *p, uint32_t rva, uint32_t v) {
    memcpy((void *)(p + rva), &v, 4);
}
static int32_t signed32(uint32_t v) {
    int32_t s;
    memcpy(&s, &v, 4);
    return s;
}
static float float32(uint32_t v) {
    float f;
    memcpy(&f, &v, 4);
    return f;
}
static int32_t cvttsd2si(double v) {
    if (isnan(v) || v >= 2147483648.0 || v < -2147483648.0)
        return INT32_MIN;
    return (int32_t)v;
}
static int32_t cvttss2si(float v) {
    if (isnan(v) || v >= 2147483648.0f || v < -2147483648.0f)
        return INT32_MIN;
    return (int32_t)v;
}
static uint64_t call(dispatch_fn f, uintptr_t state, uint32_t id, uint64_t a, uint64_t b,
                     uint64_t c, uint64_t d, uint64_t e) {
    return f(state, id, a, b, c, d, e);
}
static int type_group(uint32_t item_type, uint8_t g_a, uint8_t g_b, uint8_t g_c,
                      uint8_t g_default) {
    uint32_t index = item_type - 0x100u;
    if (index > 0x67u)
        return g_default;
    switch (index) {
    case 0x00:
    case 0x01:
    case 0x02:
    case 0x0d:
    case 0x0e:
    case 0x0f:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x1c:
    case 0x1d:
    case 0x1e:
    case 0x67:
        return g_c;
    case 0x0b:
    case 0x0c:
    case 0x10:
    case 0x14:
    case 0x1b:
        return g_b;
    default:
        return g_default;
    }
}

void selectToolForBlock(uintptr_t event_address, volatile uint8_t *image, uintptr_t state,
                        dispatch_fn invoke) {
    volatile ToolEvent *event = (volatile ToolEvent *)event_address;
    volatile ToolContext *ctx = event->context;
    if (ctx->enabled != 1)
        return;
    uint64_t item = call(invoke, state, H_23F40, ctx->game, ctx->target, 0, 0, 0);
    int32_t current = signed32((uint32_t)call(invoke, state, H_25A60, ctx->game, item, 0, 0, 0));
    int32_t selected = signed32(read32(image, SELECTED));
    {
        if (selected != -1 && signed32(read32(image, LAST_INDEX)) != current) {
            write32(image, SELECTED, UINT32_MAX);
            goto restore;
        }
        if (selected == -1) {
            uint64_t held = call(invoke, state, H_28A50, ctx->game, ctx->target, 0, 0, 0);
            uint8_t choice = image[GROUP_A];
            if (held) {
                uint32_t item_type =
                    (uint32_t)call(invoke, state, H_25C50, ctx->game, held, 0, 0, 0);
                choice = (uint8_t)type_group(item_type, image[GROUP_A], image[GROUP_B],
                                             image[GROUP_C], image[GROUP_DEFAULT]);
            }
            if (choice != 1)
                goto failed;
        }

        uint64_t bridge = call(invoke, state, H_22CF0, ctx->game, ctx->key, 0, 0, 0);
        if ((uint8_t)call(invoke, state, H_23F90, ctx->game, ctx->target, 0, 0, 0) != 0)
            goto failed;
        uint64_t active = call(invoke, state, H_25270, ctx->game, bridge, 0, 0, 0);
        if ((uint8_t)call(invoke, state, H_25490, ctx->game, active, 0, 0, 0) == 0)
            goto failed;
        if (image[ACTION_GATE] == 1) {
            uint64_t action = call(invoke, state, H_25030, ctx->game, bridge, 0, 0, 0);
            if ((uint8_t)call(invoke, state, H_25430, ctx->game, action, 0, 0, 0) == 0)
                goto failed;
        }
        uint64_t entity = call(invoke, state, H_22E10, ctx->game, ctx->key, 0, 0, 0);
        if (!entity || (int32_t)call(invoke, state, H_24B50, ctx->game, entity, 0, 0, 0) != 1)
            goto failed;
        double coordinates[3];
        call(invoke, state, H_24C10, (uintptr_t)coordinates, ctx->game, entity, 0, 0);
        int32_t x = cvttsd2si(coordinates[0]), y = cvttsd2si(coordinates[1]),
                z = cvttsd2si(coordinates[2]);
        uint64_t slot = call(invoke, state, H_24690, ctx->game, ctx->state_arg, (uint32_t)x,
                             (uint32_t)y, (uint32_t)z);
        if (!slot)
            goto failed;
        if (image[MATCH_GATE] == 1) {
            uint32_t type = (uint32_t)call(invoke, state, H_24280, ctx->game, slot, 0, 0, 0);
            if ((uint8_t)call(invoke, state, H_2AC60, (uintptr_t)(image + SLOT_FILTER), type, 0, 0,
                              0) == 0)
                goto failed;
        }
        if (signed32(read32(image, COOLDOWN)) >= 1) {
            write32(image, COOLDOWN, read32(image, COOLDOWN) - 1);
            goto restore;
        }

        uintptr_t scan_game = ctx->game;
        float best = float32(read32(image, MIN_SCORE));
        int32_t best_index = current;
        for (int32_t offset = 0; offset < 9; offset++) {
            int32_t sum = signed32((uint32_t)current + (uint32_t)offset);
            int32_t index = (int32_t)((int64_t)sum - (int64_t)(sum / 9) * 9);
            uint64_t candidate =
                call(invoke, state, H_26140, scan_game, item, (uint32_t)index, 0, 0);
            if (candidate) {
                float score = float32(
                    (uint32_t)call(invoke, state, H_25D40, scan_game, candidate, slot, 0, 0));
                if (!isnan(score) && !isnan(best) && score > best) {
                    best = score;
                    best_index = index;
                }
            }
        }
        if (best_index == current)
            return;
        uint8_t locked = (uint8_t)call(invoke, state, H_2AA80,
                                       (uintptr_t)(image + Storage::moduleDescriptor), 0, 0, 0, 0);
        if (locked) {
            call(invoke, state, H_25A80, ctx->game, item, (uint32_t)best_index, 0, 0);
            write32(image, LAST_INDEX, (uint32_t)best_index);
            if (signed32(read32(image, SELECTED)) == -1 && image[SWITCH_BACK] != 0)
                write32(image, SELECTED, (uint32_t)current);
        }
        if (best_index != -1)
            return;
        goto restore;
    }
failed:
    write32(image, COOLDOWN, (uint32_t)cvttss2si(float32(read32(image, RESET_DELAY))));
restore:
    call(invoke, state, H_2AAB0, (uintptr_t)(image + Storage::moduleDescriptor), 0, 0, 0, 0);
    if (signed32(read32(image, SELECTED)) != -1) {
        uint32_t saved_index = read32(image, SELECTED);
        call(invoke, state, H_25A80, ctx->game, item, saved_index, 0, 0);
        write32(image, SELECTED, UINT32_MAX);
    }
}

void releaseBlockFilter(volatile uint8_t *image, uintptr_t state, dispatch_fn invoke) {
    uint64_t saved = read64(image, SLOT_FILTER);
    call(invoke, state, H_13CF70, saved, 0, 0, 0, 0);
    memset((void *)(image + SLOT_FILTER), 0, 16);
}

} // namespace reconstruction::Auto_Tool
// END SOURCE modules/Auto_Tool/auto_tool.cpp

// Convenient borrowed-state interface

namespace shareable {
class AutoTool {
  public:
    static constexpr const char *kName = "Auto Tool";
    static constexpr const char *kDescription = "Selects the best tool when digging.";
    explicit AutoTool(std::uint8_t *image) : image_(image) {}
    // Activation time. Config key: activation_time.
    NumberSetting &activation_time() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2ee370);
    }
    // Switch back when done. Config key: switch_back.
    BooleanSetting &switch_back() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ee468);
    }
    // Sword. Config key: allow_using_sword.
    BooleanSetting &allow_using_sword() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ee3c8);
    }
    // Tool. Config key: allow_using_tools.
    BooleanSetting &allow_using_tools() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ee3e8);
    }
    // Fists. Config key: allow_using_fists.
    BooleanSetting &allow_using_fists() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ee3a8);
    }
    // Other. Config key: allow_using_other.
    BooleanSetting &allow_using_other() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ee408);
    }
    // Sneaking. Config key: require_sneak.
    BooleanSetting &require_sneak() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ee428);
    }
    // Restrict allowed blocks. Config key: restrict_allowed_blocks.
    BooleanSetting &restrict_allowed_blocks() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2ee448);
    }
    // allowed_blocks. Config key: allowed_blocks.
    ListSetting &allowed_blocks() const {
        return *reinterpret_cast<ListSetting *>(image_ + 0x2ee488);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_auto_tool_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_auto_tool_settings(&context, image_, &dependencies);
    }
    static void selectToolForBlock(uintptr_t event_address, volatile uint8_t *image,
                                   uintptr_t state,
                                   ::reconstruction::Auto_Tool::dispatch_fn invoke) {
        ::reconstruction::Auto_Tool::selectToolForBlock(event_address, image, state, invoke);
    }
    static void releaseBlockFilter(volatile uint8_t *image, uintptr_t state,
                                   ::reconstruction::Auto_Tool::dispatch_fn invoke) {
        ::reconstruction::Auto_Tool::releaseBlockFilter(image, state, invoke);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
