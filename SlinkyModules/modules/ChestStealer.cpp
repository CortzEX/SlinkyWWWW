// Chest Stealer

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Chest_Stealer.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Chest_Stealer.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Chest Stealer: lib_win settings 0x48790.
// UI 0x486f0.
static constexpr UiStep ui_steps_Surface_Chest_Stealer[] = {
    {UiControl::section, "Main", 0},          {UiControl::number, nullptr, 0x2f5498},
    {UiControl::number, nullptr, 0x2f54f0},   {UiControl::number, nullptr, 0x2f5528},
    {UiControl::checkbox, nullptr, 0x2f5560}, {UiControl::section, "Main", 0},
    {UiControl::checkbox, nullptr, 0x2f54d0},
};
static constexpr SettingsStep settings_steps_Surface_Chest_Stealer[] = {
    {SettingsControl::number, "delay_after_open", 0x2f5498},
    {SettingsControl::number, "delay_before_close", 0x2f54f0},
    {SettingsControl::number, "speed", 0x2f5528},
    {SettingsControl::boolean, "smart_speed", 0x2f5560},
    {SettingsControl::boolean, "require_vanilla_title", 0x2f54d0},
};
static constexpr ModuleSurface surface_Surface_Chest_Stealer{
    ui_steps_Surface_Chest_Stealer, std::size(ui_steps_Surface_Chest_Stealer),
    settings_steps_Surface_Chest_Stealer, std::size(settings_steps_Surface_Chest_Stealer)};

extern "C" __declspec(dllexport) void
recovered_chest_stealer_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                           const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Chest_Stealer, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_chest_stealer_settings(SettingsContext *context, std::uint8_t *image,
                                 const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Chest_Stealer, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Chest_Stealer.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Chest_Stealer
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Chest_Stealer.cpp
static constexpr UiStep surface_chest_stealer_ui_steps[] = {
    {UiControl::section, "Main", 0},          {UiControl::number, nullptr, 0x2f5498},
    {UiControl::number, nullptr, 0x2f54f0},   {UiControl::number, nullptr, 0x2f5528},
    {UiControl::checkbox, nullptr, 0x2f5560}, {UiControl::section, "Main", 0},
    {UiControl::checkbox, nullptr, 0x2f54d0},
};
static constexpr SettingsStep surface_chest_stealer_settings_steps[] = {
    {SettingsControl::number, "delay_after_open", 0x2f5498},
    {SettingsControl::number, "delay_before_close", 0x2f54f0},
    {SettingsControl::number, "speed", 0x2f5528},
    {SettingsControl::boolean, "smart_speed", 0x2f5560},
    {SettingsControl::boolean, "require_vanilla_title", 0x2f54d0},
};
static constexpr ModuleSurface surface_chest_stealer_surface{
    surface_chest_stealer_ui_steps, std::size(surface_chest_stealer_ui_steps),
    surface_chest_stealer_settings_steps, std::size(surface_chest_stealer_settings_steps)};

extern "C" __declspec(dllexport) void
recovered_chest_stealer_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                                 const BoundSurfaceUiDependencies *dependencies) {
    render_module_surface(surface_chest_stealer_surface, ui, layout, image, *dependencies);
}
// END SOURCE shared/BoundSurfaces.cpp@Chest_Stealer

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Chest_Stealer/ChestStealer.cpp
#include "../runtime/native/verified/module_random.hpp"
#ifndef SLINKY_SHARE_9C1223725D6759AC62FE
#define SLINKY_SHARE_9C1223725D6759AC62FE
// BEGIN SOURCE modules/Chest_Stealer/Module.hpp
#include "../runtime/shared/RenderNativeBindings.hpp"
#include "../runtime/native/verified/module_random.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_chest_stealer_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                                 const BoundSurfaceUiDependencies *);
extern "C" void recovered_chest_stealer_settings(SettingsContext *, std::uint8_t *,
                                                 const SurfaceSettingsDependencies *);

