#ifndef SLINKY_SHARE_360B471A17BC27BF17DB
#define SLINKY_SHARE_360B471A17BC27BF17DB
#include <cstddef>
#include <cstdint>
#include <cstring>

using AccessDependency = std::uint64_t (*)(void *, std::uint32_t,
    std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t);
using AccessFloatDependency = std::uint64_t (*)(std::uint64_t, std::uint64_t, float);

struct AccessDependencies {
    AccessDependency invoke;
    void *context;
    AccessFloatDependency invoke_23e60;
    AccessFloatDependency invoke_23e90;
};

struct AccessGlobals {
    std::uint8_t enabled_44940;
    std::uint8_t enabled_44940_second;
    std::uint8_t state_42b80;
    std::int32_t state_3e590;
    std::int32_t countdown_3e8e0;
    std::int32_t last_value_3e8e0;
    std::uint8_t gate_3e8e0;
};

static_assert(sizeof(AccessDependencies) == 32);
static_assert(sizeof(AccessGlobals) == 20);
static_assert(offsetof(AccessGlobals, state_3e590) == 4);

inline std::uint64_t access_word(const void *base, std::size_t offset) {
    std::uint64_t value;
    std::memcpy(&value, static_cast<const std::uint8_t *>(base) + offset, sizeof(value));
    return value;
}

inline std::uint64_t access_call(const AccessDependencies *deps, std::uint32_t helper,
    std::uint64_t a, std::uint64_t b, std::uint64_t c = 0, std::uint64_t d = 0) {
    return deps->invoke(deps->context, helper, a, b, c, d);
}
#endif // SLINKY_SHARE_360B471A17BC27BF17DB
