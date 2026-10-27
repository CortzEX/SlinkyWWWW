#ifndef SLINKY_SHARE_5F2BA658C53BB9714694
#define SLINKY_SHARE_5F2BA658C53BB9714694
#include <cstdint>
#include "WordInvoker.hpp"

using RecoveredGraphicsEndpoint = std::uint64_t (*)(std::uint64_t target,
    std::uint64_t, std::uint64_t, std::uint64_t, std::uint64_t);
std::uint64_t recovered_render_293c0(std::uint8_t *, RecoveredGraphicsEndpoint);
std::uint64_t recovered_render_29400(std::uint8_t *, RecoveredGraphicsEndpoint);
std::uint64_t recovered_render_29430(std::uint8_t *, RecoveredGraphicsEndpoint);
std::uint64_t recovered_render_29460(std::uint8_t *, RecoveredGraphicsEndpoint);
std::uint64_t recovered_render_294a0(std::uint8_t *, RecoveredGraphicsEndpoint);
std::uint64_t recovered_render_294d0(std::uint8_t *, RecoveredGraphicsEndpoint);
std::uint64_t recovered_render_29500(std::uint8_t *, RecoveredGraphicsEndpoint);
std::uint64_t recovered_render_29540(std::uint8_t *, RecoveredGraphicsEndpoint);
std::uint64_t recovered_render_29570(std::uint8_t *, RecoveredGraphicsEndpoint);
std::uint64_t recovered_render_295a0(std::uint8_t *, RecoveredGraphicsEndpoint);
std::uint32_t recovered_screen_project_295c0(std::uint8_t *context,
    const double *point, float *screen, std::uint8_t *constant_image);
std::uint32_t recovered_screen_project_295f0(std::uint8_t *context,
    const double *point, float *screen, float *reciprocal_output,
    std::uint8_t *constant_image);

// Context-bearing overloads share the exact algorithm with the legacy API.
std::uint64_t recovered_render_293c0(std::uint8_t *, RecoveredWordInvoker);
std::uint64_t recovered_render_29400(std::uint8_t *, RecoveredWordInvoker);
std::uint64_t recovered_render_29430(std::uint8_t *, RecoveredWordInvoker);
std::uint64_t recovered_render_29460(std::uint8_t *, RecoveredWordInvoker);
std::uint64_t recovered_render_294a0(std::uint8_t *, RecoveredWordInvoker);
std::uint64_t recovered_render_294d0(std::uint8_t *, RecoveredWordInvoker);
std::uint64_t recovered_render_29500(std::uint8_t *, RecoveredWordInvoker);
std::uint64_t recovered_render_29540(std::uint8_t *, RecoveredWordInvoker);
std::uint64_t recovered_render_29570(std::uint8_t *, RecoveredWordInvoker);
std::uint64_t recovered_render_295a0(std::uint8_t *, RecoveredWordInvoker);
#endif // SLINKY_SHARE_5F2BA658C53BB9714694
