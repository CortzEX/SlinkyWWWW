#include "FontStashRuntime.hpp"
#include "ByteStrings.hpp"
#include "ColorSpace.hpp"
#include <bit>
#include <cstring>
#include <emmintrin.h>
namespace reconstruction::fontstash {
namespace {
template<class T> T read(const void *p,std::ptrdiff_t offset) {T value;std::memcpy(&value,static_cast<const std::uint8_t*>(p)+offset,sizeof value);return value;}
template<class T> void write(void *p,std::ptrdiff_t offset,T value) {std::memcpy(static_cast<std::uint8_t*>(p)+offset,&value,sizeof value);}
float add(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float sub(float a,float b){return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float mul(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float div(float a,float b){return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float minimum(float a,float b){return _mm_cvtss_f32(_mm_min_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float maximum(float a,float b){return _mm_cvtss_f32(_mm_max_ss(_mm_set_ss(a),_mm_set_ss(b)));}
std::int32_t integer(float value){return _mm_cvttss_si32(_mm_set_ss(value));}
float floating(std::int32_t value){return _mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),value));}
float constant(const Dependencies&d,std::ptrdiff_t rva){return read<float>(d.image,rva);}
std::uint8_t *state(std::uint8_t *stash){return stash+0x5074+std::ptrdiff_t(read<std::int32_t>(stash,0x526c))*24;}
std::uint8_t *selectedFont(std::uint8_t *stash,std::uint8_t *settings){
    const auto index=read<std::int32_t>(settings,0);
    if(index<0 || index>=read<std::int32_t>(stash,0x74))return nullptr;
    return read<std::uint8_t*>(read<void*>(stash,0x60),std::ptrdiff_t(index)*8);
}
std::uint16_t unitsPerEm(std::uint8_t *font){auto value=read<std::uint16_t>(read<void*>(font,8),std::ptrdiff_t(read<std::int32_t>(font,0x1c))+0x12);return std::uint16_t((value<<8)|(value>>8));}
// Each caller retains its own captured constant addresses and multiplication order.
float verticalOffset(std::uint8_t *stash,std::uint8_t *font,std::uint32_t alignment,
    float size,std::ptrdiff_t ten,std::ptrdiff_t half,std::ptrdiff_t negativeTen,
    std::ptrdiff_t negativeHalf,bool sizeFirst,const Dependencies&d) {
    const bool downward=(read<std::uint8_t>(stash,8)&1)!=0;
    float metric=0;bool negateDivisor=false;
    if(alignment&8){metric=read<float>(font,0xf0);negateDivisor=!downward;}
    else if(alignment&16){metric=mul(add(read<float>(font,0xf0),read<float>(font,0xf4)),constant(d,downward?half:negativeHalf));}
    else if((alignment&0x60)==0x20){metric=read<float>(font,0xf4);negateDivisor=!downward;}
    else return 0;
    return div(sizeFirst?mul(size,metric):mul(metric,size),constant(d,negateDivisor?negativeTen:ten));
}
std::uint32_t decodeByte(std::uint32_t &codepoint,std::uint32_t oldState,std::uint8_t byte,const Dependencies&d) {
    const auto type=read<std::uint8_t>(d.image,0x2b6150+byte);
    codepoint=oldState?(codepoint<<6)|(byte&0x3fu):(0xffu>>(type&31))&byte;
    return read<std::uint8_t>(d.image,0x2b6150+0x100+std::size_t(oldState)+type);
}
}
float textBounds_6cde0(std::uint8_t *stash,float x,float y,const char *text,
    const char *end,float *bounds,const Dependencies&d) {
    auto *settings=state(stash);auto *font=selectedFont(stash,settings);
    if(!font || !read<std::uint64_t>(font,0xe0))return 0;
    const auto sizeBits=std::uint32_t(integer(mul(read<float>(settings,8),constant(d,0x2b4eb0))));
    const auto size=floating(std::bit_cast<std::int16_t>(std::uint16_t(sizeBits)));
    auto alignment=read<std::uint32_t>(settings,4);
    y=add(y,verticalOffset(stash,font,alignment,size,0x2b4eb0,0x2b4eb4,0x2b4eb8,0x2b4ebc,false,d));
    const auto blur=std::int16_t(integer(read<float>(settings,0x10)));
    const auto initialX=x;float minX=x,maxX=x,minY=y,maxY=y;
    if(!end)end=text+recovered_string_length_ab840(reinterpret_cast<const std::uint8_t*>(text));
    if(text!=end) {
        const auto scale=div(div(size,constant(d,0x2b4eb0)),floating(unitsPerEm(font)));
        std::uint32_t utf8=0,codepoint=0;std::int32_t previous=-1;
        do {
            utf8=decodeByte(codepoint,utf8,std::uint8_t(*text),d);
            if(!utf8) {
                auto *glyph=d.glyph_6d1d0(d.context,stash,font,codepoint,sizeBits,blur,1);
                if(!glyph)previous=-1;
                else {
                    GlyphQuad quad;
                    glyphQuad_6de40(stash,font,previous,glyph,scale,read<float>(settings,0x14),&x,&y,&quad,d);
                    float lower,upper;
                    if(read<std::uint8_t>(stash,8)&1){lower=quad.y0;upper=quad.y1;}else{lower=quad.y1;upper=quad.y0;}
                    minY=minimum(lower,minY);
                    maxY=upper>maxY?upper:maxY;
                    minX=minimum(quad.x0,minX);maxX=maximum(quad.x1,maxX);
                    previous=read<std::int32_t>(glyph,4);
                }
            }
            ++text;
        } while(text!=end);
        alignment=read<std::uint32_t>(settings,4);
    }
    const auto advance=sub(x,initialX);
    if(!(alignment&1)) {
        if(alignment&4){minX=sub(minX,advance);maxX=sub(maxX,advance);}
        else if(alignment&2){const auto offset=mul(constant(d,0x2b4ebc),advance);minX=add(minX,offset);maxX=add(maxX,offset);}
    }
    if(bounds){bounds[0]=minX;bounds[1]=minY;bounds[2]=maxX;bounds[3]=maxY;}
    return advance;
}
void lineBounds_6ebc0(std::uint8_t *stash,float y,float *minimumY,float *maximumY,const Dependencies&d) {
    auto *settings=state(stash);auto *font=selectedFont(stash,settings);
    if(!font || !read<std::uint64_t>(font,0xe0))return;
    const auto size=floating(std::int16_t(integer(mul(read<float>(settings,8),constant(d,0x2b4f34)))));
    y=add(y,verticalOffset(stash,font,read<std::uint32_t>(settings,4),size,0x2b4f34,0x2b4f38,0x2b4f3c,0x2b4f40,false,d));
    if(read<std::uint8_t>(stash,8)&1) {
        y=sub(y,div(mul(read<float>(font,0xf0),size),constant(d,0x2b4f34)));
        *minimumY=y;
        *maximumY=add(div(mul(size,read<float>(font,0xf8)),constant(d,0x2b4f34)),y);
    } else {
        y=add(div(mul(read<float>(font,0xf4),size),constant(d,0x2b4f34)),y);
        *maximumY=y;
        *minimumY=sub(y,div(mul(size,read<float>(font,0xf8)),constant(d,0x2b4f34)));
    }
}
std::int32_t iteratorInit_6dff0(std::uint8_t *stash,TextIterator *iterator,float x,float y,
    const char *text,const char *end,std::int32_t bitmapRequired,const Dependencies&d) {
    auto *settings=state(stash);
    for(int offset=64;offset>=0;offset-=16)std::memset(reinterpret_cast<std::uint8_t*>(iterator)+offset,0,16);
    auto *font=selectedFont(stash,settings);if(!font)return 0;
    iterator->font=font;if(!read<std::uint64_t>(font,0xe0))return 0;
    const auto size=integer(mul(read<float>(settings,8),constant(d,0x2b4edc)));
    iterator->size=std::int16_t(size);iterator->blur=std::int16_t(integer(read<float>(settings,0x10)));
    iterator->scale=div(div(floating(size),constant(d,0x2b4edc)),floating(unitsPerEm(font)));
    auto alignment=read<std::uint32_t>(settings,4);
    if(!(alignment&1)) {
        if(alignment&4)x=sub(x,textBounds_6cde0(stash,x,y,text,end,nullptr,d));
        else if(alignment&2)x=add(x,mul(textBounds_6cde0(stash,x,y,text,end,nullptr,d),constant(d,0x2b4ee0)));
    }
    alignment=read<std::uint32_t>(settings,4);
    y=add(y,verticalOffset(stash,iterator->font,alignment,floating(iterator->size),0x2b4edc,0x2b4ee4,0x2b4ee8,0x2b4ee0,true,d));
    if(!end)end=text+recovered_string_length_ab840(reinterpret_cast<const std::uint8_t*>(text));
    iterator->nextX=x;iterator->x=x;iterator->nextY=y;iterator->y=y;
    iterator->spacing=read<float>(settings,0x14);iterator->start=text;iterator->next=text;iterator->end=end;
    iterator->codepoint=0;iterator->previousGlyph=-1;iterator->bitmapRequired=bitmapRequired;return 1;
}
std::int32_t iteratorNext_6e2d0(std::uint8_t *stash,TextIterator *iterator,GlyphQuad *quad,const Dependencies&d) {
    const auto *next=iterator->next;const auto *end=iterator->end;iterator->start=next;
    if(next==end)return 0;
    const char *byte;
    do {
        byte=next;
        iterator->utf8State=decodeByte(iterator->codepoint,iterator->utf8State,std::uint8_t(*byte),d);
        if(!iterator->utf8State) {
            const auto positions=read<std::uint64_t>(iterator,8);write(iterator,0,positions);
            auto *glyph=d.glyph_6d1d0(d.context,stash,iterator->font,iterator->codepoint,
                std::uint16_t(iterator->size),iterator->blur,iterator->bitmapRequired);
            if(glyph) {
                glyphQuad_6de40(stash,iterator->font,iterator->previousGlyph,glyph,iterator->scale,
                    iterator->spacing,&iterator->nextX,&iterator->nextY,quad,d);
                iterator->previousGlyph=read<std::int32_t>(glyph,4);
            }else iterator->previousGlyph=-1;
            break;
        }
        next=byte+1;
    } while(next!=end);
    iterator->next=byte+1;return 1;
}
void glyphQuad_6de40(std::uint8_t *stash,std::uint8_t *font,std::int32_t previous,
    const std::uint8_t *glyph,float scale,float spacing,float *x,float *y,GlyphQuad *quad,const Dependencies&d) {
    if(previous!=-1) {
        const auto kern=d.kerning_64170(d.context,font,previous,read<std::int32_t>(glyph,4));
        const auto delta=floating(integer(add(add(mul(floating(kern),scale),spacing),constant(d,0x2b4ed4))));
        *x=add(delta,*x);
    }
    const auto xOffset=floating(std::int16_t(std::uint16_t(read<std::uint16_t>(glyph,0x1a)+1)));
    const auto yOffset=floating(std::int16_t(std::uint16_t(read<std::uint32_t>(glyph,0x1c)+1)));
    const auto top=floating(std::int32_t(read<std::int16_t>(glyph,0x12))+1);
    const auto bottom=floating(std::int32_t(read<std::int16_t>(glyph,0x16))-1);
    const auto left=floating(std::int32_t(read<std::int16_t>(glyph,0x10))+1);
    const auto right=floating(std::int32_t(read<std::int16_t>(glyph,0x14))-1);
    const auto x0=recovered_floor_b2a70(add(xOffset,*x),d.image);
    const bool downward=(read<std::uint8_t>(stash,8)&1)!=0;
    const auto baseY=*y;quad->x0=x0;
    const auto y0=recovered_floor_b2a70(downward?add(baseY,yOffset):sub(baseY,yOffset),d.image);
    const auto y1=downward?sub(add(y0,bottom),top):add(sub(y0,bottom),top);
    const auto x1=sub(add(x0,right),left);
    quad->y0=y0;quad->x1=x1;quad->y1=y1;
    const auto inverseWidth=read<float>(stash,0x40),inverseHeight=read<float>(stash,0x44);
    quad->s0=mul(left,inverseWidth);quad->t0=mul(top,inverseHeight);quad->s1=mul(right,inverseWidth);quad->t1=mul(bottom,inverseHeight);
    const auto advance=floating(integer(add(div(floating(read<std::int16_t>(glyph,0x18)),constant(d,0x2b4ed8)),constant(d,0x2b4ed4))));
    *x=add(advance,*x);
}
}
