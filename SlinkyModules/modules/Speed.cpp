// Speed

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Speed.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Speed.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Speed: lib_win settings 0x4bc20.
// UI 0x4bbc0.
static constexpr UiStep ui_steps_Surface_Speed[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2f6338},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2f6318},
};
static constexpr SettingsStep settings_steps_Surface_Speed[] = {
    {SettingsControl::number, "speed", 0x2f6338},
    {SettingsControl::boolean, "require_ground", 0x2f6318},
};
static constexpr ModuleSurface surface_Surface_Speed{
    ui_steps_Surface_Speed, std::size(ui_steps_Surface_Speed), settings_steps_Surface_Speed,
    std::size(settings_steps_Surface_Speed)};

extern "C" __declspec(dllexport) void
recovered_speed_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                   const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Speed, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_speed_settings(SettingsContext *context, std::uint8_t *image,
                         const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Speed, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Speed.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Speed
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Speed.cpp
static constexpr UiStep surface_speed_ui_steps[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2f6338},
    {UiControl::section, "Conditions", 0},
    {UiControl::checkbox, nullptr, 0x2f6318},
};
static constexpr SettingsStep surface_speed_settings_steps[] = {
    {SettingsControl::number, "speed", 0x2f6338},
    {SettingsControl::boolean, "require_ground", 0x2f6318},
};
static constexpr ModuleSurface surface_speed_surface{
    surface_speed_ui_steps, std::size(surface_speed_ui_steps), surface_speed_settings_steps,
    std::size(surface_speed_settings_steps)};

extern "C" __declspec(dllexport) void
recovered_speed_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                         const BoundSurfaceUiDependencies *dependencies) {
    render_module_surface(surface_speed_surface, ui, layout, image, *dependencies);
}
// END SOURCE shared/BoundSurfaces.cpp@Speed

// Runtime behavior and native ABI entry points

#ifndef SLINKY_SHARE_EF7C851CF0AEC8782522
#define SLINKY_SHARE_EF7C851CF0AEC8782522
// BEGIN SOURCE modules/Speed/Module.hpp
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/shared/Geometry.hpp"
#include <cstddef>
#include <cstdint>

// These are the existing verified shared UI/configuration implementations.
extern "C" void recovered_speed_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                         const BoundSurfaceUiDependencies *);
extern "C" void recovered_speed_settings(SettingsContext *, std::uint8_t *,
                                         const SurfaceSettingsDependencies *);

namespace reconstruction::speed {
// The image view retains native storage offsets. It does not invent initialization.

inline void renderSettings(std::uint64_t ui, std::uint64_t layout, std::uint8_t *stateImage,
                           const BoundSurfaceUiDependencies &deps) {
    recovered_speed_bound_ui(ui, layout, stateImage, &deps);
}
inline void serializeConfig(SettingsContext *context, std::uint8_t *stateImage,
                            const SurfaceSettingsDependencies &deps) {
    recovered_speed_settings(context, stateImage, &deps);
}
} // namespace reconstruction::speed

namespace reconstruction::speed::setting_offset {
// Config keys identify storage. These constants assert no initial values.
inline constexpr std::size_t speed = 0x2f6338 + offsetof(NumberSetting, current);
inline constexpr std::size_t require_ground = 0x2f6318 + offsetof(BooleanSetting, current);
} // namespace reconstruction::speed::setting_offset
// END SOURCE modules/Speed/Module.hpp

#endif // SLINKY_SHARE_EF7C851CF0AEC8782522

// Convenient borrowed-state interface

namespace shareable {
class Speed {
  public:
    static constexpr const char *kName = "Speed";
    static constexpr const char *kDescription = "";
    explicit Speed(std::uint8_t *image) : image_(image) {}
    // Speed. Config key: speed.
    NumberSetting &speed() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2f6338);
    }
    // On ground. Config key: require_ground.
    BooleanSetting &require_ground() const {
        return *reinterpret_cast<BooleanSetting *>(image_ + 0x2f6318);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_speed_ui(ui, layout, image_, &dependencies);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_speed_bound_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_speed_settings(&context, image_, &dependencies);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
