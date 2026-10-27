#ifndef SLINKY_SHARE_39743A5F13FF16A8AA62
#define SLINKY_SHARE_39743A5F13FF16A8AA62
#include <cstdint>
#include "WordInvoker.hpp"

using RecoveredTextEndpoint = std::uint64_t (*)(std::uint64_t target,
    std::uint64_t first, std::uint64_t second, std::uint64_t third, std::uint64_t fourth);

// Native builder layout: data pointer, capacity, used bytes, each eight bytes.
// The endpoint supplies the native CRT strlen, memcpy and vsnprintf boundaries.
void recovered_text_initialize_dc20(std::uint8_t *builder, std::uint8_t *buffer,
    std::uint64_t capacity);
std::uint8_t recovered_text_append_dc40(std::uint8_t *builder, const char *text,
    RecoveredTextEndpoint endpoint);
std::uint8_t recovered_text_format_dca0(std::uint8_t *builder, const char *format,
    const std::uint64_t *arguments, RecoveredTextEndpoint endpoint);
std::uint8_t recovered_text_byte_dd10(std::uint8_t *builder, std::uint8_t byte);
std::uint8_t recovered_text_finish_dd40(std::uint8_t *builder);

// Context-bearing overloads share the exact algorithm with the legacy API.
std::uint8_t recovered_text_append_dc40(std::uint8_t *builder, const char *text,
    RecoveredWordInvoker endpoint);
std::uint8_t recovered_text_format_dca0(std::uint8_t *builder, const char *format,
    const std::uint64_t *arguments, RecoveredWordInvoker endpoint);
#endif // SLINKY_SHARE_39743A5F13FF16A8AA62
