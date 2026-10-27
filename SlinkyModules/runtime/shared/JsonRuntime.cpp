#include "JsonRuntime.hpp"
#include "ByteStrings.hpp"
#include "../native/verified/module_memory.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <cstring>
#include <emmintrin.h>

namespace reconstruction::json {
namespace {
using Word=std::uint64_t;
Word address(const void *p) { return reinterpret_cast<Word>(p); }
template<class T> T load(const std::uint8_t *image,std::size_t rva) { T v;std::memcpy(&v,image+rva,sizeof v);return v; }
Word cell(Context &c,std::size_t rva) { return load<Word>(c.image,rva); }
void *allocate(Context &c,Word size) { return reinterpret_cast<void *>(c.external(cell(c,0x2f6370),size)); }
void release(Context &c,void *p) { c.external(cell(c,0x2f6378),address(p)); }
Node *create(std::uint32_t type,Context &c) {
    auto *item=static_cast<Node *>(allocate(c,0x40));
    if(!item) return nullptr;
    const auto zero=_mm_setzero_si128();
    auto *bytes=reinterpret_cast<std::uint8_t *>(item);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(bytes+0x10),zero);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(bytes+0x30),zero);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(bytes+0x20),zero);
    _mm_storeu_si128(reinterpret_cast<__m128i *>(bytes),zero);
    item->type=type;
    return item;
}
char *duplicate(const char *s,Context &c) {
    const auto size=recovered_string_length_ab840(reinterpret_cast<const std::uint8_t *>(s))+1;
    auto *copy=static_cast<char *>(allocate(c,size));
    if(copy) recovered_memory_move(copy,s,std::size_t(size));
    return copy;
}
Node *finishNamed(Node *parent,const char *name,Node *item,Context &c) {
    if(attachName_4e5b0(parent,name,item,c)) return item;
    deleteTree_4d240(item,c);
    return nullptr;
}
}
void deleteTree_4d240(Node *item,Context &c) {
    while(item) {
        auto *current=item;
        item=current->next;
        auto flags=current->type;
        if(!(flags&0x100) && current->child) {
            deleteTree_4d240(current->child,c);
            flags=current->type;
        }
        if(!(flags&0x100) && current->valueString) {
            release(c,current->valueString);
            flags=current->type;
        }
        if(!(flags&0x200) && current->name) release(c,current->name);
        release(c,current);
    }
}
void releaseText_4d3b0(void *text,Context &c) { release(c,text); }
std::uint32_t append_4e560(Node *parent,Node *item) {
    if(parent==item || !parent || !item) return 0;
    auto *head=parent->child;
    if(!head) {
        parent->child=item;
        item->previous=item;
        item->next=nullptr;
    } else if(auto *tail=head->previous) {
        tail->next=item;
        item->previous=tail;
        head->previous=item;
    }
    // An existing head with a null tail returns success without linking item.
    return 1;
}
std::uint32_t attachName_4e5b0(Node *parent,const char *name,Node *item,Context &c) {
    if(parent==item || !parent || !name || !item) return 0;
    auto *copy=duplicate(name,c);
    if(!copy) return 0;
    const auto flags=item->type & ~std::uint32_t{0x200};
    if(!(item->type&0x200) && item->name) release(c,item->name);
    item->name=copy;
    item->type=flags;
    return append_4e560(parent,item);
}
Node *createObject_4f590(Context &c) { return create(0x40,c); }
Node *writeObject_4f480(Node *parent,const char *name,Context &c) { return finishNamed(parent,name,create(0x40,c),c); }
Node *writeArray_4f5d0(Node *parent,const char *name,Context &c) { return finishNamed(parent,name,create(0x20,c),c); }
Node *writeBoolean_4ed40(Node *parent,const char *name,std::uint32_t value,Context &c) {
    return finishNamed(parent,name,create(value<1u ? 1u : 2u,c),c);
}
Node *writeNumber_4eeb0(Node *parent,const char *name,double value,Context &c) {
    auto *item=create(8,c);
    if(item) {
        item->valueNumber=value;
        std::int32_t integer=0x7fffffff;
        if(!(value>=load<double>(c.image,0x157290))) {
            integer=std::bit_cast<std::int32_t>(0x80000000u);
            if(!(load<double>(c.image,0x157298)>=value)) integer=_mm_cvttsd_si32(_mm_set_sd(value));
        }
        item->valueInteger=integer;
    }
    return finishNamed(parent,name,item,c);
}
Node *writeString_4f080(Node *parent,const char *name,const char *value,Context &c) {
    auto *item=create(0x10,c);
    if(item) {
        auto *copy=value ? duplicate(value,c) : nullptr;
        item->valueString=copy;
        if(!copy) { deleteTree_4d240(item,c);item=nullptr; }
    }
    return finishNamed(parent,name,item,c);
}
char *printAllocated_4dad0(Node *root,std::uint32_t formatted,Context &c) {
    // Native print-buffer layout: pointer/capacity/offset/depth/noalloc/format
    // followed by a snapshot of the three allocator cells.
    alignas(16) std::array<std::uint8_t,64> buffer{};
    const auto store=[&]<class T>(std::size_t at,T v) { std::memcpy(buffer.data()+at,&v,sizeof v); };
    auto *initial=static_cast<char *>(allocate(c,0x100));
    store(0,address(initial));store(8,Word{0x100});store(36,formatted);
    const auto allocator=cell(c,0x2f6370),deallocator=cell(c,0x2f6378),resizer=cell(c,0x2f6380);
    store(40,allocator);store(48,deallocator);store(56,resizer);
    if(!initial) return nullptr;
    if(!std::uint32_t(c.frame()(0x4dc80,address(root),address(buffer.data())))) goto failure;
    {
        auto *old=reinterpret_cast<char *>(load<Word>(buffer.data(),0));
        auto offset=load<Word>(buffer.data(),16);
        if(old) { offset+=recovered_string_length_ab840(reinterpret_cast<const std::uint8_t *>(old+offset));store(16,offset); }
        // Native reloads the global resizer after printing, rather than using
        // the buffer's earlier snapshot for this final shrink.
        if(const auto resize=cell(c,0x2f6380)) {
            auto *result=reinterpret_cast<char *>(c.external(resize,address(old),offset+1));
            if(result) return result;
            goto failure;
        }
        auto *result=static_cast<char *>(allocate(c,offset+1));
        if(!result) goto failure;
        const auto capacity=load<Word>(buffer.data(),8);
        recovered_memory_move(result,reinterpret_cast<const void *>(load<Word>(buffer.data(),0)),std::size_t(std::min(capacity,offset+1)));
        result[offset]=0;
        release(c,reinterpret_cast<void *>(load<Word>(buffer.data(),0)));
        return result;
    }
failure:
    if(auto *memory=reinterpret_cast<void *>(load<Word>(buffer.data(),0))) release(c,memory);
    return nullptr;
}
char *printCompact_4dbe0(Node *root,Context &c) { return printAllocated_4dad0(root,0,c); }
char *reserve_51400(PrintBuffer *buffer,Word required,Context &c) {
    auto *old=buffer->memory;
    if(!old) return nullptr;
    const auto capacity=buffer->capacity;
    if((capacity && buffer->offset>=capacity) || required>0x7fffffff) return nullptr;
    auto size=required+buffer->offset+1;
    if(size<=capacity) return old+buffer->offset;
    if(buffer->noAllocation) return nullptr;
    if(size>=0x40000000) {
        if(size>>31) return nullptr;
        size=0x7fffffff;
    } else size*=2;
    char *next;
    if(const auto resize=buffer->resize) {
        next=reinterpret_cast<char *>(c.external(resize,address(old),size));
    } else {
        next=reinterpret_cast<char *>(c.external(buffer->allocate,size));
        if(next) {
            recovered_memory_move(next,buffer->memory,std::size_t(buffer->offset+1));
            c.external(buffer->release,address(buffer->memory));
        }
    }
    if(!next) {
        c.external(buffer->release,address(buffer->memory));
        buffer->memory=nullptr;buffer->capacity=0;
        return nullptr;
    }
    buffer->capacity=size;buffer->memory=next;
    return next+buffer->offset;
}
std::uint32_t printString_514f0(const char *string,PrintBuffer *buffer,Context &c) {
    if(!string) {
        auto *out=reserve_51400(buffer,3,c);
        if(!out) return 0;
        out[2]=0;out[0]='"';out[1]='"';return 1;
    }
    Word length=0,extra=0;
    constexpr Word shortEscapes=0x400003700;
    for(;;++length) {
        const auto byte=std::uint8_t(string[length]);
        if(byte<=0x22 && ((shortEscapes>>byte)&1)) { ++extra;continue; }
        if(!byte) break;
        if(byte==0x5c) ++extra;
        else if(byte<0x20) extra+=5;
    }
    auto *out=reserve_51400(buffer,length+extra+3,c);
    if(!out) return 0;
    out[0]='"';
    if(!extra) recovered_memory_move(out+1,string,std::size_t(length));
    else {
        auto *cursor=out;
        for(const auto *input=reinterpret_cast<const std::uint8_t *>(string);*input;++input) {
            const auto byte=*input;
            if(byte>=0x20 && byte!=0x22 && byte!=0x5c) { *++cursor=char(byte);continue; }
            cursor[1]='\\';
            const auto emit=[&](char value) { cursor[2]=value;cursor+=2; };
            switch(byte) {
            case 8:emit('b');break;case 9:emit('t');break;case 10:emit('n');break;
            case 12:emit('f');break;case 13:emit('r');break;case 34:emit('"');break;case 92:emit('\\');break;
            default:
                // The captured formatter writes u%04x after the backslash.
                c.numbers.format(c.numbers.context,cursor+2,reinterpret_cast<const char *>(c.image+0x157695),byte);
                cursor+=6;break;
            }
        }
    }
    out[length+extra+1]='"';out[length+extra+2]=0;
    return 1;
}
namespace {
void updateOffset(PrintBuffer *buffer) {
    if(buffer->memory) buffer->offset+=recovered_string_length_ab840(
        reinterpret_cast<const std::uint8_t *>(buffer->memory+buffer->offset));
}
std::uint32_t printNumber(Node *item,PrintBuffer *buffer,Context &c) {
    const auto value=item->valueNumber;
    std::array<char,26> text{};
    const auto decimal=c.numbers.decimalPoint(c.numbers.context);
    std::uint32_t length;
    if((std::bit_cast<Word>(value)&0x7fffffffffffffffULL)>=0x7ff0000000000000ULL) {
        std::memcpy(text.data(),"null",5);length=4;
    } else if(value==double(item->valueInteger)) {
        length=std::uint32_t(c.numbers.format(c.numbers.context,text.data(),
            reinterpret_cast<const char *>(c.image+0x15767d),std::uint32_t(item->valueInteger)));
    } else {
        length=std::uint32_t(c.numbers.format(c.numbers.context,text.data(),
            reinterpret_cast<const char *>(c.image+0x157680),std::bit_cast<Word>(value)));
        double parsed=0;
        const auto scanned=c.numbers.scan(c.numbers.context,text.data(),
            reinterpret_cast<const char *>(c.image+0x157687),&parsed);
        const auto mask=_mm_loadu_pd(reinterpret_cast<const double *>(c.image+0x157160));
        const auto left=_mm_set_sd(parsed),right=_mm_set_sd(value);
        const auto maximum=_mm_max_sd(_mm_and_pd(left,mask),_mm_and_pd(right,mask));
        const auto error=_mm_and_pd(_mm_sub_sd(left,right),mask);
        const auto tolerance=_mm_mul_sd(maximum,_mm_load_sd(reinterpret_cast<const double *>(c.image+0x157170)));
        if(scanned!=1 || !(_mm_cvtsd_f64(tolerance)>=_mm_cvtsd_f64(error)))
            length=std::uint32_t(c.numbers.format(c.numbers.context,text.data(),
                reinterpret_cast<const char *>(c.image+0x15768b),std::bit_cast<Word>(value)));
    }
    if(length>25) return 0;
    auto *out=reserve_51400(buffer,Word(length)+1,c);
    if(!out) return 0;
    const auto vectorCount=length>=8 ? length&0x18u : 0u;
    for(std::uint32_t i=0;i<vectorCount;++i) out[i]=std::uint8_t(text[i])==decimal ? char(c.image[0x157180+(i&7)]) : text[i];
    for(auto i=vectorCount;i<length;++i) out[i]=std::uint8_t(text[i])==decimal ? '.' : text[i];
    out[length]=0;buffer->offset+=length;return 1;
}
}
std::uint32_t printValue_4dc80(Node *item,PrintBuffer *buffer,Context &c) {
    if(!item) return 0;
    const auto type=std::uint8_t(item->type);
    if(type==1 || type==2 || type==4) {
        const auto *literal=type==1 ? "false" : type==2 ? "true" : "null";
        const auto length=type==1 ? 6u : 5u;
        auto *out=reserve_51400(buffer,length,c);
        if(!out) return 0;
        recovered_memory_copy(out,literal,length);
        return 1;
    }
    if(type==8) return printNumber(item,buffer,c);
    if(type==16) return printString_514f0(item->valueString,buffer,c);
    if(type==128) {
        if(!item->valueString) return 0;
        const auto length=recovered_string_length_ab840(reinterpret_cast<const std::uint8_t *>(item->valueString))+1;
        auto *out=reserve_51400(buffer,length,c);
        if(!out) return 0;
        recovered_memory_move(out,item->valueString,std::size_t(length));return 1;
    }
    if(type==32) {
        auto *child=item->child;
        auto *out=reserve_51400(buffer,1,c);
        if(!out) return 0;
        *out='[';++buffer->offset;++buffer->depth;
        while(child) {
            if(!printValue_4dc80(child,buffer,c)) return 0;
            updateOffset(buffer);
            if(!child->next) break;
            const auto compact=Word(buffer->formatted==0);
            out=reserve_51400(buffer,compact^3,c);
            if(!out) return 0;
            out[0]=',';out[1]=0;
            if(buffer->formatted) { out[1]=' ';out[2]=0; }
            buffer->offset+=2-compact;
            child=child->next;
        }
        out=reserve_51400(buffer,2,c);
        if(!out) return 0;
        out[0]=']';out[1]=0;--buffer->depth;return 1;
    }
    if(type==64) {
        auto *child=item->child;
        const auto compact=Word(buffer->formatted==0);
        auto *out=reserve_51400(buffer,compact^3,c);
        if(!out) return 0;
        *out='{';++buffer->depth;
        if(buffer->formatted) out[1]='\n';
        buffer->offset+=2-compact;
        while(child) {
            if(buffer->formatted) {
                out=reserve_51400(buffer,buffer->depth,c);
                if(!out) return 0;
                for(Word i=0;i<buffer->depth;++i) out[i]='\t';
                buffer->offset+=buffer->depth;
            }
            if(!printString_514f0(child->name,buffer,c)) return 0;
            updateOffset(buffer);
            const auto colonWidth=buffer->formatted>=1u ? Word{2} : Word{1};
            out=reserve_51400(buffer,colonWidth,c);
            if(!out) return 0;
            out[0]=':';if(buffer->formatted) out[1]='\t';
            buffer->offset+=colonWidth;
            if(!printValue_4dc80(child,buffer,c)) return 0;
            updateOffset(buffer);
            const auto suffixWidth=Word(child->next!=nullptr)+Word(buffer->formatted>=1u);
            out=reserve_51400(buffer,suffixWidth+1,c);
            if(!out) return 0;
            auto *cursor=out;
            if(child->next) *cursor++=',';
            if(buffer->formatted) *cursor++='\n';
            *cursor=0;buffer->offset+=suffixWidth;
            child=child->next;
        }
        out=reserve_51400(buffer,buffer->formatted ? buffer->depth+1 : 2,c);
        if(!out) return 0;
        if(buffer->formatted && buffer->depth!=1) {
            Word count=0;
            do { out[count++]='\t'; } while(count<buffer->depth-1);
            out+=count;
        }
        out[0]='}';out[1]=0;--buffer->depth;return 1;
    }
    return 0;
}
Word Context::invoke(Word target,const Word *arguments,std::size_t count) {
    std::array<Word,5> a{};
    const auto copied=std::min(count,a.size());
    if(copied) std::memcpy(a.data(),arguments,copied*sizeof(Word));
    auto *parent=reinterpret_cast<Node *>(a[0]);
    const auto *name=reinterpret_cast<const char *>(a[1]);
    switch(target) {
    case 0x4e4d0:return address(lookup_4e4d0(parent,name,*this));
    case 0x4d150:return isNumber_4d150(parent);
    case 0x508c0:return isTrue_508c0(parent);
    case 0x4da70:return address(parse_4da70(reinterpret_cast<const char *>(a[0]),*this));
    case 0x4d410:return address(parseLength_4d410(reinterpret_cast<const char *>(a[0]),a[1],reinterpret_cast<const char **>(a[2]),std::uint32_t(a[3]),*this));
    case 0x4d600:return parseValue_4d600(parent,reinterpret_cast<ParseBuffer *>(a[1]),*this);
    case 0x4da00:skipWhitespace_4da00(reinterpret_cast<ParseBuffer *>(a[0]));return 0;
    case 0x50b60:return parseString_50b60(parent,reinterpret_cast<ParseBuffer *>(a[1]),*this);
    case 0x51000:return parseObject_51000(parent,reinterpret_cast<ParseBuffer *>(a[1]),*this);
    case 0x51310:return parseHex_51310(reinterpret_cast<const std::uint8_t *>(a[0]));
    case 0x4d240:deleteTree_4d240(parent,*this);return 0;
    case 0x4d3b0:releaseText_4d3b0(parent,*this);return 0;
    case 0x4e560:return append_4e560(parent,reinterpret_cast<Node *>(a[1]));
    case 0x4e5b0:return attachName_4e5b0(parent,name,reinterpret_cast<Node *>(a[2]),*this);
    case 0x4f590:return address(createObject_4f590(*this));
    case 0x4f480:return address(writeObject_4f480(parent,name,*this));
    case 0x4f5d0:return address(writeArray_4f5d0(parent,name,*this));
    case 0x4ed40:return address(writeBoolean_4ed40(parent,name,std::uint32_t(a[2]),*this));
    case 0x4eeb0:return address(writeNumber_4eeb0(parent,name,std::bit_cast<double>(a[2]),*this));
    case 0x4f080:return address(writeString_4f080(parent,name,reinterpret_cast<const char *>(a[2]),*this));
    case 0x4dad0:return address(printAllocated_4dad0(parent,std::uint32_t(a[1]),*this));
    case 0x4dbe0:return address(printCompact_4dbe0(parent,*this));
    case 0x4dc80:return printValue_4dc80(parent,reinterpret_cast<PrintBuffer *>(a[1]),*this);
    case 0x51400:return address(reserve_51400(reinterpret_cast<PrintBuffer *>(a[0]),a[1],*this));
    case 0x514f0:return printString_514f0(reinterpret_cast<const char *>(a[0]),reinterpret_cast<PrintBuffer *>(a[1]),*this);
    default:return external.invoke(external.context,target,arguments,count);
    }
}
}
