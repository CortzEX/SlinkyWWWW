#include "module_item_catalog.hpp"

#include <bit>
#include <cstring>

template <class T>
static T read(const void *pointer) {
    T value;
    std::memcpy(&value, pointer, sizeof(value));
    return value;
}

// Original 0xe3c0 and 0xe420 search 385 records at 0x2e5c20 and 0x2e7430.
// The caller supplies those tables with their name pointers relocated.
extern "C" __declspec(dllexport) std::int32_t recovered_catalog_find_identifier(
    const char *name, const ItemCatalog *catalog) {
    const auto *entry = static_cast<const std::uint8_t *>(
        catalog->search(&name, catalog->by_name, 385, 16, catalog->compare_names));
    return entry ? read<std::int32_t>(entry + 8) : -1;
}

extern "C" __declspec(dllexport) const char *recovered_catalog_find_name(
    std::int32_t identifier, const ItemCatalog *catalog) {
    const auto *entry = catalog->search(&identifier, catalog->by_identifier, 385, 16,
                                      recovered_catalog_identifier_compare);
    return entry ? read<const char *>(entry) : nullptr;
}

// The native name adapter at 0xe410 tail-calls the external string comparator.
extern "C" __declspec(dllexport) std::int32_t recovered_catalog_name_compare(
    const void *key, const void *candidate, CatalogStringCompare compare) {
    return compare(read<const char *>(key), read<const char *>(candidate));
}

extern "C" __declspec(dllexport) std::int32_t recovered_catalog_identifier_compare(
    const void *key, const void *candidate) {
    const auto identifier = read<std::uint32_t>(key);
    const auto candidate_identifier = read<std::uint32_t>(
        static_cast<const std::uint8_t *>(candidate) + 8);
    return std::bit_cast<std::int32_t>(identifier - candidate_identifier);
}
