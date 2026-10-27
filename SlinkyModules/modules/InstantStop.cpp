// Instant Stop

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Instant_Stop.md

#include "../runtime/native/verified/module_surface.hpp"

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Instant_Stop/instant_stop.cpp
#include "../runtime/shared/OwnedNativeBindings.hpp"
#ifndef SLINKY_SHARE_E5249ED60B972E65F69D
#define SLINKY_SHARE_E5249ED60B972E65F69D
// BEGIN SOURCE modules/Instant_Stop/Settings.hpp
#include "../runtime/native/verified/module_list_settings.hpp"
#include "../runtime/native/verified/module_range_settings.hpp"
#include "../runtime/native/verified/module_settings.hpp"
#include <cstdint>
namespace reconstruction::Instant_Stop {
namespace Storage {
inline constexpr std::uint32_t nativeData_1547a8 = 0x1547a8;
inline constexpr std::uint32_t nativeData_1547b0 = 0x1547b0;
inline constexpr std::uint32_t nativeData_1547b4 = 0x1547b4;
inline constexpr std::uint32_t moduleDescriptor = 0x2f2a80;
inline constexpr std::uint32_t stoppingPhase = 0x3043d0;
} // namespace Storage
// Views alias the existing image storage. They do not initialize settings.
struct SettingsView {
    std::uint8_t *image;
};
} // namespace reconstruction::Instant_Stop
// END SOURCE modules/Instant_Stop/Settings.hpp

#endif // SLINKY_SHARE_E5249ED60B972E65F69D

