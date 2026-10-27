#include "FontStashGlyph.hpp"
#include "ColorSpace.hpp"
#include "ScalarCeiling.hpp"
#include "Exponential.hpp"
#include <algorithm>
#include <bit>
#include <cstring>
#include <emmintrin.h>
namespace reconstruction::fontstash {
namespace {
template<class T>T read(const void*p,std::ptrdiff_t o){T v;std::memcpy(&v,static_cast<const std::uint8_t*>(p)+o,sizeof v);return v;}
template<class T>void write(void*p,std::ptrdiff_t o,T v){std::memcpy(static_cast<std::uint8_t*>(p)+o,&v,sizeof v);}
std::int32_t add(std::int32_t a,std::int32_t b){return std::bit_cast<std::int32_t>(std::uint32_t(a)+std::uint32_t(b));}
std::int32_t sub(std::int32_t a,std::int32_t b){return std::bit_cast<std::int32_t>(std::uint32_t(a)-std::uint32_t(b));}
std::int32_t mul(std::int32_t a,std::int32_t b){return std::bit_cast<std::int32_t>(std::uint32_t(a)*std::uint32_t(b));}
std::int16_t narrow(std::int32_t v){return std::bit_cast<std::int16_t>(std::uint16_t(v));}
float plus(float a,float b){return _mm_cvtss_f32(_mm_add_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float minus(float a,float b){return _mm_cvtss_f32(_mm_sub_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float times(float a,float b){return _mm_cvtss_f32(_mm_mul_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float divided(float a,float b){return _mm_cvtss_f32(_mm_div_ss(_mm_set_ss(a),_mm_set_ss(b)));}
float floating(std::int32_t v){return _mm_cvtss_f32(_mm_cvtsi32_ss(_mm_setzero_ps(),v));}
std::int32_t integer(float v){return _mm_cvttss_si32(_mm_set_ss(v));}
std::uint16_t big16(const std::uint8_t*p){return (std::uint16_t(p[0])<<8)|p[1];}
std::uint8_t *nodes(std::uint8_t *atlas){return read<std::uint8_t*>(atlas,8);}
void copyNode(std::uint8_t *atlas,std::int32_t destination,std::int32_t source){
    auto *p=nodes(atlas);const auto tail=read<std::uint16_t>(p,std::ptrdiff_t(source)*6+4);write(p,std::ptrdiff_t(destination)*6+4,tail);
    const auto head=read<std::uint32_t>(p,std::ptrdiff_t(source)*6);write(p,std::ptrdiff_t(destination)*6,head);
}
// Native unrolling retains this signed 32-bit fixed-point recurrence. The last
// odd step may use SHR instead of SAR; its byte after SHR7 is identical.
void blurStep(std::uint8_t *pixel,std::int32_t &accumulator,std::int32_t coefficient){
    const auto difference=sub(std::int32_t(*pixel)<<7,accumulator);
    accumulator=add(accumulator,mul(coefficient,difference)>>16);
    *pixel=std::uint8_t(std::uint32_t(accumulator)>>7);
}
void blurColumns(std::uint8_t *pixels,std::int32_t width,std::int32_t height,
    std::int32_t stride,std::int32_t coefficient){
    for(std::int32_t x=0;x<width;++x){
        auto *column=pixels+x;std::int32_t accumulator=0;
        for(std::int32_t y=1;y<height;++y)blurStep(column+std::ptrdiff_t(mul(y,stride)),accumulator,coefficient);
        column[std::ptrdiff_t(mul(sub(height,1),stride))]=0;accumulator=0;
        for(auto y=sub(height,2);y>=0;--y)blurStep(column+std::size_t(std::uint32_t(mul(y,stride))),accumulator,coefficient);
        *column=0;
    }
}
void blurRows(std::uint8_t *pixels,std::int32_t width,std::int32_t height,
    std::int32_t stride,std::int32_t coefficient){
    for(std::int32_t y=0;y<height;++y){
        auto *row=pixels+std::ptrdiff_t(stride)*y;std::int32_t accumulator=0;
        for(std::int32_t x=1;x<width;++x)blurStep(row+x,accumulator,coefficient);
        row[sub(width,1)]=0;accumulator=0;
        for(auto x=sub(width,2);x>=0;--x)blurStep(row+std::size_t(std::uint32_t(x)),accumulator,coefficient);
        *row=0;
    }
}
}
std::int32_t addRectangle_7dd90(std::uint8_t *atlas,std::int32_t width,
    std::int32_t height,std::int32_t *x,std::int32_t *y,const GlyphDependencies&d){
    auto count=read<std::int32_t>(atlas,0x10);if(count<=0)return 0;
    const auto atlasWidth=read<std::int32_t>(atlas,0),atlasHeight=read<std::int32_t>(atlas,4);
    auto *rows=nodes(atlas);auto bestHeight=atlasHeight,bestWidth=atlasWidth;
    std::int32_t best=-1,bestX=-1,bestY=-1;
    for(std::int32_t index=0;index<count;++index){
        const auto nodeX=std::int32_t(read<std::int16_t>(rows,std::ptrdiff_t(index)*6));
        if(add(width,nodeX)>atlasWidth)continue;
        auto nodeY=std::int32_t(read<std::int16_t>(rows,std::ptrdiff_t(index)*6+2));
        auto remaining=width;auto scan=index;bool fit=true;
        while(remaining>0){
            if(scan>=count){fit=false;break;}
            nodeY=std::max(nodeY,std::int32_t(read<std::int16_t>(rows,std::ptrdiff_t(scan)*6+2)));
            if(add(nodeY,height)>atlasHeight){fit=false;break;}
            remaining=sub(remaining,read<std::int16_t>(rows,std::ptrdiff_t(scan)*6+4));++scan;
        }
        if(!fit || nodeY==-1)continue;
        const auto bottom=add(nodeY,height),nodeWidth=std::int32_t(read<std::int16_t>(rows,std::ptrdiff_t(index)*6+4));
        if(bottom<bestHeight || (bottom==bestHeight && nodeWidth<bestWidth)){
            best=index;bestX=nodeX;bestY=nodeY;bestHeight=bottom;bestWidth=nodeWidth;
        }
    }
    if(best==-1)return 0;
    const auto capacity=read<std::int32_t>(atlas,0x14);
    if(count>=capacity){
        const auto next=capacity?add(capacity,capacity):8;write(atlas,0x14,next);
        auto *storage=d.resize_13cf90(d.context,nodes(atlas),std::uint64_t(std::int64_t(next))*6);
        write(atlas,8,storage);if(!storage)return 0;count=read<std::int32_t>(atlas,0x10);
    }
    for(auto index=count;index>best;--index)copyNode(atlas,index,index-1);
    rows=nodes(atlas);write(rows,std::ptrdiff_t(best)*6,narrow(bestX));write(rows,std::ptrdiff_t(best)*6+2,narrow(add(bestY,height)));write(rows,std::ptrdiff_t(best)*6+4,narrow(width));
    count=add(count,1);write(atlas,0x10,count);
    const auto index=add(best,1);
    while(index<count){
        rows=nodes(atlas);
        const auto previousEnd=add(read<std::int16_t>(rows,std::ptrdiff_t(index-1)*6),read<std::int16_t>(rows,std::ptrdiff_t(index-1)*6+4));
        const auto currentX=std::int32_t(read<std::int16_t>(rows,std::ptrdiff_t(index)*6));
        if(previousEnd<=currentX)break;
        write(rows,std::ptrdiff_t(index)*6,narrow(previousEnd));
        const auto remaining=narrow(add(sub(currentX,previousEnd),read<std::int16_t>(rows,std::ptrdiff_t(index)*6+4)));
        write(rows,std::ptrdiff_t(index)*6+4,remaining);if(remaining>0)break;
        for(auto move=index;move<read<std::int32_t>(atlas,0x10)-1;++move)copyNode(atlas,move,move+1);
        count=sub(count,1);write(atlas,0x10,count);
    }
    for(std::int32_t merge=0;merge<count-1;){
        rows=nodes(atlas);
        if(read<std::uint16_t>(rows,std::ptrdiff_t(merge)*6+2)!=read<std::uint16_t>(rows,std::ptrdiff_t(merge+1)*6+2)){++merge;continue;}
        write(rows,std::ptrdiff_t(merge)*6+4,std::uint16_t(read<std::uint16_t>(rows,std::ptrdiff_t(merge)*6+4)+read<std::uint16_t>(rows,std::ptrdiff_t(merge+1)*6+4)));
        for(auto move=merge+1;move<read<std::int32_t>(atlas,0x10)-1;++move)copyNode(atlas,move,move+1);
        count=sub(count,1);write(atlas,0x10,count);
    }
    *x=bestX;*y=bestY;return 1;
}
std::uint8_t *lookupGlyph_6d1d0(std::uint8_t *stash,std::uint8_t *font,
    std::uint32_t codepoint,std::uint32_t sizeBits,std::int16_t blur,
    std::int32_t bitmapRequired,const GlyphDependencies&d){
    const auto size=std::bit_cast<std::int16_t>(std::uint16_t(sizeBits));if(size<2)return nullptr;
    const auto clampedBlur=std::min<std::int16_t>(blur,20);write<std::uint32_t>(stash,0x5088,0);
    auto hash=~(codepoint<<15)+codepoint;hash^=hash>>10;hash*=9;hash^=hash>>6;hash=~(hash<<11)+hash;hash^=hash>>16;
    const auto bucket=hash&255;
    auto index=read<std::int32_t>(font,0x110+bucket*4);std::uint8_t *glyph=nullptr;
    auto *cache=read<std::uint8_t*>(font,0x100);
    while(index!=-1){
        auto *candidate=cache+std::ptrdiff_t(index)*32;
        if(read<std::uint32_t>(candidate,0)==codepoint && read<std::int16_t>(candidate,0xc)==size && read<std::int16_t>(candidate,0xe)==clampedBlur){glyph=candidate;break;}
        index=read<std::int32_t>(candidate,8);
    }
    if(glyph && (bitmapRequired==1 || (read<std::int16_t>(glyph,0x10)>=0 && read<std::int16_t>(glyph,0x12)>=0)))return glyph;
    const auto scaleSize=divided(floating(size),read<float>(d.image,0x2b4ec0));
    auto *renderFont=font;auto glyphIndex=d.mapGlyph_62850(d.context,font,codepoint);
    if(!glyphIndex){
        const auto fallbackCount=read<std::int32_t>(font,0x560);auto *table=read<std::uint8_t*>(stash,0x60);
        for(std::int32_t fallback=0;fallback<fallbackCount;++fallback){
            auto *next=read<std::uint8_t*>(table,std::ptrdiff_t(read<std::int32_t>(font,0x510+fallback*4))*8);
            const auto mapped=d.mapGlyph_62850(d.context,next,codepoint);
            if(mapped){renderFont=next;glyphIndex=mapped;break;}
        }
    }
    auto *fontData=read<std::uint8_t*>(renderFont,8);
    const auto scale=divided(scaleSize,floating(big16(fontData+read<std::int32_t>(renderFont,0x1c)+0x12)));
    const auto padding=std::int32_t(clampedBlur)+2;
    const auto metricCount=big16(fontData+read<std::int32_t>(renderFont,0x24)+0x22);
    auto *metric=fontData+read<std::int32_t>(renderFont,0x28)+std::ptrdiff_t(glyphIndex<metricCount?glyphIndex:metricCount-1)*4;
    const auto advanceBits=std::uint16_t((std::uint16_t(metric[0])<<8)|metric[1]);
    std::int32_t x0=0,y0=0,x1=0,y1=0;
    if(d.glyphBox_63cf0(d.context,renderFont,glyphIndex,&x0,&y0,&x1,&y1)){
        const auto left=integer(recovered_floor_b2a70(plus(times(floating(x0),scale),0),d.image));
        const auto top=integer(recovered_floor_b2a70(plus(times(floating(sub(0,y1)),scale),0),d.image));
        const auto right=integer(recovered_ceiling_float_b2920(plus(times(floating(x1),scale),0),d.image));
        const auto bottom=integer(recovered_ceiling_float_b2920(plus(times(floating(sub(0,y0)),scale),0),d.image));
        x0=left;y0=top;x1=right;y1=bottom;
    }else x0=y0=x1=y1=0;
    const auto boxWidth=sub(x1,x0),boxHeight=sub(y1,y0),width=add(boxWidth,mul(padding,2)),height=add(boxHeight,mul(padding,2));
    std::int32_t atlasX=-1,atlasY=-1;
    if(bitmapRequired==2){
        if(!addRectangle_7dd90(read<std::uint8_t*>(stash,0x68),width,height,&atlasX,&atlasY,d)){
            const auto callback=read<std::uint64_t>(stash,0x5270);if(!callback)return nullptr;
            d.atlasError(d.context,callback,read<std::uint64_t>(stash,0x5278),1,0);
            if(!addRectangle_7dd90(read<std::uint8_t*>(stash,0x68),width,height,&atlasX,&atlasY,d))return nullptr;
        }
    }
    if(!glyph){
        auto capacity=read<std::int32_t>(font,0x108);auto count=read<std::int32_t>(font,0x10c);
        auto *rows=read<std::uint8_t*>(font,0x100);
        if(count>=capacity){capacity=capacity?add(capacity,capacity):8;write(font,0x108,capacity);
            rows=static_cast<std::uint8_t*>(d.resize_13cf90(d.context,rows,std::uint64_t(std::int64_t(capacity))*32));write(font,0x100,rows);count=read<std::int32_t>(font,0x10c);
        }
        write(font,0x10c,add(count,1));glyph=rows+std::ptrdiff_t(count)*32;
        write(glyph,0,codepoint);write(glyph,0xc,size);write(glyph,0xe,clampedBlur);write<std::uint32_t>(glyph,8,0);
        write(glyph,8,read<std::int32_t>(font,0x110+bucket*4));write(font,0x110+bucket*4,count);
    }
    write(glyph,4,glyphIndex);write(glyph,0x10,narrow(atlasX));write(glyph,0x12,narrow(atlasY));write(glyph,0x14,narrow(add(atlasX,width)));write(glyph,0x16,narrow(add(atlasY,height)));
    write(glyph,0x18,narrow(integer(times(times(floating(std::bit_cast<std::int16_t>(advanceBits)),scale),read<float>(d.image,0x2b4ec0)))));
    write(glyph,0x1a,narrow(sub(x0,padding)));write(glyph,0x1c,narrow(sub(y0,padding)));
    if(bitmapRequired==1)return glyph;
    auto stride=read<std::int32_t>(stash,0);
    const auto destinationOffset=add(mul(add(std::int32_t(narrow(atlasY)),padding),stride),add(std::int32_t(narrow(atlasX)),padding));
    auto *destination=read<std::uint8_t*>(stash,0x48)+std::ptrdiff_t(destinationOffset);
    d.bitmap_66f00(d.context,renderFont,destination,boxWidth,boxHeight,stride,scale,scale,0,0,glyphIndex);
    auto *texture=read<std::uint8_t*>(stash,0x48);
    const auto borderOffset=add(mul(read<std::int16_t>(glyph,0x12),read<std::int32_t>(stash,0)),read<std::int16_t>(glyph,0x10));
    auto *pixels=texture+std::ptrdiff_t(borderOffset);
    for(std::int32_t row=0;row<height;++row){pixels[std::ptrdiff_t(read<std::int32_t>(stash,0))*row]=0;pixels[std::ptrdiff_t(add(mul(read<std::int32_t>(stash,0),row),sub(width,1)))]=0;}
    for(std::int32_t column=0;column<width;++column){pixels[column]=0;pixels[std::ptrdiff_t(add(mul(sub(height,1),read<std::int32_t>(stash,0)),column))]=0;}
    if(blur>0){
        write<std::uint32_t>(stash,0x5088,0);stride=read<std::int32_t>(stash,0);
        const auto offset=std::ptrdiff_t(read<std::int16_t>(glyph,0x12))*stride+read<std::int16_t>(glyph,0x10);
        pixels=read<std::uint8_t*>(stash,0x48)+offset;
        const auto sigma=plus(times(floating(clampedBlur),read<float>(d.image,0x2b4ec4)),read<float>(d.image,0x2b4ec8));
        const auto exponential=recovered_exponential_b2b40(divided(read<float>(d.image,0x2b4ecc),sigma),d.image);
        const auto coefficient=integer(times(minus(read<float>(d.image,0x2b4ec8),exponential),read<float>(d.image,0x2b4ed0)));
        blurColumns(pixels,width,height,stride,coefficient);blurRows(pixels,width,height,stride,coefficient);
        blurColumns(pixels,width,height,stride,coefficient);blurRows(pixels,width,height,stride,coefficient);
    }
    const auto gx=std::int32_t(read<std::int16_t>(glyph,0x10)),gy=std::int32_t(read<std::int16_t>(glyph,0x12));
    write(stash,0x50,std::min(read<std::int32_t>(stash,0x50),gx));write(stash,0x54,std::min(read<std::int32_t>(stash,0x54),gy));
    write(stash,0x58,std::max(read<std::int32_t>(stash,0x58),std::int32_t(read<std::int16_t>(glyph,0x14))));write(stash,0x5c,std::max(read<std::int32_t>(stash,0x5c),std::int32_t(read<std::int16_t>(glyph,0x16))));
    return glyph;
}
}
