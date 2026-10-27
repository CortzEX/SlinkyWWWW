// Aim Assist

// Settings, callbacks and recovered module-local behavior in one file.

// Shared numeric/JNI/UI/config support is in ../runtime.

// State is borrowed from the supplied image. No startup defaults are invented.

// Recovery limits: ../audits/modules/Aim_Assist.md

#include "../runtime/native/verified/module_surface.hpp"

// UI and configuration

// BEGIN SOURCE native/verified/surfaces/Surface_Aim_Assist.cpp
#include "../runtime/native/verified/module_surface.hpp"

// Aim Assist: lib_win settings 0x2bd00.
static constexpr SettingsStep settings_steps_Surface_Aim_Assist[] = {
    {SettingsControl::choice, "mode", 0x2e8ff0},
    {SettingsControl::number, "hor_speed", 0x2e8f20},
    {SettingsControl::number, "ver_speed", 0x2e8f58},
    {SettingsControl::boolean, "lock_on_vertical", 0x2e8f90},
    {SettingsControl::boolean, "silent_move_correct", 0x2e9050},
    {SettingsControl::boolean, "silent_ignore_manual_aim", 0x2e9030},
    {SettingsControl::number, "predict", 0x2e9190},
    {SettingsControl::number, "aim_randomization", 0x2e9238},
    {SettingsControl::number, "hor_hitbox_correct", 0x2e91c8},
    {SettingsControl::number, "ver_hitbox_correct", 0x2e9200},
    {SettingsControl::choice, "mode_target", 0x2e9150},
    {SettingsControl::choice, "sort_by", 0x2e92f0},
    {SettingsControl::boolean, "allow_exceed_fov", 0x2e9290},
    {SettingsControl::range, "range", 0x2e9070},
    {SettingsControl::range, "fov", 0x2e8ed0},
    {SettingsControl::boolean, "require_sprint", 0x2e90c0},
    {SettingsControl::boolean, "require_mouse_pressed", 0x2e90e0},
    {SettingsControl::boolean, "require_mouse_moved", 0x2e8fb0},
    {SettingsControl::boolean, "disable_on_block_break", 0x2e9100},
    {SettingsControl::boolean, "require_weapon", 0x2e9120},
    {SettingsControl::boolean, "ignore_invis", 0x2e9270},
    {SettingsControl::boolean, "require_line_of_sight", 0x2e92b0},
};
static constexpr ModuleSurface surface_Surface_Aim_Assist{
    nullptr, 0, settings_steps_Surface_Aim_Assist, std::size(settings_steps_Surface_Aim_Assist)};

extern "C" __declspec(dllexport) void
recovered_aim_assist_settings(SettingsContext *context, std::uint8_t *image,
                              const SurfaceSettingsDependencies *dependencies) {
    apply_module_settings(surface_Surface_Aim_Assist, context, image, *dependencies);
}

// Aim Assist: lib_win runtime UI 0x2bae0.
extern "C" __declspec(dllexport) void
recovered_aim_assist_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                        const SurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Aim");
    dependencies->choice(layout, ui, image + 0x2e8ff0);
    const auto mode = read_surface_value<std::uint32_t>(image, 0x2e9020);
    if (mode == 2) {
        dependencies->checkbox(layout, ui, image + 0x2e8f90);
    } else {
        if (mode == 3) {
            dependencies->checkbox(layout, ui, image + 0x2e9050);
            dependencies->checkbox(layout, ui, image + 0x2e9030);
        }
        dependencies->number(layout, ui, image + 0x2e8f20);
        dependencies->number(layout, ui, image + 0x2e8f58);
    }
    dependencies->number(layout, ui, image + 0x2e9190);
    dependencies->number(layout, ui, image + 0x2e9238);
    dependencies->section(ui, layout, "Multi-point");
    dependencies->number(layout, ui, image + 0x2e91c8);
    dependencies->number(layout, ui, image + 0x2e9200);
    dependencies->section(ui, layout, "Target");
    dependencies->choice(layout, ui, image + 0x2e9150);
    const auto target_mode = read_surface_value<std::uint32_t>(image, 0x2e9180);
    if (target_mode == 1) {
        dependencies->choice(layout, ui, image + 0x2e92f0);
    } else if (target_mode == 0) {
        dependencies->checkbox(layout, ui, image + 0x2e9290);
    }
    dependencies->range(layout, ui, image + 0x2e9070);
    dependencies->range(layout, ui, image + 0x2e8ed0);
    dependencies->section(ui, layout, "Conditions");
    if (read_surface_value<std::uint32_t>(image, 0x2e9020) != 3) {
        dependencies->checkbox(layout, ui, image + 0x2e90c0);
    }
    dependencies->checkbox(layout, ui, image + 0x2e90e0);
    dependencies->checkbox(layout, ui, image + 0x2e8fb0);
    dependencies->checkbox(layout, ui, image + 0x2e9100);
    dependencies->checkbox(layout, ui, image + 0x2e9120);
    dependencies->checkbox(layout, ui, image + 0x2e9270);
    dependencies->checkbox(layout, ui, image + 0x2e92b0);
}
// END SOURCE native/verified/surfaces/Surface_Aim_Assist.cpp

// BEGIN SOURCE shared/BoundSurfaces.cpp@Aim_Assist
// Same native ordering as reconstruction/native/verified/surfaces/Surface_Aim_Assist.cpp
extern "C" __declspec(dllexport) void
recovered_aim_assist_bound_ui(std::uint64_t ui, std::uint64_t layout, std::uint8_t *image,
                              const BoundSurfaceUiDependencies *dependencies) {
    dependencies->section(ui, layout, "Aim");
    dependencies->choice(layout, ui, image + 0x2e8ff0);
    const auto mode = read_surface_value<std::uint32_t>(image, 0x2e9020);
    if (mode == 2) {
        dependencies->checkbox(layout, ui, image + 0x2e8f90);
    } else {
        if (mode == 3) {
            dependencies->checkbox(layout, ui, image + 0x2e9050);
            dependencies->checkbox(layout, ui, image + 0x2e9030);
        }
        dependencies->number(layout, ui, image + 0x2e8f20);
        dependencies->number(layout, ui, image + 0x2e8f58);
    }
    dependencies->number(layout, ui, image + 0x2e9190);
    dependencies->number(layout, ui, image + 0x2e9238);
    dependencies->section(ui, layout, "Multi-point");
    dependencies->number(layout, ui, image + 0x2e91c8);
    dependencies->number(layout, ui, image + 0x2e9200);
    dependencies->section(ui, layout, "Target");
    dependencies->choice(layout, ui, image + 0x2e9150);
    const auto target_mode = read_surface_value<std::uint32_t>(image, 0x2e9180);
    if (target_mode == 1) {
        dependencies->choice(layout, ui, image + 0x2e92f0);
    } else if (target_mode == 0) {
        dependencies->checkbox(layout, ui, image + 0x2e9290);
    }
    dependencies->range(layout, ui, image + 0x2e9070);
    dependencies->range(layout, ui, image + 0x2e8ed0);
    dependencies->section(ui, layout, "Conditions");
    if (read_surface_value<std::uint32_t>(image, 0x2e9020) != 3) {
        dependencies->checkbox(layout, ui, image + 0x2e90c0);
    }
    dependencies->checkbox(layout, ui, image + 0x2e90e0);
    dependencies->checkbox(layout, ui, image + 0x2e8fb0);
    dependencies->checkbox(layout, ui, image + 0x2e9100);
    dependencies->checkbox(layout, ui, image + 0x2e9120);
    dependencies->checkbox(layout, ui, image + 0x2e9270);
    dependencies->checkbox(layout, ui, image + 0x2e92b0);
}
// END SOURCE shared/BoundSurfaces.cpp@Aim_Assist

// Runtime behavior and native ABI entry points

