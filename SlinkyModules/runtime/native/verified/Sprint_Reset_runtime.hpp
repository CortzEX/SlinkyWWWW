#ifndef SLINKY_SHARE_0656B1C9495EA064A9F0
#define SLINKY_SHARE_0656B1C9495EA064A9F0
#include "Sprint_Reset.hpp"
#include "Timer.hpp"
#include "Weapons.hpp"
#include "module_random_policy.hpp"

struct SprintResetEvent { std::uintptr_t event_type; TimerGame *game; };
struct SprintResetState {
    volatile std::uint32_t phase;
    volatile float timer;
    volatile double last_sample_time;
    volatile std::uint8_t have_state;
    std::uint8_t padding[3];
    volatile std::uint32_t sample_count;
    SmoothRandomState delay_random, duration_random, gate_random;
};
struct SprintResetConstants {
    double minimum_elapsed;
    float decrement, one;
    double suppression_window;
    float gate_low, gate_high, two;
    std::uint32_t padding;
    double delay_window;
};
struct SprintResetDependencies {
    std::uint32_t (*counter)(GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*other_counter)(GameAccessBridge *, std::uintptr_t);
    std::uint32_t (*damage)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*options)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*forward_key)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*sneak_key)(GameAccessBridge *, std::uintptr_t);
    std::uintptr_t (*sprint_key)(GameAccessBridge *, std::uintptr_t);
    void (*set_sprinting)(GameAccessBridge *, std::uintptr_t, std::uint8_t);
    std::uint32_t (*physical_key)(GameAccessBridge *, std::uintptr_t);
    void (*set_key)(GameAccessBridge *, std::uintptr_t, std::uint32_t);
    // The boundary provider records R8 after each JNI call. 0x3b150 retains its upper DWORD bytes.
    const volatile std::uint32_t *post_call_r8;
    std::uint64_t *frequency_bits;
    const std::uint8_t *frequency_target, *counter_target;
    WeaponCache *weapon_cache;
    const WeaponSettings *weapon_settings;
    const ItemPolicyTable *weapon_policy;
    const WeaponDependencies *weapons;
    RandomState *random;
    const RandomConstants *random_constants;
    const RandomPolicyConstants *policy_constants;
    const double *policy_clock;
};
static_assert(sizeof(SprintResetEvent) == 16);
static_assert(sizeof(SprintResetState) == 72);
static_assert(offsetof(SprintResetState, delay_random) == 24);
static_assert(offsetof(SprintResetState, duration_random) == 40);
static_assert(offsetof(SprintResetState, gate_random) == 56);
static_assert(sizeof(SprintResetConstants) == 48);
static_assert(offsetof(SprintResetConstants, delay_window) == 40);
static_assert(sizeof(SprintResetDependencies) == 176);

extern "C" {
__declspec(dllexport) void recovered_bind_sprint_reset_access(SprintResetDependencies *);
__declspec(dllexport) std::uint32_t recovered_sprint_reset_other_counter(GameAccessBridge *, std::uintptr_t);
__declspec(dllexport) std::uint32_t recovered_sprint_reset_physical_word(GameAccessBridge *, std::uintptr_t);
__declspec(dllexport) void recovered_sprint_reset_action(TimerGame *, const SprintResetSettings *, std::uint32_t active_word,
    const SprintResetDependencies *);
__declspec(dllexport) void recovered_sprint_reset_update(SprintResetEvent *, const SprintResetSettings *,
    SprintResetState *, const SprintResetConstants *, const SprintResetDependencies *);
}
#endif // SLINKY_SHARE_0656B1C9495EA064A9F0
