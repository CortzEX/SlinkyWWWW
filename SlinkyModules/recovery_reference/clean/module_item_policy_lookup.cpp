#include "module_item_policy_lookup.hpp"

// 0xdf00 uses unsigned bounds and a wrapping DWORD byte offset.
extern "C" __declspec(dllexport) std::uintptr_t recovered_item_policy_lookup(
    const ItemPolicyTable *table, std::uint32_t identifier) {
    const ItemPolicyEntry key{nullptr, identifier, 0};
    std::uint32_t low = 0, high = table->count;
    std::uintptr_t found = 0;
    while (low < high) {
        const auto middle = low + ((high - low) >> 1);
        const auto offset = middle * std::uint32_t{sizeof(ItemPolicyEntry)};
        const auto *candidate = reinterpret_cast<const ItemPolicyEntry *>(
            reinterpret_cast<std::uintptr_t>(table->entries) + offset);
        const auto order = recovered_item_policy_compare(0, &key, candidate);
        if (order < 0) high = middle;
        else if (order == 0) { found = reinterpret_cast<std::uintptr_t>(candidate); break; }
        else low = middle + 1;
    }
    return (found & ~std::uintptr_t{0xff}) | (found != 0);
}