// BEGIN SOURCE modules/Aim_Assist/AimAssist.cpp
#ifndef SLINKY_SHARE_D147A9003FE251FCC237
#define SLINKY_SHARE_D147A9003FE251FCC237
// BEGIN SOURCE modules/Aim_Assist/AimAssist.hpp
#include <cfloat>
#include <climits>
#ifndef SLINKY_SHARE_76A3E3618FC00C146812
#define SLINKY_SHARE_76A3E3618FC00C146812
// BEGIN SOURCE modules/Aim_Assist/Support.hpp
#include <cstdint>
#include <cstring>
#include <emmintrin.h>
#include "../runtime/native/verified/module_game_access.hpp"
#include "../runtime/native/verified/module_random_policy.hpp"
#include "../runtime/native/verified/module_float_math.hpp"
#include "../runtime/native/verified/module_float_distance.hpp"
#include "../runtime/native/verified/module_format.hpp"
#include "../runtime/native/verified/module_surface.hpp"
#include "../runtime/native/verified/Weapons.hpp"
#include "../runtime/shared/Geometry.hpp"

namespace aim_assist {
using ObjectRef = void *;
using EntityRef = void *;
struct Vec3d {
    double x, y, z;
};
struct Rotation {
    float yaw, pitch;
};
struct AABB {
    double minX, minY, minZ, maxX, maxY, maxZ;
};
struct Frame {
    GameAccessBridge *jni;
    std::uint64_t reserved[2];
    ObjectRef minecraft, world;
    EntityRef player;
    std::uint8_t *input;
    void *targetRecord;
    std::uint8_t focusAllowed;
};
struct WorldUpdateEvent {
    std::uint64_t kind;
    Frame *frame;
};
struct RotationFrameEvent {
    std::uint64_t kind;
    Frame *frame;
    float timerRenderPartialTicks;
    std::uint32_t reserved;
    double elapsedSeconds;
};
struct StateChangedEvent {
    std::uint64_t kind;
    Frame *frame;
    const void *descriptor;
    std::uint8_t enabled;
};
struct MovementEvent {
    std::uint64_t kind;
    std::uint8_t active, remapMovement;
};
static_assert(offsetof(Frame, focusAllowed) == 0x40);
static_assert(offsetof(RotationFrameEvent, elapsedSeconds) == 0x18);
static_assert(offsetof(StateChangedEvent, enabled) == 0x18);
static_assert(sizeof(Rotation) == 8 && sizeof(Vec3d) == 24 && sizeof(AABB) == 48);
struct BoolValue {
    std::uint8_t &value;
};
struct FloatValue {
    float &value;
};
struct RangeValue {
    float &low, &high;
};
template <class E> struct ChoiceValue {
    E &value;
};
template <class T> T &at(std::uint8_t *image, std::uint32_t rva) {
    return *reinterpret_cast<T *>(image + rva);
}
template <class T> T bits(std::uint64_t value) {
    T result;
    std::memcpy(&result, &value, sizeof result);
    return result;
}
inline std::uint64_t packed(Rotation value) {
    std::uint64_t result;
    std::memcpy(&result, &value, 8);
    return result;
}

struct Runtime;
struct SmoothedRandom {
    Runtime *runtime;
    SmoothRandomState *state;
    float sample(float low, float high, double duration) const;
    template <class Draw> float sampleTime(float low, float high, double duration, Draw) const {
        return sample(low, high, duration);
    }
};
// All storage and constants are supplied by the caller. No capture values are
// installed as defaults. angleEndpoint retains the old explicit provider ABI;
// angularRotation uses the canonical borrowed decoded-cell direction service.
struct Runtime {
    std::uint8_t *image;
    RandomState *random;
    const RandomConstants *randomConstants;
    const RandomPolicyConstants *randomPolicyConstants;
    const double *clock;
    const AngleWrapConstants *angleWrapConstants;
    const FloatDistanceConstants *distanceConstants;
    const std::uint8_t *noisePermutation;
    const float *noiseConstants; // -1, 6, -15, 10 at observed RVA 0x2b81c0
    std::uint32_t noiseSignMask;
    float noiseScale; // observed 0x2b81e0; caller supplies original constant
    double (*angleEndpoint)(double, double);
    FormatState *format;
    const char *const *statusLabels; // 0x2e8fd0, separate from setting options
    WeaponCache *weaponCache;
    const WeaponSettings *weaponSettings;
    const ItemPolicyTable *weaponItems;
    const WeaponDependencies *weaponDependencies;
    // Borrowed encoded 0x13CFD0 cell for partial-image TimerRange composition.
    const std::uint8_t *numericPairEncodedCell_13cfd0 = nullptr;
    const std::uint8_t *numericDirectionEncodedCell_13cfb0 = nullptr;

