#ifndef SLINKY_SHARE_D147A9003FE251FCC237
#define SLINKY_SHARE_D147A9003FE251FCC237
#include <cfloat>
#include <climits>
#include "Support.hpp"
extern "C" void recovered_aim_assist_bound_ui(std::uint64_t, std::uint64_t, std::uint8_t *, const BoundSurfaceUiDependencies *);
extern "C" void recovered_aim_assist_settings(SettingsContext *, std::uint8_t *, const SurfaceSettingsDependencies *);

// Semantic benchmark port, checked against raw evidence and the supplied capture.
// All native state is caller-owned and bound by RVA. See the module report.
namespace aim_assist {
class AimAssist {
public:
    static constexpr const char* kName = "Aim Assist";
    static constexpr const char* kDescription =
        "Pulls your crosshair towards other players.";

    enum class Mode : int {
        Regular = 0,
        Linear  = 1,
        LockOn  = 2,
        Silent  = 3,
    };

    enum class TargetMode : int {
        Single = 0,
        Switch = 1,
    };

    enum class SortBy : int {
        Distance = 0,
        Health   = 1,
        HurtTime = 2,
        AimAngle = 3,
    };

    Runtime &runtime;
    RangeValue fov; // current storage RVA 0x2e8f10
    FloatValue horizontalSpeed; // current storage RVA 0x2e8f50
    FloatValue verticalSpeed; // current storage RVA 0x2e8f88
    BoolValue lockOnVertical; // current storage RVA 0x2e8fa8
    BoolValue requireMouseMoved; // current storage RVA 0x2e8fc8
    ChoiceValue<Mode> mode; // current storage RVA 0x2e9020
    BoolValue silentIgnoreManualAim; // current storage RVA 0x2e9048
    BoolValue silentMoveCorrect; // current storage RVA 0x2e9068
    BoolValue requireSprint; // current storage RVA 0x2e90d8
    BoolValue requireMousePressed; // current storage RVA 0x2e90f8
    BoolValue disableOnBlockBreak; // current storage RVA 0x2e9118
    BoolValue requireWeapon; // current storage RVA 0x2e9138
    RangeValue range; // current storage RVA 0x2e90b0
    ChoiceValue<TargetMode> targetMode; // current storage RVA 0x2e9180
    FloatValue predict; // current storage RVA 0x2e91c0
    FloatValue horizontalMultipoint; // current storage RVA 0x2e91f8
    FloatValue verticalMultipoint; // current storage RVA 0x2e9230
    FloatValue randomization; // current storage RVA 0x2e9268
    BoolValue ignoreInvisibles; // current storage RVA 0x2e9288
    BoolValue allowExceedFov; // current storage RVA 0x2e92a8
    BoolValue requireLineOfSight; // current storage RVA 0x2e92c8
    ChoiceValue<SortBy> sortBy; // current storage RVA 0x2e9320

    explicit AimAssist(Runtime &context) : runtime(context),
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

    void renderSettings(std::uint64_t ui, std::uint64_t layout, const BoundSurfaceUiDependencies &dependencies) {
        recovered_aim_assist_bound_ui(ui, layout, runtime.image, &dependencies);
    }
    void serializeConfig(SettingsContext &context, const SurfaceSettingsDependencies &dependencies) {
        recovered_aim_assist_settings(&context, runtime.image, &dependencies);
    }
    void writeStatus(char *output) const {
        recovered_format(runtime.format, output, 0x20, "%s", runtime.statusLabels[static_cast<int>(mode.value)]);
    }

    EntityRef &currentTarget;
    std::uint8_t &targetActive, &silentInternalState;
    Vec3d &previousAimPoint, &currentAimPoint;
    int &mousePressedGraceTicks;
    std::uint64_t &targetTieCounter;
    SmoothedRandom pitchDamping, pitchNoise, horizontalFactor, verticalFactor, speedFactor;