namespace reconstruction::chest_stealer {
// The image view retains native storage offsets. It does not invent initialization.

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_chest_stealer_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_chest_stealer_settings(context, stateImage, &deps);
}
} // namespace reconstruction::chest_stealer

namespace reconstruction::chest_stealer {
using Endpoint5 = reconstruction::native_binding::RenderEndpoint<4, std::uint64_t>;
std::uint32_t compareTitle(std::uint8_t *, std::uint64_t, const char *, Endpoint5);
std::uint64_t updateOpenDelay(std::uint8_t *, std::uint8_t *, RandomState *,
                              const RandomConstants *, Endpoint5);
} // namespace reconstruction::chest_stealer

namespace reconstruction::chest_stealer::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t delay_after_open = 0x2f5498 + offsetof(NumberSetting, current);
inline constexpr std::size_t delay_before_close = 0x2f54f0 + offsetof(NumberSetting, current);
inline constexpr std::size_t speed = 0x2f5528 + offsetof(NumberSetting, current);
inline constexpr std::size_t smart_speed = 0x2f5560 + offsetof(BooleanSetting, current);
inline constexpr std::size_t require_vanilla_title = 0x2f54d0 + offsetof(BooleanSetting, current);
} // namespace reconstruction::chest_stealer::setting_offset
// END SOURCE modules/Chest_Stealer/Module.hpp

#endif // SLINKY_SHARE_9C1223725D6759AC62FE

#include <cstring>
#include <emmintrin.h>

namespace reconstruction::chest_stealer {
namespace {
template <class T> T load(const void *p) {
    T value;
    std::memcpy(&value, p, sizeof value);
    return value;
}
template <class T> void store(void *p, T value) {
    std::memcpy(p, &value, sizeof value);
}
std::uint64_t jniTarget(std::uintptr_t environment, std::size_t slot) {
    return load<std::uint64_t>(reinterpret_cast<const std::uint8_t *>(load<std::uint64_t>(
                                   reinterpret_cast<const void *>(environment))) +
                               slot);
}
} // namespace

// The native return preserves length bits above AL. Its caller tests only AL.
std::uint32_t compareTitle(std::uint8_t *bridge, std::uint64_t title, const char *expected,
                           Endpoint5 invoke) {
    const auto environment = load<std::uintptr_t>(bridge + 8);
    const auto temporary = invoke(jniTarget(environment, 0x538), environment,
                                  reinterpret_cast<std::uintptr_t>(expected), 0, 0);
    const auto other = invoke(0x27fc0, reinterpret_cast<std::uintptr_t>(bridge), temporary, 0, 0);
    const auto length =
        static_cast<std::uint32_t>(invoke(jniTarget(environment, 0x520), environment, title, 0, 0));
    const auto otherLength =
        static_cast<std::uint32_t>(invoke(jniTarget(environment, 0x520), environment, other, 0, 0));
    if (length != otherLength)
        return 0;
    const auto left = invoke(jniTarget(environment, 0x700), environment, title, 0, 0);
    const auto right = invoke(jniTarget(environment, 0x700), environment, other, 0, 0);
    const auto byteLength =
        static_cast<std::uint64_t>(static_cast<std::int64_t>(static_cast<std::int32_t>(length))) *
        2;
    const auto equal = static_cast<std::uint32_t>(invoke(0xab860, left, right, byteLength, 0)) == 0;
    const auto result = (length & 0xffffff00u) | static_cast<std::uint32_t>(equal);
    invoke(jniTarget(environment, 0x708), environment, title, left, 0);
    invoke(jniTarget(environment, 0x708), environment, other, right, 0);
    return result;
}

std::uint64_t updateOpenDelay(std::uint8_t *event, std::uint8_t *stateImage,
                              RandomState *randomState, const RandomConstants *constants,
                              Endpoint5 invoke) {
    auto *context = reinterpret_cast<std::uint8_t *>(load<std::uintptr_t>(event + 8));
    auto screen =
        invoke(0x22c90, load<std::uint64_t>(context), load<std::uint64_t>(context + 0x18), 0, 0);
    if (screen) {
        auto predicate = invoke(0x25bb0, load<std::uint64_t>(context), screen, 0, 0);
        if (static_cast<std::uint8_t>(predicate)) {
            if (stateImage[reconstruction::chest_stealer::setting_offset::require_vanilla_title] !=
                1)
                return predicate;
            const auto capturedBridge = load<std::uint64_t>(context);
            auto object = invoke(0x25c30, capturedBridge, screen, 0, 0);
            object = invoke(0x261e0, capturedBridge, object, 0, 0);
            if (object) {
                const auto title = invoke(0x26220, load<std::uint64_t>(context), object, 0, 0);
                auto result = compareTitle(
                    reinterpret_cast<std::uint8_t *>(load<std::uintptr_t>(context)), title,
                    reinterpret_cast<const char *>(stateImage + 0x155f9a), invoke);
                if (static_cast<std::uint8_t>(result))
                    return result;
                result = compareTitle(
                    reinterpret_cast<std::uint8_t *>(load<std::uintptr_t>(context)), title,
                    reinterpret_cast<const char *>(stateImage + 0x155faa), invoke);
                if (static_cast<std::uint8_t>(result))
                    return result;
            }
        }
    }
    store(
        stateImage + 0x304a10,
        load<float>(stateImage + reconstruction::chest_stealer::setting_offset::delay_after_open));
    const auto bounds = recovered_random_bounds(load<float>(stateImage + 0x155f60),
                                                load<float>(stateImage + 0x155f64));
    const auto sample = recovered_random_interval(randomState, constants, bounds);
    const auto scaled = _mm_cvtss_f32(_mm_mul_ss(
        _mm_set_ss(sample), _mm_load_ss(reinterpret_cast<const float *>(stateImage + 0x304a10))));
    store(stateImage + 0x304a10, scaled);
    // Native tail-call RVA 0x2aad0 receives 13, yielding the packed pair 4.0f,4.0f.
    return UINT64_C(0x4080000040800000);
}
} // namespace reconstruction::chest_stealer
// END SOURCE modules/Chest_Stealer/ChestStealer.cpp

