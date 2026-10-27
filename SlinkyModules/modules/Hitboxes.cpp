// Hitboxes

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Hitboxes.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Hitboxes.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Hitboxes: lib_win settings 0x34020.
// UI 0x33fe0.
static constexpr UiStep ui_steps_Surface_Hitboxes[] = {
    {UiControl::section, "Main", 0},
    {UiControl::number, nullptr, 0x2eceb8},
};
static constexpr SettingsStep settings_steps_Surface_Hitboxes[] = {
    {SettingsControl::number, "expand", 0x2eceb8},
};
static constexpr ModuleSurface surface_Surface_Hitboxes{
    ui_steps_Surface_Hitboxes, std::size(ui_steps_Surface_Hitboxes),
    settings_steps_Surface_Hitboxes, std::size(settings_steps_Surface_Hitboxes)};

extern "C" __declspec(dllexport) void
recovered_hitboxes_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                      const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_Hitboxes, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_hitboxes_settings(SettingsContext *context, std::uint8_t *image,
                            const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Hitboxes, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_Hitboxes.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Hitboxes/Hitboxes.cpp
#include "../runtime/native/verified/event_callbacks.hpp"
#include <cstring>

// lib_win RVA 0x33fc0: event 8 callback. expand is the module's stored setting.
extern "C" __declspec(dllexport) void recovered_hitboxes(std::uint8_t *event, float expand) {
    const double value = static_cast<double>(expand);
    event[0x10] = 1;
    std::memcpy(event + 0x20, &value, sizeof(value));
}
// END SOURCE modules/Hitboxes/Hitboxes.cpp

// BEGIN SOURCE modules/Hitboxes/Status.cpp
// Native RVA 0x34040 leaves RCX intact as the 32-byte destination.
// The decompiler incorrectly inferred the setting bits as that destination.
#ifndef SLINKY_SHARE_D2841F11326653C19EBF
#define SLINKY_SHARE_D2841F11326653C19EBF
// BEGIN SOURCE modules/Hitboxes/Status.hpp
#include <cstdint>
namespace reconstruction::hitboxes {
using StatusEndpoint = std::uint64_t (*)(std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t,
                                         std::uint64_t);
void writeStatus(char *, const std::uint8_t *stateImage, StatusEndpoint);
} // namespace reconstruction::hitboxes
// END SOURCE modules/Hitboxes/Status.hpp

#endif // SLINKY_SHARE_D2841F11326653C19EBF

#include "../runtime/native/verified/module_settings.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>
void reconstruction::hitboxes::writeStatus(char *destination, const std::uint8_t *stateImage,
                                           StatusEndpoint invoke) {
    float expand;
    std::memcpy(&expand, stateImage + 0x2eceb8 + offsetof(NumberSetting, current), 4);
    const auto asDouble = _mm_cvtsd_f64(_mm_cvtss_sd(_mm_setzero_pd(), _mm_set_ss(expand)));
    invoke(0xab710, reinterpret_cast<std::uintptr_t>(destination), 32,
           reinterpret_cast<std::uintptr_t>(stateImage + 0x151c03),
           std::bit_cast<std::uint64_t>(asDouble));
}
// END SOURCE modules/Hitboxes/Status.cpp

#ifndef SLINKY_SHARE_8ACAEA8261E564E7AD19
#define SLINKY_SHARE_8ACAEA8261E564E7AD19
// BEGIN SOURCE modules/Hitboxes/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
#include "../runtime/native/verified/event_callbacks.hpp"
#include "../runtime/native/verified/access_events.hpp"
// END SOURCE modules/Hitboxes/Api.hpp

#endif // SLINKY_SHARE_8ACAEA8261E564E7AD19

// Convenient borrowed-state interface

namespace shareable {
class Hitboxes {
  public:
    static constexpr const char *kName = "Hitboxes";
    static constexpr const char *kDescription = "Expands hitboxes of other players.";
    explicit Hitboxes(std::uint8_t *image) : image_(image) {}
    // Expand. Config key: expand.
    NumberSetting &expand() const {
        return *reinterpret_cast<NumberSetting *>(image_ + 0x2eceb8);
    }
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_hitboxes_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_hitboxes_settings(&context, image_, &dependencies);
    }
    static void hitboxes(std::uint8_t *event, float expand) {
        ::recovered_hitboxes(event, expand);
    }
    static void writeStatus(char *destination, const std::uint8_t *stateImage,
                            ::reconstruction::hitboxes::StatusEndpoint invoke) {
        ::reconstruction::hitboxes::writeStatus(destination, stateImage, invoke);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
