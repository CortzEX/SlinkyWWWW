#include "FontTables.hpp"
#include "FontCff.hpp"
#include "../native/verified/module_memory.hpp"
#include <bit>
#include <cstring>
#include <immintrin.h>

namespace reconstruction::fonttables {
namespace {
template<class T> T read(const void *p) { T value; std::memcpy(&value,p,sizeof value); return value; }
template<class T> void write(void *p,T value) { std::memcpy(p,&value,sizeof value); }
std::uint16_t big16(const std::uint8_t *p) { return std::uint16_t((std::uint16_t(p[0])<<8)|p[1]); }
std::int32_t signed16(const std::uint8_t *p) { return std::int16_t(big16(p)); }
std::uint32_t big32(const std::uint8_t *p) { return (std::uint32_t(p[0])<<24)|(std::uint32_t(p[1])<<16)|(std::uint32_t(p[2])<<8)|p[3]; }
std::int32_t wrap(std::uint32_t n) { return std::bit_cast<std::int32_t>(n); }
std::int32_t glyphOffset(std::uint8_t *font,std::int32_t glyph) {
    if(glyph>=read<std::int32_t>(font+0x14) || read<std::int32_t>(font+0x3c)>1) return -1;
    auto *data=read<std::uint8_t*>(font+8);
    auto *loca=data+read<std::int32_t>(font+0x18);
    const auto index=std::int64_t(glyph);
    const auto first=read<std::int32_t>(font+0x3c)==0 ? std::uint32_t(big16(loca+index*2))*2 : big32(loca+index*4);
    const auto second=read<std::int32_t>(font+0x3c)==0 ? std::uint32_t(big16(loca+index*2+2))*2 : big32(loca+index*4+4);
    if(first==second) return -1;
    return wrap(std::uint32_t(read<std::int32_t>(font+0x20))+first);
}
std::int32_t coverageIndex(const std::uint8_t *table,std::int32_t glyph) {
    const auto format=big16(table),count=big16(table+2);
    std::int32_t low=0,high=std::int32_t(count)-1;
    if(format==1) {
        while(low<=high) { const auto mid=(low+high)>>1;const auto value=big16(table+4+std::int64_t(mid)*2);
            if(glyph<std::int32_t(value)) high=mid-1;
            else if(std::uint32_t(glyph)<=value) return mid;
            else low=mid+1;
        }
    } else if(format==2) {
        while(low<=high) { const auto mid=(low+high)>>1;auto *row=table+4+std::int64_t(mid)*6;
            const auto first=big16(row),last=big16(row+2);
            if(glyph<std::int32_t(first)) high=mid-1;
            else if(std::uint32_t(glyph)<=last) return wrap(std::uint32_t(glyph)-first+big16(row+4));
            else low=mid+1;
        }
    }
    return -1;
}
}

// Native 0x62850. Signed codepoint gates in formats 0/4 are intentional.
std::int32_t mapGlyph_62850(std::uint8_t *font,std::uint32_t codepoint) {
    auto *data=read<std::uint8_t*>(font+8);
    const auto offset=read<std::uint32_t>(font+0x38);
    auto *table=data+offset;const auto format=big16(table);
    const auto signedCodepoint=wrap(codepoint);
    if(format==0) {
        if(signedCodepoint>=std::int32_t(big16(table+2))-6) return 0;
        return table[6+std::int64_t(signedCodepoint)];
    }
    if(format==6) {
        const auto first=big16(table+6),count=big16(table+8);
        if(codepoint<first || codepoint>=std::uint32_t(first)+count) return 0;
        return big16(table+10+std::uint64_t(codepoint-first)*2);
    }
    if(format==4) {
        if(signedCodepoint>0xffff) return 0;
        const auto segments=big16(table+6)>>1;
        auto range=std::uint32_t(big16(table+8)>>1);
        auto selector=big16(table+10);
        const auto shift=std::uint32_t(big16(table+12)>>1);
        const auto endCounts=offset+14u;auto search=endCounts;
        if(signedCodepoint>=std::int32_t(big16(data+search+shift*2))) search+=shift*2;
        search-=2;
        while(selector) {range>>=1;if(signedCodepoint>std::int32_t(big16(data+search+range*2))) search+=range*2;--selector;}
        search+=2;
        const auto item=std::uint16_t((search-endCounts)>>1);
        const auto first=big16(table+16+segments*2+std::uint32_t(item)*2);
        if(signedCodepoint<std::int32_t(first)) return 0;
        auto *rangeWord=table+16+segments*6+std::uint32_t(item)*2;
        const auto relative=big16(rangeWord);
        if(relative==0) return std::uint16_t(codepoint+big16(table+16+segments*4+std::uint32_t(item)*2));
        return big16(rangeWord+relative+std::int64_t(wrap((codepoint-first)*2)));
    }
    if(format==12 || format==13) {
        std::int32_t low=0,high=wrap(big32(table+12));
        while(low<high) {
            const auto mid=low+std::int32_t(std::uint32_t(high-low)>>1);
            auto *group=table+16+std::uint32_t(mid)*12;
            const auto first=big32(group),last=big32(group+4);
            if(codepoint<first) high=mid;
            else if(codepoint>last) low=mid+1;
            else return wrap(big32(group+8)+(format==12 ? codepoint-first : 0u));
        }
    }
    return 0;
}

// Native 0x7D0E0. This build returns -1 for unassigned glyphs, unlike the
// supplemental upstream implementation's class-zero fallback.
std::int32_t glyphClass_7d0e0(const std::uint8_t *table,std::int32_t glyph) {
    const auto format=big16(table);
    if(format==1) {
        const auto first=big16(table+2),count=big16(table+4);
        if(glyph<std::int32_t(first) || std::uint32_t(glyph)>=std::uint32_t(first)+count) return -1;
        return big16(table+6+std::int64_t(glyph-first)*2);
    }
    if(format==2) {
        std::int32_t low=0,high=std::int32_t(big16(table+2))-1;
        while(low<=high) { const auto mid=(low+high)>>1;auto *row=table+4+std::int64_t(mid)*6;
            if(glyph<std::int32_t(big16(row))) high=mid-1;
            else if(std::uint32_t(glyph)<=big16(row+2)) return big16(row+4);
            else low=mid+1;
        }
    }
    return -1;
}

// Native 0x64170: a present GPOS table suppresses the classic kern fallback.
std::int32_t kerning_64170(std::uint8_t *font,std::int32_t previous,std::int32_t current) {
    const auto gpos=read<std::int32_t>(font+0x30);
    auto *data=read<std::uint8_t*>(font+8);
    if(gpos) {
        auto *table=data+gpos;
        if(big16(table)!=1 || (table[2]|table[3])!=0) return 0;
        auto *lookups=table+big16(table+8);
        const auto count=big16(lookups);
        for(std::uint32_t i=0;i<count;++i) {
            auto *lookup=lookups+big16(lookups+2+i*2);
            if(big16(lookup)!=2) continue;
            const auto subtables=big16(lookup+4);
            for(std::uint32_t j=0;j<subtables;++j) {
                auto *pair=lookup+big16(lookup+6+j*2);
                const auto positionFormat=big16(pair);
                const auto covered=coverageIndex(pair+big16(pair+2),previous);
                if(covered==-1) continue;
                if(positionFormat==1) {
                    if(big16(pair+4)!=4 || (pair[6]|pair[7])!=0) return 0;
                    auto *values=pair+big16(pair+10+std::int64_t(covered)*2);
                    std::int32_t low=0,high=std::int32_t(big16(values))-1;
                    while(low<=high) {const auto mid=(low+high)>>1;auto *record=values+2+std::int64_t(mid)*4;
                        if(current<std::int32_t(big16(record))) high=mid-1;
                        else if(std::uint32_t(current)<=big16(record)) return signed16(record+2);
                        else low=mid+1;
                    }
                } else if(positionFormat==2) {
                    const auto class1=glyphClass_7d0e0(pair+big16(pair+8),previous);
                    const auto class2=glyphClass_7d0e0(pair+big16(pair+10),current);
                    if(big16(pair+4)!=4 || (pair[6]|pair[7])!=0) return 0;
                    const auto count1=big16(pair+12),count2=big16(pair+14);
                    if(class1<0 || std::uint32_t(class1)>=count1 || class2<0 || std::uint32_t(class2)>=count2) continue;
                    return signed16(pair+16+std::uint32_t(class1)*count2*2+std::uint32_t(class2)*2);
                } else continue;
            }
        }
        return 0;
    }
    const auto kern=read<std::int32_t>(font+0x2c);
    if(!kern) return 0;
    auto *table=data+kern;
    if((table[2]|table[3])==0 || big16(table+8)!=1) return 0;
    const auto key=(std::uint32_t(previous)<<16)|std::uint32_t(current);
    std::int32_t low=0,high=std::int32_t(big16(table+10))-1;
    while(low<=high) {const auto mid=(low+high)>>1;auto *record=table+18+std::int64_t(mid)*6;
        if(key<big32(record)) high=mid-1;
        else if(key<=big32(record)) return signed16(record+4);
        else low=mid+1;
    }
    return 0;
}

std::int32_t glyphBox_63cf0(std::uint8_t *font,std::int32_t glyph,
    std::int32_t *x0,std::int32_t *y0,std::int32_t *x1,std::int32_t *y1) {
    if(read<std::int32_t>(font+0x4c)!=0) {
        fontcff::CffContext context{};context.bounds=1;
        const auto success=fontcff::runCharString_7b3b0(font,glyph,&context);
        if(x0) *x0=success ? context.minX : 0;
        if(y0) *y0=success ? context.minY : 0;
        if(x1) *x1=success ? context.maxX : 0;
        if(y1) *y1=success ? context.maxY : 0;
        return 1;
    }
    const auto offset=glyphOffset(font,glyph);if(offset<0) return 0;
    auto *data=read<std::uint8_t*>(font+8)+std::uint32_t(offset);
    if(x0) *x0=signed16(data+2);
    if(y0) *y0=signed16(data+4);
    if(x1) *x1=signed16(data+6);
    if(y1) *y1=signed16(data+8);
    return 1;
}

namespace {
Vertex *scratch(std::uint8_t *font,std::uint32_t rounded,const ShapeDependencies &deps,bool testBuffer) {
    auto *stash=read<std::uint8_t*>(font);
    const auto used=read<std::int32_t>(stash+0x5088);
    const auto next=wrap(std::uint32_t(used)+rounded);
    if(next>=0x17701) {
        const auto target=read<std::uint64_t>(stash+0x5270);
        if(target) deps.scratchError(deps.context,target,read<std::uint64_t>(stash+0x5278),2);
        return nullptr;
    }
    auto *buffer=read<std::uint8_t*>(stash+0x5080);
    write(stash+0x5088,next);
    if(testBuffer && !buffer) return nullptr;
    return reinterpret_cast<Vertex*>(std::uintptr_t(buffer)+std::int64_t(used));
}
void vertex(Vertex *p,std::uint8_t type,std::int32_t x,std::int32_t y,std::int32_t cx,std::int32_t cy) {
    p->type=type;p->x=std::int16_t(x);p->y=std::int16_t(y);
    p->controlX=std::int16_t(cx);p->controlY=std::int16_t(cy);
}
std::int32_t closeContour(Vertex *vertices,std::int32_t count,bool wasOff,bool firstOff,
    std::int32_t x,std::int32_t y,std::int32_t firstCX,std::int32_t firstCY,
    std::int32_t cx,std::int32_t cy) {
    if(firstOff) {
        if(wasOff) vertex(vertices+count++,3,(cx+firstCX)>>1,(cy+firstCY)>>1,cx,cy);
        vertex(vertices+count++,3,x,y,firstCX,firstCY);
    } else if(wasOff) vertex(vertices+count++,3,x,y,cx,cy);
    else vertex(vertices+count++,2,x,y,0,0);
    return count;
}
std::int16_t transformed(float value,bool saturate) {
    const auto integer=_mm_cvttss_si32(_mm_set_ss(value));
    if(saturate) return integer>32767 ? 32767 : integer<-32768 ? -32768 : std::int16_t(integer);
    return std::int16_t(integer);
}
}

// Native 0x62BB0. All storage comes from the installed font's stash scratch
// arena. Reserved vertex bytes are retained, as in the captured stores.
std::int32_t getGlyphShape_62bb0(std::uint8_t *font,std::int32_t glyph,
    Vertex **output,const ShapeDependencies &deps) {
    if(read<std::int32_t>(font+0x4c)!=0) {
        fontcff::CffContext count{},drawing{};count.bounds=1;
        if(!fontcff::runCharString_7b3b0(font,glyph,&count)) {*output=nullptr;return 0;}
        drawing.vertices=scratch(font,(std::uint32_t(count.count)*14+15)&~15u,deps,false);
        *output=drawing.vertices;
        if(!fontcff::runCharString_7b3b0(font,glyph,&drawing)) {*output=nullptr;return 0;}
        return drawing.count;
    }
    const auto offset=glyphOffset(font,glyph);
    auto *bytes=offset>=0 ? read<std::uint8_t*>(font+8) : nullptr;
    *output=nullptr;if(offset<0) return 0;
    auto *record=bytes+std::uint32_t(offset);
    const auto contours=signed16(record);
    if(contours>0) {
        auto *ends=record+10;
        const auto last=std::int32_t(big16(ends+contours*2-2));
        const auto pointsCount=last+1;
        auto *vertices=scratch(font,((std::uint32_t(last+2*contours)*14+29)&0x7ffffff0u),deps,true);
        if(!vertices) return 0;
        auto *points=record+12+contours*2+big16(record+10+contours*2);
        const auto temporary=2*contours;std::uint8_t flags=0,repeats=0;
        for(std::int32_t i=0;i<pointsCount;++i) {
            if(repeats==0) {flags=*points++;if(flags&8) repeats=*points++;} else --repeats;
            vertices[temporary+i].type=flags;
        }
        std::int32_t coordinate=0;
        for(std::int32_t i=0;i<pointsCount;++i) {
            flags=vertices[temporary+i].type;
            if(flags&2) {const auto delta=*points++;coordinate=wrap(std::uint32_t(coordinate)+((flags&16) ? delta : -std::uint32_t(delta)));}
            else if(!(flags&16)) {coordinate=wrap(std::uint32_t(coordinate)+std::uint32_t(signed16(points)));points+=2;}
            vertices[temporary+i].x=std::int16_t(coordinate);
        }
        coordinate=0;
        for(std::int32_t i=0;i<pointsCount;++i) {
            flags=vertices[temporary+i].type;
            if(flags&4) {const auto delta=*points++;coordinate=wrap(std::uint32_t(coordinate)+((flags&32) ? delta : -std::uint32_t(delta)));}
            else if(!(flags&32)) {coordinate=wrap(std::uint32_t(coordinate)+std::uint32_t(signed16(points)));points+=2;}
            vertices[temporary+i].y=std::int16_t(coordinate);
        }
        std::int32_t count=0,nextMove=0,contour=0,x=0,y=0,cx=0,cy=0,firstCX=0,firstCY=0;
        bool wasOff=false,firstOff=false;
        for(std::int32_t i=0;i<pointsCount;++i) {
            const auto currentFlags=vertices[temporary+i].type;
            const auto px=std::int32_t(vertices[temporary+i].x),py=std::int32_t(vertices[temporary+i].y);
            if(nextMove==i) {
                if(i) count=closeContour(vertices,count,wasOff,firstOff,x,y,firstCX,firstCY,cx,cy);
                firstOff=!(currentFlags&1);
                if(firstOff) {
                    firstCX=px;firstCY=py;
                    if(!(vertices[temporary+i+1].type&1)) {
                        x=(px+vertices[temporary+i+1].x)>>1;y=(py+vertices[temporary+i+1].y)>>1;
                    } else {x=vertices[temporary+i+1].x;y=vertices[temporary+i+1].y;++i;}
                } else {x=px;y=py;}
                vertex(vertices+count++,1,x,y,0,0);wasOff=false;
                nextMove=1+big16(ends+contour++*2);
            } else if(!(currentFlags&1)) {
                if(wasOff) vertex(vertices+count++,3,(cx+px)>>1,(cy+py)>>1,cx,cy);
                cx=px;cy=py;wasOff=true;
            } else {
                if(wasOff) vertex(vertices+count++,3,px,py,cx,cy);
                else vertex(vertices+count++,2,px,py,0,0);
                wasOff=false;
            }
        }
        count=closeContour(vertices,count,wasOff,firstOff,x,y,firstCX,firstCY,cx,cy);
        *output=vertices;return count;
    }
    if(contours==0) return 0;
    auto *component=record+10;Vertex *vertices=nullptr;std::int32_t count=0;
    const auto unit=read<float>(deps.image+0x2b4c44),fraction=read<float>(deps.image+0x2b4c40);
    std::uint16_t flags;
    do {
        flags=big16(component);const auto componentGlyph=big16(component+2);component+=4;
        float a=unit,b=0,c=0,d=unit,tx=0,ty=0;
        if(flags&2) {
            if(flags&1) {tx=float(signed16(component));ty=float(signed16(component+2));component+=4;}
            else {tx=float(std::int8_t(component[0]));ty=float(std::int8_t(component[1]));component+=2;}
        }
        if(flags&8) {a=d=float(signed16(component))*fraction;component+=2;}
        else if(flags&64) {a=float(signed16(component))*fraction;d=float(signed16(component+2))*fraction;component+=4;}
        else if(flags&128) {
            a=float(signed16(component))*fraction;b=float(signed16(component+2))*fraction;
            c=float(signed16(component+4))*fraction;d=float(signed16(component+6))*fraction;component+=8;
        }
        Vertex *child=nullptr;const auto childCount=getGlyphShape_62bb0(font,componentGlyph,&child,deps);
        if(childCount<=0) continue;
        const auto sx=_mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(a*a+b*b)));
        const auto sy=_mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(c*c+d*d)));
        const auto vectorCount=childCount>=9 ? childCount-(childCount%8 ? childCount%8 : 8) : 0;
        for(std::int32_t i=0;i<childCount;++i) {
            // The native eight-vertex loop uses a mixture of PACKSSDW and
            // low-word stores. Its remainder uses PACKSSDW for all four fields.
            const bool packed=i>=vectorCount || (i%8>=1 && i%8<=3);
            const bool packedCX=packed && (i>=vectorCount || i%8!=2);
            const auto x=float(child[i].x),y=float(child[i].y);
            const auto cx=float(child[i].controlX),cy=float(child[i].controlY);
            child[i].x=transformed(sx*(c*y+a*x+tx),packed);
            child[i].y=transformed(sy*(b*x+d*y+ty),packed);
            child[i].controlX=transformed(sx*(c*cy+a*cx+tx),packedCX);
            child[i].controlY=transformed(sy*(b*cx+d*cy+ty),packed);
        }
        const auto next=wrap(std::uint32_t(count)+std::uint32_t(childCount));
        auto *joined=scratch(font,(std::uint32_t(next)*14+15)&~15u,deps,true);
        if(!joined) return 0;
        if(count>0) recovered_memory_copy(joined,vertices,std::size_t(count)*14);
        recovered_memory_copy(reinterpret_cast<std::uint8_t*>(joined)+std::size_t(count)*14,child,std::size_t(childCount)*14);
        count=next;vertices=joined;
    } while(flags&32);
    *output=vertices;return count;
}
}
