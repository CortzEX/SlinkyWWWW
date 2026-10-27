// Captured ordinary instructions: reports/native/render_strings_ab840.asm.
#include "ByteStrings.hpp"

// Native RVA AB840: byte scan, increment after the tested byte.
std::uint64_t recovered_string_length_ab840(const std::uint8_t *text) {
    std::uint64_t count = 0;
    while (text[count] != 0) ++count;
    return count;
}

// Native RVA AB860: unsigned byte subtraction returned in EAX, first mismatch.
std::uint32_t recovered_bytes_compare_ab860(const std::uint8_t *first,
    const std::uint8_t *second, std::uint64_t count) {
    for (std::uint64_t index = 0; index != count; ++index) {
        const auto difference = std::uint32_t(first[index]) - std::uint32_t(second[index]);
        if (difference != 0) return difference;
    }
    return 0;
}

// Native RVA AB890: initial count mod 8 bytes, then ascending groups of eight.
void *recovered_bytes_fill_ab890(void *destination, std::uint8_t byte, std::uint64_t count) {
    auto *data = static_cast<volatile std::uint8_t *>(destination);
    const auto remainder = count & 7;
    for (std::uint64_t index = 0; index != remainder; ++index) data[index] = byte;
    for (std::uint64_t index = remainder; index < count; index += 8) {
        data[index] = byte; data[index + 1] = byte;
        data[index + 2] = byte; data[index + 3] = byte;
        data[index + 4] = byte; data[index + 5] = byte;
        data[index + 6] = byte; data[index + 7] = byte;
    }
    return destination;
}
