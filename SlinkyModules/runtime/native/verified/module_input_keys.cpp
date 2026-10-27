#include "module_input_keys.hpp"
#include <bit>
#include <cstring>

// 0xea80 subtracts DWORDs with wrapping, rather than normalizing their order.
extern "C" __declspec(dllexport) std::int32_t recovered_input_key_compare(
    const void *left, const void *right) {
    std::uint32_t a, b;
    std::memcpy(&a, left, sizeof(a));
    std::memcpy(&b, right, sizeof(b));
    return std::bit_cast<std::int32_t>(a - b);
}

// 0xe870 captures the found row, but reloads its count/contexts and the callback.
extern "C" __declspec(dllexport) std::uint32_t recovered_input_keys(
    InputKeyDispatch *dispatch, std::uint32_t key, std::uint32_t requested, CatalogSearch search) {
    InputKeyRow probe{};
    probe.key = key;
    if (!dispatch->data) return 0;
    auto *row = static_cast<volatile InputKeyRow *>(search(
        &probe, dispatch->data, dispatch->count, sizeof(probe), recovered_input_key_compare));
    if (!row || !row->count) return 0;
    std::uint8_t result = 0;
    std::uint64_t index = 0;
    do {
        result |= dispatch->callback(row->contexts[index], key, requested);
        ++index;
    } while (index < row->count);
    return result & 1;
}

extern "C" __declspec(dllexport) std::uintptr_t recovered_input_bound_keys(
    std::uintptr_t binding, std::uint32_t key, std::uint8_t requested) {
    const auto *state = reinterpret_cast<const InputKeyBinding *>(binding);
    return recovered_input_keys(state->dispatch, key, requested, state->search);
}
