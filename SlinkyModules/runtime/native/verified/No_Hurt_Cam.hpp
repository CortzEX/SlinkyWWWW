#ifndef SLINKY_SHARE_FC8D4BBF571D9E1D0843
#define SLINKY_SHARE_FC8D4BBF571D9E1D0843
#include "Free_Look.hpp"

struct NoHurtCamDescriptor {
    std::uint8_t reserved[20];
    std::uint8_t enabled;
    std::uint8_t padding[3];
};
struct AngleRestoreState {
    CameraAngleState camera;
    CameraRotation observed;
    std::uint8_t applied;
    std::uint8_t padding[7];
};
struct PitchRange { float lower, upper; };
struct AngleRestoreBounds { PitchRange current, previous; };
struct NoHurtCamDependencies {
    std::uintptr_t (*client)(GameAccessBridge *);
    std::uintptr_t (*entity)(GameAccessBridge *, std::uintptr_t);
    std::uint64_t (*player_angles)(GameAccessBridge *, std::uintptr_t);
    void (*set_current_angles)(GameAccessBridge *, std::uintptr_t, std::uint64_t, const PitchRange *);
    void (*set_previous_angles)(GameAccessBridge *, std::uintptr_t, std::uint64_t, const PitchRange *);
    void (*set_hurt_time)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    std::uint64_t (*final_call)(GameAccessBridge *);
};
static_assert(offsetof(NoHurtCamDescriptor, enabled) == 20);
static_assert(sizeof(AngleRestoreState) == 32);
static_assert(offsetof(AngleRestoreState, observed) == 16);
static_assert(offsetof(AngleRestoreState, applied) == 24);
static_assert(sizeof(AngleRestoreBounds) == 16);
static_assert(sizeof(NoHurtCamDependencies) == 56);

extern "C" {
__declspec(dllexport) void recovered_bind_no_hurt_cam_access(NoHurtCamDependencies *);
__declspec(dllexport) void recovered_angle_restore(GameAccessBridge *, AngleRestoreState *,
    const AngleRestoreBounds *, const NoHurtCamDependencies *);
__declspec(dllexport) std::uint64_t recovered_no_hurt_cam_hook(const std::uint8_t *const *metadata,
    std::uintptr_t *environment, const NoHurtCamDescriptor *const *descriptor,
    AngleRestoreState *, const AngleRestoreBounds *, const NoHurtCamDependencies *);
}
#endif // SLINKY_SHARE_FC8D4BBF571D9E1D0843