    // Callback 0x2B5B0 compares the event's +0x10 descriptor with Aim
    // Assist's own descriptor and the +0x18 enabled byte before cleanup.
    void onModuleStateChanged(
        StateChangedEvent& event) {
        if (event.descriptor != runtime.image+0x2e8cc0 || event.enabled != 0)
            return;

        auto* jni = event.frame->jni;

        if (currentTarget)
            mc::releaseGlobalReference(jni, currentTarget);

        currentTarget = nullptr;
        targetActive = false;
    }

    // Kind-13 callback 0x2B610 writes the native event bytes at +8/+9.
    void onMovementCorrection(
        MovementEvent& event) {
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
    bool considerTarget(
        const Frame& frame,
        EntityRef candidate,
        const Vec3d& localEyePos,
        const Rotation& currentView,
        bool currentlyLocked,
        TargetScore& best,
        CandidateResult& result)
    {
        if (mc::entityIsDead(frame.jni, candidate))
            return false;

        // Native 0x240A0 reads the EntityPlayer sleeping field (+0x5B8).
        if (mc::entitySleeping(frame.jni, candidate))
            return false;

        if (ignoreInvisibles.value == 1 &&
            mc::entityInvisibleToPlayer(
                frame.jni, candidate, frame.player))
            return false;

        // The original calls a shared exclusion/filter helper with literal reason/type 7.
        if ((mc::entityRelationshipFlags(
                frame.jni, candidate) & 7U) != 0)
            return false;

        Vec3d position = mc::entityPosition(
            frame.jni, candidate);

        // 0x2C3B0 blends the client position toward the three
        // EntityOtherPlayerMP server-position fields before point selection.
        if (predict.value > 0.0f) {
            const Vec3d server = mc::entityOtherPlayerServerPosition(
                frame.jni, candidate);
            const double scale = static_cast<double>(predict.value);
            position = native::interpolate3(
                position, server, scale); // 0x2C3B0 -> 0x9460
        }

        // 0x2C3B0 expands the current bounding box by 0.1, clamps the
        // local eye into it, and tests range before constructing the aim point.
        const ObjectRef boxObject = mc::entityBoundingBoxObject(
            frame.jni, candidate);
        const AABB box = mc::axisAlignedBBValues(
            frame.jni, boxObject);
        AABB mutableBox=box,expanded;
        recovered_box_expand_9770(&expanded.minX,&mutableBox.minX,0.1);
        Vec3d nearest;
        recovered_box_clamp_9880(&nearest.x,&expanded.minX,&localEyePos.x);
        const double distance = distanceBetween(localEyePos, nearest);
        // 0x2C5D2..0x2C5E2 samples the lower endpoint before the upper
        // distance rejection, multipoint/noise work and angle conversion.
        std::uint8_t aimEnabled = !(static_cast<double>(range.low) > distance);
        if (distance > best.distance) // 0x2C5E6 UCOMISD/JA, unordered passes
            return false;

        const Vec3d aimPoint = selectAimPoint(
            localEyePos, position, nearest, distance,
            horizontalMultipoint.value, verticalMultipoint.value,
            randomization.value);

        const float angle = yawErrorTo(localEyePos, aimPoint, currentView);
        if (angle > best.aimAngle) { // initialized to fov.high
            if (!currentlyLocked) return false;
            aimEnabled = allowExceedFov.value;
        }

        const float health = mc::entityHealthOrTwenty(
            frame.jni, candidate);
        if (health > best.health)
            return false;

        const int hurtTime = mc::entityHurtTime(
            frame.jni, candidate);
        if (hurtTime > best.hurtTime)
            return false;

        if (requireLineOfSight.value == 1 &&
            !mc::clearWorldRayBetween(
                frame.jni, frame.world, localEyePos, aimPoint))
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
                    uint32_t x = static_cast<uint32_t>(
                                     mc::entityNumericId(
                                         frame.jni, candidate));
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
        if (currentlyLocked) targetActive = aimEnabled;
        return true;
    }

    // Kind-18 callback 0x2B630 reads the +0x08 WorldUpdateFrame.
    void updateTarget(WorldUpdateEvent& event) {
        runtime.clearManualAimDelta(); // 0x2B64B

        const auto& frame = *event.frame;
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
                mousePressedGraceTicks =
                    runtime.chanceHalf() + 1;
                return clearTarget(frame.jni);
            }
            if (mousePressedGraceTicks != 0 &&
                static_cast<int>(mode.value) < static_cast<int>(Mode::LockOn)) {
                --mousePressedGraceTicks;
                return clearTarget(frame.jni);
            }
        }

