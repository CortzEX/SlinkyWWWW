#include "KeyNames.hpp"
#include <cstring>
const char *recovered_key_name_9380(std::uint32_t key, const std::uint8_t *image) {
    const std::uint32_t index = key - 1;
    if (index > 0x66) return reinterpret_cast<const char *>(image + 0x13e692);
    std::int32_t displacement;
    std::memcpy(&displacement, image + 0x13e698 + std::uint64_t(index) * 4, 4);
    return reinterpret_cast<const char *>(image + 0x13e698 + displacement);
}