#include <stdint.h>
#include <string.h>
namespace reconstruction::Instant_Stop {
namespace NativeEntry {
inline constexpr uint32_t addVector = 0x9400;
inline constexpr uint32_t clientOptions = 0x22cf0;
inline constexpr uint32_t entityRotation = 0x23170;
inline constexpr uint32_t entityVelocity = 0x23550;
inline constexpr uint32_t entitySprinting = 0x23690;
inline constexpr uint32_t entityOnGround = 0x23780;
inline constexpr uint32_t backwardKey = 0x250d0;
inline constexpr uint32_t forwardKey = 0x25120;
inline constexpr uint32_t leftKey = 0x25170;
inline constexpr uint32_t rightKey = 0x251c0;
inline constexpr uint32_t keyDown = 0x25430;
inline constexpr uint32_t setKeyDownRaw = 0x25460;
inline constexpr uint32_t physicalKeyWord = 0x25490;
} // namespace NativeEntry

/* The dependency boundary preserves the original call-site register/stack
   arguments.  Return values are raw RAX bits; callback-specific float returns
   are returned in the low 32 bits. */
struct instant_stop_helper {
    native_binding::Context &native;
    void *user;
    uint64_t (*unresolved)(void *, uint32_t, uint64_t, uint64_t, uint64_t, uint64_t, uint32_t,
                           uint32_t, uint32_t, uint32_t *);
    // Native R8 residue is an explicit register-context dependency, not a C++
    // RNG/geometry result.
    void (*recordR8AfterBoundCall)(void *, uint32_t, const uint64_t *, uint32_t *);
    uint64_t operator()(uint32_t rva, uint64_t a, uint64_t b, uint64_t c, uint64_t d, uint32_t x2,
                        uint32_t x3, uint32_t fifth, uint32_t *r8) const {
        const uint64_t g[4] = {a, b, c, d}, x[4] = {0, 0, x2, x3}, st[2] = {fifth, 0};
        native_binding::Value value;
        if (native_binding::resolveFrame(native, rva, g, x, st, value)) {
            recordR8AfterBoundCall(user, rva, g, r8);
            return value.bits;
        }
        return unresolved(user, rva, a, b, c, d, x2, x3, fifth, r8);
    }
};
static uint64_t call(instant_stop_helper h, uint32_t *helper_r8, uint32_t id, uint64_t a,
                     uint64_t b, uint64_t c, uint64_t d, uint32_t x2, uint32_t x3, uint32_t fifth) {
    return h(id, a, b, c, d, x2, x3, fifth, helper_r8);
}

static uint8_t low_al(uint64_t x) {
    return (uint8_t)x;
}
static float f32(uint32_t u) {
    float f;
    memcpy(&f, &u, 4);
    return f;
}
static uint32_t fbits(float f) {
    uint32_t u;
    memcpy(&u, &f, 4);
    return u;
}
static double f64(uint64_t u) {
    double d;
    memcpy(&d, &u, 8);
    return d;
}

static int unordered(double a, double b) {
    return a != a || b != b;
}
static int ucomi_gt(double a, double b) {
    return !unordered(a, b) && a > b;
}
static int ucomi_le(double a, double b) {
    return unordered(a, b) || a <= b;
}

/* This matches MINSD's operand rule: if either operand is NaN or they compare
   equal, the source (right-hand) operand wins. */
static double minsd(double dest, double src) {
    return unordered(dest, src) || dest == src ? src : (dest < src ? dest : src);
}

/* RVA 0x42650. image is a copy of the supplied image with writable data pages;
   known supplied helper bodies are bound through caller-owned native context.
 */
void correctStoppingInput(void *event, uint8_t *image, instant_stop_helper helper,
                          uint32_t *helper_r8) {
    uint8_t *evt = (uint8_t *)event;
    uint64_t *ctx = (uint64_t *)(uintptr_t)*(uint64_t *)(evt + 8);
    uint64_t game = ctx[0], meta = ctx[3];
    uint64_t bridge;
    uint64_t mode1, state2, state3, state4;
    uint32_t mode = 0;
    {
        if (!low_al(call(helper, helper_r8, 0x22e60, game, meta, 0, 0, 0, 0, 0)))
            goto store;
        game = ctx[0];
        meta = ctx[3];
        bridge = call(helper, helper_r8, NativeEntry::clientOptions, game, meta, 0, 0, 0, 0, 0);
        game = ctx[0];
        mode1 = call(helper, helper_r8, NativeEntry::backwardKey, game, bridge, 0, 0, 0, 0, 0);
        game = ctx[0];
        state2 = call(helper, helper_r8, NativeEntry::forwardKey, game, bridge, 0, 0, 0, 0, 0);
        game = ctx[0];
        state3 = call(helper, helper_r8, NativeEntry::leftKey, game, bridge, 0, 0, 0, 0, 0);
        game = ctx[0];
        state4 = call(helper, helper_r8, NativeEntry::rightKey, game, bridge, 0, 0, 0, 0, 0);
        memcpy(&mode, image + Storage::stoppingPhase, 4);
        uint32_t active_mode = mode;
        mode = 0; /* R12D is the eventual value stored, initialized at entry. */
        game = ctx[0];
        if (active_mode == 2) {
            uint64_t captured_game = game;
            uint32_t value = (uint32_t)call(helper, helper_r8, NativeEntry::physicalKeyWord,
                                            captured_game, state2, 0, 0, 0, 0, 0);
            *helper_r8 = value;
            call(helper, helper_r8, NativeEntry::setKeyDownRaw, captured_game, state2, value, 0, 0,
                 0, 0);
            game = ctx[0];
            value = (uint32_t)call(helper, helper_r8, NativeEntry::physicalKeyWord, game, state3, 0,
                                   0, 0, 0, 0);
            *helper_r8 = value;
            call(helper, helper_r8, NativeEntry::setKeyDownRaw, game, state3, value, 0, 0, 0, 0);
            game = ctx[0];
            value = (uint32_t)call(helper, helper_r8, NativeEntry::physicalKeyWord, game, state4, 0,
                                   0, 0, 0, 0);
            *helper_r8 = value;
            call(helper, helper_r8, NativeEntry::setKeyDownRaw, game, state4, value, 0, 0, 0, 0);
            /* R12D starts at zero and the state-2 path never changes it. */
            mode = 0;
            goto store;
        }
        if (active_mode != 1) {
            if (!low_al(call(helper, helper_r8, NativeEntry::keyDown, game, mode1, 0, 0, 0, 0, 0)))
                return;
            mode = 1;
            goto store;
        }
        if (low_al(call(helper, helper_r8, NativeEntry::keyDown, game, mode1, 0, 0, 0, 0, 0)))
            return;
        game = ctx[0];
        uint64_t player = ctx[5];
        if (!low_al(
                call(helper, helper_r8, NativeEntry::entityOnGround, game, player, 0, 0, 0, 0, 0)))
            return;
        double start[3];
        game = ctx[0];
        player = ctx[5];
        call(helper, helper_r8, NativeEntry::entityVelocity, (uint64_t)(uintptr_t)start, game,
             player, 0, 0, 0, 0);
        game = ctx[0];
        player = ctx[5];
        uint64_t yaw =
            call(helper, helper_r8, NativeEntry::entityRotation, game, player, 0, 0, 0, 0, 0);
        game = ctx[0];
        player = ctx[5];
        float rate = f32((uint32_t)call(helper, helper_r8, 0x23b40, game, player, 0, 0, 0, 0, 0));
        game = ctx[0];
        player = ctx[5];
        if (low_al(call(helper, helper_r8, NativeEntry::entitySprinting, game, player, 0, 0, 0, 0,
                        0))) {
            double divisor = f64(*(uint64_t *)(image + Storage::nativeData_1547a8));
            rate = (float)((double)rate / divisor);
        }
        uint32_t global = (uint32_t)*(uint64_t *)(image + Storage::nativeData_1547b0);
        uint32_t third = (uint32_t)*(uint64_t *)(image + Storage::nativeData_1547b4);
        double current_min = 0.0;
        double third_distance = 0.0;
        double origin_distance = start[0] * start[0] + start[2] * start[2];
        uint32_t index = 999;
        for (unsigned candidate = 0; candidate < 3; candidate++) {
            uint32_t x3 = candidate == 0 ? global : (candidate == 1 ? 0 : third);
            double generated[3];
            call(helper, helper_r8, 0x29290, (uint64_t)(uintptr_t)generated, yaw, 0, 0, global, x3,
                 fbits(rate));
            double left_copy[3], right_copy[3], sum[3];
            memcpy(left_copy, start, sizeof(left_copy));
            memcpy(right_copy, generated, sizeof(right_copy));
            call(helper, helper_r8, NativeEntry::addVector, (uint64_t)(uintptr_t)sum,
                 (uint64_t)(uintptr_t)left_copy, (uint64_t)(uintptr_t)right_copy, 0, 0, 0, 0);
            /* The callback compares horizontal X/Z lanes; Y is carried through
               vector addition but does not contribute to this squared distance. */
            double distance = sum[0] * sum[0] + sum[2] * sum[2];
            if (candidate == 2)
                third_distance = distance;
            if (candidate == 0) {
                current_min = minsd(distance, origin_distance);
                index = ucomi_gt(origin_distance, distance) ? UINT32_MAX : 999;
            } else if (candidate == 1) {
                double old = current_min;
                current_min = minsd(distance, old);
                if (ucomi_gt(old, distance))
                    index = 0;
            } else {
                uint32_t prior = index;
                index = ucomi_le(current_min, distance) ? prior : 1;
            }
        }
        if (index == 999)
            goto store;
        /* The machine code writes only R8B here. The dependency contract supplies
           the controlled helper-produced upper bits through helper_r8. */
        uint32_t first_value = (*helper_r8 & 0xffffff00u) | 1u;
        *helper_r8 = first_value;
        game = ctx[0];
        call(helper, helper_r8, NativeEntry::setKeyDownRaw, game, state2, first_value, 0, 0, 0, 0);
        /* SETA from UCOMISD(current_min, third candidate distance). */
        game = ctx[0];
        *helper_r8 = (uint32_t)ucomi_gt(current_min, third_distance);
        call(helper, helper_r8, NativeEntry::setKeyDownRaw, game, state3, *helper_r8, 0, 0, 0, 0);
        uint32_t last_value = (*helper_r8 & 0xffffff00u) | (uint32_t)(index == UINT32_MAX);
        *helper_r8 = last_value;
        game = ctx[0];
        call(helper, helper_r8, NativeEntry::setKeyDownRaw, game, state4, last_value, 0, 0, 0, 0);
        mode = 2;
    }
store:
    memcpy(image + Storage::stoppingPhase, &mode, 4);
}

} // namespace reconstruction::Instant_Stop
// END SOURCE modules/Instant_Stop/instant_stop.cpp

// Convenient borrowed-state interface

namespace shareable {
class InstantStop {
  public:
    static constexpr const char *kName = "Instant Stop";
    static constexpr const char *kDescription =
        "Instantly stops moving when move keys are released.";
    explicit InstantStop(std::uint8_t *image) : image_(image) {}
    void correctStoppingInput(void *event,
                              ::reconstruction::Instant_Stop::instant_stop_helper helper,
                              uint32_t *helper_r8) {
        ::reconstruction::Instant_Stop::correctStoppingInput(event, image_, helper, helper_r8);
    }

  private:
    std::uint8_t *image_;
};
} // namespace shareable