        if ((disableOnBlockBreak.value & static_cast<std::uint8_t>(mouseActive)) == 1) {
            ObjectRef mouseOver = mc::minecraftObjectMouseOver(
                frame.jni, frame.minecraft);
            if (mouseOver && mc::movingObjectHitType(
                    frame.jni, mouseOver) == 1) {
                targetActive = false; // 0x2B6F9 -> 0x2B949 retains currentTarget
                return;
            }
        }

        if (requireWeapon.value == 1 &&
            !runtime.isWeapon(frame.jni, frame.player))
            return clearTarget(frame.jni);

        const Vec3d localEyePos = playerEyePosition(frame);
        const Rotation currentView =
            runtime.storedRotationValid()
                ? runtime.storedRotation()
                : mc::entityRotation(frame.jni, frame.player);

        TargetScore best {
            static_cast<double>(range.high),
            FLT_MAX,
            INT_MAX,
            0,
            fov.high
        };

        CandidateResult selectedResult{};
        EntityRef selected = nullptr;

        // Single mode validates the old global reference before enumeration.
        if (targetMode.value == TargetMode::Single && currentTarget) {
            if (considerTarget(frame, currentTarget, localEyePos, currentView,
                               true, best, selectedResult)) {
                previousAimPoint = currentAimPoint;
                currentAimPoint = selectedResult.aimPoint;
                return;
            }
            clearTarget(frame.jni); // native releases the failed locked target now
        }

