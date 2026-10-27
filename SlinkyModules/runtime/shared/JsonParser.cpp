#include "JsonRuntime.hpp"
#include "ByteStrings.hpp"
#include <array>
#include <bit>
#include <cstring>
#include <emmintrin.h>

namespace reconstruction::json {
namespace {
using Word=std::uint64_t;
Word address(const void *p) { return reinterpret_cast<Word>(p); }
template<class T> T load(const std::uint8_t *p,std::size_t at) { T v;std::memcpy(&v,p+at,sizeof v);return v; }
template<class T> void store(std::uint8_t *p,std::size_t at,T v) { std::memcpy(p+at,&v,sizeof v); }
Node *newItem(Word allocator,Context &c) {
    auto *item=reinterpret_cast<Node *>(c.external(allocator,0x40));
    if(item) {
        const auto zero=_mm_setzero_si128();auto *p=reinterpret_cast<std::uint8_t *>(item);
        for(auto at:{0x30,0x20,0x10,0}) _mm_storeu_si128(reinterpret_cast<__m128i *>(p+at),zero);
    }
    return item;
}
bool accessible(const ParseBuffer *b) { return b->offset<b->length; }
std::uint32_t parseArray(Node *item,ParseBuffer *b,Context &c) {
    if(b->depth>999) return 0;
    ++b->depth;
    if(b->content[b->offset]!='[') return 0;
    ++b->offset;skipWhitespace_4da00(b);
    if(!accessible(b)) { --b->offset;return 0; }
    if(b->content[b->offset]==']') {
        --b->depth;item->type=32;item->child=nullptr;++b->offset;return 1;
    }
    --b->offset;
    Node *head=nullptr,*tail=nullptr;
    do {
        auto *next=newItem(b->allocate,c);
        if(!next) { if(head) deleteTree_4d240(head,c);return 0; }
        if(tail) { tail->next=next;next->previous=tail; } else head=next;
        tail=next;
        ++b->offset;skipWhitespace_4da00(b);
        if(!parseValue_4d600(next,b,c)) break;
        skipWhitespace_4da00(b);
        if(!accessible(b)) break;
        const auto current=b->content[b->offset];
        if(current==',') continue;
        if(current==']') {
            --b->depth;head->previous=tail;item->type=32;item->child=head;++b->offset;return 1;
        }
        break;
    } while(true);
    deleteTree_4d240(head,c);return 0;
}
}
Node *lookup_4e4d0(Node *parent,const char *name,Context &c) {
    if(!parent || !name) return nullptr;
    auto *child=parent->child;
    while(child) {
        if(!child->name) return nullptr;
        if(std::uint32_t(c.external(0x13d0a0,address(name),address(child->name)))==0) return child;
        child=child->next;
    }
    return nullptr;
}
std::uint32_t isNumber_4d150(const Node *item) { return item && std::uint8_t(item->type)==8; }
std::uint32_t isTrue_508c0(const Node *item) { return item && std::uint8_t(item->type)==2; }
void skipWhitespace_4da00(ParseBuffer *b) {
    if(!b || !b->content || b->offset>=b->length) return;
    while(b->offset<b->length && b->content[b->offset]<=32) ++b->offset;
    if(b->offset==b->length) --b->offset;
}
Node *parse_4da70(const char *text,Context &c) {
    if(!text) return nullptr;
    return parseLength_4d410(text,recovered_string_length_ab840(reinterpret_cast<const std::uint8_t *>(text))+1,nullptr,0,c);
}
Node *parseLength_4d410(const char *text,Word length,const char **end,std::uint32_t requireTerminator,Context &c) {
    ParseBuffer buffer{};
    store<Word>(c.image,0x304bd8,0);store<Word>(c.image,0x304be0,0);
    Node *item=nullptr;
    if(text && length) {
        buffer={reinterpret_cast<const std::uint8_t *>(text),length,0,0,
            load<Word>(c.image,0x2f6370),load<Word>(c.image,0x2f6378),load<Word>(c.image,0x2f6380)};
        item=newItem(load<Word>(c.image,0x2f6370),c);
        if(item) {
            if(length>=5 && buffer.content[0]==0xef && buffer.content[1]==0xbb && buffer.content[2]==0xbf) buffer.offset=3;
            skipWhitespace_4da00(&buffer);
            if(parseValue_4d600(item,&buffer,c)) {
                if(requireTerminator) skipWhitespace_4da00(&buffer);
                if(!requireTerminator || (buffer.offset<buffer.length && buffer.content[buffer.offset]==0)) {
                    if(end) *end=reinterpret_cast<const char *>(buffer.content+buffer.offset);
                    return item;
                }
            }
            deleteTree_4d240(item,c);
        }
    }
    if(text) {
        const auto position=buffer.offset<buffer.length ? buffer.offset : (buffer.length ? buffer.length-1 : 0);
        if(end) *end=text+position;
        store(c.image,0x304bd8,address(text));store(c.image,0x304be0,position);
    }
    return nullptr;
}
std::uint32_t parseHex_51310(const std::uint8_t *p) {
    std::uint32_t value=0;
    for(unsigned i=0;i<4;++i) {
        const auto ch=p[i];std::uint32_t digit;
        if(std::uint8_t(ch-'0')<10) digit=ch-'0';
        else if(std::uint8_t(ch-'A')<6) digit=ch-'A'+10;
        else if(std::uint8_t(ch-'a')<6) digit=ch-'a'+10;
        else return 0;
        value=(value<<4)+digit;
    }
    return value;
}
std::uint32_t parseString_50b60(Node *item,ParseBuffer *b,Context &c) {
    auto *input=b->content+b->offset+1;
    const auto *quote=b->content+b->offset;
    const auto fail=[&]() { b->offset=Word(input-b->content);return 0u; };
    if(*quote!='"' || b->offset+1>=b->length) return fail();
    const auto *end=input;Word skipped=0;
    while(Word(end-b->content)<b->length && *end!='"') {
        if(*end=='\\') {
            if(Word(end-b->content)+1>=b->length) return fail();
            ++end;++skipped;
        }
        ++end;
    }
    if(Word(end-b->content)>=b->length) return fail();
    auto *output=reinterpret_cast<std::uint8_t *>(c.external(b->allocate,Word(end-quote)-skipped+1));
    if(!output) return fail();
    auto *cursor=output;
    while(input<end) {
        if(*input!='\\') { *cursor++=*input++;continue; }
        Word consumed=2;std::uint32_t code;
        switch(input[1]) {
        case 'b':*cursor++=8;break;
        case 'f':*cursor++=12;break;
        case 'n':*cursor++=10;break;
        case 'r':*cursor++=13;break;
        case 't':*cursor++=9;break;
        case '"':case '\\':case '/':*cursor++=input[1];break;
        case 'u':
            if(Word(end-input)<6) goto failure;
            code=parseHex_51310(input+2);consumed=6;
            if((code&0xfc00u)==0xdc00u) goto failure;
            if((code&0xfc00u)==0xd800u) {
                if(Word(end-input)<12 || input[6]!='\\' || input[7]!='u') goto failure;
                const auto second=parseHex_51310(input+8);
                if(second-0xe000u<0xfffffc00u) goto failure;
                code=((code&0x3ffu)<<10)+(second&0x3ffu)+0x10000u;consumed=12;
            }
            if(code<0x80) *cursor++=std::uint8_t(code);
            else {
                const unsigned width=code<0x800 ? 2 : code<0x10000 ? 3 : 4;
                if(code>0x10ffff) goto failure;
                auto rest=code;
                for(unsigned index=width-1;index!=0;--index) { cursor[index]=std::uint8_t(rest&0x3f)|0x80;rest>>=6; }
                cursor[0]=std::uint8_t(rest)|(width==2 ? 0xc0 : width==3 ? 0xe0 : 0xf0);cursor+=width;
            }
            break;
        default:goto failure;
        }
        input+=consumed;
    }
    *cursor=0;item->type=16;item->valueString=reinterpret_cast<char *>(output);
    b->offset=Word(end-b->content)+1;return 1;
failure:
    c.external(b->release,address(output));return fail();
}
std::uint32_t parseObject_51000(Node *item,ParseBuffer *b,Context &c) {
    if(b->depth>999) return 0;
    ++b->depth;
    if(!accessible(b) || b->content[b->offset]!='{') return 0;
    ++b->offset;skipWhitespace_4da00(b);
    if(!accessible(b)) { --b->offset;return 0; }
    if(b->content[b->offset]=='}') {
        --b->depth;item->type=64;item->child=nullptr;++b->offset;return 1;
    }
    --b->offset;Node *head=nullptr,*tail=nullptr;
    do {
        auto *next=newItem(b->allocate,c);
        if(!next) { if(head) deleteTree_4d240(head,c);return 0; }
        if(tail) { tail->next=next;next->previous=tail; } else head=next;
        tail=next;++b->offset;skipWhitespace_4da00(b);
        if(!parseString_50b60(next,b,c)) break;
        skipWhitespace_4da00(b);next->name=next->valueString;next->valueString=nullptr;
        if(!accessible(b) || b->content[b->offset]!=':') break;
        ++b->offset;skipWhitespace_4da00(b);
        if(!parseValue_4d600(next,b,c)) break;
        skipWhitespace_4da00(b);
        if(!accessible(b)) break;
        const auto current=b->content[b->offset];
        if(current==',') continue;
        if(current=='}') {
            --b->depth;head->previous=tail;item->type=64;item->child=head;++b->offset;return 1;
        }
        break;
    } while(true);
    deleteTree_4d240(head,c);return 0;
}
std::uint32_t parseValue_4d600(Node *item,ParseBuffer *b,Context &c) {
    if(!b || !b->content) return 0;
    const auto *content=b->content;const auto length=b->length,offset=b->offset;
    const auto literal=[&](Word width,std::size_t rva) {
        return offset+width<=length && std::uint32_t(c.external(0x13d110,address(content+offset),address(c.image+rva),width))==0;
    };
    if(literal(4,0x15766d)) { item->type=4;b->offset=offset+4;return 1; }
    if(literal(5,0x157672)) { item->type=1;b->offset=offset+5;return 1; }
    if(literal(4,0x157678)) { item->type=2;item->valueInteger=1;b->offset=offset+4;return 1; }
    if(offset>=length) return 0;
    const auto ch=content[offset];
    if(ch=='"') return parseString_50b60(item,b,c);
    if(ch=='{' ) return parseObject_51000(item,b,c);
    if(ch=='[') return parseArray(item,b,c);
    if(ch!='-' && std::uint8_t(ch-'0')>=10) return 0;
    // Native obtains the locale before reloading the input buffer and copies
    // at most 63 number bytes into its local conversion buffer.
    const auto decimal=c.numbers.decimalPoint(c.numbers.context);
    if(!b->content) return 0;
    std::array<char,64> number{};Word count=0;
    while(count<63 && b->offset+count<b->length) {
        const auto current=b->content[b->offset+count];
        if(current>='0' && current<='9') number[count]=char(current);
        else if(current=='+' || current=='-' || current=='e' || current=='E') number[count]=char(current);
        else if(current=='.') number[count]=char(decimal);
        else break;
        ++count;
    }
    char *end=nullptr;const auto value=c.numbers.parse(c.numbers.context,number.data(),&end);
    if(end==number.data()) return 0;
    item->valueNumber=value;
    if(value>=load<double>(c.image,0x157078)) item->valueInteger=0x7fffffff;
    else if(load<double>(c.image,0x157080)>=value) item->valueInteger=std::bit_cast<std::int32_t>(0x80000000u);
    else item->valueInteger=_mm_cvttsd_si32(_mm_set_sd(value));
    item->type=8;b->offset+=Word(end-number.data());return 1;
}
}
