#include "DecodedWindowQueryService.hpp"
#include <cstring>

namespace reconstruction::window_service {
Word decodedTarget_103762f(const std::uint8_t *cell) {
    Word encoded;
    std::memcpy(&encoded,cell,sizeof encoded);
    return encoded+pointerAdd_103762f;
}
Word query_103762f(const Context &context) {
    const auto *cell=context.encodedCell ? context.encodedCell
        : context.image+encodedCellRva_103762f;
    return reinterpret_cast<Word (*)()>(
        std::uintptr_t(decodedTarget_103762f(cell)))();
}
}
