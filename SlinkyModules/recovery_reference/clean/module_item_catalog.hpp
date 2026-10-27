#pragma once

#include <cstdint>

struct ItemCatalogEntry {
    const char *name;
    std::int32_t identifier;
    std::uint32_t reserved;
};
using CatalogCompare = std::int32_t (*)(const void *, const void *);
using CatalogSearch = void *(*)(const void *, const void *, std::uint64_t,
                               std::uint64_t, CatalogCompare);
using CatalogStringCompare = std::int32_t (*)(const char *, const char *);

struct ItemCatalog {
    const ItemCatalogEntry *by_name;
    const ItemCatalogEntry *by_identifier;
    CatalogSearch search;
    CatalogCompare compare_names;
};
static_assert(sizeof(ItemCatalogEntry) == 16);

extern "C" {
__declspec(dllexport) const ItemCatalogEntry *recovered_catalog_by_name();
__declspec(dllexport) const ItemCatalogEntry *recovered_catalog_by_identifier();
__declspec(dllexport) std::int32_t recovered_catalog_find_identifier(
    const char *name, const ItemCatalog *catalog);
__declspec(dllexport) const char *recovered_catalog_find_name(
    std::int32_t identifier, const ItemCatalog *catalog);
__declspec(dllexport) std::int32_t recovered_catalog_name_compare(
    const void *key, const void *candidate, CatalogStringCompare compare);
__declspec(dllexport) std::int32_t recovered_catalog_identifier_compare(
    const void *key, const void *candidate);
}
