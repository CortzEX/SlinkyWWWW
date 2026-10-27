#ifndef SLINKY_SHARE_57F86B54CFF8E179B985
#define SLINKY_SHARE_57F86B54CFF8E179B985
#include "WordInvoker.hpp"
#include <cstddef>
#include <cstdint>

namespace reconstruction::json {
struct Node {
    Node *next;
    Node *previous;
    Node *child;
    std::uint32_t type;
    std::uint32_t typePadding;
    char *valueString;
    std::int32_t valueInteger;
    std::uint32_t integerPadding;
    double valueNumber;
    char *name;
};
static_assert(sizeof(Node)==0x40 && offsetof(Node,type)==0x18 && offsetof(Node,name)==0x38);
struct PrintBuffer {
    char *memory;
    std::uint64_t capacity,offset,depth;
    std::uint32_t noAllocation,formatted;
    std::uint64_t allocate,release,resize;
};
static_assert(sizeof(PrintBuffer)==64 && offsetof(PrintBuffer,formatted)==36);
struct NumberServices {
    void *context;
    // Protected locale provider in native4DEF1 and the CRT format/scan engines.
    std::uint8_t (*decimalPoint)(void *);
    std::int32_t (*format)(void *,char *,const char *,std::uint64_t argumentBits);
    std::uint32_t (*scan)(void *,const char *,const char *,double *);
    double (*parse)(void *,const char *,char **);
};
struct Context {
    std::uint8_t *image;
    RecoveredFrameInvoker external;
    NumberServices numbers{};
    std::uint64_t invoke(std::uint64_t target,const std::uint64_t *,std::size_t);
    RecoveredFrameInvoker frame() { return {this,[](void *p,std::uint64_t target,const std::uint64_t *a,std::size_t n) {
        return static_cast<Context *>(p)->invoke(target,a,n);
    }}; }
};
void deleteTree_4d240(Node *,Context &);
void releaseText_4d3b0(void *,Context &);
std::uint32_t append_4e560(Node *parent,Node *item);
std::uint32_t attachName_4e5b0(Node *,const char *,Node *,Context &);
Node *createObject_4f590(Context &);
Node *writeObject_4f480(Node *,const char *,Context &);
Node *writeArray_4f5d0(Node *,const char *,Context &);
Node *writeBoolean_4ed40(Node *,const char *,std::uint32_t,Context &);
Node *writeNumber_4eeb0(Node *,const char *,double,Context &);
Node *writeString_4f080(Node *,const char *,const char *,Context &);
char *printAllocated_4dad0(Node *,std::uint32_t formatted,Context &);
char *printCompact_4dbe0(Node *,Context &);
char *reserve_51400(PrintBuffer *,std::uint64_t required,Context &);
std::uint32_t printString_514f0(const char *,PrintBuffer *,Context &);
std::uint32_t printValue_4dc80(Node *,PrintBuffer *,Context &);
struct ParseBuffer {
    const std::uint8_t *content;
    std::uint64_t length,offset,depth,allocate,release,resize;
};
static_assert(sizeof(ParseBuffer)==56 && offsetof(ParseBuffer,allocate)==32);
Node *lookup_4e4d0(Node *,const char *,Context &);
std::uint32_t isNumber_4d150(const Node *);
std::uint32_t isTrue_508c0(const Node *);
Node *parse_4da70(const char *,Context &);
Node *parseLength_4d410(const char *,std::uint64_t,const char **,
    std::uint32_t requireTerminator,Context &);
std::uint32_t parseValue_4d600(Node *,ParseBuffer *,Context &);
void skipWhitespace_4da00(ParseBuffer *);
std::uint32_t parseString_50b60(Node *,ParseBuffer *,Context &);
std::uint32_t parseObject_51000(Node *,ParseBuffer *,Context &);
std::uint32_t parseHex_51310(const std::uint8_t *);
}
#endif // SLINKY_SHARE_57F86B54CFF8E179B985
