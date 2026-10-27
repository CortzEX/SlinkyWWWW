#pragma once
#include <cstdint>

struct UuidKey { std::uint64_t words[2]; };
static_assert(sizeof(UuidKey) == 16);

// 0x3b380 compares the two raw qwords as big-endian byte strings; user is ignored.
extern "C" __declspec(dllexport) std::int32_t recovered_uuid_compare(
    std::uint64_t user, const void *key, const void *candidate);
