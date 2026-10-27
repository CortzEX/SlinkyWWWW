// Native 0x13CFD0 static proof: reports/ProtectedNumericStaticReview.json.
// This source calls the decoded caller-owned service, never a host substitute.
#include "DecodedNumericService.hpp"
#include <cstring>
namespace reconstruction::numeric_service {
std::uint64_t decodedTarget_13cfd0(const std::uint8_t *encodedCell) {
    std::uint64_t encoded;
    std::memcpy(&encoded, encodedCell, sizeof encoded);
    return encoded + pointerAddend_13cfd0;
}
// Native 0x13CFD0 reloads the unaligned cell on each invocation and tail-calls
// the exact external two-double service. The captured current export is
// hypot; startup selection/permanent binding are not inferred from it.
double pairCell_13cfd0(const std::uint8_t *encodedCell, double first, double second) {
    using Endpoint = double (*)(double, double);
    const auto target = decodedTarget_13cfd0(encodedCell);
    return reinterpret_cast<Endpoint>(static_cast<std::uintptr_t>(target))(first, second);
}
double pair_13cfd0(const Context &context, double first, double second) {
    const auto *cell = context.encodedCellOverride ? context.encodedCellOverride
        : context.image + inlineCellRva_13cfd0;
    return pairCell_13cfd0(cell, first, second);
}
std::uint64_t decodedTarget_13cfb0(const std::uint8_t *encodedCell) {
    std::uint64_t encoded;
    std::memcpy(&encoded, encodedCell, sizeof encoded);
    return encoded - pointerSubtract_13cfb0;
}
// Static CFB0 proof establishes the unchanged XMM0/XMM1 tail-call contract.
// The captured export is atan2; this source preserves the supplied exact
// endpoint and reloads its unaligned encoded cell on every invocation.
double directionCell_13cfb0(const std::uint8_t *encodedCell, double first, double second) {
    using Endpoint = double (*)(double, double);
    const auto target = decodedTarget_13cfb0(encodedCell);
    return reinterpret_cast<Endpoint>(static_cast<std::uintptr_t>(target))(first, second);
}
double direction_13cfb0(const Context &context, double first, double second) {
    const auto *cell = context.encodedCellOverride ? context.encodedCellOverride
        : context.image + inlineCellRva_13cfb0;
    return directionCell_13cfb0(cell, first, second);
}
std::uint64_t decodedTarget_13cfa0(const std::uint8_t *encodedCell) {
    std::uint64_t encoded;
    std::memcpy(&encoded, encodedCell, sizeof encoded);
    return encoded - pointerSubtract_13cfa0;
}
// Static CFA0 proof establishes an unchanged XMM0 unary tail-call contract.
// The captured export is acos; startup identity and numerical policy remain
// external. Each call reads the borrowed cell and uses that exact endpoint.
double projectionCell_13cfa0(const std::uint8_t *encodedCell, double value) {
    using Endpoint = double (*)(double);
    const auto target = decodedTarget_13cfa0(encodedCell);
    return reinterpret_cast<Endpoint>(static_cast<std::uintptr_t>(target))(value);
}
double projection_13cfa0(const Context &context, double value) {
    const auto *cell = context.encodedCellOverride ? context.encodedCellOverride
        : context.image + inlineCellRva_13cfa0;
    return projectionCell_13cfa0(cell, value);
}
std::uint64_t decodedTarget_13cfc0(const std::uint8_t *encodedCell) {
    std::uint64_t encoded;
    std::memcpy(&encoded, encodedCell, sizeof encoded);
    return encoded + pointerAddend_13cfc0;
}
float floatDirectionCell_13cfc0(const std::uint8_t *encodedCell, float first, float second) {
    using Endpoint = float (*)(float, float);
    const auto target = decodedTarget_13cfc0(encodedCell);
    return reinterpret_cast<Endpoint>(static_cast<std::uintptr_t>(target))(first, second);
}
float floatDirection_13cfc0(const Context &context, float first, float second) {
    const auto *cell = context.encodedCellOverride ? context.encodedCellOverride
        : context.image + inlineCellRva_13cfc0;
    return floatDirectionCell_13cfc0(cell, first, second);
}
std::uint64_t decodedTarget_13d190(const std::uint8_t *encodedCell) {
    std::uint64_t encoded;
    std::memcpy(&encoded, encodedCell, sizeof encoded);
    return encoded - pointerSubtract_13d190;
}
float floatUnaryCell_13d190(const std::uint8_t *encodedCell, float value) {
    using Endpoint = float (*)(float);
    const auto target = decodedTarget_13d190(encodedCell);
    return reinterpret_cast<Endpoint>(static_cast<std::uintptr_t>(target))(value);
}
float floatUnary_13d190(const Context &context, float value) {
    const auto *cell = context.encodedCellOverride ? context.encodedCellOverride
        : context.image + inlineCellRva_13d190;
    return floatUnaryCell_13d190(cell, value);
}
std::uint64_t decodedTarget_13cfe0(const std::uint8_t *encodedCell) {
    std::uint64_t encoded;
    std::memcpy(&encoded, encodedCell, sizeof encoded);
    return encoded - pointerSubtract_13cfe0;
}
// Native 0x13CFE0: reports/ProtectedBinaryScalarStaticReview.json proves the
// unchanged binary32 XMM0/XMM1 tail contract and exact subtraction. The
// observed external export is powf; each call uses the current borrowed cell.
float binaryScalarCell_13cfe0(const std::uint8_t *encodedCell, float first, float second) {
    using Endpoint = float (*)(float, float);
    const auto target = decodedTarget_13cfe0(encodedCell);
    return reinterpret_cast<Endpoint>(static_cast<std::uintptr_t>(target))(first, second);
}
float binaryScalar_13cfe0(const Context &context, float first, float second) {
    const auto *cell = context.encodedCellOverride ? context.encodedCellOverride
        : context.image + inlineCellRva_13cfe0;
    return binaryScalarCell_13cfe0(cell, first, second);
}
}
