#ifndef SLINKY_SHARE_76A3E3618FC00C146812
#define SLINKY_SHARE_76A3E3618FC00C146812
#include <cstdint>
#include <cstring>
#include <emmintrin.h>
#include "../../native/verified/module_game_access.hpp"
#include "../../native/verified/module_random_policy.hpp"
#include "../../native/verified/module_float_math.hpp"
#include "../../native/verified/module_float_distance.hpp"
#include "../../native/verified/module_format.hpp"
#include "../../native/verified/module_surface.hpp"
#include "../../native/verified/Weapons.hpp"
#include "../../shared/Geometry.hpp"

namespace aim_assist {
using ObjectRef = void *;
using EntityRef = void *;
struct Vec3d { double x, y, z; };
struct Rotation { float yaw, pitch; };
struct AABB { double minX, minY, minZ, maxX, maxY, maxZ; };
struct Frame {
    GameAccessBridge *jni;
    std::uint64_t reserved[2];
    ObjectRef minecraft, world;
    EntityRef player;
    std::uint8_t *input;
    void *targetRecord;
    std::uint8_t focusAllowed;
};
struct WorldUpdateEvent { std::uint64_t kind; Frame *frame; };
struct RotationFrameEvent {
    std::uint64_t kind; Frame *frame;
    float timerRenderPartialTicks; std::uint32_t reserved;
    double elapsedSeconds;
};
struct StateChangedEvent {
    std::uint64_t kind; Frame *frame; const void *descriptor; std::uint8_t enabled;
};
struct MovementEvent { std::uint64_t kind; std::uint8_t active, remapMovement; };
static_assert(offsetof(Frame, focusAllowed) == 0x40);
static_assert(offsetof(RotationFrameEvent, elapsedSeconds) == 0x18);
static_assert(offsetof(StateChangedEvent, enabled) == 0x18);
static_assert(sizeof(Rotation) == 8 && sizeof(Vec3d) == 24 && sizeof(AABB) == 48);
struct BoolValue { std::uint8_t &value; };
struct FloatValue { float &value; };
struct RangeValue { float &low, &high; };
template<class E> struct ChoiceValue { E &value; };
template<class T> T &at(std::uint8_t *image, std::uint32_t rva) {
    return *reinterpret_cast<T *>(image + rva);
}
template<class T> T bits(std::uint64_t value) {
    T result; std::memcpy(&result, &value, sizeof result); return result;
}
inline std::uint64_t packed(Rotation value) {
    std::uint64_t result; std::memcpy(&result, &value, 8); return result;
}

struct Runtime;
struct SmoothedRandom {
    Runtime *runtime; SmoothRandomState *state;
    float sample(float low, float high, double duration) const;
    template<class Draw> float sampleTime(float low, float high, double duration, Draw) const {
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
    bool storedRotationValid() const { return image[0x2f7b90] != 0; }
    Rotation storedRotation() const { return bits<Rotation>(at<std::uint64_t>(image, 0x2f7b70)); }
    Rotation accumulatedRotationDelta() const { return bits<Rotation>(at<std::uint64_t>(image, 0x2f7b58)); }
    Rotation manualAimDelta() const { return bits<Rotation>(at<std::uint64_t>(image, 0x2f7c18)); }
    void clearManualAimDelta() const { at<std::uint64_t>(image, 0x2f7c18) = 0; }
    bool claimRotationPriority(std::uint32_t priority) const;
    void addRotationDelta(Rotation) const;
};
EntityRef currentTarget(const std::uint8_t *image); // native0x2b1c0
void accumulateManualAim(std::uint8_t *image,Rotation); // native0x2b1d0
Rotation angularRotation(const Runtime &, const Vec3d &, const Vec3d &); // native 0x9f80
namespace native {
inline float roundedAdd(float a, float b) { return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a), _mm_set_ss(b))); }
inline float roundedSub(float a, float b) { return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a), _mm_set_ss(b))); }
inline float roundedMul(float a, float b) { return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a), _mm_set_ss(b))); }
inline float roundedDiv(float a, float b) { return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a), _mm_set_ss(b))); }
inline float maxFloatSse(float a, float b) { return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a), _mm_set_ss(b))); }
inline float minFloatSse(float a, float b) { return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a), _mm_set_ss(b))); }
inline double roundedAddDouble(double a, double b) { return _mm_cvtsd_f64(_mm_add_sd(_mm_set_sd(a), _mm_set_sd(b))); }
inline double roundedSubDouble(double a, double b) { return _mm_cvtsd_f64(_mm_sub_sd(_mm_set_sd(a), _mm_set_sd(b))); }
inline double roundedMulDouble(double a, double b) { return _mm_cvtsd_f64(_mm_mul_sd(_mm_set_sd(a), _mm_set_sd(b))); }
inline double roundedDivDouble(double a, double b) { return _mm_cvtsd_f64(_mm_div_sd(_mm_set_sd(a), _mm_set_sd(b))); }
inline double sqrtDouble(double value) { return _mm_cvtsd_f64(_mm_sqrt_sd(_mm_setzero_pd(), _mm_set_sd(value))); }
inline float clampFloat(float low, float high, float value) { return recovered_float_clamp_a1f0(low, high, value); }
inline double clampBoxCoordinate(double value, double low, double high) {
    const double limited = _mm_cvtsd_f64(_mm_min_sd(_mm_set_sd(high), _mm_set_sd(value)));
    return value < low ? low : limited;
}
inline Vec3d interpolate3(const Vec3d &from, const Vec3d &to, double amount) {
    Vec3d result; recovered_vector_lerp_9460(&result.x, &from.x, &to.x, amount); return result;
}
inline double distance3(const Vec3d &a, const Vec3d &b) { return recovered_vector_distance_94f0(&a.x, &b.x); }
inline double lerpDouble(double a, double b, double amount) { return recovered_scalar_lerp_a2d0(a, b, amount); }
}
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
}
bool attackInputDown(const Frame &);
}
#endif // SLINKY_SHARE_76A3E3618FC00C146812
