// No Hit Delay

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/No_Hit_Delay.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_No_Hit_Delay.cpp
#include "../runtime/native/verified/module_surface.hpp"

// No Hit Delay: lib_win settings 0x3e670.
// UI 0x3e630.
static constexpr UiStep ui_steps_Surface_No_Hit_Delay[] = {
    {UiControl::section, "In-game", 0},
    {UiControl::choice, nullptr, 0x2f0d90},
};
static constexpr SettingsStep settings_steps_Surface_No_Hit_Delay[] = {
    {SettingsControl::choice, "mode", 0x2f0d90},
};
static constexpr ModuleSurface surface_Surface_No_Hit_Delay{
    ui_steps_Surface_No_Hit_Delay, std::size(ui_steps_Surface_No_Hit_Delay),
    settings_steps_Surface_No_Hit_Delay, std::size(settings_steps_Surface_No_Hit_Delay)};

extern "C" __declspec(dllexport) void
recovered_no_hit_delay_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                          const SurfaceUiDependencies *dependencies) {
    render_module_surface(surface_Surface_No_Hit_Delay, ui, layout, image, *dependencies);
}
extern "C" __declspec(dllexport) void
recovered_no_hit_delay_settings(SettingsContext *context, std::uint8_t *image,
                                const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_No_Hit_Delay, context, image, *dependencies);
}
// END SOURCE native/verified/surfaces/Surface_No_Hit_Delay.cpp

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/No_Hit_Delay/No_Hit_Delay.cpp
#include "../runtime/native/verified/access_events.hpp"

// lib_win RVA 0x3e590: event 14 callback.
extern "C" __declspec(dllexport) void
recovered_no_hit_delay_3e590(void *event, AccessGlobals *globals, const AccessDependencies *deps) {
    if (static_cast<std::uint8_t *>(event)[0x10] != 1)
        return;
    auto *payload = reinterpret_cast<std::uint64_t *>(access_word(event, 8));
    const auto header =
        access_word(reinterpret_cast<const void *>(static_cast<std::uintptr_t>(payload[0])), 0);
    if (*reinterpret_cast<std::int32_t *>(static_cast<std::uintptr_t>(header)) == 0)
        return;
    const auto count =
        static_cast<std::int32_t>(access_call(deps, 0x22e90, payload[0], payload[3]));
    if (count <= 0)
        return;

    if (globals->state_3e590 == 1) {
        const auto token = access_call(deps, 0x22e10, payload[0], payload[3]);
        if (token != 0 &&
            static_cast<std::int32_t>(access_call(deps, 0x24b50, payload[0], token)) != 0) {
            access_call(deps, 0x22eb0, payload[0], payload[3]);
            return;
        }
    } else {
        access_call(deps, 0x22eb0, payload[0], payload[3]);
        return;
    }
    if (static_cast<std::uint8_t>(access_call(deps, 0x23f90, payload[0], payload[5])) == 0)
        access_call(deps, 0x23bb0, payload[0], payload[5]);
}
// END SOURCE modules/No_Hit_Delay/No_Hit_Delay.cpp

// BEGIN SOURCE modules/No_Hit_Delay/Status.cpp
// Native RVA 0x3e690. Unbounded DWORD option index and output capacity are retained.
#ifndef SLINKY_SHARE_E569C3D0B766448A5461
#define SLINKY_SHARE_E569C3D0B766448A5461
// BEGIN SOURCE modules/No_Hit_Delay/Status.hpp
#include <cstdint>
namespace reconstruction::no_hit_delay {
using StatusEndpoint = std::uint64_t (*)(std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t,
                                         std::uint64_t);
void writeStatus(char *, const std::uint8_t *stateImage, StatusEndpoint);
} // namespace reconstruction::no_hit_delay
// END SOURCE modules/No_Hit_Delay/Status.hpp

#endif // SLINKY_SHARE_E569C3D0B766448A5461

#include "../runtime/native/verified/module_settings.hpp"
#include <cstring>
void reconstruction::no_hit_delay::writeStatus(char *destination, const std::uint8_t *stateImage,
                                               StatusEndpoint invoke) {
    std::uint32_t mode;
    std::uint64_t option;
    std::memcpy(&mode, stateImage + 0x2f0d90 + offsetof(ChoiceSetting, current), 4);
    std::memcpy(&option, stateImage + 0x2f0d80 + std::uint64_t(mode) * 8, 8);
    invoke(0xab710, reinterpret_cast<std::uintptr_t>(destination), 32,
           reinterpret_cast<std::uintptr_t>(stateImage + 0x153eed), option);
}
// END SOURCE modules/No_Hit_Delay/Status.cpp

#ifndef SLINKY_SHARE_6784C40846F405349B71
#define SLINKY_SHARE_6784C40846F405349B71
// BEGIN SOURCE modules/No_Hit_Delay/Api.hpp
// Reuse the exact recovered ABI records and function declarations.
#include "../runtime/native/verified/event_callbacks.hpp"
#include "../runtime/native/verified/access_events.hpp"
// END SOURCE modules/No_Hit_Delay/Api.hpp

#endif // SLINKY_SHARE_6784C40846F405349B71

// Convenient borrowed-state interface

namespace shareable {
class NoHitDelay {
  public:
    static constexpr const char *kName = "No Hit Delay";
    static constexpr const char *kDescription = "Removes 1.8 swing delay.";
    explicit NoHitDelay(std::uint8_t *image) : image_(image) {}
    // Mode. Config key: mode.
    ChoiceSetting &mode() const {
        return *reinterpret_cast<ChoiceSetting *>(image_ + 0x2f0d90);
    }
    // Option labels observed in the captured metadata.
    enum class ModeMode : std::uint32_t { Regular = 0, Legit = 1 };
    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const SurfaceUiDependencies &dependencies) {
        recovered_no_hit_delay_ui(ui, layout, image_, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_no_hit_delay_settings(&context, image_, &dependencies);
    }
    static void native3e590(void *event, AccessGlobals *globals, const AccessDependencies *deps) {
        ::recovered_no_hit_delay_3e590(event, globals, deps);
    }
    static void writeStatus(char *destination, const std::uint8_t *stateImage,
                            ::reconstruction::no_hit_delay::StatusEndpoint invoke) {
        ::reconstruction::no_hit_delay::writeStatus(destination, stateImage, invoke);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
