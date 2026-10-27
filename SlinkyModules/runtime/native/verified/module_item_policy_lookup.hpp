#ifndef SLINKY_SHARE_BFF161A83EE1A1D3EA3E
#define SLINKY_SHARE_BFF161A83EE1A1D3EA3E
#include "module_item_lists.hpp"

// 0x2ac60 preserves the found pointer's upper bytes and replaces AL with a Boolean.
extern "C" __declspec(dllexport) std::uintptr_t recovered_item_policy_lookup(
    const ItemPolicyTable *, std::uint32_t identifier);
#endif // SLINKY_SHARE_BFF161A83EE1A1D3EA3E
