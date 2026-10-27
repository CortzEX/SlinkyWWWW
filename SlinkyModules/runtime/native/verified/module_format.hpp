#ifndef SLINKY_SHARE_4F21DEB97F38535F5227
#define SLINKY_SHARE_4F21DEB97F38535F5227
#include <cstddef>
#include <cstdint>
#include <cstdarg>

using FormatEndpoint = std::uint64_t (*)(std::uint64_t options, char *destination,
    std::size_t capacity, const char *format, void *locale, std::va_list arguments);

struct FormatState {
    std::uint64_t options;
    FormatEndpoint endpoint;
};
static_assert(sizeof(FormatState) == 16);
static_assert(offsetof(FormatState, endpoint) == 8);

extern "C" {
__declspec(dllexport) std::uint64_t *recovered_format_options(FormatState *);
__declspec(dllexport) std::uint64_t recovered_format_arguments(FormatState *, char *destination, std::size_t capacity, const char *format, std::va_list arguments);
__declspec(dllexport) std::uint64_t recovered_format(FormatState *, char *destination, std::size_t capacity, const char *format, ...);
}
#endif // SLINKY_SHARE_4F21DEB97F38535F5227
