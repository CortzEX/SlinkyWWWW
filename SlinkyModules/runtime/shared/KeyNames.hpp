#ifndef SLINKY_SHARE_1744212B6B55798FA877
#define SLINKY_SHARE_1744212B6B55798FA877
#include <cstdint>
// Native 9380 uses signed relative DWORDs, key minus one wrapping as DWORD.
const char *recovered_key_name_9380(std::uint32_t key, const std::uint8_t *image);
#endif // SLINKY_SHARE_1744212B6B55798FA877
