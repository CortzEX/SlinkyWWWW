#ifndef SLINKY_SHARE_8D7E01BCA52C3F7BBEC1
#define SLINKY_SHARE_8D7E01BCA52C3F7BBEC1
#include "module_list_settings.hpp"
#include <cstdint>

struct EspListTable {
    std::uint64_t count;
    std::uint64_t capacity;
    std::uint8_t *records;
};
static_assert(sizeof(EspListTable) == 24);

using EspListCompare = std::int32_t (*)(const void *, const void *);
struct EspListDependencies {
    std::int32_t (*find_identifier)(const char *);
    const char *(*find_name)(std::int32_t);
    void *(*search)(std::int32_t *, void *, std::uint64_t, std::uint64_t, EspListCompare);
    std::uint32_t (*grow)(std::uint8_t **, std::uint64_t, std::uint64_t, std::uint64_t *);
    void *(*move)(void *, const void *, std::uint64_t);
    void (*release)(void *);
};
struct EspListState {
    std::uint8_t *image;
    EspListTable *table;
    const EspListDependencies *dependencies;
};

extern "C" {
__declspec(dllexport) std::uint64_t recovered_esp_list_count(const EspListTable *);
__declspec(dllexport) const char *recovered_esp_list_name(const EspListTable *, std::uint64_t);
__declspec(dllexport) float *recovered_esp_list_color(const EspListTable *, std::uint64_t);
__declspec(dllexport) std::int32_t recovered_esp_list_compare(const void *, const void *);
__declspec(dllexport) std::uint32_t recovered_block_esp_list_add(
    EspListTable *, std::uint8_t *, const char *, const float *, const EspListDependencies *);
__declspec(dllexport) std::uint32_t recovered_item_esp_list_add(
    EspListTable *, std::uint8_t *, const char *, const float *, const EspListDependencies *);
__declspec(dllexport) void recovered_block_esp_list_remove(
    EspListTable *, std::uint8_t *, std::uint64_t, const EspListDependencies *);
__declspec(dllexport) void *recovered_item_esp_list_remove(
    EspListTable *, std::uint64_t, const EspListDependencies *);
__declspec(dllexport) void recovered_block_esp_list_clear(
    EspListTable *, std::uint8_t *, const EspListDependencies *);
__declspec(dllexport) void recovered_item_esp_list_clear(EspListTable *, const EspListDependencies *);
__declspec(dllexport) void recovered_bind_block_esp_list(ListSetting *, EspListState *);
__declspec(dllexport) void recovered_bind_item_esp_list(ListSetting *, EspListState *);
}
#endif // SLINKY_SHARE_8D7E01BCA52C3F7BBEC1
