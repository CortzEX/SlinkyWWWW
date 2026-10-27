// Recovered mutable-cell dispatch for DCDBE0; captured target ShellExecuteW.
// The original saved-frame effects have a separate fixed static proof.
#include "DecodedDirectoryService.hpp"
#include <cstring>

namespace reconstruction::directory_service {
Word decodedTarget_dcdbe0(const std::uint8_t *cell) {
    Word encoded;
    std::memcpy(&encoded,cell,sizeof encoded);
    return encoded-pointerSubtract_dcdbe0;
}
Word execute_dcdbe0(const Context &context,Word owner,const std::uint16_t *operation,
    const std::uint16_t *path,Word parameters,Word directory,std::uint32_t show) {
    const auto *cell=context.encodedCell ? context.encodedCell
        : context.image+encodedCellRva_dcdbe0;
    using Engine = Word (*)(Word,const std::uint16_t *,const std::uint16_t *,Word,Word,std::uint32_t);
    return reinterpret_cast<Engine>(std::uintptr_t(decodedTarget_dcdbe0(cell)))(
        owner,operation,path,parameters,directory,show);
}
}
