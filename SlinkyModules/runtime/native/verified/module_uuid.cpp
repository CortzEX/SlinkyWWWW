#include "module_uuid.hpp"
#include <cstring>

extern "C" __declspec(dllexport) std::int32_t recovered_uuid_compare(std::uint64_t,
    const void *key, const void *candidate) {
    const auto order = std::memcmp(key, candidate, sizeof(UuidKey));
    return order < 0 ? -1 : order > 0 ? 1 : 0;
}
