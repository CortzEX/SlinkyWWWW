#include "Text.hpp"
#include <bit>
#include <cstring>

namespace {
std::uint64_t readWord(const void *source) {
    std::uint64_t value;
    std::memcpy(&value, source, sizeof value);
    return value;
}
void writeWord(void *destination, std::uint64_t value) {
    std::memcpy(destination, &value, sizeof value);
}
std::uint64_t address(const void *value) {
    return reinterpret_cast<std::uintptr_t>(value);
}
}

// RVA DC20. Store order follows the native three MOV instructions.
void recovered_text_initialize_dc20(std::uint8_t *builder, std::uint8_t *buffer,
    std::uint64_t capacity) {
    writeWord(builder, address(buffer));
    writeWord(builder + 8, capacity);
    writeWord(builder + 16, 0);
}

// RVA DC40. The original count survives strlen, while the buffer pointer is
// reloaded after it. The post-copy count update reloads memory for reentrancy.
std::uint8_t recovered_text_append_dc40(std::uint8_t *builder, const char *text,
    RecoveredWordInvoker endpoint) {
    const std::uint64_t capacity = readWord(builder + 8);
    const std::uint64_t count = readWord(builder + 16);
    if (capacity <= count)
        return 0;
    const std::uint64_t remaining = capacity - count;
    const std::uint64_t length = endpoint(0xAB840, address(text), 0, 0, 0);
    if (length >= remaining)
        return 0;
    const std::uint64_t destination = readWord(builder) + count;
    endpoint(0xABBF0, destination, address(text), length, 0);
    writeWord(builder + 16, readWord(builder + 16) + length);
    return 1;
}

// RVA DCA0. The explicit arguments array represents the recovered native
// variadic save area; the formatter itself remains the actual CRT boundary.
std::uint8_t recovered_text_format_dca0(std::uint8_t *builder, const char *format,
    const std::uint64_t *arguments, RecoveredWordInvoker endpoint) {
    const std::uint64_t capacity = readWord(builder + 8);
    const std::uint64_t count = readWord(builder + 16);
    if (capacity <= count)
        return 0;
    const std::uint64_t remaining = capacity - count;
    const std::uint64_t destination = readWord(builder) + readWord(builder + 16);
    const std::uint32_t written = static_cast<std::uint32_t>(
        endpoint(0xAB770, destination, remaining, address(format), address(arguments)));
    if (std::bit_cast<std::int32_t>(written) < 0 || written >= remaining) {
        writeWord(builder + 16, readWord(builder + 8));
        return 0;
    }
    writeWord(builder + 16, readWord(builder + 16) + written);
    return 1;
}

// RVA DD10. Increment precedes the byte write, including when the buffer aliases
// the builder. Capacity includes the terminator only when the caller adds one.
std::uint8_t recovered_text_byte_dd10(std::uint8_t *builder, std::uint8_t byte) {
    const std::uint64_t capacity = readWord(builder + 8);
    const std::uint64_t count = readWord(builder + 16);
    if (count >= capacity)
        return 0;
    auto *buffer = reinterpret_cast<std::uint8_t *>(
        static_cast<std::uintptr_t>(readWord(builder)));
    writeWord(builder + 16, count + 1);
    buffer[count] = byte;
    return 1;
}

// RVA DD40. The terminator write precedes ADD [builder+16],1.
std::uint8_t recovered_text_finish_dd40(std::uint8_t *builder) {
    const std::uint64_t capacity = readWord(builder + 8);
    const std::uint64_t count = readWord(builder + 16);
    if (count >= capacity)
        return 0;
    auto *buffer = reinterpret_cast<std::uint8_t *>(
        static_cast<std::uintptr_t>(readWord(builder)));
    buffer[count] = 0;
    writeWord(builder + 16, readWord(builder + 16) + 1);
    return 1;
}

namespace {
std::uint64_t legacyInvoke(void *context, std::uint64_t target, std::uint64_t a,
    std::uint64_t b, std::uint64_t c, std::uint64_t d) {
    return (*static_cast<RecoveredTextEndpoint *>(context))(target, a, b, c, d);
}
}
std::uint8_t recovered_text_append_dc40(std::uint8_t *builder, const char *text, RecoveredTextEndpoint endpoint) {
    return recovered_text_append_dc40(builder, text, RecoveredWordInvoker{&endpoint, legacyInvoke});
}
std::uint8_t recovered_text_format_dca0(std::uint8_t *builder, const char *format,
    const std::uint64_t *arguments, RecoveredTextEndpoint endpoint) {
    return recovered_text_format_dca0(builder, format, arguments, RecoveredWordInvoker{&endpoint, legacyInvoke});
}
