#include "DecodedCrtServices.hpp"
#include <cstring>
namespace reconstruction::crt_service {
namespace {
std::uint64_t word(const std::uint8_t *cell) {
    std::uint64_t value;
    std::memcpy(&value,cell,sizeof value);
    return value;
}
const std::uint8_t *cell(const Context &context,const std::uint8_t *overrideCell,std::uint64_t rva) {
    return overrideCell ? overrideCell : context.image+rva;
}
}
std::uint64_t decodedCopyTarget(const std::uint8_t *cell) {return word(cell)-copySubtract;}
std::uint64_t decodedSearchTarget(const std::uint8_t *cell) {return word(cell)+searchAdd;}
std::uint64_t decodedSortTarget(const std::uint8_t *cell) {return word(cell)-sortSubtract;}
std::uint64_t decodedCompareTarget(const std::uint8_t *cell) {return word(cell)+compareAdd;}
std::uint64_t decodedClockTarget(const std::uint8_t *cell) {return word(cell)-clockSubtract;}
std::uint64_t decodedRegistrationTarget(const std::uint8_t *cell) {return word(cell)-registrationSubtract;}
char *copy_13d0b0(const Context &context,char *destination,const char *source,std::uint64_t count) {
    using Endpoint=char *(*)(char *,const char *,std::uint64_t);
    const auto target=decodedCopyTarget(cell(context,context.copyCell,copyCellRva));
    return reinterpret_cast<Endpoint>(std::uintptr_t(target))(destination,source,count);
}
void *search_13d0e0(const Context &context,const void *key,const void *array,
                    std::uint64_t count,std::uint64_t stride,Compare compare) {
    using Endpoint=void *(*)(const void *,const void *,std::uint64_t,std::uint64_t,Compare);
    const auto target=decodedSearchTarget(cell(context,context.searchCell,searchCellRva));
    return reinterpret_cast<Endpoint>(std::uintptr_t(target))(key,array,count,stride,compare);
}
void sort_13d0f0(const Context &context,void *array,std::uint64_t count,std::uint64_t stride,Compare compare) {
    using Endpoint=void (*)(void *,std::uint64_t,std::uint64_t,Compare);
    const auto target=decodedSortTarget(cell(context,context.sortCell,sortCellRva));
    reinterpret_cast<Endpoint>(std::uintptr_t(target))(array,count,stride,compare);
}
std::int32_t compare_13d0a0(const Context &context,const char *first,const char *second) {
    using Endpoint=std::int32_t (*)(const char *,const char *);
    const auto target=decodedCompareTarget(cell(context,context.compareCell,compareCellRva));
    return reinterpret_cast<Endpoint>(std::uintptr_t(target))(first,second);
}
std::int64_t clock_13d0d0(const Context &context,std::int64_t *output) {
    using Endpoint=std::int64_t (*)(std::int64_t *);
    const auto target=decodedClockTarget(cell(context,context.clockCell,clockCellRva));
    return reinterpret_cast<Endpoint>(std::uintptr_t(target))(output);
}
std::int32_t registerExit_13d030(const Context &context,void *table,ExitCallback callback) {
    using Endpoint=std::int32_t (*)(void *,ExitCallback);
    const auto target=decodedRegistrationTarget(cell(context,context.registrationCell,registrationCellRva));
    return reinterpret_cast<Endpoint>(std::uintptr_t(target))(table,callback);
}
}