    float random01() const;
    std::uint8_t chanceHalf() const;
    float wrap(float value) const;
    float magnitude(Rotation value) const;
    float noise1d(float value) const;
    bool isWeapon(GameAccessBridge *, EntityRef) const;
    bool storedRotationValid() const {
        return image[0x2f7b90] != 0;
    }
    Rotation storedRotation() const {
        return bits<Rotation>(at<std::uint64_t>(image, 0x2f7b70));
    }
    Rotation accumulatedRotationDelta() const {
        return bits<Rotation>(at<std::uint64_t>(image, 0x2f7b58));
    }
    Rotation manualAimDelta() const {
        return bits<Rotation>(at<std::uint64_t>(image, 0x2f7c18));
    }
    void clearManualAimDelta() const {
        at<std::uint64_t>(image, 0x2f7c18) = 0;
    }
    bool claimRotationPriority(std::uint32_t priority) const;
    void addRotationDelta(Rotation) const;
};
EntityRef currentTarget(const std::uint8_t *image);                      // native0x2b1c0
void accumulateManualAim(std::uint8_t *image, Rotation);                 // native0x2b1d0
Rotation angularRotation(const Runtime &, const Vec3d &, const Vec3d &); // native 0x9f80
namespace native {
inline float roundedAdd(float a, float b) {
    return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
inline float roundedSub(float a, float b) {
    return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
inline float roundedMul(float a, float b) {
    return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
inline float roundedDiv(float a, float b) {
    return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
inline float maxFloatSse(float a, float b) {
    return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
inline float minFloatSse(float a, float b) {
    return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a), _mm_set_ss(b)));
}
inline double roundedAddDouble(double a, double b) {
    return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
inline double roundedSubDouble(double a, double b) {
    return _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
inline double roundedMulDouble(double a, double b) {
    return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
inline double roundedDivDouble(double a, double b) {
    return _mm_cvtsd_f64(_mm_div_sd(_mm_set_sd(a), _mm_set_sd(b)));
}
inline double sqrtDouble(double value) {
    return _mm_cvtsd_f64(_mm_sqrt_sd(_mm_setzero_pd(), _mm_set_sd(value)));
}
inline float clampFloat(float low, float high, float value) {
    return recovered_float_clamp_a1f0(low, high, value);
}
inline double clampBoxCoordinate(double value, double low, double high) {
    const double limited = _mm_cvtsd_f64(_mm_min_sd(_mm_set_sd(high), _mm_set_sd(value)));
    return value < low ? low : limited;
}
inline Vec3d interpolate3(const Vec3d &from, const Vec3d &to, double amount) {
    Vec3d result;
    recovered_vector_lerp_9460(&result.x, &from.x, &to.x, amount);
    return result;
}
inline double distance3(const Vec3d &a, const Vec3d &b) {
    return recovered_vector_distance_94f0(&a.x, &b.x);
}
inline double lerpDouble(double a, double b, double amount) {
    return recovered_scalar_lerp_a2d0(a, b, amount);
}
} // namespace native
namespace mc {
bool entityIsDead(GameAccessBridge *, EntityRef);
bool entitySleeping(GameAccessBridge *, EntityRef);
bool entityInvisibleToPlayer(GameAccessBridge *, EntityRef, EntityRef);
std::uint8_t entityRelationshipFlags(GameAccessBridge *, EntityRef);
Vec3d entityPosition(GameAccessBridge *, EntityRef);
Vec3d entityPreviousPosition(GameAccessBridge *, EntityRef);
Vec3d entityOtherPlayerServerPosition(GameAccessBridge *, EntityRef);
Rotation entityRotation(GameAccessBridge *, EntityRef);
ObjectRef entityBoundingBoxObject(GameAccessBridge *, EntityRef);
AABB axisAlignedBBValues(GameAccessBridge *, ObjectRef);
float entityHealthOrTwenty(GameAccessBridge *, EntityRef);
int entityHurtTime(GameAccessBridge *, EntityRef);
int entityNumericId(GameAccessBridge *, EntityRef);
bool entityIsSprinting(GameAccessBridge *, EntityRef);
bool positionModeIsZero(GameAccessBridge *);
ObjectRef worldPlayerEntityList(GameAccessBridge *, ObjectRef);
int javaListSize(GameAccessBridge *, ObjectRef);
EntityRef javaListElement(GameAccessBridge *, ObjectRef, int);
bool sameJavaObject(GameAccessBridge *, ObjectRef, ObjectRef);
ObjectRef retainGlobalReference(GameAccessBridge *, ObjectRef);
void releaseGlobalReference(GameAccessBridge *, ObjectRef);
bool clearWorldRayBetween(GameAccessBridge *, ObjectRef, const Vec3d &, const Vec3d &);
ObjectRef minecraftObjectMouseOver(GameAccessBridge *, ObjectRef);
int movingObjectHitType(GameAccessBridge *, ObjectRef);
} // namespace mc
bool attackInputDown(const Frame &);
} // namespace aim_assist
// END SOURCE modules/Aim_Assist/Support.hpp

#endif // SLINKY_SHARE_76A3E3618FC00C146812

extern "C" void recovered_aim_assist_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *,
                                              const BoundSurfaceUiDependencies *);
extern "C" void recovered_aim_assist_settings(SettingsContext *, std::uint8_t *,
                                              const SurfaceSettingsDependencies *);

// Semantic benchmark port, checked against raw evidence and the supplied capture.
// All native state is caller-owned and bound by RVA. See the module report.
namespace aim_assist {
class AimAssist {
  public:
    static constexpr const char *kName = "Aim Assist";
    static constexpr const char *kDescription = "Pulls your crosshair towards other players.";

    enum class Mode : int {
        Regular = 0,
        Linear = 1,
        LockOn = 2,
        Silent = 3,
    };

    enum class TargetMode : int {
        Single = 0,
        Switch = 1,
    };

    enum class SortBy : int {
        Distance = 0,
        Health = 1,
        HurtTime = 2,
        AimAngle = 3,
    };

    Runtime &runtime;
    RangeValue fov;                     // current storage RVA 0x2e8f10
    FloatValue horizontalSpeed;         // current storage RVA 0x2e8f50
    FloatValue verticalSpeed;           // current storage RVA 0x2e8f88
    BoolValue lockOnVertical;           // current storage RVA 0x2e8fa8
    BoolValue requireMouseMoved;        // current storage RVA 0x2e8fc8
    ChoiceValue<Mode> mode;             // current storage RVA 0x2e9020
    BoolValue silentIgnoreManualAim;    // current storage RVA 0x2e9048
    BoolValue silentMoveCorrect;        // current storage RVA 0x2e9068
    BoolValue requireSprint;            // current storage RVA 0x2e90d8
    BoolValue requireMousePressed;      // current storage RVA 0x2e90f8
    BoolValue disableOnBlockBreak;      // current storage RVA 0x2e9118
    BoolValue requireWeapon;            // current storage RVA 0x2e9138
    RangeValue range;                   // current storage RVA 0x2e90b0
    ChoiceValue<TargetMode> targetMode; // current storage RVA 0x2e9180
    FloatValue predict;                 // current storage RVA 0x2e91c0
    FloatValue horizontalMultipoint;    // current storage RVA 0x2e91f8
    FloatValue verticalMultipoint;      // current storage RVA 0x2e9230
    FloatValue randomization;           // current storage RVA 0x2e9268
    BoolValue ignoreInvisibles;         // current storage RVA 0x2e9288
    BoolValue allowExceedFov;           // current storage RVA 0x2e92a8
    BoolValue requireLineOfSight;       // current storage RVA 0x2e92c8
    ChoiceValue<SortBy> sortBy;         // current storage RVA 0x2e9320

    explicit AimAssist(Runtime &context)
        : runtime(context),
          fov{at<float>(context.image, 0x2e8f10), at<float>(context.image, 0x2e8f14)},
          horizontalSpeed{at<float>(context.image, 0x2e8f50)},
          verticalSpeed{at<float>(context.image, 0x2e8f88)},
          lockOnVertical{at<std::uint8_t>(context.image, 0x2e8fa8)},
          requireMouseMoved{at<std::uint8_t>(context.image, 0x2e8fc8)},
          mode{at<Mode>(context.image, 0x2e9020)},
          silentIgnoreManualAim{at<std::uint8_t>(context.image, 0x2e9048)},
          silentMoveCorrect{at<std::uint8_t>(context.image, 0x2e9068)},
          requireSprint{at<std::uint8_t>(context.image, 0x2e90d8)},
          requireMousePressed{at<std::uint8_t>(context.image, 0x2e90f8)},
          disableOnBlockBreak{at<std::uint8_t>(context.image, 0x2e9118)},
          requireWeapon{at<std::uint8_t>(context.image, 0x2e9138)},
          range{at<float>(context.image, 0x2e90b0), at<float>(context.image, 0x2e90b4)},
          targetMode{at<TargetMode>(context.image, 0x2e9180)},
          predict{at<float>(context.image, 0x2e91c0)},
          horizontalMultipoint{at<float>(context.image, 0x2e91f8)},
          verticalMultipoint{at<float>(context.image, 0x2e9230)},
          randomization{at<float>(context.image, 0x2e9268)},
          ignoreInvisibles{at<std::uint8_t>(context.image, 0x2e9288)},
          allowExceedFov{at<std::uint8_t>(context.image, 0x2e92a8)},
          requireLineOfSight{at<std::uint8_t>(context.image, 0x2e92c8)},
          sortBy{at<SortBy>(context.image, 0x2e9320)},
          currentTarget(at<EntityRef>(context.image, 0x2f7be0)),
          targetActive(at<std::uint8_t>(context.image, 0x2f7bd8)),
          silentInternalState(at<std::uint8_t>(context.image, 0x2f7c20)),
          previousAimPoint(at<Vec3d>(context.image, 0x2f7be8)),
          currentAimPoint(at<Vec3d>(context.image, 0x2f7c00)),
          mousePressedGraceTicks(at<int>(context.image, 0x2f7c78)),
          targetTieCounter(at<std::uint64_t>(context.image, 0x2f7c80)),
          pitchDamping{&context, &at<SmoothRandomState>(context.image, 0x2f7c28)},
          pitchNoise{&context, &at<SmoothRandomState>(context.image, 0x2f7c38)},
          horizontalFactor{&context, &at<SmoothRandomState>(context.image, 0x2f7c48)},
          verticalFactor{&context, &at<SmoothRandomState>(context.image, 0x2f7c58)},
          speedFactor{&context, &at<SmoothRandomState>(context.image, 0x2f7c68)} {}

    void renderSettings(std::uint64_t ui, std::uint64_t layout,
                        const BoundSurfaceUiDependencies &dependencies) {
        recovered_aim_assist_bound_ui(ui, layout, runtime.image, &dependencies);
    }
    void serializeConfig(SettingsContext &context,
                         const SurfaceSettingsDependencies &dependencies) {
        recovered_aim_assist_settings(&context, runtime.image, &dependencies);
    }
    void writeStatus(char *output) const {
        recovered_format(runtime.format, output, 0x20, "%s",
                         runtime.statusLabels[static_cast<int>(mode.value)]);
    }

    EntityRef &currentTarget;
    std::uint8_t &targetActive, &silentInternalState;
    Vec3d &previousAimPoint, &currentAimPoint;
    int &mousePressedGraceTicks;
    std::uint64_t &targetTieCounter;
    SmoothedRandom pitchDamping, pitchNoise, horizontalFactor, verticalFactor, speedFactor;

    // Callback 0x2B5B0 compares the event's +0x10 descriptor with Aim
    // Assist's own descriptor and the +0x18 enabled byte before cleanup.
    void onModuleStateChanged(StateChangedEvent &event) {
        if (event.descriptor != runtime.image + 0x2e8cc0 || event.enabled != 0)
            return;

        auto *jni = event.frame->jni;

        if (currentTarget)
            mc::releaseGlobalReference(jni, currentTarget);

        currentTarget = nullptr;
        targetActive = false;
    }

    // Kind-13 callback 0x2B610 writes the native event bytes at +8/+9.
    void onMovementCorrection(MovementEvent &event) {
        if (silentInternalState != 1)
            return;

        event.active = 1;
        if (silentMoveCorrect.value == 1)
            event.remapMovement = 1;
    }

    struct TargetScore {
        double distance;
        float health;
        int hurtTime;
        std::uint32_t tieBreak;
        float aimAngle;
    };

    struct CandidateResult {
        Vec3d aimPoint{};
        std::uint8_t aimEnabled = 0;
    };

    // Source-equivalent reconstruction of RVA 0x2C3B0.
    // The native helper consumes the same world-update frame as its caller.
    bool considerTarget(const Frame &frame, EntityRef candidate, const Vec3d &localEyePos,
                        const Rotation &currentView, bool currentlyLocked, TargetScore &best,
                        CandidateResult &result) {
        if (mc::entityIsDead(frame.jni, candidate))
            return false;

        // Native 0x240A0 reads the EntityPlayer sleeping field (+0x5B8).
        if (mc::entitySleeping(frame.jni, candidate))
            return false;

        if (ignoreInvisibles.value == 1 &&
            mc::entityInvisibleToPlayer(frame.jni, candidate, frame.player))
            return false;

        // The original calls a shared exclusion/filter helper with literal reason/type 7.
        if ((mc::entityRelationshipFlags(frame.jni, candidate) & 7U) != 0)
            return false;

        Vec3d position = mc::entityPosition(frame.jni, candidate);

        // 0x2C3B0 blends the client position toward the three
        // EntityOtherPlayerMP server-position fields before point selection.
        if (predict.value > 0.0f) {
            const Vec3d server = mc::entityOtherPlayerServerPosition(frame.jni, candidate);
            const double scale = static_cast<double>(predict.value);
            position = native::interpolate3(position, server, scale); // 0x2C3B0 -> 0x9460
        }

        // 0x2C3B0 expands the current bounding box by 0.1, clamps the
        // local eye into it, and tests range before constructing the aim point.
        const ObjectRef boxObject = mc::entityBoundingBoxObject(frame.jni, candidate);
        const AABB box = mc::axisAlignedBBValues(frame.jni, boxObject);
        AABB mutableBox = box, expanded;
        recovered_box_expand_9770(&expanded.minX, &mutableBox.minX, 0.1);
        Vec3d nearest;
        recovered_box_clamp_9880(&nearest.x, &expanded.minX, &localEyePos.x);
        const double distance = distanceBetween(localEyePos, nearest);
        // 0x2C5D2..0x2C5E2 samples the lower endpoint before the upper
        // distance rejection, multipoint/noise work and angle conversion.
        std::uint8_t aimEnabled = !(static_cast<double>(range.low) > distance);
        if (distance > best.distance) // 0x2C5E6 UCOMISD/JA, unordered passes
            return false;

        const Vec3d aimPoint =
            selectAimPoint(localEyePos, position, nearest, distance, horizontalMultipoint.value,
                           verticalMultipoint.value, randomization.value);

        const float angle = yawErrorTo(localEyePos, aimPoint, currentView);
        if (angle > best.aimAngle) { // initialized to fov.high
            if (!currentlyLocked)
                return false;
            aimEnabled = allowExceedFov.value;
        }

        const float health = mc::entityHealthOrTwenty(frame.jni, candidate);
        if (health > best.health)
            return false;

        const int hurtTime = mc::entityHurtTime(frame.jni, candidate);
        if (hurtTime > best.hurtTime)
            return false;

        if (requireLineOfSight.value == 1 &&
            !mc::clearWorldRayBetween(frame.jni, frame.world, localEyePos, aimPoint))
            return false;

        // In Single mode the validation succeeds without changing the active sort
        // threshold. Switch mode tightens whichever metric is selected.
        if (targetMode.value != TargetMode::Single) { // 0x2C92E: zero vs nonzero
            switch (sortBy.value) {
            case SortBy::Distance:
                best.distance = distance;
                break;
            case SortBy::Health:
                best.health = health;
                break;
            case SortBy::HurtTime: {
                // Exact hash mixer recovered from x86. It provides a deterministic-ish
                // tie break among candidates with equal hurtTime.
                uint32_t x = static_cast<uint32_t>(mc::entityNumericId(frame.jni, candidate));
                const std::uint64_t counter = targetTieCounter; // 0x2C989
                x += static_cast<uint32_t>(counter);
                x ^= x >> 16;
                x *= 0x045D9F3Bu;
                x ^= x >> 16;
                x *= 0x045D9F3Bu;
                x ^= x >> 16;
                targetTieCounter = counter + 1U; // 0x2C9BD..0x2C9C1

                if (hurtTime == best.hurtTime && x < best.tieBreak)
                    return false;

                best.hurtTime = hurtTime;
                best.tieBreak = x;
                break;
            }
            case SortBy::AimAngle:
                best.aimAngle = angle;
                break;
            }
        } else {
            // In Single mode the disassembly updates the angle threshold used by the
            // existing-target validation path.
            best.aimAngle = angle;
        }

        result.aimPoint = aimPoint;
        result.aimEnabled = aimEnabled;
        // The Single validation call at 0x2B9A3 passes the live global flag
        // as the output pointer. 0x2C9F7 writes it before the caller updates
        // either aim-point history; enumeration passes a local output instead.
        if (currentlyLocked)
            targetActive = aimEnabled;
        return true;
    }

    // Kind-18 callback 0x2B630 reads the +0x08 WorldUpdateFrame.
    void updateTarget(WorldUpdateEvent &event) {
        runtime.clearManualAimDelta(); // 0x2B64B

        const auto &frame = *event.frame;
        if (frame.focusAllowed != 1)
            return clearTarget(frame.jni);

        if (requireSprint.value == 1 && mode.value != Mode::Silent &&
            !mc::entityIsSprinting(frame.jni, frame.player)) {
            targetActive = false; // 0x2B684 -> 0x2B949 retains currentTarget
            return;
        }

        // 0x29080 selects byte +2 for key code -99, otherwise byte +1.
        const bool mouseActive = attackInputDown(frame);

        if (requireMousePressed.value == 1) {
            if (!mouseActive) {
                // 0x2B630 samples FUN_18000A460 at probability 0.5,
                // then stores the resulting bit plus one.
                mousePressedGraceTicks = runtime.chanceHalf() + 1;
                return clearTarget(frame.jni);
            }
            if (mousePressedGraceTicks != 0 &&
                static_cast<int>(mode.value) < static_cast<int>(Mode::LockOn)) {
                --mousePressedGraceTicks;
                return clearTarget(frame.jni);
            }
        }

        if ((disableOnBlockBreak.value & static_cast<std::uint8_t>(mouseActive)) == 1) {
            ObjectRef mouseOver = mc::minecraftObjectMouseOver(frame.jni, frame.minecraft);
            if (mouseOver && mc::movingObjectHitType(frame.jni, mouseOver) == 1) {
                targetActive = false; // 0x2B6F9 -> 0x2B949 retains currentTarget
                return;
            }
        }

        if (requireWeapon.value == 1 && !runtime.isWeapon(frame.jni, frame.player))
            return clearTarget(frame.jni);

        const Vec3d localEyePos = playerEyePosition(frame);
        const Rotation currentView = runtime.storedRotationValid()
                                         ? runtime.storedRotation()
                                         : mc::entityRotation(frame.jni, frame.player);

        TargetScore best{static_cast<double>(range.high), FLT_MAX, INT_MAX, 0, fov.high};

        CandidateResult selectedResult{};
        EntityRef selected = nullptr;

        // Single mode validates the old global reference before enumeration.
        if (targetMode.value == TargetMode::Single && currentTarget) {
            if (considerTarget(frame, currentTarget, localEyePos, currentView, true, best,
                               selectedResult)) {
                previousAimPoint = currentAimPoint;
                currentAimPoint = selectedResult.aimPoint;
                return;
            }
            clearTarget(frame.jni); // native releases the failed locked target now
        }

        if (!selected) {
            ObjectRef players = mc::worldPlayerEntityList(frame.jni, frame.world);
            int count = mc::javaListSize(frame.jni, players);
            if (count > 0) {
                std::uint32_t index = 0;
                do {
                    EntityRef candidate =
                        mc::javaListElement(frame.jni, players, static_cast<int>(index));
                    if (!mc::sameJavaObject(frame.jni, frame.player, candidate)) {
                        CandidateResult r{};
                        if (considerTarget(frame, candidate, localEyePos, currentView, false, best,
                                           r)) {
                            selected = candidate;
                            selectedResult = r;
                        }
                    }
                    index += 1U;
                    count = mc::javaListSize(frame.jni, players);
                } while (static_cast<std::int32_t>(index) < count);
            }
        }

        if (!selected)
            return clearTarget(frame.jni);

        const bool sameObject = mc::sameJavaObject(frame.jni, currentTarget, selected);
        previousAimPoint = sameObject ? currentAimPoint : selectedResult.aimPoint;
        currentAimPoint = selectedResult.aimPoint;
        targetActive = selectedResult.aimEnabled;
        if (currentTarget)
            mc::releaseGlobalReference(frame.jni, currentTarget);
        const EntityRef retained = mc::retainGlobalReference(frame.jni, selected);
        // 0x2BA94/0x2BA97 skips the global store on allocation failure.
        // Preserve this native failure behavior, including the old value
        // remaining after DeleteGlobalRef; do not invent a nulling store.
        if (retained)
            currentTarget = retained;
    }

    // Type-1 frame callback at 0x2B200. The target flag and the silent
    // rotation-restoration flag are separate native globals.
    void onRotationFrame(RotationFrameEvent &event) {
        const auto &frame = *event.frame;
        if (frame.focusAllowed != 1)
            return;

        if (!targetActive) {
            if (silentInternalState != 1)
                return;
            if (runtime.storedRotationValid() && runtime.claimRotationPriority(100)) {
                const Rotation current = currentRotationWithPending(frame);
                const Rotation stored = runtime.storedRotation();
                Rotation error = rotationDifference(stored, current);
                if (rotationMagnitude(error) < 10.0f)
                    silentInternalState = false;
                const float scale = static_cast<float>(event.elapsedSeconds); // 0x2B309
                applyAimStep(error, scale);
                return;
            }
            silentInternalState = false;
            return;
        }

        if (!runtime.claimRotationPriority(100))
            return;
        if (!silentInternalState && mode.value == Mode::Silent)
            silentInternalState = true;
        if (silentInternalState && !runtime.storedRotationValid())
            return;

        const float playerPartialTicks = event.timerRenderPartialTicks; // 0x2B34F
        const Vec3d previous = mc::entityPreviousPosition(frame.jni, frame.player);
        const Vec3d current = mc::entityPosition(frame.jni, frame.player);
        const Vec3d displacement{
            native::roundedSubDouble(current.x, previous.x),
            native::roundedSubDouble(current.y, previous.y),
            native::roundedSubDouble(current.z, previous.z)}; // 0x2B39F -> 0x93D0
        const double playerPartial = static_cast<double>(playerPartialTicks);
        const Vec3d scaled{
            native::roundedMulDouble(playerPartial, displacement.x),
            native::roundedMulDouble(playerPartial, displacement.y),
            native::roundedMulDouble(
                playerPartial,
                displacement.z)}; // 0x2B3C2 -> 0x9430, fraction in each destination lane
        Vec3d eye{native::roundedAddDouble(previous.x, scaled.x),
                  native::roundedAddDouble(previous.y, scaled.y),
                  native::roundedAddDouble(
                      scaled.z, previous.z)}; // 0x2B3E1 -> 0x9400: X/Y first+second, Z second+first
        if (!mc::positionModeIsZero(frame.jni))
            eye.y = native::roundedAddDouble(eye.y, 1.62);

        const double partial = static_cast<double>(event.timerRenderPartialTicks); // 0x2B429
        const Vec3d aimPoint =
            native::interpolate3(previousAimPoint, currentAimPoint, partial); // 0x9460
        const Rotation desired = rotationTo(eye, aimPoint);
        const Rotation currentWithPending = currentRotationWithPending(frame);
        const Rotation error = rotationDifference(desired, currentWithPending);

        if (mode.value == Mode::Silent && !silentIgnoreManualAim.value) {
            const Rotation stored = runtime.storedRotation();
            const Rotation restore = rotationDifference(stored, currentWithPending);
            // The PE calls 0x29FF0 again at 0x2B525 and computes/wraps
            // this difference before the restoration-length threshold.
            const Rotation storedForTarget = runtime.storedRotation();
            const Rotation targetFromStored = rotationDifference(desired, storedForTarget);
            if (rotationMagnitude(restore) < 10.0f &&
                rotationMagnitude(targetFromStored) < rotationMagnitude(error)) {
                runtime.addRotationDelta(restore);
                return;
            }
        }
        const float scale = static_cast<float>(event.elapsedSeconds); // 0x2B583
        applyAimStep(error, scale);
    }

    // Source-equivalent reconstruction of RVA 0x2BF40.
    void applyAimStep(Rotation error, float timeOrInputScale) {
        using namespace native;
        // FUN_18000A510 reads DAT_1802F7330 internally, refreshed by
        // 0xA360 from the frame callback 0x6F40.
        const auto drawUnit = [this] { return runtime.random01(); };

        // Inner FOV/dead-zone: the binary subtracts fov.low from the magnitude of both
        // signed errors, clamping back toward zero.
        const float deadZone = fov.low; // one load at 0x2BF98
        error.yaw = shrinkTowardZero(error.yaw, deadZone);
        error.pitch = error.pitch > 0.0f ? maxFloatSse(roundedSub(error.pitch, deadZone), 0.0f)
                                         : minFloatSse(roundedAdd(deadZone, error.pitch), 0.0f);

        Mode sampledMode = mode.value; // 0x2BFC2/0x2C099
        if (sampledMode != Mode::LockOn) {
            const float rnd = pitchDamping.sampleTime(40.0f, 120.0f, 5.0, drawUnit);
            const double slope = roundedDivDouble(-1.0, static_cast<double>(rnd));
            const double damped = roundedAddDouble(
                roundedMulDouble(slope, static_cast<double>(absoluteBits(error.yaw))), 1.0);
            const float magnitudeScale = maxFloatSse(static_cast<float>(damped), 0.0f);
            error.pitch = roundedMul(error.pitch, magnitudeScale);
            sampledMode = mode.value; // 0x2C037 rechecks after sampling/damping
        }

        if (sampledMode == Mode::LockOn) {
            if (!lockOnVertical.value)
                error.pitch = 0.0f;
        } else {

            float hSpeed = horizontalSpeed.value;
            float vSpeed = verticalSpeed.value;
            if (sampledMode == Mode::Silent) {      // same EAX value at 0x2C056
                hSpeed = maxFloatSse(5.0f, hSpeed); // 0x2C06C operand order
                if (5.0f > vSpeed)
                    vSpeed = 5.0f; // unordered retains vSpeed
            }
            const float hHalf = roundedMul(hSpeed, 0.5f);
            const float hSquared = roundedMul(hHalf, hHalf);
            const float hRnd = horizontalFactor.sampleTime(0.9f, 1.1f, 1.0, drawUnit);
            float yawFactor = roundedMul(hRnd, hSquared);
            const float vHalf = roundedMul(vSpeed, 0.5f);
            const float vSquared = roundedMul(vHalf, vHalf);
            const float vRnd = verticalFactor.sampleTime(0.9f, 1.1f, 1.0, drawUnit);
            float pitchFactor = roundedMul(vRnd, vSquared);
            const float globalRnd = speedFactor.sampleTime(0.95f, 1.05f, 60.0, drawUnit);

            if (mode.value == Mode::Linear) {
                yawFactor = roundedMul(yawFactor, 5.0f);
                yawFactor = roundedMul(yawFactor, globalRnd);
                const float yawStep = roundedMul(yawFactor, timeOrInputScale);
                error.yaw = clampFloat(-yawStep, yawStep, error.yaw);
                pitchFactor = roundedMul(pitchFactor, 5.0f);
                pitchFactor = roundedMul(pitchFactor, globalRnd);
                const float pitchStep = roundedMul(pitchFactor, timeOrInputScale);
                error.pitch = clampFloat(-pitchStep, pitchStep, error.pitch);
            } else {
                // 0x2C2CA..0x2C2F4: error multiplication precedes the two
                // packed-float scalar multipliers at 0x9E60. Each rounds.
                float rawYaw = roundedMul(yawFactor, error.yaw);
                float rawPitch = roundedMul(pitchFactor, error.pitch);
                rawYaw = roundedMul(rawYaw, globalRnd);
                rawPitch = roundedMul(rawPitch, globalRnd);
                rawYaw = roundedMul(rawYaw, timeOrInputScale);
                rawPitch = roundedMul(rawPitch, timeOrInputScale);
                // UCOMISS/CMOVBE and UCOMISS/CMOVA also accept an unordered
                // new result. A C++ <= test would incorrectly discard NaN.
                if (!(absoluteBits(rawYaw) > absoluteBits(error.yaw)))
                    error.yaw = rawYaw;
                if (!(absoluteBits(rawPitch) > absoluteBits(error.pitch)))
                    error.pitch = rawPitch;
            }

            if (mode.value != Mode::LockOn) { // 0x2C343 reloads the mode
                const float pitchNoiseBound = static_cast<float>(
                    roundedMulDouble(static_cast<double>(absoluteBits(error.yaw)), 0.1));
                const float noise =
                    pitchNoise.sampleTime(-pitchNoiseBound, pitchNoiseBound, 1.0, drawUnit);
                error.pitch = roundedAdd(error.pitch, noise);
            }
        }

        // This common stage is reached AFTER speed/clamp and noise, including
        // from Lock-on. Moving it before those stages changes the correction.
        if (requireMouseMoved.value == 1) {
            // 0x2C0C7..0x2C14C: unconditional yaw arithmetic, conditional
            // pitch arithmetic, paired-state clear, then yaw selection.
            const Rotation manualDelta = runtime.manualAimDelta();
            const float yawMagnitude = absoluteBits(error.yaw);
            const float pitchMagnitude = absoluteBits(error.pitch);
            const float manualYawMagnitude = absoluteBits(manualDelta.yaw);
            const float manualPitchMagnitude = absoluteBits(manualDelta.pitch);
            const bool adjustYaw = manualYawMagnitude < yawMagnitude && error.yaw != 0.0f;
            const float yawRatio = roundedDiv(manualYawMagnitude, yawMagnitude);
            const float scaledYaw = roundedMul(yawRatio, error.yaw);
            const bool adjustPitch = manualPitchMagnitude < pitchMagnitude && error.pitch != 0.0f;
            if (adjustPitch) {
                const float pitchRatio = roundedDiv(manualPitchMagnitude, pitchMagnitude);
                error.pitch = roundedMul(error.pitch, pitchRatio);
            }
            runtime.clearManualAimDelta(); // 0x2C13B
            if (adjustYaw)
                error.yaw = scaledYaw;
        }
        runtime.addRotationDelta(error);
    }

  private:
    Rotation rotationTo(const Vec3d &from, const Vec3d &to) {
        return angularRotation(runtime, from, to);
    }

    Rotation rotationDifference(Rotation target, Rotation current) {
        Rotation difference =
            bits<Rotation>(recovered_angle_subtract_9e20(packed(target), packed(current)));
        difference.yaw = runtime.wrap(difference.yaw);
        return difference;
    }

    Rotation currentRotationWithPending(const Frame &frame) {
        const Rotation current = mc::entityRotation(frame.jni, frame.player);
        const Rotation pending = runtime.accumulatedRotationDelta();
        return bits<Rotation>(recovered_angle_add_9de0(packed(current), packed(pending)));
    }

    float rotationMagnitude(Rotation rotation) {
        return runtime.magnitude(rotation); // 0x9F60
    }

    void clearTarget(GameAccessBridge *jni) {
        if (currentTarget)
            mc::releaseGlobalReference(jni, currentTarget);
        currentTarget = nullptr;
        targetActive = false;
    }

    static double distanceBetween(const Vec3d &a, const Vec3d &b) {
        return native::distance3(a, b); // 0x94F0
    }

    Vec3d selectAimPoint(const Vec3d &localEye, const Vec3d &predicted, const Vec3d &nearest,
                         double distance, float horizontalPct, float verticalPct, float randomPct) {
        using namespace native;
        const Vec3d targetEye{predicted.x, roundedAddDouble(predicted.y, 1.62), predicted.z};
        double x = targetEye.x;
        double z = targetEye.z;
        if (horizontalPct > 0.0f) {
            float fraction = horizontalPct;
            if (distance < 3.5)
                fraction = static_cast<float>(roundedMulDouble(static_cast<double>(horizontalPct),
                                                               roundedDivDouble(distance, 3.5)));
            const Vec3d horizontal = native::interpolate3(
                targetEye, nearest, static_cast<double>(fraction)); // 0x2C3B0 -> 0x9460
            x = horizontal.x;
            z = horizontal.z;
        }
        const double y =
            native::lerpDouble(targetEye.y, nearest.y, static_cast<double>(verticalPct));

        // 0x2C6C4..0x2C6EF: five ADDSD instructions, one MULSD, then
        // a single float conversion. Keep the sum and multiplication separate.
        double coordinateSum = roundedAddDouble(localEye.x, localEye.y);
        coordinateSum = roundedAddDouble(coordinateSum, localEye.z);
        coordinateSum = roundedAddDouble(coordinateSum, x);
        coordinateSum = roundedAddDouble(coordinateSum, y);
        coordinateSum = roundedAddDouble(coordinateSum, z);
        const float input = static_cast<float>(roundedMulDouble(coordinateSum, 0.1));
        const float inputY = roundedAdd(10000.0f, input);
        const float inputZ = roundedAdd(20000.0f, input);
        const float noiseX = runtime.noise1d(input);
        const float noiseY = runtime.noise1d(inputY);
        const double halfNoiseX = roundedMulDouble(static_cast<double>(noiseX), 0.5);
        const double halfNoiseY = roundedMulDouble(static_cast<double>(noiseY), 0.5);
        const float noiseZ = runtime.noise1d(inputZ);
        const double halfNoiseZ = roundedMulDouble(static_cast<double>(noiseZ), 0.5);
        float randomScale = randomPct;
        if (distance < 3.5) {
            const double closeRangeFactor =
                roundedAddDouble(roundedMulDouble(roundedDivDouble(distance, 3.5), 0.9), 0.1);
            randomScale = static_cast<float>(
                roundedMulDouble(static_cast<double>(randomPct), closeRangeFactor));
        }
        const double scale = static_cast<double>(randomScale);
        const Vec3d noise{roundedMulDouble(scale, halfNoiseX), roundedMulDouble(scale, halfNoiseY),
                          roundedMulDouble(scale, halfNoiseZ)}; // 0x9430 operand order
        return {roundedAddDouble(x, noise.x), roundedAddDouble(y, noise.y),
                roundedAddDouble(z, noise.z)};
    }

    float yawErrorTo(const Vec3d &from, const Vec3d &to, const Rotation &currentView) {
        // 0x2C3B0 invokes the full 0x9F80 yaw/pitch helper even though this
        // predicate subsequently consumes only its yaw lane.
        const float targetYaw = rotationTo(from, to).yaw;
        const float error = runtime.wrap(native::roundedSub(targetYaw, currentView.yaw));
        return absoluteBits(error);
    }
    static Vec3d playerEyePosition(const Frame &frame) {
        Vec3d position = mc::entityPosition(frame.jni, frame.player);
        if (!mc::positionModeIsZero(frame.jni))
            position.y = native::roundedAddDouble(position.y, 1.62);
        return position;
    }

    static float shrinkTowardZero(float v, float amount) {
        if (v > 0.0f)
            return native::maxFloatSse(native::roundedSub(v, amount), 0.0f);
        return native::minFloatSse(native::roundedAdd(v, amount), 0.0f);
    }

    static float absoluteBits(float value) {
        std::uint32_t bits{};
        std::memcpy(&bits, &value, sizeof bits);
        bits &= 0x7FFFFFFFU;
        std::memcpy(&value, &bits, sizeof value);
        return value;
    }
};

} // namespace aim_assist
// END SOURCE modules/Aim_Assist/AimAssist.hpp

#endif // SLINKY_SHARE_D147A9003FE251FCC237

extern "C" {
__declspec(dllexport) void semantic_aim_assist_update(aim_assist::AimAssist *module,
                                                      aim_assist::RotationFrameEvent *event) {
    module->onRotationFrame(*event);
}
__declspec(dllexport) void semantic_aim_assist_target(aim_assist::AimAssist *module,
                                                      aim_assist::WorldUpdateEvent *event) {
    module->updateTarget(*event);
}
__declspec(dllexport) void semantic_aim_assist_state(aim_assist::AimAssist *module,
                                                     aim_assist::StateChangedEvent *event) {
    module->onModuleStateChanged(*event);
}
__declspec(dllexport) void semantic_aim_assist_movement(aim_assist::AimAssist *module,
                                                        aim_assist::MovementEvent *event) {
    module->onMovementCorrection(*event);
}
}
// END SOURCE modules/Aim_Assist/AimAssist.cpp

// BEGIN SOURCE modules/Aim_Assist/Noise.cpp
namespace aim_assist {
// Observed native 0x97c70. Exact integer inputs decrement the converted index;
// UCOMISS/SETBE also decrements after an unordered comparison. This is retained.
float Runtime::noise1d(float input) const {
    using namespace native;
    const std::int32_t truncated = _mm_cvttss_si32(_mm_set_ss(input));
    const float truncatedFloat = _mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(), truncated));
    const std::uint32_t indexBits = static_cast<std::uint32_t>(truncated) -
                                    static_cast<std::uint32_t>(!(input > truncatedFloat));
    std::int32_t index;
    std::memcpy(&index, &indexBits, 4);
    const float converted = _mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(), index));
    const float phase = roundedSub(input, converted);
    const float cube = roundedMul(roundedMul(phase, phase), phase);
    const float polynomial = roundedAdd(
        roundedMul(roundedAdd(roundedMul(noiseConstants[1], phase), noiseConstants[2]), phase),
        noiseConstants[3]);
    const auto gradient = [&](std::uint8_t permutation) {
        float result = static_cast<float>((permutation & 7) + 1);
        std::uint32_t value;
        std::memcpy(&value, &result, 4);
        if (permutation & 8)
            value ^= noiseSignMask;
        std::memcpy(&result, &value, 4);
        return result;
    };
    const float left =
        roundedMul(gradient(noisePermutation[static_cast<std::uint8_t>(indexBits)]), phase);
    const float rightPhase = roundedAdd(noiseConstants[0], phase);
    const float right = roundedMul(
        rightPhase, gradient(noisePermutation[static_cast<std::uint8_t>(indexBits + 1)]));
    const float weight = roundedMul(cube, polynomial);
    return roundedMul(roundedAdd(roundedMul(weight, roundedSub(right, left)), left), noiseScale);
}
} // namespace aim_assist
extern "C" __declspec(dllexport) float probe_noise(float input, const std::uint8_t *permutation,
                                                   const float *polynomial, std::uint32_t signMask,
                                                   float scale) {
    aim_assist::Runtime context;
    context.noisePermutation = permutation;
    context.noiseConstants = polynomial;
    context.noiseSignMask = signMask;
    context.noiseScale = scale;
    return context.noise1d(input);
}
// END SOURCE modules/Aim_Assist/Noise.cpp

