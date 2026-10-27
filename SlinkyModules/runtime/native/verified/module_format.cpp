#include "module_format.hpp"

// 0xab070 supplies the shared option word's address.
extern "C" __declspec(dllexport) std::uint64_t *recovered_format_options(FormatState *state) {
    return &state->options;
}

// 0xab770 forwards the existing argument list, with option bit 1 and a null locale.
extern "C" __declspec(dllexport) std::uint64_t recovered_format_arguments(
    FormatState *state, char *destination, std::size_t capacity,
    const char *format, std::va_list arguments) {
    return state->endpoint(*recovered_format_options(state) | 2, destination,
                           capacity, format, nullptr, arguments);
}

// 0xab710 retains normal Windows x64 C vararg promotions and word layout.
extern "C" __declspec(dllexport) std::uint64_t recovered_format(
    FormatState *state, char *destination, std::size_t capacity, const char *format, ...) {
    std::va_list arguments;
    va_start(arguments, format);
    const auto result = recovered_format_arguments(state, destination, capacity, format, arguments);
    va_end(arguments);
    return result;
}