// Convenient borrowed-state interface

namespace shareable {
class ChestStealer {
  public:
    static constexpr const char *kName = "Chest Stealer";
    static constexpr const char *kDescription = "";
    explicit ChestStealer(std::uint8_t *image) : image_(image) {}
    // Delay after open. Config key: delay_after_open.
    NumberSetting &delay_after_open() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f5498);
    }
    // Delay before close. Config key: delay_before_close.
    NumberSetting &delay_before_close() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f54f0);
    }
    // Speed. Config key: speed.
    NumberSetting &speed() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f5528);
    }
    // Smart speed. Config key: smart_speed.
    BooleanSetting &smart_speed() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f5560);
    }
    // Vanilla window title. Config key: require_vanilla_title.
    BooleanSetting &require_vanilla_title() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f54d0);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_chest_stealer_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_chest_stealer_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_chest_stealer_settings(&context, image_, &dependencies);
    }
    static std::uint32_t compareTitle(std::uint8_t *bridge, std::uint64_t title,
                                      const char *expected,
                                      ::reconstruction::chest_stealer::Endpoint5 invoke) {
        return ::reconstruction::chest_stealer::compareTitle(bridge, title, expected, invoke);
    }
    std::uint64_t updateOpenDelay(std::uint8_t *event, RandomState *randomState,
                                  const RandomConstants *constants,
                                  ::reconstruction::chest_stealer::Endpoint5 invoke) {
        return ::reconstruction::chest_stealer::updateOpenDelay(event, image_, randomState,
                                                                constants, invoke);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