// BEGIN SOURCE modules/Aim_Assist/Support.cpp
#include "../runtime/native/verified/module_access_helpers.hpp"
#include "../runtime/shared/SharedNativeState.hpp"

extern "C" std::uint32_t recovered_chams_flags(GameAccessBridge *, std::uintptr_t, std::uint32_t);
namespace aim_assist {
namespace {
using Word = std::uintptr_t;
Word identifier(const GameAccessBridge *bridge, std::size_t offset) {
    Word value;
    std::memcpy(&value, bridge->metadata + offset, sizeof value);
    return value;
}
template <class Function> Function slot(const GameAccessBridge *bridge, std::size_t offset) {
    return reinterpret_cast<Function>(
        reinterpret_cast<const Word *>(*bridge->environment)[offset / sizeof(Word)]);
}
Word handle(ObjectRef object) {
    return reinterpret_cast<Word>(object);
}
ObjectRef object(Word value) {
    return reinterpret_cast<ObjectRef>(value);
}
template <class Value, std::size_t Slot>
Value field(GameAccessBridge *bridge, ObjectRef entity, std::size_t offset) {
    using Getter = Value (*)(Word *, Word, Word);
    return slot<Getter>(bridge, Slot)(bridge->environment, handle(entity),
                                      identifier(bridge, offset));
}
Vec3d position(GameAccessBridge *bridge, ObjectRef entity, std::size_t offset) {
    // The bridge's environment and metadata are read again for each JNI query.
    const double x = field<double, 0x338>(bridge, entity, offset);
    const double y = field<double, 0x338>(bridge, entity, offset + 8);
    const double z = field<double, 0x338>(bridge, entity, offset + 16);
    return {x, y, z};
}
ObjectRef javaVector(GameAccessBridge *bridge, const Vec3d &value) {
    using Constructor = Word (*)(Word *, Word, Word, ...);
    return object(slot<Constructor>(bridge, 0xe0)(bridge->environment, identifier(bridge, 0x650),
                                                  identifier(bridge, 0x658), value.x, value.y,
                                                  value.z));
}
} // namespace
float Runtime::random01() const {
    return recovered_random_interval(random, randomConstants, recovered_random_bounds(0.0f, 1.0f));
}
std::uint8_t Runtime::chanceHalf() const {
    return static_cast<std::uint8_t>(recovered_random_chance(random, randomConstants, 0.5f));
}
float SmoothedRandom::sample(float low, float high, double duration) const {
    const std::uint32_t value = recovered_policy_smooth_bits(
        state, recovered_random_bounds(low, high), duration, runtime->random, runtime->clock,
        runtime->randomPolicyConstants);
    float result;
    std::memcpy(&result, &value, 4);
    return result;
}
float Runtime::wrap(float value) const {
    return recovered_wrap_angle(value, angleWrapConstants);
}
float Runtime::magnitude(Rotation value) const {
    const std::uint32_t result = recovered_angle_magnitude_9f60(packed(value), distanceConstants);
    float valueResult;
    std::memcpy(&valueResult, &result, 4);
    return valueResult;
}
bool Runtime::isWeapon(GameAccessBridge *bridge, EntityRef player) const {
    return recovered_weapon_cached_query(bridge, handle(player), weaponCache, weaponSettings,
                                         weaponItems, weaponDependencies) != 0;
}
bool Runtime::claimRotationPriority(std::uint32_t priority) const {
    auto &previous = at<std::uint32_t>(image, 0x2f7b50);
    if (priority < previous)
        return false;
    previous = priority;
    return true;
}
void Runtime::addRotationDelta(Rotation value) const {
    const Rotation previous = accumulatedRotationDelta();
    const Rotation sum{native::roundedAdd(value.yaw, previous.yaw),
                       native::roundedAdd(value.pitch, previous.pitch)};
    at<std::uint64_t>(image, 0x2f7b58) = packed(sum);
    at<std::uint32_t>(image, 0x2f7b60) = 0;
}
EntityRef currentTarget(const std::uint8_t *image) {
    EntityRef value;
    std::memcpy(&value, image + 0x2f7be0, sizeof value);
    return value;
}
void accumulateManualAim(std::uint8_t *image, Rotation incoming) {
    const Rotation previous = bits<Rotation>(at<std::uint64_t>(image, 0x2f7c18));
    at<std::uint64_t>(image, 0x2f7c18) =
        recovered_angle_add_9de0(packed(previous), packed(incoming));
}
Rotation angularRotation(const Runtime &runtime, const Vec3d &from, const Vec3d &to) {
    // Canonical 9F80 preserves the native SSE order, post-call image constant
    // loads and yaw narrowing before the second decoded direction invocation.
    return bits<Rotation>(reconstruction::native_state::targetAnglesDecoded(
        &from.x, &to.x, runtime.image,
        {runtime.image, runtime.numericDirectionEncodedCell_13cfb0}));
}

namespace mc {
bool entityIsDead(GameAccessBridge *b, EntityRef e) {
    return field<std::uint8_t, 0x300>(b, e, 0x2f8) != 0;
}
bool entitySleeping(GameAccessBridge *b, EntityRef e) {
    return field<std::uint8_t, 0x300>(b, e, 0x5b8) != 0;
}
bool entityInvisibleToPlayer(GameAccessBridge *b, EntityRef e, EntityRef player) {
    using Query_Support = std::uint8_t (*)(Word *, Word, Word, ...);
    return slot<Query_Support>(b, 0x128)(b->environment, handle(e), identifier(b, 0x580),
                                         handle(player)) != 0;
}
std::uint8_t entityRelationshipFlags(GameAccessBridge *b, EntityRef e) {
    return static_cast<std::uint8_t>(recovered_chams_flags(b, handle(e), 7));
}
Vec3d entityPosition(GameAccessBridge *b, EntityRef e) {
    return position(b, e, 0x268);
}
Vec3d entityPreviousPosition(GameAccessBridge *b, EntityRef e) {
    return position(b, e, 0x280);
}
Vec3d entityOtherPlayerServerPosition(GameAccessBridge *b, EntityRef e) {
    return position(b, e, 0x880);
}
Rotation entityRotation(GameAccessBridge *b, EntityRef e) {
    const float yaw = field<float, 0x330>(b, e, 0x298);
    const float pitch = field<float, 0x330>(b, e, 0x2a0);
    return {yaw, pitch};
}
ObjectRef entityBoundingBoxObject(GameAccessBridge *b, EntityRef e) {
    return object(field<Word, 0x2f8>(b, e, 0x2d0));
}
AABB axisAlignedBBValues(GameAccessBridge *b, ObjectRef e) {
    const Vec3d low = position(b, e, 0x4a8);
    const Vec3d high = position(b, e, 0x4c0);
    AABB result;
    recovered_geometry_pair_96b0(&result, &low, &high);
    return result;
}
float entityHealthOrTwenty(GameAccessBridge *b, EntityRef e) {
    using Query_Support = float (*)(Word *, Word, Word);
    const float value =
        slot<Query_Support>(b, 0x1b8)(b->environment, handle(e), identifier(b, 0x510));
    std::uint32_t valueBits;
    std::memcpy(&valueBits, &value, 4);
    return (valueBits & 0x7fffffffU) >= 0x7f800001U ? 20.0f : value;
}
int entityHurtTime(GameAccessBridge *b, EntityRef e) {
    return field<std::int32_t, 0x320>(b, e, 0x558);
}
int entityNumericId(GameAccessBridge *b, EntityRef e) {
    return field<std::int32_t, 0x320>(b, e, 0x2e0);
}
bool entityIsSprinting(GameAccessBridge *b, EntityRef e) {
    return recovered_game_sprinting(b, handle(e)) != 0;
}
bool positionModeIsZero(GameAccessBridge *b) {
    std::uint32_t value;
    std::memcpy(&value, b->metadata, 4);
    return value == 0;
}
ObjectRef worldPlayerEntityList(GameAccessBridge *b, ObjectRef e) {
    return object(field<Word, 0x2f8>(b, e, 0x360));
}
int javaListSize(GameAccessBridge *b, ObjectRef e) {
    using Query_Support = std::int32_t (*)(Word *, Word, Word);
    return slot<Query_Support>(b, 0x188)(b->environment, handle(e), identifier(b, 0x28));
}
EntityRef javaListElement(GameAccessBridge *b, ObjectRef e, int index) {
    using Query_Support = Word (*)(Word *, Word, Word, ...);
    return object(
        slot<Query_Support>(b, 0x110)(b->environment, handle(e), identifier(b, 0x30), index));
}
bool sameJavaObject(GameAccessBridge *b, ObjectRef a, ObjectRef c) {
    using Query_Support = std::uint8_t (*)(Word *, Word, Word);
    return slot<Query_Support>(b, 0xc0)(b->environment, handle(a), handle(c)) != 0;
}
ObjectRef retainGlobalReference(GameAccessBridge *b, ObjectRef e) {
    using Query_Support = Word (*)(Word *, Word);
    return object(slot<Query_Support>(b, 0xa8)(b->environment, handle(e)));
}
void releaseGlobalReference(GameAccessBridge *b, ObjectRef e) {
    using Query_Support = void (*)(Word *, Word);
    slot<Query_Support>(b, 0xb0)(b->environment, handle(e));
}
bool clearWorldRayBetween(GameAccessBridge *b, ObjectRef world, const Vec3d &from,
                          const Vec3d &to) {
    const ObjectRef javaFrom = javaVector(b, from);
    const ObjectRef javaTo = javaVector(b, to);
    using Query_Support = Word (*)(Word *, Word, Word, ...);
    return slot<Query_Support>(b, 0x110)(b->environment, handle(world), identifier(b, 0x330),
                                         handle(javaFrom), handle(javaTo), 0, 1, 1) == 0;
}
ObjectRef minecraftObjectMouseOver(GameAccessBridge *b, ObjectRef client) {
    return object(recovered_access_helper(b, 0x22e10, handle(client), 0, 0));
}
int movingObjectHitType(GameAccessBridge *b, ObjectRef hit) {
    return static_cast<int>(recovered_access_helper(b, 0x24b50, handle(hit), 0, 0));
}
} // namespace mc
bool attackInputDown(const Frame &frame) {
    const ObjectRef options =
        object(recovered_access_helper(frame.jni, 0x22cf0, handle(frame.minecraft), 0, 0));
    GameAccessBridge *b = frame.jni;
    const ObjectRef array = object(field<Word, 0x2f8>(b, options, 0x3b8));
    using Element = Word (*)(Word *, Word, std::int32_t);
    const ObjectRef key = object(slot<Element>(b, 0x568)(b->environment, handle(array), 0));
    const auto code = field<std::int32_t, 0x320>(frame.jni, key, 0x488);
    return frame.input[1 + (code == -99)] != 0;
}
} // namespace aim_assist
// END SOURCE modules/Aim_Assist/Support.cpp

#ifndef SLINKY_SHARE_3585E319A11C94AFDA81
#define SLINKY_SHARE_3585E319A11C94AFDA81
// BEGIN SOURCE modules/Aim_Assist/JniAccess.hpp
#include "../runtime/shared/JniAccess.hpp"
// END SOURCE modules/Aim_Assist/JniAccess.hpp

#endif // SLINKY_SHARE_3585E319A11C94AFDA81

// Convenient borrowed-state interface

namespace shareable {
using AimAssist = ::aim_assist::AimAssist;
}