        if (!selected) {
            ObjectRef players = mc::worldPlayerEntityList(
                frame.jni, frame.world);
            int count = mc::javaListSize(frame.jni, players);
            if (count > 0) {
                std::uint32_t index = 0;
                do {
                    EntityRef candidate = mc::javaListElement(
                        frame.jni, players, static_cast<int>(index));
                    if (!mc::sameJavaObject(
                            frame.jni, frame.player, candidate)) {
                        CandidateResult r{};
                        if (considerTarget(frame, candidate, localEyePos, currentView,
                                           false, best, r)) {
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

        const bool sameObject = mc::sameJavaObject(
            frame.jni, currentTarget, selected);
        previousAimPoint = sameObject ? currentAimPoint : selectedResult.aimPoint;
        currentAimPoint = selectedResult.aimPoint;
        targetActive = selectedResult.aimEnabled;
        if (currentTarget)
            mc::releaseGlobalReference(frame.jni, currentTarget);
        const EntityRef retained = mc::retainGlobalReference(
            frame.jni, selected);
        // 0x2BA94/0x2BA97 skips the global store on allocation failure.
        // Preserve this native failure behavior, including the old value
        // remaining after DeleteGlobalRef; do not invent a nulling store.
        if (retained) currentTarget = retained;
    }

    // Type-1 frame callback at 0x2B200. The target flag and the silent
    // rotation-restoration flag are separate native globals.
    void onRotationFrame(RotationFrameEvent& event) {
        const auto& frame = *event.frame;
        if (frame.focusAllowed != 1)
            return;

        if (!targetActive) {
            if (silentInternalState != 1)
                return;
            if (runtime.storedRotationValid() &&
                runtime.claimRotationPriority(100)) {
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
        if (silentInternalState &&
            !runtime.storedRotationValid())
            return;

        const float playerPartialTicks = event.timerRenderPartialTicks; // 0x2B34F
        const Vec3d previous = mc::entityPreviousPosition(
            frame.jni, frame.player);
        const Vec3d current = mc::entityPosition(
            frame.jni, frame.player);
        const Vec3d displacement {
            native::roundedSubDouble(current.x, previous.x),
            native::roundedSubDouble(current.y, previous.y),
            native::roundedSubDouble(current.z, previous.z)
        }; // 0x2B39F -> 0x93D0
        const double playerPartial = static_cast<double>(playerPartialTicks);
        const Vec3d scaled {
            native::roundedMulDouble(playerPartial, displacement.x),
            native::roundedMulDouble(playerPartial, displacement.y),
            native::roundedMulDouble(playerPartial, displacement.z)
        }; // 0x2B3C2 -> 0x9430, fraction in each destination lane
        Vec3d eye {
            native::roundedAddDouble(previous.x, scaled.x),
            native::roundedAddDouble(previous.y, scaled.y),
            native::roundedAddDouble(scaled.z, previous.z)
        }; // 0x2B3E1 -> 0x9400: X/Y first+second, Z second+first
        if (!mc::positionModeIsZero(frame.jni))
            eye.y = native::roundedAddDouble(eye.y, 1.62);

        const double partial = static_cast<double>(event.timerRenderPartialTicks); // 0x2B429
        const Vec3d aimPoint = native::interpolate3(
            previousAimPoint, currentAimPoint, partial); // 0x9460
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
                rotationMagnitude(targetFromStored) <
                    rotationMagnitude(error)) {
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
        error.pitch = error.pitch > 0.0f
            ? maxFloatSse(roundedSub(error.pitch, deadZone), 0.0f)
            : minFloatSse(roundedAdd(deadZone, error.pitch), 0.0f);

        Mode sampledMode = mode.value; // 0x2BFC2/0x2C099
        if (sampledMode != Mode::LockOn) {
            const float rnd = pitchDamping.sampleTime(
                40.0f, 120.0f, 5.0, drawUnit);
            const double slope = roundedDivDouble(-1.0, static_cast<double>(rnd));
            const double damped = roundedAddDouble(roundedMulDouble(
                slope, static_cast<double>(absoluteBits(error.yaw))), 1.0);
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
            if (sampledMode == Mode::Silent) { // same EAX value at 0x2C056
                hSpeed = maxFloatSse(5.0f, hSpeed); // 0x2C06C operand order
                if (5.0f > vSpeed) vSpeed = 5.0f; // unordered retains vSpeed
            }
            const float hHalf = roundedMul(hSpeed, 0.5f);
            const float hSquared = roundedMul(hHalf, hHalf);
            const float hRnd = horizontalFactor.sampleTime(
                0.9f, 1.1f, 1.0, drawUnit);
            float yawFactor = roundedMul(hRnd, hSquared);
            const float vHalf = roundedMul(vSpeed, 0.5f);
            const float vSquared = roundedMul(vHalf, vHalf);
            const float vRnd = verticalFactor.sampleTime(
                0.9f, 1.1f, 1.0, drawUnit);
            float pitchFactor = roundedMul(vRnd, vSquared);
            const float globalRnd = speedFactor.sampleTime(
                0.95f, 1.05f, 60.0, drawUnit);

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
                if (!(absoluteBits(rawYaw) > absoluteBits(error.yaw))) error.yaw = rawYaw;
                if (!(absoluteBits(rawPitch) > absoluteBits(error.pitch))) error.pitch = rawPitch;
            }

            if (mode.value != Mode::LockOn) { // 0x2C343 reloads the mode
                const float pitchNoiseBound = static_cast<float>(roundedMulDouble(
                    static_cast<double>(absoluteBits(error.yaw)), 0.1));
                const float noise = pitchNoise.sampleTime(
                    -pitchNoiseBound, pitchNoiseBound, 1.0, drawUnit);
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
            if (adjustYaw) error.yaw = scaledYaw;
        }
        runtime.addRotationDelta(error);
    }

private:
    Rotation rotationTo(const Vec3d &from, const Vec3d &to) { return angularRotation(runtime,from,to); }

    Rotation rotationDifference(Rotation target, Rotation current) {
        Rotation difference=bits<Rotation>(recovered_angle_subtract_9e20(packed(target),packed(current)));
        difference.yaw=runtime.wrap(difference.yaw);
        return difference;
    }

    Rotation currentRotationWithPending(
            const Frame& frame) {
        const Rotation current = mc::entityRotation(
            frame.jni, frame.player);
        const Rotation pending =
            runtime.accumulatedRotationDelta();
        return bits<Rotation>(recovered_angle_add_9de0(packed(current),packed(pending)));
    }

    float rotationMagnitude(Rotation rotation) {
        return runtime.magnitude(rotation); // 0x9F60
    }

    void clearTarget(GameAccessBridge* jni) {
        if (currentTarget)
            mc::releaseGlobalReference(jni, currentTarget);
        currentTarget = nullptr;
        targetActive = false;
    }

    static double distanceBetween(const Vec3d& a, const Vec3d& b) {
        return native::distance3(a, b); // 0x94F0
    }

    Vec3d selectAimPoint(const Vec3d& localEye, const Vec3d& predicted,
                                const Vec3d& nearest, double distance,
                                float horizontalPct, float verticalPct,
                                float randomPct) {
        using namespace native;
        const Vec3d targetEye {predicted.x, roundedAddDouble(predicted.y, 1.62), predicted.z};
        double x = targetEye.x;
        double z = targetEye.z;
        if (horizontalPct > 0.0f) {
            float fraction = horizontalPct;
            if (distance < 3.5)
                fraction = static_cast<float>(roundedMulDouble(
                    static_cast<double>(horizontalPct), roundedDivDouble(distance, 3.5)));
            const Vec3d horizontal = native::interpolate3(
                targetEye, nearest, static_cast<double>(fraction)); // 0x2C3B0 -> 0x9460
            x = horizontal.x;
            z = horizontal.z;
        }
        const double y = native::lerpDouble(
            targetEye.y,nearest.y,static_cast<double>(verticalPct));

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
            const double closeRangeFactor = roundedAddDouble(roundedMulDouble(
                roundedDivDouble(distance, 3.5), 0.9), 0.1);
            randomScale = static_cast<float>(roundedMulDouble(
                static_cast<double>(randomPct), closeRangeFactor));
        }
        const double scale = static_cast<double>(randomScale);
        const Vec3d noise {roundedMulDouble(scale, halfNoiseX),
                           roundedMulDouble(scale, halfNoiseY),
                           roundedMulDouble(scale, halfNoiseZ)}; // 0x9430 operand order
        return {roundedAddDouble(x, noise.x),
                roundedAddDouble(y, noise.y),
                roundedAddDouble(z, noise.z)};
    }

    float yawErrorTo(const Vec3d& from, const Vec3d& to,
                            const Rotation& currentView) {
        // 0x2C3B0 invokes the full 0x9F80 yaw/pitch helper even though this
        // predicate subsequently consumes only its yaw lane.
        const float targetYaw = rotationTo(from, to).yaw;
        const float error = runtime.wrap(
            native::roundedSub(targetYaw, currentView.yaw));
        return absoluteBits(error);
    }
    static Vec3d playerEyePosition(
            const Frame& frame) {
        Vec3d position = mc::entityPosition(
            frame.jni, frame.player);
        if (!mc::positionModeIsZero(frame.jni))
            position.y = native::roundedAddDouble(position.y, 1.62);
        return position;
    }

    static float shrinkTowardZero(float v, float amount) {
        if (v > 0.0f) return native::maxFloatSse(
            native::roundedSub(v, amount), 0.0f);
        return native::minFloatSse(
            native::roundedAdd(v, amount), 0.0f);
    }

    static float absoluteBits(float value) {
        std::uint32_t bits{};
        std::memcpy(&bits, &value, sizeof bits);
        bits &= 0x7FFFFFFFU;
        std::memcpy(&value, &bits, sizeof value);
        return value;
    }

};

}
#endif // SLINKY_SHARE_D147A9003FE251FCC237
