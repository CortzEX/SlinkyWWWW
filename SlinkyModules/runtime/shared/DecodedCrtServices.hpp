#ifndef SLINKY_SHARE_02C8FFB888985EB80A57
#define SLINKY_SHARE_02C8FFB888985EB80A57
// Captured string, search, sort, clock and registration dispatches. Frame
// proofs are in ProtectedCopy/Search/Sort/Compare/Clock/RegistrationStaticReview.
#include <cstdint>
namespace reconstruction::crt_service {
using Compare = std::int32_t (*)(const void *, const void *);
struct Context {
    const std::uint8_t *image;
    const std::uint8_t *copyCell = nullptr;
    const std::uint8_t *searchCell = nullptr;
    const std::uint8_t *sortCell = nullptr;
    const std::uint8_t *compareCell = nullptr;
    const std::uint8_t *clockCell = nullptr;
    const std::uint8_t *registrationCell = nullptr;
};
inline constexpr std::uint64_t copyCellRva = 0xb02390;
inline constexpr std::uint64_t copySubtract = 0x2b487396;
inline constexpr std::uint64_t searchCellRva = 0x1082312;
inline constexpr std::uint64_t searchAdd = 0x481b1dcf;
inline constexpr std::uint64_t sortCellRva = 0xea2361;
inline constexpr std::uint64_t sortSubtract = 0x1e5013d4;
inline constexpr std::uint64_t compareCellRva = 0xb5f1fa;
inline constexpr std::uint64_t compareAdd = 0x6f098693;
inline constexpr std::uint64_t clockCellRva = 0xad4fb0;
inline constexpr std::uint64_t clockSubtract = 0x4e49c46c;
inline constexpr std::uint64_t registrationCellRva = 0xbb32b0;
inline constexpr std::uint64_t registrationSubtract = 0x356c00f6;
std::uint64_t decodedCopyTarget(const std::uint8_t *);
std::uint64_t decodedSearchTarget(const std::uint8_t *);
std::uint64_t decodedSortTarget(const std::uint8_t *);
std::uint64_t decodedCompareTarget(const std::uint8_t *);
std::uint64_t decodedClockTarget(const std::uint8_t *);
std::uint64_t decodedRegistrationTarget(const std::uint8_t *);
char *copy_13d0b0(const Context &,char *destination,const char *source,std::uint64_t count);
void *search_13d0e0(const Context &,const void *key,const void *array,
    std::uint64_t count,std::uint64_t stride,Compare);
void sort_13d0f0(const Context &,void *array,std::uint64_t count,std::uint64_t stride,Compare);
std::int32_t compare_13d0a0(const Context &,const char *first,const char *second);
std::int64_t clock_13d0d0(const Context &,std::int64_t *output);
using ExitCallback=std::int32_t (*)();
std::int32_t registerExit_13d030(const Context &,void *table,ExitCallback);
// The comparator is an actual C callable address supplied by the caller.
// Recovered native RVA tokens need an explicit bridge before using this API.
// Stateful normalized comparators retain their explicit context boundary.
}
#endif // SLINKY_SHARE_02C8FFB888985EB80A57
