#include "FontCff.hpp"
#include <bit>
#include <cstring>
#include <immintrin.h>

namespace reconstruction::fontcff {
namespace {
std::int32_t add(std::int32_t a, std::int32_t b) {
    return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));
}
std::int32_t multiply(std::int32_t a, std::int32_t b) {
    return std::bit_cast<std::int32_t>(std::uint32_t(a)*std::uint32_t(b));
}
float sum(float a, float b) { return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b))); }
float negate(float f) { return std::bit_cast<float>(std::bit_cast<std::uint32_t>(f)^0x80000000u); }
std::int32_t integer(float f) { return _mm_cvttss_si32(_mm_set_ss(f)); }
std::uint8_t byte(Buffer &b) {
    if (b.cursor >= b.size) return 0;
    auto value=b.data[b.cursor]; b.cursor=add(b.cursor,1); return value;
}
std::uint32_t bytes(Buffer &b, std::int32_t count) {
    std::uint32_t value=0;
    for(std::int32_t i=0;i<count;++i) value=(value<<8)|byte(b);
    return value;
}
void seek(Buffer &b, std::int32_t cursor) {
    b.cursor=cursor<0 || cursor>b.size ? b.size : cursor;
}
void skip(Buffer &b, std::int32_t count) { seek(b,add(b.cursor,count)); }
Buffer range(const Buffer &b, std::int32_t offset, std::int32_t length) {
    if(offset<0 || length<0 || offset>b.size || length>add(b.size,-offset)) return {};
    return {b.data+offset,0,length};
}
template<class T> T load(const std::uint8_t *p, std::size_t offset) {
    T value; std::memcpy(&value,p+offset,sizeof value); return value;
}
void track(CffContext &c,std::int32_t x,std::int32_t y) {
    if(x>c.maxX || !c.started)c.maxX=x;
    if(y>c.maxY || !c.started)c.maxY=y;
    if(x<c.minX || !c.started)c.minX=x;
    if(y<c.minY || !c.started)c.minY=y;
    c.started=1;
}
void vertex(CffContext &c,std::uint8_t type,std::int32_t x,std::int32_t y,
    std::int32_t cx=0,std::int32_t cy=0,std::int32_t cx1=0,std::int32_t cy1=0) {
    if(c.bounds) {
        track(c,x,y);
        if(type==4) {track(c,cx,cy);track(c,cx1,cy1);}
    } else {
        auto &v=c.vertices[c.count];v.type=type;
        v.x=std::int16_t(x);v.y=std::int16_t(y);
        v.controlX=std::int16_t(cx);v.controlY=std::int16_t(cy);
        v.controlX1=std::int16_t(cx1);v.controlY1=std::int16_t(cy1);
    }
    c.count=add(c.count,1);
}
void relativeLine(CffContext &c,float dx,float dy) {
    c.currentX=sum(c.currentX,dx);c.currentY=sum(c.currentY,dy);
    vertex(c,2,integer(c.currentX),integer(c.currentY));
}
Buffer subroutine(Buffer index,std::int32_t number) {
    seek(index,0);auto count=bytes(index,2);
    auto bias=count>=33900 ? 32768 : count>=1240 ? 1131 : 107;
    auto element=add(number,bias);
    if(std::uint32_t(element)>=count)return {};
    Buffer result;indexElement_7c5d0(&result,&index,element);return result;
}
Buffer glyphSubroutines(std::uint8_t *font,std::int32_t glyph) {
    auto selector=load<Buffer>(font,0x90);seek(selector,0);
    auto format=byte(selector);std::int32_t selected=-1;
    if(format==0) {skip(selector,glyph);selected=byte(selector);}
    else if(format==3) {
        auto count=bytes(selector,2);auto start=bytes(selector,2);
        for(std::uint32_t i=0;i<count;++i) {
            auto value=byte(selector);auto end=bytes(selector,2);
            if(glyph>=std::int32_t(start) && glyph<std::int32_t(end)) {selected=value;break;}
            start=end;
        }
    }
    auto dictionaries=load<Buffer>(font,0x80);Buffer dictionary;
    indexElement_7c5d0(&dictionary,&dictionaries,selected);
    auto cff=load<Buffer>(font,0x40);Buffer result;
    privateSubroutines_7ccb0(&result,&cff,&dictionary);return result;
}
}

