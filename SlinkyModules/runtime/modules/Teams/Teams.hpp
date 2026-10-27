#ifndef SLINKY_SHARE_B61CAA87E171D6E52902
#define SLINKY_SHARE_B61CAA87E171D6E52902
#include "../Aim_Assist/Support.hpp"
#include "../../native/verified/Friends_runtime.hpp"
#include "../../native/verified/module_sorted_table.hpp"
#include "../../native/verified/module_named_lists.hpp"
namespace teams {
std::uint16_t prefixColor(GameAccessBridge *, std::uintptr_t); // 0x28b40
std::uint16_t componentColor(GameAccessBridge *, std::uintptr_t); // 0x28d20
std::uint16_t entityColor(GameAccessBridge *, std::uintptr_t); // 0x28e10
void update(aim_assist::WorldUpdateEvent *, std::uint8_t *);
void disable(aim_assist::StateChangedEvent *, std::uint8_t *);
void cleanup(std::uint8_t *, void (*release)(void *)); // indirect external endpoint cell at native0x13cf70
std::int32_t compare(std::uint64_t, const void *, const void *); // 0x32170
}

namespace teams { void colorNames(std::uint8_t *image,const char *const **table,std::uint64_t *count); } // native0x32430
#endif // SLINKY_SHARE_B61CAA87E171D6E52902
