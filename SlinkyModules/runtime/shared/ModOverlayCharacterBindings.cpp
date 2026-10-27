// Static captured evidence proves a resolver returning the decoded engine in
// R15. This C++ API represents that output; it does not replay protected code.
#include "ModOverlayCharacterBindings.hpp"
#include <cstring>

namespace reconstruction::overlay_character {
std::uint64_t decodedTarget_32ecfb(const std::uint8_t *encodedCell) {
    std::uint64_t word;
    std::memcpy(&word, encodedCell, sizeof word);
    return word + pointerAdd_32ecfb;
}
Endpoint resolve_32ecfb(const Context &context) {
    const auto *cell = context.encodedCellOverride ? context.encodedCellOverride
        : context.image + inlineCellRva_32ecfb;
    return reinterpret_cast<Endpoint>(std::uintptr_t(decodedTarget_32ecfb(cell)));
}
// The BB8F39 actual 34F69/34F6A frame returns the same cell target in RBX.
// Its extra saved-RAX slot and +1 continuation remain static proof facts.
Endpoint resolve_bb8f39(const Context &context) {
    return resolve_32ecfb(context);
}
// Actual collectModules 34194 resolves into R12 before its zero-length branch.
// The original length flags and compensated POP remain static frame facts.
Endpoint resolve_e6314d(const Context &context) {
    return resolve_32ecfb(context);
}
// Actual collectModules 34245 tail-dispatches each status byte and adjusts
// its saved return by +1. The captured cell is reloaded on every invocation.
std::int32_t character_e28595(const Context &context, std::int32_t character) {
    return resolve_32ecfb(context)(character);
}
}