// Captured 7C5D0 accepts a mutable copy of the INDEX record; its cursor is an output.
Buffer *indexElement_7c5d0(Buffer *out,Buffer *b,std::int32_t element) {
    seek(*b,0);auto count=bytes(*b,2);auto width=byte(*b);
    skip(*b,multiply(element,width));
    auto first=std::int32_t(bytes(*b,width));auto end=std::int32_t(bytes(*b,width));
    auto offset=add(add(2,multiply(std::int32_t(count+1),width)),first);
    *out=range(*b,offset,add(end,-first));return out;
}
void closeShape_7ca90(CffContext *c) {
    if(c->firstX!=c->currentX || c->firstY!=c->currentY)
        vertex(*c,2,integer(c->firstX),integer(c->firstY));
}
void relativeMove_7c800(CffContext *c,float dx,float dy) {
    closeShape_7ca90(c);
    c->firstX=c->currentX=sum(dx,c->currentX);
    c->firstY=c->currentY=sum(dy,c->currentY);
    vertex(*c,1,integer(c->currentX),integer(c->currentY));
}
void relativeCurve_7c8e0(CffContext *c,float dx1,float dy1,
    float dx2,float dy2,float dx3,float dy3) {
    auto x1=sum(dx1,c->currentX),y1=sum(dy1,c->currentY);
    auto x2=sum(dx2,x1),y2=sum(dy2,y1);
    c->currentX=sum(dx3,x2);c->currentY=sum(dy3,y2);
    vertex(*c,4,integer(c->currentX),integer(c->currentY),
        integer(x1),integer(y1),integer(x2),integer(y2));
}
std::uint32_t readInteger_7cb60(Buffer *b) {
    auto first=byte(*b);
    if(first>=32 && first<=246)return std::uint32_t(std::int32_t(first)-139);
    if(first>=247 && first<=250)return (first-247)*256u+byte(*b)+108;
    if(first>=251 && first<=254)return 0u-(first-251)*256u-byte(*b)-108;
    if(first==28)return bytes(*b,2);
    if(first==29)return bytes(*b,4);
    return 0;
}
void dictionaryIntegers_7cd90(Buffer *b,std::int32_t key,
    std::int32_t count,std::uint32_t *output) {
    seek(*b,0);
    while(b->cursor<b->size) {
        auto start=b->cursor;
        while(b->cursor<b->size && b->data[b->cursor]>=28) {
            if(b->data[b->cursor]==30) {
                skip(*b,1);
                while(b->cursor<b->size) {auto n=byte(*b);if((n&15)==15 || (n>>4)==15)break;}
            } else readInteger_7cb60(b);
        }
        auto end=b->cursor;auto op=std::int32_t(byte(*b));
        if(op==12)op=byte(*b)|0x100;
        if(op==key) {
            auto operands=range(*b,start,add(end,-start));
            // Native enters this loop once even when requested count is zero.
            if(operands.cursor<operands.size) {
                std::uint32_t i=0;
                do {output[i++]=readInteger_7cb60(&operands);}
                while(std::uint64_t(i)<std::uint32_t(count) && operands.cursor<operands.size);
            }
            return;
        }
    }
}
Buffer *readIndex_7cf40(Buffer *out,Buffer *b) {
    auto start=b->cursor;auto count=bytes(*b,2);
    if(count) {auto width=byte(*b);skip(*b,multiply(width,std::int32_t(count)));skip(*b,add(std::int32_t(bytes(*b,width)),-1));}
    *out=range(*b,start,add(b->cursor,-start));return out;
}
Buffer *privateSubroutines_7ccb0(Buffer *out,Buffer *cff,Buffer *dict) {
    std::uint32_t location[2]={0,0},subrs=0;
    dictionaryIntegers_7cd90(dict,18,2,location);
    if(!location[0] || !location[1]) {*out={};return out;}
    auto privateDict=range(*cff,std::int32_t(location[1]),std::int32_t(location[0]));
    dictionaryIntegers_7cd90(&privateDict,19,1,&subrs);
    if(!subrs){*out={};return out;}
    seek(*cff,add(std::int32_t(location[1]),std::int32_t(subrs)));
    return readIndex_7cf40(out,cff);
}

