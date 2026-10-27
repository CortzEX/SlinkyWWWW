#pragma once
#include "module_item_catalog.hpp"
#include <cstddef>

using InputKeyCallback = std::uint8_t (*)(std::uintptr_t, std::uint32_t, std::uint32_t);
struct InputKeyRow {
    std::uint32_t key, reserved;
    std::uint64_t count, capacity;
    std::uintptr_t *contexts;
};
struct InputKeyDispatch {
    InputKeyCallback callback;
    std::uintptr_t reserved;
    std::uint64_t count, capacity;
    InputKeyRow *data;
};
static_assert(sizeof(InputKeyRow) == 32);
static_assert(sizeof(InputKeyDispatch) == 40);
static_assert(offsetof(InputKeyRow, contexts) == 24);
struct InputKeyBinding { InputKeyDispatch *dispatch; CatalogSearch search; };
static_assert(sizeof(InputKeyBinding) == 16);
extern "C" {
__declspec(dllexport) std::int32_t recovered_input_key_compare(const void *, const void *);
__declspec(dllexport) std::uint32_t recovered_input_keys(
    InputKeyDispatch *, std::uint32_t key, std::uint32_t requested, CatalogSearch);
__declspec(dllexport) std::uintptr_t recovered_input_bound_keys(
    std::uintptr_t binding, std::uint32_t key, std::uint8_t requested);
}