std::int32_t runCharString_7b3b0(std::uint8_t *font,std::int32_t glyph,CffContext *c) {
    std::int32_t header=1,maskBits=0,height=0,sp=0;bool hasSubrs=false;
    float operands[48];Buffer returns[10],localSubrs=load<Buffer>(font,0x70);
    auto strings=load<Buffer>(font,0x50);Buffer b;indexElement_7c5d0(&b,&strings,glyph);
    while(b.cursor<b.size) {
        auto op=byte(b);std::int32_t i=0;bool clear=true;
        switch(op) {
        case 19:case 20:
            if(header)maskBits=add(maskBits,sp/2);
            header=0;skip(b,add(maskBits,7)/8);break;
        case 1:case 3:case 18:case 23:maskBits=add(maskBits,sp/2);break;
        case 21:if(sp<2)return 0;relativeMove_7c800(c,operands[sp-2],operands[sp-1]);header=0;break;
        case 4:if(sp<1)return 0;relativeMove_7c800(c,0,operands[sp-1]);header=0;break;
        case 22:if(sp<1)return 0;relativeMove_7c800(c,operands[sp-1],0);header=0;break;
        case 5:
            if(sp<2)return 0;
            for(;i+1<sp;i+=2)relativeLine(*c,operands[i],operands[i+1]);break;
        case 6:case 7: {
            if(sp<1)return 0;bool horizontal=op==6;
            for(;i<sp;++i) {relativeLine(*c,horizontal?operands[i]:0,horizontal?0:operands[i]);horizontal=!horizontal;}
            break;
        }
        case 30:case 31: {
            if(sp<4)return 0;bool horizontal=op==31;
            for(;i+3<sp;i+=4) {
                if(horizontal)relativeCurve_7c8e0(c,operands[i],0,operands[i+1],operands[i+2],sp-i==5?operands[i+4]:0,operands[i+3]);
                else relativeCurve_7c8e0(c,0,operands[i],operands[i+1],operands[i+2],operands[i+3],sp-i==5?operands[i+4]:0);
                horizontal=!horizontal;
            }
            break;
        }
        case 8:
            if(sp<6)return 0;
            for(;i+5<sp;i+=6)relativeCurve_7c8e0(c,operands[i],operands[i+1],operands[i+2],operands[i+3],operands[i+4],operands[i+5]);break;
        case 24:
            if(sp<8)return 0;
            for(;i+5<sp-2;i+=6)relativeCurve_7c8e0(c,operands[i],operands[i+1],operands[i+2],operands[i+3],operands[i+4],operands[i+5]);
            if(i+1>=sp)return 0;relativeLine(*c,operands[i],operands[i+1]);break;
        case 25:
            if(sp<8)return 0;
            for(;i+1<sp-6;i+=2)relativeLine(*c,operands[i],operands[i+1]);
            if(i+5>=sp)return 0;relativeCurve_7c8e0(c,operands[i],operands[i+1],operands[i+2],operands[i+3],operands[i+4],operands[i+5]);break;
        case 26:case 27: {
            if(sp<4)return 0;float first=0;
            if(sp&1)first=operands[i++];
            for(;i+3<sp;i+=4) {
                if(op==27)relativeCurve_7c8e0(c,operands[i],first,operands[i+1],operands[i+2],operands[i+3],0);
                else relativeCurve_7c8e0(c,first,operands[i],operands[i+1],operands[i+2],0,operands[i+3]);
                first=0;
            }
            break;
        }
        case 10:case 29: {
            if(op==10 && !hasSubrs) {if(load<Buffer>(font,0x90).size)localSubrs=glyphSubroutines(font,glyph);hasSubrs=true;}
            if(sp<1 || height>=10)return 0;
            auto number=integer(operands[--sp]);returns[height]=b;
            b=subroutine(op==10?localSubrs:load<Buffer>(font,0x60),number);
            if(b.size==0)return 0;++height;b.cursor=0;clear=false;break;
        }
        case 11:if(height<=0)return 0;b=returns[--height];clear=false;break;
        case 14:closeShape_7ca90(c);return 1;
        case 12: {
            auto escape=byte(b);
            if(escape==34) {
                if(sp<7)return 0;
                relativeCurve_7c8e0(c,operands[0],0,operands[1],operands[2],operands[3],0);
                relativeCurve_7c8e0(c,operands[4],0,operands[5],negate(operands[2]),operands[6],0);
            } else if(escape==35) {
                if(sp<13)return 0;
                relativeCurve_7c8e0(c,operands[0],operands[1],operands[2],operands[3],operands[4],operands[5]);
                relativeCurve_7c8e0(c,operands[6],operands[7],operands[8],operands[9],operands[10],operands[11]);
            } else if(escape==36) {
                if(sp<9)return 0;
                relativeCurve_7c8e0(c,operands[0],operands[1],operands[2],operands[3],operands[4],0);
                relativeCurve_7c8e0(c,operands[5],0,operands[6],operands[7],operands[8],negate(sum(sum(operands[1],operands[3]),operands[7])));
            } else if(escape==37) {
                if(sp<11)return 0;
                auto dx=sum(sum(sum(sum(operands[0],operands[2]),operands[4]),operands[6]),operands[8]);
                auto dy=sum(sum(sum(sum(operands[1],operands[3]),operands[5]),operands[7]),operands[9]);
                auto absX=std::bit_cast<float>(std::bit_cast<std::uint32_t>(dx)&0x7fffffffu);
                auto absY=std::bit_cast<float>(std::bit_cast<std::uint32_t>(dy)&0x7fffffffu);
                auto dx6=absX>absY?operands[10]:negate(dx),dy6=absX>absY?negate(dy):operands[10];
                relativeCurve_7c8e0(c,operands[0],operands[1],operands[2],operands[3],operands[4],operands[5]);
                relativeCurve_7c8e0(c,operands[6],operands[7],operands[8],operands[9],dx6,dy6);
            } else return 0;
            break;
        }
        default: {
            if(op!=255 && op!=28 && op<32)return 0;
            float value;
            if(op==255)value=_mm_cvtss_f32(_mm_mul_ss(_mm_cvtsi32_ss(_mm_setzero_ps(),std::int32_t(bytes(b,4))),_mm_set_ss(0x1p-16f)));
            else {skip(b,-1);value=float(std::int16_t(readInteger_7cb60(&b)));}
            if(sp>=48)return 0;operands[sp++]=value;clear=false;break;
        }
        }
        if(clear)sp=0;
    }
    return 0;
}
}
